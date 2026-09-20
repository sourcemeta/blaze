#include <sourcemeta/core/benchmark.h>

#include <filesystem> // std::filesystem

#include <sourcemeta/blaze/format.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>

BENCHMARK(Schema_Format_ISO_Language_To_JSON) {
  const auto document{sourcemeta::core::read_json(
      std::filesystem::path{CURRENT_DIRECTORY} / "files" /
      "2020_12_iso_language_2023_set_3.json")};

  for (auto iteration : state) {
    auto schema{document};
    sourcemeta::blaze::format(schema, sourcemeta::core::schema_walker,
                              sourcemeta::core::schema_resolver);
    sourcemeta::core::benchmark_do_not_optimize(schema);
  }
}
