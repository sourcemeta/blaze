#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <type_traits> // std::is_copy_constructible_v, etc.

#include "evaluator_utils.h"

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://example.com/metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/metaschema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://example.com/vocab/custom": true
      }
    })JSON");
  } else if (identifier == "https://example.com/schema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/schema",
      "type": "string"
    })JSON");
  } else {
    return sourcemeta::core::schema_resolver(identifier);
  }
}

TEST(Evaluator, unknown_vocabulary_required) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/metaschema"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL() << "The compile function was expected to throw";
  } catch (const sourcemeta::core::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/vocab/custom");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a vocabulary error";
  }
}

TEST(Evaluator, without_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "schema"
  })JSON")};

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::core::schema_walker, test_resolver,
                   sourcemeta::blaze::default_schema_compiler,
                   sourcemeta::blaze::Mode::FastValidation),
               sourcemeta::core::SchemaResolutionError);
}

TEST(Evaluator, with_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "schema"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "",
      "https://example.com/default")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_TRUE(result);
}

TEST(Evaluator, boolean_true) {
  const sourcemeta::core::JSON schema{true};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "https://json-schema.org/draft/2020-12/schema")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 0)
  EXPECT_TRUE(result);
}

TEST(Evaluator, boolean_false) {
  const sourcemeta::core::JSON schema{false};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "https://json-schema.org/draft/2020-12/schema")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionFail, "", "", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionFail, "", "", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "No instance is expected to succeed against the false schema");
}

TEST(Evaluator, reusable_evaluator) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;

  const sourcemeta::core::JSON instance_1{"foo bar"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance_1));

  const sourcemeta::core::JSON instance_2{"baz"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance_2));

  const sourcemeta::core::JSON instance_3{4};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance_3));

  const sourcemeta::core::JSON instance_4{"qux"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance_4));
}

TEST(Evaluator, cross_2012_12_ref_2019_09_without_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/schema",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2019-09/schema"
      }
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{"test"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(Evaluator, explicit_frame) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "$ref": "https://json-schema.org/draft/2020-12/schema" } ]
  })JSON")};

  const sourcemeta::core::JSON result{
      sourcemeta::core::bundle(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver)};
  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(result, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto compiled_schema{sourcemeta::blaze::compile(
      result, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{true};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(Evaluator, explicit_frame_locations_only) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "$ref": "https://json-schema.org/draft/2020-12/schema" } ]
  })JSON")};

  const sourcemeta::core::JSON result{
      sourcemeta::core::bundle(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver)};
  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Locations};
  frame.analyse(result, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  EXPECT_THROW(sourcemeta::blaze::compile(
                   result, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler, frame),
               sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator, is_annotation) {
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationBasenameToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationEmit));
  EXPECT_FALSE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AssertionFail));
}

TEST(Evaluator, instruction_copy_constructible) {
  EXPECT_TRUE(std::is_copy_constructible_v<sourcemeta::blaze::Instruction>);
}

TEST(Evaluator, instruction_copy_assignable) {
  EXPECT_TRUE(std::is_copy_assignable_v<sourcemeta::blaze::Instruction>);
}

TEST(Evaluator, instruction_move_constructible) {
  EXPECT_TRUE(std::is_move_constructible_v<sourcemeta::blaze::Instruction>);
}

TEST(Evaluator, instruction_move_assignable) {
  EXPECT_TRUE(std::is_move_assignable_v<sourcemeta::blaze::Instruction>);
}
