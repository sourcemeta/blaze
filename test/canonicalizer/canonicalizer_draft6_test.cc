#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "canonicalizer_test_utils.h"

namespace {
auto compiled_metaschema() -> const sourcemeta::blaze::Template & {
  static const sourcemeta::blaze::Template SCHEMA_TEMPLATE{
      sourcemeta::blaze::compile(
          sourcemeta::core::read_json(std::filesystem::path{SCHEMAS_PATH} /
                                      "canonical-draft6.json"),
          sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler)};
  return SCHEMA_TEMPLATE;
}
} // namespace

// Every other Draft 6 canonicalization case lives in
// `test/canonicalizer/draft6` as a JSON fixture. This one cannot: a schema
// that nothing satisfies canonicalizes to a bare `false`, and a boolean
// carries no `$schema` for the runner to compare against the input's, so the
// fixture format has no way to spell this result at the root. The rules that
// reach it from a subschema are covered by the
// `property_unsatisfiable_*` fixtures, where the `false` is a node instead

TEST(type_null_as_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "null",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON(
    false
  )JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}
