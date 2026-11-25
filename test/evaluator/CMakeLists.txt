sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME evaluator
  SOURCES
    evaluator_utils.h
    suite_compatibility.h
    evaluator_test.cc
    suite_compatibility_test.cc)

target_link_libraries(sourcemeta_blaze_evaluator_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_unit
  PRIVATE sourcemeta::blaze::evaluator)

if(MSVC)
  # error C1128: number of sections exceeded object file format limit: compile with /bigobj
  target_compile_options(sourcemeta_blaze_evaluator_unit PRIVATE "/bigobj")
endif()

# JSON Schema Test Suite
# See https://github.com/json-schema-org/JSON-Schema-Test-Suite
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME evaluator_official_suite
  SOURCES officialsuite.cc suite_compatibility.h)
target_compile_definitions(sourcemeta_blaze_evaluator_official_suite_unit
  PRIVATE OFFICIAL_SUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/jsonschema-test-suite")
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::blaze::evaluator)

# JSON Schema Test Suite (annotations)
# See https://github.com/json-schema-org/JSON-Schema-Test-Suite/tree/main/annotations
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME evaluator_annotation_suite
  SOURCES annotationsuite.cc suite_compatibility.h)
target_compile_definitions(sourcemeta_blaze_evaluator_annotation_suite_unit
  PRIVATE ANNOTATION_SUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/jsonschema-test-suite/annotations/tests")
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::blaze::output)

# Evaluator trace suite (JSON-driven trace tests)
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME evaluator_trace_suite
  SOURCES tracesuite.cc)
target_compile_definitions(sourcemeta_blaze_evaluator_trace_suite_unit
  PRIVATE TRACE_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/evaluator/suite")
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::blaze::evaluator)

