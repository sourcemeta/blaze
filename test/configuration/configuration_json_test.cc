#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/uri.h>

#include "configuration_test_utils.h"

#include <unordered_map> // std::unordered_map

// Windows only treats a path as absolute if it carries a root name, and the
// configuration parser canonicalises every path that goes through it
#if defined(_WIN32)
#define ROOT_NAME "C:"
#define ROOT_NAME_URI "file:///C:"
#else
#define ROOT_NAME ""
#define ROOT_NAME_URI "file://"
#endif

TEST(read_json_valid_1) {
  std::unordered_map<std::string, std::string> files;
  files[ROOT_NAME "/test/blaze.json"] = R"JSON({
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
      ROOT_NAME "/test/blaze.json", MAKE_READER(files))};

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
            std::filesystem::path{ROOT_NAME "/test"} / "schemas");
  EXPECT_TRUE(manifest.absolute_path_explicit);
  EXPECT_EQ(manifest.base, "https://schemas.sourcemeta.com");
  EXPECT_EQ(manifest.base_uri.recompose(), "https://schemas.sourcemeta.com");
  EXPECT_TRUE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.default_dialect.value(),
            "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(manifest.resolve.size(), 1);
  EXPECT_TRUE(manifest.resolve.contains("https://other.com/single.json"));
  EXPECT_EQ(manifest.resolve.at("https://other.com/single.json"),
            "../single.json");
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(read_json_valid_without_path) {
  std::unordered_map<std::string, std::string> files;
  files[ROOT_NAME "/test/blaze.json"] = R"JSON({
    "title": "Test Config Without Path",
    "description": "A test configuration file without a path property",
    "baseUri": "https://example.com"
  })JSON";

  const auto manifest{sourcemeta::blaze::Configuration::read_json(
      ROOT_NAME "/test/blaze.json", MAKE_READER(files))};

  EXPECT_TRUE(manifest.title.has_value());
  EXPECT_EQ(manifest.title.value(), "Test Config Without Path");
  EXPECT_TRUE(manifest.description.has_value());
  EXPECT_EQ(manifest.description.value(),
            "A test configuration file without a path property");
  EXPECT_FALSE(manifest.email.has_value());
  EXPECT_FALSE(manifest.github.has_value());
  EXPECT_FALSE(manifest.website.has_value());
  EXPECT_EQ(manifest.absolute_path, std::filesystem::path{ROOT_NAME "/test"});
  EXPECT_FALSE(manifest.absolute_path_explicit);
  EXPECT_EQ(manifest.base, "https://example.com");
  EXPECT_EQ(manifest.base_uri.recompose(), "https://example.com");
  EXPECT_FALSE(manifest.default_dialect.has_value());
  EXPECT_EQ(manifest.resolve.size(), 0);
  EXPECT_EQ(manifest.extra.size(), 0);
}

TEST(read_json_base_uri_defaults_to_absolute_path) {
  std::unordered_map<std::string, std::string> files;
  files[ROOT_NAME "/test/blaze.json"] = R"JSON({
    "path": "./schemas"
  })JSON";

  const auto manifest{sourcemeta::blaze::Configuration::read_json(
      ROOT_NAME "/test/blaze.json", MAKE_READER(files))};

  EXPECT_EQ(manifest.absolute_path,
            std::filesystem::path{ROOT_NAME "/test"} / "schemas");
  EXPECT_TRUE(manifest.absolute_path_explicit);
  EXPECT_EQ(manifest.base, ROOT_NAME_URI "/test/schemas");
  EXPECT_EQ(manifest.base_uri.recompose(), ROOT_NAME_URI "/test/schemas");
}

TEST(to_json_all_fields) {
  sourcemeta::blaze::Configuration config;
  config.title = "Sourcemeta";
  config.description = "The JSON Schema company";
  config.email = "hello@sourcemeta.com";
  config.github = "sourcemeta";
  config.website = "https://www.sourcemeta.com";
  config.absolute_path = ROOT_NAME "/test/schemas";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test/schemas";
  config.base = "https://schemas.sourcemeta.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.default_dialect = "http://json-schema.org/draft-07/schema#";
  config.extension = {".json", ".yaml"};
  config.resolve.emplace("https://other.com/single.json", "../single.json");
  config.dependencies.emplace(
      "https://json-schema.org/draft/2020-12/schema",
      std::filesystem::path{ROOT_NAME "/test/schemas/vendor/2020-12.json"});

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "title": "Sourcemeta",
    "description": "The JSON Schema company",
    "email": "hello@sourcemeta.com",
    "github": "sourcemeta",
    "website": "https://www.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test/schemas",
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

TEST(to_json_minimal) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com"
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_empty) {
  sourcemeta::blaze::Configuration config;

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_extra) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.extra.assign("x-foo", sourcemeta::core::JSON{"bar"});

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "x-foo": "bar"
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_roundtrip) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Sourcemeta",
    "description": "The JSON Schema company",
    "email": "hello@sourcemeta.com",
    "github": "sourcemeta",
    "website": "https://www.sourcemeta.com",
    "baseUri": "https://schemas.sourcemeta.com",
    "defaultDialect": "http://json-schema.org/draft-07/schema#",
    "path": ")JSON" ROOT_NAME R"JSON(/test/schemas",
    "x-foo": "bar"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_without_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "title": "Test Project",
    "baseUri": "https://schemas.sourcemeta.com"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  EXPECT_FALSE(config.absolute_path_explicit);
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_with_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_with_multiple_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "dependencies": {
      "https://example.com/common.json": "./vendor/common.json",
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_with_parent_dependency) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "../vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_path_differs_from_base) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test/schemas",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_dependencies_resolve_extra) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "resolve": {
      "https://other.com/single.json": "../single.json"
    },
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    },
    "x-foo": "bar"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_with_lint_rules) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.rules.emplace_back(ROOT_NAME "/test/rules/my-rule.json");
  config.lint.rules.emplace_back(ROOT_NAME "/test/rules/other-rule.json");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "rules": [ "./rules/my-rule.json", "./rules/other-rule.json" ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_lint_rules_parent) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.rules.emplace_back(ROOT_NAME "/other/rules/my-rule.json");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "rules": [ "../other/rules/my-rule.json" ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_empty_lint) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};

  const auto result{config.to_json()};

  EXPECT_FALSE(result.defines("lint"));
}

