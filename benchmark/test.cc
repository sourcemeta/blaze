#include <sourcemeta/core/benchmark.h>

#include <cassert>     // assert
#include <filesystem>  // std::filesystem
#include <functional>  // std::ref
#include <optional>    // std::optional
#include <string_view> // std::string_view

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/test.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

static constexpr std::string_view WOT_IDENTIFIER{
    "https://schemas.sourcemeta.com/w3c/wot/v1.1/thing-description"};

BENCHMARK(TestSuite_Parse_WoT) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "draft7_w3c_wot_td_v1_1.json")};

  const auto resolver{[&schema](const std::string_view identifier)
                          -> sourcemeta::core::SchemaResolverResult {
    if (identifier == WOT_IDENTIFIER) {
      return schema;
    }

    return sourcemeta::core::schema_resolver(identifier);
  }};

  const auto *const input{R"JSON({
    "target": "https://schemas.sourcemeta.com/w3c/wot/v1.1/thing-description",
    "tests": [ { "data": {}, "valid": false } ]
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  // What a target names is the caller's to resolve, bundle and frame, and a
  // runnable suite costs that plus parsing and compiling
  const auto bundled{sourcemeta::core::schema_bundle(
      schema, sourcemeta::core::schema_walker, resolver, "", WOT_IDENTIFIER)};
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      bundled,
      sourcemeta::core::schema_walker,
      resolver,
      "",
      WOT_IDENTIFIER};

  for (auto iteration : state) {
    auto suite{sourcemeta::blaze::TestSuite::parse(
        document, tracker, std::filesystem::path{CURRENT_DIRECTORY},
        [&bundled, &frame](const sourcemeta::core::JSON::String &target)
            -> sourcemeta::blaze::TestTarget {
          return {.document = bundled, .frame = frame, .entrypoint = target};
        },
        resolver, sourcemeta::core::schema_walker,
        sourcemeta::blaze::default_schema_compiler)};
    assert(suite.targets.size() == 1);
    assert(suite.tests.size() == 1);
    sourcemeta::core::benchmark_do_not_optimize(suite);
  }
}
