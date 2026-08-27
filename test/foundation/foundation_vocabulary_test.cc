#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <format> // std::format

#include <sstream>       // std::ostringstream
#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::pair
#include <variant>       // std::variant
#include <vector>        // std::vector

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/optional-core") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/optional-core",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": false
      }
    })JSON");
  } else if (identifier == "https://sourcemeta.com/no-core") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/no-core",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/validation": true
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

TEST(core_vocabularies_boolean_without_default) {
  const sourcemeta::core::JSON document{true};
  try {
    VOCABULARIES(document, sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(unresolvable_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://non-existent.com/dialect"
  })JSON");
  try {
    VOCABULARIES(document, sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(override_unresolvable) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://non-existent.com/dialect"
  })JSON");
  try {
    VOCABULARIES(document, sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(known_vocabulary_to_string) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

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

TEST(throw_if_any_unsupported_all_supported_by_enum) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core,
                Known::JSON_Schema_2020_12_Applicator};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_all_supported_custom_by_string) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab-1", true);
  vocabularies.insert("https://example.com/custom-vocab-2", true);

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{
          Known::JSON_Schema_2020_12_Core,
          sourcemeta::core::JSON::String{"https://example.com/custom-vocab-1"},
          sourcemeta::core::JSON::String{"https://example.com/custom-vocab-2"}};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_mixed_known_enum_and_custom_string) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{
          Known::JSON_Schema_2020_12_Core,
          Known::JSON_Schema_2020_12_Applicator,
          sourcemeta::core::JSON::String{"https://example.com/custom-vocab"}};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_missing_required_known) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true},
      {Known::JSON_Schema_2020_12_Validation, true}};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core,
                Known::JSON_Schema_2020_12_Applicator};

  try {
    vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(),
              "https://json-schema.org/draft/2020-12/vocab/validation");
    EXPECT_STREQ(error.what(), "Unsupported vocabulary");
  }
}

TEST(throw_if_any_unsupported_missing_required_custom) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core};

  try {
    vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://example.com/custom-vocab");
    EXPECT_STREQ(error.what(), "Unsupported vocabulary");
  }
}

TEST(throw_if_any_unsupported_optional_not_checked) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_empty_vocabularies) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_known_vocab_as_string_in_vocabularies) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{};
  vocabularies.insert("https://json-schema.org/draft/2020-12/vocab/core", true);

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_custom_supported_by_string) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{
          Known::JSON_Schema_2020_12_Core,
          sourcemeta::core::JSON::String{"https://example.com/custom-vocab"}};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(contains_any_empty_vocabularies) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{};

  EXPECT_FALSE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_FALSE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Core,
                                 Known::JSON_Schema_2020_12_Applicator}));
}

TEST(contains_any_single_match) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};

  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_TRUE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Core,
                                 Known::JSON_Schema_2020_12_Applicator}));
  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator,
                                         Known::JSON_Schema_2020_12_Core}));
}

TEST(contains_any_no_match) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};

  EXPECT_FALSE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator}));
  EXPECT_FALSE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Applicator,
                                          Known::JSON_Schema_2020_12_Validation,
                                          Known::JSON_Schema_2020_12_Content}));
}

TEST(contains_any_multiple_vocabularies) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
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

TEST(contains_any_empty_list) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};

  EXPECT_FALSE(vocabularies.contains_any({}));
}

TEST(contains_any_matches_both_required_and_optional) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  EXPECT_TRUE(vocabularies.contains_any({Known::JSON_Schema_2020_12_Core}));
  EXPECT_TRUE(
      vocabularies.contains_any({Known::JSON_Schema_2020_12_Validation}));
}

TEST(uri_to_string_known_variant) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;
  using URI = sourcemeta::blaze::SchemaVocabularies::URI;

  const URI vocabulary{Known::JSON_Schema_2020_12_Core};
  std::ostringstream stream;
  stream << vocabulary;
  EXPECT_EQ(stream.str(), "https://json-schema.org/draft/2020-12/vocab/core");
}

