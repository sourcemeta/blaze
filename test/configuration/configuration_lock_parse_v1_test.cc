#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "configuration_test_utils.h"

#include <filesystem> // std::filesystem

TEST(empty_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {}
  })JSON")};

  const auto lock{
      sourcemeta::blaze::Configuration::Lock::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(lock.size(), 0);
}

TEST(single_dependency) {
  const std::filesystem::path schema_path =
      std::filesystem::path{TEST_DIRECTORY} / "schema.json";
  const auto input{make_lock_json(
      {{"https://example.com/schema.json",
        make_lock_entry_json(schema_path.string(),
                             "d41d8cd98f00b204e9800998ecf8427e")}})};

  const auto lock{
      sourcemeta::blaze::Configuration::Lock::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/schema.json", schema_path,
                    "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(multiple_dependencies) {
  const std::filesystem::path first_path =
      std::filesystem::path{TEST_DIRECTORY} / "first.json";
  const std::filesystem::path second_path =
      std::filesystem::path{TEST_DIRECTORY} / "second.json";
  const auto input{make_lock_json(
      {{"https://example.com/first.json",
        make_lock_entry_json(first_path.string(),
                             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1")},
       {"https://example.com/second.json",
        make_lock_entry_json(second_path.string(),
                             "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2")}})};

  const auto lock{
      sourcemeta::blaze::Configuration::Lock::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(lock.size(), 2);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/first.json", first_path,
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1");
  EXPECT_LOCK_ENTRY(lock, "https://example.com/second.json", second_path,
                    "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2");
}

TEST(not_an_object) {
  const auto input{sourcemeta::core::parse_json("[]")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "The lock file must be an object");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "");
  }
}

TEST(missing_version) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {}
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "The lock file must have a version property");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "");
  }
}

TEST(unsupported_version) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 999,
    "dependencies": {}
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "Unsupported lock file version");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/version");
  }
}

TEST(dependencies_not_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": []
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependencies property must be an object");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/dependencies");
  }
}

TEST(entry_not_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": "invalid"
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must be an object");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json");
  }
}

TEST(missing_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "sha256"
      }
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must have a path");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/path");
  }
}

TEST(missing_hash) {
  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign(
      "path",
      sourcemeta::core::JSON{
          (std::filesystem::path{TEST_DIRECTORY} / "schema.json").string()});
  entry.assign("hashAlgorithm", sourcemeta::core::JSON{"sha256"});
  const auto input{
      make_lock_json({{"https://example.com/schema.json", entry}})};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must have a hash");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/hash");
  }
}

TEST(missing_hash_algorithm) {
  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign(
      "path",
      sourcemeta::core::JSON{
          (std::filesystem::path{TEST_DIRECTORY} / "schema.json").string()});
  entry.assign("hash",
               sourcemeta::core::JSON{"d41d8cd98f00b204e9800998ecf8427e"});
  const auto input{
      make_lock_json({{"https://example.com/schema.json", entry}})};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must have a hash algorithm");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/hashAlgorithm");
  }
}

TEST(unknown_hash_algorithm) {
  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign(
      "path",
      sourcemeta::core::JSON{
          (std::filesystem::path{TEST_DIRECTORY} / "schema.json").string()});
  entry.assign("hash",
               sourcemeta::core::JSON{"d41d8cd98f00b204e9800998ecf8427e"});
  entry.assign("hashAlgorithm", sourcemeta::core::JSON{"unknown"});
  const auto input{
      make_lock_json({{"https://example.com/schema.json", entry}})};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(
        input, TEST_DIRECTORY)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "Unknown hash algorithm");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/hashAlgorithm");
  }
}

TEST(relative_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "./vendor/schema.json",
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "sha256"
      }
    }
  })JSON")};

  const auto lock{
      sourcemeta::blaze::Configuration::Lock::from_json(input, TEST_DIRECTORY)};

  EXPECT_EQ(lock.size(), 1);
  const auto entry{lock.at("https://example.com/schema.json")};
  EXPECT_TRUE(entry.has_value());
  EXPECT_EQ(entry->get().path,
            std::filesystem::weakly_canonical(
                std::filesystem::path{TEST_DIRECTORY} / "vendor/schema.json"));
  EXPECT_EQ(entry->get().hash, "d41d8cd98f00b204e9800998ecf8427e");
}
