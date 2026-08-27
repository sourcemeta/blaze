#ifndef SOURCEMETA_BLAZE_FOUNDATION_H_
#define SOURCEMETA_BLAZE_FOUNDATION_H_

#ifndef SOURCEMETA_BLAZE_FOUNDATION_EXPORT
#include <sourcemeta/blaze/foundation_export.h>
#endif

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

// NOLINTBEGIN(misc-include-cleaner)
#include <sourcemeta/blaze/foundation_error.h>
#include <sourcemeta/blaze/foundation_frame.h>
#include <sourcemeta/blaze/foundation_types.h>
// NOLINTEND(misc-include-cleaner)

#include <optional>    // std::optional, std::nullopt
#include <string_view> // std::string_view

/// @defgroup foundation Foundation
/// @brief A set of JSON Schema utilities across dialects.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/blaze/foundation.h>
/// ```

namespace sourcemeta::blaze {

/// @ingroup foundation
/// A default resolver that relies on built-in official schemas.
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto schema_resolver(const std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON>;

/// @ingroup foundation
/// Check if a given identifier corresponds to a known built-in schema
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto schema_is_known(const std::string_view identifier) noexcept -> bool;

/// @ingroup foundation
/// Check if a given URI corresponds to an official schema released by the
/// JSON Schema organisation
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto schema_is_official(const std::string_view identifier) noexcept -> bool;

/// @ingroup foundation
/// A default schema walker with support for a wide range of drafts
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto schema_walker(const std::string_view keyword,
                   const SchemaVocabularies &vocabularies)
    -> const SchemaWalkerResult &;

/// @ingroup foundation
///
/// This function returns the URI identifier of the given schema, or an empty
/// string view if the schema has no identifier. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/blaze/foundation.h>
/// #include <cassert>
///
/// const sourcemeta::core::JSON document =
///     sourcemeta::core::parse_json(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "$id": "https://sourcemeta.com/example-schema"
/// })JSON");
///
/// const auto id{sourcemeta::blaze::identify(
///   document, sourcemeta::blaze::schema_resolver)};
/// assert(!id.empty());
/// assert(id == "https://sourcemeta.com/example-schema");
/// ```
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto identify(const sourcemeta::core::JSON &schema,
              const SchemaResolver &resolver,
              std::string_view default_dialect = "",
              std::string_view default_id = "",
              bool allow_dialect_override = true) -> std::string_view;

/// @ingroup foundation
///
/// A shortcut to sourcemeta::blaze::identify if you know the base dialect
/// of the schema.
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto identify(const sourcemeta::core::JSON &schema,
              const SchemaBaseDialect base_dialect,
              std::string_view default_id = "") -> std::string_view;

/// @ingroup foundation
///
/// This function sets the identifier of a schema, replacing the existing one,
/// if any. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/blaze/foundation.h>
/// #include <cassert>
///
/// sourcemeta::core::JSON document =
///     sourcemeta::core::parse_json(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "$id": "https://sourcemeta.com/example-schema"
/// })JSON");
///
/// sourcemeta::blaze::schema_reidentify(document,
///   "https://example.com/my-new-id",
///   sourcemeta::blaze::schema_resolver);
///
/// const auto id{sourcemeta::blaze::identify(
///   document, sourcemeta::blaze::schema_resolver)};
/// assert(!id.empty());
/// assert(id == "https://example.com/my-new-id");
/// ```
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto schema_reidentify(sourcemeta::core::JSON &schema,
                       std::string_view new_identifier,
                       const SchemaResolver &resolver,
                       std::string_view default_dialect = "") -> void;

/// @ingroup foundation
///
/// A shortcut to sourcemeta::blaze::schema_reidentify if you know the base
/// dialect of the schema.
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto schema_reidentify(sourcemeta::core::JSON &schema,
                       std::string_view new_identifier,
                       const SchemaBaseDialect base_dialect) -> void;

/// @ingroup foundation
///
/// Get the base dialect that applies to the given schema. If you set
/// a default dialect URI, this will be used if the given schema does not
/// declare the `$schema` keyword. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/blaze/foundation.h>
/// #include <cassert>
///
/// const sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "object"
/// })JSON");
///
/// const auto base_dialect{
///   sourcemeta::blaze::base_dialect(
///     document, sourcemeta::blaze::schema_resolver)};
///
/// assert(base_dialect.has_value());
/// assert(base_dialect.value() ==
///   sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
/// ```
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto base_dialect(const sourcemeta::core::JSON &schema,
                  const SchemaResolver &resolver,
                  std::string_view default_dialect = "",
                  bool allow_dialect_override = true)
    -> std::optional<SchemaBaseDialect>;

} // namespace sourcemeta::blaze

#endif
