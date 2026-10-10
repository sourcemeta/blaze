sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME compiler
  SOURCES
    compiler_json_test.cc
    compiler_limit_test.cc)

target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::blaze::evaluator)
