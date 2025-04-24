if(BLAZE_COMPILER AND BLAZE_EVALUATOR)
  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_compile
    FOLDER "Blaze/Contrib" SOURCES compile.cc)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::core::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::blaze::compiler)

  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_validate
    FOLDER "Blaze/Contrib" SOURCES validate.cc)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::core::jsonl)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::core::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::blaze::compiler)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::blaze::evaluator)

  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_trace
    FOLDER "Blaze/Contrib" SOURCES trace.cc)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::core::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::compiler)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::evaluator)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_perf
      FOLDER "Blaze/Contrib" SOURCES perf.cc)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::core::json)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::core::jsonl)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::core::jsonschema)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::blaze::compiler)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::blaze::evaluator)
  endif()
endif()
