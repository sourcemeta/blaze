#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <cstddef>    // std::size_t
#include <filesystem> // std::filesystem

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

static void
Alterschema_Check_Readibility_ISO_Language_Set_3(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  for (auto _ : state) {
    auto result = bundle.check(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               [](const auto &, const auto &, const auto &,
                                  const auto &, const auto &) {});
    assert(result.first);
    assert(result.second == 100);
    benchmark::DoNotOptimize(result);
  }
}

static void Alterschema_Check_Readibility_OMC(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_omc_json_v2.json")};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  for (auto _ : state) {
    auto result = bundle.check(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               [](const auto &, const auto &, const auto &,
                                  const auto &, const auto &) {});
    assert(!result.first);
    benchmark::DoNotOptimize(result);
  }
}

static void Alterschema_Check_Readibility_KrakenD(benchmark::State &state) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_krakend.json")};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  for (auto _ : state) {
    auto result{bundle.check(schema, sourcemeta::core::schema_walker,
                             sourcemeta::core::schema_resolver,
                             [](const auto &, const auto &, const auto &,
                                const auto &, const auto &) {})};
    benchmark::DoNotOptimize(result);
  }
}

static void Alterschema_Apply_Readibility_KrakenD(benchmark::State &state) {
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "2019_09_krakend.json")};

  for (auto _ : state) {
    state.PauseTiming();
    auto copy = schema;
    state.ResumeTiming();
    auto result = bundle.apply(copy, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               [](const auto &, const auto &, const auto &,
                                  const auto &, const auto &) {});
    assert(!result.first);
    benchmark::DoNotOptimize(result);
  }
}

static void Alterschema_Check_Invalid_External_Refs(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_many_invalid_external_refs.json")};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  for (auto _ : state) {
    std::size_t trace_count{0};
    auto result = bundle.check(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        [&trace_count](const auto &, [[maybe_unused]] const auto &name,
                       const auto &, const auto &, const auto &) {
          assert(name == "invalid_external_ref");
          trace_count++;
        });
    assert(!result.first);
    assert(trace_count == 1024);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Alterschema_Check_Readibility_ISO_Language_Set_3);
BENCHMARK(Alterschema_Check_Readibility_OMC);
BENCHMARK(Alterschema_Check_Readibility_KrakenD);
BENCHMARK(Alterschema_Apply_Readibility_KrakenD);
BENCHMARK(Alterschema_Check_Invalid_External_Refs);
