#include <sourcemeta/blaze/documentation.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <cstdlib>   // EXIT_SUCCESS, EXIT_FAILURE
#include <exception> // std::exception
#include <iostream>  // std::cerr, std::cout
#include <string>    // std::string

auto main(int argc, char *argv[]) -> int {
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: " << argv[0] << " <schema.json> [--html]\n";
    return EXIT_FAILURE;
  }

  const auto schema{sourcemeta::core::read_json(argv[1])};
  try {
    const auto documentation{sourcemeta::blaze::to_documentation(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver)};
    if (argc == 3 && std::string{argv[2]} == "--html") {
      std::cout << sourcemeta::blaze::to_html(documentation) << "\n";
    } else {
      sourcemeta::core::prettify(documentation, std::cout);
      std::cout << "\n";
    }
  } catch (const sourcemeta::blaze::DocumentationError &error) {
    std::cerr << sourcemeta::core::to_string(error.location()) << ": "
              << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
