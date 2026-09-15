#include <sourcemeta/blaze/convert.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <cstdlib>     // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>    // std::cerr, std::cout
#include <optional>    // std::optional, std::nullopt
#include <string_view> // std::string_view

static auto parse_target(const std::string_view target)
    -> std::optional<sourcemeta::blaze::ConvertTarget> {
  if (target == "draft4") {
    return sourcemeta::blaze::ConvertTarget::Draft4;
  }

  if (target == "draft6") {
    return sourcemeta::blaze::ConvertTarget::Draft6;
  }

  if (target == "draft7") {
    return sourcemeta::blaze::ConvertTarget::Draft7;
  }

  if (target == "2019-09") {
    return sourcemeta::blaze::ConvertTarget::Draft201909;
  }

  if (target == "2020-12") {
    return sourcemeta::blaze::ConvertTarget::Draft202012;
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
              << " -t|--target <draft4|draft6|draft7|2019-09|2020-12> "
                 "<schema.json>\n";
    return EXIT_FAILURE;
  }

  const auto &target{options.at("target").front()};
  const auto convert_target{parse_target(target)};
  if (!convert_target.has_value()) {
    std::cerr << "Error: unknown target dialect '" << target
              << "'. Supported: draft4, draft6, draft7, 2019-09, 2020-12\n";
    return EXIT_FAILURE;
  }

  auto document{sourcemeta::core::read_json(files.front())};

  sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,
                             sourcemeta::core::schema_resolver,
                             convert_target.value());

  sourcemeta::core::prettify(document, std::cout);
  std::cout << "\n";

  return EXIT_SUCCESS;
}
