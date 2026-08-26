#ifndef SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <cassert>
#include <sstream>
#include <string_view>
#include <variant>

// The base dialect that a given meta-schema URI maps to, reached the way
// consumers reach it: by framing a schema that declares it
[[maybe_unused]] static auto
test_base_dialect_of(const std::string_view dialect)
    -> sourcemeta::blaze::SchemaBaseDialect {
  auto document{sourcemeta::core::JSON::make_object()};
  document.assign("$schema", sourcemeta::core::JSON{
                                 sourcemeta::core::JSON::String{dialect}});
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  return frame.root_location().value().get().base_dialect;
}

// The vocabularies of a schema, reached the way consumers reach them: by
// framing the schema and asking the frame about its root location
[[maybe_unused]] static auto
test_vocabularies(const sourcemeta::core::JSON &document,
                  const sourcemeta::blaze::SchemaResolver &resolver,
                  const std::string_view default_dialect = "")
    -> sourcemeta::blaze::SchemaVocabularies {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};
  frame.analyse(document, sourcemeta::blaze::schema_walker, resolver,
                default_dialect);
  return frame.vocabularies(frame.root_location().value().get(), resolver);
}

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
