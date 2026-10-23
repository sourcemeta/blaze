#include <sourcemeta/blaze/binpack.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/core/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <functional> // std::ref
#include <iostream>   // std::cerr
#include <sstream>    // std::ostringstream

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
  sourcemeta::blaze::SimpleOutput output{instance};
  sourcemeta::blaze::Evaluator evaluator;
  if (!evaluator.validate(compiled_schema, instance, std::ref(output))) {
    std::cerr << "JSON Schema validation failed\n";
    return EXIT_FAILURE;
  }

  auto binpack_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
  })JSON")};
  sourcemeta::blaze::binpack_compile(binpack_schema,
                                     sourcemeta::core::schema_walker,
                                     sourcemeta::core::schema_resolver);
  const auto encoding{sourcemeta::blaze::binpack_load(binpack_schema)};
  std::ostringstream binpack_output;
  sourcemeta::blaze::BinPackEncoder encoder{binpack_output};
  encoder.write(sourcemeta::core::JSON{5}, encoding);

  return EXIT_SUCCESS;
}