TEST(to_json_roundtrip_with_lint_rules) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "rules": [ "./rules/my-rule.json" ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_with_top_level_lint_rule) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.rules.push_back(
      {.path = ROOT_NAME "/test/rules/my-rule.json", .top_level = true});

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "rules": [ { "path": "./rules/my-rule.json", "topLevel": true } ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_mixed_lint_rules) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.rules.push_back(
      {.path = ROOT_NAME "/test/rules/my-rule.json", .top_level = false});
  config.lint.rules.push_back(
      {.path = ROOT_NAME "/test/rules/other-rule.json", .top_level = true});

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "rules": [
        "./rules/my-rule.json",
        { "path": "./rules/other-rule.json", "topLevel": true }
      ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_roundtrip_with_top_level_lint_rule) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "rules": [ { "path": "./rules/my-rule.json", "topLevel": true } ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_object_lint_rule_without_top_level_as_string) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "rules": [ { "path": "./rules/my-rule.json" } ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "rules": [ "./rules/my-rule.json" ]
    }
  })JSON")};

  EXPECT_EQ(output, expected);
}

TEST(to_json_roundtrip_with_lint_and_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "dependencies": {
      "https://json-schema.org/draft/2020-12/schema": "./vendor/2020-12.json"
    },
    "lint": {
      "rules": [ "./rules/my-rule.json" ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_with_lint_exclude) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.exclude.emplace("enum_to_const");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "exclude": [ "enum_to_const" ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_lint_exclude_sorted) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.exclude.emplace("top_level_title");
  config.lint.exclude.emplace("const_not_in_enum");
  config.lint.exclude.emplace("enum_to_const");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "exclude": [ "const_not_in_enum", "enum_to_const", "top_level_title" ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_lint_rules_and_exclude) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.rules.emplace_back(ROOT_NAME "/test/rules/my-rule.json");
  config.lint.exclude.emplace("enum_to_const");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "rules": [ "./rules/my-rule.json" ],
      "exclude": [ "enum_to_const" ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_lint_exclude_duplicates_in_document_emitted_once) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "exclude": [ "enum_to_const", "enum_to_const", "enum_to_const" ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "exclude": [ "enum_to_const" ]
    }
  })JSON")};

  EXPECT_EQ(output, expected);
}

TEST(to_json_roundtrip_with_lint_exclude) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "exclude": [ "enum_to_const", "top_level_title" ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_with_lint_rules_and_exclude) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "lint": {
      "rules": [ "./rules/my-rule.json" ],
      "exclude": [ "enum_to_const" ]
    }
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_empty_lint_exclude_omitted) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.lint.rules.emplace_back(ROOT_NAME "/test/rules/my-rule.json");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "lint": {
      "rules": [ "./rules/my-rule.json" ]
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_ignore) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.ignore.emplace_back(ROOT_NAME "/test/vendor");
  config.ignore.emplace_back(ROOT_NAME "/test/build");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "ignore": [ "./vendor", "./build" ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_with_ignore_parent) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.absolute_path_explicit = true;
  config.base_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};
  config.ignore.emplace_back(ROOT_NAME "/other/vendor");

  const auto result{config.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "path": ")JSON" ROOT_NAME R"JSON(/test",
    "baseUri": "https://example.com",
    "ignore": [ "../other/vendor" ]
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(to_json_empty_ignore) {
  sourcemeta::blaze::Configuration config;
  config.absolute_path = ROOT_NAME "/test";
  config.base = "https://example.com";
  config.base_uri = sourcemeta::core::URI{config.base};

  const auto result{config.to_json()};

  EXPECT_FALSE(result.defines("ignore"));
}

TEST(to_json_roundtrip_with_ignore) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "ignore": [ "./vendor" ],
    "path": ")JSON" ROOT_NAME R"JSON(/test"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}

TEST(to_json_roundtrip_with_ignore_and_lint) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "baseUri": "https://schemas.sourcemeta.com",
    "ignore": [ "./vendor" ],
    "lint": {
      "rules": [ "./rules/my-rule.json" ]
    },
    "path": ")JSON" ROOT_NAME R"JSON(/test"
  })JSON")};

  const auto config{
      sourcemeta::blaze::Configuration::from_json(input, ROOT_NAME "/test")};
  const auto output{config.to_json()};

  EXPECT_EQ(output, input);
}
