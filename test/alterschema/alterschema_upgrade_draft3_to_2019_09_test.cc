#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(definitions_renamed_via_definitions_to_defs_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "Reusable": { "type": "string" }
    },
    "extends": { "$ref": "#/definitions/Reusable" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "Reusable": { "type": "string" }
    },
    "allOf": [ { "$ref": "#/$defs/Reusable" } ]
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(format_host_name_and_ip_address_renamed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "host": { "type": "string", "format": "host-name" },
      "ip": { "type": "string", "format": "ip-address" },
      "custom": { "type": "string", "format": "my-acme-format" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "host": { "type": "string", "format": "hostname" },
      "ip": { "type": "string", "format": "ipv4" },
      "custom": { "type": "string", "format": "my-acme-format" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(metaschema_cascade_from_draft3_emits_2019_09_vocabulary) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/my-dialect",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/my-dialect",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": true,
      "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
      "https://json-schema.org/draft/2019-09/vocab/format": false,
      "https://json-schema.org/draft/2019-09/vocab/content": true
    },
    "type": "object"
  })JSON");

  UPGRADE_2019_09_AS_METASCHEMA(document, expected);
}
