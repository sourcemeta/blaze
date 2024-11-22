#ifndef SOURCEMETA_JSONTOOLKIT_REGEX_H_
#define SOURCEMETA_JSONTOOLKIT_REGEX_H_

#ifndef SOURCEMETA_JSONTOOLKIT_REGEX_EXPORT
#include <sourcemeta/jsontoolkit/regex_export.h>
#endif

#include <sourcemeta/jsontoolkit/json.h>

#include <cstdint>  // std::uint8_t, std::uint64_t
#include <optional> // std::optional
#include <regex>    // std::regex
#include <utility>  // std::pair
#include <variant>  // std::variant

/// @defgroup regex Regex
/// @brief An ECMA-262 regex library for use with other JSON libraries
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/regex.h>
/// ```

namespace sourcemeta::jsontoolkit {

/// @ingroup regex
using RegexTypeEngine = std::regex;

/// @ingroup regex
using RegexTypePrefix = JSON::String;

/// @ingroup regex
struct RegexTypeNonEmpty {};

/// @ingroup regex
using RegexTypeRange = std::pair<std::uint64_t, std::uint64_t>;

/// @ingroup regex
struct RegexTypeNoop {};

/// @ingroup regex
using Regex = std::variant<RegexTypeEngine, RegexTypePrefix, RegexTypeNonEmpty,
                           RegexTypeRange, RegexTypeNoop>;
#if !defined(DOXYGEN)
// For fast internal dispatching. It must stay in sync with the variant above
enum class RegexIndex : std::uint8_t {
  Engine = 0,
  Prefix,
  NonEmpty,
  Range,
  Noop
};
#endif

/// @ingroup regex
///
/// Compile a regular expression from a string. If the regular expression is
/// invalid, no value is returned. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/regex.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::Regex regex{
///   sourcemeta::jsontoolkit::to_regex("^foo")};
/// assert(regex.has_value());
/// ```
SOURCEMETA_JSONTOOLKIT_REGEX_EXPORT
auto to_regex(const JSON::String &pattern) noexcept -> std::optional<Regex>;

/// @ingroup regex
///
/// Validate a string against a regular expression. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/regex.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::Regex regex{
///   sourcemeta::jsontoolkit::to_regex("^foo")};
/// assert(regex.has_value());
/// assert(sourcemeta::jsontoolkit::matches(regex.value(), "foo bar"));
/// ```
SOURCEMETA_JSONTOOLKIT_REGEX_EXPORT
auto matches(const Regex &regex, const JSON::String &value) -> bool;

} // namespace sourcemeta::jsontoolkit

#endif
