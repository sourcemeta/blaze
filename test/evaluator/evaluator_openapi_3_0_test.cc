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

TEST(explicit_schema_with_root_ref_keeps_the_sibling_type_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": { "string": { "type": "string" } },
    "$ref": "#/$defs/string",
    "type": "integer"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  // The declared dialect keeps the assertion beside `$ref` alive, so a string
  // that satisfies the reference still fails the sibling type
  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("foo")JSON")};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(explicit_schema_with_root_ref_keeps_the_reference_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": { "string": { "type": "string" } },
    "$ref": "#/$defs/string",
    "type": "integer"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  // The declared dialect keeps the reference alive, so an integer that
  // satisfies the sibling type still fails the referenced string schema
  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(1)JSON")};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(external_reference_inherits_the_default_dialect_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "$ref": "https://example.com/name" }
    }
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/name") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "string",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  // Only this dialect gives `nullable` a meaning, so a null passing is what
  // shows the default dialect reached the externally resolved document
  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "name": null })JSON")};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(external_reference_enforces_the_target_constraints_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "$ref": "https://example.com/name" }
    }
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/name") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "string",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "name": 1 })JSON")};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(external_reference_answers_to_the_closed_dialect_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "$ref": "https://example.com/name" }
    }
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/name") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "object",
                "patternProperties": { "^x": { "type": "string" } }
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker, test_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    // Where the offending keyword sits after bundling embeds the external
    // document is a bundling detail, so only the refusal itself is pinned
    EXPECT_EQ(std::string{error.what()},
              "This keyword is prohibited by this dialect");
  }
}

// A root Reference Object is only rejected over the members beside `$ref`, so
// a root that is nothing but `$ref` must resolve like any other reference.
// Only this dialect gives `nullable` a meaning, so a null passing is what
// shows the default dialect reached the externally resolved document
TEST(root_reference_without_siblings_accepts_null_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com/target"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/target") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "integer",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("null")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
                     "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
      "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type null");
}

TEST(root_reference_without_siblings_accepts_an_integer_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com/target"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/target") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "integer",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
                     "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
      "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type integer");
}

TEST(root_reference_without_siblings_rejects_a_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com/target"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/target") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "integer",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("\"1\"")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
                     "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
      "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer but it was of type string");
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

// RFC 4648 Section 3.5 lets an implementation reject an encoding whose pad
// bits are not zero, and the strict check does, so that every octet sequence
// has exactly one accepted encoding
TEST(format_byte_rejects_nonzero_pad_bits_after_one_octet_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zh==")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zh==\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_rejects_nonzero_pad_bits_after_two_octets_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zm9=")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zm9=\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

// Zero octets encode to the empty string, so the strict check accepts it
TEST(format_byte_accepts_the_empty_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

// Padding is part of the canonical form, so a strict check accepts it
TEST(format_byte_accepts_two_padding_characters_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zg==")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zg==\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_accepts_the_full_alphabet_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("+/8=")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"+/8=\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_rejects_interior_padding_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("AA==AAAA")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"AA==AAAA\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_rejects_whitespace_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zm9v YmFy")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zm9v YmFy\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_ignores_non_strings_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(1)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

// The check reads every byte of the string, so a NUL does not end it early
// and a byte outside ASCII is just another byte outside the alphabet
TEST(format_byte_rejects_an_embedded_nul_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zg==\u0000")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  // The description carries the raw NUL byte, so the expectation has to be
  // built with an explicit length rather than from a literal that would end
  // at that byte
  std::string expected_message{"The string value \"Zg=="};
  expected_message.push_back('\0');
  expected_message +=
      "\" was expected to represent a valid RFC 4648 Base64 string";
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0, expected_message);
}

TEST(format_byte_rejects_non_ascii_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("éAAA")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"\u00e9AAA\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
}

// `nullable` widens `type`, while the format assertion stays bound to
// strings: a null passes with no format callback at all, and a string keeps
// answering to the strict check
TEST(format_byte_accepts_null_when_nullable_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true,
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type null, or string and it was of "
      "type null");
}

TEST(format_byte_still_asserts_beside_nullable_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true,
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("notbase64!")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"notbase64!\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
}

