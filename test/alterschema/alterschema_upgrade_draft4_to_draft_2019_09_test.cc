#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft4_to_2019_09, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     id_renamed_definitions_to_defs_dependencies_split) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "ref-to-foo": { "$ref": "#/definitions/foo" }
    },
    "dependencies": {
      "alpha": { "type": "object" },
      "beta": [ "gamma" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$defs": {
      "foo": { "type": "string" }
    },
    "properties": {
      "ref-to-foo": { "$ref": "#/$defs/foo" }
    },
    "dependentSchemas": {
      "alpha": { "type": "object" }
    },
    "dependentRequired": {
      "beta": [ "gamma" ]
    }
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(
    AlterSchema_upgrade_Draft4_to_2019_09,
    boolean_exclusive_minimum_folded_then_definitions_renamed_then_dependencies_split) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 3,
    "exclusiveMinimum": true,
    "definitions": {
      "foo": { "type": "string" }
    },
    "dependencies": {
      "alpha": [ "beta" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3,
    "$defs": {
      "foo": { "type": "string" }
    },
    "dependentRequired": {
      "alpha": [ "beta" ]
    }
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     id_with_fragment_anchor_split_after_id_promoted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "#tag"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "tag"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09, idempotent_after_first_pass) {
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     embedded_draft_4_inside_outer_draft_4_both_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     mixed_chain_with_promoted_keyword_prefixing) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "const": "draft6-promoted",
    "if": "draft7-promoted",
    "$anchor": "twentynineteen-promoted"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-const": "draft6-promoted",
    "x-if": "draft7-promoted",
    "x-$anchor": "twentynineteen-promoted"
  })JSON");

  UPGRADE_DRAFT_2019_09(document, expected);
}
