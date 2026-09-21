#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>   // std::ranges::find, std::ranges::any_of
#include <array>       // std::array
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint64_t
#include <filesystem>  // std::filesystem
#include <iostream>    // std::cerr
#include <limits>      // std::numeric_limits
#include <optional>    // std::optional, std::nullopt
#include <sstream>     // std::ostringstream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace {

// Every key a fixture may declare. Anything else is a mistake that would
// otherwise go unnoticed, as the runner would simply not read it
// NOLINTBEGIN(cert-err58-cpp,bugprone-throwing-static-initialization)
const std::vector<std::string> KNOWN_KEYS{
    "schema",      "resolver",  "defaultDialect", "defaultId",
    "defaultBase", "container", "paths",          "maxLocations",
    "result",      "errors",    "inserted"};

// Every exception that bundling throws, named after the class itself so that
// a fixture states which one it means rather than leaving the runner to guess
// from the fields that happen to be there
const std::vector<std::string> KNOWN_ERROR_TYPES{
    "SchemaError",
    "SchemaResolutionError",
    "SchemaReferenceError",
    "SchemaReferenceObjectResourceError",
    "SchemaUnknownBaseDialectError",
    "SchemaFrameLimitError"};

const std::vector<std::string> KNOWN_ERROR_KEYS{"type", "message", "identifier",
                                                "location", "limit"};
// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

struct Mode {
  std::string_view name;
  sourcemeta::blaze::BundleMode value;
};

// Every strategy that bundling takes, as a fixture has to account for both of
// them rather than for the one whoever wrote it happened to think of
constexpr std::array<Mode, 2> MODES{
    {{.name = "nonOfficialMetaschemas",
      .value = sourcemeta::blaze::BundleMode::NonOfficialMetaschemas},
     {.name = "references",
      .value = sourcemeta::blaze::BundleMode::References}}};

// Both sides carry the mode they came from, as a fixture accounts for two of
// them and a bare pair of schemas does not say which one went wrong
auto expect_equal(const std::string_view mode,
                  const sourcemeta::core::JSON &actual,
                  const sourcemeta::core::JSON &expected) -> void {
  auto actual_entry{sourcemeta::core::JSON::make_object()};
  actual_entry.assign("mode", sourcemeta::core::JSON{mode});
  actual_entry.assign("schema", actual);
  auto expected_entry{sourcemeta::core::JSON::make_object()};
  expected_entry.assign("mode", sourcemeta::core::JSON{mode});
  expected_entry.assign("schema", expected);

  EXPECT_EQ(actual_entry, expected_entry);
}

auto make_resolver(const sourcemeta::core::JSON &test)
    -> sourcemeta::core::SchemaResolver {
  if (!test.defines("resolver")) {
    return sourcemeta::core::schema_resolver;
  }

  const auto &registry{test.at("resolver")};
  return [registry](const std::string_view identifier)
             -> sourcemeta::core::SchemaResolverResult {
    const auto *match{
        registry.try_at(sourcemeta::core::JSON::String{identifier})};
    if (match != nullptr) {
      return *match;
    }

    return sourcemeta::core::schema_resolver(identifier);
  };
}

// Bundling keeps views into the default dialect, the default identifier and
// the default base for as long as it runs, and the paths it walks point into
// pointers that the caller owns, so the caller owns all of it
struct Inputs {
  sourcemeta::core::JSON::String default_dialect;
  sourcemeta::core::JSON::String default_id;
  sourcemeta::core::JSON::String default_base;
  std::optional<sourcemeta::core::Pointer> container;
  std::vector<sourcemeta::core::Pointer> path_storage;
  sourcemeta::core::SchemaFrame::Paths paths;
  std::uint64_t max_locations{std::numeric_limits<std::uint64_t>::max()};
};

