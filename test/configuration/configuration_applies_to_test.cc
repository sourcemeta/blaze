#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>

TEST(default_extensions) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.json"));
  EXPECT_TRUE(config.applies_to("bar.yaml"));
  EXPECT_TRUE(config.applies_to("baz.yml"));
  EXPECT_FALSE(config.applies_to("qux.schema"));
  EXPECT_FALSE(config.applies_to("no_extension"));
}

TEST(single_extension_match) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": ".json"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.json"));
  EXPECT_TRUE(config.applies_to("/path/to/schema.json"));
}

TEST(single_extension_no_match) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": ".json"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_FALSE(config.applies_to("foo.yaml"));
  EXPECT_FALSE(config.applies_to("foo.schema"));
  EXPECT_FALSE(config.applies_to("no_extension"));
}

TEST(multiple_extensions_match) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": [ ".json", ".yaml", ".yml" ]
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.json"));
  EXPECT_TRUE(config.applies_to("bar.yaml"));
  EXPECT_TRUE(config.applies_to("baz.yml"));
}

TEST(multiple_extensions_no_match) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": [ ".json", ".yaml" ]
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_FALSE(config.applies_to("foo.schema"));
  EXPECT_FALSE(config.applies_to("bar.txt"));
  EXPECT_FALSE(config.applies_to("no_extension"));
}

TEST(double_extension_match) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": ".json"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.schema.json"));
  EXPECT_TRUE(config.applies_to("/path/to/bar.test.json"));
}

TEST(compound_extension_match) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": ".schema.json"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.schema.json"));
  EXPECT_TRUE(config.applies_to("/path/to/bar.schema.json"));
  EXPECT_FALSE(config.applies_to("baz.json"));
  EXPECT_FALSE(config.applies_to("qux.schema.yaml"));
}

TEST(empty_string_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": ""
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_FALSE(config.applies_to("foo.json"));
  EXPECT_FALSE(config.applies_to("bar.yaml"));
  EXPECT_TRUE(config.applies_to("any_file"));
}

TEST(empty_array_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": []
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.json"));
  EXPECT_TRUE(config.applies_to("bar.yaml"));
  EXPECT_TRUE(config.applies_to("any_file"));
}

TEST(array_with_empty_string_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com",
    "extension": [ ".json", "" ]
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.applies_to("foo.json"));
  EXPECT_FALSE(config.applies_to("bar.yaml"));
  EXPECT_TRUE(config.applies_to("any_file"));
}
