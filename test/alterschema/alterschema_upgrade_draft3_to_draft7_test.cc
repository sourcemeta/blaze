#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft3_to_Draft7, trivial_root_promotes_three_drafts) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_Draft7, full_pipeline_combined) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "required": true }
    },
    "extends": { "type": "object" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "required": [ "name" ],
    "properties": {
      "name": { "type": "string" }
    },
    "allOf": [ { "type": "object" } ]
  })JSON");

  UPGRADE_DRAFT_7(document, expected);
}
