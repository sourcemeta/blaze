#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

// Only what the JSON trace suites cannot express belongs here. That suite reads
// every schema under one dialect and holds it to that dialect's meta-schema,
// which rules out a schema that declares a dialect of its own, and it has no
// way of asking for a compiler tweak
static constexpr auto OPENAPI_3_0_DIALECT{
    "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"};

TEST(explicit_schema_overrides_the_default_dialect_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "null" ]
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_WITH_DEFAULT_DIALECT(schema, instance, 1,
                                                        OPENAPI_3_0_DIALECT);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type null, or string and it was of "
      "type null");
}

TEST(format_assertion_tweak_is_unsupported_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uri"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    [[maybe_unused]] const auto compiled_schema{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler,
                                   sourcemeta::blaze::Mode::FastValidation,
                                   OPENAPI_3_0_DIALECT, "", "", tweaks)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(std::string{error.what()},
              "The format assertion tweak not supported in this dialect");
    EXPECT_EQ(error.base().recompose(), "");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/format");
  }
}
