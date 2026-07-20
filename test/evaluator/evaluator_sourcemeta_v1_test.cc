#include <sourcemeta/core/test.h>

#include <optional>
#include <string_view>
#include <unordered_set>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "evaluator_utils.h"

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "tag:sourcemeta.com,2026:extension/v1/2019-09") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "tag:sourcemeta.com,2026:extension/v1/2019-09",
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2019-09/vocab/core": true,
        "https://json-schema.org/draft/2019-09/vocab/applicator": true,
        "https://json-schema.org/draft/2019-09/vocab/validation": true,
        "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
        "https://json-schema.org/draft/2019-09/vocab/format": false,
        "https://json-schema.org/draft/2019-09/vocab/content": true,
        "tag:sourcemeta.com,2026:extension/v1": true
      }
    })JSON");
  }

  if (identifier == "tag:sourcemeta.com,2026:extension/v1/2020-12") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "tag:sourcemeta.com,2026:extension/v1/2020-12",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true,
        "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
        "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
        "https://json-schema.org/draft/2020-12/vocab/content": true,
        "tag:sourcemeta.com,2026:extension/v1": true
      }
    })JSON");
  }

  return sourcemeta::blaze::schema_resolver(identifier);
}

TEST(x_jsonld_id_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-id": "https://schema.org/name"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "",
                                 "https://schema.org/name");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD predicate was \"https://schema.org/name\"");
}

TEST(x_jsonld_id_no_annotation_fast_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-id": "https://schema.org/name"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 0, "",
                                            test_resolver);
}

TEST(x_jsonld_multiple_keywords_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-id": "https://schema.org/releaseDate",
    "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-01-15"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-datatype", "#/x-jsonld-datatype",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-id", "#/x-jsonld-id", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-datatype", "#/x-jsonld-datatype",
                                 "", "http://www.w3.org/2001/XMLSchema#date");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-id", "#/x-jsonld-id", "",
                                 "https://schema.org/releaseDate");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The JSON-LD datatype was \"http://www.w3.org/2001/XMLSchema#date\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The JSON-LD predicate was \"https://schema.org/releaseDate\"");
}

TEST(x_jsonld_type_array_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-type": [ "https://schema.org/Product", "https://schema.org/Thing" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-type", "#/x-jsonld-type", "");
  EVALUATE_TRACE_POST_ANNOTATION(
      0, "/x-jsonld-type", "#/x-jsonld-type", "",
      sourcemeta::core::parse_json(
          R"JSON([ "https://schema.org/Product", "https://schema.org/Thing" ])JSON"));
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The JSON-LD types were \"https://schema.org/Product\", and "
      "\"https://schema.org/Thing\"");
}

TEST(x_jsonld_reverse_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-reverse": "https://schema.org/subjectOf"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-reverse", "#/x-jsonld-reverse",
                                "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-reverse", "#/x-jsonld-reverse",
                                 "", "https://schema.org/subjectOf");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The reverse JSON-LD predicate was "
                               "\"https://schema.org/subjectOf\"");
}

TEST(x_jsonld_type_string_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-type": "https://schema.org/Product"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-type", "#/x-jsonld-type", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-type", "#/x-jsonld-type", "",
                                 "https://schema.org/Product");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD type was \"https://schema.org/Product\"");
}

TEST(x_jsonld_type_empty_array_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-type": []
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-type", "#/x-jsonld-type", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-type", "#/x-jsonld-type", "",
                                 sourcemeta::core::parse_json("[]"));
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0, "No JSON-LD types were assigned");
}

TEST(x_jsonld_language_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-language": "en-US"
  })JSON")};

  const sourcemeta::core::JSON instance{"hello"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-language", "#/x-jsonld-language",
                                "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-language", "#/x-jsonld-language",
                                 "", "en-US");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The natural language was \"en-US\"");
}

TEST(x_jsonld_direction_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-direction": "rtl"
  })JSON")};

  const sourcemeta::core::JSON instance{"hello"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-direction",
                                "#/x-jsonld-direction", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-direction",
                                 "#/x-jsonld-direction", "", "rtl");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0, "The base direction was \"rtl\"");
}

