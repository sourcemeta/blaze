#include <benchmark/benchmark.h>

#include <cassert> // assert
#include <string>  // std::string

#include <sourcemeta/blaze/regex.h>

#define BENCHMARK_REGEX(name, pattern, input)                                  \
  static void name(benchmark::State &state) {                                  \
    const auto regex{sourcemeta::blaze::to_regex<std::string>(pattern)};       \
    assert(regex.has_value());                                                 \
    for (auto _ : state) {                                                     \
      auto result{                                                             \
          sourcemeta::blaze::matches<std::string>(regex.value(), input)};      \
      assert(result);                                                          \
      benchmark::DoNotOptimize(result);                                        \
    }                                                                          \
  }                                                                            \
  BENCHMARK(name);

BENCHMARK_REGEX(Regex_Lower_S_Or_Upper_S_Asterisk, "[\\s\\S]*", "foo")
BENCHMARK_REGEX(Regex_Caret_Lower_S_Or_Upper_S_Asterisk_Dollar, "^[\\s\\S]*$",
                "foo")
BENCHMARK_REGEX(Regex_Period_Asterisk, ".*", "foo")
BENCHMARK_REGEX(Regex_Group_Period_Asterisk_Group, "(.*)", "foo")
BENCHMARK_REGEX(Regex_Period_Plus, ".+", "foo")
BENCHMARK_REGEX(Regex_Period, ".", "foo")
BENCHMARK_REGEX(Regex_Caret_Period_Plus_Dollar, "^.+$", "foo")
BENCHMARK_REGEX(Regex_Caret_Group_Period_Plus_Group_Dollar, "^(.+)$", "foo")
BENCHMARK_REGEX(Regex_Caret_Period_Asterisk_Dollar, "^.*$", "foo")
BENCHMARK_REGEX(Regex_Caret_Group_Period_Asterisk_Group_Dollar, "^(.*)$", "foo")
BENCHMARK_REGEX(Regex_Caret_X_Hyphen, "^x-", "x-foo")
BENCHMARK_REGEX(Regex_Period_Md_Dollar, "\\.md$", "foo.md")
BENCHMARK_REGEX(Regex_Caret_Slash_Period_Asterisk, "^/.*", "/foo/bar")
BENCHMARK_REGEX(Regex_Caret_Period_Range_Dollar, "^.{1,256}$", "foobar")
// As a stress test, it is supposed to have O(2^n) complexity
BENCHMARK_REGEX(Regex_Nested_Backtrack, "^(x+x+)+y$", "xxxxxxxxxxxxxxxxy")
