#ifndef SOURCEMETA_BLAZE_ALTERSCHEMA_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_ALTERSCHEMA_TEST_UTILS_H_

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sstream>
#include <tuple>
#include <vector>

static auto alterschema_test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
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
             "https://example.com/unsupported-vocabulary-metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/unsupported-vocabulary-metaschema",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true,
        "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
        "https://json-schema.org/draft/2020-12/vocab/format-assertion": true
      }
    })JSON");
  } else {
    return sourcemeta::core::schema_resolver(identifier);
  }
}

#define LINT_WITHOUT_FIX(document, result, traces)                             \
  std::vector<                                                                 \
      std::tuple<sourcemeta::core::Pointer, std::string, std::string,          \
                 sourcemeta::blaze::SchemaTransformRule::Result, bool>>        \
      traces;                                                                  \
  sourcemeta::blaze::SchemaTransformer bundle;                                 \
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);  \
  const auto result = bundle.check(                                            \
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,    \
      [&traces](const auto &pointer, const auto &name, const auto &message,    \
                const auto &outcome, const auto &fixable) {                    \
        traces.emplace_back(pointer, name, message, outcome, fixable);         \
      });

#define EXPECT_LINT_TRACE(traces, index, pointer, name, message, fixable)      \
  EXPECT_EQ(sourcemeta::core::to_string(std::get<0>((traces).at(index))),      \
            (pointer));                                                        \
  EXPECT_EQ(std::get<1>((traces).at(index)), (name));                          \
  EXPECT_EQ(std::get<2>((traces).at(index)), (message));                       \
  EXPECT_EQ(std::get<4>((traces).at(index)), (fixable));

#define LINT_AND_FIX(document, result, traces)                                 \
  std::vector<                                                                 \
      std::tuple<sourcemeta::core::Pointer, std::string, std::string,          \
                 sourcemeta::blaze::SchemaTransformRule::Result, bool>>        \
      traces;                                                                  \
  sourcemeta::blaze::SchemaTransformer bundle;                                 \
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);  \
  const auto result = bundle.apply(                                            \
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,    \
      [&traces](const auto &pointer, const auto &name, const auto &message,    \
                const auto &outcome, const auto &fixable) {                    \
        traces.emplace_back(pointer, name, message, outcome, fixable);         \
      });

#define CANONICALIZE_AND_VALIDATE(document, expected, compiled_template)       \
  {                                                                            \
    sourcemeta::blaze::SchemaTransformer _bundle;                              \
    sourcemeta::blaze::add(_bundle,                                            \
                           sourcemeta::blaze::AlterSchemaMode::Canonicalizer); \
    const auto _result = _bundle.apply(                                        \
        document, sourcemeta::core::schema_walker, alterschema_test_resolver,  \
        [](const auto &, const auto &, const auto &, const auto &,             \
           const auto &) {});                                                  \
    EXPECT_TRUE(_result.first);                                                \
    EXPECT_EQ(document, expected);                                             \
    sourcemeta::blaze::Evaluator _evaluator;                                   \
    EXPECT_TRUE(_evaluator.validate(compiled_template, document));             \
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

#define UPGRADE_DRAFT_6(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::SchemaTransformer _bundle;                              \
    sourcemeta::blaze::add(_bundle,                                            \
                           sourcemeta::blaze::AlterSchemaMode::UpgradeDraft6); \
    const auto _result = _bundle.apply(                                        \
        document, sourcemeta::core::schema_walker, alterschema_test_resolver,  \
        [](const auto &, const auto &, const auto &, const auto &,             \
           const auto &) {});                                                  \
    EXPECT_TRUE(_result.first);                                                \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_DRAFT_7(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::SchemaTransformer _bundle;                              \
    sourcemeta::blaze::add(_bundle,                                            \
                           sourcemeta::blaze::AlterSchemaMode::UpgradeDraft7); \
    const auto _result = _bundle.apply(                                        \
        document, sourcemeta::core::schema_walker, alterschema_test_resolver,  \
        [](const auto &, const auto &, const auto &, const auto &,             \
           const auto &) {});                                                  \
    EXPECT_TRUE(_result.first);                                                \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2019_09(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::SchemaTransformer _bundle;                              \
    sourcemeta::blaze::add(_bundle,                                            \
                           sourcemeta::blaze::AlterSchemaMode::Upgrade201909); \
    const auto _result = _bundle.apply(                                        \
        document, sourcemeta::core::schema_walker, alterschema_test_resolver,  \
        [](const auto &, const auto &, const auto &, const auto &,             \
           const auto &) {});                                                  \
    EXPECT_TRUE(_result.first);                                                \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#define UPGRADE_2020_12(document, expected)                                    \
  {                                                                            \
    sourcemeta::blaze::SchemaTransformer _bundle;                              \
    sourcemeta::blaze::add(_bundle,                                            \
                           sourcemeta::blaze::AlterSchemaMode::Upgrade202012); \
    const auto _result = _bundle.apply(                                        \
        document, sourcemeta::core::schema_walker, alterschema_test_resolver,  \
        [](const auto &, const auto &, const auto &, const auto &,             \
           const auto &) {});                                                  \
    EXPECT_TRUE(_result.first);                                                \
    EXPECT_JSON_EQ_WITH_ORDERING(document, expected);                          \
  }

#endif
