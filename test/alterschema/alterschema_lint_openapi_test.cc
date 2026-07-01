#include <sourcemeta/core/test.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(openapi_3_1_discriminator_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "discriminator": { "propertyName": "type" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "discriminator": { "propertyName": "type" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_1_xml_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "xml": { "name": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "xml": { "name": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_1_externalDocs_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "externalDocs": { "url": "https://example.com" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object",
    "externalDocs": { "url": "https://example.com" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_1_example_known_with_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "example": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "string",
    "example": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

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

TEST(openapi_discriminator_unknown_without_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "discriminator": { "propertyName": "type" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-discriminator": { "propertyName": "type" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_xml_unknown_without_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "xml": { "name": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-xml": { "name": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_externalDocs_unknown_without_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "externalDocs": { "url": "https://example.com" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-externalDocs": { "url": "https://example.com" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_example_unknown_without_vocabulary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "example": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "x-example": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_1_pattern_non_ecma_regex_invalid_escape) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
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

TEST(openapi_3_1_pattern_non_ecma_regex_valid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
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

TEST(openapi_3_1_pattern_properties_non_ecma_regex_invalid_escape) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
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

TEST(openapi_3_1_pattern_properties_non_ecma_regex_valid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
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
