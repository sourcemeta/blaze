#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

#include <cassert>     // assert
#include <cstdint>     // std::uint8_t
#include <cstdio>      // std::fprintf
#include <filesystem>  // std::filesystem::path
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move, std::unreachable

static auto to_instruction_index(const std::string_view name)
    -> sourcemeta::blaze::InstructionIndex {
  constexpr auto count{sizeof(sourcemeta::blaze::InstructionNames) /
                       sizeof(std::string_view)};
  for (std::uint8_t index = 0; index < count; index++) {
    if (sourcemeta::blaze::InstructionNames[index] == name) {
      return static_cast<sourcemeta::blaze::InstructionIndex>(index);
    }
  }

  std::fprintf(stderr, "Unknown instruction type: %.*s\n",
               static_cast<int>(name.size()), name.data());
  std::unreachable();
}

class TraceTest : public testing::Test {
public:
  explicit TraceTest(sourcemeta::core::JSON test_data,
                     const sourcemeta::blaze::Mode test_mode,
                     const char *test_mode_key)
      : data{std::move(test_data)}, mode{test_mode}, mode_key{test_mode_key} {}

  auto TestBody() -> void override {
    const auto &schema{this->data.at("schema")};
    const auto &instance{this->data.at("instance")};
    const bool expected_valid{this->data.at("valid").to_boolean()};

    const auto &mode_data{this->data.at(this->mode_key)};

    const auto pre{
        mode_data.defines("pre")
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

    const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, this->mode)};
    __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
    EVALUATE_WITH_TRACE(compiled_schema, instance, count);

    if (expected_valid) {
      EXPECT_TRUE(result);
    } else {
      EXPECT_FALSE(result);
    }

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
        __EVALUATE_TRACE_POST_SUCCESS(
            index, to_instruction_index(expected_type),
            expected.at(2).to_string(), expected.at(3).to_string(),
            expected.at(4).to_string());
      } else {
        __EVALUATE_TRACE_POST_FAILURE(
            index, to_instruction_index(expected_type),
            expected.at(2).to_string(), expected.at(3).to_string(),
            expected.at(4).to_string());
      }
    }

    for (std::size_t index = 0; index < trace_descriptions.size(); index++) {
      EVALUATE_TRACE_POST_DESCRIBE(instance, index,
                                   trace_descriptions.at(index).to_string());
    }
  }

private:
  const sourcemeta::core::JSON data;
  const sourcemeta::blaze::Mode mode;
  const char *mode_key;
};

class CanonicalizeTraceTest : public testing::Test {
public:
  explicit CanonicalizeTraceTest(sourcemeta::core::JSON test_data,
                                 const sourcemeta::blaze::Mode test_mode)
      : data{std::move(test_data)}, mode{test_mode} {}

  auto TestBody() -> void override {
    auto schema{this->data.at("schema")};
    const auto &instance{this->data.at("instance")};
    const bool expected_valid{this->data.at("valid").to_boolean()};

    sourcemeta::blaze::SchemaTransformer bundle;
    sourcemeta::blaze::add(bundle,
                           sourcemeta::blaze::AlterSchemaMode::Canonicalizer);
    const auto canonicalize_result{bundle.apply(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        [](const auto &pointer, const auto &name, const auto &message,
           const auto &, const auto &) {
          // TODO: Temporary for debugging purposes. Remove once everything
          // passes
          std::fprintf(stderr, "  canonicalize: %s: %s: %s\n",
                       sourcemeta::core::to_string(pointer).c_str(),
                       std::string{name}.c_str(), std::string{message}.c_str());
        })};
    EXPECT_TRUE(canonicalize_result.first);

    const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, this->mode)};
    __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);

    sourcemeta::blaze::Evaluator evaluator;
    const auto result{evaluator.validate(compiled_schema, instance)};

    if (expected_valid) {
      EXPECT_TRUE(result);
    } else {
      EXPECT_FALSE(result);
    }
  }

private:
  const sourcemeta::core::JSON data;
  const sourcemeta::blaze::Mode mode;
};

static auto register_tests(const std::filesystem::path &path,
                           const std::string &suite_name) -> void {
  std::fprintf(stderr, "-- Parsing: %s\n", path.string().c_str());
  auto suite{sourcemeta::core::read_json(path)};
  assert(suite.is_array());

  for (const auto &test_case : suite.as_array()) {
    assert(test_case.is_object());
    assert(test_case.defines("description"));
    const auto &description{test_case.at("description").to_string()};

    assert(test_case.defines("fast"));
    assert(test_case.defines("exhaustive"));

    for (const auto &[mode_key, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {

      const auto title{description +
                       (mode == sourcemeta::blaze::Mode::FastValidation
                            ? "_fast"
                            : "_exhaustive")};

      testing::RegisterTest(suite_name.c_str(), title.c_str(), nullptr, nullptr,
                            __FILE__, __LINE__, [=]() -> TraceTest * {
                              return new TraceTest(test_case, mode, mode_key);
                            });
    }

    for (const auto &[mode_suffix, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "_fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "_exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {

      const auto title{description + mode_suffix};

      const auto canonicalize_suite_name{suite_name + "_canonicalize"};
      testing::RegisterTest(canonicalize_suite_name.c_str(), title.c_str(),
                            nullptr, nullptr, __FILE__, __LINE__,
                            [=]() -> CanonicalizeTraceTest * {
                              return new CanonicalizeTraceTest(test_case, mode);
                            });
    }
  }
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);

  try {
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_openapi_3_1.json",
                   "Evaluator_trace_OpenAPI_3_1");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_openapi_3_2.json",
                   "Evaluator_trace_OpenAPI_3_2");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_draft7.json",
                   "Evaluator_trace_draft7");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_2019_09.json",
                   "Evaluator_trace_2019_09");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_draft6.json",
                   "Evaluator_trace_draft6");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_2020_12.json",
                   "Evaluator_trace_2020_12");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_draft4.json",
                   "Evaluator_trace_draft4");
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return RUN_ALL_TESTS();
}
