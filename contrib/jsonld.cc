#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <cstdlib>       // EXIT_SUCCESS, EXIT_FAILURE
#include <exception>     // std::exception
#include <iostream>      // std::cerr, std::cout
#include <unordered_set> // std::unordered_set
#include <variant>       // std::get, std::holds_alternative

// A convenience script to evaluate an instance against a JSON Schema whose
// atoms carry JSON-LD annotations, and print the resulting expanded JSON-LD,
// the schema validation errors, or the JSON-LD resolution error.

static auto run(const char *schema_path, const char *instance_path) -> int;

auto main(int argc, char *argv[]) -> int {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <schema.json> <instance.json>\n";
    return EXIT_FAILURE;
  }

  try {
    return run(argv[1], argv[2]);
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }
}

static auto run(const char *schema_path, const char *instance_path) -> int {
  const auto schema{sourcemeta::core::read_json(schema_path)};
  const auto instance{sourcemeta::core::read_json(instance_path)};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "x-jsonld-id", "x-jsonld-type"};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  sourcemeta::blaze::Evaluator evaluator;
  const auto outcome{
      sourcemeta::blaze::jsonld(evaluator, schema_template, instance)};

  if (std::holds_alternative<sourcemeta::core::JSON>(outcome)) {
    sourcemeta::core::prettify(std::get<sourcemeta::core::JSON>(outcome),
                               std::cout);
    std::cout << "\n";
    return EXIT_SUCCESS;
  }

  if (std::holds_alternative<sourcemeta::blaze::JSONLDInvalid>(outcome)) {
    std::cerr << "The instance does not conform to the schema:\n";
    for (const auto &entry :
         std::get<sourcemeta::blaze::JSONLDInvalid>(outcome)) {
      std::cerr << "  - " << entry.message << "\n    at instance location \""
                << sourcemeta::core::to_string(entry.instance_location)
                << "\"\n    at evaluate path \""
                << sourcemeta::core::to_string(entry.evaluate_path) << "\"\n";
    }
    return EXIT_FAILURE;
  }

  const auto &error{
      std::get<sourcemeta::blaze::JSONLDResolutionError>(outcome)};
  std::cerr << "The instance conforms but could not be resolved into JSON-LD:\n"
            << "  - " << error.message << "\n    at instance location \""
            << sourcemeta::core::to_string(error.instance_location) << "\"\n";
  return EXIT_FAILURE;
}
