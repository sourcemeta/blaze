set(BENCHMARK_SOURCES)

if(BLAZE_COMPILER)
  list(APPEND BENCHMARK_SOURCES compiler_draft6.cc)
endif()
if(BLAZE_EVALUATOR)
  list(APPEND BENCHMARK_SOURCES
    evaluator_draft4.cc
    evaluator_draft6.cc
    evaluator_draft7.cc
    evaluator_2020_12.cc)
endif()

if(BENCHMARK_SOURCES)
  add_executable(sourcemeta_blaze_benchmark ${BENCHMARK_SOURCES})
  noa_add_default_options(PRIVATE sourcemeta_blaze_benchmark)
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE benchmark::benchmark)
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE benchmark::benchmark_main)
  target_compile_definitions(sourcemeta_blaze_benchmark
    PRIVATE CURRENT_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta::jsontoolkit::json)
  target_link_libraries(sourcemeta_blaze_benchmark
    PRIVATE sourcemeta::jsontoolkit::jsonschema)

  if(BLAZE_COMPILER)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::compiler)
  endif()
  if(BLAZE_EVALUATOR)
    target_link_libraries(sourcemeta_blaze_benchmark
      PRIVATE sourcemeta::blaze::evaluator)
  endif()

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

if(BLAZE_COMPILER AND BLAZE_EVALUATOR)
  add_executable(sourcemeta_blaze_benchmark_validator_helper validator_helper.cc)
  noa_add_default_options(PRIVATE sourcemeta_blaze_benchmark_validator_helper)
  target_link_libraries(sourcemeta_blaze_benchmark_validator_helper
    PRIVATE sourcemeta::jsontoolkit::json)
  target_link_libraries(sourcemeta_blaze_benchmark_validator_helper
    PRIVATE sourcemeta::jsontoolkit::jsonl)
  target_link_libraries(sourcemeta_blaze_benchmark_validator_helper
    PRIVATE sourcemeta::jsontoolkit::jsonschema)
  target_link_libraries(sourcemeta_blaze_benchmark_validator_helper
    PRIVATE sourcemeta::blaze::compiler)
  target_link_libraries(sourcemeta_blaze_benchmark_validator_helper
    PRIVATE sourcemeta::blaze::evaluator)
endif()
