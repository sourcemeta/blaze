sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME convert
  SOURCES
    convert_draft3_to_draft4_test.cc
    convert_draft3_to_draft6_test.cc
    convert_draft3_to_draft7_test.cc
    convert_draft3_to_2019_09_test.cc
    convert_draft3_to_2020_12_test.cc
    convert_draft4_to_draft6_test.cc
    convert_draft4_to_draft7_test.cc
    convert_draft4_to_2019_09_test.cc
    convert_draft6_to_draft7_test.cc
    convert_draft6_to_2019_09_test.cc
    convert_draft7_to_2019_09_test.cc
    convert_2019_09_to_2020_12_test.cc
    convert_draft4_to_2020_12_test.cc
    convert_draft6_to_2020_12_test.cc
    convert_draft7_to_2020_12_test.cc
    convert_test_utils.h)

target_link_libraries(sourcemeta_blaze_convert_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_convert_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_convert_unit
  PRIVATE sourcemeta::blaze::convert)

set_tests_properties(blaze.convert PROPERTIES TIMEOUT 60)
