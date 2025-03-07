#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Evaluator_2019_09_Unevaluated_Properties(benchmark::State &state) {
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

static void Evaluator_2019_09_OMC_JSON_V2_1(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "schemas" / "2019_09_omc_json_v2.json")};

  const auto instance{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "instances" / "2019_09_omc_json_v2_1.json")};

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

BENCHMARK(Evaluator_2019_09_Unevaluated_Properties);
BENCHMARK(Evaluator_2019_09_OMC_JSON_V2_1);
