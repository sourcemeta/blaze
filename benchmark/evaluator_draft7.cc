#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Evaluator_Draft7_If_Then_Else(benchmark::State &state) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const sourcemeta::jsontoolkit::JSON instance{"foo"};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::EvaluationContext context;
  for (auto _ : state) {
    auto result{
        sourcemeta::blaze::evaluate(schema_template, instance, context)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Evaluator_Draft7_Vercel_1(benchmark::State &state) {
  const auto schema{sourcemeta::jsontoolkit::from_file(
      std::filesystem::path{CURRENT_DIRECTORY} / "schemas" /
      "draft7_vercel.json")};

  const auto instance{sourcemeta::jsontoolkit::from_file(
      std::filesystem::path{CURRENT_DIRECTORY} / "instances" /
      "draft7_vercel_1.json")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::EvaluationContext context;
  for (auto _ : state) {
    auto result{
        sourcemeta::blaze::evaluate(schema_template, instance, context)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Evaluator_Draft7_If_Then_Else);
BENCHMARK(Evaluator_Draft7_Vercel_1);
