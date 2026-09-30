#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_H_
#define SOURCEMETA_BLAZE_DOCUMENTATION_H_

/// @defgroup documentation Documentation
/// @brief Describe a JSON Schema as documentation, for readers
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/blaze/documentation.h>
/// ```
///
/// A schema is converted once into the table format, a description of data that
/// does not depend on any schema language, and a renderer reads that format
/// instead of the schema. The format states what a reader needs: which fields
/// there are, what may go in each, and which are required. Every rule it states
/// holds for the data the schema accepts, and a schema it cannot describe
/// exactly is refused.

#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_EXPORT
#include <sourcemeta/blaze/documentation_export.h>
#endif

// NOLINTBEGIN(misc-include-cleaner)
#include <sourcemeta/blaze/documentation_error.h>
// NOLINTEND(misc-include-cleaner)

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <string> // std::string

namespace sourcemeta::blaze {

/// @ingroup documentation
///
/// The address of the table format this module writes. A document states it as
/// its `$schema`, and it names the version of the format too.
SOURCEMETA_BLAZE_DOCUMENTATION_EXPORT
extern const char *const DOCUMENTATION_FORMAT;

/// @ingroup documentation
///
/// Describe a JSON Schema in the table format. For example:
///
/// ```cpp
/// #include <sourcemeta/blaze/documentation.h>
///
/// #include <sourcemeta/core/jsonschema.h>
/// #include <sourcemeta/core/json.h>
///
/// #include <cassert>
///
/// const sourcemeta::core::JSON schema =
///     sourcemeta::core::parse_json(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "string"
/// })JSON");
///
/// const auto documentation{sourcemeta::blaze::to_documentation(
///     schema, sourcemeta::core::schema_walker,
///     sourcemeta::core::schema_resolver)};
///
/// assert(documentation.at("root").at("kind").to_string() == "string");
/// ```
///
/// Throws sourcemeta::blaze::DocumentationError when the schema cannot be
/// described exactly, saying what and where.
[[nodiscard]] SOURCEMETA_BLAZE_DOCUMENTATION_EXPORT auto
to_documentation(const sourcemeta::core::JSON &schema,
                 const sourcemeta::core::SchemaWalker &walker,
                 const sourcemeta::core::SchemaResolver &resolver)
    -> sourcemeta::core::JSON;

/// @ingroup documentation
///
/// Render a table format document as HTML. The renderer reads the format alone,
/// so it draws a page for a schema of any language that was converted into it.
/// For example:
///
/// ```cpp
/// #include <sourcemeta/blaze/documentation.h>
///
/// #include <sourcemeta/core/json.h>
///
/// #include <cassert>
///
/// const sourcemeta::core::JSON documentation =
///     sourcemeta::core::parse_json(R"JSON({
///   "$schema":
///   "tag:sourcemeta.com,2026:table-format/2",
///   "title": "Order",
///   "language": "https://json-schema.org/draft/2020-12/schema",
///   "root": { "kind": "string" }
/// })JSON");
///
/// const auto page{sourcemeta::blaze::to_html(documentation)};
/// assert(!page.empty());
/// ```
[[nodiscard]] SOURCEMETA_BLAZE_DOCUMENTATION_EXPORT auto
to_html(const sourcemeta::core::JSON &documentation) -> std::string;

} // namespace sourcemeta::blaze

#endif
