#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem
#include <vector>     // std::vector

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/uri.h>

static void Schema_Frame_WoT_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "draft7_w3c_wot_td_v1_1.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References};
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_OMC_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References};
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_OMC_Locations(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::Locations};
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_ISO_Language_Locations(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::Locations};
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_KrakenD_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_krakend.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References};
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_KrakenD_Reachable(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_krakend.json")};

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  for (auto _ : state) {
    state.PauseTiming();
    frame.reset();
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    state.ResumeTiming();

    for (const auto &entry : frame.locations()) {
      if (entry.second.type ==
          sourcemeta::blaze::SchemaFrame::LocationType::Pointer) {
        continue;
      }

      for (const auto &subentry : frame.locations()) {
        if (subentry.second.type ==
                sourcemeta::blaze::SchemaFrame::LocationType::Resource ||
            subentry.second.type ==
                sourcemeta::blaze::SchemaFrame::LocationType::Subschema) {
          auto result{frame.is_reachable(subentry.second, entry.second,
                                         sourcemeta::blaze::schema_walker,
                                         sourcemeta::blaze::schema_resolver)};
          benchmark::DoNotOptimize(result);
        }
      }
    }
  }
}

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

static void
Schema_Frame_ISO_Language_Locations_To_JSON(benchmark::State &state) {
  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON schema{nullptr};
  sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" /
                                  "2020_12_iso_language_2023_set_3.json",
                              schema, std::ref(tracker));

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  for (auto _ : state) {
    auto result{frame.to_json(tracker)};
    assert(result.is_object());
    benchmark::DoNotOptimize(result);
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

static void Schema_Format_ISO_Language_To_JSON(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto schema{sourcemeta::core::read_json(
        std::filesystem::path{CURRENT_DIRECTORY} / "files" /
        "2020_12_iso_language_2023_set_3.json")};
    state.ResumeTiming();
    sourcemeta::blaze::format(schema, sourcemeta::blaze::schema_walker,
                              sourcemeta::blaze::schema_resolver);
    assert(schema.is_object());
  }
}

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

static void Schema_Frame_Many_Resources_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2020_12_many_resources.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References};
    frame.analyse(schema, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    benchmark::DoNotOptimize(frame);
  }
}

BENCHMARK(Schema_Frame_WoT_References);
BENCHMARK(Schema_Frame_OMC_References);
BENCHMARK(Schema_Frame_OMC_Locations);
BENCHMARK(Schema_Frame_ISO_Language_Locations);
BENCHMARK(Schema_Frame_KrakenD_References);
BENCHMARK(Schema_Frame_KrakenD_Reachable);
BENCHMARK(Schema_Iterator_ISO_Language);
BENCHMARK(Schema_Frame_ISO_Language_Locations_To_JSON);
BENCHMARK(Schema_Tracker_ISO_Language);
BENCHMARK(Schema_Tracker_ISO_Language_To_JSON);
BENCHMARK(Schema_Format_ISO_Language_To_JSON);
BENCHMARK(Schema_Bundle_Meta_2020_12);
BENCHMARK(Schema_Frame_Many_Resources_References);
