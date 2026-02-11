#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/uri.h>

#include <filesystem> // std::filesystem::path

TEST(Configuration_add_dependency, single) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test/schemas";
  config.base = "https://example.com";

  config.add_dependency("https://json-schema.org/draft/2020-12/schema",
                        std::filesystem::path{"/test/vendor/2020-12.json"});

  EXPECT_EQ(config.dependencies.size(), 1);
  EXPECT_TRUE(config.dependencies.contains(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_EQ(
      config.dependencies.at("https://json-schema.org/draft/2020-12/schema"),
      std::filesystem::path{"/test/vendor/2020-12.json"});
}

TEST(Configuration_add_dependency, multiple) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test/schemas";
  config.base = "https://example.com";

  config.add_dependency("https://json-schema.org/draft/2020-12/schema",
                        std::filesystem::path{"/test/vendor/2020-12.json"});
  config.add_dependency("https://example.com/common.json",
                        std::filesystem::path{"/test/vendor/common.json"});

  EXPECT_EQ(config.dependencies.size(), 2);
  EXPECT_TRUE(config.dependencies.contains(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_EQ(
      config.dependencies.at("https://json-schema.org/draft/2020-12/schema"),
      std::filesystem::path{"/test/vendor/2020-12.json"});
  EXPECT_TRUE(config.dependencies.contains("https://example.com/common.json"));
  EXPECT_EQ(config.dependencies.at("https://example.com/common.json"),
            std::filesystem::path{"/test/vendor/common.json"});
}

TEST(Configuration_add_dependency, duplicate_uri) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test/schemas";
  config.base = "https://example.com";

  config.add_dependency("https://json-schema.org/draft/2020-12/schema",
                        std::filesystem::path{"/test/vendor/2020-12.json"});

  try {
    config.add_dependency("https://json-schema.org/draft/2020-12/schema",
                          std::filesystem::path{"/test/vendor/other.json"});
    FAIL() << "The function was expected to throw";
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "The dependency already exists");
    EXPECT_EQ(
        sourcemeta::core::to_string(error.location()),
        "/dependencies/https:~1~1json-schema.org~1draft~12020-12~1schema");
  } catch (...) {
    FAIL() << "The function was expected to throw a parse error";
  }
}

TEST(Configuration_add_dependency, uri_is_canonicalised) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test/schemas";
  config.base = "https://example.com";

  config.add_dependency("HTTP://Example.COM:80/draft/2020-12/schema",
                        std::filesystem::path{"/test/vendor/2020-12.json"});

  EXPECT_EQ(config.dependencies.size(), 1);
  EXPECT_TRUE(
      config.dependencies.contains("http://example.com/draft/2020-12/schema"));
  EXPECT_EQ(config.dependencies.at("http://example.com/draft/2020-12/schema"),
            std::filesystem::path{"/test/vendor/2020-12.json"});
}

TEST(Configuration_add_dependency, duplicate_uri_after_canonicalisation) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test/schemas";
  config.base = "https://example.com";

  config.add_dependency("http://example.com/schema.json",
                        std::filesystem::path{"/test/vendor/first.json"});

  try {
    config.add_dependency("HTTP://Example.COM:80/schema.json",
                          std::filesystem::path{"/test/vendor/second.json"});
    FAIL() << "The function was expected to throw";
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "The dependency already exists");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/http:~1~1example.com~1schema.json");
  } catch (...) {
    FAIL() << "The function was expected to throw a parse error";
  }
}

TEST(Configuration_add_dependency, duplicate_path) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test/schemas";
  config.base = "https://example.com";

  config.add_dependency("https://json-schema.org/draft/2020-12/schema",
                        std::filesystem::path{"/test/vendor/schema.json"});

  try {
    config.add_dependency("https://example.com/other.json",
                          std::filesystem::path{"/test/vendor/schema.json"});
    FAIL() << "The function was expected to throw";
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "Multiple dependencies cannot point to the same path");
    EXPECT_EQ(
        sourcemeta::core::to_string(error.location()),
        "/dependencies/https:~1~1json-schema.org~1draft~12020-12~1schema");
  } catch (...) {
    FAIL() << "The function was expected to throw a parse error";
  }
}
