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
  std::pair<bool, std::optional<sourcemeta::blaze::Vocabularies::URI>>
      vocabulary;
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
         entry.vocabulary});
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
            sourcemeta::blaze::Vocabularies::URI{expected_vocabulary});

#define EXPECT_OUTPUT_UNKNOWN_VOCABULARY(                                      \
    traces, index, expected_type, expected_name, expected_instance_location,   \
    expected_evaluate_path, expected_keyword_location, expected_annotation)    \
  EXPECT_OUTPUT(traces, index, expected_type, expected_name,                   \
                expected_instance_location, expected_evaluate_path,            \
                expected_keyword_location, expected_annotation);               \
  EXPECT_TRUE(traces.at((index)).vocabulary.first);                            \
  EXPECT_FALSE(traces.at((index)).vocabulary.second.has_value());

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
  sourcemeta::blaze::TraceOutput output{sourcemeta::blaze::schema_walker,
                                        sourcemeta::blaze::schema_resolver,
                                        collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
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
  sourcemeta::blaze::TraceOutput output{sourcemeta::blaze::schema_walker,
                                        sourcemeta::blaze::schema_resolver,
                                        collect(traces)};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
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
  sourcemeta::blaze::TraceOutput output{sourcemeta::blaze::schema_walker,
                                        sourcemeta::blaze::schema_resolver,
                                        collect(traces),
                                        {std::cref(ref)}};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
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
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(traces), sourcemeta::core::EMPTY_WEAK_POINTER, frame};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 8);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Annotation, "AnnotationEmit", "", "/title", "#/title",
      sourcemeta::core::JSON{"Foo Bar"},
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Meta_Data);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_UNKNOWN_VOCABULARY(traces, 2, Annotation, "AnnotationEmit",
                                   "/foo", "/properties/foo/unknown",
                                   "#/properties/foo/unknown",
                                   sourcemeta::core::JSON{true});
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"foo"},
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Annotation, "AnnotationEmit", "", "/properties",
      "#/properties", sourcemeta::core::JSON{"bar"},
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Pass, "LoopPropertiesMatch", "", "/properties", "#/properties",
      std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 6, Push, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 7, Pass, "LoopPropertiesExcept", "", "/additionalProperties",
      "#/additionalProperties", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
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
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(traces), sourcemeta::core::EMPTY_WEAK_POINTER, frame};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 2);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
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
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(traces), sourcemeta::core::EMPTY_WEAK_POINTER, frame};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  EXPECT_EQ(traces.size(), 6);

  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 0, Push, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 1, Push, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Validation);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 2, Pass, "AssertionPropertyTypeStrict", "/foo",
      "/properties/foo/type", "#/properties/foo/type", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Validation);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 3, Push, "AssertionPropertyType", "/bar", "/properties/bar/type",
      "#/properties/bar/type", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Validation);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 4, Pass, "AssertionPropertyType", "/bar", "/properties/bar/type",
      "#/properties/bar/type", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Validation);
  EXPECT_OUTPUT_WITH_VOCABULARY(
      traces, 5, Pass, "LoopPropertiesMatchClosed", "", "/properties",
      "#/properties", std::nullopt,
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator);
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
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
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

