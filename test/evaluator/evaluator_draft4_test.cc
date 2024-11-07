#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include "evaluator_utils.h"

#include <iostream>

TEST(Evaluator_draft4, metaschema_1) {
  const auto metaschema{sourcemeta::jsontoolkit::official_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 4);
}

TEST(Evaluator_draft4, metaschema_2) {
  const auto metaschema{sourcemeta::jsontoolkit::official_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "type": [ "string" ]
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 17);
}

TEST(Evaluator_draft4, unknown_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "foobar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, annotation_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "title": "foo"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, annotation_keyword_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "title": "foo"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, type_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, type_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string "
                               "but it was of type integer");
}

TEST(Evaluator_draft4, type_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, type_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, type_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"3.14"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type number but it was of type string");
}

TEST(Evaluator_draft4, type_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, type_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_draft4, type_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number", "object" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string, "
                               "number, or object and it was of type number");
}

TEST(Evaluator_draft4, type_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number", "object" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string, "
                               "number, or object but it was of type boolean");
}

TEST(Evaluator_draft4, required_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, required_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionDefines, "/required", "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefines, "/required", "#/required",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"foo\"");
}

TEST(Evaluator_draft4, required_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "baz" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionDefinesAll, "/required", "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDefinesAll, "/required", "#/required",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define properties \"foo\", and \"baz\" "
      "but did not define the property \"baz\"");
}

TEST(Evaluator_draft4, required_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);
  EVALUATE_TRACE_PRE(0, AssertionDefinesAll, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAll, "/required", "#/required",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to define "
                               "properties \"foo\", and \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, allOf_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "object" },
      { "required": [ "foo", "bar" ] }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
                               "properties \"foo\", and \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the 2 given subschemas");
}

TEST(Evaluator_draft4, allOf_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "object" },
      { "required": [ "foo", "bar" ] }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"baz\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/allOf/0/type", "#/allOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionDefinesAll, "/allOf/1/required",
                     "#/allOf/1/required", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/type",
                              "#/allOf/0/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionDefinesAll, "/allOf/1/required",
                              "#/allOf/1/required", "");
  EVALUATE_TRACE_POST_FAILURE(2, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was expected to define properties \"foo\", and \"bar\" "
      "but did not define the property \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the 2 given subschemas");
}

TEST(Evaluator_draft4, ref_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/definitions/string/type", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the given subschema");
}

TEST(Evaluator_draft4, ref_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/definitions/string/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value was expected to validate against the given subschema");
}

TEST(Evaluator_draft4, ref_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/allOf/0/$ref", "#/allOf/0/$ref", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "#/definitions/string/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/allOf/0/$ref", "#/allOf/0/$ref",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The string value was expected to validate against the given subschema");
}

TEST(Evaluator_draft4, ref_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "https://example.com"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": {} }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlLabel, "/properties/foo/$ref",
                     "https://example.com#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/$ref/type",
                     "https://example.com#/type", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type",
                     "https://example.com#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/properties/foo/$ref/type",
                              "https://example.com#/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlLabel, "/properties/foo/$ref",
                              "https://example.com#/properties/foo/$ref",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type",
                              "https://example.com#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, ref_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "https://example.com"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"foo\": {} } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, ControlLabel, "/properties/foo/$ref",
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
  EVALUATE_TRACE_POST_SUCCESS(3, ControlLabel, "/properties/foo/$ref",
                              "https://example.com#/properties/foo/$ref",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/type",
                              "https://example.com#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, ref_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "https://example.com"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"foo\": 1 } }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlLabel, "/properties/foo/$ref",
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
  EVALUATE_TRACE_POST_FAILURE(2, ControlLabel, "/properties/foo/$ref",
                              "https://example.com#/properties/foo/$ref",
                              "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type object but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the statically referenced schema");
}

TEST(Evaluator_draft4, ref_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "$ref": "#"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": {} }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlLabel, "/properties/foo/$ref",
                     "#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/$ref/type",
                     "#/type", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/properties/foo/$ref/type", "#/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlLabel, "/properties/foo/$ref",
                              "#/properties/foo/$ref", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, ref_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, LoopPropertiesMatch, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesMatch, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to validate "
                               "against the 6 defined properties subschemas");
}

