sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME canonicalizer
  SOURCES
    canonicalizer_2020_12_test.cc
    canonicalizer_2019_09_test.cc
    canonicalizer_draft7_test.cc
    canonicalizer_draft6_test.cc
    canonicalizer_draft4_test.cc
    canonicalizer_draft3_test.cc
    canonicalizer_draft2_test.cc
    canonicalizer_draft1_test.cc
    canonicalizer_draft0_test.cc
    canonicalizer_test_utils.h)

target_link_libraries(sourcemeta_blaze_canonicalizer_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_canonicalizer_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_canonicalizer_unit
  PRIVATE sourcemeta::blaze::canonicalizer)
target_link_libraries(sourcemeta_blaze_canonicalizer_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_canonicalizer_unit
  PRIVATE sourcemeta::blaze::evaluator)
target_compile_definitions(sourcemeta_blaze_canonicalizer_unit
  PRIVATE SCHEMAS_PATH="${PROJECT_SOURCE_DIR}/schemas")

set_tests_properties(blaze.canonicalizer PROPERTIES TIMEOUT 90)

# Complete draft 3 canonicalization tests, expressed as JSON fixtures
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME canonicalizer_suite
  SOURCES canonicalizersuite.cc)
target_compile_definitions(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE CANONICALIZER_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/canonicalizer")
target_compile_definitions(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE SCHEMAS_PATH="${PROJECT_SOURCE_DIR}/schemas")
target_link_libraries(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE sourcemeta::blaze::canonicalizer)
target_link_libraries(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_canonicalizer_suite_unit
  PRIVATE sourcemeta::blaze::evaluator)

set_tests_properties(blaze.canonicalizer_suite PROPERTIES TIMEOUT 90)
