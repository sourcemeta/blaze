#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_2019_09_to_2020_12, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, already_2020_12_unchanged) {
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

TEST(AlterSchema_upgrade_2019_09_to_2020_12, schema_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     schema_bumped_keeps_other_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "minLength": 1
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 1
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     custom_prefixItems_keyword_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "prefixItems": "i-was-custom-in-2019-09"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-prefixItems": "i-was-custom-in-2019-09"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     custom_dynamic_anchor_keyword_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$dynamicAnchor": "i-was-custom"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-$dynamicAnchor": "i-was-custom"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     recursive_anchor_true_at_root_with_recursive_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "type": "object",
    "additionalProperties": { "$recursiveRef": "#" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "meta",
    "type": "object",
    "additionalProperties": { "$dynamicRef": "#meta" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, recursive_anchor_false_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": false,
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     recursive_ref_with_no_recursive_anchor_keeps_static_fallback) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "additionalProperties": { "$recursiveRef": "#" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": { "$dynamicRef": "#" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     recursive_anchor_in_embedded_resource_does_not_affect_outer) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/outer",
    "type": "object",
    "additionalProperties": { "$recursiveRef": "#" },
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner",
        "$recursiveAnchor": true,
        "type": "object",
        "additionalProperties": { "$recursiveRef": "#" }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/outer",
    "type": "object",
    "additionalProperties": { "$dynamicRef": "#" },
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner",
        "$dynamicAnchor": "meta",
        "type": "object",
        "additionalProperties": { "$dynamicRef": "#meta" }
      }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     recursive_anchor_deeply_nested_renamed_anyway) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "child": {
        "$recursiveAnchor": true,
        "type": "string"
      }
    },
    "additionalProperties": { "$recursiveRef": "#" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "child": {
        "$dynamicAnchor": "meta",
        "type": "string"
      }
    },
    "additionalProperties": { "$dynamicRef": "#meta" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, items_array_to_prefix_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     items_array_with_additional_items_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_upgrade_2019_09_to_2020_12, empty_items_array_alone_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": []
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     empty_items_array_with_additional_items_collapses_to_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [],
    "additionalItems": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, items_schema_alone_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     items_schema_with_stray_additional_items_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": { "type": "string" },
    "additionalItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     ref_into_items_array_rewritten_to_prefix_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" } ],
    "$defs": {
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

TEST(AlterSchema_upgrade_2019_09_to_2020_12, anchor_with_colon_sanitized) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "x": { "$anchor": "ns:thing", "type": "string" },
      "y": { "$ref": "#ns:thing" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "x": { "$anchor": "ns-thing", "type": "string" },
      "y": { "$ref": "#ns-thing" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     anchor_collision_after_sanitization_double_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "a": { "$anchor": "ns:foo" },
      "b": { "$anchor": "ns-foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$anchor": "x-ns-foo" },
      "b": { "$anchor": "ns-foo" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     anchor_referenced_via_full_uri_rewritten) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/root",
    "$defs": {
      "x": { "$anchor": "ns:thing", "type": "string" },
      "y": { "$ref": "https://example.com/root#ns:thing" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$defs": {
      "x": { "$anchor": "ns-thing", "type": "string" },
      "y": { "$ref": "https://example.com/root#ns-thing" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_without_unevaluated_items_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_wrapped_into_top_level_not) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "not": { "not": { "contains": { "type": "string" } } }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_with_min_max_keeps_them_inside_wrapper) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 2,
    "maxContains": 5,
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "not": {
      "not": {
        "contains": { "type": "string" },
        "minContains": 2,
        "maxContains": 5
      }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_with_existing_not_uses_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false,
    "not": { "type": "null" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "not": { "type": "null" },
    "allOf": [
      { "not": { "not": { "contains": { "type": "string" } } } }
    ]
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_with_existing_allof_but_no_not_uses_top_level_not) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false,
    "allOf": [ { "type": "array" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "allOf": [ { "type": "array" } ],
    "not": { "not": { "contains": { "type": "string" } } }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_with_existing_not_and_allof_appends_to_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false,
    "not": { "type": "null" },
    "allOf": [ { "type": "array" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "not": { "type": "null" },
    "allOf": [
      { "type": "array" },
      { "not": { "not": { "contains": { "type": "string" } } } }
    ]
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     contains_inside_anyof_each_branch_wrapped_independently) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": false,
    "anyOf": [
      { "type": "array", "contains": { "type": "string" } },
      { "type": "array", "contains": { "type": "integer" } }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "anyOf": [
      {
        "type": "array",
        "not": { "not": { "contains": { "type": "string" } } }
      },
      {
        "type": "array",
        "not": { "not": { "contains": { "type": "integer" } } }
      }
    ]
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(
    AlterSchema_upgrade_2019_09_to_2020_12,
    contains_alongside_unevaluated_items_preserves_2019_09_conservative_reading) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "not": { "not": { "contains": { "type": "string" } } }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     custom_dynamic_ref_with_collision_double_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$dynamicRef": "original",
    "x-$dynamicRef": "already-prefixed"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-x-$dynamicRef": "original",
    "x-$dynamicRef": "already-prefixed"
  })JSON");

  UPGRADE_2020_12(document, expected);
}
