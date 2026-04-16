#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class CanonicalizerDraft1Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-draft1.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    CanonicalizerDraft1Test::compiled_meta_ = nullptr;

TEST_F(CanonicalizerDraft1Test, type_boolean_as_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, type_null_as_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, equal_numeric_bounds_to_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 3 ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, string_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, integer_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maxDecimal": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, number_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, object_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {},
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, array_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "array",
    "items": {},
    "minItems": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, minimum_can_equal_true_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "minimum": 0,
    "minimumCanEqual": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "minimum": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, maximum_can_equal_true_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "maximum": 100,
    "maximumCanEqual": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "maximum": 100
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, minimum_can_equal_integer_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 0,
    "minimumCanEqual": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maxDecimal": 0,
    "minimum": 1
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, maximum_can_equal_integer_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maximum": 10,
    "maximumCanEqual": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maxDecimal": 0,
    "maximum": 9
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, object_with_property_optional_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0, "optional": false }
    },
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, object_with_property_optional_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "optional": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0, "optional": true }
    },
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, object_with_empty_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "foo": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {
      "foo": {}
    },
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, extends_single_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "extends": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "extends": [
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, disallow_string_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "disallow": [ "number" ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, minimum_can_equal_false_with_equal_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3,
    "minimumCanEqual": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maxDecimal": 0,
    "minimum": 4,
    "maximum": 3
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test,
       number_minimum_can_equal_false_with_equal_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "minimum": 3,
    "maximum": 3,
    "minimumCanEqual": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "minimum": 3,
    "maximum": 3,
    "minimumCanEqual": false
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test,
       number_maximum_can_equal_false_with_equal_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "minimum": 5,
    "maximum": 5,
    "maximumCanEqual": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number",
    "minimum": 5,
    "maximum": 5,
    "maximumCanEqual": false
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, enum_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft1Test, additionalProperties_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object",
    "properties": {},
    "additionalProperties": false
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}
