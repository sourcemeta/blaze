#include <benchmark/benchmark.h>

#include <cassert>     // assert
#include <filesystem>  // std::filesystem
#include <functional>  // std::ref
#include <optional>    // std::optional
#include <string_view> // std::string_view

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

static constexpr std::string_view WOT_IDENTIFIER{
    "https://schemas.sourcemeta.com/w3c/wot/v1.1/thing-description"};

static auto TestSuite_Parse_WoT(benchmark::State &state) -> void {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "draft7_w3c_wot_td_v1_1.json")};

  const auto resolver{[&schema](const std::string_view identifier)
                          -> sourcemeta::blaze::SchemaResolverResult {
    if (identifier == WOT_IDENTIFIER) {
      return schema;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  }};

  const auto input{R"JSON({
    "target": "https://schemas.sourcemeta.com/w3c/wot/v1.1/thing-description",
    "tests": [ { "data": {}, "valid": false } ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  for (auto _ : state) {
    auto suite{sourcemeta::blaze::TestSuite::parse(
        document, tracker, std::filesystem::path{CURRENT_DIRECTORY}, resolver,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::default_schema_compiler)};
    assert(suite.targets.size() == 1);
    assert(suite.tests.size() == 1);
    benchmark::DoNotOptimize(suite);
  }
}

BENCHMARK(TestSuite_Parse_WoT);
