#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/core/jsonschema.h>

#include "compiler_test_utils.h"

TEST(unevaluatedProperties_1) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": true },
    "patternProperties": { "^@": true },
    "additionalProperties": true,
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

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

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

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

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

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

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

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

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

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

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

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

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");
}

TEST(unevaluatedProperties_root_self_reference_2019_09) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(result.size(), 1);
  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");

  // Non-progressing references need not validate; compilation must terminate.
  for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                          sourcemeta::blaze::Mode::Exhaustive}) {
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, mode)};
    EXPECT_FALSE(schema_template.targets.empty());
  }
}

TEST(unevaluatedItems_root_self_reference_2019_09) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "unevaluatedItems": false
  })JSON");

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(result.size(), 1);
  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");

  // Non-progressing references need not validate; compilation must terminate.
  for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                          sourcemeta::blaze::Mode::Exhaustive}) {
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, mode)};
    EXPECT_FALSE(schema_template.targets.empty());
  }
}

TEST(shared_dynamic_target_2019_09) {
  // Both non-cyclic reference origins need their own dynamic dependency entry.
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "common": {
        "anyOf": [
          {
            "properties": {"a": {"type": "integer"}},
            "required": ["a"]
          },
          {
            "properties": {"b": {"type": "integer"}},
            "required": ["b"]
          }
        ]
      }
    },
    "anyOf": [{"$ref": "#/$defs/common"}, {"$ref": "#/$defs/common"}],
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(result.size(), 1);
  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 0);
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 4);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/$defs/common/anyOf/0/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/$defs/common/anyOf/1/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/$ref");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/1/$ref");
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedProperties");

  for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                          sourcemeta::blaze::Mode::Exhaustive}) {
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, mode)};
    EXPECT_FALSE(schema_template.targets.empty());
    sourcemeta::blaze::Evaluator evaluator;
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON({"a": 1})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON({"b": 2})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"a": 1, "b": 2})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"a": 1, "b": "x"})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"a": 1, "extra": 3})JSON")));
  }
}
