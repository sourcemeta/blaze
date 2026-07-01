#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/codegen.h>

#include <map>    // std::map
#include <string> // std::string
#include <vector> // std::vector

TEST(prefix_only_no_symbol) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{}, cache),
            "Schema");
}

TEST(single_lowercase_word) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
}

TEST(single_already_capitalized_word) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"Address"}, cache),
            "SchemaAddress");
}

TEST(hyphenated_two_words) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer,
                std::vector<std::string>{"structured-address"}, cache),
            "SchemaStructuredAddress");
}

TEST(hyphenated_three_words) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(
      sourcemeta::blaze::mangle(
          "Schema", pointer, std::vector<std::string>{"very-long-name"}, cache),
      "SchemaVeryLongName");
}

TEST(dot_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"user.profile"},
                                      cache),
            "SchemaUserProfile");
}

TEST(whitespace_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer,
                std::vector<std::string>{"structured address"}, cache),
            "SchemaStructuredAddress");
}

TEST(mixed_separators) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"a-b.c d"}, cache),
            "SchemaABCD");
}

TEST(consecutive_separators) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"a--b"}, cache),
            "SchemaAB");
}

TEST(leading_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"-abc"}, cache),
            "SchemaAbc");
}

TEST(trailing_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"abc-"}, cache),
            "SchemaAbc");
}

TEST(multiple_segments_with_hyphen) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer,
                std::vector<std::string>{"user", "structured-address"}, cache),
            "SchemaUserStructuredAddress");
}

TEST(digit_inside_word) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"line1"}, cache),
            "SchemaLine1");
}

TEST(segment_starting_with_digit) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"2fa"}, cache),
            "Schema_2fa");
}

TEST(digit_after_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"a-2b"}, cache),
            "SchemaA2b");
}

TEST(underscore_preserved) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"foo_bar"}, cache),
            "SchemaFoo_bar");
}

TEST(dollar_preserved) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"$ref"}, cache),
            "Schema$ref");
}

TEST(empty_segment_skipped) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"", "name"}, cache),
            "SchemaName");
}

TEST(segment_of_only_separators) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"---"}, cache),
            "Schema");
}

TEST(acronym_preserved) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"HTTPServer"},
                                      cache),
            "SchemaHTTPServer");
}

TEST(other_characters_dropped_as_boundary) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"foo@bar"}, cache),
            "SchemaFooBar");
}

TEST(collision_same_pointer_returns_same_name) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{"a"};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
}

TEST(collision_different_pointer_gets_prefixed) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer first{"a"};
  const sourcemeta::core::Pointer second{"b"};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", first, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", second, std::vector<std::string>{"address"}, cache),
            "_SchemaAddress");
}
