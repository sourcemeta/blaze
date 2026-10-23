#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "canonicalizer_test_utils.h"

static constexpr auto OPENAPI_3_0_DIALECT{
    "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"};

namespace {
// The Schema Object is a closed dialect, so whatever canonicalisation makes of
// one has to be a Schema Object still. Its own dialect is what says whether it
// is, and it names no keyword that could hold a lifted subschema
auto compiled_dialect() -> const sourcemeta::blaze::Template & {
  static const sourcemeta::blaze::Template SCHEMA_TEMPLATE{
      sourcemeta::blaze::compile(
          sourcemeta::core::schema_resolver(OPENAPI_3_0_DIALECT).value(),
          sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler)};
  return SCHEMA_TEMPLATE;
}
} // namespace

TEST(nullable_type_is_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "nullable": true
  })JSON");

  CANONICALIZE_WITH_DIALECT_AND_VALIDATE(
      document, expected, OPENAPI_3_0_DIALECT, compiled_dialect());
}

TEST(nested_subschemas_are_not_lifted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    }
  })JSON");

  CANONICALIZE_WITH_DIALECT_AND_VALIDATE(
      document, expected, OPENAPI_3_0_DIALECT, compiled_dialect());
}

TEST(repeated_subschemas_are_not_shared) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "allOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "allOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  CANONICALIZE_WITH_DIALECT_AND_VALIDATE(
      document, expected, OPENAPI_3_0_DIALECT, compiled_dialect());
}

TEST(a_local_reference_keeps_the_pointer_it_names) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "self": { "$ref": "#" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "self": { "$ref": "#" }
    }
  })JSON");

  CANONICALIZE_WITH_DIALECT_AND_VALIDATE(
      document, expected, OPENAPI_3_0_DIALECT, compiled_dialect());
}
