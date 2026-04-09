#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_lint_draft0, single_type_array_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": [ "string" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_array_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "array",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "array",
    "minItems": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_boolean_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "boolean",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_null_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "null",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_numeric_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "number",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "number"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_numeric_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "integer",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_object_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "object",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "object",
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, drop_non_string_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "string",
    "additionalProperties": false,
    "minLength": 2,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "title": "Test",
    "type": "string",
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, draft_official_dialect_without_empty_fragment_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, draft_ref_siblings_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, draft_ref_siblings_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo",
    "type": "string",
    "minLength": 5,
    "description": "A string field"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo",
    "description": "A string field"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, draft_ref_siblings_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo",
    "title": "Test Schema",
    "$comment": "This is a comment",
    "examples": [42],
    "default": null,
    "type": "object",
    "required": ["name"]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo",
    "default": null,
    "title": "Test Schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, draft_ref_siblings_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "id": "http://example.com/schema",
    "$ref": "#/definitions/foo",
    "type": "string",
    "description": "Documentation"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "#/definitions/foo",
    "description": "Documentation"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "fooBar": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "x-fooBar": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "string",
    "baz": 123
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "string",
    "x-baz": 123
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "needsPrefix": "value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "x-needsPrefix": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "customKeyword": "value",
    "anotherOne": 123,
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "x-customKeyword": "value",
    "x-anotherOne": 123,
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "foo": "original value",
    "x-foo": "already prefixed value",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "x-x-foo": "original value",
    "x-foo": "already prefixed value",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "foo": "original value",
    "x-foo": "first prefixed",
    "x-x-foo": "second prefixed",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "x-x-x-foo": "original value",
    "x-foo": "first prefixed",
    "x-x-foo": "second prefixed",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "definitions": {
      "MyType": {
        "type": "string"
      }
    },
    "customKeyword": "should be prefixed"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
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

TEST(AlterSchema_lint_draft0, unknown_keywords_prefix_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "schema",
    "unknownKeyword": "should be removed due to $ref siblings rule",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "$ref": "schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_draft0, draft_official_dialect_with_https_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-00/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}