TEST(uri_to_string_custom_variant) {
  using URI = sourcemeta::blaze::SchemaVocabularies::URI;

  const URI vocabulary{
      sourcemeta::core::JSON::String{"https://example.com/custom-vocab"}};
  std::ostringstream stream;
  stream << vocabulary;
  EXPECT_EQ(stream.str(), "https://example.com/custom-vocab");
}

TEST(format_known) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  EXPECT_EQ(std::format("{}", Known::JSON_Schema_2020_12_Core),
            "https://json-schema.org/draft/2020-12/vocab/core");
  EXPECT_EQ(std::format("{}", Known::JSON_Schema_2019_09_Applicator),
            "https://json-schema.org/draft/2019-09/vocab/applicator");
  EXPECT_EQ(std::format("{}", Known::JSON_Schema_Draft_7),
            "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(std::format("{}", Known::OpenAPI_3_1_Base),
            "https://spec.openapis.org/oas/3.1/vocab/base");
  EXPECT_EQ(std::format("{}", Known::OpenAPI_3_2_Base),
            "https://spec.openapis.org/oas/3.2/vocab/base");
}

TEST(format_uri_known_variant) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;
  using URI = sourcemeta::blaze::SchemaVocabularies::URI;

  const URI vocabulary{Known::JSON_Schema_2020_12_Validation};
  EXPECT_EQ(std::format("{}", vocabulary),
            "https://json-schema.org/draft/2020-12/vocab/validation");
}

TEST(format_uri_custom_variant) {
  using URI = sourcemeta::blaze::SchemaVocabularies::URI;

  const URI vocabulary{
      sourcemeta::core::JSON::String{"https://example.com/my-vocab"}};
  EXPECT_EQ(std::format("{}", vocabulary), "https://example.com/my-vocab");
}

TEST(has_unknown_empty_vocabularies) {
  const sourcemeta::blaze::SchemaVocabularies vocabularies{};
  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(has_unknown_only_known_required) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Applicator, true}};

  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(has_unknown_only_known_optional) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::JSON_Schema_2020_12_Validation, false}};

  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(has_unknown_with_custom_required) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", true);

  EXPECT_TRUE(vocabularies.has_unknown());
}

TEST(has_unknown_with_custom_optional) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab", false);

  EXPECT_TRUE(vocabularies.has_unknown());
}

TEST(has_unknown_with_multiple_custom) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://example.com/custom-vocab-1", true);
  vocabularies.insert("https://example.com/custom-vocab-2", false);

  EXPECT_TRUE(vocabularies.has_unknown());
}

TEST(contains_any_openapi_3_1_base) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_1_Base, true}};

  EXPECT_TRUE(vocabularies.contains_any({Known::OpenAPI_3_1_Base}));
  EXPECT_TRUE(vocabularies.contains_any(
      {Known::OpenAPI_3_1_Base, Known::OpenAPI_3_2_Base}));
  EXPECT_FALSE(vocabularies.contains_any({Known::OpenAPI_3_2_Base}));
}

TEST(contains_any_openapi_3_2_base) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_2_Base, true}};

  EXPECT_TRUE(vocabularies.contains_any({Known::OpenAPI_3_2_Base}));
  EXPECT_TRUE(vocabularies.contains_any(
      {Known::OpenAPI_3_1_Base, Known::OpenAPI_3_2_Base}));
  EXPECT_FALSE(vocabularies.contains_any({Known::OpenAPI_3_1_Base}));
}

TEST(insert_openapi_3_1_base_by_string) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://spec.openapis.org/oas/3.1/vocab/base", true);

  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_TRUE(vocabularies.contains(Known::OpenAPI_3_1_Base));
  EXPECT_TRUE(vocabularies.get(Known::OpenAPI_3_1_Base).value());
  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(insert_openapi_3_2_base_by_string) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}};
  vocabularies.insert("https://spec.openapis.org/oas/3.2/vocab/base", false);

  EXPECT_EQ(vocabularies.size(), 2);
  EXPECT_TRUE(vocabularies.contains(Known::OpenAPI_3_2_Base));
  EXPECT_FALSE(vocabularies.get(Known::OpenAPI_3_2_Base).value());
  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(throw_if_any_unsupported_openapi_required_not_in_supported) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_1_Base, true}};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core};

  try {
    vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaVocabularyError &error) {
    EXPECT_EQ(error.uri(), "https://spec.openapis.org/oas/3.1/vocab/base");
    EXPECT_STREQ(error.what(), "Unsupported vocabulary");
  }
}

