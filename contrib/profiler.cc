#include <sourcemeta/core/crypto.h>
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonl.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include "perf_counters.h"

// Profile the compilation of a schema and the evaluation of a set of instances
// against it, and report the measurements as a single JSON document. Every
// measurement is taken through public APIs only, so the libraries being
// profiled are exactly the ones that ship. That also means some costs can only
// be attributed coarsely, and the report says so where it matters. Run it from
// a Release build, as the report records whether assertions were enabled. The
// program builds as `sourcemeta_blaze_contrib_profiler`:
//
//   <program> --output report.json schema.json instances.jsonl
//
// The phases run one after the other, so that no instrumentation leaks into a
// measurement it is not part of:
//
// - Compilation: bundling, framing and compiling once, and then compiling
//   again `--compile-iterations` times both plainly and through a keyword
//   compiler that times itself, to report the cost of each keyword along with
//   what that costs
// - Evaluation: a cold pass timing every instance, `--warmup` untimed passes,
//   `--iterations` passes timing every instance, and as many passes timed as
//   a whole, which is closest to how a service validates
// - Trace steps, with `--trace-steps`: a pass with the evaluation callback
//   attached, counting steps by instruction. The callback misses some of the
//   instructions that run, which the report quantifies as its coverage
// - Hardware counters, on Linux when the kernel provides them, around the
//   first compilation, the cold pass, and the whole passes

#include <algorithm>    // std::ranges::sort, std::count, std::max, std::min
#include <array>        // std::array
#include <charconv>     // std::from_chars
#include <chrono>       // std::chrono
#include <concepts>     // std::integral
#include <cstddef>      // std::size_t
#include <cstdint>      // std::int64_t, std::uint64_t
#include <cstdlib>      // EXIT_SUCCESS, EXIT_FAILURE
#include <exception>    // std::exception
#include <filesystem>   // std::filesystem::path
#include <format>       // std::format
#include <fstream>      // std::ifstream, std::ofstream
#include <functional>   // std::less
#include <iostream>     // std::cerr, std::cout
#include <iterator>     // std::size
#include <limits>       // std::numeric_limits
#include <map>          // std::map
#include <numeric>      // std::accumulate
#include <optional>     // std::optional
#include <random>       // std::random_device
#include <sstream>      // std::ostringstream
#include <stdexcept>    // std::runtime_error
#include <string>       // std::string
#include <string_view>  // std::string_view
#include <system_error> // std::errc
#include <utility>      // std::to_underlying
#include <vector>       // std::vector

namespace {

constexpr std::int64_t REPORT_VERSION{1};

using Clock = std::chrono::steady_clock;

constexpr auto INSTRUCTION_TYPES{
    std::size(sourcemeta::blaze::INSTRUCTION_NAMES)};

auto elapsed_ns(const Clock::time_point start, const Clock::time_point end)
    -> std::int64_t {
  return static_cast<std::int64_t>(
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
          .count());
}

// The JSON integer constructors do not agree on which unsigned type a count
// is across platforms, so every integer goes through here
template <std::integral T>
auto integer(const T value) -> sourcemeta::core::JSON {
  return sourcemeta::core::JSON{
      static_cast<sourcemeta::core::JSON::Integer>(value)};
}

auto real_or_null(const std::optional<double> &value)
    -> sourcemeta::core::JSON {
  return value.has_value() ? sourcemeta::core::JSON{value.value()}
                           : sourcemeta::core::JSON{nullptr};
}

auto read_bytes(const std::filesystem::path &path) -> std::string {
  std::ifstream stream{path, std::ios::binary};
  if (!stream) {
    throw std::runtime_error{"Could not open " + path.string()};
  }

  std::ostringstream buffer;
  buffer << stream.rdbuf();
  return buffer.str();
}

/////////////////////////////////////////////////////////////////////
// Summary statistics
/////////////////////////////////////////////////////////////////////

// Percentiles use the nearest-rank method, so they are always one of the
// observed samples rather than an interpolation between two
auto percentile(const std::vector<std::int64_t> &sorted,
                const std::size_t percent) -> std::int64_t {
  const auto rank{
      std::max<std::size_t>(1, (percent * sorted.size() + 99) / 100)};
  return sorted[rank - 1];
}

auto summarize(std::vector<std::int64_t> samples) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("count", integer(samples.size()));
  const auto total{
      std::accumulate(samples.cbegin(), samples.cend(), std::int64_t{0})};
  result.assign("total_ns", integer(total));
  if (samples.empty()) {
    // Nothing was measured, which is not the same as measuring zero
    for (const auto *key :
         {"min_ns", "max_ns", "mean_ns", "p50_ns", "p95_ns", "p99_ns"}) {
      result.assign(key, sourcemeta::core::JSON{nullptr});
    }

    return result;
  }

  std::ranges::sort(samples);
  result.assign("min_ns", integer(samples.front()));
  result.assign("max_ns", integer(samples.back()));
  result.assign("mean_ns",
                sourcemeta::core::JSON{static_cast<double>(total) /
                                       static_cast<double>(samples.size())});
  result.assign("p50_ns", integer(percentile(samples, 50)));
  result.assign("p95_ns", integer(percentile(samples, 95)));
  result.assign("p99_ns", integer(percentile(samples, 99)));
  return result;
}

auto median(std::vector<std::int64_t> samples) -> std::optional<std::int64_t> {
  if (samples.empty()) {
    return std::nullopt;
  }

  std::ranges::sort(samples);
  return percentile(samples, 50);
}

