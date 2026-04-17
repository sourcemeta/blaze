#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class CanonicalizerDraft7Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-draft7.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    CanonicalizerDraft7Test::compiled_meta_ = nullptr;

TEST_F(CanonicalizerDraft7Test, duplicate_allof_branches_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, duplicate_allof_branches_3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, duplicate_allof_branches_4) {
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_boolean_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_boolean_as_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_null_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_null_as_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, boolean_true_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {
          "foo": true
        },
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 0
      },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": true },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, min_properties_covered_by_required_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "minProperties": 2,
  "required": [ "foo", "bar" ],
  "patternProperties": {},
  "propertyNames": true,
  "properties": {},
  "additionalProperties": true
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, min_properties_implicit_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "required": [ "foo", "bar" ],
  "patternProperties": {},
  "propertyNames": true,
  "minProperties": 2,
  "properties": {},
  "additionalProperties": true
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, min_properties_implicit_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "minProperties": 2,
  "required": [ "foo", "bar" ],
  "patternProperties": {},
  "propertyNames": true,
  "properties": {},
  "additionalProperties": true
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       pattern_properties_additional_properties_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "patternProperties": { "^[a-z]+$": true },
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {},
    "patternProperties": { "^[a-z]+$": true },
    "additionalProperties": false,
    "propertyNames": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, equal_numeric_bounds_to_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_with_all_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 1,
    "maxLength": 100,
    "pattern": "^[a-z]+$",
    "format": "email"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 1,
    "maxLength": 100,
    "pattern": "^[a-z]+$",
    "format": "email"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_with_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 0,
    "maximum": 100
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 0,
    "maximum": 100
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_exclusive_minimum_numeric_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_exclusive_maximum_numeric_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 10
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 9
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_both_exclusive_bounds_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 0,
    "exclusiveMaximum": 10
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1,
    "maximum": 9
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, number_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, number_with_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "minimum": 0,
    "maximum": 1.5,
    "multipleOf": 0.1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "minimum": 0,
    "maximum": 1.5,
    "multipleOf": 0.1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, number_with_exclusive_minimum_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMinimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMinimum": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, number_with_exclusive_maximum_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMaximum": 10
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMaximum": 10
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_with_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0 },
      "age": { "type": "integer", "multipleOf": 1 }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_with_additional_properties_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "additionalProperties": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": { "type": "string", "minLength": 0 },
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_with_max_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "maxProperties": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0,
    "maxProperties": 5
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_with_items_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "items": { "type": "string", "minLength": 0 }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_with_max_items_and_unique) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": { "type": "number" },
    "maxItems": 10,
    "uniqueItems": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": { "type": "number" },
    "minItems": 0,
    "maxItems": 10,
    "uniqueItems": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_schema_items_additional_items_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": { "type": "string" },
    "additionalItems": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": { "type": "string", "minLength": 0 },
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_tuple_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      { "type": "string", "minLength": 0 },
      { "type": "integer", "multipleOf": 1 }
    ],
    "additionalItems": true,
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_tuple_with_additional_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      { "type": "string" }
    ],
    "additionalItems": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      { "type": "string", "minLength": 0 }
    ],
    "additionalItems": { "type": "number" },
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_tuple_additional_items_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [ { "type": "number" } ],
    "additionalItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [ { "type": "number" } ],
    "additionalItems": false,
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "red", "green", "blue" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "red", "green", "blue" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_with_type_matching) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "enum": [ "a", "b", "c" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "a", "b", "c" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, equal_numeric_bounds_number) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "minimum": 3.5,
    "maximum": 3.5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 3.5 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, ref_with_siblings_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "type": "object",
    "properties": {
      "bar": {
        "$ref": "#/definitions/foo",
        "type": "integer"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string", "minLength": 0 }
    },
    "type": "object",
    "properties": {
      "bar": { "$ref": "#/definitions/foo" }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_array_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "string", "number" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_array_single_element) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, empty_subschema_to_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "data": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "data": true
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, anyof_standalone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, oneof_standalone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "integer", "multipleOf": 1 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, not_with_boolean_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, not_with_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "string", "minLength": 0 }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, allof_single_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, unknown_keyword_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "customKeyword": "value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "x-customKeyword": "value"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, definitions_subschemas_canonicalized) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    },
    "type": "object",
    "properties": {
      "name": { "$ref": "#/definitions/name" },
      "age": { "$ref": "#/definitions/age" }
    },
    "required": [ "name" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "name": { "type": "string", "minLength": 0 },
      "age": { "type": "integer", "multipleOf": 1 }
    },
    "type": "object",
    "properties": {
      "name": { "$ref": "#/definitions/name" },
      "age": { "$ref": "#/definitions/age" }
    },
    "required": [ "name" ],
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, nested_object_with_array_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": { "type": "string" }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": { "type": "string", "minLength": 0 },
        "minItems": 0,
        "uniqueItems": false
      }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, full_realistic_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/person",
    "title": "Person",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 1 },
      "age": { "type": "integer", "minimum": 0 },
      "email": { "type": "string", "format": "email" },
      "active": { "type": "boolean" },
      "tags": {
        "type": "array",
        "items": { "type": "string" },
        "uniqueItems": true
      }
    },
    "required": [ "name", "email" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/person",
    "title": "Person",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 1 },
      "age": { "type": "integer", "multipleOf": 1, "minimum": 0 },
      "email": { "type": "string", "minLength": 0, "format": "email" },
      "active": { "enum": [ false, true ] },
      "tags": {
        "type": "array",
        "items": { "type": "string", "minLength": 0 },
        "minItems": 0,
        "uniqueItems": true
      }
    },
    "required": [ "name", "email" ],
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 2
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, annotations_preserved_on_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "title": "Name",
    "description": "The person name",
    "default": "unknown"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "title": "Name",
    "description": "The person name",
    "default": "unknown"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_with_numeric_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_with_string_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minLength": 5,
    "pattern": "^[a-z]+$"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, circular_ref_in_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "definitions": {
      "node": {
        "type": "object",
        "properties": {
          "value": { "type": "string" },
          "child": { "$ref": "#/definitions/node" }
        }
      }
    },
    "properties": {
      "root": { "$ref": "#/definitions/node" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "definitions": {
      "node": {
        "type": "object",
        "properties": {
          "value": { "type": "string", "minLength": 0 },
          "child": { "$ref": "#/definitions/node" }
        },
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 0
      }
    },
    "properties": {
      "root": { "$ref": "#/definitions/node" }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       type_array_with_minimum_distributed_to_numeric) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "integer", "string" ],
    "minimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "integer", "multipleOf": 1, "minimum": 5 },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_array_string_and_null) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "string", "null" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "enum": [ null ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_array_three_types_with_mixed_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "integer", "number", "string" ],
    "minimum": 5,
    "minLength": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "integer", "multipleOf": 1, "minimum": 5 },
      { "type": "number", "minimum": 5 },
      { "type": "string", "minLength": 3 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_array_object_and_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "object", "array" ],
    "minProperties": 1,
    "minItems": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "object", "properties": {}, "patternProperties": {},
        "additionalProperties": true, "propertyNames": true,
        "minProperties": 1 },
      { "type": "array", "minItems": 1, "uniqueItems": false, "items": true }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, dependencies_property_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "dependencies": { "foo": [ "bar" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "not": {
            "type": "object",
            "required": [ "foo" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          }
        },
        {
          "type": "object",
          "required": [ "foo", "bar" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 2,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, dependencies_schema_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "dependencies": { "foo": { "required": [ "bar" ] } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "not": {
            "type": "object",
            "required": [ "foo" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          }
        },
        {
          "allOf": [
            {
              "type": "object",
              "required": [ "foo" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            },
            {
              "anyOf": [
                {
                  "enum": [ null ]
                },
                {
                  "enum": [ false, true ]
                },
                {
                  "type": "object",
                  "required": [ "bar" ],
                  "patternProperties": {},
                  "propertyNames": true,
                  "minProperties": 1,
                  "properties": {},
                  "additionalProperties": true
                },
                {
                  "type": "array",
                  "uniqueItems": false,
                  "items": true,
                  "minItems": 0
                },
                {
                  "type": "string",
                  "minLength": 0
                },
                {
                  "type": "number"
                }
              ]
            }
          ]
        }
      ]
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_with_not_sibling_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "not": {
      "type": "string",
      "pattern": "^admin"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "not": {
          "type": "string",
          "pattern": "^admin",
          "minLength": 0
        }
      },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, ref_siblings_stripped_in_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "$ref": "#/definitions/name_type", "title": "Name", "minLength": 1 }
    },
    "definitions": { "name_type": { "type": "string" } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": { "name": { "$ref": "#/definitions/name_type", "title": "Name" } },
    "definitions": { "name_type": { "type": "string", "minLength": 0 } },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_with_format_only) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "format": "date-time"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "format": "date-time"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, deeply_nested_objects) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "address": {
        "type": "object",
        "properties": {
          "street": { "type": "string" },
          "city": { "type": "string" },
          "zip": { "type": "string", "pattern": "^[0-9]{5}$" }
        },
        "required": [ "street", "city" ]
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "address": {
        "type": "object",
        "properties": {
          "street": { "type": "string", "minLength": 0 },
          "city": { "type": "string", "minLength": 0 },
          "zip": { "type": "string", "minLength": 0, "pattern": "^[0-9]{5}$" }
        },
        "required": [ "street", "city" ],
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 2
      }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, pattern_properties_with_schemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" },
      "^[0-9]+$": { "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {
      "^x-": { "type": "string", "minLength": 0 },
      "^[0-9]+$": { "type": "integer", "multipleOf": 1 }
    },
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, allof_with_compatible_branches) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "integer", "minimum": 0 },
      { "type": "integer", "maximum": 100 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "integer", "multipleOf": 1, "minimum": 0 },
      { "type": "integer", "multipleOf": 1, "maximum": 100 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_mixed_types) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, "two", true, null, { "x": 1 }, [ 1 ] ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, "two", true, null, { "x": 1 }, [ 1 ] ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_single_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 42 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 42 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_duplicate_values_removed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 1, 3, 2 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_additional_properties_false_named) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": { "name": { "type": "string" } },
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": { "name": { "type": "string", "minLength": 0 } },
    "patternProperties": {},
    "additionalProperties": false,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       integer_exclusive_bounds_fold_then_equal_bounds_to_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 4,
    "exclusiveMaximum": 6
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 5 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_items_object_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": {
      "type": "object",
      "properties": { "id": { "type": "integer" }, "label": { "type": "string" } },
      "required": [ "id" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": {
      "type": "object",
      "properties": {
        "id": { "type": "integer", "multipleOf": 1 },
        "label": { "type": "string", "minLength": 0 }
      },
      "required": [ "id" ],
      "patternProperties": {},
      "additionalProperties": true,
      "propertyNames": true,
      "minProperties": 1
    },
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, anyof_with_nested_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "allOf": [
        { "type": "object", "required": [ "name" ] },
        { "type": "object", "required": [ "age" ] }
      ] },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "anyOf": [
    {
      "allOf": [
        {
          "type": "object",
          "required": [ "name" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        },
        {
          "type": "object",
          "required": [ "age" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "type": "string",
      "minLength": 0
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, oneof_disjoint_types_to_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [
      { "type": "string", "minLength": 1 },
      { "type": "number", "minimum": 0 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "string", "minLength": 1 },
      { "type": "number", "minimum": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, not_with_object_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "object", "required": [ "forbidden" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "not": {
    "type": "object",
    "required": [ "forbidden" ],
    "patternProperties": {},
    "propertyNames": true,
    "minProperties": 1,
    "properties": {},
    "additionalProperties": true
  }
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, schema_with_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/my-schema",
    "type": "string",
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/my-schema",
    "type": "string",
    "minLength": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, allof_empty_branch_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [ { "type": "string" }, {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, multiple_x_keywords_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "x-source": "database",
    "x-deprecated-since": "2.0"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "x-source": "database",
    "x-deprecated-since": "2.0"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_required_already_in_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": { "name": { "type": "string" }, "age": { "type": "integer" } },
    "required": [ "name" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": { "name": { "type": "string", "minLength": 0 },
                     "age": { "type": "integer", "multipleOf": 1 } },
    "required": [ "name" ], "patternProperties": {},
    "additionalProperties": true, "propertyNames": true,
    "minProperties": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, orphan_definitions_removed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "definitions": { "unused": { "type": "integer" } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_with_type_matching_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "enum": [ "a", "b", "c" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "a", "b", "c" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_cross_type_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_cross_type_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minLength": 5,
    "pattern": "^[a-z]+$"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, anyof_with_type_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "anyOf": [
      { "type": "object", "required": [ "a" ] },
      { "type": "object", "required": [ "b" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "type": "object",
          "required": [ "a" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        },
        {
          "type": "object",
          "required": [ "b" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, not_with_anyof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "string" },
    "anyOf": [
      { "type": "number" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "not": {
          "type": "string",
          "minLength": 0
        }
      },
      {
        "anyOf": [
          { "type": "number" },
          {
            "type": "integer",
            "multipleOf": 1
          }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_with_anyof_and_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "anyOf": [
      { "type": "object", "required": [ "name" ] },
      { "type": "object", "required": [ "age" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "type": "object",
          "required": [ "name" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        },
        {
          "type": "object",
          "required": [ "age" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "type": "object",
      "properties": {
        "name": {
          "type": "string",
          "minLength": 0
        }
      },
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, double_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": {
      "not": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": {
      "not": {
        "type": "string",
        "minLength": 0
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, unsatisfiable_integer_min_gt_max) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 10,
    "maximum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 5,
    "minimum": 10,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       integer_both_exclusive_bounds_fold_to_single_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 0,
    "exclusiveMaximum": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, deeply_nested_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      {
        "anyOf": [
          {
            "anyOf": [
              { "type": "string" },
              { "type": "number" }
            ]
          }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 0,
        "properties": {},
        "additionalProperties": true
      },
      {
        "type": "array",
        "uniqueItems": false,
        "items": true,
        "minItems": 0
      },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_with_allof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ],
    "allOf": [
      { "minimum": 2 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0,
            "properties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "uniqueItems": false,
            "items": true,
            "minItems": 0
          },
          { "type": "string", "minLength": 0 },
          { "type": "number", "minimum": 2 }
        ]
      },
      { "enum": [ 1, 2, 3 ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, deeply_nested_additional_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "additionalProperties": {
      "type": "object",
      "additionalProperties": {
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": {
      "type": "object",
      "properties": {},
      "patternProperties": {},
      "additionalProperties": {
        "type": "string",
        "minLength": 0
      },
      "propertyNames": true,
      "minProperties": 0
    },
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, tuple_items_with_nested_objects) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      {
        "type": "object",
        "properties": {
          "x": { "type": "integer" }
        }
      },
      {
        "type": "array",
        "items": { "type": "string" }
      }
    ],
    "additionalItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      {
        "type": "object",
        "properties": {
          "x": { "type": "integer", "multipleOf": 1 }
        },
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 0
      },
      {
        "type": "array",
        "items": { "type": "string", "minLength": 0 },
        "minItems": 0,
        "uniqueItems": false
      }
    ],
    "additionalItems": false,
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_required_max_less_than_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "required": [ "a", "b", "c" ],
    "maxProperties": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "required": [ "a", "b", "c" ],
  "maxProperties": 2,
  "patternProperties": {},
  "propertyNames": true,
  "minProperties": 3,
  "properties": {},
  "additionalProperties": true
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, definitions_chain_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "definitions": {
      "a": { "type": "string", "minLength": 1 },
      "b": { "$ref": "#/definitions/a" }
    },
    "properties": {
      "name": { "$ref": "#/definitions/b" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "definitions": {
      "a": {
        "type": "string",
        "minLength": 1
      },
      "b": { "$ref": "#/definitions/a" }
    },
    "properties": {
      "name": { "$ref": "#/definitions/b" }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, oneof_non_disjoint_stays) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [
      { "type": "string", "maxLength": 5 },
      { "type": "string", "minLength": 10 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [
      {
        "type": "string",
        "maxLength": 5,
        "minLength": 0
      },
      {
        "type": "string",
        "minLength": 10
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, tuple_duplicate_schemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [
      { "type": "string" },
      { "type": "string" }
    ],
    "uniqueItems": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": true,
    "items": [
      { "type": "string", "minLength": 0 },
      { "type": "string", "minLength": 0 }
    ],
    "additionalItems": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, empty_subschemas_become_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "patternProperties": {
      "^x-": {}
    },
    "additionalProperties": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {},
    "patternProperties": {
      "^x-": true
    },
    "additionalProperties": true,
    "propertyNames": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_enum_minlength_collapsed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "enum": [ "a", "b" ],
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 1
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [ "a", "b" ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, not_with_anyof_child) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": {
      "anyOf": [
        { "type": "string" },
        { "type": "number" }
      ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": {
      "anyOf": [
        { "type": "string", "minLength": 0 },
        { "type": "number" }
      ]
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, object_with_enum_additional_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "additionalProperties": {
      "enum": [ 1, 2, 3 ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {},
    "patternProperties": {},
    "additionalProperties": {
      "enum": [ 1, 2, 3 ]
    },
    "propertyNames": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_single_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ true ],
    "title": "Always true"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ true ],
    "title": "Always true"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, empty_definitions_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, string_maxlength_zero) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "maxLength": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "maxLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, array_items_not_null) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": {
      "not": { "type": "null" }
    },
    "minItems": 1,
    "maxItems": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": {
      "not": { "enum": [ null ] }
    },
    "minItems": 1,
    "maxItems": 1,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, deeply_nested_closed_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "nested": {
        "type": "object",
        "properties": {
          "deep": {
            "type": "object",
            "properties": {
              "value": { "type": "boolean" }
            },
            "additionalProperties": false,
            "required": [ "value" ]
          }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "nested": {
        "type": "object",
        "properties": {
          "deep": {
            "type": "object",
            "properties": {
              "value": { "enum": [ false, true ] }
            },
            "additionalProperties": false,
            "required": [ "value" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1
          }
        },
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 0
      }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, number_precise_multipleof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "multipleOf": 0.01,
    "minimum": 0,
    "maximum": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "multipleOf": 0.01,
    "minimum": 0,
    "maximum": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, anyof_single_enum_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ 1 ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_oneof_unwrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_allof_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [ true ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 0,
        "properties": {},
        "additionalProperties": true
      },
      {
        "type": "array",
        "uniqueItems": false,
        "items": true,
        "minItems": 0
      },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_anyof_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [ true ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 0,
        "properties": {},
        "additionalProperties": true
      },
      {
        "type": "array",
        "uniqueItems": false,
        "items": true,
        "minItems": 0
      },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_oneof_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [ true ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 0,
        "properties": {},
        "additionalProperties": true
      },
      {
        "type": "array",
        "uniqueItems": false,
        "items": true,
        "minItems": 0
      },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_allof_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [ false ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_anyof_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [ false ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, single_branch_oneof_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [ false ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, duplicate_allof_branches_dedup_to_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, duplicate_anyof_branches_dedup_to_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "type": "integer" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, allof_ref_with_type_and_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "definitions": {
      "base": {
        "type": "object",
        "properties": {
          "id": { "type": "integer" }
        }
      }
    },
    "allOf": [
      { "$ref": "#/definitions/base" }
    ],
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "$ref": "#/definitions/base"
      },
      {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {
          "name": {
            "type": "string",
            "minLength": 0
          }
        },
        "patternProperties": {},
        "additionalProperties": true
      }
    ],
    "definitions": {
      "base": {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {
          "id": {
            "type": "integer",
            "multipleOf": 1
          }
        },
        "patternProperties": {},
        "additionalProperties": true
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, recursive_ref_in_array_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "item": {
        "type": "object",
        "properties": {
          "id": { "type": "integer" },
          "children": {
            "type": "array",
            "items": { "$ref": "#/definitions/item" }
          }
        }
      }
    },
    "type": "array",
    "items": { "$ref": "#/definitions/item" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "items": { "$ref": "#/definitions/item" },
    "definitions": {
      "item": {
        "type": "object",
        "minProperties": 0,
        "properties": {
          "id": {
            "type": "integer",
            "multipleOf": 1
          },
          "children": {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": { "$ref": "#/definitions/item" }
          }
        },
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, property_named_ref_not_a_reference) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "$ref": { "type": "string" }
    },
    "not": { "required": [ "admin" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "not": {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "required": [ "admin" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "uniqueItems": false,
            "items": true,
            "minItems": 0
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      }
    },
    {
      "type": "object",
      "properties": {
        "$ref": {
          "type": "string",
          "minLength": 0
        }
      },
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_value_containing_ref_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "kind": { "enum": [ "$ref", "inline" ] }
    },
    "anyOf": [
      { "type": "object", "required": [ "kind" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "type": "object",
      "required": [ "kind" ],
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 1,
      "properties": {},
      "additionalProperties": true
    },
    {
      "type": "object",
      "properties": {
        "kind": {
          "enum": [ "$ref", "inline" ]
        }
      },
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_partial_type_match_filtered) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "enum": [ "hello", "world", 42, null ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [ "hello", "world" ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, dependencies_tautology_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "dependencies": {
      "foo": [ "bar" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "required": [ "bar", "foo" ],
  "patternProperties": {},
  "propertyNames": true,
  "minProperties": 2,
  "properties": {},
  "additionalProperties": true
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_allof_ref_and_typed_not) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "base": { "type": "object" }
    },
    "type": "object",
    "allOf": [
      { "$ref": "#/definitions/base" }
    ],
    "not": { "type": "object", "required": [ "forbidden" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "definitions": {
    "base": {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  },
  "allOf": [
    {
      "not": {
        "type": "object",
        "required": [ "forbidden" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      }
    },
    {
      "$ref": "#/definitions/base"
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_fold_non_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 10.5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 10,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_fold_non_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 5.2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, dependencies_with_existing_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "anyOf": [
      { "required": [ "a" ] },
      { "required": [ "b" ] }
    ],
    "dependencies": { "x": [ "y" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "anyOf": [
            {
              "enum": [ null ]
            },
            {
              "enum": [ false, true ]
            },
            {
              "type": "object",
              "required": [ "a" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            },
            {
              "type": "array",
              "uniqueItems": false,
              "items": true,
              "minItems": 0
            },
            {
              "type": "string",
              "minLength": 0
            },
            {
              "type": "number"
            }
          ]
        },
        {
          "anyOf": [
            {
              "enum": [ null ]
            },
            {
              "enum": [ false, true ]
            },
            {
              "type": "object",
              "required": [ "b" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            },
            {
              "type": "array",
              "uniqueItems": false,
              "items": true,
              "minItems": 0
            },
            {
              "type": "string",
              "minLength": 0
            },
            {
              "type": "number"
            }
          ]
        }
      ]
    },
    {
      "anyOf": [
        {
          "not": {
            "type": "object",
            "required": [ "x" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          }
        },
        {
          "type": "object",
          "required": [ "x", "y" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 2,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, full_restructure_ref_in_typed_keyword) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "pos": { "type": "integer", "minimum": 0 }
    },
    "type": "object",
    "not": { "required": [ "forbidden" ] },
    "anyOf": [
      { "required": [ "a" ] },
      { "required": [ "b" ] }
    ],
    "properties": {
      "x": { "$ref": "#/definitions/pos" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "definitions": {
    "pos": {
      "type": "integer",
      "minimum": 0,
      "multipleOf": 1
    }
  },
  "allOf": [
    {
      "not": {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "required": [ "forbidden" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "uniqueItems": false,
            "items": true,
            "minItems": 0
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      }
    },
    {
      "anyOf": [
        {
          "anyOf": [
            {
              "enum": [ null ]
            },
            {
              "enum": [ false, true ]
            },
            {
              "type": "object",
              "required": [ "a" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            },
            {
              "type": "array",
              "uniqueItems": false,
              "items": true,
              "minItems": 0
            },
            {
              "type": "string",
              "minLength": 0
            },
            {
              "type": "number"
            }
          ]
        },
        {
          "anyOf": [
            {
              "enum": [ null ]
            },
            {
              "enum": [ false, true ]
            },
            {
              "type": "object",
              "required": [ "b" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            },
            {
              "type": "array",
              "uniqueItems": false,
              "items": true,
              "minItems": 0
            },
            {
              "type": "string",
              "minLength": 0
            },
            {
              "type": "number"
            }
          ]
        }
      ]
    },
    {
      "type": "object",
      "properties": {
        "x": {
          "$ref": "#/definitions/pos"
        }
      },
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_fold_exponential_notation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1e1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 9,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_fold_exponential_notation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 1e1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 11,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       exclusive_maximum_fold_non_integral_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1.05e1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 10,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       exclusive_minimum_fold_non_integral_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 5.2e0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, equal_bounds_to_enum_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 1e1,
    "maximum": 1e1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 10 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_minimum_large_decimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 1e2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 100,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_maximum_large_decimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 1e3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 1000,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, number_multiple_of_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "multipleOf": 1e-1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "multipleOf": 1e-1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_fold_real_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 10.0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 9,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_fold_real_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 5.0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_fold_int64_max) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 9223372036854775807
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 9.223372036854776e+18,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_fold_int64_min) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": -9223372036854775808
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": -9.223372036854776e+18,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_fold_large_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 1e19
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 1.000000000000000e+19,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_fold_large_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1e19
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 1.000000000000000e+19,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_fold_large_integer_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 18014398509481984.0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 18014398509481983,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_fold_large_integer_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 18014398509481984.0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 18014398509481985,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_integer_to_maximum_decimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMaximum": 1.0e400
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 10.00000000000000e+399
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_integer_to_minimum_decimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "exclusiveMinimum": 1.0e400
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1.0e+400
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_maximum_without_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "exclusiveMaximum": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 0
      },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": true },
      { "type": "string", "minLength": 0 },
      { "type": "number", "exclusiveMaximum": 1 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_without_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "exclusiveMinimum": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": true,
        "propertyNames": true,
        "minProperties": 0
      },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": true },
      { "type": "string", "minLength": 0 },
      { "type": "number", "exclusiveMinimum": 1 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_to_enum_integer) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": 42
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 42 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_to_enum_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": "hello"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "hello" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_to_enum_null) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": null
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_to_enum_boolean) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ true ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_to_enum_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": { "key": "value" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ { "key": "value" } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_to_enum_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ [ 1, 2, 3 ] ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, property_names_implicit_on_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "minProperties": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0 }
    },
    "minProperties": 1,
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_real_with_zero_fraction) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "minimum": 3.0,
    "maximum": 3.0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, examples_annotation_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "examples": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "examples": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, property_names_with_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "propertyNames": { "pattern": "^[a-z]+$" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": {
      "anyOf": [
        { "enum": [ null ] },
        { "enum": [ false, true ] },
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        },
        {
          "type": "array",
          "uniqueItems": false,
          "items": true,
          "minItems": 0
        },
        {
          "type": "string",
          "pattern": "^[a-z]+$",
          "minLength": 0
        },
        {
          "type": "number"
        }
      ]
    },
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, contains_with_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "contains": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": true,
    "contains": { "type": "string", "minLength": 0 },
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_multipleof_with_exclusive_max) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 3,
    "minimum": 1,
    "exclusiveMaximum": 12
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "maximum": 11,
    "minimum": 1,
    "multipleOf": 3
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, definitions_exclusive_bounds_folded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "pos": {
        "type": "integer",
        "exclusiveMinimum": 0
      },
      "neg": {
        "type": "integer",
        "exclusiveMaximum": 0
      }
    },
    "type": "object",
    "properties": {
      "gain": { "$ref": "#/definitions/pos" },
      "loss": { "$ref": "#/definitions/neg" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {
      "gain": { "$ref": "#/definitions/pos" },
      "loss": { "$ref": "#/definitions/neg" }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "definitions": {
      "pos": {
        "type": "integer",
        "minimum": 1,
        "multipleOf": 1
      },
      "neg": {
        "type": "integer",
        "maximum": -1,
        "multipleOf": 1
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_assertion_minLength_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "abc", "def" ],
    "minLength": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 2
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [ "abc", "def" ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_assertion_multipleOf_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 2, 4, 6 ],
    "multipleOf": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number",
            "multipleOf": 2
          }
        ]
      },
      {
        "enum": [ 2, 4, 6 ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_assertion_minimum_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 5, 10 ],
    "minimum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number",
            "minimum": 3
          }
        ]
      },
      {
        "enum": [ 5, 10 ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_assertion_pattern_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "foo", "bar" ],
    "pattern": "^f"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "pattern": "^f",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [ "foo", "bar" ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_tautological_items_true_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ [ 1 ], [ 2 ] ],
    "items": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [
      [ 1 ],
      [ 2 ]
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       enum_tautological_additionalProperties_true_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ { "a": 1 } ],
    "additionalProperties": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [
      {
        "a": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_constraining_items_schema_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ [ 1 ], [ 2 ] ],
    "items": { "type": "integer" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": {
              "type": "integer",
              "multipleOf": 1
            }
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [
          [ 1 ],
          [ 2 ]
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       enum_constraining_additionalProperties_false_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ { "a": 1 } ],
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": false
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [
          {
            "a": 1
          }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_constraining_anyof_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "a", "b", 1 ],
    "anyOf": [ { "type": "string" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "type": "string",
        "minLength": 0
      },
      {
        "enum": [ "a", "b", 1 ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_constraining_not_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ],
    "not": { "minimum": 3 }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "not": {
          "anyOf": [
            {
              "enum": [ null ]
            },
            {
              "enum": [ false, true ]
            },
            {
              "type": "object",
              "minProperties": 0,
              "propertyNames": true,
              "properties": {},
              "patternProperties": {},
              "additionalProperties": true
            },
            {
              "type": "array",
              "minItems": 0,
              "uniqueItems": false,
              "items": true
            },
            {
              "type": "string",
              "minLength": 0
            },
            {
              "type": "number",
              "minimum": 3
            }
          ]
        }
      },
      {
        "enum": [ 1, 2, 3 ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_constraining_oneof_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2 ],
    "oneOf": [ { "minimum": 2 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0,
            "properties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "uniqueItems": false,
            "items": true,
            "minItems": 0
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number",
            "minimum": 2
          }
        ]
      },
      {
        "enum": [ 1, 2 ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_mixed_assertion_and_applicator) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ],
    "minimum": 0,
    "allOf": [ { "maximum": 5 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0,
            "properties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "uniqueItems": false,
            "items": true,
            "minItems": 0
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number",
            "minimum": 0
          }
        ]
      },
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0,
            "properties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "uniqueItems": false,
            "items": true,
            "minItems": 0
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number",
            "maximum": 5
          }
        ]
      },
      {
        "enum": [ 1, 2, 3 ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test,
       enum_tautological_patternProperties_empty_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ { "a": 1 } ],
    "patternProperties": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [
      {
        "a": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_assertion_uniqueItems_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ [ 1, 2 ], [ 3, 4 ] ],
    "uniqueItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          {
            "enum": [ null ]
          },
          {
            "enum": [ false, true ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          {
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      },
      {
        "enum": [
          [ 1, 2 ],
          [ 3, 4 ]
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_applicator_preserves_dollar_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "http://example.com/schema",
    "type": "string",
    "not": { "pattern": "^admin" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "http://example.com/schema",
    "allOf": [
      {
        "not": {
          "anyOf": [
            { "enum": [ null ] },
            { "enum": [ false, true ] },
            {
              "type": "object",
              "minProperties": 0,
              "propertyNames": true,
              "properties": {},
              "patternProperties": {},
              "additionalProperties": true
            },
            {
              "type": "array",
              "minItems": 0,
              "uniqueItems": false,
              "items": true
            },
            {
              "type": "string",
              "pattern": "^admin",
              "minLength": 0
            },
            { "type": "number" }
          ]
        }
      },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_with_incompatible_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "const": 42
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, const_null_with_string_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "const": null
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, integer_enum_with_real_equivalent) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "enum": [ 3, 3.0, "hello" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          { "type": "string", "minLength": 0 },
          { "type": "number", "multipleOf": 1 }
        ]
      },
      { "enum": [ 3, 3.0 ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, property_names_false_restricts_objects) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "propertyNames": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "minProperties": 0,
    "propertyNames": false,
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, contains_false_restricts_arrays) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "contains": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "contains": false,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, exclusive_minimum_subsumes_minimum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "minimum": 5,
    "exclusiveMinimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMinimum": 5
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, draft4_id_becomes_unknown_keyword) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "id": "http://old.com",
    "$id": "http://new.com",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "http://new.com",
    "x-id": "http://old.com",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_basic) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": { "type": "number" }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_implicit_else) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_else_implicit_then) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "number" },
    "else": { "type": "string", "minLength": 5 }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "number" },
    "then": true,
    "else": { "type": "string", "minLength": 5 }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_only_no_then_no_else_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string" },
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_type_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "if": { "type": "string", "minLength": 5 },
    "then": { "type": "string", "pattern": "^[a-z]+$" },
    "else": { "type": "string", "maxLength": 10 }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "if": { "type": "string", "minLength": 5 },
        "then": { "type": "string", "minLength": 0, "pattern": "^[a-z]+$" },
        "else": { "type": "string", "minLength": 0, "maxLength": 10 }
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_type_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "if": { "type": "object", "required": [ "foo" ] },
    "then": { "type": "object", "required": [ "bar" ] },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "if": {
        "type": "object",
        "required": [ "foo" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      },
      "then": {
        "type": "object",
        "required": [ "bar" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      },
      "else": true
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_not_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "null" },
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "not": { "enum": [ null ] } },
      {
        "if": { "type": "string", "minLength": 0 },
        "then": { "type": "string", "minLength": 1 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_anyof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "anyOf": [ { "type": "string" }, { "type": "number" } ],
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      {
        "if": { "type": "string", "minLength": 0 },
        "then": { "type": "string", "minLength": 1 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_type_and_not) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "not": { "type": "integer", "minimum": 100 },
    "if": { "type": "integer", "minimum": 0 },
    "then": { "type": "integer", "maximum": 50 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "not": { "type": "integer", "multipleOf": 1, "minimum": 100 }
      },
      {
        "if": { "type": "integer", "multipleOf": 1, "minimum": 0 },
        "then": { "type": "integer", "multipleOf": 1, "maximum": 50 },
        "else": true
      },
      {
        "type": "integer",
        "multipleOf": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_nested_canonicalized) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": {
      "type": "object",
      "properties": { "kind": { "const": "a" } }
    },
    "then": { "type": "string" },
    "else": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": {
      "type": "object",
      "properties": { "kind": { "enum": [ "a" ] } },
      "patternProperties": {},
      "additionalProperties": true,
      "propertyNames": true,
      "minProperties": 0
    },
    "then": { "type": "string", "minLength": 0 },
    "else": { "type": "number" }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_all_boolean) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": true,
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": true,
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_false_if) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": false,
    "then": { "type": "string" },
    "else": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": false,
    "then": { "type": "string", "minLength": 0 },
    "else": { "type": "number" }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, then_without_if_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "then": { "type": "string" },
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, else_without_if_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "else": { "type": "string" },
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_drop_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$comment": "This is a comment",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_drop_with_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$comment": "Allowed values",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_drop_nested) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": {
        "$comment": "The user name",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0 }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_drop_on_integer) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$comment": "An integer value",
    "type": "integer",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_drop_on_number) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$comment": "Any number",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, content_encoding_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "contentEncoding": "base64"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "contentEncoding": "base64"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, content_encoding_and_media_type_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, content_media_type_without_encoding_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "contentMediaType": "application/json"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, read_only_preserved_on_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "readOnly": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "readOnly": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, write_only_preserved_on_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "writeOnly": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 0,
    "writeOnly": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, read_only_preserved_on_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "readOnly": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "readOnly": true,
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, read_only_preserved_on_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ],
    "readOnly": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3 ],
    "readOnly": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, read_write_only_both_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "readOnly": true,
    "writeOnly": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1,
    "readOnly": true,
    "writeOnly": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_with_if_then_else) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$comment": "Conditional validation",
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_annotations) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "My Schema",
    "description": "A test",
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "My Schema",
    "description": "A test",
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "http://example.com/schema",
    "if": { "type": "integer" },
    "then": { "type": "integer", "minimum": 0 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "http://example.com/schema",
    "if": { "type": "integer", "multipleOf": 1 },
    "then": { "type": "integer", "multipleOf": 1, "minimum": 0 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_allof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [ { "type": "integer", "minimum": 0 } ],
    "if": { "type": "integer", "minimum": 10 },
    "then": { "type": "integer", "maximum": 100 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "type": "integer", "minimum": 0, "multipleOf": 1 },
      {
        "if": { "type": "integer", "minimum": 10, "multipleOf": 1 },
        "then": { "type": "integer", "maximum": 100, "multipleOf": 1 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_oneof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "oneOf": [ { "type": "string" }, { "type": "integer" } ],
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "anyOf": [ { "type": "string", "minLength": 0 }, { "type": "integer", "multipleOf": 1 } ] },
      {
        "if": { "type": "string", "minLength": 0 },
        "then": { "type": "string", "minLength": 1 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_empty_subschemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": {},
    "then": {},
    "else": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": true,
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_all_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": false,
    "then": false,
    "else": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": false,
    "then": false,
    "else": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_true_if_false_then) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": false,
    "else": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": false,
    "else": { "type": "string", "minLength": 0 }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, nested_if_then_else_in_then) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "object" },
    "then": {
      "if": { "type": "object", "required": [ "name" ] },
      "then": { "type": "object", "required": [ "name", "age" ] },
      "else": true
    },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "if": {
    "type": "object",
    "patternProperties": {},
    "propertyNames": true,
    "minProperties": 0,
    "properties": {},
    "additionalProperties": true
  },
  "then": {
    "if": {
      "type": "object",
      "required": [ "name" ],
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 1,
      "properties": {},
      "additionalProperties": true
    },
    "then": {
      "type": "object",
      "required": [ "name", "age" ],
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 2,
      "properties": {},
      "additionalProperties": true
    },
    "else": true
  },
  "else": true
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, type_array_with_if_then_else) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": [ "string", "number" ],
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      {
        "if": { "type": "string", "minLength": 0 },
        "then": { "type": "string", "minLength": 1 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, dependencies_with_if_then_else) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "dependencies": {
      "foo": [ "bar" ]
    },
    "if": { "type": "object", "required": [ "baz" ] },
    "then": { "type": "object", "required": [ "baz", "qux" ] },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "not": {
            "type": "object",
            "required": [ "foo" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          }
        },
        {
          "type": "object",
          "required": [ "foo", "bar" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 2,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "if": {
        "type": "object",
        "required": [ "baz" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      },
      "then": {
        "type": "object",
        "required": [ "baz", "qux" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 2,
        "properties": {},
        "additionalProperties": true
      },
      "else": true
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, read_only_on_if_then_else) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "readOnly": true,
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "readOnly": true,
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, comment_inside_if_then_else_branches) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "$comment": "check type", "type": "string" },
    "then": { "$comment": "require min", "type": "string", "minLength": 1 },
    "else": { "$comment": "fallback", "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": { "type": "number" }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, ref_inside_if_with_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "positive": { "type": "integer", "minimum": 0 }
    },
    "type": "integer",
    "if": { "$ref": "#/definitions/positive" },
    "then": { "type": "integer", "maximum": 100 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "if": { "$ref": "#/definitions/positive" },
        "then": { "type": "integer", "maximum": 100, "multipleOf": 1 },
        "else": true
      },
      {
        "type": "integer",
        "multipleOf": 1
      }
    ],
    "definitions": {
      "positive": { "type": "integer", "minimum": 0, "multipleOf": 1 }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_examples) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "examples": [ 1, "hello" ],
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "examples": [ 1, "hello" ],
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_default) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "default": 42,
    "if": { "type": "integer" },
    "then": { "type": "integer", "minimum": 0 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "default": 42,
    "if": { "type": "integer", "multipleOf": 1 },
    "then": { "type": "integer", "multipleOf": 1, "minimum": 0 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, content_encoding_on_non_string_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "contentEncoding": "base64"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, write_only_on_if_then_else_with_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "writeOnly": true,
    "if": { "type": "string", "minLength": 5 },
    "then": { "type": "string", "pattern": "^[a-z]+$" },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "if": { "type": "string", "minLength": 5 },
        "then": { "type": "string", "minLength": 0, "pattern": "^[a-z]+$" },
        "else": true
      },
      {
        "type": "string",
        "minLength": 0,
        "writeOnly": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_with_only_else_no_then_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string" },
    "else": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "type": "string", "minLength": 0 },
    "then": true,
    "else": { "type": "number" }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_x_extension) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "x-custom": "value",
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "x-custom": "value",
    "if": { "type": "string", "minLength": 0 },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_not_and_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "null" },
    "anyOf": [ { "type": "string" }, { "type": "number" } ],
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "not": { "enum": [ null ] } },
      { "anyOf": [ { "type": "string", "minLength": 0 }, { "type": "number" } ] },
      {
        "if": { "type": "string", "minLength": 0 },
        "then": { "type": "string", "minLength": 1 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_type_not_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "not": { "type": "object", "required": [ "banned" ] },
    "anyOf": [
      { "type": "object", "required": [ "a" ] },
      { "type": "object", "required": [ "b" ] }
    ],
    "if": { "type": "object", "required": [ "flag" ] },
    "then": { "type": "object", "required": [ "flag", "extra" ] },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "not": {
        "type": "object",
        "required": [ "banned" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      }
    },
    {
      "anyOf": [
        {
          "type": "object",
          "required": [ "a" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        },
        {
          "type": "object",
          "required": [ "b" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {},
          "additionalProperties": true
        }
      ]
    },
    {
      "if": {
        "type": "object",
        "required": [ "flag" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      },
      "then": {
        "type": "object",
        "required": [ "flag", "extra" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 2,
        "properties": {},
        "additionalProperties": true
      },
      "else": true
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_with_dependencies_and_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "dependencies": {
      "credit_card": { "type": "object", "required": [ "billing_address" ] }
    },
    "if": { "type": "object", "required": [ "premium" ] },
    "then": { "type": "object", "required": [ "premium", "support_level" ] },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "anyOf": [
        {
          "not": {
            "type": "object",
            "required": [ "credit_card" ],
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 1,
            "properties": {},
            "additionalProperties": true
          }
        },
        {
          "allOf": [
            {
              "type": "object",
              "required": [ "credit_card" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            },
            {
              "type": "object",
              "required": [ "billing_address" ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {},
              "additionalProperties": true
            }
          ]
        }
      ]
    },
    {
      "if": {
        "type": "object",
        "required": [ "premium" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      },
      "then": {
        "type": "object",
        "required": [ "premium", "support_level" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 2,
        "properties": {},
        "additionalProperties": true
      },
      "else": true
    },
    {
      "type": "object",
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0,
      "properties": {},
      "additionalProperties": true
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, enum_with_if_then_else_and_minimum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ 1, 2, 3, 4, 5 ],
    "minimum": 2,
    "if": { "type": "integer", "maximum": 3 },
    "then": { "type": "integer", "multipleOf": 1 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {},
            "additionalProperties": true
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": true
          },
          { "type": "string", "minLength": 0 },
          { "type": "number", "minimum": 2 }
        ]
      },
      {
        "if": { "type": "integer", "multipleOf": 1, "maximum": 3 },
        "then": { "type": "integer", "multipleOf": 1 },
        "else": true
      },
      { "enum": [ 1, 2, 3, 4, 5 ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, ref_inside_then_with_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "strict": { "type": "string", "minLength": 1, "maxLength": 100 }
    },
    "type": "string",
    "if": { "type": "string", "format": "email" },
    "then": { "$ref": "#/definitions/strict" },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "if": { "type": "string", "format": "email", "minLength": 0 },
        "then": { "$ref": "#/definitions/strict" },
        "else": true
      },
      {
        "type": "string",
        "minLength": 0
      }
    ],
    "definitions": {
      "strict": { "type": "string", "maxLength": 100, "minLength": 1 }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_implicit_with_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "if": { "type": "string", "minLength": 10 },
    "then": { "type": "string", "pattern": "^[A-Z]" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      {
        "if": { "type": "string", "minLength": 10 },
        "then": { "type": "string", "minLength": 0, "pattern": "^[A-Z]" },
        "else": true
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, multiple_applicators_no_type_with_if) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "not": { "type": "null" },
    "oneOf": [ { "type": "string" }, { "type": "integer" } ],
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 5 },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "allOf": [
      { "not": { "enum": [ null ] } },
      { "anyOf": [ { "type": "string", "minLength": 0 }, { "type": "integer", "multipleOf": 1 } ] },
      {
        "if": { "type": "string", "minLength": 0 },
        "then": { "type": "string", "minLength": 5 },
        "else": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft7Test, if_then_else_closed_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": { "name": { "type": "string" } },
    "additionalProperties": false,
    "if": { "type": "object", "required": [ "name" ] },
    "then": { "type": "object", "properties": { "name": { "type": "string", "minLength": 1 } } },
    "else": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "allOf": [
    {
      "if": {
        "type": "object",
        "required": [ "name" ],
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 1,
        "properties": {},
        "additionalProperties": true
      },
      "then": {
        "type": "object",
        "properties": {
          "name": {
            "type": "string",
            "minLength": 1
          }
        },
        "patternProperties": {},
        "propertyNames": true,
        "minProperties": 0,
        "additionalProperties": true
      },
      "else": true
    },
    {
      "type": "object",
      "properties": {
        "name": {
          "type": "string",
          "minLength": 0
        }
      },
      "additionalProperties": false,
      "patternProperties": {},
      "propertyNames": true,
      "minProperties": 0
    }
  ]
})JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}
