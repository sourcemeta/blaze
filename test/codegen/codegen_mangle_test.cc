#include <gtest/gtest.h>

#include <sourcemeta/blaze/codegen.h>

#include <map>    // std::map
#include <string> // std::string
#include <vector> // std::vector

TEST(Codegen_mangle, prefix_only_no_symbol) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{}, cache),
            "Schema");
}

TEST(Codegen_mangle, single_lowercase_word) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
}

TEST(Codegen_mangle, single_already_capitalized_word) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"Address"}, cache),
            "SchemaAddress");
}

TEST(Codegen_mangle, hyphenated_two_words) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer,
                std::vector<std::string>{"structured-address"}, cache),
            "SchemaStructuredAddress");
}

TEST(Codegen_mangle, hyphenated_three_words) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(
      sourcemeta::blaze::mangle(
          "Schema", pointer, std::vector<std::string>{"very-long-name"}, cache),
      "SchemaVeryLongName");
}

TEST(Codegen_mangle, dot_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"user.profile"},
                                      cache),
            "SchemaUserProfile");
}

TEST(Codegen_mangle, whitespace_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer,
                std::vector<std::string>{"structured address"}, cache),
            "SchemaStructuredAddress");
}

TEST(Codegen_mangle, mixed_separators) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"a-b.c d"}, cache),
            "SchemaABCD");
}

TEST(Codegen_mangle, consecutive_separators) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"a--b"}, cache),
            "SchemaAB");
}

TEST(Codegen_mangle, leading_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"-abc"}, cache),
            "SchemaAbc");
}

TEST(Codegen_mangle, trailing_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"abc-"}, cache),
            "SchemaAbc");
}

TEST(Codegen_mangle, multiple_segments_with_hyphen) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer,
                std::vector<std::string>{"user", "structured-address"}, cache),
            "SchemaUserStructuredAddress");
}

TEST(Codegen_mangle, digit_inside_word) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"line1"}, cache),
            "SchemaLine1");
}

TEST(Codegen_mangle, segment_starting_with_digit) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"2fa"}, cache),
            "Schema_2fa");
}

TEST(Codegen_mangle, digit_after_separator) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"a-2b"}, cache),
            "SchemaA2b");
}

TEST(Codegen_mangle, underscore_preserved) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"foo_bar"}, cache),
            "SchemaFoo_bar");
}

TEST(Codegen_mangle, dollar_preserved) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"$ref"}, cache),
            "Schema$ref");
}

TEST(Codegen_mangle, empty_segment_skipped) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"", "name"}, cache),
            "SchemaName");
}

TEST(Codegen_mangle, segment_of_only_separators) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"---"}, cache),
            "Schema");
}

TEST(Codegen_mangle, acronym_preserved) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle("Schema", pointer,
                                      std::vector<std::string>{"HTTPServer"},
                                      cache),
            "SchemaHTTPServer");
}

TEST(Codegen_mangle, other_characters_dropped_as_boundary) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"foo@bar"}, cache),
            "SchemaFooBar");
}

TEST(Codegen_mangle, collision_same_pointer_returns_same_name) {
  std::map<std::string, sourcemeta::core::Pointer> cache;
  const sourcemeta::core::Pointer pointer{"a"};
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
  EXPECT_EQ(sourcemeta::blaze::mangle(
                "Schema", pointer, std::vector<std::string>{"address"}, cache),
            "SchemaAddress");
}

TEST(Codegen_mangle, collision_different_pointer_gets_prefixed) {
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
