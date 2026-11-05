set(BENCHMARK_SOURCES)

if(BLAZE_COMPILER AND BLAZE_EVALUATOR AND BLAZE_OUTPUT)
  list(APPEND BENCHMARK_SOURCES
    e2e/runner.cc
    jsonld.cc
    micro/draft4.cc
    micro/draft6.cc
    micro/draft7.cc
    micro/2019_09.cc
    micro/2020_12.cc)
endif()

if(BLAZE_TEST)
  list(APPEND BENCHMARK_SOURCES test.cc)
endif()

if(BLAZE_ALTERSCHEMA)
  list(APPEND BENCHMARK_SOURCES alterschema.cc)
endif()

if(BLAZE_CONVERT)
  list(APPEND BENCHMARK_SOURCES convert.cc)
endif()

if(BENCHMARK_SOURCES)
  sourcemeta_benchmark(NAMESPACE sourcemeta PROJECT blaze
    SOURCES ${BENCHMARK_SOURCES})
  target_compile_definitions(sourcemeta_blaze_benchmarks
    PRIVATE CURRENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

  # The evaluator hot path lives entirely in headers, so it compiles into this
  # target rather than into the library, which makes this target's ISA level
  # the one the benchmark measures. Raise it to AVX2 where the machine can
  # execute those instructions, leaving everything we install at the baseline.
  # Asking the machine rather than the compiler is sound here, as this binary
  # only ever runs where it was built
  if(NOT CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_PROCESSOR MATCHES "x86|AMD64")
    include(CheckCXXSourceRuns)

    if(MSVC)
      set(BENCHMARK_AVX2_FLAGS "/arch:AVX2")
    else()
      set(BENCHMARK_AVX2_FLAGS "-mavx2")
    endif()

    list(JOIN BENCHMARK_AVX2_FLAGS " " CMAKE_REQUIRED_FLAGS)
    check_cxx_source_runs("
      #include <immintrin.h>
      auto main() -> int {
        const auto zero{_mm256_setzero_si256()};
        return _mm256_extract_epi32(_mm256_xor_si256(zero, zero), 0);
      }" BENCHMARK_MACHINE_SUPPORTS_AVX2)
    unset(CMAKE_REQUIRED_FLAGS)

    if(BENCHMARK_MACHINE_SUPPORTS_AVX2)
      message(STATUS "Benchmarking the evaluator with AVX2")
      target_compile_options(sourcemeta_blaze_benchmarks
        PRIVATE ${BENCHMARK_AVX2_FLAGS})
    endif()
  endif()

  target_link_libraries(sourcemeta_blaze_benchmarks
    PRIVATE sourcemeta::core::io)
  target_link_libraries(sourcemeta_blaze_benchmarks
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_benchmarks
    PRIVATE sourcemeta::core::jsonl)
  if(BLAZE_COMPILER)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::compiler)
  endif()
  if(BLAZE_EVALUATOR)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::evaluator)
  endif()
  if(BLAZE_OUTPUT)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::output)
  endif()
  if(BLAZE_TEST)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::test)
  endif()
  if(BLAZE_ALTERSCHEMA)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::alterschema)
  endif()
  if(BLAZE_CONVERT)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::convert)
  endif()

  # A single run prints the human readable report and writes the JSON file, so
  # that recording results for later comparison costs nothing extra
  add_custom_target(benchmark
    COMMAND sourcemeta_blaze_benchmarks
      --output "${PROJECT_BINARY_DIR}/benchmark.json"
    DEPENDS sourcemeta_blaze_benchmarks
    COMMENT "Running benchmark...")
else()
  add_custom_target(benchmark VERBATIM
    COMMAND "${CMAKE_COMMAND}" -E echo "Nothing to benchmark"
    COMMAND "${CMAKE_COMMAND}" -E false)
endif()
