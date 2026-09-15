#ifndef SOURCEMETA_BLAZE_CONVERT_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_CONVERT_TEST_UTILS_H_

#include <sourcemeta/blaze/convert.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sstream>     // std::ostringstream
#include <string_view> // std::string_view

static auto convert_test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier ==
      "https://sourcemeta.com/2020-12-custom-vocabulary-optional") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2020-12-custom-vocabulary-optional",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://sourcemeta.com/2020-12-custom-vocabulary-optional": false
      }
    })JSON");
  } else if (identifier == "https://example.com") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    })JSON");
  } else if (identifier == "https://example.com/external") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/external",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    })JSON");
  } else if (identifier == "https://example.com/external-with-defs") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/external-with-defs",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$defs": {
        "foo": { "type": "string" }
      }
    })JSON");
  } else if (identifier == "ref.schema.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "ref.schema.json",
      "$schema": "https://json-schema.org/draft/2020-12/schema"
    })JSON");
  } else if (identifier == "https://example.com/ref.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/ref.json",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "integer"
    })JSON");
  } else if (identifier ==
             "https://sourcemeta.com/2020-12-validation-without-applicator") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2020-12-validation-without-applicator",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true
      }
    })JSON");
  } else if (identifier ==
             "https://sourcemeta.com/2020-12-applicator-without-validation") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/2020-12-applicator-without-validation",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true
      }
    })JSON");
  } else if (identifier ==
             "https://example.com/unsupported-vocabulary-metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/unsupported-vocabulary-metaschema",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true,
        "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
        "https://example.com/vocab/unsupported-fictional": true
      }
    })JSON");
  } else {
    return sourcemeta::core::schema_resolver(identifier);
  }
}

#define EXPECT_JSON_EQ_WITH_ORDERING(actual, expected)                         \
  {                                                                            \
    EXPECT_EQ(actual, expected);                                               \
    std::ostringstream _actual_stream;                                         \
    std::ostringstream _expected_stream;                                       \
    sourcemeta::core::prettify(actual, _actual_stream);                        \
    sourcemeta::core::prettify(expected, _expected_stream);                    \
    EXPECT_EQ(_actual_stream.str(), _expected_stream.str());                   \
  }

#define UPGRADE_DRAFT_4(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,      \
                               convert_test_resolver,                          \
                               sourcemeta::blaze::ConvertTarget::Draft4);      \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_DRAFT_4_WITH_DIALECT(document, expected, default_dialect)      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft4, (default_dialect));          \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_DRAFT_6(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,      \
                               convert_test_resolver,                          \
                               sourcemeta::blaze::ConvertTarget::Draft6);      \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_DRAFT_6_WITH_DIALECT(document, expected, default_dialect)      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft6, (default_dialect));          \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_DRAFT_7(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,      \
                               convert_test_resolver,                          \
                               sourcemeta::blaze::ConvertTarget::Draft7);      \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_DRAFT_7_WITH_DIALECT(document, expected, default_dialect)      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft7, (default_dialect));          \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2019_09(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,      \
                               convert_test_resolver,                          \
                               sourcemeta::blaze::ConvertTarget::Draft201909); \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2019_09_WITH_DIALECT(document, expected, default_dialect)      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft201909, (default_dialect));     \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2020_12(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,      \
                               convert_test_resolver,                          \
                               sourcemeta::blaze::ConvertTarget::Draft202012); \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2020_12_WITH_DIALECT(document, expected, default_dialect)      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft202012, (default_dialect));     \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2019_09_AS_METASCHEMA(document, expected)                      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft201909, "", "", true);          \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2020_12_AS_METASCHEMA(document, expected)                      \
  {                                                                            \
    sourcemeta::blaze::convert(                                                \
        document, sourcemeta::core::schema_walker, convert_test_resolver,      \
        sourcemeta::blaze::ConvertTarget::Draft202012, "", "", true);          \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#endif
