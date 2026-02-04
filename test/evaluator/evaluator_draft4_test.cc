#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft4, metaschema_1) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 3, "");
}

TEST(Evaluator_draft4, metaschema_2) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "type": [ "string" ]
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 16, "");
}

TEST(Evaluator_draft4, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 768,
                                   "");
}

TEST(Evaluator_draft4, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         957, "");
}

TEST(Evaluator_draft4, unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "foobar": "baz"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, annotation_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "title": "foo"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, annotation_keyword_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "title": "foo"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, type_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, type_1_hyperschema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/hyper-schema#",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, type_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string "
                               "but it was of type integer");
}

TEST(Evaluator_draft4, type_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, type_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, type_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{"3.14"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type number but it was of type string");
}

TEST(Evaluator_draft4, type_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, type_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_draft4, type_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number", "object" ]
  })JSON")};

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number, "
                               "string, or object and it was of type number");
}

TEST(Evaluator_draft4, type_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number", "object" ]
  })JSON")};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number, "
                               "string, or object but it was of type boolean");
}

TEST(Evaluator_draft4, type_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft4, type_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft4, type_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string and it was of type integer");
}

TEST(Evaluator_draft4, type_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string but it was of type number");
}

TEST(Evaluator_draft4, required_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, required_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionDefines, "/required", "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefines, "/required", "#/required",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"foo\"");
}

TEST(Evaluator_draft4, required_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "baz" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionDefinesAll, "/required", "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesAll, "/required", "#/required",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define properties \"baz\", and \"foo\" "
      "but did not define the property \"baz\"");
}

TEST(Evaluator_draft4, required_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesAllStrict, "/required", "#/required",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAllStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"foo\"");
}

TEST(Evaluator_draft4, required_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");
  EVALUATE_TRACE_PRE(0, AssertionDefinesAllStrict, "/required", "#/required",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAllStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, required_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    },
    "patternProperties": { "^@": {} },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": true,
    "bar": true,
    "@baz": true
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesAllStrict, "/required", "#/required",
                     "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAllStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_draft4, required_5_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    },
    "patternProperties": { "^@": {} },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": true,
    "bar": true,
    "@baz": true
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesAllStrict, "/required", "#/required",
                     "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAllStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was not expected to define additional properties");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, required_6) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "required": "bar"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": {}
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, allOf_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "object" },
      { "required": [ "foo", "bar" ] }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/allOf/0/type", "#/allOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionDefinesAll, "/allOf/1/required",
                     "#/allOf/1/required", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/type",
                              "#/allOf/0/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionDefinesAll, "/allOf/1/required",
                              "#/allOf/1/required", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to define "
                               "properties \"bar\", and \"foo\"");
}

TEST(Evaluator_draft4, allOf_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "object" },
      { "required": [ "foo", "bar" ] }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/allOf/0/type", "#/allOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionDefinesAll, "/allOf/1/required",
                     "#/allOf/1/required", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/type",
                              "#/allOf/0/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionDefinesAll, "/allOf/1/required",
                              "#/allOf/1/required", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the 2 given subschemas");
}

TEST(Evaluator_draft4, allOf_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "object" },
      { "required": [ "foo", "bar" ] }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"baz\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/allOf/0/type", "#/allOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionDefinesAll, "/allOf/1/required",
                     "#/allOf/1/required", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/type",
                              "#/allOf/0/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionDefinesAll, "/allOf/1/required",
                              "#/allOf/1/required", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was expected to define properties \"bar\", and \"foo\" "
      "but did not define the property \"bar\"");
}

TEST(Evaluator_draft4, ref_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_draft4, ref_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, ref_2_entrypoint) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "#/allOf/0");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, ref_2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, ControlJump, "/allOf/0/$ref", "#/allOf/0/$ref", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/definitions/string/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlJump, "/allOf/0/$ref", "#/allOf/0/$ref",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The string value was expected to validate against the given subschema");
}

TEST(Evaluator_draft4, ref_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "https://example.com"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": {} }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, ControlJump, "/properties/foo/$ref",
                     "https://example.com#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/$ref/type",
                     "https://example.com#/type", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type",
                     "https://example.com#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/properties/foo/$ref/type",
                              "https://example.com#/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlJump, "/properties/foo/$ref",
                              "https://example.com#/properties/foo/$ref",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type",
                              "https://example.com#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, ref_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "https://example.com"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": { \"foo\": {} } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, ControlJump, "/properties/foo/$ref",
                     "https://example.com#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_PRE(1, ControlJump, "/properties/foo/$ref/properties/foo/$ref",
                     "https://example.com#/properties/foo/$ref", "/foo/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict,
                     "/properties/foo/$ref/properties/foo/$ref/type",
                     "https://example.com#/type", "/foo/foo");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/properties/foo/$ref/type",
                     "https://example.com#/type", "/foo");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/type",
                     "https://example.com#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/properties/foo/$ref/properties/foo/$ref/type",
                              "https://example.com#/type", "/foo/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlJump, "/properties/foo/$ref/properties/foo/$ref",
      "https://example.com#/properties/foo/$ref", "/foo/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict,
                              "/properties/foo/$ref/type",
                              "https://example.com#/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, ControlJump, "/properties/foo/$ref",
                              "https://example.com#/properties/foo/$ref",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/type",
                              "https://example.com#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, ref_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "https://example.com"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": { \"foo\": 1 } }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, ControlJump, "/properties/foo/$ref",
                     "https://example.com#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_PRE(1, ControlJump, "/properties/foo/$ref/properties/foo/$ref",
                     "https://example.com#/properties/foo/$ref", "/foo/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict,
                     "/properties/foo/$ref/properties/foo/$ref/type",
                     "https://example.com#/type", "/foo/foo");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict,
                              "/properties/foo/$ref/properties/foo/$ref/type",
                              "https://example.com#/type", "/foo/foo");
  EVALUATE_TRACE_POST_FAILURE(
      1, ControlJump, "/properties/foo/$ref/properties/foo/$ref",
      "https://example.com#/properties/foo/$ref", "/foo/foo");
  EVALUATE_TRACE_POST_FAILURE(2, ControlJump, "/properties/foo/$ref",
                              "https://example.com#/properties/foo/$ref",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type object but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the referenced schema");
}

TEST(Evaluator_draft4, ref_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "#"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": {} }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, ControlJump, "/properties/foo/$ref",
                     "#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/$ref/type",
                     "#/type", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/properties/foo/$ref/type", "#/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlJump, "/properties/foo/$ref",
                              "#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, ref_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "a": { "$ref": "#" },
      "b": { "$ref": "#" },
      "c": { "$ref": "#" },
      "d": { "$ref": "#" },
      "e": { "$ref": "#" },
      "f": { "$ref": "#" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, LoopPropertiesMatch, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesMatch, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to validate "
                               "against the 6 defined properties subschemas");
}

