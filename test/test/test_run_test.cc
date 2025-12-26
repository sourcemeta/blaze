#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/uri.h>
#include <sourcemeta/core/yaml.h>

#include <cstddef>    // std::size_t
#include <filesystem> // std::filesystem::path
#include <optional>   // std::optional, std::nullopt
#include <string>     // std::string
#include <tuple>      // std::tuple, std::get
#include <vector>     // std::vector

TEST(TestSuite_run, empty_tests) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": []
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  std::vector<std::tuple<std::string, std::size_t, std::size_t, std::string,
                         bool, bool>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t index,
                std::size_t total, const sourcemeta::blaze::TestCase &test_case,
                bool actual, sourcemeta::blaze::TestTimestamp,
                sourcemeta::blaze::TestTimestamp) {
        traces.emplace_back(target, index, total, test_case.description,
                            test_case.valid, actual);
      })};

  EXPECT_EQ(result.total, 0);
  EXPECT_EQ(result.passed, 0);
  EXPECT_TRUE(traces.empty());
}

TEST(TestSuite_run, all_passing) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": [
      {
        "data": { "$schema": "https://json-schema.org/draft/2020-12/schema" },
        "valid": true,
        "description": "valid schema 1"
      },
      {
        "data": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "type": "string"
        },
        "valid": true,
        "description": "valid schema 2"
      }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  std::vector<std::tuple<std::string, std::size_t, std::size_t, std::string,
                         bool, bool>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t index,
                std::size_t total, const sourcemeta::blaze::TestCase &test_case,
                bool actual, sourcemeta::blaze::TestTimestamp,
                sourcemeta::blaze::TestTimestamp) {
        traces.emplace_back(target, index, total, test_case.description,
                            test_case.valid, actual);
      })};

  EXPECT_EQ(result.total, 2);
  EXPECT_EQ(result.passed, 2);
  EXPECT_EQ(traces.size(), 2);

  EXPECT_EQ(std::get<0>(traces[0]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[0]), 1);
  EXPECT_EQ(std::get<2>(traces[0]), 2);
  EXPECT_EQ(std::get<3>(traces[0]), "valid schema 1");
  EXPECT_TRUE(std::get<4>(traces[0]));
  EXPECT_TRUE(std::get<5>(traces[0]));

  EXPECT_EQ(std::get<0>(traces[1]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[1]), 2);
  EXPECT_EQ(std::get<2>(traces[1]), 2);
  EXPECT_EQ(std::get<3>(traces[1]), "valid schema 2");
  EXPECT_TRUE(std::get<4>(traces[1]));
  EXPECT_TRUE(std::get<5>(traces[1]));

  EXPECT_EQ(std::get<0>(suite.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[0].position), 8);
  EXPECT_EQ(std::get<3>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[1].position), 9);
  EXPECT_EQ(std::get<1>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[1].position), 16);
  EXPECT_EQ(std::get<3>(suite.tests[1].position), 7);
}

TEST(TestSuite_run, all_failing) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": [
      {
        "data": { "$schema": "https://json-schema.org/draft/2020-12/schema" },
        "valid": false,
        "description": "expected invalid but valid"
      },
      {
        "data": "not a schema",
        "valid": true,
        "description": "expected valid but invalid"
      }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  std::vector<std::tuple<std::string, std::size_t, std::size_t, std::string,
                         bool, bool>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t index,
                std::size_t total, const sourcemeta::blaze::TestCase &test_case,
                bool actual, sourcemeta::blaze::TestTimestamp,
                sourcemeta::blaze::TestTimestamp) {
        traces.emplace_back(target, index, total, test_case.description,
                            test_case.valid, actual);
      })};

  EXPECT_EQ(result.total, 2);
  EXPECT_EQ(result.passed, 0);
  EXPECT_EQ(traces.size(), 2);

  EXPECT_EQ(std::get<0>(traces[0]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[0]), 1);
  EXPECT_EQ(std::get<2>(traces[0]), 2);
  EXPECT_EQ(std::get<3>(traces[0]), "expected invalid but valid");
  EXPECT_FALSE(std::get<4>(traces[0]));
  EXPECT_TRUE(std::get<5>(traces[0]));

  EXPECT_EQ(std::get<0>(traces[1]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[1]), 2);
  EXPECT_EQ(std::get<2>(traces[1]), 2);
  EXPECT_EQ(std::get<3>(traces[1]), "expected valid but invalid");
  EXPECT_TRUE(std::get<4>(traces[1]));
  EXPECT_FALSE(std::get<5>(traces[1]));

  EXPECT_EQ(std::get<0>(suite.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[0].position), 8);
  EXPECT_EQ(std::get<3>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[1].position), 9);
  EXPECT_EQ(std::get<1>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[1].position), 13);
  EXPECT_EQ(std::get<3>(suite.tests[1].position), 7);
}

