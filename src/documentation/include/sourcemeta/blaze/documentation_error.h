#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_ERROR_H_
#define SOURCEMETA_BLAZE_DOCUMENTATION_ERROR_H_

#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_EXPORT
#include <sourcemeta/blaze/documentation_export.h>
#endif

#include <sourcemeta/core/jsonpointer.h>

#include <exception> // std::exception
#include <string>    // std::string
#include <utility>   // std::move

namespace sourcemeta::blaze {

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif

/// @ingroup documentation
///
/// A schema that cannot be described in the table format exactly, with the
/// place in the schema that cannot be described.
class SOURCEMETA_BLAZE_DOCUMENTATION_EXPORT DocumentationError
    : public std::exception {
public:
  DocumentationError(std::string message, sourcemeta::core::Pointer location)
      : message_{std::move(message)}, location_{std::move(location)} {}

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_.c_str();
  }

  /// Where in the schema the trouble is
  [[nodiscard]] auto location() const noexcept
      -> const sourcemeta::core::Pointer & {
    return this->location_;
  }

private:
  std::string message_;
  sourcemeta::core::Pointer location_;
};

} // namespace sourcemeta::blaze

#endif
