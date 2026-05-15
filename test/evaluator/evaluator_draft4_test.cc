#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft4, metaschema_1) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 3, "");
}

TEST(Evaluator_draft4, metaschema_2) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "type": [ "string" ]
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 16, "");
}

TEST(Evaluator_draft4, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 768,
                                   "");
}

TEST(Evaluator_draft4, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         957, "");
}

TEST(Evaluator_draft4, ref_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler),
      sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com") {
      return sourcemeta::core::parse_json(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::core::schema_walker, test_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com") {
      return sourcemeta::core::parse_json(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  EXPECT_THROW(sourcemeta::blaze::compile(
                   schema, sourcemeta::core::schema_walker, test_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::core::SchemaReferenceError);
}

TEST(Evaluator_draft4, ref_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/foo" } ],
    "definitions": {
      "foo": { "$ref": "#/definitions/bar" },
      "bar": { "$ref": "#/definitions/foo" }
    }
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{true};
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

TEST(Evaluator_draft4, properties_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": false,
    "properties": {
      "a": { "type": "string" },
      "b": { "type": "string" },
      "c": { "type": "string" },
      "d": { "type": "string" },
      "e": { "type": "string" },
      "f": { "type": "string" },
      "g": { "type": "string" },
      "h": { "type": "string" },
      "i": { "type": "string" },
      "j": { "type": "string" },
      "k": { "type": "string" },
      "l": { "type": "string" },
      "m": { "type": "string" },
      "n": { "type": "string" },
      "o": { "type": "string" },
      "p": { "type": "string" },
      "q": { "type": "string" },
      "r": { "type": "string" },
      "s": { "type": "string" },
      "t": { "type": "string" },
      "u": { "type": "string" },
      "v": { "type": "string" },
      "w": { "type": "string" },
      "x": { "type": "string" },
      "y": { "type": "string" },
      "z": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"f\": \"foo\", \"extra\": 2 }")};

  if (FIRST_PROPERTY_IS(instance, "f")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/f/type",
                       "#/properties/f/type", "/f");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                                "/properties/f/type", "#/properties/f/type",
                                "/f");
    EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The value was expected to be of type string");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "Every object value was expected to validate "
        "against one of the 26 defined properties subschemas");
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "Every object value was expected to validate "
        "against one of the 26 defined properties subschemas");
  }
}

// From https://github.com/sourcemeta/jsonschema/issues/432
TEST(Evaluator_draft4, pattern_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, pattern_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, pattern_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "id": "https://nested.com",
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com");
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, patternProperties_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^[a-zA-Z0-9\\_\\.\\-]*$": { "type": "string" }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
    SUCCEED();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\_\\.\\-]*$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"patternProperties"}));
    EXPECT_EQ(error.base().recompose(), "");
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, patternProperties_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^[a-z]+$": { "type": "string" } },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": \"bar\", \"@bar\": \"baz\" }")};

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                       "#/patternProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict,
                       "/patternProperties/^[a-z]+$/type",
                       // Note that the caret needs to be URI escaped
                       "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(
        0, AssertionTypeStrict, "/patternProperties/^[a-z]+$/type",
        // Note that the caret needs to be URI escaped
        "#/patternProperties/%5E%5Ba-z%5D+$/type", "/foo");
    EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesRegexClosed,
                                "/patternProperties", "#/patternProperties",
                                "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The value was expected to be of type string");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object properties were expected to match the regular expression "
        "\"^[a-z]+$\" and validate against the defined pattern property "
        "subschema");
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesRegexClosed, "/patternProperties",
                       "#/patternProperties", "");
    EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesRegexClosed,
                                "/patternProperties", "#/patternProperties",
                                "");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "The object properties were expected to match the regular expression "
        "\"^[a-z]+$\" and validate against the defined pattern property "
        "subschema");
  }
}

TEST(Evaluator_draft4, additionalProperties_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3, "");

  EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                     "#/additionalProperties", "");

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
  } else {
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
  }

  EVALUATE_TRACE_POST_SUCCESS(2, LoopProperties, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_draft4, additionalProperties_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "baz": {
        "type": "integer"
      }
    },
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopPropertiesExcept, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept,
                                "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  } else {
    EVALUATE_TRACE_PRE(0, LoopPropertiesExcept, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                                "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept,
                                "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  }
}

TEST(Evaluator_draft4, additionalProperties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "boolean"
      }
    },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": true, \"bar\": 2 }")};

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrict, "/properties/foo/type",
                       "#/properties/foo/type", "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                                "/properties/foo/type", "#/properties/foo/type",
                                "/foo");
    EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type boolean");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object value was expected to validate "
        "against the single defined property subschema")
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

    EVALUATE_TRACE_PRE(0, LoopPropertiesMatchClosed, "/properties",
                       "#/properties", "");
    EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesMatchClosed, "/properties",
                                "#/properties", "");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "The object value was expected to validate "
        "against the single defined property subschema")
  }
}

