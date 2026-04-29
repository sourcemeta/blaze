#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft6_to_Draft7, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     empty_object_subschema_becomes_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
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

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     dollar_schema_with_https_scheme_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     dollar_schema_without_empty_fragment_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     nested_subschemas_only_root_changes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" },
      "bar": {
        "type": "object",
        "properties": {
          "nested": { "type": "integer" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" },
      "bar": {
        "type": "object",
        "properties": {
          "nested": { "type": "integer" }
        }
      }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7, draft_6_keyword_examples_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "examples": [ "alpha", "beta" ],
    "properties": {
      "nested": {
        "type": "integer",
        "examples": [ 1, 2, 3 ]
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "examples": [ "alpha", "beta" ],
    "properties": {
      "nested": {
        "type": "integer",
        "examples": [ 1, 2, 3 ]
      }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7, idempotent_after_first_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7, already_draft_7_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7, already_2019_09_left_unchanged) {
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

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     nested_2019_09_resource_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "newer": {
        "$id": "https://example.com/newer",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "definitions": {
      "newer": {
        "$id": "https://example.com/newer",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     embedded_older_dialect_resource_transitively_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "integer"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "integer"
      }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7, single_item_enum_becomes_const) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "only" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": "only"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     single_item_enum_in_nested_subschema_becomes_const) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": {
      "status": {
        "enum": [ "active" ]
      },
      "kind": {
        "enum": [ "alpha", "beta" ]
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "status": {
        "const": "active"
      },
      "kind": {
        "enum": [ "alpha", "beta" ]
      }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     enum_with_existing_const_is_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": "only",
    "enum": [ "only" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "const": "only",
    "enum": [ "only" ]
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     custom_keyword_named_after_draft_7_addition_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "if": "i-was-custom-in-draft-6"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "x-if": "i-was-custom-in-draft-6"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_Draft7,
     embedded_draft_6_resource_also_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "integer"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/outer",
    "type": "object",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "integer"
      }
    }
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}
