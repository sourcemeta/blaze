#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "configuration_test_utils.h"

#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

static auto stub_resolver(std::string_view uri)
    -> std::optional<sourcemeta::core::JSON> {
  if (uri == "https://example.com/simple.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/simple.json",
      "type": "string"
    })JSON");
  }

  if (uri == "https://example.com/with-ref.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/with-ref.json",
      "$ref": "https://example.com/simple.json"
    })JSON");
  }

  if (uri == "https://json-schema.org/draft/2020-12/schema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://json-schema.org/draft/2020-12/schema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true
      }
    })JSON");
  }

  if (uri == "https://example.com/no-schema.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://example.com/no-schema.json",
      "type": "integer"
    })JSON");
  }

  return std::nullopt;
}

static auto stub_fetcher(std::string_view uri) -> sourcemeta::core::JSON {
  auto result{stub_resolver(uri)};
  if (result.has_value()) {
    return std::move(result).value();
  }
  throw std::runtime_error("Unknown URI: " + std::string{uri});
}

TEST(Configuration_fetch_frozen, dry_run_untracked_dependency) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/unknown.json": "unknown.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], Untracked, "https://example.com/unknown.json",
                     "unknown.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, dry_run_file_missing) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "nonexistent.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "nonexistent.json",
               "somehash123");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], FileMissing, "https://example.com/simple.json",
                     "nonexistent.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, dry_run_up_to_date) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, dry_run_mismatched) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "wrong-content.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json")
            .generic_string()] = "wrong content\n";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json",
               "expected_hash");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], Mismatched, "https://example.com/simple.json",
                     "wrong-content.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, dry_run_orphaned_lock_entry) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");
  lock.emplace("https://example.com/orphaned.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned.json",
               "orphanedhash");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Orphaned, "https://example.com/orphaned.json",
                     "orphaned.json", 0, 0, "");
}

TEST(Configuration_fetch_frozen, frozen_mismatched_fails) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "wrong-content.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json")
            .generic_string()] = "wrong content\n";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json",
               "expected_hash");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], Mismatched, "https://example.com/simple.json",
                     "wrong-content.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "wrong-content.json", 0, 1,
                     "File hash does not match lock file in frozen mode");
}

TEST(Configuration_fetch_frozen, dry_run_path_mismatch) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "new_location.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "old_location.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "old_location.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], PathMismatch, "https://example.com/simple.json",
                     "new_location.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, frozen_path_mismatch_fails) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "new_location.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "old_location.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "old_location.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], PathMismatch, "https://example.com/simple.json",
                     "new_location.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "new_location.json", 0, 1,
                     "Configured path does not match lock file in frozen mode");
}

TEST(Configuration_fetch_frozen, callback_abort_stops_processing) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return false;
      },
      true);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], Untracked, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, fetcher_exception_emits_error) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/nonexistent.json": "nonexistent.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/nonexistent.json",
               std::filesystem::path{TEST_DIRECTORY} / "nonexistent.json",
               "somehash");

  auto throwing_fetcher = [](std::string_view) -> sourcemeta::core::JSON {
    throw std::runtime_error("Network error");
  };

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, throwing_fetcher, stub_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], FetchStart,
                     "https://example.com/nonexistent.json", "nonexistent.json",
                     0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/nonexistent.json",
                     "nonexistent.json", 0, 1, "Failed to fetch schema");
  EXPECT_NE(events[1].exception, nullptr);
}

TEST(Configuration_fetch_frozen, empty_dependencies_no_events) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com"
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_TRUE(events.empty());
}

TEST(Configuration_fetch_frozen, empty_dependencies_with_orphaned_lock) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com"
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/orphaned.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned.json",
               "somehash");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], Orphaned, "https://example.com/orphaned.json",
                     "orphaned.json", 0, 0, "");
}

