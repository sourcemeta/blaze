#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "frame_test_utils.h"

#include <vector> // std::vector

TEST(instance_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "properties": {
      "foo": {
        "type": "string",
        "requires": { "type": "object" }
      },
      "bar": false
    },
    "additionalProperties": { "type": "number" },
    "items": { "items": [ { "type": "string" }, { "type": "integer" } ] },
    "type": [ "string", { "type": "number" }, { "type": "integer" } ],
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

  EXPECT_EQ(entries.size(), 12);

  EXPECT_WALKER_ENTRY_DRAFT1(entries, 0, "", std::nullopt);

  // Applicators (object)
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 1, "/properties/foo", "");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 2, "/properties/foo/requires",
                             "/properties/foo");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 3, "/properties/bar", "");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 4, "/additionalProperties", "");

  // Applicators (array)
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 5, "/items", "");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 6, "/items/items/0", "/items");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 7, "/items/items/1", "/items");

  // Applicators (any)
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 8, "/type/1", "");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 9, "/type/2", "");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 10, "/extends", "");
  EXPECT_WALKER_ENTRY_DRAFT1(entries, 11, "/extends/extends/0", "/extends");
}
