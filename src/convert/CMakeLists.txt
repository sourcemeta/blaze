set(CONVERT_RULES_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/rules.h")
set(CONVERT_RULES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/rules")
include(./rules.cmake)

sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME convert
  FOLDER "Blaze/Convert"
  PRIVATE_HEADERS error.h
  SOURCES convert.cc
    rule.h
    helpers.h
    analysis_2019_09.h
    template_rule.h)

if(BLAZE_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT blaze NAME convert)
endif()

target_include_directories(sourcemeta_blaze_convert PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(sourcemeta_blaze_convert PUBLIC
  sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_convert PRIVATE
  sourcemeta::blaze::transform)
target_link_libraries(sourcemeta_blaze_convert PRIVATE
  sourcemeta::core::uri)
