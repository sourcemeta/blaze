#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_canonicalize_2020_12, duplicate_allof_branches_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, duplicate_allof_branches_3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, duplicate_allof_branches_4) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" },
      { "type": "number" },
      { "type": "number" },
      { "type": "string" },
      { "type": "string" },
      { "type": "string" },
      { "type": "number" },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, allof_false_simplify_preserves_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "type": "string",
    "allOf": [ false ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, allof_false_simplify_preserves_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "myanchor",
    "type": "string",
    "allOf": [ false ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "myanchor",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, allof_false_simplify_removes_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "allOf": [ false ],
    "$defs": {
      "foo": { "type": "number" }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, duplicate_allof_branches_5) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "multipleOf": 2,
    "allOf": [
      { "type": "number", "multipleOf": 1 }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "multipleOf": 2,
    "type": "number",
    "anyOf": [
      { "type": "number", "multipleOf": 1 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, dependent_required_tautology_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo" ],
    "dependentRequired": {
      "foo": [ "bar" ],
      "bar": [ "baz" ]
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "baz" ],
    "dependentRequired": {},
    "properties": {
      "foo": true,
      "bar": true,
      "baz": true
    },
    "minProperties": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_boolean_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_boolean_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_null_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_null_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, const_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_maximum_integer_to_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_maximum_integer_to_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1.2
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_maximum_integer_to_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_maximum_integer_to_maximum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "properties": {}, "minProperties": 0, "type": "object" },
      { "minItems": 0, "type": "array", "items": true },
      { "minLength": 0, "type": "string" },
      { "type": "number", "exclusiveMaximum": 1 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_minimum_integer_to_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_minimum_integer_to_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1.2
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_minimum_integer_to_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, exclusive_minimum_integer_to_minimum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "properties": {}, "minProperties": 0, "type": "object" },
      { "minItems": 0, "type": "array", "items": true },
      { "minLength": 0, "type": "string" },
      { "type": "number", "exclusiveMinimum": 1 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, boolean_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {
          "foo": true
        },
        "minProperties": 0
      },
      { "type": "array", "minItems": 0, "items": true },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_array_to_any_of_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo",
    "type": [ "integer", "number", "string" ],
    "minimum": 5
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo",
    "anyOf": [
      { "type": "integer", "minimum": 5, "multipleOf": 1 },
      { "type": "number", "minimum": 5 },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_array_to_any_of_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "integer", "number", "string" ],
    "anyOf": [
      { "minimum": 4, "type": "integer" },
      { "maximum": 8, "type": "integer" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "integer", "multipleOf": 1 },
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ],
    "allOf": [
      {
        "anyOf": [
          { "minimum": 4, "type": "integer", "multipleOf": 1 },
          { "maximum": 8, "type": "integer", "multipleOf": 1 }
        ]
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_array_to_any_of_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array", "string" ],
    "additionalProperties": {
      "$anchor": "foo",
      "type": "string"
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "type": "object",
        "properties": {},
        "minProperties": 0,
        "additionalProperties": {
          "$anchor": "foo",
          "type": "string",
          "minLength": 0
        }
      },
      {
        "type": "array",
        "minItems": 0,
        "items": true
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_array_to_any_of_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array" ],
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "string",
        "minLength": 0
      }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "type": "object",
        "properties": {},
        "minProperties": 0
      },
      {
        "type": "array",
        "minItems": 0,
        "items": true
      }
    ],
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "string",
        "minLength": 0
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, type_array_to_any_of_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "number" ],
    "anyOf": [
      { "minLength": 1 },
      { "minimum": 0 }
    ],
    "allOf": [
      { "title": "My schema" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ],
    "allOf": [
      {
        "anyOf": [
          {
            "anyOf": [
              { "enum": [ null ] },
              { "enum": [ false, true ] },
              { "type": "object", "minProperties": 0, "properties": {} },
              { "type": "array", "minItems": 0, "items": true },
              { "type": "string", "minLength": 1 },
              { "type": "number" }
            ]
          },
          {
            "anyOf": [
              { "enum": [ null ] },
              { "enum": [ false, true ] },
              { "type": "object", "minProperties": 0, "properties": {} },
              { "type": "array", "minItems": 0, "items": true },
              { "type": "string", "minLength": 0 },
              { "type": "number", "minimum": 0 }
            ]
          }
        ]
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, max_contains_covered_by_max_items_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2,
    "maxItems": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxContains": 1,
    "minItems": 0,
    "maxItems": 1,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, min_properties_covered_by_required_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, min_properties_implicit_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    },
    "minProperties": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, min_properties_implicit_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    },
    "minProperties": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, min_items_given_min_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "boolean" },
    "minContains": 3
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "enum": [ false, true ] },
    "minContains": 3,
    "minItems": 3,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, min_items_given_min_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minContains": 3
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     exclusive_maximum_integer_to_maximum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1.0e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 10.00000000000000e+399
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     exclusive_minimum_integer_to_minimum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1.0e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1.0e+400
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, circular_ref_through_defs_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$ref": "#/$defs/b" },
      "b": { "$ref": "#/$defs/a" }
    },
    "$ref": "#/$defs/a"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$ref": "#/$defs/b" },
      "b": { "$ref": "#/$defs/a" }
    },
    "$ref": "#/$defs/a"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, conflicting_type_and_const_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "const": 42
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ 42 ],
    "minLength": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, conflicting_type_and_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ 1, 2, 3 ],
    "minLength": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, allof_two_required_branches_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "required": [ "a" ] },
      { "required": [ "b" ] }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "b" ],
    "anyOf": [
      {
        "type": "object",
        "required": [ "a" ],
        "properties": {
          "a": true
        },
        "minProperties": 1
      }
    ],
    "minProperties": 1,
    "properties": {
      "b": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, allof_min_max_constraints_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "integer", "minimum": 0 },
      { "maximum": 100 }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100,
    "minimum": 0,
    "multipleOf": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, allof_two_properties_branches_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "properties": { "a": {} } },
      { "properties": { "b": {} } }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "anyOf": [
      {
        "type": "object",
        "properties": {
          "a": {
            "anyOf": [
              { "enum": [ null ] },
              { "enum": [ false, true ] },
              { "type": "object", "minProperties": 0, "properties": {} },
              { "type": "array", "minItems": 0, "items": true },
              { "type": "string", "minLength": 0 },
              { "type": "number" }
            ]
          }
        },
        "minProperties": 0
      }
    ],
    "allOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "properties": {
              "b": {
                "anyOf": [
                  { "enum": [ null ] },
                  { "enum": [ false, true ] },
                  { "type": "object", "minProperties": 0, "properties": {} },
                  { "type": "array", "minItems": 0, "items": true },
                  { "type": "string", "minLength": 0 },
                  { "type": "number" }
                ]
              }
            },
            "minProperties": 0
          },
          { "type": "array", "minItems": 0, "items": true },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    ],
    "minProperties": 0,
    "properties": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     type_union_implicit_with_content_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentMediaType": "application/json",
    "contentEncoding": "base64",
    "contentSchema": { "type": "object" }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "type": "object", "minProperties": 0, "properties": {} },
      { "type": "array", "minItems": 0, "items": true },
      {
        "type": "string",
        "contentSchema": {
          "type": "object",
          "minProperties": 0,
          "properties": {}
        },
        "contentEncoding": "base64",
        "contentMediaType": "application/json",
        "minLength": 0
      },
      { "type": "number" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     unsatisfiable_logic_branch_type_anyof_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "anyOf": [
      { "type": "number" },
      { "minLength": 1 }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "anyOf": [
      {
        "minLength": 1,
        "type": "string"
      }
    ],
    "minLength": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     unsatisfiable_logic_branch_type_oneof_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "oneOf": [
      { "type": "string" },
      { "minimum": 0 }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "oneOf": [
      false,
      {
        "minimum": 0,
        "type": "number"
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     unsatisfiable_logic_branch_type_if_then_else_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": { "type": "number" },
    "then": { "type": "array" },
    "else": { "type": "object" }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0,
    "if": false,
    "then": false,
    "else": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     allof_two_properties_branches_with_typed_values_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      {
        "properties": {
          "name": { "type": "string" }
        }
      },
      {
        "properties": {
          "age": { "type": "integer" }
        }
      }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "anyOf": [
      {
        "type": "object",
        "properties": {
          "name": { "type": "string", "minLength": 0 }
        },
        "minProperties": 0
      }
    ],
    "allOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "properties": {
              "age": { "type": "integer", "multipleOf": 1 }
            },
            "minProperties": 0
          },
          { "type": "array", "minItems": 0, "items": true },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    ],
    "minProperties": 0,
    "properties": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, items_implicit_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, items_implicit_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "items": { "type": "string", "minLength": 0 }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, object_anyof_untyped_branches_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "title": "Pet",
    "properties": {
      "kind": { "const": "cat" }
    },
    "anyOf": [
      { "properties": { "indoor":  { "type": "boolean" } } },
      { "properties": { "outdoor": { "type": "boolean" } } }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "title": "Pet",
    "properties": {
      "kind": {
        "enum": [ "cat" ]
      }
    },
    "anyOf": [
      {
        "type": "object",
        "properties": {
          "indoor": { "enum": [ false, true ] }
        },
        "minProperties": 0
      },
      {
        "type": "object",
        "properties": {
          "outdoor": { "enum": [ false, true ] }
        },
        "minProperties": 0
      }
    ],
    "minProperties": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     ref_into_subschema_broken_by_type_array_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "items": { "type": "string" }
      }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema/anyOf/3/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "properties": {}
          },
          {
            "type": "array",
            "items": {
              "type": "string",
              "minLength": 0
            },
            "minItems": 0
          },
          {
            "type": "string",
            "minLength": 0
          },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, ref_into_subschema_with_existing_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "type": [ "array", "string" ],
        "anyOf": [ { "minLength": 1 } ],
        "items": { "type": "integer" }
      }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema/anyOf/0/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "allOf": [
          {
            "anyOf": [
              {
                "anyOf": [
                  { "enum": [ null ] },
                  { "enum": [ false, true ] },
                  {
                    "type": "object",
                    "minProperties": 0,
                    "properties": {}
                  },
                  {
                    "type": "array",
                    "minItems": 0,
                    "items": true
                  },
                  {
                    "type": "string",
                    "minLength": 1
                  },
                  { "type": "number" }
                ]
              }
            ]
          }
        ],
        "anyOf": [
          {
            "type": "array",
            "minItems": 0,
            "items": {
              "type": "integer",
              "multipleOf": 1
            }
          },
          {
            "type": "string",
            "minLength": 0
          }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     ref_into_subschema_with_existing_allof_and_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "type": [ "array", "string" ],
        "allOf": [ { "maxLength": 100 } ],
        "anyOf": [ { "minLength": 1 } ],
        "items": { "type": "integer" }
      }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema/anyOf/0/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "allOf": [
          {
            "anyOf": [
              {
                "anyOf": [
                  { "enum": [ null ] },
                  { "enum": [ false, true ] },
                  {
                    "type": "object",
                    "minProperties": 0,
                    "properties": {}
                  },
                  {
                    "type": "array",
                    "minItems": 0,
                    "items": true
                  },
                  {
                    "type": "string",
                    "minLength": 1
                  },
                  { "type": "number" }
                ]
              }
            ]
          }
        ],
        "anyOf": [
          {
            "type": "array",
            "minItems": 0,
            "items": {
              "type": "integer",
              "multipleOf": 1
            }
          },
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "maxLength": 100
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     unevaluated_properties_with_root_and_allof_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "object" }
    },
    "allOf": [
      { "properties": { "bar": true } }
    ],
    "unevaluatedProperties": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {
          "foo": {
            "type": "object",
            "minProperties": 0,
            "properties": {}
          }
        }
      },
      {
        "type": "array",
        "minItems": 0,
        "items": true
      },
      {
        "type": "string",
        "minLength": 0
      },
      { "type": "number" }
    ],
    "properties": {
      "bar": true
    },
    "unevaluatedProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     ref_into_nested_subschema_within_resource) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/resource/properties/nested/items",
    "$defs": {
      "resource": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "properties": {
          "nested": {
            "type": [ "array", "string" ],
            "items": { "type": "integer" }
          }
        }
      }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/resource/anyOf/2/properties/nested/anyOf/0/items",
    "$defs": {
      "resource": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "properties": {
              "nested": {
                "anyOf": [
                  {
                    "type": "array",
                    "minItems": 0,
                    "items": {
                      "type": "integer",
                      "multipleOf": 1
                    }
                  },
                  {
                    "type": "string",
                    "minLength": 0
                  }
                ]
              }
            }
          },
          {
            "type": "array",
            "minItems": 0,
            "items": true
          },
          {
            "type": "string",
            "minLength": 0
          },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     items_implicit_skipped_with_direct_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "unevaluatedItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     items_implicit_skipped_with_anyof_items_and_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "properties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "items": {
              "enum": [ false, true ]
            }
          },
          {
            "type": "string",
            "minLength": 0
          },
          { "type": "number" }
        ]
      },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12,
     items_implicit_skipped_with_anyof_prefix_items_and_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "prefixItems": [ { "type": "boolean" } ] },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "properties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "prefixItems": [
              {
                "enum": [ false, true ]
              }
            ]
          },
          {
            "type": "string",
            "minLength": 0
          },
          { "type": "number" }
        ]
      },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2020_12, ref_into_subschema_via_absolute_uri) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.example.com#/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "items": { "type": "string" }
      }
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.example.com#/anyOf/3/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "properties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "items": {
              "type": "string",
              "minLength": 0
            }
          },
          {
            "type": "string",
            "minLength": 0
          },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
