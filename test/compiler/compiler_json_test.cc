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
          "type": "type",
          "value": 4
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
    "properties": {
      "foo": {
        "type": "array",
        "items": {
          "const": 999
        }
      }
    },
    "additionalProperties": {
      "type": "number"
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
        "t": 88,
        "s": "/properties",
        "i": "",
        "k": "#/properties",
        "r": 0,
        "v": {
          "type": "property",
          "value": [
            "foo",
            [ 0, 1869571584, 0, 0 ]
          ]
        },
        "c": [
          {
            "t": 78,
            "s": "/properties/foo/items",
            "i": "/foo",
            "k": "#/properties/foo/items",
            "r": 0,
            "v": {
              "type": "unsigned-integer",
              "value": 0
            },
            "c": [
              {
                "t": 26,
                "s": "/const",
                "i": "",
                "k": "#/properties/foo/items/const",
                "r": 0,
                "v": {
                  "type": "json",
                  "value": 999
                },
                "c": []
              }
            ]
          },
          {
            "t": 11,
            "s": "/properties/foo/type",
            "i": "/foo",
            "k": "#/properties/foo/type",
            "r": 0,
            "v": {
              "type": "type",
              "value": 5
            },
            "c": []
          }
        ]
      },
      {
        "t": 66,
        "s": "/additionalProperties",
        "i": "",
        "k": "#/additionalProperties",
        "r": 0,
        "v": {
          "type": "property-filter",
          "value": [
            {
              "type": "string-set",
              "value": [ "foo" ]
            },
            {
              "type": "strings",
              "value": []
            },
            []
          ]
        },
        "c": [
          {
            "t": 12,
            "s": "/type",
            "i": "",
            "k": "#/additionalProperties/type",
            "r": 0,
            "v": {
              "type": "types",
              "value": [ 3, 2 ]
            },
            "c": []
          }
        ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}