TEST(Evaluator_draft4, ref_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/foo" } ],
    "definitions": {
      "foo": {
        "additionalProperties": {
          "$ref": "#/definitions/bar"
        }
      },
      "bar": {
        "additionalProperties": {
          "$ref": "#/definitions/foo"
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, ref_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": { "$ref": "#/definitions/one" },
    "definitions": {
      "one": { "$ref": "#/definitions/two" },
      "two": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict,
                     "/additionalProperties/$ref/$ref/type",
                     "#/definitions/two/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties/$ref/$ref/type",
                              "#/definitions/two/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type boolean");
}

TEST(Evaluator_draft4, ref_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "$ref": "#/definitions/one" },
    "additionalProperties": { "$ref": "#/definitions/one" },
    "definitions": {
      "one": { "$ref": "#/definitions/two" },
      "two": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict,
                     "/additionalProperties/$ref/$ref/type",
                     "#/definitions/two/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties/$ref/$ref/type",
                              "#/definitions/two/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type boolean");
}

TEST(Evaluator_draft4, ref_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler),
      sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com") {
      return sourcemeta::core::parse_json(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::core::schema_walker, test_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com") {
      return sourcemeta::core::parse_json(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::core::schema_walker, test_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/foo" } ],
    "definitions": {
      "foo": { "$ref": "#/definitions/bar" },
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{true};
  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_THROW(evaluator.validate(compiled_schema, instance),
               sourcemeta::blaze::EvaluationError);
}

TEST(Evaluator_draft4, ref_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "$ref": "#/definitions/three" }
    },
    "definitions": {
      "three": { "$ref": "#/definitions/four" },
      "four": { "$ref": "#/definitions/five" },
      "five": {
        "properties": {
          "requires": {
            "additionalProperties": {
              "type": "string"
            }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": {
      "bar": {}
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, ControlJump, "/properties/foo/$ref/$ref",
                     "#/definitions/three/$ref", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, ControlJump, "/properties/foo/$ref/$ref",
                              "#/definitions/three/$ref", "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to validate against the referenced "
      "schema");
}

TEST(Evaluator_draft4, properties_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string "
                               "but it was of type integer");
}

TEST(Evaluator_draft4, properties_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": \"xxx\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": \"xxx\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the defined properties subschemas");
}

TEST(Evaluator_draft4, properties_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"baz\": [] }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, properties_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "properties": {
          "bar": {
            "type": "string"
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": { \"bar\": \"baz\" } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict,
                     "/properties/foo/properties/bar/type",
                     "#/properties/foo/properties/bar/type", "/foo/bar");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionPropertyTypeStrict, "/properties/foo/properties/bar/type",
      "#/properties/foo/properties/bar/type", "/foo/bar");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "properties": {
          "bar": {
            "type": "string"
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": { \"bar\": \"baz\" } }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, LogicalWhenType, "/properties/foo/properties",
                     "#/properties/foo/properties", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict,
                     "/properties/foo/properties/bar/type",
                     "#/properties/foo/properties/bar/type", "/foo/bar");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/properties/foo/properties/bar/type",
      "#/properties/foo/properties/bar/type", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalWhenType, "/properties/foo/properties",
                              "#/properties/foo/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}

TEST(Evaluator_draft4, properties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"xxx\", \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesAllStrict, "/required", "#/required",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAllStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "image": {
        "required": [ "file" ],
        "properties": {
          "file": { "type": "string" }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"image\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, properties_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string", "pattern": "^a" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": \"abc\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  // Note we evaluate "bar" before "foo" because the number of instructions
  // in "bar" is less
  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(1, AssertionRegex, "/properties/foo/pattern",
                     "#/properties/foo/pattern", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionRegex, "/properties/foo/pattern",
                              "#/properties/foo/pattern", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value \"abc\" was expected to match "
                               "the regular expression \"^a\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "bar": { "type": "string", "pattern": "^a" },
      "foo": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 2, \"bar\": \"abc\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  // Note we evaluate "foo" before "bar" because the number of instructions
  // in "foo" is less
  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionRegex, "/properties/bar/pattern",
                     "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionRegex, "/properties/bar/pattern",
                              "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value \"abc\" was expected to match "
                               "the regular expression \"^a\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "properties": {
          "bar": {
            "type": "number"
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": { \"bar\": 1 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrictAny,
                     "/properties/foo/properties/bar/type",
                     "#/properties/foo/properties/bar/type", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionPropertyTypeStrictAny, "/properties/foo/properties/bar/type",
      "#/properties/foo/properties/bar/type", "/foo/bar");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, properties_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "number"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrictAny, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrictAny,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, properties_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "items": {
          "type": "number",
          "multipleOf": 3,
          "maximum": 100
        }
      },
      "bar": { "type": "string", "pattern": "^a" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": [3], \"bar\": \"abc\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 6, "");

  // We evaluate "bar" first because it has less number of steps, even though
  // if we don't count steps recursively, its the other way around
  EVALUATE_TRACE_PRE(0, AssertionRegex, "/properties/bar/pattern",
                     "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");

  EVALUATE_TRACE_PRE(2, LoopItems, "/properties/foo/items",
                     "#/properties/foo/items", "/foo");
  EVALUATE_TRACE_PRE(3, AssertionLessEqual, "/properties/foo/items/maximum",
                     "#/properties/foo/items/maximum", "/foo/0");
  EVALUATE_TRACE_PRE(4, AssertionDivisible, "/properties/foo/items/multipleOf",
                     "#/properties/foo/items/multipleOf", "/foo/0");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrictAny, "/properties/foo/items/type",
                     "#/properties/foo/items/type", "/foo/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionRegex, "/properties/bar/pattern",
                              "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionLessEqual,
                              "/properties/foo/items/maximum",
                              "#/properties/foo/items/maximum", "/foo/0");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionDivisible,
                              "/properties/foo/items/multipleOf",
                              "#/properties/foo/items/multipleOf", "/foo/0");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrictAny,
                              "/properties/foo/items/type",
                              "#/properties/foo/items/type", "/foo/0");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItems, "/properties/foo/items",
                              "#/properties/foo/items", "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"abc\" was expected to match "
                               "the regular expression \"^a\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The integer value 3 was expected to be less "
                               "than or equal to the integer 100");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The integer value 3 was expected to be divisible by the integer 3");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type number");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_draft4, properties_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "bar": { "type": "string" },
      "foo": { "type": "string", "enum": [ "baz" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": \"foo\", \"foo\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  // We evaluate "foo" first because it has an "enum"/"const"
  EVALUATE_TRACE_PRE(0, AssertionEqual, "/properties/foo/enum",
                     "#/properties/foo/enum", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/properties/foo/enum",
                              "#/properties/foo/enum", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"baz\" was expected to equal "
                               "the string constant \"baz\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "bar": { "$ref": "#/definitions/helper" },
      "foo": { "enum": [ "foo" ] }
    },
    "definitions": {
      "helper": {
        "enum": [ "test" ]
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": \"test\", \"foo\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  // We evaluate "foo" first because it has a direct "enum"/"const"
  EVALUATE_TRACE_PRE(0, AssertionEqual, "/properties/foo/enum",
                     "#/properties/foo/enum", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/properties/bar/$ref/enum",
                     "#/definitions/helper/enum", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/properties/foo/enum",
                              "#/properties/foo/enum", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionEqual, "/properties/bar/$ref/enum",
                              "#/definitions/helper/enum", "/bar");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value \"test\" was expected to "
                               "equal the string constant \"test\"");
}

TEST(Evaluator_draft4, properties_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": false,
    "properties": {
      "a": { "type": "string" },
      "b": { "type": "string" },
      "c": { "type": "string" },
      "d": { "type": "string" },
      "e": { "type": "string" },
      "f": { "type": "string" },
      "g": { "type": "string" },
      "h": { "type": "string" },
      "i": { "type": "string" },
      "j": { "type": "string" },
      "k": { "type": "string" },
      "l": { "type": "string" },
      "m": { "type": "string" },
      "n": { "type": "string" },
      "o": { "type": "string" },
      "p": { "type": "string" },
      "q": { "type": "string" },
      "r": { "type": "string" },
      "s": { "type": "string" },
      "t": { "type": "string" },
      "u": { "type": "string" },
      "v": { "type": "string" },
      "w": { "type": "string" },
      "x": { "type": "string" },
      "y": { "type": "string" },
      "z": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"f\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/f/type",
                     "#/properties/f/type", "/f");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/f/type", "#/properties/f/type",
                              "/f");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesMatchClosed, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "Every object value was expected to validate "
      "against one of the 26 defined properties subschemas");
}

TEST(Evaluator_draft4, properties_14_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": false,
    "properties": {
      "a": { "type": "string" },
      "b": { "type": "string" },
      "c": { "type": "string" },
      "d": { "type": "string" },
      "e": { "type": "string" },
      "f": { "type": "string" },
      "g": { "type": "string" },
      "h": { "type": "string" },
      "i": { "type": "string" },
      "j": { "type": "string" },
      "k": { "type": "string" },
      "l": { "type": "string" },
      "m": { "type": "string" },
      "n": { "type": "string" },
      "o": { "type": "string" },
      "p": { "type": "string" },
      "q": { "type": "string" },
      "r": { "type": "string" },
      "s": { "type": "string" },
      "t": { "type": "string" },
      "u": { "type": "string" },
      "v": { "type": "string" },
      "w": { "type": "string" },
      "x": { "type": "string" },
      "y": { "type": "string" },
      "z": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"f\": \"foo\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesMatch, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/f/type",
                     "#/properties/f/type", "/f");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/f/type",
                              "#/properties/f/type", "/f");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesMatch, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the 26 defined properties subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_draft4, properties_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": false,
    "properties": {
      "a": { "type": "string" },
      "b": { "type": "string" },
      "c": { "type": "string" },
      "d": { "type": "string" },
      "e": { "type": "string" },
      "f": { "type": "string" },
      "g": { "type": "string" },
      "h": { "type": "string" },
      "i": { "type": "string" },
      "j": { "type": "string" },
      "k": { "type": "string" },
      "l": { "type": "string" },
      "m": { "type": "string" },
      "n": { "type": "string" },
      "o": { "type": "string" },
      "p": { "type": "string" },
      "q": { "type": "string" },
      "r": { "type": "string" },
      "s": { "type": "string" },
      "t": { "type": "string" },
      "u": { "type": "string" },
      "v": { "type": "string" },
      "w": { "type": "string" },
      "x": { "type": "string" },
      "y": { "type": "string" },
      "z": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"f\": \"foo\", \"extra\": 2 }")};

  if (FIRST_PROPERTY_IS(instance, "f")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/f/type",
                       "#/properties/f/type", "/f");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                                "/properties/f/type", "#/properties/f/type",
                                "/f");
    EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The value was expected to be of type string");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "Every object value was expected to validate "
        "against one of the 26 defined properties subschemas");
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "Every object value was expected to validate "
        "against one of the 26 defined properties subschemas");
  }
}

