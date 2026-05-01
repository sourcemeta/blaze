#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft4_to_2020_12, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2020_12, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2020_12, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2020_12,
     id_to_dollar_id_and_exclusive_minimum_lifted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/root",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "type": "number",
    "exclusiveMinimum": 0
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2020_12, items_array_to_prefix_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": [ { "type": "string" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" } ]
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2020_12, idempotent_after_first_pass) {
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
