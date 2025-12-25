#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/uri.h>
#include <sourcemeta/core/yaml.h>

#include <filesystem> // std::filesystem::path
#include <optional>   // std::optional, std::nullopt
#include <string>     // std::string

TEST(TestSuite_parse, error_not_an_object) {
  const auto input{"[]"};
  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_no_target) {
  const auto input{R"JSON({
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_not_string) {
  const auto input{R"JSON({
    "target": 123,
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_no_tests) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema"
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_tests_not_array) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": {}
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_unresolvable_target) {
  const auto input{R"JSON({
    "target": "https://example.com/non-existent-schema",
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaResolutionError);
}

TEST(TestSuite_parse, valid_empty_tests) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  EXPECT_EQ(result.target, "https://json-schema.org/draft/2020-12/schema");
  EXPECT_TRUE(result.tests.empty());
}

TEST(TestSuite_parse, valid_with_test_cases) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": [
      { "data": {}, "valid": true },
      { "data": [], "valid": false, "description": "Not an object" }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  EXPECT_EQ(result.target, "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].description.empty());
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(result.tests[1].description, "Not an object");
  EXPECT_FALSE(result.tests[1].valid);
}

TEST(TestSuite_parse, error_invalid_test_case) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": [
      { "data": {}, "valid": true },
      { "valid": true }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, valid_with_file_path_target) {
  const auto input{R"JSON({
    "target": "schema.json",
    "tests": [
      { "data": { "foo": "bar" }, "valid": true },
      { "data": {}, "valid": false, "description": "missing foo" }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  const auto test_resolver{
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
        const sourcemeta::core::URI uri{std::string{identifier}};
        if (uri.is_file()) {
          return sourcemeta::core::read_yaml_or_json(uri.to_path());
        }

        return sourcemeta::core::schema_resolver(identifier);
      }};

  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH}, test_resolver,
      sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};
  const auto expected_target{sourcemeta::core::URI::from_path(
      std::filesystem::path{STUBS_PATH} / "schema.json")};

  EXPECT_EQ(result.target, expected_target.recompose());
  EXPECT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].description.empty());
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(result.tests[1].description, "missing foo");
  EXPECT_FALSE(result.tests[1].valid);
}

TEST(TestSuite_parse, error_no_dialect_without_default) {
  const auto input{R"JSON({
    "target": "schema_no_dialect.json",
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  const auto test_resolver{
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
        const sourcemeta::core::URI uri{std::string{identifier}};
        if (uri.is_file()) {
          return sourcemeta::core::read_yaml_or_json(uri.to_path());
        }

        return sourcemeta::core::schema_resolver(identifier);
      }};

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   test_resolver, sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaResolutionError);
}

TEST(TestSuite_parse, valid_with_default_dialect) {
  const auto input{R"JSON({
    "target": "schema_no_dialect.json",
    "tests": [
      { "data": { "name": "test" }, "valid": true },
      { "data": {}, "valid": false, "description": "missing name" }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  const auto test_resolver{
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
        const sourcemeta::core::URI uri{std::string{identifier}};
        if (uri.is_file()) {
          return sourcemeta::core::read_yaml_or_json(uri.to_path());
        }

        return sourcemeta::core::schema_resolver(identifier);
      }};

  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH}, test_resolver,
      sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler,
      "https://json-schema.org/draft/2020-12/schema")};
  const auto expected_target{sourcemeta::core::URI::from_path(
      std::filesystem::path{STUBS_PATH} / "schema_no_dialect.json")};

  EXPECT_EQ(result.target, expected_target.recompose());
  EXPECT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(result.tests[1].description, "missing name");
  EXPECT_FALSE(result.tests[1].valid);
}
