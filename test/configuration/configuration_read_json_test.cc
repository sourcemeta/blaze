#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>

#include "configuration_test_utils.h"

#include <unordered_map> // std::unordered_map

TEST(Configuration_read_json, valid_1) {
  std::unordered_map<std::string, std::string> files;
  files["/test/blaze.json"] = R"JSON({
    "title": "Sourcemeta",
    "description": "The JSON Schema company",
    "email": "hello@sourcemeta.com",
    "github": "sourcemeta",
    "website": "https://www.sourcemeta.com",
    "path": "./schemas",
    "baseUri": "https://schemas.sourcemeta.com",
    "defaultDialect": "http://json-schema.org/draft-07/schema#",
    "resolve": {
      "https://other.com/single.json": "../single.json"
    }
  })JSON";

  const auto manifest{sourcemeta::blaze::Configuration::read_json(
      "/test/blaze.json", MAKE_READER(files))};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Sourcemeta");
  EXPECT_TRUE(manifest.description.has_value());
  EXPECT_EQ(manifest.description.value(), "The JSON Schema company");
  EXPECT_TRUE(manifest.email.has_value());
  EXPECT_EQ(manifest.email.value(), "hello@sourcemeta.com");
  EXPECT_TRUE(manifest.github.has_value());
  EXPECT_EQ(manifest.github.value(), "sourcemeta");
  EXPECT_TRUE(manifest.website.has_value());
  EXPECT_EQ(manifest.website.value(), "https://www.sourcemeta.com");
  EXPECT_EQ(manifest.absolute_path, std::filesystem::path{"/test"} / "schemas");
  EXPECT_EQ(manifest.base, "https://schemas.sourcemeta.com");
  EXPECT_TRUE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.default_dialect.value(),
            "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(manifest.resolve.size(), 1);
  EXPECT_TRUE(manifest.resolve.contains("https://other.com/single.json"));
  EXPECT_EQ(manifest.resolve.at("https://other.com/single.json"),
            "../single.json");
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(Configuration_read_json, valid_without_path) {
  std::unordered_map<std::string, std::string> files;
  files["/test/blaze.json"] = R"JSON({
    "title": "Test Config Without Path",
    "description": "A test configuration file without a path property",
    "baseUri": "https://example.com"
  })JSON";

  const auto manifest{sourcemeta::blaze::Configuration::read_json(
      "/test/blaze.json", MAKE_READER(files))};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Test Config Without Path");
  EXPECT_TRUE(manifest.description.has_value());
  EXPECT_EQ(manifest.description.value(),
            "A test configuration file without a path property");
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_EQ(manifest.absolute_path, std::filesystem::path{"/test"});
  EXPECT_EQ(manifest.base, "https://example.com");
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 0);
}
