#include <sourcemeta/blaze/binpack.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>

#include <variant>

TEST(DOUBLE_VARINT_TUPLE) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "DOUBLE_VARINT_TUPLE",
    "binpackOptions": {}
  })JSON");

  const auto result{sourcemeta::blaze::binpack_load(input)};
  using namespace sourcemeta::blaze;
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(result));
}

TEST(NUMBER_VARINT_TUPLE) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "NUMBER_VARINT_TUPLE",
    "binpackOptions": {}
  })JSON");

  const auto result{sourcemeta::blaze::binpack_load(input)};
  using namespace sourcemeta::blaze;
  EXPECT_TRUE(std::holds_alternative<NUMBER_VARINT_TUPLE>(result));
}
