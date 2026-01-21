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

#define EXPECT_BIDIRECTIONAL_JSON_WITHOUT_EXPECTED(schema_template)            \
  {                                                                            \
    const auto result{sourcemeta::blaze::to_json(schema_template)};            \
    const auto template_back{sourcemeta::blaze::from_json(result)};            \
    EXPECT_TRUE(template_back.has_value());                                    \
    EXPECT_EQ(sourcemeta::blaze::to_json(template_back.value()), (result));    \
  }

TEST(Compiler_JSON, example_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON([
    false,
    false,
    [],
    [
      [
        [
          11,
          "/type",
          "",
          "#/type",
          0,
          [ 8, 4 ]
        ]
      ]
    ],
    []
  ])JSON")};

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

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON([
    false,
    false,
    [],
    [
      [
        [
          61,
          "/additionalProperties",
          "",
          "#/additionalProperties",
          0,
          [ 0 ],
          [
            [
              34,
              "/multipleOf",
              "",
              "#/additionalProperties/multipleOf",
              0,
              [ 1, 2 ]
            ],
            [
              10,
              "/type",
              "",
              "#/additionalProperties/type",
              0,
              [ 7, 156 ]
            ]
          ]
        ]
      ]
    ],
    []
  ])JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(Compiler_JSON, example_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "pattern": "^f"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON([
    false,
    false,
    [],
    [
      [
        [
          19,
          "/pattern",
          "",
          "#/pattern",
          0,
          [ 9, "^f" ]
        ]
      ]
    ],
    []
  ])JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(Compiler_JSON, example_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/top",
    "additionalProperties": {
      "$id": "https://other.com/nested",
      "type": [ "number", "string" ],
      "multipleOf": 2
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON([
    false,
    false,
    [ "https://example.com/top", "https://other.com/nested" ],
    [
      [
        [
          61,
          "/additionalProperties",
          "",
          "#/additionalProperties",
          1,
          [ 0 ],
          [
            [
              34,
              "/multipleOf",
              "",
              "#/multipleOf",
              2,
              [ 1, 2 ]
            ],
            [
              10,
              "/type",
              "",
              "#/type",
              2,
              [ 7, 156 ]
            ]
          ]
        ]
      ]
    ],
    []
  ])JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);

  // Confirm that the keyword locations are fully constructed back
  const auto template_back{sourcemeta::blaze::from_json(expected)};
  EXPECT_TRUE(template_back.has_value());
  EXPECT_EQ(template_back.value().targets.at(0).at(0).keyword_location,
            "https://example.com/top#/additionalProperties");
  EXPECT_EQ(
      template_back.value().targets.at(0).at(0).children.at(0).keyword_location,
      "https://other.com/nested#/multipleOf");
  EXPECT_EQ(
      template_back.value().targets.at(0).at(0).children.at(1).keyword_location,
      "https://other.com/nested#/type");
}

TEST(Compiler_JSON, example_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/top",
    "foo%": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON([
    false,
    true,
    [ "https://example.com/top" ],
    [
      [
        [
          44,
          "/foo%",
          "",
          "#/foo%25",
          1,
          [ 1, true ]
        ]
      ]
    ],
    []
  ])JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);

  // Confirm that the keyword locations are fully constructed back
  const auto template_back{sourcemeta::blaze::from_json(expected)};
  EXPECT_TRUE(template_back.has_value());
  EXPECT_EQ(template_back.value().targets.at(0).at(0).keyword_location,
            "https://example.com/top#/foo%25");
}

TEST(Compiler_JSON, example_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/top",
    "additionalProperties": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON([
    false,
    true,
    [ "https://example.com/top" ],
    [
      [
        [
          61,
          "/additionalProperties",
          "",
          "#/additionalProperties",
          1,
          [ 0 ],
          [
            [
              11,
              "/type",
              "",
              "#/additionalProperties/type",
              1,
              [ 8, 4 ]
            ],
            [
              46,
              "",
              "",
              "#/additionalProperties",
              1,
              [ 0 ]
            ]
          ]
        ]
      ]
    ],
    []
  ])JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);

  // Confirm that the keyword locations are fully constructed back
  const auto template_back{sourcemeta::blaze::from_json(expected)};
  EXPECT_TRUE(template_back.has_value());
  EXPECT_EQ(template_back.value().targets.at(0).at(0).keyword_location,
            "https://example.com/top#/additionalProperties");
  EXPECT_EQ(
      template_back.value().targets.at(0).at(0).children.at(0).keyword_location,
      "https://example.com/top#/additionalProperties/type");
  EXPECT_EQ(
      template_back.value().targets.at(0).at(0).children.at(1).keyword_location,
      "https://example.com/top#/additionalProperties");
}

TEST(Compiler_JSON, without_expected_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/top#",
    "allOf": [
      { "$ref": "http://json-schema.org/draft-04/schema#" }
    ],
    "definitions": {
      "schema": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "http://json-schema.org/draft-04/schema#",
        "properties": {
          "a": { "$ref": "#" },
          "b": { "$ref": "#" },
          "c": { "$ref": "#" },
          "d": { "$ref": "#" },
          "e": { "$ref": "#" },
          "f": { "$ref": "#" },
          "g": { "$ref": "#" },
          "h": { "$ref": "#" },
          "j": { "$ref": "#" }
        }
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  EXPECT_BIDIRECTIONAL_JSON_WITHOUT_EXPECTED(schema_template);
}

TEST(Compiler_JSON, without_expected_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "[\\-]": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  EXPECT_BIDIRECTIONAL_JSON_WITHOUT_EXPECTED(schema_template);
}

TEST(Compiler_JSON, invalid_1) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "d": false,
    "t": false,
    "i": [
      { "t": 99 }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::from_json(input)};
  EXPECT_FALSE(result.has_value());
}
