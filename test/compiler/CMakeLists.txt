add_executable(sourcemeta_blaze_compiler_unit
  compiler_output_error_test.cc
  compiler_output_trace_test.cc)
noa_add_default_options(PRIVATE sourcemeta_blaze_compiler_unit)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE GTest::gtest)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE GTest::gtest_main)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::regex)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_compiler_unit
  PRIVATE sourcemeta::blaze::evaluator)
add_test(NAME Compiler COMMAND sourcemeta_blaze_compiler_unit --gtest_brief=1)
set_target_properties(sourcemeta_blaze_compiler_unit
  PROPERTIES FOLDER "Blaze/Compiler")
