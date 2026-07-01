#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>

TEST(vocabularies_known_2020_12_core) {
  const auto vocabulary{
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Core};
  const auto result{sourcemeta::core::to_json(vocabulary)};
  EXPECT_TRUE(result.is_integer());
  EXPECT_EQ(result.to_integer(), 21);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::Known>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(vocabulary, back.value());
}

TEST(vocabularies_known_2020_12_applicator) {
  const auto vocabulary{
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Applicator};
  const auto result{sourcemeta::core::to_json(vocabulary)};
  EXPECT_TRUE(result.is_integer());
  EXPECT_EQ(result.to_integer(), 22);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::Known>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(vocabulary, back.value());
}

TEST(vocabularies_known_draft_0) {
  const auto vocabulary{
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_Draft_0};
  const auto result{sourcemeta::core::to_json(vocabulary)};
  EXPECT_TRUE(result.is_integer());
  EXPECT_EQ(result.to_integer(), 0);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::Known>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(vocabulary, back.value());
}

TEST(vocabularies_known_from_json_invalid_type) {
  const sourcemeta::core::JSON input{"not-an-integer"};
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::Known>(
          input)};
  EXPECT_FALSE(result.has_value());
}

TEST(vocabularies_uri_with_known) {
  const sourcemeta::blaze::Vocabularies::URI uri{
      sourcemeta::blaze::Vocabularies::Known::JSON_Schema_2020_12_Core};
  const auto result{sourcemeta::core::to_json(uri)};
  EXPECT_TRUE(result.is_array());
  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(result.at(0).is_integer());
  EXPECT_EQ(result.at(0).to_integer(), 0);
  EXPECT_TRUE(result.at(1).is_integer());
  EXPECT_EQ(result.at(1).to_integer(), 21);
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::URI>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(uri, back.value());
}

TEST(vocabularies_uri_with_custom_string) {
  const sourcemeta::blaze::Vocabularies::URI uri{
      sourcemeta::core::JSON::String{"https://example.com/my-custom-vocab"}};
  const auto result{sourcemeta::core::to_json(uri)};
  EXPECT_TRUE(result.is_array());
  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(result.at(0).is_integer());
  EXPECT_EQ(result.at(0).to_integer(), 1);
  EXPECT_TRUE(result.at(1).is_string());
  EXPECT_EQ(result.at(1).to_string(), "https://example.com/my-custom-vocab");
  const auto back{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::URI>(
          result)};
  EXPECT_TRUE(back.has_value());
  EXPECT_EQ(uri, back.value());
}

TEST(vocabularies_uri_from_json_invalid_type) {
  const sourcemeta::core::JSON input{"not-an-array"};
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::URI>(input)};
  EXPECT_FALSE(result.has_value());
}

TEST(vocabularies_uri_from_json_invalid_size) {
  auto input{sourcemeta::core::JSON::make_array()};
  input.push_back(sourcemeta::core::JSON{0});
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::URI>(input)};
  EXPECT_FALSE(result.has_value());
}

TEST(vocabularies_uri_from_json_invalid_index) {
  auto input{sourcemeta::core::JSON::make_array()};
  input.push_back(sourcemeta::core::JSON{99});
  input.push_back(sourcemeta::core::JSON{0});
  const auto result{
      sourcemeta::core::from_json<sourcemeta::blaze::Vocabularies::URI>(input)};
  EXPECT_FALSE(result.has_value());
}
