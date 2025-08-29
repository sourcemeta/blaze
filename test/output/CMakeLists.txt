sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME output
  FOLDER "Blaze/Output"
  SOURCES
    output_simple_test.cc
    output_standard_flag_test.cc
    output_standard_basic_test.cc
    output_trace_test.cc)

target_link_libraries(sourcemeta_blaze_output_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_output_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_output_unit
  PRIVATE sourcemeta::blaze::output)
target_link_libraries(sourcemeta_blaze_output_unit
  PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_output_unit
  PRIVATE sourcemeta::blaze::compiler)
