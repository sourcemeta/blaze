#ifndef SOURCEMETA_BLAZE_SUITE_COMPATIBILITY_H_
#define SOURCEMETA_BLAZE_SUITE_COMPATIBILITY_H_

#include <cassert>      // assert
#include <charconv>     // std::from_chars
#include <cstdint>      // std::uint32_t
#include <string_view>  // std::string_view
#include <system_error> // std::errc

// Whether a test case that declares the given `compatibility` applies to the
// release under test, as documented in
// vendor/jsonschema-test-suite/validation/README.md. Releases are the numbers
// the suite uses: 3, 4, 6, 7, 2019, 2020, and 9999 for unreleased features.
// The suite omits the property altogether to mean every release, which callers
// handle, as this function takes no empty input
inline auto suite_compatibility(const std::string_view compatibility,
                                const std::uint32_t version) -> bool {
  assert(!compatibility.empty());

  auto result{true};
  [[maybe_unused]] std::uint32_t previous{0};
  std::string_view pending{compatibility};

  while (!pending.empty()) {
    const auto separator{pending.find(',')};
    auto constraint{pending.substr(0, separator)};
    pending = (separator == std::string_view::npos)
                  ? std::string_view{}
                  : pending.substr(separator + 1);
    assert(!constraint.empty());

    const auto maximum{constraint.starts_with("<=")};
    const auto exact{!maximum && constraint.starts_with("=")};
    if (maximum) {
      constraint.remove_prefix(2);
    } else if (exact) {
      constraint.remove_prefix(1);
    }

    std::uint32_t target{0};
    [[maybe_unused]] const auto parsed{std::from_chars(
        constraint.data(), constraint.data() + constraint.size(), target)};
    assert(parsed.ec == std::errc{});
    assert(parsed.ptr == constraint.data() + constraint.size());

    // The algorithm relies on the suite's requirement that constraints come
    // ordered from the smallest release to the largest one, as it stops at the
    // first constraint that covers the release under test
    assert(target >= previous);
    previous = target;

    if (maximum) {
      result = version <= target;
    } else if (exact) {
      result = version == target;
    } else {
      result = version >= target;
    }

    if (version <= target) {
      break;
    }
  }

  return result;
}

#endif
