/// @file
/// @brief std::allocator adapter for rpmalloc when enabled

#ifndef SOURCEMETA_BLAZE_ALLOCATOR_ADAPTER_H_
#define SOURCEMETA_BLAZE_ALLOCATOR_ADAPTER_H_

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>

#ifdef BLAZE_ALLOCATOR_RPMALLOC
#include <rpmalloc.h>
#endif

namespace sourcemeta::blaze {

/// @brief Custom allocator adapter for use with STL containers
/// @tparam T Value type
/// 
/// When BLAZE_ALLOCATOR_RPMALLOC is enabled, uses rpmalloc.
/// Otherwise falls back to standard malloc/free.
template <typename T>
class RpmallocAdapter {
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  RpmallocAdapter() = default;

  template <typename U>
  RpmallocAdapter(const RpmallocAdapter<U>&) {}

  /// @brief Allocate memory for n elements
  [[nodiscard]] pointer allocate(size_type n) {
#ifdef BLAZE_ALLOCATOR_RPMALLOC
    return static_cast<pointer>(rpmalloc(n * sizeof(T)));
#else
    return static_cast<pointer>(malloc(n * sizeof(T)));
#endif
  }

  /// @brief Deallocate memory
  void deallocate(pointer p, size_type) {
#ifdef BLAZE_ALLOCATOR_RPMALLOC
    rpfree(p);
#else
    free(p);
#endif
  }

  bool operator==(const RpmallocAdapter&) const { return true; }
  bool operator!=(const RpmallocAdapter&) const { return false; }
};

} // namespace sourcemeta::blaze

#endif
