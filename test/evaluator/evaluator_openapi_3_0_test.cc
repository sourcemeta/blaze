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

TEST(format_byte_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zm9vYmFy")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zm9vYmFy\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zm9vYmF")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zm9vYmF\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_date_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("2026-10-08")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"2026-10-08\" was expected "
                               "to represent a valid RFC 3339 full-date");
}

TEST(format_date_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("not-a-date")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not-a-date\" was expected "
                               "to represent a valid RFC 3339 full-date");
}

TEST(format_date_time_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("2026-10-08T00:00:00Z")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-10-08T00:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(format_date_time_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("nope")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"nope\" was expected to "
                               "represent a valid RFC 3339 date-time");
}

TEST(format_email_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("a@b.com")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"a@b.com\" was expected to "
                               "represent a valid email address");
}

TEST(format_email_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("nope")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"nope\" was expected to "
                               "represent a valid email address");
}

TEST(format_hostname_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("example.com")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"example.com\" was expected "
                               "to represent a valid hostname");
}

TEST(format_ipv4_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("1.2.3.4")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"1.2.3.4\" was expected to "
                               "represent a valid IPv4 address");
}

TEST(format_ipv4_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("999.1.1.1")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"999.1.1.1\" was expected to "
                               "represent a valid IPv4 address");
}

TEST(format_ipv6_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("::1")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"::1\" was expected to "
                               "represent a valid IPv6 address");
}

TEST(format_uri_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("https://x.com")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"https://x.com\" was "
                               "expected to represent a valid URI");
}

TEST(format_uri_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("://bad")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_int32_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

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
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(2147483648)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2147483648 was expected to be an integer between "
      "-2147483648 and 2147483647");
}

TEST(format_int32_fractional_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(1.5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 1.5 was expected to be an "
                               "integer between -2147483648 and 2147483647");
}

TEST(format_int64_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int64"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(9223372036854775807)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 9223372036854775807 was expected to be an integer "
      "between -9223372036854775808 and 9223372036854775807");
}

TEST(format_int64_beyond_range_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int64"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(9223372036854775808)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

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
    "format": "float"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(0.5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be exactly representable as an "
      "IEEE 754 single precision floating point number");
}

TEST(format_float_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "float"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(3.14)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.14 was expected to be exactly representable as an "
      "IEEE 754 single precision floating point number");
}

TEST(format_double_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "double"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(0.5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be exactly representable as an "
      "IEEE 754 double precision floating point number");
}

TEST(format_double_not_representable_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "double"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(1e300)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 1e+300 was expected to be exactly representable as an "
      "IEEE 754 double precision floating point number");
}

TEST(format_binary_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "binary"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("any sequence of octets")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_password_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "password"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("hunter2")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_int32_ignores_non_numbers_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("5")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_uuid_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("not-a-uuid")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_time_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("00:00:00")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_int8_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int8"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_uri_is_ignored_without_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_WITH_DEFAULT_DIALECT(schema, instance, 0,
                                                        OPENAPI_3_0_DIALECT);
}

TEST(format_byte_with_x_format_assertion_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"Zm9vYmF"};

  EVALUATE_WITH_TRACE_FAST_FAILURE_WITH_DEFAULT_DIALECT(schema, instance, 1,
                                                        OPENAPI_3_0_DIALECT);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"Zm9vYmF\" was expected to represent a valid RFC "
      "4648 Base64 string");
}

// The OpenAPI 3.0 meta-schema inlines Draft 4's `schemaArray` without carrying
// over its `minItems` of one, so it accepts an empty array where the
// specification these keywords come from requires at least one element. The
// trace suites cross-check every case against the meta-schema, so the three
// that follow can only live here
TEST(all_of_empty_is_malformed) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "allOf": []
  })JSON")};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(std::string{error.what()},
              "This keyword was expected to be set to a non-empty array of "
              "valid schemas");
    EXPECT_EQ(error.base().recompose(), "");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/allOf");
  }
}

TEST(any_of_empty_is_malformed) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "anyOf": []
  })JSON")};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(std::string{error.what()},
              "This keyword was expected to be set to a non-empty array of "
              "valid schemas");
    EXPECT_EQ(error.base().recompose(), "");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/anyOf");
  }
}

TEST(one_of_empty_is_malformed) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "oneOf": []
  })JSON")};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(std::string{error.what()},
              "This keyword was expected to be set to a non-empty array of "
              "valid schemas");
    EXPECT_EQ(error.base().recompose(), "");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/oneOf");
  }
}

// A decimal literal is only a binary64 value when it lands on one exactly, so
// the ones an API typically carries do not satisfy this format
TEST(format_double_rejects_an_inexact_decimal_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "double"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(3.14)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNumberType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.14 was expected to be exactly representable as an "
      "IEEE 754 double precision floating point number");
}