/////////////////////////////////////////////////////////////////////
// Keyword compilation profile
/////////////////////////////////////////////////////////////////////

struct KeywordStatistics {
  std::uint64_t calls{0};
  std::uint64_t calls_without_instructions{0};
  std::uint64_t returned_instructions{0};
  std::int64_t inclusive_ns{0};
  std::int64_t self_ns{0};
};

// Keyword compilers recurse into each other through subschemas, so the time
// of a call is inclusive of every call nested within it. A stack of
// accumulators collects the inclusive time of the direct children of each
// call in flight, which is what gets subtracted to obtain self time
class KeywordProfile {
public:
  // A single keyword compiler call in flight. Construction starts the clock
  // and `finish` stops it. Destruction without `finish` means that the call
  // threw, in which case the frame unwinds anyway so the stack stays balanced
  class Frame {
  public:
    Frame(KeywordProfile &profile, const std::string_view keyword)
        : profile_{profile}, keyword_{keyword} {
      this->profile_.children_.push_back(0);
      this->profile_.max_depth_ =
          std::max(this->profile_.max_depth_, this->profile_.children_.size());
      this->start_ = Clock::now();
    }

    ~Frame() {
      if (!this->finished_) {
        this->profile_.children_.pop_back();
        this->profile_.aborted_ = true;
      }
    }

    Frame(const Frame &) = delete;
    auto operator=(const Frame &) -> Frame & = delete;
    Frame(Frame &&) = delete;
    auto operator=(Frame &&) -> Frame & = delete;

    auto finish(const std::size_t instructions) -> void {
      const auto inclusive{elapsed_ns(this->start_, Clock::now())};
      const auto children{this->profile_.children_.back()};
      this->profile_.children_.pop_back();
      if (this->profile_.children_.empty()) {
        this->profile_.top_level_ns_ += inclusive;
      } else {
        this->profile_.children_.back() += inclusive;
      }

      auto &statistics{this->profile_.at(this->keyword_)};
      statistics.calls += 1;
      if (instructions == 0) {
        statistics.calls_without_instructions += 1;
      }

      statistics.returned_instructions += instructions;
      statistics.inclusive_ns += inclusive;
      statistics.self_ns += inclusive - children;
      this->finished_ = true;
    }

  private:
    KeywordProfile &profile_;
    const std::string_view keyword_;
    Clock::time_point start_;
    bool finished_{false};
  };

  [[nodiscard]] auto keywords() const
      -> const std::map<std::string, KeywordStatistics, std::less<>> & {
    return this->keywords_;
  }

  [[nodiscard]] auto top_level_ns() const -> std::int64_t {
    return this->top_level_ns_;
  }

  [[nodiscard]] auto max_depth() const -> std::size_t {
    return this->max_depth_;
  }

  [[nodiscard]] auto balanced() const -> bool {
    return this->children_.empty() && !this->aborted_;
  }

private:
  auto at(const std::string_view keyword) -> KeywordStatistics & {
    const auto match{this->keywords_.find(keyword)};
    if (match != this->keywords_.end()) {
      return match->second;
    }

    return this->keywords_.emplace(std::string{keyword}, KeywordStatistics{})
        .first->second;
  }

  std::map<std::string, KeywordStatistics, std::less<>> keywords_;
  std::vector<std::int64_t> children_;
  std::int64_t top_level_ns_{0};
  std::size_t max_depth_{0};
  bool aborted_{false};
};

auto profiling_compiler(KeywordProfile &profile)
    -> sourcemeta::blaze::Compiler {
  return [&profile](const sourcemeta::blaze::Context &context,
                    const sourcemeta::blaze::SchemaContext &schema_context,
                    const sourcemeta::blaze::DynamicContext &dynamic_context,
                    const sourcemeta::blaze::Instructions &current)
             -> sourcemeta::blaze::Instructions {
    KeywordProfile::Frame frame{profile, dynamic_context.keyword};
    auto result{sourcemeta::blaze::default_schema_compiler(
        context, schema_context, dynamic_context, current)};
    frame.finish(result.size());
    return result;
  };
}

/////////////////////////////////////////////////////////////////////
// Template statistics
/////////////////////////////////////////////////////////////////////

struct TemplateStatistics {
  std::uint64_t instructions{0};
  std::uint64_t max_depth{0};
  std::array<std::uint64_t, INSTRUCTION_TYPES> by_type{};
  // The children of a fused simple-properties instruction are evaluated with
  // the callback detached, so evaluation tracing never observes them
  std::uint64_t hidden_subtree_roots{0};
  std::uint64_t hidden_instructions{0};
};

auto walk(const sourcemeta::blaze::Instructions &instructions,
          const std::uint64_t depth, const bool hidden,
          TemplateStatistics &statistics) -> void {
  for (const auto &instruction : instructions) {
    statistics.instructions += 1;
    statistics.max_depth = std::max(statistics.max_depth, depth);
    statistics.by_type[std::to_underlying(instruction.type)] += 1;
    if (hidden) {
      statistics.hidden_instructions += 1;
    }

    const auto fused{
        instruction.type ==
        sourcemeta::blaze::InstructionIndex::AssertionObjectPropertiesSimple};
    if (fused && !hidden) {
      statistics.hidden_subtree_roots += 1;
    }

    walk(instruction.children, depth + 1, hidden || fused, statistics);
  }
}

auto template_statistics(const sourcemeta::blaze::Template &schema_template)
    -> TemplateStatistics {
  TemplateStatistics result;
  for (const auto &target : schema_template.targets) {
    walk(target, 1, false, result);
  }

  return result;
}

