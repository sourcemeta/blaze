#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "frame_test_utils.h"

#include <vector> // std::vector

TEST(instance_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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
    "dependencies": {
      "foo": [ "bar" ],
      "baz": { "type": "string" }
    },
    "propertyNames": { "minLength": 1 },
    "contains": { "type": "number" },
    "additionalItems": { "minimum": 2 },
    "items": { "items": [ true, false ] },
    "definitions": { "foo": true }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 22);

  EXPECT_WALKER_ENTRY_DRAFT7(entries, 0, "", std::nullopt);

  // Applicators (any)
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 1, "/allOf/0", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 2, "/allOf/1", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 3, "/anyOf/0", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 4, "/oneOf/0", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 5, "/if", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 6, "/then", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 7, "/else", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 8, "/not", "");

  // Applicators (object)
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 9, "/properties/foo", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 10, "/properties/bar", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 11, "/additionalProperties", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 12, "/patternProperties/^f", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 13, "/patternProperties/x$", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 14, "/dependencies/baz", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 15, "/propertyNames", "");

  // Applicators (array)
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 16, "/contains", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 17, "/additionalItems", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 18, "/items", "");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 19, "/items/items/0", "/items");
  EXPECT_WALKER_ENTRY_DRAFT7(entries, 20, "/items/items/1", "/items");

  // Core
  EXPECT_WALKER_ENTRY_DRAFT7_ORPHAN(entries, 21, "/definitions/foo", "");
}

TEST(definitions_subschemas) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
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

  EXPECT_WALKER_ENTRY_DRAFT7(entries, 0, "", std::nullopt);
  EXPECT_WALKER_ENTRY_DRAFT7_ORPHAN(entries, 1, "/definitions/foo", "");
  EXPECT_WALKER_ENTRY_DRAFT7_ORPHAN(
      entries, 2, "/definitions/foo/properties/bar", "/definitions/foo");
  EXPECT_WALKER_ENTRY_DRAFT7_ORPHAN(
      entries, 3, "/definitions/foo/properties/bar/additionalProperties",
      "/definitions/foo/properties/bar");
}
