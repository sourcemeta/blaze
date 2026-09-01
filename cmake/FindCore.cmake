if(NOT Core_FOUND)
  if(BLAZE_INSTALL)
    set(SOURCEMETA_CORE_INSTALL ON CACHE BOOL "enable installation")
  else()
    set(SOURCEMETA_CORE_INSTALL OFF CACHE BOOL "disable installation")
  endif()

  set(SOURCEMETA_CORE_EXTENSION_BUILD OFF CACHE BOOL "disable")

  set(SOURCEMETA_CORE_ADDRESS_SANITIZER ${BLAZE_ADDRESS_SANITIZER}
    CACHE BOOL "address sanitizer")

  set(SOURCEMETA_CORE_CONTRIB_GOOGLETEST ${BLAZE_TESTS} CACHE BOOL "GoogleTest")
  set(SOURCEMETA_CORE_CONTRIB_GOOGLEBENCHMARK ${BLAZE_BENCHMARK} CACHE BOOL "GoogleBenchmark")

  # Core builds every one of its libraries by default. Blaze only needs a
  # subset of them, and consumers otherwise end up with a pile of libraries
  # they have no use for, plus the OpenSSL and cURL dependencies that some of
  # them bring in
  set(SOURCEMETA_CORE_HTML OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_HTTP OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_JOSE OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_JSONPATH OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_JSONRPC OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_MARKDOWN OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_MCP OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_OAUTH OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_OIDC OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_SEMVER OFF CACHE BOOL "unused by Blaze")
  set(SOURCEMETA_CORE_LANG_PARALLEL OFF CACHE BOOL "unused by Blaze")

  # Only the test suite makes use of the Core testing library, which in turn
  # is what pulls in these three
  set(SOURCEMETA_CORE_LANG_TEST ${BLAZE_TESTS} CACHE BOOL "Core test library")
  set(SOURCEMETA_CORE_DIFF ${BLAZE_TESTS} CACHE BOOL "Core test library only")
  set(SOURCEMETA_CORE_LANG_PROCESS ${BLAZE_TESTS}
    CACHE BOOL "Core test library only")
  set(SOURCEMETA_CORE_LANG_STACKTRACE ${BLAZE_TESTS}
    CACHE BOOL "Core test library only")
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/core")
  include(Sourcemeta)
  set(Core_FOUND ON)
endif()
