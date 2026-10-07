#ifndef SOURCEMETA_CORE_MCP_PROTOCOL_H_
#define SOURCEMETA_CORE_MCP_PROTOCOL_H_

#ifndef SOURCEMETA_CORE_MCP_EXPORT
#include <sourcemeta/core/mcp_export.h>
#endif

#include <sourcemeta/core/json.h>

#include <cstdint>  // std::uint8_t
#include <optional> // std::optional, std::nullopt
#include <utility>  // std::unreachable

namespace sourcemeta::core {

/// @ingroup mcp
/// The supported MCP protocol revisions.
enum class MCPProtocolVersion : std::uint8_t {
  /// The MCP 2025-03-26 protocol revision.
  V_2025_03_26,
  /// The MCP 2025-06-18 protocol revision.
  V_2025_06_18,
  /// The MCP 2025-11-25 protocol revision.
  V_2025_11_25,
};

/// @ingroup mcp
/// Get the canonical wire-format string for an MCP protocol version. For
/// example:
///
/// ```cpp
/// #include <sourcemeta/core/mcp.h>
/// #include <cassert>
///
/// assert(sourcemeta::core::mcp_protocol_version_string(
///            sourcemeta::core::MCPProtocolVersion::V_2025_11_25) ==
///        "2025-11-25");
/// ```
constexpr auto
mcp_protocol_version_string(const MCPProtocolVersion version) noexcept
    -> JSON::StringView {
  switch (version) {
    case MCPProtocolVersion::V_2025_03_26:
      return "2025-03-26";
    case MCPProtocolVersion::V_2025_06_18:
      return "2025-06-18";
    case MCPProtocolVersion::V_2025_11_25:
      return "2025-11-25";
  }
  std::unreachable();
}

/// @ingroup mcp
/// The MCP method name for the `initialize` request.
constexpr JSON::StringView MCP_METHOD_INITIALIZE{"initialize"};

/// @ingroup mcp
/// The MCP method name for the `ping` request.
constexpr JSON::StringView MCP_METHOD_PING{"ping"};

/// @ingroup mcp
/// The MCP method name for the `tools/list` request.
constexpr JSON::StringView MCP_METHOD_TOOLS_LIST{"tools/list"};

/// @ingroup mcp
/// The MCP method name for the `tools/call` request.
constexpr JSON::StringView MCP_METHOD_TOOLS_CALL{"tools/call"};

/// @ingroup mcp
/// The MCP method name for the `resources/list` request.
constexpr JSON::StringView MCP_METHOD_RESOURCES_LIST{"resources/list"};

/// @ingroup mcp
/// The MCP method name for the `resources/read` request.
constexpr JSON::StringView MCP_METHOD_RESOURCES_READ{"resources/read"};

/// @ingroup mcp
/// The MCP method name for the `resources/templates/list` request.
constexpr JSON::StringView MCP_METHOD_RESOURCES_TEMPLATES_LIST{
    "resources/templates/list"};

/// @ingroup mcp
/// The MCP method name for the `notifications/initialized` notification.
constexpr JSON::StringView MCP_METHOD_NOTIFICATIONS_INITIALIZED{
    "notifications/initialized"};

/// @ingroup mcp
/// Check whether the given method name corresponds to an MCP request method
/// (notifications excluded). For example:
///
/// ```cpp
/// #include <sourcemeta/core/mcp.h>
/// #include <cassert>
///
/// assert(sourcemeta::core::mcp_is_request_method("initialize"));
/// assert(!sourcemeta::core::mcp_is_request_method("notifications/initialized"));
/// ```
constexpr auto mcp_is_request_method(const JSON::StringView method) noexcept
    -> bool {
  return method == MCP_METHOD_INITIALIZE || method == MCP_METHOD_PING ||
         method == MCP_METHOD_TOOLS_LIST || method == MCP_METHOD_TOOLS_CALL ||
         method == MCP_METHOD_RESOURCES_LIST ||
         method == MCP_METHOD_RESOURCES_READ ||
         method == MCP_METHOD_RESOURCES_TEMPLATES_LIST;
}

/// @ingroup mcp
/// Resolve an `MCP-Protocol-Version` header value into a known protocol
/// version, or `std::nullopt` when the value is unrecognised. An absent header
/// resolves to the oldest supported version per the Streamable HTTP transport.
/// For example:
///
/// ```cpp
/// #include <sourcemeta/core/mcp.h>
/// #include <cassert>
///
/// const auto resolved{
///     sourcemeta::core::mcp_resolve_protocol_version("2025-11-25")};
/// assert(resolved.has_value());
/// assert(resolved.value() ==
///        sourcemeta::core::MCPProtocolVersion::V_2025_11_25);
/// ```
constexpr auto
mcp_resolve_protocol_version(const JSON::StringView header) noexcept
    -> std::optional<MCPProtocolVersion> {
  if (header.empty()) {
    // Per the MCP Streamable HTTP transport spec: if the server does not
    // receive an MCP-Protocol-Version header, and has no other way to identify
    // the version, the server SHOULD assume protocol version 2025-03-26.
    // https://modelcontextprotocol.io/specification/2025-06-18/basic/transports#protocol-version-header
    return MCPProtocolVersion::V_2025_03_26;
  }
  if (header == "2025-11-25") {
    return MCPProtocolVersion::V_2025_11_25;
  }
  if (header == "2025-06-18") {
    return MCPProtocolVersion::V_2025_06_18;
  }
  if (header == "2025-03-26") {
    return MCPProtocolVersion::V_2025_03_26;
  }
  return std::nullopt;
}

/// @ingroup mcp
/// Whether the given protocol version supports per-tool `outputSchema`.
constexpr auto
mcp_supports_output_schema(const MCPProtocolVersion version) noexcept -> bool {
  return version != MCPProtocolVersion::V_2025_03_26;
}

/// @ingroup mcp
/// Whether the given protocol version supports `structuredContent` in tool
/// results.
constexpr auto
mcp_supports_structured_content(const MCPProtocolVersion version) noexcept
    -> bool {
  return version != MCPProtocolVersion::V_2025_03_26;
}

/// @ingroup mcp
/// Whether the given protocol version supports `resource_link` content blocks.
constexpr auto
mcp_supports_resource_link_content(const MCPProtocolVersion version) noexcept
    -> bool {
  return version != MCPProtocolVersion::V_2025_03_26;
}

/// @ingroup mcp
/// Whether the given protocol version supports the `title` field on the
/// implementation info object.
constexpr auto
mcp_supports_implementation_title(const MCPProtocolVersion version) noexcept
    -> bool {
  return version != MCPProtocolVersion::V_2025_03_26;
}

/// @ingroup mcp
/// Whether the given protocol version supports the `description` field on the
/// implementation info object.
constexpr auto mcp_supports_implementation_description(
    const MCPProtocolVersion version) noexcept -> bool {
  return version == MCPProtocolVersion::V_2025_11_25;
}

/// @ingroup mcp
/// Whether the given protocol version supports the `websiteUrl` field on the
/// implementation info object.
constexpr auto mcp_supports_implementation_website_url(
    const MCPProtocolVersion version) noexcept -> bool {
  return version == MCPProtocolVersion::V_2025_11_25;
}

/// @ingroup mcp
/// Whether the given protocol version supports JSON-RPC 2.0 batching.
constexpr auto
mcp_supports_jsonrpc_batching(const MCPProtocolVersion version) noexcept
    -> bool {
  return version == MCPProtocolVersion::V_2025_03_26;
}

} // namespace sourcemeta::core

#endif
