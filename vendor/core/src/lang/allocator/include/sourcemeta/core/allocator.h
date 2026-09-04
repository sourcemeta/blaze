#ifndef SOURCEMETA_CORE_ALLOCATOR_H_
#define SOURCEMETA_CORE_ALLOCATOR_H_

#ifndef SOURCEMETA_CORE_ALLOCATOR_EXPORT
#include <sourcemeta/core/allocator_export.h>
#endif

// NOLINTBEGIN(misc-include-cleaner)
#include <sourcemeta/core/allocator_backend.h>
// NOLINTEND(misc-include-cleaner)

#include <string_view> // std::string_view

/// @defgroup allocator Allocator
/// @brief The memory allocator that every program linking this project runs on.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/core/allocator.h>
/// ```

namespace sourcemeta::core {

/// @ingroup allocator
///
/// Report the allocator that this build replaces the standard one with, or
/// `system` if it leaves the platform allocator in place. For example:
///
/// ```cpp
/// #include <sourcemeta/core/allocator.h>
/// #include <iostream>
///
/// std::cout << sourcemeta::core::allocator() << "\n";
/// ```
SOURCEMETA_CORE_ALLOCATOR_EXPORT
auto allocator() -> std::string_view;

} // namespace sourcemeta::core

#endif