// From https://github.com/sourcemeta/jsonschema/issues/432
TEST(Evaluator_draft4, properties_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "additionalProperties": false,
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": {},
      "bar": { "type": "object" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"baz"};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactlyStrict, "/required",
                     "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesExactlyStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "only defines properties \"bar\", and \"foo\"");
}

// From https://github.com/sourcemeta/jsonschema/issues/432
TEST(Evaluator_draft4, properties_16_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "additionalProperties": false,
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": {},
      "bar": { "type": "object" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"baz"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type object but it was of type string");
}

TEST(Evaluator_draft4, properties_17) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "additionalProperties": false,
    "required": [ "foo", "bar", "baz" ],
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "array" },
      "baz": { "type": "object" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"baz"};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactlyStrictHash3, "/required",
                     "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesExactlyStrictHash3,
                              "/required", "#/required", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "only defines the 3 given properties");
}

TEST(Evaluator_draft4, properties_18) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": "not-an-object"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, properties_19) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft4, properties_20) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft4, properties_21) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": [ "integer", "string" ] }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrictAny, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrictAny,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string and it was of type integer");
}

TEST(Evaluator_draft4, pattern_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^x"
  })JSON")};

  const sourcemeta::core::JSON instance{"xxx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionRegex, "/pattern", "#/pattern", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionRegex, "/pattern", "#/pattern", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"xxx\" was expected to match "
                               "the regular expression \"^x\"");
}

TEST(Evaluator_draft4, pattern_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^x"
  })JSON")};

  const sourcemeta::core::JSON instance{"aaa"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionRegex, "/pattern", "#/pattern", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionRegex, "/pattern", "#/pattern", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"aaa\" was expected to match "
                               "the regular expression \"^x\"");
}

TEST(Evaluator_draft4, pattern_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^x"
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, pattern_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, pattern_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, pattern_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "id": "https://nested.com",
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, pattern_7) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": 123
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, patternProperties_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {}
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, patternProperties_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^v": true
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, patternProperties_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": true
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, patternProperties_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_draft4, patternProperties_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_draft4, patternProperties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict,
                              "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_draft4, patternProperties_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "o$": { "type": "integer" },
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/patternProperties/o$/type",
                     "#/patternProperties/o$/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict,
                              "/patternProperties/o$/type",
                              "#/patternProperties/o$/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object properties that match the regular expression \"o$\" were "
      "expected to validate against the defined pattern property subschema");
}

TEST(Evaluator_draft4, patternProperties_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": {
        "patternProperties": {
          "^b": { "type": "integer" }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": { \"bar\": 2 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesStartsWith,
                     "/patternProperties/^f/patternProperties",
                     "#/patternProperties/%5Ef/patternProperties", "/foo");
  EVALUATE_TRACE_PRE(
      2, AssertionTypeStrict, "/patternProperties/^f/patternProperties/^b/type",
      "#/patternProperties/%5Ef/patternProperties/%5Eb/type", "/foo/bar");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/patternProperties/^f/patternProperties/^b/type",
      "#/patternProperties/%5Ef/patternProperties/%5Eb/type", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(
      1, LoopPropertiesStartsWith, "/patternProperties/^f/patternProperties",
      "#/patternProperties/%5Ef/patternProperties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"b\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_draft4, patternProperties_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^@": true },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"@foo\": 1, \"bar\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_draft4, patternProperties_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^[a-zA-Z0-9\\_\\.\\-]*$": { "type": "string" }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\_\\.\\-]*$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"patternProperties"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, patternProperties_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^/": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"/foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^~1/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5E~1/type", "/~1foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^~1/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5E~1/type", "/~1foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"/\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_draft4, patternProperties_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^[a-z]+$": { "type": "string" } },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^[a-z]+$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/patternProperties/^[a-z]+$/type",
      // Note that the caret needs to be URI escaped
      "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegexClosed,
                              "/patternProperties", "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties were expected to match the regular expression "
      "\"^[a-z]+$\" and validate against the defined pattern property "
      "subschema");
}

TEST(Evaluator_draft4, patternProperties_11_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^[a-z]+$": { "type": "string" } },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^[a-z]+$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/patternProperties/^[a-z]+$/type",
      // Note that the caret needs to be URI escaped
      "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^[a-z]+$\" "
      "were expected to validate against the defined pattern property "
      "subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_draft4, patternProperties_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^[a-z]+$": { "type": "string" } },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"bar\", \"@bar\": \"baz\" }")};

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                       "#/patternProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict,
                       "/patternProperties/^[a-z]+$/type",
                       // Note that the caret needs to be URI escaped
                       "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(
        0, AssertionTypeStrict, "/patternProperties/^[a-z]+$/type",
        // Note that the caret needs to be URI escaped
        "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");
    EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesRegexClosed,
                                "/patternProperties", "#/patternProperties",
                                "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The value was expected to be of type string");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object properties were expected to match the regular expression "
        "\"^[a-z]+$\" and validate against the defined pattern property "
        "subschema");
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                       "#/patternProperties", "");
    EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesRegexClosed,
                                "/patternProperties", "#/patternProperties",
                                "");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "The object properties were expected to match the regular expression "
        "\"^[a-z]+$\" and validate against the defined pattern property "
        "subschema");
  }
}

TEST(Evaluator_draft4, patternProperties_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^[a-z]+$": true },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesRegexClosed,
                              "/patternProperties", "#/patternProperties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object properties were expected to match the regular expression "
      "\"^[a-z]+$\" and validate against the defined pattern property "
      "subschema");
}

TEST(Evaluator_draft4, patternProperties_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^[a-z]+$": true },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"bar\", \"@bar\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesRegexClosed,
                              "/patternProperties", "#/patternProperties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object properties were expected to match the regular expression "
      "\"^[a-z]+$\" and validate against the defined pattern property "
      "subschema");
}

TEST(Evaluator_draft4, patternProperties_15) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": "not-an-object"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, additionalProperties_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                     "#/additionalProperties", "");

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
  } else {
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
  }

  EVALUATE_TRACE_POST_SUCCESS(2, LoopProperties, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_draft4, additionalProperties_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "boolean"
      }
    },
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema")
}

TEST(Evaluator_draft4, additionalProperties_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "baz": {
        "type": "integer"
      }
    },
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopPropertiesExcept, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept,
                                "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  } else {
    EVALUATE_TRACE_PRE(0, LoopPropertiesExcept, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept,
                                "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  }
}

TEST(Evaluator_draft4, additionalProperties_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");

  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_PRE(3, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/baz");

  // `patternProperties`
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^bar$/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  // `properties`
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  // `additionalProperties`
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/baz");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^bar$\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_draft4, additionalProperties_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");

  EVALUATE_TRACE_PRE(2, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_PRE(4, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/baz");

  // `patternProperties`
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^bar$/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  // `properties`
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalWhenType, "/properties", "#/properties",
                              "");

  // `additionalProperties`
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/baz");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^bar$\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_draft4, additionalProperties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "boolean"
      }
    },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": 2 }")};

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/foo/type",
                       "#/properties/foo/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                                "/properties/foo/type", "#/properties/foo/type",
                                "/foo");
    EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type boolean");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object value was expected to validate "
        "against the single defined property subschema")
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "The object value was expected to validate "
        "against the single defined property subschema")
  }
}

