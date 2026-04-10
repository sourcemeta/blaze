#ifndef SOURCEMETA_BLAZE_ALTERSCHEMA_ERROR_H_
#define SOURCEMETA_BLAZE_ALTERSCHEMA_ERROR_H_

#ifndef SOURCEMETA_BLAZE_ALTERSCHEMA_EXPORT
#include <sourcemeta/blaze/alterschema_export.h>
#endif

#include <exception>   // std::exception
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::blaze {

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif

/// @ingroup alterschema
/// An error that represents a missing schema rule name
class SOURCEMETA_BLAZE_ALTERSCHEMA_EXPORT SchemaRuleMissingNameError
    : public std::exception {
public:
  [[nodiscard]] auto what() const noexcept -> const char * override {
    return "The schema rule is missing a title";
  }
};

/// @ingroup alterschema
/// An error that represents an invalid schema rule name. The name must
/// consist only of lowercase ASCII letters, digits, underscores, or slashes.
class SOURCEMETA_BLAZE_ALTERSCHEMA_EXPORT SchemaRuleInvalidNameError
    : public std::exception {
public:
  SchemaRuleInvalidNameError(const std::string_view identifier,
                             const char *message)
      : identifier_{identifier}, message_{message} {}
  SchemaRuleInvalidNameError(const std::string_view identifier,
                             std::string message) = delete;
  SchemaRuleInvalidNameError(const std::string_view identifier,
                             std::string &&message) = delete;
  SchemaRuleInvalidNameError(const std::string_view identifier,
                             std::string_view message) = delete;

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return this->message_;
  }

  [[nodiscard]] auto identifier() const noexcept -> const std::string & {
    return this->identifier_;
  }

private:
  std::string identifier_;
  const char *message_;
};

/// @ingroup alterschema
/// An error that represents a schema rule name that does not match
/// the required pattern
class SOURCEMETA_BLAZE_ALTERSCHEMA_EXPORT SchemaRuleInvalidNamePatternError
    : public std::exception {
public:
  SchemaRuleInvalidNamePatternError(const std::string_view identifier,
                                    const std::string_view regex)
      : identifier_{identifier}, regex_{regex} {}

  [[nodiscard]] auto what() const noexcept -> const char * override {
    return "The schema rule name does not match the required pattern";
  }

  [[nodiscard]] auto identifier() const noexcept -> const std::string & {
    return this->identifier_;
  }

  [[nodiscard]] auto regex() const noexcept -> const std::string & {
    return this->regex_;
  }

private:
  std::string identifier_;
  std::string regex_;
};

#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif

} // namespace sourcemeta::blaze

#endif
