#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <vector>        // std::vector

#define EXPECT_OUTPUT(traces, index, expected_instance_location,               \
                      expected_evaluate_path, expected_schema_location,        \
                      expected_message)                                        \
  EXPECT_TRUE(traces.size() > index);                                          \
  EXPECT_EQ(traces.at((index)).message, (expected_message));                   \
  EXPECT_EQ(sourcemeta::core::to_string(traces.at((index)).instance_location), \
            expected_instance_location);                                       \
  EXPECT_EQ(sourcemeta::core::to_string(traces.at((index)).evaluate_path),     \
            expected_evaluate_path);                                           \
  EXPECT_EQ(traces.at((index)).schema_location.get(),                          \
            (expected_schema_location));

#define EXPECT_ANNOTATION_COUNT(output, expected_count)                        \
  EXPECT_EQ(output.annotations().size(), (expected_count));

#define EXPECT_ANNOTATION(output, index, expected_instance_location,           \
                          expected_evaluate_path, expected_schema_location,    \
                          expected_value)                                      \
  {                                                                            \
    EXPECT_TRUE(output.annotations().size() > (index));                        \
    const auto &annotation{output.annotations().at(index)};                    \
    EXPECT_EQ(sourcemeta::core::to_string(annotation.instance_location),       \
              (expected_instance_location));                                   \
    EXPECT_EQ(sourcemeta::core::to_string(annotation.evaluate_path),           \
              (expected_evaluate_path));                                       \
    EXPECT_EQ(annotation.schema_location.get(), (expected_schema_location));   \
    EXPECT_EQ(annotation.value, (expected_value));                             \
  }

TEST(success_string_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_meaningless_if_1) {
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

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      "#/properties/foo/unevaluatedProperties",
      "The object value was not expected to define the property \"/baz\"");
  EXPECT_OUTPUT(
      traces, 1, "/foo", "/properties/foo/unevaluatedProperties",
      "#/properties/foo/unevaluatedProperties",
      "The object value was not expected to define unevaluated properties");

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_dynamic_anchor_1) {
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

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_oneof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_anyof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_not_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      traces, 0, "", "/type", "#/type",
      "The value was expected to be of type string but it was of type integer");

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(release_yields_collected_errors_and_consumes_them) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);

  const auto entries{std::move(output).release()};

  EXPECT_EQ(entries.size(), 1);
  EXPECT_OUTPUT(
      entries, 0, "", "/type", "#/type",
      "The value was expected to be of type string but it was of type integer");

  EXPECT_TRUE(output.cbegin() == output.cend());
}

TEST(release_yields_no_errors_on_success) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);

  const auto entries{std::move(output).release()};

  EXPECT_TRUE(entries.empty());
}

