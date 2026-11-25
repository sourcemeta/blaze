#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>

#include <optional>      // std::optional
#include <string>        // std::string
#include <string_view>   // std::string_view
#include <type_traits>   // std::is_copy_constructible_v, etc.
#include <unordered_set> // std::unordered_set

#include "evaluator_utils.h"

static auto test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://example.com/metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/metaschema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://example.com/vocab/custom": true
      }
    })JSON");
  }
  if (identifier ==
      "https://example.com/metaschema-unsupported-required-vocab") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/metaschema-unsupported-required-vocab",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://example.com/vocab/unsupported-fictional": true
      }
    })JSON");
  }
  if (identifier == "https://example.com/schema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/schema",
      "type": "string"
    })JSON");
  }
  if (identifier == "https://example.com/anonymous-draft4") {
    return sourcemeta::core::parse_json(R"JSON({
      "minimum": 2,
      "exclusiveMinimum": true
    })JSON");
  }
  if (identifier == "https://example.com/anonymous-draft7") {
    return sourcemeta::core::parse_json(R"JSON({
      "definitions": {
        "helper": { "type": "string" }
      },
      "allOf": [ { "$ref": "#/definitions/helper", "type": "integer" } ]
    })JSON");
  }
  if (identifier == "https://example.com/anonymous-embedded") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-04/schema#",
      "id": "https://example.com/anonymous-embedded",
      "allOf": [ { "$ref": "shared" } ],
      "definitions": {
        "https://example.com/shared": {
          "id": "https://example.com/shared",
          "type": "string"
        }
      }
    })JSON");
  }
  return sourcemeta::core::schema_resolver(identifier);
}

TEST(unknown_vocabulary_required) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/metaschema"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::core::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/vocab/custom");
  } catch (const std::exception &) {
    FAIL();
  }
}

TEST(without_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "schema"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation);
    FAIL();
  } catch (const sourcemeta::core::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the reference to an external schema");
  }
}

TEST(with_default_id) {
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

TEST(integer_lower_bound_real_beyond_integer_range) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0
  })JSON")};

  const sourcemeta::core::JSON instance{1.0e19};
  EXPECT_TRUE(instance.is_real());
  EXPECT_TRUE(instance.is_integral());

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerLowerBound, "/minimum", "#/minimum",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeIntegerLowerBound, "/minimum",
                              "#/minimum", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer above the given minimum");
}

TEST(integer_lower_bound_real_needs_exact_decimal_conversion) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 1000000000000000110
  })JSON")};

  const sourcemeta::core::JSON instance{1000000000000000128.0};
  EXPECT_TRUE(instance.is_real());
  EXPECT_TRUE(instance.is_integral());

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerLowerBound, "/minimum", "#/minimum",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeIntegerLowerBound, "/minimum",
                              "#/minimum", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer above the given minimum");
}

