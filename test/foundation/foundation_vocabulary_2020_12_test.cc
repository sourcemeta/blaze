#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "foundation_test_utils.h"

#include <string> // std::string

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/2020-12-custom-vocabularies") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2020-12-custom-vocabularies",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": false
      }
    })JSON");
  } else if (identifier == "https://sourcemeta.com/optional-core") {
    // Optional core
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/optional-core",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": false
      }
    })JSON");
  } else if (identifier == "https://sourcemeta.com/no-core") {
    // Missing core
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/no-core",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/validation": true
      }
    })JSON");
  } else if (identifier == "https://sourcemeta.com/2020-12-no-vocabularies") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2020-12-no-vocabularies",
      "$schema": "https://json-schema.org/draft/2020-12/schema"
    })JSON");
  } else if (identifier ==
             "https://sourcemeta.com/2020-12-hyper-no-vocabularies") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2020-12-hyper-no-vocabularies",
      "$schema": "https://json-schema.org/draft/2020-12/hyper-schema"
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(Foundation_vocabulary_2020_12, parse_vocabularies_with_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true,
      "https://json-schema.org/draft/2020-12/vocab/validation": false
    }
  })JSON");

  const auto result{
      sourcemeta::blaze::parse_vocabularies(document, test_resolver)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 3);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2020_12_Applicator);
  EXPECT_VOCABULARY_OPTIONAL(*result, JSON_Schema_2020_12_Validation);
}

TEST(Foundation_vocabulary_2020_12, parse_vocabularies_without_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  const auto result{
      sourcemeta::blaze::parse_vocabularies(document, test_resolver)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2020_12, parse_vocabularies_boolean_schema) {
  const sourcemeta::core::JSON document{true};
  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, test_resolver, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2020_12,
     parse_vocabularies_with_base_dialect_with_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    }
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 2);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2020_12_Applicator);
}

TEST(Foundation_vocabulary_2020_12,
     parse_vocabularies_with_base_dialect_without_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "object"
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12)};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_vocabulary_2020_12,
     parse_vocabularies_with_base_dialect_hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true
    }
  })JSON");

  const auto result{sourcemeta::blaze::parse_vocabularies(
      document,
      sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12_Hyper)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 1);
  EXPECT_VOCABULARY_REQUIRED(*result, JSON_Schema_2020_12_Core);
}

TEST(Foundation_vocabulary_2020_12, core_vocabularies_boolean_with_default) {
  const sourcemeta::core::JSON document{true};
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(
          document, test_resolver,
          "https://sourcemeta.com/2020-12-custom-vocabularies")};
  EXPECT_EQ(vocabularies.size(), 3);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Applicator);
  EXPECT_VOCABULARY_OPTIONAL(vocabularies, JSON_Schema_2020_12_Validation);
}

TEST(Foundation_vocabulary_2020_12,
     real_metaschema_takes_precedence_over_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2020-12-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(
          document, test_resolver,
          "https://sourcemeta.com/2020-12-custom-vocabularies")};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
}

TEST(Foundation_vocabulary_2020_12, core_cannot_be_optional) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/optional-core"
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::vocabularies(document, test_resolver),
               sourcemeta::blaze::SchemaError);
}

TEST(Foundation_vocabulary_2020_12, core_must_be_declared) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/no-core"
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::vocabularies(document, test_resolver),
               sourcemeta::blaze::SchemaError);
}

TEST(Foundation_vocabulary_2020_12, no_vocabularies) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2020-12-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
}

TEST(Foundation_vocabulary_2020_12, no_vocabularies_hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2020-12-hyper-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
}

TEST(Foundation_vocabulary_2020_12, hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/hyper-schema"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 8);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Applicator);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Unevaluated);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Validation);
  EXPECT_VOCABULARY_REQUIRED(vocabularies,
                             JSON_Schema_2020_12_Format_Annotation);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Content);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Meta_Data);
  // Notice this is 2019-09. That's actually correct.
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Hyper_Schema);
}
