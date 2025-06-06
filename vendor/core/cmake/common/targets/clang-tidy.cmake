function(sourcemeta_target_clang_tidy)
  cmake_parse_arguments(SOURCEMETA_TARGET_CLANG_TIDY "REQUIRED" "" "SOURCES" ${ARGN})

  set(CLANG_TIDY_FIND_PATHS "")

  # Locate ClangTidy on default Homebrew installations,
  # given that the LLVM formula won't symlink `clang-tidy`
  # to any available path by default.
  if(APPLE)
    if(IS_DIRECTORY "/opt/homebrew/Cellar")
      set(HOMEBREW_CELLAR "/opt/homebrew/Cellar")
    elseif(IS_DIRECTORY "/usr/local/Cellar")
      set(HOMEBREW_CELLAR "/opt/local/Cellar")
    endif()
    if(HOMEBREW_CELLAR)
      file(GLOB llvm_version_paths LIST_DIRECTORIES true "${HOMEBREW_CELLAR}/llvm*/*")
      foreach(llvm_version_path ${llvm_version_paths})
        list(APPEND CLANG_TIDY_FIND_PATHS "${llvm_version_path}/bin")
      endforeach()
    endif()
  endif()

  if(SOURCEMETA_TARGET_CLANG_TIDY_REQUIRED)
    find_program(CLANG_TIDY_BIN NAMES clang-tidy REQUIRED
      PATHS ${CLANG_TIDY_FIND_PATHS})
  else()
    find_program(CLANG_TIDY_BIN NAMES clang-tidy
      PATHS ${CLANG_TIDY_FIND_PATHS})
  endif()

  # This covers the empty list too
  if(NOT SOURCEMETA_TARGET_CLANG_TIDY_SOURCES)
    message(FATAL_ERROR "You must pass file globs to analyze in the SOURCES option")
  endif()
  file(GLOB_RECURSE SOURCEMETA_TARGET_CLANG_TIDY_FILES
    ${SOURCEMETA_TARGET_CLANG_TIDY_SOURCES})

  set(CLANG_TIDY_CONFIG "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/clang-tidy.config")
  if(CLANG_TIDY_BIN)
    add_custom_target(clang_tidy
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CLANG_TIDY_BIN}" -p "${PROJECT_BINARY_DIR}"
        --config-file "${CLANG_TIDY_CONFIG}"
        ${SOURCEMETA_TARGET_CLANG_TIDY_FILES}
        COMMENT "Analyzing sources using ClangTidy")
  else()
    add_custom_target(clang_tidy
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CMAKE_COMMAND}" -E echo "Could not locate ClangTidy"
      COMMAND "${CMAKE_COMMAND}" -E false)
  endif()

  set_target_properties(clang_tidy PROPERTIES FOLDER "Linting")
endfunction()
