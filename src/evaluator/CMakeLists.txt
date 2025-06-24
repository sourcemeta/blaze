sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME evaluator
  FOLDER "Blaze/Evaluator"
  PRIVATE_HEADERS string_set.h
  SOURCES evaluator_string_set.cc)

target_link_libraries(sourcemeta_blaze_evaluator PUBLIC
  sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_evaluator PUBLIC
  sourcemeta::core::regex)
target_link_libraries(sourcemeta_blaze_evaluator PUBLIC
  sourcemeta::core::jsonpointer)
target_link_libraries(sourcemeta_blaze_evaluator PRIVATE
  sourcemeta::core::uri)
