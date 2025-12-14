sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME evaluator
  FOLDER "Blaze/Evaluator"
  SOURCES
    evaluator_utils.h
    evaluator_2019_09_test.cc
    evaluator_2020_12_test.cc
    evaluator_draft4_test.cc
    evaluator_draft6_test.cc
    evaluator_draft7_test.cc
    evaluator_openapi_3_1_test.cc
    evaluator_openapi_3_2_test.cc
    evaluator_test.cc)

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
sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME evaluator_official_suite
  FOLDER "Blaze/Evaluator" SOURCES officialsuite.cc)
target_compile_definitions(sourcemeta_blaze_evaluator_official_suite_unit
  PRIVATE OFFICIAL_SUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/jsonschema-test-suite")
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_official_suite_unit PRIVATE sourcemeta::blaze::evaluator)

# JSON Schema Test Suite (annotations)
# See https://github.com/json-schema-org/JSON-Schema-Test-Suite/tree/main/annotations
sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME evaluator_annotation_suite
  FOLDER "Blaze/Evaluator" SOURCES annotationsuite.cc)
target_compile_definitions(sourcemeta_blaze_evaluator_annotation_suite_unit
  PRIVATE ANNOTATION_SUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/jsonschema-test-suite/annotations/tests")
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_evaluator_annotation_suite_unit PRIVATE sourcemeta::blaze::output)
