#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include "compiler_test_utils.h"

TEST(unevaluatedProperties_root_self_reference_2020_12) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(unevaluatedItems_root_self_reference_2020_12) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(allOf_self_reference) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [{"$ref": "#"}],
    "properties": {"a": true},
    "unevaluatedProperties": false
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

TEST(anyOf_self_reference_static_and_dynamic) {
  // Re-entering a static location dynamically must still collect its
  // dependencies.
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [{"$ref": "#"}],
    "properties": {"a": true},
    "unevaluatedProperties": false
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
                                        "/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/$ref");
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

TEST(if_self_reference) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {"$ref": "#"},
    "properties": {"a": true},
    "unevaluatedProperties": false
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
                                        "/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/if/$ref");
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

TEST(then_self_reference) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "then": {"$ref": "#"},
    "properties": {"a": true},
    "unevaluatedProperties": false,
    "if": true
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
                                        "/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/then/$ref");
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

TEST(else_self_reference) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "else": {"$ref": "#"},
    "properties": {"a": true},
    "unevaluatedProperties": false,
    "if": false
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
                                        "/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/else/$ref");
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

TEST(unevaluatedProperties_mutual_definitions) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": {"$ref": "#/$defs/b", "properties": {"a": true}},
      "b": {"$ref": "#/$defs/a", "properties": {"a": true}}
    },
    "$ref": "#/$defs/a",
    "unevaluatedProperties": false
  })JSON");

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(result.size(), 1);
  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/$defs/a/properties");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                       "/$defs/b/properties");
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

TEST(unevaluatedItems_mutual_definitions) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": {"$ref": "#/$defs/b", "prefixItems": [true]},
      "b": {"$ref": "#/$defs/a", "prefixItems": [true]}
    },
    "$ref": "#/$defs/a",
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
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/$defs/a/prefixItems");
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/$defs/b/prefixItems");
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

TEST(dependentSchemas_self_reference) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {"trigger": true},
    "dependentSchemas": {"trigger": {"$ref": "#", "properties": {"allowed": true}}},
    "unevaluatedProperties": false
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
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 3);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/dependentSchemas/trigger/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/dependentSchemas/trigger/$ref");
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
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"extra": 1})JSON")));
  }
}

TEST(contains_self_reference_properties) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {"a": true},
    "contains": {"$ref": "#"},
    "minContains": 0,
    "unevaluatedProperties": false
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
                                        "/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/contains/$ref");
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
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON({"a": 1})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"extra": 1})JSON")));
  }
}

TEST(contains_recursive_items) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {"anyOf": [{"type": "integer"}, {"$ref": "#"}]},
    "unevaluatedItems": false
  })JSON");

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};
  const auto result{sourcemeta::blaze::unevaluated(
      schema, frame, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(result.size(), 1);
  EXPECT_UNEVALUATED_STATIC(result, "#/unevaluatedItems", 1);
  EXPECT_UNEVALUATED_STATIC_DEPENDENCY(result, "#/unevaluatedItems",
                                       "/contains");
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 0);
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");

  for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                          sourcemeta::blaze::Mode::Exhaustive}) {
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, mode)};
    EXPECT_FALSE(schema_template.targets.empty());
    sourcemeta::blaze::Evaluator evaluator;
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([1])JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([1, [2]])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([1, "x"])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([[]])JSON")));
  }
}

TEST(not_self_reference) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {"$ref": "#"},
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

TEST(not_does_not_contribute_properties) {
  // Dependencies under not must not make hidden properties evaluated.
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "required": ["blocked"],
      "properties": {"hidden": true},
      "if": false,
      "then": {"$ref": "#"}
    },
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

  for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                          sourcemeta::blaze::Mode::Exhaustive}) {
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, mode)};
    EXPECT_FALSE(schema_template.targets.empty());
    sourcemeta::blaze::Evaluator evaluator;
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"hidden": 1})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"blocked": 1})JSON")));
  }
}

