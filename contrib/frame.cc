#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream> // std::cerr, std::cin, std::cout

auto main(int argc, char *argv[]) -> int {
  if (argc > 2) {
    std::cerr << "Usage: " << argv[0] << " [schema.json]\n"
              << "Reads the schema from standard input if no path is given\n";
    return EXIT_FAILURE;
  }

  try {
    const auto schema{argc == 2 ? sourcemeta::core::read_json(argv[1])
                                : sourcemeta::core::parse_json(std::cin)};

    sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References, schema,
        sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

    sourcemeta::core::prettify(
        frame.to_json(sourcemeta::blaze::schema_resolver), std::cout);
    std::cout << "\n";
  } catch (const std::exception &error) {
    std::cerr << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
