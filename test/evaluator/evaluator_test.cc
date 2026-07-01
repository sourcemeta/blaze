#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>

#include <sourcemeta/core/json.h>

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
  } else if (identifier ==
             "https://example.com/metaschema-unsupported-required-vocab") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/metaschema-unsupported-required-vocab",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://example.com/vocab/unsupported-fictional": true
      }
    })JSON");
  } else if (identifier == "https://example.com/schema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/schema",
      "type": "string"
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(unknown_vocabulary_required) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/metaschema"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
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
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &) {
  }
}

TEST(with_default_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "schema"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "",
      "https://example.com/default")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_TRUE(result);
}

TEST(boolean_true) {
  const sourcemeta::core::JSON schema{true};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "https://json-schema.org/draft/2020-12/schema")};

  const sourcemeta::core::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 0)
  EXPECT_TRUE(result);
}

TEST(boolean_false) {
  const sourcemeta::core::JSON schema{false};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
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

TEST(reusable_evaluator) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
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
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{"test"};
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));
}

TEST(explicit_frame) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "$ref": "https://json-schema.org/draft/2020-12/schema" } ]
  })JSON")};

  const sourcemeta::core::JSON result{sourcemeta::blaze::bundle(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas)};
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(result, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto compiled_schema{sourcemeta::blaze::compile(
      result, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
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

  const sourcemeta::core::JSON result{sourcemeta::blaze::bundle(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas)};
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(result, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  try {
    sourcemeta::blaze::compile(result, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               frame, frame.root());
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceError &) {
  }
}

TEST(is_annotation) {
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationBasenameToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationToParent));
  EXPECT_TRUE(sourcemeta::blaze::is_annotation(
      sourcemeta::blaze::InstructionIndex::AnnotationEmit));
  EXPECT_FALSE(sourcemeta::blaze::is_annotation(
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

TEST(invalid_entrypoint_does_not_exist) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
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

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
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
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
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

  const auto bundled{sourcemeta::blaze::bundle(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://example.com/default")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(bundled, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, "",
                "https://example.com/default");

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
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

  const auto bundled{sourcemeta::blaze::bundle(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://example.com/default")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(bundled, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, "",
                "https://example.com/default");

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
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

  const auto bundled{sourcemeta::blaze::bundle(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://example.com/default")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(bundled, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, "",
                "https://example.com/default");

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
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

  const auto bundled{sourcemeta::blaze::bundle(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://example.com/default")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(bundled, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, "",
                "https://example.com/default");

  const auto compiled_schema{sourcemeta::blaze::compile(
      bundled, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON")};
  const auto result{evaluator.validate(compiled_schema, instance)};
  EXPECT_TRUE(result);
}
