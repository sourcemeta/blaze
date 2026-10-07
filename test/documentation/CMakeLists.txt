sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME documentation
  SOURCES
    documentation_test_utils.h
    documentation_2020_12_test.cc
    documentation_draft7_test.cc
    documentation_html_test.cc)

target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_documentation_unit
  PRIVATE sourcemeta::blaze::documentation)
