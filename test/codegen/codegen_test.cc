#include <gtest/gtest.h>

#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/core/jsonschema.h>

TEST(Codegen, unsupported_dialect_draft3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON")};

  EXPECT_THROW(sourcemeta::blaze::compile(schema,
                                          sourcemeta::core::schema_walker,
                                          sourcemeta::core::schema_resolver,
                                          sourcemeta::blaze::default_compiler),
               sourcemeta::core::SchemaVocabularyError);
}

TEST(Codegen, unsupported_keyword_error_not) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" }
  })JSON")};

  EXPECT_THROW(sourcemeta::blaze::compile(schema,
                                          sourcemeta::core::schema_walker,
                                          sourcemeta::core::schema_resolver,
                                          sourcemeta::blaze::default_compiler),
               sourcemeta::blaze::CodegenUnsupportedKeywordError);
}

TEST(Codegen, unsupported_keyword_value_error_type_not_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": 123
  })JSON")};

  EXPECT_THROW(sourcemeta::blaze::compile(schema,
                                          sourcemeta::core::schema_walker,
                                          sourcemeta::core::schema_resolver,
                                          sourcemeta::blaze::default_compiler),
               sourcemeta::blaze::CodegenUnsupportedKeywordValueError);
}

TEST(Codegen, unsupported_keyword_value_error_unknown_type) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "foo"
  })JSON")};

  EXPECT_THROW(sourcemeta::blaze::compile(schema,
                                          sourcemeta::core::schema_walker,
                                          sourcemeta::core::schema_resolver,
                                          sourcemeta::blaze::default_compiler),
               sourcemeta::blaze::CodegenUnsupportedKeywordValueError);
}
