#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(format_uri_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(format_uri_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_uri_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri\"");
}

TEST(format_uri_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

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

TEST(format_uri_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(format_uri_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(format_int32_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 5 was expected to be an "
                               "integer between -2147483648 and 2147483647");
}

TEST(format_int32_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("2147483648")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2147483648 was expected to be an integer between "
      "-2147483648 and 2147483647");
}

TEST(format_int32_ignores_non_numbers_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{"5"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(format_int64_beyond_range_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "int64"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("9223372036854775808")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 9223372036854775808 was expected to be an integer "
      "between -9223372036854775808 and 9223372036854775807");
}

TEST(format_float_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "float"
  })JSON")};

  const sourcemeta::core::JSON instance{0.5};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 0.5 was expected to be "
                               "exactly representable as an IEEE "
                               "754 single precision floating point number");
}

TEST(format_float_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "float"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.14 was expected to be "
                               "exactly representable as an IEEE "
                               "754 single precision floating point number");
}

TEST(format_double_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "double"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.14 was expected to be "
                               "exactly representable as an IEEE "
                               "754 double precision floating point number");
}

TEST(format_password_emits_nothing_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "password"
  })JSON")};

  const sourcemeta::core::JSON instance{"hunter2"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
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

TEST(format_byte_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{"not base64 at all!"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(format_binary_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "binary"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(format_uint32_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "uint32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("4294967296")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(format_decimal_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "format": "decimal"
  })JSON")};

  const sourcemeta::core::JSON instance{"not a decimal"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}
