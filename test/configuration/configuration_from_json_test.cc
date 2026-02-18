#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/uri.h>

#define EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(                            \
    input, base, expected_message, expected_location)                          \
  try {                                                                        \
    (void)sourcemeta::blaze::Configuration::from_json((input), (base));        \
    FAIL() << "The function was expected to throw";                            \
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {          \
    EXPECT_STREQ(error.what(), (expected_message));                            \
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),                   \
              (expected_location));                                            \
  } catch (...) {                                                              \
    FAIL() << "The function was expected to throw a parse error";              \
  }

TEST(Configuration_from_json, valid_1) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Sourcemeta",
    "description": "The JSON Schema company",
    "email": "hello@sourcemeta.com",
    "github": "sourcemeta",
    "website": "https://www.sourcemeta.com",
    "baseUri": "https://schemas.sourcemeta.com",
    "path": "./schemas",
    "defaultDialect": "http://json-schema.org/draft-07/schema#",
    "resolve": {
      "https://other.com/single.json": "../single.json"
    }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

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
  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::path{TEST_DIRECTORY} / "schemas");
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

TEST(Configuration_from_json, valid_2) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "./schemas"
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_FALSE(manifest.title.has_value());
  EXPECT_FALSE(manifest.description.has_value());
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::path{TEST_DIRECTORY} / "schemas");
  EXPECT_EQ(
      manifest.base,
      sourcemeta::core::URI::from_path(manifest.absolute_path).recompose());
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.extension.size(), 3);
  EXPECT_TRUE(manifest.extension.contains(".json"));
  EXPECT_TRUE(manifest.extension.contains(".yml"));
  EXPECT_TRUE(manifest.extension.contains(".yaml"));
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(Configuration_from_json, valid_3) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "/foo/bar/schemas"
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_FALSE(manifest.title.has_value());
  EXPECT_FALSE(manifest.description.has_value());
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_TRUE(manifest.absolute_path.is_absolute());
  EXPECT_EQ(
      manifest.base,
      sourcemeta::core::URI::from_path(manifest.absolute_path).recompose());
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(Configuration_from_json, valid_4) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "/foo/bar/schemas",
    "x-foo": "bar"
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_FALSE(manifest.title.has_value());
  EXPECT_FALSE(manifest.description.has_value());
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_TRUE(manifest.absolute_path.is_absolute());
  EXPECT_EQ(
      manifest.base,
      sourcemeta::core::URI::from_path(manifest.absolute_path).recompose());
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 1);
  EXPECT_TRUE(manifest.extra.defines("x-foo"));
  EXPECT_TRUE(manifest.extra.at("x-foo").is_string());
  EXPECT_EQ(manifest.extra.at("x-foo").to_string(), "bar");
}

TEST(Configuration_from_json, valid_without_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Test Project"
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Test Project");
  EXPECT_FALSE(manifest.description.has_value());
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_EQ(manifest.absolute_path, TEST_DIRECTORY);
  EXPECT_EQ(
      manifest.base,
      sourcemeta::core::URI::from_path(manifest.absolute_path).recompose());
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.extension.size(), 3);
  EXPECT_TRUE(manifest.extension.contains(".json"));
  EXPECT_TRUE(manifest.extension.contains(".yml"));
  EXPECT_TRUE(manifest.extension.contains(".yaml"));
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(Configuration_from_json, valid_extension_with_leading_dot) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "extension": [ ".json", ".schema" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.extension.size(), 2);
  EXPECT_TRUE(manifest.extension.contains(".json"));
  EXPECT_TRUE(manifest.extension.contains(".schema"));
}

TEST(Configuration_from_json, valid_extension_without_leading_dot) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "extension": [ "json", "schema" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.extension.size(), 2);
  EXPECT_TRUE(manifest.extension.contains(".json"));
  EXPECT_TRUE(manifest.extension.contains(".schema"));
}

TEST(Configuration_from_json, invalid_1) {
  const auto input{sourcemeta::core::parse_json("[]")};
  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The configuration must be an object", "");
}

TEST(Configuration_from_json, invalid_2) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The title property must be a string", "/title");
}

