#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <string_view>
#include <unordered_set>

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

TEST(Evaluator_2020_12,
     prop_type_integer_bounded_6_exhaustive_annotations_none) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 3.0 })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations.emplace();

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 4, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/properties/x/type",
                     "#/properties/x/type", "/x");
  EVALUATE_TRACE_PRE(2, AssertionLessEqual, "/properties/x/maximum",
                     "#/properties/x/maximum", "/x");
  EVALUATE_TRACE_PRE(3, AssertionGreaterEqual, "/properties/x/minimum",
                     "#/properties/x/minimum", "/x");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/properties/x/type",
                              "#/properties/x/type", "/x");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionLessEqual, "/properties/x/maximum",
                              "#/properties/x/maximum", "/x");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionGreaterEqual, "/properties/x/minimum",
                              "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalWhenType, "/properties", "#/properties",
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
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}

TEST(Evaluator_2020_12,
     prop_type_integer_bounded_6_exhaustive_annotations_selected) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 3.0 })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"properties"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 5, "",
                                                 tweaks);

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

TEST(Evaluator_2020_12, annotation_contains_nested_not_short_circuited) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "title": "x", "type": "string" }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ "a", "b" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"title"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 5, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/contains/title", "#/contains/title", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/contains/title", "#/contains/title", "/1");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/contains/title", "#/contains/title", "/0",
                                 "x");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/contains/title", "#/contains/title", "/1",
                                 "x");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The title of the instance location \"/0\" was \"x\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2, "The title of the instance location \"/1\" was \"x\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The array value was expected to contain at "
                               "least 1 item that validates against the given "
                               "subschema");
}

TEST(Evaluator_2020_12, annotation_custom_keyword_selected) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My title",
    "x-test-custom": "hello"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"x-test-custom"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-test-custom", "#/x-test-custom", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-test-custom", "#/x-test-custom", "",
                                 "hello");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The unrecognized keyword \"x-test-custom\" was "
                               "collected as the annotation \"hello\"");
}

TEST(Evaluator_2020_12, annotation_fast_mode_respects_tweak) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "title": "My title"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"title"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 2, "", tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/title", "#/title", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/title", "#/title", "", "My title");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The title of the instance was \"My title\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_2020_12,
     annotation_properties_closed_object_fast_keeps_closure) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo" ],
    "additionalProperties": false,
    "properties": { "foo": { "type": "string" } }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "bar", "extra": 1 })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"properties"};

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 5, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionDefinesStrict, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionFail, "/additionalProperties",
                     "#/additionalProperties", "/extra");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/properties", "#/properties", "", "foo");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionFail, "/additionalProperties",
                              "#/additionalProperties", "/extra");
  EVALUATE_TRACE_POST_FAILURE(4, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an object that defines the property "
      "\"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define the property \"extra\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_2020_12, unevaluated_properties_annotations_none_still_tracks) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "a": { "type": "integer" } },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": 1, "b": 2 })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations.emplace();

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive, "", "", "", tweaks)};

  // Even with all annotations filtered out, evaluation tracking still marks "a"
  // as evaluated, so the unevaluated "b" is rejected
  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));

  const sourcemeta::core::JSON evaluated{
      sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};
  EXPECT_TRUE(evaluator.validate(compiled_schema, evaluated));
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

TEST(Evaluator_2020_12, format_uri_x_assertion_true_valid_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_2020_12, format_uri_x_assertion_true_invalid_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(Evaluator_2020_12, format_uri_x_assertion_true_valid_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/x-format-assertion",
                                "#/x-format-assertion", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/x-format-assertion",
                                 "#/x-format-assertion", "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The unrecognized keyword \"x-format-assertion\""
                               " was collected as the annotation true");
}

TEST(Evaluator_2020_12,
     format_uri_x_assertion_true_invalid_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(Evaluator_2020_12, format_uri_x_assertion_false_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri",
    "x-format-assertion": false
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-format-assertion",
                                "#/x-format-assertion", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "uri");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-format-assertion",
                                 "#/x-format-assertion", "", false);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"uri\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The unrecognized keyword \"x-format-assertion\""
                               " was collected as the annotation false");
}

TEST(Evaluator_2020_12, x_assertion_true_without_format_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_2020_12, x_assertion_true_without_format_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-format-assertion",
                                "#/x-format-assertion", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-format-assertion",
                                 "#/x-format-assertion", "", true);
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The unrecognized keyword \"x-format-assertion\""
                               " was collected as the annotation true");
}

