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
    std::cerr << "Usage: " << argv[0]
              << " <schema.json or table.json> [--html]\n";
    return EXIT_FAILURE;
  }

  const auto html{argc == 3};
  if (html && std::string{argv[2]} != "--html") {
    std::cerr << "Unknown option: " << argv[2] << "\n";
    std::cerr << "Usage: " << argv[0]
              << " <schema.json or table.json> [--html]\n";
    return EXIT_FAILURE;
  }

  try {
    // Reading the schema belongs inside here too. It throws on a file that is
    // missing or is not JSON, and that is as much a failure of this command as
    // a schema it cannot describe.
    const auto schema{sourcemeta::core::read_json(argv[1])};
    // Describing a schema assumes it is one, so anything else stops here.
    if (!schema.is_object() && !schema.is_boolean()) {
      std::cerr << "A schema must be an object or a boolean\n";
      return EXIT_FAILURE;
    }

    // A document already in the table format is drawn as it is.
    const auto described{schema.is_object() && schema.defines("$schema") &&
                         schema.at("$schema").is_string() &&
                         schema.at("$schema").to_string() ==
                             sourcemeta::blaze::DOCUMENTATION_FORMAT};
    const auto documentation{described
                                 ? schema
                                 : sourcemeta::blaze::to_documentation(
                                       schema, sourcemeta::core::schema_walker,
                                       sourcemeta::core::schema_resolver)};
    if (html) {
      std::string page;
      sourcemeta::blaze::to_html(documentation, page);
      std::cout << page << "\n";
    } else {
      sourcemeta::core::prettify(documentation, std::cout);
      std::cout << "\n";
    }
  } catch (const sourcemeta::blaze::DocumentationError &error) {
    std::cerr << sourcemeta::core::to_string(error.location()) << ": "
              << error.what() << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception &error) {
    std::cerr << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
