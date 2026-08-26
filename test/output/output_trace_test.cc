#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/core/jsonpointer.h>

#include <map>     // std::map
#include <sstream> // std::ostringstream
#include <string>  // std::string
#include <vector>  // std::vector

struct StoredTrace {
  sourcemeta::blaze::TraceOutput::EntryType type;
  std::string name;
  sourcemeta::core::WeakPointer instance_location;
  sourcemeta::core::WeakPointer evaluate_path;
  std::string keyword_location;
  std::optional<sourcemeta::core::JSON> annotation;
  std::optional<std::string> vocabulary;
};

static auto collect(std::vector<StoredTrace> &traces)
    -> sourcemeta::blaze::TraceOutput::Callback {
  return [&traces](const sourcemeta::blaze::TraceOutput::Entry &entry) {
    traces.push_back(
        {entry.type, std::string{entry.name}, entry.instance_location,
         entry.evaluate_path, std::string{entry.keyword_location},
         entry.type == sourcemeta::blaze::TraceOutput::EntryType::Annotation
             ? std::optional<sourcemeta::core::JSON>{entry.annotation}
             : std::nullopt,
         entry.vocabulary.has_value()
             ? std::optional<std::string>{std::string{entry.vocabulary.value()}}
             : std::nullopt});
  };
}

#define EXPECT_OUTPUT(traces, index, expected_type, expected_name,             \
                      expected_instance_location, expected_evaluate_path,      \
                      expected_keyword_location, expected_annotation)          \
  EXPECT_TRUE(traces.size() > index);                                          \
  EXPECT_EQ(traces.at((index)).type,                                           \
            sourcemeta::blaze::TraceOutput::EntryType::expected_type);         \
  EXPECT_EQ(traces.at((index)).name, expected_name);                           \
  EXPECT_EQ(sourcemeta::core::to_string(traces.at((index)).instance_location), \
            expected_instance_location);                                       \
  EXPECT_EQ(sourcemeta::core::to_string(traces.at((index)).evaluate_path),     \
            expected_evaluate_path);                                           \
  EXPECT_EQ(traces.at((index)).keyword_location, (expected_keyword_location)); \
  if (std::optional<sourcemeta::core::JSON>{expected_annotation}               \
          .has_value()) {                                                      \
    EXPECT_TRUE(traces.at((index)).annotation.has_value());                    \
    EXPECT_EQ(                                                                 \
        traces.at((index)).annotation.value(),                                 \
        std::optional<sourcemeta::core::JSON>{expected_annotation}.value());   \
  } else {                                                                     \
    EXPECT_FALSE(traces.at((index)).annotation.has_value());                   \
  }

#define EXPECT_OUTPUT_WITHOUT_VOCABULARY(                                      \
    traces, index, expected_type, expected_name, expected_instance_location,   \
    expected_evaluate_path, expected_keyword_location, expected_annotation)    \
  EXPECT_OUTPUT(traces, index, expected_type, expected_name,                   \
                expected_instance_location, expected_evaluate_path,            \
                expected_keyword_location, expected_annotation);               \
  EXPECT_FALSE(traces.at((index)).vocabulary.has_value());

#define EXPECT_OUTPUT_WITH_VOCABULARY(                                         \
    traces, index, expected_type, expected_name, expected_instance_location,   \
    expected_evaluate_path, expected_keyword_location, expected_annotation,    \
    expected_vocabulary)                                                       \
  EXPECT_OUTPUT(traces, index, expected_type, expected_name,                   \
                expected_instance_location, expected_evaluate_path,            \
                expected_keyword_location, expected_annotation);               \
  EXPECT_TRUE(traces.at((index)).vocabulary.has_value());                      \
  EXPECT_EQ(traces.at((index)).vocabulary.value(), (expected_vocabulary));

