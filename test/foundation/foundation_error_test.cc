#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>

#include <exception>   // std::exception
#include <string>      // std::string
#include <type_traits> // std::is_base_of_v

TEST(JSONSchema, schema_error_throw) {
  static_assert(
      std::is_base_of_v<std::exception, sourcemeta::blaze::SchemaError>,
      "Must subclass std::exception");
  auto exception{sourcemeta::blaze::SchemaError("My error")};
  EXPECT_THROW(throw exception, sourcemeta::blaze::SchemaError);
  EXPECT_EQ(std::string{exception.what()}, "My error");
}

TEST(JSONSchema, resolution_error_throw) {
  static_assert(std::is_base_of_v<std::exception,
                                  sourcemeta::blaze::SchemaResolutionError>,
                "Must subclass std::exception");
  auto exception{sourcemeta::blaze::SchemaResolutionError(
      "https://sourcemeta.com/test", "My error")};
  EXPECT_THROW(throw exception, sourcemeta::blaze::SchemaResolutionError);
  EXPECT_EQ(std::string{exception.what()}, "My error");
  EXPECT_EQ(exception.identifier(), "https://sourcemeta.com/test");
}
