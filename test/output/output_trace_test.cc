#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

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
  EXPECT_FALSE(traces.at((index)).vocabulary.first);                           \
  EXPECT_FALSE(traces.at((index)).vocabulary.second.has_value());

#define EXPECT_OUTPUT_WITH_VOCABULARY(                                         \
    traces, index, expected_type, expected_name, expected_instance_location,   \
    expected_evaluate_path, expected_keyword_location, expected_annotation,    \
    expected_vocabulary)                                                       \
  EXPECT_OUTPUT(traces, index, expected_type, expected_name,                   \
                expected_instance_location, expected_evaluate_path,            \
                expected_keyword_location, expected_annotation);               \
  EXPECT_TRUE(traces.at((index)).vocabulary.first);                            \
  EXPECT_EQ(traces.at((index)).vocabulary.second.value(),                      \
            sourcemeta::core::Vocabularies::URI{expected_vocabulary});

#define EXPECT_OUTPUT_UNKNOWN_VOCABULARY(                                      \
    traces, index, expected_type, expected_name, expected_instance_location,   \
    expected_evaluate_path, expected_keyword_location, expected_annotation)    \
  EXPECT_OUTPUT(traces, index, expected_type, expected_name,                   \
                expected_instance_location, expected_evaluate_path,            \
                expected_keyword_location, expected_annotation);               \
  EXPECT_TRUE(traces.at((index)).vocabulary.first);                            \
  EXPECT_FALSE(traces.at((index)).vocabulary.second.has_value());

TEST(Output_trace, pass_1) {
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
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "qux"
  })JSON")};

  sourcemeta::blaze::TraceOutput output{sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 4);

  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 0, Push, "LoopPropertiesMatchClosed",
                                   "", "/properties", "#/properties",
                                   std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(
      traces, 1, Push, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(
      traces, 2, Pass, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 3, Pass, "LoopPropertiesMatchClosed",
                                   "", "/properties", "#/properties",
                                   std::nullopt);
}

TEST(Output_trace, pass_annotations) {
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
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  sourcemeta::blaze::TraceOutput output{sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 7);

  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 0, Annotation, "AnnotationEmit", "",
                                   "/title", "#/title",
                                   sourcemeta::core::JSON{"Foo Bar"});
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 1, Push, "LoopPropertiesMatch", "",
                                   "/properties", "#/properties", std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 2, Annotation, "AnnotationEmit", "",
                                   "/properties", "#/properties",
                                   sourcemeta::core::JSON{"foo"});
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 3, Annotation, "AnnotationEmit", "",
                                   "/properties", "#/properties",
                                   sourcemeta::core::JSON{"bar"});
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 4, Pass, "LoopPropertiesMatch", "",
                                   "/properties", "#/properties", std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 5, Push, "LoopPropertiesExcept", "",
                                   "/additionalProperties",
                                   "#/additionalProperties", std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 6, Pass, "LoopPropertiesExcept", "",
                                   "/additionalProperties",
                                   "#/additionalProperties", std::nullopt);
}

TEST(Output_trace, pass_with_matching_prefix_1) {
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
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "qux"
  })JSON")};

  const std::string ref{"$ref"};

  sourcemeta::blaze::TraceOutput output{sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver,
                                        {std::cref(ref)}};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 4);

  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 0, Push, "LoopPropertiesMatchClosed",
                                   "", "/properties",
                                   "#/$defs/helper/properties", std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(
      traces, 1, Push, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/$defs/helper/properties/foo/type",
      std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(
      traces, 2, Pass, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/$defs/helper/properties/foo/type",
      std::nullopt);
  EXPECT_OUTPUT_WITHOUT_VOCABULARY(traces, 3, Pass, "LoopPropertiesMatchClosed",
                                   "", "/properties",
                                   "#/$defs/helper/properties", std::nullopt);
}

TEST(Output_trace, pass_with_frame_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo Bar",
    "additionalProperties": false,
    "properties": {
      "foo": { "unknown": true },
      "bar": true
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  sourcemeta::blaze::TraceOutput output{
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      sourcemeta::core::empty_weak_pointer, frame};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 8);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Annotation, "AnnotationEmit", "", "/title", "#/title",
      sourcemeta::core::JSON{"Foo Bar"},
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Meta_Data);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt,
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_UNKNOWN_VOCABULARY(traces, 2, Annotation, "AnnotationEmit",
                                   "/foo", "/properties/foo/unknown",
                                   "#/properties/foo/unknown",
                                   sourcemeta::core::JSON{true});
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"foo"},
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"bar"},
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Pass, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt,
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 6, Push, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 7, Pass, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
}

TEST(Output_trace, pass_with_frame_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo Bar",
    "additionalProperties": false,
    "properties": {
      "foo": { "unknown": true },
      "bar": true
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  sourcemeta::blaze::TraceOutput output{
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      sourcemeta::core::empty_weak_pointer, frame};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 2);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      sourcemeta::core::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
}
