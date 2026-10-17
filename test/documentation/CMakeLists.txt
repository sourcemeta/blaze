sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME documentation
  SOURCES
    documentation_test_utils.h
    documentation_refusal_test.cc
    documentation_dialect_test.cc
    documentation_html_test.cc)

target_compile_definitions(sourcemeta_blaze_documentation_unit
  PRIVATE TABLE_FORMAT_SCHEMA_PATH="${PROJECT_SOURCE_DIR}/schemas/table-format.json")

target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::documentation)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::evaluator)

# Complete descriptions, expressed as fixtures of real data
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME documentation_suite
  SOURCES documentationsuite.cc)
target_compile_definitions(sourcemeta_blaze_documentation_suite_unit
  PRIVATE DOCUMENTATION_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/documentation/suite")
target_compile_definitions(sourcemeta_blaze_documentation_suite_unit
  PRIVATE TABLE_FORMAT_SCHEMA_PATH="${PROJECT_SOURCE_DIR}/schemas/table-format.json")
target_link_libraries(sourcemeta_blaze_documentation_suite_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_documentation_suite_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_documentation_suite_unit
  PRIVATE sourcemeta::blaze::documentation)
target_link_libraries(sourcemeta_blaze_documentation_suite_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_documentation_suite_unit
  PRIVATE sourcemeta::blaze::evaluator)
