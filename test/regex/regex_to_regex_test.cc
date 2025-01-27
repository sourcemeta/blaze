#include <gtest/gtest.h>

#include <string>

#include <sourcemeta/blaze/regex.h>

TEST(Regex_to_regex, valid_1) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^foo")};
  EXPECT_TRUE(regex.has_value());
}

TEST(Regex_to_regex, invalid_1) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("(abc")};
  EXPECT_FALSE(regex.has_value());
}
