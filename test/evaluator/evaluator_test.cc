#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include "evaluator_utils.h"

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::jsontoolkit::JSON> {
  if (identifier == "https://example.com/metaschema") {
    return sourcemeta::jsontoolkit::parse(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/metaschema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://example.com/vocab/custom": true
      }
    })JSON");
  } else {
    return sourcemeta::jsontoolkit::official_resolver(identifier);
  }
}

TEST(Evaluator, unknown_vocabulary_required) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://example.com/metaschema"
  })JSON")};

  try {
    sourcemeta::blaze::compile(
        schema, sourcemeta::jsontoolkit::default_schema_walker, test_resolver,
        sourcemeta::blaze::default_schema_compiler);
    FAIL() << "The compile function was expected to throw";
  } catch (const sourcemeta::jsontoolkit::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/vocab/custom");
    SUCCEED();
  } catch (const std::exception &) {
    FAIL() << "The compile function was expected to throw a vocabulary error";
  }
}

TEST(Evaluator, boolean_true) {
  const sourcemeta::jsontoolkit::JSON schema{true};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "https://json-schema.org/draft/2020-12/schema")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 0)
  EXPECT_TRUE(result);
}

TEST(Evaluator, boolean_false) {
  const sourcemeta::jsontoolkit::JSON schema{false};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation,
      "https://json-schema.org/draft/2020-12/schema")};

  const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
  EVALUATE_WITH_TRACE(compiled_schema, instance, 1)
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionFail, "", "", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionFail, "", "", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "No instance is expected to succeed against the false schema");
}

TEST(Evaluator, reusable_context) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::EvaluationContext context;

  const sourcemeta::jsontoolkit::JSON instance_1{"foo bar"};
  context.reset();
  EXPECT_TRUE(
      sourcemeta::blaze::evaluate(compiled_schema, instance_1, context));

  const sourcemeta::jsontoolkit::JSON instance_2{"baz"};
  context.reset();
  EXPECT_TRUE(
      sourcemeta::blaze::evaluate(compiled_schema, instance_2, context));

  const sourcemeta::jsontoolkit::JSON instance_3{4};
  context.reset();
  EXPECT_FALSE(
      sourcemeta::blaze::evaluate(compiled_schema, instance_3, context));

  const sourcemeta::jsontoolkit::JSON instance_4{"qux"};
  context.reset();
  EXPECT_TRUE(
      sourcemeta::blaze::evaluate(compiled_schema, instance_4, context));
}
