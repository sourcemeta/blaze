noa_library(NAMESPACE sourcemeta PROJECT jsontoolkit NAME regex
  FOLDER "JSON Toolkit/Regex"
  SOURCES regex.cc)

target_link_libraries(sourcemeta_jsontoolkit_regex
  PUBLIC sourcemeta::jsontoolkit::json)

if(JSONTOOLKIT_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsontoolkit NAME regex)
endif()
