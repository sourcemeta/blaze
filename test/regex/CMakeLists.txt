noa_googletest(NAMESPACE sourcemeta PROJECT blaze NAME regex
  FOLDER "Blaze/Regex"
  SOURCES regex_matches_test.cc regex_to_regex_test.cc)

target_link_libraries(sourcemeta_blaze_regex_unit
  PRIVATE sourcemeta::blaze::regex)