TEST(reuse_after_a_template_that_opens_frames) {
  // A disjunction makes the dependency dynamic, which is what keeps the
  // keyword from being compiled away into a static property filter
  const sourcemeta::core::JSON tracking{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "properties": { "foo": true } } ],
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::core::JSON plain{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": { "type": "string" } }
  })JSON")};

  const auto tracking_template{
      sourcemeta::blaze::compile(tracking, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  const auto plain_template{sourcemeta::blaze::compile(
      plain, sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  EXPECT_TRUE(tracking_template.frames);
  EXPECT_FALSE(plain_template.frames);

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_TRUE(evaluator.validate(tracking_template, instance));
  EXPECT_TRUE(evaluator.validate(plain_template, instance));
  EXPECT_TRUE(evaluator.validate(tracking_template, instance));
}

TEST(boolean_true_exhaustive) {
  const sourcemeta::core::JSON schema{true};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_WITH_DEFAULT_DIALECT(
      schema, instance, 0, "https://json-schema.org/draft/2020-12/schema");
}

TEST(boolean_false_exhaustive) {
  const sourcemeta::core::JSON schema{false};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_WITH_DEFAULT_DIALECT(
      schema, instance, 1, "https://json-schema.org/draft/2020-12/schema");

  EVALUATE_TRACE_PRE(0, AssertionFail, "", "", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionFail, "", "", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "No instance is expected to succeed against the false schema");
}

TEST(boolean_true) {
  const sourcemeta::core::JSON schema{true};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS_WITH_DEFAULT_DIALECT(
      schema, instance, 0, "https://json-schema.org/draft/2020-12/schema");
}

TEST(boolean_false) {
  const sourcemeta::core::JSON schema{false};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE_FAST_FAILURE_WITH_DEFAULT_DIALECT(
      schema, instance, 1, "https://json-schema.org/draft/2020-12/schema");

  EVALUATE_TRACE_PRE(0, AssertionFail, "", "", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionFail, "", "", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "No instance is expected to succeed against the false schema");
}

TEST(reusable_evaluator) {
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

TEST(cross_2012_12_ref_2019_09_without_id) {
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

TEST(cross_2020_12_ref_anonymous_with_draft4_default_dialect_valid) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/anonymous-draft4"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "http://json-schema.org/draft-04/schema#")};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{3};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(cross_2020_12_ref_anonymous_with_draft4_default_dialect_invalid) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/anonymous-draft4"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "http://json-schema.org/draft-04/schema#")};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{2};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(cross_2020_12_ref_anonymous_with_draft7_default_dialect_valid) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/anonymous-draft7"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "http://json-schema.org/draft-07/schema#")};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{"foo"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(cross_2020_12_ref_anonymous_with_draft7_default_dialect_invalid) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/anonymous-draft7"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "http://json-schema.org/draft-07/schema#")};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{5};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(cross_2020_12_ref_draft4_anonymous_embedded_valid) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/anonymous-embedded"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{"foo"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(cross_2020_12_ref_draft4_anonymous_embedded_invalid) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/anonymous-embedded"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{5};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(explicit_frame) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "$ref": "https://json-schema.org/draft/2020-12/schema" } ]
  })JSON")};

  const sourcemeta::core::JSON result{
      sourcemeta::core::schema_bundle(schema, sourcemeta::core::schema_walker,
                                      sourcemeta::core::schema_resolver)};
  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, result,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  const auto compiled_schema{sourcemeta::blaze::compile(
      result, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root())};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{true};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(explicit_frame_locations_only) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "$ref": "https://json-schema.org/draft/2020-12/schema" } ]
  })JSON")};

  const sourcemeta::core::JSON result{
      sourcemeta::core::schema_bundle(schema, sourcemeta::core::schema_walker,
                                      sourcemeta::core::schema_resolver)};
  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Locations, result,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  try {
    sourcemeta::blaze::compile(result, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               frame, frame.root());
    FAIL();
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_STREQ(error.what(), "Could not resolve schema reference");
  }
}

TEST(explicit_frame_unaddressable_static_reference_target) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/unaddressable",
    "$defs": {
      "https://example.com/unaddressable": {
        "id": "https://example.com/unaddressable",
        "type": "string"
      }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               frame, frame.root());
    FAIL();
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "The referenced schema is not considered to be a valid "
                 "subschema given the dialect and vocabularies in use");
    EXPECT_EQ(error.identifier(), "https://example.com/unaddressable");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"$ref"}));
  }
}

TEST(explicit_frame_with_default_base) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "",
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::EMPTY_WEAK_POINTER},
      "https://example.com/schema"};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame,
      "https://example.com/schema", sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type",
                     "https://example.com/schema#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type",
                              "https://example.com/schema#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(is_annotation) {
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationBasenameToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationEmit));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationEmitWrapped));
  EXPECT_FALSE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AssertionFail));
}

TEST(is_wrapped_annotation) {
  EXPECT_TRUE(sourcemeta::blaze::is_wrapped_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationBasenameToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_wrapped_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationEmitWrapped));
  EXPECT_FALSE(sourcemeta::blaze::is_wrapped_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationEmit));
  EXPECT_FALSE(sourcemeta::blaze::is_wrapped_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationToParent));
  EXPECT_FALSE(sourcemeta::blaze::is_wrapped_annotation(
      sourcemeta::blaze::InstructionIndex::AssertionFail));
}

