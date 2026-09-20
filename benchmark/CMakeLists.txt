set(BENCHMARK_SOURCES)

if(BLAZE_BUNDLE)
  list(APPEND BENCHMARK_SOURCES bundle.cc)
endif()

if(BLAZE_FORMAT)
  list(APPEND BENCHMARK_SOURCES format.cc)
endif()

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

if(BENCHMARK_SOURCES)
  sourcemeta_benchmark(NAMESPACE sourcemeta PROJECT blaze
    SOURCES ${BENCHMARK_SOURCES})
  target_compile_definitions(sourcemeta_blaze_benchmarks
    PRIVATE CURRENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

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
  if(BLAZE_BUNDLE)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::bundle)
  endif()
  if(BLAZE_FORMAT)
    target_link_libraries(sourcemeta_blaze_benchmarks
      PRIVATE sourcemeta::blaze::format)
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
