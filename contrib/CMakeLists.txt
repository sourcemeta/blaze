if(BLAZE_COMPILER AND BLAZE_EVALUATOR)
  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_compile
    FOLDER "Blaze/Contrib" SOURCES compile.cc)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::core::jsonpointer)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::core::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::core::options)
  target_link_libraries(sourcemeta_blaze_contrib_compile
    PRIVATE sourcemeta::blaze::compiler)

  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_validate
    FOLDER "Blaze/Contrib" SOURCES validate.cc)
  target_link_libraries(sourcemeta_blaze_contrib_validate
    PRIVATE sourcemeta::core::io)
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
    PRIVATE sourcemeta::core::options)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::compiler)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::evaluator)
  target_link_libraries(sourcemeta_blaze_contrib_trace
    PRIVATE sourcemeta::blaze::output)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_perf
      FOLDER "Blaze/Contrib" SOURCES perf.cc)
    target_link_libraries(sourcemeta_blaze_contrib_perf
      PRIVATE sourcemeta::core::io)
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

if(BLAZE_CODEGEN)
  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze NAME contrib_typescript
    FOLDER "Blaze/Contrib" SOURCES typescript.cc)
  target_link_libraries(sourcemeta_blaze_contrib_typescript
    PRIVATE sourcemeta::blaze::codegen)
  target_link_libraries(sourcemeta_blaze_contrib_typescript
    PRIVATE sourcemeta::core::options)
endif()

if(BLAZE_ALTERSCHEMA)
  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze
    NAME contrib_canonicalize
    FOLDER "Blaze/Contrib" SOURCES canonicalize.cc)
  target_link_libraries(sourcemeta_blaze_contrib_canonicalize
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_contrib_canonicalize
    PRIVATE sourcemeta::core::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_canonicalize
    PRIVATE sourcemeta::blaze::alterschema)
endif()

if(BLAZE_DOCUMENTATION)
  sourcemeta_executable(NAMESPACE sourcemeta PROJECT blaze
    NAME contrib_document
    FOLDER "Blaze/Contrib" SOURCES document.cc)
  target_link_libraries(sourcemeta_blaze_contrib_document
    PRIVATE sourcemeta::core::json)
  target_link_libraries(sourcemeta_blaze_contrib_document
    PRIVATE sourcemeta::core::jsonschema)
  target_link_libraries(sourcemeta_blaze_contrib_document
    PRIVATE sourcemeta::core::html)
  target_link_libraries(sourcemeta_blaze_contrib_document
    PRIVATE sourcemeta::core::options)
  target_link_libraries(sourcemeta_blaze_contrib_document
    PRIVATE sourcemeta::blaze::documentation)
endif()