TEST(Evaluator_draft4, invalid_ref_top_level) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft4, invalid_ref_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "$ref": "#/definitions/i-dont-exist"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, invalid_ref_embedded) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "$ref": "#/definitions/bar"
    },
    "definitions": {
      "bar": {
        "id": "https://example.com/nested",
        "additionalProperties": {
          "$ref": "#/definitions/baz"
        }
      },
      "baz": {}
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer(
                  {"definitions", "bar", "additionalProperties", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, reference_from_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "$ref": "#/$defs/bar" },
      "baz": { "type": "string" }
    },
    "$defs": {
      "bar": {
        "$ref": "#/properties/baz"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(), "#/$defs/bar");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"$defs"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, reference_to_nested_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [
      {
        "$ref": "#/allOf/1/additionalProperties/x-this-is-invalid/$defs/test"
      },
      {
        "additionalProperties": {
          "x-this-is-invalid": {
            "$defs": {
              "test": {
                "type": "string"
              }
            }
          }
        }
      }
    ]
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(),
              "#/allOf/1/additionalProperties/x-this-is-invalid/$defs/test");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer(
                  {"allOf", 1, "additionalProperties", "x-this-is-invalid"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft4, ref_to_non_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "array": {
        "items": [
          { "type": "string" },
          { "type": "array" }
        ]
      }
    },
    "additionalProperties": {
      "$ref": "#/definitions/array/items"
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL() << "The compile function was expected to throw";
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(), "#/definitions/array/items");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"definitions", "array", "items"}));
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft4, top_level_ref_with_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft4, top_level_ref_with_id_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft4, type_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft4, type_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string but it was of type number");
}

TEST(Evaluator_draft4, properties_20) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft4, additionalProperties_20) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "integer" },
        "bar": { "type": "integer" }
      }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  auto item{sourcemeta::core::JSON::make_object()};
  item.assign_assume_new("foo",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  item.assign_assume_new("bar",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  instance.push_back(std::move(item));

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsPropertiesExactlyTypeStrictHash,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type integer");
}

TEST(Evaluator_draft4, additionalProperties_22) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "object",
      "required": [ "foo", "bar", "baz" ],
      "additionalProperties": false,
      "properties": {
        "foo": { "type": "integer" },
        "bar": { "type": "integer" },
        "baz": { "type": "integer" }
      }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  auto item{sourcemeta::core::JSON::make_object()};
  item.assign_assume_new("foo",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  item.assign_assume_new("bar",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  item.assign_assume_new("baz",
                         sourcemeta::core::JSON{sourcemeta::core::Decimal(
                             "99999999999999999999999999999999999.0")});
  instance.push_back(std::move(item));

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsPropertiesExactlyTypeStrictHash3, "/items",
                     "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsPropertiesExactlyTypeStrictHash3,
                              "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be an object whose required "
      "properties were of type integer");
}

TEST(Evaluator_draft4, additionalProperties_24) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesTypeStrict, "/properties", "#/properties",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesTypeStrict, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_26) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": {
      "type": [ "integer", "string" ]
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrictAny,
                     "/additionalProperties/type",
                     "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesTypeStrictAny,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object properties were expected to be of type integer, or string");
}

TEST(Evaluator_draft4, additionalProperties_28) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrictHash, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesExactlyTypeStrictHash,
                              "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, additionalProperties_30) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "required": [
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
      "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"
    ],
    "additionalProperties": false,
    "properties": {
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx": { "type": "integer" },
      "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});
  instance.assign_assume_new("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal(
                                 "99999999999999999999999999999999999.0")});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopPropertiesExactlyTypeStrict, "/properties",
                     "#/properties", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesExactlyTypeStrict, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The required object properties were expected to be of type integer");
}

TEST(Evaluator_draft4, items_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": "integer"
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsTypeStrict, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type integer");
}

TEST(Evaluator_draft4, items_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "type": [ "integer", "string" ]
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrictAny, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsTypeStrictAny, "/items", "#/items",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array items were expected to be of type integer, or string");
}

TEST(Evaluator_draft4, multipleOf_19) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.1"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be divisible by the number 0.1");
}

TEST(Evaluator_draft4, multipleOf_20) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});
  schema.assign_assume_new(
      "multipleOf", sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.01"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"1280.32"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 1280.32 was expected to be divisible by the number "
      "0.01");
}

TEST(Evaluator_draft4, ref_2_entrypoint) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/string" } ],
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "#/allOf/0");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, enum_17) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "enum": [ 3.0 ]
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/type", "#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the number constant 3.0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft4, items_integer_bounded_decimal_in_range) {
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
}

