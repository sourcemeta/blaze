sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME dependencies
  SOURCES
    dependencies_test.cc)

target_link_libraries(sourcemeta_blaze_dependencies_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_dependencies_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_dependencies_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_dependencies_unit
  PRIVATE sourcemeta::blaze::dependencies)
