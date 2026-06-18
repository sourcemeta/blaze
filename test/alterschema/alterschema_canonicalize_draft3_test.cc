#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class CanonicalizerDraft3Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-draft3.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema,
                                   sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver,
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
      "name": {
        "extends": [
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "required": false
      }
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
      "name": {
        "extends": [
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "required": true
      }
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
      "foo": {
        "extends": [
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "required": false
      },
      "bar": {
        "$ref": "#"
      }
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

TEST_F(CanonicalizerDraft3Test, ref_sibling_dropped_in_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "bar": { "$ref": "#", "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "bar": { "$ref": "#" }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, ref_metadata_siblings_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "bar": {
        "$ref": "#",
        "title": "A ref",
        "description": "Refers to root"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "bar": {
        "title": "A ref",
        "description": "Refers to root",
        "$ref": "#"
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, embedded_id_typed_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/embedded",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/embedded",
        "extends": [
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "required": false
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, embedded_id_self_recursive_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/embedded",
        "type": "object",
        "properties": {
          "bar": { "$ref": "#" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/embedded",
        "extends": [
          {
            "type": "object",
            "properties": {
              "bar": {
                "$ref": "#"
              }
            },
            "patternProperties": {},
            "additionalProperties": {}
          }
        ],
        "required": false
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, nested_embedded_ids) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/a",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/a/b",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/a",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/a/b",
        "extends": [
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "required": false
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, ref_into_embedded_resource_pointer) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "https://example.com/embedded",
        "type": "object",
        "properties": {
          "x": { "type": "string" }
        }
      },
      "b": { "$ref": "https://example.com/embedded#/properties/x" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "https://example.com/embedded",
        "extends": [
          {
            "type": "object",
            "properties": {
              "x": {
                "extends": [
                  {
                    "type": "string",
                    "minLength": 0
                  }
                ],
                "required": false
              }
            },
            "patternProperties": {},
            "additionalProperties": {}
          }
        ],
        "required": false
      },
      "b": {
        "$ref": "https://example.com/embedded#/extends/0/properties/x"
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, required_enum_property_preserves_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "enum": [ 1, 2 ], "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "extends": [
          {
            "enum": [ 1, 2 ]
          }
        ],
        "required": true
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, optional_enum_property_stays_compact) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "enum": [ 1, 2 ] }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "extends": [
          {
            "enum": [ 1, 2 ]
          }
        ],
        "required": false
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, required_boolean_property_preserves_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "boolean", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "extends": [
          {
            "enum": [ false, true ]
          }
        ],
        "required": true
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, required_sibling_to_ref_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "$ref": "#", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "$ref": "#" }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, fragment_id_anchor_with_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "id": "#target", "type": "string" },
      "b": { "$ref": "#target" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "#target",
        "extends": [
          {
            "type": "string",
            "minLength": 0
          }
        ],
        "required": false
      },
      "b": {
        "$ref": "#target"
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_string_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "minLength": 0 } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_integer_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "integer", "divisibleBy": 1 } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_boolean_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ false, true ] } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_null_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ null ] } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_object_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {}
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_array_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "items": {}
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_any_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "any"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ {} ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_array_of_types) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "number" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_array_null_and_boolean) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "null", "boolean" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "enum": [ null ] },
      { "enum": [ false, true ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_schema_with_pattern) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "pattern": "^x" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "pattern": "^x", "minLength": 0 } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_schema_with_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ 1, 2 ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ 1, 2 ] } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_schema_with_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "$ref": "#" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "$ref": "#" } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_schema_with_minimum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "number", "minimum": 0 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "number", "minimum": 0 } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_schema_multiple_constraints) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "minLength": 3, "maxLength": 10 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "maxLength": 10, "minLength": 3 } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_three_type_schemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "string" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "string", "minLength": 0 },
      { "type": "number" },
      { "enum": [ false, true ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_mixed_string_and_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", { "type": "object" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "string", "minLength": 0 },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {}
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_double_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "disallow": [ { "type": "string" } ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "disallow": [ { "type": "string", "minLength": 0 } ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_object_with_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "object", "properties": { "a": { "type": "string" } } }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "object",
        "properties": {
          "a": {
            "extends": [
              {
                "type": "string",
                "minLength": 0
              }
            ],
            "required": false
          }
        },
        "patternProperties": {},
        "additionalProperties": {}
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_duplicate_entries) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "string", "minLength": 0 },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_string_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ "a", "b" ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ "a", "b" ] } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_ref_and_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "$ref": "#" }, { "enum": [ 1 ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "$ref": "#" }, { "enum": [ 1 ] } ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, type_string_disallow_non_overlapping) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, type_string_disallow_overlapping) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "disallow": [ { "type": "string", "minLength": 0 } ] },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, type_union_disallow_schema_form_narrows) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "number" ],
    "disallow": [ { "type": "string" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, enum_with_disallow) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 1, 2 ],
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "disallow": [ { "type": "string", "minLength": 0 } ] },
      { "enum": [ 1, 2 ] }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, type_with_typeless_disallow_distributes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": [ { "pattern": "^x" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      {
        "disallow": [
          {
            "type": [
              { "enum": [ null ] },
              { "enum": [ false, true ] },
              {
                "type": "object",
                "properties": {},
                "patternProperties": {},
                "additionalProperties": {}
              },
              {
                "type": "array",
                "minItems": 0,
                "uniqueItems": false,
                "items": {}
              },
              { "type": "string", "pattern": "^x", "minLength": 0 },
              { "type": "number" }
            ]
          }
        ]
      },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_typeless_scalar_distributes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "minLength": 3 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "properties": {},
            "patternProperties": {},
            "additionalProperties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": {}
          },
          { "type": "string", "minLength": 3 },
          { "type": "number" }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, typeless_pattern_distributes_to_string_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "pattern": "^x"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "items": {}
      },
      { "type": "string", "pattern": "^x", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, typeless_minimum_distributes_to_number_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "minimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "items": {}
      },
      { "type": "string", "minLength": 0 },
      { "type": "number", "minimum": 5 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test,
       typeless_max_items_distributes_to_array_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "maxItems": 4
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {}
      },
      {
        "type": "array",
        "maxItems": 4,
        "minItems": 0,
        "uniqueItems": false,
        "items": {}
      },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test,
       type_union_conflicting_sibling_wraps_in_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "string", "minLength": 1 },
      { "type": "string" }
    ],
    "minLength": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      {
        "type": [
          { "type": "string", "minLength": 1 },
          { "type": "string", "minLength": 0 }
        ]
      },
      {
        "type": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          {
            "type": "object",
            "properties": {},
            "patternProperties": {},
            "additionalProperties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "items": {}
          },
          { "type": "string", "minLength": 3 },
          { "type": "number" }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_empty_array_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": []
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "items": {}
      },
      { "type": "string", "minLength": 0 },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, disallow_property_keeps_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "disallow": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "extends": [
          {
            "disallow": [
              {
                "type": "string",
                "minLength": 0
              }
            ]
          }
        ],
        "required": false
      }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft3Test, ref_through_wrapped_property_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "object", "properties": { "x": { "type": "string" } } },
      "b": { "$ref": "#/properties/a/properties/x" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "extends": [
          {
            "type": "object",
            "properties": {
              "x": {
                "extends": [
                  { "type": "string", "minLength": 0 }
                ],
                "required": false
              }
            },
            "patternProperties": {},
            "additionalProperties": {}
          }
        ],
        "required": false
      },
      "b": { "$ref": "#/properties/a/extends/0/properties/x" }
    },
    "patternProperties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}
