#ifndef SOURCEMETA_BLAZE_TRACESUITE_H_
#define SOURCEMETA_BLAZE_TRACESUITE_H_

#include <sourcemeta/blaze/compiler.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>  // std::ranges::find, std::ranges::sort
#include <filesystem> // std::filesystem::path, std::filesystem::recursive_directory_iterator, std::filesystem::directory_entry
#include <initializer_list> // std::initializer_list
#include <optional>         // std::optional, std::nullopt
#include <sstream>          // std::ostringstream
#include <stdexcept>        // std::runtime_error
#include <string>           // std::string
#include <string_view>      // std::string_view
#include <utility>          // std::pair, std::move
#include <vector>           // std::vector

// The schemas a fixture supplies for the URIs its own schema reaches for, so
// that reviewing one fixture means reading one file. Whatever it does not
// name, the default resolver answers
class FixtureResolver {
public:
  explicit FixtureResolver(const sourcemeta::core::JSON &fixture) {
    const auto *entry{fixture.try_at("resolve")};
    if (entry != nullptr) {
      this->schemas = *entry;
    }
  }

  auto operator()(const std::string_view identifier) const
      -> sourcemeta::core::SchemaResolverResult {
    const auto *match{
        this->schemas.try_at(sourcemeta::core::JSON::StringView{identifier})};
    if (match != nullptr) {
      return *match;
    }

    return sourcemeta::core::schema_resolver(identifier);
  }

private:
  sourcemeta::core::JSON schemas{sourcemeta::core::JSON::make_object()};
};

// What a suite directory expects every fixture it holds to be. A fixture of one
// kind left in the other kind's directory would otherwise be read as something
// it is not
enum class FixtureKind { Trace, Error };

// The whole key set is checked, rather than only the keys a runner goes on to
// read, because that is what keeps an error fixture out of a trace directory
// and the other way around. These are runtime checks rather than assertions on
// purpose: CI builds these tests with `NDEBUG` set, which would leave a
// misplaced fixture to be read as whatever the runner assumed it was
inline auto check_fixture_keys(
    const std::filesystem::path &path, const sourcemeta::core::JSON &fixture,
    const std::initializer_list<std::string_view> required,
    const std::initializer_list<std::string_view> optional) -> void {
  if (!fixture.is_object()) {
    throw std::runtime_error{path.string() +
                             ": expected the fixture to be an object"};
  }

  for (const auto key : required) {
    if (!fixture.defines(key)) {
      throw std::runtime_error{path.string() + ": expected the fixture to " +
                               "define `" + std::string{key} + "`"};
    }
  }

  for (const auto &entry : fixture.as_object()) {
    if (std::ranges::find(required, entry.first) == required.end() &&
        std::ranges::find(optional, entry.first) == optional.end()) {
      throw std::runtime_error{path.string() + ": the fixture defines `" +
                               entry.first +
                               "`, which no fixture of this kind takes"};
    }
  }
}

// A fixture says what it is through its file name, so a comment is only there
// to say why it exists. One line keeps it to that, rather than letting prose
// that belongs in a document grow inside the data
inline auto check_fixture_comment(const std::filesystem::path &path,
                                  const sourcemeta::core::JSON &fixture)
    -> void {
  const auto *comment{fixture.try_at("comment")};
  if (comment == nullptr) {
    return;
  }

  if (!comment->is_string() || comment->empty()) {
    throw std::runtime_error{path.string() +
                             ": expected `comment` to be a non-empty string"};
  }

  if (comment->to_string().find('\n') != sourcemeta::core::JSON::String::npos) {
    throw std::runtime_error{path.string() +
                             ": expected `comment` to be a single line"};
  }
}

// Compilation starts at the root unless a fixture says otherwise, so an
// `entrypoint` that is present but says nothing would ask for the default in a
// way that reads as a deliberate choice
inline auto check_fixture_entrypoint(const std::filesystem::path &path,
                                     const sourcemeta::core::JSON &fixture)
    -> void {
  const auto *entrypoint{fixture.try_at("entrypoint")};
  if (entrypoint == nullptr) {
    return;
  }

  if (!entrypoint->is_string() || entrypoint->empty()) {
    throw std::runtime_error{
        path.string() + ": expected `entrypoint` to be a non-empty string"};
  }
}

