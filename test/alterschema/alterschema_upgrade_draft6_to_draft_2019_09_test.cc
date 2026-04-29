#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft6_to_2019_09, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, definitions_renamed_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "$ref": "#/definitions/foo" }
    },
    "definitions": {
      "foo": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/foo" }
    },
    "$defs": {
      "foo": { "type": "string" }
    }
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, dependencies_split_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "dependencies": {
      "foo": { "type": "string" },
      "qux": [ "foo" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string" }
    },
    "dependentRequired": {
      "qux": [ "foo" ]
    }
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     id_pure_fragment_becomes_anchor_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "#tag"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "tag"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     draft_7_promoted_keyword_in_draft_6_schema_prefixed_first) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "if": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-if": "custom-value"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, idempotent_after_first_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, single_item_enum_becomes_const) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "single-value" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "single-value"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     embedded_draft_4_resource_also_upgraded_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_with_sibling_keywords_prefixed_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "type": "string",
        "minLength": 3
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/$defs/foo",
        "x-type": "string",
        "x-minLength": 3
      }
    }
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}
