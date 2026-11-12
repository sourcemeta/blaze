#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>

#include <algorithm>     // std::ranges::count
#include <unordered_set> // std::unordered_set

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

TEST(example_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [
            11,
            [ "type" ],
            [],
            "#/type",
            0,
            1,
            1,
            2,
            [ 8, 4 ]
          ]
        ]
      ],
      [],
      [ "https://json-schema.org/draft/2020-12/vocab/validation" ],
      [
        "{0} was expected to be of type {1}",
        "{0} was expected to be of type {1} but it was of type {2}"
      ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(example_2) {
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

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [
            71,
            [ "additionalProperties" ],
            [],
            "#/additionalProperties",
            0,
            2,
            1,
            0,
            [ 0 ],
            [
              [
                35,
                [ "multipleOf" ],
                [],
                "#/additionalProperties/multipleOf",
                0,
                1,
                2,
                0,
                [ 1, 2 ]
              ],
              [
                10,
                [ "type" ],
                [],
                "#/additionalProperties/type",
                0,
                1,
                3,
                4,
                [ 7, 156 ]
              ]
            ]
          ]
        ]
      ],
      [],
      [
        "https://json-schema.org/draft/2020-12/vocab/validation",
        "https://json-schema.org/draft/2020-12/vocab/applicator"
      ],
      [
        "The object properties not covered by other adjacent object keywords were expected to validate against this subschema",
        "The {0} value {1} was expected to be divisible by the {2} {3}",
        "{0} was expected to be of type {1} and it was of type {2}",
        "{0} was expected to be of type {1} but it was of type {2}"
      ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(example_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "pattern": "^f"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [
            20,
            [ "pattern" ],
            [],
            "#/pattern",
            0,
            1,
            1,
            0,
            [ 9, "^f" ]
          ]
        ]
      ],
      [],
      [ "https://json-schema.org/draft/2020-12/vocab/validation" ],
      [ "{0} was expected to match the regular expression {1}" ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(example_4) {
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

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [
            71,
            [ "additionalProperties" ],
            [],
            "https://example.com/top#/additionalProperties",
            1,
            2,
            1,
            0,
            [ 0 ],
            [
              [
                35,
                [ "multipleOf" ],
                [],
                "https://other.com/nested#/multipleOf",
                2,
                1,
                2,
                0,
                [ 1, 2 ]
              ],
              [
                10,
                [ "type" ],
                [],
                "https://other.com/nested#/type",
                2,
                1,
                3,
                4,
                [ 7, 156 ]
              ]
            ]
          ]
        ]
      ],
      [],
      [
        "https://json-schema.org/draft/2020-12/vocab/validation",
        "https://json-schema.org/draft/2020-12/vocab/applicator"
      ],
      [
        "The object properties not covered by other adjacent object keywords were expected to validate against this subschema",
        "The {0} value {1} was expected to be divisible by the {2} {3}",
        "{0} was expected to be of type {1} and it was of type {2}",
        "{0} was expected to be of type {1} but it was of type {2}"
      ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);

  // Confirm that the keyword locations are fully constructed back
  const auto template_back{sourcemeta::blaze::from_json(expected)};
  EXPECT_TRUE(template_back.has_value());
  EXPECT_EQ(template_back.value()
                .extra[template_back.value().targets.at(0).at(0).extra_index]
                .keyword_location,
            "https://example.com/top#/additionalProperties");
  EXPECT_EQ(template_back.value()
                .extra[template_back.value()
                           .targets.at(0)
                           .at(0)
                           .children.at(0)
                           .extra_index]
                .keyword_location,
            "https://other.com/nested#/multipleOf");
  EXPECT_EQ(template_back.value()
                .extra[template_back.value()
                           .targets.at(0)
                           .at(0)
                           .children.at(1)
                           .extra_index]
                .keyword_location,
            "https://other.com/nested#/type");
}

TEST(example_5) {
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

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      true,
      [
        [
          [
            53,
            [ "foo%" ],
            [],
            "https://example.com/top#/foo%25",
            1,
            0,
            1,
            0,
            [ 1, true ]
          ]
        ]
      ],
      [],
      [],
      [ "The unrecognized keyword {4} was collected as the annotation {2}" ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);

  // Confirm that the keyword locations are fully constructed back
  const auto template_back{sourcemeta::blaze::from_json(expected)};
  EXPECT_TRUE(template_back.has_value());
  EXPECT_EQ(template_back.value()
                .extra[template_back.value().targets.at(0).at(0).extra_index]
                .keyword_location,
            "https://example.com/top#/foo%25");
}