TEST(instruction_copy_constructible) {
  EXPECT_TRUE(std::is_copy_constructible_v<sourcemeta::blaze::Instruction>);
}

TEST(instruction_copy_assignable) {
  EXPECT_TRUE(std::is_copy_assignable_v<sourcemeta::blaze::Instruction>);
}

TEST(instruction_move_constructible) {
  EXPECT_TRUE(std::is_move_constructible_v<sourcemeta::blaze::Instruction>);
}

TEST(instruction_move_assignable) {
  EXPECT_TRUE(std::is_move_assignable_v<sourcemeta::blaze::Instruction>);
}

TEST(invalid_entrypoint_that_is_not_a_uri) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               frame, "http://[");
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(), "http://[");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI does not exist in the schema");
  }
}

TEST(invalid_entrypoint_does_not_exist) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               frame, "https://example.com/does-not-exist");
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/does-not-exist");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI does not exist in the schema");
  }
}

TEST(invalid_entrypoint_not_a_subschema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               frame, "#/properties");
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(), "#/properties");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI is not a valid subschema");
  }
}

TEST(unsupported_required_vocabulary) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/metaschema-unsupported-required-vocab"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::core::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/vocab/unsupported-fictional");
  } catch (const std::exception &) {
    FAIL();
  }
}

TEST(unevaluated_properties_with_root_dynamic_anchor_and_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/metadata-tree",
    "$dynamicAnchor": "member",
    "unevaluatedProperties": false
  })JSON")};

  const auto bundled{sourcemeta::core::schema_bundle(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, "", "https://example.com/default")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      bundled,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "",
      "https://example.com/default"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(unevaluated_items_with_root_dynamic_anchor_and_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/metadata-tree",
    "$dynamicAnchor": "member",
    "unevaluatedItems": false
  })JSON")};

  const auto bundled{sourcemeta::core::schema_bundle(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, "", "https://example.com/default")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      bundled,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "",
      "https://example.com/default"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1 ])JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(unevaluated_properties_with_root_recursive_anchor_and_default_id_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/metadata-tree",
    "$recursiveAnchor": true,
    "unevaluatedProperties": false
  })JSON")};

  const auto bundled{sourcemeta::core::schema_bundle(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, "", "https://example.com/default")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      bundled,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "",
      "https://example.com/default"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(unevaluated_properties_schema_with_root_dynamic_anchor_and_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/metadata-tree",
    "$dynamicAnchor": "member",
    "unevaluatedProperties": { "type": "string" }
  })JSON")};

  const auto bundled{sourcemeta::core::schema_bundle(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, "", "https://example.com/default")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      bundled,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "",
      "https://example.com/default"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_TRUE(result);
}

TEST(properties_as_a_loop_with_an_inlined_deeper_assertion) {
  // Inlining the reference leaves an assertion on `/a/b` inside the group that
  // the loop enters for `a`, so a child of that group is not necessarily about
  // the property the loop is standing on
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "inner": {
        "type": "object",
        "required": [ "b" ],
        "properties": { "b": { "type": "string" } },
        "allOf": [ true ]
      }
    },
    "properties": {
      "a": { "$ref": "#/definitions/inner" },
      "c": { "type": "string" },
      "d": { "type": "string" },
      "e": { "type": "string" },
      "f": { "type": "string" },
      "g": { "type": "string" }
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": { "b": "ok" } })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_TRUE(result);
}

TEST(properties_as_a_loop_with_an_inlined_deeper_assertion_failure) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "inner": {
        "type": "object",
        "required": [ "b" ],
        "properties": { "b": { "type": "string" } },
        "allOf": [ true ]
      }
    },
    "properties": {
      "a": { "$ref": "#/definitions/inner" },
      "c": { "type": "string" },
      "d": { "type": "string" },
      "e": { "type": "string" },
      "f": { "type": "string" },
      "g": { "type": "string" }
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": { "b": 1 } })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(items_as_a_bounded_array_of_typed_items) {
  // The outer `items` and the size-bounded inner `items` fuse into a single
  // instruction, so the nested loop runs without a dispatch per item
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "array",
      "items": { "type": "number" },
      "minItems": 2
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ [ 1, 2 ], [ 3, 4, 5 ] ])JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_TRUE(result);
}

