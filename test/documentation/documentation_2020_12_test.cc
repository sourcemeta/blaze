#include "documentation_test_utils.h"

TEST(2020_12_string) {
  EXPECT_DOCUMENTATION(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "A name",
    "description": "What someone is called",
    "type": "string"
  })JSON",
                       R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "A name",
    "description": "What someone is called",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": { "kind": "string" }
  })JSON");
}

TEST(2020_12_string_facts) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "format": "email",
    "pattern": "^a",
    "minLength": 2,
    "maxLength": 8
  })JSON",
                            R"JSON({
    "kind": "string",
    "format": "email",
    "pattern": "^a",
    "length": { "min": 2, "max": 8 }
  })JSON");
}

TEST(2020_12_integer_range) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 1,
    "exclusiveMaximum": 10,
    "multipleOf": 2
  })JSON",
                            R"JSON({
    "kind": "integer",
    "range": { "min": 1, "max": 10, "maxExclusive": true },
    "multipleOf": 2
  })JSON");
}

TEST(2020_12_object_fields) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "id": { "type": "string" },
      "count": { "type": "integer" }
    },
    "required": [ "id" ],
    "additionalProperties": false
  })JSON",
                            R"JSON({
    "kind": "object",
    "fields": [
      { "name": "id", "required": true, "value": { "kind": "string" } },
      { "name": "count", "value": { "kind": "integer" } }
    ],
    "closed": true
  })JSON");
}

TEST(2020_12_object_required_without_a_description) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "id" ]
  })JSON",
                            R"JSON({
    "kind": "object",
    "fields": [ { "name": "id", "required": true } ]
  })JSON");
}

TEST(2020_12_object_other_fields) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": { "^x-": { "type": "string" } },
    "additionalProperties": { "type": "integer" },
    "propertyNames": { "pattern": "^[a-z]" },
    "minProperties": 1,
    "maxProperties": 4
  })JSON",
                            R"JSON({
    "kind": "object",
    "patternFields": [ { "pattern": "^x-", "value": { "kind": "string" } } ],
    "otherFields": { "kind": "integer" },
    "keys": { "kind": "string", "pattern": "^[a-z]", "otherTypesAllowed": true },
    "fieldCount": { "min": 1, "max": 4 }
  })JSON");
}

TEST(2020_12_array) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "minItems": 1,
    "uniqueItems": true
  })JSON",
                            R"JSON({
    "kind": "array",
    "item": { "kind": "string" },
    "length": { "min": 1 },
    "unique": true
  })JSON");
}

TEST(2020_12_array_slots_and_contains) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [ { "type": "string" }, { "type": "integer" } ],
    "items": false,
    "contains": { "type": "string" },
    "minContains": 2
  })JSON",
                            R"JSON({
    "kind": "array",
    "slots": [ { "kind": "string" }, { "kind": "integer" } ],
    "item": { "kind": "never" },
    "contains": { "value": { "kind": "string" }, "min": 2 }
  })JSON");
}

TEST(2020_12_enumeration) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "wide", "tall" ]
  })JSON",
                            R"JSON({
    "kind": "enum",
    "values": [ "wide", "tall" ]
  })JSON");
}

TEST(2020_12_constant) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 3
  })JSON",
                            R"JSON({
    "kind": "enum",
    "values": [ 3 ]
  })JSON");
}

TEST(2020_12_type_list) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "integer" ]
  })JSON",
                            R"JSON({
    "kind": "choice",
    "options": [ { "kind": "string" }, { "kind": "integer" } ]
  })JSON");
}

TEST(2020_12_type_list_with_null) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "null" ]
  })JSON",
                            R"JSON({
    "kind": "string",
    "nullable": true
  })JSON");
}

TEST(2020_12_no_type_allows_other_types) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minLength": 2
  })JSON",
                            R"JSON({
    "kind": "string",
    "length": { "min": 2 },
    "otherTypesAllowed": true
  })JSON");
}

TEST(2020_12_one_of) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON",
                            R"JSON({
    "kind": "any",
    "also": [
      {
        "kind": "choice",
        "options": [ { "kind": "string" }, { "kind": "integer" } ]
      }
    ]
  })JSON");
}

TEST(2020_12_any_of_overlaps) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON",
                            R"JSON({
    "kind": "any",
    "also": [
      {
        "kind": "choice",
        "options": [ { "kind": "string" }, { "kind": "integer" } ],
        "overlap": true
      }
    ]
  })JSON");
}

TEST(2020_12_any_of_with_a_null_branch) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "type": "null" }, { "type": "string" } ]
  })JSON",
                            R"JSON({
    "kind": "any",
    "nullable": true,
    "also": [ { "kind": "string" } ]
  })JSON");
}

