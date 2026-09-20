#include <sourcemeta/core/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

BENCHMARK(Micro_2019_09_Unevaluated_Properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "name": true,
      "prohibited": false
    },
    "not": {
      "required": [ "prohibited" ]
    },
    "unevaluatedProperties": false,
    "$ref": "#/$defs/extension",
    "$defs": {
      "extension": {
        "patternProperties": { "^x-": true }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "name": "John Doe",
    "x-foo": "bar"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto iteration : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    sourcemeta::core::benchmark_do_not_optimize(result);
  }
}

BENCHMARK(Micro_2019_09_Compile_Wrap) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "micro" / "schemas" /
      "2019_09_krakend_wrap.json")};

  for (auto iteration : state) {
    auto schema_template{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler)};
    sourcemeta::core::benchmark_do_not_optimize(schema_template);
  }
}