TEST(Evaluator_draft4, ref_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/foo",
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

  const sourcemeta::jsontoolkit::JSON instance{true};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, ref_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": { "$ref": "#/definitions/one" },
    "definitions": {
      "one": { "$ref": "#/definitions/two" },
      "two": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties", "#/additionalProperties",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type boolean");
}

TEST(Evaluator_draft4, ref_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "$ref": "#/definitions/one" },
    "additionalProperties": { "$ref": "#/definitions/one" },
    "definitions": {
      "one": { "$ref": "#/definitions/two" },
      "two": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties", "#/additionalProperties",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type boolean");
}

TEST(Evaluator_draft4, ref_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   sourcemeta::jsontoolkit::official_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::jsontoolkit::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_12) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "https://example.com#/i-dont-exist"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::jsontoolkit::JSON> {
    if (identifier == "https://example.com") {
      return sourcemeta::jsontoolkit::parse(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::jsontoolkit::official_resolver(identifier);
  };

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   test_resolver, sourcemeta::blaze::default_schema_compiler),
               sourcemeta::jsontoolkit::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_13) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "https://example.com#i-dont-exist"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::jsontoolkit::JSON> {
    if (identifier == "https://example.com") {
      return sourcemeta::jsontoolkit::parse(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::jsontoolkit::official_resolver(identifier);
  };

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   test_resolver, sourcemeta::blaze::default_schema_compiler),
               sourcemeta::jsontoolkit::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_14) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": { "$ref": "#/definitions/bar" },
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{true};
  EXPECT_THROW(sourcemeta::blaze::evaluate(compiled_schema, instance),
               sourcemeta::blaze::EvaluationError);
}

TEST(Evaluator_draft4, properties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": \"xxx\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": \"xxx\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the defined properties subschemas");
}

TEST(Evaluator_draft4, properties_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"baz\": [] }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, properties_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": \"baz\" } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": \"baz\" } }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/properties/foo/properties",
                     "#/properties/foo/properties", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict,
                     "/properties/foo/properties/bar/type",
                     "#/properties/foo/properties/bar/type", "/foo/bar");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/properties/foo/properties/bar/type",
      "#/properties/foo/properties/bar/type", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/properties/foo/properties",
                              "#/properties/foo/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/properties", "#/properties", "");

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"xxx\", \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, AssertionDefinesAll, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesAll, "/required", "#/required",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to define "
                               "properties \"foo\", and \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, properties_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"image\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, properties_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string", "pattern": "^a" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": \"abc\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  // Note we evaluate "bar" before "foo" because the number of instructions
  // in "bar" is less
  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(1, AssertionRegex, "/properties/foo/pattern",
                     "#/properties/foo/pattern", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/bar/type", "#/properties/bar/type",
                              "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionRegex, "/properties/foo/pattern",
                              "#/properties/foo/pattern", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value \"abc\" was expected to match "
                               "the regular expression \"^a\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "bar": { "type": "string", "pattern": "^a" },
      "foo": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 2, \"bar\": \"abc\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  // Note we evaluate "foo" before "bar" because the number of instructions
  // in "foo" is less
  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionRegex, "/properties/bar/pattern",
                     "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionRegex, "/properties/bar/pattern",
                              "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value \"abc\" was expected to match "
                               "the regular expression \"^a\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, properties_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": 1 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "number"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrictAny, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrictAny,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, properties_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": [3], \"bar\": \"abc\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 6);

  // We evaluate "bar" first because it has less number of steps, even though
  // if we don't count steps recursively, its the other way around
  EVALUATE_TRACE_PRE(0, AssertionRegex, "/properties/bar/pattern",
                     "#/properties/bar/pattern", "/bar");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/bar/type",
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
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "bar": { "type": "string" },
      "foo": { "type": "string", "enum": [ "baz" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": \"foo\", \"foo\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"bar\": \"test\", \"foo\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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

TEST(Evaluator_draft4, pattern_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^x"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xxx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionRegex, "/pattern", "#/pattern", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionRegex, "/pattern", "#/pattern", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"xxx\" was expected to match "
                               "the regular expression \"^x\"");
}

TEST(Evaluator_draft4, pattern_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^x"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"aaa"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionRegex, "/pattern", "#/pattern", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionRegex, "/pattern", "#/pattern", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"aaa\" was expected to match "
                               "the regular expression \"^x\"");
}

TEST(Evaluator_draft4, pattern_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^x"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, pattern_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::jsontoolkit::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, pattern_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::jsontoolkit::Pointer(
                                    {"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, pattern_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "id": "https://nested.com",
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::jsontoolkit::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, patternProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {}
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, patternProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^v": true
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, patternProperties_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": true
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, patternProperties_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "o$": { "type": "integer" },
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^f": {
        "patternProperties": {
          "^b": { "type": "integer" }
        }
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": 2 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^@": true },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"@foo\": 1, \"bar\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^[a-zA-Z0-9\\_\\.\\-]*$": { "type": "string" }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "Invalid regular expression: ^[a-zA-Z0-9\\_\\.\\-]*$");
    EXPECT_EQ(error.location(),
              sourcemeta::jsontoolkit::Pointer({"patternProperties"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a schema error";
  }
}

TEST(Evaluator_draft4, patternProperties_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^/": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"/foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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

TEST(Evaluator_draft4, additionalProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties", "#/additionalProperties",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": true, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");

  EVALUATE_TRACE_PRE(2, LogicalAnd, "/properties", "#/properties", "");
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
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalAnd, "/properties", "#/properties", "");

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "boolean"
      }
    },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": true, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesWhitelist, "/additionalProperties",
                     "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesWhitelist,
                              "/additionalProperties", "#/additionalProperties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was not expected to define additional properties")
}

