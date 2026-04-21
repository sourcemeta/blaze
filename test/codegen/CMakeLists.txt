sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME codegen
  FOLDER "Blaze/Codegen"
  SOURCES codegen_test.cc codegen_2020_12_test.cc
    codegen_symbol_test.cc codegen_test_utils.h)

target_link_libraries(sourcemeta_blaze_codegen_unit
  PRIVATE sourcemeta::blaze::codegen)

if(BLAZE_CODEGEN)
  add_subdirectory(e2e/typescript)
endif()
