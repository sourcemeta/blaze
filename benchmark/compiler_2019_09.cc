#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>

static void Compiler_2019_09_OMC_JSON_V2(benchmark::State &state) {
  const auto schema{sourcemeta::jsontoolkit::from_file(
      std::filesystem::path{CURRENT_DIRECTORY} / "schemas" /
      "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    auto result{sourcemeta::blaze::compile(
        schema, sourcemeta::jsontoolkit::default_schema_walker,
        sourcemeta::jsontoolkit::official_resolver,
        sourcemeta::blaze::default_schema_compiler)};
    assert(!result.instructions.empty());
    benchmark::DoNotOptimize(result.instructions);
  }
}

BENCHMARK(Compiler_2019_09_OMC_JSON_V2);
