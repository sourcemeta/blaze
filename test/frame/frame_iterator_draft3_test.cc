#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "frame_test_utils.h"

#include <vector> // std::vector

TEST(instance_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
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
    "additionalItems": { "minimum": 2 },
    "items": { "items": [ true, false ] },
    "type": [ "string", { "type": "number" }, { "type": "integer" } ],
    "disallow": [ "boolean", { "type": "string" }, { "type": "integer" } ],
    "extends": {
      "extends": [ { "type": "string" } ]
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 17);

  EXPECT_WALKER_ENTRY_DRAFT3(entries, 0, "", std::nullopt);

  // Applicators (object)
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 1, "/properties/foo", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 2, "/properties/bar", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 3, "/additionalProperties", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 4, "/patternProperties/^f", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 5, "/patternProperties/x$", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 6, "/dependencies/baz", "");

  // Applicators (array)
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 7, "/additionalItems", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 8, "/items", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 9, "/items/items/0", "/items");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 10, "/items/items/1", "/items");

  // Applicators (any)
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 11, "/type/1", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 12, "/type/2", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 13, "/disallow/1", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 14, "/disallow/2", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 15, "/extends", "");
  EXPECT_WALKER_ENTRY_DRAFT3(entries, 16, "/extends/extends/0", "/extends");
}
