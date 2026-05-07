#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft3_to_Draft6, trivial_root_promotes_two_drafts) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft6, full_pipeline_combined) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/root",
    "type": "object",
    "properties": {
      "name": { "type": "string", "required": true },
      "age": { "type": "number", "minimum": 0, "exclusiveMinimum": true }
    },
    "extends": { "type": "object" },
    "divisibleBy": 1,
    "dependencies": { "name": "age" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/root",
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number", "exclusiveMinimum": 0 }
    },
    "multipleOf": 1,
    "dependencies": { "name": ["age"] },
    "allOf": [ { "type": "object" } ],
    "required": ["name"]
  })JSON");

  UPGRADE_DRAFT_6(document, expected);
}