// A directory already supplies the dialect its fixtures speak when they do not
// say, so one that repeats that dialect says nothing, and one that is present
// but empty asks for no dialect at all in a way that reads as a choice
inline auto check_fixture_default_dialect(const std::filesystem::path &path,
                                          const sourcemeta::core::JSON &fixture)
    -> void {
  const auto *dialect{fixture.try_at("defaultDialect")};
  if (dialect == nullptr) {
    return;
  }

  if (!dialect->is_string() || dialect->empty()) {
    throw std::runtime_error{
        path.string() + ": expected `defaultDialect` to be a non-empty string"};
  }
}

// The default resolver already answers for every official URI, so a `resolve`
// that is present names something it does not, and one that is empty asks for
// nothing in a way that reads as a deliberate choice
inline auto check_fixture_resolve(const std::filesystem::path &path,
                                  const sourcemeta::core::JSON &fixture)
    -> void {
  const auto *resolve{fixture.try_at("resolve")};
  if (resolve == nullptr) {
    return;
  }

  if (!resolve->is_object() || resolve->empty()) {
    throw std::runtime_error{
        path.string() +
        ": expected `resolve` to be a non-empty object of URIs to schemas"};
  }

  for (const auto &entry : resolve->as_object()) {
    if (!entry.second.is_object() && !entry.second.is_boolean()) {
      throw std::runtime_error{path.string() +
                               ": expected `resolve` to name a schema for `" +
                               entry.first + "`"};
    }
  }
}

inline auto check_fixture(const std::filesystem::path &path,
                          const FixtureKind kind,
                          const sourcemeta::core::JSON &fixture) -> void {
  if (kind == FixtureKind::Trace) {
    check_fixture_keys(
        path, fixture, {"schema", "instance", "valid", "fast", "exhaustive"},
        {"comment", "defaultDialect", "entrypoint", "resolve", "tweaks"});
  } else {
    check_fixture_keys(path, fixture, {"schema", "error"},
                       {"comment", "tweaks"});
  }

  check_fixture_comment(path, fixture);
  check_fixture_entrypoint(path, fixture);
  check_fixture_default_dialect(path, fixture);
  check_fixture_resolve(path, fixture);
}

// The compiler knobs a fixture asks for, if it asks for any. Only the knobs the
// suites exercise are understood, so a misspelled one is refused rather than
// quietly ignored, which would leave a fixture asserting the behaviour of a
// compilation it never asked for.
//
// `Tweaks::annotations` holds views rather than strings, so the fixture this
// reads from has to outlive what comes back
inline auto fixture_tweaks(const std::string &name,
                           const sourcemeta::core::JSON &fixture)
    -> std::optional<sourcemeta::blaze::Tweaks> {
  const auto *entry{fixture.try_at("tweaks")};
  if (entry == nullptr) {
    return std::nullopt;
  }

  if (!entry->is_object() || entry->empty()) {
    throw std::runtime_error{name +
                             ": expected `tweaks` to be a non-empty object"};
  }

  sourcemeta::blaze::Tweaks tweaks;
  for (const auto &property : entry->as_object()) {
    if (property.first == "formatAssertion") {
      if (!property.second.is_boolean()) {
        throw std::runtime_error{
            name + ": expected `formatAssertion` to be a boolean"};
      }

      tweaks.format_assertion = property.second.to_boolean();
    } else if (property.first == "annotations") {
      if (!property.second.is_array()) {
        throw std::runtime_error{name +
                                 ": expected `annotations` to be an array"};
      }

      auto &keywords{tweaks.annotations.emplace()};
      for (const auto &keyword : property.second.as_array()) {
        if (!keyword.is_string()) {
          throw std::runtime_error{
              name + ": expected `annotations` to hold keyword names"};
        }

        keywords.emplace(keyword.to_string());
      }
    } else {
      throw std::runtime_error{name + ": `tweaks` does not take `" +
                               property.first + "`"};
    }
  }

  return tweaks;
}

// Where in the schema a fixture asks compilation to begin, which is the root
// for every fixture that names nothing
inline auto fixture_entrypoint(const sourcemeta::core::JSON &fixture)
    -> sourcemeta::core::JSON::String {
  const auto *entrypoint{fixture.try_at("entrypoint")};
  return entrypoint == nullptr ? sourcemeta::core::JSON::String{}
                               : entrypoint->to_string();
}