// The root-level cases cannot tell a correctly placed assertion from one that
// only ever reports the schema and instance roots, so a property schema pins
// the nested keyword and instance locations
TEST(format_byte_within_properties_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "type": "string", "format": "byte" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "Zg==" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 3, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/data/format",
                     "#/properties/data/format", "/data");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/data/type",
                     "#/properties/data/type", "/data");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/properties/data/format",
                              "#/properties/data/format", "/data");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/data/type", "#/properties/data/type",
                              "/data");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zg==\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(format_byte_within_properties_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "type": "string", "format": "byte" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "not base64" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/data/format",
                     "#/properties/data/format", "/data");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/properties/data/format",
                              "#/properties/data/format", "/data");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not base64\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
}

// The root-level exhaustive case cannot show a nested failure propagating
// through the properties wrapper that fast mode never emits
TEST(format_byte_within_properties_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "type": "string", "format": "byte" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "not base64" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 2, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/properties/data/format",
                     "#/properties/data/format", "/data");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/properties/data/format",
                              "#/properties/data/format", "/data");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not base64\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the single defined property "
                               "subschema");
}

// Unlike the ignored sibling case, a `format` inside the referenced target
// is active, so the assertion must travel into the bundled target
TEST(format_byte_in_reference_target_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "$ref": "#/x-definitions/S" }
    },
    "x-definitions": {
      "S": { "type": "string", "format": "byte" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "Zg==" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 3, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/data/$ref/format",
                     "#/x-definitions/S/format", "/data");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict,
                     "/properties/data/$ref/type", "#/x-definitions/S/type",
                     "/data");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType,
                              "/properties/data/$ref/format",
                              "#/x-definitions/S/format", "/data");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/data/$ref/type",
                              "#/x-definitions/S/type", "/data");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zg==\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(format_byte_in_reference_target_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "$ref": "#/x-definitions/S" }
    },
    "x-definitions": {
      "S": { "type": "string", "format": "byte" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "not base64" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/data/$ref/format",
                     "#/x-definitions/S/format", "/data");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType,
                              "/properties/data/$ref/format",
                              "#/x-definitions/S/format", "/data");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not base64\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_in_reference_target_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "$ref": "#/x-definitions/S" }
    },
    "x-definitions": {
      "S": { "type": "string", "format": "byte" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "not base64" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 3, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, ControlJump, "/properties/data/$ref",
                     "#/properties/data/$ref", "/data");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/properties/data/$ref/format",
                     "#/x-definitions/S/format", "/data");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType,
                              "/properties/data/$ref/format",
                              "#/x-definitions/S/format", "/data");
  EVALUATE_TRACE_POST_FAILURE(1, ControlJump, "/properties/data/$ref",
                              "#/properties/data/$ref", "/data");
  EVALUATE_TRACE_POST_FAILURE(2, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not base64\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property "
                               "subschema");
}

// Serialized templates are a product surface, and textual round-trip equality
// alone cannot show the rebuilt instructions still evaluate, so these run the
// deserialized template
TEST(format_byte_accepts_through_a_deserialized_template_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation,
                                 OPENAPI_3_0_DIALECT, "", "", tweaks)};
  const auto restored{sourcemeta::blaze::from_json(
      sourcemeta::blaze::to_json(compiled_schema))};
  EXPECT_TRUE(restored.has_value());

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zg==")JSON")};
  EVALUATE_WITH_TRACE(restored.value(), instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zg==\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_rejects_through_a_deserialized_template_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation,
                                 OPENAPI_3_0_DIALECT, "", "", tweaks)};
  const auto restored{sourcemeta::blaze::from_json(
      sourcemeta::blaze::to_json(compiled_schema))};
  EXPECT_TRUE(restored.has_value());

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("not base64")JSON")};
  EVALUATE_WITH_TRACE(restored.value(), instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not base64\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
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

TEST(format_hostname_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("-foo")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"-foo\" was expected to "
                               "represent a valid hostname");
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

TEST(format_ipv6_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("::g")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"::g\" was expected to "
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

// Annotation extraction only exists from 2019-09 onwards, so even exhaustive
// mode compiles a format assertion to that one instruction and nothing else
TEST(format_byte_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zm9vYmFy")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zm9vYmFy\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_int32_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(7)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 7 was expected to be an "
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

// Two's complement makes each lower bound one further from zero than its
// upper bound, which is exactly where a hand-written range check slips
TEST(format_int32_accepts_the_lower_bound_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(-2147483648)JSON")};

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
      "The integer value -2147483648 was expected to be an integer between "
      "-2147483648 and 2147483647");
}

TEST(format_int32_below_range_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(-2147483649)JSON")};

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
      "The integer value -2147483649 was expected to be an integer between "
      "-2147483648 and 2147483647");
}

TEST(format_int64_accepts_the_lower_bound_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int64"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(-9223372036854775808)JSON")};

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
      "The integer value -9223372036854775808 was expected to be an integer "
      "between -9223372036854775808 and 9223372036854775807");
}

