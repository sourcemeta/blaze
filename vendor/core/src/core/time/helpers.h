#ifndef SOURCEMETA_CORE_TIME_HELPERS_H_
#define SOURCEMETA_CORE_TIME_HELPERS_H_

#include <sourcemeta/core/time.h>

#include <array>       // std::array
#include <cstdint>     // std::uint8_t, std::uint16_t
#include <ctime>       // std::tm
#include <string_view> // std::string_view
#include <utility>     // std::cmp_greater

namespace sourcemeta::core {

// RFC 9110 §5.6.7: "HTTP-date is case sensitive". The standard library's
// std::get_time matches day and month names case-insensitively on some
// implementations, so the exact spelling is verified against the parsed index
inline auto is_case_sensitive_day_abbreviation(const std::string_view name,
                                               const int weekday) -> bool {
  static constexpr std::array<std::string_view, 7> names{
      {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}};
  return weekday >= 0 && weekday < 7 &&
         name == names[static_cast<std::size_t>(weekday)];
}

inline auto is_case_sensitive_month_abbreviation(const std::string_view name,
                                                 const int month) -> bool {
  static constexpr std::array<std::string_view, 12> names{
      {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
       "Nov", "Dec"}};
  return month >= 0 && month < 12 &&
         name == names[static_cast<std::size_t>(month)];
}

// Validate the calendar fields of a broken-down time, since the conversion to
// an epoch time point would otherwise silently normalise out-of-range values
inline auto is_valid_broken_down_time(const std::tm &parts) -> bool {
  if (parts.tm_mon < 0 || parts.tm_mon > 11) {
    return false;
  }
  const auto month{static_cast<std::uint8_t>(parts.tm_mon + 1)};
  const auto year{static_cast<std::uint16_t>(parts.tm_year + 1900)};
  if (parts.tm_mday < 1 ||
      std::cmp_greater(parts.tm_mday, max_day_in_month(month, year))) {
    return false;
  }
  if (parts.tm_hour < 0 || parts.tm_hour > 23) {
    return false;
  }
  if (parts.tm_min < 0 || parts.tm_min > 59) {
    return false;
  }
  // RFC 3339 §5.6: a leap second is represented as a "60" second value
  if (parts.tm_sec < 0 || parts.tm_sec > 60) {
    return false;
  }
  return true;
}

} // namespace sourcemeta::core

#endif
