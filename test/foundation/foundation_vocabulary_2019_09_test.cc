#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "foundation_test_utils.h"

#include <string> // std::string

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/2019-09-custom-vocabularies") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2019-09-custom-vocabularies",
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2019-09/vocab/core": true,
        "https://json-schema.org/draft/2019-09/vocab/applicator": true,
        "https://json-schema.org/draft/2019-09/vocab/validation": false
      }
    })JSON");
  } else if (identifier == "https://sourcemeta.com/2019-09-no-vocabularies") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2019-09-no-vocabularies",
      "$schema": "https://json-schema.org/draft/2019-09/schema"
    })JSON");
  } else if (identifier ==
             "https://sourcemeta.com/2019-09-hyper-no-vocabularies") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2019-09-hyper-no-vocabularies",
      "$schema": "https://json-schema.org/draft/2019-09/hyper-schema"
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(Foundation_vocabulary_2019_09, parse_vocabularies_with_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": false
    }
  })JSON");

  const auto result{
      sourcemeta::blaze::parse_vocabularies(document, test_resolver)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 3);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2019_09_Core);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2019_09_Applicator);
  EXPECT_VOCABULARY_OPTIONAL(*result, JSON_Schema_2019_09_Validation);
}

TEST(Foundation_vocabulary_2019_09, parse_vocabularies_without_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  const auto result{
      sourcemeta::blaze::parse_vocabularies(document, test_resolver)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09, parse_vocabularies_boolean_schema) {
  const sourcemeta::core::JSON document{true};
  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, test_resolver, "https://json-schema.org/draft/2019-09/schema")};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_base_dialect_with_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true
    }
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 2);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2019_09_Core);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2019_09_Applicator);
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_base_dialect_without_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "object"
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_base_dialect_hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true
    }
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document,
      sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09_Hyper)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 1);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2019_09_Core);
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_base_dialect_vocabulary_not_object_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$vocabulary": "not-an-object"
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_base_dialect_vocabulary_entry_not_boolean) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": "not-a-bool"
    }
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_resolver_vocabulary_not_object) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": "not-an-object"
  })JSON");

  const auto result{
      sourcemeta::blaze::parse_vocabularies(document, test_resolver)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09,
     parse_vocabularies_with_resolver_vocabulary_entry_not_boolean) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": "not-a-bool"
    }
  })JSON");

  const auto result{
      sourcemeta::blaze::parse_vocabularies(document, test_resolver)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2019_09, no_vocabularies) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2019-09-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
}

TEST(Foundation_vocabulary_2019_09, no_vocabularies_hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2019-09-hyper-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
}

TEST(Foundation_vocabulary_2019_09, hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 7);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Applicator);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Validation);
  EXPECT_VOCABULARY_OPTIONAL(vocabularies, JSON_Schema_2019_09_Format);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Content);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Meta_Data);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Hyper_Schema);
}

TEST(Foundation_vocabulary_2019_09, custom_vocabularies) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2019-09-custom-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 3);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Applicator);
  EXPECT_VOCABULARY_OPTIONAL(vocabularies, JSON_Schema_2019_09_Validation);
}