TEST(Evaluator_draft4, items_integer_bounded_decimal_out_of_range) {
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
}

TEST(Evaluator_draft4, items_integer_bounded_large_decimal_in_range) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "type": "number", "minimum": 0, "maximum": 100 }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"99.99999999999999999999999999999"}});
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsIntegerBounded, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsIntegerBounded, "/items", "#/items",
                              "");
}

TEST(Evaluator_draft4, prop_type_integer_bounded_strict_real_3_0_fails) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 3.0 })JSON")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerBoundedStrict, "", "#/properties",
                     "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerBoundedStrict, "",
                              "#/properties", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer within the given range");
}

TEST(Evaluator_draft4, prop_type_integer_bounded_strict_real_3_5_fails) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 3.5 })JSON")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerBoundedStrict, "", "#/properties",
                     "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerBoundedStrict, "",
                              "#/properties", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer within the given range");
}

TEST(Evaluator_draft4, prop_type_integer_lower_bound_strict_real_5_0_fails) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "type": "integer", "minimum": 1 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 5.0 })JSON")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerLowerBoundStrict, "",
                     "#/properties", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerLowerBoundStrict, "",
                              "#/properties", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer above the given minimum");
}

TEST(Evaluator_draft4, prop_type_integer_lower_bound_strict_real_5_5_fails) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "type": "integer", "minimum": 1 }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": 5.5 })JSON")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerLowerBoundStrict, "",
                     "#/properties", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerLowerBoundStrict, "",
                              "#/properties", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer above the given minimum");
}

TEST(Evaluator_draft4, prop_type_integer_bounded_strict_decimal_3_0_fails) {
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

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerBoundedStrict, "", "#/properties",
                     "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerBoundedStrict, "",
                              "#/properties", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer within the given range");
}

TEST(Evaluator_draft4, minimum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.0 was expected to be "
                               "greater than or equal to the number 2.5");
}

TEST(Evaluator_draft4, minimum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.0 was expected to be "
                               "greater than or equal to the number 2.5");
}

TEST(Evaluator_draft4, minimum_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.0 was expected to be "
                               "greater than or equal to the number 2.5");
}

TEST(Evaluator_draft4, minimum_17) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.0 was expected to be "
                               "greater than or equal to the number 2.5");
}

TEST(Evaluator_draft4, minimum_22) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 5.0
  })JSON")};

  const sourcemeta::core::JSON instance{10.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreaterEqual, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreaterEqual, "/minimum", "#/minimum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 10.0 was expected to be "
                               "greater than or equal to the number 5.0");
}

TEST(Evaluator_draft4, maximum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.0 was expected to be less "
                               "than or equal to the number 2.5");
}

TEST(Evaluator_draft4, maximum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.0 was expected to be less "
                               "than or equal to the number 2.5");
}

TEST(Evaluator_draft4, maximum_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 2.0 was expected to be less "
                               "than or equal to the number 2.5");
}

TEST(Evaluator_draft4, maximum_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.0 was expected to be less "
                               "than or equal to the number 2.5");
}

TEST(Evaluator_draft4, maximum_21) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 5.0
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLessEqual, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLessEqual, "/maximum", "#/maximum",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The number value 3.0 was expected to be less "
                               "than or equal to the number 5.0");
}

TEST(Evaluator_draft4, exclusiveMinimum_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMinimum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 2.5,
    "exclusiveMinimum": true
  })JSON")};

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionGreater, "/minimum", "#/minimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/minimum", "#/minimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMaximum_8) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(Evaluator_draft4, exclusiveMaximum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "maximum": 2.5,
    "exclusiveMaximum": true
  })JSON")};

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionLess, "/maximum", "#/maximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/maximum", "#/maximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 3.2
  })JSON")};

  const sourcemeta::core::JSON instance{6.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 3.2");
}

TEST(Evaluator_draft4, multipleOf_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{5.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 5.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{6.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_15) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{5.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 5.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_16) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{6.0};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 6.0 was expected to be divisible by the number 2.5");
}

TEST(Evaluator_draft4, multipleOf_21) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "multipleOf": 5.0
  })JSON")};

  const sourcemeta::core::JSON instance{15.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/multipleOf", "#/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/multipleOf",
                              "#/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 15.0 was expected to be divisible by the number 5.0");
}

TEST(Evaluator_draft4, type_integer_invalid_real_integer_valued_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_real_integer_valued_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1e0_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1e0_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1_5e1_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e1")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1_5e1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e1")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1_5e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1_5e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_30e_minus_1_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("30e-1")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_30e_minus_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("30e-1")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1e_minus_2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e-2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_invalid_decimal_1e_minus_2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e-2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft4, type_integer_valid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft4, type_integer_valid_decimal_lexical_bignum_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft4,
     type_array_integer_string_invalid_real_integer_valued_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft4,
     type_array_integer_string_invalid_real_integer_valued_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft4, type_array_integer_string_invalid_decimal_1e0_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft4,
     type_array_integer_string_invalid_decimal_1e0_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft4, type_array_integer_string_invalid_decimal_1_5e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft4,
     type_array_integer_string_invalid_decimal_1_5e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft4,
     type_array_integer_string_valid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string and it was of "
      "type integer");
}

