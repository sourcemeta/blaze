#ifndef SOURCEMETA_BLAZE_CONTRIB_PERF_COUNTERS_H_
#define SOURCEMETA_BLAZE_CONTRIB_PERF_COUNTERS_H_

// Hardware performance counters for the contrib programs. On Linux they come
// from `perf_event_open`, opened as a single group so that every counter
// covers exactly the same span of execution. Elsewhere, or whenever the kernel
// refuses to hand them out, they report as unavailable along with the reason,
// so that callers can carry on with software measurements alone

#if defined(__linux__)
#include <linux/perf_event.h> // perf_event_attr, PERF_*
#include <sys/ioctl.h>        // ioctl
#include <sys/syscall.h>      // SYS_perf_event_open
#include <unistd.h>           // syscall, read, close

#include <cerrno>  // errno, ENOENT, EOPNOTSUPP, ENODEV, EACCES, EPERM
#include <cstring> // std::strerror
#endif

#include <array>       // std::array
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint8_t, std::uint64_t
#include <optional>    // std::optional, std::nullopt
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::to_underlying

enum class PerfCounter : std::uint8_t {
  Cycles = 0,
  Instructions,
  BranchInstructions,
  BranchMisses,
  CacheReferences,
  CacheMisses
};

inline constexpr std::size_t PERF_COUNTER_COUNT{6};

// Must stay in sync with the ordering of the enumeration above
inline constexpr std::array<std::string_view, PERF_COUNTER_COUNT>
    PERF_COUNTER_NAMES{{"cycles", "instructions", "branch_instructions",
                        "branch_misses", "cache_references", "cache_misses"}};

struct PerfCounterSample {
  // A counter that the kernel did not open is absent, which is not the same
  // as having counted zero events
  std::array<std::optional<std::uint64_t>, PERF_COUNTER_COUNT> values;
  std::uint64_t time_enabled_ns;
  std::uint64_t time_running_ns;

  [[nodiscard]] auto at(const PerfCounter counter) const
      -> const std::optional<std::uint64_t> & {
    return this->values[std::to_underlying(counter)];
  }

  // A group that never got onto the hardware counted nothing at all, so its
  // values carry no information
  [[nodiscard]] auto scheduled() const -> bool {
    return this->time_running_ns > 0;
  }

  // The kernel may share the hardware between groups, in which case the
  // values only cover part of the span. They are reported as counted rather
  // than scaled up, as scaling assumes the workload is uniform
  [[nodiscard]] auto multiplexed() const -> bool {
    return this->time_running_ns < this->time_enabled_ns;
  }
};

// The ratio is undefined when either side was not counted or when the
// denominator is zero, which is not the same as a ratio of zero
inline auto perf_ratio(const std::optional<std::uint64_t> &numerator,
                       const std::optional<std::uint64_t> &denominator)
    -> std::optional<double> {
  if (!numerator.has_value() || !denominator.has_value() ||
      denominator.value() == 0) {
    return std::nullopt;
  }

  return static_cast<double>(numerator.value()) /
         static_cast<double>(denominator.value());
}

#if defined(__linux__)
// The plain error message is easy to misread here, as for example a missing
// performance monitoring unit is reported as a missing file
inline auto perf_open_error(const int error) -> std::string {
  std::string result{std::strerror(error)};
  if (error == ENOENT || error == EOPNOTSUPP || error == ENODEV) {
    result += " (the CPU or kernel does not expose this event)";
  } else if (error == EACCES || error == EPERM) {
    result += " (restricted by perf_event_paranoid, seccomp or a missing "
              "CAP_PERFMON capability)";
  }

  return result;
}
#endif

class PerfCounters {
public:
#if defined(__linux__)
  PerfCounters() {
    static constexpr std::array<std::uint64_t, PERF_COUNTER_COUNT> CONFIGS{
        {PERF_COUNT_HW_CPU_CYCLES, PERF_COUNT_HW_INSTRUCTIONS,
         PERF_COUNT_HW_BRANCH_INSTRUCTIONS, PERF_COUNT_HW_BRANCH_MISSES,
         PERF_COUNT_HW_CACHE_REFERENCES, PERF_COUNT_HW_CACHE_MISSES}};

    // Not every machine supports every event, so a counter that fails to
    // open is left out rather than taking the others down with it. The first
    // one that opens leads the group
    for (std::size_t index = 0; index < PERF_COUNTER_COUNT; index++) {
      perf_event_attr attributes{};
      attributes.type = PERF_TYPE_HARDWARE;
      attributes.size = sizeof(perf_event_attr);
      attributes.config = CONFIGS[index];
      attributes.disabled = 1;
      attributes.exclude_kernel = 1;
      attributes.exclude_hv = 1;
      attributes.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID |
                               PERF_FORMAT_TOTAL_TIME_ENABLED |
                               PERF_FORMAT_TOTAL_TIME_RUNNING;
      const auto descriptor{
          syscall(SYS_perf_event_open, &attributes, 0, -1, this->leader_, 0)};
      if (descriptor == -1) {
        this->counter_reasons_[index] = perf_open_error(errno);
        continue;
      }

      const auto file{static_cast<int>(descriptor)};
      if (ioctl(file, PERF_EVENT_IOC_ID, &this->ids_[index]) == -1) {
        this->counter_reasons_[index] = perf_open_error(errno);
        close(file);
        continue;
      }

      this->files_[index] = file;
      if (this->leader_ == -1) {
        this->leader_ = file;
      }
    }

    if (this->leader_ == -1) {
      this->reason_ = "perf_event_open failed for every hardware counter: ";
      this->reason_ += this->counter_reasons_[0];
    }
  }

