#ifndef SOURCEMETA_CORE_MCP_CAPABILITIES_H_
#define SOURCEMETA_CORE_MCP_CAPABILITIES_H_

#ifndef SOURCEMETA_CORE_MCP_EXPORT
#include <sourcemeta/core/mcp_export.h>
#endif

#include <sourcemeta/core/json.h>

namespace sourcemeta::core {

/// @ingroup mcp
/// Implementation info advertised by an MCP server during the initialize
/// handshake.
struct MCPImplementation {
  /// Short machine-readable server name.
  JSON::StringView name;
  /// Semver-compatible server version.
  JSON::StringView version;
  /// Optional human-readable title.
  JSON::StringView title = {};
  /// Optional human-readable description.
  JSON::StringView description = {};
  /// Optional public website URL.
  JSON::StringView website_url = {};
};

/// @ingroup mcp
/// Boolean toggles for the MCP `capabilities` object returned during the
/// initialize handshake.
struct MCPServerCapabilities {
  /// Whether the server advertises prompts.
  bool prompts = false;
  /// Whether the server advertises resources.
  bool resources = false;
  /// Whether the server advertises tools.
  bool tools = false;
  /// Whether the server advertises logging.
  bool logging = false;
  /// Whether the server advertises completions.
  bool completions = false;
};

} // namespace sourcemeta::core

#endif
