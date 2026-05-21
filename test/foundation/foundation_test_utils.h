#ifndef SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_

#include <cassert>
#include <sstream>
#include <variant>

#define EXPECT_VOCABULARY_KNOWN(vocabulary_value, expected_known)              \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::Vocabularies::Known>(  \
      (vocabulary_value)));                                                    \
  EXPECT_EQ(                                                                   \
      std::get<sourcemeta::blaze::Vocabularies::Known>((vocabulary_value)),    \
      sourcemeta::blaze::Vocabularies::Known::expected_known)

#define EXPECT_VOCABULARY_REQUIRED(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(sourcemeta::blaze::Vocabularies::Known::expected_known));  \
  EXPECT_TRUE((vocabularies)                                                   \
                  .get(sourcemeta::blaze::Vocabularies::Known::expected_known) \
                  .value())

#define EXPECT_VOCABULARY_OPTIONAL(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(sourcemeta::blaze::Vocabularies::Known::expected_known));  \
  EXPECT_FALSE(                                                                \
      (vocabularies)                                                           \
          .get(sourcemeta::blaze::Vocabularies::Known::expected_known)         \
          .value())

#define EXPECT_OPTIONAL_POINTER(optional_value, expected_optional)             \
  if (std::optional<std::string>{expected_optional}.has_value()) {             \
    EXPECT_TRUE((optional_value).has_value());                                 \
    EXPECT_EQ(sourcemeta::core::to_string((optional_value).value()),           \
              std::optional<std::string>{expected_optional}.value());          \
  } else {                                                                     \
    EXPECT_FALSE((optional_value).has_value());                                \
  }

#define EXPECT_POINTER_TEMPLATE(pointer, expected)                             \
  {                                                                            \
    std::ostringstream stream;                                                 \
    sourcemeta::core::stringify((pointer), stream);                            \
    EXPECT_EQ(stream.str(), (expected));                                       \
  }

#define TO_POINTER(pointer_string)                                             \
  sourcemeta::core::to_pointer((pointer_string))

#define __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,        \
                              expected_parent_location, expected_dialect,      \
                              expected_base_dialect)                           \
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(index).pointer),            \
            expected_schema_location);                                         \
  EXPECT_OPTIONAL_POINTER(entries.at(index).parent, expected_parent_location); \
  EXPECT_FALSE(entries.at(index).dialect.empty());                             \
  EXPECT_TRUE(entries.at(index).base_dialect.has_value());                     \
  EXPECT_EQ(entries.at(index).dialect, expected_dialect);                      \
  EXPECT_EQ(                                                                   \
      sourcemeta::blaze::to_string(entries.at(index).base_dialect.value()),    \
      expected_base_dialect);                                                  \
  EXPECT_FALSE(entries.at(index).vocabularies.empty());

#define EXPECT_WALKER_ENTRY_2020_12(entries, index, expected_schema_location,  \
                                    expected_parent_location)                  \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2020-12/schema",        \
                        "https://json-schema.org/draft/2020-12/schema");       \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_2020_12_ORPHAN(                                    \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2020-12/schema",        \
                        "https://json-schema.org/draft/2020-12/schema");       \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_2019_09(entries, index, expected_schema_location,  \
                                    expected_parent_location)                  \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2019-09/schema",        \
                        "https://json-schema.org/draft/2019-09/schema");       \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_2019_09_ORPHAN(                                    \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2019-09/schema",        \
                        "https://json-schema.org/draft/2019-09/schema");       \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT7(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-07/schema#",             \
                        "http://json-schema.org/draft-07/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT7_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-07/schema#",             \
                        "http://json-schema.org/draft-07/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT6(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-06/schema#",             \
                        "http://json-schema.org/draft-06/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);                                      \
  EXPECT_FALSE(entries.at(index).property_name);

#define EXPECT_WALKER_ENTRY_DRAFT6_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-06/schema#",             \
                        "http://json-schema.org/draft-06/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);                                       \
  EXPECT_FALSE(entries.at(index).property_name);

#define EXPECT_WALKER_ENTRY_DRAFT6_PROPERTY_NAME(                              \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-06/schema#",             \
                        "http://json-schema.org/draft-06/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);                                      \
  EXPECT_TRUE(entries.at(index).property_name);

#define EXPECT_WALKER_ENTRY_DRAFT4(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-04/schema#",             \
                        "http://json-schema.org/draft-04/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT4_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-04/schema#",             \
                        "http://json-schema.org/draft-04/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT3(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-03/schema#",             \
                        "http://json-schema.org/draft-03/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT3_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-03/schema#",             \
                        "http://json-schema.org/draft-03/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT2(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-02/schema#",             \
                        "http://json-schema.org/draft-02/hyper-schema#");      \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT2_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-02/schema#",             \
                        "http://json-schema.org/draft-02/hyper-schema#");      \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT1(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-01/schema#",             \
                        "http://json-schema.org/draft-01/hyper-schema#");      \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT1_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-01/schema#",             \
                        "http://json-schema.org/draft-01/hyper-schema#");      \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT0(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-00/schema#",             \
                        "http://json-schema.org/draft-00/hyper-schema#");      \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT0_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-00/schema#",             \
                        "http://json-schema.org/draft-00/hyper-schema#");      \
  EXPECT_TRUE(entries.at(index).orphan);

#endif
