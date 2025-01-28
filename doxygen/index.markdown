Getting Started
===============

@tableofcontents

Blaze is a ultra high-performance [JSON Schema](http://json-schema.org)
evaluator for modern C++. It targets C++20 and supports the Clang, GCC, and
MSVC compilers on macOS, GNU/Linux, FreeBSD, Windows, and Unikraft (through the
ELF loader).

Installation
------------

### As a git submodule

```sh
# Add the project as a submodule, in this case to deps/blaze
$ git submodule add https://github.com/sourcemeta/blaze.git deps/blaze

# Add the project as a CMake subdirectory
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/blaze")

# Link your targets accordingly
target_link_libraries(my_executable_or_library PUBLIC sourcemeta::blaze::evaluator)
target_link_libraries(my_executable_or_library PUBLIC sourcemeta::blaze::compiler)
```

### Using FetchContent

```cmake
cmake_minimum_required(VERSION 3.14)
project(my_project)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  blaze
  URL https://github.com/sourcemeta/blaze/archive/<commit-sha>.zip
  DOWNLOAD_EXTRACT_TIMESTAMP NO)
FetchContent_MakeAvailable(blaze)

add_executable(my_example ...)
target_link_libraries(my_example PUBLIC sourcemeta::blaze::evaluator)
target_link_libraries(my_example PUBLIC sourcemeta::blaze::compiler)
```

### Using find_package

Assuming you have installed Blaze in a place where CMake can find the
package config file:

```sh
find_package(Blaze REQUIRED)

# This package also supports component-based inclusion
find_package(Blaze REQUIRED COMPONENTS evaluator compiler)

# Link your targets accordingly
target_link_libraries(my_executable_or_library PUBLIC sourcemeta::blaze::evaluator)
target_link_libraries(my_executable_or_library PUBLIC sourcemeta::blaze::compiler)
```

CMake
-----

### Options

| Option                      | Type    | Default | Description                             |
|-----------------------------|---------|---------|-----------------------------------------|
| `BLAZE_COMPILER`            | Boolean | `ON`    | Build the Blaze compiler library        |
| `BLAZE_EVALUATOR`           | Boolean | `ON`    | Build the Blaze evaluator library       |
| `BLAZE_TESTS`               | Boolean | `OFF`   | Build the Blaze tests                   |
| `BLAZE_BENCHMARK`           | Boolean | `OFF`   | Build the Blaze benchmarks              |
| `BLAZE_CONTRIB`             | Boolean | `OFF`   | Build the Blaze contrib programs        |
| `BLAZE_DOCS`                | Boolean | `OFF`   | Build the Blaze docs                    |
| `BLAZE_INSTALL`             | Boolean | `ON`    | Install the Blaze library               |
| `BLAZE_ADDRESS_SANITIZER`   | Boolean | `OFF`   | Enable the address sanitizer            |
| `BLAZE_UNDEFINED_SANITIZER` | Boolean | `OFF`   | Enable the undefined behavior sanitizer |

### Components

If you install Blaze from source, keep in mind that the project is split
into a set of CMake components:

| Component              | Description                             |
|------------------------|-----------------------------------------|
| `sourcemeta_blaze`     | The core Blaze libraries                |
| `sourcemeta_blaze_dev` | The Blaze headers and development files |

Contributing
------------

Blaze makes use of the [CMake](https://cmake.org) build system. You can
configure, build and test the project as follows:

```sh
cmake -S . -B ./build \
  -DCMAKE_BUILD_TYPE:STRING=<Debug|Release> \
  -DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
  -DBLAZE_DOCS:BOOL=ON \
  -DBLAZE_TESTS:BOOL=ON
# Format the code
cmake --build ./build --config <Debug|Release> --target clang_format
# Build the project
cmake --build ./build --config <Debug|Release>
# Run the test suite
ctest --test-dir ./build --build-config <Debug|Release> --output-on-failure --progress
```

Or simply run:

```sh
# On UNIX-based systems
make
# On Windows
nmake
```
