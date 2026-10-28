#ifndef SOURCEMETA_BLAZE_CONVERT_TRANSFORM_H_
#define SOURCEMETA_BLAZE_CONVERT_TRANSFORM_H_

// An interpreter for declarative JSON transformation rules. It is internal to
// this module on purpose: the language is still moving, and keeping it here
// means a change to it and to the rules that exercise it land together. It
// knows nothing about JSON Schema, and the questions that do reach into a
// schema arrive through the predicate and function it is handed

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <exception>   // std::exception
#include <functional>  // std::function
#include <map>         // std::map
#include <string_view> // std::string_view
#include <utility>     // std::pair
#include <vector>      // std::vector

/// Raised when rule data is not something the interpreter can read
class TransformError : public std::exception {
public:
  TransformError(const char *const message) : message_{message} {}

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_;
  }

private:
  const char *message_;
};

/// A term a pattern bound, with where it was found
struct TransformBinding {
  /// The bound term
  sourcemeta::core::JSON value;
  /// Where it was found, relative to the matched term
  sourcemeta::core::Pointer pointer;
};

/// Every name a pattern bound
using TransformBindings =
    std::map<sourcemeta::core::JSON::String, TransformBinding>;

/// What a host answers when a rule asks it something. A pattern reads the
/// answer as a verdict and takes anything but `true` for a refusal, while a
/// build places it as the term it is
using TransformHost = std::function<sourcemeta::core::JSON(
    std::string_view, const std::vector<sourcemeta::core::JSON> &)>;

/// Where a build moved a term, as positions relative to the matched term
using TransformRelocation =
    std::pair<sourcemeta::core::Pointer, sourcemeta::core::Pointer>;

/// What a build did, beyond rewriting the term
struct TransformTrace {
  /// Where the build moved material
  std::vector<TransformRelocation> relocations;
  /// Subtrees a function produced, whose provenance is unknown
  std::vector<sourcemeta::core::Pointer> opaque;
};

/// Whether a pattern matches a term, collecting what it bound
auto transform_match(const sourcemeta::core::JSON &pattern,
                     const sourcemeta::core::JSON &term,
                     const TransformHost &host, TransformBindings &bindings)
    -> bool;

/// Whether a pattern matches a term, without requiring the pattern to be
/// positive. The at-least-one-positive rule exists to stop a rule matching
/// every term, which a guard scoped to a term already selected cannot do, so
/// a guard such as a `when` is evaluated through here
auto transform_guard(const sourcemeta::core::JSON &pattern,
                     const sourcemeta::core::JSON &term,
                     const TransformHost &host, TransformBindings &bindings)
    -> bool;

/// Apply a build to a term, returning what it moved
auto transform_apply(const sourcemeta::core::JSON &build,
                     sourcemeta::core::JSON &term,
                     const TransformBindings &bindings,
                     const TransformHost &host) -> TransformTrace;

#endif
