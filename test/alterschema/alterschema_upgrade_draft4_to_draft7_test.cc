#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft4_to_Draft7, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7,
     empty_object_subschema_becomes_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "anything": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "anything": true
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7, root_id_with_anchor_value_renamed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "#tag",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "#tag",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7,
     dollar_schema_with_https_scheme_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7,
     dollar_schema_without_empty_fragment_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7, root_id_renamed_and_dialect_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/root",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7,
     boolean_exclusive_minimum_folded_and_dialect_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "number",
    "exclusiveMinimum": 5
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7,
     single_item_enum_becomes_const_after_full_upgrade) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "object",
    "properties": {
      "status": { "enum": [ "active" ] }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/root",
    "type": "object",
    "properties": {
      "status": { "const": "active" }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7,
     sub_resource_via_id_with_boolean_exclusive_and_single_enum) {
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
      },
      "kindType": {
        "enum": [ "alpha" ]
      }
    },
    "properties": {
      "user": { "$ref": "https://example.com/userType" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "userType": {
        "$id": "https://example.com/userType",
        "type": "number",
        "exclusiveMinimum": 0
      },
      "kindType": {
        "const": "alpha"
      }
    },
    "properties": {
      "user": { "$ref": "https://example.com/userType" }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_Draft7, idempotent_after_first_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "minimum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/root",
    "exclusiveMinimum": 5
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
  UPGRADE_DRAFT_7(document, expected);
}