TEST(Configuration_from_json, invalid_3) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "description": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The description property must be a string",
      "/description");
}

TEST(Configuration_from_json, invalid_4) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "email": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The email property must be a string", "/email");
}

TEST(Configuration_from_json, invalid_5) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "github": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The github property must be a string", "/github");
}

TEST(Configuration_from_json, invalid_6) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "website": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The website property must be a string",
      "/website");
}

TEST(Configuration_from_json, invalid_7) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The path property must be a string", "/path");
}

TEST(Configuration_from_json, invalid_8) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The baseUri property must be a string",
      "/baseUri");
}

TEST(Configuration_from_json, invalid_9) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "defaultDialect": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The defaultDialect property must be a string",
      "/defaultDialect");
}

TEST(Configuration_from_json, invalid_10) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The resolve property must be an object",
      "/resolve");
}

TEST(Configuration_from_json, invalid_11) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "foo": 1
    }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The values in the resolve object must be strings",
      "/resolve/foo");
}

TEST(Configuration_from_json, invalid_12) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "%"
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The baseUri property must represent a valid URI",
      "/baseUri");
}

TEST(Configuration_from_json, invalid_13) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "relative"
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The baseUri property must be an absolute URI",
      "/baseUri");
}

TEST(Configuration_from_json, invalid_14) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "foo": "%"
    }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "The values in the resolve object must represent valid URIs",
      "/resolve/foo");
}

TEST(Configuration_from_json, valid_extension_string_with_leading_dot) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "extension": ".schema"
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.extension.size(), 1);
  EXPECT_TRUE(manifest.extension.contains(".schema"));
}

TEST(Configuration_from_json, valid_extension_string_without_leading_dot) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "extension": "schema"
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.extension.size(), 1);
  EXPECT_TRUE(manifest.extension.contains(".schema"));
}

TEST(Configuration_from_json, invalid_15) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "extension": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "The extension property must be a string or an array", "/extension");
}

TEST(Configuration_from_json, invalid_16) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "extension": [ "json", 1 ]
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "The values in the extension array must be strings", "/extension/1");
}

// For backwards compatibility when we add new fields
TEST(Configuration_from_json, unknown_field_ignored) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Test Project",
    "unknown": 1
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Test Project");
  EXPECT_FALSE(manifest.description.has_value());
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_EQ(manifest.absolute_path, TEST_DIRECTORY);
  EXPECT_EQ(
      manifest.base,
      sourcemeta::core::URI::from_path(manifest.absolute_path).recompose());
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(Configuration_from_json, dependencies_empty) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {}
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.dependencies.size(), 0);
}

TEST(Configuration_from_json, dependencies_single) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.dependencies.size(), 1);
  EXPECT_TRUE(manifest.dependencies.contains(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_EQ(
      manifest.dependencies.at("https://json-schema.org/draft/2020-12/schema"),
      std::filesystem::path{TEST_DIRECTORY} / "vendor" / "2020-12.json");
}

TEST(Configuration_from_json, dependencies_multiple) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json",
      "https://example.com/common.json": "./vendor/common.json"
    }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.dependencies.size(), 2);
  EXPECT_TRUE(manifest.dependencies.contains(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_EQ(
      manifest.dependencies.at("https://json-schema.org/draft/2020-12/schema"),
      std::filesystem::path{TEST_DIRECTORY} / "vendor" / "2020-12.json");
  EXPECT_TRUE(
      manifest.dependencies.contains("https://example.com/common.json"));
  EXPECT_EQ(manifest.dependencies.at("https://example.com/common.json"),
            std::filesystem::path{TEST_DIRECTORY} / "vendor" / "common.json");
}

TEST(Configuration_from_json, dependencies_resolved_from_config_location) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "./foo/bar",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "foo" / "bar"));
  EXPECT_EQ(manifest.dependencies.size(), 1);
  EXPECT_TRUE(manifest.dependencies.contains(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_EQ(
      manifest.dependencies.at("https://json-schema.org/draft/2020-12/schema"),
      std::filesystem::path{TEST_DIRECTORY} / "vendor" / "2020-12.json");
}

TEST(Configuration_from_json, dependencies_not_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": []
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The dependencies property must be an object",
      "/dependencies");
}

