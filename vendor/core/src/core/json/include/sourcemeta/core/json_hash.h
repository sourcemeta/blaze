#ifndef SOURCEMETA_CORE_JSON_HASH_H_
#define SOURCEMETA_CORE_JSON_HASH_H_

#include <cassert> // assert
#include <cstdint> // std::uint64_t
#include <cstring> // std::memcpy

#include "MurmurHash3.h"

namespace sourcemeta::core {

/// @ingroup json
template <typename T> struct HashJSON {
  using hash_type = std::uint64_t;
  inline auto operator()(const T &value) const noexcept -> hash_type {
    return value.fast_hash();
  }

  inline auto is_perfect(const hash_type) const noexcept -> bool {
    return false;
  }
};

/// @ingroup json
template <typename T> struct PropertyHashJSON {
  struct hash_type {
    // For performance when the platform allows it
#if defined(__SIZEOF_INT128__)
    using type = __uint128_t;
    type a{0};
#else
    using type = std::uint64_t;
    type a{0};
#endif

    inline auto operator==(const hash_type &other) const noexcept -> bool {
      return this->a == other.a;
    }
  };

  inline auto hash(const T &value, const std::size_t size) const noexcept
      -> hash_type {
    hash_type result;
    assert(!value.empty());
    assert(value.size() <= 31);
    // Copy starting a byte 2
    std::memcpy(reinterpret_cast<char *>(&result) + 1, value.data(), size);
    return result;
  }

  inline auto operator()(const T &value) const noexcept -> hash_type {
    hash_type result;
    MurmurHash3_x64_128(value.data(), (int) value.size(), 0, &result);
    return result;
  }

  inline auto is_perfect(const hash_type &) const noexcept -> bool {
    // If there is anything written past the first byte,
    // then it is a perfect hash
    return false;
  }
};

} // namespace sourcemeta::core

#endif
