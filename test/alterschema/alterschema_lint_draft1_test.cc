#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_lint_draft1, enum_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, enum_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, enum_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, enum_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar" ],
    "minimum": 0
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, 2, 3 ],
    "minLength": 0,
    "maxLength": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ { "a": 1 }, { "b": 2 } ],
    "minLength": 3,
    "minimum": 0
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ { "a": 1 }, { "b": 2 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
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
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ { "name": "alice" }, { "age": 25 } ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3,
    "minItems": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 42, "hello", true, null, { "key": "value" }, [1, 2, 3] ],
    "minimum": 10,
    "minLength": 2,
    "minItems": 1,
    "x-foo-bar": 1,
    "maxLength": 100,
    "maxItems": 10,
    "x-baz-qux": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 42, "hello", true, null, { "key": "value" }, [1, 2, 3] ],
    "minimum": 10,
    "minLength": 2,
    "minItems": 1,
    "x-foo-bar": 1,
    "maxLength": 100,
    "maxItems": 10,
    "x-baz-qux": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1,
     non_applicable_enum_validation_keywords_unknown_keyword) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar" ],
    "x-unknown-keyword": "value",
    "x-custom-prop": 42
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ "foo", "bar" ],
    "x-unknown-keyword": "value",
    "x-custom-prop": 42
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_enum_validation_keywords_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "id": "https://example.com/schema",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "enum": [ "red", "green", "blue" ],
    "minimum": 5,
    "minLength": 10,
    "minItems": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "id": "https://example.com/schema",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "enum": [ "red", "green", "blue" ],
    "minLength": 10
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, single_type_array_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": [ "string" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, items_schema_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "items": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, items_schema_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "items": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, items_schema_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "items": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "items": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, items_array_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "items": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, duplicate_enum_values_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, {}, 2, 1, 1, 3, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, {}, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, maximum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maximum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, minimum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, maximum_real_for_integer_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maximum": 1.23456789012345678901234567890e500
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maximum": 1.23456789012345678901234567890e+500
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, minimum_real_for_integer_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 9.99999999999999999999999999999e400
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 99.9999999999999999999999999999e+399
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_array_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "array",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "array",
    "minItems": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_boolean_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "boolean",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_null_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "null",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_numeric_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "number",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "number"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_numeric_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "integer",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_object_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "object",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "object",
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, drop_non_string_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "string",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "title": "Test",
    "type": "string",
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, type_boolean_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "boolean"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, type_null_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "null"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, equal_numeric_bounds_to_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, draft_official_dialect_without_empty_fragment_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, draft_ref_siblings_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, draft_ref_siblings_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo",
    "type": "string",
    "minLength": 5,
    "description": "A string field"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo",
    "description": "A string field"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, draft_ref_siblings_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo",
    "title": "Test Schema",
    "$comment": "This is a comment",
    "examples": [42],
    "default": null,
    "type": "object",
    "required": ["name"]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo",
    "title": "Test Schema",
    "default": null
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, draft_ref_siblings_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "id": "http://example.com/schema",
    "$ref": "#/definitions/foo",
    "type": "string",
    "description": "Documentation"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "#/definitions/foo",
    "description": "Documentation"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, non_applicable_type_specific_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ true, false ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ true, false ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "fooBar": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "x-fooBar": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "baz": 123
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "x-baz": 123
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "needsPrefix": "value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "x-needsPrefix": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "customKeyword": "value",
    "anotherOne": 123,
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "x-customKeyword": "value",
    "x-anotherOne": 123,
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "foo": "original value",
    "x-foo": "already prefixed value",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "x-x-foo": "original value",
    "x-foo": "already prefixed value",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "foo": "original value",
    "x-foo": "first prefixed",
    "x-x-foo": "second prefixed",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "x-x-x-foo": "original value",
    "x-foo": "first prefixed",
    "x-x-foo": "second prefixed",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "definitions": {
      "MyType": {
        "type": "string"
      }
    },
    "customKeyword": "should be prefixed"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "x-definitions": {
      "MyType": {
        "type": "string"
      }
    },
    "x-customKeyword": "should be prefixed"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, unknown_keywords_prefix_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "schema",
    "unknownKeyword": "should be removed due to $ref siblings rule",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "$ref": "schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft1, draft_official_dialect_with_https_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-01/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}