  ~PerfCounters() {
    // Close the group members before the leader
    for (const auto file : this->files_) {
      if (file != -1 && file != this->leader_) {
        close(file);
      }
    }

    if (this->leader_ != -1) {
      close(this->leader_);
    }
  }
#else
  PerfCounters() : reason_{"Hardware counters require Linux perf_event_open"} {
    for (auto &reason : this->counter_reasons_) {
      reason = this->reason_;
    }
  }

  ~PerfCounters() = default;
#endif

  PerfCounters(const PerfCounters &) = delete;
  auto operator=(const PerfCounters &) -> PerfCounters & = delete;
  PerfCounters(PerfCounters &&) = delete;
  auto operator=(PerfCounters &&) -> PerfCounters & = delete;

  // Whether at least one counter opened
  [[nodiscard]] auto available() const -> bool {
#if defined(__linux__)
    return this->leader_ != -1;
#else
    return false;
#endif
  }

  // Why no counter at all is available, empty otherwise
  [[nodiscard]] auto unavailable_reason() const -> std::string_view {
    return this->reason_;
  }

  // Why a specific counter is not available, empty otherwise
  [[nodiscard]] auto unavailable_reason(const PerfCounter counter) const
      -> std::string_view {
    return this->counter_reasons_[std::to_underlying(counter)];
  }

  // Reset and enable the whole group at once
  auto start() -> bool {
#if defined(__linux__)
    if (this->leader_ == -1 ||
        ioctl(this->leader_, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
      return false;
    }

    // Resetting zeroes the counts but not the enabled and running times,
    // which keep accumulating since the group was opened. The group is still
    // disabled here, so its times are frozen and can serve as the baseline
    const auto baseline{this->read_group()};
    if (!baseline.has_value()) {
      return false;
    }

    this->baseline_enabled_ns_ = baseline->time_enabled_ns;
    this->baseline_running_ns_ = baseline->time_running_ns;
    return ioctl(this->leader_, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) !=
           -1;
#else
    return false;
#endif
  }

  auto stop() -> bool {
#if defined(__linux__)
    return this->leader_ != -1 && ioctl(this->leader_, PERF_EVENT_IOC_DISABLE,
                                        PERF_IOC_FLAG_GROUP) != -1;
#else
    return false;
#endif
  }

  // The values counted between the last start and stop
  [[nodiscard]] auto sample() const -> std::optional<PerfCounterSample> {
#if defined(__linux__)
    auto result{this->read_group()};
    if (result.has_value()) {
      result->time_enabled_ns -= this->baseline_enabled_ns_;
      result->time_running_ns -= this->baseline_running_ns_;
      // A group that never got onto the hardware reads as zero, which would
      // otherwise pass for having counted zero events
      if (!result->scheduled()) {
        result->values.fill(std::nullopt);
      }
    }

    return result;
#else
    return std::nullopt;
#endif
  }

private:
#if defined(__linux__)
  // The raw group as the kernel reports it, with times since it was opened
  [[nodiscard]] auto read_group() const -> std::optional<PerfCounterSample> {
    if (this->leader_ == -1) {
      return std::nullopt;
    }

    // The group layout is the number of counters, the enabled and running
    // times, and then a value and identifier pair per counter
    constexpr std::size_t HEADER_SIZE{3};
    std::array<std::uint64_t, HEADER_SIZE + 2 * PERF_COUNTER_COUNT> buffer{};
    const auto bytes{read(this->leader_, buffer.data(), sizeof(buffer))};
    if (bytes < static_cast<ssize_t>(HEADER_SIZE * sizeof(std::uint64_t))) {
      return std::nullopt;
    }

    const auto count{buffer[0]};
    if (count > PERF_COUNTER_COUNT ||
        static_cast<std::size_t>(bytes) <
            (HEADER_SIZE + 2 * count) * sizeof(std::uint64_t)) {
      return std::nullopt;
    }

    PerfCounterSample result{.values = {},
                             .time_enabled_ns = buffer[1],
                             .time_running_ns = buffer[2]};
    for (std::size_t entry = 0; entry < count; entry++) {
      const auto value{buffer[HEADER_SIZE + 2 * entry]};
      const auto id{buffer[HEADER_SIZE + 2 * entry + 1]};
      for (std::size_t index = 0; index < PERF_COUNTER_COUNT; index++) {
        if (this->files_[index] != -1 && this->ids_[index] == id) {
          result.values[index] = value;
          break;
        }
      }
    }

    return result;
  }

  int leader_{-1};
  std::array<int, PERF_COUNTER_COUNT> files_{{-1, -1, -1, -1, -1, -1}};
  std::array<std::uint64_t, PERF_COUNTER_COUNT> ids_{};
  std::uint64_t baseline_enabled_ns_{0};
  std::uint64_t baseline_running_ns_{0};
#endif
  std::string reason_;
  std::array<std::string, PERF_COUNTER_COUNT> counter_reasons_;
};

#endif
