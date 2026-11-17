#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/jsonpointer.h>

TEST(single) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("https://example.com/single.json", "../single.json");

  EXPECT_EQ(config.resolve.size(), 1);
  EXPECT_TRUE(config.resolve.contains("https://example.com/single.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/single.json"),
            "../single.json");
}

TEST(multiple) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("https://example.com/single.json", "../single.json");
  config.add_resolve("https://example.com/other.json", "../other.json");

  EXPECT_EQ(config.resolve.size(), 2);
  EXPECT_TRUE(config.resolve.contains("https://example.com/single.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/single.json"),
            "../single.json");
  EXPECT_TRUE(config.resolve.contains("https://example.com/other.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/other.json"),
            "../other.json");
}

TEST(identifier_is_canonicalised) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("HTTPS://Example.com:443/single.json", "../single.json");

  EXPECT_EQ(config.resolve.size(), 1);
  EXPECT_TRUE(config.resolve.contains("https://example.com/single.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/single.json"),
            "../single.json");
}

TEST(target_is_canonicalised) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("https://example.com/single.json",
                     "HTTPS://Example.com:443/single.json");

  EXPECT_EQ(config.resolve.size(), 1);
  EXPECT_TRUE(config.resolve.contains("https://example.com/single.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/single.json"),
            "https://example.com/single.json");
}

TEST(identifier_is_found_however_it_is_spelled) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("HTTPS://Example.com:443/single.json", "../single.json");

  const auto *match{config.find_resolve("https://example.com/single.json")};
  EXPECT_TRUE(match != nullptr);
  EXPECT_EQ(*match, "../single.json");
}

TEST(identifier_invalid_uri) {
  sourcemeta::blaze::Configuration config;

  try {
    config.add_resolve("%", "../single.json");
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The keys in the resolve object must represent valid URIs");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/resolve/%");
  } catch (...) {
    FAIL();
  }

  EXPECT_EQ(config.resolve.size(), 0);
}

TEST(target_invalid_uri) {
  sourcemeta::blaze::Configuration config;

  try {
    config.add_resolve("https://example.com/single.json", "%");
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The values in the resolve object must represent valid URIs");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/resolve/https:~1~1example.com~1single.json");
  } catch (...) {
    FAIL();
  }

  EXPECT_EQ(config.resolve.size(), 0);
}

TEST(duplicate_identifier) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("https://example.com/single.json", "../first.json");

  try {
    config.add_resolve("https://example.com/single.json", "../second.json");
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "Two keys in the resolve object denote the same URI");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/resolve/https:~1~1example.com~1single.json");
  } catch (...) {
    FAIL();
  }

  EXPECT_EQ(config.resolve.size(), 1);
  EXPECT_TRUE(config.resolve.contains("https://example.com/single.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/single.json"),
            "../first.json");
}

TEST(duplicate_identifier_after_canonicalisation_reports_the_identifier_given) {
  sourcemeta::blaze::Configuration config;

  config.add_resolve("https://example.com/single.json", "../first.json");

  try {
    config.add_resolve("HTTPS://Example.com:443/single.json", "../second.json");
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "Two keys in the resolve object denote the same URI");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/resolve/HTTPS:~1~1Example.com:443~1single.json");
  } catch (...) {
    FAIL();
  }

  EXPECT_EQ(config.resolve.size(), 1);
  EXPECT_TRUE(config.resolve.contains("https://example.com/single.json"));
  EXPECT_EQ(config.resolve.at("https://example.com/single.json"),
            "../first.json");
}
