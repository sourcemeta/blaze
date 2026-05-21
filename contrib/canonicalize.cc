#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/format.h>
#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream> // std::cerr, std::cout

auto main(int argc, char *argv[]) -> int {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <schema.json>\n";
    return EXIT_FAILURE;
  }

  auto document{sourcemeta::core::read_json(argv[1])};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle,
                         sourcemeta::blaze::AlterSchemaMode::Canonicalizer);
  const auto result{
      bundle.apply(document, sourcemeta::blaze::schema_walker,
                   sourcemeta::blaze::schema_resolver,
                   [](const auto &pointer, const auto &name,
                      const auto &message, const auto &, const auto &) {
                     std::cerr << sourcemeta::core::to_string(pointer) << ": "
                               << name << ": " << message << "\n";
                   })};

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  sourcemeta::core::prettify(document, std::cout);
  std::cout << "\n";

  return result.first ? EXIT_SUCCESS : EXIT_FAILURE;
}
