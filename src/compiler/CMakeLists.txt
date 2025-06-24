sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME compiler
  FOLDER "Blaze/Compiler"
  SOURCES compile_json.cc)
target_link_libraries(sourcemeta_blaze_compiler PUBLIC
  sourcemeta::core::json)
