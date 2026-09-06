#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem
#include <functional> // std::ref

#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

static void schema_tracker_iso_language(benchmark::State &state) {
  for (auto _ : state) {
    sourcemeta::core::PointerPositionTracker tracker;
    sourcemeta::core::JSON schema{nullptr};
    sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                    "files" /
                                    "2020_12_iso_language_2023_set_3.json",
                                schema, std::ref(tracker));
    assert(schema.is_object());
    benchmark::DoNotOptimize(schema);
  }
}

static void schema_tracker_iso_language_to_json(benchmark::State &state) {
  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON schema{nullptr};
  sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" /
                                  "2020_12_iso_language_2023_set_3.json",
                              schema, std::ref(tracker));

  for (auto _ : state) {
    auto result{sourcemeta::core::to_json(tracker)};
    assert(result.is_object());
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(schema_tracker_iso_language);
BENCHMARK(schema_tracker_iso_language_to_json);
