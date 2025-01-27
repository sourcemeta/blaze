noa_library(NAMESPACE sourcemeta PROJECT blaze NAME regex
  FOLDER "Blaze/Regex")

if(NOA_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT blaze NAME regex)
endif()

target_link_libraries(sourcemeta_blaze_regex INTERFACE Boost::regex)
