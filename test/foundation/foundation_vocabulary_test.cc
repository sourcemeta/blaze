#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "foundation_test_utils.h"

#include <sstream>       // std::ostringstream
#include <unordered_set> // std::unordered_set
#include <variant>       // std::variant

TEST(Foundation_vocabulary, core_vocabularies_boolean_without_default) {
  const sourcemeta::core::JSON document{true};
  EXPECT_THROW(sourcemeta::blaze::vocabularies(
                   document, sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_vocabulary, unresolvable_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://non-existent.com/dialect"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::vocabularies(
                   document, sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_vocabulary, override_returns_override_vocabularies) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 7);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Applicator);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Unevaluated);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Validation);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Meta_Data);
  EXPECT_VOCABULARY_REQUIRED(vocabularies,
                             JSON_Schema_2020_12_Format_Annotation);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Content);
}

TEST(Foundation_vocabulary, override_only_returns_override_vocabularies) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-07/schema#"
  })JSON");
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_7);
}

TEST(Foundation_vocabulary, override_unresolvable) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://non-existent.com/dialect"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::vocabularies(
                   document, sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_vocabulary, known_vocabulary_to_string) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

#define EXPECT_VOCABULARY_URI(vocabulary, expected_uri)                        \
  {                                                                            \
    std::ostringstream stream;                                                 \
    stream << vocabulary;                                                      \
    EXPECT_EQ(stream.str(), expected_uri);                                     \
  }

  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_0,
                        "http://json-schema.org/draft-00/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_0_Hyper,
                        "http://json-schema.org/draft-00/hyper-schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_1,
                        "http://json-schema.org/draft-01/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_1_Hyper,
                        "http://json-schema.org/draft-01/hyper-schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_2,
                        "http://json-schema.org/draft-02/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_2_Hyper,
                        "http://json-schema.org/draft-02/hyper-schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_3,
                        "http://json-schema.org/draft-03/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_3_Hyper,
                        "http://json-schema.org/draft-03/hyper-schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_4,
                        "http://json-schema.org/draft-04/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_4_Hyper,
                        "http://json-schema.org/draft-04/hyper-schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_6,
                        "http://json-schema.org/draft-06/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_6_Hyper,
                        "http://json-schema.org/draft-06/hyper-schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_7,
                        "http://json-schema.org/draft-07/schema#");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_Draft_7_Hyper,
                        "http://json-schema.org/draft-07/hyper-schema#");

  EXPECT_VOCABULARY_URI(Known::JSON_Schema_2019_09_Core,
                        "https://json-schema.org/draft/2019-09/vocab/core");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2019_09_Applicator,
      "https://json-schema.org/draft/2019-09/vocab/applicator");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2019_09_Validation,
      "https://json-schema.org/draft/2019-09/vocab/validation");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2019_09_Meta_Data,
      "https://json-schema.org/draft/2019-09/vocab/meta-data");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_2019_09_Format,
                        "https://json-schema.org/draft/2019-09/vocab/format");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_2019_09_Content,
                        "https://json-schema.org/draft/2019-09/vocab/content");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2019_09_Hyper_Schema,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema");

  EXPECT_VOCABULARY_URI(Known::JSON_Schema_2020_12_Core,
                        "https://json-schema.org/draft/2020-12/vocab/core");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2020_12_Applicator,
      "https://json-schema.org/draft/2020-12/vocab/applicator");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2020_12_Unevaluated,
      "https://json-schema.org/draft/2020-12/vocab/unevaluated");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2020_12_Validation,
      "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2020_12_Meta_Data,
      "https://json-schema.org/draft/2020-12/vocab/meta-data");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2020_12_Format_Annotation,
      "https://json-schema.org/draft/2020-12/vocab/format-annotation");
  EXPECT_VOCABULARY_URI(
      Known::JSON_Schema_2020_12_Format_Assertion,
      "https://json-schema.org/draft/2020-12/vocab/format-assertion");
  EXPECT_VOCABULARY_URI(Known::JSON_Schema_2020_12_Content,
                        "https://json-schema.org/draft/2020-12/vocab/content");

  EXPECT_VOCABULARY_URI(Known::OpenAPI_3_1_Base,
                        "https://spec.openapis.org/oas/3.1/vocab/base");
  EXPECT_VOCABULARY_URI(Known::OpenAPI_3_2_Base,
                        "https://spec.openapis.org/oas/3.2/vocab/base");