auto make_inputs(const sourcemeta::core::JSON &test) -> Inputs {
  Inputs inputs;
  const auto *raw_dialect{test.try_at("defaultDialect")};
  if (raw_dialect != nullptr) {
    inputs.default_dialect = raw_dialect->to_string();
  }

  const auto *raw_id{test.try_at("defaultId")};
  if (raw_id != nullptr) {
    inputs.default_id = raw_id->to_string();
  }

  const auto *raw_base{test.try_at("defaultBase")};
  if (raw_base != nullptr) {
    inputs.default_base = raw_base->to_string();
  }

  const auto *raw_container{test.try_at("container")};
  if (raw_container != nullptr) {
    inputs.container = sourcemeta::core::to_pointer(raw_container->to_string());
  }

  const auto *raw_limit{test.try_at("maxLocations")};
  if (raw_limit != nullptr) {
    inputs.max_locations = static_cast<std::uint64_t>(raw_limit->to_integer());
  }

  const auto *raw_paths{test.try_at("paths")};
  if (raw_paths == nullptr) {
    inputs.paths.push_back(sourcemeta::core::EMPTY_WEAK_POINTER);
    return inputs;
  }

  // Every pointer has to be in its final place before anything points into it
  inputs.path_storage.reserve(raw_paths->size());
  for (const auto &path : raw_paths->as_array()) {
    inputs.path_storage.push_back(
        sourcemeta::core::to_pointer(path.to_string()));
  }

  inputs.paths.reserve(inputs.path_storage.size());
  for (const auto &path : inputs.path_storage) {
    inputs.paths.push_back(sourcemeta::core::to_weak_pointer(path));
  }

  return inputs;
}

auto bundle_schema(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::SchemaResolver &resolver,
                   const Inputs &inputs, const Mode &mode,
                   const std::uint64_t max_locations,
                   std::vector<sourcemeta::core::Pointer> &insertions)
    -> sourcemeta::core::JSON {
  auto document{schema};
  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, resolver, mode.value,
      inputs.default_dialect, inputs.default_id, inputs.container, inputs.paths,
      inputs.default_base, max_locations,
      [&insertions](const sourcemeta::core::WeakPointer &location) -> void {
        insertions.push_back(sourcemeta::core::to_pointer(location));
      });
  return document;
}

auto to_json(const std::vector<sourcemeta::core::Pointer> &insertions)
    -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_array()};
  for (const auto &location : insertions) {
    result.push_back(
        sourcemeta::core::JSON{sourcemeta::core::to_string(location)});
  }

  return result;
}

auto expect_insertions(const std::string_view mode,
                       const std::vector<sourcemeta::core::Pointer> &actual,
                       const sourcemeta::core::JSON &expected) -> void {
  auto actual_entry{sourcemeta::core::JSON::make_object()};
  actual_entry.assign("mode", sourcemeta::core::JSON{mode});
  actual_entry.assign("inserted", to_json(actual));
  auto expected_entry{sourcemeta::core::JSON::make_object()};
  expected_entry.assign("mode", sourcemeta::core::JSON{mode});
  expected_entry.assign("inserted", expected);

  EXPECT_EQ(actual_entry, expected_entry);
}

// Bundling into a container that the dialect does not otherwise traverse
// leaves its own output invisible to the next pass, so the idempotency pass
// frames where the first pass actually put things.
//
// Framing rejects a path that contains another, so a fixture that frames from
// the root cannot name those locations at all. Dropping them is safe rather
// than merely necessary: framing from the root already reaches every container
// the dialect traverses, and one it does not traverse never settles no matter
// what this returns. Handing back fewer paths can only make the next pass
// embed more and fail louder, never pass when it should not
auto with_insertions(const Inputs &inputs,
                     const std::vector<sourcemeta::core::Pointer> &insertions)
    -> Inputs {
  Inputs result;
  result.default_dialect = inputs.default_dialect;
  result.default_id = inputs.default_id;
  result.default_base = inputs.default_base;
  result.container = inputs.container;
  if (inputs.path_storage.empty()) {
    result.paths.push_back(sourcemeta::core::EMPTY_WEAK_POINTER);
    return result;
  }

  result.path_storage.reserve(inputs.path_storage.size() + insertions.size());
  result.path_storage.insert(result.path_storage.cend(),
                             inputs.path_storage.cbegin(),
                             inputs.path_storage.cend());
  result.path_storage.insert(result.path_storage.cend(), insertions.cbegin(),
                             insertions.cend());
  result.paths.reserve(result.path_storage.size());
  for (const auto &path : result.path_storage) {
    result.paths.push_back(sourcemeta::core::to_weak_pointer(path));
  }

  return result;
}