TEST(Configuration_from_json, dependencies_value_not_string) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {
      "https://example.com/schema.json": 123
    }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "The values in the dependencies object must be strings",
      "/dependencies/https:~1~1example.com~1schema.json");
}

TEST(Configuration_from_json, dependencies_duplicate_paths) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {
      "https://example.com/first.json": "./vendor/schema.json",
      "https://example.com/second.json": "./vendor/schema.json"
    }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "Multiple dependencies cannot point to the same path",
      "/dependencies/https:~1~1example.com~1first.json");
}

TEST(Configuration_from_json, dependencies_invalid_uri_key) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {
      "%": "./vendor/schema.json"
    }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(input, TEST_DIRECTORY,
                                             "The dependency URI is not valid",
                                             "/dependencies/%");
}

TEST(Configuration_from_json, dependencies_with_resolve) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "resolve": {
      "https://internal.corp/foo.json": "./local/foo.json"
    },
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.resolve.size(), 1);
  EXPECT_TRUE(manifest.resolve.contains("https://internal.corp/foo.json"));
  EXPECT_EQ(manifest.resolve.at("https://internal.corp/foo.json"),
            "local/foo.json");
  EXPECT_EQ(manifest.dependencies.size(), 1);
  EXPECT_TRUE(manifest.dependencies.contains(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_EQ(
      manifest.dependencies.at("https://json-schema.org/draft/2020-12/schema"),
      std::filesystem::path{TEST_DIRECTORY} / "vendor" / "2020-12.json");
}

TEST(Configuration_from_json, lint_empty_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": {}
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.lint.rules.empty());
}

TEST(Configuration_from_json, lint_rules_empty) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": [] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.lint.rules.empty());
}

TEST(Configuration_from_json, lint_rules_single) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": [ "./rules/my-rule.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.lint.rules.size(), 1);
  EXPECT_TRUE(manifest.lint.rules[0].is_absolute());
  EXPECT_EQ(manifest.lint.rules[0], std::filesystem::weakly_canonical(
                                        std::filesystem::path{TEST_DIRECTORY} /
                                        "rules" / "my-rule.json"));
}

TEST(Configuration_from_json, lint_rules_multiple) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": [ "./rules/a.json", "./rules/b.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.lint.rules.size(), 2);
  EXPECT_TRUE(manifest.lint.rules[0].is_absolute());
  EXPECT_TRUE(manifest.lint.rules[1].is_absolute());
  EXPECT_EQ(manifest.lint.rules[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "rules" / "a.json"));
  EXPECT_EQ(manifest.lint.rules[1],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "rules" / "b.json"));
}

TEST(Configuration_from_json, lint_rules_absolute_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": [ "/absolute/path/rule.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.lint.rules.size(), 1);
  EXPECT_TRUE(manifest.lint.rules[0].is_absolute());
  EXPECT_EQ(manifest.lint.rules[0], std::filesystem::weakly_canonical(
                                        std::filesystem::path{TEST_DIRECTORY} /
                                        "/absolute/path/rule.json"));
}

TEST(Configuration_from_json, lint_rules_with_other_fields) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    },
    "lint": { "rules": [ "./rules/my-rule.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Test");
  EXPECT_EQ(manifest.dependencies.size(), 1);
  EXPECT_EQ(manifest.lint.rules.size(), 1);
  EXPECT_EQ(manifest.lint.rules[0], std::filesystem::weakly_canonical(
                                        std::filesystem::path{TEST_DIRECTORY} /
                                        "rules" / "my-rule.json"));
}