#undef EXPECT_VOCABULARY_URI
}

TEST(Foundation_vocabulary, throw_if_any_unsupported_all_supported_by_enum) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core, Known::JSON_Schema_2020_12_Applicator};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary,
     throw_if_any_unsupported_all_supported_custom_by_string) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab-1", true);
  vocabularies.insert("https://example.com/custom-vocab-2", true);

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core,
      sourcemeta::core::JSON::String{"https://example.com/custom-vocab-1"},
      sourcemeta::core::JSON::String{"https://example.com/custom-vocab-2"}};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary,
     throw_if_any_unsupported_mixed_known_enum_and_custom_string) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core, Known::JSON_Schema_2020_12_Applicator,
      sourcemeta::core::JSON::String{"https://example.com/custom-vocab"}};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary, throw_if_any_unsupported_missing_required_known) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true},
      {Known::JSON_Schema_2020_12_Validation, true}};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core, Known::JSON_Schema_2020_12_Applicator};

  try {
    vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(),
              "https://json-schema.org/draft/2020-12/vocab/validation");
    EXPECT_STREQ(error.what(), "Unsupported vocabulary");
  }
}

TEST(Foundation_vocabulary, throw_if_any_unsupported_missing_required_custom) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core};

  try {
    vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/custom-vocab");
    EXPECT_STREQ(error.what(), "Unsupported vocabulary");
  }
}

TEST(Foundation_vocabulary, throw_if_any_unsupported_optional_not_checked) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary, throw_if_any_unsupported_empty_vocabularies) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary,
     throw_if_any_unsupported_known_vocab_as_string_in_vocabularies) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{};
  vocabularies.insert("https://json-schema.org/draft/2020-12/vocab/core", true);

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary,
     throw_if_any_unsupported_custom_supported_by_string) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core,
      sourcemeta::core::JSON::String{"https://example.com/custom-vocab"}};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary, contains_any_empty_vocabularies) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{};

  EXPECT_FALSE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_FALSE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Core,
                                 Known::JSON_Schema_2020_12_Applicator}));
}

TEST(Foundation_vocabulary, contains_any_single_match) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};

  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_TRUE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Core,
                                 Known::JSON_Schema_2020_12_Applicator}));
  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator,
                                         Known::JSON_Schema_2020_12_Core}));
}

TEST(Foundation_vocabulary, contains_any_no_match) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};

  EXPECT_FALSE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator}));
  EXPECT_FALSE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator,
                                          Known::JSON_Schema_2020_12_Validation,
                                          Known::JSON_Schema_2020_12_Content}));
}

TEST(Foundation_vocabulary, contains_any_multiple_vocabularies) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_TRUE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator}));
  EXPECT_TRUE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Validation}));
  EXPECT_TRUE(vocabularies.contains_any(
      {Known::JSON_Schema_2020_12_Content, Known::JSON_Schema_2020_12_Core}));
  EXPECT_FALSE(vocabularies.contains_any(
      {Known::JSON_Schema_2020_12_Content, Known::JSON_Schema_Draft_7}));
}

TEST(Foundation_vocabulary, contains_any_empty_list) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};

  EXPECT_FALSE(vocabularies.contains_any({}));
}

TEST(Foundation_vocabulary, contains_any_matches_both_required_and_optional) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_TRUE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Validation}));
}

TEST(Foundation_vocabulary, uri_to_string_known_variant) {
  using Known = sourcemeta::blaze::Vocabularies::Known;
  using URI = sourcemeta::blaze::Vocabularies::URI;

  const URI vocabulary{Known::JSON_Schema_2020_12_Core};
  std::ostringstream stream;
  stream << vocabulary;
  EXPECT_EQ(stream.str(), "https://json-schema.org/draft/2020-12/vocab/core");
}