TEST(conditional_cycle_in_inactive_then) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": {"required": ["recurse"]},
    "then": {"$ref": "#"},
    "else": {"properties": {"allowed": {"type": "integer"}}},
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
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/else/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/then/$ref");
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
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"allowed": 1})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"allowed": "x"})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"extra": 1})JSON")));
  }
}

TEST(conditional_cycle_in_inactive_else) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": {"required": ["stop"]},
    "then": {
      "properties": {"stop": true, "allowed": {"type": "integer"}}
    },
    "else": {"$ref": "#"},
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
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/then/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/else/$ref");
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
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"stop": true})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(
                             R"JSON({"stop": true, "allowed": 1})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(
                             R"JSON({"stop": true, "allowed": "x"})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"stop": true, "extra": 1})JSON")));
  }
}

TEST(shared_dynamic_target_2020_12) {
  // Both non-cyclic reference origins need their own dynamic dependency entry.
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(shared_target_static_then_dynamic) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {"common": {"properties": {"a": true}}},
    "allOf": [{"$ref": "#/$defs/common"}],
    "anyOf": [{"$ref": "#/$defs/common"}],
    "unevaluatedProperties": false
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
                                       "/$defs/common/properties");
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 2);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/$defs/common/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/anyOf/0/$ref");
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
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON({"a": 1})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"extra": 1})JSON")));
  }
}

TEST(shared_target_across_conditional_paths) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {"common": {"properties": {"allowed": {"type": "integer"}}}},
    "if": {"$ref": "#/$defs/common"},
    "then": {"$ref": "#/$defs/common"},
    "else": {"$ref": "#/$defs/common"},
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
                                        "/$defs/common/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/if/$ref");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/then/$ref");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/else/$ref");
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
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"allowed": 1})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"allowed": "x"})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"extra": 1})JSON")));
  }
}

TEST(dependentSchemas_shared_target) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {"common": {"properties": {"allowed": {"type": "integer"}}}},
    "properties": {"a": true, "b": true},
    "dependentSchemas": {
      "a": {"$ref": "#/$defs/common"},
      "b": {"$ref": "#/$defs/common"}
    },
    "unevaluatedProperties": false
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
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedProperties", 3);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/$defs/common/properties");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/dependentSchemas/a/$ref");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedProperties",
                                        "/dependentSchemas/b/$ref");
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
        schema_template, sourcemeta::core::parse_json(R"JSON({})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"a": 1, "allowed": 2})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"b": 1, "allowed": 2})JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(
                             R"JSON({"a": 1, "b": 1, "allowed": 2})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"allowed": 2})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"a": 1, "allowed": "x"})JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template,
        sourcemeta::core::parse_json(R"JSON({"b": 1, "extra": 2})JSON")));
  }
}

TEST(shared_target_items) {
  const auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {"common": {"contains": {"type": "integer"}}},
    "anyOf": [{"$ref": "#/$defs/common"}, {"$ref": "#/$defs/common"}],
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
  EXPECT_UNEVALUATED_DYNAMIC(result, "#/unevaluatedItems", 3);
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedItems",
                                        "/$defs/common/contains");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedItems",
                                        "/anyOf/0/$ref");
  EXPECT_UNEVALUATED_DYNAMIC_DEPENDENCY(result, "#/unevaluatedItems",
                                        "/anyOf/1/$ref");
  EXPECT_UNEVALUATED_RESOLVED(result, "#/unevaluatedItems");

  for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                          sourcemeta::blaze::Mode::Exhaustive}) {
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, mode)};
    EXPECT_FALSE(schema_template.targets.empty());
    sourcemeta::blaze::Evaluator evaluator;
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([1])JSON")));
    EXPECT_TRUE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([1, 2])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON([1, "x"])JSON")));
    EXPECT_FALSE(evaluator.validate(
        schema_template, sourcemeta::core::parse_json(R"JSON(["x"])JSON")));
  }
}
