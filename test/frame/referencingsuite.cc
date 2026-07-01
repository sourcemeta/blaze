#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/uri.h>

#include <cassert>
#include <filesystem>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

static auto dereference(
    const std::string_view uri,
    const std::map<std::string, std::pair<sourcemeta::core::JSON, std::string>>
        &registry)
    -> std::optional<std::pair<sourcemeta::core::JSON, std::string>> {
  const std::string key{uri};
  if (!registry.contains(key)) {
    return std::nullopt;
  }

  return registry.at(key);
}

namespace {
auto assert_case(
    const sourcemeta::core::JSON &current,
    const std::string_view default_base_uri,
    const std::map<std::string, std::pair<sourcemeta::core::JSON, std::string>>
        &registry) -> void {
  const bool is_error{current.defines("error") &&
                      current.at("error").is_boolean() &&
                      current.at("error").to_boolean()};

  // These need to be std::string because URI constructor requires it
  const std::string base_uri{current.defines("base_uri")
                                 ? current.at("base_uri").to_string()
                                 : std::string{default_base_uri}};

  assert(current.defines("ref"));
  assert(current.at("ref").is_string());
  const std::string ref_string{current.at("ref").to_string()};

  try {
    sourcemeta::core::URI ref_uri{ref_string};
    if (!base_uri.empty()) {
      ref_uri.resolve_from(sourcemeta::core::URI{base_uri});
    }

    ref_uri.canonicalize();
    const auto result{dereference(ref_uri.recompose(), registry)};

    if (is_error) {
      EXPECT_FALSE(result.has_value());
    } else {
      EXPECT_TRUE(current.defines("target"));
      EXPECT_TRUE(result.has_value());
      EXPECT_EQ(result.value().first, current.at("target"));
      if (current.defines("then")) {
        assert_case(current.at("then"), result.value().second, registry);
      }
    }
  } catch (const sourcemeta::core::URIParseError &) {
    EXPECT_TRUE(is_error);
  }
}

auto run_referencing_test(const sourcemeta::core::JSON &suite,
                          const sourcemeta::core::JSON &test,
                          const std::string &dialect) -> void {
  std::map<std::string, std::pair<sourcemeta::core::JSON, std::string>>
      registry;

  // (1) Pre-populate the registry
  EXPECT_TRUE(suite.defines("registry"));
  EXPECT_TRUE(suite.at("registry").is_object());
  for (const auto &entry : suite.at("registry").as_object()) {
    assert(sourcemeta::blaze::is_schema(entry.second));
    registry.insert({entry.first, {entry.second, entry.first}});
  }

  // (2) Frame every schema and re-populate registry
  std::map<std::string, std::pair<sourcemeta::core::JSON, std::string>>
      new_entries;
  for (const auto &[uri, schema] : registry) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References};
    frame.analyse(schema.first, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver, dialect, uri);
    for (const auto &[key, entry] : frame.locations()) {
      new_entries.insert({key.second,
                          {sourcemeta::core::get(schema.first, entry.pointer),
                           std::string{entry.base}}});
    }
  }

  // We don't insert into the main registry on the above loop,
  // otherwise we would affect the loop itself.
  for (auto pair : new_entries) {
    registry.insert(std::move(pair));
  }

  // (3) Run test
  assert_case(test, "", registry);
}
} // namespace

static auto register_tests(const std::filesystem::path &subdirectory,
                           const std::string &suite_name,
                           const std::string &default_dialect) -> void {
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator(
           std::filesystem::path{REFERENCING_SUITE_PATH} / subdirectory)) {
    const std::string name{entry.path().stem().string()};
    const sourcemeta::core::JSON test =
        sourcemeta::core::read_json(entry.path());
    assert(test.is_object());
    assert(test.defines("tests"));
    assert(test.at("tests").is_array());
    for (unsigned int index = 0; index < test.at("tests").size(); index++) {
      std::ostringstream test_name;
      for (const auto character : name) {
        // Keep test identifiers free of hyphens
        test_name << (character == '-' ? '_' : character);
      }

      test_name << '_' << index;
      sourcemeta::core::test_register(
          suite_name, test_name.str(), __FILE__, __LINE__,
          [test, index, default_dialect]() -> void {
            run_referencing_test(test, test.at("tests").at(index),
                                 default_dialect);
          });
    }
  }
}

auto main(int argc, char **argv) -> int {
  // 2020-12
  register_tests("json-schema-draft-2020-12",
                 "JSONSchemaReferencingSuite_2020_12",
                 "https://json-schema.org/draft/2020-12/schema");

  // 2019-09
  register_tests("json-schema-draft-2019-09",
                 "JSONSchemaReferencingSuite_2019_09",
                 "https://json-schema.org/draft/2019-09/schema");

  // Draft7
  register_tests("json-schema-draft-07", "JSONSchemaReferencingSuite_Draft7",
                 "http://json-schema.org/draft-07/schema#");

  // Draft6
  register_tests("json-schema-draft-06", "JSONSchemaReferencingSuite_Draft6",
                 "http://json-schema.org/draft-06/schema#");

  // Draft4
  register_tests("json-schema-draft-04", "JSONSchemaReferencingSuite_Draft4",
                 "http://json-schema.org/draft-04/schema#");

  // Draft3
  register_tests("json-schema-draft-03", "JSONSchemaReferencingSuite_Draft3",
                 "http://json-schema.org/draft-03/schema#");

  return sourcemeta::core::test_run(argc, argv);
}
