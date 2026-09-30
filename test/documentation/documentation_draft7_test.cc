#include "documentation_test_utils.h"

TEST(draft7_dialect_is_the_language) {
  EXPECT_DOCUMENTATION(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON",
                       R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Schema",
    "language": "http://json-schema.org/draft-07/schema#",
    "root": { "kind": "string" }
  })JSON");
}

TEST(draft7_list_items_and_additional_items) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "items": [ { "type": "string" } ],
    "additionalItems": { "type": "integer" }
  })JSON",
                            R"JSON({
    "kind": "array",
    "slots": [ { "kind": "string" } ],
    "item": { "kind": "integer" }
  })JSON");
}

TEST(draft7_dependencies_become_conditions) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "dependencies": { "card": [ "expiry" ] }
  })JSON",
                            R"JSON({
    "kind": "object",
    "conditions": [
      {
        "when": {
          "kind": "object",
          "fields": [ { "name": "card", "required": true } ]
        },
        "then": {
          "kind": "object",
          "fields": [ { "name": "expiry", "required": true } ]
        }
      }
    ]
  })JSON");
}

TEST(draft7_prefix_items_is_not_a_keyword) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "array",
    "prefixItems": [ { "type": "string" } ]
  })JSON",
                            R"JSON({ "kind": "array" })JSON");
}

TEST(draft7_a_reference_stands_alone) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": { "name": { "type": "string" } },
    "$ref": "#/definitions/name",
    "type": "integer"
  })JSON",
                            R"JSON({
    "kind": "ref",
    "ref": "/definitions/name"
  })JSON");
}

TEST(draft7_unevaluated_properties_is_not_a_keyword) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "unevaluatedProperties": false
  })JSON",
                            R"JSON({ "kind": "object" })JSON");
}

TEST(draft4_exclusive_bounds_are_flags) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1,
    "exclusiveMinimum": true
  })JSON",
                            R"JSON({
    "kind": "integer",
    "range": { "min": 1, "minExclusive": true }
  })JSON");
}

TEST(draft4_an_exclusive_bound_without_its_bound_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "exclusiveMinimum": true
  })JSON",
      "The `exclusiveMinimum` keyword needs a `minimum` in draft 4");
}

TEST(draft4_has_no_const) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "const": 3
  })JSON",
                            R"JSON({ "kind": "any" })JSON");
}

TEST(draft6_has_const) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "const": 3
  })JSON",
                            R"JSON({ "kind": "enum", "values": [ 3 ] })JSON");
}

TEST(draft3_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON",
      "This module describes JSON Schema draft 4, 6 and 7, 2019-09 and "
      "2020-12, and not hyper-schema");
}

TEST(draft7_a_dialect_address_without_a_fragment_is_read) {
  EXPECT_DOCUMENTATION(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema",
    "type": "string"
  })JSON",
                       R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Schema",
    "language": "http://json-schema.org/draft-07/schema",
    "root": { "kind": "string" }
  })JSON");
}

TEST(draft7_keywords_of_later_dialects_are_skipped) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependentRequired": { "a": [ "b" ] },
    "minContains": 2
  })JSON",
                            R"JSON({ "kind": "any" })JSON");
}
