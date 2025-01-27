#include <gtest/gtest.h>

#include <string>

#include <sourcemeta/blaze/regex.h>

TEST(Regex_matches, match_true_1) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^foo")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foobar"));
}

TEST(Regex_matches, match_true_2) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^.*$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foobar"));
}

TEST(Regex_matches, match_true_3) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^(.*)$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foobar"));
}

TEST(Regex_matches, match_true_4) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>(".*")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foobar"));
}

TEST(Regex_matches, match_true_5) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>(".+")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foobar"));
}

TEST(Regex_matches, match_true_6) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^/.*")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(
      sourcemeta::blaze::matches<std::string>(regex.value(), "/foo/bar"));
}

TEST(Regex_matches, match_true_7) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^/.*")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "/"));
}

TEST(Regex_matches, match_true_8) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^.{1,256}$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foo"));
}

TEST(Regex_matches, match_true_9) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^.{1,256}$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "f"));
}

TEST(Regex_matches, match_true_10) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^.{1,256}$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(),
                                                      std::string(256, 'x')));
}

TEST(Regex_matches, match_true_11) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^@")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "@foo"));
}

TEST(Regex_matches, match_true_12) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("o$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "foo"));
}

TEST(Regex_matches, match_true_13) {
  const auto regex{
      sourcemeta::blaze::to_regex<std::string>("^[a-z][a-z0-9-_]{1,63}$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(), "abcd"));
}

TEST(Regex_matches, match_true_14) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>(
      "^(?:@[0-9a-z-_.]+\\/)?[a-z][0-9a-z-_.]*$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_TRUE(sourcemeta::blaze::matches<std::string>(regex.value(),
                                                      "@namespace/mypackage"));
}

TEST(Regex_matches, match_false_1) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^foo")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_FALSE(sourcemeta::blaze::matches<std::string>(regex.value(), "bar"));
}

TEST(Regex_matches, match_false_2) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>(".+")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_FALSE(sourcemeta::blaze::matches<std::string>(regex.value(), ""));
}

TEST(Regex_matches, match_false_3) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^/.*")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_FALSE(
      sourcemeta::blaze::matches<std::string>(regex.value(), "foo/bar"));
}

TEST(Regex_matches, match_false_4) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^.{1,256}$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_FALSE(sourcemeta::blaze::matches<std::string>(regex.value(),
                                                       std::string(257, 'x')));
}

TEST(Regex_matches, match_false_5) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("^@")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_FALSE(sourcemeta::blaze::matches<std::string>(regex.value(), "foo"));
}

TEST(Regex_matches, match_false_6) {
  const auto regex{sourcemeta::blaze::to_regex<std::string>("o$")};
  EXPECT_TRUE(regex.has_value());
  EXPECT_FALSE(sourcemeta::blaze::matches<std::string>(regex.value(), "bar"));
}
