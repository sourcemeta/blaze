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
  # Meson defaults to a debug build, which on MSVC selects the debug runtime
  # and a different iterator debug level than the libraries it is linking
  # against, which the linker refuses to mix
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MESON_BUILD_TYPE debug)
  elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(MESON_BUILD_TYPE debugoptimized)
  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(MESON_BUILD_TYPE minsize)
  else()
    set(MESON_BUILD_TYPE release)
  endif()

  # Meson otherwise prefers whatever compiler it finds first on the system,
  # which on Windows is the MinGW GCC that the runners ship, while this project
  # is built with MSVC. The option is a no-op everywhere else
  add_test(NAME packaging.meson_setup COMMAND
    "${MESON_EXECUTABLE}" setup --reconfigure --vsenv
    "--buildtype=${MESON_BUILD_TYPE}"
    "${CMAKE_CURRENT_BINARY_DIR}/meson"
    "${CMAKE_CURRENT_SOURCE_DIR}/meson"
    "-Dcmake_prefix_path=${PROJECT_SOURCE_DIR}/build/dist")
  add_test(NAME packaging.meson_compile COMMAND
    "${MESON_EXECUTABLE}" compile -C "${CMAKE_CURRENT_BINARY_DIR}/meson")
  set_tests_properties(packaging.meson_compile
    PROPERTIES DEPENDS packaging.meson_setup)
endif()