TEST(fail_string_over_ref) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      traces, 0, "", "/$ref/type", "#/$defs/string/type",
      "The value was expected to be of type string but it was of type integer");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_string_with_matching_base) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      traces, 0, "", "/type", "#/$defs/string/type",
      "The value was expected to be of type string but it was of type integer");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_string_with_non_matching_base) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/string",
    "$defs": {
      "string": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      traces, 0, "", "/$ref/type", "#/$defs/string/type",
      "The value was expected to be of type string but it was of type integer");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_oneof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 3 }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
  EXPECT_OUTPUT(traces, 0, "", "/oneOf", "#/oneOf",
                "The string value was expected to validate against one and "
                "only one of the 2 given subschemas");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_oneof_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 3);
  EXPECT_OUTPUT(
      traces, 0, "", "/oneOf/0/type", "#/oneOf/0/type",
      "The value was expected to be of type string but it was of type boolean");
  EXPECT_OUTPUT(traces, 1, "", "/oneOf/1/type", "#/oneOf/1/type",
                "The value was expected to be of type integer but it was of "
                "type boolean");
  EXPECT_OUTPUT(traces, 2, "", "/oneOf", "#/oneOf",
                "The boolean value was expected to validate against one and "
                "only one of the 2 given subschemas");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_not_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
  EXPECT_OUTPUT(traces, 0, "", "/not", "#/not",
                "The string value was expected to not validate against the "
                "given subschema, but it did");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_not_not_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "not": {
        "type": "string"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
  EXPECT_OUTPUT(traces, 0, "", "/not", "#/not",
                "The integer value was expected to not validate against the "
                "given subschema, but it did");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_anyof_1) {
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

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      traces, 0, "", "/allOf/1/type", "#/allOf/1/type",
      "The value was expected to be of type integer but it was of type object");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_anyof_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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

  EXPECT_EQ(traces.size(), 3);
  EXPECT_OUTPUT(traces, 0, "", "/anyOf/0/required", "#/anyOf/0/required",
                "The object value was expected to define the property \"foo\"");
  EXPECT_OUTPUT(traces, 1, "", "/anyOf/1/required", "#/anyOf/1/required",
                "The object value was expected to define the property \"bar\"");
  EXPECT_OUTPUT(traces, 2, "", "/anyOf", "#/anyOf",
                "The object value was expected to validate against at least "
                "one of the 2 given subschemas");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_if_then_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "minLength": 3 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foobar"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 0);
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_if_else_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "minimum": 0 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 0);
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_if_then_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "minLength": 10 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
  EXPECT_OUTPUT(traces, 0, "", "/then/minLength", "#/then/minLength",
                "The string value \"foo\" was expected to consist of at least "
                "10 characters but it consisted of 3 characters");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_if_else_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "minimum": 100 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/else/minimum", "#/else/minimum",
                "The integer value 42 was expected to be greater than or equal "
                "to the integer 100");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_contains_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "contains": { "type": "string" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, \"foo\", 3 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 0);
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_contains_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "contains": { "type": "string" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 4);
  EXPECT_OUTPUT(traces, 0, "/0", "/contains/type", "#/contains/type",
                "The value was expected to be of type string but it was of "
                "type integer");
  EXPECT_OUTPUT(traces, 1, "/1", "/contains/type", "#/contains/type",
                "The value was expected to be of type string but it was of "
                "type integer");
  EXPECT_OUTPUT(traces, 2, "/2", "/contains/type", "#/contains/type",
                "The value was expected to be of type string but it was of "
                "type integer");
  EXPECT_OUTPUT(traces, 3, "", "/contains", "#/contains",
                "The array value was expected to contain at least 1 item that "
                "validates against the given subschema");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_contains_mincontains_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" },
    "minContains": 2
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, \"foo\", 2, \"bar\" ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 0);
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(success_contains_maxcontains_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" },
    "maxContains": 2
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, \"foo\", 2 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 0);
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_contains_mincontains_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" },
    "minContains": 2
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 4);
  EXPECT_OUTPUT(traces, 0, "/0", "/contains/type", "#/contains/type",
                "The value was expected to be of type string but it was of "
                "type integer");
  EXPECT_OUTPUT(traces, 1, "/1", "/contains/type", "#/contains/type",
                "The value was expected to be of type string but it was of "
                "type integer");
  EXPECT_OUTPUT(traces, 2, "/2", "/contains/type", "#/contains/type",
                "The value was expected to be of type string but it was of "
                "type integer");
  EXPECT_OUTPUT(traces, 3, "", "/contains", "#/contains",
                "The array value was expected to contain at least 2 items "
                "that validate against the given subschema");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_contains_maxcontains_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "string" },
    "maxContains": 1
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", \"bar\" ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/contains", "#/contains",
                "The array value was expected to contain exactly 1 item that "
                "validates against the given subschema");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(fail_nested_oneof_anyof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "anyOf": [ { "type": "string" }, { "type": "integer" } ] },
      { "type": "boolean" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON{nullptr}};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 5);
  EXPECT_OUTPUT(
      traces, 0, "", "/oneOf/0/anyOf/0/type", "#/oneOf/0/anyOf/0/type",
      "The value was expected to be of type string but it was of type null");
  EXPECT_OUTPUT(
      traces, 1, "", "/oneOf/0/anyOf/1/type", "#/oneOf/0/anyOf/1/type",
      "The value was expected to be of type integer but it was of type null");
  EXPECT_OUTPUT(
      traces, 2, "", "/oneOf/0/anyOf", "#/oneOf/0/anyOf",
      "The null value was expected to validate against at least one of the 2 "
      "given subschemas");
  EXPECT_OUTPUT(
      traces, 3, "", "/oneOf/1/type", "#/oneOf/1/type",
      "The value was expected to be of type boolean but it was of type null");
  EXPECT_OUTPUT(traces, 4, "", "/oneOf", "#/oneOf",
                "The null value was expected to validate against one and only "
                "one of the 2 given subschemas");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(annotations_failure_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "title": "Foo", "type": "string" },
      "bar": { "title": "Bar" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": 5,
    "bar": "hello"
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
      traces, 0, "/foo", "/properties/foo/type", "#/properties/foo/type",
      "The value was expected to be of type string but it was of type integer");
  EXPECT_OUTPUT(traces, 1, "", "/properties", "#/properties",
                "The object value was expected to validate against the defined "
                "properties "
                "subschemas");

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "/bar", "/properties/bar/title",
                    "#/properties/bar/title", sourcemeta::core::JSON{"Bar"});
}