TEST(x_jsonld_json_true_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-json": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-json", "#/x-jsonld-json", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-json", "#/x-jsonld-json", "",
                                 true);
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be treated as an opaque JSON literal");
}

TEST(x_jsonld_json_false_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-json": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-json", "#/x-jsonld-json", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-json", "#/x-jsonld-json", "",
                                 false);
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was not expected to be treated as an opaque JSON literal");
}

TEST(x_jsonld_graph_true_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-graph": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-graph", "#/x-jsonld-graph", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-graph", "#/x-jsonld-graph", "",
                                 true);
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be wrapped in a JSON-LD named graph");
}

TEST(x_jsonld_graph_false_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-graph": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-graph", "#/x-jsonld-graph", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-graph", "#/x-jsonld-graph", "",
                                 false);
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was not expected to be wrapped in a JSON-LD named graph");
}

TEST(x_jsonld_container_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-container": "@list"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-container",
                                "#/x-jsonld-container", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-container",
                                 "#/x-jsonld-container", "", "@list");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The JSON-LD container was \"@list\"");
}

TEST(x_jsonld_self_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-self": "https://www.iso.org/iso-4217/{this}"
  })JSON")};

  const sourcemeta::core::JSON instance{"USD"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-self", "#/x-jsonld-self", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-self", "#/x-jsonld-self", "",
                                 "https://www.iso.org/iso-4217/{this}");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The JSON-LD identifier template was "
                               "\"https://www.iso.org/iso-4217/{this}\"");
}

TEST(x_jsonld_override_true_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_override_false_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-override": false
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", false);
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The sibling JSON-LD annotations were not "
                               "expected to override any other annotations");
}

TEST(x_jsonld_id_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-id": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "",
                                 nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The nested JSON-LD predicates were expected to be removed");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_reverse_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-override": true,
    "x-jsonld-reverse": null
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-reverse", "#/x-jsonld-reverse",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-reverse", "#/x-jsonld-reverse",
                                 "", nullptr);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The nested reverse JSON-LD predicates were "
                               "expected to be removed");
}

TEST(x_jsonld_type_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-override": true,
    "x-jsonld-type": null
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-type", "#/x-jsonld-type", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-type", "#/x-jsonld-type", "",
                                 nullptr);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The nested JSON-LD types were expected to be removed");
}

TEST(x_jsonld_datatype_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-datatype": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-datatype", "#/x-jsonld-datatype",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-datatype", "#/x-jsonld-datatype",
                                 "", nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD datatype was expected to be removed");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_language_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-language": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-language", "#/x-jsonld-language",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-language", "#/x-jsonld-language",
                                 "", nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The natural language was expected to be removed");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_direction_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-direction": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-direction",
                                "#/x-jsonld-direction", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-direction",
                                 "#/x-jsonld-direction", "", nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The base direction was expected to be removed");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_json_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-json": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-json", "#/x-jsonld-json", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-json", "#/x-jsonld-json", "",
                                 nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was not expected to be treated as "
                               "an opaque JSON literal");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_graph_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-graph": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-graph", "#/x-jsonld-graph", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-graph", "#/x-jsonld-graph", "",
                                 nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was not expected to be wrapped in a "
                               "JSON-LD named graph");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_container_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-container": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("[]")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-container",
                                "#/x-jsonld-container", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-container",
                                 "#/x-jsonld-container", "", nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD container was expected to be removed");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(x_jsonld_self_null_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-override": true,
    "x-jsonld-self": null
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-self", "#/x-jsonld-self", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-self", "#/x-jsonld-self", "",
                                 nullptr);

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The JSON-LD identifier was expected to be removed");
}

TEST(x_jsonld_id_nested_annotation_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "properties": {
      "name": {
        "x-jsonld-id": "https://schema.org/name"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "foo"
  })JSON")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 3, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE(0, LogicalWhenType, "/properties", "#/properties", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/properties/name/x-jsonld-id",
                                "#/properties/name/x-jsonld-id", "/name");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/properties/name/x-jsonld-id",
                                 "#/properties/name/x-jsonld-id", "/name",
                                 "https://schema.org/name");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/properties", "#/properties", "", "name");
  EVALUATE_TRACE_POST_SUCCESS(2, LogicalWhenType, "/properties", "#/properties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD predicate was \"https://schema.org/name\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The object property \"name\" successfully "
                               "validated against its property subschema");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "The object value was expected to validate "
                               "against the single defined property subschema");
}