TEST(Evaluator_draft4, additionalProperties_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": {}
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  // Note we don't emit `additionalProperties` as it will do nothing anyway

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^bar$/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^bar$\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
}

TEST(Evaluator_draft4, additionalProperties_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  // Note we don't emit `additionalProperties` as it will do nothing anyway

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/patternProperties/^bar$/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^bar$\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
}

TEST(Evaluator_draft4, additionalProperties_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {}
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, additionalProperties_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, additionalProperties_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "number"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrictAny,
                     "/additionalProperties/type",
                     "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrictAny,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type number");
}

TEST(Evaluator_draft4, additionalProperties_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": false,
    "properties": {}
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeLess, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionObjectSizeLess,
                              "/additionalProperties", "#/additionalProperties",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_draft4, additionalProperties_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "boolean" },
      "bar": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": false }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesTypeStrict, "/properties", "#/properties",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesTypeStrict, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type boolean");
}

TEST(Evaluator_draft4, additionalProperties_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "boolean" },
      "bar": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "{ \"foo\": true, \"bar\": false, \"baz\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
}

TEST(Evaluator_draft4, additionalProperties_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "boolean" },
      "bar": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": false }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrictHash, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesExactlyTypeStrictHash,
                              "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type boolean");
}

TEST(Evaluator_draft4, additionalProperties_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "patternProperties": { "^@": true },
    "properties": {
      "foo": { "type": "boolean" },
      "bar": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": false }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesAll, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(3, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAll, "/required", "#/required",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_draft4, additionalProperties_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "boolean" },
        "bar": { "type": "boolean" }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ { \"foo\": true, \"bar\": false } ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsPropertiesExactlyTypeStrictHash,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type boolean");
}

TEST(Evaluator_draft4, additionalProperties_17) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "boolean" },
        "bar": { "type": "boolean" }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsPropertiesExactlyTypeStrictHash,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type boolean");
}

TEST(Evaluator_draft4, additionalProperties_18) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo" ],
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": { "^[@$_#]": {} },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": false, \"@bar\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesStrict, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesStrict, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines the property \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define additional properties");
}

TEST(Evaluator_draft4, additionalProperties_19) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "integer" },
        "bar": { "type": "integer" }
      }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  auto item{sourcemeta::core::JSON::make_object()};
  item.assign_assume_new("foo",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999")});
  item.assign_assume_new("bar",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999")});
  instance.push_back(std::move(item));

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsPropertiesExactlyTypeStrictHash,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type integer");
}

TEST(Evaluator_draft4, additionalProperties_20) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "integer" },
        "bar": { "type": "integer" }
      }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  auto item{sourcemeta::core::JSON::make_object()};
  item.assign_assume_new("foo",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  item.assign_assume_new("bar",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  instance.push_back(std::move(item));

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsPropertiesExactlyTypeStrictHash,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type integer");
}

TEST(Evaluator_draft4, additionalProperties_21) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar", "baz" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "integer" },
        "bar": { "type": "integer" },
        "baz": { "type": "integer" }
      }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  auto item{sourcemeta::core::JSON::make_object()};
  item.assign_assume_new("foo",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999")});
  item.assign_assume_new("bar",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999")});
  item.assign_assume_new("baz",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999")});
  instance.push_back(std::move(item));

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash3, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsPropertiesExactlyTypeStrictHash3,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type integer");
}

TEST(Evaluator_draft4, additionalProperties_22) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar", "baz" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "integer" },
        "bar": { "type": "integer" },
        "baz": { "type": "integer" }
      }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  auto item{sourcemeta::core::JSON::make_object()};
  item.assign_assume_new("foo",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  item.assign_assume_new("bar",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  item.assign_assume_new("baz",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  instance.push_back(std::move(item));

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash3, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsPropertiesExactlyTypeStrictHash3,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type integer");
}

TEST(Evaluator_draft4, additionalProperties_23) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesTypeStrict, "/properties", "#/properties",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesTypeStrict, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_24) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesTypeStrict, "/properties", "#/properties",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesTypeStrict, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_25) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": [ "integer", "string" ]
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrictAny,
                     "/additionalProperties/type",
                     "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrictAny,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object properties were expected to be of type integer, or string");
}

TEST(Evaluator_draft4, additionalProperties_26) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": [ "integer", "string" ]
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrictAny,
                     "/additionalProperties/type",
                     "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesTypeStrictAny,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object properties were expected to be of type integer, or string");
}

TEST(Evaluator_draft4, additionalProperties_27) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrictHash, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesExactlyTypeStrictHash,
                              "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_28) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrictHash, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesExactlyTypeStrictHash,
                              "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_29) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
      "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"
    ],
    "additionalProperties": false,
    "properties": {
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx": { "type": "integer" },
      "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});
  instance.assign_assume_new("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999")});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrict, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesExactlyTypeStrict, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_30) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
      "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"
    ],
    "additionalProperties": false,
    "properties": {
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx": { "type": "integer" },
      "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});
  instance.assign_assume_new("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrict, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesExactlyTypeStrict, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, not_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalNot, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/not/type", "#/not/type", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/not/type", "#/not/type",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalNot, "/not", "#/not", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to not validate "
                               "against the given subschema");
}

TEST(Evaluator_draft4, not_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalNot, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/not/type", "#/not/type", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/not/type", "#/not/type",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalNot, "/not", "#/not", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to not validate "
                               "against the given subschema");
}

TEST(Evaluator_draft4, not_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalNot, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/not/type", "#/not/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/not/type", "#/not/type",
                              "");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalNot, "/not", "#/not", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to not validate "
                               "against the given subschema, but it did");
}

TEST(Evaluator_draft4, not_2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalNot, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/not/type", "#/not/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/not/type", "#/not/type",
                              "");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalNot, "/not", "#/not", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to not validate "
                               "against the given subschema, but it did");
}

TEST(Evaluator_draft4, not_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "properties": {
        "foo": {
          "type": "boolean"
        }
      },
      "additionalProperties": {
        "type": "integer"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": false }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, LogicalNot, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/not/properties/foo/type",
                     "#/not/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/not/additionalProperties",
                     "#/not/additionalProperties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/not/additionalProperties/type",
                     "#/not/additionalProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/not/properties/foo/type",
                              "#/not/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict,
                              "/not/additionalProperties/type",
                              "#/not/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_FAILURE(2, LoopPropertiesExcept,
                              "/not/additionalProperties",
                              "#/not/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalNot, "/not", "#/not", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer "
                               "but it was of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to not validate "
                               "against the given subschema");
}

TEST(Evaluator_draft4, items_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, items_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type string");
}

TEST(Evaluator_draft4, items_2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_draft4, items_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", 5, \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type string");
}

TEST(Evaluator_draft4, items_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "string" } ]
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, items_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_draft4, items_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[ 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_draft4, items_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 5, true, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_draft4, items_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 5, 1, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_draft4, items_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "properties": {
          "bar": {
            "items": {
              "type": "string"
            }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": {}, \"bar\": [] }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, items_10) {
  // Adapted from GeoJSON
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "features": {
        "items": {
          "properties": {
            "geometry": {
              "type": "object",
              "required": [ "geometries" ],
              "properties": {
                "geometries": {
                  "items": {
                    "type": "string"
                  }
                }
              }
            }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "features": [
      { "geometry": null }
    ]
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopItems, "/properties/features/items",
                     "#/properties/features/items", "/features");
  EVALUATE_TRACE_PRE(1, AssertionDefinesStrict,
                     "/properties/features/items/properties/geometry/required",
                     "#/properties/features/items/properties/geometry/required",
                     "/features/0/geometry");

  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionDefinesStrict,
      "/properties/features/items/properties/geometry/required",
      "#/properties/features/items/properties/geometry/required",
      "/features/0/geometry");
  EVALUATE_TRACE_POST_FAILURE(1, LoopItems, "/properties/features/items",
                              "#/properties/features/items", "/features");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines the property \"geometries\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_draft4, items_11) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": "not-an-array"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, items_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "integer"
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type integer");
}

TEST(Evaluator_draft4, items_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "integer"
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type integer");
}

TEST(Evaluator_draft4, items_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": [ "integer", "string" ]
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrictAny, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrictAny, "/items", "#/items",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array items were expected to be of type integer, or string");
}

TEST(Evaluator_draft4, items_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": [ "integer", "string" ]
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrictAny, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsTypeStrictAny, "/items", "#/items",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array items were expected to be of type integer, or string");
}

TEST(Evaluator_draft4, additionalItems_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, additionalItems_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "integer" },
    "items": { "type": "string" }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type string");
}

TEST(Evaluator_draft4, additionalItems_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ true, 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_draft4, additionalItems_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 6, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, LoopItemsFrom, "/additionalItems", "#/additionalItems",
                     "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/3");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/3");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItemsFrom, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_draft4, additionalItems_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, LoopItemsFrom, "/additionalItems", "#/additionalItems",
                     "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/3");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/3");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItemsFrom, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_draft4, additionalItems_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ true, 5, 6, \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, LoopItemsFrom, "/additionalItems", "#/additionalItems",
                     "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItemsFrom, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_draft4, anyOf_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/anyOf", "#/anyOf",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number, "
                               "or string and it was of type number");
}

