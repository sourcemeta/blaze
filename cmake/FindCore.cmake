if(NOT Core_FOUND)
  if(BLAZE_INSTALL)
    set(SOURCEMETA_CORE_INSTALL ON CACHE BOOL "enable installation")
  else()
    set(SOURCEMETA_CORE_INSTALL OFF CACHE BOOL "disable installation")
  endif()

  set(SOURCEMETA_CORE_EXTENSION_BUILD OFF CACHE BOOL "disable")

  if(BLAZE_ADDRESS_SANITIZER OR BLAZE_UNDEFINED_SANITIZER)
    set(SOURCEMETA_CORE_USE_SYSTEM_ALLOCATOR ON
      CACHE BOOL "enable the system allocator")
  else()
    set(SOURCEMETA_CORE_USE_SYSTEM_ALLOCATOR OFF
      CACHE BOOL "disable the system allocator")
  endif()

  set(SOURCEMETA_CORE_CONTRIB_GOOGLETEST ${BLAZE_TESTS} CACHE BOOL "GoogleTest")
  set(SOURCEMETA_CORE_CONTRIB_GOOGLEBENCHMARK ${BLAZE_BENCHMARK} CACHE BOOL "GoogleBenchmark")
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/core")
  include(Sourcemeta)
  set(Core_FOUND ON)
endif()
