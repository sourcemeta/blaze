cmake_minimum_required(VERSION 3.16)
project(sourcemeta_blaze_nodejs LANGUAGES C CXX)
set(BLAZE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
include("${BLAZE_ROOT}/vendor/core/cmake/Sourcemeta.cmake")
include_directories(${CMAKE_JS_INC})

set(BLAZE_INSTALL OFF CACHE BOOL "disable installation")
set(BLAZE_TESTS OFF CACHE BOOL "disable tests")
set(BLAZE_BENCHMARK OFF CACHE BOOL "disable benchmarks")
set(BLAZE_CONTRIB OFF CACHE BOOL "disable contrib")
set(BLAZE_DOCS OFF CACHE BOOL "disable docs")
set(BLAZE_LINTER OFF CACHE BOOL "disable linter")
set(SOURCEMETA_CORE_JSONL OFF CACHE BOOL "disable")
set(SOURCEMETA_CORE_PUNYCODE OFF CACHE BOOL "disable")
set(SOURCEMETA_CORE_LANG_PROCESS OFF CACHE BOOL "disable")
set(SOURCEMETA_CORE_LANG_PARALLEL OFF CACHE BOOL "disable")
set(SOURCEMETA_CORE_EXTENSION_ALTERSCHEMA OFF CACHE BOOL "disable")
set(SOURCEMETA_CORE_EXTENSION_EDITORSCHEMA OFF CACHE BOOL "disable")
set(SOURCEMETA_CORE_EXTENSION_SCHEMACONFIG OFF CACHE BOOL "disable")
add_subdirectory("${BLAZE_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}/blaze")

add_library(${PROJECT_NAME} SHARED
  src/addon.cc
  src/blaze_json.h
  src/blaze_schema.h
  ${CMAKE_JS_SRC})
sourcemeta_add_default_options(PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(${PROJECT_NAME} PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(${PROJECT_NAME} PRIVATE sourcemeta::blaze::output)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX ""
  SUFFIX ".node" OUTPUT_NAME "blaze")

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  execute_process(COMMAND ${CMAKE_AR}
    /def:${CMAKE_JS_NODELIB_DEF}
    /out:${CMAKE_JS_NODELIB_TARGET}
    ${CMAKE_STATIC_LINKER_FLAGS})
endif()
