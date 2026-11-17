#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>

TEST(no_resolve_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://example.com"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.find_resolve("https://example.com/single.json") ==
              nullptr);
}

TEST(identifier_as_the_key_is_spelled) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("https://example.com/single.json")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_spelled_non_canonically) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("HTTPS://Example.com:443/single.json")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(key_spelled_non_canonically) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "HTTPS://Example.com:443/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("https://example.com/single.json")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_without_the_json_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("https://example.com/single")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_with_the_json_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("https://example.com/single.json")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_non_canonical_without_the_json_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("HTTPS://Example.com:443/single")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(both_spellings_declared) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single": "../bare.json",
      "https://example.com/single.json": "../extension.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *bare{config.find_resolve("https://example.com/single")};
  EXPECT_TRUE(bare != nullptr);
  EXPECT_EQ(*bare, "../bare.json");
  const auto *extension{config.find_resolve("https://example.com/single.json")};
  EXPECT_TRUE(extension != nullptr);
  EXPECT_EQ(*extension, "../extension.json");
}

TEST(unknown_identifier) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.find_resolve("https://example.com/other.json") == nullptr);
}

TEST(identifier_that_is_not_a_uri) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(config.find_resolve("%") == nullptr);
}

TEST(identifier_with_a_query_without_the_json_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single.json?version=2": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{
      config.find_resolve("https://example.com/single?version=2")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_with_a_query_with_the_json_extension) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single?version=2": "../single.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{
      config.find_resolve("https://example.com/single.json?version=2")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_with_an_empty_fragment) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://example.com/single": "../single.json",
      "https://example.com/single#.json": "../fragment.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  const auto *match{config.find_resolve("https://example.com/single#")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}
