sourcemeta_test(NAMESPACE sourcemeta PROJECT blaze NAME binpack
  SOURCES
    binpack_decode_any_test.cc
    binpack_decode_array_test.cc
    binpack_decode_integer_test.cc
    binpack_decode_number_test.cc
    binpack_decode_object_test.cc
    binpack_decode_string_test.cc
    binpack_decode_test.cc
    binpack_decode_traits_test.cc
    binpack_encode_any_test.cc
    binpack_encode_array_test.cc
    binpack_encode_cache_test.cc
    binpack_encode_integer_test.cc
    binpack_encode_number_test.cc
    binpack_encode_object_test.cc
    binpack_encode_real_test.cc
    binpack_encode_string_test.cc
    binpack_encode_test.cc
    binpack_encode_traits_test.cc
    binpack_input_stream_varint_test.cc
    binpack_output_stream_varint_test.cc
    binpack_encoding_traits_test.cc
    binpack_v1_loader_test.cc
    binpack_v1_any_loader_test.cc
    binpack_v1_array_loader_test.cc
    binpack_v1_integer_loader_test.cc
    binpack_v1_number_loader_test.cc
    binpack_v1_string_loader_test.cc

    binpack_canonicalizer_test.cc
    binpack_compiler_test.cc
    binpack_2020_12_compiler_any_test.cc
    binpack_2020_12_compiler_integer_test.cc
    binpack_2020_12_compiler_number_test.cc)

target_link_libraries(sourcemeta_blaze_binpack_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_blaze_binpack_unit
  PRIVATE sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_blaze_binpack_unit
  PRIVATE sourcemeta::blaze::binpack)

set_tests_properties(blaze.binpack PROPERTIES TIMEOUT 60)

add_subdirectory(e2e)