auto counts_by_type(const std::array<std::uint64_t, INSTRUCTION_TYPES> &counts)
    -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  for (std::size_t index = 0; index < INSTRUCTION_TYPES; index++) {
    if (counts[index] > 0) {
      result.assign(std::string{sourcemeta::blaze::INSTRUCTION_NAMES[index]},
                    integer(counts[index]));
    }
  }

  return result;
}

/////////////////////////////////////////////////////////////////////
// Hardware counters
/////////////////////////////////////////////////////////////////////

auto counters_to_json(const PerfCounters &counters,
                      const std::optional<PerfCounterSample> &sample,
                      const std::string_view scope) -> sourcemeta::core::JSON {
  if (!sample.has_value()) {
    return sourcemeta::core::JSON{nullptr};
  }

  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("scope", sourcemeta::core::JSON{scope});
  result.assign("scheduled", sourcemeta::core::JSON{sample->scheduled()});
  result.assign("multiplexed", sourcemeta::core::JSON{sample->multiplexed()});
  result.assign("time_enabled_ns", integer(sample->time_enabled_ns));
  result.assign("time_running_ns", integer(sample->time_running_ns));
  auto values{sourcemeta::core::JSON::make_object()};
  auto unavailable{sourcemeta::core::JSON::make_object()};
  for (std::size_t index = 0; index < PERF_COUNTER_COUNT; index++) {
    const auto counter{static_cast<PerfCounter>(index)};
    const std::string name{PERF_COUNTER_NAMES[index]};
    const auto &value{sample->at(counter)};
    values.assign(name, value.has_value() ? integer(value.value())
                                          : sourcemeta::core::JSON{nullptr});
    if (!value.has_value()) {
      unavailable.assign(
          name, sourcemeta::core::JSON{counters.unavailable_reason(counter)});
    }
  }

  result.assign("values", std::move(values));
  result.assign("unavailable_counters", std::move(unavailable));
  auto ratios{sourcemeta::core::JSON::make_object()};
  ratios.assign(
      "branch_misses_per_branch_instruction",
      real_or_null(perf_ratio(sample->at(PerfCounter::BranchMisses),
                              sample->at(PerfCounter::BranchInstructions))));
  ratios.assign(
      "cache_misses_per_cache_reference",
      real_or_null(perf_ratio(sample->at(PerfCounter::CacheMisses),
                              sample->at(PerfCounter::CacheReferences))));
  result.assign("ratios", std::move(ratios));
  return result;
}

// Hardware counters only ever surround whole phases, never a single
// instruction or instance, so enabling them does not change what is timed
class CounterScope {
public:
  explicit CounterScope(std::optional<PerfCounters> &counters)
      : counters_{counters} {
    if (this->counters_.has_value()) {
      this->counters_->start();
    }
  }

  auto finish() -> std::optional<PerfCounterSample> {
    if (!this->counters_.has_value()) {
      return std::nullopt;
    }

    this->counters_->stop();
    return this->counters_->sample();
  }

private:
  std::optional<PerfCounters> &counters_;
};

/////////////////////////////////////////////////////////////////////
// Run metadata
/////////////////////////////////////////////////////////////////////

auto run_identifier() -> std::string {
  std::random_device device;
  std::mt19937_64 generator{device()};
  return std::format("{:016x}{:016x}", generator(), generator());
}

auto operating_system() -> std::string_view {
#if defined(__linux__)
  return "linux";
#elif defined(__APPLE__)
  return "darwin";
#elif defined(_WIN32)
  return "windows";
#else
  return "unknown";
#endif
}

auto architecture() -> std::string_view {
#if defined(__x86_64__) || defined(_M_X64)
  return "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
  return "arm64";
#else
  return "unknown";
#endif
}

auto timer_calibration() -> sourcemeta::core::JSON {
  using Period = Clock::period;
  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("clock", sourcemeta::core::JSON{"std::chrono::steady_clock"});
  result.assign("period_ns",
                sourcemeta::core::JSON{static_cast<double>(Period::num) * 1e9 /
                                       static_cast<double>(Period::den)});

  // The smallest step the clock is observed to take, which may be coarser
  // than what its period claims
  constexpr std::size_t RESOLUTION_SAMPLES{100000};
  std::int64_t resolution{std::numeric_limits<std::int64_t>::max()};
  auto previous{Clock::now()};
  for (std::size_t index = 0; index < RESOLUTION_SAMPLES; index++) {
    const auto current{Clock::now()};
    const auto step{elapsed_ns(previous, current)};
    if (step > 0) {
      resolution = std::min(resolution, step);
    }

    previous = current;
  }

  result.assign("observed_resolution_ns",
                resolution == std::numeric_limits<std::int64_t>::max()
                    ? sourcemeta::core::JSON{nullptr}
                    : integer(resolution));

  // Timing an empty region tells apart what two clock reads cost, which is
  // what timing every instance adds to a pass, from what they measure, which
  // is the bias that every per-instance sample carries
  constexpr std::size_t PAIR_SAMPLES{1000000};
  std::int64_t empty_regions{0};
  const auto start{Clock::now()};
  for (std::size_t index = 0; index < PAIR_SAMPLES; index++) {
    const auto begin{Clock::now()};
    empty_regions += elapsed_ns(begin, Clock::now());
  }

  const auto total{elapsed_ns(start, Clock::now())};
  result.assign("mean_timer_pair_ns",
                sourcemeta::core::JSON{static_cast<double>(total) /
                                       static_cast<double>(PAIR_SAMPLES)});
  result.assign("mean_empty_region_ns",
                sourcemeta::core::JSON{static_cast<double>(empty_regions) /
                                       static_cast<double>(PAIR_SAMPLES)});
  return result;
}