TEST(Evaluator_2020_12, x_assertion_nested_selective_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "relaxed": {
        "format": "uri"
      },
      "strict": {
        "format": "uri",
        "x-format-assertion": true
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "relaxed": "://bad", "strict": "://bad" })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/strict/format",
                     "#/properties/strict/format", "/strict");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType,
                              "/properties/strict/format",
                              "#/properties/strict/format", "/strict");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(Evaluator_2020_12, x_assertion_nested_selective_valid_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "relaxed": {
        "format": "uri"
      },
      "strict": {
        "format": "uri",
        "x-format-assertion": true
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "relaxed": "://bad", "strict": "https://example.com" })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/strict/format",
                     "#/properties/strict/format", "/strict");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType,
                              "/properties/strict/format",
                              "#/properties/strict/format", "/strict");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_2020_12, annotation_fast_metadata_title) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "Test title"
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"title"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/title", "#/title", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/title", "#/title", "", "Test title");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The title of the instance was \"Test title\"");
}

TEST(Evaluator_2020_12, annotation_fast_metadata_selective) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "T",
  "description": "D"
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"title"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/title", "#/title", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/title", "#/title", "", "T");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The title of the instance was \"T\"");
}

TEST(Evaluator_2020_12, annotation_fast_format) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "format": "email"
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("a@b.com")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"format"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "email");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"email\"");
}

TEST(Evaluator_2020_12, annotation_fast_content_media_type) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "contentMediaType": "text/plain"
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("hi")JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "contentMediaType"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/contentMediaType", "#/contentMediaType",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/contentMediaType", "#/contentMediaType",
                                 "", "text/plain");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The content media type of the instance was \"text/plain\"");
}

TEST(Evaluator_2020_12, annotation_fast_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "properties": {
    "foo": {
      "type": "string"
    }
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "x" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"properties"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 2, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
}

TEST(Evaluator_2020_12, annotation_fast_pattern_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "patternProperties": {
    "^x": {
      "type": "string"
    }
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "xa": "y" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "patternProperties"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^x/type",
                     "#/patternProperties/%5Ex/type", "/xa");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/patternProperties", "#/patternProperties",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^x/type",
                              "#/patternProperties/%5Ex/type", "/xa");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                 "", "xa");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object property \"xa\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that start with the string \"x\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_2020_12, annotation_fast_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "properties": {
    "foo": {
      "type": "integer"
    }
  },
  "additionalProperties": {
    "type": "string"
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": 1, "bar": "y" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "additionalProperties"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 4, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionPropertyType, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/additionalProperties",
                                "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyType, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/additionalProperties",
                                 "#/additionalProperties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object property \"bar\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_2020_12, annotation_fast_prefix_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "prefixItems": [
    {
      "type": "integer"
    }
  ]
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1 ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"prefixItems"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 4, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/prefixItems", "#/prefixItems", "");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/prefixItems", "#/prefixItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/prefixItems", "#/prefixItems", "", 0);
  EVALUATE_TRACE_POST_ANNOTATION(2, "/prefixItems", "#/prefixItems", "", true);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item of the array value validated "
                               "against the given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
}

TEST(Evaluator_2020_12, annotation_fast_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "prefixItems": [
    {
      "type": "integer"
    }
  ],
  "items": {
    "type": "string"
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1, "a" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"items"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 6, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsFrom, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(4, LogicalWhenArraySizeGreater, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItemsFrom, "/items", "#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(5, LogicalWhenArraySizeGreater, "/items",
                              "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "Every item in the array value except for the first one was expected to "
      "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The array value contains 1 additional item not "
                               "described by related keywords");
}

TEST(Evaluator_2020_12, annotation_fast_contains) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "contains": {
    "type": "integer"
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1, 2 ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"contains"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 5, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/contains/type", "#/contains/type",
                     "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(3, AssertionType, "/contains/type", "#/contains/type",
                     "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/contains", "#/contains", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionType, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/contains", "#/contains", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(4, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The item at index 0 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The item at index 1 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2020_12, annotation_fast_unevaluated_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "properties": {
    "foo": {
      "type": "integer"
    }
  },
  "unevaluatedProperties": {
    "type": "string"
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": 1, "bar": "y" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "unevaluatedProperties"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 4, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionPropertyType, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesExcept, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/unevaluatedProperties",
                                "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyType, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/unevaluatedProperties",
                                 "#/unevaluatedProperties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesExcept, "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object property \"bar\" successfully validated against the "
      "subschema for unevaluated properties");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, annotation_fast_unevaluated_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "prefixItems": [
    {
      "type": "integer"
    }
  ],
  "unevaluatedItems": {
    "type": "string"
  }
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1, "a" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "unevaluatedItems"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 5, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/prefixItems",
                     "#/prefixItems", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/unevaluatedItems", "#/unevaluatedItems",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefixEvaluate, "/prefixItems",
                              "#/prefixItems", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/unevaluatedItems", "#/unevaluatedItems",
                                 "", true);
  EVALUATE_TRACE_POST_SUCCESS(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "At least one item of the array value successfully validated against the "
      "subschema for unevaluated items");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, annotation_fast_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "x-custom": "hello"
})JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(5)JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"x-custom"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-custom", "#/x-custom", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-custom", "#/x-custom", "", "hello");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The unrecognized keyword \"x-custom\" was "
                               "collected as the annotation \"hello\"");
}
