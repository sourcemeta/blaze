#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class Canonicalizer202012Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-2020-12.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    Canonicalizer202012Test::compiled_meta_ = nullptr;

TEST_F(Canonicalizer202012Test, duplicate_allof_branches_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "number"
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, duplicate_allof_branches_3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "number"
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, duplicate_allof_branches_4) {
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "number"
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, single_branch_allof_unwrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, single_branch_anyof_unwrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, single_branch_oneof_unwrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       single_branch_allof_with_unevaluated_properties_stays) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string" }
    ],
    "unevaluatedProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "string",
        "minLength": 0
      }
    ],
    "unevaluatedProperties": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       single_branch_allof_with_unevaluated_items_stays) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "array" }
    ],
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false
      }
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       single_branch_anyof_with_unevaluated_properties_renamed_to_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" }
    ],
    "unevaluatedProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "string",
        "minLength": 0
      }
    ],
    "unevaluatedProperties": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       single_branch_anyof_with_unevaluated_items_renamed_to_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "array" }
    ],
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false
      }
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       single_branch_oneof_with_unevaluated_properties_renamed_to_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" }
    ],
    "unevaluatedProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "string",
        "minLength": 0
      }
    ],
    "unevaluatedProperties": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, single_branch_allof_bare_ref_stays) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#"
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       duplicate_allof_branches_dedup_to_single_then_unwrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       duplicate_anyof_branches_dedup_to_single_then_unwrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "integer" },
      { "type": "integer" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_false_simplify_preserves_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "type": "string",
    "allOf": [ false ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_false_simplify_preserves_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "myanchor",
    "type": "string",
    "allOf": [ false ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "myanchor",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_false_simplify_removes_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "allOf": [ false ],
    "$defs": {
      "foo": { "type": "number" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, duplicate_allof_branches_5) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "multipleOf": 2,
    "allOf": [
      { "type": "number", "multipleOf": 1 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "type": "number",
          "multipleOf": 1
        },
        {
          "multipleOf": 2,
          "type": "number"
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dependent_required_tautology_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo" ],
    "dependentRequired": {
      "foo": [ "bar" ],
      "bar": [ "baz" ]
    }
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "baz" ],
    "minProperties": 3,
    "propertyNames": true,
    "properties": {
      "foo": true,
      "bar": true,
      "baz": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_boolean_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean"
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_boolean_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json("false");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_null_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null"
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_null_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json("false");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, const_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_maximum_integer_to_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_maximum_integer_to_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1.2
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_maximum_integer_to_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_maximum_integer_to_maximum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMaximum": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
        "patternProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "minContains": 0,
        "contains": true,
        "items": true
      },
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number",
        "exclusiveMaximum": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_minimum_integer_to_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_minimum_integer_to_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1.2
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_minimum_integer_to_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, exclusive_minimum_integer_to_minimum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
        "patternProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "minContains": 0,
        "contains": true,
        "items": true
      },
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number",
        "exclusiveMinimum": 1
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, boolean_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
        "properties": {
          "foo": true
        },
        "patternProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "minContains": 0,
        "contains": true,
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
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_array_to_any_of_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo",
    "type": [ "integer", "number", "string" ],
    "minimum": 5
  })JSON");

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

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_array_to_any_of_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "integer", "number", "string" ],
    "anyOf": [
      { "minimum": 4, "type": "integer" },
      { "maximum": 8, "type": "integer" }
    ]
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "anyOf": [
          {
            "type": "integer",
            "minimum": 4,
            "multipleOf": 1
          },
          {
            "type": "integer",
            "maximum": 8,
            "multipleOf": 1
          }
        ]
      },
      {
        "anyOf": [
          {
            "type": "integer",
            "multipleOf": 1
          },
          {
            "type": "number"
          },
          {
            "type": "string",
            "minLength": 0
          }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_array_to_any_of_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array", "string" ],
    "additionalProperties": {
      "$anchor": "foo",
      "type": "string"
    }
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {
          "$anchor": "foo",
          "type": "string",
          "minLength": 0
        }
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "minContains": 0,
        "contains": true,
        "items": true
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_array_to_any_of_4) {
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

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#/$defs/foo"
      },
      {
        "anyOf": [
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "minContains": 0,
            "contains": true,
            "items": true
          }
        ]
      }
    ],
    "$defs": {
      "foo": {
        "type": "string",
        "minLength": 0
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_array_to_any_of_5) {
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

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "title": "My schema",
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
            "properties": {}
          },
          {
            "type": "array",
            "uniqueItems": false,
            "minItems": 0,
            "contains": true,
            "minContains": 0,
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
            "properties": {}
          },
          {
            "type": "array",
            "uniqueItems": false,
            "minItems": 0,
            "contains": true,
            "minContains": 0,
            "items": true
          },
          {
            "type": "string",
            "minLength": 1
          },
          {
            "type": "number"
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
            "type": "string",
            "minLength": 0
          },
          {
            "type": "number"
          }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, max_contains_covered_by_max_items_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2,
    "maxItems": 1
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 1,
    "minItems": 0,
    "uniqueItems": false,
    "maxContains": 1,
    "minContains": 1,
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, min_properties_covered_by_required_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo", "bar" ]
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "propertyNames": true,
    "properties": {
      "foo": true,
      "bar": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, min_properties_implicit_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "propertyNames": true,
    "properties": {
      "foo": true,
      "bar": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, min_properties_implicit_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ]
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "propertyNames": true,
    "properties": {
      "foo": true,
      "bar": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, min_items_given_min_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "boolean" },
    "minContains": 3
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 3,
    "contains": {
      "enum": [ false, true ]
    },
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, min_items_given_min_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minContains": 3
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       exclusive_maximum_integer_to_maximum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1.0e400
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 10.00000000000000e+399
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       exclusive_minimum_integer_to_minimum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1.0e400
  })JSON");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1.0e+400
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, circular_ref_through_defs_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$ref": "#/$defs/b" },
      "b": { "$ref": "#/$defs/a" }
    },
    "$ref": "#/$defs/a"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#/$defs/a"
      }
    ],
    "$defs": {
      "a": {
        "$ref": "#/$defs/b"
      },
      "b": {
        "$ref": "#/$defs/a"
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, conflicting_type_and_const_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "const": 42
  })JSON");

  const auto expected = sourcemeta::core::parse_json("false");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, conflicting_type_and_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json("false");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_two_required_branches_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "required": [ "a" ] },
      { "required": [ "b" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "required": [
            "a"
          ],
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {
            "a": true
          }
        },
        {
          "required": [
            "b"
          ],
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {
            "b": true
          }
        },
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_min_max_constraints_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "integer", "minimum": 0 },
      { "maximum": 100 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "type": "integer",
          "minimum": 0,
          "multipleOf": 1
        },
        {
          "maximum": 100,
          "type": "integer",
          "multipleOf": 1
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_two_properties_branches_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "properties": { "a": {} } },
      { "properties": { "b": {} } }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "properties": {
            "a": true
          },
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0
        },
        {
          "properties": {
            "b": true
          },
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0
        },
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_union_implicit_with_content_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentMediaType": "application/json",
    "contentEncoding": "base64",
    "contentSchema": { "type": "object" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
        "patternProperties": {}
      },
      {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "minContains": 0,
        "contains": true,
        "items": true
      },
      {
        "type": "string",
        "minLength": 0,
        "contentEncoding": "base64",
        "contentMediaType": "application/json",
        "contentSchema": {
          "type": "object",
          "minProperties": 0,
          "propertyNames": true,
          "properties": {},
          "patternProperties": {}
        }
      },
      {
        "type": "number"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, unsatisfiable_logic_branch_type_anyof_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "anyOf": [
      { "type": "number" },
      { "minLength": 1 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "minLength": 1,
          "type": "string"
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

TEST_F(Canonicalizer202012Test, unsatisfiable_logic_branch_type_oneof_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "oneOf": [
      { "type": "string" },
      { "minimum": 0 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "oneOf": [
            false,
            {
              "minimum": 0,
              "type": "number"
            }
          ]
        },
        {
          "type": "number"
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       unsatisfiable_logic_branch_type_if_then_else_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": { "type": "number" },
    "then": { "type": "array" },
    "else": { "type": "object" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "if": false,
        "then": false,
        "else": false
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
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

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "properties": {
            "name": {
              "type": "string",
              "minLength": 0
            }
          },
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0
        },
        {
          "properties": {
            "age": {
              "type": "integer",
              "multipleOf": 1
            }
          },
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0
        },
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, items_implicit_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, items_implicit_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": {
      "type": "string",
      "minLength": 0
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, object_anyof_untyped_branches_1) {
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

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "anyOf": [
            {
              "properties": {
                "indoor": {
                  "enum": [
                    false,
                    true
                  ]
                }
              },
              "type": "object",
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 0
            },
            {
              "properties": {
                "outdoor": {
                  "enum": [
                    false,
                    true
                  ]
                }
              },
              "type": "object",
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 0
            }
          ]
        },
        {
          "type": "object",
          "title": "Pet",
          "properties": {
            "kind": {
              "enum": [
                "cat"
              ]
            }
          },
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#/$defs/schema/anyOf/3/items"
      }
    ],
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
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
            "patternProperties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "minContains": 0,
            "contains": true,
            "items": {
              "type": "string",
              "minLength": 0
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
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_into_subschema_with_existing_anyof) {
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
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
                "properties": {}
              },
              {
                "type": "array",
                "uniqueItems": false,
                "minItems": 0,
                "contains": true,
                "minContains": 0,
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
            "anyOf": [
              {
                "type": "array",
                "items": {
                  "type": "integer",
                  "multipleOf": 1
                },
                "uniqueItems": false,
                "minItems": 0,
                "contains": true,
                "minContains": 0
              },
              {
                "type": "string",
                "minLength": 0
              }
            ]
          }
        ]
      }
    },
    "allOf": [
      {
        "$ref": "#/$defs/schema/allOf/1/anyOf/0/items"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
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
                "properties": {}
              },
              {
                "type": "array",
                "uniqueItems": false,
                "minItems": 0,
                "contains": true,
                "minContains": 0,
                "items": true
              },
              {
                "type": "string",
                "maxLength": 100,
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
                "patternProperties": {},
                "propertyNames": true,
                "minProperties": 0,
                "properties": {}
              },
              {
                "type": "array",
                "uniqueItems": false,
                "minItems": 0,
                "contains": true,
                "minContains": 0,
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
            "anyOf": [
              {
                "type": "array",
                "items": {
                  "type": "integer",
                  "multipleOf": 1
                },
                "uniqueItems": false,
                "minItems": 0,
                "contains": true,
                "minContains": 0
              },
              {
                "type": "string",
                "minLength": 0
              }
            ]
          }
        ]
      }
    },
    "allOf": [
      {
        "$ref": "#/$defs/schema/allOf/2/anyOf/0/items"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
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
            "properties": {
              "bar": true
            },
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0
          },
          {
            "type": "array",
            "uniqueItems": false,
            "minItems": 0,
            "contains": true,
            "minContains": 0,
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
              "foo": {
                "type": "object",
                "patternProperties": {},
                "propertyNames": true,
                "minProperties": 0,
                "properties": {}
              }
            },
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0
          },
          {
            "type": "array",
            "uniqueItems": false,
            "minItems": 0,
            "contains": true,
            "minContains": 0,
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
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_into_nested_subschema_within_resource) {
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#/$defs/resource/anyOf/2/properties/nested/anyOf/0/items"
      }
    ],
    "$defs": {
      "resource": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
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
            "properties": {
              "nested": {
                "anyOf": [
                  {
                    "type": "array",
                    "minItems": 0,
                    "uniqueItems": false,
                    "minContains": 0,
                    "contains": true,
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
            },
            "patternProperties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "minContains": 0,
            "contains": true,
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
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       items_implicit_skipped_with_direct_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       items_implicit_skipped_with_anyof_items_and_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
        "properties": {}
      },
      {
        "type": "array",
        "items": {
          "enum": [ false, true ]
        },
        "uniqueItems": false,
        "minItems": 0
      },
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number"
      },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       items_implicit_skipped_with_anyof_prefix_items_and_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "prefixItems": [ { "type": "boolean" } ] },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
        "properties": {}
      },
      {
        "type": "array",
        "prefixItems": [
          {
            "enum": [ false, true ]
          }
        ],
        "uniqueItems": false,
        "minItems": 0
      },
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number"
      },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_into_subschema_via_absolute_uri) {
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

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "https://www.example.com#/anyOf/3/items"
      }
    ],
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.example.com",
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
            "patternProperties": {}
          },
          {
            "type": "array",
            "minItems": 0,
            "uniqueItems": false,
            "minContains": 0,
            "contains": true,
            "items": {
              "type": "string",
              "minLength": 0
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
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, empty_object_as_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "data": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {
      "data": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, comment_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "This is a comment",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, definitions_to_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "definitions": {
      "foo": { "type": "string" }
    },
    "type": "object",
    "properties": {
      "x": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {
      "x": {
        "$ref": "#/$defs/foo"
      }
    },
    "patternProperties": {},
    "$defs": {
      "foo": {
        "type": "string",
        "minLength": 0
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, deprecated_false_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "deprecated": false,
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, implicit_contains_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, implicit_object_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {},
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, property_names_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {
      "name": {
        "type": "string",
        "minLength": 0
      }
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, if_then_else_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "then": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "then": true,
    "else": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, no_additional_properties_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {},
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, no_additional_items_implicit_prefix) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [ true ],
    "minItems": 0,
    "uniqueItems": false,
    "contains": true,
    "minContains": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [ true ],
    "minItems": 0,
    "uniqueItems": false,
    "contains": true,
    "minContains": 0,
    "items": true
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dependent_schemas_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "dependentSchemas": {
      "foo": { "type": "string", "minLength": 0 }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "not": {
          "type": "object",
          "required": [ "foo" ],
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {
            "foo": true
          }
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
            "properties": {
              "foo": true
            }
          },
          {
            "type": "string",
            "minLength": 0
          }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dependent_required_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "dependentRequired": {
      "foo": [ "bar" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "enum": [ null ]
      },
      {
        "enum": [ false, true ]
      },
      {
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
                  "properties": {
                    "foo": true
                  }
                }
              },
              {
                "type": "object",
                "required": [ "foo", "bar" ],
                "patternProperties": {},
                "propertyNames": true,
                "minProperties": 2,
                "properties": {
                  "foo": true,
                  "bar": true
                }
              }
            ]
          },
          {
            "type": "object",
            "patternProperties": {},
            "propertyNames": true,
            "minProperties": 0,
            "properties": {}
          }
        ]
      },
      {
        "type": "array",
        "uniqueItems": false,
        "minItems": 0,
        "contains": true,
        "minContains": 0,
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
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, empty_defs_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, empty_dependent_schemas_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "dependentSchemas": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, empty_dependent_required_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "dependentRequired": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_with_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0,
    "allOf": [ true ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, enum_filter_by_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "a", 1 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "minLength": 0,
          "type": "string"
        },
        {
          "enum": [
            "a"
          ]
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, full_string_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "$comment": "test",
    "minLength": 1,
    "maxLength": 10,
    "pattern": "^[a-z]+$"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "pattern": "^[a-z]+$",
    "maxLength": 10,
    "minLength": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, full_object_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$comment": "test",
    "properties": {
      "name": { "type": "string" }
    },
    "required": [ "name" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "name" ],
    "minProperties": 1,
    "propertyNames": true,
    "properties": {
      "name": {
        "type": "string",
        "minLength": 0
      }
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_with_not_and_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0,
    "not": { "type": "string", "minLength": 5 },
    "anyOf": [
      { "type": "string", "minLength": 1 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "not": {
          "type": "string",
          "minLength": 5
        }
      },
      {
        "type": "string",
        "minLength": 1
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, type_with_if_then_else) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0,
    "if": { "type": "string", "maxLength": 10 },
    "then": { "type": "string", "pattern": "^short" },
    "else": { "type": "string", "pattern": "^long" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "if": { "type": "string", "maxLength": 10, "minLength": 0 },
        "then": { "type": "string", "pattern": "^short", "minLength": 0 },
        "else": { "type": "string", "pattern": "^long", "minLength": 0 }
      },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_with_type_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#foo",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$dynamicRef": "#foo" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_with_type_sibling) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "type": "string",
    "$defs": {
      "foo": { "type": "number" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "type": "number" }
    },
    "allOf": [
      { "$ref": "#/$defs/foo" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_through_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "arr": {
        "type": "array",
        "unevaluatedItems": false
      }
    },
    "$ref": "#/$defs/arr/unevaluatedItems"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "arr": {
        "type": "array",
        "minItems": 0,
        "uniqueItems": false,
        "minContains": 0,
        "contains": true,
        "items": false
      }
    },
    "allOf": [
      {
        "$ref": "#/$defs/arr/items"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_through_unevaluated_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "obj": {
        "type": "object",
        "unevaluatedProperties": false
      }
    },
    "$ref": "#/$defs/obj/unevaluatedProperties"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "obj": {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {},
        "patternProperties": {},
        "additionalProperties": false
      }
    },
    "allOf": [
      {
        "$ref": "#/$defs/obj/additionalProperties"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, lone_ref_with_defs_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#/$defs/foo"
      }
    ],
    "$defs": {
      "foo": true
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, lone_dynamic_ref_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#foo"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$dynamicRef": "#foo"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_and_dynamic_ref_in_separate_branches) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/a",
    "$dynamicRef": "#foo",
    "$defs": {
      "a": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": {
        "type": "string",
        "minLength": 0
      }
    },
    "allOf": [
      {
        "$ref": "#/$defs/a"
      },
      {
        "$dynamicRef": "#foo"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_to_static_ref_no_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#/$defs/string",
    "$defs": {
      "string": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "string": {
        "type": "string",
        "minLength": 0
      }
    },
    "allOf": [
      {
        "$ref": "#/$defs/string"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_to_static_ref_single_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#foo",
    "$defs": {
      "string": {
        "$dynamicAnchor": "foo",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "string": {
        "$dynamicAnchor": "foo",
        "type": "string",
        "minLength": 0
      }
    },
    "allOf": [
      {
        "$ref": "#foo"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_stays_dynamic_multiple_resources) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$dynamicAnchor": "foo",
    "$dynamicRef": "#foo",
    "$defs": {
      "other": {
        "$id": "https://example.com/other",
        "$dynamicAnchor": "foo",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$defs": {
      "other": {
        "$id": "https://example.com/other",
        "$dynamicAnchor": "foo",
        "type": "string",
        "minLength": 0
      }
    },
    "$dynamicAnchor": "foo",
    "allOf": [
      {
        "$dynamicRef": "#foo"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_to_static_ref_id_no_fragment) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$dynamicRef": "https://example.com/nested",
    "$defs": {
      "nested": {
        "$id": "https://example.com/nested",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$defs": {
      "nested": {
        "$id": "https://example.com/nested",
        "type": "string",
        "minLength": 0
      }
    },
    "allOf": [
      {
        "$ref": "https://example.com/nested"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_to_static_ref_static_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#bar",
    "$defs": {
      "string": {
        "$anchor": "bar",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "string": {
        "$anchor": "bar",
        "type": "string",
        "minLength": 0
      }
    },
    "allOf": [
      {
        "$ref": "#bar"
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, dynamic_ref_to_static_ref_self_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#"
      },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, object_required_annotations_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "email": {
        "type": "string",
        "format": "email",
        "description": "The user email address"
      },
      "age": {
        "type": "integer",
        "minimum": 0
      }
    },
    "required": ["email"]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "email": {
        "type": "string",
        "format": "email",
        "description": "The user email address",
        "minLength": 0
      },
      "age": {
        "type": "integer",
        "minimum": 0,
        "multipleOf": 1
      }
    },
    "required": [ "email" ],
    "patternProperties": {},
    "propertyNames": true,
    "minProperties": 1
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, contains_object_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": {
      "type": "object",
      "anyOf": [
        { "properties": { "x": { "const": "a" } } },
        { "properties": { "x": { "const": "b" } } }
      ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
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
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        },
        {
          "type": "array",
          "contains": {
            "allOf": [
              {
                "anyOf": [
                  {
                    "properties": {
                      "x": {
                        "enum": [
                          "a"
                        ]
                      }
                    },
                    "type": "object",
                    "patternProperties": {},
                    "propertyNames": true,
                    "minProperties": 0
                  },
                  {
                    "properties": {
                      "x": {
                        "enum": [
                          "b"
                        ]
                      }
                    },
                    "type": "object",
                    "patternProperties": {},
                    "propertyNames": true,
                    "minProperties": 0
                  }
                ]
              },
              {
                "type": "object",
                "patternProperties": {},
                "propertyNames": true,
                "minProperties": 0,
                "properties": {}
              }
            ]
          },
          "uniqueItems": false,
          "minItems": 0,
          "minContains": 1,
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
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, content_schema_object_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": {
      "type": "object",
      "anyOf": [
        { "properties": { "x": { "const": "a" } } },
        { "properties": { "x": { "const": "b" } } }
      ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
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
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        },
        {
          "type": "array",
          "uniqueItems": false,
          "minItems": 0,
          "contains": true,
          "minContains": 0,
          "items": true
        },
        {
          "type": "string",
          "contentSchema": {
            "allOf": [
              {
                "anyOf": [
                  {
                    "properties": {
                      "x": {
                        "enum": [
                          "a"
                        ]
                      }
                    },
                    "type": "object",
                    "patternProperties": {},
                    "propertyNames": true,
                    "minProperties": 0
                  },
                  {
                    "properties": {
                      "x": {
                        "enum": [
                          "b"
                        ]
                      }
                    },
                    "type": "object",
                    "patternProperties": {},
                    "propertyNames": true,
                    "minProperties": 0
                  }
                ]
              },
              {
                "type": "object",
                "patternProperties": {},
                "propertyNames": true,
                "minProperties": 0,
                "properties": {}
              }
            ]
          },
          "contentMediaType": "application/json",
          "contentEncoding": "base64",
          "minLength": 0
        },
        {
          "type": "number"
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, ref_with_annotation_no_type_expansion) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/main",
    "title": "My Schema",
    "$defs": {
      "main": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "title": "My Schema",
        "$ref": "#/$defs/main"
      }
    ],
    "$defs": {
      "main": {
        "type": "string",
        "minLength": 0
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, safe_extract_wraps_modern_ref_into_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$ref": "#/$defs/base",
    "properties": {
      "name": { "type": "string" }
    },
    "allOf": [
      {
        "type": "object",
        "properties": {
          "alias": { "$ref": "#/properties/name" }
        }
      }
    ],
    "$defs": {
      "base": { "type": "object" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {
          "alias": {
            "$ref": "#/allOf/1/properties/name"
          }
        },
        "patternProperties": {}
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
        "patternProperties": {}
      },
      {
        "$ref": "#/$defs/base"
      }
    ],
    "$defs": {
      "base": {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {},
        "patternProperties": {}
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       allof_ref_typed_plus_untyped_has_redundant_type_union) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "#/$defs/base" },
      { "required": [ "name" ] }
    ],
    "$defs": {
      "base": {
        "type": "object",
        "properties": { "id": { "type": "integer" } }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "$ref": "#/$defs/base"
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
                "name"
              ],
              "patternProperties": {},
              "propertyNames": true,
              "minProperties": 1,
              "properties": {
                "name": true
              }
            },
            {
              "type": "array",
              "uniqueItems": false,
              "minItems": 0,
              "contains": true,
              "minContains": 0,
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
        }
      ],
      "$defs": {
        "base": {
          "type": "object",
          "properties": {
            "id": {
              "type": "integer",
              "multipleOf": 1
            }
          },
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0
        }
      }
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_merge_type_and_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "object" },
      { "required": [ "foo" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo" ],
    "minProperties": 1,
    "propertyNames": true,
    "properties": {
      "foo": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_no_merge_branch_has_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "object" },
      { "$anchor": "test", "required": [ "x" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        },
        {
          "$anchor": "test",
          "required": [
            "x"
          ],
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {
            "x": true
          }
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_no_merge_branch_has_dynamic_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "object" },
      { "$dynamicAnchor": "node", "required": [ "x" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        },
        {
          "$dynamicAnchor": "node",
          "required": [
            "x"
          ],
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {
            "x": true
          }
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test, allof_no_merge_branch_has_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "object" },
      { "$id": "https://example.com/branch", "required": [ "x" ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "allOf": [
        {
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 0,
          "properties": {}
        },
        {
          "$id": "https://example.com/branch",
          "required": [
            "x"
          ],
          "type": "object",
          "patternProperties": {},
          "propertyNames": true,
          "minProperties": 1,
          "properties": {
            "x": true
          }
        }
      ]
    }
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer202012Test,
       ref_with_applicator_sibling_preserves_cross_refs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$ref": "#/$defs/base",
    "properties": {
      "name": { "type": "string" }
    },
    "$defs": {
      "base": {
        "type": "object",
        "additionalProperties": { "$ref": "#/properties/name" }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#/$defs/base"
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
        "patternProperties": {}
      }
    ],
    "$defs": {
      "base": {
        "type": "object",
        "minProperties": 0,
        "propertyNames": true,
        "properties": {},
        "patternProperties": {},
        "additionalProperties": {
          "$ref": "#/allOf/1/properties/name"
        }
      }
    }
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, *compiled_meta_);
}