TEST(Evaluator_draft4, anyOf_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/anyOf", "#/anyOf",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number, "
                               "or string but it was of type boolean");
}

TEST(Evaluator_draft4, anyOf_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      {
        "properties": {
          "version": { "enum": [ 1 ] },
          "one": { "items": { "type": "integer" } },
          "two": { "items": { "type": "boolean" } },
          "three": { "items": { "type": "object" } },
          "four": { "items": { "type": "integer" } },
          "five": { "items": { "type": "boolean" } },
          "six": { "items": { "type": "object" } },
          "seven": { "items": { "type": "object" } },
          "eight": { "items": { "type": "object" } },
          "nine": { "items": { "type": "object" } },
          "then": { "items": { "type": "object" } }
        }
      },
      {
        "properties": {
          "version": { "enum": [ 2 ] },
          "one": { "type": "string" }
        }
      },
      {
        "properties": {
          "version": { "enum": [ 3 ] },
          "one": { "items": { "type": "integer" } },
          "two": { "items": { "type": "boolean" } },
          "three": { "items": { "type": "object" } }
        }
      }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"version\": 2, \"one\": \"two\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/anyOf/0/properties/version/enum",
                     "#/anyOf/0/properties/version/enum", "/version");
  EVALUATE_TRACE_PRE(2, AssertionEqual, "/anyOf/1/properties/version/enum",
                     "#/anyOf/1/properties/version/enum", "/version");
  EVALUATE_TRACE_PRE(3, AssertionPropertyTypeStrict,
                     "/anyOf/1/properties/one/type",
                     "#/anyOf/1/properties/one/type", "/one");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual,
                              "/anyOf/0/properties/version/enum",
                              "#/anyOf/0/properties/version/enum", "/version");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionEqual,
                              "/anyOf/1/properties/version/enum",
                              "#/anyOf/1/properties/version/enum", "/version");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/anyOf/1/properties/one/type",
                              "#/anyOf/1/properties/one/type", "/one");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalOr, "/anyOf", "#/anyOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value 2 was expected to equal the integer constant 2");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was expected to validate against at least one of the 3 "
      "given subschemas");
}

TEST(Evaluator_draft4, anyOf_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "$ref": "#/definitions/test" },
      true
    ],
    "definitions": {
      "test": {
        "properties": {
          "a": { "type": "string" },
          "b": { "type": "string", "pattern": "^b" },
          "c": { "type": "string", "pattern": "^c" },
          "d": { "type": "string", "pattern": "^d" },
          "e": { "type": "string", "pattern": "^e" },
          "f": { "type": "string", "pattern": "^f" },
          "g": { "type": "string", "pattern": "^g" },
          "h": { "type": "string", "pattern": "^h" },
          "i": { "type": "string", "pattern": "^i" },
          "j": { "type": "string", "pattern": "^j" },
          "k": { "type": "string", "pattern": "^k" }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"a\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesMatch, "/anyOf/0/$ref/properties",
                     "#/definitions/test/properties", "");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict,
                     "/anyOf/0/$ref/properties/a/type",
                     "#/definitions/test/properties/a/type", "/a");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/anyOf/0/$ref/properties/a/type",
                              "#/definitions/test/properties/a/type", "/a");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesMatch,
                              "/anyOf/0/$ref/properties",
                              "#/definitions/test/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalOr, "/anyOf", "#/anyOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the 11 defined properties subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was expected to validate against at least one of the 2 "
      "given subschemas");
}

TEST(Evaluator_draft4, oneOf_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, LogicalXor, "/oneOf", "#/oneOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/oneOf/0/type", "#/oneOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/oneOf/1/type", "#/oneOf/1/type",
                     "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrictAny, "/oneOf/2/type",
                     "#/oneOf/2/type", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/oneOf/3/type", "#/oneOf/3/type",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/oneOf/0/type",
                              "#/oneOf/0/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/oneOf/1/type",
                              "#/oneOf/1/type", "");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrictAny, "/oneOf/2/type",
                              "#/oneOf/2/type", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/oneOf/3/type",
                              "#/oneOf/3/type", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalXor, "/oneOf", "#/oneOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type integer but it was of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type number but it was of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The value was expected to be of type boolean but it was of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The string value was expected to validate against one and only one of "
      "the 4 given subschemas");
}

TEST(Evaluator_draft4, oneOf_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, LogicalXor, "/oneOf", "#/oneOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/oneOf/0/type", "#/oneOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/oneOf/1/type", "#/oneOf/1/type",
                     "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrictAny, "/oneOf/2/type",
                     "#/oneOf/2/type", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/oneOf/3/type", "#/oneOf/3/type",
                     "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/oneOf/0/type",
                              "#/oneOf/0/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/oneOf/1/type",
                              "#/oneOf/1/type", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrictAny, "/oneOf/2/type",
                              "#/oneOf/2/type", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/oneOf/3/type",
                              "#/oneOf/3/type", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalXor, "/oneOf", "#/oneOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type number");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type integer but it was of type number");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type number");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The value was expected to be of type boolean but it was of type number");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The number value was expected to validate against one and only one of "
      "the 4 given subschemas");
}

TEST(Evaluator_draft4, oneOf_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4, "");

  EVALUATE_TRACE_PRE(0, LogicalXor, "/oneOf", "#/oneOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/oneOf/0/type", "#/oneOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/oneOf/1/type", "#/oneOf/1/type",
                     "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrictAny, "/oneOf/2/type",
                     "#/oneOf/2/type", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/oneOf/0/type",
                              "#/oneOf/0/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/oneOf/1/type",
                              "#/oneOf/1/type", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrictAny, "/oneOf/2/type",
                              "#/oneOf/2/type", "");
  EVALUATE_TRACE_POST_FAILURE(3, LogicalXor, "/oneOf", "#/oneOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type number");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The integer value was expected to validate against one and only one of "
      "the 4 given subschemas");
}

TEST(Evaluator_draft4, oneOf_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "number" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalXor, "/oneOf", "#/oneOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrictAny, "/oneOf/0/type",
                     "#/oneOf/0/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/oneOf/0/type",
                              "#/oneOf/0/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalXor, "/oneOf", "#/oneOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The number value was expected to validate against the given subschema");
}

