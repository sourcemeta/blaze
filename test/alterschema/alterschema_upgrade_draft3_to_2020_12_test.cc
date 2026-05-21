#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft3_to_2020_12, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_2020_12,
     items_array_promoted_to_prefixItems_via_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array",
    "items": [ { "type": "string" }, { "type": "number" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [ { "type": "string" }, { "type": "number" } ]
  })JSON");

  UPGRADE_2020_12(document, expected);
}

TEST(AlterSchema_upgrade_Draft3_to_2020_12,
     format_host_name_and_ip_address_renamed) {
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
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "host": { "type": "string", "format": "hostname" },
      "ip": { "type": "string", "format": "ipv4" },
      "custom": { "type": "string", "format": "my-acme-format" }
    }
  })JSON");

  UPGRADE_2020_12(document, expected);
}
