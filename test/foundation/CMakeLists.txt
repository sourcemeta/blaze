sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME foundation
  FOLDER "Blaze/Foundation"
  SOURCES
    foundation_identify_2020_12_test.cc
    foundation_identify_2019_09_test.cc
    foundation_identify_draft7_test.cc
    foundation_identify_draft6_test.cc
    foundation_identify_draft4_test.cc
    foundation_identify_draft3_test.cc
    foundation_identify_draft2_test.cc
    foundation_identify_draft1_test.cc
    foundation_identify_draft0_test.cc
    foundation_identify_test.cc
    foundation_is_schema_test.cc
    foundation_is_empty_schema_test.cc
    foundation_metaschema_test.cc
    foundation_dialect_test.cc
    foundation_dialect_2020_12_test.cc
    foundation_dialect_2019_09_test.cc
    foundation_dialect_draft7_test.cc
    foundation_dialect_draft6_test.cc
    foundation_dialect_draft4_test.cc
    foundation_dialect_draft3_test.cc
    foundation_dialect_draft2_test.cc
    foundation_dialect_draft1_test.cc
    foundation_dialect_draft0_test.cc
    foundation_base_dialect_test.cc
    foundation_base_dialect_2020_12_test.cc
    foundation_base_dialect_2019_09_test.cc
    foundation_base_dialect_draft7_test.cc
    foundation_base_dialect_draft6_test.cc
    foundation_base_dialect_draft4_test.cc
    foundation_base_dialect_draft3_test.cc
    foundation_base_dialect_draft2_test.cc
    foundation_base_dialect_draft1_test.cc
    foundation_base_dialect_draft0_test.cc
    foundation_vocabulary_2020_12_test.cc
    foundation_vocabulary_2019_09_test.cc
    foundation_vocabulary_draft7_test.cc
    foundation_vocabulary_draft6_test.cc
    foundation_vocabulary_draft4_test.cc
    foundation_vocabulary_draft3_test.cc
    foundation_vocabulary_draft2_test.cc
    foundation_vocabulary_draft1_test.cc
    foundation_vocabulary_draft0_test.cc
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
    foundation_walker_test.cc
    foundation_error_test.cc
    foundation_keyword_iterator_test.cc
    foundation_resolver_test.cc
    foundation_parse_type_test.cc
    foundation_json_auto_test.cc)

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
