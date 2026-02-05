#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/linter.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/blaze/test.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cerr

auto main() -> int {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};
  sourcemeta::blaze::Evaluator evaluator;
  if (!evaluator.validate(compiled_schema, instance)) {
    std::cerr << "JSON Schema validation failed\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
