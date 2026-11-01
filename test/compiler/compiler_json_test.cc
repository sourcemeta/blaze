#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>

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
      14,
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
            [ 8, 4 ]
          ]
        ]
      ],
      [],
      [ "https://json-schema.org/draft/2020-12/vocab/validation" ]
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
      14,
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
            [ 0 ],
            [
              [
                35,
                [ "multipleOf" ],
                [],
                "#/additionalProperties/multipleOf",
                0,
                1,
                [ 1, 2 ]
              ],
              [
                10,
                [ "type" ],
                [],
                "#/additionalProperties/type",
                0,
                1,
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
      14,
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
            [ 9, "^f" ]
          ]
        ]
      ],
      [],
      [ "https://json-schema.org/draft/2020-12/vocab/validation" ]
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
      14,
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
            [ 0 ],
            [
              [
                35,
                [ "multipleOf" ],
                [],
                "https://other.com/nested#/multipleOf",
                2,
                1,
                [ 1, 2 ]
              ],
              [
                10,
                [ "type" ],
                [],
                "https://other.com/nested#/type",
                2,
                1,
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
      14,
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
            [ 1, true ]
          ]
        ]
      ],
      [],
      []
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
      14,
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
            [ 0 ],
            [
              [
                11,
                [ "type" ],
                [],
                "https://example.com/top#/additionalProperties/type",
                1,
                1,
                [ 8, 4 ]
              ],
              [
                56,
                [],
                [],
                "https://example.com/top#/additionalProperties",
                1,
                2,
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
      14,
      false,
      false,
      [
        [
          [
            69,
            [
              "properties"
            ],
            [],
            "#/properties",
            0,
            2,
            [
              13,
              [
                [
                  [
                    [
                      0,
                      24833,
                      0,
                      0
                    ],
                    0,
                    "a"
                  ],
                  [
                    [
                      0,
                      6447618,
                      0,
                      0
                    ],
                    1,
                    "bb"
                  ],
                  [
                    [
                      0,
                      6513410,
                      0,
                      0
                    ],
                    2,
                    "cc"
                  ],
                  [
                    [
                      0,
                      431181030404,
                      0,
                      0
                    ],
                    3,
                    "dddd"
                  ],
                  [
                    [
                      0,
                      111486167246085,
                      0,
                      0
                    ],
                    4,
                    "eeeee"
                  ],
                  [
                    [
                      0,
                      28823037615171078,
                      0,
                      0
                    ],
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
                [
                  0
                ],
                [
                  [
                    45,
                    [
                      "a",
                      "type"
                    ],
                    [
                      "a"
                    ],
                    "#/properties/a/type",
                    0,
                    1,
                    [
                      8,
                      4
                    ]
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
                [
                  0
                ],
                [
                  [
                    43,
                    [
                      "bb",
                      "type"
                    ],
                    [
                      "bb"
                    ],
                    "#/properties/bb/type",
                    0,
                    1,
                    [
                      8,
                      2
                    ]
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
                [
                  0
                ],
                [
                  [
                    45,
                    [
                      "cc",
                      "type"
                    ],
                    [
                      "cc"
                    ],
                    "#/properties/cc/type",
                    0,
                    1,
                    [
                      8,
                      1
                    ]
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
                [
                  0
                ],
                [
                  [
                    45,
                    [
                      "dddd",
                      "type"
                    ],
                    [
                      "dddd"
                    ],
                    "#/properties/dddd/type",
                    0,
                    1,
                    [
                      8,
                      0
                    ]
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
                [
                  0
                ],
                [
                  [
                    45,
                    [
                      "eeeee",
                      "type"
                    ],
                    [
                      "eeeee"
                    ],
                    "#/properties/eeeee/type",
                    0,
                    1,
                    [
                      8,
                      5
                    ]
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
                [
                  0
                ],
                [
                  [
                    45,
                    [
                      "ffffff",
                      "type"
                    ],
                    [
                      "ffffff"
                    ],
                    "#/properties/ffffff/type",
                    0,
                    1,
                    [
                      8,
                      6
                    ]
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
  EXPECT_EQ(json_output.size(), 6);
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
      14,
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
      [ "http://json-schema.org/draft-07/schema#" ]
    ]
  )JSON")};

  EXPECT_BIDIRECTIONAL_JSON(schema_template, expected);
}
