#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_lint_openapi_3_1, discriminator_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_1, xml_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_1, externalDocs_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_1, example_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_2, discriminator_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_2, xml_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_2, externalDocs_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi_3_2, example_known_with_vocabulary) {
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

TEST(AlterSchema_lint_openapi, discriminator_unknown_without_vocabulary) {
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

TEST(AlterSchema_lint_openapi, xml_unknown_without_vocabulary) {
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

TEST(AlterSchema_lint_openapi, externalDocs_unknown_without_vocabulary) {
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

TEST(AlterSchema_lint_openapi, example_unknown_without_vocabulary) {
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