TEST(format_int64_below_range_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int64"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(-9223372036854775809)JSON")};

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
      "The integer value -9223372036854775809 was expected to be an integer "
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

// The string formats below belong to later drafts than the one the Schema
// Object builds on, so they stay unasserted no matter how assertions are
// enabled, the way the Draft 4 compiler already treats them
TEST(format_uri_reference_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("%zz")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_uri_template_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("{unclosed")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

TEST(format_json_pointer_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("not/a/pointer")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 0, OPENAPI_3_0_DIALECT, tweaks);
}

// Wright-00 spells this name without the dash, but the Draft 4 compiler
// never asserted it under either spelling, and neither does this dialect
TEST(format_uriref_is_not_asserted_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "uriref"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("%zz")JSON")};

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

// `$ref` overrides whatever sits beside it on this rung, so a sibling is not a
// keyword of the schema and its shape is never held against it
TEST(malformed_nullable_beside_ref_is_ignored_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "A": { "type": "integer" }
    },
    "allOf": [
      { "$ref": "#/x-definitions/A", "nullable": "not a boolean" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS_WITH_DEFAULT_DIALECT(schema, instance, 1,
                                                        OPENAPI_3_0_DIALECT);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/x-definitions/A/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/x-definitions/A/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

// A Reference Object ignores every sibling keyword, and that must hold for
// `format` even when format assertions are enabled: the instance violates the
// sibling `byte` yet satisfies the referenced target
TEST(format_beside_a_nested_reference_is_ignored_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "data": { "$ref": "#/x-definitions/S", "format": "byte" }
    },
    "x-definitions": {
      "S": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "data": "not base64" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 2, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict,
                     "/properties/data/$ref/type", "#/x-definitions/S/type",
                     "/data");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/data/$ref/type",
                              "#/x-definitions/S/type", "/data");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
}

TEST(malformed_nullable_without_ref_is_rejected_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "nullable": "not a boolean"
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
              "This keyword was expected to be set to a boolean");
    EXPECT_EQ(error.base().recompose(), "");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/nullable");
  }
}

TEST(boolean_reference_target_is_rejected_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "additionalProperties": false,
    "properties": {
      "a": { "$ref": "#/additionalProperties" }
    }
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
              "This dialect does not support boolean schemas");
    EXPECT_EQ(error.base().recompose(), "");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/additionalProperties");
  }
}

// The overload that takes a pre-built frame must speak the dialect the way
// the bundling overload does: `nullable` support that lives in a
// preprocessing step of the latter would vanish on this path
TEST(nullable_through_the_frame_overload_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{nullptr};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(nullable_array_type_is_refused_through_the_frame_overload_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": [ "string", "null" ],
    "nullable": true
  })JSON")};

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
        sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(
        std::string{error.what()},
        "The value this keyword is set to is not supported by this dialect");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/type");
  }
}

// A subschema the walker cannot reach, such as one parked under an `x-`
// container, still compiles under the external default when named as an
// entrypoint through an explicitly framed path
TEST(nullable_through_a_nested_entrypoint_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "foo": { "type": "string", "nullable": true }
    }
  })JSON")};

  const sourcemeta::core::Pointer foo{"x-definitions", "foo"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(foo)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/foo",
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{nullptr};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

// Framing a second, invalid schema must not leak into the selected
// entrypoint: compilation answers for the named schema and nothing else
TEST(nested_entrypoint_ignores_an_unrelated_framed_schema_accepts_null_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/good",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("null")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type",
                     "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type",
                              "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "string and it was of type null");
}

TEST(
    nested_entrypoint_ignores_an_unrelated_framed_schema_accepts_a_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/good",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"a"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type",
                     "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type",
                              "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "string and it was of type string");
}

TEST(
    nested_entrypoint_ignores_an_unrelated_framed_schema_rejects_an_integer_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/good",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type",
                     "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type",
                              "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "string but it was of type integer");
}

TEST(invalid_nested_entrypoint_is_still_rejected_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, frame,
        "#/x-definitions/bad", sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(
        std::string{error.what()},
        "The value this keyword is set to is not supported by this dialect");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/x-definitions/bad/type");
  }
}

