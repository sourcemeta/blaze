cmake_minimum_required(VERSION 3.16)
project(blaze VERSION 0.0.1 LANGUAGES CXX
  DESCRIPTION "The ultra high-performance JSON Schema evaluator"
  HOMEPAGE_URL "https://github.com/sourcemeta/blaze")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(Core REQUIRED)
add_subdirectory(src/compiler)
add_subdirectory(src/evaluator)