TEST(Evaluator_draft4, oneOf_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      {
        "properties": {
          "version": { "enum": [ 1 ] },
          "one": { "items": { "type": "integer" } },
          "two": { "items": { "type": "boolean" } },
          "three": { "items": { "type": "object" } },
          "four": { "items": { "type": "integer" } },
          "five": { "items": { "type": "boolean" } },
          "six": { "items": { "type": "object" } },
          "seven": { "items": { "type": "object" } },
          "eight": { "items": { "type": "object" } },
          "nine": { "items": { "type": "object" } },
          "then": { "items": { "type": "object" } }
        }
      },
      {
        "properties": {
          "version": { "enum": [ 2 ] },
          "one": { "type": "string" }
        }
      },
      {
        "properties": {
          "version": { "enum": [ 3 ] },
          "one": { "items": { "type": "integer" } },
          "two": { "items": { "type": "boolean" } },
          "three": { "items": { "type": "object" } }
        }
      }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"version\": 2, \"one\": \"two\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5, "");

  EVALUATE_TRACE_PRE(0, LogicalXor, "/oneOf", "#/oneOf", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/oneOf/0/properties/version/enum",
                     "#/oneOf/0/properties/version/enum", "/version");
  EVALUATE_TRACE_PRE(2, AssertionEqual, "/oneOf/1/properties/version/enum",
                     "#/oneOf/1/properties/version/enum", "/version");
  EVALUATE_TRACE_PRE(3, AssertionPropertyTypeStrict,
                     "/oneOf/1/properties/one/type",
                     "#/oneOf/1/properties/one/type", "/one");
  EVALUATE_TRACE_PRE(4, AssertionEqual, "/oneOf/2/properties/version/enum",
                     "#/oneOf/2/properties/version/enum", "/version");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual,
                              "/oneOf/0/properties/version/enum",
                              "#/oneOf/0/properties/version/enum", "/version");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionEqual,
                              "/oneOf/1/properties/version/enum",
                              "#/oneOf/1/properties/version/enum", "/version");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/oneOf/1/properties/one/type",
                              "#/oneOf/1/properties/one/type", "/one");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionEqual,
                              "/oneOf/2/properties/version/enum",
                              "#/oneOf/2/properties/version/enum", "/version");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalXor, "/oneOf", "#/oneOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value 2 was expected to equal the integer constant 2");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The integer value 2 was expected to equal the integer constant 3");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was expected to validate against one and only one of "
      "the 3 given subschemas");
}

TEST(Evaluator_draft4, oneOf_6) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": "not-an-array"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, oneOf_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalXor, "/oneOf", "#/oneOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/oneOf/0/type", "#/oneOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/oneOf/1/type", "#/oneOf/1/type",
                     "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/oneOf/0/type",
                              "#/oneOf/0/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/oneOf/1/type",
                              "#/oneOf/1/type", "");
  EVALUATE_TRACE_POST_FAILURE(2, LogicalXor, "/oneOf", "#/oneOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer "
                               "but it was of type boolean");
  // TODO: We should be able to say "... but it validated against none", but
  // the describe callback does not have such context
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The boolean value was expected to validate against one and only one of "
      "the 2 given subschemas");
}

TEST(Evaluator_draft4, dependencies_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, dependencies_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Because the object value defined the property \"foo\", it was also "
      "expected to define the properties \"bar\", and \"baz\"");
}

TEST(Evaluator_draft4, dependencies_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Because the object value defined the property \"foo\", it was also "
      "expected to define the property \"bar\"");
}

TEST(Evaluator_draft4, dependencies_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"qux\": 1, \"extra\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenDefines, "/dependencies", "#/dependencies",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionDefines, "/dependencies/qux/required",
                     "#/dependencies/qux/required", "");
  EVALUATE_TRACE_PRE(2, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefines, "/dependencies/qux/required",
                              "#/dependencies/qux/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalWhenDefines, "/dependencies",
                              "#/dependencies", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"extra\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value defined the property \"qux\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2, "The object value did not define the property \"foo\"");
}

TEST(Evaluator_draft4, dependencies_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"qux\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenDefines, "/dependencies", "#/dependencies",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionDefines, "/dependencies/qux/required",
                     "#/dependencies/qux/required", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefines, "/dependencies/qux/required",
                              "#/dependencies/qux/required", "");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalWhenDefines, "/dependencies",
                              "#/dependencies", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"extra\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value defined the property \"qux\"");
}

TEST(Evaluator_draft4, dependencies_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"none\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object value did not define the property \"foo\"");
}

TEST(Evaluator_draft4, dependencies_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ]
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"none\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object value did not define the property \"foo\"");
}

TEST(Evaluator_draft4, dependencies_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"qux\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenDefines, "/dependencies", "#/dependencies",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionDefines, "/dependencies/qux/required",
                     "#/dependencies/qux/required", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefines, "/dependencies/qux/required",
                              "#/dependencies/qux/required", "");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalWhenDefines, "/dependencies",
                              "#/dependencies", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"extra\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value defined the property \"qux\"");
}

TEST(Evaluator_draft4, dependencies_9) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": "not-an-object"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, enum_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, {}, "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqualsAny, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {} was expected to equal one of the 3 declared values");
}

TEST(Evaluator_draft4, enum_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, {}, "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqualsAny, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {\"foo\":1} was expected to equal one of the following "
      "values: 1, \"foo\", and {}");
}

TEST(Evaluator_draft4, enum_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1 ]
  })JSON")};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 1 was expected to equal the integer constant 1");
}

TEST(Evaluator_draft4, enum_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
}

TEST(Evaluator_draft4, enum_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, enum_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "boolean",
    "enum": [ true ]
  })JSON")};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The boolean value true was expected to equal the boolean constant true");
}

TEST(Evaluator_draft4, enum_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "enum": [ 3.14 ]
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.14 was expected to equal the number constant 3.14");
}

TEST(Evaluator_draft4, enum_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "enum": [ 3 ]
  })JSON")};

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft4, enum_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "enum": [ 3 ]
  })JSON")};

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft4, enum_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqualsAnyStringHash, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqualsAnyStringHash, "/enum",
                              "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "one of the given declared values");
}

TEST(Evaluator_draft4, enum_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "one of the 2 declared values");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, enum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "enum": [ [1] ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[1]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value [1] was expected to equal the array constant [1]");
}

TEST(Evaluator_draft4, enum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "enum": [ {} ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {} was expected to equal the object constant {}");
}

TEST(Evaluator_draft4, enum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "null",
    "enum": [ null ]
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The null value null was expected to equal the null constant null");
}

TEST(Evaluator_draft4, enum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1,
    "enum": [ "foo" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStringBounded, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStringBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to consist of a string of at least 1 character");
}

TEST(Evaluator_draft4, enum_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 1,
    "enum": [ [1] ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[1]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeArrayBounded, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value [1] was expected to equal the array constant [1]");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to consist of an array of at least 1 item");
}

TEST(Evaluator_draft4, enum_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1,
    "enum": [ { "foo": 1 } ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeObjectBounded, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeObjectBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value {\"foo\":1} was expected to "
                               "equal the object constant {\"foo\":1}");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to consist of an object of at least 1 property");
}

TEST(Evaluator_draft4, enum_17) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "enum": [ 3.0 ]
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the number constant 3.0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft4, enum_18) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const sourcemeta::core::JSON instance{"xxxx"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqualsAnyStringHash, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqualsAnyStringHash, "/enum",
                              "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"xxxx\" was expected to equal "
      "one of the given declared values");
}

TEST(Evaluator_draft4, enum_19) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "object",
        "required": [ "bar" ],
        "properties": {
          "bar": {
            "enum": [ "baz" ]
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesStrict, "/properties/foo/required",
                     "#/properties/foo/required", "/foo");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesStrict,
                              "/properties/foo/required",
                              "#/properties/foo/required", "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines the property \"bar\"");
}

TEST(Evaluator_draft4, enum_19_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "object",
        "required": [ "bar" ],
        "properties": {
          "bar": {
            "enum": [ "baz" ]
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionDefinesStrict, "/properties/foo/required",
                     "#/properties/foo/required", "/foo");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesStrict,
                              "/properties/foo/required",
                              "#/properties/foo/required", "/foo");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines the property \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}

TEST(Evaluator_draft4, enum_20) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "object",
        "required": [ "bar", "baz" ],
        "properties": {
          "bar": {
            "enum": [ "qux" ]
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesAllStrict, "/properties/foo/required",
                     "#/properties/foo/required", "/foo");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesAllStrict,
                              "/properties/foo/required",
                              "#/properties/foo/required", "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"baz\"");
}

TEST(Evaluator_draft4, enum_20_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "object",
        "required": [ "bar", "baz" ],
        "properties": {
          "bar": {
            "enum": [ "qux" ]
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionDefinesAllStrict, "/properties/foo/required",
                     "#/properties/foo/required", "/foo");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesAllStrict,
                              "/properties/foo/required",
                              "#/properties/foo/required", "/foo");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be an object that "
                               "defines properties \"bar\", and \"baz\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}

TEST(Evaluator_draft4, enum_21) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": "not-an-array"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, uniqueItems_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value was expected to not contain duplicate items");
}

TEST(Evaluator_draft4, uniqueItems_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, uniqueItems_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value was expected to not contain duplicate items");
}

TEST(Evaluator_draft4, uniqueItems_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 2, 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array value contained the following duplicate item: 2");
}

TEST(Evaluator_draft4, uniqueItems_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 2, 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, uniqueItems_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 2, 1, 2, 3, 2, 2, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array value contained the following duplicate item: 2");
}

