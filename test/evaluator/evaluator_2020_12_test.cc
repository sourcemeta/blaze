#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_2020_12, unknown_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2020_12, unknown_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/fooBar", "#/fooBar", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/fooBar", "#/fooBar", "", "baz");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The unrecognized keyword \"fooBar\" was "
                               "collected as the annotation \"baz\"");
}

TEST(Evaluator_2020_12, unknown_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-test": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2020_12, unknown_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-test": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-test", "#/x-test", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-test", "#/x-test", "", 1);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The unrecognized keyword \"x-test\" was collected as the annotation 1");
}

TEST(Evaluator_2020_12, items_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2020_12, items_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

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

TEST(Evaluator_2020_12, items_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");
  EVALUATE_TRACE_PRE(4, LogicalWhenArraySizeGreater, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(5, LogicalWhenArraySizeGreater, "/items",
                              "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The array value contains 3 additional items "
                               "not described by related keywords");
}

TEST(Evaluator_2020_12, items_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", 5, \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2020_12, items_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" },
    "prefixItems": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, items_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" },
    "prefixItems": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/prefixItems", "#/prefixItems", "");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/prefixItems", "#/prefixItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/prefixItems", "#/prefixItems", "", 1);
  EVALUATE_TRACE_POST_ANNOTATION(3, "/prefixItems", "#/prefixItems", "", true);
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item of the array value validated "
                               "against the given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, items_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" },
    "prefixItems": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/3");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/3");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItems, "/items", "#/items", "");

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