TEST(annotations_success_oneof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "title": "First", "type": "string" },
      { "title": "Second", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "", "/oneOf/1/title", "#/oneOf/1/title",
                    sourcemeta::core::JSON{"Second"});
}

TEST(annotations_success_whitelist_oneof_within_object_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": {
        "oneOf": [
          { "type": "string", "x-custom": "First" },
          { "type": "integer", "x-custom": "Second" }
        ]
      }
    }
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"x-custom"};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "value": "foo" })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "/value", "/properties/value/oneOf/0/x-custom",
                    "#/properties/value/oneOf/0/x-custom",
                    sourcemeta::core::JSON{"First"});
}

TEST(annotations_success_if_then_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "title": "Then Title", "minLength": 3 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{"foobar"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "", "/then/title", "#/then/title",
                    sourcemeta::core::JSON{"Then Title"});
}

TEST(annotations_success_if_else_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "else": { "title": "Else Title", "minimum": 0 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "", "/else/title", "#/else/title",
                    sourcemeta::core::JSON{"Else Title"});
}

TEST(annotations_failure_oneof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "title": "First", "type": "string" },
      { "title": "Second", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 3);
  EXPECT_OUTPUT(
      traces, 0, "", "/oneOf/0/type", "#/oneOf/0/type",
      "The value was expected to be of type string but it was of type boolean");
  EXPECT_OUTPUT(traces, 1, "", "/oneOf/1/type", "#/oneOf/1/type",
                "The value was expected to be of type integer but it was of "
                "type boolean");
  EXPECT_OUTPUT(traces, 2, "", "/oneOf", "#/oneOf",
                "The boolean value was expected to validate against one and "
                "only one of the 2 given subschemas");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(annotations_failure_anyof_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "First", "type": "string" },
      { "title": "Second", "type": "integer" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 3);
  EXPECT_OUTPUT(
      traces, 0, "", "/anyOf/0/type", "#/anyOf/0/type",
      "The value was expected to be of type string but it was of type boolean");
  EXPECT_OUTPUT(traces, 1, "", "/anyOf/1/type", "#/anyOf/1/type",
                "The value was expected to be of type integer but it was of "
                "type boolean");
  EXPECT_OUTPUT(traces, 2, "", "/anyOf", "#/anyOf",
                "The boolean value was expected to validate against at least "
                "one of the 2 given subschemas");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(annotations_failure_if_then_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "title": "Then Title", "minLength": 10 }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{"foo"};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};

  EXPECT_EQ(traces.size(), 1);
  EXPECT_OUTPUT(traces, 0, "", "/then/minLength", "#/then/minLength",
                "The string value \"foo\" was expected to consist of at least "
                "10 characters but it consisted of 3 characters");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(annotations_success_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My Schema",
    "properties": {
      "foo": {
        "title": "Foo",
        "deprecated": true,
        "$ref": "#/$defs/test"
      },
      "bar": true
    },
    "$defs": {
      "test": {
        "title": "Test"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 6);

  EXPECT_ANNOTATION(output, 0, "", "/title", "#/title",
                    sourcemeta::core::JSON{"My Schema"});
  EXPECT_ANNOTATION(output, 1, "", "/properties", "#/properties",
                    sourcemeta::core::JSON{"bar"});
  EXPECT_ANNOTATION(output, 2, "/foo", "/properties/foo/$ref/title",
                    "#/$defs/test/title", sourcemeta::core::JSON{"Test"});
  EXPECT_ANNOTATION(output, 3, "/foo", "/properties/foo/deprecated",
                    "#/properties/foo/deprecated",
                    sourcemeta::core::JSON{true});
  EXPECT_ANNOTATION(output, 4, "/foo", "/properties/foo/title",
                    "#/properties/foo/title", sourcemeta::core::JSON{"Foo"});
  EXPECT_ANNOTATION(output, 5, "", "/properties", "#/properties",
                    sourcemeta::core::JSON{"foo"});
}

TEST(annotations_success_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "First branch" },
      { "type": "string", "title": "Second branch" },
      { "title": "Third branch" }
    ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION(output, 0, "", "/anyOf/0/title", "#/anyOf/0/title",
                    sourcemeta::core::JSON{"First branch"});
  EXPECT_ANNOTATION(output, 1, "", "/anyOf/2/title", "#/anyOf/2/title",
                    sourcemeta::core::JSON{"Third branch"});
}

