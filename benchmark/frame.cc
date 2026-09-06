#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem
#include <functional> // std::ref
#include <optional>   // std::optional

#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

static void schema_frame_wo_t_references(benchmark::State &state) {
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

static void schema_frame_omc_references(benchmark::State &state) {
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

static void schema_frame_omc_pointers(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_omc_json_v2.json")};

  for (auto _ : state) {
    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::Pointers, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
    benchmark::DoNotOptimize(frame);
  }
}

static void schema_frame_omc_locations(benchmark::State &state) {
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

static void schema_frame_iso_language_locations(benchmark::State &state) {
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

static void schema_frame_iso_language_root(benchmark::State &state) {
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

static void schema_frame_kraken_d_references(benchmark::State &state) {
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

static void schema_frame_kraken_d_reachable(benchmark::State &state) {
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

    frame->for_each_location(
        [&frame](
            const sourcemeta::blaze::SchemaReferenceType,
            const std::string_view,
            const sourcemeta::blaze::SchemaFrame::Location &entry) -> void {
          if (entry.type ==
              sourcemeta::blaze::SchemaFrame::LocationType::Pointer) {
            return;
          }

          frame->for_each_subschema(
              [&frame,
               &entry](const sourcemeta::blaze::SchemaFrame::Location &subentry)
                  -> void {
                auto result{frame->is_reachable(
                    subentry, entry, sourcemeta::blaze::schema_walker,
                    sourcemeta::blaze::schema_resolver)};
                benchmark::DoNotOptimize(result);
              });
        });
  }
}

static void
schema_frame_iso_language_locations_to_json(benchmark::State &state) {
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

static void schema_frame_many_resources_references(benchmark::State &state) {
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

static void schema_frame_deeply_nested_references(benchmark::State &state) {
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

BENCHMARK(schema_frame_wo_t_references);
BENCHMARK(schema_frame_omc_references);
BENCHMARK(schema_frame_omc_pointers);
BENCHMARK(schema_frame_omc_locations);
BENCHMARK(schema_frame_iso_language_locations);
BENCHMARK(schema_frame_iso_language_root);
BENCHMARK(schema_frame_kraken_d_references);
BENCHMARK(schema_frame_kraken_d_reachable);
BENCHMARK(schema_frame_iso_language_locations_to_json);
BENCHMARK(schema_frame_many_resources_references);
BENCHMARK(schema_frame_deeply_nested_references);
