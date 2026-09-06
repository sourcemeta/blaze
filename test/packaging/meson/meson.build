project('blaze_hello', 'cpp',
        version : '0.0.1',
        # MSVC exposes no c++23, so fall back to its latest, which is
        # what this project's own Windows build compiles with anyway
        default_options : [ 'cpp_std=c++23,c++latest' ])

# Meson's own `cmake_prefix_path` option is global, so a project with more than
# one CMake dependency needs this per-dependency form. Passing it empty would
# override that global option rather than leave it alone, so it only goes in
# when there is a prefix to name
blaze_prefix = get_option('blaze_prefix')
blaze_cmake_args = []
if blaze_prefix.length() > 0
  blaze_cmake_args = [ '-DCMAKE_PREFIX_PATH=' + ';'.join(blaze_prefix) ]
endif

blaze_dependency = dependency('Blaze',
                              method : 'cmake',
                              modules : [ 'sourcemeta::core::json',
                                          'sourcemeta::blaze::compiler',
                                          'sourcemeta::blaze::evaluator',
                                          'sourcemeta::blaze::output' ],
                              required : true,
                              cmake_args : blaze_cmake_args)

blaze_hello = executable('blaze_hello', 'hello.cc',
                         dependencies : [ blaze_dependency ])

# Linking is not enough to know that the consumer got a working library
test('blaze_hello', blaze_hello)
