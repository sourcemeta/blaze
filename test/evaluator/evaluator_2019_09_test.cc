#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_2019_09, metaschema_1) {
  const auto metaschema{sourcemeta::jsontoolkit::official_resolver(
      "https://json-schema.org/draft/2019-09/schema")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "type": [ "string" ]
      }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 59);
}

TEST(Evaluator_2019_09, properties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": \"xxx\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyType, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyType, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the defined properties subschemas");
}

TEST(Evaluator_2019_09, properties_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": \"xxx\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/properties", "#/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalAnd, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"bar\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object value was expected to validate "
                               "against the defined properties subschemas");
}

TEST(Evaluator_2019_09, properties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyType, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyType, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_FAILURE(2, LogicalAnd, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the defined properties subschemas");
}

TEST(Evaluator_2019_09, properties_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/properties/bar/type",
                     "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/properties/bar/type",
                              "#/properties/bar/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "bar");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_FAILURE(3, LogicalAnd, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"bar\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the defined properties subschemas");
}

TEST(Evaluator_2019_09, dependentRequired_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar", "baz" ],
      "qux": [ "extra" ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, dependentRequired_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar", "baz" ],
      "qux": [ "extra" ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2, \"baz\": 3 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependentRequired",
                     "#/dependentRequired", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies,
                              "/dependentRequired", "#/dependentRequired", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Because the object value defined the property \"foo\", it was also "
      "expected to define the properties \"bar\", and \"baz\"");
}

TEST(Evaluator_2019_09, dependentRequired_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar", "baz" ],
      "qux": [ "extra" ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependentRequired",
                     "#/dependentRequired", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionPropertyDependencies,
                              "/dependentRequired", "#/dependentRequired", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Because the object value defined the property \"foo\", it was also "
      "expected to define the property \"baz\"");
}

TEST(Evaluator_2019_09, dependentRequired_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar", "baz" ],
      "qux": [ "extra" ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"none\": true }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependentRequired",
                     "#/dependentRequired", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies,
                              "/dependentRequired", "#/dependentRequired", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value did not define the properties \"foo\", or \"qux\"");
}

TEST(Evaluator_2019_09, dependentRequired_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar", "baz" ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"none\": true }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionPropertyDependencies, "/dependentRequired",
                     "#/dependentRequired", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyDependencies,
                              "/dependentRequired", "#/dependentRequired", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object value did not define the property \"foo\"");
}

TEST(Evaluator_2019_09, dependentSchemas_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "required": [ "bar", "baz" ] },
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, dependentSchemas_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "required": [ "bar", "baz" ] },
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"qux\": 1, \"extra\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/dependentSchemas",
                     "#/dependentSchemas", "");
  EVALUATE_TRACE_PRE(1, LogicalWhenDefines, "/dependentSchemas",
                     "#/dependentSchemas", "");
  EVALUATE_TRACE_PRE(2, AssertionDefines, "/dependentSchemas/qux/required",
                     "#/dependentSchemas/qux/required", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefines,
                              "/dependentSchemas/qux/required",
                              "#/dependentSchemas/qux/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalWhenDefines, "/dependentSchemas",
                              "#/dependentSchemas", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalWhenType, "/dependentSchemas",
                              "#/dependentSchemas", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"extra\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value defined the property \"qux\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "Because the object value defined the property \"qux\", it was also "
      "expected to validate against the corresponding subschema");
}

TEST(Evaluator_2019_09, dependentSchemas_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "required": [ "bar", "baz" ] },
      "qux": { "required": [ "extra" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"none\": 1 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/dependentSchemas",
                     "#/dependentSchemas", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LogicalWhenType, "/dependentSchemas",
                              "#/dependentSchemas", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value did not define the properties \"foo\", or \"qux\"");
}

TEST(Evaluator_2019_09, dependentSchemas_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "required": [ "bar" ] },
      "baz": { "required": [ "qux" ] }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": 1, \"bar\": 2, \"baz\": 3, \"qux\": 4 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/dependentSchemas",
                     "#/dependentSchemas", "");
  EVALUATE_TRACE_PRE(1, LogicalWhenDefines, "/dependentSchemas",
                     "#/dependentSchemas", "");
  EVALUATE_TRACE_PRE(2, AssertionDefines, "/dependentSchemas/baz/required",
                     "#/dependentSchemas/baz/required", "");
  EVALUATE_TRACE_PRE(3, LogicalWhenDefines, "/dependentSchemas",
                     "#/dependentSchemas", "");
  EVALUATE_TRACE_PRE(4, AssertionDefines, "/dependentSchemas/foo/required",
                     "#/dependentSchemas/foo/required", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefines,
                              "/dependentSchemas/baz/required",
                              "#/dependentSchemas/baz/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalWhenDefines, "/dependentSchemas",
                              "#/dependentSchemas", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionDefines,
                              "/dependentSchemas/foo/required",
                              "#/dependentSchemas/foo/required", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalWhenDefines, "/dependentSchemas",
                              "#/dependentSchemas", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalWhenType, "/dependentSchemas",
                              "#/dependentSchemas", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was expected to define the property \"qux\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value defined the property \"baz\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was expected to define the property \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value defined the property \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "Because the object value defined the properties \"baz\", and \"foo\", "
      "it was also expected to validate against the corresponding subschemas");
}

TEST(Evaluator_2019_09, additionalProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesType, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesType, "/additionalProperties",
                              "#/additionalProperties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type integer");
}

TEST(Evaluator_2019_09, additionalProperties_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE_ANNOTATION(2, "/additionalProperties",
                                  "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(3, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_PRE_ANNOTATION(4, "/additionalProperties",
                                  "#/additionalProperties", "");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_ANNOTATION(1, "/additionalProperties",
                                   "#/additionalProperties", "", "foo");
    EVALUATE_TRACE_POST_SUCCESS(2, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_ANNOTATION(3, "/additionalProperties",
                                   "#/additionalProperties", "", "bar");
    EVALUATE_TRACE_POST_SUCCESS(4, LoopProperties, "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object property \"foo\" successfully validated against the "
        "additional properties subschema");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 3,
        "The object property \"bar\" successfully validated against the "
        "additional properties subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  } else {
    EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_PRE_ANNOTATION(2, "/additionalProperties",
                                  "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(3, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE_ANNOTATION(4, "/additionalProperties",
                                  "#/additionalProperties", "");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_ANNOTATION(1, "/additionalProperties",
                                   "#/additionalProperties", "", "bar");
    EVALUATE_TRACE_POST_SUCCESS(2, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_ANNOTATION(3, "/additionalProperties",
                                   "#/additionalProperties", "", "foo");
    EVALUATE_TRACE_POST_SUCCESS(4, LoopProperties, "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object property \"bar\" successfully validated against the "
        "additional properties subschema");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 3,
        "The object property \"foo\" successfully validated against the "
        "additional properties subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  }
}

TEST(Evaluator_2019_09, additionalProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "type": "boolean"
      }
    },
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionType, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, additionalProperties_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "type": "boolean"
      }
    },
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": true, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionType, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/additionalProperties",
                                "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionType, "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/additionalProperties",
                                 "#/additionalProperties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object property \"bar\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, additionalProperties_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": \"baz\", \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesType, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopPropertiesType, "/additionalProperties",
                              "#/additionalProperties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type integer");
}