// A custom compiler callback may start an independent compilation of an
// unrelated schema while the outer one is in flight. The dialect keeps no
// state across compilations, so the nested schema compiles exactly as it
// does standalone
TEST(nested_independent_compilation_accepts_null_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::Context &context,
                const sourcemeta::blaze::SchemaContext &schema_context,
                const sourcemeta::blaze::DynamicContext &dynamic_context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, schema_context,
                                                      dynamic_context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("null")};
  EVALUATE_WITH_TRACE(nested.value(), instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type null");
}

TEST(nested_independent_compilation_accepts_an_integer_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::Context &context,
                const sourcemeta::blaze::SchemaContext &schema_context,
                const sourcemeta::blaze::DynamicContext &dynamic_context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, schema_context,
                                                      dynamic_context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE(nested.value(), instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type integer");
}

TEST(nested_independent_compilation_rejects_a_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::Context &context,
                const sourcemeta::blaze::SchemaContext &schema_context,
                const sourcemeta::blaze::DynamicContext &dynamic_context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, schema_context,
                                                      dynamic_context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON instance{"a"};
  EVALUATE_WITH_TRACE(nested.value(), instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer but it was of type string");
}

TEST(nested_independent_compilation_matches_a_standalone_compilation_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::Context &context,
                const sourcemeta::blaze::SchemaContext &schema_context,
                const sourcemeta::blaze::DynamicContext &dynamic_context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, schema_context,
                                                      dynamic_context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
    "type": "integer",
    "nullable": true
  })JSON")};

  const auto standalone{sourcemeta::blaze::compile(
      inner, sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  EXPECT_EQ(sourcemeta::blaze::to_json(nested.value()),
            sourcemeta::blaze::to_json(standalone));
}

// `date` and `date-time` name different RFC 3339 productions, so neither
// accepts the other's shape
TEST(format_date_rejects_a_date_time_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-10-08T00:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-10-08T00:00:00Z\" was expected to represent a "
      "valid RFC 3339 full-date");
}

TEST(format_date_time_rejects_a_date_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-10-08"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-10-08\" was expected to represent a valid RFC "
      "3339 date-time");
}

// The specification names RFC 4648 Section 4, whose alphabet is not the
// Section 5 one that spells the last two characters as `-` and `_`
TEST(format_byte_rejects_base64url_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  const sourcemeta::core::JSON instance{"a-_b"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"a-_b\" was expected to represent a valid RFC 4648 "
      "Base64 string");
}

// The specification counts `1` and `1.0` as the same integer, so a real with
// no fractional part satisfies a format defined for signed integers
TEST(format_int32_accepts_an_integral_real_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "int32"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(5.0)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_WITH_DEFAULT_DIALECT(
      schema, instance, 1, OPENAPI_3_0_DIALECT, tweaks);

  EVALUATE_TRACE_PRE(0, AssertionNumberIntegerBounded, "/format", "#/format",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNumberIntegerBounded, "/format",
                              "#/format", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 5.0 was expected to be an "
                               "integer between -2147483648 and 2147483647");
}

// Widening a scalar type with `nullable` must not loosen the type itself, and
// this rung keeps Draft 4's rule that a real is no integer. The JavaScript
// port cannot carry this case, as `JSON.parse` renders `2.0` as `2`
TEST(nullable_integer_rejects_an_integral_real_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "integer",
    "nullable": true
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(2.0)JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE_WITH_DEFAULT_DIALECT(schema, instance, 1,
                                                        OPENAPI_3_0_DIALECT);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type null, or integer but it was of "
      "type number");
}

TEST(type_integer_beside_enum_rejects_an_integral_real_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "integer",
    "enum": [ 1 ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(1.0)JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE_WITH_DEFAULT_DIALECT(schema, instance, 2,
                                                        OPENAPI_3_0_DIALECT);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 1.0 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type integer but it was of type number");
}
