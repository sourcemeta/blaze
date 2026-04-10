#ifndef SOURCEMETA_BLAZE_ALTERSCHEMA_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_ALTERSCHEMA_TEST_UTILS_H_

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>
#include <string_view>
#include <tuple>
#include <vector>

template <typename TraceCollection>
static auto has_lint_trace(const TraceCollection &traces,
                           std::string_view pointer, std::string_view name,
                           std::string_view message, const bool fixable)
    -> bool {
  return std::any_of(traces.cbegin(), traces.cend(),
                     [&pointer, &name, &message, fixable](const auto &trace) {
                       return sourcemeta::core::to_string(std::get<0>(trace)) ==
                                  pointer &&
                              std::get<1>(trace) == name &&
                              std::get<2>(trace) == message &&
                              std::get<4>(trace) == fixable;
                     });
}

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
  } else {
    return sourcemeta::core::schema_resolver(identifier);
  }
}

#define LINT_WITHOUT_FIX(document, result, traces)                             \
  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,  \
                         sourcemeta::core::SchemaTransformRule::Result, bool>> \
      traces;                                                                  \
  sourcemeta::core::SchemaTransformer bundle;                                  \
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

#define EXPECT_LINT_TRACE_EXISTS(traces, pointer, name, message, fixable)      \
  EXPECT_TRUE(                                                                 \
      has_lint_trace((traces), (pointer), (name), (message), (fixable)));

#define LINT_AND_FIX(document, result, traces)                                 \
  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,  \
                         sourcemeta::core::SchemaTransformRule::Result, bool>> \
      traces;                                                                  \
  sourcemeta::core::SchemaTransformer bundle;                                  \
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);  \
  const auto result = bundle.apply(                                            \
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,    \
      [&traces](const auto &pointer, const auto &name, const auto &message,    \
                const auto &outcome, const auto &fixable) {                    \
        traces.emplace_back(pointer, name, message, outcome, fixable);         \
      });

#define CANONICALIZE(document, result, traces)                                 \
  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,  \
                         sourcemeta::core::SchemaTransformRule::Result, bool>> \
      traces;                                                                  \
  sourcemeta::core::SchemaTransformer bundle;                                  \
  sourcemeta::blaze::add(bundle,                                               \
                         sourcemeta::blaze::AlterSchemaMode::Canonicalizer);   \
  const auto result = bundle.apply(                                            \
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,    \
      [&traces](const auto &pointer, const auto &name, const auto &message,    \
                const auto &outcome, const auto &fixable) {                    \
        traces.emplace_back(pointer, name, message, outcome, fixable);         \
      });

#endif
