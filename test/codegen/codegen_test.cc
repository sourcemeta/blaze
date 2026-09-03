#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/blaze/foundation.h>

#include <sstream> // std::ostringstream

#include "codegen_test_utils.h"

TEST(unsupported_dialect_draft3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_STREQ(error.what(), "Unsupported required vocabulary");
  }
}

TEST(unsupported_keyword_error_not) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnsupportedKeywordError &error) {
    EXPECT_STREQ(error.what(), "Unsupported keyword in subschema");
  }
}

TEST(unsupported_keyword_value_error_type_not_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": 123
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a string value");
  }
}

TEST(unknown_type_value_ignored) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "foo"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);

  EXPECT_EQ(output.str(), "export type Schema_5 = number;\n"
                          "\n"
                          "export type Schema_4 = string;\n"
                          "\n"
                          "export type Schema_3Items = unknown;\n"
                          "\n"
                          "export type Schema_3 = Schema_3Items[];\n"
                          "\n"
                          "export type Schema_2 = Record<string, unknown>;\n"
                          "\n"
                          "export type Schema_1 = boolean;\n"
                          "\n"
                          "export type Schema_0 = null;\n"
                          "\n"
                          "export type Schema =\n"
                          "  Schema_0 |\n"
                          "  Schema_1 |\n"
                          "  Schema_2 |\n"
                          "  Schema_3 |\n"
                          "  Schema_4 |\n"
                          "  Schema_5;\n");
}

TEST(unsupported_keyword_value_error_properties_not_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an object value");
    EXPECT_EQ(error.keyword(), "properties");
    EXPECT_AS_STRING(error.pointer(), "/anyOf/2");
  }
}

TEST(unsupported_keyword_value_error_properties_not_object_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "object", "properties": true } }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an object value");
    EXPECT_EQ(error.keyword(), "properties");
    EXPECT_AS_STRING(error.pointer(), "/properties/foo");
  }
}

TEST(unsupported_keyword_value_error_required_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array value");
    EXPECT_EQ(error.keyword(), "required");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_required_item_not_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": [ 5 ]
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array of string values");
    EXPECT_EQ(error.keyword(), "required");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_pattern_properties_not_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an object value");
    EXPECT_EQ(error.keyword(), "patternProperties");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_prefix_items_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array value");
    EXPECT_EQ(error.keyword(), "prefixItems");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_enum_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": 5
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array value");
    EXPECT_EQ(error.keyword(), "enum");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_any_of_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "anyOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_any_of_empty) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "anyOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_one_of_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": 5
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "oneOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_one_of_empty) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "oneOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_all_of_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": { "type": "string" }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "allOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_all_of_empty) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "allOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_error_draft4_empty_enum) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnsupportedKeywordError &error) {
    EXPECT_STREQ(error.what(), "Unsupported keyword in subschema");
    EXPECT_EQ(error.keyword(), "not");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(draft7_empty_enum) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": []
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);

  EXPECT_EQ(output.str(), "export type Schema = never;\n");
}

TEST(unexpected_schema_error_required_property_not_allowed) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": [ "bar" ],
    "additionalProperties": false
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnexpectedSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "This schema requires a property that it does not allow");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unexpected_schema_error_required_property_not_allowed_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "object",
        "properties": { "qux": { "type": "string" } },
        "required": [ "bar" ],
        "additionalProperties": false
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnexpectedSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "This schema requires a property that it does not allow");
    EXPECT_AS_STRING(error.pointer(), "/properties/foo");
  }
}

TEST(required_property_not_in_properties_open) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": [ "bar" ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);

  EXPECT_EQ(output.str(), "export type SchemaFoo = string;\n"
                          "\n"
                          "export type SchemaBar = unknown;\n"
                          "\n"
                          "export interface Schema {\n"
                          "  \"foo\"?: SchemaFoo;\n"
                          "  \"bar\": SchemaBar;\n"
                          "  [key: string]: unknown | undefined;\n"
                          "}\n");
}
