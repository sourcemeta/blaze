#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>

#define EXPECT_BIDIRECTIONAL_JSON(schema_template, expected_json)              \
  {                                                                            \
    const auto result{sourcemeta::blaze::to_json(schema_template)};            \
    EXPECT_EQ(result, (expected));                                             \
    const auto template_back{sourcemeta::blaze::from_json(result)};            \
    EXPECT_TRUE(template_back.has_value());                                    \
    EXPECT_EQ(sourcemeta::blaze::to_json(template_back.value()), (expected));  \
  }

TEST(Compiler_JSON, example_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

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

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
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

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
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

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(Compiler_JSON, invalid_1) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dynamic": false,
    "track": false,
    "instructions": [
      { "t": 99 }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::from_json(input)};
  EXPECT_FALSE(result.has_value());
}