TEST(Configuration_fetch_frozen, dry_run_multiple_mixed_results) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json",
          "https://example.com/other.json": "wrong-content.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";
  files[(std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json")
            .generic_string()] = "wrong content\n";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");
  lock.emplace("https://example.com/other.json",
               std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json",
               "wrong_hash_value");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], Mismatched, "https://example.com/other.json",
                     "wrong-content.json", 0, 2, "");
  EXPECT_FETCH_EVENT(events[1], UpToDate, "https://example.com/simple.json",
                     "simple.json", 1, 2, "");
}

TEST(Configuration_fetch_frozen, dry_run_multiple_with_untracked_and_missing) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json",
          "https://example.com/untracked.json": "untracked.json",
          "https://example.com/missing.json": "missing.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");
  lock.emplace("https://example.com/missing.json",
               std::filesystem::path{TEST_DIRECTORY} / "missing.json",
               "somehash");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 3);
  if (events[0].uri == "https://example.com/missing.json") {
    EXPECT_FETCH_EVENT(events[0], FileMissing,
                       "https://example.com/missing.json", "missing.json", 0, 3,
                       "");
    EXPECT_FETCH_EVENT(events[1], Untracked,
                       "https://example.com/untracked.json", "untracked.json",
                       1, 3, "");
    EXPECT_FETCH_EVENT(events[2], UpToDate, "https://example.com/simple.json",
                       "simple.json", 2, 3, "");
  } else {
    EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                       "simple.json", 0, 3, "");
    EXPECT_FETCH_EVENT(events[1], Untracked,
                       "https://example.com/untracked.json", "untracked.json",
                       1, 3, "");
    EXPECT_FETCH_EVENT(events[2], FileMissing,
                       "https://example.com/missing.json", "missing.json", 2, 3,
                       "");
  }
}

TEST(Configuration_fetch_frozen, dry_run_all_status_types) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json",
          "https://example.com/untracked.json": "untracked.json",
          "https://example.com/missing.json": "missing.json",
          "https://example.com/mismatched.json": "wrong-content.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";
  files[(std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json")
            .generic_string()] = "wrong content\n";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");
  lock.emplace("https://example.com/missing.json",
               std::filesystem::path{TEST_DIRECTORY} / "missing.json",
               "somehash");
  lock.emplace("https://example.com/mismatched.json",
               std::filesystem::path{TEST_DIRECTORY} / "wrong-content.json",
               "wrong_hash");
  lock.emplace("https://example.com/orphaned.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned.json",
               "orphanedhash");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 5);

  if (events[0].uri == "https://example.com/missing.json") {
    EXPECT_FETCH_EVENT(events[0], FileMissing,
                       "https://example.com/missing.json", "missing.json", 0, 4,
                       "");
    EXPECT_FETCH_EVENT(events[1], Mismatched,
                       "https://example.com/mismatched.json",
                       "wrong-content.json", 1, 4, "");
    EXPECT_FETCH_EVENT(events[2], Untracked,
                       "https://example.com/untracked.json", "untracked.json",
                       2, 4, "");
    EXPECT_FETCH_EVENT(events[3], UpToDate, "https://example.com/simple.json",
                       "simple.json", 3, 4, "");
  } else if (events[0].uri == "https://example.com/mismatched.json") {
    EXPECT_FETCH_EVENT(events[0], Mismatched,
                       "https://example.com/mismatched.json",
                       "wrong-content.json", 0, 4, "");
    EXPECT_FETCH_EVENT(events[1], FileMissing,
                       "https://example.com/missing.json", "missing.json", 1, 4,
                       "");
    EXPECT_FETCH_EVENT(events[2], Untracked,
                       "https://example.com/untracked.json", "untracked.json",
                       2, 4, "");
    EXPECT_FETCH_EVENT(events[3], UpToDate, "https://example.com/simple.json",
                       "simple.json", 3, 4, "");
  } else {
    EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                       "simple.json", 0, 4, "");
    EXPECT_FETCH_EVENT(events[1], Untracked,
                       "https://example.com/untracked.json", "untracked.json",
                       1, 4, "");
    EXPECT_FETCH_EVENT(events[2], FileMissing,
                       "https://example.com/missing.json", "missing.json", 2, 4,
                       "");
    EXPECT_FETCH_EVENT(events[3], Mismatched,
                       "https://example.com/mismatched.json",
                       "wrong-content.json", 3, 4, "");
  }

  EXPECT_FETCH_EVENT(events[4], Orphaned, "https://example.com/orphaned.json",
                     "orphaned.json", 0, 0, "");
}