TEST(Evaluator_draft4, uniqueItems_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 2, 1, 2, 3, 2, 2, 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value contained the following duplicate items: 1, and 2");
}

TEST(Evaluator_draft4, minLength_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minLength_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeGreater, "/minLength", "#/minLength",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater, "/minLength",
                              "#/minLength", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"xx\" was expected to consist of at least 2 "
      "characters and it consisted of 2 characters");
}

TEST(Evaluator_draft4, minLength_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"x"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeGreater, "/minLength", "#/minLength",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringSizeGreater, "/minLength",
                              "#/minLength", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"x\" was expected to consist of at least 2 characters "
      "but it consisted of 1 character");
}

TEST(Evaluator_draft4, minLength_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStringBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStringBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of at least 1 character");
}

TEST(Evaluator_draft4, minLength_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeGreater, "/minLength", "#/minLength",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater, "/minLength",
                              "#/minLength", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"xx\" was expected to consist of at least 1 character "
      "and it consisted of 2 characters");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, minLength_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, minLength_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 0
  })JSON")};

  const sourcemeta::core::JSON instance{"x"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minLength_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 0
  })JSON")};

  const sourcemeta::core::JSON instance{""};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minLength_8) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": "not-an-integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maxLength_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maxLength_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeLess, "/maxLength", "#/maxLength",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeLess, "/maxLength",
                              "#/maxLength", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"xx\" was expected to consist of at most 2 characters "
      "and it consisted of 2 characters");
}

TEST(Evaluator_draft4, maxLength_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xxx"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeLess, "/maxLength", "#/maxLength",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringSizeLess, "/maxLength",
                              "#/maxLength", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"xxx\" was expected to consist of at most 2 "
      "characters but it consisted of 3 characters");
}

TEST(Evaluator_draft4, maxLength_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStringUpper, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStringUpper, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of at most 2 characters");
}

TEST(Evaluator_draft4, maxLength_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeLess, "/maxLength", "#/maxLength",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeLess, "/maxLength",
                              "#/maxLength", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"xx\" was expected to consist of at most 2 characters "
      "and it consisted of 2 characters");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, maxLength_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xxx"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStringUpper, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStringUpper, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of at most 2 characters");
}

TEST(Evaluator_draft4, maxLength_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1,
    "maxLength": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStringBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStringBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of 1 to 2 characters");
}

TEST(Evaluator_draft4, maxLength_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 0
  })JSON")};

  const sourcemeta::core::JSON instance{"x"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeLess, "/maxLength", "#/maxLength",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringSizeLess, "/maxLength",
                              "#/maxLength", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"x\" was expected to consist of at most 0 characters "
      "but it consisted of 1 character");
}

TEST(Evaluator_draft4, maxLength_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 0
  })JSON")};

  const sourcemeta::core::JSON instance{""};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringSizeLess, "/maxLength", "#/maxLength",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeLess, "/maxLength",
                              "#/maxLength", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"\" was expected to consist of at most 0 characters "
      "and it consisted of 0 characters");
}

TEST(Evaluator_draft4, maxLength_9) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": "not-an-integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minItems_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minItems_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/minItems", "#/minItems",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeGreater, "/minItems",
                              "#/minItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 2 items and it contained 2 items");
}

TEST(Evaluator_draft4, minItems_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[ 1 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/minItems", "#/minItems",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionArraySizeGreater, "/minItems",
                              "#/minItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 2 items but it contained 1 item");
}

TEST(Evaluator_draft4, minItems_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, minItems_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of at least 2 items");
}

TEST(Evaluator_draft4, minItems_5_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/minItems", "#/minItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeGreater, "/minItems",
                              "#/minItems", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 2 items and it contained 3 items");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft4, minItems_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 0
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft4, minItems_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 0
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[ 1 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minItems_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 0
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minItems_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 0,
    "items": {
      "type": "number"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[1]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrictAny, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrictAny, "/items", "#/items",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type number");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft4, minItems_9_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 0,
    "items": {
      "type": "number"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[1]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrictAny, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft4, minItems_10) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": "not-an-integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maxItems_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maxItems_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 2 items and it contained 2 items");
}

TEST(Evaluator_draft4, maxItems_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 2 items but it contained 3 items");
}

TEST(Evaluator_draft4, maxItems_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, maxItems_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayUpper, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeArrayUpper, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of at most 2 items");
}

TEST(Evaluator_draft4, maxItems_5_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 2 items and it contained 2 items");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft4, maxItems_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayUpper, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeArrayUpper, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of at most 2 items");
}

TEST(Evaluator_draft4, maxItems_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 1,
    "maxItems": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of 1 to 2 items");
}

TEST(Evaluator_draft4, maxItems_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 0
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[ 1 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 0 items but it contained 1 item");
}

TEST(Evaluator_draft4, maxItems_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 0
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 0 items and it contained 0 items");
}

TEST(Evaluator_draft4, maxItems_10) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": "not-an-integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minProperties_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minProperties_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeGreater, "/minProperties",
                     "#/minProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionObjectSizeGreater, "/minProperties",
                              "#/minProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at least 2 properties and it "
      "contained 2 properties: \"bar\", and \"foo\"");
}

TEST(Evaluator_draft4, minProperties_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeGreater, "/minProperties",
                     "#/minProperties", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionObjectSizeGreater, "/minProperties",
                              "#/minProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at least 2 properties but it "
      "contained 1 property: \"foo\"");
}

TEST(Evaluator_draft4, minProperties_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeObjectBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of at least 1 property");
}

TEST(Evaluator_draft4, minProperties_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeGreater, "/minProperties",
                     "#/minProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionObjectSizeGreater, "/minProperties",
                              "#/minProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at least 1 property and it "
      "contained 1 property: \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, minProperties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 0
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, minProperties_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 0
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minProperties_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 0
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minProperties_8) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": "not-an-integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maxProperties_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maxProperties_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeLess, "/maxProperties",
                     "#/maxProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionObjectSizeLess, "/maxProperties",
                              "#/maxProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at most 2 properties and it "
      "contained 2 properties: \"bar\", and \"foo\"");
}

TEST(Evaluator_draft4, maxProperties_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"baz\": 3, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeLess, "/maxProperties",
                     "#/maxProperties", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionObjectSizeLess, "/maxProperties",
                              "#/maxProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at most 2 properties but it "
      "contained 3 properties: \"bar\", \"baz\", and \"foo\"");
}

TEST(Evaluator_draft4, maxProperties_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectUpper, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeObjectUpper, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of at most 2 properties");
}

TEST(Evaluator_draft4, maxProperties_4_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeLess, "/maxProperties",
                     "#/maxProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionObjectSizeLess, "/maxProperties",
                              "#/maxProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at most 2 properties and it "
      "contained 2 properties: \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, maxProperties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectUpper, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeObjectUpper, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of at most 2 properties");
}

TEST(Evaluator_draft4, maxProperties_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1,
    "maxProperties": 2
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeObjectBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of 1 to 2 properties");
}

TEST(Evaluator_draft4, maxProperties_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 0
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeLess, "/maxProperties",
                     "#/maxProperties", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionObjectSizeLess, "/maxProperties",
                              "#/maxProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at most 0 properties but it "
      "contained 1 property: \"foo\"");
}

TEST(Evaluator_draft4, maxProperties_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 0
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionObjectSizeLess, "/maxProperties",
                     "#/maxProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionObjectSizeLess, "/maxProperties",
                              "#/maxProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to contain at most 0 properties and it "
      "contained 0 properties");
}

TEST(Evaluator_draft4, maxProperties_9) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": "not-an-integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minimum_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minimum_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.1 was expected to be "
                               "greater than or equal to the integer 2");
}

TEST(Evaluator_draft4, minimum_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, minimum_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{1.8};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 1.8 was expected to be "
                               "greater than or equal to the integer 2");
}

TEST(Evaluator_draft4, minimum_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 0
  })JSON")};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 0");
}

TEST(Evaluator_draft4, minimum_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 0
  })JSON")};

  const sourcemeta::core::JSON instance{0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 0 was expected to be greater "
                               "than or equal to the integer 0");
}

