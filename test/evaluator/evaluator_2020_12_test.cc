#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <string_view>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "evaluator_utils.h"

static const std::string FORMAT_ASSERTION_METASCHEMA_URI{
    "https://example.com/2020-12-format-assertion-meta"};

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == FORMAT_ASSERTION_METASCHEMA_URI) {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/2020-12-format-assertion-meta",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true,
        "https://json-schema.org/draft/2020-12/vocab/format-assertion": true
      },
      "$dynamicAnchor": "meta",
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2020-12/meta/core" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/applicator" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/validation" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/format-assertion" }
      ]
    })JSON");
  }

  return sourcemeta::blaze::schema_resolver(identifier);
}

TEST(Evaluator_2020_12, metaschema_hyper_1) {
  const auto metaschema{sourcemeta::blaze::schema_resolver(
      "https://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 24, "");
}

TEST(Evaluator_2020_12, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::blaze::schema_resolver(
      "https://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 100,
                                   "");
}

TEST(Evaluator_2020_12, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::blaze::schema_resolver(
      "https://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         207, "");
}

TEST(Evaluator_2020_12, dynamicRef_with_multiple_anchors) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "https://example.com/target#meta",
    "$defs": {
      "target": {
        "$id": "https://example.com/target",
        "$dynamicAnchor": "meta",
        "type": "boolean"
      },
      "other": {
        "$id": "https://example.com/other",
        "$dynamicAnchor": "meta",
        "type": "number"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, ControlDynamicAnchorJump, "/$dynamicRef",
                     "#/$dynamicRef", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/$dynamicRef/type",
                     "https://example.com/target#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$dynamicRef/type",
                              "https://example.com/target#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlDynamicAnchorJump, "/$dynamicRef",
                              "#/$dynamicRef", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The boolean value was expected to validate against the first subschema "
      "in scope that declared the dynamic anchor \"meta\"");
}

TEST(Evaluator_2020_12, dynamicRef_with_multiple_anchors_from_json) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "https://example.com/target#meta",
    "$defs": {
      "target": {
        "$id": "https://example.com/target",
        "$dynamicAnchor": "meta",
        "type": "boolean"
      },
      "other": {
        "$id": "https://example.com/other",
        "$dynamicAnchor": "meta",
        "type": "number"
      }
    }
  })JSON")};

  const auto original{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const auto roundtripped{
      sourcemeta::blaze::from_json(sourcemeta::blaze::to_json(original))};
  ASSERT_TRUE(roundtripped.has_value());

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE(roundtripped.value(), instance, 2);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, ControlDynamicAnchorJump, "/$dynamicRef",
                     "#/$dynamicRef", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/$dynamicRef/type",
                     "https://example.com/target#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$dynamicRef/type",
                              "https://example.com/target#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlDynamicAnchorJump, "/$dynamicRef",
                              "#/$dynamicRef", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The boolean value was expected to validate against the first subschema "
      "in scope that declared the dynamic anchor \"meta\"");
}

TEST(Evaluator_2020_12, reference_from_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/definitions/bar" },
      "baz": { "type": "string" }
    },
    "definitions": {
      "bar": {
        "$ref": "#/properties/baz"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::blaze::SchemaReferenceError &error) {
    EXPECT_EQ(error.identifier(), "#/properties/baz");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"definitions", "bar", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_2020_12, type_integer_bounded_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "maximum": 100
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_PRE(1, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_PRE(2, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionLessEqual, "/maximum", "#/maximum",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The number value 3.0 was expected to be less "
                               "than or equal to the integer 100");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The number value 3.0 was expected to be "
                               "greater than or equal to the integer 0");
}

TEST(Evaluator_2020_12, type_integer_lower_bound_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 1
  })JSON")};

  const sourcemeta::core::JSON instance{5.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_PRE(1, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The number value 5.0 was expected to be "
                               "greater than or equal to the integer 1");
}

TEST(Evaluator_2020_12, prop_type_integer_bounded_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 3.0 })JSON")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerBounded, "", "#/properties", "/x");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeIntegerBounded, "",
                              "#/properties", "/x");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer within the given range");
}