TEST(items_as_a_bounded_array_of_typed_items_failure_on_an_inner_type) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "array",
      "items": { "type": "number" },
      "minItems": 2
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ [ 1, 2 ], [ 3, "x" ] ])JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(items_as_a_bounded_array_of_typed_items_failure_on_the_size) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "array",
      "items": { "type": "number" },
      "minItems": 2
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ [ 1, 2 ], [ 3 ] ])JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(items_as_a_bounded_array_of_typed_items_failure_on_a_scalar_item) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "array",
      "items": { "type": "number" },
      "minItems": 2
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 5 ])JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_FALSE(result);
}

TEST(items_as_a_bounded_array_of_typed_items_on_a_non_array) {
  // The instruction passes trivially when the instance is not an array, as its
  // own precondition makes it
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "array",
      "items": { "type": "number" },
      "minItems": 2
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_TRUE(result);
}

// JSON Schema Draft 4
TEST(items_integer_bounded_decimal_in_range) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "type": "number", "minimum": 0, "maximum": 100 }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};
  instance.push_back(sourcemeta::core::JSON{sourcemeta::core::Decimal{"50.5"}});
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsIntegerBounded, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsIntegerBounded, "/items", "#/items",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be a number within the "
      "given range");
}

TEST(items_integer_bounded_decimal_out_of_range) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "type": "number", "minimum": 0, "maximum": 100 }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};
  instance.push_back(
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"200.5"}});
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsIntegerBounded, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsIntegerBounded, "/items", "#/items",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be a number within the "
      "given range");
}

TEST(prop_type_integer_bounded_strict_decimal_3_0_fails) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  instance.assign("x",
                  sourcemeta::core::JSON{sourcemeta::core::Decimal{"3.0"}});
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerBoundedStrict,
                     "/properties/x/minimum", "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerBoundedStrict,
                              "/properties/x/minimum", "#/properties/x/minimum",
                              "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer within the given range");
}

// JSON Schema Draft 6
TEST(exclusiveMinimum_5) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(exclusiveMinimum_6) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5");
}

TEST(exclusiveMinimum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(exclusiveMinimum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5");
}

TEST(exclusiveMinimum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(exclusiveMinimum_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be greater than the number 2.5");
}

TEST(exclusiveMinimum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(exclusiveMinimum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5");
}

TEST(exclusiveMinimum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(exclusiveMinimum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be greater than the number 2.5");
}

TEST(exclusiveMinimum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.7"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.7 was expected to be greater than the number 0.5");
}

TEST(exclusiveMinimum_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be greater than the number 0.5");
}

TEST(exclusiveMaximum_5) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(exclusiveMaximum_6) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5");
}

TEST(exclusiveMaximum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(exclusiveMaximum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5");
}

TEST(exclusiveMaximum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(exclusiveMaximum_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be less than the number 2.5");
}

TEST(exclusiveMaximum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(exclusiveMaximum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5");
}

TEST(exclusiveMaximum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(exclusiveMaximum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be less than the number 2.5");
}

TEST(exclusiveMaximum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be less than the number 0.5");
}

TEST(exclusiveMaximum_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be less than the number 0.5");
}

// JSON Schema 2020-12
// NOLINTBEGIN(cert-err58-cpp,bugprone-throwing-static-initialization)
static const std::string FORMAT_ASSERTION_METASCHEMA_URI{
    "https://example.com/2020-12-format-assertion-meta"};

static auto format_assertion_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == FORMAT_ASSERTION_METASCHEMA_URI) {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/2020-12-format-assertion-meta",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true,
        "https://json-schema.org/draft/2020-12/vocab/format-assertion": true
      },
      "$dynamicAnchor": "meta",
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2020-12/meta/core" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/applicator" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/validation" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/format-assertion" }
      ]
    })JSON");
  }

  return sourcemeta::core::schema_resolver(identifier);
}

// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

