sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME linter
  FOLDER "Blaze/Linter"
  SOURCES
    linter_schema_test.cc
    linter_valid_default_test.cc
    linter_valid_examples_test.cc)

target_link_libraries(sourcemeta_blaze_linter_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_linter_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_linter_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_linter_unit
  PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_linter_unit
  PRIVATE sourcemeta::blaze::linter)
