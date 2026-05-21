#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem
#include <functional> // std::ref

#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

static void Schema_Iterator_ISO_Language(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaIterator iterator{
        schema, sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver};
    auto subschema_count = static_cast<std::size_t>(
        std::distance(iterator.cbegin(), iterator.cend()));
    benchmark::DoNotOptimize(subschema_count);
  }
}

static void Schema_Tracker_ISO_Language(benchmark::State &state) {
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

static void Schema_Tracker_ISO_Language_To_JSON(benchmark::State &state) {
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

BENCHMARK(Schema_Iterator_ISO_Language);
BENCHMARK(Schema_Tracker_ISO_Language);
BENCHMARK(Schema_Tracker_ISO_Language_To_JSON);