TEST(Evaluator_2019_09, additionalProperties_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "type": "integer"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": \"baz\", \"foo\": 1 }")};

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 4);

    EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_PRE_ANNOTATION(2, "/additionalProperties",
                                  "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(3, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/foo");
    EVALUATE_TRACE_POST_ANNOTATION(1, "/additionalProperties",
                                   "#/additionalProperties", "", "foo");
    EVALUATE_TRACE_POST_FAILURE(2, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_FAILURE(3, LoopProperties, "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0, "The value was expected to be of type integer");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object property \"foo\" successfully validated against the "
        "additional properties subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                                 "The value was expected to be of type integer "
                                 "but it was of type string");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  } else {
    EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 2);

    EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                       "#/additionalProperties", "");
    EVALUATE_TRACE_PRE(1, AssertionType, "/additionalProperties/type",
                       "#/additionalProperties/type", "/bar");

    EVALUATE_TRACE_POST_FAILURE(0, AssertionType, "/additionalProperties/type",
                                "#/additionalProperties/type", "/bar");
    EVALUATE_TRACE_POST_FAILURE(1, LoopProperties, "/additionalProperties",
                                "#/additionalProperties", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The value was expected to be of type integer "
                                 "but it was of type string");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object properties not covered by other "
                                 "adjacent object keywords were "
                                 "expected to validate against this subschema");
  }
}

TEST(Evaluator_2019_09, additionalProperties_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");

  EVALUATE_TRACE_PRE(2, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");

  EVALUATE_TRACE_PRE(3, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/baz");

  // `patternProperties`
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/patternProperties/^bar$/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  // `properties`
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");

  // `additionalProperties`
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/baz");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^bar$\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, additionalProperties_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "type": "boolean" }
    },
    "patternProperties": {
      "^bar$": { "type": "integer" }
    },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{sourcemeta::jsontoolkit::parse(
      "{ \"foo\": true, \"bar\": 2, \"baz\": \"qux\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 9);

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/patternProperties/^bar$/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/patternProperties", "#/patternProperties",
                                "");

  EVALUATE_TRACE_PRE(3, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/properties", "#/properties", "");

  EVALUATE_TRACE_PRE(6, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(7, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/baz");
  EVALUATE_TRACE_PRE_ANNOTATION(8, "/additionalProperties",
                                "#/additionalProperties", "");

  // `patternProperties`
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/patternProperties/^bar$/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ebar$/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                 "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  // `properties`
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/properties", "#/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(5, LogicalAnd, "/properties", "#/properties", "");

  // `additionalProperties`
  EVALUATE_TRACE_POST_SUCCESS(6, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/baz");
  EVALUATE_TRACE_POST_ANNOTATION(7, "/additionalProperties",
                                 "#/additionalProperties", "", "baz");
  EVALUATE_TRACE_POST_SUCCESS(8, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object property \"bar\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that match the regular expression \"^bar$\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 6,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 7,
      "The object property \"baz\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 8,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, contains_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{2};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, contains_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"bar\", 3 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain at least 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain at least 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"foo\", 2 ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain at least 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "maxContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 1, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain 1 to 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "maxContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain 1 to 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 2,
    "maxContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", 1 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain exactly 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 2,
    "maxContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(3, LoopContains, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to contain exactly 2 items that validate "
      "against the given subschema");
}

TEST(Evaluator_2019_09, contains_12) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 3,
    "maxContains": 2,
    "contains": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionFail, "/contains", "#/contains", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionFail, "/contains", "#/contains", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The constraints declared for this keyword were not satisfiable");
}

TEST(Evaluator_2019_09, contains_13) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArraySizeGreater, "/contains", "#/contains",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArraySizeGreater, "/contains",
                              "#/contains", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The array value was expected to contain at "
                               "least 1 item and it contained 3 items");
}

TEST(Evaluator_2019_09, title) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "My title"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, title_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "My title"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/title", "#/title", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/title", "#/title", "", "My title");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The title of the instance was \"My title\"");
}

TEST(Evaluator_2019_09, title_with_core_keywords) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$comment": "My comment",
    "$anchor": "main",
    "title": "My title"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, title_with_core_keywords_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$comment": "My comment",
    "$anchor": "main",
    "title": "My title"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/title", "https://example.com#/title", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/title", "https://example.com#/title", "",
                                 "My title");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The title of the instance was \"My title\"");
}

TEST(Evaluator_2019_09, description) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "description": "My description"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, description_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "description": "My description"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/description", "#/description", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/description", "#/description", "",
                                 "My description");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The description of the instance was \"My description\"");
}

TEST(Evaluator_2019_09, default) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "default": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, default_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "default": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/default", "#/default", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/default", "#/default", "", 1);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The default value of the instance was 1");
}

TEST(Evaluator_2019_09, deprecated_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "deprecated": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, deprecated_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "deprecated": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/deprecated", "#/deprecated", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/deprecated", "#/deprecated", "", true);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance was considered deprecated");
}

TEST(Evaluator_2019_09, deprecated_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "deprecated": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, deprecated_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "deprecated": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/deprecated", "#/deprecated", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/deprecated", "#/deprecated", "", false);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance was not considered deprecated");
}

TEST(Evaluator_2019_09, readOnly_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "readOnly": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, readOnly_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "readOnly": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/readOnly", "#/readOnly", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/readOnly", "#/readOnly", "", false);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance was not considered read-only");
}

TEST(Evaluator_2019_09, readOnly_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "readOnly": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, readOnly_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "readOnly": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/readOnly", "#/readOnly", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/readOnly", "#/readOnly", "", true);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance was considered read-only");
}

TEST(Evaluator_2019_09, writeOnly_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "writeOnly": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, writeOnly_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "writeOnly": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/writeOnly", "#/writeOnly", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/writeOnly", "#/writeOnly", "", false);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance was not considered write-only");
}

TEST(Evaluator_2019_09, writeOnly_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "writeOnly": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, writeOnly_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "writeOnly": true
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/writeOnly", "#/writeOnly", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/writeOnly", "#/writeOnly", "", true);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance was considered write-only");
}

TEST(Evaluator_2019_09, examples) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ 1, 2, 3 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, examples_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ 1, 2, 3 ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  auto examples{sourcemeta::jsontoolkit::JSON::make_array()};
  examples.push_back(sourcemeta::jsontoolkit::JSON{1});
  examples.push_back(sourcemeta::jsontoolkit::JSON{2});
  examples.push_back(sourcemeta::jsontoolkit::JSON{3});

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/examples", "#/examples", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/examples", "#/examples", "", examples);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "Examples of the instance were 1, 2, and 3");
}