TEST(dynamicRef_with_multiple_anchors_from_json) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "https://example.com/target#meta",
    "$defs": {
      "target": {
        "$id": "https://example.com/target",
        "$dynamicAnchor": "meta",
        "type": "boolean"
      },
      "other": {
        "$id": "https://example.com/other",
        "$dynamicAnchor": "meta",
        "type": "number"
      }
    }
  })JSON")};

  const auto original{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  const auto roundtripped{
      sourcemeta::blaze::from_json(sourcemeta::blaze::to_json(original))};
  EXPECT_TRUE(roundtripped.has_value());

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE(roundtripped.value(), instance, 2);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, ControlDynamicAnchorJump, "/$dynamicRef",
                     "#/$dynamicRef", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/$dynamicRef/type",
                     "https://example.com/target#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$dynamicRef/type",
                              "https://example.com/target#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlDynamicAnchorJump, "/$dynamicRef",
                              "#/$dynamicRef", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The boolean value was expected to validate against the first subschema "
      "in scope that declared the dynamic anchor \"meta\"");
}

TEST(unevaluated_properties_annotations_none_still_tracks) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "a": { "type": "integer" } },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": 1, "b": 2 })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations.emplace();

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive, "", "", "", tweaks)};

  // Even with all annotations filtered out, evaluation tracking still marks "a"
  // as evaluated, so the unevaluated "b" is rejected
  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));

  const sourcemeta::core::JSON evaluated{
      sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};
  EXPECT_TRUE(evaluator.validate(compiled_schema, evaluated));
}

TEST(format_uri_with_assertion_vocab_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, format_assertion_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(format_uri_with_assertion_vocab_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, format_assertion_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_uri_with_assertion_vocab_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, format_assertion_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 2)
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri\"");
}

TEST(format_uri_with_assertion_vocab_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/2020-12-format-assertion-meta",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, format_assertion_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::Exhaustive)};

  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

// OpenAPI 3.0
// Only what the JSON trace suites cannot express belongs here. That suite reads
// every schema under one dialect and holds it to that dialect's meta-schema,
// which rules out a schema that declares a dialect of its own, and it has no
// way of asking for a compiler tweak
static constexpr auto OPENAPI_3_0_DIALECT{
    "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"};

TEST(explicit_schema_with_root_ref_keeps_the_sibling_type_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": { "string": { "type": "string" } },
    "$ref": "#/$defs/string",
    "type": "integer"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  // The declared dialect keeps the assertion beside `$ref` alive, so a string
  // that satisfies the reference still fails the sibling type
  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("foo")JSON")};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(explicit_schema_with_root_ref_keeps_the_reference_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": { "string": { "type": "string" } },
    "$ref": "#/$defs/string",
    "type": "integer"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  // The declared dialect keeps the reference alive, so an integer that
  // satisfies the sibling type still fails the referenced string schema
  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON(1)JSON")};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(external_reference_inherits_the_default_dialect_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "$ref": "https://example.com/name" }
    }
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/name") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "string",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  // Only this dialect gives `nullable` a meaning, so a null passing is what
  // shows the default dialect reached the externally resolved document
  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "name": null })JSON")};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(external_reference_enforces_the_target_constraints_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "$ref": "https://example.com/name" }
    }
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/name") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "string",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "name": 1 })JSON")};
  EXPECT_FALSE(evaluator.validate(compiled_schema, instance));
}

TEST(root_reference_without_siblings_accepts_null_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com/target"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/target") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "integer",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("null")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
                     "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
      "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type null");
}

TEST(root_reference_without_siblings_accepts_an_integer_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com/target"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/target") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "integer",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
                     "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
      "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type integer");
}

TEST(root_reference_without_siblings_rejects_a_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com/target"
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com/target") {
      return sourcemeta::core::parse_json(R"JSON({
                "type": "integer",
                "nullable": true
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("\"1\"")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
                     "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionTypeStrictAny, "/allOf/0/$ref/type",
      "#/x-definitions/https:~1~1example.com~1target/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer but it was of type string");
}

