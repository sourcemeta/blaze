#include <sourcemeta/core/test.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(openapi_3_2_discriminator_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "discriminator": { "propertyName": "type" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "discriminator": { "propertyName": "type" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_xml_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "xml": { "name": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "xml": { "name": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_externalDocs_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "externalDocs": { "url": "https://example.com" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "object",
    "externalDocs": { "url": "https://example.com" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_example_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "example": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "type": "string",
    "example": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_pattern_non_ecma_regex_invalid_escape) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "pattern": "\\a" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "/properties/foo", "pattern_non_ecma_regex",
      "For interoperability reasons, only set this keyword to a regular "
      "expression that strictly adheres to the ECMA-262 dialect",
      false);
}

TEST(openapi_3_2_pattern_non_ecma_regex_valid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "pattern": "^foo$" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_2_pattern_properties_non_ecma_regex_invalid_escape) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "patternProperties": {
      "\\a": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "pattern_properties_non_ecma_regex",
      "For interoperability reasons, only set the keys of this keyword to "
      "regular expressions that strictly adhere to the ECMA-262 dialect",
      false);
}

TEST(openapi_3_2_pattern_properties_non_ecma_regex_valid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "patternProperties": {
      "^foo$": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_2_valid_examples) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "examples": [ 1 ] }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_valid_examples_matching_instances) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_2_duplicate_examples) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "examples": [ "bar", "bar" ] }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "duplicate_examples",
                    "Setting duplicate values in `examples` is redundant",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_top_level_examples) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);
}

TEST(openapi_3_2_valid_example) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": 1 }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_example",
                    "Only set an `example` value that validates against the "
                    "schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_valid_example_matching_instance) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": "bar" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_2_valid_example_sibling_to_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "$ref": "#/$defs/helper", "example": 1 }
    },
    "$defs": {
      "helper": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_example",
                    "Only set an `example` value that validates against the "
                    "schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "$ref": "#/$defs/helper" }
    },
    "$defs": {
      "helper": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_valid_example_with_valid_examples) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": "bar", "examples": [ "baz" ] }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_2_invalid_example_with_invalid_examples) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": 1, "examples": [ 2 ] }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_example",
                    "Only set an `example` value that validates against the "
                    "schema",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "/properties/foo", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_valid_example_with_invalid_examples) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": "bar", "examples": [ 1 ] }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": "bar" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_invalid_example_with_valid_examples) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "example": 1, "examples": [ "bar" ] }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_example",
                    "Only set an `example` value that validates against the "
                    "schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_2_valid_example_escaped_as_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "object", "example": "<foo>bar</foo>" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_2_valid_example_string_on_string_schema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "maxLength": 3, "example": "toolong" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "valid_example",
                    "Only set an `example` value that validates against the "
                    "schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.2/dialect/2025-09-17",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string", "maxLength": 3 }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
