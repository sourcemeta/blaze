if(NOT UnorderedDense_FOUND)
  add_library(ankerl_unordered_dense INTERFACE
    "${PROJECT_SOURCE_DIR}/vendor/unordered_dense/include/ankerl/unordered_dense.h")
  add_library(ankerl::unordered_dense ALIAS ankerl_unordered_dense)
  target_include_directories(ankerl_unordered_dense INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/vendor/unordered_dense/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
  set_target_properties(ankerl_unordered_dense
    PROPERTIES
      OUTPUT_NAME ankerl_unordered_dense
      PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/vendor/unordered_dense/include/ankerl/unordered_dense.h")

  if(JSONTOOLKIT_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ankerl_unordered_dense
      EXPORT ankerl_unordered_dense
      PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/ankerl"
        COMPONENT sourcemeta_jsontoolkit)
    install(EXPORT ankerl_unordered_dense
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ankerl"
      COMPONENT sourcemeta_jsontoolkit_dev)
  endif()

  set(UnorderedDense_FOUND ON)
endif()
