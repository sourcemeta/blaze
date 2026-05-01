#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft6_to_2020_12, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2020_12, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2020_12, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2020_12, ref_into_items_array_rewritten) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": [ { "type": "string" } ],
    "definitions": {
      "alias": { "$ref": "#/items/0" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" } ],
    "$defs": {
      "alias": { "$ref": "#/prefixItems/0" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2020_12, items_array_with_additional_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": [ { "type": "string" } ],
    "additionalItems": { "type": "integer" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" } ],
    "items": { "type": "integer" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2020_12,
     contains_unchanged_when_no_unevaluated_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "contains": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2020_12, idempotent_on_2020_12) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_2020_12(document, expected);
}
