# Every rule this module applies as data, read from the JSON it is written in
# and emitted as one array of strings, so that adding a rule means adding a
# file and nothing else

if(NOT CANONICALIZER_RULES_OUTPUT)
  message(FATAL_ERROR "Missing CANONICALIZER_RULES_OUTPUT")
endif()
if(NOT CANONICALIZER_RULES_DIRECTORY)
  message(FATAL_ERROR "Missing CANONICALIZER_RULES_DIRECTORY")
endif()

file(GLOB CANONICALIZER_RULE_FILES
  "${CANONICALIZER_RULES_DIRECTORY}/*.json")
list(SORT CANONICALIZER_RULE_FILES)

set(CANONICALIZER_RULES_BODY
"#ifndef SOURCEMETA_BLAZE_CANONICALIZER_RULES_H_
#define SOURCEMETA_BLAZE_CANONICALIZER_RULES_H_

// Generated from the JSON files in `rules_json/` by `rules.cmake`. A rule is
// written and reviewed as JSON and reaches the compiler as a string

#include <array>       // std::array
#include <string_view> // std::string_view

inline constexpr std::array CANONICALIZER_RULES{
")

foreach(CANONICALIZER_RULE_FILE ${CANONICALIZER_RULE_FILES})
  file(READ "${CANONICALIZER_RULE_FILE}" CANONICALIZER_RULE)

  # A rule that is not valid JSON would otherwise only fail once the module is
  # asked to canonicalize something
  string(JSON CANONICALIZER_RULE_LENGTH ERROR_VARIABLE CANONICALIZER_RULE_ERROR
    LENGTH "${CANONICALIZER_RULE}")
  if(CANONICALIZER_RULE_ERROR)
    message(FATAL_ERROR "Invalid JSON in ${CANONICALIZER_RULE_FILE}: "
      "${CANONICALIZER_RULE_ERROR}")
  endif()

  cmake_path(GET CANONICALIZER_RULE_FILE STEM CANONICALIZER_RULE_STEM)
  string(JSON CANONICALIZER_RULE_DECLARED GET "${CANONICALIZER_RULE}" name)
  if(NOT CANONICALIZER_RULE_DECLARED STREQUAL CANONICALIZER_RULE_STEM)
    message(FATAL_ERROR
      "Rule ${CANONICALIZER_RULE_FILE} calls itself ${CANONICALIZER_RULE_DECLARED}")
  endif()

  cmake_path(GET CANONICALIZER_RULE_FILE FILENAME CANONICALIZER_RULE_NAME)
  string(APPEND CANONICALIZER_RULES_BODY
    "    // ${CANONICALIZER_RULE_NAME}\n"
    "    std::string_view{R\"JSON(${CANONICALIZER_RULE})JSON\"},\n")
endforeach()

string(APPEND CANONICALIZER_RULES_BODY "};\n\n#endif\n")

# Editing a rule has to regenerate the header, which only happens if CMake
# knows the rules are inputs to the configure step that read them
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
  ${CANONICALIZER_RULE_FILES})

# Written through a staging file so that a configure that changes no rule
# leaves the header alone, and nothing downstream recompiles
file(WRITE "${CANONICALIZER_RULES_OUTPUT}.staging"
  "${CANONICALIZER_RULES_BODY}")
configure_file("${CANONICALIZER_RULES_OUTPUT}.staging"
  "${CANONICALIZER_RULES_OUTPUT}" COPYONLY)
