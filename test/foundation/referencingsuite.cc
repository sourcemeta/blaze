#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
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

class ReferencingTest : public testing::Test {
public:
  explicit ReferencingTest(sourcemeta::core::JSON test_suite,
                           sourcemeta::core::JSON test_document,
                           std::string default_dialect)
      // Ubuntu's ClangFormat gets a bit lost on this one
      // clang-format off
    : suite{std::move(test_suite)}, test{std::move(test_document)},
      dialect{std::move(default_dialect)} {}
  // clang-format on

  auto TestBody() -> void override {
    // (1) Pre-populate the registry
    EXPECT_TRUE(this->suite.defines("registry"));
    EXPECT_TRUE(this->suite.at("registry").is_object());
    for (const auto &entry : this->suite.at("registry").as_object()) {
      assert(sourcemeta::blaze::is_schema(entry.second));
      this->registry.insert({entry.first, {entry.second, entry.first}});
    }

    // (2) Frame every schema and re-populate registry
    std::map<std::string, std::pair<sourcemeta::core::JSON, std::string>>
        new_entries;
    for (const auto &[uri, schema] : this->registry) {
      sourcemeta::blaze::SchemaFrame frame{
          sourcemeta::blaze::SchemaFrame::Mode::References};
      frame.analyse(schema.first, sourcemeta::blaze::schema_walker,
                    sourcemeta::blaze::schema_resolver, this->dialect, uri);
      for (const auto &[key, entry] : frame.locations()) {
        new_entries.insert({key.second,
                            {sourcemeta::core::get(schema.first, entry.pointer),
                             std::string{entry.base}}});
      }
    }

    // We don't insert into the main registry on the above loop,
    // otherwise we would affect the loop itself.
    for (auto pair : new_entries) {
      this->registry.insert(std::move(pair));
    }

    // (3) Run test
    this->assert_case(this->test, "");
  }

  auto assert_case(const sourcemeta::core::JSON &current,
                   const std::string_view default_base_uri) -> void {
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
        ref_uri.resolve_from(base_uri);
      }

      ref_uri.canonicalize();
      const auto result{dereference(ref_uri.recompose(), this->registry)};

      if (is_error) {
        EXPECT_FALSE(result.has_value());
      } else {
        EXPECT_TRUE(current.defines("target"));
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value().first, current.at("target"));
        if (current.defines("then")) {
          assert_case(current.at("then"), result.value().second);
        }
      }
    } catch (const sourcemeta::core::URIParseError &) {
      EXPECT_TRUE(is_error);
    }
  }

private:
  const sourcemeta::core::JSON suite;
  const sourcemeta::core::JSON test;
  const std::string dialect;
  std::map<std::string, std::pair<sourcemeta::core::JSON, std::string>>
      registry;
};

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
        // Hyphens break `--gtest_filter`
        test_name << (character == '-' ? '_' : character);
      }

      test_name << '_' << index;
      testing::RegisterTest(
          suite_name.c_str(), test_name.str().c_str(), nullptr, nullptr,
          __FILE__, __LINE__, [=]() -> ReferencingTest * {
            return new ReferencingTest(test, test.at("tests").at(index),
                                       default_dialect);
          });
    }
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

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

  return RUN_ALL_TESTS();
}
