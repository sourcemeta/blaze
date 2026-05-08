#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class CanonicalizerDraft3Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-draft3.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    CanonicalizerDraft3Test::compiled_meta_ = nullptr;

TEST_F(CanonicalizerDraft3Test, type_boolean_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, type_null_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, equal_numeric_bounds_to_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, string_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, integer_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, number_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, object_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, array_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array",
    "items": {},
    "minItems": 0,
    "uniqueItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, divisible_by_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 1,
    "minimum": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, divisible_by_explicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 2
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, exclusive_minimum_false_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number",
    "minimum": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, exclusive_minimum_integer_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "minimum": 0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 1,
    "minimum": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, exclusive_maximum_integer_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "maximum": 10,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 1,
    "maximum": 9
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, object_with_property_required_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0, "required": false }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, object_with_property_required_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0, "required": true }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, object_with_empty_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {}
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, extends_single_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_string_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, enum_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, object_with_ref_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "$ref": "#" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string", "minLength": 0, "required": false },
      "bar": { "$ref": "#" }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_type_any_in_array_with_extras_expanded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "any", "title": "Anything goes" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      {
        "title": "Anything goes",
        "type": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "properties": {}, "patternProperties": {}, "additionalProperties": {} },
          { "type": "array", "minItems": 0, "uniqueItems": false, "items": {} },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test,
       draft3_type_any_in_array_string_form_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "any", "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "type": "object", "properties": {}, "patternProperties": {}, "additionalProperties": {} },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": {} },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test,
       draft3_type_any_in_array_bare_object_form_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", { "type": "any" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "type": "object", "properties": {}, "patternProperties": {}, "additionalProperties": {} },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": {} },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test,
       draft3_type_any_in_array_empty_object_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "type": "object", "properties": {}, "patternProperties": {}, "additionalProperties": {} },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": {} },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_type_any_as_string_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "any"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      { "type": "object", "properties": {}, "patternProperties": {}, "additionalProperties": {} },
      { "type": "array", "minItems": 0, "uniqueItems": false, "items": {} },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_extends_with_any_type_branch_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [
      { "type": "any" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_extends_empty_object_erased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_extends_array_with_single_empty_erased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [ {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_extends_array_drops_empty_keeps_others) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      {},
      { "type": "string", "minLength": 5 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "type": "string", "minLength": 5 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, draft3_extends_array_all_empty_erased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [ {}, {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, additionalProperties_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, unnecessary_extends_ref_wrapper_array_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": {
      "extends": [ { "$ref": "#" } ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": {
      "$ref": "#"
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, unnecessary_extends_ref_wrapper_single_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": {
      "extends": { "$ref": "#" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": {
      "$ref": "#"
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, flatten_nested_extends_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "extends": [ { "type": "string" } ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, non_applicable_disallow_types_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": [ "number", "boolean" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      {
        "disallow": [
          { "enum": [ false, true ] }
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

TEST_F(CanonicalizerDraft3Test, disallow_narrows_type_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "number" ],
    "disallow": [ "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}
