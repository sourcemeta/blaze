noa_library(NAMESPACE sourcemeta PROJECT jsontoolkit NAME json
  FOLDER "JSON Toolkit/JSON"
  PRIVATE_HEADERS array.h error.h object.h value.h hash.h
  SOURCES grammar.h parser.h stringify.h json.cc json_value.cc)

target_link_libraries(sourcemeta_jsontoolkit_json PUBLIC
  ankerl::unordered_dense)

if(JSONTOOLKIT_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsontoolkit NAME json)
endif()
