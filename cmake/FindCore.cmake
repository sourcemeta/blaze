if(NOT Core_FOUND)
  if(BLAZE_INSTALL)
    set(SOURCEMETA_CORE_INSTALL ON CACHE BOOL "enable installation")
  else()
    set(SOURCEMETA_CORE_INSTALL OFF CACHE BOOL "disable installation")
  endif()

  set(SOURCEMETA_CORE_YAML OFF CACHE BOOL "disable YAML support")
  set(SOURCEMETA_CORE_CONTRIB_GOOGLETEST ${BLAZE_TESTS} CACHE BOOL "GoogleTest")
  set(SOURCEMETA_CORE_CONTRIB_GOOGLEBENCHMARK ${BLAZE_BENCHMARK} CACHE BOOL "GoogleBenchmark")
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/core")
  include(Sourcemeta)
  set(Core_FOUND ON)
endif()
