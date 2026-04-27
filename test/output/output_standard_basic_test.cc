#include <gtest/gtest.h>

#include <sstream>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

TEST(Output_standard_basic, prettify_annotations) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{R"JSON({
  "valid": true,
  "annotations": [
    {
      "keywordLocation": "/properties",
      "absoluteKeywordLocation": "#/properties",
      "instanceLocation": "",
      "annotation": [ "foo" ]
    }
  ]
})JSON"};

  std::ostringstream prettified;
  sourcemeta::core::prettify(result, prettified);

  EXPECT_EQ(prettified.str(), expected);
}

TEST(Output_standard_basic, prettify_annotations_with_instance_positions) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON instance{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON",
                               instance, std::ref(tracker));

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{sourcemeta::blaze::standard(
      evaluator, schema_template, instance,
      sourcemeta::blaze::StandardOutput::Basic, tracker)};

  const auto expected{R"JSON({
  "valid": true,
  "annotations": [
    {
      "keywordLocation": "/properties",
      "absoluteKeywordLocation": "#/properties",
      "instanceLocation": "",
      "instancePosition": [ 1, 1, 3, 3 ],
      "annotation": [ "foo" ]
    }
  ]
})JSON"};

  std::ostringstream prettified;
  sourcemeta::core::prettify(result, prettified);

  EXPECT_EQ(prettified.str(), expected);
}

TEST(Output_standard_basic, prettify_errors) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{R"JSON({
  "valid": false,
  "errors": [
    {
      "keywordLocation": "/properties/foo/type",
      "absoluteKeywordLocation": "#/properties/foo/type",
      "instanceLocation": "/foo",
      "error": "The value was expected to be of type string but it was of type integer"
    }
  ]
})JSON"};

  std::ostringstream prettified;
  sourcemeta::core::prettify(result, prettified);

  EXPECT_EQ(prettified.str(), expected);
}

TEST(Output_standard_basic, prettify_errors_with_instance_positions) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON instance{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON",
                               instance, std::ref(tracker));

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{sourcemeta::blaze::standard(
      evaluator, schema_template, instance,
      sourcemeta::blaze::StandardOutput::Basic, tracker)};

  const auto expected{R"JSON({
  "valid": false,
  "errors": [
    {
      "keywordLocation": "/properties/foo/type",
      "absoluteKeywordLocation": "#/properties/foo/type",
      "instanceLocation": "/foo",
      "instancePosition": [ 2, 5, 2, 12 ],
      "error": "The value was expected to be of type string but it was of type integer"
    }
  ]
})JSON"};

  std::ostringstream prettified;
  sourcemeta::core::prettify(result, prettified);

  EXPECT_EQ(prettified.str(), expected);
}