TEST(Evaluator_draft4, additionalProperties_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": {}
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {}
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, additionalProperties_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, additionalProperties_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "number"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrictAny, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrictAny,
                              "/additionalProperties", "#/additionalProperties",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object properties were expected to be of type number, or integer");
}

TEST(Evaluator_draft4, not_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": true, \"bar\": false }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, items_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type string");
}

TEST(Evaluator_draft4, items_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", 5, \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type string");
}

TEST(Evaluator_draft4, items_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "string" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, items_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_draft4, items_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, 1, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": {}, \"bar\": [] }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, items_10) {
  // Adapted from GeoJSON
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "features": [
      { "geometry": null }
    ]
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopItems, "/properties/features/items",
                     "#/properties/features/items", "/features");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict,
                     "/properties/features/items/properties/geometry/type",
                     "#/properties/features/items/properties/geometry/type",
                     "/features/0/geometry");

  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionTypeStrict,
      "/properties/features/items/properties/geometry/type",
      "#/properties/features/items/properties/geometry/type",
      "/features/0/geometry");
  EVALUATE_TRACE_POST_FAILURE(1, LoopItems, "/properties/features/items",
                              "#/properties/features/items", "/features");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type object but it was of type null");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_draft4, additionalItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, additionalItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "integer" },
    "items": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type string");
}

TEST(Evaluator_draft4, additionalItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/additionalItems", "#/additionalItems", "");
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
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItems, "/additionalItems",
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/additionalItems", "#/additionalItems", "");
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
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItems, "/additionalItems",
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, 6, \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItems, "/additionalItems",
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/anyOf/0/type", "#/anyOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/1/type", "#/anyOf/1/type",
                     "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/anyOf/0/type",
                              "#/anyOf/0/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/anyOf/1/type",
                              "#/anyOf/1/type", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalOr, "/anyOf", "#/anyOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The integer value was expected to validate against at least one of the "
      "3 given subschemas");
}

TEST(Evaluator_draft4, anyOf_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/anyOf/0/type", "#/anyOf/0/type",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/1/type", "#/anyOf/1/type",
                     "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrictAny, "/anyOf/2/type",
                     "#/anyOf/2/type", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/anyOf/0/type",
                              "#/anyOf/0/type", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/anyOf/1/type",
                              "#/anyOf/1/type", "");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrictAny, "/anyOf/2/type",
                              "#/anyOf/2/type", "");
  EVALUATE_TRACE_POST_FAILURE(3, LogicalOr, "/anyOf", "#/anyOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer "
                               "but it was of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type number but it was of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The boolean value was expected to validate against at least one of the "
      "3 given subschemas");
}

