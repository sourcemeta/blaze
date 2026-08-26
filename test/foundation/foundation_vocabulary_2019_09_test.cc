#include <sourcemeta/core/test.h>

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

TEST(no_vocabularies) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2019-09-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
}

TEST(no_vocabularies_hyper) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2019-09-hyper-no-vocabularies"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
}

TEST(hyper) {
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

TEST(custom_vocabularies) {
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