TEST(Configuration_fetch_frozen, fetch_and_bundle_simple_schema) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 8);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], VerifyStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[7], VerifyEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");

  EXPECT_FILE_JSON_EQ(
      files, std::filesystem::path{TEST_DIRECTORY} / "simple.json", R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/simple.json",
    "type": "string"
  })JSON");
}

TEST(Configuration_fetch_frozen, fetch_and_bundle_with_ref) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/with-ref.json": "with-ref.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/with-ref.json",
               std::filesystem::path{TEST_DIRECTORY} / "with-ref.json",
               "411100825ac747c9c6523633d3870ec3");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 8);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart,
                     "https://example.com/with-ref.json", "with-ref.json", 0, 1,
                     "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], VerifyStart,
                     "https://example.com/with-ref.json", "with-ref.json", 0, 1,
                     "");
  EXPECT_FETCH_EVENT(events[7], VerifyEnd, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");

  EXPECT_FILE_JSON_EQ(
      files, std::filesystem::path{TEST_DIRECTORY} / "with-ref.json", R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/with-ref.json",
    "$ref": "https://example.com/simple.json",
    "$defs": {
      "https://example.com/simple.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/simple.json",
        "type": "string"
      }
    }
  })JSON");
}

TEST(Configuration_fetch_frozen, fetch_schema_without_schema_using_default) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "defaultDialect": "https://json-schema.org/draft/2020-12/schema",
        "dependencies": {
          "https://example.com/no-schema.json": "no-schema.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/no-schema.json",
               std::filesystem::path{TEST_DIRECTORY} / "no-schema.json",
               "b688158d45f1668036d1f26ca6de7753");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 8);
  EXPECT_FETCH_EVENT(events[0], FetchStart,
                     "https://example.com/no-schema.json", "no-schema.json", 0,
                     1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/no-schema.json",
                     "no-schema.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart,
                     "https://example.com/no-schema.json", "no-schema.json", 0,
                     1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/no-schema.json",
                     "no-schema.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart,
                     "https://example.com/no-schema.json", "no-schema.json", 0,
                     1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/no-schema.json",
                     "no-schema.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], VerifyStart,
                     "https://example.com/no-schema.json", "no-schema.json", 0,
                     1, "");
  EXPECT_FETCH_EVENT(events[7], VerifyEnd, "https://example.com/no-schema.json",
                     "no-schema.json", 0, 1, "");

  EXPECT_FILE_JSON_EQ(
      files, std::filesystem::path{TEST_DIRECTORY} / "no-schema.json", R"JSON({
    "$id": "https://example.com/no-schema.json",
    "type": "integer"
  })JSON");
}

TEST(Configuration_fetch_frozen, fetch_schema_without_schema_no_default_fails) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/no-schema.json": "no-schema.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/no-schema.json",
               std::filesystem::path{TEST_DIRECTORY} / "no-schema.json",
               "somehash");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 4);
  EXPECT_FETCH_EVENT(events[0], FetchStart,
                     "https://example.com/no-schema.json", "no-schema.json", 0,
                     1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/no-schema.json",
                     "no-schema.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart,
                     "https://example.com/no-schema.json", "no-schema.json", 0,
                     1, "");
  EXPECT_FETCH_EVENT(events[3], Error, "https://example.com/no-schema.json",
                     "no-schema.json", 0, 1, "Failed to bundle schema");
  EXPECT_NE(events[3].exception, nullptr);

  try {
    std::rethrow_exception(events[3].exception);
    FAIL() << "Expected exception to be thrown";
  } catch (const sourcemeta::core::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(Configuration_fetch_frozen, writer_exception_emits_error) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  auto throwing_writer = [](const std::filesystem::path &,
                            const sourcemeta::core::JSON &) -> void {
    throw std::runtime_error("Disk full");
  };

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), throwing_writer,
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 6);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Failed to write schema");
  EXPECT_NE(events[5].exception, nullptr);
}

