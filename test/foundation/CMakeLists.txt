sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME foundation
  SOURCES
    foundation_reidentify_test.cc
    foundation_vocabulary_test.cc
    foundation_walker_2020_12_test.cc
    foundation_walker_2019_09_test.cc
    foundation_walker_draft7_test.cc
    foundation_walker_draft6_test.cc
    foundation_walker_draft4_test.cc
    foundation_walker_draft3_test.cc
    foundation_walker_draft2_test.cc
    foundation_walker_draft1_test.cc
    foundation_walker_draft0_test.cc
    foundation_walker_openapi_test.cc
    foundation_error_test.cc
    foundation_resolver_test.cc
    foundation_frame_test.cc
    foundation_frame_error_test.cc
    foundation_frame_limit_test.cc)

target_link_libraries(sourcemeta_blaze_foundation_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_foundation_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_foundation_unit
  PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_foundation_unit
  PRIVATE sourcemeta::core::uri)

if(MSVC)
  target_compile_options(sourcemeta_blaze_foundation_unit PRIVATE /bigobj)
endif()

# JSON Schema Referencing Suite
# See https://github.com/python-jsonschema/referencing-suite
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME referencing_suite
  SOURCES referencingsuite.cc)
target_compile_definitions(sourcemeta_blaze_referencing_suite_unit
  PRIVATE REFERENCING_SUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/referencing-suite/tests")
target_link_libraries(sourcemeta_blaze_referencing_suite_unit PRIVATE sourcemeta::core::uri)
target_link_libraries(sourcemeta_blaze_referencing_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_referencing_suite_unit PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_referencing_suite_unit PRIVATE sourcemeta::core::jsonpointer)

# Complete frame tests, expressed as JSON fixtures
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME frame_suite
  SOURCES framesuite.cc)
target_compile_definitions(sourcemeta_blaze_frame_suite_unit
  PRIVATE FRAME_SUITE_PATH="${PROJECT_SOURCE_DIR}/test/foundation/frame")
target_link_libraries(sourcemeta_blaze_frame_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_frame_suite_unit PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_frame_suite_unit PRIVATE sourcemeta::blaze::foundation)
