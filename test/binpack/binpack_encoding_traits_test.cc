#include <sourcemeta/blaze/binpack.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>

#include <type_traits>

TEST(encoding_movable) {
  using namespace sourcemeta::blaze;
  EXPECT_TRUE(std::is_move_constructible_v<BinPackEncoding>);
}

TEST(encoding_nothrow_movable) {
  using namespace sourcemeta::blaze;
  EXPECT_TRUE(std::is_nothrow_move_constructible_v<BinPackEncoding>);
}

TEST(encoding_copyable) {
  using namespace sourcemeta::blaze;
  EXPECT_TRUE(std::is_copy_constructible_v<BinPackEncoding>);
}
