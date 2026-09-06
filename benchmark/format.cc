#include <benchmark/benchmark.h>

#include <filesystem> // std::filesystem

#include <sourcemeta/blaze/format.h>
#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

static void schema_format_iso_language_to_json(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto schema{sourcemeta::core::read_json(
        std::filesystem::path{CURRENT_DIRECTORY} / "files" /
        "2020_12_iso_language_2023_set_3.json")};
    state.ResumeTiming();
    sourcemeta::blaze::format(schema, sourcemeta::blaze::schema_walker,
                              sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(schema);
  }
}

BENCHMARK(schema_format_iso_language_to_json);
