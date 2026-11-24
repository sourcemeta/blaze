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
      [&nested](const sourcemeta::blaze::KeywordContext &context,
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

    return sourcemeta::blaze::default_schema_compiler(context, current);
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
      [&nested](const sourcemeta::blaze::KeywordContext &context,
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

    return sourcemeta::blaze::default_schema_compiler(context, current);
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
      [&nested](const sourcemeta::blaze::KeywordContext &context,
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

    return sourcemeta::blaze::default_schema_compiler(context, current);
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
      [&nested](const sourcemeta::blaze::KeywordContext &context,
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

    return sourcemeta::blaze::default_schema_compiler(context, current);
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
