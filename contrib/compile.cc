#include <sourcemeta/blaze/compiler.h>

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/options.h>

#include "tweaks.h"

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

// The schemas a file names, by the URI each one answers to. This is what a
// suite directory's `resolver.json` holds, so the same file serves the C++
// suites and whatever borrows the compiler through this tool
static auto read_resolve_maps(const std::vector<std::string> &paths)
    -> sourcemeta::core::JSON {
  auto schemas{sourcemeta::core::JSON::make_object()};
  for (const auto &path : paths) {
    const auto document{
        sourcemeta::core::read_json(std::filesystem::path{path})};
    if (!document.is_object()) {
      throw sourcemeta::core::JSONParseError{1, 1};
    }

    for (const auto &entry : document.as_object()) {
      schemas.assign(entry.first, entry.second);
    }
  }

  return schemas;
}

static auto resolve_schema(const std::string_view identifier,
                           const ResolveDirectories &resolve_directories,
                           const sourcemeta::core::JSON &schemas)
    -> sourcemeta::core::SchemaResolverResult {
  const auto *named{
      schemas.try_at(sourcemeta::core::JSON::StringView{identifier})};
  if (named != nullptr) {
    return *named;
  }

  for (const auto &[prefix, directory] : resolve_directories) {
    if (!identifier.starts_with(prefix)) {
      continue;
    }

    auto suffix{identifier.substr(prefix.size())};
    if (!suffix.empty() && suffix.front() == '/') {
      suffix.remove_prefix(1);
    }

    const auto file_path{sourcemeta::core::weakly_canonical(
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
  options.option("entrypoint", {"e"});
  options.option("resolve-map", {});
  register_tweak_options(options);

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
                 "[--resolve-map <file>]... "
                 "[--path <pointer>] [--entrypoint <uri-or-pointer>] "
                 "[--format-assertion] "
                 "[--annotations <keyword>]... [--no-annotations] "
                 "<schema.json>\n";
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

  const auto tweaks{tweaks_from_options(options, std::cerr)};

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
            sourcemeta::core::weakly_canonical(entry.value().second)};
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

    const auto schemas{read_resolve_maps(
        options.contains("resolve-map")
            ? std::vector<std::string>{options.at("resolve-map").cbegin(),
                                       options.at("resolve-map").cend()}
            : std::vector<std::string>{})};

    const auto resolver{
        [&resolve_directories, &schemas](const std::string_view identifier)
            -> sourcemeta::core::SchemaResolverResult {
          return resolve_schema(identifier, resolve_directories, schemas);
        }};

    auto document{
        sourcemeta::core::read_json(std::filesystem::path{positional.front()})};
    std::cerr << "Input: " << positional.front() << "\n";

    if (options.contains("path")) {
      const auto pointer{
          sourcemeta::core::to_pointer(options.at("path").front())};
      const auto *result{sourcemeta::core::try_get(document, pointer)};
      if (result == nullptr) {
        std::cerr << "error: path not found in input: "
                  << options.at("path").front() << "\n";
        return EXIT_FAILURE;
      }

      auto extracted{*result};
      document = std::move(extracted);
    }

    const auto compile_start{std::chrono::high_resolution_clock::now()};
    std::string entrypoint;
    if (options.contains("entrypoint")) {
      entrypoint = options.at("entrypoint").front();
      std::cerr << "Entrypoint: " << entrypoint << "\n";
    }

    const auto schema_template{sourcemeta::blaze::compile(
        document, sourcemeta::core::schema_walker, resolver,
        sourcemeta::blaze::default_schema_compiler, mode, default_dialect, "",
        entrypoint, tweaks)};
    const auto compile_end{std::chrono::high_resolution_clock::now()};
    const auto compile_duration{
        std::chrono::duration_cast<std::chrono::milliseconds>(compile_end -
                                                              compile_start)};
    std::cerr << "Compiled in " << compile_duration.count() << "ms ("
              << schema_template.targets[0].size() << " instructions)\n";

    sourcemeta::core::prettify(sourcemeta::blaze::to_json(schema_template),
                               std::cout);
    std::cout << "\n";
  } catch (const sourcemeta::blaze::CompilerError &error) {
    std::cerr << "error: " << error.what() << "\n";
    std::cerr << "  at base: " << error.base().recompose() << "\n";
    std::cerr << "  at location: ";
    sourcemeta::core::stringify(error.location(), std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
