#include <sourcemeta/jsontoolkit/regex.h>

namespace sourcemeta::jsontoolkit {

auto compile(const JSON::String &pattern) -> std::optional<Regex> {
  try {
    return std::regex{pattern, std::regex::ECMAScript | std::regex::nosubs};
  } catch (const std::regex_error &) {
    return std::nullopt;
  }
}

auto validate(const Regex &regex, const JSON::String &value) -> bool {
  return std::regex_search(value, regex);
}

} // namespace sourcemeta::jsontoolkit
