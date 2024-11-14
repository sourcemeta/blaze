#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft6, metaschema) {
  const auto metaschema{sourcemeta::jsontoolkit::official_resolver(
      "http://json-schema.org/draft-06/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 3);
}

TEST(Evaluator_draft6, unknown_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "foobar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, const_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 1 was expected to equal the integer constant 1");
}

TEST(Evaluator_draft6, const_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual, "/const", "#/const", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"foo\" was expected to equal the integer constant 1");
}

TEST(Evaluator_draft6, const_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "const": "foo"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
}

TEST(Evaluator_draft6, const_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "null",
    "const": null
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{nullptr};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The null value null was expected to equal the null constant null");
}

TEST(Evaluator_draft6, const_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "boolean",
    "const": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{true};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The boolean value true was expected to equal the boolean constant true");
}

TEST(Evaluator_draft6, const_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "number",
    "const": 3.14
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.14};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.14 was expected to equal the number constant 3.14");
}

TEST(Evaluator_draft6, const_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "const": 3
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft6, const_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "const": 3.0
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the number constant 3.0");
}

TEST(Evaluator_draft6, const_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "const": []
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value [] was expected to equal the array constant []");
}

TEST(Evaluator_draft6, const_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "const": {}
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {} was expected to equal the object constant {}");
}

TEST(Evaluator_draft6, const_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "minProperties": 1,
    "const": { "foo": 1 }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeObjectBounded, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeObjectBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value {\"foo\":1} was expected to "
                               "equal the object constant {\"foo\":1}");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to consist of an object of at least 1 property");
}

TEST(Evaluator_draft6, const_12) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "minItems": 1,
    "const": [ 1 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[1]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeArrayBounded, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeArrayBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value [1] was expected to equal the array constant [1]");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to consist of an array of at least 1 item");
}

TEST(Evaluator_draft6, const_13) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "minLength": 1,
    "const": "foo"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStringBounded, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/const", "#/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStringBounded, "/type", "#/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"foo\" was expected to equal "
                               "the string constant \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to consist of a string of at least 1 character");
}

TEST(Evaluator_draft6, exclusiveMinimum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2.1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.1 was expected to be greater than the integer 2");
}

TEST(Evaluator_draft6, exclusiveMinimum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be greater "
                               "than the integer 2, but they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{1.9};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 1.9 was expected to be less than the integer 2");
}

TEST(Evaluator_draft6, exclusiveMaximum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 2
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The integer value 2 was expected to be less "
                               "than the integer 2, but they were equal");
}

TEST(Evaluator_draft6, contains_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, contains_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"bar\", 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_draft6, contains_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_draft6, contains_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_draft6, contains_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "contains": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/contains", "#/contains",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeGreater, "/contains",
                              "#/contains", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 1 item and it contained 3 items");
}

TEST(Evaluator_draft6, propertyNames_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "propertyNames": { "minLength": 5 }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, propertyNames_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "propertyNames": { "minLength": 3 }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"foo\", and \"bar\" were expected to "
        "validate against the given subschema");
  } else {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"bar\", and \"foo\" were expected to "
        "validate against the given subschema");
  }
}

TEST(Evaluator_draft6, propertyNames_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "propertyNames": { "minLength": 3 }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"fo\": 1 }")};

  if (FIRST_PROPERTY_IS(instance, "fo")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2);

    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/fo");

    EVALUATE_TRACE_POST_FAILURE(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/fo");
    EVALUATE_TRACE_POST_FAILURE(1, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "The object property name \"fo\" was expected to consist of at least 3 "
        "characters but it consisted of 2 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object properties \"fo\", and \"bar\" were expected to validate "
        "against the given subschema");
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/fo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_FAILURE(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/fo");
    EVALUATE_TRACE_POST_FAILURE(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object property name \"fo\" was expected to consist of at least 3 "
        "characters but it consisted of 2 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"bar\", and \"fo\" were expected to validate "
        "against the given subschema");
  }
}

TEST(Evaluator_draft6, propertyNames_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {
        "propertyNames": {}
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "foo": {}
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, propertyNames_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": { "minLength": 3 }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");
    EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"foo\", and \"bar\" were expected to "
        "validate against the given subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                                 "The value was expected to be of type object");
  } else {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");
    EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");
    EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"bar\", and \"foo\" were expected to "
        "validate against the given subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                                 "The value was expected to be of type object");
  }
}

TEST(Evaluator_draft6, invalid_ref_top_level) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, invalid_ref_nested) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, invalid_ref_embedded) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com",
    "$schema": "http://json-schema.org/draft-06/schema#",
    "additionalProperties": {
      "$ref": "#/definitions/bar"
    },
    "definitions": {
      "bar": {
        "$id": "https://example.com/nested",
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

TEST(Evaluator_draft6, metadata) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "My title",
    "description": "My description",
    "default": 1,
    "examples": [ 1, 2, 3 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, unknown_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, unknown_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "x-test": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft6, reference_from_unknown_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, minLength_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxLength_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxLength_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxLength_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, minItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, minProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, maxProperties_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_8_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "enum": [ [1] ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[1]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array value [1] was expected to equal the array constant [1]");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type array");
}

TEST(Evaluator_draft6, enum_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_9_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "enum": [ {} ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{}")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value {} was expected to equal the object constant {}");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
}

TEST(Evaluator_draft6, enum_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_12) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_13) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(Evaluator_draft6, enum_14) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "enum": [ 3.0 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the number constant 3.0");
}
