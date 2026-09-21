sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME bundle
  SOURCES
    bundle_container_test.cc
    bundle_dependencies_test.cc)

target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::blaze::bundle)

# Complete bundling tests, expressed as JSON fixtures
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME bundle_suite
  SOURCES bundlesuite.cc)
target_compile_definitions(sourcemeta_blaze_bundle_suite_unit
  PRIVATE BUNDLE_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/bundle/suite")
target_link_libraries(sourcemeta_blaze_bundle_suite_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_bundle_suite_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_bundle_suite_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_bundle_suite_unit
  PRIVATE sourcemeta::blaze::bundle)

set_tests_properties(blaze.bundle_suite PROPERTIES TIMEOUT 60)
