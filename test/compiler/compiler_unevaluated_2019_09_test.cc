#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/frame.h>

#include "compiler_test_utils.h"

TEST(unevaluatedProperties_1) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$recursiveAnchor": true,
    "$ref": "tree",
    "properties": { "name": true },
    "$defs": {
      "tree": {
        "$id": "tree",
        "$recursiveAnchor": true,
        "properties": {
          "branches": {
            "unevaluatedProperties": false,
            "$recursiveRef": "#"
          }
        }
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

  EXPECT_UNEVALUATED_STATIC(
      result,
      "https://example.com/tree#/properties/branches/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_DYNAMIC(
      result,
      "https://example.com/tree#/properties/branches/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_UNRESOLVED(
      result,
      "https://example.com/tree#/properties/branches/unevaluatedProperties");
}

TEST(unevaluatedProperties_4) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": true },
    "unevaluatedProperties": false,
    "anyOf": [
      {
        "properties": {
          "bar": { "const": "bar" }
        }
      },
      {
        "properties": {
          "baz": { "const": "baz" }
        }
      }
    ]
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
                                       "/properties");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/1/properties");

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");
}

TEST(unevaluatedItems_1) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": true,
    "additionalItems": true,
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

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 2);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems", "/items");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/additionalItems");

  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);

  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");
}

TEST(unevaluatedItems_2) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$ref": "test",
    "$recursiveAnchor": true,
    "unevaluatedItems": false,
    "$defs": {
      "test": {
        "$id": "test",
        "$recursiveAnchor": true,
        "items": [ { "$ref": "#" } ]
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

  EXPECT_UNEVALUATED_STATIC(result, "https://example.com#/unevaluatedItems", 1);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(
      result, "https://example.com#/unevaluatedItems", "/$defs/test/items");

  EXPECT_UNEVALUATED_DYNAMIC(result, "https://example.com#/unevaluatedItems",
                             0);
  EXPECT_UNEVALUATED_RESOLVED(result, "https://example.com#/unevaluatedItems");
}

TEST(unevaluatedItems_3) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": {"type": "number"},
    "unevaluatedItems": {"type": "string"}
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");
}