// Serialized templates are a product surface, and textual round-trip equality
// alone cannot show the rebuilt instructions still evaluate, so these run the
// deserialized template
TEST(format_byte_accepts_through_a_deserialized_template_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation,
                                 OPENAPI_3_0_DIALECT, "", "", tweaks)};
  const auto restored{sourcemeta::blaze::from_json(
      sourcemeta::blaze::to_json(compiled_schema))};
  EXPECT_TRUE(restored.has_value());

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("Zg==")JSON")};
  EVALUATE_WITH_TRACE(restored.value(), instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"Zg==\" was expected to "
                               "represent a valid RFC 4648 Base64 string");
}

TEST(format_byte_rejects_through_a_deserialized_template_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "format": "byte"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation,
                                 OPENAPI_3_0_DIALECT, "", "", tweaks)};
  const auto restored{sourcemeta::blaze::from_json(
      sourcemeta::blaze::to_json(compiled_schema))};
  EXPECT_TRUE(restored.has_value());

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON("not base64")JSON")};
  EVALUATE_WITH_TRACE(restored.value(), instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The string value \"not base64\" was expected "
                               "to represent a valid RFC 4648 Base64 string");
}

TEST(nullable_through_the_frame_overload_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{nullptr};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(nullable_array_type_is_refused_through_the_frame_overload_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": [ "string", "null" ],
    "nullable": true
  })JSON")};

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
        sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(
        std::string{error.what()},
        "The value this keyword is set to is not supported by this dialect");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/type");
  }
}

// A subschema the walker cannot reach, such as one parked under an `x-`
// container, still compiles under the external default when named as an
// entrypoint through an explicitly framed path
TEST(nullable_through_a_nested_entrypoint_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "foo": { "type": "string", "nullable": true }
    }
  })JSON")};

  const sourcemeta::core::Pointer foo{"x-definitions", "foo"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(foo)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/foo",
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{nullptr};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

// Framing a second, invalid schema must not leak into the selected
// entrypoint: compilation answers for the named schema and nothing else
TEST(nested_entrypoint_ignores_an_unrelated_framed_schema_accepts_null_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/good",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("null")};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type",
                     "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type",
                              "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "string and it was of type null");
}

TEST(
    nested_entrypoint_ignores_an_unrelated_framed_schema_accepts_a_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/good",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"a"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type",
                     "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type",
                              "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "string and it was of type string");
}

TEST(
    nested_entrypoint_ignores_an_unrelated_framed_schema_rejects_an_integer_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, "#/x-definitions/good",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type",
                     "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type",
                              "#/x-definitions/good/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "string but it was of type integer");
}

TEST(invalid_nested_entrypoint_is_still_rejected_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "x-definitions": {
      "good": { "type": "string", "nullable": true },
      "bad": { "type": "null" }
    }
  })JSON")};

  const sourcemeta::core::Pointer good{"x-definitions", "good"};
  const sourcemeta::core::Pointer bad{"x-definitions", "bad"};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      schema,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      OPENAPI_3_0_DIALECT,
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::to_weak_pointer(good),
       sourcemeta::core::to_weak_pointer(bad)}};

  try {
    [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, frame,
        "#/x-definitions/bad", sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_EQ(
        std::string{error.what()},
        "The value this keyword is set to is not supported by this dialect");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/x-definitions/bad/type");
  }
}

// A custom compiler callback may start an independent compilation of an
// unrelated schema while the outer one is in flight. The dialect keeps no
// state across compilations, so the nested schema compiles exactly as it
// does standalone
TEST(nested_independent_compilation_accepts_null_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::KeywordContext &context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("null")};
  EVALUATE_WITH_TRACE(nested.value(), instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type null");
}

