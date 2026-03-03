#ifndef SOURCEMETA_BLAZE_EVALUATOR_PROFILING_H_
#define SOURCEMETA_BLAZE_EVALUATOR_PROFILING_H_

#ifdef BLAZE_PROFILING

#include <atomic>  // std::atomic_uint64_t
#include <cstdint> // std::uint64_t
#include <cstdio>  // std::fprintf, stderr
#include <cstdlib> // std::atexit

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) ||             \
    defined(_M_IX86)
#include <x86intrin.h> // __rdtsc
inline auto blaze_rdtsc() -> std::uint64_t { return __rdtsc(); }
#elif defined(__aarch64__) || defined(_M_ARM64)
inline auto blaze_rdtsc() -> std::uint64_t {
  std::uint64_t value;
  __asm__ volatile("mrs %0, cntvct_el0" : "=r"(value));
  return value;
}
#else
#error "BLAZE_PROFILING: unsupported architecture"
#endif

namespace sourcemeta::blaze::profiling {

constexpr std::size_t MAX_INSTRUCTION_TYPES{128};

inline std::atomic_uint64_t dispatch_cycles{0};
inline std::atomic_uint64_t get_target_cycles{0};
inline std::atomic_uint64_t value_access_cycles{0};
inline std::atomic_uint64_t children_loop_cycles{0};
inline std::atomic_uint64_t total_eval_cycles{0};

inline std::atomic_uint64_t instruction_count{0};
inline std::atomic_uint64_t get_empty_count{0};
inline std::atomic_uint64_t get_nonempty_count{0};

// NOLINTNEXTLINE(modernize-avoid-c-arrays)
inline std::atomic_uint64_t instruction_type_count[MAX_INSTRUCTION_TYPES]{};
// NOLINTNEXTLINE(modernize-avoid-c-arrays)
inline std::atomic_uint64_t instruction_type_cycles[MAX_INSTRUCTION_TYPES]{};

inline auto report() -> void {
  const auto total{total_eval_cycles.load()};
  const auto instructions{instruction_count.load()};
  const auto dispatch{dispatch_cycles.load()};
  const auto get_target{get_target_cycles.load()};
  const auto value_access{value_access_cycles.load()};
  const auto children_loop{children_loop_cycles.load()};
  const auto empty{get_empty_count.load()};
  const auto nonempty{get_nonempty_count.load()};
  const auto get_total{empty + nonempty};

  if (instructions == 0) {
    return;
  }

  auto percent = [&](std::uint64_t value) -> double {
    if (total == 0) {
      return 0.0;
    }
    return static_cast<double>(value) * 100.0 / static_cast<double>(total);
  };

  auto per_instr = [&](std::uint64_t value) -> double {
    return static_cast<double>(value) / static_cast<double>(instructions);
  };

  std::fprintf(stderr, "\n=== BLAZE EVALUATOR PROFILE ===\n");
  std::fprintf(stderr, "Instructions executed:  %llu\n",
               static_cast<unsigned long long>(instructions));
  std::fprintf(stderr, "Total eval cycles:      %llu\n",
               static_cast<unsigned long long>(total));

  std::fprintf(stderr, "\n%-20s %-14s %-9s %s\n", "Category", "Cycles",
               "%Total", "Per-Instr");
  std::fprintf(stderr, "%-20s %-14llu %-9.1f %.1f\n", "dispatch",
               static_cast<unsigned long long>(dispatch), percent(dispatch),
               per_instr(dispatch));
  std::fprintf(stderr, "%-20s %-14llu %-9.1f %.1f\n", "get_target",
               static_cast<unsigned long long>(get_target), percent(get_target),
               per_instr(get_target));

  if (get_total > 0) {
    std::fprintf(stderr, "  empty ptrs:       %llu (%llu%%)\n",
                 static_cast<unsigned long long>(empty),
                 static_cast<unsigned long long>(empty * 100 / get_total));
    std::fprintf(stderr, "  non-empty ptrs:   %llu (%llu%%)\n",
                 static_cast<unsigned long long>(nonempty),
                 static_cast<unsigned long long>(nonempty * 100 / get_total));
  }

  std::fprintf(stderr, "%-20s %-14llu %-9.1f %.1f\n", "value_access",
               static_cast<unsigned long long>(value_access),
               percent(value_access), per_instr(value_access));
  std::fprintf(stderr, "%-20s %-14llu %-9.1f %.1f\n", "children_loop",
               static_cast<unsigned long long>(children_loop),
               percent(children_loop), per_instr(children_loop));

  std::fprintf(stderr, "\n--- Per-Instruction-Type Breakdown ---\n");
  std::fprintf(stderr, "%-6s %-14s %-9s %-14s %s\n", "Type#", "Count", "%Count",
               "Cycles(incl)", "Avg-Cyc");
  for (std::size_t index = 0; index < MAX_INSTRUCTION_TYPES; index++) {
    const auto count{instruction_type_count[index].load()};
    if (count == 0) {
      continue;
    }
    const auto cycles{instruction_type_cycles[index].load()};
    const auto count_pct{static_cast<double>(count) * 100.0 /
                         static_cast<double>(instructions)};
    const auto avg_cycles{static_cast<double>(cycles) /
                          static_cast<double>(count)};
    std::fprintf(stderr, "%-6zu %-14llu %-9.1f %-14llu %.1f\n", index,
                 static_cast<unsigned long long>(count), count_pct,
                 static_cast<unsigned long long>(cycles), avg_cycles);
  }

  std::fprintf(stderr, "================================\n");
}

inline auto ensure_reporter_registered() -> void {
  static bool registered{false};
  if (!registered) {
    std::atexit(report);
    registered = true;
  }
}

} // namespace sourcemeta::blaze::profiling

