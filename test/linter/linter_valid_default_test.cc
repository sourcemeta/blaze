#include <gtest/gtest.h>

#include <sourcemeta/blaze/linter.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

TEST(Linter, valid_default_1) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_2) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": "bar" },
    "properties": {
      "foo": {
        "type": "string",
        "default": "baz"
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": "bar" },
    "properties": {
      "foo": {
        "type": "string",
        "default": "baz"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_3) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_4) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_5) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_6) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_7) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_8) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "default": {}
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "default": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}