TEST(Configuration_fetch_frozen, hash_verification_failure) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "wrong_expected_hash_value");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 9);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], VerifyStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[7], VerifyEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[8], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1,
                     "Written file hash does not match lock file");
}

TEST(Configuration_fetch_frozen, callback_abort_on_fetch_end) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::FetchEnd;
      },
      false);

  EXPECT_EQ(events.size(), 3);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_bundle_start) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::BundleStart;
      },
      false);

  EXPECT_EQ(events.size(), 4);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_bundle_end) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::BundleEnd;
      },
      false);

  EXPECT_EQ(events.size(), 5);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_write_start) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::WriteStart;
      },
      false);

  EXPECT_EQ(events.size(), 6);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_write_end) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::WriteEnd;
      },
      false);

  EXPECT_EQ(events.size(), 7);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_verify_start) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::VerifyStart;
      },
      false);

  EXPECT_EQ(events.size(), 8);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], VerifyStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[7], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_verify_end) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::VerifyEnd;
      },
      false);

  EXPECT_EQ(events.size(), 9);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[3], BundleEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[4], WriteStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[6], VerifyStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[7], VerifyEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[8], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, callback_abort_on_orphaned) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com"
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/orphaned.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned.json",
               "somehash");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return false;
      },
      true);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], Orphaned, "https://example.com/orphaned.json",
                     "orphaned.json", 0, 0, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/orphaned.json",
                     "orphaned.json", 0, 0, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, multiple_orphaned_entries) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com"
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/orphaned1.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned1.json",
               "hash1");
  lock.emplace("https://example.com/orphaned2.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned2.json",
               "hash2");
  lock.emplace("https://example.com/orphaned3.json",
               std::filesystem::path{TEST_DIRECTORY} / "orphaned3.json",
               "hash3");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      true);

  EXPECT_EQ(events.size(), 3);
  if (events[0].uri == "https://example.com/orphaned1.json") {
    EXPECT_FETCH_EVENT(events[0], Orphaned,
                       "https://example.com/orphaned1.json", "orphaned1.json",
                       0, 0, "");
    if (events[1].uri == "https://example.com/orphaned2.json") {
      EXPECT_FETCH_EVENT(events[1], Orphaned,
                         "https://example.com/orphaned2.json", "orphaned2.json",
                         0, 0, "");
      EXPECT_FETCH_EVENT(events[2], Orphaned,
                         "https://example.com/orphaned3.json", "orphaned3.json",
                         0, 0, "");
    } else {
      EXPECT_FETCH_EVENT(events[1], Orphaned,
                         "https://example.com/orphaned3.json", "orphaned3.json",
                         0, 0, "");
      EXPECT_FETCH_EVENT(events[2], Orphaned,
                         "https://example.com/orphaned2.json", "orphaned2.json",
                         0, 0, "");
    }
  } else if (events[0].uri == "https://example.com/orphaned2.json") {
    EXPECT_FETCH_EVENT(events[0], Orphaned,
                       "https://example.com/orphaned2.json", "orphaned2.json",
                       0, 0, "");
    if (events[1].uri == "https://example.com/orphaned1.json") {
      EXPECT_FETCH_EVENT(events[1], Orphaned,
                         "https://example.com/orphaned1.json", "orphaned1.json",
                         0, 0, "");
      EXPECT_FETCH_EVENT(events[2], Orphaned,
                         "https://example.com/orphaned3.json", "orphaned3.json",
                         0, 0, "");
    } else {
      EXPECT_FETCH_EVENT(events[1], Orphaned,
                         "https://example.com/orphaned3.json", "orphaned3.json",
                         0, 0, "");
      EXPECT_FETCH_EVENT(events[2], Orphaned,
                         "https://example.com/orphaned1.json", "orphaned1.json",
                         0, 0, "");
    }
  } else {
    EXPECT_FETCH_EVENT(events[0], Orphaned,
                       "https://example.com/orphaned3.json", "orphaned3.json",
                       0, 0, "");
    if (events[1].uri == "https://example.com/orphaned1.json") {
      EXPECT_FETCH_EVENT(events[1], Orphaned,
                         "https://example.com/orphaned1.json", "orphaned1.json",
                         0, 0, "");
      EXPECT_FETCH_EVENT(events[2], Orphaned,
                         "https://example.com/orphaned2.json", "orphaned2.json",
                         0, 0, "");
    } else {
      EXPECT_FETCH_EVENT(events[1], Orphaned,
                         "https://example.com/orphaned2.json", "orphaned2.json",
                         0, 0, "");
      EXPECT_FETCH_EVENT(events[2], Orphaned,
                         "https://example.com/orphaned1.json", "orphaned1.json",
                         0, 0, "");
    }
  }
}