TEST(Evaluator_2019_09, contentEncoding) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, contentEncoding_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/contentEncoding", "#/contentEncoding", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/contentEncoding", "#/contentEncoding", "",
                                 "base64");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The content encoding of the instance was \"base64\"");
}

TEST(Evaluator_2019_09, contentMediaType) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentMediaType": "application/json"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, contentMediaType_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentMediaType": "application/json"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/contentMediaType", "#/contentMediaType",
                                "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/contentMediaType", "#/contentMediaType",
                                 "", "application/json");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The content media type of the instance was \"application/json\"");
}

TEST(Evaluator_2019_09, contentSchema) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentSchema": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, contentSchema_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentSchema": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/contentSchema", "#/contentSchema", "");

  auto content_schema{sourcemeta::jsontoolkit::JSON::make_object()};
  content_schema.assign("type", sourcemeta::jsontoolkit::JSON{"string"});

  EVALUATE_TRACE_POST_ANNOTATION(0, "/contentSchema", "#/contentSchema", "",
                                 content_schema);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "When decoded, the instance was expected to validate against the schema "
      "{\"type\":\"string\"}");
}

TEST(Evaluator_2019_09, unknown_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, unknown_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "fooBar": "baz"
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/fooBar", "#/fooBar", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/fooBar", "#/fooBar", "", "baz");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The unrecognized keyword \"fooBar\" was "
                               "collected as the annotation \"baz\"");
}

TEST(Evaluator_2019_09, unknown_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-test": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, unknown_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-test": 1
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-test", "#/x-test", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-test", "#/x-test", "", 1);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The unrecognized keyword \"x-test\" was collected as the annotation 1");
}

TEST(Evaluator_2019_09, items_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, items_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2019_09, items_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");
  EVALUATE_TRACE_PRE(4, LogicalWhenType, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(5, LogicalWhenType, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The value was expected to be of type array");
}

TEST(Evaluator_2019_09, items_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", 5, \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2019_09, items_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", 5, \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2019_09, items_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, items_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_6_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/items", "#/items", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_7_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true, \"extra\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, 1, \"extra\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_8_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, 1, \"extra\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_9_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "integer" }, { "type": "boolean" } ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5, true ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/items/0/type", "#/items/0/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/1/type", "#/items/1/type",
                     "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", 1);
  EVALUATE_TRACE_POST_ANNOTATION(3, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, items_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ true ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The first item of the array value was expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, additionalItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, additionalItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "integer" },
    "items": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2019_09, additionalItems_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "integer" },
    "items": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", \"bar\", \"baz\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/1");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/2");
  EVALUATE_TRACE_PRE(4, LogicalWhenType, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(5, LogicalWhenType, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The value was expected to be of type array");
}

TEST(Evaluator_2019_09, additionalItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5 ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/items/1/type", "#/items/1/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, additionalItems_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5 ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/items/1/type", "#/items/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", 1);
  EVALUATE_TRACE_POST_ANNOTATION(3, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionArrayPrefix, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
}

TEST(Evaluator_2019_09, additionalItems_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/items/1/type", "#/items/1/type", "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/3");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/3");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItems, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_2019_09, additionalItems_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, \"foo\", \"bar\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 9);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/items/1/type", "#/items/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(4, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");
  EVALUATE_TRACE_PRE(6, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/3");
  EVALUATE_TRACE_PRE(7, LogicalWhenArraySizeGreater, "/additionalItems",
                     "#/additionalItems", "");
  EVALUATE_TRACE_PRE_ANNOTATION(8, "/additionalItems", "#/additionalItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_SUCCESS(5, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/3");
  EVALUATE_TRACE_POST_SUCCESS(6, LoopItems, "/additionalItems",
                              "#/additionalItems", "");
  EVALUATE_TRACE_POST_ANNOTATION(7, "/additionalItems", "#/additionalItems", "",
                                 true);
  EVALUATE_TRACE_POST_SUCCESS(8, LogicalWhenArraySizeGreater,
                              "/additionalItems", "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 7, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 8,
                               "The array value contains 2 additional items "
                               "not described by related keywords");
}

TEST(Evaluator_2019_09, additionalItems_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, 6, \"bar\" ]")};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/items/1/type", "#/items/1/type", "/1");
  EVALUATE_TRACE_PRE(3, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItems, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_2019_09, additionalItems_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": { "type": "string" },
    "items": [
      { "type": "boolean" },
      { "type": "integer" }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, 5, 6, \"bar\" ]")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionType, "/items/1/type", "#/items/1/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(4, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/2");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionType, "/items/1/type",
                              "#/items/1/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", 1);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/2");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItems, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value successfully validated against the "
      "given positional subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The value was expected to be of type string but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "Every item in the array value except for the first 2 was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": true }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/unevaluatedProperties",
                                "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/unevaluatedProperties",
                                 "#/unevaluatedProperties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object property \"bar\" successfully validated against the "
      "subschema for unevaluated properties");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "allOf": [
      {
        "properties": {
          "foo": { "type": "string" }
        }
      }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrictEvaluate,
                     "/allOf/0/properties/foo/type",
                     "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrictEvaluate,
                              "/allOf/0/properties/foo/type",
                              "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "allOf": [
      {
        "properties": {
          "foo": { "type": "string" }
        }
      }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": true }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 8);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/allOf/0/properties",
                     "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/properties/foo/type",
                     "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/allOf/0/properties",
                                "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE(4, ControlEvaluate, "/allOf/0/properties",
                     "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_PRE(5, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(6, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(7, "/unevaluatedProperties",
                                "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/allOf/0/properties/foo/type",
                              "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/allOf/0/properties",
                                 "#/allOf/0/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, ControlEvaluate, "/allOf/0/properties",
                              "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalAnd, "/allOf/0/properties",
                              "#/allOf/0/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_SUCCESS(5, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(6, "/unevaluatedProperties",
                                 "#/unevaluatedProperties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(7, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "The object property \"bar\" successfully validated against the "
      "subschema for unevaluated properties");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 7,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "allOf": [
      {
        "properties": {
          "foo": { "type": "string" }
        }
      }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionPropertyTypeStrictEvaluate,
                     "/allOf/0/properties/foo/type",
                     "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrictEvaluate,
                              "/allOf/0/properties/foo/type",
                              "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_FAILURE(3, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "boolean" },
    "allOf": [
      {
        "properties": {
          "foo": { "type": "string" }
        }
      }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 7);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/allOf/0/properties",
                     "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/properties/foo/type",
                     "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/allOf/0/properties",
                                "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE(4, ControlEvaluate, "/allOf/0/properties",
                     "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_PRE(5, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(6, AssertionTypeStrict, "/unevaluatedProperties/type",
                     "#/unevaluatedProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/allOf/0/properties/foo/type",
                              "#/allOf/0/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/allOf/0/properties",
                                 "#/allOf/0/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, ControlEvaluate, "/allOf/0/properties",
                              "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalAnd, "/allOf/0/properties",
                              "#/allOf/0/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_FAILURE(5, AssertionTypeStrict,
                              "/unevaluatedProperties/type",
                              "#/unevaluatedProperties/type", "/bar");
  EVALUATE_TRACE_POST_FAILURE(6, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "The object properties not covered by other object keywords were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": false,
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": true }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionPropertyTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE(1, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionFail, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyTypeStrict,
                              "/properties/foo/type", "#/properties/foo/type",
                              "/foo");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionFail, "/unevaluatedProperties",
                              "#/unevaluatedProperties", "/bar");
  EVALUATE_TRACE_POST_FAILURE(2, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object value was not expected to define the property \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": false,
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\", \"bar\": true }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionFail, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/properties", "#/properties", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionFail, "/unevaluatedProperties",
                              "#/unevaluatedProperties", "/bar");
  EVALUATE_TRACE_POST_FAILURE(4, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define the property \"bar\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": true,
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, unevaluatedProperties_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": true,
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/additionalProperties",
                                "#/additionalProperties", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/additionalProperties",
                                 "#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopProperties, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": { "^@": true },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"@foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_6_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": { "^@": true },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"@foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                "");
  EVALUATE_TRACE_PRE(2, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/patternProperties", "#/patternProperties",
                                 "", "@foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object property \"@foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^@\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "properties": { "foo": true } },
      { "unevaluatedProperties": false }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/allOf/0/properties",
                     "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE(2, ControlEvaluate, "/allOf/0/properties",
                     "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_PRE(3, LoopPropertiesUnevaluated,
                     "/allOf/1/unevaluatedProperties",
                     "#/allOf/1/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionFail, "/allOf/1/unevaluatedProperties",
                     "#/allOf/1/unevaluatedProperties", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlEvaluate, "/allOf/0/properties",
                              "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/allOf/0/properties",
                              "#/allOf/0/properties", "");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionFail,
                              "/allOf/1/unevaluatedProperties",
                              "#/allOf/1/unevaluatedProperties", "/foo");
  EVALUATE_TRACE_POST_FAILURE(3, LoopPropertiesUnevaluated,
                              "/allOf/1/unevaluatedProperties",
                              "#/allOf/1/unevaluatedProperties", "");
  EVALUATE_TRACE_POST_FAILURE(4, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define the property \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define unevaluated properties");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object value was expected to validate "
                               "against the 2 given subschemas");
}