TEST(Evaluator_draft4, minimum_7) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": "not-a-number"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maximum_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, maximum_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{1.9};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 1.9 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, maximum_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, maximum_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::core::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.1 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, maximum_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 0
  })JSON")};

  const sourcemeta::core::JSON instance{0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 0 was expected to be less "
                               "than or equal to the integer 0");
}

TEST(Evaluator_draft4, maximum_6) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": "not-a-number"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, minimum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_11) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_12) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, minimum_13) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be greater than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, minimum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, minimum_17) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.0"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be greater than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, minimum_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("minimum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"199999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 199999999999999999999999999999999998 was expected to "
      "be greater than or equal to the integer "
      "99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, minimum_19) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("minimum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 99999999999999999999999999999999998 was expected to "
      "be greater than or equal to the integer "
      "99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, minimum_20) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.7"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.7 was expected to be greater than or equal to the "
      "number 0.5");
}

TEST(Evaluator_draft4, minimum_21) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be greater than or equal to the "
      "number 0.5");
}

TEST(Evaluator_draft4, minimum_22) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5.0"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 10.0 was expected to be greater than or equal to the "
      "number 5.0");
}

TEST(Evaluator_draft4, minimum_23) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, minimum_24) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, maximum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_11) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, maximum_12) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be less than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, maximum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, maximum_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3.0"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be less than or equal to the "
      "number 2.5");
}

TEST(Evaluator_draft4, maximum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("maximum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 99999999999999999999999999999999998 was expected to "
      "be less than or equal to the integer "
      "99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, maximum_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("maximum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"199999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 199999999999999999999999999999999998 was expected to "
      "be less than or equal to the integer "
      "99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, maximum_19) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be less than or equal to the "
      "number 0.5");
}

TEST(Evaluator_draft4, maximum_20) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.7"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.7 was expected to be less than or equal to the "
      "number 0.5");
}

TEST(Evaluator_draft4, maximum_21) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5.0"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be less than or equal to the "
      "number 5.0");
}

TEST(Evaluator_draft4, maximum_22) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than or equal to the "
      "integer 5");
}

TEST(Evaluator_draft4, maximum_23) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5.5"}});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than or equal to the "
      "number 5.5");
}

TEST(Evaluator_draft4, exclusiveMinimum_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.1 was expected to be greater than the integer 2");
}

TEST(Evaluator_draft4, exclusiveMinimum_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than the integer 2, but they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2,
    "exclusiveMinimum": false
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, exclusiveMaximum_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{1.9};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 1.9 was expected to be less than the integer 2");
}

TEST(Evaluator_draft4, exclusiveMaximum_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than the integer 2, but they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2,
    "exclusiveMaximum": false
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, exclusiveMinimum_4) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(Evaluator_draft4, exclusiveMinimum_5) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_6) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(Evaluator_draft4, exclusiveMinimum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMinimum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{2.5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be greater than the number 2.5, "
      "but they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(Evaluator_draft4, exclusiveMinimum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMinimum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be greater than the number 2.5, "
      "but they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_14) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("minimum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"199999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 199999999999999999999999999999999998 was expected to "
      "be greater than the integer 99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, exclusiveMinimum_15) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("minimum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 99999999999999999999999999999999999 was expected to "
      "be greater than the integer 99999999999999999999999999999999999, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_16) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.7"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.7 was expected to be greater than the number 0.5");
}

TEST(Evaluator_draft4, exclusiveMinimum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "minimum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});
  schema.assign_assume_new("exclusiveMinimum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be greater than the number 0.5, "
      "but they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_4) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(Evaluator_draft4, exclusiveMaximum_5) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_6) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(Evaluator_draft4, exclusiveMaximum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMaximum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{2.5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be less than the number 2.5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 5,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(Evaluator_draft4, exclusiveMaximum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 5,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMaximum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be less than the number 2.5, but "
      "they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_14) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("maximum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 99999999999999999999999999999999998 was expected to "
      "be less than the integer 99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, exclusiveMaximum_15) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("maximum",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 99999999999999999999999999999999999 was expected to "
      "be less than the integer 99999999999999999999999999999999999, but they "
      "were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_16) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be less than the number 0.5");
}

TEST(Evaluator_draft4, exclusiveMaximum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "maximum", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});
  schema.assign_assume_new("exclusiveMaximum", sourcemeta::core::JSON{true});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be less than the number 0.5, but "
      "they were equal");
}

TEST(Evaluator_draft4, multipleOf_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, multipleOf_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::core::JSON instance{6};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 6 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::core::JSON instance{7};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 7 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3.2
  })JSON")};

  const sourcemeta::core::JSON instance{6.4};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.4 was expected to be divisible by the number 3.2");
}

TEST(Evaluator_draft4, multipleOf_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3.2
  })JSON")};

  const sourcemeta::core::JSON instance{6.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 3.2");
}

TEST(Evaluator_draft4, multipleOf_6) {
  // This is purposely invalid
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": "not-a-number"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("\"foo\"")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, multipleOf_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"3"}});

  const sourcemeta::core::JSON instance{9};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 9 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"3"}});

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"3"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"9"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 9 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"3"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_11) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{5.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 5.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_12) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{6.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"9"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 9 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 5.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"6.0"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("multipleOf",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"299999999999999999999999999999999997"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 299999999999999999999999999999999997 was expected to "
      "be divisible by the integer 99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, multipleOf_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new("multipleOf",
                           sourcemeta::core::JSON{sourcemeta::core::Decimal{
                               "99999999999999999999999999999999999"}});

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"299999999999999999999999999999999998"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 299999999999999999999999999999999998 was expected to "
      "be divisible by the integer 99999999999999999999999999999999999");
}

TEST(Evaluator_draft4, multipleOf_19) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.1"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be divisible by the number 0.1");
}

TEST(Evaluator_draft4, multipleOf_20) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.1"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.35"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.35 was expected to be divisible by the number 0.1");
}

TEST(Evaluator_draft4, multipleOf_21) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"5.0"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"15.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 15.0 was expected to be divisible by the number 5.0");
}

TEST(Evaluator_draft4, multipleOf_22) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"1.5"}});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be divisible by the number 1.5");
}

TEST(Evaluator_draft4, invalid_ref_top_level) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft4, invalid_ref_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "$ref": "#/definitions/i-dont-exist"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, invalid_ref_embedded) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "$ref": "#/definitions/bar"
    },
    "definitions": {
      "bar": {
        "id": "https://example.com/nested",
        "additionalProperties": {
          "$ref": "#/definitions/baz"
        }
      },
      "baz": {}
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer(
                  {"definitions", "bar", "additionalProperties", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, metadata) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "title": "My title",
    "description": "My description",
    "default": 1
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, unknown_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, unknown_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-test": 1
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, reference_from_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "$ref": "#/$defs/bar" },
      "baz": { "type": "string" }
    },
    "$defs": {
      "bar": {
        "$ref": "#/properties/baz"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(), "#/$defs/bar");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"$defs"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, reference_to_nested_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      {
        "$ref": "#/allOf/1/additionalProperties/x-this-is-invalid/$defs/test"
      },
      {
        "additionalProperties": {
          "x-this-is-invalid": {
            "$defs": {
              "test": {
                "type": "string"
              }
            }
          }
        }
      }
    ]
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(),
              "#/allOf/1/additionalProperties/x-this-is-invalid/$defs/test");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer(
                  {"allOf", 1, "additionalProperties", "x-this-is-invalid"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, format_uri_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{6};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_uri_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://www.example.com"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"https://www.example.com\" "
                               "was expected to represent a valid URI");
}

TEST(Evaluator_draft4, format_uri_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"!!!x::://"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"!!!x::://\" was expected to represent a valid URI");
}

TEST(Evaluator_draft4, ref_to_non_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "array": {
        "items": [
          { "type": "string" },
          { "type": "array" }
        ]
      }
    },
    "additionalProperties": {
      "$ref": "#/definitions/array/items"
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL() << "The compile function was expected to throw";
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(), "#/definitions/array/items");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"definitions", "array", "items"}));
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, relative_base_uri_with_ref) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema",
    "id": "common",
    "allOf": [ { "$ref": "#reference" } ],
    "definitions": {
      "reference": {
        "id": "#reference",
        "type": "string"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"test"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "common#/definitions/reference/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "common#/definitions/reference/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, top_level_ref_with_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft4, top_level_ref_with_id_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive),
      sourcemeta::core::SchemaError);
}
