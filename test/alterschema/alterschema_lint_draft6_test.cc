#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_lint_draft6, enum_to_const_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "string", "null" ],
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "boolean", "null" ],
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "boolean", "null" ],
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, enum_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, enum_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, enum_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, enum_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "foo", "bar" ],
    "minimum": 0
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, 2, 3 ],
    "minLength": 0,
    "maxLength": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ { "a": 1 }, { "b": 2 } ],
    "minLength": 3,
    "minimum": 0
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ { "a": 1 }, { "b": 2 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ { "name": "alice" }, { "age": 25 } ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" }
    },
    "minLength": 5,
    "minimum": 10
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ { "name": "alice" }, { "age": 25 } ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3,
    "minItems": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 42, "hello", true, null, { "key": "value" }, [1, 2, 3] ],
    "minimum": 10,
    "minLength": 2,
    "minItems": 1,
    "minProperties": 1,
    "maxLength": 100,
    "maxItems": 10,
    "maxProperties": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 42, "hello", true, null, { "key": "value" }, [1, 2, 3] ],
    "minimum": 10,
    "minLength": 2,
    "minItems": 1,
    "minProperties": 1,
    "maxLength": 100,
    "maxItems": 10,
    "maxProperties": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_enum_validation_keywords_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/schema",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "enum": [ "red", "green", "blue" ],
    "minimum": 5,
    "minLength": 10,
    "minItems": 2,
    "minProperties": 1,
    "maxProperties": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/schema",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "enum": [ "red", "green", "blue" ],
    "minLength": 10
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, single_type_array_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "string" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, items_schema_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, items_schema_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, items_schema_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, items_array_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, duplicate_enum_values_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, {}, 2, 1, 1, 3, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ 1, {}, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, duplicate_required_values_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar", "baz", "foo" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_maximum_number_and_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_maximum_number_and_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 3,
    "maximum": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "maximum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_maximum_number_and_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 3,
    "maximum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "maximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_minimum_number_and_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 3,
    "minimum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_minimum_number_and_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 3,
    "minimum": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_minimum_number_and_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 3,
    "minimum": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, duplicate_allof_branches_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [ { "type": "string" }, { "type": "integer" }, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, duplicate_anyof_branches_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ { "type": "string" }, { "type": "integer" }, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, anyof_true_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ true, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, anyof_true_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ { "type": "string" }, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, anyof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, anyof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, oneof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "oneOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, oneof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "oneOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "oneOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, oneof_to_anyof_disjoint_types_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, oneof_to_anyof_disjoint_types_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, maximum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "maximum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "maximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, minimum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "minimum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, dependent_required_tautology_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo" ],
    "dependencies": {
      "foo": [ "bar" ],
      "xxx": { "type": "string" },
      "yyy": [ "extra" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "dependencies": {
      "xxx": { "type": "string" },
      "yyy": [ "extra" ]
    },
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, dependent_required_tautology_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo" ],
    "dependencies": {
      "foo": [ "bar" ],
      "bar": [ "baz" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar", "baz" ],
    "properties": {
      "foo": true,
      "bar": true,
      "baz": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, pattern_properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "patternProperties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unsatisfiable_min_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unsatisfiable_min_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "bar", "baz", "foo" ],
    "minProperties": 4,
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unsatisfiable_min_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_array_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "array",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "array",
    "minItems": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_boolean_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "boolean",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_null_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "null",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_numeric_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "number",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "number"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_numeric_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "integer",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_object_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "object",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "object",
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, drop_non_string_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "string",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "type": "string",
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, type_boolean_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "boolean"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, type_null_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "null"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_maximum_integer_to_maximum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, exclusive_minimum_integer_to_minimum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, equal_numeric_bounds_to_const_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, equal_numeric_bounds_to_const_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");
  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, equal_numeric_bounds_to_const_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "minimum": 1.0e400,
    "maximum": 1.0e400
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 1.0e+400
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unnecessary_allof_wrapper_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unnecessary_allof_wrapper_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unnecessary_allof_wrapper_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, multiple_of_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, multiple_of_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "multipleOf": 1.0,
    "maximum": 100
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "maximum": 100
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unnecessary_allof_wrapper_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "$ref": "https://example.com",
        "properties": {
          "bar": { "pattern": "^f" }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "$ref": "https://example.com"
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unnecessary_allof_ref_wrapper_draft_elevation) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "additionalProperties": {
      "allOf": [
        { "$ref": "https://example.com" }
      ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "additionalProperties": {
      "$ref": "https://example.com"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_ref_wrapper_draft_no_elevation_with_schema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_ref_wrapper_draft_no_elevation_with_sibling_keyword) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_ref_wrapper_draft_no_elevation_ref_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      {
        "$ref": "https://example.com",
        "$id": "https://other.com"
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      {
        "$ref": "https://example.com"
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_ref_wrapper_draft_no_elevation_multiple_branches) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_official_dialect_without_empty_fragment_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, additional_items_with_schema_items_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "type": "number"
    },
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "type": "number"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, additional_items_with_schema_items_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "const": "foo"
    },
    "additionalItems": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "const": "foo"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     additional_items_with_schema_items_boolean_items_true) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": true,
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     additional_items_with_schema_items_boolean_items_false) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": false,
    "additionalItems": {
      "type": "string"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, additional_items_with_schema_items_array_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": [
      { "type": "string" },
      { "type": "number" }
    ],
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": [
      { "type": "string" },
      { "type": "number" }
    ],
    "additionalItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, property_names_type_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": {
      "type": "string",
      "pattern": "^S_"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": {
      "pattern": "^S_"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, property_names_type_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": {
      "type": [ "string" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, property_names_type_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": {
      "type": "integer"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": {
      "type": "integer"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, property_names_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_ref_siblings_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_ref_siblings_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo",
    "type": "string",
    "minLength": 5,
    "description": "A string field"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "description": "A string field"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_ref_siblings_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "http://example.com/schema",
    "$ref": "#/definitions/foo",
    "type": "string",
    "minLength": 5,
    "description": "Documentation"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "description": "Documentation"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_ref_siblings_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo",
    "description": "Documentation only"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "description": "Documentation only"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_ref_siblings_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, draft_ref_siblings_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "nested": {
        "$ref": "#/definitions/bar",
        "type": "object",
        "description": "Nested schema with $ref"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "nested": {
        "description": "Nested schema with $ref"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_type_specific_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ true, false ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ true, false ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_type_specific_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": null,
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": null
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, non_applicable_type_specific_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": "foo",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": "foo",
    "maxLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, not_false_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, not_false_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "minimum": 5,
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "minimum": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, not_false_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, not_false_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "not": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, not_false_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "not": {
      "type": "number"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "not": {
      "type": "number"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": {},
      "bar": false,
      "baz": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": false,
      "baz": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_16) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, required_properties_in_properties_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "fooBar": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "x-fooBar": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "baz": 123
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "x-baz": 123
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "needsPrefix": "value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "x-needsPrefix": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "customKeyword": "value",
    "anotherOne": 123,
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "x-customKeyword": "value",
    "x-anotherOne": 123,
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "custom": "value",
    "x-custom": "conflicting value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "x-custom": "conflicting value",
    "x-x-custom": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "nested": {
        "type": "string",
        "custom": "value",
        "x-custom": "conflicting value"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "nested": {
        "type": "string",
        "x-custom": "conflicting value",
        "x-x-custom": "value"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "definitions": {
      "foo": {
        "type": "string",
        "custom": "value",
        "x-custom": "conflicting value"
      }
    },
    "properties": {
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "definitions": {
      "foo": {
        "type": "string",
        "x-custom": "conflicting value",
        "x-x-custom": "value"
      }
    },
    "properties": {
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unknown_keywords_prefix_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo",
    "custom": "value",
    "x-custom": "conflicting value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, top_level_ref_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://sourcemeta.com",
    "$ref": "https://example.com"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, additional_items_with_no_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, top_level_examples_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "My schema",
    "description": "A description",
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);
}

TEST(AlterSchema_lint_draft6, top_level_examples_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "My schema",
    "description": "A description",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_draft6, duplicate_examples_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ "foo", "bar", "foo" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, duplicate_examples_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ "foo", "bar", "baz" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ "foo", "bar", "baz" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, orphan_definitions_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, orphan_definitions_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, orphan_definitions_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    },
    "properties": {
      "baz": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "baz": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_wrapper_inner_additional_properties_outer_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "additionalProperties": false }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "additionalProperties": false }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_wrapper_inner_properties_and_additional_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      {
        "properties": { "foo": { "type": "string" } },
        "additionalProperties": false
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": { "foo": { "type": "string" } },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, unnecessary_allof_wrapper_with_id_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$id": "nested", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$id": "nested", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6,
     unnecessary_allof_wrapper_with_id_anchor_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$id": "#foo", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [
      { "$id": "#foo", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, simple_properties_identifiers_skip_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "http://json-schema.org/draft-06/schema#",
    "title": "My Meta-Schema",
    "description": "A meta-schema for testing",
    "examples": [ {} ],
    "properties": {
      "foo-bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_draft6,
     simple_properties_identifiers_skip_metaschema_nested) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "http://json-schema.org/draft-06/schema#",
    "title": "My Meta-Schema",
    "description": "A meta-schema for testing",
    "examples": [ {} ],
    "properties": {
      "valid": {
        "properties": {
          "also-invalid": { "type": "number" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_draft6, simple_properties_identifiers_applies_non_meta) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/my-schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo-bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "simple_properties_identifiers",
                    "Set `properties` to identifier names that can be easily "
                    "mapped to programming languages (matching "
                    "[A-Za-z_][A-Za-z0-9_]*)",
                    false);
}

TEST(AlterSchema_lint_draft6,
     simple_properties_identifiers_skip_bundled_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/main",
    "title": "Main schema",
    "description": "A schema that bundles a meta-schema",
    "examples": [ {} ],
    "allOf": [
      { "$ref": "#/definitions/metaschema" }
    ],
    "definitions": {
      "metaschema": {
        "$schema": "http://json-schema.org/draft-06/schema#",
        "$id": "http://json-schema.org/draft-06/schema#",
        "title": "Bundled Meta-Schema",
        "description": "A bundled meta-schema",
        "examples": [ {} ],
        "properties": {
          "foo-bar": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_draft6, empty_object_as_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {}
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, forbid_empty_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, forbid_empty_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": [1, 2]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": [1, 2]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, forbid_empty_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, forbid_empty_enum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "enum": []
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "not": true
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_in_enum_edge_case_preserves_siblings) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/schemas/my-schema",
    "description": "Edge case schema",
    "examples": [{}],
    "title": "Edge Case Schema",
    "x-custom-annotation": "should not be deleted",
    "const": 1,
    "enum": [1, 2, 3]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/schemas/my-schema",
    "description": "Edge case schema",
    "title": "Edge Case Schema",
    "x-custom-annotation": "should not be deleted",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, const_not_in_enum_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "description": "Test description",
    "examples": [1],
    "const": 1,
    "enum": [2, 3]
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "const_not_in_enum",
                    "Do not set the `const` and `enum` keyword at the same "
                    "time, mainly when their values diverge",
                    false);
  EXPECT_LINT_TRACE(traces, 1, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_draft6, const_not_in_enum_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "properties": {
      "foo": {
        "const": 1,
        "enum": [2, 3]
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "const_not_in_enum",
                    "Do not set the `const` and `enum` keyword at the same "
                    "time, mainly when their values diverge",
                    false);
}

TEST(AlterSchema_lint_draft6, invalid_external_ref_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://unknown.example.com/nonexistent"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
}

TEST(AlterSchema_lint_draft6, invalid_external_ref_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "bar": {
        "$ref": "#/definitions/foo"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_draft6, draft_official_dialect_with_https_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, valid_examples_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft6, valid_default_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