TEST(Evaluator_2019_09, unevaluatedProperties_7_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "properties": { "foo": true } },
      { "unevaluatedProperties": false }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/allOf/0/properties",
                     "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/allOf/0/properties",
                                "#/allOf/0/properties", "");
  EVALUATE_TRACE_PRE(3, ControlEvaluate, "/allOf/0/properties",
                     "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_PRE(4, LoopPropertiesUnevaluated,
                     "/allOf/1/unevaluatedProperties",
                     "#/allOf/1/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(5, AssertionFail, "/allOf/1/unevaluatedProperties",
                     "#/allOf/1/unevaluatedProperties", "/foo");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/allOf/0/properties",
                                 "#/allOf/0/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlEvaluate, "/allOf/0/properties",
                              "#/allOf/0/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf/0/properties",
                              "#/allOf/0/properties", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionFail,
                              "/allOf/1/unevaluatedProperties",
                              "#/allOf/1/unevaluatedProperties", "/foo");
  EVALUATE_TRACE_POST_FAILURE(4, LoopPropertiesUnevaluated,
                              "/allOf/1/unevaluatedProperties",
                              "#/allOf/1/unevaluatedProperties", "");
  EVALUATE_TRACE_POST_FAILURE(5, LogicalAnd, "/allOf", "#/allOf", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define the property \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was not expected to define unevaluated properties");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "The object value was expected to validate "
                               "against the 2 given subschemas");
}

TEST(Evaluator_2019_09, unevaluatedProperties_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": {
      "not": { "properties": { "foo": true } }
    },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalNotEvaluate, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, LogicalNotEvaluate, "/not/not", "#/not/not", "");
  EVALUATE_TRACE_PRE(2, LogicalAnd, "/not/not/properties",
                     "#/not/not/properties", "");
  EVALUATE_TRACE_PRE(3, ControlEvaluate, "/not/not/properties",
                     "#/not/not/properties", "/foo");
  EVALUATE_TRACE_PRE(4, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(5, AssertionFail, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlEvaluate, "/not/not/properties",
                              "#/not/not/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/not/not/properties",
                              "#/not/not/properties", "");
  EVALUATE_TRACE_POST_FAILURE(2, LogicalNotEvaluate, "/not/not", "#/not/not",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalNotEvaluate, "/not", "#/not", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionFail, "/unevaluatedProperties",
                              "#/unevaluatedProperties", "/foo");
  EVALUATE_TRACE_POST_FAILURE(5, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to not validate "
                               "against the given subschema, but it did");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to not validate "
                               "against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object value was not expected to define the property \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_8_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": {
      "not": { "properties": { "foo": true } }
    },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 7);

  EVALUATE_TRACE_PRE(0, LogicalNotEvaluate, "/not", "#/not", "");
  EVALUATE_TRACE_PRE(1, LogicalNotEvaluate, "/not/not", "#/not/not", "");
  EVALUATE_TRACE_PRE(2, LogicalAnd, "/not/not/properties",
                     "#/not/not/properties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/not/not/properties",
                                "#/not/not/properties", "");
  EVALUATE_TRACE_PRE(4, ControlEvaluate, "/not/not/properties",
                     "#/not/not/properties", "/foo");
  EVALUATE_TRACE_PRE(5, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");
  EVALUATE_TRACE_PRE(6, AssertionFail, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "/foo");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/not/not/properties",
                                 "#/not/not/properties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlEvaluate, "/not/not/properties",
                              "#/not/not/properties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/not/not/properties",
                              "#/not/not/properties", "");
  EVALUATE_TRACE_POST_FAILURE(3, LogicalNotEvaluate, "/not/not", "#/not/not",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(4, LogicalNotEvaluate, "/not", "#/not", "");
  EVALUATE_TRACE_POST_FAILURE(5, AssertionFail, "/unevaluatedProperties",
                              "#/unevaluatedProperties", "/foo");
  EVALUATE_TRACE_POST_FAILURE(6, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object property \"foo\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object value was expected to not validate "
                               "against the given subschema, but it did");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object value was expected to not validate "
                               "against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The object value was not expected to define the property \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": false,
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" },
      "g": { "type": "boolean" },
      "h": { "type": "boolean" },
      "i": { "type": "boolean" },
      "j": { "type": "boolean" },
      "k": { "type": "boolean" },
      "l": { "type": "boolean" },
      "m": { "type": "boolean" },
      "n": { "type": "boolean" },
      "o": { "type": "boolean" },
      "p": { "type": "boolean" },
      "q": { "type": "boolean" },
      "r": { "type": "boolean" },
      "s": { "type": "boolean" },
      "t": { "type": "boolean" },
      "u": { "type": "boolean" },
      "v": { "type": "boolean" },
      "w": { "type": "boolean" },
      "x": { "type": "boolean" },
      "y": { "type": "boolean" },
      "z": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"a\": true }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopPropertiesMatch, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/a/type",
                     "#/properties/a/type", "/a");
  EVALUATE_TRACE_PRE(2, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/a/type",
                              "#/properties/a/type", "/a");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesMatch, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object value was expected to validate "
                               "against the 26 defined properties subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_9_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": false,
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" },
      "g": { "type": "boolean" },
      "h": { "type": "boolean" },
      "i": { "type": "boolean" },
      "j": { "type": "boolean" },
      "k": { "type": "boolean" },
      "l": { "type": "boolean" },
      "m": { "type": "boolean" },
      "n": { "type": "boolean" },
      "o": { "type": "boolean" },
      "p": { "type": "boolean" },
      "q": { "type": "boolean" },
      "r": { "type": "boolean" },
      "s": { "type": "boolean" },
      "t": { "type": "boolean" },
      "u": { "type": "boolean" },
      "v": { "type": "boolean" },
      "w": { "type": "boolean" },
      "x": { "type": "boolean" },
      "y": { "type": "boolean" },
      "z": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"a\": true }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopPropertiesMatch, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/properties/a/type",
                     "#/properties/a/type", "/a");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE(3, LoopPropertiesUnevaluatedExcept,
                     "/unevaluatedProperties", "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/properties/a/type",
                              "#/properties/a/type", "/a");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "a");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesMatch, "/properties",
                              "#/properties", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesUnevaluatedExcept,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"a\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the 26 defined properties subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedProperties_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": { "type": "string" },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopPropertiesTypeStrict, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopPropertiesTypeStrict,
                              "/additionalProperties", "#/additionalProperties",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The object properties were expected to be of type string");
}

