#include <sourcemeta/blaze/binpack.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>

TEST(arbitrary) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON");

  sourcemeta::blaze::binpack_compile(schema, sourcemeta::core::schema_walker,
                                     sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "NUMBER_VARINT_TUPLE",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}
