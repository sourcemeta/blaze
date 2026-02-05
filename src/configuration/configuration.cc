#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/core/io.h>

#include <algorithm> // std::ranges::any_of
#include <cassert>   // assert
#include <string>    // std::string

namespace sourcemeta::blaze {

auto Configuration::find(const std::filesystem::path &path)
    -> std::optional<std::filesystem::path> {
  const auto canonical{sourcemeta::core::weakly_canonical(path)};
  assert(canonical.is_absolute());
  auto current = std::filesystem::is_directory(canonical)
                     ? canonical
                     : canonical.parent_path();

  while (!current.empty()) {
    auto candidate = current / "jsonschema.json";
    if (std::filesystem::exists(candidate) &&
        std::filesystem::is_regular_file(candidate)) {
      return candidate;
    }

    auto parent = current.parent_path();
    if (parent == current) {
      break;
    } else {
      current = parent;
    }
  }

  return std::nullopt;
}

auto Configuration::applies_to(const std::filesystem::path &path) const
    -> bool {
  if (this->extension.empty()) {
    return true;
  }

  const std::string filename{path.filename().string()};
  return std::ranges::any_of(this->extension,
                             [&path, &filename](const auto &suffix) {
                               if (suffix.empty()) {
                                 return path.extension().empty();
                               }

                               return filename.ends_with(suffix);
                             });
}

} // namespace sourcemeta::blaze
