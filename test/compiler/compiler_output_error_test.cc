#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/jsonpointer.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#define EXPECT_OUTPUT(traces, index, expected_instance_location,               \
                      expected_evaluate_path, expected_message)                \
  EXPECT_TRUE(traces.size() > index);                                          \
  EXPECT_EQ(traces.at((index)).message, (expected_message));                   \
  EXPECT_EQ(sourcemeta::jsontoolkit::to_string(                                \
                traces.at((index)).instance_location),                         \
            expected_instance_location);                                       \
  EXPECT_EQ(                                                                   \
      sourcemeta::jsontoolkit::to_string(traces.at((index)).evaluate_path),    \
      expected_evaluate_path);

TEST(Compiler_output_error, success_string_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};
  EXPECT_TRUE(traces.empty());
}

TEST(Compiler_output_error, fail_meaningless_if_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "foo": { "/baz": 1 },
    "bar": { "qux": {} }
  })JSON")};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 2);

  EXPECT_OUTPUT(
      traces, 0, "/foo/~1baz", "/properties/foo/unevaluatedProperties",
      "The object value was not expected to define the property \"/baz\"");
  EXPECT_OUTPUT(
      traces, 1, "/foo", "/properties/foo/unevaluatedProperties",
      "The object value was not expected to define unevaluated properties");
}

TEST(Compiler_output_error, success_dynamic_anchor_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};
  EXPECT_TRUE(traces.empty());
}

TEST(Compiler_output_error, success_oneof_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{"fo"};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};
  EXPECT_TRUE(traces.empty());
}

TEST(Compiler_output_error, fail_string) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{5};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_error, fail_string_over_ref) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{5};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/$ref/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_error, fail_string_with_matching_base) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{5};

  const std::string ref = "$ref";
  const sourcemeta::jsontoolkit::WeakPointer pointer{std::cref(ref)};
  sourcemeta::blaze::ErrorOutput output{instance, pointer};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_error, fail_string_with_non_matching_base) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{5};
  const std::string foo = "foo";
  const sourcemeta::jsontoolkit::WeakPointer pointer{std::cref(foo)};
  sourcemeta::blaze::ErrorOutput output{instance, pointer};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(
      traces, 0, "", "/$ref/type",
      "The value was expected to be of type string but it was of type integer");
}

TEST(Compiler_output_error, fail_oneof_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/oneOf",
                "The string value was expected to validate against one and "
                "only one of the 2 given subschemas");
}

TEST(Compiler_output_error, fail_not_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/not",
                "The string value was expected to not validate against the "
                "given subschema, but it did");
}

TEST(Compiler_output_error, fail_not_not_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "not": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{1};

  sourcemeta::blaze::ErrorOutput output{instance};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::ErrorOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/not",
                "The integer value was expected to not validate against the "
                "given subschema, but it did");
}