TEST(nested_independent_compilation_accepts_an_integer_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::KeywordContext &context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE(nested.value(), instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer and it was of type integer");
}

TEST(nested_independent_compilation_rejects_a_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::KeywordContext &context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON instance{"a"};
  EVALUATE_WITH_TRACE(nested.value(), instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type null, or "
                               "integer but it was of type string");
}

TEST(nested_independent_compilation_matches_a_standalone_compilation_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON")};

  std::optional<sourcemeta::blaze::Template> nested;
  auto nesting_compiler =
      [&nested](const sourcemeta::blaze::KeywordContext &context,
                const sourcemeta::blaze::Instructions &current)
      -> sourcemeta::blaze::Instructions {
    if (!nested.has_value()) {
      const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
        "type": "integer",
        "nullable": true
      })JSON")};
      nested = sourcemeta::blaze::compile(
          inner, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler,
          sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT);
    }

    return sourcemeta::blaze::default_schema_compiler(context, current);
  };

  [[maybe_unused]] const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, nesting_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};
  EXPECT_TRUE(nested.has_value());

  const sourcemeta::core::JSON inner{sourcemeta::core::parse_json(R"JSON({
    "type": "integer",
    "nullable": true
  })JSON")};

  const auto standalone{sourcemeta::blaze::compile(
      inner, sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, OPENAPI_3_0_DIALECT)};

  EXPECT_EQ(sourcemeta::blaze::to_json(nested.value()),
            sourcemeta::blaze::to_json(standalone));
}

// Widening a scalar type with `nullable` must not loosen the type itself, and
// this rung keeps Draft 4's rule that a real is no integer. The JavaScript
// port cannot carry this case, as `JSON.parse` renders `2.0` as `2`

// schemas embedded in a document
static auto embedded_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://example.com/pet.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/pet.json",
      "type": "string"
    })JSON");
  }

  return sourcemeta::core::schema_resolver(identifier);
}

static auto compile_embedded(const sourcemeta::core::JSON &document,
                             const sourcemeta::core::SchemaFrame::Paths &paths,
                             const std::string_view entrypoint,
                             const sourcemeta::blaze::Mode mode)
    -> sourcemeta::blaze::Template {
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      document,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://spec.openapis.org/oas/3.1/dialect/base",
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      paths,
      "https://example.com/openapi.json"};
  return sourcemeta::blaze::compile(document, sourcemeta::core::schema_walker,
                                    sourcemeta::core::schema_resolver,
                                    sourcemeta::blaze::default_schema_compiler,
                                    frame, entrypoint, mode);
}

