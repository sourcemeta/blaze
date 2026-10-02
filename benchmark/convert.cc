#include <sourcemeta/core/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem

#include <sourcemeta/blaze/convert.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

BENCHMARK(Convert_Draft3_To_2020_12) {
  const auto schema{
      sourcemeta::core::read_json(std::filesystem::path{CURRENT_DIRECTORY} /
                                  "files" / "draft3_upgrade_stress.json")};

  for (auto iteration : state) {
    auto copy = schema;
    sourcemeta::blaze::convert(copy, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::ConvertTarget::Draft202012);
    assert(copy.at("$schema").to_string() ==
           "https://json-schema.org/draft/2020-12/schema");
    assert(copy != schema);
    sourcemeta::core::benchmark_do_not_optimize(copy);
  }
}

BENCHMARK(Convert_201909_To_2020_12_Unevaluated) {
  const auto schema{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2019_09_unevaluated_upgrade_stress.json")};

  for (auto iteration : state) {
    auto copy = schema;
    sourcemeta::blaze::convert(copy, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::ConvertTarget::Draft202012);
    assert(copy.at("$schema").to_string() ==
           "https://json-schema.org/draft/2020-12/schema");
    assert(copy != schema);
    sourcemeta::core::benchmark_do_not_optimize(copy);
  }
}
