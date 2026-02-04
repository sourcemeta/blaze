#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_OpenAPI_3_2, discriminator_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "discriminator": {
      "propertyName": "petType",
      "mapping": {
        "dog": "#/definitions/Dog",
        "cat": "#/definitions/Cat"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "petType": "dog",
    "name": "Rex"
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, discriminator_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "discriminator": {
      "propertyName": "petType",
      "mapping": {
        "dog": "#/definitions/Dog",
        "cat": "#/definitions/Cat"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "petType": "dog",
    "name": "Rex"
  })JSON")};
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, xml_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "xml": {
      "nodeType": "element",
      "name": "pet",
      "namespace": "http://example.com/schema",
      "prefix": "ex"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "Rex"
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, xml_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "xml": {
      "nodeType": "element",
      "name": "pet",
      "namespace": "http://example.com/schema",
      "prefix": "ex"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "Rex"
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, externalDocs_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "externalDocs": {
      "url": "https://example.com/docs",
      "description": "Find more info here"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, externalDocs_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "externalDocs": {
      "url": "https://example.com/docs",
      "description": "Find more info here"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, example_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "example": {
      "name": "Rex",
      "petType": "dog"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "Fluffy",
    "petType": "cat"
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, example_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "example": {
      "name": "Rex",
      "petType": "dog"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "Fluffy",
    "petType": "cat"
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_OpenAPI_3_2, type_string_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{"hello"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_OpenAPI_3_2, type_string_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{"hello"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(Evaluator_OpenAPI_3_2, type_string_failure_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_OpenAPI_3_2, type_string_failure_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}