TEST(Evaluator_2019_09, unevaluatedProperties_10_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": { "type": "string" },
    "unevaluatedProperties": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"baz\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopProperties, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/additionalProperties",
                                "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/additionalProperties",
                                 "#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopProperties, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedProperties_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": false,
    "allOf": [
      { "patternProperties": { "^f": true } }
    ]
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": \"bar\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesStartsWith, "/allOf/0/patternProperties",
                     "#/allOf/0/patternProperties", "");
  EVALUATE_TRACE_PRE(2, ControlEvaluate, "/allOf/0/patternProperties",
                     "#/allOf/0/patternProperties", "/foo");
  EVALUATE_TRACE_PRE(3, LoopPropertiesUnevaluated, "/unevaluatedProperties",
                     "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlEvaluate, "/allOf/0/patternProperties",
                              "#/allOf/0/patternProperties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith,
                              "/allOf/0/patternProperties",
                              "#/allOf/0/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesUnevaluated,
                              "/unevaluatedProperties",
                              "#/unevaluatedProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The instance location was marked as evaluated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object value was not expected to define unevaluated properties");
}

TEST(Evaluator_2019_09, unevaluatedItems_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, false ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);
  EVALUATE_TRACE_PRE(0, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/0");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, false ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);
  EVALUATE_TRACE_PRE(0, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/unevaluatedItems", "#/unevaluatedItems",
                                "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/unevaluatedItems", "#/unevaluatedItems",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/unevaluatedItems", "#/unevaluatedItems",
                                 "", true);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  // TODO: Ideally we wouldn't emit this annotation twice
  EVALUATE_TRACE_POST_ANNOTATION(3, "/unevaluatedItems", "#/unevaluatedItems",
                                 "", true);
  EVALUATE_TRACE_POST_SUCCESS(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "At least one item of the array value successfully validated against the "
      "subschema for unevaluated items");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "At least one item of the array value successfully validated against the "
      "subschema for unevaluated items");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": { "type": "string" },
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\" ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopItems, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": { "type": "string" },
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\" ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/type", "#/items/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, LogicalWhenType, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/type",
                              "#/items/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalWhenType, "/items", "#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type array");
}

TEST(Evaluator_2019_09, unevaluatedItems_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" }, { "type": "string" } ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\" ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefixEvaluate, "/items",
                              "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" }, { "type": "string" } ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\" ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/items", "#/items", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefixEvaluate, "/items",
                              "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first 2 items of the array value were expected to validate against "
      "the corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" } ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\" ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefixEvaluate, "/items",
                              "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" } ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\" ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/items", "#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/items", "#/items", "", 0);
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items", "#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionArrayPrefixEvaluate, "/items",
                              "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" } ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", true ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefixEvaluate, "/items",
                              "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_6_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "string" } ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", true ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefixEvaluate, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/unevaluatedItems", "#/unevaluatedItems",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/items", "#/items", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefixEvaluate, "/items",
                              "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/unevaluatedItems", "#/unevaluatedItems",
                                 "", true);
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "At least one item of the array value successfully validated against the "
      "subschema for unevaluated items");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_7) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "items": [ { "type": "string" } ] }
    ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", true ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                     "#/allOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/items/0/type",
                     "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/items/0/type",
                              "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                              "#/allOf/0/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_7_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "items": [ { "type": "string" } ] }
    ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", true ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 7);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                     "#/allOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/items/0/type",
                     "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/allOf/0/items", "#/allOf/0/items", "");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_PRE_ANNOTATION(6, "/unevaluatedItems", "#/unevaluatedItems",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/items/0/type",
                              "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/allOf/0/items", "#/allOf/0/items", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                              "#/allOf/0/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_ANNOTATION(5, "/unevaluatedItems", "#/unevaluatedItems",
                                 "", true);
  EVALUATE_TRACE_POST_SUCCESS(6, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "At least one item of the array value successfully validated against the "
      "subschema for unevaluated items");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_8) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "items": [ { "type": "string" } ] }
    ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", 1 ]")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                     "#/allOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/items/0/type",
                     "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_PRE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/items/0/type",
                              "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                              "#/allOf/0/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_FAILURE(3, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_8_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "items": [ { "type": "string" } ] }
    ],
    "unevaluatedItems": { "type": "boolean" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ \"foo\", 1 ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_PRE(1, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                     "#/allOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/allOf/0/items/0/type",
                     "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/allOf/0/items", "#/allOf/0/items", "");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(5, AssertionTypeStrict, "/unevaluatedItems/type",
                     "#/unevaluatedItems/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/allOf/0/items/0/type",
                              "#/allOf/0/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/allOf/0/items", "#/allOf/0/items", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefixEvaluate, "/allOf/0/items",
                              "#/allOf/0/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalAnd, "/allOf", "#/allOf", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionTypeStrict, "/unevaluatedItems/type",
                              "#/unevaluatedItems/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_9) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "boolean" } ],
    "additionalItems": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, false ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE(2, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/1");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/additionalItems",
                              "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "Every item in the array value except for the first one was expected to "
      "validate against the given subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_9_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [ { "type": "boolean" } ],
    "additionalItems": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ true, false ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 7);

  EVALUATE_TRACE_PRE(0, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/items/0/type", "#/items/0/type",
                     "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(3, LoopItems, "/additionalItems", "#/additionalItems", "");
  EVALUATE_TRACE_PRE(4, AssertionTypeStrict, "/additionalItems/type",
                     "#/additionalItems/type", "/1");
  EVALUATE_TRACE_PRE(5, LogicalWhenArraySizeGreater, "/additionalItems",
                     "#/additionalItems", "");
  EVALUATE_TRACE_PRE_ANNOTATION(6, "/additionalItems", "#/additionalItems", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/items/0/type",
                              "#/items/0/type", "/0");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/items", "#/items", "", 0);
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/additionalItems/type",
                              "#/additionalItems/type", "/1");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopItems, "/additionalItems",
                              "#/additionalItems", "");
  EVALUATE_TRACE_POST_ANNOTATION(5, "/additionalItems", "#/additionalItems", "",
                                 true);
  EVALUATE_TRACE_POST_SUCCESS(6, LogicalWhenArraySizeGreater,
                              "/additionalItems", "#/additionalItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "Every item in the array value except for the first one was expected to "
      "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 6,
                               "The array value contains 1 additional item not "
                               "described by related keywords");
}

