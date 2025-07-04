sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME compiler
  FOLDER "Blaze/Compiler"
  PRIVATE_HEADERS error.h output.h unevaluated.h
  SOURCES
    compile.cc compile_describe.cc compile_json.cc
    compile_helpers.h default_compiler.cc unevaluated.cc
    compile_output_simple.cc
    compile_output_trace.cc
    compile_output_standard.cc
    default_compiler_2020_12.h
    default_compiler_2019_09.h
    default_compiler_draft7.h
    default_compiler_draft6.h
    default_compiler_draft4.h)

if(BLAZE_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT blaze NAME compiler)
endif()

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
target_link_libraries(sourcemeta_blaze_compiler PUBLIC
  sourcemeta::blaze::evaluator)
