if(NOT GoogleTest_FOUND)
  set(BUILD_GMOCK ON CACHE BOOL "enable googlemock")
  set(INSTALL_GTEST OFF CACHE BOOL "disable installation")
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/googletest")
  set(GoogleTest_FOUND ON)
endif()
