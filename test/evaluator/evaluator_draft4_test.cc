#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(metaschema_1) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 3, "");
}

TEST(metaschema_2) {
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

TEST(metaschema_invalid_definition) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "type": 1
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(metaschema.value(), instance, 10, "");
}

TEST(metaschema_invalid_definition_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "type": 1
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(metaschema.value(), instance, 11, "");
}

TEST(metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 768,
                                   "");
}

TEST(metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         957, "");
}

TEST(ref_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_STREQ(error.what(), "Could not resolve schema reference");
  }
}

TEST(ref_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/i-dont-exist" } ]
  })JSON")};

  auto test_resolver = [](const std::string_view identifier)
      -> sourcemeta::core::SchemaResolverResult {
    if (identifier == "https://example.com") {
      return sourcemeta::core::parse_json(R"JSON({
                "$schema": "http://json-schema.org/draft-04/schema#",
                "id": "https://example.com"
              })JSON");
    }

    return sourcemeta::core::schema_resolver(identifier);
  };

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               test_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_STREQ(error.what(), "Could not resolve schema reference");
  }
}

TEST(ref_14) {
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

TEST(pattern_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(pattern_5) {
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
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(pattern_6) {
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
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com/");
  } catch (...) {
    FAIL();
  }
}

TEST(pattern_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "id": "https://nested.com",
        "pattern": "("
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "(");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com/");
  } catch (...) {
    FAIL();
  }
}

TEST(patternProperties_9) {
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
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\_\\.\\-]*$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"patternProperties"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(invalid_ref_top_level) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::core::SchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "Cannot bundle a JSON Schema Draft 7 or older with a "
                 "top-level `$ref` (which overrides sibling keywords) without "
                 "introducing undefined behavior");
  }
}

TEST(invalid_ref_nested) {
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

TEST(invalid_ref_embedded) {
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

TEST(reference_from_unknown_keyword) {
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

TEST(reference_to_nested_unknown_keyword) {
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

TEST(ref_to_non_schema) {
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
    FAIL();
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(), "#/definitions/array/items");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"definitions", "array", "items"}));
  } catch (...) {
    FAIL();
  }
}

TEST(top_level_ref_with_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation);
    FAIL();
  } catch (const sourcemeta::core::SchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "Cannot bundle a JSON Schema Draft 7 or older with a "
                 "top-level `$ref` (which overrides sibling keywords) without "
                 "introducing undefined behavior");
  }
}

TEST(top_level_ref_with_id_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive);
    FAIL();
  } catch (const sourcemeta::core::SchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "Cannot bundle a JSON Schema Draft 7 or older with a "
                 "top-level `$ref` (which overrides sibling keywords) without "
                 "introducing undefined behavior");
  }
}

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

TEST(boolean_root_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json("true")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation,
                               "http://json-schema.org/draft-04/schema#");
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(), "This dialect does not support boolean schemas");
  } catch (...) {
    FAIL();
  }
}

TEST(boolean_subschema_entrypoint) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "everything": true
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "#/definitions/everything");
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(), "This dialect does not support boolean schemas");
  } catch (...) {
    FAIL();
  }
}
