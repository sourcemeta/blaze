#ifndef SOURCEMETA_BLAZE_CONFIGURATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_CONFIGURATION_TEST_UTILS_H_

#include <gtest/gtest.h>

#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/json.h>

#include <filesystem>    // std::filesystem::path
#include <sstream>       // std::ostringstream
#include <stdexcept>     // std::runtime_error
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::pair
#include <vector>        // std::vector

inline auto
MAKE_READER(const std::unordered_map<std::string, std::string> &files)
    -> sourcemeta::blaze::Configuration::ReadCallback {
  return [&files](const std::filesystem::path &path) -> std::string {
    const auto iterator{files.find(path.string())};
    if (iterator == files.end()) {
      throw std::runtime_error("File not found: " + path.string());
    }
    return iterator->second;
  };
}

inline auto MAKE_WRITER(std::unordered_map<std::string, std::string> &files)
    -> sourcemeta::blaze::Configuration::WriteCallback {
  return [&files](const std::filesystem::path &path,
                  const sourcemeta::core::JSON &json) -> void {
    std::ostringstream output;
    sourcemeta::core::prettify(json, output);
    output << "\n";
    files[path.string()] = output.str();
  };
}

#define EXPECT_FILE_JSON_EQ(files, path, expected_json)                        \
  {                                                                            \
    const auto path_string = (path).string();                                  \
    EXPECT_TRUE((files).contains(path_string));                                \
    const auto written_schema =                                                \
        sourcemeta::core::parse_json((files).at(path_string));                 \
    const auto expected_schema = sourcemeta::core::parse_json(expected_json);  \
    EXPECT_EQ(written_schema, expected_schema);                                \
  }

#define EXPECT_LOCK_ENTRY(lock, uri, expected_path, expected_hash)             \
  {                                                                            \
    const auto result{(lock).at(uri)};                                         \
    EXPECT_TRUE(result.has_value());                                           \
    EXPECT_EQ(result->get().path, std::filesystem::path{expected_path});       \
    EXPECT_EQ(result->get().hash, expected_hash);                              \
    EXPECT_EQ(                                                                 \
        result->get().hash_algorithm,                                          \
        sourcemeta::blaze::Configuration::Lock::Entry::HashAlgorithm::MD5);    \
  }

inline auto make_lock_entry_json(const std::string &path,
                                 const std::string &hash,
                                 const std::string &algorithm = "md5")
    -> sourcemeta::core::JSON {
  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign("path", sourcemeta::core::JSON{path});
  entry.assign("hash", sourcemeta::core::JSON{hash});
  entry.assign("hashAlgorithm", sourcemeta::core::JSON{algorithm});
  return entry;
}

inline auto
make_lock_json(const std::vector<std::pair<std::string, sourcemeta::core::JSON>>
                   &dependencies) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("version", sourcemeta::core::JSON{1});
  auto dependencies_json{sourcemeta::core::JSON::make_object()};
  for (const auto &dependency : dependencies) {
    dependencies_json.assign(dependency.first, dependency.second);
  }
  result.assign("dependencies", std::move(dependencies_json));
  return result;
}

#define EXPECT_FETCH_EVENT(event, expected_type, expected_uri,                 \
                           expected_path_filename, expected_index,             \
                           expected_total, expected_details)                   \
  {                                                                            \
    EXPECT_EQ(                                                                 \
        (event).type,                                                          \
        sourcemeta::blaze::Configuration::FetchEvent::Type::expected_type);    \
    EXPECT_EQ((event).uri, (expected_uri));                                    \
    EXPECT_EQ((event).path.filename(), (expected_path_filename));              \
    EXPECT_EQ((event).index, (expected_index));                                \
    EXPECT_EQ((event).total, (expected_total));                                \
    EXPECT_EQ((event).details, (expected_details));                            \
  }

#endif
