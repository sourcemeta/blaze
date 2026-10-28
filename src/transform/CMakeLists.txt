sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME transform
  FOLDER "Blaze/Transform"
  SOURCES transform.cc
    transform_match.h
    transform_build.h)

if(BLAZE_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT blaze NAME transform)
endif()

target_link_libraries(sourcemeta_blaze_transform PUBLIC
  sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_transform PUBLIC
  sourcemeta::core::jsonpointer)
