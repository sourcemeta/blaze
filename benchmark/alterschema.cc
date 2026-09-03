#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <cstddef>    // std::size_t
#include <filesystem> // std::filesystem
#include <map>        // std::map
#include <string>     // std::string, std::to_string

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

static void
Alterschema_Check_Readibility_ISO_Language_Set_3(benchmark::State &state) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  for (auto _ : state) {
    auto result = bundle.check(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
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
    auto result = bundle.check(schema, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
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
    auto result{bundle.check(schema, sourcemeta::blaze::schema_walker,
                             sourcemeta::blaze::schema_resolver,
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
    auto result = bundle.apply(copy, sourcemeta::blaze::schema_walker,
                               sourcemeta::blaze::schema_resolver,
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
        schema, sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
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

// Every reference here resolves, so the linter reaches the check that a
// fragment names something the remote actually has
static void
Alterschema_Check_Resolvable_External_Refs(benchmark::State &state) {
  static constexpr auto REMOTES{20};
  static constexpr auto SUBSCHEMAS{200};

  auto body{sourcemeta::core::JSON::make_object()};
  for (auto index = 0; index < SUBSCHEMAS; index++) {
    auto subschema{sourcemeta::core::JSON::make_object()};
    subschema.assign("type", sourcemeta::core::JSON{"string"});
    body.assign("property-" + std::to_string(index), std::move(subschema));
  }

  std::map<std::string, sourcemeta::core::JSON> registry;
  auto properties{sourcemeta::core::JSON::make_object()};
  for (auto index = 0; index < REMOTES; index++) {
    const auto identifier{"https://example.com/remote-" +
                          std::to_string(index)};
    auto remote{sourcemeta::core::JSON::make_object()};
    remote.assign(
        "$schema",
        sourcemeta::core::JSON{"https://json-schema.org/draft/2020-12/schema"});
    remote.assign("$id", sourcemeta::core::JSON{identifier});
    remote.assign("properties", body);
    registry.emplace(identifier, std::move(remote));

    auto property{sourcemeta::core::JSON::make_object()};
    property.assign(
        "$ref", sourcemeta::core::JSON{identifier + "#/properties/property-0"});
    properties.assign("from-" + std::to_string(index), std::move(property));
  }

  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign("$schema", sourcemeta::core::JSON{
                               "https://json-schema.org/draft/2020-12/schema"});
  schema.assign("$id", sourcemeta::core::JSON{"https://example.com/main"});
  schema.assign("properties", std::move(properties));

  const auto resolver{[&registry](const std::string_view identifier)
                          -> sourcemeta::blaze::SchemaResolverResult {
    const auto match{registry.find(std::string{identifier})};
    if (match != registry.cend()) {
      return match->second;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  }};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);

  for (auto _ : state) {
    auto result =
        bundle.check(schema, sourcemeta::blaze::schema_walker, resolver,
                     [](const auto &, const auto &, const auto &, const auto &,
                        const auto &) {});
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Alterschema_Check_Readibility_ISO_Language_Set_3);
BENCHMARK(Alterschema_Check_Readibility_OMC);
BENCHMARK(Alterschema_Check_Readibility_KrakenD);
BENCHMARK(Alterschema_Apply_Readibility_KrakenD);
BENCHMARK(Alterschema_Check_Invalid_External_Refs);
BENCHMARK(Alterschema_Check_Resolvable_External_Refs);
