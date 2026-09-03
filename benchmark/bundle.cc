#include <benchmark/benchmark.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/foundation.h>

#include <map>    // std::map
#include <string> // std::string, std::to_string

static void Schema_Bundle_Meta_2020_12(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto schema{sourcemeta::blaze::schema_resolver(
                    "https://json-schema.org/draft/2020-12/schema")
                    .value()};
    state.ResumeTiming();
    sourcemeta::blaze::bundle(
        schema, sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    benchmark::DoNotOptimize(schema);
  }
}

// Bundling checks that the fragment of a reference names something the remote
// actually has, once per distinct remote that a fragment reaches into
static void Schema_Bundle_Many_Remotes_With_Fragments(benchmark::State &state) {
  static constexpr auto REMOTES{10};
  static constexpr auto SUBSCHEMAS{200};

  auto body{sourcemeta::core::JSON::make_object()};
  for (auto index = 0; index < SUBSCHEMAS; index++) {
    auto subschema{sourcemeta::core::JSON::make_object()};
    subschema.assign("type", sourcemeta::core::JSON{"string"});
    subschema.assign("minLength", sourcemeta::core::JSON{index});
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

  auto document{sourcemeta::core::JSON::make_object()};
  document.assign(
      "$schema",
      sourcemeta::core::JSON{"https://json-schema.org/draft/2020-12/schema"});
  document.assign("$id", sourcemeta::core::JSON{"https://example.com/main"});
  document.assign("properties", std::move(properties));

  const auto resolver{[&registry](const std::string_view identifier)
                          -> sourcemeta::blaze::SchemaResolverResult {
    const auto match{registry.find(std::string{identifier})};
    if (match != registry.cend()) {
      return match->second;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  }};

  for (auto _ : state) {
    state.PauseTiming();
    auto schema{document};
    state.ResumeTiming();
    sourcemeta::blaze::bundle(
        schema, sourcemeta::blaze::schema_walker, resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    benchmark::DoNotOptimize(schema);
  }
}

BENCHMARK(Schema_Bundle_Meta_2020_12);
BENCHMARK(Schema_Bundle_Many_Remotes_With_Fragments);
