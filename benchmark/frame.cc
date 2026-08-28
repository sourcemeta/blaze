#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem
#include <functional> // std::ref
#include <optional>   // std::optional

#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

static void Schema_Frame_WoT_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "draft7_w3c_wot_td_v1_1.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_OMC_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_OMC_Locations(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::Locations, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_ISO_Language_Locations(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::Locations, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_ISO_Language_Root(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::Root, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_KrakenD_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_krakend.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_KrakenD_Reachable(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_krakend.json")};

  // Kept out of the timed region so that neither building nor discarding the
  // frame counts towards the reachability measurement
  std::optional<sourcemeta::blaze::SchemaFrame> frame;

  for (auto _ : state) {
    state.PauseTiming();
    frame.emplace(sourcemeta::blaze::SchemaFrame::Mode::References, schema,
                  sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    state.ResumeTiming();

    for (const auto &entry : frame->locations()) {
      if (entry.second.type ==
          sourcemeta::blaze::SchemaFrame::LocationType::Pointer) {
        continue;
      }

      for (const auto &subentry : frame->locations()) {
        if (subentry.second.type ==
                sourcemeta::blaze::SchemaFrame::LocationType::Resource ||
            subentry.second.type ==
                sourcemeta::blaze::SchemaFrame::LocationType::Subschema) {
          auto result{frame->is_reachable(subentry.second, entry.second,
                                          sourcemeta::blaze::schema_walker,
                                          sourcemeta::blaze::schema_resolver)};
          benchmark::DoNotOptimize(result);
        }
      }
    }
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
      sourcemeta::blaze::SchemaFrame::Mode::Locations, schema,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  for (auto _ : state) {
    auto result{frame.to_json(sourcemeta::blaze::schema_resolver, tracker)};
    assert(result.is_object());
    benchmark::DoNotOptimize(result);
  }
}

static void Schema_Frame_Many_Resources_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2020_12_many_resources.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void Schema_Frame_Deeply_Nested_References(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2020_12_deeply_nested.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

BENCHMARK(Schema_Frame_WoT_References);
BENCHMARK(Schema_Frame_OMC_References);
BENCHMARK(Schema_Frame_OMC_Locations);
BENCHMARK(Schema_Frame_ISO_Language_Locations);
BENCHMARK(Schema_Frame_ISO_Language_Root);
BENCHMARK(Schema_Frame_KrakenD_References);
BENCHMARK(Schema_Frame_KrakenD_Reachable);
BENCHMARK(Schema_Frame_ISO_Language_Locations_To_JSON);
BENCHMARK(Schema_Frame_Many_Resources_References);
BENCHMARK(Schema_Frame_Deeply_Nested_References);