TEST(Evaluator_2020_12, prop_type_integer_bounded_6_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 3.0 })JSON")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/properties/x/type",
                     "#/properties/x/type", "/x");
  EVALUATE_TRACE_PRE(2, AssertionLessEqual, "/properties/x/maximum",
                     "#/properties/x/maximum", "/x");
  EVALUATE_TRACE_PRE(3, AssertionGreaterEqual, "/properties/x/minimum",
                     "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/properties/x/type",
                              "#/properties/x/type", "/x");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionLessEqual, "/properties/x/maximum",
                              "#/properties/x/maximum", "/x");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionGreaterEqual, "/properties/x/minimum",
                              "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/properties", "#/properties", "", "x");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The number value 3.0 was expected to be less "
                               "than or equal to the integer 100");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The number value 3.0 was expected to be "
                               "greater than or equal to the integer 0");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object property \"x\" successfully "
                               "validated against its property subschema");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}

TEST(Evaluator_2020_12, prop_type_integer_lower_bound_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "type": "integer", "minimum": 1 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 5.0 })JSON")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerLowerBound, "", "#/properties",
                     "/x");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeIntegerLowerBound, "",
                              "#/properties", "/x");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer above the given minimum");
}

TEST(Evaluator_2020_12, prop_type_integer_lower_bound_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "type": "integer", "minimum": 1 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 5.0 })JSON")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/properties/x/type",
                     "#/properties/x/type", "/x");
  EVALUATE_TRACE_PRE(2, AssertionGreaterEqual, "/properties/x/minimum",
                     "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/properties/x/type",
                              "#/properties/x/type", "/x");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionGreaterEqual, "/properties/x/minimum",
                              "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/properties", "#/properties", "", "x");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The number value 5.0 was expected to be "
                               "greater than or equal to the integer 1");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object property \"x\" successfully "
                               "validated against its property subschema");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}
TEST(Evaluator_2020_12, format_date_time_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15T14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15T14:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_2020_12, format_date_time_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-date\" was expected to represent a valid RFC "
      "3339 date-time");
}

TEST(Evaluator_2020_12, format_date_time_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15T14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "date-time");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15T14:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"date-time\"");
}

TEST(Evaluator_2020_12, format_date_time_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-date\" was expected to represent a valid RFC "
      "3339 date-time");
}

TEST(Evaluator_2020_12, format_date_time_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_date_time_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "date-time");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"date-time\"");
}

TEST(Evaluator_2020_12, format_date_time_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_date_time_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_date_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15\" was expected to represent a valid RFC "
      "3339 full-date");
}

TEST(Evaluator_2020_12, format_date_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-13-45"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-13-45\" was expected to represent a valid RFC "
      "3339 full-date");
}

TEST(Evaluator_2020_12, format_date_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "date");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15\" was expected to represent a valid RFC "
      "3339 full-date");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"date\"");
}

TEST(Evaluator_2020_12, format_date_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-13-45"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-13-45\" was expected to represent a valid RFC "
      "3339 full-date");
}

TEST(Evaluator_2020_12, format_date_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-13-45"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_date_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-13-45"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "date");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"date\"");
}

TEST(Evaluator_2020_12, format_date_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_date_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_time_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"14:00:00Z\" was expected to represent a valid RFC "
      "3339 full-time");
}

TEST(Evaluator_2020_12, format_time_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"25:00:00"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"25:00:00\" was expected to represent a valid RFC "
      "3339 full-time");
}

TEST(Evaluator_2020_12, format_time_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "time");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"14:00:00Z\" was expected to represent a valid RFC "
      "3339 full-time");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"time\"");
}

TEST(Evaluator_2020_12, format_time_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"25:00:00"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"25:00:00\" was expected to represent a valid RFC "
      "3339 full-time");
}

TEST(Evaluator_2020_12, format_time_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"25:00:00"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_time_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"25:00:00"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "time");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"time\"");
}

TEST(Evaluator_2020_12, format_time_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_time_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_duration_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{"P1D"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"P1D\" was expected to represent a valid RFC 3339 "
      "duration");
}

TEST(Evaluator_2020_12, format_duration_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{"1 day"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"1 day\" was expected to represent a valid RFC 3339 "
      "duration");
}

TEST(Evaluator_2020_12, format_duration_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{"P1D"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "duration");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"P1D\" was expected to represent a valid RFC 3339 "
      "duration");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"duration\"");
}

TEST(Evaluator_2020_12, format_duration_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{"1 day"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"1 day\" was expected to represent a valid RFC 3339 "
      "duration");
}