TEST(TestSuite_run, mixed_results) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": [
      {
        "data": { "$schema": "https://json-schema.org/draft/2020-12/schema" },
        "valid": true,
        "description": "pass"
      },
      {
        "data": "not a schema",
        "valid": true,
        "description": "fail"
      },
      {
        "data": { "type": "number" },
        "valid": true,
        "description": "pass again"
      }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  std::vector<std::tuple<std::string, std::size_t, std::size_t, std::string,
                         bool, bool>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t index,
                std::size_t total, const sourcemeta::blaze::TestCase &test_case,
                bool actual, sourcemeta::blaze::TestTimestamp,
                sourcemeta::blaze::TestTimestamp) {
        traces.emplace_back(target, index, total, test_case.description,
                            test_case.valid, actual);
      })};

  EXPECT_EQ(result.total, 3);
  EXPECT_EQ(result.passed, 2);
  EXPECT_EQ(traces.size(), 3);

  EXPECT_EQ(std::get<0>(traces[0]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[0]), 1);
  EXPECT_EQ(std::get<2>(traces[0]), 3);
  EXPECT_EQ(std::get<3>(traces[0]), "pass");
  EXPECT_TRUE(std::get<4>(traces[0]));
  EXPECT_TRUE(std::get<5>(traces[0]));

  EXPECT_EQ(std::get<0>(traces[1]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[1]), 2);
  EXPECT_EQ(std::get<2>(traces[1]), 3);
  EXPECT_EQ(std::get<3>(traces[1]), "fail");
  EXPECT_TRUE(std::get<4>(traces[1]));
  EXPECT_FALSE(std::get<5>(traces[1]));

  EXPECT_EQ(std::get<0>(traces[2]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<1>(traces[2]), 3);
  EXPECT_EQ(std::get<2>(traces[2]), 3);
  EXPECT_EQ(std::get<3>(traces[2]), "pass again");
  EXPECT_TRUE(std::get<4>(traces[2]));
  EXPECT_TRUE(std::get<5>(traces[2]));

  EXPECT_EQ(std::get<0>(suite.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[0].position), 8);
  EXPECT_EQ(std::get<3>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[1].position), 9);
  EXPECT_EQ(std::get<1>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[1].position), 13);
  EXPECT_EQ(std::get<3>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[2].position), 14);
  EXPECT_EQ(std::get<1>(suite.tests[2].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[2].position), 18);
  EXPECT_EQ(std::get<3>(suite.tests[2].position), 7);
}

