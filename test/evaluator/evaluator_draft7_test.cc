#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft7, metaschema) {
  const auto metaschema{sourcemeta::core::official_resolver(
      "http://json-schema.org/draft-07/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 3);
}

TEST(Evaluator_draft7, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::official_resolver(
      "http://json-schema.org/draft-07/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 462);
}

TEST(Evaluator_draft7, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::official_resolver(
      "http://json-schema.org/draft-07/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         567);
}

TEST(Evaluator_draft7, if_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 1 }
  })JSON")};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 1 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, if_1_hyperschema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/hyper-schema#",
    "if": { "const": 1 }
  })JSON")};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 1 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, if_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 1 }
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, then_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "then": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft7, then_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 10 },
    "then": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_PRE(2, AssertionDivisible, "/then/multipleOf",
                     "#/then/multipleOf", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionDivisible, "/then/multipleOf",
                              "#/then/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to equal the integer constant 10");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value 10 was expected to be divisible by the integer 5");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, then_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 10 },
    "then": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to equal the integer constant 10");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, then_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": { "multipleOf": 5 },
    "else": { "multipleOf": 8 }
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/then/multipleOf",
                     "#/then/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDivisible, "/then/multipleOf",
                              "#/then/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be divisible by the integer 5");
}

TEST(Evaluator_draft7, then_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": true,
    "then": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionDivisible, "/then/multipleOf",
                     "#/then/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionDivisible, "/then/multipleOf",
                              "#/then/multipleOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 2 was expected to be divisible by the integer 5");
}

TEST(Evaluator_draft7, then_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": {
        "allOf": [
          {
            "if": { "type": "object" },
            "then": {
              "required": [ "bar" ]
            }
          }
        ]
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse("{ \"foo\": { \"bar\": 1 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/properties/foo/allOf/0/if",
                     "#/properties/foo/allOf/0/if", "/foo");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/allOf/0/if/type",
                     "#/properties/foo/allOf/0/if/type", "/foo");
  EVALUATE_TRACE_PRE(2, AssertionDefines,
                     "/properties/foo/allOf/0/then/required",
                     "#/properties/foo/allOf/0/then/required", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/properties/foo/allOf/0/if/type",
                              "#/properties/foo/allOf/0/if/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionDefines,
                              "/properties/foo/allOf/0/then/required",
                              "#/properties/foo/allOf/0/then/required", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalCondition, "/properties/foo/allOf/0/if",
                              "#/properties/foo/allOf/0/if", "/foo");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was expected to define the property \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, else_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "else": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft7, else_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 1 },
    "else": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 1 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, else_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 1 },
    "else": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_PRE(2, AssertionDivisible, "/else/multipleOf",
                     "#/else/multipleOf", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionDivisible, "/else/multipleOf",
                              "#/else/multipleOf", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value 10 was expected to be divisible by the integer 5");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, else_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "if": { "const": 1 },
    "else": { "multipleOf": 5 }
  })JSON")};

  const sourcemeta::core::JSON instance{8};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalCondition, "/if", "#/if", "");
  EVALUATE_TRACE_PRE(1, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_PRE(2, AssertionDivisible, "/else/multipleOf",
                     "#/else/multipleOf", "");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionEqual, "/if/const", "#/if/const", "");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionDivisible, "/else/multipleOf",
                              "#/else/multipleOf", "");
  EVALUATE_TRACE_POST_FAILURE(2, LogicalCondition, "/if", "#/if", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 8 was expected to equal the integer constant 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value 8 was expected to be divisible by the integer 5");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The integer value was expected to validate "
                               "against the given conditional");
}

TEST(Evaluator_draft7, invalid_ref_top_level) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::default_schema_walker,
                               sourcemeta::core::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"$ref"}));
    SUCCEED();
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft7, invalid_ref_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": {
        "$ref": "#/definitions/i-dont-exist"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::default_schema_walker,
                               sourcemeta::core::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft7, invalid_ref_embedded) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$id": "https://example.com",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": {
      "$ref": "#/definitions/bar"
    },
    "definitions": {
      "bar": {
        "$id": "https://example.com/nested",
        "additionalProperties": {
          "$ref": "#/definitions/baz"
        }
      },
      "baz": {}
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::default_schema_walker,
                               sourcemeta::core::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer(
                  {"definitions", "bar", "additionalProperties", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft7, metadata) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "My title",
    "description": "My description",
    "default": 1,
    "readOnly": true,
    "writeOnly": false,
    "examples": [ 1, 2, 3 ]
  })JSON")};

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft7, content) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON")};

  const sourcemeta::core::JSON instance{"test"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft7, unknown_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft7, unknown_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "x-test": 1
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_draft7, reference_from_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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
    sourcemeta::blaze::compile(schema, sourcemeta::core::default_schema_walker,
                               sourcemeta::core::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.id(), "#/properties/baz");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"$defs", "bar", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft7, items_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": {
      "type": "number"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse("[ 11, 54 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopItemsTypeStrictAny, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsTypeStrictAny, "/items", "#/items",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array items were expected to be of type number, or integer");
}
