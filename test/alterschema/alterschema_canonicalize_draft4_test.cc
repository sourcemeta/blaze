#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class CanonicalizerDraft4Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-draft4.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    CanonicalizerDraft4Test::compiled_meta_ = nullptr;

TEST_F(CanonicalizerDraft4Test, duplicate_allof_branches_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, duplicate_allof_branches_3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, duplicate_allof_branches_4) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_boolean_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_boolean_as_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_null_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_null_as_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, boolean_true_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
        "minProperties": 0
      },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": true },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, min_properties_covered_by_required_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "type": "object",
      "minProperties": 2,
      "required": [
        "foo",
        "bar"
      ],
      "patternProperties": {},
      "properties": {
        "foo": true,
        "bar": true
      },
      "additionalProperties": true
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, min_properties_implicit_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "type": "object",
      "required": [
        "foo",
        "bar"
      ],
      "patternProperties": {},
      "minProperties": 2,
      "properties": {
        "foo": true,
        "bar": true
      },
      "additionalProperties": true
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, min_properties_implicit_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "type": "object",
      "minProperties": 2,
      "required": [
        "foo",
        "bar"
      ],
      "patternProperties": {},
      "properties": {
        "foo": true,
        "bar": true
      },
      "additionalProperties": true
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       pattern_properties_additional_properties_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "patternProperties": { "^[a-z]+$": true },
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {},
    "patternProperties": { "^[a-z]+$": true },
    "additionalProperties": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, equal_numeric_bounds_to_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, string_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, string_with_all_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1,
    "maxLength": 100,
    "pattern": "^[a-z]+$",
    "format": "email"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 1,
    "maxLength": 100,
    "pattern": "^[a-z]+$",
    "format": "email"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_with_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 0,
    "maximum": 100
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 0,
    "maximum": 100
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_exclusive_minimum_boolean_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_exclusive_maximum_boolean_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 10,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 9
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_both_exclusive_bounds_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 0,
    "exclusiveMinimum": true,
    "maximum": 10,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1,
    "maximum": 9
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_exclusive_minimum_false_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 5,
    "exclusiveMinimum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 5
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, number_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, number_with_exclusive_minimum_boolean) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, number_with_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "maximum": 1.5,
    "multipleOf": 0.1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "maximum": 1.5,
    "multipleOf": 0.1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_with_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0 },
      "age": { "type": "integer", "multipleOf": 1 }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_with_additional_properties_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "additionalProperties": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": { "type": "string", "minLength": 0 },
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_with_max_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "maxProperties": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0,
    "maxProperties": 5
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_with_items_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "items": { "type": "string", "minLength": 0 }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_with_max_items_and_unique) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "number" },
    "maxItems": 10,
    "uniqueItems": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "number" },
    "minItems": 0,
    "maxItems": 10,
    "uniqueItems": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_schema_items_additional_items_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "string" },
    "additionalItems": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "string", "minLength": 0 },
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_tuple_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, array_tuple_with_additional_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [
      { "type": "string" }
    ],
    "additionalItems": { "type": "number" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, array_tuple_additional_items_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [ { "type": "number" } ],
    "additionalItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [ { "type": "number" } ],
    "additionalItems": false,
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_bare) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "red", "green", "blue" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "red", "green", "blue" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_with_type_matching) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "a", "b", "c" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "a", "b", "c" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, equal_numeric_bounds_number) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 3.5,
    "maximum": 3.5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 3.5 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, ref_with_siblings_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": { "type": "string", "minLength": 0 }
    },
    "type": "object",
    "properties": {
      "bar": { "$ref": "#/definitions/foo" }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_array_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_array_single_element) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, empty_subschema_to_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "data": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "data": true
    },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, anyof_standalone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, oneof_standalone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "type": "integer", "multipleOf": 1 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, not_with_boolean_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, not_with_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": "string", "minLength": 0 }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, allof_single_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, unknown_keyword_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "customKeyword": "value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0,
    "x-customKeyword": "value"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, definitions_subschemas_canonicalized) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "minProperties": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, nested_object_with_array_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": { "type": "string" }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, full_realistic_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/person",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/person",
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
    "minProperties": 2
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, annotations_preserved_on_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "title": "Name",
    "description": "The person name",
    "default": "unknown"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0,
    "title": "Name",
    "description": "The person name",
    "default": "unknown"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, string_with_numeric_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_with_string_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minLength": 5,
    "pattern": "^[a-z]+$"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, circular_ref_in_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
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
        "minProperties": 0
      }
    },
    "properties": {
      "root": { "$ref": "#/definitions/node" }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       type_array_with_minimum_distributed_to_numeric) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ],
    "minimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "integer", "multipleOf": 1, "minimum": 5 },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_array_string_and_null) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "null" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string", "minLength": 0 },
      { "enum": [ null ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_array_three_types_with_mixed_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "number", "string" ],
    "minimum": 5,
    "minLength": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "integer", "multipleOf": 1, "minimum": 5 },
      { "type": "number", "minimum": 5 },
      { "type": "string", "minLength": 3 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_array_object_and_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "object", "array" ],
    "minProperties": 1,
    "minItems": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "object", "properties": {}, "patternProperties": {},
        "additionalProperties": true,
        "minProperties": 1 },
      { "type": "array", "minItems": 1, "uniqueItems": false, "items": true }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, dependencies_property_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "dependencies": { "foo": [ "bar" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "anyOf": [
            {
              "not": {
                "type": "object",
                "required": [
                  "foo"
                ],
                "patternProperties": {},
                "minProperties": 1,
                "properties": {
                  "foo": true
                },
                "additionalProperties": true
              }
            },
            {
              "type": "object",
              "required": [
                "foo",
                "bar"
              ],
              "patternProperties": {},
              "minProperties": 2,
              "properties": {
                "foo": true,
                "bar": true
              },
              "additionalProperties": true
            }
          ]
        },
        {
          "type": "object",
          "patternProperties": {},
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, dependencies_schema_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "dependencies": { "foo": { "required": [ "bar" ] } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "anyOf": [
            {
              "not": {
                "type": "object",
                "required": [
                  "foo"
                ],
                "patternProperties": {},
                "minProperties": 1,
                "properties": {
                  "foo": true
                },
                "additionalProperties": true
              }
            },
            {
              "allOf": [
                {
                  "type": "object",
                  "required": [
                    "foo"
                  ],
                  "patternProperties": {},
                  "minProperties": 1,
                  "properties": {
                    "foo": true
                  },
                  "additionalProperties": true
                },
                {
                  "anyOf": [
                    {
                      "enum": [
                        null
                      ]
                    },
                    {
                      "enum": [
                        false,
                        true
                      ]
                    },
                    {
                      "type": "object",
                      "required": [
                        "bar"
                      ],
                      "patternProperties": {},
                      "minProperties": 1,
                      "properties": {
                        "bar": true
                      },
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
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_with_not_sibling_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "not": {
      "type": "string",
      "pattern": "^admin"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, ref_siblings_stripped_in_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "$ref": "#/definitions/name_type", "title": "Name", "minLength": 1 }
    },
    "definitions": { "name_type": { "type": "string" } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": { "name": { "$ref": "#/definitions/name_type", "title": "Name" } },
    "definitions": { "name_type": { "type": "string", "minLength": 0 } },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, string_with_format_only) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "date-time"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0,
    "format": "date-time"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, deeply_nested_objects) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
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
        "minProperties": 2
      }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, pattern_properties_with_schemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" },
      "^[0-9]+$": { "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {
      "^x-": { "type": "string", "minLength": 0 },
      "^[0-9]+$": { "type": "integer", "multipleOf": 1 }
    },
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, allof_with_compatible_branches) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "integer", "minimum": 0 },
      { "type": "integer", "maximum": 100 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      { "type": "integer", "multipleOf": 1, "minimum": 0 },
      { "type": "integer", "multipleOf": 1, "maximum": 100 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_mixed_types) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, "two", true, null, { "x": 1 }, [ 1 ] ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, "two", true, null, { "x": 1 }, [ 1 ] ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_single_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 42 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 42 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_duplicate_values_removed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2, 1, 3, 2 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_additional_properties_false_named) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": { "name": { "type": "string" } },
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": { "name": { "type": "string", "minLength": 0 } },
    "patternProperties": {},
    "additionalProperties": false,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       integer_exclusive_bounds_fold_then_equal_bounds_to_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 4,
    "exclusiveMinimum": true,
    "maximum": 6,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 5 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_items_object_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": {
      "type": "object",
      "properties": { "id": { "type": "integer" }, "label": { "type": "string" } },
      "required": [ "id" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
      "minProperties": 1
    },
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, anyof_with_nested_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "allOf": [
        { "type": "object", "required": [ "name" ] },
        { "type": "object", "required": [ "age" ] }
      ] },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "anyOf": [
        {
          "allOf": [
            {
              "type": "object",
              "required": [
                "name"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "name": true
              },
              "additionalProperties": true
            },
            {
              "type": "object",
              "required": [
                "age"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "age": true
              },
              "additionalProperties": true
            }
          ]
        },
        {
          "type": "string",
          "minLength": 0
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, oneof_disjoint_types_to_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string", "minLength": 1 },
      { "type": "number", "minimum": 0 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string", "minLength": 1 },
      { "type": "number", "minimum": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, not_with_object_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": "object", "required": [ "forbidden" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "not": {
        "type": "object",
        "required": [
          "forbidden"
        ],
        "patternProperties": {},
        "minProperties": 1,
        "properties": {
          "forbidden": true
        },
        "additionalProperties": true
      }
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, schema_with_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/my-schema",
    "type": "string",
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/my-schema",
    "type": "string",
    "minLength": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, allof_empty_branch_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "type": "string" }, {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, multiple_x_keywords_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "x-source": "database",
    "x-deprecated-since": "2.0"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0,
    "x-source": "database",
    "x-deprecated-since": "2.0"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_required_already_in_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": { "name": { "type": "string" }, "age": { "type": "integer" } },
    "required": [ "name" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": { "name": { "type": "string", "minLength": 0 },
                     "age": { "type": "integer", "multipleOf": 1 } },
    "required": [ "name" ], "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, orphan_definitions_removed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "definitions": { "unused": { "type": "integer" } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_with_type_matching_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "a", "b", "c" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "a", "b", "c" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, string_cross_type_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_cross_type_keywords_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minLength": 5,
    "pattern": "^[a-z]+$"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, anyof_with_type_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "anyOf": [
      { "type": "object", "required": [ "a" ] },
      { "type": "object", "required": [ "b" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "anyOf": [
            {
              "type": "object",
              "required": [
                "a"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "a": true
              },
              "additionalProperties": true
            },
            {
              "type": "object",
              "required": [
                "b"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "b": true
              },
              "additionalProperties": true
            }
          ]
        },
        {
          "type": "object",
          "patternProperties": {},
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, not_with_anyof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": "string" },
    "anyOf": [
      { "type": "number" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, type_with_anyof_and_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "anyOf": [
      { "type": "object", "required": [ "name" ] },
      { "type": "object", "required": [ "age" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "anyOf": [
            {
              "type": "object",
              "required": [
                "name"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "name": true
              },
              "additionalProperties": true
            },
            {
              "type": "object",
              "required": [
                "age"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "age": true
              },
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
          "minProperties": 0,
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, double_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "not": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, unsatisfiable_integer_min_gt_max) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 10,
    "maximum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 5,
    "minimum": 10,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       integer_both_exclusive_bounds_fold_to_single_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 0,
    "exclusiveMinimum": true,
    "maximum": 2,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, number_exclusive_minimum_false_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, deeply_nested_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_with_allof_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2, 3 ],
    "allOf": [
      { "minimum": 2 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "patternProperties": {},
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

TEST_F(CanonicalizerDraft4Test, deeply_nested_additional_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "additionalProperties": {
      "type": "object",
      "additionalProperties": {
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
      "minProperties": 0
    },
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, tuple_items_with_nested_objects) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [
      {
        "type": "object",
        "properties": {
          "x": { "type": "integer", "multipleOf": 1 }
        },
        "patternProperties": {},
        "additionalProperties": true,
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

TEST_F(CanonicalizerDraft4Test, object_required_max_less_than_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "a", "b", "c" ],
    "maxProperties": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "type": "object",
      "required": [
        "a",
        "b",
        "c"
      ],
      "maxProperties": 2,
      "patternProperties": {},
      "minProperties": 3,
      "properties": {
        "a": true,
        "b": true,
        "c": true
      },
      "additionalProperties": true
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, definitions_chain_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, oneof_non_disjoint_stays) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "oneOf": [
      { "type": "string", "maxLength": 5 },
      { "type": "string", "minLength": 10 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, tuple_duplicate_schemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [
      { "type": "string" },
      { "type": "string" }
    ],
    "uniqueItems": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, empty_subschemas_become_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "patternProperties": {
      "^x-": {}
    },
    "additionalProperties": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {},
    "patternProperties": {
      "^x-": true
    },
    "additionalProperties": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_multipleof_with_exclusive_max) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 3,
    "minimum": 1,
    "maximum": 12,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 11,
    "minimum": 1,
    "multipleOf": 3
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, definitions_exclusive_bounds_folded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "pos": {
        "type": "integer",
        "minimum": 0,
        "exclusiveMinimum": true
      },
      "neg": {
        "type": "integer",
        "maximum": 0,
        "exclusiveMaximum": true
      }
    },
    "type": "object",
    "properties": {
      "gain": { "$ref": "#/definitions/pos" },
      "loss": { "$ref": "#/definitions/neg" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {
      "gain": { "$ref": "#/definitions/pos" },
      "loss": { "$ref": "#/definitions/neg" }
    },
    "patternProperties": {},
    "additionalProperties": true,
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

TEST_F(CanonicalizerDraft4Test, string_enum_minlength_collapsed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "a", "b" ],
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, not_with_anyof_child) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "anyOf": [
        { "type": "string" },
        { "type": "number" }
      ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "anyOf": [
        { "type": "string", "minLength": 0 },
        { "type": "number" }
      ]
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, object_with_enum_additional_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {},
    "additionalProperties": {
      "enum": [ 1, 2, 3 ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 0,
    "properties": {},
    "patternProperties": {},
    "additionalProperties": {
      "enum": [ 1, 2, 3 ]
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_single_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ true ],
    "title": "Always true"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ true ],
    "title": "Always true"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, empty_definitions_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_min_with_equal_max_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 5,
    "exclusiveMinimum": true,
    "maximum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 5,
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, string_maxlength_zero) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0,
    "maxLength": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 0,
    "maxLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, array_items_not_null) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": {
      "not": { "type": "null" }
    },
    "minItems": 1,
    "maxItems": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, deeply_nested_closed_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
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
            "minProperties": 1
          }
        },
        "patternProperties": {},
        "additionalProperties": true,
        "minProperties": 0
      }
    },
    "patternProperties": {},
    "additionalProperties": true,
    "minProperties": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, number_precise_multipleof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "multipleOf": 0.01,
    "minimum": 0,
    "maximum": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "multipleOf": 0.01,
    "minimum": 0,
    "maximum": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, anyof_single_enum_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "enum": [ 1 ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, allof_ref_with_type_and_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      {
        "$ref": "#/definitions/base"
      },
      {
        "type": "object",
        "minProperties": 0,
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

TEST_F(CanonicalizerDraft4Test, recursive_ref_in_array_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
    "$schema": "http://json-schema.org/draft-04/schema#",
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
        "additionalProperties": true
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, property_named_ref_not_a_reference) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "$ref": { "type": "string" }
    },
    "not": { "required": [ "admin" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "not": {
            "anyOf": [
              {
                "enum": [
                  null
                ]
              },
              {
                "enum": [
                  false,
                  true
                ]
              },
              {
                "type": "object",
                "required": [
                  "admin"
                ],
                "patternProperties": {},
                "minProperties": 1,
                "properties": {
                  "admin": true
                },
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
          "minProperties": 0,
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_value_containing_ref_string) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "kind": { "enum": [ "$ref", "inline" ] }
    },
    "anyOf": [
      { "type": "object", "required": [ "kind" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "type": "object",
          "required": [
            "kind"
          ],
          "patternProperties": {},
          "minProperties": 1,
          "properties": {
            "kind": true
          },
          "additionalProperties": true
        },
        {
          "type": "object",
          "properties": {
            "kind": {
              "enum": [
                "$ref",
                "inline"
              ]
            }
          },
          "patternProperties": {},
          "minProperties": 0,
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_partial_type_match_filtered) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "enum": [ "hello", "world", 42, null ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, dependencies_tautology_stripped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "dependencies": {
      "foo": [ "bar" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "type": "object",
      "required": [
        "bar",
        "foo"
      ],
      "patternProperties": {},
      "minProperties": 2,
      "properties": {
        "bar": true,
        "foo": true
      },
      "additionalProperties": true
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, type_allof_ref_and_typed_not) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "base": { "type": "object" }
    },
    "type": "object",
    "allOf": [
      { "$ref": "#/definitions/base" }
    ],
    "not": { "type": "object", "required": [ "forbidden" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "definitions": {
        "base": {
          "type": "object",
          "patternProperties": {},
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        }
      },
      "allOf": [
        {
          "not": {
            "type": "object",
            "required": [
              "forbidden"
            ],
            "patternProperties": {},
            "minProperties": 1,
            "properties": {
              "forbidden": true
            },
            "additionalProperties": true
          }
        },
        {
          "$ref": "#/definitions/base"
        },
        {
          "type": "object",
          "patternProperties": {},
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_fold_non_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 10.5,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 10,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_fold_non_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 5.2,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, dependencies_with_existing_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "anyOf": [
      { "required": [ "a" ] },
      { "required": [ "b" ] }
    ],
    "dependencies": { "x": [ "y" ] }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
      "allOf": [
        {
          "anyOf": [
            {
              "enum": [
                null
              ]
            },
            {
              "enum": [
                false,
                true
              ]
            },
            {
              "type": "object",
              "required": [
                "a"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "a": true
              },
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
            },
            {
              "type": "object",
              "required": [
                "b"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "b": true
              },
              "additionalProperties": true
            }
          ]
        },
        {
          "anyOf": [
            {
              "not": {
                "type": "object",
                "required": [
                  "x"
                ],
                "patternProperties": {},
                "minProperties": 1,
                "properties": {
                  "x": true
                },
                "additionalProperties": true
              }
            },
            {
              "type": "object",
              "required": [
                "x",
                "y"
              ],
              "patternProperties": {},
              "minProperties": 2,
              "properties": {
                "x": true,
                "y": true
              },
              "additionalProperties": true
            }
          ]
        },
        {
          "type": "object",
          "patternProperties": {},
          "minProperties": 0,
          "properties": {},
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, full_restructure_ref_in_typed_keyword) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "http://json-schema.org/draft-04/schema#",
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
                "enum": [
                  null
                ]
              },
              {
                "enum": [
                  false,
                  true
                ]
              },
              {
                "type": "object",
                "required": [
                  "forbidden"
                ],
                "patternProperties": {},
                "minProperties": 1,
                "properties": {
                  "forbidden": true
                },
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
              "enum": [
                null
              ]
            },
            {
              "enum": [
                false,
                true
              ]
            },
            {
              "type": "object",
              "required": [
                "a"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "a": true
              },
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
            },
            {
              "type": "object",
              "required": [
                "b"
              ],
              "patternProperties": {},
              "minProperties": 1,
              "properties": {
                "b": true
              },
              "additionalProperties": true
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
          "minProperties": 0,
          "additionalProperties": true
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       equal_bounds_with_exclusive_minimum_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5,
    "maximum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       equal_bounds_with_exclusive_maximum_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5,
    "maximum": 5,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_fold_exponential_notation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 1e1,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 9,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_fold_exponential_notation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1e1,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 11,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       exclusive_maximum_fold_non_integral_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 1.05e1,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 10,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       exclusive_minimum_fold_non_integral_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 5.2e0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, equal_bounds_to_enum_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1e1,
    "maximum": 1e1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 10 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       equal_bounds_exclusive_exponential_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 1e1,
    "maximum": 1e1,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_minimum_large_decimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1e2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 100,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, integer_maximum_large_decimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 1e3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 1000,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, number_multiple_of_exponential) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "multipleOf": 1e-1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "multipleOf": 1e-1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_fold_real_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 10.0,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 9,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_fold_real_integral) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 5.0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 6,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       exclusive_equal_bounds_without_type_not_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 5,
    "maximum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {},
        "patternProperties": {},
        "additionalProperties": true
      },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": true },
      { "type": "string", "minLength": 0 },
      false
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_false_dropped_on_number) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5,
    "exclusiveMinimum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_false_dropped_on_number) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "maximum": 10,
    "exclusiveMaximum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "maximum": 10
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_fold_int64_max) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 9223372036854775807,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 9.223372036854776e+18,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_fold_int64_min) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": -9223372036854775808,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": -9.223372036854776e+18,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_fold_large_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1e19,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1.000000000000000e+19,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_fold_large_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 1e19,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 1.000000000000000e+19,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_maximum_fold_large_integer_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 18014398509481984.0,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "maximum": 18014398509481983,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, exclusive_minimum_fold_large_integer_real) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 18014398509481984.0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 18014398509481985,
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_assertion_minLength_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "abc", "def" ],
    "minLength": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_assertion_multipleOf_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 2, 4, 6 ],
    "multipleOf": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_assertion_minimum_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 5, 10 ],
    "minimum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_assertion_pattern_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "foo", "bar" ],
    "pattern": "^f"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_tautological_items_true_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ [ 1 ], [ 2 ] ],
    "items": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [
      [ 1 ],
      [ 2 ]
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test,
       enum_tautological_additionalProperties_true_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ { "a": 1 } ],
    "additionalProperties": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [
      {
        "a": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_constraining_items_schema_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ [ 1 ], [ 2 ] ],
    "items": { "type": "integer" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test,
       enum_constraining_additionalProperties_false_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ { "a": 1 } ],
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_constraining_anyof_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "a", "b", 1 ],
    "anyOf": [ { "type": "string" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_constraining_not_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2, 3 ],
    "not": { "minimum": 3 }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_constraining_oneof_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2 ],
    "oneOf": [ { "minimum": 2 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_mixed_assertion_and_applicator) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2, 3 ],
    "minimum": 0,
    "allOf": [ { "maximum": 5 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test,
       enum_tautological_patternProperties_empty_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ { "a": 1 } ],
    "patternProperties": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [
      {
        "a": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, enum_assertion_uniqueItems_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ [ 1, 2 ], [ 3, 4 ] ],
    "uniqueItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST_F(CanonicalizerDraft4Test, enum_wrap_with_ref_through_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ 1, 2, 3 ],
    "not": { "minimum": 3 },
    "allOf": [
      { "$ref": "#/not" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      {
        "enum": [ 1, 2, 3 ]
      },
      {
        "not": {
          "anyOf": [
            { "enum": [ null ] },
            { "enum": [ false, true ] },
            {
              "type": "object",
              "minProperties": 0,
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
            { "type": "number", "minimum": 3 }
          ]
        }
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft4Test, anyof_with_untyped_properties_branches) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      {
        "properties": {
          "version": { "enum": [ 1 ] },
          "data": { "type": "string" }
        }
      },
      {
        "properties": {
          "version": { "enum": [ 2 ] },
          "data": { "type": "integer" }
        }
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      {
        "enum": [ null ]
      },
      {
        "enum": [ false, true ]
      },
      {
        "type": "object",
        "properties": {
          "version": {
            "enum": [ 1 ]
          },
          "data": {
            "type": "string",
            "minLength": 0
          }
        },
        "patternProperties": {},
        "minProperties": 0,
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
      },
      {
        "type": "object",
        "properties": {
          "version": {
            "enum": [ 2 ]
          },
          "data": {
            "type": "integer",
            "multipleOf": 1
          }
        },
        "patternProperties": {},
        "minProperties": 0,
        "additionalProperties": true
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}
