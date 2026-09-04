project('blaze_hello', 'cpp',
        version : '0.0.1',
        # MSVC exposes no c++23, so fall back to its latest, which is
        # what this project's own Windows build compiles with anyway
        default_options : [ 'cpp_std=c++23,c++latest' ])

blaze_dependency = dependency('Blaze',
                              method : 'cmake',
                              modules : [ 'sourcemeta::core::json',
                                          'sourcemeta::blaze::compiler',
                                          'sourcemeta::blaze::evaluator',
                                          'sourcemeta::blaze::output' ],
                              required : true,
                              # Meson's own `cmake_prefix_path` option is
                              # global, so a project with more than one CMake
                              # dependency needs this per-dependency form
                              cmake_args : [
                                '-DCMAKE_PREFIX_PATH=' +
                                  ';'.join(get_option('blaze_prefix')) ])

blaze_hello = executable('blaze_hello', 'hello.cc',
                         dependencies : [ blaze_dependency ])

# Linking is not enough to know that the consumer got a working library
test('blaze_hello', blaze_hello)
