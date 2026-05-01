sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME alterschema
  FOLDER "Blaze/AlterSchema"
  SOURCES
    alterschema_canonicalize_2020_12_test.cc
    alterschema_canonicalize_2019_09_test.cc
    alterschema_canonicalize_draft7_test.cc
    alterschema_canonicalize_draft6_test.cc
    alterschema_canonicalize_draft4_test.cc
    alterschema_canonicalize_draft3_test.cc
    alterschema_canonicalize_draft2_test.cc
    alterschema_canonicalize_draft1_test.cc
    alterschema_canonicalize_draft0_test.cc
    alterschema_lint_2020_12_test.cc
    alterschema_lint_2019_09_test.cc
    alterschema_lint_draft7_test.cc
    alterschema_lint_draft6_test.cc
    alterschema_lint_draft4_test.cc
    alterschema_lint_draft3_test.cc
    alterschema_lint_draft2_test.cc
    alterschema_lint_draft1_test.cc
    alterschema_lint_draft0_test.cc
    alterschema_lint_openapi_test.cc
    alterschema_upgrade_draft4_to_draft6_test.cc
    alterschema_upgrade_draft4_to_draft7_test.cc
    alterschema_upgrade_draft4_to_2019_09_test.cc
    alterschema_upgrade_draft6_to_draft7_test.cc
    alterschema_upgrade_draft6_to_2019_09_test.cc
    alterschema_upgrade_draft7_to_2019_09_test.cc
    alterschema_upgrade_2019_09_to_2020_12_test.cc
    alterschema_upgrade_draft4_to_2020_12_test.cc
    alterschema_upgrade_draft6_to_2020_12_test.cc
    alterschema_upgrade_draft7_to_2020_12_test.cc
    alterschema_schema_rule_test.cc
    alterschema_transform_rule_test.cc
    alterschema_transformer_test.cc
    alterschema_transform_rules.h
    alterschema_test_utils.h)

target_link_libraries(sourcemeta_blaze_alterschema_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_alterschema_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_alterschema_unit
  PRIVATE sourcemeta::blaze::alterschema)
target_link_libraries(sourcemeta_blaze_alterschema_unit
  PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_alterschema_unit
  PRIVATE sourcemeta::blaze::evaluator)
target_compile_definitions(sourcemeta_blaze_alterschema_unit
  PRIVATE SCHEMAS_PATH="${PROJECT_SOURCE_DIR}/schemas")

set_tests_properties(blaze.alterschema PROPERTIES TIMEOUT 60)
