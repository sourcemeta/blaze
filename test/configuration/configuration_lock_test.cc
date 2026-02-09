#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>

#include "configuration_test_utils.h"

#include <unordered_map> // std::unordered_map

TEST(Configuration_Lock, to_json_empty) {
  sourcemeta::blaze::Configuration::Lock lock;

  const auto result{lock.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {}
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_Lock, to_json_single_entry) {
  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/schema.json",
               "/absolute/path/to/schema.json",
               "d41d8cd98f00b204e9800998ecf8427e");

  const auto result{lock.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "/absolute/path/to/schema.json",
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "md5"
      }
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_Lock, to_json_multiple_entries) {
  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/first.json", "/path/to/first.json",
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1");
  lock.emplace("https://example.com/second.json", "/path/to/second.json",
               "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2");

  const auto result{lock.to_json()};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/first.json": {
        "path": "/path/to/first.json",
        "hash": "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1",
        "hashAlgorithm": "md5"
      },
      "https://example.com/second.json": {
        "path": "/path/to/second.json",
        "hash": "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2",
        "hashAlgorithm": "md5"
      }
    }
  })JSON")};

  EXPECT_EQ(result, expected);
}

TEST(Configuration_Lock, to_json_unknown_hash_algorithm) {
  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace(
      "https://example.com/schema.json", "/absolute/path/to/schema.json",
      "d41d8cd98f00b204e9800998ecf8427e",
      static_cast<sourcemeta::blaze::Configuration::Lock::Entry::HashAlgorithm>(
          99));

  try {
    static_cast<void>(lock.to_json());
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "Unknown hash algorithm");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"dependencies",
                                         "https://example.com/schema.json",
                                         "hashAlgorithm"}));
  }
}

TEST(Configuration_Lock, check_untracked) {
  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  const auto reader{MAKE_READER(files)};
  const auto status{lock.check(
      "https://example.com/unknown.json",
      std::filesystem::path{TEST_DIRECTORY} / "schema.json", reader)};

  EXPECT_EQ(status,
            sourcemeta::blaze::Configuration::Lock::Entry::Status::Untracked);
}

TEST(Configuration_Lock, check_file_missing) {
  const auto schema_path{std::filesystem::path{TEST_DIRECTORY} / "schema.json"};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/schema.json", schema_path,
               "d41d8cd98f00b204e9800998ecf8427e");

  std::unordered_map<std::string, std::string> files;
  const auto reader{MAKE_READER(files)};
  const auto status{
      lock.check("https://example.com/schema.json", schema_path, reader)};

  EXPECT_EQ(status,
            sourcemeta::blaze::Configuration::Lock::Entry::Status::FileMissing);
}

TEST(Configuration_Lock, check_mismatched) {
  const auto schema_path{std::filesystem::path{TEST_DIRECTORY} / "schema.json"};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/schema.json", schema_path,
               "0000000000000000000000000000000");

  std::unordered_map<std::string, std::string> files;
  files[schema_path.generic_string()] = "{ \"type\": \"string\" }\n";
  const auto reader{MAKE_READER(files)};
  const auto status{
      lock.check("https://example.com/schema.json", schema_path, reader)};

  EXPECT_EQ(status,
            sourcemeta::blaze::Configuration::Lock::Entry::Status::Mismatched);
}

TEST(Configuration_Lock, check_up_to_date) {
  const auto schema_path{std::filesystem::path{TEST_DIRECTORY} / "schema.json"};
  const std::string content{"{ \"type\": \"string\" }\n"};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/schema.json", schema_path,
               "62f43a110117f85c2b57189200ec3e84");

  std::unordered_map<std::string, std::string> files;
  files[schema_path.generic_string()] = content;
  const auto reader{MAKE_READER(files)};
  const auto status{
      lock.check("https://example.com/schema.json", schema_path, reader)};

  EXPECT_EQ(status,
            sourcemeta::blaze::Configuration::Lock::Entry::Status::UpToDate);
}

TEST(Configuration_Lock, check_path_mismatch) {
  const auto old_path{std::filesystem::path{TEST_DIRECTORY} / "old.json"};
  const auto new_path{std::filesystem::path{TEST_DIRECTORY} / "new.json"};
  const std::string content{"{ \"type\": \"string\" }\n"};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/schema.json", old_path,
               "62f43a110117f85c2b57189200ec3e84");

  std::unordered_map<std::string, std::string> files;
  files[old_path.generic_string()] = content;
  const auto reader{MAKE_READER(files)};
  const auto status{
      lock.check("https://example.com/schema.json", new_path, reader)};

  EXPECT_EQ(
      status,
      sourcemeta::blaze::Configuration::Lock::Entry::Status::PathMismatch);
}
