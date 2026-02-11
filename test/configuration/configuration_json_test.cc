#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>

#include "configuration_test_utils.h"

#include <unordered_map> // std::unordered_map

TEST(Configuration_json, read_json_valid_1) {
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

TEST(Configuration_json, read_json_valid_without_path) {
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

TEST(Configuration_json, to_json_all_fields) {
  sourcemeta::blaze::Configuration config;
  config.title = "Sourcemeta";
  config.description = "The JSON Schema company";
  config.email = "hello@sourcemeta.com";
  config.github = "sourcemeta";
  config.website = "https://www.sourcemeta.com";
  config.absolute_path = "/test/schemas";
  config.base = "https://schemas.sourcemeta.com";
  config.default_dialect = "http://json-schema.org/draft-07/schema#";
  config.extension = {".json", ".yaml"};
  config.resolve.emplace("https://other.com/single.json", "../single.json");
  config.dependencies.emplace(
      "https://json-schema.org/draft/2020-12/schema",
      std::filesystem::path{"/test/schemas/vendor/2020-12.json"});

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "title": "Sourcemeta",
    "description": "The JSON Schema company",
    "email": "hello@sourcemeta.com",
    "github": "sourcemeta",
    "website": "https://www.sourcemeta.com",
    "path": "/test/schemas",
    "baseUri": "https://schemas.sourcemeta.com",
    "defaultDialect": "http://json-schema.org/draft-07/schema#",
    "extension": [ ".json", ".yaml" ],
    "resolve": {
      "https://other.com/single.json": "../single.json"
    },
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_json, to_json_minimal) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test";
  config.base = "https://example.com";

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": "/test",
    "baseUri": "https://example.com"
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_json, to_json_empty) {
  sourcemeta::blaze::Configuration config;

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_json, to_json_with_extra) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = "/test";
  config.base = "https://example.com";
  config.extra.assign("x-foo", sourcemeta::core::JSON{"bar"});

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": "/test",
    "baseUri": "https://example.com",
    "x-foo": "bar"
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_json, to_json_roundtrip) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Sourcemeta",
    "description": "The JSON Schema company",
    "email": "hello@sourcemeta.com",
    "github": "sourcemeta",
    "website": "https://www.sourcemeta.com",
    "baseUri": "https://schemas.sourcemeta.com",
    "defaultDialect": "http://json-schema.org/draft-07/schema#",
    "path": "/test/schemas",
    "x-foo": "bar"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(Configuration_json, to_json_roundtrip_with_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": "/test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(Configuration_json, to_json_roundtrip_with_multiple_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": "/test",
    "dependencies": {
      "https://example.com/common.json": "./vendor/common.json",
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(Configuration_json, to_json_roundtrip_with_parent_dependency) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": "/test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "../vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(Configuration_json, to_json_roundtrip_path_differs_from_base) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": "/test/schemas",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(Configuration_json, to_json_roundtrip_dependencies_resolve_extra) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": "/test",
    "resolve": {
      "https://other.com/single.json": "../single.json"
    },
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    },
    "x-foo": "bar"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}