TEST(entrypoint_at_embedded_root_success) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" },
        "Order": { "type": "integer" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(entrypoint_at_embedded_root_failure) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" },
        "Order": { "type": "integer" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(entrypoint_at_embedded_subschema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "properties": {
            "name": { "type": "string" }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet/properties/"
      "name",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type",
                     "https://example.com/openapi.json#/components/schemas/"
                     "Pet/properties/name/type",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/properties/"
      "name/type",
      "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(reference_to_embedded_sibling_by_pointer) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" },
        "Order": { "$ref": "#/components/schemas/Pet" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(reference_to_embedded_sibling_by_identifier) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$id": "pet", "type": "string" },
        "Order": { "$ref": "pet" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "https://example.com/pet#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "https://example.com/pet#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(entrypoint_at_embedded_shell) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};

  try {
    [[maybe_unused]] const auto schema_template{
        compile_embedded(document, {sourcemeta::core::to_weak_pointer(pet)},
                         "https://example.com/openapi.json#/info",
                         sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/openapi.json#/info");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI is not a valid subschema");
  }
}

TEST(entrypoint_at_embedded_missing_location) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};

  try {
    [[maybe_unused]] const auto schema_template{compile_embedded(
        document, {sourcemeta::core::to_weak_pointer(pet)},
        "https://example.com/openapi.json#/components/schemas/Missing",
        sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(),
              "https://example.com/openapi.json#/components/schemas/Missing");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI does not exist in the schema");
  }
}

TEST(reference_from_embedded_schema_into_shell) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$ref": "#/info" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};

  try {
    [[maybe_unused]] const auto schema_template{compile_embedded(
        document, {sourcemeta::core::to_weak_pointer(pet)},
        "https://example.com/openapi.json#/components/schemas/Pet",
        sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "The referenced schema is not considered to be a valid "
                 "subschema given the dialect and vocabularies in use");
    EXPECT_EQ(error.identifier(), "https://example.com/openapi.json#/info");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer(
                                    {"components", "schemas", "Pet", "$ref"}));
  }
}

TEST(reference_to_embedded_sibling_by_anchor) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$anchor": "pet", "type": "string" },
        "Order": { "$ref": "#pet" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(reference_to_embedded_sibling_subschema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "properties": {
            "name": { "type": "string" }
          }
        },
        "Order": { "$ref": "#/components/schemas/Pet/properties/name" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "https://example.com/openapi.json#/components/schemas/"
                     "Pet/properties/name/type",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "https://example.com/openapi.json#/components/"
                              "schemas/Pet/properties/name/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(entrypoint_at_embedded_false_schema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": false
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionFail, "",
                     "https://example.com/openapi.json#/components/schemas/Pet",
                     "");
  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionFail, "",
      "https://example.com/openapi.json#/components/schemas/Pet", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "No instance is expected to succeed against the false schema");
}

TEST(entrypoint_at_embedded_true_schema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": true
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 0);
  EXPECT_TRUE(result);
}

TEST(dynamic_reference_within_embedded_schema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "$dynamicRef": "https://example.com/target#meta",
          "$defs": {
            "target": {
              "$id": "https://example.com/target",
              "$dynamicAnchor": "meta",
              "type": "boolean"
            },
            "other": {
              "$id": "https://example.com/other",
              "$dynamicAnchor": "meta",
              "type": "number"
            }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE(schema_template, instance, 2);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, ControlDynamicAnchorJump, "/$dynamicRef",
      "https://example.com/openapi.json#/components/schemas/Pet/$dynamicRef",
      "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/$dynamicRef/type",
                     "https://example.com/target#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$dynamicRef/type",
                              "https://example.com/target#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlDynamicAnchorJump, "/$dynamicRef",
      "https://example.com/openapi.json#/components/schemas/Pet/$dynamicRef",
      "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The boolean value was expected to validate against the first subschema "
      "in scope that declared the dynamic anchor \"meta\"");
}

TEST(embedded_schema_declaring_its_own_dialect) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "$schema": "http://json-schema.org/draft-07/schema#",
          "type": "string"
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(embedded_schema_with_default_dialect_vocabulary_keyword) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "type": "object",
          "discriminator": { "propertyName": "kind" }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::make_object()};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(unevaluated_properties_through_reference_to_embedded_sibling) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Base": {
          "type": "object",
          "properties": { "shared": true }
        },
        "Pet": {
          "type": "object",
          "allOf": [ { "$ref": "#/components/schemas/Base" } ],
          "properties": { "local": true },
          "unevaluatedProperties": false
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer base{"components", "schemas", "Base"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(base),
       sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "shared": 1 })JSON")};
  EVALUATE_WITH_TRACE(schema_template, instance, 3);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/allOf/0/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Base/type", "");
  EVALUATE_TRACE_PRE(
      1, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/unevaluatedProperties",
                     "https://example.com/openapi.json#/components/schemas/"
                     "Pet/unevaluatedProperties",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/allOf/0/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Base/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/unevaluatedProperties",
                              "https://example.com/openapi.json#/components/"
                              "schemas/Pet/unevaluatedProperties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define unevaluated properties");
}

TEST(entrypoint_at_embedded_root_with_bundled_external_reference) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$ref": "pet.json" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  sourcemeta::core::SchemaBundleOptions options;
  options.mode = sourcemeta::core::SchemaBundleOptions::Mode::References;
  options.default_container = sourcemeta::core::Pointer{"x-bundled"};
  options.paths = {sourcemeta::core::to_weak_pointer(pet)};
  options.default_base = "https://example.com/openapi.json";
  const sourcemeta::core::JSON bundled{sourcemeta::core::schema_bundle(
      document, sourcemeta::core::schema_walker, embedded_resolver,
      "https://spec.openapis.org/oas/3.1/dialect/base", "", options)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$ref": "https://example.com/pet.json" }
      }
    },
    "x-bundled": {
      "https://example.com/pet.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/pet.json",
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(bundled, expected);

  const sourcemeta::core::Pointer bundled_pet{"x-bundled",
                                              "https://example.com/pet.json"};
  const auto schema_template{compile_embedded(
      bundled,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(bundled_pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "https://example.com/pet.json#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "https://example.com/pet.json#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}