TEST(annotations_success_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "title": "First branch",
      "type": "string"
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(annotations_success_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, 1, true, 2 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION(output, 0, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION(output, 1, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{2});
}

TEST(annotations_success_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, 1, true ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION(output, 0, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION(output, 1, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{2});
}

TEST(annotations_success_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, true ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION(output, 0, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION(output, 1, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{1});
}

TEST(annotations_success_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{0});
}

TEST(annotations_success_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ 1, 2, 3, 4 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 4);

  EXPECT_ANNOTATION(output, 0, "", "/unevaluatedItems", "#/unevaluatedItems",
                    sourcemeta::core::JSON{true});
  EXPECT_ANNOTATION(output, 1, "", "/unevaluatedItems", "#/unevaluatedItems",
                    sourcemeta::core::JSON{true});
  EXPECT_ANNOTATION(output, 2, "", "/unevaluatedItems", "#/unevaluatedItems",
                    sourcemeta::core::JSON{true});
  EXPECT_ANNOTATION(output, 3, "", "/unevaluatedItems", "#/unevaluatedItems",
                    sourcemeta::core::JSON{true});
}

TEST(annotations_success_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" },
    "unevaluatedItems": { "type": "number" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ true, 1, false, 2 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 4);

  EXPECT_ANNOTATION(output, 0, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION(output, 1, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{2});
  EXPECT_ANNOTATION(output, 2, "", "/unevaluatedItems", "#/unevaluatedItems",
                    sourcemeta::core::JSON{true});
  EXPECT_ANNOTATION(output, 3, "", "/unevaluatedItems", "#/unevaluatedItems",
                    sourcemeta::core::JSON{true});
}

TEST(annotations_success_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "number", "title": "Test" }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ \"foo\", 42, true ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION(output, 0, "/1", "/contains/title", "#/contains/title",
                    sourcemeta::core::JSON{"Test"});
  EXPECT_ANNOTATION(output, 1, "", "/contains", "#/contains",
                    sourcemeta::core::JSON{1});
}

TEST(annotations_failure_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

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
      traces, 0, "", "/type", "#/type",
      "The value was expected to be of type string but it was of type integer");
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(annotations_success_anyof_failed_branch_nested_property_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "payment": {
        "anyOf": [
          {
            "properties": {
              "amount": { "title": "Wrong" },
              "kind": {
                "type": "number",
                "minimum": 5,
                "maximum": 10,
                "multipleOf": 2
              }
            }
          },
          {
            "properties": {
              "amount": { "title": "Right" }
            }
          }
        ]
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "payment": { "amount": "hi", "kind": 999 } })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 3);

  EXPECT_ANNOTATION(output, 0, "/payment/amount",
                    "/properties/payment/anyOf/1/properties/amount/title",
                    "#/properties/payment/anyOf/1/properties/amount/title",
                    sourcemeta::core::JSON{"Right"});
  EXPECT_ANNOTATION(output, 1, "/payment",
                    "/properties/payment/anyOf/1/properties",
                    "#/properties/payment/anyOf/1/properties",
                    sourcemeta::core::JSON{"amount"});
  EXPECT_ANNOTATION(output, 2, "", "/properties", "#/properties",
                    sourcemeta::core::JSON{"payment"});
}