TEST(2020_12_all_of_each_member_holds) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "properties": { "a": { "type": "string" } } },
      { "required": [ "b" ] }
    ]
  })JSON",
                            R"JSON({
    "kind": "object",
    "also": [
      {
        "kind": "object",
        "fields": [ { "name": "a", "value": { "kind": "string" } } ],
        "otherTypesAllowed": true
      },
      {
        "kind": "object",
        "fields": [ { "name": "b", "required": true } ],
        "otherTypesAllowed": true
      }
    ]
  })JSON");
}

TEST(2020_12_not) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" }
  })JSON",
                            R"JSON({
    "kind": "any",
    "not": { "kind": "string" }
  })JSON");
}

TEST(2020_12_two_prohibitions_become_one) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" },
    "allOf": [ { "not": { "type": "integer" } } ]
  })JSON",
                            R"JSON({
    "kind": "any",
    "also": [ { "kind": "any", "not": { "kind": "integer" } } ],
    "not": { "kind": "string" }
  })JSON");
}

TEST(2020_12_condition) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "properties": { "kind": { "const": "wide" } } },
    "then": { "required": [ "width" ] }
  })JSON",
                            R"JSON({
    "kind": "object",
    "conditions": [
      {
        "when": {
          "kind": "object",
          "fields": [
            { "name": "kind", "value": { "kind": "enum", "values": [ "wide" ] } }
          ],
          "otherTypesAllowed": true
        },
        "then": {
          "kind": "object",
          "fields": [ { "name": "width", "required": true } ],
          "otherTypesAllowed": true
        }
      }
    ]
  })JSON");
}

TEST(2020_12_dependent_required) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "dependentRequired": { "card": [ "expiry" ] }
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

TEST(2020_12_reference_becomes_a_shape) {
  EXPECT_DOCUMENTATION(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Order",
    "type": "object",
    "properties": {
      "buyer": { "$ref": "#/$defs/party" },
      "seller": { "$ref": "#/$defs/party" }
    },
    "$defs": {
      "party": { "type": "object", "properties": { "name": { "type": "string" } } }
    }
  })JSON",
                       R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "buyer", "value": { "kind": "ref", "ref": "/$defs/party" } },
        { "name": "seller", "value": { "kind": "ref", "ref": "/$defs/party" } }
      ]
    },
    "shapes": [
      {
        "id": "/$defs/party",
        "name": "party",
        "value": {
          "kind": "object",
          "fields": [ { "name": "name", "value": { "kind": "string" } } ]
        }
      }
    ]
  })JSON");
}

TEST(2020_12_reference_outside_the_document) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/order",
    "$ref": "https://example.com/party"
  })JSON",
                            R"JSON({
    "kind": "external",
    "href": "https://example.com/party"
  })JSON");
}

TEST(2020_12_annotations) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "id": {
        "type": "string",
        "title": "The identifier",
        "default": "none",
        "examples": [ "abc" ],
        "deprecated": true,
        "readOnly": true
      }
    }
  })JSON",
                            R"JSON({
    "kind": "object",
    "fields": [
      {
        "name": "id",
        "value": {
          "kind": "string",
          "title": "The identifier",
          "default": "none",
          "examples": [ "abc" ],
          "deprecated": true,
          "access": "read"
        }
      }
    ]
  })JSON");
}

TEST(2020_12_boolean_schemas) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "a": true, "b": false }
  })JSON",
                            R"JSON({
    "kind": "object",
    "fields": [
      { "name": "a", "value": { "kind": "any" } },
      { "name": "b", "value": { "kind": "never" } }
    ]
  })JSON");
}

TEST(2020_12_no_dialect_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({ "type": "string" })JSON",
      "The schema does not say which dialect it is written in");
}

TEST(2020_12_unevaluated_properties_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "unevaluatedProperties": false
  })JSON",
      "The `unevaluatedProperties` keyword depends on what the rest of the "
      "schema happened to describe, which the format cannot state exactly");
}

TEST(2020_12_dynamic_reference_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/tree",
    "$dynamicAnchor": "node",
    "properties": { "child": { "$dynamicRef": "#node" } }
  })JSON",
      "The `$dynamicRef` keyword names a place that depends on where it is "
      "used, which the format cannot state exactly");
}

TEST(2020_12_a_type_that_is_not_a_json_type_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "text"
  })JSON",
      "The `type` keyword names text, which is not a JSON type");
}

TEST(2020_12_a_repeated_type_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "string" ]
  })JSON",
      "The `type` keyword names string twice");
}

