function(noa_executable)
  cmake_parse_arguments(NOA_EXECUTABLE ""
    "NAMESPACE;PROJECT;NAME;FOLDER;VARIANT;OUTPUT" "SOURCES" ${ARGN})

  if(NOT NOA_EXECUTABLE_PROJECT)
    message(FATAL_ERROR "You must pass the project name using the PROJECT option")
  endif()
  if(NOT NOA_EXECUTABLE_NAME)
    message(FATAL_ERROR "You must pass the executable name using the NAME option")
  endif()
  if(NOT NOA_EXECUTABLE_FOLDER)
    message(FATAL_ERROR "You must pass the folder name using the FOLDER option")
  endif()
  if(NOT NOA_EXECUTABLE_SOURCES)
    message(FATAL_ERROR "You must pass the sources list using the SOURCES option")
  endif()

  if(NOA_EXECUTABLE_NAMESPACE)
    set(TARGET_NAME "${NOA_EXECUTABLE_NAMESPACE}_${NOA_EXECUTABLE_PROJECT}_${NOA_EXECUTABLE_NAME}")
  else()
    set(TARGET_NAME "${NOA_EXECUTABLE_PROJECT}_${NOA_EXECUTABLE_NAME}")
  endif()

  if(NOA_EXECUTABLE_VARIANT)
    set(TARGET_NAME "${TARGET_NAME}_${NOA_EXECUTABLE_VARIANT}")
  endif()

  if(NOA_EXECUTABLE_OUTPUT)
    set("${NOA_EXECUTABLE_OUTPUT}" "${TARGET_NAME}" PARENT_SCOPE)
  endif()

  add_executable("${TARGET_NAME}" ${NOA_EXECUTABLE_SOURCES})
  noa_add_default_options(PRIVATE ${TARGET_NAME})
  set_target_properties("${TARGET_NAME}" PROPERTIES FOLDER "${NOA_EXECUTABLE_FOLDER}")
endfunction()
