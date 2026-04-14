#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class Canonicalizer201909Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-2019-09.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    Canonicalizer201909Test::compiled_meta_ = nullptr;

TEST(AlterSchema_canonicalize_2019_09, duplicate_allof_branches_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, duplicate_allof_branches_3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, duplicate_allof_branches_4) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, type_boolean_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, type_boolean_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, type_null_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "null"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ null ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, type_null_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, const_as_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_maximum_integer_to_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_maximum_integer_to_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMaximum": 1.2
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_maximum_integer_to_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "number",
    "exclusiveMaximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_maximum_integer_to_maximum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMaximum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, exclusive_minimum_integer_to_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_minimum_integer_to_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMinimum": 1.2
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_minimum_integer_to_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "number",
    "exclusiveMinimum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, exclusive_minimum_integer_to_minimum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, boolean_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, max_contains_covered_by_max_items_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2,
    "maxItems": 1
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, min_properties_covered_by_required_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, min_properties_implicit_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, min_properties_implicit_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "minProperties": 2,
    "required": [ "foo", "bar" ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_canonicalize_2019_09, min_items_given_min_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "boolean" },
    "minContains": 3
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "enum": [ false, true ] },
    "minContains": 3,
    "minItems": 3,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, min_items_given_min_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "minContains": 3
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09,
     exclusive_maximum_integer_to_maximum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMaximum": 1.0e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 10.00000000000000e+399
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09,
     exclusive_minimum_integer_to_minimum_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMinimum": 1.0e400
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 1.0e+400
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09,
     unevaluated_properties_with_allof_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "allOf": [
      { "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {
          "foo": {
            "type": "string",
            "minLength": 0
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
    "unevaluatedProperties": {
      "enum": [ false, true ]
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, unevaluated_properties_inside_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "properties": { "foo": true } },
      { "unevaluatedProperties": false }
    ]
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
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
            "minLength": 0
          },
          { "type": "number" }
        ],
        "unevaluatedProperties": false
      }
    ],
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09, items_implicit_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array"
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09,
     items_implicit_skipped_with_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
        "contains": {
          "enum": [ false, true ]
        }
      },
      {
        "type": "string",
        "minLength": 0
      },
      { "type": "number" }
    ],
    "unevaluatedItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09,
     items_implicit_skipped_with_direct_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "minItems": 0,
    "unevaluatedItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_canonicalize_2019_09,
     items_implicit_skipped_with_anyof_and_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
            "items": {
              "enum": [ false, true ]
            },
            "minItems": 0
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

TEST_F(Canonicalizer201909Test, empty_object_as_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "data": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {
      "data": true
    },
    "patternProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, comment_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$comment": "This is a comment",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, definitions_to_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "definitions": {
      "foo": { "type": "string" }
    },
    "type": "object",
    "properties": {
      "x": { "$ref": "#/definitions/foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, deprecated_false_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "deprecated": false,
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, recursive_anchor_false_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": false,
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, implicit_contains_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": true
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, implicit_object_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {},
    "patternProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, property_names_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, if_then_else_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true,
    "then": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true,
    "then": true,
    "else": true
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, no_additional_properties_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {},
    "patternProperties": {},
    "propertyNames": true,
    "minProperties": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "minProperties": 0,
    "propertyNames": true,
    "properties": {},
    "patternProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, no_additional_items_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "items": [ true ],
    "minItems": 0,
    "uniqueItems": false,
    "contains": true,
    "minContains": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "minItems": 0,
    "uniqueItems": false,
    "minContains": 0,
    "contains": true,
    "items": [ true ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, dependent_schemas_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string", "minLength": 0 }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      {
        "anyOf": [
          {
            "not": {
              "type": "object",
              "required": [ "foo" ],
              "minProperties": 1,
              "propertyNames": true,
              "properties": {
                "foo": true
              },
              "patternProperties": {}
            }
          },
          {
            "allOf": [
              {
                "type": "object",
                "required": [ "foo" ],
                "minProperties": 1,
                "propertyNames": true,
                "properties": {
                  "foo": true
                },
                "patternProperties": {}
              },
              {
                "type": "string",
                "minLength": 0
              }
            ]
          }
        ]
      }
    ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, dependent_required_to_any_of) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
            "allOf": [
              {
                "anyOf": [
                  {
                    "not": {
                      "type": "object",
                      "required": [ "foo" ],
                      "minProperties": 1,
                      "propertyNames": true,
                      "properties": {
                        "foo": true
                      },
                      "patternProperties": {}
                    }
                  },
                  {
                    "type": "object",
                    "required": [ "foo", "bar" ],
                    "minProperties": 2,
                    "propertyNames": true,
                    "properties": {
                      "foo": true,
                      "bar": true
                    },
                    "patternProperties": {}
                  }
                ]
              }
            ]
          },
          {
            "type": "object",
            "minProperties": 0,
            "propertyNames": true,
            "properties": {},
            "patternProperties": {}
          }
        ]
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

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, empty_defs_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, empty_dependent_schemas_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, empty_dependent_required_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, type_with_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0,
    "allOf": [ true ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, enum_filter_by_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "enum": [ "a", 1 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
      },
      {
        "enum": [ "a" ]
      }
    ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, full_string_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "$comment": "test",
    "minLength": 1,
    "maxLength": 10,
    "pattern": "^[a-z]+$"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "pattern": "^[a-z]+$",
    "maxLength": 10,
    "minLength": 1
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(Canonicalizer201909Test, full_object_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "$comment": "test",
    "properties": {
      "name": { "type": "string" }
    },
    "required": [ "name" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}