// Every key a fixture declares has to be one the runner reads, every mode has
// to be accounted for exactly once, either as a result or as an error, and an
// error has to carry the fields that the class it names actually has
auto check_shape(const sourcemeta::core::JSON &test) -> void {
  for (const auto &entry : test.as_object()) {
    EXPECT_TRUE(std::ranges::find(KNOWN_KEYS, entry.first) !=
                KNOWN_KEYS.cend());
  }

  EXPECT_TRUE(test.defines("schema"));
  EXPECT_TRUE(test.defines("result"));

  const auto &results{test.at("result")};
  EXPECT_TRUE(results.is_object());
  for (const auto &entry : results.as_object()) {
    EXPECT_TRUE(std::ranges::any_of(MODES, [&entry](const auto &mode) {
      return mode.name == entry.first;
    }));
  }

  if (test.defines("errors")) {
    for (const auto &entry : test.at("errors").as_object()) {
      EXPECT_TRUE(std::ranges::any_of(MODES, [&entry](const auto &mode) {
        return mode.name == entry.first;
      }));
      EXPECT_FALSE(results.defines(entry.first));
      for (const auto &detail : entry.second.as_object()) {
        EXPECT_TRUE(std::ranges::find(KNOWN_ERROR_KEYS, detail.first) !=
                    KNOWN_ERROR_KEYS.cend());
      }

      const auto &type{entry.second.at("type").to_string()};
      EXPECT_TRUE(std::ranges::find(KNOWN_ERROR_TYPES, type) !=
                  KNOWN_ERROR_TYPES.cend());
      EXPECT_TRUE(entry.second.defines("message"));
      EXPECT_EQ(entry.second.defines("identifier"),
                type == "SchemaResolutionError" ||
                    type == "SchemaReferenceError" ||
                    type == "SchemaReferenceObjectResourceError");
      EXPECT_EQ(entry.second.defines("location"),
                type == "SchemaReferenceError");
      EXPECT_EQ(entry.second.defines("limit"), type == "SchemaFrameLimitError");
    }
  }

  EXPECT_TRUE(test.defines("inserted"));
  const auto &insertions{test.at("inserted")};
  EXPECT_TRUE(insertions.is_object());

  for (const auto &mode : MODES) {
    const sourcemeta::core::JSON::String name{mode.name};
    EXPECT_TRUE(results.defines(name) ||
                (test.defines("errors") && test.at("errors").defines(name)));
    EXPECT_EQ(insertions.defines(name), results.defines(name));
    if (insertions.defines(name)) {
      EXPECT_TRUE(insertions.at(name).is_array());
    }
  }
}

auto check_error(const sourcemeta::core::JSON &schema,
                 const sourcemeta::core::SchemaResolver &resolver,
                 const Inputs &inputs, const Mode &mode,
                 const sourcemeta::core::JSON &expected) -> void {
  const auto &type{expected.at("type").to_string()};
  const auto &message{expected.at("message").to_string()};

  if (type == "SchemaError") {
    try {
      std::vector<sourcemeta::core::Pointer> insertions;
      [[maybe_unused]] const auto document{bundle_schema(
          schema, resolver, inputs, mode, inputs.max_locations, insertions)};
      FAIL();
    } catch (const sourcemeta::core::SchemaError &error) {
      EXPECT_STREQ(error.what(), message.c_str());
    }
  } else if (type == "SchemaResolutionError") {
    try {
      std::vector<sourcemeta::core::Pointer> insertions;
      [[maybe_unused]] const auto document{bundle_schema(
          schema, resolver, inputs, mode, inputs.max_locations, insertions)};
      FAIL();
    } catch (const sourcemeta::core::SchemaResolutionError &error) {
      EXPECT_STREQ(error.what(), message.c_str());
      EXPECT_EQ(error.identifier(), expected.at("identifier").to_string());
    }
  } else if (type == "SchemaReferenceError") {
    try {
      std::vector<sourcemeta::core::Pointer> insertions;
      [[maybe_unused]] const auto document{bundle_schema(
          schema, resolver, inputs, mode, inputs.max_locations, insertions)};
      FAIL();
    } catch (const sourcemeta::core::SchemaReferenceError &error) {
      EXPECT_STREQ(error.what(), message.c_str());
      EXPECT_EQ(error.identifier(), expected.at("identifier").to_string());
      EXPECT_EQ(sourcemeta::core::to_string(error.location()),
                expected.at("location").to_string());
    }
  } else if (type == "SchemaReferenceObjectResourceError") {
    try {
      std::vector<sourcemeta::core::Pointer> insertions;
      [[maybe_unused]] const auto document{bundle_schema(
          schema, resolver, inputs, mode, inputs.max_locations, insertions)};
      FAIL();
    } catch (
        const sourcemeta::core::SchemaReferenceObjectResourceError &error) {
      EXPECT_STREQ(error.what(), message.c_str());
      EXPECT_EQ(error.identifier(), expected.at("identifier").to_string());
    }
  } else if (type == "SchemaUnknownBaseDialectError") {
    try {
      std::vector<sourcemeta::core::Pointer> insertions;
      [[maybe_unused]] const auto document{bundle_schema(
          schema, resolver, inputs, mode, inputs.max_locations, insertions)};
      FAIL();
    } catch (const sourcemeta::core::SchemaUnknownBaseDialectError &error) {
      EXPECT_STREQ(error.what(), message.c_str());
    }
  } else {
    try {
      std::vector<sourcemeta::core::Pointer> insertions;
      [[maybe_unused]] const auto document{bundle_schema(
          schema, resolver, inputs, mode, inputs.max_locations, insertions)};
      FAIL();
    } catch (const sourcemeta::core::SchemaFrameLimitError &error) {
      EXPECT_STREQ(error.what(), message.c_str());
      EXPECT_EQ(error.limit(),
                static_cast<std::uint64_t>(expected.at("limit").to_integer()));
    }
  }
}