TEST(Evaluator_2019_09, unevaluatedItems_10) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false ]")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(3, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_10_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "boolean" },
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/contains/type",
                     "#/contains/type", "/0");
  EVALUATE_TRACE_PRE(2, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(3, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/contains/type",
                              "#/contains/type", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopContains, "/contains", "#/contains", "");
  EVALUATE_TRACE_POST_FAILURE(2, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(3, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The array value was expected to contain at least 1 item that validates "
      "against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_11) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false, 1 ]")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, LoopItems, "/anyOf/0/items", "#/anyOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(5, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/anyOf/0/items", "#/anyOf/0/items",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to validate against at least one of the 2 "
      "given subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, unevaluatedItems_11_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [
      { "items": { "type": "boolean" } },
      true
    ],
    "unevaluatedItems": false
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ false, 1 ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_PRE(1, LoopItems, "/anyOf/0/items", "#/anyOf/0/items", "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/anyOf/0/items/type",
                     "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_PRE(4, LoopItemsUnevaluated, "/unevaluatedItems",
                     "#/unevaluatedItems", "");
  EVALUATE_TRACE_PRE(5, AssertionFail, "/unevaluatedItems",
                     "#/unevaluatedItems", "/0");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionTypeStrict, "/anyOf/0/items/type",
                              "#/anyOf/0/items/type", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/anyOf/0/items", "#/anyOf/0/items",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(3, LogicalOr, "/anyOf", "#/anyOf", "");
  EVALUATE_TRACE_POST_FAILURE(4, AssertionFail, "/unevaluatedItems",
                              "#/unevaluatedItems", "/0");
  EVALUATE_TRACE_POST_FAILURE(5, LoopItemsUnevaluated, "/unevaluatedItems",
                              "#/unevaluatedItems", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type boolean "
                               "but it was of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The array value was expected to validate against at least one of the 2 "
      "given subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The array value was not expected to define the item at index 0");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The array items not covered by other array keywords, if any, were "
      "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "additionalProperties": {
      "$recursiveRef": "#"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/schema", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(
      2, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/schema",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      2, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "additionalProperties": {
      "$recursiveRef": "#"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/schema", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(
      2, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(
      3, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/schema",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(
      2, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(
      3, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "minimum": 1,
    "additionalProperties": {
      "$recursiveRef": "#"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/schema", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(
      2, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_PRE(3, AssertionGreaterEqual,
                     "/additionalProperties/$recursiveRef/minimum",
                     "https://example.com/schema#/minimum", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/schema",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionGreaterEqual,
                              "/additionalProperties/$recursiveRef/minimum",
                              "https://example.com/schema#/minimum", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      2, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      3, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "minimum": 1,
    "additionalProperties": {
      "$recursiveRef": "#"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/schema", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(
      2, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_PRE(3, AssertionGreaterEqual,
                     "/additionalProperties/$recursiveRef/minimum",
                     "https://example.com/schema#/minimum", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(
      4, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/schema",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionGreaterEqual,
                              "/additionalProperties/$recursiveRef/minimum",
                              "https://example.com/schema#/minimum", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      2, ControlDynamicAnchorJump, "/additionalProperties/$recursiveRef",
      "https://example.com/schema#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(
      3, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(
      4, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "$id": "nested",
      "$recursiveAnchor": true,
      "minimum": 1,
      "additionalProperties": {
        "$recursiveRef": "#"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/nested", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionGreaterEqual, "/additionalProperties/minimum",
                     "https://example.com/nested#/minimum", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/nested",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionGreaterEqual,
                              "/additionalProperties/minimum",
                              "https://example.com/nested#/minimum", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      2, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 1");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "$id": "nested",
      "$recursiveAnchor": true,
      "minimum": 1,
      "additionalProperties": {
        "$recursiveRef": "#"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/nested", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, AssertionGreaterEqual, "/additionalProperties/minimum",
                     "https://example.com/nested#/minimum", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(
      3, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/nested",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionGreaterEqual,
                              "/additionalProperties/minimum",
                              "https://example.com/nested#/minimum", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(
      2, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(
      3, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for "
                               "future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "$id": "nested",
      "$recursiveAnchor": true,
      "minimum": 1,
      "additionalProperties": {
        "$recursiveRef": "#"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": 1 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/nested", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(
      2, LoopProperties, "/additionalProperties/additionalProperties",
      "https://example.com/nested#/additionalProperties", "/foo");
  EVALUATE_TRACE_PRE(
      3, ControlDynamicAnchorJump,
      "/additionalProperties/additionalProperties/$recursiveRef",
      "https://example.com/nested#/additionalProperties/$recursiveRef",
      "/foo/bar");
  EVALUATE_TRACE_PRE(
      4, AssertionGreaterEqual,
      "/additionalProperties/additionalProperties/$recursiveRef/minimum",
      "https://example.com/nested#/minimum", "/foo/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/nested",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, AssertionGreaterEqual,
      "/additionalProperties/additionalProperties/$recursiveRef/minimum",
      "https://example.com/nested#/minimum", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(
      2, ControlDynamicAnchorJump,
      "/additionalProperties/additionalProperties/$recursiveRef",
      "https://example.com/nested#/additionalProperties/$recursiveRef",
      "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(
      3, LoopProperties, "/additionalProperties/additionalProperties",
      "https://example.com/nested#/additionalProperties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(
      4, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for "
                               "future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": {
      "$id": "nested",
      "$recursiveAnchor": true,
      "minimum": 1,
      "additionalProperties": {
        "$recursiveRef": "#"
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": 1 } }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 7);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/nested", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "https://example.com/schema#/additionalProperties", "");
  EVALUATE_TRACE_PRE(
      2, LoopProperties, "/additionalProperties/additionalProperties",
      "https://example.com/nested#/additionalProperties", "/foo");
  EVALUATE_TRACE_PRE(
      3, ControlDynamicAnchorJump,
      "/additionalProperties/additionalProperties/$recursiveRef",
      "https://example.com/nested#/additionalProperties/$recursiveRef",
      "/foo/bar");
  EVALUATE_TRACE_PRE(
      4, AssertionGreaterEqual,
      "/additionalProperties/additionalProperties/$recursiveRef/minimum",
      "https://example.com/nested#/minimum", "/foo/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(
      5, "/additionalProperties/additionalProperties",
      "https://example.com/nested#/additionalProperties", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(
      6, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/nested",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, AssertionGreaterEqual,
      "/additionalProperties/additionalProperties/$recursiveRef/minimum",
      "https://example.com/nested#/minimum", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(
      2, ControlDynamicAnchorJump,
      "/additionalProperties/additionalProperties/$recursiveRef",
      "https://example.com/nested#/additionalProperties/$recursiveRef",
      "/foo/bar");
  EVALUATE_TRACE_POST_ANNOTATION(
      3, "/additionalProperties/additionalProperties",
      "https://example.com/nested#/additionalProperties", "/foo", "bar");
  EVALUATE_TRACE_POST_SUCCESS(
      4, LoopProperties, "/additionalProperties/additionalProperties",
      "https://example.com/nested#/additionalProperties", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(
      5, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(
      6, LoopProperties, "/additionalProperties",
      "https://example.com/schema#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for "
                               "future use");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The integer value 1 was expected to be greater "
                               "than or equal to the integer 1");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object property \"bar\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 4,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 6,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "$id": "nested",
      "$recursiveAnchor": true,
      "items": [
        { "$recursiveRef": "#" }
      ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ [ 1 ] ]")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/nested", "");
  EVALUATE_TRACE_PRE(1, LoopItems, "/items",
                     "https://example.com/schema#/items", "");
  EVALUATE_TRACE_PRE(2, AssertionArrayPrefix, "/items/items",
                     "https://example.com/nested#/items", "/0");
  EVALUATE_TRACE_PRE(
      3, ControlDynamicAnchorJump, "/items/items/0/$recursiveRef",
      "https://example.com/nested#/items/0/$recursiveRef", "/0/0");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/nested",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlDynamicAnchorJump, "/items/items/0/$recursiveRef",
      "https://example.com/nested#/items/0/$recursiveRef", "/0/0");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionArrayPrefix, "/items/items",
                              "https://example.com/nested#/items", "/0");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopItems, "/items",
                              "https://example.com/schema#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for "
                               "future use");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
}

TEST(Evaluator_2019_09, recursiveRef_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "$id": "nested",
      "$recursiveAnchor": true,
      "items": [
        { "$recursiveRef": "#" }
      ]
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("[ [ 1 ] ]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 8);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "https://example.com/nested", "");
  EVALUATE_TRACE_PRE(1, LoopItems, "/items",
                     "https://example.com/schema#/items", "");
  EVALUATE_TRACE_PRE(2, AssertionArrayPrefix, "/items/items",
                     "https://example.com/nested#/items", "/0");
  EVALUATE_TRACE_PRE(
      3, ControlDynamicAnchorJump, "/items/items/0/$recursiveRef",
      "https://example.com/nested#/items/0/$recursiveRef", "/0/0");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/items/items",
                                "https://example.com/nested#/items", "/0");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/items/items",
                                "https://example.com/nested#/items", "/0");
  EVALUATE_TRACE_PRE(6, LogicalWhenType, "/items",
                     "https://example.com/schema#/items", "");
  EVALUATE_TRACE_PRE_ANNOTATION(7, "/items",
                                "https://example.com/schema#/items", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "https://example.com/nested",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlDynamicAnchorJump, "/items/items/0/$recursiveRef",
      "https://example.com/nested#/items/0/$recursiveRef", "/0/0");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/items/items",
                                 "https://example.com/nested#/items", "/0", 0);
  EVALUATE_TRACE_POST_ANNOTATION(
      3, "/items/items", "https://example.com/nested#/items", "/0", true);
  EVALUATE_TRACE_POST_SUCCESS(4, AssertionArrayPrefix, "/items/items",
                              "https://example.com/nested#/items", "/0");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopItems, "/items",
                              "https://example.com/schema#/items", "");
  EVALUATE_TRACE_POST_ANNOTATION(6, "/items",
                                 "https://example.com/schema#/items", "", true);
  EVALUATE_TRACE_POST_SUCCESS(7, LogicalWhenType, "/items",
                              "https://example.com/schema#/items", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for "
                               "future use");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The first item of the array value successfully validated against the "
      "first positional subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The first item of the array value was expected to validate against the "
      "corresponding subschemas");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 5,
                               "Every item in the array value was expected to "
                               "validate against the given subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 6, "Every item in the array value was successfully validated");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 7,
                               "The value was expected to be of type array");
}

TEST(Evaluator_2019_09, recursiveRef_6) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "additionalProperties": {
      "$recursiveRef": "#"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, ControlDynamicAnchorJump,
                     "/additionalProperties/$recursiveRef",
                     "#/additionalProperties/$recursiveRef", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "", "");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlDynamicAnchorJump,
                              "/additionalProperties/$recursiveRef",
                              "#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopProperties, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, recursiveRef_6_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "additionalProperties": {
      "$recursiveRef": "#"
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, ControlMark, "", "", "");
  EVALUATE_TRACE_PRE(1, LoopProperties, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(2, ControlDynamicAnchorJump,
                     "/additionalProperties/$recursiveRef",
                     "#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/additionalProperties",
                                "#/additionalProperties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, ControlMark, "", "", "");
  EVALUATE_TRACE_POST_SUCCESS(1, ControlDynamicAnchorJump,
                              "/additionalProperties/$recursiveRef",
                              "#/additionalProperties/$recursiveRef", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/additionalProperties",
                                 "#/additionalProperties", "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopProperties, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The schema location was marked for future use");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The integer value was expected to validate against the first subschema "
      "in scope that declared a recursive anchor");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object property \"foo\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The object properties not covered by other "
                               "adjacent object keywords were "
                               "expected to validate against this subschema");
}

TEST(Evaluator_2019_09, reference_from_unknown_keyword) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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
    sourcemeta::blaze::compile(schema,
                               sourcemeta::jsontoolkit::default_schema_walker,
                               sourcemeta::jsontoolkit::official_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::jsontoolkit::SchemaReferenceError &error) {
    EXPECT_EQ(error.id(), "#/properties/baz");
    EXPECT_EQ(error.location(),
              sourcemeta::jsontoolkit::Pointer({"definitions", "bar", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_2019_09, patternProperties_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "^f": true
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0);
}

TEST(Evaluator_2019_09, patternProperties_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "^f": true
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/patternProperties", "#/patternProperties",
                                 "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object property \"foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_2) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_2_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/patternProperties", "#/patternProperties",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                 "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object property \"foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_3) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "o$": { "type": "integer" },
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_PRE(2, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(3, AssertionType, "/patternProperties/o$/type",
                     "#/patternProperties/o$/type", "/foo");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionType, "/patternProperties/o$/type",
                              "#/patternProperties/o$/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(3, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object properties that match the regular expression \"o$\" were "
      "expected to validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_3_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "o$": { "type": "integer" },
      "^f": { "type": "integer" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"bar\": 2, \"foo\": 1 }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 6);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionType, "/patternProperties/^f/type",
                     // Note that the caret needs to be URI escaped
                     "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/patternProperties", "#/patternProperties",
                                "");
  EVALUATE_TRACE_PRE(3, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(4, AssertionType, "/patternProperties/o$/type",
                     "#/patternProperties/o$/type", "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(5, "/patternProperties", "#/patternProperties",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/patternProperties/^f/type",
                              // Note that the caret needs to be URI escaped
                              "#/patternProperties/%5Ef/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                 "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(3, AssertionType, "/patternProperties/o$/type",
                              "#/patternProperties/o$/type", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(4, "/patternProperties", "#/patternProperties",
                                 "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(5, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object property \"foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object property \"foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 5,
      "The object properties that match the regular expression \"o$\" were "
      "expected to validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_4) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "^f": {
        "patternProperties": {
          "^b": { "type": "integer" }
        }
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": 2 } }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesStartsWith,
                     "/patternProperties/^f/patternProperties",
                     "#/patternProperties/%5Ef/patternProperties", "/foo");
  EVALUATE_TRACE_PRE(
      2, AssertionType, "/patternProperties/^f/patternProperties/^b/type",
      "#/patternProperties/%5Ef/patternProperties/%5Eb/type", "/foo/bar");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionType, "/patternProperties/^f/patternProperties/^b/type",
      "#/patternProperties/%5Ef/patternProperties/%5Eb/type", "/foo/bar");
  EVALUATE_TRACE_POST_SUCCESS(
      1, LoopPropertiesStartsWith, "/patternProperties/^f/patternProperties",
      "#/patternProperties/%5Ef/patternProperties", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that start with the string \"b\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_4_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {
      "^f": {
        "patternProperties": {
          "^b": { "type": "integer" }
        }
      }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"foo\": { \"bar\": 2 } }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LoopPropertiesStartsWith, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesStartsWith,
                     "/patternProperties/^f/patternProperties",
                     "#/patternProperties/%5Ef/patternProperties", "/foo");
  EVALUATE_TRACE_PRE(
      2, AssertionType, "/patternProperties/^f/patternProperties/^b/type",
      "#/patternProperties/%5Ef/patternProperties/%5Eb/type", "/foo/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(3, "/patternProperties/^f/patternProperties",
                                "#/patternProperties/%5Ef/patternProperties",
                                "/foo");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/patternProperties", "#/patternProperties",
                                "");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionType, "/patternProperties/^f/patternProperties/^b/type",
      "#/patternProperties/%5Ef/patternProperties/%5Eb/type", "/foo/bar");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/patternProperties/^f/patternProperties",
                                 "#/patternProperties/%5Ef/patternProperties",
                                 "/foo", "bar");
  EVALUATE_TRACE_POST_SUCCESS(
      2, LoopPropertiesStartsWith, "/patternProperties/^f/patternProperties",
      "#/patternProperties/%5Ef/patternProperties", "/foo");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/patternProperties", "#/patternProperties",
                                 "", "foo");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopPropertiesStartsWith, "/patternProperties",
                              "#/patternProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object property \"bar\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object properties that start with the string \"b\" were expected to "
      "validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object property \"foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object properties that start with the string \"f\" were expected to "
      "validate against the defined pattern property subschema");
}

TEST(Evaluator_2019_09, patternProperties_5) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": { "^@": true },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"@foo\": 1, \"bar\": \"baz\" }")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2);

  EVALUATE_TRACE_PRE(0, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_2019_09, patternProperties_5_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": { "^@": true },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse("{ \"@foo\": 1, \"bar\": \"baz\" }")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 5);

  EVALUATE_TRACE_PRE(0, LoopPropertiesRegex, "/patternProperties",
                     "#/patternProperties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/patternProperties", "#/patternProperties",
                                "");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/additionalProperties",
                     "#/additionalProperties", "");
  EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/additionalProperties/type",
                     "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_PRE_ANNOTATION(4, "/additionalProperties",
                                "#/additionalProperties", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/patternProperties", "#/patternProperties",
                                 "", "@foo");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesRegex, "/patternProperties",
                              "#/patternProperties", "");
  EVALUATE_TRACE_POST_SUCCESS(2, AssertionTypeStrict,
                              "/additionalProperties/type",
                              "#/additionalProperties/type", "/bar");
  EVALUATE_TRACE_POST_ANNOTATION(3, "/additionalProperties",
                                 "#/additionalProperties", "", "bar");
  EVALUATE_TRACE_POST_SUCCESS(4, LoopPropertiesExcept, "/additionalProperties",
                              "#/additionalProperties", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The object property \"@foo\" successfully validated against its pattern "
      "property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The object properties that match the regular expression \"^@\" were "
      "expected to validate against the defined pattern property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 3,
      "The object property \"bar\" successfully validated against the "
      "additional properties subschema");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 4,
      "The object properties not covered by other adjacent object keywords "
      "were expected to validate against this subschema");
}

TEST(Evaluator_2019_09, definitions_1) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/definitions/middle",
    "definitions": {
      "middle": { "$ref": "#/definitions/string" },
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/$ref/type",
                     "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_2019_09, definitions_1_exhaustive) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/definitions/middle",
    "definitions": {
      "middle": { "$ref": "#/definitions/string" },
      "string": { "type": "string" }
    }
  })JSON")};

  const sourcemeta::jsontoolkit::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 3);

  EVALUATE_TRACE_PRE(0, LogicalAnd, "/$ref", "#/$ref", "");
  EVALUATE_TRACE_PRE(1, LogicalAnd, "/$ref/$ref", "#/definitions/middle/$ref",
                     "");
  EVALUATE_TRACE_PRE(2, AssertionTypeStrict, "/$ref/$ref/type",
                     "#/definitions/string/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/$ref/type",
                              "#/definitions/string/type", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LogicalAnd, "/$ref/$ref",
                              "#/definitions/middle/$ref", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalAnd, "/$ref", "#/$ref", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The string value was expected to validate "
                               "against the statically referenced schema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The string value was expected to validate "
                               "against the statically referenced schema");
}
