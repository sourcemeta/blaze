noa_googletest(NAMESPACE sourcemeta PROJECT blaze NAME compiler
  FOLDER "Blaze/Compiler"
  SOURCES compiler_output_error_test.cc compiler_output_trace_test.cc)

target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::blaze::evaluator)