TEST(Evaluator_draft4, anyOf_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"version\": 2, \"one\": \"two\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"a\": \"foo\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesMatch, "/anyOf/0/$ref/properties",
                     "#/definitions/test/properties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/$ref/properties/a/type",
                     "#/definitions/test/properties/a/type", "/a");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

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
      "The value was expected to be an integer but it was a real number");
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "number" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"version\": 2, \"one\": \"two\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

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

TEST(Evaluator_draft4, dependencies_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, dependencies_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"qux\": 1, \"extra\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"qux\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"none\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object value did not define the property \"foo\"");
}

TEST(Evaluator_draft4, dependencies_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"none\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependencies",
                     "#/dependencies", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies, "/dependencies",
                              "#/dependencies", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object value did not define the property \"foo\"");
}

TEST(Evaluator_draft4, dependencies_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ],
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"qux\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

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

TEST(Evaluator_draft4, enum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, {}, "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqualsAny, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {} was expected to equal one of the 3 declared values");
}

TEST(Evaluator_draft4, enum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, {}, "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqualsAny, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {\"foo\":1} was expected to equal one of the following "
      "values: 1, {}, and \"foo\"");
}

TEST(Evaluator_draft4, enum_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 1 was expected to equal the integer constant 1");
}

TEST(Evaluator_draft4, enum_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
}

TEST(Evaluator_draft4, enum_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "boolean",
    "enum": [ true ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The boolean value true was expected to equal the boolean constant true");
}

TEST(Evaluator_draft4, enum_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "enum": [ 3.14 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.14 was expected to equal the number constant 3.14");
}

TEST(Evaluator_draft4, enum_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "enum": [ 3 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft4, enum_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "enum": [ 3 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft4, enum_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqualsAny, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqualsAny, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "one of the 3 declared values");
}

TEST(Evaluator_draft4, enum_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "enum": [ [1] ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[1]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value [1] was expected to equal the array constant [1]");
}

TEST(Evaluator_draft4, enum_12) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "enum": [ {} ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {} was expected to equal the object constant {}");
}

TEST(Evaluator_draft4, enum_13) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "null",
    "enum": [ null ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{nullptr};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The null value null was expected to equal the null constant null");
}

TEST(Evaluator_draft4, enum_14) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1,
    "enum": [ "foo" ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 1,
    "enum": [ [1] ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[1]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1,
    "enum": [ { "foo": 1 } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "enum": [ 3.0 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the number constant 3.0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be an integer but it was a real number");
}

TEST(Evaluator_draft4, uniqueItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value was expected to not contain duplicate items");
}

TEST(Evaluator_draft4, uniqueItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, uniqueItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value was expected to not contain duplicate items");
}

TEST(Evaluator_draft4, uniqueItems_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 2, 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array value contained the following duplicate item: 2");
}

TEST(Evaluator_draft4, uniqueItems_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 2, 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, uniqueItems_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 2, 1, 2, 3, 2, 2, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array value contained the following duplicate item: 2");
}

TEST(Evaluator_draft4, uniqueItems_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "uniqueItems": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 2, 1, 2, 3, 2, 2, 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionUnique, "/uniqueItems", "#/uniqueItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionUnique, "/uniqueItems",
                              "#/uniqueItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value contained the following duplicate items: 1, and 2");
}

TEST(Evaluator_draft4, minLength_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, minLength_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"x"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStringBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStringBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of at least 1 character");
}

TEST(Evaluator_draft4, minLength_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, maxLength_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, maxLength_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xxx"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStringBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStringBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of at most 2 characters");
}

TEST(Evaluator_draft4, maxLength_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xxx"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStringBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStringBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of at most 2 characters");
}

TEST(Evaluator_draft4, maxLength_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1,
    "maxLength": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"xx"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStringBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStringBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of a string of 1 to 2 characters");
}

TEST(Evaluator_draft4, minItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, minItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/minItems", "#/minItems",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeGreater, "/minItems",
                              "#/minItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 2 items and it contained 2 items");
}

TEST(Evaluator_draft4, minItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/minItems", "#/minItems",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionArraySizeGreater, "/minItems",
                              "#/minItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 2 items but it contained 1 item");
}

TEST(Evaluator_draft4, minItems_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, minItems_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of at least 2 items");
}

TEST(Evaluator_draft4, minItems_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 0
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft4, maxItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, maxItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 2 items and it contained 2 items");
}

TEST(Evaluator_draft4, maxItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArraySizeLess, "/maxItems", "#/maxItems", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionArraySizeLess, "/maxItems",
                              "#/maxItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "most 2 items but it contained 3 items");
}

TEST(Evaluator_draft4, maxItems_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, maxItems_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of at most 2 items");
}

TEST(Evaluator_draft4, maxItems_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of at most 2 items");
}

TEST(Evaluator_draft4, maxItems_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 1,
    "maxItems": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeArrayBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an array of 1 to 2 items");
}

TEST(Evaluator_draft4, minProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, minProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeObjectBounded, "/type", "#/type",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of at least 1 property");
}

TEST(Evaluator_draft4, minProperties_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 0
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft4, maxProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, maxProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"baz\": 3, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeObjectBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of at most 2 properties");
}

TEST(Evaluator_draft4, maxProperties_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

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
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeObjectBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of at most 2 properties");
}

TEST(Evaluator_draft4, maxProperties_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1,
    "maxProperties": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeObjectBounded, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeObjectBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to consist of an object of 1 to 2 properties");
}

TEST(Evaluator_draft4, minimum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, minimum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.1 was expected to be "
                               "greater than or equal to the integer 2");
}