auto run_bundle_test(const sourcemeta::core::JSON &test) -> void {
  check_shape(test);

  const auto resolver{make_resolver(test)};
  const auto inputs{make_inputs(test)};
  const auto &results{test.at("result")};

  for (const auto &mode : MODES) {
    const sourcemeta::core::JSON::String name{mode.name};
    if (test.defines("errors") && test.at("errors").defines(name)) {
      check_error(test.at("schema"), resolver, inputs, mode,
                  test.at("errors").at(name));
      continue;
    }

    const auto &expected{results.at(name)};
    std::vector<sourcemeta::core::Pointer> insertions;
    const auto document{bundle_schema(test.at("schema"), resolver, inputs, mode,
                                      inputs.max_locations, insertions)};
    expect_equal(mode.name, document, expected);
    expect_insertions(mode.name, insertions, test.at("inserted").at(name));

    // A caller picks between the overload that mutates and the one that
    // returns for reasons that have nothing to do with what bundling produces
    expect_equal(mode.name,
                 sourcemeta::blaze::bundle(
                     test.at("schema"), sourcemeta::core::schema_walker,
                     resolver, mode.value, inputs.default_dialect,
                     inputs.default_id, inputs.container, inputs.paths,
                     inputs.default_base, inputs.max_locations),
                 expected);

    // Bundling that keeps finding work to do on its own output never settles.
    // The limit is a budget rather than semantics, and the output is larger
    // than the input it came from, so this pass spends whatever it needs
    const auto settled{with_insertions(inputs, insertions)};
    std::vector<sourcemeta::core::Pointer> repeated;
    expect_equal(mode.name,
                 bundle_schema(document, resolver, settled, mode,
                               std::numeric_limits<std::uint64_t>::max(),
                               repeated),
                 document);
  }
}

auto register_tests(const std::filesystem::path &directory) -> std::size_t {
  std::size_t count{0};
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::recursive_directory_iterator{directory}) {
    if (!entry.is_regular_file() || entry.path().extension() != ".json") {
      continue;
    }

    const auto suite{entry.path().parent_path().filename().string()};
    std::ostringstream name;
    for (const auto character : entry.path().stem().string()) {
      name << (character == '-' ? '_' : character);
    }

    const auto test{sourcemeta::core::read_json(entry.path())};
    sourcemeta::core::test_register(
        "BundleSuite_" + suite, name.str(), __FILE__, __LINE__,
        [test]() -> void { run_bundle_test(test); });
    count += 1;
  }

  return count;
}

} // namespace

auto main(int argc, char **argv) -> int {
  const auto count{register_tests(std::filesystem::path{BUNDLE_SUITE_PATH})};
  // A fixture in the wrong place, or with the wrong extension, would otherwise
  // never run and nobody would notice
  if (count == 0) {
    std::cerr << "No bundle fixtures found at " << BUNDLE_SUITE_PATH << "\n";
    return 1;
  }

  return sourcemeta::core::test_run(argc, argv);
}
