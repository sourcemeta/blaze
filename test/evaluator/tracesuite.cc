#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

#include <algorithm> // std::ranges::all_of, std::ranges::find, std::ranges::find_if, std::ranges::sort
#include <array>     // std::array
#include <cassert>   // assert
#include <cstdint>   // std::uint8_t
#include <cstdio>    // std::fprintf
#include <filesystem> // std::filesystem::path, std::filesystem::recursive_directory_iterator, std::filesystem::directory_entry
#include <initializer_list> // std::initializer_list
#include <map>              // std::map
#include <optional>         // std::optional, std::nullopt
#include <sstream>          // std::ostringstream
#include <stdexcept>        // std::runtime_error
#include <string>           // std::string
#include <string_view>      // std::string_view
#include <utility>          // std::pair, std::move, std::unreachable
#include <vector>           // std::vector

static auto to_instruction_index(const std::string_view name)
    -> sourcemeta::blaze::InstructionIndex {
  constexpr auto COUNT{sizeof(sourcemeta::blaze::INSTRUCTION_NAMES) /
                       sizeof(std::string_view)};
  for (std::uint8_t index = 0; index < COUNT; index++) {
    if (sourcemeta::blaze::INSTRUCTION_NAMES[index] == name) {
      return static_cast<sourcemeta::blaze::InstructionIndex>(index);
    }
  }

  // GCC 13, which this project still supports, ships no <print>, so these stay
  // on the C stdio calls that every supported toolchain has
  // NOLINTNEXTLINE(modernize-use-std-print)
  std::fprintf(stderr, "Unknown instruction type: %.*s\n",
               static_cast<int>(name.size()), name.data());
  std::unreachable();
}

namespace {

// The schemas a fixture supplies for the URIs its own schema reaches for, so
// that reviewing one fixture means reading one file. Whatever it does not
// name, the default resolver answers
class FixtureResolver {
public:
  explicit FixtureResolver(const sourcemeta::core::JSON &fixture) {
    const auto *entry{fixture.try_at("resolve")};
    if (entry != nullptr) {
      this->schemas_ = *entry;
    }
  }