TEST(annotations_success_anyof_failed_branch_nested_property_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "payment": {
        "anyOf": [
          {
            "properties": {
              "amount": { "title": "Wrong" },
              "kind": { "const": 4 }
            }
          },
          {
            "properties": {
              "amount": { "title": "Right" }
            }
          }
        ]
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "payment": { "amount": "hi", "kind": 999 } })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 3);

  EXPECT_ANNOTATION(output, 0, "/payment/amount",
                    "/properties/payment/anyOf/1/properties/amount/title",
                    "#/properties/payment/anyOf/1/properties/amount/title",
                    sourcemeta::core::JSON{"Right"});
  EXPECT_ANNOTATION(output, 1, "/payment",
                    "/properties/payment/anyOf/1/properties",
                    "#/properties/payment/anyOf/1/properties",
                    sourcemeta::core::JSON{"amount"});
  EXPECT_ANNOTATION(output, 2, "", "/properties", "#/properties",
                    sourcemeta::core::JSON{"payment"});
}

TEST(annotations_success_whitelist_anyof_failed_branch_nested_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "payment": {
        "anyOf": [
          {
            "properties": {
              "amount": { "x-custom": "Wrong" },
              "kind": {
                "type": "number",
                "minimum": 5,
                "maximum": 10,
                "multipleOf": 2
              }
            }
          },
          {
            "properties": {
              "amount": { "x-custom": "Right" }
            }
          }
        ]
      }
    }
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"x-custom"};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "payment": { "amount": "hi", "kind": 999 } })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION(output, 0, "/payment/amount",
                    "/properties/payment/anyOf/1/properties/amount/x-custom",
                    "#/properties/payment/anyOf/1/properties/amount/x-custom",
                    sourcemeta::core::JSON{"Right"});
}

TEST(annotations_success_oneof_failed_branch_nested_property_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "payment": {
        "oneOf": [
          {
            "properties": {
              "amount": { "title": "Wrong" },
              "kind": {
                "type": "number",
                "minimum": 5,
                "maximum": 10,
                "multipleOf": 2
              }
            }
          },
          {
            "properties": {
              "amount": { "title": "Right" },
              "kind": { "const": 999 }
            }
          }
        ]
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "payment": { "amount": "hi", "kind": 999 } })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 4);

  EXPECT_ANNOTATION(output, 0, "/payment",
                    "/properties/payment/oneOf/1/properties",
                    "#/properties/payment/oneOf/1/properties",
                    sourcemeta::core::JSON{"kind"});
  EXPECT_ANNOTATION(output, 1, "/payment/amount",
                    "/properties/payment/oneOf/1/properties/amount/title",
                    "#/properties/payment/oneOf/1/properties/amount/title",
                    sourcemeta::core::JSON{"Right"});
  EXPECT_ANNOTATION(output, 2, "/payment",
                    "/properties/payment/oneOf/1/properties",
                    "#/properties/payment/oneOf/1/properties",
                    sourcemeta::core::JSON{"amount"});
  EXPECT_ANNOTATION(output, 3, "", "/properties", "#/properties",
                    sourcemeta::core::JSON{"payment"});
}

TEST(annotations_success_if_else_failed_branch_nested_property_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "amount": { "title": "Wrong" },
        "kind": {
          "type": "number",
          "minimum": 5,
          "maximum": 10,
          "multipleOf": 2
        }
      }
    },
    "else": {
      "properties": {
        "amount": { "title": "Right" }
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "amount": "hi", "kind": 999 })JSON")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::SimpleOutput::Entry> traces{output.cbegin(),
                                                             output.cend()};
  EXPECT_TRUE(traces.empty());

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION(output, 0, "/amount", "/else/properties/amount/title",
                    "#/else/properties/amount/title",
                    sourcemeta::core::JSON{"Right"});
  EXPECT_ANNOTATION(output, 1, "", "/else/properties", "#/else/properties",
                    sourcemeta::core::JSON{"amount"});
}
