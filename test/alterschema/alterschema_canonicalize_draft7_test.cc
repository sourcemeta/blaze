#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_canonicalize_draft7, duplicate_allof_branches_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, duplicate_allof_branches_3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, duplicate_allof_branches_4) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, type_boolean_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "boolean"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, type_boolean_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, type_null_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "null"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ null ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, type_null_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, const_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_maximum_integer_to_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_maximum_integer_to_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1.2
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_maximum_integer_to_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_maximum_integer_to_maximum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_canonicalize_draft7, exclusive_minimum_integer_to_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_minimum_integer_to_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 1.2
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_minimum_integer_to_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, exclusive_minimum_integer_to_minimum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_canonicalize_draft7,
     exclusive_maximum_integer_to_maximum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1.0e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 10.00000000000000e+399
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7,
     exclusive_maximum_integer_to_maximum_decimal_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 9.99999999999999999999999999999e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 100.0000000000000e+399
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7,
     exclusive_minimum_integer_to_minimum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 1.0e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1.0e+400
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7,
     exclusive_minimum_integer_to_minimum_decimal_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 9.99999999999999999999999999999e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1.0e+401
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_draft7, boolean_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": true
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_canonicalize_draft7, min_properties_covered_by_required_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_canonicalize_draft7, min_properties_implicit_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_canonicalize_draft7, min_properties_implicit_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_canonicalize_draft7, items_implicit_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}
