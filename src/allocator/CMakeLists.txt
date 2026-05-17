add_library(sourcemeta_blaze_allocator STATIC allocator.cc)

target_include_directories(sourcemeta_blaze_allocator
  PUBLIC include)

if(BLAZE_ALLOCATOR_RPMALLOC)
  # Link rpmalloc backend if enabled
  if(TARGET blaze_rpmalloc_backend)
    target_link_libraries(sourcemeta_blaze_allocator
      PUBLIC blaze_rpmalloc_backend)
    target_compile_definitions(sourcemeta_blaze_allocator
      PUBLIC BLAZE_ALLOCATOR_RPMALLOC=1)
    # Ensure rpmalloc headers are visible when the backend is present
    if(DEFINED rpmalloc_SOURCE_DIR)
      target_include_directories(sourcemeta_blaze_allocator
        PUBLIC ${rpmalloc_SOURCE_DIR}/rpmalloc)
    endif()
  endif()
endif()

# Export for downstream use
set_target_properties(sourcemeta_blaze_allocator PROPERTIES
  EXPORT_NAME blaze::allocator)
