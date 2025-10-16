#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Micro_Draft7_If_Then_Else(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-07/schema#",
        "if": {
          "type": "string"
        },
        "then": {
          "if": { "minLength": 2 },
          "then": { "maxLength": 5 },
          "else": { "maxLength": 3 }
        },
        "else": {
          "if": { "type": "integer" },
          "then": { "minimum": 4 },
          "else": { "maxProperties": 4 }
        }
      })JSON")};

  const sourcemeta::core::JSON instance{"foo"};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Micro_Draft7_If_Then_Else);
