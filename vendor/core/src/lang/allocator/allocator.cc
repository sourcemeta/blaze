#include <sourcemeta/core/allocator.h>

#include <string_view> // std::string_view

namespace sourcemeta::core {

auto allocator() -> std::string_view {
#if SOURCEMETA_CORE_ALLOCATOR_MIMALLOC
  return "mimalloc";
#else
  return "system";
#endif
}

} // namespace sourcemeta::core
