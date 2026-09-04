sourcemeta_library(NAMESPACE sourcemeta PROJECT core NAME memory
  PRIVATE_HEADERS owned_or_reference.h)

if(Mimalloc_FOUND)
  set(SOURCEMETA_CORE_ALLOCATOR_MIMALLOC 1)
else()
  set(SOURCEMETA_CORE_ALLOCATOR_MIMALLOC 0)
endif()

# Which allocator a build ends up with is not something a consumer can work out
# from the headers alone, and it decides whether the allocator entry points are
# there to be called at all
set(ALLOCATOR_HEADER_PATH
  "${CMAKE_CURRENT_BINARY_DIR}/include/sourcemeta/core/memory_allocator.h")
configure_file(allocator.h.in "${ALLOCATOR_HEADER_PATH}" @ONLY)
target_include_directories(sourcemeta_core_memory INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

if(SOURCEMETA_CORE_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT core NAME memory)
  include(GNUInstallDirs)
  install(FILES "${ALLOCATOR_HEADER_PATH}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sourcemeta/core"
    COMPONENT sourcemeta_core_dev)
endif()