TEST(2020_12_a_repeated_required_name_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "a", "a" ]
  })JSON",
      "The `required` keyword names a twice");
}

TEST(2020_12_a_negative_count_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": -1
  })JSON",
      "The `minLength` keyword must be a count");
}

TEST(2020_12_a_list_items_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": [ { "type": "string" } ]
  })JSON",
      "The `items` keyword must be a schema in 2020-12, not a list");
}

TEST(2020_12_text_that_says_nothing_is_left_out) {
  EXPECT_DOCUMENTATION(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "",
    "description": "",
    "type": "object",
    "properties": { "id": { "type": "string", "description": "" } }
  })JSON",
                       R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Schema",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [ { "name": "id", "value": { "kind": "string" } } ]
    }
  })JSON");
}

TEST(2020_12_a_dialect_that_cannot_be_read_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://example.com/a-dialect-nobody-has",
    "type": "string"
  })JSON",
      "The schema could not be read: Could not resolve the metaschema of the "
      "schema");
}

TEST(2020_12_a_shape_reached_only_from_another_shape_is_described) {
  EXPECT_DOCUMENTATION(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/A",
    "$defs": {
      "A": { "type": "object", "properties": { "b": { "$ref": "#/$defs/B" } } },
      "B": { "type": "string", "title": "Bee" }
    }
  })JSON",
                       R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Schema",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": { "kind": "ref", "ref": "/$defs/A" },
    "shapes": [
      {
        "id": "/$defs/A",
        "name": "A",
        "value": {
          "kind": "object",
          "fields": [ { "name": "b", "value": { "kind": "ref", "ref": "/$defs/B" } } ]
        }
      },
      {
        "id": "/$defs/B",
        "name": "B",
        "value": { "kind": "string", "title": "Bee" }
      }
    ]
  })JSON");
}

TEST(2020_12_enum_keeps_only_the_values_the_rest_allows) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "a", 1, null, "bb" ],
    "minLength": 2
  })JSON",
                            R"JSON({
    "kind": "enum",
    "values": [ "bb" ]
  })JSON");
}

TEST(2020_12_enum_states_what_it_cannot_decide) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ { "a": 1 } ],
    "required": [ "b" ]
  })JSON",
                            R"JSON({
    "kind": "enum",
    "values": [ { "a": 1 } ],
    "also": [
      {
        "kind": "object",
        "fields": [ { "name": "b", "required": true } ],
        "otherTypesAllowed": true
      }
    ]
  })JSON");
}

TEST(2020_12_const_and_enum_keep_only_what_both_allow) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2 ],
    "const": 3
  })JSON",
                            R"JSON({ "kind": "never" })JSON");
}

TEST(2020_12_a_number_and_a_whole_number_overlap) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "number", "integer" ]
  })JSON",
                            R"JSON({
    "kind": "choice",
    "options": [ { "kind": "number" }, { "kind": "integer" } ],
    "overlap": true
  })JSON");
}

TEST(2020_12_the_tighter_of_two_bounds_is_the_rule) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 5,
    "exclusiveMinimum": 1
  })JSON",
                            R"JSON({
    "kind": "integer",
    "range": { "min": 5 }
  })JSON");
}

TEST(2020_12_null_stays_a_form_when_something_else_can_forbid_it) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "null" ],
    "allOf": [ { "type": "string" } ]
  })JSON",
                            R"JSON({
    "kind": "choice",
    "options": [ { "kind": "string" }, { "kind": "null" } ],
    "also": [ { "kind": "string" } ]
  })JSON");
}

TEST(2020_12_a_label_with_no_type_is_about_text) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "email"
  })JSON",
                            R"JSON({
    "kind": "string",
    "format": "email",
    "otherTypesAllowed": true
  })JSON");
}

TEST(2020_12_a_reference_that_lands_nowhere_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/order",
    "$ref": "#/$defs/missing"
  })JSON",
      "The `$ref` keyword names a place in this schema that does not resolve");
}

TEST(2020_12_a_reference_to_something_that_is_not_a_schema_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "x",
    "$ref": "#/title"
  })JSON",
      "The `$ref` keyword names something that is not a schema");
}

TEST(2020_12_a_step_of_zero_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 0
  })JSON",
      "The `multipleOf` keyword must be a number above zero");
}

TEST(2020_12_read_and_write_together_say_nothing) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "readOnly": true,
    "writeOnly": true
  })JSON",
                            R"JSON({ "kind": "string" })JSON");
}

TEST(2020_12_a_default_that_is_empty_text_is_kept) {
  EXPECT_DOCUMENTATION_ROOT(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "default": ""
  })JSON",
                            R"JSON({ "kind": "string", "default": "" })JSON");
}