TEST(example_6) {
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

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      true,
      [
        [
          [
            71,
            [ "additionalProperties" ],
            [],
            "https://example.com/top#/additionalProperties",
            1,
            2,
            1,
            0,
            [ 0 ],
            [
              [
                11,
                [ "type" ],
                [],
                "https://example.com/top#/additionalProperties/type",
                1,
                1,
                2,
                3,
                [ 8, 4 ]
              ],
              [
                56,
                [],
                [],
                "https://example.com/top#/additionalProperties",
                1,
                2,
                4,
                0,
                [ 0 ]
              ]
            ]
          ]
        ]
      ],
      [],
      [
        "https://json-schema.org/draft/2020-12/vocab/validation",
        "https://json-schema.org/draft/2020-12/vocab/applicator"
      ],
      [
        "The object properties not covered by other adjacent object keywords were expected to validate against this subschema",
        "{0} was expected to be of type {1}",
        "{0} was expected to be of type {1} but it was of type {2}",
        "The object property {0} successfully validated against the additional properties subschema"
      ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);

  // Confirm that the keyword locations are fully constructed back
  const auto template_back{sourcemeta::blaze::from_json(expected)};
  EXPECT_TRUE(template_back.has_value());
  EXPECT_EQ(template_back.value()
                .extra[template_back.value().targets.at(0).at(0).extra_index]
                .keyword_location,
            "https://example.com/top#/additionalProperties");
  EXPECT_EQ(template_back.value()
                .extra[template_back.value()
                           .targets.at(0)
                           .at(0)
                           .children.at(0)
                           .extra_index]
                .keyword_location,
            "https://example.com/top#/additionalProperties/type");
  EXPECT_EQ(template_back.value()
                .extra[template_back.value()
                           .targets.at(0)
                           .at(0)
                           .children.at(1)
                           .extra_index]
                .keyword_location,
            "https://example.com/top#/additionalProperties");
}