TEST(Foundation_vocabulary, uri_to_string_custom_variant) {
  using URI = sourcemeta::blaze::Vocabularies::URI;

  const URI vocabulary{
      sourcemeta::core::JSON::String{"https://example.com/custom-vocab"}};
  std::ostringstream stream;
  stream << vocabulary;
  EXPECT_EQ(stream.str(), "https://example.com/custom-vocab");
}

TEST(Foundation_vocabulary, to_string_known) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  EXPECT_EQ(sourcemeta::blaze::to_string(Known::JSON_Schema_2020_12_Core),
            "https://json-schema.org/draft/2020-12/vocab/core");
  EXPECT_EQ(sourcemeta::blaze::to_string(Known::JSON_Schema_2019_09_Applicator),
            "https://json-schema.org/draft/2019-09/vocab/applicator");
  EXPECT_EQ(sourcemeta::blaze::to_string(Known::JSON_Schema_Draft_7),
            "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(sourcemeta::blaze::to_string(Known::OpenAPI_3_1_Base),
            "https://spec.openapis.org/oas/3.1/vocab/base");
  EXPECT_EQ(sourcemeta::blaze::to_string(Known::OpenAPI_3_2_Base),
            "https://spec.openapis.org/oas/3.2/vocab/base");
}

TEST(Foundation_vocabulary, to_string_uri_known_variant) {
  using Known = sourcemeta::blaze::Vocabularies::Known;
  using URI = sourcemeta::blaze::Vocabularies::URI;

  const URI vocabulary{Known::JSON_Schema_2020_12_Validation};
  EXPECT_EQ(sourcemeta::blaze::to_string(vocabulary),
            "https://json-schema.org/draft/2020-12/vocab/validation");
}

TEST(Foundation_vocabulary, to_string_uri_custom_variant) {
  using URI = sourcemeta::blaze::Vocabularies::URI;

  const URI vocabulary{
      sourcemeta::core::JSON::String{"https://example.com/my-vocab"}};
  EXPECT_EQ(sourcemeta::blaze::to_string(vocabulary),
            "https://example.com/my-vocab");
}

TEST(Foundation_vocabulary, has_unknown_empty_vocabularies) {
  const sourcemeta::blaze::Vocabularies vocabularies{};
  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, has_unknown_only_known_required) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true}};

  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, has_unknown_only_known_optional) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, has_unknown_with_custom_required) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  EXPECT_TRUE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, has_unknown_with_custom_optional) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", false);

  EXPECT_TRUE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, has_unknown_with_multiple_custom) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab-1", true);
  vocabularies.insert("https://example.com/custom-vocab-2", false);

  EXPECT_TRUE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, throw_if_any_unknown_required_empty) {
  const sourcemeta::blaze::Vocabularies vocabularies{};
  EXPECT_NO_THROW(
      vocabularies.throw_if_any_unknown_required("Unknown vocabulary"));
}

TEST(Foundation_vocabulary, throw_if_any_unknown_required_only_known) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true}};

  EXPECT_NO_THROW(
      vocabularies.throw_if_any_unknown_required("Unknown vocabulary"));
}

TEST(Foundation_vocabulary, throw_if_any_unknown_required_only_optional) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", false);

  EXPECT_NO_THROW(
      vocabularies.throw_if_any_unknown_required("Unknown vocabulary"));
}

TEST(Foundation_vocabulary, throw_if_any_unknown_required_with_required) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  try {
    vocabularies.throw_if_any_unknown_required("Unknown vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/custom-vocab");
    EXPECT_STREQ(error.what(), "Unknown vocabulary");
  }
}

TEST(Foundation_vocabulary,
     throw_if_any_unknown_required_mixed_required_optional) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/optional-vocab", false);
  vocabularies.insert("https://example.com/required-vocab", true);

  try {
    vocabularies.throw_if_any_unknown_required("Unknown vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/required-vocab");
    EXPECT_STREQ(error.what(), "Unknown vocabulary");
  }
}

