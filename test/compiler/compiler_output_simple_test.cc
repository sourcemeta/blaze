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

#define EXPECT_ANNOTATION_COUNT(output, expected_count)                        \
  EXPECT_EQ(output.annotations().size(), (expected_count));

#define EXPECT_ANNOTATION_ENTRY(                                               \
    output, expected_instance_location, expected_evaluate_path,                \
    expected_schema_location, expected_entry_count)                            \
  {                                                                            \
    const auto instance_location{                                              \
        sourcemeta::core::to_pointer(expected_instance_location)};             \
    const auto evaluate_path{                                                  \
        sourcemeta::core::to_pointer(expected_evaluate_path)};                 \
    EXPECT_TRUE(output.annotations().contains(                                 \
        {sourcemeta::core::to_weak_pointer(instance_location),                 \
         sourcemeta::core::to_weak_pointer(evaluate_path),                     \
         (expected_schema_location)}));                                        \
    EXPECT_EQ(output.annotations()                                             \
                  .at({sourcemeta::core::to_weak_pointer(instance_location),   \
                       sourcemeta::core::to_weak_pointer(evaluate_path),       \
                       (expected_schema_location)})                            \
                  .size(),                                                     \
              (expected_entry_count));                                         \
  }

#define EXPECT_ANNOTATION_VALUE(                                               \
    output, expected_instance_location, expected_evaluate_path,                \
    expected_schema_location, expected_entry_index, expected_value)            \
  {                                                                            \
    const auto instance_location{                                              \
        sourcemeta::core::to_pointer(expected_instance_location)};             \
    const auto evaluate_path{                                                  \
        sourcemeta::core::to_pointer(expected_evaluate_path)};                 \
    EXPECT_EQ(output.annotations()                                             \
                  .at({sourcemeta::core::to_weak_pointer(instance_location),   \
                       sourcemeta::core::to_weak_pointer(evaluate_path),       \
                       (expected_schema_location)})                            \
                  .at(expected_entry_index),                                   \
              (expected_value));                                               \
  }

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

  EXPECT_ANNOTATION_COUNT(output, 0);
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

  EXPECT_ANNOTATION_COUNT(output, 0);
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

  EXPECT_ANNOTATION_COUNT(output, 0);
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

  EXPECT_ANNOTATION_COUNT(output, 0);
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

  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
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
  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(Compiler_output_simple, annotations_success_1) {
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

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
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

  EXPECT_ANNOTATION_COUNT(output, 5);

  EXPECT_ANNOTATION_ENTRY(output, "", "/properties", "#/properties", 2);
  EXPECT_ANNOTATION_VALUE(output, "", "/properties", "#/properties", 0,
                          sourcemeta::core::JSON{"bar"});
  EXPECT_ANNOTATION_VALUE(output, "", "/properties", "#/properties", 1,
                          sourcemeta::core::JSON{"foo"});

  EXPECT_ANNOTATION_ENTRY(output, "", "/title", "#/title", 1);
  EXPECT_ANNOTATION_VALUE(output, "", "/title", "#/title", 0,
                          sourcemeta::core::JSON{"My Schema"});

  EXPECT_ANNOTATION_ENTRY(output, "/foo", "/properties/foo/$ref/title",
                          "#/$defs/test/title", 1);
  EXPECT_ANNOTATION_VALUE(output, "/foo", "/properties/foo/$ref/title",
                          "#/$defs/test/title", 0,
                          sourcemeta::core::JSON{"Test"});

  EXPECT_ANNOTATION_ENTRY(output, "/foo", "/properties/foo/title",
                          "#/properties/foo/title", 1);
  EXPECT_ANNOTATION_VALUE(output, "/foo", "/properties/foo/title",
                          "#/properties/foo/title", 0,
                          sourcemeta::core::JSON{"Foo"});

  EXPECT_ANNOTATION_ENTRY(output, "/foo", "/properties/foo/deprecated",
                          "#/properties/foo/deprecated", 1);
  EXPECT_ANNOTATION_VALUE(output, "/foo", "/properties/foo/deprecated",
                          "#/properties/foo/deprecated", 0,
                          sourcemeta::core::JSON{true});
}

TEST(Compiler_output_simple, annotations_success_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "title": "First branch" },
      { "type": "string", "title": "Second branch" },
      { "title": "Third branch" }
    ]
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_ANNOTATION_COUNT(output, 2);

  EXPECT_ANNOTATION_ENTRY(output, "", "/anyOf/0/title", "#/anyOf/0/title", 1);
  EXPECT_ANNOTATION_VALUE(output, "", "/anyOf/0/title", "#/anyOf/0/title", 0,
                          sourcemeta::core::JSON{"First branch"});

  EXPECT_ANNOTATION_ENTRY(output, "", "/anyOf/2/title", "#/anyOf/2/title", 1);
  EXPECT_ANNOTATION_VALUE(output, "", "/anyOf/2/title", "#/anyOf/2/title", 0,
                          sourcemeta::core::JSON{"Third branch"});
}

TEST(Compiler_output_simple, annotations_success_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": {
      "title": "First branch",
      "type": "string"
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_ANNOTATION_COUNT(output, 0);
}

TEST(Compiler_output_simple, annotations_success_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, 1, true, 2 ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION_ENTRY(output, "", "/contains", "#/contains", 2);
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 0,
                          sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 1,
                          sourcemeta::core::JSON{2});
}

TEST(Compiler_output_simple, annotations_success_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, 1, true ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION_ENTRY(output, "", "/contains", "#/contains", 2);
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 0,
                          sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 1,
                          sourcemeta::core::JSON{2});
}

TEST(Compiler_output_simple, annotations_success_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false, true ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION_ENTRY(output, "", "/contains", "#/contains", 2);
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 0,
                          sourcemeta::core::JSON{0});
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 1,
                          sourcemeta::core::JSON{1});
}

TEST(Compiler_output_simple, annotations_success_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "boolean" }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("[ false ]")};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_ANNOTATION_COUNT(output, 1);

  EXPECT_ANNOTATION_ENTRY(output, "", "/contains", "#/contains", 1);
  EXPECT_ANNOTATION_VALUE(output, "", "/contains", "#/contains", 0,
                          sourcemeta::core::JSON{0});
}

TEST(Compiler_output_simple, annotations_failure_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo",
    "type": "string"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{5};

  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);
  EXPECT_ANNOTATION_COUNT(output, 0);
}