TEST(TestSuite_run, file_path_target) {
  const auto input{R"JSON({
    "target": "schema.json",
    "tests": [
      {
        "data": { "foo": "bar" },
        "valid": true,
        "description": "valid object"
      },
      {
        "data": {},
        "valid": false,
        "description": "missing required foo"
      },
      {
        "data": { "foo": 123 },
        "valid": false,
        "description": "foo is not a string"
      }
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

  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH}, test_resolver,
      sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  const auto expected_target{sourcemeta::core::URI::from_path(
      std::filesystem::path{STUBS_PATH} / "schema.json")};

  std::vector<std::tuple<std::string, std::size_t, std::size_t, std::string,
                         bool, bool>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t index,
                std::size_t total, const sourcemeta::blaze::TestCase &test_case,
                bool actual, sourcemeta::blaze::TestTimestamp,
                sourcemeta::blaze::TestTimestamp) {
        traces.emplace_back(target, index, total, test_case.description,
                            test_case.valid, actual);
      })};

  EXPECT_EQ(result.total, 3);
  EXPECT_EQ(result.passed, 3);
  EXPECT_EQ(traces.size(), 3);

  EXPECT_EQ(std::get<0>(traces[0]), expected_target.recompose());
  EXPECT_EQ(std::get<1>(traces[0]), 1);
  EXPECT_EQ(std::get<2>(traces[0]), 3);
  EXPECT_EQ(std::get<3>(traces[0]), "valid object");
  EXPECT_TRUE(std::get<4>(traces[0]));
  EXPECT_TRUE(std::get<5>(traces[0]));

  EXPECT_EQ(std::get<0>(traces[1]), expected_target.recompose());
  EXPECT_EQ(std::get<1>(traces[1]), 2);
  EXPECT_EQ(std::get<2>(traces[1]), 3);
  EXPECT_EQ(std::get<3>(traces[1]), "missing required foo");
  EXPECT_FALSE(std::get<4>(traces[1]));
  EXPECT_FALSE(std::get<5>(traces[1]));

  EXPECT_EQ(std::get<0>(traces[2]), expected_target.recompose());
  EXPECT_EQ(std::get<1>(traces[2]), 3);
  EXPECT_EQ(std::get<2>(traces[2]), 3);
  EXPECT_EQ(std::get<3>(traces[2]), "foo is not a string");
  EXPECT_FALSE(std::get<4>(traces[2]));
  EXPECT_FALSE(std::get<5>(traces[2]));

  EXPECT_EQ(std::get<0>(suite.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[0].position), 8);
  EXPECT_EQ(std::get<3>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[1].position), 9);
  EXPECT_EQ(std::get<1>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[1].position), 13);
  EXPECT_EQ(std::get<3>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[2].position), 14);
  EXPECT_EQ(std::get<1>(suite.tests[2].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[2].position), 18);
  EXPECT_EQ(std::get<3>(suite.tests[2].position), 7);
}

TEST(TestSuite_run, default_dialect) {
  const auto input{R"JSON({
    "target": "schema_no_dialect.json",
    "tests": [
      {
        "data": { "name": "Alice" },
        "valid": true,
        "description": "valid object"
      },
      {
        "data": {},
        "valid": false,
        "description": "missing required name"
      },
      {
        "data": { "name": 123 },
        "valid": false,
        "description": "name is not a string"
      }
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

  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH}, test_resolver,
      sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler,
      "https://json-schema.org/draft/2020-12/schema")};

  const auto expected_target{sourcemeta::core::URI::from_path(
      std::filesystem::path{STUBS_PATH} / "schema_no_dialect.json")};

  std::vector<std::tuple<std::string, std::size_t, std::size_t, std::string,
                         bool, bool>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t index,
                std::size_t total, const sourcemeta::blaze::TestCase &test_case,
                bool actual, sourcemeta::blaze::TestTimestamp,
                sourcemeta::blaze::TestTimestamp) {
        traces.emplace_back(target, index, total, test_case.description,
                            test_case.valid, actual);
      })};

  EXPECT_EQ(result.total, 3);
  EXPECT_EQ(result.passed, 3);
  EXPECT_EQ(traces.size(), 3);

  EXPECT_EQ(std::get<0>(traces[0]), expected_target.recompose());
  EXPECT_EQ(std::get<1>(traces[0]), 1);
  EXPECT_EQ(std::get<2>(traces[0]), 3);
  EXPECT_EQ(std::get<3>(traces[0]), "valid object");
  EXPECT_TRUE(std::get<4>(traces[0]));
  EXPECT_TRUE(std::get<5>(traces[0]));

  EXPECT_EQ(std::get<0>(traces[1]), expected_target.recompose());
  EXPECT_EQ(std::get<1>(traces[1]), 2);
  EXPECT_EQ(std::get<2>(traces[1]), 3);
  EXPECT_EQ(std::get<3>(traces[1]), "missing required name");
  EXPECT_FALSE(std::get<4>(traces[1]));
  EXPECT_FALSE(std::get<5>(traces[1]));

  EXPECT_EQ(std::get<0>(traces[2]), expected_target.recompose());
  EXPECT_EQ(std::get<1>(traces[2]), 3);
  EXPECT_EQ(std::get<2>(traces[2]), 3);
  EXPECT_EQ(std::get<3>(traces[2]), "name is not a string");
  EXPECT_FALSE(std::get<4>(traces[2]));
  EXPECT_FALSE(std::get<5>(traces[2]));

  EXPECT_EQ(std::get<0>(suite.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[0].position), 8);
  EXPECT_EQ(std::get<3>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[1].position), 9);
  EXPECT_EQ(std::get<1>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[1].position), 13);
  EXPECT_EQ(std::get<3>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[2].position), 14);
  EXPECT_EQ(std::get<1>(suite.tests[2].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[2].position), 18);
  EXPECT_EQ(std::get<3>(suite.tests[2].position), 7);
}

