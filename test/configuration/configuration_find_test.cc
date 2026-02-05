#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>

TEST(Configuration_find, file_no_configuration) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "stub-valid.json"};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_FALSE(result.has_value());
}

TEST(Configuration_find, directory_no_configuration) {
  const std::filesystem::path path{TEST_DIRECTORY};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_FALSE(result.has_value());
}

TEST(Configuration_find, unknown_no_configuration) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "xyz"};
  EXPECT_FALSE(std::filesystem::exists(path));
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_FALSE(result.has_value());
}

TEST(Configuration_find, directory_sibling) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "foo"};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), path / "jsonschema.json");
}

TEST(Configuration_find, file_nested) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "foo" / "bar" / "baz.json"};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), base / "foo" / "jsonschema.json");
}

TEST(Configuration_find, unknown_nested) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "foo" / "bar" / "xyz.json"};
  EXPECT_FALSE(std::filesystem::exists(path));
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), base / "foo" / "jsonschema.json");
}
