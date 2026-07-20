#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/blaze/foundation.h>

#include <sstream> // std::ostringstream

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
