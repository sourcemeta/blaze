#ifndef SOURCEMETA_JSONTOOLKIT_REGEX_H_
#define SOURCEMETA_JSONTOOLKIT_REGEX_H_

#ifndef SOURCEMETA_JSONTOOLKIT_REGEX_EXPORT
#include <sourcemeta/jsontoolkit/regex_export.h>
#endif

#include <sourcemeta/jsontoolkit/json.h>

#include <optional> // std::optional
#include <regex>    // std::regex

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
using Regex = std::regex;

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
///   sourcemeta::jsontoolkit::compile("^foo")};
/// assert(regex.has_value());
/// ```
SOURCEMETA_JSONTOOLKIT_REGEX_EXPORT
auto compile(const JSON::String &pattern) -> std::optional<Regex>;

/// @ingroup regex
///
/// Validate a string against a regular expression. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/regex.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::Regex regex{
///   sourcemeta::jsontoolkit::compile("^foo")};
/// assert(regex.has_value());
/// assert(sourcemeta::jsontoolkit::validate(regex.value(), "foo bar"));
/// ```
SOURCEMETA_JSONTOOLKIT_REGEX_EXPORT
auto validate(const Regex &regex, const JSON::String &value) -> bool;

} // namespace sourcemeta::jsontoolkit

#endif