TEST(throw_if_any_unsupported_openapi_optional_not_checked) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::OpenAPI_3_1_Base, false}};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(throw_if_any_unsupported_openapi_in_supported) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true}, {Known::OpenAPI_3_1_Base, true}};

  const std::unordered_set<sourcemeta::blaze::SchemaVocabularies::URI>
      supported{Known::JSON_Schema_2020_12_Core, Known::OpenAPI_3_1_Base};

  vocabularies.throw_if_any_unsupported(supported, "Unsupported vocabulary");
}

TEST(has_unknown_with_openapi_vocabularies) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;

  const sourcemeta::blaze::SchemaVocabularies vocabularies{
      {Known::JSON_Schema_2020_12_Core, true},
      {Known::OpenAPI_3_1_Base, true},
      {Known::OpenAPI_3_2_Base, false}};

  EXPECT_FALSE(vocabularies.has_unknown());
}

TEST(embedded_custom_metaschema_wrong_container) {
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
    VOCABULARIES(document, sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(for_each_empty) {
  const sourcemeta::blaze::SchemaVocabularies vocabularies;
  std::vector<std::pair<std::string, bool>> seen;
  vocabularies.for_each(
      [&seen](const sourcemeta::blaze::SchemaVocabularies::URI &uri,
              const bool required) {
        seen.emplace_back(std::format("{}", uri), required);
      });

  EXPECT_TRUE(seen.empty());
}

TEST(for_each_known_required_and_optional) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;
  sourcemeta::blaze::SchemaVocabularies vocabularies;
  vocabularies.insert(Known::JSON_Schema_2020_12_Core, true);
  vocabularies.insert(Known::JSON_Schema_2020_12_Validation, false);

  std::vector<std::pair<std::string, bool>> seen;
  vocabularies.for_each(
      [&seen](const sourcemeta::blaze::SchemaVocabularies::URI &uri,
              const bool required) {
        seen.emplace_back(std::format("{}", uri), required);
      });

  EXPECT_EQ(seen.size(), 2);
  EXPECT_EQ(seen.at(0).first,
            "https://json-schema.org/draft/2020-12/vocab/core");
  EXPECT_TRUE(seen.at(0).second);
  EXPECT_EQ(seen.at(1).first,
            "https://json-schema.org/draft/2020-12/vocab/validation");
  EXPECT_FALSE(seen.at(1).second);
}

TEST(for_each_unknown) {
  sourcemeta::blaze::SchemaVocabularies vocabularies;
  vocabularies.insert(sourcemeta::core::JSON::String{"https://example.com/one"},
                      true);

  std::vector<std::pair<std::string, bool>> seen;
  vocabularies.for_each(
      [&seen](const sourcemeta::blaze::SchemaVocabularies::URI &uri,
              const bool required) {
        seen.emplace_back(std::format("{}", uri), required);
      });

  EXPECT_EQ(seen.size(), 1);
  EXPECT_EQ(seen.at(0).first, "https://example.com/one");
  EXPECT_TRUE(seen.at(0).second);
}

TEST(for_each_known_and_unknown) {
  using Known = sourcemeta::blaze::SchemaVocabularies::Known;
  sourcemeta::blaze::SchemaVocabularies vocabularies;
  vocabularies.insert(Known::JSON_Schema_2020_12_Core, true);
  vocabularies.insert(sourcemeta::core::JSON::String{"https://example.com/one"},
                      false);

  std::vector<std::pair<std::string, bool>> seen;
  vocabularies.for_each(
      [&seen](const sourcemeta::blaze::SchemaVocabularies::URI &uri,
              const bool required) {
        seen.emplace_back(std::format("{}", uri), required);
      });

  EXPECT_EQ(seen.size(), vocabularies.size());
  EXPECT_EQ(seen.size(), 2);
  // Known vocabularies always come before unknown ones
  EXPECT_EQ(seen.at(0).first,
            "https://json-schema.org/draft/2020-12/vocab/core");
  EXPECT_TRUE(seen.at(0).second);
  EXPECT_EQ(seen.at(1).first, "https://example.com/one");
  EXPECT_FALSE(seen.at(1).second);
}

TEST(vocabularies_known_2020_12_core) {
  const auto vocabulary{
      sourcemeta::blaze::SchemaVocabularies::Known::JSON_Schema_2020_12_Core};
  const auto result{sourcemeta::core::to_json(vocabulary)};
  EXPECT_TRUE(result.is_integer());
  EXPECT_EQ(result.to_integer(), 21);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::Known>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(vocabulary, back.value());
}

TEST(vocabularies_known_2020_12_applicator) {
  const auto vocabulary{sourcemeta::blaze::SchemaVocabularies::Known::
                            JSON_Schema_2020_12_Applicator};
  const auto result{sourcemeta::core::to_json(vocabulary)};
  EXPECT_TRUE(result.is_integer());
  EXPECT_EQ(result.to_integer(), 22);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::Known>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(vocabulary, back.value());
}

TEST(vocabularies_known_draft_0) {
  const auto vocabulary{
      sourcemeta::blaze::SchemaVocabularies::Known::JSON_Schema_Draft_0};
  const auto result{sourcemeta::core::to_json(vocabulary)};
  EXPECT_TRUE(result.is_integer());
  EXPECT_EQ(result.to_integer(), 0);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::Known>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(vocabulary, back.value());
}

TEST(vocabularies_known_from_json_invalid_type) {
  const sourcemeta::core::JSON input{"not-an-integer"};
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::Known>(
          input)};
  EXPECT_FALSE(result.has_value());
}

