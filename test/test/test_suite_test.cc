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
#include <tuple>      // std::get

TEST(TestSuite_parse, error_not_an_object) {
  const auto input{"[]"};
  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_neither_string_nor_array) {
  const auto input{R"JSON({
    "target": 123,
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  ASSERT_EQ(result.targets.size(), 1);
  EXPECT_EQ(result.targets.front(),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.schemas_fast.size(), 1);
  EXPECT_EQ(result.schemas_exhaustive.size(), 1);
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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  ASSERT_EQ(result.targets.size(), 1);
  EXPECT_EQ(result.targets.front(),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.schemas_fast.size(), 1);
  EXPECT_EQ(result.schemas_exhaustive.size(), 1);
  EXPECT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].description.empty());
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(std::get<0>(result.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(result.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(result.tests[0].position), 4);
  EXPECT_EQ(std::get<3>(result.tests[0].position), 35);
  EXPECT_EQ(result.tests[1].description, "Not an object");
  EXPECT_FALSE(result.tests[1].valid);
  EXPECT_EQ(std::get<0>(result.tests[1].position), 5);
  EXPECT_EQ(std::get<1>(result.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(result.tests[1].position), 5);
  EXPECT_EQ(std::get<3>(result.tests[1].position), 68);
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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
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

  ASSERT_EQ(result.targets.size(), 1);
  EXPECT_EQ(result.targets.front(), expected_target.recompose());
  EXPECT_EQ(result.schemas_fast.size(), 1);
  EXPECT_EQ(result.schemas_exhaustive.size(), 1);
  EXPECT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].description.empty());
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(std::get<0>(result.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(result.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(result.tests[0].position), 4);
  EXPECT_EQ(std::get<3>(result.tests[0].position), 49);
  EXPECT_EQ(result.tests[1].description, "missing foo");
  EXPECT_FALSE(result.tests[1].valid);
  EXPECT_EQ(std::get<0>(result.tests[1].position), 5);
  EXPECT_EQ(std::get<1>(result.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(result.tests[1].position), 5);
  EXPECT_EQ(std::get<3>(result.tests[1].position), 66);
}

TEST(TestSuite_parse, error_no_dialect_without_default) {
  const auto input{R"JSON({
    "target": "schema_no_dialect.json",
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
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
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
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

  ASSERT_EQ(result.targets.size(), 1);
  EXPECT_EQ(result.targets.front(), expected_target.recompose());
  EXPECT_EQ(result.schemas_fast.size(), 1);
  EXPECT_EQ(result.schemas_exhaustive.size(), 1);
  EXPECT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(std::get<0>(result.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(result.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(result.tests[0].position), 4);
  EXPECT_EQ(std::get<3>(result.tests[0].position), 51);
  EXPECT_EQ(result.tests[1].description, "missing name");
  EXPECT_FALSE(result.tests[1].valid);
  EXPECT_EQ(std::get<0>(result.tests[1].position), 5);
  EXPECT_EQ(std::get<1>(result.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(result.tests[1].position), 5);
  EXPECT_EQ(std::get<3>(result.tests[1].position), 67);
}

TEST(TestSuite_parse, error_target_object) {
  const auto input{R"JSON({
    "target": { "uri": "https://json-schema.org/draft/2020-12/schema" },
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_null) {
  const auto input{R"JSON({
    "target": null,
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_empty_array) {
  const auto input{R"JSON({
    "target": [],
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_array_first_element_not_string) {
  const auto input{R"JSON({
    "target": [
      123,
      "https://json-schema.org/draft/2020-12/schema"
    ],
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_array_trailing_element_not_string) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      true
    ],
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_array_element_null) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      null
    ],
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_array_element_array) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      [ "https://json-schema.org/draft/2019-09/schema" ]
    ],
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::TestParseError);
}

TEST(TestSuite_parse, error_target_array_unresolvable_entry) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      "https://example.com/non-existent-schema"
    ],
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  EXPECT_THROW(sourcemeta::blaze::TestSuite::parse(
                   document, tracker, std::filesystem::path{STUBS_PATH},
                   sourcemeta::core::schema_resolver,
                   sourcemeta::core::schema_walker,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaResolutionError);
}

TEST(TestSuite_parse, valid_target_array_single_element) {
  const auto input{R"JSON({
    "target": [ "https://json-schema.org/draft/2020-12/schema" ],
    "tests": [
      { "data": {}, "valid": true }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  ASSERT_EQ(result.targets.size(), 1);
  EXPECT_EQ(result.targets.front(),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.schemas_fast.size(), 1);
  EXPECT_EQ(result.schemas_exhaustive.size(), 1);
  EXPECT_EQ(result.tests.size(), 1);
}

TEST(TestSuite_parse, valid_target_array_multiple_uris) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2019-09/schema",
      "http://json-schema.org/draft-07/schema#"
    ],
    "tests": [
      { "data": {}, "valid": true },
      { "data": [], "valid": false, "description": "Not an object" }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  ASSERT_EQ(result.targets.size(), 3);
  EXPECT_EQ(result.targets[0], "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.targets[1], "https://json-schema.org/draft/2019-09/schema");
  EXPECT_EQ(result.targets[2], "http://json-schema.org/draft-07/schema");
  EXPECT_EQ(result.schemas_fast.size(), 3);
  EXPECT_EQ(result.schemas_exhaustive.size(), 3);
  EXPECT_EQ(result.tests.size(), 2);
}

TEST(TestSuite_parse, valid_target_array_with_file_paths) {
  const auto input{R"JSON({
    "target": [ "schema.json" ],
    "tests": [
      { "data": { "foo": "bar" }, "valid": true }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
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

  ASSERT_EQ(result.targets.size(), 1);
  EXPECT_EQ(result.targets.front(), expected_target.recompose());
  EXPECT_EQ(result.schemas_fast.size(), 1);
  EXPECT_EQ(result.schemas_exhaustive.size(), 1);
  EXPECT_EQ(result.tests.size(), 1);
}

TEST(TestSuite_parse, valid_target_array_mixed_uri_and_file_path) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      "schema.json"
    ],
    "tests": [
      { "data": { "foo": "bar" }, "valid": true }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
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
  const auto expected_file_target{sourcemeta::core::URI::from_path(
      std::filesystem::path{STUBS_PATH} / "schema.json")};

  ASSERT_EQ(result.targets.size(), 2);
  EXPECT_EQ(result.targets[0], "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.targets[1], expected_file_target.recompose());
  EXPECT_EQ(result.schemas_fast.size(), 2);
  EXPECT_EQ(result.schemas_exhaustive.size(), 2);
  EXPECT_EQ(result.tests.size(), 1);
}

TEST(TestSuite_parse, valid_target_array_with_default_dialect) {
  const auto input{R"JSON({
    "target": [
      "schema_no_dialect.json",
      "https://json-schema.org/draft/2020-12/schema"
    ],
    "tests": [
      { "data": { "name": "test" }, "valid": true }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
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
  const auto expected_file_target{sourcemeta::core::URI::from_path(
      std::filesystem::path{STUBS_PATH} / "schema_no_dialect.json")};

  ASSERT_EQ(result.targets.size(), 2);
  EXPECT_EQ(result.targets[0], expected_file_target.recompose());
  EXPECT_EQ(result.targets[1], "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(result.schemas_fast.size(), 2);
  EXPECT_EQ(result.schemas_exhaustive.size(), 2);
  EXPECT_EQ(result.tests.size(), 1);
}

TEST(TestSuite_parse, valid_target_array_preserves_test_case_positions) {
  const auto input{R"JSON({
    "target": [
      "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2019-09/schema"
    ],
    "tests": [
      { "data": {}, "valid": true },
      { "data": [], "valid": false, "description": "Not an object" }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  ASSERT_EQ(result.targets.size(), 2);
  ASSERT_EQ(result.tests.size(), 2);
  EXPECT_TRUE(result.tests[0].description.empty());
  EXPECT_TRUE(result.tests[0].valid);
  EXPECT_EQ(result.tests[1].description, "Not an object");
  EXPECT_FALSE(result.tests[1].valid);
  EXPECT_GT(std::get<0>(result.tests[0].position), 0);
  EXPECT_GT(std::get<0>(result.tests[1].position),
            std::get<0>(result.tests[0].position));
}