// Unlike `std::stoull`, this rejects a negative count rather than wrapping it
// around into an enormous one
auto parse_count(const sourcemeta::core::Options &options,
                 const std::string_view name, const std::uint64_t fallback)
    -> std::uint64_t {
  if (!options.contains(name) || options.at(name).empty()) {
    return fallback;
  }

  const std::string_view value{options.at(name).front()};
  std::uint64_t result{0};
  const auto [end, error]{
      std::from_chars(value.data(), value.data() + value.size(), result)};
  if (error != std::errc{} || end != value.data() + value.size()) {
    throw std::runtime_error{std::format(
        "--{} expects a non-negative integer, got: {}", name, value)};
  }

  return result;
}

} // namespace

auto main(int argc, char **argv) noexcept -> int {
  sourcemeta::core::Options options;
  options.flag("exhaustive", {"e"});
  options.option("dialect", {"d"});
  options.option("warmup", {"w"});
  options.option("iterations", {"i"});
  options.option("compile-iterations", {"c"});
  options.flag("trace-steps", {"t"});
  options.flag("no-hardware-counters", {"n"});
  options.option("output", {"o"});

  try {
    options.parse(argc, argv);
  } catch (const sourcemeta::core::OptionsError &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  const auto &positional{options.positional()};
  if (positional.size() < 2) {
    std::cerr
        << "Usage: " << argv[0]
        << " [--exhaustive] [--dialect <uri>] [--warmup <n>]"
           " [--iterations <n>] [--compile-iterations <n>] [--trace-steps]"
           " [--no-hardware-counters] [--output <report.json>]"
           " <schema.json> <instances.json|instances.jsonl>\n";
    return EXIT_FAILURE;
  }

  try {
    const auto mode{options.contains("exhaustive")
                        ? sourcemeta::blaze::Mode::Exhaustive
                        : sourcemeta::blaze::Mode::FastValidation};
    const std::string default_dialect{options.contains("dialect") &&
                                              !options.at("dialect").empty()
                                          ? options.at("dialect").front()
                                          : ""};
    const auto warmup{parse_count(options, "warmup", 10)};
    const auto iterations{parse_count(options, "iterations", 10)};
    const auto compile_iterations{
        parse_count(options, "compile-iterations", 5)};
    const auto trace_steps{options.contains("trace-steps")};
    const auto hardware_requested{!options.contains("no-hardware-counters")};

    /////////////////////////////////////////////////////////////////
    // Inputs
    /////////////////////////////////////////////////////////////////

    const std::filesystem::path schema_path{positional.at(0)};
    const std::filesystem::path instances_path{positional.at(1)};
    const auto schema{sourcemeta::core::read_json(schema_path)};
    const auto is_jsonl{instances_path.extension() == ".jsonl"};
    std::vector<sourcemeta::core::JSON> instances;
    if (is_jsonl) {
      auto stream{sourcemeta::core::read_file(instances_path)};
      for (const auto &instance : sourcemeta::core::JSONL{stream}) {
        instances.push_back(instance);
      }
    } else {
      instances.push_back(sourcemeta::core::read_json(instances_path));
    }

    std::optional<PerfCounters> counters;
    std::string hardware_reason{"Not requested"};
    if (hardware_requested) {
      counters.emplace();
      if (!counters->available()) {
        hardware_reason = counters->unavailable_reason();
        counters.reset();
      }
    }

    auto hardware_scopes{sourcemeta::core::JSON{nullptr}};

    std::vector<std::string> notes;
    // Calibrate before measuring anything, so that the evaluation can be
    // judged against what the clock is able to resolve
    auto timer{timer_calibration()};
    const auto &resolution{timer.at("observed_resolution_ns")};
    auto report{sourcemeta::core::JSON::make_object()};
    report.assign("report_version", integer(REPORT_VERSION));

    /////////////////////////////////////////////////////////////////
    // Run metadata
    /////////////////////////////////////////////////////////////////

    auto run{sourcemeta::core::JSON::make_object()};
    run.assign("id", sourcemeta::core::JSON{run_identifier()});
    run.assign("timestamp",
               sourcemeta::core::JSON{std::format(
                   "{:%FT%TZ}", std::chrono::floor<std::chrono::seconds>(
                                    std::chrono::system_clock::now()))});
    auto platform{sourcemeta::core::JSON::make_object()};
    platform.assign("os", sourcemeta::core::JSON{operating_system()});
    platform.assign("architecture", sourcemeta::core::JSON{architecture()});
    run.assign("platform", std::move(platform));
    auto build{sourcemeta::core::JSON::make_object()};
#if defined(NDEBUG)
    constexpr bool ASSERTIONS{false};
#else
    constexpr bool ASSERTIONS{true};
    notes.emplace_back("Assertions are enabled, as in a Debug build, so the "
                       "timings do not represent a Release build");
#endif
    build.assign("assertions_enabled", sourcemeta::core::JSON{ASSERTIONS});
#if defined(__OPTIMIZE__)
    build.assign("optimized", sourcemeta::core::JSON{true});
#elif defined(__GNUC__)
    build.assign("optimized", sourcemeta::core::JSON{false});
    notes.emplace_back("The profiler was built without optimisations");
#else
    build.assign("optimized", sourcemeta::core::JSON{nullptr});
#endif
    run.assign("build", std::move(build));
    run.assign("profiling_mode",
               sourcemeta::core::JSON{counters.has_value()
                                          ? "software-and-hardware-counters"
                                          : "software"});
    report.assign("run", std::move(run));

    /////////////////////////////////////////////////////////////////
    // Workload
    /////////////////////////////////////////////////////////////////

    auto workload{sourcemeta::core::JSON::make_object()};
    auto schema_entry{sourcemeta::core::JSON::make_object()};
    schema_entry.assign("path", sourcemeta::core::JSON{schema_path.string()});
    schema_entry.assign("sha256",
                        sourcemeta::core::JSON{
                            sourcemeta::core::sha256(read_bytes(schema_path))});
    workload.assign("schema", std::move(schema_entry));
    auto instances_entry{sourcemeta::core::JSON::make_object()};
    instances_entry.assign("path",
                           sourcemeta::core::JSON{instances_path.string()});
    instances_entry.assign(
        "sha256", sourcemeta::core::JSON{
                      sourcemeta::core::sha256(read_bytes(instances_path))});
    instances_entry.assign("format",
                           sourcemeta::core::JSON{is_jsonl ? "jsonl" : "json"});
    workload.assign("instances", std::move(instances_entry));
    workload.assign("instance_count", integer(instances.size()));
    auto configuration{sourcemeta::core::JSON::make_object()};
    configuration.assign("mode", sourcemeta::core::JSON{
                                     mode == sourcemeta::blaze::Mode::Exhaustive
                                         ? "exhaustive"
                                         : "fast-validation"});
    configuration.assign("default_dialect",
                         default_dialect.empty()
                             ? sourcemeta::core::JSON{nullptr}
                             : sourcemeta::core::JSON{default_dialect});
    configuration.assign("compile_iterations", integer(compile_iterations));
    configuration.assign("warmup_iterations", integer(warmup));
    configuration.assign("measured_iterations", integer(iterations));
    configuration.assign("trace_steps", sourcemeta::core::JSON{trace_steps});
    configuration.assign("hardware_counters_requested",
                         sourcemeta::core::JSON{hardware_requested});
    workload.assign("configuration", std::move(configuration));

    /////////////////////////////////////////////////////////////////
    // Compilation
    /////////////////////////////////////////////////////////////////

    // This is what the convenience overload of the compiler does, split into
    // its phases so that each of them can be timed on its own
    sourcemeta::core::SchemaBundleOptions bundle_options;
    bundle_options.mode =
        sourcemeta::core::SchemaBundleOptions::Mode::References;
    bundle_options.max_locations = std::numeric_limits<std::uint64_t>::max();
    std::optional<sourcemeta::core::JSON> bundled;
    std::optional<sourcemeta::core::SchemaFrame> frame;
    std::optional<sourcemeta::blaze::Template> schema_template;
    std::optional<std::string> compile_error;
    std::int64_t bundle_ns{0};
    std::int64_t frame_ns{0};
    std::int64_t body_ns{0};
    std::optional<PerfCounterSample> compilation_counters;

    // Every compilation below reuses the bundle and the frame of the first
    const auto compile_body{[&](const sourcemeta::blaze::Compiler &compiler) {
      return sourcemeta::blaze::compile(
          bundled.value(), sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver, compiler, frame.value(),
          frame->root(), mode);
    }};

    try {
      CounterScope scope{counters};
      const auto bundle_start{Clock::now()};
      bundled.emplace(sourcemeta::core::schema_bundle(
          schema, sourcemeta::core::schema_walker,
          sourcemeta::core::schema_resolver, default_dialect, "",
          bundle_options));
      const auto frame_start{Clock::now()};
      frame.emplace(sourcemeta::core::SchemaFrame::Mode::References,
                    bundled.value(), sourcemeta::core::schema_walker,
                    sourcemeta::core::schema_resolver, default_dialect, "",
                    sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
                    sourcemeta::core::SchemaFrame::Paths{
                        sourcemeta::core::EMPTY_WEAK_POINTER},
                    "", std::numeric_limits<std::uint64_t>::max());
      const auto body_start{Clock::now()};
      schema_template.emplace(
          compile_body(sourcemeta::blaze::default_schema_compiler));
      const auto body_end{Clock::now()};
      compilation_counters = scope.finish();
      bundle_ns = elapsed_ns(bundle_start, frame_start);
      frame_ns = elapsed_ns(frame_start, body_start);
      body_ns = elapsed_ns(body_start, body_end);
    } catch (const std::exception &error) {
      compile_error = error.what();
    }

    auto compilation{sourcemeta::core::JSON::make_object()};
    compilation.assign("success",
                       sourcemeta::core::JSON{schema_template.has_value()});
    if (!schema_template.has_value()) {
      compilation.assign("error",
                         sourcemeta::core::JSON{compile_error.value_or("")});
      report.assign("workload", std::move(workload));
      report.assign("compilation", std::move(compilation));
      report.assign("evaluation", sourcemeta::core::JSON{nullptr});
    } else {
      // Dialect metadata comes from the frame of the bundled schema
      const auto root_location{frame->traverse(frame->root())};
      workload.assign("dialect",
                      root_location.has_value()
                          ? sourcemeta::core::JSON{root_location->get().dialect}
                          : sourcemeta::core::JSON{nullptr});
      workload.assign("base_dialect",
                      root_location.has_value()
                          ? sourcemeta::core::JSON{std::format(
                                "{}", root_location->get().base_dialect)}
                          : sourcemeta::core::JSON{nullptr});
      report.assign("workload", std::move(workload));

      compilation.assign("wall_time_ns",
                         integer(bundle_ns + frame_ns + body_ns));
      auto phases{sourcemeta::core::JSON::make_object()};
      phases.assign("bundle_ns", integer(bundle_ns));
      phases.assign("frame_ns", integer(frame_ns));
      phases.assign("compile_body_ns", integer(body_ns));
      compilation.assign("phases", std::move(phases));

      const auto statistics{template_statistics(schema_template.value())};
      compilation.assign("template_instruction_count",
                         integer(statistics.instructions));
      compilation.assign("template_target_count",
                         integer(schema_template->targets.size()));
      compilation.assign("template_max_nesting_depth",
                         integer(statistics.max_depth));
      compilation.assign("template_instruction_counts_by_type",
                         counts_by_type(statistics.by_type));
      // There is no honest way to measure this from the outside, as the
      // instructions own heap allocations of many kinds
      compilation.assign("template_size_bytes",
                         sourcemeta::core::JSON{nullptr});
      compilation.assign("template_tracks_evaluation",
                         sourcemeta::core::JSON{schema_template->track});
      compilation.assign("template_uses_dynamic_scopes",
                         sourcemeta::core::JSON{schema_template->dynamic});

      // Repeat the compile body, both plainly and through the profiling
      // compiler, reusing the frame from above. The difference between the
      // two is the cost of profiling keyword compilers
      std::vector<std::int64_t> plain_bodies;
      std::vector<std::int64_t> profiled_bodies;
      std::optional<KeywordProfile> profile;
      std::int64_t profiled_body_ns{0};
      for (std::uint64_t index = 0; index < compile_iterations; index++) {
        const auto plain_start{Clock::now()};
        const auto plain{
            compile_body(sourcemeta::blaze::default_schema_compiler)};
        plain_bodies.push_back(elapsed_ns(plain_start, Clock::now()));

        profile.emplace();
        const auto compiler{profiling_compiler(profile.value())};
        const auto profiled_start{Clock::now()};
        const auto profiled{compile_body(compiler)};
        profiled_body_ns = elapsed_ns(profiled_start, Clock::now());
        profiled_bodies.push_back(profiled_body_ns);
      }

      compilation.assign("compile_body_repeated", summarize(plain_bodies));

      if (profile.has_value()) {
        auto keywords{sourcemeta::core::JSON::make_object()};
        std::int64_t self_total{0};
        bool no_negative_self{true};
        for (const auto &[keyword, entry] : profile->keywords()) {
          auto object{sourcemeta::core::JSON::make_object()};
          object.assign("calls", integer(entry.calls));
          object.assign("calls_without_instructions",
                        integer(entry.calls_without_instructions));
          object.assign("returned_instructions",
                        integer(entry.returned_instructions));
          object.assign("inclusive_ns", integer(entry.inclusive_ns));
          object.assign("self_ns", integer(entry.self_ns));
          keywords.assign(keyword, std::move(object));
          self_total += entry.self_ns;
          no_negative_self = no_negative_self && entry.self_ns >= 0;
        }

        auto keyword_profile{sourcemeta::core::JSON::make_object()};
        keyword_profile.assign("instrumented_compile_body_ns",
                               integer(profiled_body_ns));
        keyword_profile.assign("keyword_compilers_top_level_ns",
                               integer(profile->top_level_ns()));
        keyword_profile.assign(
            "outside_keyword_compilers_ns",
            integer(profiled_body_ns - profile->top_level_ns()));
        keyword_profile.assign("self_ns_total", integer(self_total));
        keyword_profile.assign("max_nesting_depth",
                               integer(profile->max_depth()));
        keyword_profile.assign("keywords", std::move(keywords));

        auto accounting{sourcemeta::core::JSON::make_object()};
        accounting.assign("stack_balanced",
                          sourcemeta::core::JSON{profile->balanced()});
        accounting.assign(
            "self_total_equals_top_level_inclusive",
            sourcemeta::core::JSON{self_total == profile->top_level_ns()});
        accounting.assign("top_level_within_compile_body",
                          sourcemeta::core::JSON{profile->top_level_ns() <=
                                                 profiled_body_ns});
        accounting.assign("no_negative_self_time",
                          sourcemeta::core::JSON{no_negative_self});
        keyword_profile.assign("accounting", std::move(accounting));

        auto overhead{sourcemeta::core::JSON::make_object()};
        const auto plain_median{median(plain_bodies)};
        const auto profiled_median{median(profiled_bodies)};
        overhead.assign("plain_compile_body_median_ns",
                        integer(plain_median.value()));
        overhead.assign("instrumented_compile_body_median_ns",
                        integer(profiled_median.value()));
        overhead.assign("difference_ns", integer(profiled_median.value() -
                                                 plain_median.value()));
        keyword_profile.assign("overhead", std::move(overhead));
        compilation.assign("keyword_profile", std::move(keyword_profile));
      } else {
        compilation.assign("keyword_profile", sourcemeta::core::JSON{nullptr});
      }

      report.assign("compilation", std::move(compilation));

      ///////////////////////////////////////////////////////////////
      // Evaluation
      ///////////////////////////////////////////////////////////////

      sourcemeta::blaze::Evaluator evaluator;
      auto evaluation{sourcemeta::core::JSON::make_object()};
      evaluation.assign("instance_count", integer(instances.size()));

      // The very first pass over the instances, which is the only one that
      // pays for cold caches and branch predictors
      std::vector<bool> expected;
      expected.reserve(instances.size());
      std::vector<std::int64_t> cold_samples;
      cold_samples.reserve(instances.size());
      std::uint64_t marks_total{0};
      std::uint64_t marks_max{0};
      std::optional<PerfCounterSample> cold_counters;
      {
        CounterScope scope{counters};
        for (const auto &instance : instances) {
          const auto start{Clock::now()};
          const auto result{
              evaluator.validate(schema_template.value(), instance)};
          cold_samples.push_back(elapsed_ns(start, Clock::now()));
          expected.push_back(result);
          // Whatever evaluation marks survive a validation are left behind
          // until the next one starts, so they can be read from here
          if (schema_template->track) {
            const auto marks{evaluator.evaluated.size()};
            marks_total += marks;
            marks_max = std::max<std::uint64_t>(marks_max, marks);
          }
        }

        cold_counters = scope.finish();
      }

      const auto valid_count{static_cast<std::uint64_t>(
          std::count(expected.cbegin(), expected.cend(), true))};
      evaluation.assign("valid_count", integer(valid_count));
      evaluation.assign("invalid_count",
                        integer(instances.size() - valid_count));
      evaluation.assign("cold", summarize(cold_samples));

      for (std::uint64_t pass = 0; pass < warmup; pass++) {
        for (const auto &instance : instances) {
          static_cast<void>(
              evaluator.validate(schema_template.value(), instance));
        }
      }

      std::vector<std::int64_t> warm_samples;
      warm_samples.reserve(instances.size() * iterations);
      std::uint64_t mismatches{0};
      for (std::uint64_t pass = 0; pass < iterations; pass++) {
        for (std::size_t index = 0; index < instances.size(); index++) {
          const auto start{Clock::now()};
          const auto result{
              evaluator.validate(schema_template.value(), instances[index])};
          warm_samples.push_back(elapsed_ns(start, Clock::now()));
          if (result != expected[index]) {
            mismatches += 1;
          }
        }
      }

      auto warm_summary{summarize(warm_samples)};
      // A sample only a few clock ticks long says little about its instance
      constexpr std::int64_t COARSE_TICKS{10};
      if (resolution.is_integer() && warm_summary.at("p50_ns").is_integer() &&
          warm_summary.at("p50_ns").to_integer() <
              COARSE_TICKS * resolution.to_integer()) {
        notes.emplace_back(
            "The median warm per-instance sample is within ten ticks of the "
            "clock resolution, so per-instance timings are coarse. Prefer "
            "warm_whole_pass.median_ns_per_instance");
      }

      evaluation.assign("warm_per_instance", std::move(warm_summary));

      // Whole passes with no timer around each instance, which is closest to
      // how a service validates, and shows what per-instance timing costs
      std::vector<std::int64_t> pass_samples;
      std::optional<PerfCounterSample> warm_counters;
      {
        CounterScope scope{counters};
        for (std::uint64_t pass = 0; pass < iterations; pass++) {
          const auto start{Clock::now()};
          for (std::size_t index = 0; index < instances.size(); index++) {
            if (evaluator.validate(schema_template.value(), instances[index]) !=
                expected[index]) {
              mismatches += 1;
            }
          }

          pass_samples.push_back(elapsed_ns(start, Clock::now()));
        }

        warm_counters = scope.finish();
      }

      auto passes{summarize(pass_samples)};
      const auto pass_median{median(pass_samples)};
      passes.assign(
          "median_ns_per_instance",
          pass_median.has_value() && !instances.empty()
              ? sourcemeta::core::JSON{static_cast<double>(
                                           pass_median.value()) /
                                       static_cast<double>(instances.size())}
              : sourcemeta::core::JSON{nullptr});
      evaluation.assign("warm_whole_pass", std::move(passes));
      evaluation.assign(
          "total_wall_time_ns",
          integer(std::accumulate(cold_samples.cbegin(), cold_samples.cend(),
                                  std::int64_t{0}) +
                  std::accumulate(warm_samples.cbegin(), warm_samples.cend(),
                                  std::int64_t{0}) +
                  std::accumulate(pass_samples.cbegin(), pass_samples.cend(),
                                  std::int64_t{0})));
      evaluation.assign("result_mismatches", integer(mismatches));
      if (mismatches > 0) {
        notes.emplace_back("Repeated validations disagreed with the first "
                           "one, which must never happen");
      }

      if (schema_template->track) {
        auto marks{sourcemeta::core::JSON::make_object()};
        marks.assign("total", integer(marks_total));
        marks.assign("max", integer(marks_max));
        evaluation.assign("final_evaluation_marks", std::move(marks));
      } else {
        evaluation.assign("final_evaluation_marks",
                          sourcemeta::core::JSON{nullptr});
      }

      ///////////////////////////////////////////////////////////////
      // Trace steps
      ///////////////////////////////////////////////////////////////

      if (trace_steps) {
        std::array<std::uint64_t, INSTRUCTION_TYPES> steps{};
        const sourcemeta::blaze::Callback callback{
            [&steps](const sourcemeta::blaze::EvaluationType type, const bool,
                     const sourcemeta::blaze::Instruction &instruction,
                     const sourcemeta::blaze::InstructionExtra &,
                     const sourcemeta::core::WeakPointer &,
                     const sourcemeta::core::WeakPointer &,
                     const sourcemeta::core::JSON &) -> void {
              if (type == sourcemeta::blaze::EvaluationType::Pre) {
                steps[std::to_underlying(instruction.type)] += 1;
              }
            }};

        std::uint64_t trace_mismatches{0};
        const auto trace_start{Clock::now()};
        for (std::size_t index = 0; index < instances.size(); index++) {
          if (evaluator.validate(schema_template.value(), instances[index],
                                 callback) != expected[index]) {
            trace_mismatches += 1;
          }
        }

        const auto trace_ns{elapsed_ns(trace_start, Clock::now())};
        std::uint64_t total_steps{0};
        for (const auto count : steps) {
          total_steps += count;
        }

        auto trace{sourcemeta::core::JSON::make_object()};
        trace.assign("definition",
                     sourcemeta::core::JSON{
                         "Evaluation callback steps of type Pre, one per "
                         "instruction that applied to its instance, over one "
                         "pass of every instance. These are not CPU "
                         "instructions and not every executed instruction"});
        trace.assign("passes", integer(1));
        trace.assign("total", integer(total_steps));
        trace.assign("by_type", counts_by_type(steps));
        trace.assign("wall_time_ns", integer(trace_ns));
        trace.assign("result_mismatches", integer(trace_mismatches));

        auto coverage{sourcemeta::core::JSON::make_object()};
        coverage.assign("complete", sourcemeta::core::JSON{
                                        statistics.hidden_subtree_roots == 0});
        coverage.assign("hidden_subtree_roots",
                        integer(statistics.hidden_subtree_roots));
        coverage.assign("hidden_static_instructions",
                        integer(statistics.hidden_instructions));
        auto never_reported{sourcemeta::core::JSON::make_array()};
        for (const auto *name : {"ControlGroup", "ControlGroupWhenDefines",
                                 "ControlGroupWhenDefinesDirect",
                                 "ControlGroupWhenType", "ControlEvaluate"}) {
          never_reported.push_back(sourcemeta::core::JSON{name});
        }

        coverage.assign("never_reported_types", std::move(never_reported));
        trace.assign("coverage", std::move(coverage));
        evaluation.assign("trace_step_counts", std::move(trace));

        notes.emplace_back(
            "trace_step_counts come from a separate pass with the evaluation "
            "callback attached, which takes a slower evaluation path. Its "
            "wall time is not representative of plain validation");
        if (statistics.hidden_subtree_roots > 0) {
          notes.emplace_back(
              "trace_step_counts are incomplete: the children of "
              "AssertionObjectPropertiesSimple, and any targets they jump to, "
              "are evaluated with the callback detached");
        }
        if (trace_mismatches > 0) {
          notes.emplace_back("Validation with the evaluation callback "
                             "disagreed with plain validation");
        }
      } else {
        evaluation.assign("trace_step_counts", sourcemeta::core::JSON{nullptr});
      }

      report.assign("evaluation", std::move(evaluation));

      if (counters.has_value()) {
        auto &scopes{hardware_scopes};
        scopes = sourcemeta::core::JSON::make_object();
        scopes.assign("compilation",
                      counters_to_json(counters.value(), compilation_counters,
                                       "bundle, frame and compile body of "
                                       "the first compilation"));
        scopes.assign("evaluation_cold",
                      counters_to_json(counters.value(), cold_counters,
                                       "first pass over every instance, with "
                                       "a timer around each"));
        scopes.assign("evaluation_warm",
                      counters_to_json(counters.value(), warm_counters,
                                       "every warm whole pass, with no "
                                       "per-instance timer"));
      }
    }

    /////////////////////////////////////////////////////////////////
    // Hardware counter availability
    /////////////////////////////////////////////////////////////////

    auto hardware{sourcemeta::core::JSON::make_object()};
    hardware.assign("requested", sourcemeta::core::JSON{hardware_requested});
    hardware.assign("available", sourcemeta::core::JSON{counters.has_value()});
    hardware.assign("unavailable_reason",
                    counters.has_value()
                        ? sourcemeta::core::JSON{nullptr}
                        : sourcemeta::core::JSON{hardware_reason});
    hardware.assign("scopes", std::move(hardware_scopes));

    report.assign("hardware_counters", std::move(hardware));
    report.assign("timer", std::move(timer));

    notes.emplace_back(
        "Keyword self_ns includes the glue that compiles the keywords of "
        "nested subschemas and any timer overhead of nested calls. "
        "outside_keyword_compilers_ns is derived as the instrumented compile "
        "body minus top-level keyword time, and covers reference planning, "
        "unevaluated dependency analysis, postprocessing and top-level glue");
    notes.emplace_back("Keywords that share a name across dialects are "
                       "aggregated together");
    notes.emplace_back("Per-instance timings include the cost of two clock "
                       "reads, see timer.mean_timer_pair_ns");
    auto notes_json{sourcemeta::core::JSON::make_array()};
    for (const auto &note : notes) {
      notes_json.push_back(sourcemeta::core::JSON{note});
    }

    report.assign("notes", std::move(notes_json));

    if (options.contains("output") && !options.at("output").empty()) {
      const std::filesystem::path output_path{options.at("output").front()};
      std::ofstream output{output_path};
      sourcemeta::core::prettify(report, output);
      output << "\n";
      output.close();
      if (!output) {
        throw std::runtime_error{"Could not write the report to " +
                                 output_path.string()};
      }
    } else {
      sourcemeta::core::prettify(report, std::cout);
      std::cout << "\n";
    }

    return schema_template.has_value() ? EXIT_SUCCESS : EXIT_FAILURE;
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }
}
