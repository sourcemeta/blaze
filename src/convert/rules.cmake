# Every rule this module applies as data, read from the JSON it is written in
# and emitted as one array of strings, so that adding a rule means adding a
# file and nothing else

if(NOT CONVERT_RULES_OUTPUT)
  message(FATAL_ERROR "Missing CONVERT_RULES_OUTPUT")
endif()
if(NOT CONVERT_RULES_DIRECTORY)
  message(FATAL_ERROR "Missing CONVERT_RULES_DIRECTORY")
endif()

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/patterns.json" CONVERT_PATTERNS)
string(JSON CONVERT_PATTERNS_LENGTH ERROR_VARIABLE CONVERT_PATTERNS_ERROR
  LENGTH "${CONVERT_PATTERNS}")
if(CONVERT_PATTERNS_ERROR)
  message(FATAL_ERROR "Invalid JSON in patterns.json: ${CONVERT_PATTERNS_ERROR}")
endif()

file(GLOB CONVERT_RULE_FILES "${CONVERT_RULES_DIRECTORY}/*.json")
list(SORT CONVERT_RULE_FILES)

set(CONVERT_RULES_BODY
"#ifndef SOURCEMETA_BLAZE_CONVERT_RULES_H_
#define SOURCEMETA_BLAZE_CONVERT_RULES_H_

// Generated from the JSON files in `rules/` by `rules.cmake`. A rule is
// written and reviewed as JSON and reaches the compiler as a string

#include <array>       // std::array
#include <string_view> // std::string_view

// patterns.json
inline constexpr auto CONVERT_PATTERNS = R\"JSON(${CONVERT_PATTERNS})JSON\";

inline constexpr std::array CONVERT_RULES{
")

foreach(CONVERT_RULE_FILE ${CONVERT_RULE_FILES})
  file(READ "${CONVERT_RULE_FILE}" CONVERT_RULE)

  # A rule that is not valid JSON would otherwise only fail once the module is
  # asked to convert something
  string(JSON CONVERT_RULE_LENGTH ERROR_VARIABLE CONVERT_RULE_ERROR
    LENGTH "${CONVERT_RULE}")
  if(CONVERT_RULE_ERROR)
    message(FATAL_ERROR
      "Invalid JSON in ${CONVERT_RULE_FILE}: ${CONVERT_RULE_ERROR}")
  endif()

  cmake_path(GET CONVERT_RULE_FILE STEM CONVERT_RULE_STEM)
  string(JSON CONVERT_RULE_DECLARED GET "${CONVERT_RULE}" name)
  if(NOT CONVERT_RULE_DECLARED STREQUAL CONVERT_RULE_STEM)
    message(FATAL_ERROR
      "Rule ${CONVERT_RULE_FILE} calls itself ${CONVERT_RULE_DECLARED}")
  endif()

  cmake_path(GET CONVERT_RULE_FILE FILENAME CONVERT_RULE_NAME)
  string(APPEND CONVERT_RULES_BODY
    "    // ${CONVERT_RULE_NAME}\n"
    "    std::string_view{R\"JSON(${CONVERT_RULE})JSON\"},\n")
endforeach()

string(APPEND CONVERT_RULES_BODY "};\n\n#endif\n")

# Editing a rule has to regenerate the header, which only happens if CMake
# knows the rules are inputs to the configure step that read them
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
  ${CONVERT_RULE_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/patterns.json")

# Written through a staging file so that a configure that changes no rule
# leaves the header alone, and nothing downstream recompiles
file(WRITE "${CONVERT_RULES_OUTPUT}.staging" "${CONVERT_RULES_BODY}")
configure_file("${CONVERT_RULES_OUTPUT}.staging" "${CONVERT_RULES_OUTPUT}"
  COPYONLY)