TEST(vocabularies_uri_with_known) {
  const sourcemeta::blaze::SchemaVocabularies::URI uri{
      sourcemeta::blaze::SchemaVocabularies::Known::JSON_Schema_2020_12_Core};
  const auto result{sourcemeta::core::to_json(uri)};
  EXPECT_TRUE(result.is_array());
  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(result.at(0).is_integer());
  EXPECT_EQ(result.at(0).to_integer(), 0);
  EXPECT_TRUE(result.at(1).is_integer());
  EXPECT_EQ(result.at(1).to_integer(), 21);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::URI>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(uri, back.value());
}

TEST(vocabularies_uri_with_custom_string) {
  const sourcemeta::blaze::SchemaVocabularies::URI uri{
      sourcemeta::core::JSON::String{"https://example.com/my-custom-vocab"}};
  const auto result{sourcemeta::core::to_json(uri)};
  EXPECT_TRUE(result.is_array());
  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(result.at(0).is_integer());
  EXPECT_EQ(result.at(0).to_integer(), 1);
  EXPECT_TRUE(result.at(1).is_string());
  EXPECT_EQ(result.at(1).to_string(), "https://example.com/my-custom-vocab");
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::URI>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(uri, back.value());
}

TEST(vocabularies_uri_from_json_invalid_type) {
  const sourcemeta::core::JSON input{"not-an-array"};
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::URI>(
          input)};
  EXPECT_FALSE(result.has_value());
}

TEST(vocabularies_uri_from_json_invalid_size) {
  auto input{sourcemeta::core::JSON::make_array()};
  input.push_back(sourcemeta::core::JSON{0});
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::URI>(
          input)};
  EXPECT_FALSE(result.has_value());
}

TEST(vocabularies_uri_from_json_invalid_index) {
  auto input{sourcemeta::core::JSON::make_array()};
  input.push_back(sourcemeta::core::JSON{99});
  input.push_back(sourcemeta::core::JSON{0});
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::SchemaVocabularies::URI>(
          input)};
  EXPECT_FALSE(result.has_value());
}

TEST(core_cannot_be_optional) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/optional-core"
  })JSON");

  try {
    VOCABULARIES(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaError &error) {
    EXPECT_STREQ(error.what(), "The core vocabulary must always be required");
  }
}

TEST(core_must_be_declared) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/no-core"
  })JSON");

  try {
    VOCABULARIES(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaError &error) {
    EXPECT_STREQ(error.what(), "The core vocabulary must always be present");
  }
}