TEST(Foundation_vocabulary, contains_any_openapi_3_1_base) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_1_Base, true}};

  EXPECT_TRUE(vocabularies.contains_any({Known::OpenAPI_3_1_Base}));
  EXPECT_TRUE(vocabularies.contains_any(
      {Known::OpenAPI_3_1_Base, Known::OpenAPI_3_2_Base}));
  EXPECT_FALSE(vocabularies.contains_any({Known::OpenAPI_3_2_Base}));
}

TEST(Foundation_vocabulary, contains_any_openapi_3_2_base) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_2_Base, true}};

  EXPECT_TRUE(vocabularies.contains_any({Known::OpenAPI_3_2_Base}));
  EXPECT_TRUE(vocabularies.contains_any(
      {Known::OpenAPI_3_1_Base, Known::OpenAPI_3_2_Base}));
  EXPECT_FALSE(vocabularies.contains_any({Known::OpenAPI_3_1_Base}));
}

TEST(Foundation_vocabulary, insert_openapi_3_1_base_by_string) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://spec.openapis.org/oas/3.1/vocab/base", true);

  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_TRUE(vocabularies.contains(Known::OpenAPI_3_1_Base));
  EXPECT_TRUE(vocabularies.get(Known::OpenAPI_3_1_Base).value());
  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, insert_openapi_3_2_base_by_string) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://spec.openapis.org/oas/3.2/vocab/base", false);

  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_TRUE(vocabularies.contains(Known::OpenAPI_3_2_Base));
  EXPECT_FALSE(vocabularies.get(Known::OpenAPI_3_2_Base).value());
  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary,
     throw_if_any_unsupported_openapi_required_not_in_supported) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_1_Base, true}};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core};

  try {
    vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://spec.openapis.org/oas/3.1/vocab/base");
    EXPECT_STREQ(error.what(), "Unsupported vocabulary");
  }
}

TEST(Foundation_vocabulary,
     throw_if_any_unsupported_openapi_optional_not_checked) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::OpenAPI_3_1_Base, false}};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary, throw_if_any_unsupported_openapi_in_supported) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_1_Base, true}};

  const std::unordered_set<sourcemeta::blaze::Vocabularies::URI> supported{
      Known::JSON_Schema_2020_12_Core, Known::OpenAPI_3_1_Base};

  EXPECT_NO_THROW(vocabularies.throw_if_any_unsupported(
      supported, "Unsupported vocabulary"));
}

TEST(Foundation_vocabulary, has_unknown_with_openapi_vocabularies) {
  using Known = sourcemeta::blaze::Vocabularies::Known;

  const sourcemeta::blaze::Vocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::OpenAPI_3_1_Base, true},
      {Known::OpenAPI_3_2_Base, false}};

  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(Foundation_vocabulary, embedded_custom_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Validation);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_2019_09) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true,
          "https://json-schema.org/draft/2019-09/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2019_09_Validation);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_7);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_draft4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_4);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_chain) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Validation);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_without_vocabulary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_definitions_2020_12) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  // In 2019-09 and 2020-12, `definitions` is still supported
  // for backwards compatibility
  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_wrong_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  try {
    sourcemeta::blaze::vocabularies(document,
                                    sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_precedence) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  // A resolver that knows about the custom meta-schema, but with a
  // different vocabulary set than the embedded copy
  const auto resolver =
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/meta") {
      return sourcemeta::core::parse_json(R"JSON({
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        }
      })JSON");
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document, resolver)};
  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_2020_12_Validation);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_draft6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_6);
}

TEST(Foundation_vocabulary, embedded_custom_metaschema_draft3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::blaze::Vocabularies vocabularies{
      sourcemeta::blaze::vocabularies(document,
                                      sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(vocabularies.size(), 1);
  EXPECT_VOCABULARY_REQUIRED(vocabularies, JSON_Schema_Draft_3);
}