TEST(x_jsonld_id_nested_no_annotation_fast_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "properties": {
      "name": {
        "x-jsonld-id": "https://schema.org/name"
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "foo"
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 0, "",
                                            test_resolver);
}

TEST(x_jsonld_id_annotation_whitelist_tweak_fast_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "x-jsonld-id": "https://schema.org/releaseDate",
    "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-01-15"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations =
      std::unordered_set<sourcemeta::core::JSON::StringView>{"x-jsonld-id"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED_RESOLVER(schema, instance, 1, "",
                                                    tweaks, test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "",
                                 "https://schema.org/releaseDate");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The JSON-LD predicate was \"https://schema.org/releaseDate\"");
}

TEST(format_uri_x_format_assertion_true_valid_fast_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(format_uri_x_format_assertion_true_invalid_fast_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_FAILURE_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_uri_x_format_assertion_true_valid_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 3, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/x-format-assertion",
                                "#/x-format-assertion", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/x-format-assertion",
                                 "#/x-format-assertion", "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "A sibling `format` keyword was expected to "
                               "be enforced as an assertion");
}

TEST(format_uri_x_format_assertion_true_invalid_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_uri_x_format_assertion_false_invalid_fast_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "format": "uri",
    "x-format-assertion": false
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 0, "",
                                            test_resolver);
}

TEST(format_uri_x_format_assertion_false_invalid_exhaustive_2020_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2020-12",
    "format": "uri",
    "x-format-assertion": false
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-format-assertion",
                                "#/x-format-assertion", "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/format", "#/format", "", "uri");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-format-assertion",
                                 "#/x-format-assertion", "", false);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The logical type of the instance was expected to be \"uri\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "A sibling `format` keyword was expected to "
                               "be collected as an annotation");
}

TEST(x_jsonld_id_annotation_exhaustive_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "x-jsonld-id": "https://schema.org/name"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "");
  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-id", "#/x-jsonld-id", "",
                                 "https://schema.org/name");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD predicate was \"https://schema.org/name\"");
}

TEST(x_jsonld_id_no_annotation_fast_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "x-jsonld-id": "https://schema.org/name"
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 0, "",
                                            test_resolver);
}

TEST(x_jsonld_datatype_null_annotation_exhaustive_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "x-jsonld-datatype": null,
    "x-jsonld-override": true
  })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 2, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE_ANNOTATION(0, "/x-jsonld-datatype", "#/x-jsonld-datatype",
                                "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                "");

  EVALUATE_TRACE_POST_ANNOTATION(0, "/x-jsonld-datatype", "#/x-jsonld-datatype",
                                 "", nullptr);
  EVALUATE_TRACE_POST_ANNOTATION(1, "/x-jsonld-override", "#/x-jsonld-override",
                                 "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The JSON-LD datatype was expected to be removed");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The sibling JSON-LD annotations were expected "
                               "to override the nested annotations they "
                               "shadow");
}

TEST(format_uri_x_format_assertion_true_valid_fast_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(format_uri_x_format_assertion_true_invalid_fast_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_FAST_FAILURE_RESOLVER(schema, instance, 1, "",
                                            test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}

TEST(format_uri_x_format_assertion_true_valid_exhaustive_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_RESOLVER(schema, instance, 3, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(1, "/format", "#/format", "");
  EVALUATE_TRACE_PRE_ANNOTATION(2, "/x-format-assertion",
                                "#/x-format-assertion", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_ANNOTATION(1, "/format", "#/format", "", "uri");
  EVALUATE_TRACE_POST_ANNOTATION(2, "/x-format-assertion",
                                 "#/x-format-assertion", "", true);

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The logical type of the instance was expected to be \"uri\"");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 2,
                               "A sibling `format` keyword was expected to "
                               "be enforced as an assertion");
}

TEST(format_uri_x_format_assertion_true_invalid_exhaustive_2019_09) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:extension/v1/2019-09",
    "format": "uri",
    "x-format-assertion": true
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_RESOLVER(schema, instance, 1, "",
                                                  test_resolver);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"://bad\" was expected to represent a valid URI");
}
