#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>
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

class CanonicalizeTest : public testing::Test {
public:
  explicit CanonicalizeTest(sourcemeta::core::JSON test_data,
                            const sourcemeta::blaze::Mode test_mode)
      : data{std::move(test_data)}, mode{test_mode} {}

  auto TestBody() -> void override {
    auto schema{this->data.at("schema")};
    const auto &instance{this->data.at("instance")};
    const bool expected_valid{this->data.at("valid").to_boolean()};

    sourcemeta::blaze::SchemaTransformer bundle;
    sourcemeta::blaze::add(bundle,
                           sourcemeta::blaze::AlterSchemaMode::Canonicalizer);
    const auto canonicalize_result{
        bundle.apply(schema, sourcemeta::core::schema_walker,
                     sourcemeta::core::schema_resolver,
                     [](const auto &, const auto &, const auto &, const auto &,
                        const auto &) {})};
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

    for (const auto &[mode_suffix, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "_fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "_exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {

      const auto title{description + mode_suffix};

      testing::RegisterTest(suite_name.c_str(), title.c_str(), nullptr, nullptr,
                            __FILE__, __LINE__, [=]() -> CanonicalizeTest * {
                              return new CanonicalizeTest(test_case, mode);
                            });
    }
  }
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);

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
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return RUN_ALL_TESTS();
}