TEST(Evaluator_2020_12, format_duration_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{"1 day"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_duration_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{"1 day"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "duration");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"duration\"");
}

TEST(Evaluator_2020_12, format_duration_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_duration_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "duration"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_email_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_2020_12, format_email_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a valid "
      "email address");
}

TEST(Evaluator_2020_12, format_email_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "email");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid email address");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"email\"");
}

TEST(Evaluator_2020_12, format_email_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a valid "
      "email address");
}

TEST(Evaluator_2020_12, format_email_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_email_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "email");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"email\"");
}

TEST(Evaluator_2020_12, format_email_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_email_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_idn_email_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid internationalized email address");
}

TEST(Evaluator_2020_12, format_idn_email_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a valid "
      "internationalized email address");
}

TEST(Evaluator_2020_12, format_idn_email_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "idn-email");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid internationalized email address");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"idn-email\"");
}

TEST(Evaluator_2020_12, format_idn_email_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a valid "
      "internationalized email address");
}

TEST(Evaluator_2020_12, format_idn_email_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_idn_email_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "idn-email");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"idn-email\"");
}

TEST(Evaluator_2020_12, format_idn_email_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_idn_email_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_hostname_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"example.com\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_2020_12, format_hostname_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_2020_12, format_hostname_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "hostname");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"example.com\" was expected to represent a valid "
      "hostname");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"hostname\"");
}

TEST(Evaluator_2020_12, format_hostname_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_2020_12, format_hostname_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_hostname_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "hostname");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"hostname\"");
}

TEST(Evaluator_2020_12, format_hostname_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_hostname_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_idn_hostname_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"example.com\" was expected to represent a valid "
      "internationalized hostname");
}

TEST(Evaluator_2020_12, format_idn_hostname_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a valid "
      "internationalized hostname");
}

TEST(Evaluator_2020_12, format_idn_hostname_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "idn-hostname");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"example.com\" was expected to represent a valid "
      "internationalized hostname");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"idn-hostname\"");
}

TEST(Evaluator_2020_12, format_idn_hostname_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a valid "
      "internationalized hostname");
}

TEST(Evaluator_2020_12, format_idn_hostname_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_idn_hostname_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "idn-hostname");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"idn-hostname\"");
}

TEST(Evaluator_2020_12, format_idn_hostname_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_idn_hostname_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "idn-hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_ipv4_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"192.168.1.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"192.168.1.1\" was expected to represent a valid "
      "IPv4 address");
}

TEST(Evaluator_2020_12, format_ipv4_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a valid IPv4 "
      "address");
}

TEST(Evaluator_2020_12, format_ipv4_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"192.168.1.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "ipv4");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"192.168.1.1\" was expected to represent a valid "
      "IPv4 address");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"ipv4\"");
}

TEST(Evaluator_2020_12, format_ipv4_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a valid IPv4 "
      "address");
}

TEST(Evaluator_2020_12, format_ipv4_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_ipv4_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "ipv4");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"ipv4\"");
}

TEST(Evaluator_2020_12, format_ipv4_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_ipv4_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_ipv6_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"::1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"::1\" was expected to represent a valid IPv6 "
      "address");
}

TEST(Evaluator_2020_12, format_ipv6_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-ipv6"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-ipv6\" was expected to represent a valid "
      "IPv6 address");
}

TEST(Evaluator_2020_12, format_ipv6_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"::1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "ipv6");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"::1\" was expected to represent a valid IPv6 "
      "address");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"ipv6\"");
}

TEST(Evaluator_2020_12, format_ipv6_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-ipv6"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-ipv6\" was expected to represent a valid "
      "IPv6 address");
}

TEST(Evaluator_2020_12, format_ipv6_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-ipv6"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_ipv6_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-ipv6"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "ipv6");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"ipv6\"");
}

TEST(Evaluator_2020_12, format_ipv6_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_ipv6_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_uri_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, format_uri_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, format_uri_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, format_uri_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, format_uri_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_uri_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, format_uri_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_uri_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_uri_reference_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"/relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/relative/path\" was expected to represent a valid "
      "URI reference");
}

TEST(Evaluator_2020_12, format_uri_reference_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
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
      "The string value \"://bad\" was expected to represent a valid URI "
      "reference");
}

TEST(Evaluator_2020_12, format_uri_reference_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"/relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri-reference");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/relative/path\" was expected to represent a valid "
      "URI reference");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri-reference\"");
}

