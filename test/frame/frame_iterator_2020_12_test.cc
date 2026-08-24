#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "frame_test_utils.h"

#include <vector> // std::vector

TEST(instance_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "type": "string" }, { "minLength": 3 } ],
    "anyOf": [ { "type": "string" } ],
    "oneOf": [ { "type": "string" } ],
    "if": { "const": "foo" },
    "then": true,
    "else": { "maxLength": 10 },
    "not": { "const": "bar" },
    "properties": {
      "foo": { "type": "string" },
      "bar": false
    },
    "additionalProperties": { "type": "number" },
    "patternProperties": {
      "^f": { "type": "integer" },
      "x$": true
    },
    "dependentSchemas": {
      "foo": { "minProperties": 1 },
      "bar": { "maxProperties": 10 }
    },
    "propertyNames": { "minLength": 1 },
    "contains": { "type": "number" },
    "items": { "minimum": 2 },
    "prefixItems": [ true, false ],
    "unevaluatedProperties": { "type": "number" },
    "unevaluatedItems": { "minimum": 2 },
    "contentSchema": { "type": "string" },
    "$defs": {
      "foo": {
        "properties": {
          "bar": { "type": "string" }
        }
      }
    },
    "definitions": { "foo": true }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 27);

  EXPECT_WALKER_ENTRY_2020_12(entries, 0, "", std::nullopt);

  // Applicator vocabulary (any)
  EXPECT_WALKER_ENTRY_2020_12(entries, 1, "/allOf/0", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 2, "/allOf/1", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 3, "/anyOf/0", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 4, "/oneOf/0", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 5, "/if", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 6, "/then", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 7, "/else", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 8, "/not", "");

  // Applicator vocabulary (object)
  EXPECT_WALKER_ENTRY_2020_12(entries, 9, "/properties/foo", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 10, "/properties/bar", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 11, "/additionalProperties", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 12, "/patternProperties/^f", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 13, "/patternProperties/x$", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 14, "/dependentSchemas/foo", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 15, "/dependentSchemas/bar", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 16, "/propertyNames", "");

  // Applicator vocabulary (array)
  EXPECT_WALKER_ENTRY_2020_12(entries, 17, "/contains", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 18, "/items", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 19, "/prefixItems/0", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 20, "/prefixItems/1", "");

  // Unevaluated vocabulary
  EXPECT_WALKER_ENTRY_2020_12(entries, 21, "/unevaluatedProperties", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 22, "/unevaluatedItems", "");

  // Content vocabulary
  EXPECT_WALKER_ENTRY_2020_12(entries, 23, "/contentSchema", "");

  // Core vocabulary
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(entries, 24, "/$defs/foo", "");
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(entries, 25, "/$defs/foo/properties/bar",
                                     "/$defs/foo");
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(entries, 26, "/definitions/foo", "");
}

TEST(instance_locations_nested) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": {
      "properties": {
        "foo": {
          "allOf": [
            { "type": "string" }
          ]
        }
      }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 4);

  EXPECT_WALKER_ENTRY_2020_12(entries, 0, "", std::nullopt);
  EXPECT_WALKER_ENTRY_2020_12(entries, 1, "/additionalProperties", "");
  EXPECT_WALKER_ENTRY_2020_12(entries, 2,
                              "/additionalProperties/properties/foo",
                              "/additionalProperties");
  EXPECT_WALKER_ENTRY_2020_12(entries, 3,
                              "/additionalProperties/properties/foo/allOf/0",
                              "/additionalProperties/properties/foo");
}

TEST(instance_locations_defs_with_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "common",
      "allOf": [ { "$ref": "#foo" } ],
      "$defs": {
        "foo": {
          "$anchor": "foo"
        }
      }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 3);

  EXPECT_WALKER_ENTRY_2020_12(entries, 0, "", std::nullopt);
  EXPECT_WALKER_ENTRY_2020_12(entries, 1, "/allOf/0", "");
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(entries, 2, "/$defs/foo", "");
}

TEST(definitions_subschemas) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "properties": {
          "bar": {
            "additionalProperties": {
              "type": "string"
            }
          }
        }
      }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 4);

  EXPECT_WALKER_ENTRY_2020_12(entries, 0, "", std::nullopt);
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(entries, 1, "/$defs/foo", "");
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(entries, 2, "/$defs/foo/properties/bar",
                                     "/$defs/foo");
  EXPECT_WALKER_ENTRY_2020_12_ORPHAN(
      entries, 3, "/$defs/foo/properties/bar/additionalProperties",
      "/$defs/foo/properties/bar");
}
