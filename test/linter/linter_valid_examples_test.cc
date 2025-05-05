#include <gtest/gtest.h>

#include <sourcemeta/blaze/linter.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

TEST(Linter, valid_examples_1) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
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

TEST(Linter, valid_examples_2) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", "bar", "baz" ]
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", "bar", "baz" ]
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_3) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
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

TEST(Linter, valid_examples_4) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
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

TEST(Linter, valid_examples_5) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
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

TEST(Linter, valid_examples_6) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
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

TEST(Linter, valid_examples_7) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_8) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [],
    "properties": {
      "foo": {
        "type": "string",
        "examples": []
      }
    }
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [],
    "properties": {
      "foo": {
        "type": "string",
        "examples": []
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_9) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "examples": [ {} ]
  })JSON")};

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "examples": [ {} ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}
