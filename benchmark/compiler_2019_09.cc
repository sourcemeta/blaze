#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>

static void Compiler_2019_09_OMC_JSON_V2(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "schemas" / "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    auto result{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_official_walker,
        sourcemeta::core::schema_official_resolver,
        sourcemeta::blaze::default_schema_compiler)};
    assert(!result.instructions.empty());
    benchmark::DoNotOptimize(result.instructions);
  }
}

BENCHMARK(Compiler_2019_09_OMC_JSON_V2);
