if(BLAZE_COMPILER AND BLAZE_EVALUATOR)
  add_executable(sourcemeta_blaze_contrib_validate validate.cc)
  noa_add_default_options(PRIVATE sourcemeta_blaze_contrib_validate)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::jsontoolkit::json)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::jsontoolkit::jsonl)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::jsontoolkit::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::blaze::compiler)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::blaze::evaluator)
endif()
