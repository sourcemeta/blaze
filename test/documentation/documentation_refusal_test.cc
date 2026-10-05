#include "documentation_test_utils.h"

TEST(2020_12_no_dialect_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({ "type": "string" })JSON",
      "The schema does not say which dialect it is written in", "", "");
}

TEST(2020_12_unevaluated_properties_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "unevaluatedProperties": false
  })JSON",
      "This keyword depends on what the rest of the schema happened to "
      "describe, which the format cannot state exactly",
      "unevaluatedProperties", "");
}

TEST(2020_12_dynamic_reference_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/tree",
    "$dynamicAnchor": "node",
    "properties": { "child": { "$dynamicRef": "#node" } }
  })JSON",
      "This keyword names a place that depends on where it is used, which the "
      "format cannot state exactly",
      "$dynamicRef", "/properties/child");
}

TEST(2020_12_a_type_that_is_not_a_json_type_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "text"
  })JSON",
      "The `type` keyword names something that is not a JSON type", "text", "");
}

TEST(2020_12_a_repeated_type_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "string" ]
  })JSON",
      "The `type` keyword names a type twice", "string", "");
}

TEST(2020_12_a_repeated_required_name_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "a", "a" ]
  })JSON",
      "The `required` keyword names this property twice", "a", "");
}

TEST(2020_12_a_negative_count_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": -1
  })JSON",
      "This keyword must be a count", "minLength", "");
}

TEST(2020_12_a_list_items_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": [ { "type": "string" } ]
  })JSON",
      "The `items` keyword must be a schema in 2020-12, not a list", "", "");
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
      "The `$ref` keyword names a place in this schema that does not resolve",
      "", "");
}

TEST(2020_12_a_reference_to_something_that_is_not_a_schema_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "x",
    "$ref": "#/title"
  })JSON",
      "The `$ref` keyword names something that is not a schema", "", "");
}

TEST(2020_12_a_step_of_zero_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 0
  })JSON",
      "The `multipleOf` keyword must be a number above zero", "", "");
}

TEST(2020_12_a_bound_past_what_json_holds_exactly_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 99999999999999999999
  })JSON",
      "This keyword is past the numbers JSON holds exactly, so the format "
      "cannot state it",
      "maximum", "");
}

TEST(2020_12_a_resource_of_another_dialect_is_refused) {
  // `prefixItems` is not a keyword in Draft 7, so reading this resource as
  // 2020-12 would state a rule the schema does not have.
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "type": "object",
    "properties": {
      "inner": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "array",
        "prefixItems": [ { "type": "string" } ]
      }
    }
  })JSON",
      "This resource is written in a different dialect from the rest of the "
      "schema, which the format cannot state exactly",
      "", "/properties/inner");
}
