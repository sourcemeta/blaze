#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#define EXPECT_OUTPUT(traces, index, expected_instance_location,               \
                      expected_evaluate_path, expected_message)                \
  EXPECT_TRUE(traces.size() > index);                                          \
  EXPECT_EQ(traces.at((index)).message, (expected_message));                   \
  EXPECT_EQ(sourcemeta::core::to_string(traces.at((index)).instance_location), \
            expected_instance_location);                                       \
  EXPECT_EQ(sourcemeta::core::to_string(traces.at((index)).evaluate_path),     \
            expected_evaluate_path);

TEST(Compiler_output_simple, success_string_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());
}

TEST(Compiler_output_simple, fail_meaningless_if_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "object", "unevaluatedProperties": false },
      "bar": {
        "additionalProperties": {
          "if": {
            "type": "object",
            "required": [ "$ref" ]
          }
        }
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": { "/baz": 1 },
    "bar": { "qux": {} }
  })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 2);

  EXPECT_OUTPUT(
      traces, 0, "/foo/~1baz", "/properties/foo/unevaluatedProperties",
      "The object value was not expected to define the property \"/baz\"");
  EXPECT_OUTPUT(
      traces, 1, "/foo", "/properties/foo/unevaluatedProperties",
      "The object value was not expected to define unevaluated properties");
}

TEST(Compiler_output_simple, success_dynamic_anchor_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#foo",
    "$defs": {
      "test": {
        "$dynamicAnchor": "foo",
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());
}

TEST(Compiler_output_simple, success_oneof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"fo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());
}

TEST(Compiler_output_simple, fail_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_simple, fail_string_over_ref) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/$ref/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_simple, fail_string_with_matching_base) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{5};

  const std::string ref = "$ref";
  const sourcemeta::core::WeakPointer pointer{std::cref(ref)};
  sourcemeta::blaze::SimpleOutput output{instance, pointer};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_simple, fail_string_with_non_matching_base) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{5};
  const std::string foo = "foo";
  const sourcemeta::core::WeakPointer pointer{std::cref(foo)};
  sourcemeta::blaze::SimpleOutput output{instance, pointer};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/$ref/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_simple, fail_oneof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/oneOf",
                "The string value was expected to validate against one and "
                "only one of the 2 given subschemas");
}

TEST(Compiler_output_simple, fail_not_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/not",
                "The string value was expected to not validate against the "
                "given subschema, but it did");
}

TEST(Compiler_output_simple, fail_not_not_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "not": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{1};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/not",
                "The integer value was expected to not validate against the "
                "given subschema, but it did");
}

TEST(Compiler_output_simple, fail_anyof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "anyOf": [
          { "required": [ "foo" ] },
          { "required": [ "bar" ] }
        ]
      },
      { "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "bar": 1
  })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/allOf/1/type",
      "The value was expected to be of type integer but it was of type object");
}

TEST(Compiler_output_simple, fail_anyof_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "baz": 1
  })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/anyOf",
                "The object value was expected to validate against at least "
                "one of the 2 given subschemas");
}
