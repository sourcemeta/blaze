#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "configuration_test_utils.h"

TEST(Configuration_Lock_Parse_V1, empty_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {}
  })JSON")};

  const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};

  EXPECT_EQ(lock.size(), 0);
}

TEST(Configuration_Lock_Parse_V1, single_dependency) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "/absolute/path/to/schema.json",
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "md5"
      }
    }
  })JSON")};

  const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/schema.json",
                    "/absolute/path/to/schema.json",
                    "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(Configuration_Lock_Parse_V1, multiple_dependencies) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
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

  const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};

  EXPECT_EQ(lock.size(), 2);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/first.json",
                    "/path/to/first.json", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1");
  EXPECT_LOCK_ENTRY(lock, "https://example.com/second.json",
                    "/path/to/second.json", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb2");
}

TEST(Configuration_Lock_Parse_V1, not_an_object) {
  const auto input{sourcemeta::core::parse_json("[]")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "The lock file must be an object");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "");
  }
}

TEST(Configuration_Lock_Parse_V1, missing_version) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "dependencies": {}
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "The lock file must have a version property");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "");
  }
}

TEST(Configuration_Lock_Parse_V1, unsupported_version) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 999,
    "dependencies": {}
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "Unsupported lock file version");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/version");
  }
}

TEST(Configuration_Lock_Parse_V1, dependencies_not_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": []
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependencies property must be an object");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/dependencies");
  }
}

TEST(Configuration_Lock_Parse_V1, entry_not_object) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": "invalid"
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must be an object");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json");
  }
}

TEST(Configuration_Lock_Parse_V1, missing_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "md5"
      }
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must have a path");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/path");
  }
}

TEST(Configuration_Lock_Parse_V1, missing_hash) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "/absolute/path/to/schema.json",
        "hashAlgorithm": "md5"
      }
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must have a hash");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/hash");
  }
}

TEST(Configuration_Lock_Parse_V1, missing_hash_algorithm) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "/absolute/path/to/schema.json",
        "hash": "d41d8cd98f00b204e9800998ecf8427e"
      }
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry must have a hash algorithm");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/hashAlgorithm");
  }
}

TEST(Configuration_Lock_Parse_V1, unknown_hash_algorithm) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "/absolute/path/to/schema.json",
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "unknown"
      }
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(), "Unknown hash algorithm");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/hashAlgorithm");
  }
}

TEST(Configuration_Lock_Parse_V1, relative_path) {
  const auto input{sourcemeta::core::parse_json(R"JSON({
    "version": 1,
    "dependencies": {
      "https://example.com/schema.json": {
        "path": "./relative/path/to/schema.json",
        "hash": "d41d8cd98f00b204e9800998ecf8427e",
        "hashAlgorithm": "md5"
      }
    }
  })JSON")};

  try {
    const auto lock{sourcemeta::blaze::Configuration::Lock::from_json(input)};
    FAIL();
  } catch (const sourcemeta::blaze::ConfigurationParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The lock file dependency entry path must be absolute");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              "/dependencies/https:~1~1example.com~1schema.json/path");
  }
}