TEST(Evaluator_2020_12, format_uri_reference_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
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
      "The string value \"://bad\" was expected to represent a valid URI "
      "reference");
}

TEST(Evaluator_2020_12, format_uri_reference_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_uri_reference_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "uri-reference");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"uri-reference\"");
}

TEST(Evaluator_2020_12, format_uri_reference_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_uri_reference_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_iri_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com/path\" was expected to represent "
      "a valid IRI");
}

TEST(Evaluator_2020_12, format_iri_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
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
      "The string value \"://bad\" was expected to represent a valid IRI");
}

TEST(Evaluator_2020_12, format_iri_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "iri");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com/path\" was expected to represent "
      "a valid IRI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"iri\"");
}

TEST(Evaluator_2020_12, format_iri_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
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
      "The string value \"://bad\" was expected to represent a valid IRI");
}

TEST(Evaluator_2020_12, format_iri_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_iri_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "iri");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"iri\"");
}

TEST(Evaluator_2020_12, format_iri_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_iri_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_iri_reference_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"/relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/relative/path\" was expected to represent a valid "
      "IRI reference");
}

TEST(Evaluator_2020_12, format_iri_reference_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
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
      "The string value \"://bad\" was expected to represent a valid IRI "
      "reference");
}

TEST(Evaluator_2020_12, format_iri_reference_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"/relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "iri-reference");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/relative/path\" was expected to represent a valid "
      "IRI reference");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"iri-reference\"");
}

TEST(Evaluator_2020_12, format_iri_reference_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
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
      "The string value \"://bad\" was expected to represent a valid IRI "
      "reference");
}

TEST(Evaluator_2020_12, format_iri_reference_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_iri_reference_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "iri-reference");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"iri-reference\"");
}

TEST(Evaluator_2020_12, format_iri_reference_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_iri_reference_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "iri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_uri_template_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"http://example.com/{var}"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"http://example.com/{var}\" was expected to represent "
      "a valid URI template");
}

TEST(Evaluator_2020_12, format_uri_template_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"{bad"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"{bad\" was expected to represent a valid URI "
      "template");
}

TEST(Evaluator_2020_12, format_uri_template_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"http://example.com/{var}"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri-template");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"http://example.com/{var}\" was expected to represent "
      "a valid URI template");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri-template\"");
}

TEST(Evaluator_2020_12, format_uri_template_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"{bad"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"{bad\" was expected to represent a valid URI "
      "template");
}

TEST(Evaluator_2020_12, format_uri_template_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"{bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_uri_template_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"{bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "uri-template");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"uri-template\"");
}

TEST(Evaluator_2020_12, format_uri_template_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_uri_template_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_json_pointer_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/foo/bar"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/foo/bar\" was expected to represent a valid JSON "
      "Pointer");
}

TEST(Evaluator_2020_12, format_json_pointer_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"no-leading-slash"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"no-leading-slash\" was expected to represent a "
      "valid JSON Pointer");
}

TEST(Evaluator_2020_12, format_json_pointer_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/foo/bar"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "json-pointer");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/foo/bar\" was expected to represent a valid JSON "
      "Pointer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"json-pointer\"");
}

TEST(Evaluator_2020_12, format_json_pointer_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"no-leading-slash"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"no-leading-slash\" was expected to represent a "
      "valid JSON Pointer");
}

TEST(Evaluator_2020_12, format_json_pointer_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"no-leading-slash"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_json_pointer_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"no-leading-slash"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "json-pointer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"json-pointer\"");
}

TEST(Evaluator_2020_12, format_json_pointer_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_json_pointer_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_relative_json_pointer_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"1/foo"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"1/foo\" was expected to represent a valid relative "
      "JSON Pointer");
}

TEST(Evaluator_2020_12, format_relative_json_pointer_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/absolute"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/absolute\" was expected to represent a valid "
      "relative JSON Pointer");
}

TEST(Evaluator_2020_12,
     format_relative_json_pointer_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"1/foo"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "",
                                 "relative-json-pointer");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"1/foo\" was expected to represent a valid relative "
      "JSON Pointer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The logical type of the instance was expected "
                               "to be \"relative-json-pointer\"");
}