TEST(pass_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "boolean" },
      "baz": { "type": "integer" }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "qux"
  })JSON")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 4);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 2, Pass, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(pass_annotations) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo Bar",
    "additionalProperties": false,
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 7);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Annotation, "AnnotationEmit", "", "/title", "#/title",
      sourcemeta::core::JSON{"Foo Bar"},
      "https://json-schema.org/draft/2020-12/vocab/meta-data");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt, "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 2, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"foo"},
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"bar"},
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Pass, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt, "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Push, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 6, Pass, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(pass_with_matching_prefix_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/helper",
    "$defs": {
      "helper": {
        "additionalProperties": false,
        "properties": {
          "foo": { "type": "string" },
          "bar": { "type": "boolean" },
          "baz": { "type": "integer" }
        }
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "qux"
  })JSON")};

  const std::string ref{"$ref"};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{
      schema_template, collect(traces), {std::cref(ref)}};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 4);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/$defs/helper/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/$defs/helper/properties/foo/type",
      std::nullopt, "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 2, Pass, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/$defs/helper/properties/foo/type",
      std::nullopt, "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/$defs/helper/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(pass_with_frame_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo Bar",
    "additionalProperties": false,
    "properties": {
      "foo": { "unknown": true },
      "bar": true
    }
  })JSON")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 8);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Annotation, "AnnotationEmit", "", "/title", "#/title",
      sourcemeta::core::JSON{"Foo Bar"},
      "https://json-schema.org/draft/2020-12/vocab/meta-data");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt, "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 2, Annotation, "AnnotationEmit",
                                   "/foo", "/properties/foo/unknown",
                                   "#/properties/foo/unknown",
                                   sourcemeta::core::JSON{true});
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"foo"},
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"bar"},
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Pass, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt, "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 6, Push, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 7, Pass, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(pass_with_frame_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo Bar",
    "additionalProperties": false,
    "properties": {
      "foo": { "unknown": true },
      "bar": true
    }
  })JSON")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 2);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(nested_vocabulary_correctness) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": 1
  })JSON")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 6);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 2, Pass, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Push, "AssertionPropertyType", "/bar", "/properties/bar/type",
      "#/properties/bar/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Pass, "AssertionPropertyType", "/bar", "/properties/bar/type",
      "#/properties/bar/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(entry_carries_the_instruction_for_describing) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};

  std::vector<std::string> messages;
  sourcemeta::blaze::TraceOutput output{
      schema_template,
      [&messages,
       &instance](const sourcemeta::blaze::TraceOutput::Entry &entry) -> void {
        if (entry.type == sourcemeta::blaze::TraceOutput::EntryType::Push) {
          return;
        }

        const auto valid{entry.type !=
                         sourcemeta::blaze::TraceOutput::EntryType::Fail};
        messages.push_back(sourcemeta::blaze::describe(
            valid, entry.step, entry.evaluate_path, entry.instance_location,
            instance, entry.annotation));
      }};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  EXPECT_EQ(messages.size(), 1);
  EXPECT_EQ(messages.at(0), "The value was expected to be of type string but "
                            "it was of type integer");
}

TEST(vocabulary_across_schemas_through_a_reference) {
  const sourcemeta::core::JSON remote{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/remote",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/main",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/remote"
  })JSON")};

  const auto resolver{[&remote](const std::string_view identifier)
                          -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/remote") {
      return remote;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  }};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);

  EXPECT_EQ(traces.size(), 2);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "AssertionTypeStrict", "", "/$ref/type",
      "https://example.com/remote#/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Fail, "AssertionTypeStrict", "", "/$ref/type",
      "https://example.com/remote#/type", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
}

TEST(vocabulary_of_a_subschema_under_a_property_named_after_a_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "type": { "anyOf": [ { "minLength": 1 } ] }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "type": "x"
  })JSON")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{schema_template, collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_TRUE(result);

  EXPECT_EQ(traces.size(), 7);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LogicalWhenType", "", "/properties",
      "https://example.com#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "LogicalOr", "/type", "/properties/type/anyOf",
      "https://example.com#/properties/type/anyOf", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 2, Push, "AssertionStringSizeGreater", "/type",
      "/properties/type/anyOf/0/minLength",
      "https://example.com#/properties/type/anyOf/0/minLength", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Pass, "AssertionStringSizeGreater", "/type",
      "/properties/type/anyOf/0/minLength",
      "https://example.com#/properties/type/anyOf/0/minLength", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Pass, "LogicalOr", "/type", "/properties/type/anyOf",
      "https://example.com#/properties/type/anyOf", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Annotation, "AnnotationEmit", "", "/properties",
      "https://example.com#/properties", sourcemeta::core::JSON{"type"},
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 6, Pass, "LogicalWhenType", "", "/properties",
      "https://example.com#/properties", std::nullopt,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}
