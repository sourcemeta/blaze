set(BENCHMARK_SOURCES)

if(BLAZE_FOUNDATION)
  list(APPEND BENCHMARK_SOURCES foundation.cc)
endif()

if(BLAZE_FRAME)
  list(APPEND BENCHMARK_SOURCES frame.cc)
endif()

if(BLAZE_BUNDLE)
  list(APPEND BENCHMARK_SOURCES bundle.cc)
endif()

if(BLAZE_FORMAT)
  list(APPEND BENCHMARK_SOURCES format.cc)
endif()

if(BLAZE_COMPILER AND BLAZE_EVALUATOR AND BLAZE_OUTPUT)
  list(APPEND BENCHMARK_SOURCES
    micro/allocator_profile.cc
    e2e/runner.cc
    micro/draft4.cc
    micro/draft6.cc
    micro/draft7.cc
    micro/2019_09.cc
    micro/2020_12.cc)
endif()

if(BLAZE_ALTERSCHEMA)
  list(APPEND BENCHMARK_SOURCES alterschema.cc)
endif()

if(BENCHMARK_SOURCES)
  sourcemeta_googlebenchmark(NAMESPACE sourcemeta PROJECT blaze
    FOLDER "Blaze" SOURCES ${BENCHMARK_SOURCES})
  target_compile_definitions(sourcemeta_blaze_benchmark
    PRIVATE CURRENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta::core::io)
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta::core::jsonl)
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta::blaze::foundation)

  if(BLAZE_COMPILER)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::compiler)
  endif()
  if(BLAZE_EVALUATOR)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::evaluator)
  endif()
  if(BLAZE_OUTPUT)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::output)
  endif()
  if(BLAZE_ALTERSCHEMA)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::alterschema)
  endif()
  if(BLAZE_FOUNDATION)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::foundation)
  endif()
  if(BLAZE_FRAME)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::frame)
  endif()
  if(BLAZE_BUNDLE)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::bundle)
  endif()
  if(BLAZE_FORMAT)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::format)
  endif()
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta_blaze_allocator)

  add_custom_target(benchmark_all
    COMMAND sourcemeta_blaze_benchmark
    DEPENDS sourcemeta_blaze_benchmark
    COMMENT "Running benchmark...")
  add_custom_target(benchmark_json
    COMMAND sourcemeta_blaze_benchmark
      --benchmark_format=json
      --benchmark_out="${PROJECT_BINARY_DIR}/benchmark.json"
    DEPENDS sourcemeta_blaze_benchmark
    COMMENT "Running benchmark...")
else()
  add_custom_target(benchmark_all VERBATIM
    COMMAND "${CMAKE_COMMAND}" -E echo "Nothing to benchmark"
    COMMAND "${CMAKE_COMMAND}" -E false)
  add_custom_target(benchmark_json VERBATIM
    COMMAND "${CMAKE_COMMAND}" -E echo "Nothing to benchmark"
    COMMAND "${CMAKE_COMMAND}" -E false)
endif()
