#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

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
    "not": { "not": { "contains": { "type": "string" } } },
    "unevaluatedItems": false
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
    "not": {
      "not": {
        "contains": { "type": "string" },
        "minContains": 2,
        "maxContains": 5
      }
    },
    "unevaluatedItems": false
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     ref_into_contains_rewritten_after_wrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false,
    "$defs": {
      "alias": { "$ref": "#/contains" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "not": {
      "not": {
        "contains": { "type": "string" }
      }
    },
    "unevaluatedItems": false,
    "$defs": {
      "alias": { "$ref": "#/not/not/contains" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     ref_into_contains_with_existing_not_rewritten_via_allof) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "unevaluatedItems": false,
    "not": { "type": "null" },
    "$defs": {
      "alias": { "$ref": "#/contains" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "unevaluatedItems": false,
    "not": { "type": "null" },
    "$defs": {
      "alias": { "$ref": "#/allOf/0/not/not/contains" }
    },
    "allOf": [
      {
        "not": {
          "not": { "contains": { "type": "string" } }
        }
      }
    ]
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
    "not": { "not": { "contains": { "type": "string" } } },
    "unevaluatedItems": false,
    "allOf": [ { "type": "array" } ]
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
    "not": { "not": { "contains": { "type": "string" } } },
    "unevaluatedItems": false
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

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     no_dollar_schema_with_default_dialect_2019_09) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/test",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "id": "https://example.com/test",
    "type": "integer"
  })JSON");

  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "https://json-schema.org/draft/2019-09/schema");
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     no_dollar_schema_with_default_dialect_2019_09_with_recursive_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$recursiveAnchor": true,
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "meta",
    "type": "object"
  })JSON");

  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "https://json-schema.org/draft/2019-09/schema");
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     no_dollar_schema_no_actionable_content_with_default_dialect_2019_09) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "https://json-schema.org/draft/2019-09/schema");
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     true_boolean_schema_unchanged_with_default_dialect_2019_09) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "https://json-schema.org/draft/2019-09/schema");
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     false_boolean_schema_unchanged_with_default_dialect_2019_09) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2020_12_WITH_DIALECT(document, expected,
                               "https://json-schema.org/draft/2019-09/schema");
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, format_values_preserved) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "a": { "type": "string", "format": "hostname" },
      "b": { "type": "string", "format": "ipv4" },
      "c": { "type": "string", "format": "ipv6" },
      "d": { "type": "string", "format": "email" },
      "e": { "type": "string", "format": "uri" },
      "f": { "type": "string", "format": "date-time" },
      "g": { "type": "string", "format": "uri-reference" },
      "h": { "type": "string", "format": "uri-template" },
      "i": { "type": "string", "format": "json-pointer" },
      "j": { "type": "string", "format": "date" },
      "k": { "type": "string", "format": "time" },
      "l": { "type": "string", "format": "regex" },
      "m": { "type": "string", "format": "idn-email" },
      "n": { "type": "string", "format": "idn-hostname" },
      "o": { "type": "string", "format": "iri" },
      "p": { "type": "string", "format": "iri-reference" },
      "q": { "type": "string", "format": "relative-json-pointer" },
      "r": { "type": "string", "format": "duration" },
      "s": { "type": "string", "format": "uuid" },
      "z": { "type": "string", "format": "my-acme-format" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "a": { "type": "string", "format": "hostname" },
      "b": { "type": "string", "format": "ipv4" },
      "c": { "type": "string", "format": "ipv6" },
      "d": { "type": "string", "format": "email" },
      "e": { "type": "string", "format": "uri" },
      "f": { "type": "string", "format": "date-time" },
      "g": { "type": "string", "format": "uri-reference" },
      "h": { "type": "string", "format": "uri-template" },
      "i": { "type": "string", "format": "json-pointer" },
      "j": { "type": "string", "format": "date" },
      "k": { "type": "string", "format": "time" },
      "l": { "type": "string", "format": "regex" },
      "m": { "type": "string", "format": "idn-email" },
      "n": { "type": "string", "format": "idn-hostname" },
      "o": { "type": "string", "format": "iri" },
      "p": { "type": "string", "format": "iri-reference" },
      "q": { "type": "string", "format": "relative-json-pointer" },
      "r": { "type": "string", "format": "duration" },
      "s": { "type": "string", "format": "uuid" },
      "z": { "type": "string", "format": "my-acme-format" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12, vocabulary_core_uri_rewritten) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_direct_rename_uris_rewritten) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": true,
      "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
      "https://json-schema.org/draft/2019-09/vocab/content": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/validation": true,
      "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
      "https://json-schema.org/draft/2020-12/vocab/content": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_format_maps_to_format_annotation_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/format": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/format-annotation": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_format_maps_to_format_annotation_optional) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/format": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/format-annotation": false
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_applicator_emits_applicator_and_unevaluated_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_applicator_emits_applicator_and_unevaluated_optional) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": false,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": false
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_applicator_keeps_existing_unevaluated_value) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": false
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_applicator_after_existing_unevaluated_preserves_order) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": false,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": false,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_custom_uri_passes_through_intact) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://example.com/vocab/custom-required": true,
      "https://example.com/vocab/custom-optional": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://example.com/vocab/custom-required": true,
      "https://example.com/vocab/custom-optional": false
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_hyper_schema_uri_left_intact) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema": false
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_full_official_set_and_custom) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-meta",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": true,
      "https://json-schema.org/draft/2019-09/vocab/meta-data": false,
      "https://json-schema.org/draft/2019-09/vocab/format": false,
      "https://json-schema.org/draft/2019-09/vocab/content": false,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema": false,
      "https://example.com/vocab/extra": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-meta",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
      "https://json-schema.org/draft/2020-12/vocab/validation": true,
      "https://json-schema.org/draft/2020-12/vocab/meta-data": false,
      "https://json-schema.org/draft/2020-12/vocab/format-annotation": false,
      "https://json-schema.org/draft/2020-12/vocab/content": false,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema": false,
      "https://example.com/vocab/extra": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_already_2020_12_uris_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_empty_object_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {}
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_non_object_left_untouched) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": "not-an-object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": "not-an-object"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_explicit_2020_12_wins_over_2019_09_equivalent) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": false,
      "https://json-schema.org/draft/2020-12/vocab/core": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_explicit_2020_12_wins_over_2019_09_equivalent_reversed_order) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/core": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_explicit_2020_12_applicator_wins_no_inline_unevaluated) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/applicator": false,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_explicit_2020_12_format_annotation_wins_over_2019_09_format) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/format": true,
      "https://json-schema.org/draft/2020-12/vocab/format-annotation": false
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/format-annotation": false
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_2019_09_to_2020_12,
     vocabulary_inside_embedded_meta_schema_rewritten) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/outer",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner-meta",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true,
          "https://json-schema.org/draft/2019-09/vocab/applicator": true
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/outer",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "inner": {
        "$id": "https://example.com/inner-meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true,
          "https://json-schema.org/draft/2020-12/vocab/unevaluated": true
        }
      }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}
