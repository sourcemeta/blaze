#include <benchmark/benchmark.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/foundation.h>

static void Schema_Bundle_Meta_2020_12(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto schema{sourcemeta::blaze::schema_resolver(
                    "https://json-schema.org/draft/2020-12/schema")
                    .value()};
    state.ResumeTiming();
    sourcemeta::blaze::bundle(schema, sourcemeta::blaze::schema_walker,
                              sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(schema);
  }
}

BENCHMARK(Schema_Bundle_Meta_2020_12);
