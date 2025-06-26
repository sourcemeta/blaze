#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>

// TODO: Eventually test parsing the JSON back and asserting that it equals the
// original template, using a helper macro to define each test

TEST(Compiler_JSON, example_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const auto result{sourcemeta::blaze::to_json(schema_template)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON({
    "dynamic": false,
    "track": false,
    "instructions": [
      {
        "t": 11,
        "s": "/type",
        "i": "",
        "k": "#/type",
        "r": 0,
        "v": {
          "t": 8,
          "v": 4
        },
        "c": []
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_JSON, example_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": {
      "type": [ "number", "string" ],
      "multipleOf": 2
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const auto result{sourcemeta::blaze::to_json(schema_template)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON({
    "dynamic": false,
    "track": false,
    "instructions": [
      {
        "t": 61,
        "s": "/additionalProperties",
        "i": "",
        "k": "#/additionalProperties",
        "r": 0,
        "v": {
          "t": 0,
          "v": null
        },
        "c": [
          {
            "t": 34,
            "s": "/multipleOf",
            "i": "",
            "k": "#/additionalProperties/multipleOf",
            "r": 0,
            "v": {
              "t": 1,
              "v": 2
            },
            "c": []
          },
          {
            "t": 10,
            "s": "/type",
            "i": "",
            "k": "#/additionalProperties/type",
            "r": 0,
            "v": {
              "t": 7,
              "v": [ 2, 3, 4 ]
            },
            "c": []
          }
        ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_JSON, example_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "pattern": "^f"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const auto result{sourcemeta::blaze::to_json(schema_template)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON({
    "dynamic": false,
    "track": false,
    "instructions": [
      {
        "t": 19,
        "s": "/pattern",
        "i": "",
        "k": "#/pattern",
        "r": 0,
        "v": {
          "t": 9,
          "v": "^f"
        },
        "c": []
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}
