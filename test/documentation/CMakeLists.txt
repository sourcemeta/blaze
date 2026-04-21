sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME documentation
  FOLDER "Blaze/Documentation"
  SOURCES
    documentation_test_utils.h
    documentation_2020_12_test.cc
    documentation_html_test.cc)

target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::documentation)

target_compile_definitions(sourcemeta_blaze_documentation_unit
  PRIVATE SCHEMAS_PATH="${PROJECT_SOURCE_DIR}/schemas")
