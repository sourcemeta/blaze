if(NOT Benchmark_FOUND)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "enable testing of the benchmark library")

  # This library compiles its own sources with warnings as errors, and those
  # warnings are not ours to answer for on every compiler that we support
  set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "enable warnings as errors when building the benchmark library")

  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/googlebenchmark")

  # Consumers run static analysis over their own benchmark sources, and the
  # headers this library exposes are not theirs to answer for
  get_target_property(BENCHMARK_INCLUDE_DIRECTORIES
    benchmark INTERFACE_INCLUDE_DIRECTORIES)
  set_target_properties(benchmark PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${BENCHMARK_INCLUDE_DIRECTORIES}")

  set(Benchmark_FOUND ON)
endif()
