#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "compiler_test_utils.h"

TEST(unevaluatedProperties_1) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "patternProperties": { "^@": true },
    "additionalProperties": true,
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 3);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/properties");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/patternProperties");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/additionalProperties");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 0);

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedProperties_2) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "patternProperties": { "^@": true },
    "additionalProperties": true,
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result,
                            "https://example.com#/unevaluatedProperties", 3);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(
      result, "https://example.com#/unevaluatedProperties", "/properties");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(
      result, "https://example.com#/unevaluatedProperties",
      "/patternProperties");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(
      result, "https://example.com#/unevaluatedProperties",
      "/additionalProperties");

  EXPECT_UNEVALUATED_DYNAMIC(result,
                             "https://example.com#/unevaluatedProperties", 0);

  EXPECT_UNEVALUATED_RESOLVED(result,
                              "https://example.com#/unevaluatedProperties");
}

TEST(unevaluatedProperties_3) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "allOf": [ { "patternProperties": { "^@": true } } ],
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/properties");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/allOf/0/patternProperties");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 0);

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedProperties_4) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": { "foo": true }
    },
    "then": {
      "properties": { "bar": true }
    },
    "anyOf": [ { "patternProperties": { "^@": true } } ],
    "dependentSchemas": {
      "foo": {
        "additionalProperties": true
      }
    },
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 0);

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 4);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/if/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/then/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/patternProperties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(
      result, "#/unevaluatedProperties",
      "/dependentSchemas/foo/additionalProperties");

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedProperties_5) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "unevaluatedProperties": false } ],
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 2);

  EXPECT_UNEVALUATED_STATIC(result, "#/allOf/0/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/allOf/0/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/allOf/0/unevaluatedProperties");

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 1);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/allOf/0/unevaluatedProperties");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedProperties_6) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "unevaluatedProperties": false } ],
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 2);

  EXPECT_UNEVALUATED_STATIC(result, "#/anyOf/0/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/anyOf/0/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/anyOf/0/unevaluatedProperties");

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 0);

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 1);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/unevaluatedProperties");
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedProperties_7) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "unevaluatedProperties": false,
    "anyOf": [ { "$ref": "#/$defs/bar" } ],
    "$defs": {
      "foo": {
        "properties": {
          "foo": true
        }
      },
      "bar": {
        "additionalProperties": false
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 1);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/$defs/foo/properties");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/$defs/bar/additionalProperties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/$ref");

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedProperties_8) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#test",
    "unevaluatedProperties": false,
    "$defs": {
      "foo": {
        "$id": "nested",
        "$dynamicAnchor": "test",
        "properties": {
          "foo": true
        }
      },
      "bar": {
        "$dynamicAnchor": "test",
        "$ref": "#/$defs/foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result,
                            "https://example.com#/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result,
                             "https://example.com#/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_UNRESOLVED(result,
                                "https://example.com#/unevaluatedProperties");
}

TEST(unevaluatedItems_1) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": true,
    "items": true,
    "contains": true,
    "unevaluatedItems": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 3);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/prefixItems");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems", "/items");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/contains");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");
}

TEST(unevaluatedItems_2) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "unevaluatedItems": false } ],
    "unevaluatedItems": false
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 2);

  EXPECT_UNEVALUATED_STATIC(result, "#/allOf/0/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/allOf/0/unevaluatedItems", 0);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 1);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/allOf/0/unevaluatedItems");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");
}