TEST(Evaluator_draft4, minimum_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, minimum_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1.8};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 1.8 was expected to be "
                               "greater than or equal to the integer 2");
}

TEST(Evaluator_draft4, maximum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, maximum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1.9};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 1.9 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, maximum_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, maximum_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.1 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, exclusiveMinimum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.1 was expected to be greater than the integer 2");
}

TEST(Evaluator_draft4, exclusiveMinimum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than the integer 2, but they were equal");
}

TEST(Evaluator_draft4, exclusiveMinimum_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2,
    "exclusiveMinimum": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, exclusiveMaximum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1.9};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 1.9 was expected to be less than the integer 2");
}

TEST(Evaluator_draft4, exclusiveMaximum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than the integer 2, but they were equal");
}

TEST(Evaluator_draft4, exclusiveMaximum_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2,
    "exclusiveMaximum": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than or equal to the integer 2");
}

TEST(Evaluator_draft4, multipleOf_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, multipleOf_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{6};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 6 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{7};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 7 was expected to be divisible by the integer 3");
}

TEST(Evaluator_draft4, multipleOf_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3.2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{6.4};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.4 was expected to be divisible by the number 3.2");
}

TEST(Evaluator_draft4, multipleOf_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3.2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{6.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 3.2");
}

TEST(Evaluator_draft4, invalid_ref_top_level) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(), sourcemeta::jsontoolkit::Pointer({"$ref"}));
    SUCCEED();
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, invalid_ref_nested) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "$ref": "#/definitions/i-dont-exist"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::jsontoolkit::Pointer({"properties", "foo", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, invalid_ref_embedded) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::jsontoolkit::Pointer(
                  {"definitions", "bar", "additionalProperties", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, metadata) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "title": "My title",
    "description": "My description",
    "default": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, unknown_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, unknown_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-test": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, reference_from_unknown_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.id(), "#/properties/baz");
    EXPECT_EQ(error.location(),
              sourcemeta::jsontoolkit::Pointer({"$defs", "bar", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, format_uri_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{6};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft4, format_uri_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"https://www.example.com"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"https://www.example.com\" "
                               "was expected to represent a valid URI");
}

TEST(Evaluator_draft4, format_uri_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"!!!x::://"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"!!!x::://\" was expected to represent a valid URI");
}

TEST(Evaluator_draft4, ref_to_non_schema) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL() << "The compile function was expected to throw";
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.id(), "#/definitions/array/items");
    EXPECT_EQ(sourcemeta::jsontoolkit::to_string(error.location()),
              "/additionalProperties/$ref");
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, relative_base_uri_with_ref) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{"test"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "common#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/allOf/0/$ref/type",
                     "common#/definitions/reference/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/$ref/type",
                              "common#/definitions/reference/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/allOf", "common#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value was expected to validate against the given subschema");
}
