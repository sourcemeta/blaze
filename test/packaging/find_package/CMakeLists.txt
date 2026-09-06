cmake_minimum_required(VERSION 3.18)
project(blaze_hello VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Blaze REQUIRED)
add_executable(blaze_hello hello.cc)
target_link_libraries(blaze_hello PRIVATE sourcemeta::core::json)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::compiler)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::evaluator)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::test)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::output)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::configuration)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::alterschema)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::codegen)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::editor)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::foundation)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::bundle)
target_link_libraries(blaze_hello PRIVATE sourcemeta::blaze::format)

# A shared build hands the consumer DLLs that the installation keeps in its own
# binary directory, which is not somewhere Windows looks when starting a
# program, so they have to travel next to this one. A static installation has
# none, and asking to copy an empty set of them is an error rather than a no-op
get_target_property(BLAZE_EVALUATOR_TYPE sourcemeta::blaze::evaluator TYPE)
if(WIN32 AND BLAZE_EVALUATOR_TYPE STREQUAL "SHARED_LIBRARY")
  add_custom_command(TARGET blaze_hello POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
      "$<TARGET_RUNTIME_DLLS:blaze_hello>" "$<TARGET_FILE_DIR:blaze_hello>"
    COMMAND_EXPAND_LISTS)
endif()

# Linking is not enough to know that the consumer got a working library
add_custom_command(TARGET blaze_hello POST_BUILD COMMAND blaze_hello)

# Blaze must not impose its own diagnostics or code generation choices on the
# programs that consume it. Reading the property through a generator expression
# collects the options inherited from every library in the link closure, so
# this covers the entire installation rather than the targets named above
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/inherited-options.txt"
  CONTENT "$<TARGET_PROPERTY:blaze_hello,COMPILE_OPTIONS>")
