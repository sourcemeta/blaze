sourcemeta_googletest(NAMESPACE sourcemeta PROJECT blaze NAME codegen_e2e_typescript
  FOLDER "Blaze/Codegen/E2E/TypeScript"
  SOURCES e2e.cc)

target_link_libraries(sourcemeta_blaze_codegen_e2e_typescript_unit
  PRIVATE sourcemeta::blaze::codegen)
target_compile_definitions(sourcemeta_blaze_codegen_e2e_typescript_unit
  PRIVATE E2E_TYPESCRIPT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

if(WIN32)
  set(TSC_BIN "${PROJECT_SOURCE_DIR}/node_modules/.bin/tsc.cmd")
else()
  set(TSC_BIN "${PROJECT_SOURCE_DIR}/node_modules/.bin/tsc")
endif()

set(E2E_SCHEMAS "")
file(GLOB TYPESCRIPT_DIALECT_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(DIALECT_DIRECTORY ${TYPESCRIPT_DIALECT_DIRECTORIES})
  if(IS_DIRECTORY ${DIALECT_DIRECTORY})
    get_filename_component(DIALECT_NAME ${DIALECT_DIRECTORY} NAME)
    file(GLOB TYPESCRIPT_CASE_DIRECTORIES "${DIALECT_DIRECTORY}/*")
    foreach(CASE_DIRECTORY ${TYPESCRIPT_CASE_DIRECTORIES})
      if(IS_DIRECTORY ${CASE_DIRECTORY})
        get_filename_component(CASE_NAME ${CASE_DIRECTORY} NAME)
        list(APPEND E2E_SCHEMAS "${CASE_DIRECTORY}/schema.json")
        add_test(NAME "blaze.codegen.e2e.typescript.tsc.${DIALECT_NAME}.${CASE_NAME}"
          COMMAND "${TSC_BIN}" --strict --noEmit
            "${CASE_DIRECTORY}/expected.d.ts"
            "${CASE_DIRECTORY}/test.ts")
      endif()
    endforeach()
  endif()
endforeach()
set(E2E_SCHEMAS "${E2E_SCHEMAS}" PARENT_SCOPE)
