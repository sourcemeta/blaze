#include <sourcemeta/jsontoolkit/regex.h>

#include <cassert> // assert
#include <string>  // std::stoull

namespace sourcemeta::jsontoolkit {

auto to_regex(const JSON::String &pattern) noexcept -> std::optional<Regex> {
  if (pattern == ".*" || pattern == "^.*$" || pattern == "^(.*)$" ||
      pattern == "(.*)" || pattern == "[\\s\\S]*" || pattern == "^[\\s\\S]*$") {
    return RegexTypeNoop{};
  } else if (pattern == ".+" || pattern == "^.+$" || pattern == "^(.+)$" ||
             pattern == ".") {
    return RegexTypeNonEmpty{};
  }

  try {
    const std::regex PREFIX_REGEX{R"(^\^([a-zA-Z0-9-_/]+)(\.\*)?)"};
    std::smatch matches_prefix;
    if (std::regex_match(pattern, matches_prefix, PREFIX_REGEX)) {
      return RegexTypePrefix{matches_prefix[1].str()};
    }

    const std::regex RANGE_REGEX{R"(^\^\.\{(\d+),(\d+)\}\$$)"};
    std::smatch matches_range;
    if (std::regex_match(pattern, matches_range, RANGE_REGEX)) {
      const std::uint64_t minimum{std::stoull(matches_range[1].str())};
      const std::uint64_t maximum{std::stoull(matches_range[2].str())};
      assert(minimum <= maximum);
      return RegexTypeRange{minimum, maximum};
    }

    return std::regex{pattern, std::regex::ECMAScript | std::regex::nosubs};
  } catch (...) {
    return std::nullopt;
  }
}

auto matches(const Regex &regex, const JSON::String &value) -> bool {
  switch (static_cast<RegexIndex>(regex.index())) {
    case RegexIndex::Engine:
      return std::regex_search(value, std::get<RegexTypeEngine>(regex));
    case RegexIndex::Prefix:
      return value.starts_with(std::get<RegexTypePrefix>(regex));
    case RegexIndex::NonEmpty:
      return !value.empty();
    case RegexIndex::Range:
      return value.size() >= std::get<RegexTypeRange>(regex).first &&
             value.size() <= std::get<RegexTypeRange>(regex).second;
    case RegexIndex::Noop:
      return true;
  }

    // See https://en.cppreference.com/w/cpp/utility/unreachable
#if defined(_MSC_VER) && !defined(__clang__)
  __assume(false);
#else
  __builtin_unreachable();
#endif
}

} // namespace sourcemeta::jsontoolkit
