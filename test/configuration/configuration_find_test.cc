#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/configuration.h>

TEST(file_no_configuration) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "stubs"};
  EXPECT_TRUE(std::filesystem::exists(path));
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_FALSE(result.has_value());
}

TEST(directory_no_configuration) {
  const std::filesystem::path path{TEST_DIRECTORY};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_FALSE(result.has_value());
}

TEST(unknown_no_configuration) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "xyz"};
  EXPECT_FALSE(std::filesystem::exists(path));
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_FALSE(result.has_value());
}

TEST(directory_sibling) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "stubs" / "foo"};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), path / "jsonschema.json");
}

TEST(file_nested) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "stubs" / "foo" / "bar" / "baz.json"};
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), base / "stubs" / "foo" / "jsonschema.json");
}

TEST(unknown_nested) {
  const std::filesystem::path base{TEST_DIRECTORY};
  const auto path{base / "stubs" / "foo" / "bar" / "xyz.json"};
  EXPECT_FALSE(std::filesystem::exists(path));
  const auto result{sourcemeta::blaze::Configuration::find(path)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), base / "stubs" / "foo" / "jsonschema.json");
}
