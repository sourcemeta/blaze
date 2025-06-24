sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME compiler
  FOLDER "Blaze/Compiler"
  SOURCES compile_json.cc)

target_link_libraries(sourcemeta_blaze_compiler PUBLIC
  sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_compiler PRIVATE
  sourcemeta::core::regex)
target_link_libraries(sourcemeta_blaze_compiler PUBLIC
  sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_compiler PRIVATE
  sourcemeta::core::uri)
target_link_libraries(sourcemeta_blaze_compiler PUBLIC
  sourcemeta::core::jsonschema)
