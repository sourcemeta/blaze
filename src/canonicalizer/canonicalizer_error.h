#ifndef SOURCEMETA_BLAZE_CANONICALIZER_ERROR_H_
#define SOURCEMETA_BLAZE_CANONICALIZER_ERROR_H_

#ifndef SOURCEMETA_BLAZE_CANONICALIZER_EXPORT
#include <sourcemeta/blaze/canonicalizer_export.h>
#endif

#include <sourcemeta/core/jsonpointer.h>

#include <exception>   // std::exception
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move

namespace sourcemeta::blaze::canonicalizer {

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif

/// @ingroup canonicalizer
/// An error that represents a broken schema reference after transformation
class SOURCEMETA_BLAZE_CANONICALIZER_EXPORT SchemaBrokenReferenceError
    : public std::exception {
public:
  SchemaBrokenReferenceError(const std::string_view identifier,
                             sourcemeta::core::Pointer schema_location,
                             const char *message)
      : identifier_{identifier}, schema_location_{std::move(schema_location)},
        message_{message} {}

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_;
  }

  [[nodiscard]] auto identifier() const noexcept -> std::string_view {
    return this->identifier_;
  }

  [[nodiscard]] auto location() const noexcept
      -> const sourcemeta::core::Pointer & {
    return this->schema_location_;
  }

private:
  std::string identifier_;
  sourcemeta::core::Pointer schema_location_;
  const char *message_;
};

/// @ingroup canonicalizer
/// An error that signifies that a transform rule was applied more than once
class SOURCEMETA_BLAZE_CANONICALIZER_EXPORT
    SchemaTransformRuleProcessedTwiceError : public std::exception {
public:
  SchemaTransformRuleProcessedTwiceError(const std::string_view name,
                                         sourcemeta::core::Pointer location)
      : name_{name}, location_{std::move(location)} {}

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return "Transformation rules must only be processed once";
  }

  [[nodiscard]] auto name() const noexcept -> std::string_view {
    return this->name_;
  }

  [[nodiscard]] auto location() const noexcept
      -> const sourcemeta::core::Pointer & {
    return this->location_;
  }

private:
  std::string name_;
  sourcemeta::core::Pointer location_;
};

#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif

} // namespace sourcemeta::blaze::canonicalizer

#endif
