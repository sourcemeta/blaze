#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft3_to_Draft4, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     custom_keyword_named_after_draft_4_addition_prefixed_multipleOf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "multipleOf": "i-was-custom-in-draft-3"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "x-multipleOf": "i-was-custom-in-draft-3"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     custom_keywords_named_after_draft_4_additions_prefixed_all) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "multipleOf": 1,
    "maxProperties": 1,
    "minProperties": 1,
    "allOf": "x",
    "anyOf": "x",
    "oneOf": "x",
    "not": "x"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "x-multipleOf": 1,
    "x-maxProperties": 1,
    "x-minProperties": 1,
    "x-allOf": "x",
    "x-anyOf": "x",
    "x-oneOf": "x",
    "x-not": "x"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, prefixed_collision_iterates) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "not": "original",
    "x-not": "already-prefixed"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-x-not": "original",
    "x-not": "already-prefixed"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     unrelated_custom_keyword_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "myAnnotation": "value",
    "acmeCorpFlag": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "myAnnotation": "value",
    "acmeCorpFlag": true
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     dollar_schema_with_https_scheme_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     dollar_schema_without_empty_fragment_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, idempotent_after_first_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, already_draft_4_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, already_draft_6_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     nested_draft_4_resource_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "newer": {
        "id": "https://example.com/newer",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "newer": {
        "id": "https://example.com/newer",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, type_any_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "any"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     type_array_with_any_collapses_to_no_type) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "any" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     type_array_with_simple_strings_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "number" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number" ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, type_any_in_nested_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "anything": { "type": "any" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "anything": {}
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     type_array_with_subschema_becomes_anyOf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      "string",
      {
        "type": "object",
        "properties": { "foo": { "type": "string" } }
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "object", "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     type_array_only_strings_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "number", "null" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "string", "number", "null" ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     type_array_with_two_subschemas_becomes_anyOf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ { "type": "string" }, { "type": "number" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, disallow_single_string_to_not) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": "string" }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_array_of_strings_to_not_with_type_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "number" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": [ "string", "number" ] }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_array_with_mixed_strings_and_subschemas_to_not_anyof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      "string",
      {
        "type": "object",
        "properties": { "foo": { "type": "string" } }
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "anyOf": [
        { "type": "string" },
        { "type": "object", "properties": { "foo": { "type": "string" } } }
      ]
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_in_nested_subschema_translated) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "x": { "disallow": "null" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "x": { "not": { "type": "null" } }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, extends_single_schema_to_allOf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "type": "string" } ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, extends_array_of_schemas_to_allOf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [ { "type": "string" }, { "minLength": 1 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "type": "string" }, { "minLength": 1 } ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, extends_with_ref_to_definitions) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "Reusable": { "type": "string" }
    },
    "extends": { "$ref": "#/definitions/Reusable" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "Reusable": { "type": "string" }
    },
    "allOf": [ { "$ref": "#/definitions/Reusable" } ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     definitions_left_unchanged_with_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "Reusable": { "type": "string" }
    },
    "extends": { "$ref": "#/definitions/Reusable" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "Reusable": { "type": "string" }
    },
    "allOf": [ { "$ref": "#/definitions/Reusable" } ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, divisibleBy_renamed_to_multipleOf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "multipleOf": 5
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     divisibleBy_in_nested_subschema_renamed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "amount": { "type": "number", "divisibleBy": 0.25 }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "amount": { "type": "number", "multipleOf": 0.25 }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     required_true_inside_properties_lifted_to_parent_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "required": true },
      "age": { "type": "number" },
      "email": { "type": "string", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "name", "email" ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" },
      "email": { "type": "string" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     required_false_dropped_no_parent_required_added) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "age": { "type": "number", "required": false }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "age": { "type": "number" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     required_true_with_only_required_property_becomes_empty_object) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "tag": { "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "tag" ],
    "properties": {
      "tag": {}
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     required_true_with_existing_parent_required_array_dedups) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "required": [ "existing" ],
    "properties": {
      "name": { "type": "string", "required": true },
      "existing": { "type": "string", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "existing", "name" ],
    "properties": {
      "name": { "type": "string" },
      "existing": { "type": "string" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     required_true_in_property_with_ref_lifted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "$ref": "#/definitions/X", "required": true }
    },
    "definitions": {
      "X": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "name" ],
    "properties": {
      "name": { "$ref": "#/definitions/X" }
    },
    "definitions": {
      "X": { "type": "string" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     dependencies_string_form_to_array_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "dependencies": {
      "foo": "bar"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar" ]
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, dependencies_array_form_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar", "baz" ]
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, dependencies_schema_form_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "dependencies": {
      "foo": { "type": "object" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": { "type": "object" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     dependencies_mixed_string_and_other_forms) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "dependencies": {
      "foo": "bar",
      "qux": [ "a", "b" ],
      "schemaForm": { "type": "object" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "dependencies": {
      "foo": [ "bar" ],
      "qux": [ "a", "b" ],
      "schemaForm": { "type": "object" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, embedded_draft_3_resource_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, idempotent_after_full_transform) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/root",
    "type": "object",
    "properties": {
      "name": { "type": "string", "required": true },
      "tag": { "disallow": "null", "divisibleBy": 1 }
    },
    "extends": { "type": "object" },
    "dependencies": { "name": "tag" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "object",
    "required": [ "name" ],
    "properties": {
      "name": { "type": "string" },
      "tag": { "multipleOf": 1, "not": { "type": "null" } }
    },
    "dependencies": { "name": [ "tag" ] },
    "allOf": [ { "type": "object" } ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     embedded_draft_3_subresource_independently_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "any",
        "disallow": "null"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "not": { "type": "null" }
      }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     no_dollar_schema_with_default_dialect_draft3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "any",
    "extends": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "type": "string" } ]
  })JSON");

  UPGRADE_DRAFT_4_WITH_DIALECT(document, expected,
                               "http://json-schema.org/draft-03/schema#");
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     official_suite_extends_with_required_in_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": { "bar": { "type": "integer", "required": true }},
    "extends": {
      "properties": {
        "foo": { "type": "string", "required": true }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "bar" ],
    "properties": { "bar": { "type": "integer" } },
    "allOf": [
      {
        "required": [ "foo" ],
        "properties": {
          "foo": { "type": "string" }
        }
      }
    ]
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     official_suite_disallow_with_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      "string",
      {
        "type": "object",
        "properties": {
          "foo": { "type": "string" }
        }
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {
      "anyOf": [
        { "type": "string" },
        {
          "type": "object",
          "properties": {
            "foo": { "type": "string" }
          }
        }
      ]
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_string_any_collapses_to_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "any"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {}
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_array_with_any_collapses_to_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "any" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {}
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_array_with_any_and_subschema_collapses_to_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "any", { "type": "object" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": {}
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     disallow_with_unexpected_value_type_left_intact) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": 42
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "disallow": 42
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     extends_with_unexpected_value_type_left_intact) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": 42
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "extends": 42
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, format_host_name_renamed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "host-name"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "hostname"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, format_ip_address_renamed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "ip-address"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "ipv4"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_unchanged_values_are_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "string", "format": "date-time" },
      "b": { "type": "string", "format": "email" },
      "c": { "type": "string", "format": "ipv6" },
      "d": { "type": "string", "format": "uri" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "string", "format": "date-time" },
      "b": { "type": "string", "format": "email" },
      "c": { "type": "string", "format": "ipv6" },
      "d": { "type": "string", "format": "uri" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_removed_values_are_preserved_verbatim) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "string", "format": "date" },
      "b": { "type": "string", "format": "time" },
      "c": { "type": "string", "format": "regex" },
      "d": { "type": "number", "format": "utc-millisec" },
      "e": { "type": "string", "format": "color" },
      "f": { "type": "string", "format": "style" },
      "g": { "type": "string", "format": "phone" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "string", "format": "date" },
      "b": { "type": "string", "format": "time" },
      "c": { "type": "string", "format": "regex" },
      "d": { "type": "number", "format": "utc-millisec" },
      "e": { "type": "string", "format": "color" },
      "f": { "type": "string", "format": "style" },
      "g": { "type": "string", "format": "phone" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, format_rename_triggers_rule_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, format_rename_inside_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "host": { "type": "string", "format": "host-name" },
      "ip": { "type": "string", "format": "ip-address" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "host": { "type": "string", "format": "hostname" },
      "ip": { "type": "string", "format": "ipv4" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_rename_with_other_draft_3_rewrites) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "host-name",
    "disallow": "number",
    "divisibleBy": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "hostname",
    "multipleOf": 2,
    "not": { "type": "number" }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_non_string_value_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": 42
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": 42
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, format_rename_is_idempotent) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "host-name"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "hostname"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_host_name_under_draft_4_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "host-name"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "host-name"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_rename_inside_nested_draft_3_resource) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "inner": {
        "$schema": "http://json-schema.org/draft-03/schema#",
        "id": "https://example.com/inner",
        "type": "string",
        "format": "ip-address"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "inner": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "https://example.com/inner",
        "type": "string",
        "format": "ipv4"
      }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4, format_rename_inside_definitions) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "host": { "type": "string", "format": "host-name" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "host": { "type": "string", "format": "hostname" }
    }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_rename_inside_items_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array",
    "items": { "type": "string", "format": "ip-address" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "string", "format": "ipv4" }
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft4,
     format_value_unrelated_to_known_names_is_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "my-acme-format"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "my-acme-format"
  })JSON");

  UPGRADE_DRAFT_4(document, expected);
}
