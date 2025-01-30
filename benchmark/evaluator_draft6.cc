#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Evaluator_Draft6_Property_Names(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-06/schema#",
        "propertyNames": {
          "minLength": 2
        }
      })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
        "aa": true,
        "bb": true,
        "cc": true,
        "dd": true,
        "ee": true,
        "ff": true,
        "gg": true,
        "hh": true,
        "ii": true,
        "jj": true,
        "kk": true,
        "ll": true,
        "mm": true,
        "nn": true,
        "oo": true,
        "pp": true,
        "qq": true,
        "rr": true,
        "ss": true,
        "tt": true,
        "uu": true,
        "vv": true,
        "ww": true,
        "xx": true,
        "yy": true,
        "zz": true
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

BENCHMARK(Evaluator_Draft6_Property_Names);
