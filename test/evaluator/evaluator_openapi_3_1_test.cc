#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

// NOLINTBEGIN(cert-err58-cpp,bugprone-throwing-static-initialization)
static const std::string FORMAT_ASSERTION_METASCHEMA_URI{
    "https://example.com/openapi-3-1-format-assertion-meta"};

static auto test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == FORMAT_ASSERTION_METASCHEMA_URI) {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/openapi-3-1-format-assertion-meta",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true,
        "https://json-schema.org/draft/2020-12/vocab/format-assertion": true,
        "https://spec.openapis.org/oas/3.1/vocab/base": true
      },
      "$dynamicAnchor": "meta",
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2020-12/meta/core" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/validation" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/format-assertion" },
        { "$ref": "https://spec.openapis.org/oas/3.1/meta/base" }
      ]
    })JSON");
  }

  return sourcemeta::core::schema_resolver(identifier);
}

// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

TEST(format_uri_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(format_uri_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "uri");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"uri\"");
}

TEST(format_int32_is_ignored_without_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("2147483648")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(format_int32_valid_with_assertion_vocabulary_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/openapi-3-1-format-assertion-meta",
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 5 was expected to be an "
                               "integer between -2147483648 and 2147483647");
}

TEST(format_int32_invalid_with_assertion_vocabulary_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/openapi-3-1-format-assertion-meta",
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("2147483648")};
  EVALUATE_WITH_TRACE_FAST_FAILURE_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2147483648 was expected to be an integer between "
      "-2147483648 and 2147483647");
}

TEST(format_float_invalid_with_assertion_vocabulary_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/openapi-3-1-format-assertion-meta",
    "format": "float"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(3.14)JSON")};
  EVALUATE_WITH_TRACE_FAST_FAILURE_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.14 was expected to be exactly representable as an "
      "IEEE 754 single precision floating point number");
}

TEST(format_uri_invalid_with_assertion_vocabulary_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/openapi-3-1-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};
  EVALUATE_WITH_TRACE_FAST_FAILURE_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_uint32_is_not_asserted_with_assertion_vocabulary_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/openapi-3-1-format-assertion-meta",
    "format": "uint32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("4294967296")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 0, "",
                                            test_resolver);
}
