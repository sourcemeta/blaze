#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "configuration_test_utils.h"

#include <filesystem>    // std::filesystem
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

  return std::nullopt;
}

static auto stub_fetcher(std::string_view uri) -> sourcemeta::core::JSON {
  auto result{stub_resolver(uri)};
  if (result.has_value()) {
    return std::move(result).value();
  }
  throw std::runtime_error("Unknown URI: " + std::string{uri});
}

TEST(Configuration_fetch, missing_mode_untracked_fetches_and_updates_lock) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  sourcemeta::blaze::Configuration::Lock lock;
  EXPECT_EQ(lock.size(), 0);

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

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
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");

  EXPECT_FILE_JSON_EQ(
      files, std::filesystem::path{TEST_DIRECTORY} / "simple.json", R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/simple.json",
    "type": "string"
  })JSON");
}

TEST(Configuration_fetch, missing_mode_file_missing_fetches_and_updates_lock) {
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
               "old_hash_value");

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

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
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");
}

TEST(Configuration_fetch, missing_mode_mismatched_fetches_and_updates_lock) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[std::filesystem::path{TEST_DIRECTORY} / "simple.json"] =
      "wrong content\n";

  sourcemeta::blaze::Configuration::Lock lock;
  lock.emplace("https://example.com/simple.json",
               std::filesystem::path{TEST_DIRECTORY} / "simple.json",
               "old_hash_value");

  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

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
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");
}

TEST(Configuration_fetch, missing_mode_up_to_date_skips_fetch) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[std::filesystem::path{TEST_DIRECTORY} / "simple.json"] = R"JSON({
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
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_EQ(events.size(), 1);
  EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");
}

TEST(Configuration_fetch, all_mode_up_to_date_still_fetches) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[std::filesystem::path{TEST_DIRECTORY} / "simple.json"] = R"JSON({
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
      sourcemeta::blaze::Configuration::FetchMode::All);

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
  EXPECT_FETCH_EVENT(events[5], WriteEnd, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");
}

TEST(Configuration_fetch, fetcher_exception_emits_error) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/unknown.json": "unknown.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  auto throwing_fetcher = [](std::string_view) -> sourcemeta::core::JSON {
    throw std::runtime_error("Network error");
  };

  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, throwing_fetcher, stub_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/unknown.json",
                     "unknown.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/unknown.json",
                     "unknown.json", 0, 1, "Failed to fetch schema");
  EXPECT_NE(events[1].exception, nullptr);

  EXPECT_EQ(lock.size(), 0);
}

TEST(Configuration_fetch, bundle_exception_emits_error) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/with-ref.json": "with-ref.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

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

  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, partial_resolver, MAKE_READER(files),
      MAKE_WRITER(files),
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

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

  EXPECT_EQ(lock.size(), 0);
}

TEST(Configuration_fetch, writer_exception_emits_error) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  auto throwing_writer = [](const std::filesystem::path &,
                            const sourcemeta::core::JSON &) -> void {
    throw std::runtime_error("Disk full");
  };

  sourcemeta::blaze::Configuration::Lock lock;

  std::unordered_map<std::string, std::string> files;
  std::vector<sourcemeta::blaze::Configuration::FetchEvent> events;
  configuration.fetch(
      lock, stub_fetcher, stub_resolver, MAKE_READER(files), throwing_writer,
      [&events](const sourcemeta::blaze::Configuration::FetchEvent &event) {
        events.push_back(event);
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

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

  EXPECT_EQ(lock.size(), 0);
}

TEST(Configuration_fetch, callback_abort_on_fetch_start) {
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
        return event.type !=
               sourcemeta::blaze::Configuration::FetchEvent::Type::FetchStart;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], FetchStart, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");

  EXPECT_EQ(lock.size(), 0);
}

TEST(Configuration_fetch, callback_abort_on_up_to_date) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/simple.json": "simple.json"
        }
      })JSON"),
      std::filesystem::path{TEST_DIRECTORY})};

  std::unordered_map<std::string, std::string> files;
  files[std::filesystem::path{TEST_DIRECTORY} / "simple.json"] = R"JSON({
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
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_EQ(events.size(), 2);
  EXPECT_FETCH_EVENT(events[0], UpToDate, "https://example.com/simple.json",
                     "simple.json", 0, 1, "");
  EXPECT_FETCH_EVENT(events[1], Error, "https://example.com/simple.json",
                     "simple.json", 0, 1, "Operation aborted by callback");

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");
}

TEST(Configuration_fetch, empty_dependencies_no_events) {
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
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_TRUE(events.empty());
  EXPECT_EQ(lock.size(), 0);
}

TEST(Configuration_fetch, fetch_and_bundle_with_ref) {
  const auto configuration{sourcemeta::blaze::Configuration::from_json(
      sourcemeta::core::parse_json(R"JSON({
        "base": "https://test.com",
        "dependencies": {
          "https://example.com/with-ref.json": "with-ref.json"
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
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_EQ(events.size(), 6);
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

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/with-ref.json",
                    std::filesystem::path{TEST_DIRECTORY} / "with-ref.json",
                    "411100825ac747c9c6523633d3870ec3");

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

TEST(Configuration_fetch, lock_to_json_after_fetch) {
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
        return true;
      },
      sourcemeta::blaze::Configuration::FetchMode::Missing);

  EXPECT_EQ(lock.size(), 1);
  EXPECT_LOCK_ENTRY(lock, "https://example.com/simple.json",
                    std::filesystem::path{TEST_DIRECTORY} / "simple.json",
                    "e35af8b70997788842aece3ab5f994d8");

  const auto lock_json{lock.to_json()};

  auto expected_entry{sourcemeta::core::JSON::make_object()};
  expected_entry.assign(
      "path", sourcemeta::core::JSON{std::filesystem::path{
                  std::filesystem::path{TEST_DIRECTORY} / "simple.json"}
                                         .generic_string()});
  expected_entry.assign(
      "hash", sourcemeta::core::JSON{"e35af8b70997788842aece3ab5f994d8"});
  expected_entry.assign("hashAlgorithm", sourcemeta::core::JSON{"md5"});

  auto expected_deps{sourcemeta::core::JSON::make_object()};
  expected_deps.assign("https://example.com/simple.json",
                       std::move(expected_entry));

  auto expected{sourcemeta::core::JSON::make_object()};
  expected.assign("version", sourcemeta::core::JSON{1});
  expected.assign("dependencies", std::move(expected_deps));

  EXPECT_EQ(lock_json, expected);
}
