if(NOT SmallVector_FOUND)
  set(SMALLVECTOR_DIR "${PROJECT_SOURCE_DIR}/vendor/small-vector")
  set(SMALLVECTOR_PUBLIC_HEADER "${SMALLVECTOR_DIR}/source/include/gch/small_vector.hpp")

  add_library(smallvector INTERFACE
    "${SMALLVECTOR_PUBLIC_HEADER}" ${SMALLVECTOR_PRIVATE_HEADERS})

  target_include_directories(smallvector INTERFACE
    "$<BUILD_INTERFACE:${SMALLVECTOR_DIR}/source/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gch>")

  set_target_properties(smallvector
    PROPERTIES
      OUTPUT_NAME smallvector
      PUBLIC_HEADER "${SMALLVECTOR_PUBLIC_HEADER}"
      EXPORT_NAME smallvector)

  if(JSONTOOLKIT_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS smallvector
      EXPORT smallvector
      PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/gch"
        COMPONENT sourcemeta_jsontoolkit_dev
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT sourcemeta_jsontoolkit
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT sourcemeta_jsontoolkit
        NAMELINK_COMPONENT sourcemeta_jsontoolkit_dev
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT sourcemeta_jsontoolkit_dev)
    install(EXPORT smallvector
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/smallvector"
      COMPONENT sourcemeta_jsontoolkit_dev)

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/smallvector-config.cmake
      "include(\"\${CMAKE_CURRENT_LIST_DIR}/smallvector.cmake\")\n"
      "check_required_components(\"smallvector\")\n")
    install(FILES
      "${CMAKE_CURRENT_BINARY_DIR}/smallvector-config.cmake"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/smallvector"
      COMPONENT sourcemeta_jsontoolkit_dev)
  endif()

  set(SmallVector_FOUND ON)
endif()
