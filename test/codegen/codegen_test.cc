#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/blaze/foundation.h>

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

TEST(unsupported_keyword_value_error_unknown_type) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "foo"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Unsupported type value");
  }
}
