# The dependencies that this project vendors and links statically are an
# implementation detail. Installing their headers would shadow, or be shadowed
# by, the real ones on any prefix that a consumer shares with other libraries
file(GLOB BLAZE_PACKAGING_HEADERS "${BLAZE_PACKAGING_PREFIX}/include/*")
foreach(entry IN LISTS BLAZE_PACKAGING_HEADERS)
  get_filename_component(name "${entry}" NAME)
  if(NOT name STREQUAL "sourcemeta")
    message(FATAL_ERROR
      "The installation prefix exposes a vendored header: ${name}")
  endif()
endforeach()
