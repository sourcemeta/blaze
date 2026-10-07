#ifndef SOURCEMETA_CORE_MCP_ERROR_H_
#define SOURCEMETA_CORE_MCP_ERROR_H_

#ifndef SOURCEMETA_CORE_MCP_EXPORT
#include <sourcemeta/core/mcp_export.h>
#endif

#include <sourcemeta/core/json.h>

#include <cstdint> // std::int64_t

namespace sourcemeta::core {

/// @ingroup mcp
/// The MCP error code returned when a requested resource cannot be found.
constexpr std::int64_t MCP_CODE_RESOURCE_NOT_FOUND{-32002};

/// @ingroup mcp
/// The MCP error code indicating that the client must complete a URL
/// elicitation flow before retrying.
constexpr std::int64_t MCP_CODE_URL_ELICITATION_REQUIRED{-32042};

/// @ingroup mcp
/// Build a JSON-RPC error envelope reporting that an MCP resource URI could
/// not be resolved. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/mcp.h>
/// #include <cassert>
///
/// const auto identifier{sourcemeta::core::JSON{3}};
/// const auto envelope{
///     sourcemeta::core::mcp_make_error_resource_not_found(identifier)};
/// assert(envelope.at("error").at("code").to_integer() == -32002);
/// ```
SOURCEMETA_CORE_MCP_EXPORT
auto mcp_make_error_resource_not_found(const sourcemeta::core::JSON &identifier)
    -> sourcemeta::core::JSON;

} // namespace sourcemeta::core

#endif
