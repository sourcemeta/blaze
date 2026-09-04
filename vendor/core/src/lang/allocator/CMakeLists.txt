if(Mimalloc_FOUND)
  set(SOURCEMETA_CORE_ALLOCATOR_MIMALLOC 1)
else()
  set(SOURCEMETA_CORE_ALLOCATOR_MIMALLOC 0)
endif()

# Which allocator a build ends up with is not something a consumer can work out
# from the headers alone, and it decides whether the allocator entry points are
# there to be called at all
set(BACKEND_HEADER_PATH
  "${CMAKE_CURRENT_BINARY_DIR}/include/sourcemeta/core/allocator_backend.h")
configure_file(backend.h.in "${BACKEND_HEADER_PATH}" @ONLY)

sourcemeta_library(NAMESPACE sourcemeta PROJECT core NAME allocator
  SOURCES allocator.cc)

if(Mimalloc_FOUND)
  # This is the one library that carries the allocator, so that the entry
  # points it replaces are defined exactly once across the whole project
  target_link_libraries(sourcemeta_core_allocator PRIVATE mimalloc)
endif()

if(SOURCEMETA_CORE_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT core NAME allocator)
  install(FILES "${BACKEND_HEADER_PATH}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sourcemeta/core"
    COMPONENT sourcemeta_core_dev)
endif()
