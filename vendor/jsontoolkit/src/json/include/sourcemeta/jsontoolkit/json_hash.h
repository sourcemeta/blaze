#ifndef SOURCEMETA_JSONTOOLKIT_JSON_HASH_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_HASH_H_

#include <cstddef> // std::size_t
#include <cstring> // std::memcpy

namespace sourcemeta::jsontoolkit {

/// @ingroup json
template <typename T> struct FastHash {
  using hash_type = std::size_t;

  inline auto operator()(const typename T::String &value) const noexcept
      -> hash_type {
    const auto size{value.size()};
    hash_type result{0};
    switch (size) {
      case 0:
        return 0;
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
        std::memcpy(&result, value.data(), size);
        result = result << 8;
        return result;
      default:
        // This case is specifically designed to be constant with regards to
        // string length, and to exploit the fact that most JSON objects don't
        // have a lot of entries, so hash collision is not as common
        return (size + static_cast<hash_type>(value.front()) +
                static_cast<hash_type>(value.back())) %
               // Make sure the property hash can never exceed 8 bits
               256;
    }
  }

  inline auto is_perfect_string_hash(const hash_type hash) const noexcept
      -> bool {
    return hash > 255;
  }

  inline auto equal(const typename T::String &left,
                    const typename T::String &right, const hash_type hash) const
      -> bool {
    // If the hash is a perfect hash, then we don't need to check anymore
    return is_perfect_string_hash(hash) || left == right;
  }

  inline auto operator()(const T &value) const noexcept -> hash_type {
    return value.fast_hash();
  }
};

} // namespace sourcemeta::jsontoolkit

#endif