TEST(Evaluator_2020_12, items_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" },
    "prefixItems": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 9);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/prefixItems", "#/prefixItems", "");
  EVALUATE_TRACE_PRE(4, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");
  EVALUATE_TRACE_PRE(6, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/3");
  EVALUATE_TRACE_PRE(7, LogicalWhenArraySizeGreater, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(8, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/prefixItems", "#/prefixItems", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(5, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/3");
  EVALUATE_TRACE_POST_SUCCESS(6, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(7, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(8, LogicalWhenArraySizeGreater, "/items",
                              "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 7, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 8,
                               "The array value contains 2 additional items "
                               "not described by related keywords");
}

TEST(Evaluator_2020_12, items_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" },
    "prefixItems": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, 6, \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItems, "/items", "#/items", "");

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

TEST(Evaluator_2020_12, items_6_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" },
    "prefixItems": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, 6, \"bar\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/prefixItems", "#/prefixItems", "");
  EVALUATE_TRACE_PRE(4, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/prefixItems", "#/prefixItems", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_2020_12, prefixItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2020_12, prefixItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, prefixItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, prefixItems_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/prefixItems", "#/prefixItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/prefixItems", "#/prefixItems", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, prefixItems_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, prefixItems_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true, \"extra\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/prefixItems", "#/prefixItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/prefixItems", "#/prefixItems", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, prefixItems_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, 1, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

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

TEST(Evaluator_2020_12, prefixItems_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, 1, \"extra\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

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

TEST(Evaluator_2020_12, prefixItems_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, prefixItems_6_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/prefixItems", "#/prefixItems",
                     "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/prefixItems/0/type",
                     "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/prefixItems/1/type",
                     "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/prefixItems", "#/prefixItems", "");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/prefixItems", "#/prefixItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/prefixItems/0/type",
                              "#/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/prefixItems/1/type",
                              "#/prefixItems/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/prefixItems", "#/prefixItems", "", 1);
  EVALUATE_TRACE_POST_ANNOTATION(3, "/prefixItems", "#/prefixItems", "", true);
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionArrayPrefix, "/prefixItems",
                              "#/prefixItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item of the array value validated "
                               "against the given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2020_12, contains_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2020_12, contains_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, contains_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"bar\", 3 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/contains", "#/contains", "", 1);
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The item at index 1 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2020_12, contains_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, contains_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 4);

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

TEST(Evaluator_2020_12, contains_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Evaluator_2020_12, contains_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 7);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");
  EVALUATE_TRACE_PRE_ANNOTATION(6, "/contains", "#/contains", "");

  // TODO: We should be emitting "true" by the end of this as all items matched

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/contains", "#/contains", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/contains", "#/contains", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_ANNOTATION(5, "/contains", "#/contains", "", 2);
  EVALUATE_TRACE_POST_SUCCESS(6, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The item at index 0 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The item at index 1 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The item at index 2 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2020_12, contains_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "maxContains": 1,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to contain exactly 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2020_12, contains_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "maxContains": 1,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/contains", "#/contains", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/contains", "#/contains", "", 1);
  EVALUATE_TRACE_POST_FAILURE(4, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The item at index 0 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The item at index 1 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was expected to contain exactly 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2020_12, reference_from_unknown_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.id(), "#/properties/baz");
    EXPECT_EQ(error.location(),
              sourcemeta::jsontoolkit::Pointer({"definitions", "bar", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_2020_12, dynamicRef_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#foo",
    "$defs": {
      "string": {
        "$dynamicAnchor": "foo",
        "type": "string"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "#/$defs/string", "");
  EVALUATE_TRACE_PRE(1, ControlDynamicAnchorJump, "/$dynamicRef",
                     "#/$dynamicRef", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/$dynamicRef/type",
                     "#/$defs/string/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "#/$defs/string", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/$dynamicRef/type",
                              "#/$defs/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(2, ControlDynamicAnchorJump, "/$dynamicRef",
                              "#/$dynamicRef", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for "
                               "future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The string value was expected to validate against the first subschema "
      "in scope that declared the dynamic anchor \"foo\"");
}

TEST(Evaluator_2020_12, definitions_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/middle",
    "definitions": {
      "middle": { "$ref": "#/definitions/string" },
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/$ref/type",
                     "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_2020_12, definitions_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/middle",
    "definitions": {
      "middle": { "$ref": "#/definitions/string" },
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/$ref", "#/$ref", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/$ref/$ref", "#/definitions/middle/$ref",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/$ref/$ref/type",
                     "#/definitions/string/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/$ref/$ref",
                              "#/definitions/middle/$ref", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/$ref", "#/$ref", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The string value was expected to validate "
                               "against the statically referenced schema");
}

TEST(Evaluator_2020_12, unevaluatedItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, ControlEvaluate, "/contains", "#/contains", "/0");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlEvaluate, "/contains", "#/contains",
                              "/0");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, unevaluatedItems_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(3, ControlEvaluate, "/contains", "#/contains", "/0");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/contains", "#/contains", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, ControlEvaluate, "/contains", "#/contains",
                              "/0");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The item at index 0 of the array value successfully validated against "
      "the containment check subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, unevaluatedItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false, 1 ]")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, LoopItems, "/anyOf/0/items", "#/anyOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(5, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/anyOf/0/items", "#/anyOf/0/items",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to validate against at least one of the 2 "
      "given subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, unevaluatedItems_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false, 1 ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, LoopItems, "/anyOf/0/items", "#/anyOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(5, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/anyOf/0/items", "#/anyOf/0/items",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to validate against at least one of the 2 "
      "given subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, unevaluatedItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "prefixItems": [ { "type": "boolean" } ] },
      true
    ],
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, AssertionArrayPrefix, "/anyOf/0/prefixItems",
                     "#/anyOf/0/prefixItems", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/prefixItems/0/type",
                     "#/anyOf/0/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(4, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict,
                              "/anyOf/0/prefixItems/0/type",
                              "#/anyOf/0/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionArrayPrefix, "/anyOf/0/prefixItems",
                              "#/anyOf/0/prefixItems", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to validate against at least one of the 2 "
      "given subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2020_12, unevaluatedItems_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "prefixItems": [ { "type": "boolean" } ] },
      true
    ],
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2 ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, AssertionArrayPrefix, "/anyOf/0/prefixItems",
                     "#/anyOf/0/prefixItems", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/prefixItems/0/type",
                     "#/anyOf/0/prefixItems/0/type", "/0");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(4, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict,
                              "/anyOf/0/prefixItems/0/type",
                              "#/anyOf/0/prefixItems/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionArrayPrefix, "/anyOf/0/prefixItems",
                              "#/anyOf/0/prefixItems", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to validate against at least one of the 2 "
      "given subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}
