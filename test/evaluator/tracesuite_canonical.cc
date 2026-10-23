#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/canonicalizer.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

#include <cassert>    // assert
#include <cstdio>     // std::fprintf
#include <filesystem> // std::filesystem::path
#include <string>     // std::string
#include <utility>    // std::move

namespace {
auto declared_dialect(const sourcemeta::core::JSON &schema)
    -> sourcemeta::core::JSON::String {
  if (!schema.is_object()) {
    return {};
  }

  const auto *dialect{schema.try_at("$schema")};
  return (dialect != nullptr && dialect->is_string())
             ? dialect->to_string()
             : sourcemeta::core::JSON::String{};
}

auto run_canonicalize_test(const sourcemeta::core::JSON &data,
                           const sourcemeta::blaze::Mode mode,
                           const std::string &default_dialect) -> void {
  auto schema{data.at("schema")};
  const auto &instance{data.at("instance")};
  const bool expected_valid{data.at("valid").to_boolean()};

  // Canonicalisation can collapse an unsatisfiable schema into a boolean,
  // which has no room for the dialect the document declares, so hold on to
  // that dialect for the compilation that follows. A dialect that forbids
  // self-identification only arrives from the outside
  auto dialect{declared_dialect(schema)};
  if (dialect.empty()) {
    dialect = default_dialect;
  }

  sourcemeta::blaze::canonicalize(schema, sourcemeta::core::schema_walker,
                                  sourcemeta::core::schema_resolver, dialect);

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, mode, dialect)};
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
                           const std::string &suite_name,
                           const std::string &default_dialect = "") -> void {
  // NOLINTNEXTLINE(modernize-use-std-print)
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

      sourcemeta::core::test_register(
          suite_name, title, __FILE__, __LINE__,
          [test_case, mode, default_dialect]() -> void {
            run_canonicalize_test(test_case, mode, default_dialect);
          });
    }
  }
}

auto main(int argc, char **argv) -> int {
  try {
    // The two dated OpenAPI 3.0 dialects answer with the same Schema Object
    // definition, so one suite says what both of them mean
    for (const auto &[label, dialect] :
         {std::pair<const char *, const char *>{
              "2024_10_18", "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"},
          std::pair<const char *, const char *>{
              "2021_09_28",
              "tag:spec.openapis.org,2021-09-28:oas/3.0/dialect"}}) {
      register_tests(std::filesystem::path{TRACE_SUITE_CANONICAL_PATH} /
                         "evaluator_openapi_3_0.json",
                     std::string{"Canonicalize_OpenAPI_3_0_"} + label, dialect);
    }
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
    // NOLINTNEXTLINE(modernize-use-std-print)
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
