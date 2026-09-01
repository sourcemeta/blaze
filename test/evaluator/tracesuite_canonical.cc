#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/canonicalizer.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "evaluator_utils.h"

#include <cassert>    // assert
#include <cstdio>     // std::fprintf
#include <filesystem> // std::filesystem::path
#include <string>     // std::string
#include <utility>    // std::move

namespace {
auto run_canonicalize_test(const sourcemeta::core::JSON &data,
                           const sourcemeta::blaze::Mode mode) -> void {
  auto schema{data.at("schema")};
  const auto &instance{data.at("instance")};
  const bool expected_valid{data.at("valid").to_boolean()};

  sourcemeta::blaze::canonicalize(schema, sourcemeta::blaze::schema_walker,
                                  sourcemeta::blaze::schema_resolver);

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, mode)};
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{evaluator.validate(compiled_schema, instance)};

  if (expected_valid) {
    EXPECT_TRUE(result);
  } else {
    EXPECT_FALSE(result);
  }
}
} // namespace

static auto register_tests(const std::filesystem::path &path,
                           const std::string &suite_name) -> void {
  std::fprintf(stderr, "-- Parsing: %s\n", path.string().c_str());
  auto suite{sourcemeta::core::read_json(path)};
  assert(suite.is_array());

  for (const auto &test_case : suite.as_array()) {
    assert(test_case.is_object());
    assert(test_case.defines("description"));
    const auto &description{test_case.at("description").to_string()};

    for (const auto &[mode_suffix, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "_fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "_exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {

      const auto title{description + mode_suffix};

      sourcemeta::core::test_register(suite_name, title, __FILE__, __LINE__,
                                      [test_case, mode]() -> void {
                                        run_canonicalize_test(test_case, mode);
                                      });
    }
  }
}

auto main(int argc, char **argv) -> int {
  try {
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_openapi_3_1.json",
                   "Canonicalize_OpenAPI_3_1");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_openapi_3_2.json",
                   "Canonicalize_OpenAPI_3_2");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_draft7.json",
                   "Canonicalize_draft7");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_2019_09.json",
                   "Canonicalize_2019_09");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_draft6.json",
                   "Canonicalize_draft6");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_2020_12.json",
                   "Canonicalize_2020_12");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_draft4.json",
                   "Canonicalize_draft4");
    register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                       "evaluator_draft3.json",
                   "Canonicalize_draft3");
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
