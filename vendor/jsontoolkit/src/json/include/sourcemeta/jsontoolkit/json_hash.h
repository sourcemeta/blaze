#ifndef SOURCEMETA_JSONTOOLKIT_JSON_HASH_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_HASH_H_

#include <cassert> // assert
#include <cstdint> // std::uint64_t
#include <cstring> // std::memcpy

namespace sourcemeta::jsontoolkit {

/// @ingroup json
template <typename T> struct FastHash {
  using hash_type = std::uint64_t;
  inline auto operator()(const T &value) const noexcept -> hash_type {
    return value.fast_hash();
  }

  inline auto is_perfect(const hash_type) const noexcept -> bool {
    return false;
  }
};

/// @ingroup json
template <typename T> struct KeyHash {
  struct hash_type {
    // For performance when the platform allows it
#if defined(__SIZEOF_INT128__)
    using type = __uint128_t;
    type a{0};
    type b{0};
#else
    using type = std::uint64_t;
    type a{0};
    type b{0};
    type c{0};
    type d{0};
#endif

    inline auto operator==(const hash_type &other) const noexcept -> bool {
#if defined(__SIZEOF_INT128__)
      return this->a == other.a && this->b == other.b;
#else
      return this->a == other.a && this->b == other.b && this->c == other.c &&
             this->d == other.d;
#endif
    }
  };

  inline auto perfect(const T &value) const noexcept -> hash_type {
    hash_type result;
    assert(!value.empty());
    assert(value.size() <= 31);
    // Copy starting a byte 2
    std::memcpy(reinterpret_cast<char *>(&result) + 1, value.data(),
                value.size());
    return result;
  }

  inline auto operator()(const T &value) const noexcept -> hash_type {
    const auto size{value.size()};
    if (size == 0) {
      return {};
    } else if (size <= 31) {
      return this->perfect(value);
    } else {
      // This case is specifically designed to be constant with regards to
      // string length, and to exploit the fact that most JSON objects don't
      // have a lot of entries, so hash collision is not as common
      return {(size + static_cast<typename hash_type::type>(value.front()) +
               static_cast<typename hash_type::type>(value.back())) %
              // Make sure the property hash can never exceed 8 bits
              256};
    }
  }

  inline auto is_perfect(const hash_type &hash) const noexcept -> bool {
    // If there is anything written past the first byte,
    // then it is a perfect hash
    return hash.a > 255;
  }
};

} // namespace sourcemeta::jsontoolkit

#endif
