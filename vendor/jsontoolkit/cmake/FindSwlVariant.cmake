if(NOT SwlVariant_FOUND)
  set(SWL_VARIANT_DIR "${PROJECT_SOURCE_DIR}/vendor/swl-variant")
  set(SWL_VARIANT_PUBLIC_HEADER "${SWL_VARIANT_DIR}/include/swl/variant.hpp")
  set(SWL_VARIANT_PRIVATE_HEADERS
    "${SWL_VARIANT_DIR}/include/swl/variant_detail.hpp"
    "${SWL_VARIANT_DIR}/include/swl/variant_visit.hpp")

  add_library(swl_variant INTERFACE
    "${SWL_VARIANT_PUBLIC_HEADER}"
    ${SWL_VARIANT_PRIVATE_HEADERS})

  add_library(swl::variant ALIAS swl_variant)

  target_compile_definitions(swl_variant INTERFACE SWL_VARIANT_NO_STD_HASH)
  target_compile_definitions(swl_variant INTERFACE SWL_VARIANT_NO_CONSTEXPR_EMPLACE)

  target_include_directories(swl_variant INTERFACE
    "$<BUILD_INTERFACE:${SWL_VARIANT_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

  set_target_properties(swl_variant
    PROPERTIES
      OUTPUT_NAME swl_variant
      PUBLIC_HEADER "${SWL_VARIANT_PUBLIC_HEADER}"
      PRIVATE_HEADER "${SWL_VARIANT_PRIVATE_HEADERS}"
      EXPORT_NAME swl_variant)

  if(JSONTOOLKIT_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS swl_variant
      EXPORT swlvariant
      PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/swl"
        COMPONENT sourcemeta_jsontoolkit
      PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/swl"
        COMPONENT sourcemeta_jsontoolkit
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT sourcemeta_jsontoolkit
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT sourcemeta_jsontoolkit
        NAMELINK_COMPONENT sourcemeta_jsontoolkit_dev
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT sourcemeta_jsontoolkit_dev)
    install(EXPORT swlvariant
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/swlvariant"
      COMPONENT sourcemeta_jsontoolkit_dev)

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/swlvariant-config.cmake
      "include(\"\${CMAKE_CURRENT_LIST_DIR}/swlvariant.cmake\")\n"
      "check_required_components(\"swlvariant\")\n")
    install(FILES
      "${CMAKE_CURRENT_BINARY_DIR}/swlvariant-config.cmake"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/swlvariant"
      COMPONENT sourcemeta_jsontoolkit_dev)
  endif()

  set(SwlVariant_FOUND ON)
endif()
