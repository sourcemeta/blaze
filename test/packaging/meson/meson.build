project('blaze_hello', 'cpp',
        version : '0.0.1',
        default_options : [ 'cpp_std=c++23' ])

blaze_dependency = dependency('Blaze',
                              method : 'cmake',
                              modules : [ 'sourcemeta::core::json',
                                          'sourcemeta::blaze::compiler',
                                          'sourcemeta::blaze::evaluator',
                                          'sourcemeta::blaze::output' ],
                              required : true)

executable('blaze_hello', 'hello.cc', dependencies : [ blaze_dependency ])
