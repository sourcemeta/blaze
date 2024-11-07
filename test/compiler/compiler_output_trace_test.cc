#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/jsonpointer.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#ifdef __clang__
#define EXPECT_OUTPUT(traces, index, expected_type, expected_name,             \
                      expected_instance_location, expected_evaluate_path)      \
  EXPECT_TRUE(traces.size() > index);                                          \
  EXPECT_EQ(traces.at((index)).type,                                           \
            sourcemeta::blaze::TraceOutput::EntryType::expected_type);         \
  EXPECT_EQ(traces.at((index)).name, (expected_name));                         \
  EXPECT_EQ(sourcemeta::jsontoolkit::to_string(                                \
                traces.at((index)).instance_location),                         \
            expected_instance_location);                                       \
  EXPECT_EQ(                                                                   \
      sourcemeta::jsontoolkit::to_string(traces.at((index)).evaluate_path),    \
      expected_evaluate_path);
#else
#define EXPECT_OUTPUT(traces, index, expected_type, expected_name,             \
                      expected_instance_location, expected_evaluate_path)      \
  EXPECT_TRUE(traces.size() > index);                                          \
  EXPECT_EQ(traces.at((index)).type,                                           \
            sourcemeta::blaze::TraceOutput::EntryType::expected_type);         \
  EXPECT_EQ(traces.at((index)).name, "????");                                  \
  EXPECT_EQ(sourcemeta::jsontoolkit::to_string(                                \
                traces.at((index)).instance_location),                         \
            expected_instance_location);                                       \
  EXPECT_EQ(                                                                   \
      sourcemeta::jsontoolkit::to_string(traces.at((index)).evaluate_path),    \
      expected_evaluate_path);
#endif

TEST(Compiler_output_trace, pass_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "boolean" },
      "baz": { "type": "integer" }
    }
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "foo": "qux"
  })JSON")};

  sourcemeta::blaze::TraceOutput output;
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 4);

  EXPECT_OUTPUT(traces, 0, Push, "AssertionPropertyTypeStrict", "/foo",
                "/properties/foo/type");
  EXPECT_OUTPUT(traces, 1, Pass, "AssertionPropertyTypeStrict", "/foo",
                "/properties/foo/type");
  EXPECT_OUTPUT(traces, 2, Push, "LoopPropertiesWhitelist", "",
                "/additionalProperties");
  EXPECT_OUTPUT(traces, 3, Pass, "LoopPropertiesWhitelist", "",
                "/additionalProperties");
}

TEST(Compiler_output_trace, pass_with_matching_prefix_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "foo": "qux"
  })JSON")};

  const std::string ref{"$ref"};
  sourcemeta::blaze::TraceOutput output{{std::cref(ref)}};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, std::ref(output))};

  EXPECT_TRUE(result);
  std::vector<sourcemeta::blaze::TraceOutput::Entry> traces{output.cbegin(),
                                                            output.cend()};

  EXPECT_EQ(traces.size(), 4);

  EXPECT_OUTPUT(traces, 0, Push, "AssertionPropertyTypeStrict", "/foo",
                "/properties/foo/type");
  EXPECT_OUTPUT(traces, 1, Pass, "AssertionPropertyTypeStrict", "/foo",
                "/properties/foo/type");
  EXPECT_OUTPUT(traces, 2, Push, "LoopPropertiesWhitelist", "",
                "/additionalProperties");
  EXPECT_OUTPUT(traces, 3, Pass, "LoopPropertiesWhitelist", "",
                "/additionalProperties");
}
