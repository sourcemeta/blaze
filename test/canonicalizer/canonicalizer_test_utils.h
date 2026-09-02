#ifndef SOURCEMETA_BLAZE_CANONICALIZER_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_CANONICALIZER_TEST_UTILS_H_

#include <sourcemeta/blaze/canonicalizer.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <initializer_list> // std::initializer_list

#include <optional>    // std::optional
#include <string_view> // std::string_view

static auto canonicalizer_test_resolver(std::string_view identifier)
    -> sourcemeta::blaze::SchemaResolverResult {
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
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

#define CANONICALIZE_AND_VALIDATE(document, expected, compiled_template)       \
  {                                                                            \
    sourcemeta::blaze::canonicalize(document,                                  \
                                    sourcemeta::blaze::schema_walker,          \
                                    canonicalizer_test_resolver);              \
    EXPECT_EQ(document, expected);                                             \
    sourcemeta::blaze::Evaluator _evaluator;                                   \
    EXPECT_TRUE(_evaluator.validate(compiled_template, document));             \
  }

// Structural expectations cannot tell whether a rewrite preserved what the
// schema actually accepts. Compile the schema before and after canonicalising
// it and require both to agree on every given instance
#define CANONICALIZE_AND_COMPARE_EVALUATION(document, ...)                     \
  {                                                                            \
    auto _canonical{document};                                                 \
    sourcemeta::blaze::canonicalize(_canonical,                                \
                                    sourcemeta::blaze::schema_walker,          \
                                    canonicalizer_test_resolver);              \
    const auto _before{sourcemeta::blaze::compile(                             \
        document, sourcemeta::blaze::schema_walker,                            \
        canonicalizer_test_resolver,                                           \
        sourcemeta::blaze::default_schema_compiler)};                          \
    const auto _after{sourcemeta::blaze::compile(                              \
        _canonical, sourcemeta::blaze::schema_walker,                          \
        canonicalizer_test_resolver,                                           \
        sourcemeta::blaze::default_schema_compiler)};                          \
    sourcemeta::blaze::Evaluator _evaluator;                                   \
    for (const auto &_instance :                                               \
         std::initializer_list<sourcemeta::core::JSON>{__VA_ARGS__}) {         \
      EXPECT_EQ(_evaluator.validate(_before, _instance),                       \
                _evaluator.validate(_after, _instance));                       \
    }                                                                          \
  }

#endif