TEST(Output_standard_basic, success_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_1_with_instance_positions) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON instance{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON",
                               instance, std::ref(tracker));

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{sourcemeta::blaze::standard(
      evaluator, schema_template, instance,
      sourcemeta::blaze::StandardOutput::Basic, tracker)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/properties",
        "absoluteKeywordLocation": "#/properties",
        "instanceLocation": "",
        "annotation": [ "foo" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_1_exhaustive_with_instance_positions) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON instance{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "foo": "bar"
  })JSON",
                               instance, std::ref(tracker));

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{sourcemeta::blaze::standard(
      evaluator, schema_template, instance,
      sourcemeta::blaze::StandardOutput::Basic, tracker)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/properties",
        "absoluteKeywordLocation": "#/properties",
        "instanceLocation": "",
        "instancePosition": [ 1, 1, 3, 3 ],
        "annotation": [ "foo" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_2) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "#1", "type": "string" },
      { "title": "#2", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_2_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "#1", "type": "string" },
      { "title": "#2", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/anyOf/1/title",
        "absoluteKeywordLocation": "#/anyOf/1/title",
        "instanceLocation": "",
        "annotation": [ "#2" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_3) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "title": "Negation",
      "type": "integer"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_4) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "title": "Negation",
      "type": "integer"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/properties/foo/type",
        "absoluteKeywordLocation": "#/properties/foo/type",
        "instanceLocation": "/foo",
        "error": "The value was expected to be of type string but it was of type integer"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_1_with_instance_positions) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON instance{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON",
                               instance, std::ref(tracker));

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{sourcemeta::blaze::standard(
      evaluator, schema_template, instance,
      sourcemeta::blaze::StandardOutput::Basic, tracker)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/properties/foo/type",
        "absoluteKeywordLocation": "#/properties/foo/type",
        "instanceLocation": "/foo",
        "instancePosition": [ 2, 5, 2, 12 ],
        "error": "The value was expected to be of type string but it was of type integer"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/properties/foo/type",
        "absoluteKeywordLocation": "#/properties/foo/type",
        "instanceLocation": "/foo",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/properties",
        "absoluteKeywordLocation": "#/properties",
        "instanceLocation": "",
        "error": "The object value was expected to validate against the single defined property subschema"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_oneof_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"fo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_oneof_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/oneOf/0/type",
        "absoluteKeywordLocation": "#/oneOf/0/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type string but it was of type boolean"
      },
      {
        "keywordLocation": "/oneOf/1/type",
        "absoluteKeywordLocation": "#/oneOf/1/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type integer but it was of type boolean"
      },
      {
        "keywordLocation": "/oneOf",
        "absoluteKeywordLocation": "#/oneOf",
        "instanceLocation": "",
        "error": "The boolean value was expected to validate against one and only one of the 2 given subschemas"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_not_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_not_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/not",
        "absoluteKeywordLocation": "#/not",
        "instanceLocation": "",
        "error": "The string value was expected to not validate against the given subschema, but it did"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_anyof_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_anyof_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/anyOf/0/type",
        "absoluteKeywordLocation": "#/anyOf/0/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type string but it was of type boolean"
      },
      {
        "keywordLocation": "/anyOf/1/type",
        "absoluteKeywordLocation": "#/anyOf/1/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type integer but it was of type boolean"
      },
      {
        "keywordLocation": "/anyOf",
        "absoluteKeywordLocation": "#/anyOf",
        "instanceLocation": "",
        "error": "The boolean value was expected to validate against at least one of the 2 given subschemas"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_if_then_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "minLength": 3 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foobar"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_if_then_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "minLength": 10 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/then/minLength",
        "absoluteKeywordLocation": "#/then/minLength",
        "instanceLocation": "",
        "error": "The string value \"foo\" was expected to consist of at least 10 characters but it consisted of 3 characters"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_if_else_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "minimum": 0 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_if_else_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "minimum": 100 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/else/minimum",
        "absoluteKeywordLocation": "#/else/minimum",
        "instanceLocation": "",
        "error": "The integer value 42 was expected to be greater than or equal to the integer 100"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_contains_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, \"foo\", 3 ]")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_contains_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/contains/type",
        "absoluteKeywordLocation": "#/contains/type",
        "instanceLocation": "/0",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/contains/type",
        "absoluteKeywordLocation": "#/contains/type",
        "instanceLocation": "/1",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/contains/type",
        "absoluteKeywordLocation": "#/contains/type",
        "instanceLocation": "/2",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/contains",
        "absoluteKeywordLocation": "#/contains",
        "instanceLocation": "",
        "error": "The array value was expected to contain at least 1 item that validates against the given subschema"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_oneof_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "title": "First", "type": "string" },
      { "title": "Second", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/oneOf/1/title",
        "absoluteKeywordLocation": "#/oneOf/1/title",
        "instanceLocation": "",
        "annotation": [ "Second" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_not_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "title": "Negation",
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_anyof_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "#1", "type": "string" },
      { "title": "#2", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/anyOf/1/title",
        "absoluteKeywordLocation": "#/anyOf/1/title",
        "instanceLocation": "",
        "annotation": [ "#2" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_if_then_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "title": "Then Title", "minLength": 3 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{"foobar"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/then/title",
        "absoluteKeywordLocation": "#/then/title",
        "instanceLocation": "",
        "annotation": [ "Then Title" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_if_else_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "title": "Else Title", "minimum": 0 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/else/title",
        "absoluteKeywordLocation": "#/else/title",
        "instanceLocation": "",
        "annotation": [ "Else Title" ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, success_contains_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, 1, true ]")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": true,
    "annotations": [
      {
        "keywordLocation": "/contains",
        "absoluteKeywordLocation": "#/contains",
        "instanceLocation": "",
        "annotation": [ 0, 2 ]
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_nested_oneof_anyof_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "anyOf": [ { "type": "string" }, { "type": "integer" } ] },
      { "type": "boolean" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON{nullptr}};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/oneOf/0/anyOf/0/type",
        "absoluteKeywordLocation": "#/oneOf/0/anyOf/0/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type string but it was of type null"
      },
      {
        "keywordLocation": "/oneOf/0/anyOf/1/type",
        "absoluteKeywordLocation": "#/oneOf/0/anyOf/1/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type integer but it was of type null"
      },
      {
        "keywordLocation": "/oneOf/0/anyOf",
        "absoluteKeywordLocation": "#/oneOf/0/anyOf",
        "instanceLocation": "",
        "error": "The null value was expected to validate against at least one of the 2 given subschemas"
      },
      {
        "keywordLocation": "/oneOf/1/type",
        "absoluteKeywordLocation": "#/oneOf/1/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type boolean but it was of type null"
      },
      {
        "keywordLocation": "/oneOf",
        "absoluteKeywordLocation": "#/oneOf",
        "instanceLocation": "",
        "error": "The null value was expected to validate against one and only one of the 2 given subschemas"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_oneof_2) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/oneOf",
        "absoluteKeywordLocation": "#/oneOf",
        "instanceLocation": "",
        "error": "The string value was expected to validate against one and only one of the 2 given subschemas"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_not_not_1) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "not": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{1};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/not",
        "absoluteKeywordLocation": "#/not",
        "instanceLocation": "",
        "error": "The integer value was expected to not validate against the given subschema, but it did"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_oneof_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "title": "First", "type": "string" },
      { "title": "Second", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/oneOf/0/type",
        "absoluteKeywordLocation": "#/oneOf/0/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type string but it was of type boolean"
      },
      {
        "keywordLocation": "/oneOf/1/type",
        "absoluteKeywordLocation": "#/oneOf/1/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type integer but it was of type boolean"
      },
      {
        "keywordLocation": "/oneOf",
        "absoluteKeywordLocation": "#/oneOf",
        "instanceLocation": "",
        "error": "The boolean value was expected to validate against one and only one of the 2 given subschemas"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_anyof_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "First", "type": "string" },
      { "title": "Second", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/anyOf/0/type",
        "absoluteKeywordLocation": "#/anyOf/0/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type string but it was of type boolean"
      },
      {
        "keywordLocation": "/anyOf/1/type",
        "absoluteKeywordLocation": "#/anyOf/1/type",
        "instanceLocation": "",
        "error": "The value was expected to be of type integer but it was of type boolean"
      },
      {
        "keywordLocation": "/anyOf",
        "absoluteKeywordLocation": "#/anyOf",
        "instanceLocation": "",
        "error": "The boolean value was expected to validate against at least one of the 2 given subschemas"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_if_then_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "title": "Then Title", "minLength": 10 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/then/minLength",
        "absoluteKeywordLocation": "#/then/minLength",
        "instanceLocation": "",
        "error": "The string value \"foo\" was expected to consist of at least 10 characters but it consisted of 3 characters"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_if_else_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "title": "Else Title", "minimum": 100 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/else/minimum",
        "absoluteKeywordLocation": "#/else/minimum",
        "instanceLocation": "",
        "error": "The integer value 42 was expected to be greater than or equal to the integer 100"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Output_standard_basic, failure_contains_1_exhaustive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "valid": false,
    "errors": [
      {
        "keywordLocation": "/contains/type",
        "absoluteKeywordLocation": "#/contains/type",
        "instanceLocation": "/0",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/contains/type",
        "absoluteKeywordLocation": "#/contains/type",
        "instanceLocation": "/1",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/contains/type",
        "absoluteKeywordLocation": "#/contains/type",
        "instanceLocation": "/2",
        "error": "The value was expected to be of type string but it was of type integer"
      },
      {
        "keywordLocation": "/contains",
        "absoluteKeywordLocation": "#/contains",
        "instanceLocation": "",
        "error": "The array value was expected to contain at least 1 item that validates against the given subschema"
      }
    ]
  })JSON")};

  EXPECT_EQ(result, expected);
}
