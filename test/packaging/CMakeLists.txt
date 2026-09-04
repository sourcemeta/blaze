# TODO: Get install path from a variable?
set(BLAZE_PACKAGING_PREFIX "${PROJECT_SOURCE_DIR}/build/dist")

# Consumers routinely have a prefix like this ahead of ours on their search
# path, so every case below resolves Blaze with it in the way
set(BLAZE_PACKAGING_DECOY "${CMAKE_CURRENT_SOURCE_DIR}/decoy")

# Every case starts from scratch. Otherwise a stale cache in the consumer build
# directories keeps resolving whatever a previous run already found, and the
# decoy prefix never gets a chance to bite
add_test(NAME packaging.clean COMMAND
  "${CMAKE_COMMAND}" -E rm -rf
  "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  "${CMAKE_CURRENT_BINARY_DIR}/meson")
set_tests_properties(packaging.clean PROPERTIES FIXTURES_SETUP packaging)

add_test(NAME packaging.prefix COMMAND
  "${CMAKE_COMMAND}"
  "-DBLAZE_PACKAGING_PREFIX:PATH=${BLAZE_PACKAGING_PREFIX}"
  -P "${CMAKE_CURRENT_SOURCE_DIR}/prefix.cmake")

add_test(NAME packaging.find_package_configure COMMAND
  "${CMAKE_COMMAND}"
  -S "${CMAKE_CURRENT_SOURCE_DIR}/find_package"
  -B "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
  "-DCMAKE_PREFIX_PATH:PATH=${BLAZE_PACKAGING_DECOY};${CMAKE_PREFIX_PATH};${BLAZE_PACKAGING_PREFIX}"
  "-DCMAKE_TOOLCHAIN_FILE:PATH=${CMAKE_TOOLCHAIN_FILE}")
set_tests_properties(packaging.find_package_configure
  PROPERTIES FIXTURES_REQUIRED packaging)
add_test(NAME packaging.find_package_build COMMAND
  "${CMAKE_COMMAND}"
  --build "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  --config "${CMAKE_BUILD_TYPE}")
set_tests_properties(packaging.find_package_build
  PROPERTIES DEPENDS packaging.find_package_configure
  FIXTURES_REQUIRED packaging)

# The consumer writes out whatever it inherited from the installation, which
# must be nothing at all
add_test(NAME packaging.find_package_options COMMAND
  "${CMAKE_COMMAND}" -E cat
  "${CMAKE_CURRENT_BINARY_DIR}/find_package/inherited-options.txt")
set_tests_properties(packaging.find_package_options
  PROPERTIES DEPENDS packaging.find_package_configure
  FIXTURES_REQUIRED packaging
  FAIL_REGULAR_EXPRESSION ".")

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
    "-Dblaze_prefix=${BLAZE_PACKAGING_DECOY},${BLAZE_PACKAGING_PREFIX}")
  set_tests_properties(packaging.meson_setup
    PROPERTIES FIXTURES_REQUIRED packaging)
  add_test(NAME packaging.meson_compile COMMAND
    "${MESON_EXECUTABLE}" compile -C "${CMAKE_CURRENT_BINARY_DIR}/meson")
  set_tests_properties(packaging.meson_compile
    PROPERTIES DEPENDS packaging.meson_setup
    FIXTURES_REQUIRED packaging)
  add_test(NAME packaging.meson_test COMMAND
    "${MESON_EXECUTABLE}" test -C "${CMAKE_CURRENT_BINARY_DIR}/meson")
  set_tests_properties(packaging.meson_test
    PROPERTIES DEPENDS packaging.meson_compile
    FIXTURES_REQUIRED packaging)
endif()
