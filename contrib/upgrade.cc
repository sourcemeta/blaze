#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <cstdlib>     // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>    // std::cerr, std::cout
#include <optional>    // std::optional, std::nullopt
#include <string_view> // std::string_view

static auto target_to_mode(const std::string_view target)
    -> std::optional<sourcemeta::blaze::AlterSchemaMode> {
  if (target == "draft6") {
    return sourcemeta::blaze::AlterSchemaMode::UpgradeDraft6;
  }

  if (target == "draft7") {
    return sourcemeta::blaze::AlterSchemaMode::UpgradeDraft7;
  }

  if (target == "2019-09") {
    return sourcemeta::blaze::AlterSchemaMode::Upgrade201909;
  }

  if (target == "2020-12") {
    return sourcemeta::blaze::AlterSchemaMode::Upgrade202012;
  }

  return std::nullopt;
}

auto main(int argc, char *argv[]) -> int {
  sourcemeta::core::Options options;
  options.option("target", {"t"});
  options.parse(argc, argv);

  const auto &files{options.positional()};
  if (files.size() != 1 || !options.contains("target")) {
    std::cerr << "Usage: " << argv[0]
              << " -t|--target <draft6|draft7|2019-09|2020-12> <schema.json>\n";
    return EXIT_FAILURE;
  }

  const auto &target{options.at("target").front()};
  const auto mode{target_to_mode(target)};
  if (!mode.has_value()) {
    std::cerr << "Error: unknown target dialect '" << target
              << "'. Supported: draft6, draft7, 2019-09\n";
    return EXIT_FAILURE;
  }

  auto document{sourcemeta::core::read_json(std::string{files.front()})};

  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, mode.value());
  const auto result{
      bundle.apply(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   [](const auto &pointer, const auto &name,
                      const auto &message, const auto &, const auto &) {
                     std::cerr << sourcemeta::core::to_string(pointer) << ": "
                               << name << ": " << message << "\n";
                   })};

  sourcemeta::core::prettify(document, std::cout);
  std::cout << "\n";

  return result.first ? EXIT_SUCCESS : EXIT_FAILURE;
}
