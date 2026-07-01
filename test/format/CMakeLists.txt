sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME format
  SOURCES format_test.cc)

target_link_libraries(sourcemeta_blaze_format_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_format_unit
  PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_format_unit
  PRIVATE sourcemeta::blaze::format)