TEST(Configuration_from_json, lint_rules_resolved_from_config_location) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "./foo/bar",
    "lint": { "rules": [ "./rules/my-rule.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "foo" / "bar"));
  EXPECT_EQ(manifest.lint.rules.size(), 1);
  EXPECT_TRUE(manifest.lint.rules[0].is_absolute());
  EXPECT_EQ(manifest.lint.rules[0], std::filesystem::weakly_canonical(
                                        std::filesystem::path{TEST_DIRECTORY} /
                                        "rules" / "my-rule.json"));
}

TEST(Configuration_from_json,
     lint_rules_multiple_resolved_from_config_location) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "./foo/bar",
    "lint": { "rules": [ "./rules/a.json", "./rules/b.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "foo" / "bar"));
  EXPECT_EQ(manifest.lint.rules.size(), 2);
  EXPECT_EQ(manifest.lint.rules[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "rules" / "a.json"));
  EXPECT_EQ(manifest.lint.rules[1],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "rules" / "b.json"));
}

TEST(Configuration_from_json, lint_not_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The lint property must be an object", "/lint");
}

TEST(Configuration_from_json, lint_rules_not_array) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": 1 }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The lint rules property must be an array",
      "/lint/rules");
}

TEST(Configuration_from_json, lint_rules_element_not_string) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": [ 1 ] }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "The values in the lint rules array must be strings", "/lint/rules/0");
}

TEST(Configuration_from_json, lint_rules_mixed_types) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "lint": { "rules": [ "./a.json", 2 ] }
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY,
      "The values in the lint rules array must be strings", "/lint/rules/1");
}

TEST(Configuration_from_json, ignore_empty) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": []
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.ignore.empty());
}

TEST(Configuration_from_json, ignore_single) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": [ "./vendor" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.ignore.size(), 1);
  EXPECT_TRUE(manifest.ignore[0].is_absolute());
  EXPECT_EQ(manifest.ignore[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "vendor"));
}

TEST(Configuration_from_json, ignore_multiple) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": [ "./vendor", "./build" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.ignore.size(), 2);
  EXPECT_TRUE(manifest.ignore[0].is_absolute());
  EXPECT_TRUE(manifest.ignore[1].is_absolute());
  EXPECT_EQ(manifest.ignore[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "vendor"));
  EXPECT_EQ(manifest.ignore[1],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "build"));
}

TEST(Configuration_from_json, ignore_absolute_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": [ "/absolute/path/vendor" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.ignore.size(), 1);
  EXPECT_TRUE(manifest.ignore[0].is_absolute());
  EXPECT_EQ(manifest.ignore[0], std::filesystem::weakly_canonical(
                                    std::filesystem::path{TEST_DIRECTORY} /
                                    "/absolute/path/vendor"));
}

TEST(Configuration_from_json, ignore_with_other_fields) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    },
    "ignore": [ "./vendor" ],
    "lint": { "rules": [ "./rules/my-rule.json" ] }
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Test");
  EXPECT_EQ(manifest.dependencies.size(), 1);
  EXPECT_EQ(manifest.ignore.size(), 1);
  EXPECT_EQ(manifest.ignore[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "vendor"));
  EXPECT_EQ(manifest.lint.rules.size(), 1);
}

TEST(Configuration_from_json, ignore_resolved_from_config_location) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "./foo/bar",
    "ignore": [ "./vendor" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "foo" / "bar"));
  EXPECT_EQ(manifest.ignore.size(), 1);
  EXPECT_TRUE(manifest.ignore[0].is_absolute());
  EXPECT_EQ(manifest.ignore[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "vendor"));
}

TEST(Configuration_from_json, ignore_multiple_resolved_from_config_location) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "path": "./foo/bar",
    "ignore": [ "./vendor", "./build" ]
  })JSON")};

  const auto manifest{
      sourcemeta::blaze::Configuration::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "foo" / "bar"));
  EXPECT_EQ(manifest.ignore.size(), 2);
  EXPECT_EQ(manifest.ignore[0],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "vendor"));
  EXPECT_EQ(manifest.ignore[1],
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "build"));
}

TEST(Configuration_from_json, ignore_not_array) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": 1
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The ignore property must be an array", "/ignore");
}

TEST(Configuration_from_json, ignore_element_not_string) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": [ 1 ]
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The values in the ignore array must be strings",
      "/ignore/0");
}

TEST(Configuration_from_json, ignore_mixed_types) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "ignore": [ "./vendor", 2 ]
  })JSON")};

  EXPECT_CONFIGURATION_FROM_JSON_PARSE_ERROR(
      input, TEST_DIRECTORY, "The values in the ignore array must be strings",
      "/ignore/1");
}
