# TODO: Get install path from a variable?
add_test(NAME packaging.find_package_configure COMMAND
  "${CMAKE_COMMAND}"
  -S "${CMAKE_CURRENT_SOURCE_DIR}/find_package"
  -B "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
  "-DCMAKE_PREFIX_PATH:PATH=${CMAKE_PREFIX_PATH};${PROJECT_SOURCE_DIR}/build/dist"
  "-DCMAKE_TOOLCHAIN_FILE:PATH=${CMAKE_TOOLCHAIN_FILE}")
add_test(NAME packaging.find_package_build COMMAND
  "${CMAKE_COMMAND}"
  --build "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  --config "${CMAKE_BUILD_TYPE}")
set_tests_properties(packaging.find_package_build
  PROPERTIES DEPENDS packaging.find_package_configure)

find_program(MESON_EXECUTABLE NAMES meson)
if(MESON_EXECUTABLE)
  add_test(NAME packaging.meson_setup COMMAND
    "${MESON_EXECUTABLE}" setup --reconfigure
    "${CMAKE_CURRENT_BINARY_DIR}/meson"
    "${CMAKE_CURRENT_SOURCE_DIR}/meson"
    "-Dcmake_prefix_path=${PROJECT_SOURCE_DIR}/build/dist")
  add_test(NAME packaging.meson_compile COMMAND
    "${MESON_EXECUTABLE}" compile -C "${CMAKE_CURRENT_BINARY_DIR}/meson")
  set_tests_properties(packaging.meson_compile
    PROPERTIES DEPENDS packaging.meson_setup)
endif()