TEST(Configuration_fetch_frozen, resolver_returns_nullopt_during_bundle) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/with-ref.json": "with-ref.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/with-ref.json",
               std::filesystem::path{TEST_DIRECTORY} / "with-ref.json",
               "somehash");

  auto partial_resolver =
      [](std::string_view uri) -> std::optional<sourcemeta::core::JSON> {
    if (uri == "https://example.com/with-ref.json") {
      return sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/with-ref.json",
        "$ref": "https://example.com/simple.json"
      })JSON");
    }
    if (uri == "https://json-schema.org/draft/2020-12/schema") {
      return sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        }
      })JSON");
    }
    return std::nullopt;
  };

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, partial_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 4);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], FetchEnd, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[2], BundleStart,
                     "https://example.com/with-ref.json", "with-ref.json", 0, 1,
                     "");
  EXPECT_FETCH_EVENT(events[3], Error, "https://example.com/with-ref.json",
                     "with-ref.json", 0, 1, "Failed to bundle schema");
  EXPECT_NE(events[3].exception, nullptr);
}

TEST(Configuration_fetch_frozen, callback_abort_on_fetch_start) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::FetchStart;
      },
      false);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}

TEST(Configuration_fetch_frozen, up_to_date_skips_fetch_in_non_dry_run) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  auto failing_fetcher = [](std::string_view) -> sourcemeta::core::JSON {
    throw std::runtime_error("Fetcher should not be called for up-to-date");
  };

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, failing_fetcher, stub_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, untracked_skips_fetch_in_non_dry_run) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/unknown.json": "unknown.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;

  auto failing_fetcher = [](std::string_view) -> sourcemeta::core::JSON {
    throw std::runtime_error("Fetcher should not be called for untracked");
  };

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, failing_fetcher, stub_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], Untracked, "https://example.com/unknown.json",
                     "unknown.json", 0, 1, "");
}

TEST(Configuration_fetch_frozen, multiple_dependencies_stops_on_first_error) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/failing.json": "failing.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/failing.json",
               std::filesystem::path{TEST_DIRECTORY} / "failing.json",
               "somehash");

  auto failing_fetcher = [](std::string_view) -> sourcemeta::core::JSON {
    throw std::runtime_error("Network error");
  };

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, failing_fetcher, stub_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      false);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/failing.json",
                     "failing.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/failing.json",
                     "failing.json", 0, 1, "Failed to fetch schema");
  EXPECT_NE(events[1].exception, nullptr);
}

TEST(Configuration_fetch_frozen, callback_abort_on_up_to_date) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[(std::filesystem::path{TEST_DIRECTORY} / "simple.json")
            .generic_string()] =
      R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/simple.json",
  "type": "string"
}
)JSON";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "e35af8b70997788842aece3ab5f994d8");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return false;
      },
      false);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");
}
