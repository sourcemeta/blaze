#ifndef SOURCEMETA_JSONTOOLKIT_JSON_HASH_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_HASH_H_

namespace sourcemeta::jsontoolkit {

/// @ingroup json
template <typename T> struct FastHash {
  // This hash function is specifically designed to be constant
  // with regards to string length, and to exploit the fact that
  // most JSON objects don't have a lot of entries, so hash collision
  // is not as common
  inline auto operator()(const typename T::String &value) const noexcept
      -> std::size_t {
    return value.empty()
               ? 0
               : value.size() + static_cast<std::size_t>(value.front()) +
                     static_cast<std::size_t>(value.back());
  }

  inline auto operator()(const T &value) const noexcept -> std::size_t {
    return value.fast_hash();
  }
};

} // namespace sourcemeta::jsontoolkit

#endif
