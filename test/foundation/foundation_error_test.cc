#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>

#include <exception>   // std::exception
#include <string>      // std::string
#include <type_traits> // std::is_base_of_v

TEST(schema_error_throw) {
  static_assert(
      std::is_base_of_v<std::exception, sourcemeta::blaze::SchemaError>,
      "Must subclass std::exception");
  auto exception{sourcemeta::blaze::SchemaError("My error")};
  try {
    // Thrown by name on purpose, so that the assertion after the catch can
    // check the original object survived being thrown
    // NOLINTNEXTLINE(cert-err09-cpp,cert-err61-cpp,misc-throw-by-value-catch-by-reference)
    throw exception;
    FAIL();
  } catch (const sourcemeta::blaze::SchemaError &error) {
    EXPECT_STREQ(error.what(), "My error");
  }
  EXPECT_EQ(std::string{exception.what()}, "My error");
}

TEST(resolution_error_throw) {
  static_assert(std::is_base_of_v<std::exception,
                                  sourcemeta::blaze::SchemaResolutionError>,
                "Must subclass std::exception");
  auto exception{sourcemeta::blaze::SchemaResolutionError(
      "https://sourcemeta.com/test", "My error")};
  try {
    // Thrown by name on purpose, so that the assertion after the catch can
    // check the original object survived being thrown
    // NOLINTNEXTLINE(cert-err09-cpp,cert-err61-cpp,misc-throw-by-value-catch-by-reference,bugprone-exception-copy-constructor-throws,cert-err60-cpp)
    throw exception;
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(), "My error");
  }
  EXPECT_EQ(std::string{exception.what()}, "My error");
  EXPECT_EQ(exception.identifier(), "https://sourcemeta.com/test");
}
