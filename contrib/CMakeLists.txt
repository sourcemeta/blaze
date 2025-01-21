if(BLAZE_COMPILER AND BLAZE_EVALUATOR)
  noa_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_validate 
    FOLDER "Blaze/Contrib" SOURCES validate.cc)
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

  noa_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_trace 
    FOLDER "Blaze/Contrib" SOURCES trace.cc)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::jsontoolkit::json)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::jsontoolkit::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::compiler)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::evaluator)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    noa_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_perf 
      FOLDER "Blaze/Contrib" SOURCES perf.cc)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::jsontoolkit::json)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::jsontoolkit::jsonl)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::jsontoolkit::jsonschema)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::blaze::compiler)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::blaze::evaluator)
  endif()
endif()
