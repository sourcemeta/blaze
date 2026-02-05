sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME configuration
  SOURCES
    configuration_applies_to_test.cc
    configuration_find_test.cc
    configuration_from_json_test.cc
    configuration_read_json_test.cc)

target_compile_definitions(sourcemeta_blaze_configuration_unit
  PRIVATE TEST_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(sourcemeta_blaze_configuration_unit
  PRIVATE sourcemeta::core::uri)
target_link_libraries(sourcemeta_blaze_configuration_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_configuration_unit
  PRIVATE sourcemeta::blaze::configuration)
