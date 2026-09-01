#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

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

namespace {
auto run_trace_test(const sourcemeta::core::JSON &data,
                    const sourcemeta::blaze::Mode mode, const char *mode_key)
    -> void {
  const auto &schema{data.at("schema")};
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

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, mode)};
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
auto run_error_test(const sourcemeta::core::JSON &data) -> void {
  const auto &expected{data.at("error")};
  try {
    sourcemeta::blaze::compile(data.at("schema"),
                               sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(std::string{error.what()}, expected.at("message").to_string());
    EXPECT_EQ(error.base().recompose(), expected.at("base").to_string());
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              expected.at("location").to_string());
  } catch (const std::exception &error) {
    // Any other failure is still a failure of this expectation, and reporting
    // it here beats letting it escape as an uncaught exception
    std::fprintf(stderr, "Unexpected exception: %s\n", error.what());
    FAIL();
  }
}
} // namespace

// Schemas whose keywords the official meta-schema rejects, which the compiler
// refuses rather than silently ignores
static auto register_error_tests(const std::filesystem::path &path,
                                 const std::string &suite_name) -> void {
  std::fprintf(stderr, "-- Parsing: %s\n", path.string().c_str());
  auto suite{sourcemeta::core::read_json(path)};
  assert(suite.is_array());

  for (const auto &test_case : suite.as_array()) {
    assert(test_case.is_object());
    assert(test_case.defines("description"));
    assert(test_case.defines("error"));
    sourcemeta::core::test_register(
        suite_name, test_case.at("description").to_string(), __FILE__, __LINE__,
        [test_case]() -> void { run_error_test(test_case); });
  }
}

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

      sourcemeta::core::test_register(suite_name, title, __FILE__, __LINE__,
                                      [test_case, mode, mode_key]() -> void {
                                        run_trace_test(test_case, mode,
                                                       mode_key);
                                      });
    }
  }
}

auto main(int argc, char **argv) -> int {
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
    register_error_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                             "evaluator_draft7_invalid.json",
                         "Evaluator_error_draft7");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_2019_09.json",
                   "Evaluator_trace_2019_09");
    register_error_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                             "evaluator_2019_09_invalid.json",
                         "Evaluator_error_2019_09");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_draft6.json",
                   "Evaluator_trace_draft6");
    register_error_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                             "evaluator_draft6_invalid.json",
                         "Evaluator_error_draft6");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_2020_12.json",
                   "Evaluator_trace_2020_12");
    register_error_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                             "evaluator_2020_12_invalid.json",
                         "Evaluator_error_2020_12");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_draft4.json",
                   "Evaluator_trace_draft4");
    register_error_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                             "evaluator_draft4_invalid.json",
                         "Evaluator_error_draft4");
    register_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                       "evaluator_draft3.json",
                   "Evaluator_trace_draft3");
    register_error_tests(std::filesystem::path{TRACE_SUITE_PATH} /
                             "evaluator_draft3_invalid.json",
                         "Evaluator_error_draft3");
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