#define BLAZE_PROFILE_START(name)                                              \
  const auto blaze_profile_start_##name{blaze_rdtsc()};

#define BLAZE_PROFILE_END(name, category)                                      \
  sourcemeta::blaze::profiling::category##_cycles.fetch_add(                   \
      blaze_rdtsc() - blaze_profile_start_##name, std::memory_order_relaxed);

#define BLAZE_PROFILE_COUNT(counter)                                           \
  sourcemeta::blaze::profiling::counter.fetch_add(1, std::memory_order_relaxed);

#define BLAZE_PROFILE_INIT                                                     \
  sourcemeta::blaze::profiling::ensure_reporter_registered();

#define BLAZE_PROFILE_COUNT_GET_PTR(location)                                  \
  if ((location).empty()) {                                                    \
    BLAZE_PROFILE_COUNT(get_empty_count)                                       \
  } else {                                                                     \
    BLAZE_PROFILE_COUNT(get_nonempty_count)                                    \
  }

#define BLAZE_PROFILE_DISPATCH(type_index, start_tsc)                          \
  {                                                                            \
    const auto elapsed_{blaze_rdtsc() - (start_tsc)};                          \
    const auto idx_{static_cast<std::size_t>(type_index)};                     \
    sourcemeta::blaze::profiling::instruction_type_count[idx_].fetch_add(      \
        1, std::memory_order_relaxed);                                         \
    sourcemeta::blaze::profiling::instruction_type_cycles[idx_].fetch_add(     \
        elapsed_, std::memory_order_relaxed);                                  \
  }

#else // !BLAZE_PROFILING

#define BLAZE_PROFILE_START(name)
#define BLAZE_PROFILE_END(name, category)
#define BLAZE_PROFILE_COUNT(counter)
#define BLAZE_PROFILE_INIT
#define BLAZE_PROFILE_COUNT_GET_PTR(location)
#define BLAZE_PROFILE_DISPATCH(type_index, start_tsc)

#endif // BLAZE_PROFILING

#endif
