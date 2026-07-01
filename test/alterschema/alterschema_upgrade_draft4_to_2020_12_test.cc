#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2020_12(document, expected);
}

TEST(false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2020_12(document, expected);
}

TEST(trivial_root) {
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

TEST(id_to_dollar_id_and_exclusive_minimum_lifted) {
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

TEST(items_array_to_prefix_items) {
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

TEST(ref_into_items_array_rewritten) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(idempotent_after_first_pass) {
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

TEST(no_dollar_schema_with_default_dialect_draft4) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/test",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/test",
    "type": "integer"
  })JSON");

  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "http://json-schema.org/draft-04/schema#");
}

TEST(no_dollar_schema_no_actionable_content_with_default_dialect_draft4) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "http://json-schema.org/draft-04/schema#");
}

TEST(true_boolean_schema_unchanged_with_default_dialect_draft4) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "http://json-schema.org/draft-04/schema#");
}

TEST(false_boolean_schema_unchanged_with_default_dialect_draft4) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "http://json-schema.org/draft-04/schema#");
}

TEST(metaschema_cascade_from_draft4_emits_2020_12_vocabulary) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/my-dialect",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/my-dialect",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
      "https://json-schema.org/draft/2020-12/vocab/validation": true,
      "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
      "https://json-schema.org/draft/2020-12/vocab/format-annotation": false,
      "https://json-schema.org/draft/2020-12/vocab/content": true
    },
    "type": "object"
  })JSON");

  UPGRADE_2020_12_AS_METASCHEMA(document, expected);
}
