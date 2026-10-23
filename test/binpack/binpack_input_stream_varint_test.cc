#include <limits> // std::numeric_limits
#include <sourcemeta/blaze/binpack_input_stream.h>
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/test.h>

TEST(varint_0x01) {
  sourcemeta::core::InputByteStream stream{0x01};
  sourcemeta::blaze::BinPackInputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 1);
}

TEST(varint_0x17) {
  sourcemeta::core::InputByteStream stream{0x17};
  sourcemeta::blaze::BinPackInputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 23);
}

TEST(varint_0xac_0x02) {
  sourcemeta::core::InputByteStream stream{{0xac, 0x02}};
  sourcemeta::blaze::BinPackInputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 300);
}

TEST(varint_0xdf_0x89_0x03) {
  sourcemeta::core::InputByteStream stream{{0xdf, 0x89, 0x03}};
  sourcemeta::blaze::BinPackInputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 50399);
}

TEST(varint_0xfe_0xff_0xff_0xff_0x0f) {
  sourcemeta::core::InputByteStream stream{{0xfe, 0xff, 0xff, 0xff, 0x0f}};
  sourcemeta::blaze::BinPackInputStream decoder{stream};
  const std::uint64_t result{decoder.get_varint()};
  const std::uint64_t expected{4294967294};
  EXPECT_EQ(result, expected);
}

TEST(varint_uint64_max) {
  // In Base-128: (1)1111111 (1)1111111 (1)1111111 (1)1111111
  // (1)1111111 (1)1111111 (1)1111111 (1)1111111 (1)1111111 (0)0000001
  sourcemeta::core::InputByteStream stream{
      {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01}};
  sourcemeta::blaze::BinPackInputStream decoder{stream};
  const std::uint64_t result{decoder.get_varint()};
  const std::uint64_t expected{18446744073709551615U};
  EXPECT_EQ(result, expected);
}
