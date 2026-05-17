/// @file
/// @brief Allocator abstraction layer for runtime backend selection

#ifndef SOURCEMETA_BLAZE_ALLOCATOR_H_
#define SOURCEMETA_BLAZE_ALLOCATOR_H_

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace sourcemeta::blaze::allocator {

/// @brief Allocator backend enumeration
enum class Backend : std::uint8_t {
  Standard, ///< Standard libc malloc/free
  RPMalloc  ///< rpmalloc (if compiled with BLAZE_ALLOCATOR_RPMALLOC=ON)
};

/// @brief Global allocator configuration
struct Config {
  Backend backend = Backend::Standard;

  /// @brief Get human-readable name for backend
  [[nodiscard]] std::string_view backend_name() const noexcept {
    switch (backend) {
      case Backend::Standard:
        return "standard";
      case Backend::RPMalloc:
        return "rpmalloc";
    }
    return "unknown";
  }
};

/// @brief Initialize global allocator at process start
/// @param config Allocator configuration
/// @throws std::runtime_error if rpmalloc backend requested but not
/// compiled
void initialize(const Config &config = Config{});

/// @brief Finalize allocator at process exit
void finalize();

/// @brief Initialize thread-local allocator state (call at thread start)
void thread_initialize();

/// @brief Finalize thread-local allocator state (call at thread exit)
void thread_finalize();

/// @brief Query current configuration
[[nodiscard]] Config current_config() noexcept;

} // namespace sourcemeta::blaze::allocator

#endif
