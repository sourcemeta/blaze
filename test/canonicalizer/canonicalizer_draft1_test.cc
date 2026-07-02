#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "canonicalizer_test_utils.h"

namespace {
auto compiled_metaschema() -> const sourcemeta::blaze::Template & {
  static const sourcemeta::blaze::Template schema_template{
      sourcemeta::blaze::compile(
          sourcemeta::core::read_json(std::filesystem::path{SCHEMAS_PATH} /
                                      "canonical-draft1.json"),
          sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
          sourcemeta::blaze::default_schema_compiler)};
  return schema_template;
}
} // namespace

TEST(type_boolean_as_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_null_as_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ null ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(equal_numeric_bounds_to_enum) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(string_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "minLength": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(integer_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "integer",
    "maxDecimal": 0
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(number_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "number"
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_minimal) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(array_minimal) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(minimum_can_equal_true_drop) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(maximum_can_equal_true_drop) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(minimum_can_equal_integer_fold) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(maximum_can_equal_integer_fold) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_property_optional_implicit) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_property_optional_true) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_empty_property) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(extends_single_to_array) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_string_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "disallow": [ "number" ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(minimum_can_equal_false_with_equal_bounds) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(number_minimum_can_equal_false_with_equal_bounds) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(number_maximum_can_equal_false_with_equal_bounds) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(additionalProperties_false) {
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

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}