  auto operator()(const std::string_view identifier) const
      -> sourcemeta::core::SchemaResolverResult {
    const auto *match{
        this->schemas_.try_at(sourcemeta::core::JSON::StringView{identifier})};
    if (match != nullptr) {
      return *match;
    }

    return sourcemeta::core::schema_resolver(identifier);
  }

private:
  sourcemeta::core::JSON schemas_{sourcemeta::core::JSON::make_object()};
};

// What a suite directory expects every fixture it holds to be, named after the
// directory that holds it. A fixture of one kind left in another kind's
// directory would otherwise be read as something it is not:
//
//   - `valid`   compiles and evaluates, and the fixture says what it reports
//   - `invalid` is no schema of its dialect, so the compiler turns it down
//   - `error`   is a schema, but asking for it raises something
enum class FixtureKind : std::uint8_t { Trace, Invalid, Error };

// The whole key set is checked, rather than only the keys a runner goes on to
// read, because that is what keeps an error fixture out of a trace directory
// and the other way around. These are runtime checks rather than assertions on
// purpose: CI builds these tests with `NDEBUG` set, which would leave a
// misplaced fixture to be read as whatever the runner assumed it was
auto check_fixture_keys(const std::filesystem::path &path,
                        const sourcemeta::core::JSON &fixture,
                        const std::initializer_list<std::string_view> required,
                        const std::initializer_list<std::string_view> optional)
    -> void {
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
auto check_fixture_comment(const std::filesystem::path &path,
                           const sourcemeta::core::JSON &fixture) -> void {
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
auto check_fixture_entrypoint(const std::filesystem::path &path,
                              const sourcemeta::core::JSON &fixture) -> void {
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
auto check_fixture_default_dialect(const std::filesystem::path &path,
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
auto check_fixture_resolve(const std::filesystem::path &path,
                           const sourcemeta::core::JSON &fixture) -> void {
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

// A fixture may name the schema it puts under test by URI rather than writing
// it out, which is how the official meta-schemas get tested without a copy of
// one going stale in the suite. Anything else has to be a schema as written
auto check_fixture_schema(const std::filesystem::path &path,
                          const FixtureKind kind,
                          const sourcemeta::core::JSON &fixture) -> void {
  const auto &schema{fixture.at("schema")};
  if (!schema.is_string()) {
    return;
  }

  if (kind != FixtureKind::Trace) {
    throw std::runtime_error{
        path.string() + ": only a trace fixture may name its schema by URI"};
  }

  if (schema.empty()) {
    throw std::runtime_error{path.string() +
                             ": expected `schema` to name a URI, not nothing"};
  }
}

// What an `error` fixture may name, and what each one carries. Every one of
// them reports a message, and the rest is what that exception answers for
// beyond it, so a fixture records everything the exception knows rather than
// only the part a test happened to look at
struct ThrownShape {
  std::string_view type;
  bool base{false};
  bool location{false};
  bool identifier{false};
  bool regex{false};
};

constexpr std::array<ThrownShape, 7> KNOWN_THROWN{
    {{.type = "CompilerError", .base = true, .location = true},
     {.type = "CompilerInvalidEntryPoint", .identifier = true},
     {.type = "CompilerInvalidRegexError",
      .base = true,
      .location = true,
      .regex = true},
     {.type = "CompilerReferenceTargetNotSchemaError",
      .location = true,
      .identifier = true},
     {.type = "EvaluationError"},
     {.type = "SchemaError"},
     {.type = "SchemaReferenceError", .location = true, .identifier = true}}};

// What the suite knows about an exception that names itself this way, or
// nothing where it knows of none. This hands back a pointer rather than an
// iterator because what an iterator into an array is spelled as differs
// between standard libraries
auto known_thrown(const std::string_view type) -> const ThrownShape * {
  for (const auto &candidate : KNOWN_THROWN) {
    if (candidate.type == type) {
      return &candidate;
    }
  }

  return nullptr;
}

// A fixture carries the fields its exception answers for and no others, so a
// field that moves between exceptions cannot sit unnoticed on the wrong one,
// and one that is forgotten shows up as a fixture that says less than it could
auto check_fixture_thrown(const std::filesystem::path &path,
                          const sourcemeta::core::JSON &fixture) -> void {
  const auto &error{fixture.at("error")};
  if (!error.is_object() || !error.defines("type") ||
      !error.at("type").is_string()) {
    throw std::runtime_error{path.string() +
                             ": expected `error` to name a `type`"};
  }

  const auto &type{error.at("type").to_string()};
  const auto *const match{known_thrown(type)};
  if (match == nullptr) {
    throw std::runtime_error{path.string() + ": `" + type +
                             "` is no exception this suite knows"};
  }

  for (const auto &[field, expected] :
       {std::pair{"base", match->base}, std::pair{"location", match->location},
        std::pair{"identifier", match->identifier},
        std::pair{"regex", match->regex}}) {
    if (error.defines(field) != expected) {
      throw std::runtime_error{
          path.string() + ": `" + type + "` " +
          (expected ? "answers for `" : "does not answer for `") + field +
          "`, so the fixture " + (expected ? "has to name it" : "cannot")};
    }
  }

  if (!error.defines("message") || !error.at("message").is_string()) {
    throw std::runtime_error{path.string() +
                             ": expected `error` to carry a `message`"};
  }

  for (const auto &entry : error.as_object()) {
    if (entry.first != "type" && entry.first != "message" &&
        entry.first != "base" && entry.first != "location" &&
        entry.first != "identifier" && entry.first != "regex") {
      throw std::runtime_error{path.string() + ": the error defines `" +
                               entry.first + "`, which no exception takes"};
    }
  }
}

// A schema may be wrapped in a document that is not one, and `paths` says
// where the schemas inside it are, exactly as a frame takes them. A frame
// given none treats the root as the schema, which is what every other fixture
// means, so naming an empty set would ask for nothing
auto check_fixture_paths(const std::filesystem::path &path,
                         const sourcemeta::core::JSON &fixture) -> void {
  const auto *paths{fixture.try_at("paths")};
  if (paths == nullptr) {
    if (fixture.defines("defaultBase")) {
      throw std::runtime_error{
          path.string() +
          ": `defaultBase` only means something beside `paths`"};
    }

    return;
  }

  if (!paths->is_array() || paths->empty()) {
    throw std::runtime_error{
        path.string() +
        ": expected `paths` to be a non-empty array of JSON Pointers"};
  }

  for (const auto &entry : paths->as_array()) {
    if (!entry.is_string()) {
      throw std::runtime_error{path.string() +
                               ": expected every `paths` entry to be a string"};
    }
  }

  const auto *base{fixture.try_at("defaultBase")};
  if (base != nullptr && (!base->is_string() || base->empty())) {
    throw std::runtime_error{
        path.string() + ": expected `defaultBase` to be a non-empty string"};
  }
}

auto check_fixture(const std::filesystem::path &path, const FixtureKind kind,
                   const sourcemeta::core::JSON &fixture) -> void {
  if (kind == FixtureKind::Trace) {
    check_fixture_keys(path, fixture,
                       {"schema", "instance", "valid", "fast", "exhaustive"},
                       {"comment", "defaultBase", "defaultDialect",
                        "entrypoint", "paths", "resolve", "tweaks"});
  } else if (kind == FixtureKind::Invalid) {
    check_fixture_keys(path, fixture, {"schema", "error"},
                       {"comment", "tweaks"});
  } else {
    check_fixture_keys(path, fixture, {"schema", "error"},
                       {"comment", "defaultBase", "defaultDialect",
                        "entrypoint", "instance", "paths", "resolve",
                        "tweaks"});
  }

  if (kind == FixtureKind::Error) {
    check_fixture_thrown(path, fixture);
  }

  check_fixture_schema(path, kind, fixture);
  check_fixture_comment(path, fixture);
  check_fixture_entrypoint(path, fixture);
  check_fixture_default_dialect(path, fixture);
  check_fixture_resolve(path, fixture);
  check_fixture_paths(path, fixture);
}

// The compiler knobs a fixture asks for, if it asks for any. Only the knobs the
// suites exercise are understood, so a misspelled one is refused rather than
// quietly ignored, which would leave a fixture asserting the behaviour of a
// compilation it never asked for.
//
// `Tweaks::annotations` holds views rather than strings, so the fixture this
// reads from has to outlive what comes back
auto fixture_tweaks(const std::string &name,
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
auto fixture_entrypoint(const sourcemeta::core::JSON &fixture)
    -> sourcemeta::core::JSON::String {
  const auto *entrypoint{fixture.try_at("entrypoint")};
  return entrypoint == nullptr ? sourcemeta::core::JSON::String{}
                               : entrypoint->to_string();
}

// What dialect a schema speaks when it declares none. A fixture that names one
// overrides what its directory supplies, which is how a schema that leaves
// `$schema` out on purpose sits beside the ones that declare it
auto fixture_default_dialect(const sourcemeta::core::JSON &fixture,
                             const std::string &fallback) -> std::string {
  const auto *dialect{fixture.try_at("defaultDialect")};
  return dialect == nullptr ? fallback : dialect->to_string();
}

// The schema a fixture puts under test, fetched where the fixture names it by
// URI rather than writing it out
auto fixture_schema(const sourcemeta::core::JSON &fixture,
                    const sourcemeta::core::SchemaResolver &resolver)
    -> sourcemeta::core::JSON {
  const auto &schema{fixture.at("schema")};
  if (!schema.is_string()) {
    return schema;
  }

  auto resolved{resolver(schema.to_string())};
  if (!resolved.has_value()) {
    throw std::runtime_error{
        "Could not resolve the schema the fixture names: " +
        schema.to_string()};
  }

  return std::move(resolved).to_owned();
}

// Hyper-schema is the same draft as the validation dialect it builds on, and a
// suite directory holds the fixtures of either
// The locations inside a wrapper that are schemas, owned here because a frame
// borrows the tokens of the pointers it is handed rather than copying them
auto fixture_pointers(const sourcemeta::core::JSON &fixture)
    -> std::vector<sourcemeta::core::Pointer> {
  std::vector<sourcemeta::core::Pointer> pointers;
  const auto *paths{fixture.try_at("paths")};
  if (paths == nullptr) {
    return pointers;
  }

  pointers.reserve(paths->size());
  for (const auto &entry : paths->as_array()) {
    pointers.push_back(sourcemeta::core::to_pointer(entry.to_string()));
  }

  return pointers;
}

// The same, as a frame takes them. Whatever was handed in has to outlive the
// result and the frame built from it
auto fixture_paths(const std::vector<sourcemeta::core::Pointer> &pointers)
    -> sourcemeta::core::SchemaFrame::Paths {
  sourcemeta::core::SchemaFrame::Paths paths;
  paths.reserve(pointers.size());
  for (const auto &pointer : pointers) {
    paths.push_back(sourcemeta::core::to_weak_pointer(pointer));
  }

  return paths;
}

// What the wrapper answers to, where the fixture gives it an identity for its
// entrypoint and its references to be relative to
auto fixture_default_base(const sourcemeta::core::JSON &fixture)
    -> sourcemeta::core::JSON::String {
  const auto *base{fixture.try_at("defaultBase")};
  return base == nullptr ? sourcemeta::core::JSON::String{} : base->to_string();
}

auto validation_base_dialect(
    const sourcemeta::core::SchemaBaseDialect base_dialect)
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
auto check_one_base_dialect(const std::filesystem::path &path,
                            const sourcemeta::core::JSON &schema,
                            const sourcemeta::core::SchemaBaseDialect expected,
                            const std::string &default_dialect,
                            const sourcemeta::core::SchemaResolver &resolver)
    -> void {
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Root, schema,
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

// Where a wrapper holds the schemas, each of them has to speak the directory's
// dialect, which is what this says of the schema itself otherwise. What the
// entrypoint names is no help here, because a fixture may exist to show that
// it names nothing
auto check_fixture_base_dialect(
    const std::filesystem::path &path, const sourcemeta::core::JSON &fixture,
    const sourcemeta::core::SchemaBaseDialect expected,
    const std::string &default_dialect,
    const sourcemeta::core::SchemaResolver &resolver) -> void {
  const auto schema{fixture_schema(fixture, resolver)};
  const auto pointers{fixture_pointers(fixture)};
  if (pointers.empty()) {
    check_one_base_dialect(path, schema, expected, default_dialect, resolver);
    return;
  }

  for (const auto &pointer : pointers) {
    const auto *embedded{sourcemeta::core::try_get(schema, pointer)};
    if (embedded == nullptr) {
      throw std::runtime_error{path.string() +
                               ": expected a schema at the path: " +
                               sourcemeta::core::to_string(pointer)};
    }

    check_one_base_dialect(path, *embedded, expected, default_dialect,
                           resolver);
  }
}

// The fixtures a suite directory holds, each one paired with the name its file
// gives it. A directory that holds none is a mistake rather than an empty
// suite: a fixture left in the wrong place would otherwise never run, and
// nobody would notice
auto read_fixtures(const std::filesystem::path &directory,
                   const FixtureKind kind,
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

// Compiling a meta-schema is expensive, so each one is compiled on first use
// and reused for every case in its suite
auto metaschema_template(const std::string &uri)
    -> const sourcemeta::blaze::Template & {
  static std::map<std::string, sourcemeta::blaze::Template> cache;
  const auto match{cache.find(uri)};
  if (match != cache.cend()) {
    return match->second;
  }

  const auto metaschema{sourcemeta::core::schema_resolver(uri)};
  assert(metaschema.has_value());
  return cache
      .emplace(uri, sourcemeta::blaze::compile(
                        metaschema.value(), sourcemeta::core::schema_walker,
                        sourcemeta::core::schema_resolver,
                        sourcemeta::blaze::default_schema_compiler,
                        sourcemeta::blaze::Mode::FastValidation))
      .first->second;
}

// Whether the schema is one its own dialect considers well-formed. Compilation
// must agree with this: a schema the meta-schema accepts must compile, and one
// it rejects must not
// Compiling the schema a fixture puts under test. A fixture that names the
// locations inside a wrapper is framed first, because a frame is the only way
// to say which of them are schemas, and the entrypoint picks the one to compile
auto compile_fixture(const std::string &name,
                     const sourcemeta::core::JSON &data,
                     const sourcemeta::core::JSON &schema,
                     const std::string &default_dialect,
                     const sourcemeta::blaze::Mode mode,
                     const sourcemeta::core::SchemaResolver &resolver)
    -> sourcemeta::blaze::Template {
  const auto pointers{fixture_pointers(data)};
  if (pointers.empty()) {
    return sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker, resolver,
        sourcemeta::blaze::default_schema_compiler, mode, default_dialect, "",
        fixture_entrypoint(data), fixture_tweaks(name, data));
  }

  const auto paths{fixture_paths(pointers)};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      resolver,
      default_dialect,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      paths,
      fixture_default_base(data)};
  return sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, resolver,
      sourcemeta::blaze::default_schema_compiler, frame,
      fixture_entrypoint(data), mode, fixture_tweaks(name, data));
}

auto matches_one_metaschema(const std::string &uri,
                            const sourcemeta::core::JSON &fixture,
                            const sourcemeta::core::JSON &schema) -> bool {
  sourcemeta::blaze::Evaluator evaluator;

  // A fixture that supplies the meta-schema itself stands outside the cache,
  // because another fixture may answer the same URI with another document.
  // Where it supplies nothing for this URI, the default resolver is what
  // answers, so the compiled template is the same for every fixture
  const auto *resolve{fixture.try_at("resolve")};
  if (resolve == nullptr || !resolve->defines(uri)) {
    return evaluator.validate(metaschema_template(uri), schema);
  }

  const FixtureResolver resolver{fixture};
  const auto metaschema{resolver(uri)};
  assert(metaschema.has_value());
  return evaluator.validate(
      sourcemeta::blaze::compile(metaschema.value(),
                                 sourcemeta::core::schema_walker, resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation),
      schema);
}

// Where a wrapper holds the schemas, every one of them has to be a schema of
// the directory's dialect, which is what this says of the schema itself when
// the fixture names no locations inside one
auto matches_metaschema(const std::string &uri,
                        const sourcemeta::core::JSON &fixture,
                        const sourcemeta::core::JSON &schema) -> bool {
  const auto pointers{fixture_pointers(fixture)};
  if (pointers.empty()) {
    return matches_one_metaschema(uri, fixture, schema);
  }

  return std::ranges::all_of(pointers, [&](const auto &pointer) {
    const auto *embedded{sourcemeta::core::try_get(schema, pointer)};
    return embedded != nullptr &&
           matches_one_metaschema(uri, fixture, *embedded);
  });
}

auto run_trace_test(const std::string &name, const sourcemeta::core::JSON &data,
                    const sourcemeta::blaze::Mode mode, const char *mode_key,
                    const std::string &metaschema,
                    const std::string &directory_dialect) -> void {
  const auto default_dialect{fixture_default_dialect(data, directory_dialect)};
  const FixtureResolver resolver{data};
  const auto schema{fixture_schema(data, resolver)};
  EXPECT_TRUE(matches_metaschema(metaschema, data, schema));

  const auto &instance{data.at("instance")};
  const bool expected_valid{data.at("valid").to_boolean()};

  const auto &mode_data{data.at(mode_key)};

  const auto pre{mode_data.defines("pre")
                     ? mode_data.at("pre")
                     : sourcemeta::core::JSON{sourcemeta::core::JSON::Array{}}};
  const auto post{
      mode_data.defines("post")
          ? mode_data.at("post")
          : sourcemeta::core::JSON{sourcemeta::core::JSON::Array{}}};
  const auto trace_descriptions{
      mode_data.defines("descriptions")
          ? mode_data.at("descriptions")
          : sourcemeta::core::JSON{sourcemeta::core::JSON::Array{}}};

  assert(pre.size() == post.size());
  assert(pre.size() == trace_descriptions.size());
  const auto count{pre.size()};

  const auto compiled_schema{
      compile_fixture(name, data, schema, default_dialect, mode, resolver)};
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, count);

  if (expected_valid) {
    EXPECT_TRUE(result);
  } else {
    EXPECT_FALSE(result);
  }

  // A callback turns off the shortcuts that the evaluator takes when nothing is
  // watching, such as deciding a property loop's children against the value the
  // loop already holds, so the verdict is asked for again without one
  const auto untraced_result{evaluator.validate(compiled_schema, instance)};
  EXPECT_EQ(untraced_result, expected_valid);

  for (std::size_t index = 0; index < pre.size(); index++) {
    const auto &expected{pre.at(index)};
    assert(expected.is_array());
    assert(expected.size() == 4);
    const auto &expected_type{expected.at(0).to_string()};
    if (expected_type == "Annotation") {
      EVALUATE_TRACE_PRE_ANNOTATION(index, expected.at(1).to_string(),
                                    expected.at(2).to_string(),
                                    expected.at(3).to_string());
    } else {
      __EVALUATE_TRACE_PRE(index, to_instruction_index(expected_type),
                           expected.at(1).to_string(),
                           expected.at(2).to_string(),
                           expected.at(3).to_string());
    }
  }

  for (std::size_t index = 0; index < post.size(); index++) {
    const auto &expected{post.at(index)};
    assert(expected.is_array());
    assert(expected.size() >= 5);
    const auto &expected_type{expected.at(1).to_string()};
    if (expected_type == "Annotation") {
      assert(expected.size() == 6);
      EVALUATE_TRACE_POST_ANNOTATION(
          index, expected.at(2).to_string(), expected.at(3).to_string(),
          expected.at(4).to_string(), expected.at(5));
    } else if (expected.at(0).to_boolean()) {
      __EVALUATE_TRACE_POST_SUCCESS(index, to_instruction_index(expected_type),
                                    expected.at(2).to_string(),
                                    expected.at(3).to_string(),
                                    expected.at(4).to_string());
    } else {
      __EVALUATE_TRACE_POST_FAILURE(index, to_instruction_index(expected_type),
                                    expected.at(2).to_string(),
                                    expected.at(3).to_string(),
                                    expected.at(4).to_string());
    }
  }

  for (std::size_t index = 0; index < trace_descriptions.size(); index++) {
    EVALUATE_TRACE_POST_DESCRIBE(instance, index,
                                 trace_descriptions.at(index).to_string());
  }
}
auto run_error_test(const std::string &name, const sourcemeta::core::JSON &data,
                    const std::string &metaschema,
                    const std::string &default_dialect,
                    const sourcemeta::blaze::Mode mode) -> void {
  const auto &expected{data.at("error")};
  const FixtureResolver resolver{data};
  EXPECT_FALSE(matches_metaschema(metaschema, data, data.at("schema")));

  try {
    sourcemeta::blaze::compile(data.at("schema"),
                               sourcemeta::core::schema_walker, resolver,
                               sourcemeta::blaze::default_schema_compiler, mode,
                               fixture_default_dialect(data, default_dialect),
                               "", "", fixture_tweaks(name, data));
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(std::string{error.what()}, expected.at("message").to_string());
    EXPECT_EQ(error.base().recompose(), expected.at("base").to_string());
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              expected.at("location").to_string());
  } catch (const std::exception &error) {
    // Any other failure is still a failure of this expectation, and reporting
    // it here beats letting it escape as an uncaught exception
    // NOLINTNEXTLINE(modernize-use-std-print)
    std::fprintf(stderr, "Unexpected exception: %s\n", error.what());
    FAIL();
  }
}
// Asking for the schema, which is either compiling it or compiling it and then
// evaluating the instance the fixture carries. A fixture that names an
// instance expects the throw to come from evaluation, and one that does not
// expects it from compilation
auto ask_for(const std::string &name, const sourcemeta::core::JSON &data,
             const std::string &default_dialect,
             const sourcemeta::blaze::Mode mode,
             const sourcemeta::core::SchemaResolver &resolver) -> void {
  const auto compiled_schema{compile_fixture(
      name, data, fixture_schema(data, resolver),
      fixture_default_dialect(data, default_dialect), mode, resolver)};

  const auto *instance{data.try_at("instance")};
  if (instance == nullptr) {
    return;
  }

  sourcemeta::blaze::Evaluator evaluator;
  [[maybe_unused]] const auto result{
      evaluator.validate(compiled_schema, *instance)};
}

auto run_thrown_test(const std::string &name,
                     const sourcemeta::core::JSON &data,
                     const std::string &default_dialect,
                     const sourcemeta::blaze::Mode mode) -> void {
  const auto &expected{data.at("error")};
  const auto &type{expected.at("type").to_string()};
  const FixtureResolver resolver{data};

#define EXPECT_THROWN_MESSAGE(error)                                           \
  EXPECT_EQ(std::string{(error).what()}, expected.at("message").to_string())
#define EXPECT_THROWN_BASE(error)                                              \
  EXPECT_EQ((error).base().recompose(), expected.at("base").to_string())
#define EXPECT_THROWN_LOCATION(error)                                          \
  EXPECT_EQ(sourcemeta::core::to_string((error).location()),                   \
            expected.at("location").to_string())
#define EXPECT_THROWN_IDENTIFIER(error)                                        \
  EXPECT_EQ(std::string{(error).identifier()},                                 \
            expected.at("identifier").to_string())

  try {
    ask_for(name, data, default_dialect, mode, resolver);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_EQ(type, "CompilerInvalidRegexError");
    EXPECT_THROWN_MESSAGE(error);
    EXPECT_THROWN_BASE(error);
    EXPECT_THROWN_LOCATION(error);
    EXPECT_EQ(error.regex(), expected.at("regex").to_string());
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(type, "CompilerInvalidEntryPoint");
    EXPECT_THROWN_MESSAGE(error);
    EXPECT_THROWN_IDENTIFIER(error);
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(type, "CompilerReferenceTargetNotSchemaError");
    EXPECT_THROWN_MESSAGE(error);
    EXPECT_THROWN_LOCATION(error);
    EXPECT_THROWN_IDENTIFIER(error);
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(type, "CompilerError");
    EXPECT_THROWN_MESSAGE(error);
    EXPECT_THROWN_BASE(error);
    EXPECT_THROWN_LOCATION(error);
  } catch (const sourcemeta::blaze::EvaluationError &error) {
    EXPECT_EQ(type, "EvaluationError");
    EXPECT_THROWN_MESSAGE(error);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(type, "SchemaReferenceError");
    EXPECT_THROWN_MESSAGE(error);
    EXPECT_THROWN_LOCATION(error);
    EXPECT_THROWN_IDENTIFIER(error);
  } catch (const sourcemeta::core::SchemaError &error) {
    EXPECT_EQ(type, "SchemaError");
    EXPECT_THROWN_MESSAGE(error);
  } catch (const std::exception &error) {
    // Reporting it here beats letting it escape as an uncaught exception, and
    // a fixture naming an exception this does not catch lands here too
    // NOLINTNEXTLINE(modernize-use-std-print)
    std::fprintf(stderr, "Unexpected exception: %s\n", error.what());
    FAIL();
  }

#undef EXPECT_THROWN_MESSAGE
#undef EXPECT_THROWN_BASE
#undef EXPECT_THROWN_LOCATION
#undef EXPECT_THROWN_IDENTIFIER
}
} // namespace

// Schemas whose keywords the official meta-schema rejects, which the compiler
// refuses rather than silently ignores
static auto register_error_tests(
    const std::filesystem::path &directory, const std::string &suite_name,
    const std::string &metaschema, const std::string &default_dialect,
    const sourcemeta::core::SchemaBaseDialect base_dialect) -> void {
  // NOLINTNEXTLINE(modernize-use-std-print)
  std::fprintf(stderr, "-- Parsing: %s\n", directory.string().c_str());

  for (const auto &[name, test_case] : read_fixtures(
           directory, FixtureKind::Invalid, base_dialect, default_dialect)) {

    // Whether a schema is well-formed is a property of its dialect rather than
    // of the mode it compiles in, so both modes have to refuse the same ones
    for (const auto &[mode_suffix, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "_fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "_exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {
      sourcemeta::core::test_register(
          suite_name, name + mode_suffix, __FILE__, __LINE__,
          [name, test_case, metaschema, default_dialect, mode]() -> void {
            run_error_test(name, test_case, metaschema, default_dialect, mode);
          });
    }
  }
}

// Schemas that are schemas of their dialect, but where asking for them raises
// something: the compiler turns one down for a reason the meta-schema has no
// say over, or evaluation runs into a wall
static auto register_thrown_tests(
    const std::filesystem::path &directory, const std::string &suite_name,
    const std::string &default_dialect,
    const sourcemeta::core::SchemaBaseDialect base_dialect) -> void {
  // NOLINTNEXTLINE(modernize-use-std-print)
  std::fprintf(stderr, "-- Parsing: %s\n", directory.string().c_str());

  for (const auto &[name, test_case] : read_fixtures(
           directory, FixtureKind::Error, base_dialect, default_dialect)) {
    for (const auto &[mode_suffix, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "_fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "_exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {
      sourcemeta::core::test_register(
          suite_name, name + mode_suffix, __FILE__, __LINE__,
          [name, test_case, default_dialect, mode]() -> void {
            run_thrown_test(name, test_case, default_dialect, mode);
          });
    }
  }
}

static auto
register_tests(const std::filesystem::path &directory,
               const std::string &suite_name, const std::string &metaschema,
               const std::string &default_dialect,
               const sourcemeta::core::SchemaBaseDialect base_dialect) -> void {
  // NOLINTNEXTLINE(modernize-use-std-print)
  std::fprintf(stderr, "-- Parsing: %s\n", directory.string().c_str());

  for (const auto &[name, test_case] : read_fixtures(
           directory, FixtureKind::Trace, base_dialect, default_dialect)) {

    for (const auto &[mode_key, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {

      const auto title{name + "_" + mode_key};

      sourcemeta::core::test_register(suite_name, title, __FILE__, __LINE__,
                                      [name, test_case, mode, mode_key,
                                       metaschema, default_dialect]() -> void {
                                        run_trace_test(name, test_case, mode,
                                                       mode_key, metaschema,
                                                       default_dialect);
                                      });
    }
  }
}

auto main(int argc, char **argv) -> int {
  try {
    const std::filesystem::path suite{TRACE_SUITE_PATH};

    // The two dated OpenAPI 3.0 dialects answer with the same Schema Object
    // definition, so one suite says what both of them mean. What differs
    // between the documents they come from describes the rest of an OpenAPI
    // document, which a schema of this dialect never reaches
    for (const auto &[label, dialect] :
         {std::pair<const char *, const char *>{
              "2024_10_18", "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"},
          std::pair<const char *, const char *>{
              "2021_09_28",
              "tag:spec.openapis.org,2021-09-28:oas/3.0/dialect"}}) {
      register_tests(suite / "openapi_3_0" / "valid",
                     std::string{"Evaluator_trace_OpenAPI_3_0_"} + label,
                     dialect, dialect,
                     sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
      register_error_tests(
          suite / "openapi_3_0" / "invalid",
          std::string{"Evaluator_error_OpenAPI_3_0_"} + label, dialect, dialect,
          sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
      register_thrown_tests(
          suite / "openapi_3_0" / "error",
          std::string{"Evaluator_thrown_OpenAPI_3_0_"} + label, dialect,
          sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
    }
    register_tests(suite / "openapi_3_1" / "valid",
                   "Evaluator_trace_OpenAPI_3_1",
                   "https://spec.openapis.org/oas/3.1/dialect/base", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_thrown_tests(
        suite / "openapi_3_1" / "error", "Evaluator_thrown_OpenAPI_3_1",
        "https://spec.openapis.org/oas/3.1/dialect/base",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "openapi_3_2" / "valid",
                   "Evaluator_trace_OpenAPI_3_2",
                   "https://spec.openapis.org/oas/3.2/dialect/2025-09-17", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "draft7" / "valid", "Evaluator_trace_draft7",
                   "http://json-schema.org/draft-07/schema#", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_7);
    register_error_tests(
        suite / "draft7" / "invalid", "Evaluator_error_draft7",
        "http://json-schema.org/draft-07/schema#", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_7);
    register_thrown_tests(
        suite / "draft7" / "error", "Evaluator_thrown_draft7", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_7);
    register_tests(suite / "2019_09" / "valid", "Evaluator_trace_2019_09",
                   "https://json-schema.org/draft/2019-09/schema", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09);

    // The Sourcemeta extension vocabulary has a meta-schema per draft it
    // builds on, and a fixture answers to the base dialect of the one it
    // declares, so each of them holds its fixtures in a directory of its own.
    // Every fixture here resolves that meta-schema itself, reduced to the
    // vocabulary declarations that make the extension keywords compile, so the
    // check against it says only that the schema is well-formed for the draft
    // underneath. The dialect these stand in for is in `schemas/`, and
    // reaching for it instead would mean carrying its vocabulary document
    // through every fixture
    register_tests(suite / "sourcemeta_v1_2019_09" / "valid",
                   "Evaluator_trace_sourcemeta_v1_2019_09",
                   "tag:sourcemeta.com,2026:extension/v1/2019-09", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09);
    register_tests(suite / "sourcemeta_v1_2020_12" / "valid",
                   "Evaluator_trace_sourcemeta_v1_2020_12",
                   "tag:sourcemeta.com,2026:extension/v1/2020-12", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_error_tests(
        suite / "2019_09" / "invalid", "Evaluator_error_2019_09",
        "https://json-schema.org/draft/2019-09/schema", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09);
    register_thrown_tests(
        suite / "2019_09" / "error", "Evaluator_thrown_2019_09", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09);
    register_tests(suite / "draft6" / "valid", "Evaluator_trace_draft6",
                   "http://json-schema.org/draft-06/schema#", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_6);
    register_error_tests(
        suite / "draft6" / "invalid", "Evaluator_error_draft6",
        "http://json-schema.org/draft-06/schema#", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_6);
    register_thrown_tests(
        suite / "draft6" / "error", "Evaluator_thrown_draft6", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_6);
    register_tests(suite / "2020_12" / "valid", "Evaluator_trace_2020_12",
                   "https://json-schema.org/draft/2020-12/schema", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_error_tests(
        suite / "2020_12" / "invalid", "Evaluator_error_2020_12",
        "https://json-schema.org/draft/2020-12/schema", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_thrown_tests(
        suite / "2020_12" / "error", "Evaluator_thrown_2020_12", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "draft4" / "valid", "Evaluator_trace_draft4",
                   "http://json-schema.org/draft-04/schema#", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
    register_error_tests(
        suite / "draft4" / "invalid", "Evaluator_error_draft4",
        "http://json-schema.org/draft-04/schema#", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
    register_thrown_tests(
        suite / "draft4" / "error", "Evaluator_thrown_draft4", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
    register_tests(suite / "draft3" / "valid", "Evaluator_trace_draft3",
                   "http://json-schema.org/draft-03/schema#", "",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_3);
    register_error_tests(
        suite / "draft3" / "invalid", "Evaluator_error_draft3",
        "http://json-schema.org/draft-03/schema#", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_3);
    register_thrown_tests(
        suite / "draft3" / "error", "Evaluator_thrown_draft3", "",
        sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_3);
  } catch (const std::exception &error) {
    // NOLINTNEXTLINE(modernize-use-std-print)
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
