#include <sourcemeta/core/uri.h>

#include "escaping.h"

#include <algorithm>  // std::ranges::replace
#include <filesystem> // std::filesystem
#include <iterator>   // std::advance, std::next
#include <sstream>    // std::istringstream, std::ostringstream
#include <string>     // std::string

namespace sourcemeta::core {

auto URI::to_path() const -> std::filesystem::path {
  auto path = this->path().value_or("");

  // For non-file URIs, just return the path as-is
  if (!this->is_file()) {
    return path;
  }

  // Check for Windows absolute path (e.g., /C:/)
  const auto is_windows_absolute =
      path.size() >= 3 && path[0] == '/' && path[2] == ':';
  if (is_windows_absolute) {
    // Remove leading slash
    path.erase(0, 1);
    // Convert to Windows separators
    std::ranges::replace(path, '/', '\\');
  }

  // Unescape percent-encoded characters
  std::istringstream input{path};
  std::ostringstream output;
  uri_unescape(input, output);
  return output.str();
}

auto URI::from_path(const std::filesystem::path &path) -> URI {
  auto normalized = path.lexically_normal().string();
  const auto is_unc = normalized.starts_with("\\\\");
  const auto is_windows_absolute =
      normalized.size() >= 2 && normalized[1] == ':';

  // Convert backslashes to forward slashes
  std::ranges::replace(normalized, '\\', '/');
  const auto is_unix_absolute = normalized.starts_with("/");

  // Only absolute paths can be converted to file:// URIs
  if (!is_unix_absolute && !is_windows_absolute && !is_unc) {
    throw URIError(
        "It is not valid to construct a file:// URI out of a relative path");
  }

  // Remove leading slashes for processing
  normalized.erase(0, normalized.find_first_not_of('/'));
  const std::filesystem::path final_path{normalized};

  URI result{"file://"};
  auto iterator = final_path.begin();

  // For UNC paths, the first segment is the hostname
  if (is_unc) {
    std::istringstream input{iterator->string()};
    std::ostringstream output;
    uri_escape(input, output, URIEscapeMode::Filesystem);
    result.host_ = output.str();
    std::advance(iterator, 1);
  }

  // Process remaining path segments
  for (; iterator != final_path.end(); ++iterator) {
    if (iterator->empty()) {
      result.append_path("/");
    } else if (*iterator == "/") {
      if (std::next(iterator) == final_path.end()) {
        result.append_path("/");
      }
    } else {
      // Escape the segment
      std::istringstream input{iterator->string()};
      std::ostringstream output;
      uri_escape(input, output, URIEscapeMode::Filesystem);
      const auto escaped_segment = output.str();

      if (result.path_.has_value()) {
        result.append_path(escaped_segment);
      } else {
        // First segment: file:// URIs need leading slash
        result.path_ = "/" + escaped_segment;
      }
    }
  }

  return result;
}

} // namespace sourcemeta::core
