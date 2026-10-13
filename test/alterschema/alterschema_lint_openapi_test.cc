#include <sourcemeta/core/test.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

static constexpr auto OPENAPI_3_0_DIALECT{
    "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"};

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

TEST(openapi_3_0_title_trim) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "  Test  ",
    "description": "A test schema"
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "title_trim",
                    "Titles should not contain leading or trailing whitespace",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_title_trailing_period) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test.",
    "description": "A test schema"
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "title_trailing_period",
                    "Titles should not end with a period to give user "
                    "interfaces flexibility in presenting the text",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_description_trim) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "  A test schema  "
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "description_trim",
      "Descriptions should not contain leading or trailing whitespace", true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_description_trailing_period) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema."
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "description_trailing_period",
                    "Descriptions should not end with a period to give user "
                    "interfaces flexibility in presenting the text",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_title_description_equal) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "Test"
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "title_description_equal",
                    "The title and description metadata keywords should not "
                    "be set to the same value",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "", "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_top_level_title) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "description": "A test schema",
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_title",
                    "Set a concise non-empty title at the top level of the "
                    "schema to explain what the definition is about",
                    false);
}

TEST(openapi_3_0_top_level_description) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);
}

TEST(openapi_3_0_anyof_true_simplify) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "anyOf": [ {}, { "maxLength": 5 } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "anyof_true_simplify",
                    "An `anyOf` with a `true` or `{}` branch always succeeds",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_double_negation_elimination) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "not": { "not": { "maxLength": 5 } }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "double_negation_elimination",
                    "A `not` whose value is a schema containing only another "
                    "`not` is equivalent to the inner value",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "maxLength": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_drop_allof_empty_schemas) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "allOf": [ {}, { "maxLength": 5 }, { "maxLength": 3 } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "drop_allof_empty_schemas",
                    "Empty schemas in `allOf` are redundant and can be removed",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "allOf": [ { "maxLength": 5 }, { "maxLength": 3 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_duplicate_allof_branches) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "maxLength": 9,
    "allOf": [ { "maxLength": 5 }, { "maxLength": 5 } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "duplicate_allof_branches",
      "Setting duplicate subschemas in `allOf` is redundant, as it produces "
      "unnecessary additional validation that is guaranteed to not affect the "
      "validation result",
      true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "maxLength": 9,
    "allOf": [ { "maxLength": 5 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_duplicate_anyof_branches) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "anyOf": [ { "maxLength": 5 }, { "maxLength": 5 } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "duplicate_anyof_branches",
      "Setting duplicate subschemas in `anyOf` is redundant, as it produces "
      "unnecessary additional validation that is guaranteed to not affect the "
      "validation result",
      true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "anyOf": [ { "maxLength": 5 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_flatten_nested_allof) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "maxLength": 9,
    "minLength": 2,
    "allOf": [ { "allOf": [ { "maxLength": 5 }, { "minLength": 1 } ] } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "flatten_nested_allof",
                    "An `allOf` branch that only contains another `allOf` can "
                    "be flattened into the parent `allOf`",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "maxLength": 9,
    "minLength": 2,
    "allOf": [ { "maxLength": 5 }, { "minLength": 1 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_flatten_nested_anyof) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "anyOf": [ { "anyOf": [ { "maxLength": 5 }, { "minLength": 1 } ] } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "flatten_nested_anyof",
                    "An `anyOf` branch that only contains another `anyOf` can "
                    "be flattened into the parent `anyOf`",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "anyOf": [ { "maxLength": 5 }, { "minLength": 1 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_oneof_to_anyof_disjoint_types) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "oneOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "oneof_to_anyof_disjoint_types",
                    "A `oneOf` where all branches have disjoint types can be "
                    "safely converted to `anyOf`",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "anyOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_oneof_to_anyof_disjoint_types_nullable_branches) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "oneOf": [
      { "type": "string", "nullable": true },
      { "type": "integer", "nullable": true }
    ]
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_unnecessary_allof_ref_wrapper_draft) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "allOf": [ { "$ref": "#/properties/bar" } ] },
      "bar": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo",
                    "unnecessary_allof_ref_wrapper_draft",
                    "Wrapping `$ref` in `allOf` is only necessary if there "
                    "are other sibling keywords",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "$ref": "#/properties/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_unnecessary_allof_wrapper) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "allOf": [ { "maxProperties": 5 } ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "unnecessary_allof_wrapper",
                    "Keywords inside `allOf` that do not conflict with the "
                    "parent schema can be elevated",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "", "drop_allof_empty_schemas",
                    "Empty schemas in `allOf` are redundant and can be removed",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "maxProperties": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_unnecessary_allof_wrapper_nullable_branch) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "allOf": [ { "type": "string", "nullable": true } ]
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_unnecessary_allof_wrapper_nullable_branch_matching_parent) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "allOf": [ { "type": "string", "nullable": true } ]
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_unnecessary_allof_wrapper_nullable_parent) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "nullable": true,
    "allOf": [ { "type": "string" } ]
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_draft_ref_siblings) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "$ref": "#/properties/bar", "maxLength": 5 },
      "bar": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "draft_ref_siblings",
                    "In Draft 7 and older dialects, keywords sibling to "
                    "`$ref` are never evaluated",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "$ref": "#/properties/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_items_schema_default) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "array",
    "items": {}
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "items_schema_default",
                    "Setting the `items` keyword to the true schema does not "
                    "add any further constraint",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "array"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_properties_default) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "properties": {}
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "properties_default",
                    "Setting the `properties` keyword to the empty object "
                    "does not add any further constraint",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_duplicate_enum_values) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": [ "foo", "bar", "foo" ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "duplicate_enum_values",
      "Setting duplicate values in `enum` is considered an anti-pattern", true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_duplicate_required_values) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "required": [ "foo", "foo" ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "duplicate_required_values",
      "Setting duplicate values in `required` is considered an anti-pattern",
      true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "required": [ "foo" ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_enum_with_type) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "enum_with_type",
                    "Setting `type` alongside `enum` is considered an "
                    "anti-pattern, as the enumeration choices already imply "
                    "their respective types",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_equal_numeric_bounds_to_enum) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "equal_numeric_bounds_to_enum",
                    "Setting `minimum` and `maximum` to the same number only "
                    "leaves one possible value",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": [ 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_equal_numeric_bounds_to_enum_nullable) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "nullable": true,
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_exclusive_bounds_false_drop) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "minimum": 3,
    "exclusiveMinimum": false
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "exclusive_bounds_false_drop",
                    "Setting `exclusiveMinimum` or `exclusiveMaximum` to "
                    "`false` adds no constraint",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "minimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_maximum_real_for_integer) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "maximum": 3.5
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "maximum_real_for_integer",
                    "If an instance is guaranteed to be an integer, setting a "
                    "real number upper bound is the same as a floor of that "
                    "upper bound",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "maximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_minimum_real_for_integer) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "minimum": 3.5
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "minimum_real_for_integer",
                    "If an instance is guaranteed to be an integer, setting a "
                    "real number lower bound is the same as a ceil of that "
                    "lower bound",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_multiple_of_default) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "multiple_of_default",
      "Setting `multipleOf` to 1 does not add any further constraint", true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_non_applicable_type_specific_keywords) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "maxItems": 3
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "non_applicable_type_specific_keywords",
                    "Avoid keywords that don't apply to the type or types "
                    "that the current subschema expects",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_non_applicable_type_specific_keywords_nullable) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "nullable": true,
    "maxItems": 3
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "non_applicable_type_specific_keywords",
                    "Avoid keywords that don't apply to the type or types "
                    "that the current subschema expects",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "nullable": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_non_applicable_type_specific_keywords_from_enum) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": [ "foo" ],
    "maxItems": 3
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "non_applicable_type_specific_keywords",
                    "Avoid keywords that don't apply to the type or types "
                    "that the current subschema expects",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": [ "foo" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_forbid_empty_enum) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "enum": []
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "forbid_empty_enum",
                    "An empty `enum` validates nothing and is unsatisfiable",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "not": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_unsatisfiable_min_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "minProperties": 1,
    "required": [ "foo" ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unsatisfiable_min_properties",
                    "Setting `minProperties` to a number less than `required` "
                    "does not add any further constraint",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "required": [ "foo" ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_required_properties_in_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "required": [ "foo" ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "required_properties_in_properties",
                    "Every property listed in the `required` keyword must be "
                    "explicitly defined using the `properties` keyword",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "required": [ "foo" ],
    "properties": {
      "foo": {}
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_pattern_non_ecma_regex) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "pattern": "\\a"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "pattern_non_ecma_regex",
      "For interoperability reasons, only set this keyword to a regular "
      "expression that strictly adheres to the ECMA-262 dialect",
      false);
}

TEST(openapi_3_0_simple_properties_identifiers) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "properties": {
      "foo-bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "simple_properties_identifiers",
      "Set `properties` to identifier names that can be easily mapped to "
      "programming languages (matching [A-Za-z_][A-Za-z0-9_]*)",
      false);
}