TEST(vocabulary_from_an_exported_frame) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto locations{frame.to_json().at("locations")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(traces), sourcemeta::core::EMPTY_WEAK_POINTER,
      [&locations](const std::string_view)
          -> std::optional<
              std::reference_wrapper<const sourcemeta::core::JSON>> {
        return std::cref(locations);
      }};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  EXPECT_FALSE(result);
  EXPECT_EQ(traces.size(), 2);

  EXPECT_TRUE(traces.at(0).vocabulary.first);
  EXPECT_TRUE(traces.at(0).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(traces.at(0).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_TRUE(traces.at(1).vocabulary.first);
  EXPECT_TRUE(traces.at(1).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(traces.at(1).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/validation");
}

TEST(vocabulary_from_an_exported_frame_matches_a_live_frame) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Foo Bar",
    "additionalProperties": false,
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  const auto locations{frame.to_json().at("locations")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz"
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;

  std::vector<StoredTrace> from_live;
  sourcemeta::blaze::TraceOutput live{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(from_live), sourcemeta::core::EMPTY_WEAK_POINTER,
      std::cref(frame)};
  const auto live_result{
      evaluator.validate(schema_template, instance, std::ref(live))};
  EXPECT_TRUE(live_result);

  std::vector<StoredTrace> from_export;
  sourcemeta::blaze::TraceOutput exported{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(from_export), sourcemeta::core::EMPTY_WEAK_POINTER,
      [&locations](const std::string_view)
          -> std::optional<
              std::reference_wrapper<const sourcemeta::core::JSON>> {
        return std::cref(locations);
      }};
  const auto export_result{
      evaluator.validate(schema_template, instance, std::ref(exported))};
  EXPECT_TRUE(export_result);

  EXPECT_EQ(from_live.size(), 7);
  EXPECT_EQ(from_export.size(), 7);

  EXPECT_EQ(from_live.at(0).keyword_location, "https://example.com#/title");
  EXPECT_TRUE(from_live.at(0).vocabulary.first);
  EXPECT_TRUE(from_live.at(0).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(0).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/meta-data");
  EXPECT_EQ(from_export.at(0).keyword_location, "https://example.com#/title");
  EXPECT_TRUE(from_export.at(0).vocabulary.first);
  EXPECT_TRUE(from_export.at(0).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(0).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/meta-data");

  EXPECT_EQ(from_live.at(1).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_live.at(1).vocabulary.first);
  EXPECT_TRUE(from_live.at(1).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(1).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_EQ(from_export.at(1).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_export.at(1).vocabulary.first);
  EXPECT_TRUE(from_export.at(1).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(1).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");

  EXPECT_EQ(from_live.at(2).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_live.at(2).vocabulary.first);
  EXPECT_TRUE(from_live.at(2).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(2).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_EQ(from_export.at(2).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_export.at(2).vocabulary.first);
  EXPECT_TRUE(from_export.at(2).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(2).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");

  EXPECT_EQ(from_live.at(3).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_live.at(3).vocabulary.first);
  EXPECT_TRUE(from_live.at(3).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(3).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_EQ(from_export.at(3).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_export.at(3).vocabulary.first);
  EXPECT_TRUE(from_export.at(3).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(3).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");

  EXPECT_EQ(from_live.at(4).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_live.at(4).vocabulary.first);
  EXPECT_TRUE(from_live.at(4).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(4).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_EQ(from_export.at(4).keyword_location,
            "https://example.com#/properties");
  EXPECT_TRUE(from_export.at(4).vocabulary.first);
  EXPECT_TRUE(from_export.at(4).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(4).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");

  EXPECT_EQ(from_live.at(5).keyword_location,
            "https://example.com#/additionalProperties");
  EXPECT_TRUE(from_live.at(5).vocabulary.first);
  EXPECT_TRUE(from_live.at(5).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(5).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_EQ(from_export.at(5).keyword_location,
            "https://example.com#/additionalProperties");
  EXPECT_TRUE(from_export.at(5).vocabulary.first);
  EXPECT_TRUE(from_export.at(5).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(5).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");

  EXPECT_EQ(from_live.at(6).keyword_location,
            "https://example.com#/additionalProperties");
  EXPECT_TRUE(from_live.at(6).vocabulary.first);
  EXPECT_TRUE(from_live.at(6).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_live.at(6).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_EQ(from_export.at(6).keyword_location,
            "https://example.com#/additionalProperties");
  EXPECT_TRUE(from_export.at(6).vocabulary.first);
  EXPECT_TRUE(from_export.at(6).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(from_export.at(6).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/applicator");
}

TEST(vocabulary_absent_when_the_export_does_not_know_the_location) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto locations{sourcemeta::core::parse_json(R"JSON({
    "static": {},
    "dynamic": {}
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(traces), sourcemeta::core::EMPTY_WEAK_POINTER,
      [&locations](const std::string_view)
          -> std::optional<
              std::reference_wrapper<const sourcemeta::core::JSON>> {
        return std::cref(locations);
      }};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);

  EXPECT_EQ(traces.size(), 2);
  EXPECT_FALSE(traces.at(0).vocabulary.first);
  EXPECT_FALSE(traces.at(0).vocabulary.second.has_value());
  EXPECT_FALSE(traces.at(1).vocabulary.first);
  EXPECT_FALSE(traces.at(1).vocabulary.second.has_value());
}
TEST(vocabulary_across_schemas_from_separate_exports) {
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

  sourcemeta::blaze::SchemaFrame main_frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  main_frame.analyse(schema, sourcemeta::blaze::schema_walker, resolver);
  sourcemeta::blaze::SchemaFrame remote_frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  remote_frame.analyse(remote, sourcemeta::blaze::schema_walker, resolver);

  std::map<std::string, sourcemeta::core::JSON> exports;
  exports.emplace("https://example.com/main",
                  main_frame.to_json().at("locations"));
  exports.emplace("https://example.com/remote",
                  remote_frame.to_json().at("locations"));

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, resolver, collect(traces),
      sourcemeta::core::EMPTY_WEAK_POINTER,
      [&exports](const std::string_view schema_uri)
          -> std::optional<
              std::reference_wrapper<const sourcemeta::core::JSON>> {
        const auto match{exports.find(std::string{schema_uri})};
        if (match == exports.cend()) {
          return std::nullopt;
        }

        return std::cref(match->second);
      }};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);

  EXPECT_EQ(traces.size(), 2);

  EXPECT_EQ(traces.at(0).type, sourcemeta::blaze::TraceOutput::EntryType::Push);
  EXPECT_EQ(traces.at(0).name, "AssertionTypeStrict");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(0).instance_location), "");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(0).evaluate_path),
            "/$ref/type");
  EXPECT_EQ(traces.at(0).keyword_location, "https://example.com/remote#/type");
  EXPECT_TRUE(traces.at(0).vocabulary.first);
  EXPECT_TRUE(traces.at(0).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(traces.at(0).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/validation");

  EXPECT_EQ(traces.at(1).type, sourcemeta::blaze::TraceOutput::EntryType::Fail);
  EXPECT_EQ(traces.at(1).name, "AssertionTypeStrict");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(1).instance_location), "");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(1).evaluate_path),
            "/$ref/type");
  EXPECT_EQ(traces.at(1).keyword_location, "https://example.com/remote#/type");
  EXPECT_TRUE(traces.at(1).vocabulary.first);
  EXPECT_TRUE(traces.at(1).vocabulary.second.has_value());
  EXPECT_EQ(
      sourcemeta::blaze::to_string(traces.at(1).vocabulary.second.value()),
      "https://json-schema.org/draft/2020-12/vocab/validation");
}

TEST(vocabulary_absent_when_the_export_names_an_unresolvable_dialect) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON locations{sourcemeta::core::parse_json(R"JSON({
    "static": {
      "https://example.com#/type": {
        "dialect": "https://example.com/unknown-meta",
        "baseDialect": "https://json-schema.org/draft/2020-12/schema"
      }
    }
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};

  std::vector<StoredTrace> traces;
  sourcemeta::blaze::TraceOutput output{
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver,
      collect(traces), sourcemeta::core::EMPTY_WEAK_POINTER,
      [&locations](const std::string_view)
          -> std::optional<
              std::reference_wrapper<const sourcemeta::core::JSON>> {
        return std::cref(locations);
      }};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};
  EXPECT_FALSE(result);

  EXPECT_EQ(traces.size(), 2);

  EXPECT_EQ(traces.at(0).type, sourcemeta::blaze::TraceOutput::EntryType::Push);
  EXPECT_EQ(traces.at(0).name, "AssertionTypeStrict");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(0).instance_location), "");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(0).evaluate_path), "/type");
  EXPECT_EQ(traces.at(0).keyword_location, "https://example.com#/type");
  EXPECT_FALSE(traces.at(0).vocabulary.first);
  EXPECT_FALSE(traces.at(0).vocabulary.second.has_value());

  EXPECT_EQ(traces.at(1).type, sourcemeta::blaze::TraceOutput::EntryType::Fail);
  EXPECT_EQ(traces.at(1).name, "AssertionTypeStrict");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(1).instance_location), "");
  EXPECT_EQ(sourcemeta::core::to_string(traces.at(1).evaluate_path), "/type");
  EXPECT_EQ(traces.at(1).keyword_location, "https://example.com#/type");
  EXPECT_FALSE(traces.at(1).vocabulary.first);
  EXPECT_FALSE(traces.at(1).vocabulary.second.has_value());
}
