#ifndef SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_

#include <cassert>
#include <sstream>
#include <variant>

#define EXPECT_VOCABULARY_KNOWN(vocabulary_value, expected_known)              \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::SchemaVocabularies::Known>(    \
          (vocabulary_value)));                                                \
  EXPECT_EQ(std::get<sourcemeta::blaze::SchemaVocabularies::Known>(            \
                (vocabulary_value)),                                           \
            sourcemeta::blaze::SchemaVocabularies::Known::expected_known)

#define EXPECT_VOCABULARY_REQUIRED(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(                                                           \
              sourcemeta::blaze::SchemaVocabularies::Known::expected_known));  \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .get(sourcemeta::blaze::SchemaVocabularies::Known::expected_known)   \
          .value())

#define EXPECT_VOCABULARY_OPTIONAL(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(                                                           \
              sourcemeta::blaze::SchemaVocabularies::Known::expected_known));  \
  EXPECT_FALSE(                                                                \
      (vocabularies)                                                           \
          .get(sourcemeta::blaze::SchemaVocabularies::Known::expected_known)   \
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

#endif
