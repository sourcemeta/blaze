#include "documentation_test_utils.h"

TEST(draft2_hyper_schema_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-02/hyper-schema#",
    "type": "string"
  })JSON",
      "This module describes JSON Schema Draft 3 to 2020-12", "", "");
}

TEST(a_schema_without_a_dialect_is_read_as_the_default) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "type": "array",
    "prefixItems": [ { "type": "string" } ]
  })JSON")};
  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  expect_fits_the_format(documentation);
  EXPECT_EQ(documentation.at("language").to_string(),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(documentation.at("root"), sourcemeta::core::parse_json(R"JSON({
    "kind": "array",
    "slots": [ { "kind": "string" } ]
  })JSON"));
}

namespace {

auto vocabulary_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://example.com/meta/without-meta-data") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/meta/without-meta-data",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true
      },
      "$dynamicAnchor": "meta",
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2020-12/meta/core" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/applicator" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/validation" }
      ]
    })JSON");
  }

  if (identifier == "https://example.com/meta/without-validation") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/meta/without-validation",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/meta-data": true
      },
      "$dynamicAnchor": "meta",
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2020-12/meta/core" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/applicator" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/meta-data" }
      ]
    })JSON");
  }

  if (identifier == "https://example.com/meta/without-applicator") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://example.com/meta/without-applicator",
      "$vocabulary": {
        "https://json-schema.org/draft/2019-09/vocab/core": true,
        "https://json-schema.org/draft/2019-09/vocab/validation": true
      },
      "$recursiveAnchor": true,
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2019-09/meta/core" },
        { "$ref": "https://json-schema.org/draft/2019-09/meta/validation" }
      ]
    })JSON");
  }

  return sourcemeta::core::schema_resolver(identifier);
}

auto describe_with_vocabularies(const char *schema) -> sourcemeta::core::JSON {
  auto documentation{sourcemeta::blaze::to_documentation(
      sourcemeta::core::parse_json(schema), sourcemeta::core::schema_walker,
      vocabulary_resolver)};
  expect_fits_the_format(documentation);
  return documentation;
}

} // namespace

TEST(2020_12_without_the_meta_data_vocabulary_annotations_say_nothing) {
  EXPECT_EQ(describe_with_vocabularies(R"JSON({
    "$schema": "https://example.com/meta/without-meta-data",
    "title": "Order",
    "type": "string",
    "default": "none",
    "examples": [ "one" ]
  })JSON"),
            sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Schema",
    "language": "https://example.com/meta/without-meta-data",
    "root": { "kind": "string" }
  })JSON"));
}

TEST(2020_12_without_the_validation_vocabulary_types_and_limits_say_nothing) {
  EXPECT_EQ(describe_with_vocabularies(R"JSON({
    "$schema": "https://example.com/meta/without-validation",
    "title": "Name",
    "type": "string",
    "minLength": 2
  })JSON"),
            sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Name",
    "language": "https://example.com/meta/without-validation",
    "root": { "kind": "any" }
  })JSON"));
}

TEST(2019_09_without_the_applicator_vocabulary_properties_say_nothing) {
  EXPECT_EQ(describe_with_vocabularies(R"JSON({
    "$schema": "https://example.com/meta/without-applicator",
    "type": "object",
    "properties": { "name": { "type": "string" } },
    "required": [ "name" ]
  })JSON"),
            sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Schema",
    "language": "https://example.com/meta/without-applicator",
    "root": {
      "kind": "object",
      "properties": [ { "name": "name", "required": true } ]
    }
  })JSON"));
}
