#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonl.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include "perf_counters.h"

#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint64_t
#include <cstdlib>     // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // std::filesystem::path
#include <iostream>    // std::cerr
#include <optional>    // std::optional
#include <string_view> // std::string_view
#include <vector>      // std::vector

auto print_ratio(const std::string_view label,
                 const std::optional<std::uint64_t> &numerator,
                 const std::optional<std::uint64_t> &denominator) -> void {
  std::cerr << label << ": ";
  const auto ratio{perf_ratio(numerator, denominator)};
  if (ratio.has_value()) {
    std::cerr << numerator.value() << "/" << denominator.value() << " = "
              << ratio.value() * 100 << "%\n";
  } else {
    std::cerr << "n/a\n";
  }
}

auto print_counters(const PerfCounters &counters) -> void {
  const auto sample{counters.sample()};
  // The reason they are unavailable is printed once, up front
  if (!sample.has_value()) {
    std::cerr << (counters.available() ? "Hardware counters could not be read\n"
                                       : "Hardware counters unavailable\n");
    return;
  }

  if (!sample->scheduled()) {
    std::cerr << "Hardware counters were never scheduled\n";
    return;
  }

  for (std::size_t index = 0; index < PERF_COUNTER_COUNT; index++) {
    const auto counter{static_cast<PerfCounter>(index)};
    std::cerr << PERF_COUNTER_NAMES[index] << ": ";
    const auto &value{sample->at(counter)};
    if (value.has_value()) {
      std::cerr << value.value() << "\n";
    } else {
      std::cerr << "unavailable (" << counters.unavailable_reason(counter)
                << ")\n";
    }
  }

  print_ratio("cache_misses / cache_references",
              sample->at(PerfCounter::CacheMisses),
              sample->at(PerfCounter::CacheReferences));
  print_ratio("branch_misses / branch_instructions",
              sample->at(PerfCounter::BranchMisses),
              sample->at(PerfCounter::BranchInstructions));

  if (sample->multiplexed()) {
    std::cerr << "Note: multiplexed, counted for " << sample->time_running_ns
              << "ns of " << sample->time_enabled_ns
              << "ns enabled (values not scaled)\n";
  }
}

bool validate_all(auto &evaluator, const auto &instances,
                  const auto &schema_template) {
  for (std::size_t num = 0; num < instances.size(); num++) {
    const auto result{evaluator.validate(schema_template, instances[num])};
    if (!result) {
      std::cerr << "Error validating instance " << num << "\n";
      return false;
    }
  }

  return true;
}

auto main(int argc, char **argv) noexcept -> int {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <schema.json> <instances.jsonl>\n";
    return EXIT_FAILURE;
  }

  const auto schema{sourcemeta::core::read_json(argv[1])};
  const std::filesystem::path instance_path{argv[2]};
  auto stream{sourcemeta::core::read_file(instance_path)};
  std::vector<sourcemeta::core::JSON> instances;
  for (const auto &instance : sourcemeta::core::JSONL{stream}) {
    instances.push_back(instance);
  }

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation)};

  sourcemeta::blaze::Evaluator evaluator;
  PerfCounters counters;
  // Validation still runs without counters, so that the program behaves the
  // same on machines that do not expose them
  if (!counters.available()) {
    std::cerr << "Hardware counters unavailable: "
              << counters.unavailable_reason() << "\n\n";
  }

  counters.start();
  if (!validate_all(evaluator, instances, schema_template)) {
    return EXIT_FAILURE;
  }
  counters.stop();

  std::cerr << "Cold\n==============================\n";
  print_counters(counters);
  std::cerr << "\n";

  for (int i = 0; i < 100; i++) {
    validate_all(evaluator, instances, schema_template);
  }

  counters.start();
  validate_all(evaluator, instances, schema_template);
  counters.stop();

  std::cerr << "Warm\n==============================\n";
  print_counters(counters);
  std::cerr << "\n";

  return EXIT_SUCCESS;
}