// What dialect a schema speaks when it declares none. A fixture that names one
// overrides what its directory supplies, which is how a schema that leaves
// `$schema` out on purpose sits beside the ones that declare it
inline auto fixture_default_dialect(const sourcemeta::core::JSON &fixture,
                                    const std::string &fallback)
    -> std::string {
  const auto *dialect{fixture.try_at("defaultDialect")};
  return dialect == nullptr ? fallback : dialect->to_string();
}

// Hyper-schema is the same draft as the validation dialect it builds on, and a
// suite directory holds the fixtures of either
inline auto
validation_base_dialect(const sourcemeta::core::SchemaBaseDialect base_dialect)
    -> sourcemeta::core::SchemaBaseDialect {
  using Base = sourcemeta::core::SchemaBaseDialect;
  switch (base_dialect) {
    case Base::JSON_SCHEMA_2020_12_HYPER:
      return Base::JSON_SCHEMA_2020_12;
    case Base::JSON_SCHEMA_2019_09_HYPER:
      return Base::JSON_SCHEMA_2019_09;
    case Base::JSON_SCHEMA_DRAFT_7_HYPER:
      return Base::JSON_SCHEMA_DRAFT_7;
    case Base::JSON_SCHEMA_DRAFT_6_HYPER:
      return Base::JSON_SCHEMA_DRAFT_6;
    case Base::JSON_SCHEMA_DRAFT_4_HYPER:
      return Base::JSON_SCHEMA_DRAFT_4;
    case Base::JSON_SCHEMA_DRAFT_3_HYPER:
      return Base::JSON_SCHEMA_DRAFT_3;
    default:
      return base_dialect;
  }
}

// Which dialect a fixture speaks is what decides the directory it belongs in.
// The base dialect is what to compare, rather than the `$schema` the fixture
// spells, because a fixture may legitimately declare a hyper-schema, a custom
// meta-schema that extends the dialect, or a URI that only normalisation
// settles, and every one of those still belongs to its directory's dialect
inline auto check_fixture_base_dialect(
    const std::filesystem::path &path, const sourcemeta::core::JSON &fixture,
    const sourcemeta::core::SchemaBaseDialect expected,
    const std::string &default_dialect,
    const sourcemeta::core::SchemaResolver &resolver) -> void {
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Root, fixture.at("schema"),
      sourcemeta::core::schema_walker, resolver, default_dialect};

  const auto location{frame.root_location()};
  if (!location.has_value()) {
    throw std::runtime_error{
        path.string() + ": expected the schema to frame as a single schema"};
  }

  const auto actual{validation_base_dialect(location->get().base_dialect)};
  if (actual != expected) {
    std::ostringstream message;
    message << path.string() << ": the schema speaks " << actual
            << ", but this directory holds " << expected << " ones";
    throw std::runtime_error{message.str()};
  }
}

// The fixtures a suite directory holds, each one paired with the name its file
// gives it. A directory that holds none is a mistake rather than an empty
// suite: a fixture left in the wrong place would otherwise never run, and
// nobody would notice
inline auto
read_fixtures(const std::filesystem::path &directory, const FixtureKind kind,
              const sourcemeta::core::SchemaBaseDialect base_dialect,
              const std::string &default_dialect)
    -> std::vector<std::pair<std::string, sourcemeta::core::JSON>> {
  std::vector<std::filesystem::path> paths;
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::recursive_directory_iterator{directory}) {
    if (entry.is_regular_file() && entry.path().extension() == ".json") {
      paths.push_back(entry.path());
    }
  }

  if (paths.empty()) {
    throw std::runtime_error{"No fixtures found at " + directory.string()};
  }

  // Directory iteration order is unspecified, so the tests a suite registers
  // would otherwise come out in a different order on every machine
  std::ranges::sort(paths);

  std::vector<std::pair<std::string, sourcemeta::core::JSON>> result;
  result.reserve(paths.size());
  for (const auto &path : paths) {
    auto fixture{sourcemeta::core::read_json(path)};
    check_fixture(path, kind, fixture);
    check_fixture_base_dialect(
        path, fixture, base_dialect,
        fixture_default_dialect(fixture, default_dialect),
        FixtureResolver{fixture});
    result.emplace_back(path.stem().string(), std::move(fixture));
  }

  return result;
}

#endif
