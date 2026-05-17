#include <sourcemeta/blaze/allocator.h>

#ifdef BLAZE_ALLOCATOR_RPMALLOC
#include <rpmalloc.h>
#endif

namespace sourcemeta::blaze::allocator {

static Config g_config;

void initialize(const Config &config) {
  g_config = config;
  switch (g_config.backend) {
    case Backend::Standard:
      // No-op; libc allocator is default
      break;
    case Backend::RPMalloc:
#ifdef BLAZE_ALLOCATOR_RPMALLOC
      rpmalloc_initialize();
#else
      throw std::runtime_error("rpmalloc backend not compiled; "
                               "rebuild with -DBLAZE_ALLOCATOR_RPMALLOC=ON");
#endif
      break;
  }
}

void finalize() {
  switch (g_config.backend) {
    case Backend::Standard:
      break;
    case Backend::RPMalloc:
#ifdef BLAZE_ALLOCATOR_RPMALLOC
      rpmalloc_finalize();
#endif
      break;
  }
}

void thread_initialize() {
  switch (g_config.backend) {
    case Backend::Standard:
      break;
    case Backend::RPMalloc:
#ifdef BLAZE_ALLOCATOR_RPMALLOC
      rpmalloc_thread_initialize();
#endif
      break;
  }
}

void thread_finalize() {
  switch (g_config.backend) {
    case Backend::Standard:
      break;
    case Backend::RPMalloc:
#ifdef BLAZE_ALLOCATOR_RPMALLOC
      rpmalloc_thread_finalize(1);
#endif
      break;
  }
}

Config current_config() noexcept { return g_config; }

} // namespace sourcemeta::blaze::allocator
