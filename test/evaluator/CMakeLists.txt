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
  SOURCES tracesuite.cc tracesuite.h)
target_compile_definitions(sourcemeta_blaze_evaluator_trace_suite_unit
  PRIVATE TRACE_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/evaluator/suite")
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_unit PRIVATE sourcemeta::blaze::evaluator)

# Evaluator trace suite with canonicalization (JSON-driven)
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME evaluator_trace_suite_canonical
  SOURCES tracesuite_canonical.cc tracesuite.h)
target_compile_definitions(sourcemeta_blaze_evaluator_trace_suite_canonical_unit
  PRIVATE TRACE_SUITE_CANONICAL_PATH="${PROJECT_SOURCE_DIR}/test/evaluator/suite")
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_canonical_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_canonical_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_canonical_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_canonical_unit PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_evaluator_trace_suite_canonical_unit PRIVATE sourcemeta::blaze::canonicalizer)
# Canonicalising a schema and compiling the result costs far more than
# compiling it alone, and this suite now does that for the official
# meta-schemas and hyper-schemas too, which are the largest schemas it holds
set_tests_properties(blaze.evaluator_trace_suite_canonical PROPERTIES TIMEOUT 300)
