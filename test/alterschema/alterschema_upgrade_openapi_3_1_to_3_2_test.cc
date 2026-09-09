#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(already_openapi_3_2_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(plain_2020_12_document_stops_at_2020_12) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(draft7_document_stops_at_2020_12) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 1
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(dialect_base_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(dialect_base_bumped_keeps_other_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "minLength": 1
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(dialect_2024_10_25_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/2024-10-25",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(dialect_2024_11_10_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/2024-11-10",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(dialect_from_default_dialect) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON");

  UPGRADE_OPENAPI_3_2_WITH_DIALECT(
      document, expected, "https://spec.openapis.org/oas/3.1/dialect/base");
}

TEST(embedded_resource_dialect_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner",
        "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
        "type": "integer"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner",
        "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
        "type": "integer"
      }
    }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(vocabulary_bumped_in_metaschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/dialect",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://spec.openapis.org/oas/3.1/vocab/base": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/dialect",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://spec.openapis.org/oas/3.2/vocab/base": false
    }
  })JSON");

  UPGRADE_OPENAPI_3_2_AS_METASCHEMA(document, expected);
}

TEST(vocabulary_bumped_in_metaschema_with_existing_3_2_vocabulary) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/dialect",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://spec.openapis.org/oas/3.1/vocab/base": false,
      "https://spec.openapis.org/oas/3.2/vocab/base": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/dialect",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://spec.openapis.org/oas/3.2/vocab/base": false
    }
  })JSON");

  UPGRADE_OPENAPI_3_2_AS_METASCHEMA(document, expected);
}

TEST(example_to_examples) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "example": "foo"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "examples": [ "foo" ]
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_to_examples_wraps_array_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "array",
    "example": [ 1, 2 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "array",
    "examples": [ [ 1, 2 ] ]
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_to_examples_wraps_object_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "example": { "foo": "bar" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "examples": [ { "foo": "bar" } ]
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_to_examples_wraps_null_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "example": null
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "examples": [ null ]
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_appended_to_existing_examples) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "examples": [ "foo" ],
    "example": "bar"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "examples": [ "foo", "bar" ]
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_kept_when_examples_is_not_an_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "examples": "not-an-array",
    "example": "foo"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "examples": "not-an-array",
    "example": "foo"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_in_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string",
        "example": "bar"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "bar" ]
      }
    }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_untouched_without_openapi_vocabulary) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "example": "foo"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "example": "foo"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_attribute_true_to_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "attribute": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "nodeType": "attribute" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_attribute_true_keeps_other_fields) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "name": "id", "attribute": true, "prefix": "ex" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "name": "id", "nodeType": "attribute", "prefix": "ex" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_attribute_false_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "name": "id", "attribute": false }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "name": "id" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_wrapped_true_to_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "array",
    "xml": { "name": "books", "wrapped": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "array",
    "xml": { "name": "books", "nodeType": "element" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_wrapped_false_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "array",
    "xml": { "name": "books", "wrapped": false }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "array",
    "xml": { "name": "books" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_attribute_true_with_wrapped_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "attribute": true, "wrapped": false }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "nodeType": "attribute" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_wrapped_true_with_attribute_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "array",
    "xml": { "attribute": false, "wrapped": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "array",
    "xml": { "nodeType": "element" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_attribute_true_with_wrapped_true_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "array",
    "xml": { "attribute": true, "wrapped": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "array",
    "xml": { "attribute": true, "wrapped": true }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_node_type_already_present_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "nodeType": "text", "attribute": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "nodeType": "text", "attribute": true }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_non_boolean_attribute_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "attribute": "yes" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "attribute": "yes" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_non_boolean_wrapped_alongside_attribute_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "array",
    "xml": { "attribute": true, "wrapped": "yes" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "array",
    "xml": { "attribute": true, "wrapped": "yes" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_attribute_false_alone_leaves_empty_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "attribute": false }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": {}
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_with_namespace_gets_element_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "namespace": "https://example.com/schema" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "namespace": "https://example.com/schema", "nodeType": "element" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_with_attribute_false_and_name_gets_element_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "name": "pet", "attribute": false }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "name": "pet", "nodeType": "element" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_without_legacy_fields_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "xml": { "name": "id", "namespace": "https://example.com" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "xml": { "name": "id", "namespace": "https://example.com" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_with_name_gets_element_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "name": "pet" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "name": "pet", "nodeType": "element" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_dynamic_ref_with_name_gets_element_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "$dynamicAnchor": "pet", "type": "string" }
    },
    "$dynamicRef": "#pet",
    "xml": { "prefix": "ex" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "$dynamicAnchor": "pet", "type": "string" }
    },
    "$dynamicRef": "#pet",
    "xml": { "prefix": "ex", "nodeType": "element" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_with_attribute_true_prefers_attribute_node_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "name": "pet", "attribute": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "name": "pet", "nodeType": "attribute" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_without_naming_fields_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "x-vendor": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "xml": { "x-vendor": true }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_with_array_type_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "type": "array",
    "xml": { "name": "pets" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "type": "array",
    "xml": { "name": "pets" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_ref_with_array_in_type_union_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "type": [ "array", "null" ],
    "xml": { "name": "pets" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "pet": { "type": "string" }
    },
    "$ref": "#/$defs/pet",
    "type": [ "array", "null" ],
    "xml": { "name": "pets" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_untouched_without_openapi_vocabulary) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "xml": { "attribute": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "xml": { "attribute": true }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(xml_in_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "properties": {
      "id": {
        "type": "string",
        "xml": { "attribute": true }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "properties": {
      "id": {
        "type": "string",
        "xml": { "nodeType": "attribute" }
      }
    }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_in_embedded_resource) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner",
        "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
        "type": "integer",
        "example": 1
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner",
        "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
        "type": "integer",
        "examples": [ 1 ]
      }
    }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(discriminator_and_external_docs_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "discriminator": {
      "propertyName": "petType",
      "mapping": { "dog": "#/$defs/dog" }
    },
    "externalDocs": {
      "url": "https://example.com/docs"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "discriminator": {
      "propertyName": "petType",
      "mapping": { "dog": "#/$defs/dog" }
    },
    "externalDocs": {
      "url": "https://example.com/docs"
    }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(example_and_xml_together) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "example": "foo",
    "xml": { "attribute": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "examples": [ "foo" ],
    "xml": { "nodeType": "attribute" }
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}

TEST(draft7_with_example_reaches_2020_12_without_openapi_rules) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "example": "foo"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "example": "foo"
  })JSON");

  UPGRADE_OPENAPI_3_2(document, expected);
}
