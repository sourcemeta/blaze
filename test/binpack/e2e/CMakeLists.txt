add_executable(blaze_binpack_e2e_runner runner.cc)
sourcemeta_add_default_options(PRIVATE blaze_binpack_e2e_runner)
target_link_libraries(blaze_binpack_e2e_runner PRIVATE sourcemeta::core::options)
target_link_libraries(blaze_binpack_e2e_runner PRIVATE sourcemeta::blaze::binpack)
set_target_properties(blaze_binpack_e2e_runner
  PROPERTIES FOLDER "Blaze/BinPack/E2E")

macro(add_blaze_binpack_e2e_test_schemaless name)
  add_test(NAME blaze.binpack.e2e.${name}.schema-less
    COMMAND "$<TARGET_FILE:blaze_binpack_e2e_runner>"
    "${CMAKE_CURRENT_SOURCE_DIR}/${name}/document.json"
    "${CMAKE_CURRENT_SOURCE_DIR}/${name}/schema-less")
endmacro()

macro(add_blaze_binpack_e2e_test name)
  add_blaze_binpack_e2e_test_schemaless(${name})
  # TODO: Test schema-driven too
endmacro()

add_blaze_binpack_e2e_test(circleciblank)
add_blaze_binpack_e2e_test(circlecimatrix)
add_blaze_binpack_e2e_test(commitlint)
add_blaze_binpack_e2e_test(commitlintbasic)
add_blaze_binpack_e2e_test(epr)
add_blaze_binpack_e2e_test(eslintrc)
add_blaze_binpack_e2e_test(esmrc)
add_blaze_binpack_e2e_test(geojson)
add_blaze_binpack_e2e_test(githubfundingblank)
add_blaze_binpack_e2e_test(githubworkflow)
add_blaze_binpack_e2e_test(gruntcontribclean)
add_blaze_binpack_e2e_test(imageoptimizerwebjob)
add_blaze_binpack_e2e_test(jsonereversesort)
add_blaze_binpack_e2e_test(jsonesort)
add_blaze_binpack_e2e_test(jsonfeed)
# TODO: This case regresses and we are beaten by Smile. Should be 2612
add_blaze_binpack_e2e_test(jsonresume)
add_blaze_binpack_e2e_test(mixed-bounded-object)
add_blaze_binpack_e2e_test(netcoreproject)
add_blaze_binpack_e2e_test(nightwatch)
add_blaze_binpack_e2e_test(openweathermap)
add_blaze_binpack_e2e_test(openweatherroadrisk)
add_blaze_binpack_e2e_test(ox-test)
add_blaze_binpack_e2e_test(packagejson)
add_blaze_binpack_e2e_test(packagejsonlintrc)
add_blaze_binpack_e2e_test(sapcloudsdkpipeline)
add_blaze_binpack_e2e_test(travisnotifications)
add_blaze_binpack_e2e_test(tslintbasic)
add_blaze_binpack_e2e_test(tslintextend)
add_blaze_binpack_e2e_test(tslintmulti)