TEST(properties_as_a_loop_without_a_table_of_contents) {
  // Enough optional properties for the compiler to prefer one pass over the
  // instance to unrolling every property, which emits the named indexes, but
  // too few for it to give them a table of contents
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "a": { "type": "string" },
      "bb": { "type": "integer" },
      "cc": { "type": "boolean" },
      "dddd": { "type": "null" },
      "eeeee": { "type": "array" },
      "ffffff": { "type": "object" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [
            69,
            [ "properties" ],
            [],
            "#/properties",
            0,
            2,
            1,
            0,
            [
              13,
              [
                [
                  [
                    [ 0, 24833, 0, 0 ],
                    0,
                    "a"
                  ],
                  [
                    [ 0, 6447618, 0, 0 ],
                    1,
                    "bb"
                  ],
                  [
                    [ 0, 6513410, 0, 0 ],
                    2,
                    "cc"
                  ],
                  [
                    [ 0, 431181030404, 0, 0 ],
                    3,
                    "dddd"
                  ],
                  [
                    [ 0, 111486167246085, 0, 0 ],
                    4,
                    "eeeee"
                  ],
                  [
                    [ 0, 28823037615171078, 0, 0 ],
                    5,
                    "ffffff"
                  ]
                ],
                []
              ]
            ],
            [
              [
                98,
                [],
                [],
                "#/properties",
                0,
                2,
                0,
                0,
                [ 0 ],
                [
                  [
                    45,
                    [ "a", "type" ],
                    [ "a" ],
                    "#/properties/a/type",
                    0,
                    1,
                    2,
                    3,
                    [ 8, 4 ]
                  ]
                ]
              ],
              [
                98,
                [],
                [],
                "#/properties",
                0,
                2,
                0,
                0,
                [ 0 ],
                [
                  [
                    43,
                    [ "bb", "type" ],
                    [ "bb" ],
                    "#/properties/bb/type",
                    0,
                    1,
                    2,
                    3,
                    [ 8, 2 ]
                  ]
                ]
              ],
              [
                98,
                [],
                [],
                "#/properties",
                0,
                2,
                0,
                0,
                [ 0 ],
                [
                  [
                    45,
                    [ "cc", "type" ],
                    [ "cc" ],
                    "#/properties/cc/type",
                    0,
                    1,
                    2,
                    3,
                    [ 8, 1 ]
                  ]
                ]
              ],
              [
                98,
                [],
                [],
                "#/properties",
                0,
                2,
                0,
                0,
                [ 0 ],
                [
                  [
                    45,
                    [ "dddd", "type" ],
                    [ "dddd" ],
                    "#/properties/dddd/type",
                    0,
                    1,
                    2,
                    3,
                    [ 8, 0 ]
                  ]
                ]
              ],
              [
                98,
                [],
                [],
                "#/properties",
                0,
                2,
                0,
                0,
                [ 0 ],
                [
                  [
                    45,
                    [ "eeeee", "type" ],
                    [ "eeeee" ],
                    "#/properties/eeeee/type",
                    0,
                    1,
                    2,
                    3,
                    [ 8, 5 ]
                  ]
                ]
              ],
              [
                98,
                [],
                [],
                "#/properties",
                0,
                2,
                0,
                0,
                [ 0 ],
                [
                  [
                    45,
                    [ "ffffff", "type" ],
                    [ "ffffff" ],
                    "#/properties/ffffff/type",
                    0,
                    1,
                    2,
                    3,
                    [ 8, 6 ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ],
      [],
      [
        "https://json-schema.org/draft/2020-12/vocab/validation",
        "https://json-schema.org/draft/2020-12/vocab/applicator"
      ],
      [
        "The object value was expected to validate against the {0} defined properties subschemas",
        "{0} was expected to be of type {1}",
        "{0} was expected to be of type {1} but it was of type {2}"
      ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(without_expected_1) {
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

TEST(without_expected_2) {
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

TEST(without_expected_3) {
  // The draft 7 metaschema declares more properties than the threshold at
  // which the compiler gives the named indexes a table of contents, so this
  // covers encoding and decoding them with one
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-07/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto schema_template{sourcemeta::blaze::compile(
      metaschema.value(), sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  EXPECT_BIDIRECTIONAL_JSON_WITHOUT_EXPECTED(schema_template);
}

TEST(invalid_1) {
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

TEST(invalid_version) {
  const auto input{sourcemeta::core::parse_json(R"JSON([
    6,
    false,
    false,
    [
      [
        [
          11,
          [ "type" ],
          [],
          "#/type",
          0,
          [ 8, 4 ]
        ]
      ]
    ],
    []
  ])JSON")};

  const auto result{sourcemeta::blaze::from_json(input)};
  EXPECT_FALSE(result.has_value());
}

TEST(unreachable_refs_are_pruned) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "$defs": {
      "def0": { "$ref": "#/$defs/def1" },
      "def1": { "$ref": "#/$defs/def2" },
      "def2": { "$ref": "#/$defs/def3" },
      "def3": { "$ref": "#/$defs/def4" },
      "def4": { "$ref": "#/$defs/def0" },
      "unused": {
        "properties": {
          "a": { "$ref": "#/$defs/def0" },
          "b": { "$ref": "#/$defs/def1" }
        }
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const auto json_output{sourcemeta::blaze::to_json(schema_template)};

  EXPECT_TRUE(json_output.is_array());
  EXPECT_EQ(json_output.size(), 7);
  const auto &targets{json_output.at(3)};

  // NOTE: The targets must have exactly 1 entry (the root)
  // as all definitions are unreachable from the root
  EXPECT_TRUE(targets.is_array());
  EXPECT_EQ(targets.size(), 1);

  EXPECT_BIDIRECTIONAL_JSON_WITHOUT_EXPECTED(schema_template);
}

TEST(annotations_whitelist_unused_matches_untweaked) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" },
      "value": {
        "anyOf": [ { "type": "string" }, { "type": "integer" } ],
        "oneOf": [ { "minimum": 0 }, { "maximum": 10 } ]
      },
      "tags": {
        "type": "array",
        "contains": { "type": "string" }
      }
    },
    "required": [ "name", "age" ]
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "x-jsonld-id",       "x-jsonld-type",     "x-jsonld-reverse",
      "x-jsonld-datatype", "x-jsonld-language", "x-jsonld-direction",
      "x-jsonld-json",     "x-jsonld-graph",    "x-jsonld-container",
      "x-jsonld-self"};

  const auto with_whitelist{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  const auto without_tweaks{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  EXPECT_EQ(sourcemeta::blaze::to_json(with_whitelist),
            sourcemeta::blaze::to_json(without_tweaks));
}

TEST(items_fused_as_a_bounded_array_type_loop) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "array",
      "items": { "type": "number" },
      "minItems": 2
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [
            96,
            [ "items" ],
            [],
            "#/items",
            0,
            1,
            1,
            0,
            [
              26,
              [
                140,
                [ 2, null, false ]
              ]
            ]
          ]
        ]
      ],
      [],
      [ "http://json-schema.org/draft-07/schema#" ],
      [
        "Every item in the array was expected to be an array of the given size whose items were of the given types"
      ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}

TEST(messages_pool_carries_the_template_of_a_migrated_family) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  EXPECT_EQ(schema_template.extra.size(), 1);
  const auto &metadata{schema_template.extra.at(0)};
  EXPECT_TRUE(metadata.message > 0);
  EXPECT_TRUE(metadata.message_detail > 0);
  EXPECT_EQ(schema_template.messages.at(metadata.message - 1),
            "{0} was expected to be of type {1}");
  EXPECT_EQ(schema_template.messages.at(metadata.message_detail - 1),
            "{0} was expected to be of type {1} but it was of type {2}");
}

TEST(messages_pool_leaves_a_control_instruction_without_a_template) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" }, { "type": "integer" } ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  EXPECT_EQ(schema_template.targets.size(), 1);
  EXPECT_EQ(schema_template.targets.front().size(), 1);
  const auto &group{schema_template.targets.front().front().children.front()};
  EXPECT_EQ(group.type, sourcemeta::blaze::InstructionIndex::ControlGroup);
  EXPECT_EQ(schema_template.extra.at(group.extra_index).message, 0);
  EXPECT_EQ(schema_template.extra.at(group.extra_index).message_detail, 0);
}

TEST(messages_pool_carries_a_format_template) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "format": "uri"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive, "", "", "", tweaks)};

  EXPECT_EQ(std::ranges::count(
                schema_template.messages,
                "The string value {0} was expected to represent a valid URI"),
            1);
}

TEST(messages_pool_deduplicates_a_repeated_template) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "a": { "format": "uri" },
      "b": { "format": "uri" },
      "c": { "format": "email" }
    }
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive, "", "", "", tweaks)};

  EXPECT_EQ(std::ranges::count(
                schema_template.messages,
                "The string value {0} was expected to represent a valid URI"),
            1);
  EXPECT_EQ(std::ranges::count(schema_template.messages,
                               "The string value {0} was expected to represent "
                               "a valid email address"),
            1);
}

TEST(messages_pool_survives_a_json_round_trip) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "format": "ipv4"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive, "", "", "", tweaks)};

  const auto parsed{sourcemeta::blaze::from_json(
      sourcemeta::blaze::to_json(schema_template))};
  EXPECT_TRUE(parsed.has_value());
  EXPECT_EQ(parsed.value().messages, schema_template.messages);

  const auto &original{schema_template.extra};
  const auto &restored{parsed.value().extra};
  EXPECT_EQ(restored.size(), original.size());
  for (std::size_t index = 0; index < original.size(); index++) {
    EXPECT_EQ(restored.at(index).message, original.at(index).message);
  }
}

