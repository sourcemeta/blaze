#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft4_to_Draft6, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     custom_keyword_named_after_draft_6_addition_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "const": "i-was-custom-in-draft-4"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "x-const": "i-was-custom-in-draft-4"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     custom_keyword_in_nested_subschema_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string",
        "contains": "i-was-custom-in-draft-4"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string",
        "x-contains": "i-was-custom-in-draft-4"
      }
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     promoted_annotation_keyword_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "examples": "any-value-in-draft-4"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "examples": "any-value-in-draft-4"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     prefixed_collision_gets_double_prefix) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "const": "original-custom",
    "x-const": "already-prefixed"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "x-x-const": "original-custom",
    "x-const": "already-prefixed"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     empty_object_subschema_becomes_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "anything": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "anything": true
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, root_id_with_anchor_value_renamed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "#tag",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "#tag",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     dollar_schema_with_https_scheme_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     dollar_schema_without_empty_fragment_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, root_id_renamed_to_dollar_id) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     boolean_exclusive_minimum_with_minimum_at_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "number",
    "exclusiveMinimum": 5
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     boolean_exclusive_maximum_with_maximum_at_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "maximum": 10,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "number",
    "exclusiveMaximum": 10
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     exclusive_minimum_false_dropped_at_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5,
    "exclusiveMinimum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "number",
    "minimum": 5
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     exclusive_maximum_false_dropped_at_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "maximum": 10,
    "exclusiveMaximum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "number",
    "maximum": 10
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     boolean_exclusive_minimum_in_nested_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "age": {
        "type": "number",
        "minimum": 0,
        "exclusiveMinimum": true
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "age": {
        "type": "number",
        "exclusiveMinimum": 0
      }
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     id_rename_combined_with_nested_exclusive_bound) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "object",
    "properties": {
      "amount": {
        "type": "number",
        "maximum": 100,
        "exclusiveMaximum": true
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "object",
    "properties": {
      "amount": {
        "type": "number",
        "exclusiveMaximum": 100
      }
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, idempotent_after_first_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "exclusiveMinimum": 5
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, already_draft_6_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "number",
    "exclusiveMinimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "number",
    "exclusiveMinimum": 5
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, already_draft_7_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, already_2019_09_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     nested_draft_7_resource_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "newer": {
        "$id": "https://example.com/newer",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "newer": {
        "$id": "https://example.com/newer",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6,
     sub_resource_via_id_only_renamed_and_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "userType": {
        "id": "https://example.com/userType",
        "type": "number",
        "minimum": 0,
        "exclusiveMinimum": true
      }
    },
    "properties": {
      "user": { "$ref": "https://example.com/userType" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "userType": {
        "$id": "https://example.com/userType",
        "type": "number",
        "exclusiveMinimum": 0
      }
    },
    "properties": {
      "user": { "$ref": "https://example.com/userType" }
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft6, embedded_draft_4_resource_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "number",
        "minimum": 0,
        "exclusiveMinimum": true
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "number",
        "exclusiveMinimum": 0
      }
    }
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}