TEST(openapi_3_0_conflicting_readonly_writeonly) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "readOnly": true,
    "writeOnly": true
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "conflicting_readonly_writeonly",
                    "The `readOnly` and `writeOnly` keywords are mutually "
                    "exclusive",
                    false);
}

TEST(openapi_3_0_unknown_local_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "properties": {
      "foo": { "$ref": "#/properties/bar" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "unknown_local_ref",
                    "Local references that point to unknown locations are "
                    "invalid and will result in evaluation failures",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "properties": {
      "foo": {}
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_invalid_external_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "$ref": "https://unknown.example.com/nonexistent" }
    }
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
}

TEST(openapi_3_0_unknown_format_prefix) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "format": "uuid"
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unknown_format_prefix",
                    "For interoperability purposes, the JSON Schema "
                    "specification advises against the use of `format` values "
                    "that are not explicitly defined by the specification",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "x-format": "uuid"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_unknown_format_prefix_int32) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "integer",
    "format": "int32"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_unknown_format_prefix_password) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "format": "password"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_unknown_format_prefix_uriref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "format": "uriref"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_valid_default) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "default": 1
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_default",
                    "Only set a `default` value that validates against the "
                    "schema",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_valid_default_matching_instance) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "default": "foo"
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_unsatisfiable_in_place_applicator_type_not_applied) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "allOf": [ { "type": "integer" } ]
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_empty_object_as_true_not_applied) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "object",
    "properties": {
      "foo": {}
    }
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_not_false_not_applied) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "not": false
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_single_type_array_not_applied) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": [ "string" ]
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_items_array_default_not_applied) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "array",
    "items": []
  })JSON");

  LINT_WITHOUT_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                        OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(openapi_3_0_pattern_properties_default_not_applied) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "patternProperties": {}
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unknown_keywords_prefix",
                    "Future versions of JSON Schema will refuse to evaluate "
                    "unknown keywords or custom keywords from optional "
                    "vocabularies that don't have an x- prefix",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "x-patternProperties": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_orphan_definitions_not_applied) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "definitions": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unknown_keywords_prefix",
                    "Future versions of JSON Schema will refuse to evaluate "
                    "unknown keywords or custom keywords from optional "
                    "vocabularies that don't have an x- prefix",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "x-definitions": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_dependencies_default_not_applied) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "dependencies": {}
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unknown_keywords_prefix",
                    "Future versions of JSON Schema will refuse to evaluate "
                    "unknown keywords or custom keywords from optional "
                    "vocabularies that don't have an x- prefix",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "x-dependencies": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_valid_examples_not_applied) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "examples": [ 1 ]
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unknown_keywords_prefix",
                    "Future versions of JSON Schema will refuse to evaluate "
                    "unknown keywords or custom keywords from optional "
                    "vocabularies that don't have an x- prefix",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "x-examples": [ 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_dialect_cannot_be_declared_in_the_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect",
    "title": "Test",
    "description": "A test schema",
    "type": "string"
  })JSON");

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  try {
    [[maybe_unused]] const auto result{bundle.check(
        document, sourcemeta::core::schema_walker, alterschema_test_resolver,
        [](const auto &, const auto &, const auto &, const auto &,
           const auto &) {})};
    FAIL();
  } catch (const sourcemeta::core::SchemaDialectImpossibleError &error) {
    EXPECT_STREQ(error.what(), "The dialect that this schema declares does not "
                               "define the keyword that declares it");
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.dialect(), OPENAPI_3_0_DIALECT);
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "");
  }
}

TEST(openapi_3_0_unsatisfiable_drop_validation) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "type": "string",
    "minLength": 1,
    "not": {}
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unsatisfiable_drop_validation",
                    "Do not place assertions or applicators next to an "
                    "unsatisfiable negation",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "not": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(openapi_3_0_unsatisfiable_drop_validation_with_ref_sibling) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "$ref": "#/properties/bar", "not": {} },
      "bar": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX_WITH_DEFAULT_DIALECT(document, result, traces,
                                    OPENAPI_3_0_DIALECT);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "draft_ref_siblings",
                    "In Draft 7 and older dialects, keywords sibling to "
                    "`$ref` are never evaluated",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "description": "A test schema",
    "properties": {
      "foo": { "$ref": "#/properties/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
