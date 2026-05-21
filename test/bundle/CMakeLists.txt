sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME bundle
  FOLDER "Blaze/Bundle"
  SOURCES
    bundle_2020_12_test.cc
    bundle_2019_09_test.cc
    bundle_draft7_test.cc
    bundle_draft6_test.cc
    bundle_draft4_test.cc
    bundle_draft3_test.cc
    bundle_draft2_test.cc
    bundle_draft1_test.cc
    bundle_draft0_test.cc
    bundle_test.cc
    bundle_dependencies_test.cc)

target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_bundle_unit
  PRIVATE sourcemeta::blaze::bundle)