TEST(Evaluator_draft4,
     type_array_integer_string_valid_decimal_lexical_bignum_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string and it was of "
      "type integer");
}

TEST(Evaluator_draft4, type_number_valid_decimal_1e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, type_number_valid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft4, format_date_time_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15T14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15T14:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_draft4, format_date_time_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-date\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_draft4, format_date_time_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_email_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_draft4, format_email_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_draft4, format_email_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_hostname_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"www.example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"www.example.com\" was expected to represent a "
      "valid hostname");
}

TEST(Evaluator_draft4, format_hostname_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a "
      "valid hostname");
}

TEST(Evaluator_draft4, format_hostname_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_ipv4_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"192.168.1.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"192.168.1.1\" was expected to represent a "
      "valid IPv4 address");
}

TEST(Evaluator_draft4, format_ipv4_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a "
      "valid IPv4 address");
}

TEST(Evaluator_draft4, format_ipv4_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_ipv6_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"2001:db8::1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2001:db8::1\" was expected to represent a "
      "valid IPv6 address");
}

TEST(Evaluator_draft4, format_ipv6_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not an address\" was expected to represent a "
      "valid IPv6 address");
}

TEST(Evaluator_draft4, format_ipv6_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_uri_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com/path\" was expected to represent "
      "a valid URI");
}

TEST(Evaluator_draft4, format_uri_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft4, format_uri_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_unknown_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "not-a-real-format"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_date_time_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15T14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15T14:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_draft4, format_date_time_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-date\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_draft4, format_date_time_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_email_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_draft4, format_email_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_draft4, format_email_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_hostname_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"www.example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"www.example.com\" was expected to represent a "
      "valid hostname");
}

TEST(Evaluator_draft4, format_hostname_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a "
      "valid hostname");
}

TEST(Evaluator_draft4, format_hostname_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_ipv4_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"192.168.1.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"192.168.1.1\" was expected to represent a "
      "valid IPv4 address");
}

TEST(Evaluator_draft4, format_ipv4_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a "
      "valid IPv4 address");
}

TEST(Evaluator_draft4, format_ipv4_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_ipv6_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"2001:db8::1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2001:db8::1\" was expected to represent a "
      "valid IPv6 address");
}

TEST(Evaluator_draft4, format_ipv6_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not an address\" was expected to represent a "
      "valid IPv6 address");
}

TEST(Evaluator_draft4, format_ipv6_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_uri_valid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com/path\" was expected to represent "
      "a valid URI");
}

TEST(Evaluator_draft4, format_uri_invalid_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft4, format_uri_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_unknown_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "not-a-real-format"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_uri_reference_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_uri_reference_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_uri_template_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"http://example.com/{var}"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_uri_template_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri-template"
  })JSON")};

  const sourcemeta::core::JSON instance{"http://example.com/{var}"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_json_pointer_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/foo/bar"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft4, format_json_pointer_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "json-pointer"
  })JSON")};

  const sourcemeta::core::JSON instance{"/foo/bar"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_date_time_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_date_time_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_email_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_email_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_hostname_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_hostname_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_ipv4_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_ipv4_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_ipv6_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_ipv6_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_uri_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_uri_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_keyword_value_integer_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": 42
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_keyword_value_integer_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": 42
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_keyword_value_null_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": null
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft4, format_keyword_value_null_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "format": null
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft4, format_under_properties_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "format": "uri" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "x": "https://example.com" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/x/format",
                     "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/properties/x/format",
                              "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_draft4, format_under_properties_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "format": "uri" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "relative/path" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/x/format",
                     "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/properties/x/format",
                              "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft4, format_under_items_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "format": "uri" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON([ "https://example.com", "https://example.org" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/items/format", "#/items/format",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/items/format", "#/items/format",
                     "/1");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/items/format",
                              "#/items/format", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringType, "/items/format",
                              "#/items/format", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value \"https://example.org\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_draft4, format_under_items_invalid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "format": "uri" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON([ "https://example.com", "relative/path" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/items/format", "#/items/format",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/items/format", "#/items/format",
                     "/1");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/items/format",
                              "#/items/format", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionStringType, "/items/format",
                              "#/items/format", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft4, format_with_type_string_valid_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 2, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft4, format_with_type_string_invalid_format_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft4, format_with_type_string_non_string_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_draft4, format_with_type_integer_short_circuits_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}
