#include "documentation_test_utils.h"

TEST(2020_12_no_dialect_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({ "type": "string" })JSON",
      "The schema does not say which dialect it is written in", "", "");
}

TEST(2020_12_a_dialect_that_cannot_be_read_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://example.com/a-dialect-nobody-has",
    "type": "string"
  })JSON",
      "The schema could not be read",
      "Could not resolve the metaschema of the schema", "");
}

TEST(2020_12_a_reference_that_lands_nowhere_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/order",
    "$ref": "#/$defs/missing"
  })JSON",
      "This keyword names a place in this schema that does not resolve", "$ref",
      "");
}

TEST(2020_12_a_reference_to_something_that_is_not_a_schema_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "x",
    "$ref": "#/title"
  })JSON",
      "This keyword names something that is not a schema", "$ref", "");
}

TEST(2020_12_unevaluated_items_beside_a_branch_that_looks_at_items_is_refused) {
  // Which entries count as looked at depends on which branch matched, and the
  // format has no way to say a rule holds only after the branch that matched.
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "list": {
      "anyOf": [ { "prefixItems": [ true ] }, { "prefixItems": [ true, true ] } ],
      "unevaluatedItems": false
    } }
  })JSON",
      "This keyword beside a part that only sometimes applies, and looks at "
      "entries, depends on which part matched, which the format cannot state "
      "exactly",
      "unevaluatedItems", "/properties/list");
}

TEST(draft7_a_reference_into_this_schema_that_lands_nowhere_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": { "a": { "$ref": "#/definitions/nope" } }
  })JSON",
      "This keyword names a place in this schema that does not resolve", "$ref",
      "/properties/a");
}

TEST(2020_12_a_reference_to_where_subschemas_are_kept_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "a": { "$ref": "#/properties" } }
  })JSON",
      "This keyword names something that is not a schema", "$ref",
      "/properties/a");
}
