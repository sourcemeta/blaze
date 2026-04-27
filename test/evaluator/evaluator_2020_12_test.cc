#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_2020_12, metaschema_hyper_1) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 24, "");
}

TEST(Evaluator_2020_12, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 100,
                                   "");
}

TEST(Evaluator_2020_12, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
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
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
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
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
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
