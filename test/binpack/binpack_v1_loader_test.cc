#include <sourcemeta/blaze/binpack.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>

TEST(invalid_encoding_name) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FOO_BAR",
    "binpackOptions": {}
  })JSON");

  try {
    sourcemeta::blaze::binpack_load(input);
    FAIL();
  } catch (const sourcemeta::blaze::BinPackEncodingError &error) {
    EXPECT_STREQ(error.what(), "Unrecognized encoding: FOO_BAR");
  }
}
