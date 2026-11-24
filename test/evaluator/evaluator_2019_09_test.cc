#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(metaschema_1) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2019-09/schema")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "type": [ "string" ]
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 35, "");
}

TEST(metaschema_invalid_definition) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2019-09/schema")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "type": 1
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(metaschema.value(), instance, 14, "");
}

TEST(metaschema_invalid_definition_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2019-09/schema")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "type": 1
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(metaschema.value(), instance, 25, "");
}

TEST(metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2019-09/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 67,
                                   "");
}

TEST(metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "https://json-schema.org/draft/2019-09/hyper-schema")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         170, "");
}

// NOLINTNEXTLINE(google-readability-function-size,hicpp-function-size,readability-function-size)
TEST(reference_from_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "#/definitions/bar" },
      "baz": { "type": "string" }
    },
    "definitions": {
      "bar": {
        "$ref": "#/properties/baz"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.identifier(), "#/properties/baz");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"definitions", "bar", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(invalid_ref_top_level) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(unevaluated_properties_root_self_reference_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "unevaluatedProperties": false
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  // The reference makes no progress on the instance, so evaluation can only
  // stop by running into the depth limit
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};
  sourcemeta::blaze::Evaluator evaluator;
  try {
    evaluator.validate(compiled_schema, instance);
    FAIL();
  } catch (const sourcemeta::blaze::EvaluationError &error) {
    EXPECT_STREQ(error.what(), "The evaluation path depth limit was reached "
                               "likely due to infinite recursion");
  } catch (...) {
    FAIL();
  }
}

TEST(unevaluated_properties_root_self_reference_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "unevaluatedProperties": false
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  // The reference makes no progress on the instance, so evaluation can only
  // stop by running into the depth limit
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};
  sourcemeta::blaze::Evaluator evaluator;
  try {
    evaluator.validate(compiled_schema, instance);
    FAIL();
  } catch (const sourcemeta::blaze::EvaluationError &error) {
    EXPECT_STREQ(error.what(), "The evaluation path depth limit was reached "
                               "likely due to infinite recursion");
  } catch (...) {
    FAIL();
  }
}

TEST(unevaluated_items_root_self_reference_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "unevaluatedItems": false
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  // The reference makes no progress on the instance, so evaluation can only
  // stop by running into the depth limit
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1 ])JSON")};
  sourcemeta::blaze::Evaluator evaluator;
  try {
    evaluator.validate(compiled_schema, instance);
    FAIL();
  } catch (const sourcemeta::blaze::EvaluationError &error) {
    EXPECT_STREQ(error.what(), "The evaluation path depth limit was reached "
                               "likely due to infinite recursion");
  } catch (...) {
    FAIL();
  }
}

TEST(unevaluated_items_root_self_reference_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "unevaluatedItems": false
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive)};

  // The reference makes no progress on the instance, so evaluation can only
  // stop by running into the depth limit
  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON([ 1 ])JSON")};
  sourcemeta::blaze::Evaluator evaluator;
  try {
    evaluator.validate(compiled_schema, instance);
    FAIL();
  } catch (const sourcemeta::blaze::EvaluationError &error) {
    EXPECT_STREQ(error.what(), "The evaluation path depth limit was reached "
                               "likely due to infinite recursion");
  } catch (...) {
    FAIL();
  }
}
