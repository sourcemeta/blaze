#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(null_string) {
  const sourcemeta::core::JSON type{"null"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Null)));
  EXPECT_EQ(result.count(), 1);
}

TEST(boolean_string) {
  const sourcemeta::core::JSON type{"boolean"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Boolean)));
  EXPECT_EQ(result.count(), 1);
}

TEST(object_string) {
  const sourcemeta::core::JSON type{"object"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Object)));
  EXPECT_EQ(result.count(), 1);
}

TEST(array_string) {
  const sourcemeta::core::JSON type{"array"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Array)));
  EXPECT_EQ(result.count(), 1);
}

TEST(number_string) {
  const sourcemeta::core::JSON type{"number"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Integer)));
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Real)));
  EXPECT_EQ(result.count(), 2);
}

TEST(integer_string) {
  const sourcemeta::core::JSON type{"integer"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Integer)));
  EXPECT_EQ(result.count(), 1);
}

TEST(string_string) {
  const sourcemeta::core::JSON type{"string"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::String)));
  EXPECT_EQ(result.count(), 1);
}

TEST(unknown_string) {
  const sourcemeta::core::JSON type{"foo"};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_EQ(result.count(), 0);
}

TEST(array_single) {
  const auto type{sourcemeta::core::parse_json(R"JSON([ "string" ])JSON")};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::String)));
  EXPECT_EQ(result.count(), 1);
}

TEST(array_multiple) {
  const auto type{sourcemeta::core::parse_json(
      R"JSON([ "string", "null", "object" ])JSON")};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::String)));
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Null)));
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Object)));
  EXPECT_EQ(result.count(), 3);
}

TEST(array_with_number) {
  const auto type{
      sourcemeta::core::parse_json(R"JSON([ "number", "boolean" ])JSON")};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Integer)));
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Real)));
  EXPECT_TRUE(result.test(
      static_cast<std::size_t>(sourcemeta::core::JSON::Type::Boolean)));
  EXPECT_EQ(result.count(), 3);
}

TEST(array_empty) {
  const auto type{sourcemeta::core::parse_json(R"JSON([])JSON")};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_EQ(result.count(), 0);
}

TEST(non_string_non_array) {
  const sourcemeta::core::JSON type{42};
  const auto result{sourcemeta::blaze::parse_schema_type(type)};
  EXPECT_EQ(result.count(), 0);
}