TEST(TestSuite_run, timestamps_ordering) {
  const auto input{R"JSON({
    "target": "https://json-schema.org/draft/2020-12/schema",
    "tests": [
      {
        "data": { "$schema": "https://json-schema.org/draft/2020-12/schema" },
        "valid": true,
        "description": "test 1"
      },
      {
        "data": { "type": "string" },
        "valid": true,
        "description": "test 2"
      },
      {
        "data": { "type": "number" },
        "valid": true,
        "description": "test 3"
      }
    ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  const auto document{sourcemeta::core::parse_json(input, std::ref(tracker))};
  auto suite{sourcemeta::blaze::TestSuite::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::schema_resolver, sourcemeta::core::schema_walker,
      sourcemeta::blaze::default_schema_compiler)};

  std::vector<std::tuple<std::string, sourcemeta::blaze::TestTimestamp,
                         sourcemeta::blaze::TestTimestamp>>
      traces;
  const auto result{suite.run(
      [&traces](const sourcemeta::core::JSON::String &target, std::size_t,
                std::size_t, const sourcemeta::blaze::TestCase &, bool,
                sourcemeta::blaze::TestTimestamp start,
                sourcemeta::blaze::TestTimestamp end) {
        traces.emplace_back(target, start, end);
      })};

  EXPECT_EQ(suite.tests.size(), 3);
  EXPECT_EQ(traces.size(), 3);
  EXPECT_GE(result.end, result.start);

  EXPECT_EQ(std::get<0>(traces[0]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<0>(traces[1]),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(std::get<0>(traces[2]),
            "https://json-schema.org/draft/2020-12/schema");

  EXPECT_GE(std::get<2>(traces[0]), std::get<1>(traces[0]));
  EXPECT_GE(std::get<1>(traces[0]), result.start);
  EXPECT_LE(std::get<2>(traces[0]), result.end);

  EXPECT_GE(std::get<2>(traces[1]), std::get<1>(traces[1]));
  EXPECT_GE(std::get<1>(traces[1]), result.start);
  EXPECT_LE(std::get<2>(traces[1]), result.end);

  EXPECT_GE(std::get<2>(traces[2]), std::get<1>(traces[2]));
  EXPECT_GE(std::get<1>(traces[2]), result.start);
  EXPECT_LE(std::get<2>(traces[2]), result.end);

  EXPECT_EQ(std::get<0>(suite.tests[0].position), 4);
  EXPECT_EQ(std::get<1>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[0].position), 8);
  EXPECT_EQ(std::get<3>(suite.tests[0].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[1].position), 9);
  EXPECT_EQ(std::get<1>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[1].position), 13);
  EXPECT_EQ(std::get<3>(suite.tests[1].position), 7);
  EXPECT_EQ(std::get<0>(suite.tests[2].position), 14);
  EXPECT_EQ(std::get<1>(suite.tests[2].position), 7);
  EXPECT_EQ(std::get<2>(suite.tests[2].position), 18);
  EXPECT_EQ(std::get<3>(suite.tests[2].position), 7);
}
