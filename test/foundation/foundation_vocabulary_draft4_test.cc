#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "foundation_test_utils.h"

#include <string> // std::string

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/one-hop") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/one-hop",
      "$schema": "http://json-schema.org/draft-04/schema#"
    })JSON");
  } else if (identifier == "https://sourcemeta.com/with-vocabulary") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/with-vocabulary",
      "$schema": "http://json-schema.org/draft-04/schema#",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": false
      }
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

static auto VOCABULARIES(const sourcemeta::core::JSON &document,
                         const sourcemeta::blaze::SchemaResolver &resolver,
                         const std::string_view default_dialect = "")
    -> sourcemeta::blaze::SchemaVocabularies {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};
  frame.analyse(document, sourcemeta::blaze::schema_walker, resolver,
                default_dialect);
  return frame.vocabularies(frame.root_location().value().get(), resolver);
}

TEST(schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object"
  })JSON");
  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      VOCABULARIES(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_4);
}

TEST(hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/hyper-schema#",
    "type": "object"
  })JSON");
  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      VOCABULARIES(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_4_Hyper);
}

TEST(one_hop) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/one-hop",
    "type": "object"
  })JSON");
  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      VOCABULARIES(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_4);
}

TEST(ignore_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/with-vocabulary",
    "type": "object"
  })JSON");
  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      VOCABULARIES(document, test_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_4);
}
