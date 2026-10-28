#ifndef SOURCEMETA_BLAZE_TRANSFORM_H_
#define SOURCEMETA_BLAZE_TRANSFORM_H_

/// @defgroup transform Transform
/// @brief An interpreter for declarative JSON transformation rules.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/blaze/transform.h>
/// ```
///
/// The language this interpreter reads is still moving, so nothing here is a
/// stable interface yet. It knows nothing about JSON Schema, and every
/// question that reaches into one arrives through the host it is handed

#ifndef SOURCEMETA_BLAZE_TRANSFORM_EXPORT
#include <sourcemeta/blaze/transform_export.h>
#endif

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <exception>   // std::exception
#include <functional>  // std::function
#include <map>         // std::map
#include <string_view> // std::string_view
#include <utility>     // std::pair
#include <vector>      // std::vector

namespace sourcemeta::blaze {

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif

/// @ingroup transform
/// Raised when rule data is not something the interpreter can read
class SOURCEMETA_BLAZE_TRANSFORM_EXPORT TransformError : public std::exception {
public:
  TransformError(const char *const message) : message_{message} {}

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_;
  }

private:
  const char *message_;
};

/// @ingroup transform
/// A term a pattern bound, with where it was found
struct TransformBinding {
  /// The bound term
  sourcemeta::core::JSON value;
  /// Where it was found, relative to the matched term
  sourcemeta::core::Pointer pointer;
};

/// @ingroup transform
/// Every name a pattern bound
using TransformBindings =
    std::map<sourcemeta::core::JSON::String, TransformBinding>;

/// @ingroup transform
/// What a host answers when a rule asks it something. A pattern reads the
/// answer as a verdict and takes anything but `true` for a refusal, while a
/// build places it as the term it is
using TransformHost = std::function<sourcemeta::core::JSON(
    std::string_view, const std::vector<sourcemeta::core::JSON> &)>;

/// @ingroup transform
/// Where a build moved a term, as positions relative to the matched term
using TransformRelocation =
    std::pair<sourcemeta::core::Pointer, sourcemeta::core::Pointer>;

/// @ingroup transform
/// What a build did, beyond rewriting the term
struct TransformTrace {
  /// Where the build moved material
  std::vector<TransformRelocation> relocations;
  /// Subtrees a function produced, whose provenance is unknown
  std::vector<sourcemeta::core::Pointer> opaque;
};

/// @ingroup transform
/// Whether a pattern matches a term, collecting what it bound
SOURCEMETA_BLAZE_TRANSFORM_EXPORT
auto transform_match(const sourcemeta::core::JSON &pattern,
                     const sourcemeta::core::JSON &term,
                     const TransformHost &host, TransformBindings &bindings)
    -> bool;

/// @ingroup transform
/// Whether a pattern matches a term, without requiring the pattern to be
/// positive. The at-least-one-positive rule exists to stop a rule matching
/// every term, which a guard scoped to a term already selected cannot do, so
/// a guard such as a `when` is evaluated through here
SOURCEMETA_BLAZE_TRANSFORM_EXPORT
auto transform_guard(const sourcemeta::core::JSON &pattern,
                     const sourcemeta::core::JSON &term,
                     const TransformHost &host, TransformBindings &bindings)
    -> bool;

/// @ingroup transform
/// Apply a build to a term, returning what it moved
SOURCEMETA_BLAZE_TRANSFORM_EXPORT
auto transform_apply(const sourcemeta::core::JSON &build,
                     sourcemeta::core::JSON &term,
                     const TransformBindings &bindings,
                     const TransformHost &host) -> TransformTrace;

#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif

} // namespace sourcemeta::blaze

#endif
