#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonl.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

// This is just a convenience script to run validation under a profiler,
// without the additional overhead of Google Benchmark.

#include <chrono>     // std::chrono
#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem::path
#include <iostream>   // std::cerr
#include <vector>     // std::vector

auto main(int argc, char **argv) noexcept -> int {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << " <schema.json> <instance.json> [--warmup]\n";
    return EXIT_FAILURE;
  }

  // Get the schema
  const auto schema{sourcemeta::core::read_json(argv[1])};
  std::cerr << "Compiling schema\n";
  const auto compile_start{std::chrono::high_resolution_clock::now()};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  const auto compile_end{std::chrono::high_resolution_clock::now()};
  const auto compile_duration{
      std::chrono::duration_cast<std::chrono::milliseconds>(compile_end -
                                                            compile_start)};

  std::cerr << compile_duration.count() << "ms\n";

  // Get the instance/s
  const std::filesystem::path instance_path{argv[2]};
  std::vector<sourcemeta::core::JSON> instances;
  if (instance_path.extension() == ".jsonl") {
    std::cerr << "Interpreting instance as JSONL\n";
    auto stream{sourcemeta::core::read_file(instance_path)};
    for (const auto &instance : sourcemeta::core::JSONL{stream}) {
      instances.push_back(instance);
    }
  } else {
    instances.push_back(sourcemeta::core::read_json(instance_path));
  }
  std::cerr << "Number of instances: " << instances.size() << "\n";

  // Validate and measure
  sourcemeta::blaze::Evaluator evaluator;

  if (argc > 3 && std::string{argv[3]} == "--warmup") {
    std::cerr << "Warming up...\n";
    for (std::size_t count = 0; count < 1000000; count++) {
      for (const auto &instance : instances) {
        const auto result{evaluator.validate(schema_template, instance)};
        if (!result) {
          return EXIT_FAILURE;
        }
      }
    }
  }

  std::size_t cursor{0};
  for (const auto &instance : instances) {
    cursor += 1;
    const auto timestamp_start{std::chrono::high_resolution_clock::now()};
    const auto result{evaluator.validate(schema_template, instance)};
    const auto timestamp_end{std::chrono::high_resolution_clock::now()};
    const auto duration{std::chrono::duration_cast<std::chrono::nanoseconds>(
        timestamp_end - timestamp_start)};
    std::cout << "#" << cursor << " " << duration.count() << "ns\n";
    if (!result) {
      std::cerr << "Fail to validate instance #" << cursor << "\n";
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
