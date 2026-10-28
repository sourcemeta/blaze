sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME convert
  SOURCES
    convert_boolean_test.cc)

target_link_libraries(sourcemeta_blaze_convert_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_convert_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_convert_unit
  PRIVATE sourcemeta::blaze::convert)

set_tests_properties(blaze.convert PROPERTIES TIMEOUT 60)

# Complete conversion tests, expressed as JSON fixtures
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME convert_suite
  SOURCES convertsuite.cc)
target_compile_definitions(sourcemeta_blaze_convert_suite_unit
  PRIVATE CONVERT_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/convert/suite")
target_link_libraries(sourcemeta_blaze_convert_suite_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_convert_suite_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_convert_suite_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_convert_suite_unit
  PRIVATE sourcemeta::blaze::convert)
target_link_libraries(sourcemeta_blaze_convert_suite_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_convert_suite_unit
  PRIVATE sourcemeta::blaze::evaluator)

# The rules are interpreted from JSON rather than compiled, which roughly
# doubles what this suite costs. The interpreter is a spike and is not
# optimised, so the budget is raised rather than the suite trimmed
set_tests_properties(blaze.convert_suite PROPERTIES TIMEOUT 180)
