#include <sourcemeta/core/test.h>

#include <array>       // std::array
#include <cstdint>     // std::uint32_t
#include <string>      // std::string, std::to_string
#include <string_view> // std::string_view

#include "suite_compatibility.h"

namespace {
constexpr std::array<std::uint32_t, 7> VERSIONS{3, 4, 6, 7, 2019, 2020, 9999};

auto matching_versions(const std::string_view compatibility) -> std::string {
  std::string result;

  for (const auto version : VERSIONS) {
    if (!suite_compatibility(compatibility, version)) {
      continue;
    }

    if (!result.empty()) {
      result += ',';
    }

    result += std::to_string(version);
  }

  return result;
}
} // namespace

TEST(minimum_3) { EXPECT_EQ(matching_versions("3"), "3,4,6,7,2019,2020,9999"); }

TEST(minimum_4) { EXPECT_EQ(matching_versions("4"), "4,6,7,2019,2020,9999"); }

TEST(minimum_6) { EXPECT_EQ(matching_versions("6"), "6,7,2019,2020,9999"); }

TEST(minimum_7) { EXPECT_EQ(matching_versions("7"), "7,2019,2020,9999"); }

TEST(minimum_2019) { EXPECT_EQ(matching_versions("2019"), "2019,2020,9999"); }

TEST(minimum_2020) { EXPECT_EQ(matching_versions("2020"), "2020,9999"); }

TEST(minimum_9999) { EXPECT_EQ(matching_versions("9999"), "9999"); }

TEST(maximum_3) { EXPECT_EQ(matching_versions("<=3"), "3"); }

TEST(maximum_4) { EXPECT_EQ(matching_versions("<=4"), "3,4"); }

TEST(maximum_7) { EXPECT_EQ(matching_versions("<=7"), "3,4,6,7"); }

TEST(maximum_2019) { EXPECT_EQ(matching_versions("<=2019"), "3,4,6,7,2019"); }

TEST(maximum_2020) {
  EXPECT_EQ(matching_versions("<=2020"), "3,4,6,7,2019,2020");
}

TEST(exact_3) { EXPECT_EQ(matching_versions("=3"), "3"); }

TEST(exact_4) { EXPECT_EQ(matching_versions("=4"), "4"); }

TEST(exact_7) { EXPECT_EQ(matching_versions("=7"), "7"); }

TEST(exact_2019) { EXPECT_EQ(matching_versions("=2019"), "2019"); }

TEST(exact_2020) { EXPECT_EQ(matching_versions("=2020"), "2020"); }

TEST(range_3_to_4) { EXPECT_EQ(matching_versions("3,<=4"), "3,4"); }

TEST(range_3_to_7) { EXPECT_EQ(matching_versions("3,<=7"), "3,4,6,7"); }

TEST(range_3_to_2019) {
  EXPECT_EQ(matching_versions("3,<=2019"), "3,4,6,7,2019");
}

TEST(range_4_to_7) { EXPECT_EQ(matching_versions("4,<=7"), "4,6,7"); }

TEST(range_4_to_2019) {
  EXPECT_EQ(matching_versions("4,<=2019"), "4,6,7,2019");
}

TEST(range_4_to_6_and_minimum_9999) {
  EXPECT_EQ(matching_versions("4,<=6,9999"), "4,6,9999");
}

TEST(range_6_to_7) { EXPECT_EQ(matching_versions("6,<=7"), "6,7"); }

TEST(range_6_to_2019) { EXPECT_EQ(matching_versions("6,<=2019"), "6,7,2019"); }

TEST(range_7_to_2019) { EXPECT_EQ(matching_versions("7,<=2019"), "7,2019"); }

TEST(range_7_to_2020) {
  EXPECT_EQ(matching_versions("7,<=2020"), "7,2019,2020");
}

TEST(range_2019_to_2020) {
  EXPECT_EQ(matching_versions("2019,<=2020"), "2019,2020");
}

TEST(maximum_3_and_minimum_7) {
  EXPECT_EQ(matching_versions("<=3,7"), "3,7,2019,2020,9999");
}

TEST(exact_3_and_minimum_7) {
  EXPECT_EQ(matching_versions("=3,7"), "3,7,2019,2020,9999");
}

TEST(exact_3_and_range_7_to_2020) {
  EXPECT_EQ(matching_versions("=3,7,<=2020"), "3,7,2019,2020");
}
