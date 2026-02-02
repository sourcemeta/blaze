#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/linter.h>

static void Micro_2019_09_Unevaluated_Properties(benchmark::State &state) {
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
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_2019_09_Compile_Wrap(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "micro" / "schemas" /
      "2019_09_krakend_wrap.json")};

  for (auto _ : state) {
    auto schema_template{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler)};
    benchmark::DoNotOptimize(schema_template);
  }
}

static void Micro_2019_09_KrakenD_Linter_Check(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "micro" / "schemas" /
      "2019_09_krakend.json")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  for (auto _ : state) {
    auto result{bundle.check(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        [](const auto &, const auto &, const auto &, const auto &) {})};
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_2019_09_KrakenD_Linter_Apply(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "micro" / "schemas" /
      "2019_09_krakend.json")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  for (auto _ : state) {
    state.PauseTiming();
    auto copy{schema};
    state.ResumeTiming();

    auto result{bundle.apply(
        copy, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        [](const auto &, const auto &, const auto &, const auto &) {})};
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Micro_2019_09_Unevaluated_Properties);
BENCHMARK(Micro_2019_09_Compile_Wrap);
BENCHMARK(Micro_2019_09_KrakenD_Linter_Check);
BENCHMARK(Micro_2019_09_KrakenD_Linter_Apply);
