#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <chrono>      // std::chrono
#include <cstdlib>     // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // std::filesystem
#include <iostream>    // std::cerr, std::cout
#include <optional>    // std::optional, std::nullopt
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::pair
#include <vector>      // std::vector

using ResolveDirectories =
    std::vector<std::pair<std::string, std::filesystem::path>>;

static auto parse_resolve_directory(const std::string_view value)
    -> std::optional<std::pair<std::string, std::filesystem::path>> {
  const auto comma{value.find(',')};
  if (comma == std::string_view::npos || comma == 0 ||
      comma == value.size() - 1) {
    return std::nullopt;
  }

  return std::pair{std::string{value.substr(0, comma)},
                   std::filesystem::path{value.substr(comma + 1)}};
}

static auto resolve_schema(const std::string_view identifier,
                           const ResolveDirectories &resolve_directories)
    -> std::optional<sourcemeta::core::JSON> {
  for (const auto &[prefix, directory] : resolve_directories) {
    if (!identifier.starts_with(prefix)) {
      continue;
    }

    auto suffix{identifier.substr(prefix.size())};
    if (!suffix.empty() && suffix.front() == '/') {
      suffix.remove_prefix(1);
    }

    const auto file_path{std::filesystem::weakly_canonical(
        directory / std::filesystem::path{suffix})};
    const auto directory_string{directory.string()};
    const auto file_string{file_path.string()};
    if (!file_string.starts_with(directory_string)) {
      continue;
    }

    if (std::filesystem::exists(file_path)) {
      return sourcemeta::core::read_json(file_path);
    }
  }

  return sourcemeta::core::schema_resolver(identifier);
}

auto main(int argc, char **argv) noexcept -> int {
  sourcemeta::core::Options options;
  options.flag("fast", {"f"});
  options.option("default-dialect", {"d"});
  options.option("resolve-directory", {"r"});
  options.option("path", {"p"});

  try {
    options.parse(argc, argv);
  } catch (const sourcemeta::core::OptionsError &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  const auto &positional{options.positional()};
  if (positional.empty()) {
    std::cerr << "Usage: " << argv[0]
              << " [--fast] [--default-dialect <uri>] "
                 "[--resolve-directory <uri-prefix>,<dir>]... "
                 "[--path <pointer>] <schema.json>\n";
    return EXIT_FAILURE;
  }

  const auto mode{options.contains("fast")
                      ? sourcemeta::blaze::Mode::FastValidation
                      : sourcemeta::blaze::Mode::Exhaustive};
  std::cerr << "Mode: "
            << (mode == sourcemeta::blaze::Mode::FastValidation ? "fast"
                                                                : "exhaustive")
            << "\n";

  std::string default_dialect;
  if (options.contains("default-dialect")) {
    default_dialect = options.at("default-dialect").front();
    std::cerr << "Default dialect: " << default_dialect << "\n";
  }

  try {
    std::vector<std::pair<std::string, std::filesystem::path>>
        resolve_directories;
    if (options.contains("resolve-directory")) {
      for (const auto &value : options.at("resolve-directory")) {
        auto entry{parse_resolve_directory(value)};
        if (!entry.has_value()) {
          std::cerr << "error: --resolve-directory value must be "
                       "<uri-prefix>,<directory>\n";
          return EXIT_FAILURE;
        }

        const auto canonical{
            std::filesystem::weakly_canonical(entry.value().second)};
        if (!std::filesystem::is_directory(canonical)) {
          std::cerr << "error: not a directory: " << entry.value().second
                    << "\n";
          return EXIT_FAILURE;
        }

        entry.value().second = canonical;
        std::cerr << "Resolve: " << entry.value().first << " -> " << canonical
                  << "\n";
        resolve_directories.push_back(std::move(entry.value()));
      }
    }

    const auto resolver{
        [&resolve_directories](const std::string_view identifier)
            -> std::optional<sourcemeta::core::JSON> {
          return resolve_schema(identifier, resolve_directories);
        }};

    auto document{
        sourcemeta::core::read_json(std::filesystem::path{positional.front()})};
    std::cerr << "Input: " << positional.front() << "\n";

    // The compiler assumes valid schema input (object or boolean) and
    // asserts otherwise. Guard here at the CLI boundary to ensure
    // graceful failure instead of aborting on malformed inputs.
    if (!sourcemeta::core::is_schema(document)) {
      std::cerr << "error: the input is not a valid JSON Schema\n";
      return EXIT_FAILURE;
    }

    if (options.contains("path")) {
      const auto pointer{sourcemeta::core::to_pointer(
          std::string{options.at("path").front()})};
      const auto *result{sourcemeta::core::try_get(document, pointer)};
      if (result == nullptr) {
        std::cerr << "error: path not found in input: "
                  << options.at("path").front() << "\n";
        return EXIT_FAILURE;
      }

      auto extracted{*result};
      document = std::move(extracted);

      if (!sourcemeta::core::is_schema(document)) {
        std::cerr << "error: the value at the given path is not a valid "
                     "JSON Schema\n";
        return EXIT_FAILURE;
      }
    }

    const auto compile_start{std::chrono::high_resolution_clock::now()};
    const auto schema_template{sourcemeta::blaze::compile(
        document, sourcemeta::core::schema_walker, resolver,
        sourcemeta::blaze::default_schema_compiler, mode, default_dialect)};
    const auto compile_end{std::chrono::high_resolution_clock::now()};
    const auto compile_duration{
        std::chrono::duration_cast<std::chrono::milliseconds>(compile_end -
                                                              compile_start)};
    std::cerr << "Compiled in " << compile_duration.count() << "ms ("
              << schema_template.targets[0].size() << " instructions)\n";

    sourcemeta::core::prettify(sourcemeta::blaze::to_json(schema_template),
                               std::cout);
    std::cout << "\n";
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