TEST(accepts_a_message_index_at_the_pool_size) {
  const auto input{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [ 11, [ "type" ], [], "#/type", 0, 0, 1, 0, [ 8, 4 ] ]
        ]
      ],
      [],
      [],
      [ "{0} was expected to be of type {1}" ]
    ]
  )JSON")};

  EXPECT_TRUE(sourcemeta::blaze::from_json(input).has_value());
}

TEST(rejects_a_message_index_beyond_the_pool) {
  const auto input{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [ 11, [ "type" ], [], "#/type", 0, 0, 2, 0, [ 8, 4 ] ]
        ]
      ],
      [],
      [],
      [ "{0} was expected to be of type {1}" ]
    ]
  )JSON")};

  EXPECT_FALSE(sourcemeta::blaze::from_json(input).has_value());
}

TEST(rejects_a_message_detail_index_beyond_the_pool) {
  const auto input{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [ 11, [ "type" ], [], "#/type", 0, 0, 1, 2, [ 8, 4 ] ]
        ]
      ],
      [],
      [],
      [ "{0} was expected to be of type {1}" ]
    ]
  )JSON")};

  EXPECT_FALSE(sourcemeta::blaze::from_json(input).has_value());
}

TEST(rejects_a_vocabulary_index_beyond_the_pool) {
  const auto input{sourcemeta::core::parse_json(R"JSON(
    [
      15,
      false,
      false,
      [
        [
          [ 11, [ "type" ], [], "#/type", 0, 1, 1, 0, [ 8, 4 ] ]
        ]
      ],
      [],
      [],
      [ "{0} was expected to be of type {1}" ]
    ]
  )JSON")};

  EXPECT_FALSE(sourcemeta::blaze::from_json(input).has_value());
}

TEST(rejects_the_previous_template_version) {
  const auto input{sourcemeta::core::parse_json(R"JSON(
    [
      14,
      false,
      false,
      [
        []
      ],
      [],
      [],
      []
    ]
  )JSON")};

  EXPECT_FALSE(sourcemeta::blaze::from_json(input).has_value());
}
