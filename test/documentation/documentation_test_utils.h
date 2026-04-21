#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_DOCUMENTATION_TEST_UTILS_H_

#include <gtest/gtest.h>

#include <sourcemeta/blaze/documentation.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>

#include <set>    // std::set
#include <string> // std::string

static auto collect_identifiers_and_check(
    const sourcemeta::core::JSON &table, std::set<std::int64_t> &identifiers,
    std::set<std::int64_t> &recursive_ref_targets) -> void {
  ASSERT_TRUE(table.is_object());
  ASSERT_TRUE(table.defines("identifier"));
  ASSERT_TRUE(table.defines("rows"));

  const auto table_id{table.at("identifier").to_integer()};
  EXPECT_TRUE(identifiers.insert(table_id).second);

  const auto &rows{table.at("rows")};
  ASSERT_TRUE(rows.is_array());

  const auto has_children{table.defines("children") &&
                          !table.at("children").empty()};
  EXPECT_TRUE(!rows.empty() || has_children);

  std::set<std::string> paths;
  for (std::size_t index = 0; index < rows.array_size(); ++index) {
    const auto &row{rows.at(index)};
    ASSERT_TRUE(row.is_object());
    ASSERT_TRUE(row.defines("identifier"));

    const auto row_id{row.at("identifier").to_integer()};
    EXPECT_TRUE(identifiers.insert(row_id).second);

    if (row.defines("path")) {
      std::string path_key;
      for (const auto &segment : row.at("path").as_array()) {
        if (!path_key.empty()) {
          path_key += "/";
        }
        path_key += segment.at("value").to_string();
      }
      EXPECT_TRUE(paths.insert(path_key).second);
    }

    if (row.defines("type") && row.at("type").defines("kind")) {
      const auto &kind{row.at("type").at("kind").to_string()};
      if (kind == "recursiveRef" && row.at("type").defines("identifier")) {
        recursive_ref_targets.insert(
            row.at("type").at("identifier").to_integer());
      } else if (kind == "array" && row.at("type").defines("items")) {
        const auto &items{row.at("type").at("items")};
        if (items.defines("kind") &&
            items.at("kind").to_string() == "recursiveRef" &&
            items.defines("identifier")) {
          recursive_ref_targets.insert(items.at("identifier").to_integer());
        }
      }
    }

    if (row.defines("children")) {
      for (const auto &section : row.at("children").as_array()) {
        for (std::size_t branch = 0;
             branch < section.at("children").array_size(); ++branch) {
          collect_identifiers_and_check(section.at("children").at(branch),
                                        identifiers, recursive_ref_targets);
        }
      }
    }
  }

  if (table.defines("children")) {
    for (std::size_t index = 0; index < table.at("children").array_size();
         ++index) {
      const auto &section{table.at("children").at(index)};
      for (std::size_t branch = 0; branch < section.at("children").array_size();
           ++branch) {
        collect_identifiers_and_check(section.at("children").at(branch),
                                      identifiers, recursive_ref_targets);
      }
    }
  }
}

#define EXPECT_DOCUMENTATION(schema, walker, resolver, compiled_schema,        \
                             expected)                                         \
  {                                                                            \
    const auto _json{                                                          \
        sourcemeta::blaze::to_documentation((schema), (walker), (resolver))};  \
    std::set<std::int64_t> _ids;                                               \
    std::set<std::int64_t> _ref_targets;                                       \
    collect_identifiers_and_check(_json, _ids, _ref_targets);                  \
    EXPECT_FALSE(_ids.empty());                                                \
    EXPECT_EQ(*_ids.begin(), 0);                                               \
    EXPECT_EQ(*_ids.rbegin(), static_cast<std::int64_t>(_ids.size()) - 1);     \
    for (const auto &_target : _ref_targets) {                                 \
      EXPECT_TRUE(_ids.contains(_target));                                     \
    }                                                                          \
    sourcemeta::blaze::Evaluator _evaluator;                                   \
    EXPECT_TRUE(_evaluator.validate((compiled_schema), _json));                \
    EXPECT_EQ(_json, (expected));                                              \
  }

#endif
