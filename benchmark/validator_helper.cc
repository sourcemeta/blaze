#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonl.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

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
    std::cerr << "Usage: " << argv[0] << " <schema.json> <instance.json>\n";
    return EXIT_FAILURE;
  }

  // Get the schema
  const auto schema{sourcemeta::jsontoolkit::from_file(argv[1])};
  std::cerr << "Compiling schema\n";
  const auto compile_start{std::chrono::high_resolution_clock::now()};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  const auto compile_end{std::chrono::high_resolution_clock::now()};
  const auto compile_duration{
      std::chrono::duration_cast<std::chrono::milliseconds>(compile_end -
                                                            compile_start)};

  const sourcemeta::jsontoolkit::JSON template_json{
      sourcemeta::blaze::to_json(schema_template)};
  sourcemeta::jsontoolkit::prettify(
      template_json, std::cout,
      sourcemeta::blaze::compiler_template_format_compare);
  std::cout << std::endl;

  std::cout << compile_duration.count() << "ms\n";

  // Get the instance/s
  const std::filesystem::path instance_path{argv[2]};
  std::vector<sourcemeta::jsontoolkit::JSON> instances;
  if (instance_path.extension() == ".jsonl") {
    std::cerr << "Interpreting instance as JSONL\n";
    auto stream{sourcemeta::jsontoolkit::read_file(instance_path)};
    for (const auto &instance : sourcemeta::jsontoolkit::JSONL{stream}) {
      instances.push_back(instance);
    }
  } else {
    instances.push_back(sourcemeta::jsontoolkit::from_file(instance_path));
  }
  std::cerr << "Number of instances: " << instances.size() << "\n";

  // Validate and measure
  sourcemeta::blaze::EvaluationContext context;
  const auto timestamp_start{std::chrono::high_resolution_clock::now()};
  std::size_t cursor{0};
  for (const auto &instance : instances) {
    context.prepare(instance);
    cursor += 1;
    const auto result{sourcemeta::blaze::evaluate(schema_template, context)};
    if (!result) {
      std::cerr << "Fail to validate instance #" << cursor << "\n";
      return EXIT_FAILURE;
    }
  }
  const auto timestamp_end{std::chrono::high_resolution_clock::now()};
  const auto duration{std::chrono::duration_cast<std::chrono::nanoseconds>(
      timestamp_end - timestamp_start)};
  std::cout << duration.count() << "ns\n";
  return EXIT_SUCCESS;
}
