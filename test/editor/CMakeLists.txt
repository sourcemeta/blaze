sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME editor
  FOLDER "Blaze/Editor"
  SOURCES editor_test.cc)

target_link_libraries(sourcemeta_blaze_editor_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_editor_unit
  PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_editor_unit
  PRIVATE sourcemeta::blaze::editor)
