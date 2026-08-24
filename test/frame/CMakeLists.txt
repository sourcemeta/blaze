sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME frame
  SOURCES
    frame_test_utils.h
    frame_2020_12_test.cc
    frame_2019_09_test.cc
    frame_draft7_test.cc
    frame_draft6_test.cc
    frame_draft4_test.cc
    frame_draft3_test.cc
    frame_draft2_test.cc
    frame_draft1_test.cc
    frame_draft0_test.cc
    frame_test.cc)

target_link_libraries(sourcemeta_blaze_frame_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_frame_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_frame_unit
  PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_frame_unit
  PRIVATE sourcemeta::blaze::frame)

if(MSVC)
  target_compile_options(sourcemeta_blaze_frame_unit PRIVATE /bigobj)
endif()

# JSON Schema Referencing Suite
# See https://github.com/python-jsonschema/referencing-suite
sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME frame_referencing_suite
  SOURCES referencingsuite.cc)
target_compile_definitions(sourcemeta_blaze_frame_referencing_suite_unit
  PRIVATE REFERENCING_SUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/referencing-suite/tests")
target_link_libraries(sourcemeta_blaze_frame_referencing_suite_unit PRIVATE sourcemeta::core::uri)
target_link_libraries(sourcemeta_blaze_frame_referencing_suite_unit PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_frame_referencing_suite_unit PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_frame_referencing_suite_unit PRIVATE sourcemeta::blaze::frame)
target_link_libraries(sourcemeta_blaze_frame_referencing_suite_unit PRIVATE sourcemeta::core::jsonpointer)
