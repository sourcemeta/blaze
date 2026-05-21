#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(JSONSchema, is_schema_true) {
  const sourcemeta::core::JSON document{true};
  EXPECT_TRUE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_false) {
  const sourcemeta::core::JSON document{false};
  EXPECT_TRUE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_int) {
  const sourcemeta::core::JSON document{5};
  EXPECT_FALSE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_real) {
  const sourcemeta::core::JSON document{5.3};
  EXPECT_FALSE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_null) {
  const sourcemeta::core::JSON document{nullptr};
  EXPECT_FALSE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_string) {
  const sourcemeta::core::JSON document{"foo"};
  EXPECT_FALSE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_array) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ 1, 2, 3 ]");
  EXPECT_FALSE(sourcemeta::blaze::is_schema(document));
}

TEST(JSONSchema, is_schema_empty_object) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  EXPECT_TRUE(sourcemeta::blaze::is_schema(document));
}
