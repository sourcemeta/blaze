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
                              required : true)

executable('blaze_hello', 'hello.cc', dependencies : [ blaze_dependency ])
