sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME test
  FOLDER "Blaze/Test"
  SOURCES test_case_test.cc test_suite_test.cc test_run_test.cc)

target_link_libraries(sourcemeta_blaze_test_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_test_unit
  PRIVATE sourcemeta::core::uri)
target_link_libraries(sourcemeta_blaze_test_unit
  PRIVATE sourcemeta::core::yaml)
target_link_libraries(sourcemeta_blaze_test_unit
  PRIVATE sourcemeta::blaze::test)

target_compile_definitions(sourcemeta_blaze_test_unit
  PRIVATE STUBS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/stubs")