TEST(Evaluator_2020_12,
     format_relative_json_pointer_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/absolute"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/absolute\" was expected to represent a valid "
      "relative JSON Pointer");
}

TEST(Evaluator_2020_12, format_relative_json_pointer_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/absolute"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_relative_json_pointer_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/absolute"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "",
                                 "relative-json-pointer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The logical type of the instance was expected "
                               "to be \"relative-json-pointer\"");
}

TEST(Evaluator_2020_12,
     format_relative_json_pointer_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12,
     format_relative_json_pointer_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "relative-json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_regex_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"^[abc]+$"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"^[abc]+$\" was expected to represent a valid "
      "ECMA-262 regular expression");
}

TEST(Evaluator_2020_12, format_regex_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"["};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"[\" was expected to represent a valid ECMA-262 "
      "regular expression");
}

TEST(Evaluator_2020_12, format_regex_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"^[abc]+$"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "regex");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"^[abc]+$\" was expected to represent a valid "
      "ECMA-262 regular expression");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"regex\"");
}

TEST(Evaluator_2020_12, format_regex_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"["};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"[\" was expected to represent a valid ECMA-262 "
      "regular expression");
}

TEST(Evaluator_2020_12, format_regex_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"["};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_regex_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"["};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "regex");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"regex\"");
}

TEST(Evaluator_2020_12, format_regex_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_regex_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_uuid_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{"550e8400-e29b-41d4-a716-446655440000"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"550e8400-e29b-41d4-a716-446655440000\" was expected "
      "to represent a valid UUID");
}

TEST(Evaluator_2020_12, format_uuid_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-uuid"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-uuid\" was expected to represent a valid "
      "UUID");
}

TEST(Evaluator_2020_12, format_uuid_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{"550e8400-e29b-41d4-a716-446655440000"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 2, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uuid");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"550e8400-e29b-41d4-a716-446655440000\" was expected "
      "to represent a valid UUID");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uuid\"");
}

TEST(Evaluator_2020_12, format_uuid_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-uuid"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-uuid\" was expected to represent a valid "
      "UUID");
}

TEST(Evaluator_2020_12, format_uuid_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-uuid"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, format_uuid_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-uuid"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "uuid");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"uuid\"");
}

TEST(Evaluator_2020_12, format_uuid_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_uuid_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uuid"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}
TEST(Evaluator_2020_12, format_unknown_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "not-a-real-format"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_unknown_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "not-a-real-format"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_keyword_value_integer_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": 42
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_keyword_value_integer_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": 42
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_keyword_value_null_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": null
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_2020_12, format_keyword_value_null_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": null
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_2020_12, format_under_properties_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "format": "uri" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "x": "https://example.com" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/x/format",
                     "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/properties/x/format",
                              "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_2020_12, format_under_properties_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "format": "uri-reference" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "://bad" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/x/format",
                     "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/properties/x/format",
                              "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI "
      "reference");
}

TEST(Evaluator_2020_12, format_under_items_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "format": "json-pointer" }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ "/foo", "/bar/baz" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopItemsFrom, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/items/format", "#/items/format",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/items/format", "#/items/format",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/items/format",
                              "#/items/format", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringType, "/items/format",
                              "#/items/format", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopItemsFrom, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"/foo\" was expected to represent a valid JSON "
      "Pointer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value \"/bar/baz\" was expected to represent a valid JSON "
      "Pointer");
}

TEST(Evaluator_2020_12, format_under_items_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "format": "uri-template" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON([ "http://example.com/{var}", "{bad" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopItemsFrom, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/items/format", "#/items/format",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/items/format", "#/items/format",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/items/format",
                              "#/items/format", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionStringType, "/items/format",
                              "#/items/format", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItemsFrom, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"http://example.com/{var}\" was expected to represent "
      "a valid URI template");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value \"{bad\" was expected to represent a valid URI "
      "template");
}

TEST(Evaluator_2020_12, format_with_type_string_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 2, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_2020_12,
     format_with_type_string_invalid_format_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_2020_12, format_with_type_string_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_2020_12,
     format_with_type_integer_short_circuits_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_2020_12, format_uri_with_assertion_vocab_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_2020_12, format_uri_with_assertion_vocab_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(Evaluator_2020_12, format_uri_with_assertion_vocab_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 2)
  EXPECT_TRUE(result);

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

TEST(Evaluator_2020_12, format_uri_with_assertion_vocab_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}
