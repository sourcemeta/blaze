#ifndef SOURCEMETA_BLAZE_FOUNDATION_HELPERS_H
#define SOURCEMETA_BLAZE_FOUNDATION_HELPERS_H

#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/uri.h>

#include <cassert>          // assert
#include <deque>            // std::deque
#include <initializer_list> // std::initializer_list
#include <optional>         // std::optional
#include <string_view>      // std::string_view
#include <unordered_set>    // std::unordered_set
#include <utility>          // std::pair, std::move
#include <vector>           // std::vector

namespace sourcemeta::blaze {

auto base_dialect_uri(const SchemaBaseDialect base_dialect) -> std::string_view;

/// @ingroup foundation
///
/// List the vocabularies that a specific schema makes use of. If you set a
/// default dialect URI, this will be used if the given schema does not
/// declare the
/// `$schema` keyword. The resulting map values are set to `true` or `false`
/// depending on whether the corresponding vocabulary is required or optional,
/// respectively. For example:
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
/// const auto vocabularies{
///   sourcemeta::blaze::vocabularies(
///     document, sourcemeta::blaze::schema_resolver)};
///
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/core"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/applicator"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/unevaluated"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/validation"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/meta-data"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/format-annotation"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/content"));
/// ```
auto vocabularies(const sourcemeta::core::JSON &schema,
                  const SchemaResolver &resolver,
                  std::string_view default_dialect = "") -> SchemaVocabularies;
/// @ingroup foundation
///
/// A shortcut to sourcemeta::blaze::vocabularies based on the base
/// dialect and dialect URI.
auto vocabularies(const SchemaResolver &resolver,
                  const SchemaBaseDialect base_dialect,
                  std::string_view dialect) -> SchemaVocabularies;
/// @ingroup foundation
/// Parse a base dialect URI to its enum representation
auto to_base_dialect(const std::string_view base_dialect)
    -> std::optional<SchemaBaseDialect>;
/// @ingroup foundation
///
/// Try to locate the meta-schema that the given schema declares from within
/// the schema itself, as self-contained schemas embed the meta-schemas they
/// depend on. The result points into the given document and is null if no
/// valid embedded meta-schema could be found. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/blaze/foundation.h>
/// #include <cassert>
///
/// const sourcemeta::core::JSON schema =
///   sourcemeta::core::parse_json(R"JSON({
///   "$schema": "https://example.com/meta",
///   "$defs": {
///     "https://example.com/meta": {
///       "$id": "https://example.com/meta",
///       "$schema": "https://json-schema.org/draft/2020-12/schema",
///       "type": "object"
///     }
///   }
/// })JSON");
///
/// const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
///   schema, "https://example.com/meta",
///   sourcemeta::blaze::schema_resolver)};
///
/// assert(metaschema);
/// assert(metaschema == &schema.at("$defs").at("https://example.com/meta"));
/// ```
auto metaschema_try_embedded(const sourcemeta::core::JSON &schema,
                             std::string_view identifier,
                             const SchemaResolver &resolver)
    -> const sourcemeta::core::JSON *;
auto vocabulary_uri(SchemaVocabularies::Known vocabulary) -> std::string_view;
auto vocabulary_uri(const SchemaVocabularies::URI &vocabulary)
    -> std::string_view;

inline auto id_keyword(const SchemaBaseDialect base_dialect)
    -> std::string_view {
  switch (base_dialect) {
    case SchemaBaseDialect::JSON_Schema_2020_12:
    case SchemaBaseDialect::JSON_Schema_2020_12_Hyper:
    case SchemaBaseDialect::JSON_Schema_2019_09:
    case SchemaBaseDialect::JSON_Schema_2019_09_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_7:
    case SchemaBaseDialect::JSON_Schema_Draft_7_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_6:
    case SchemaBaseDialect::JSON_Schema_Draft_6_Hyper:
      return "$id";
    case SchemaBaseDialect::JSON_Schema_Draft_4:
    case SchemaBaseDialect::JSON_Schema_Draft_4_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_3:
    case SchemaBaseDialect::JSON_Schema_Draft_3_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_2_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_1_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_0_Hyper:
      return "id";
  }

  assert(false);
  return "$id";
}

inline auto definitions_keyword(const SchemaBaseDialect base_dialect)
    -> std::string_view {
  switch (base_dialect) {
    case SchemaBaseDialect::JSON_Schema_2020_12:
    case SchemaBaseDialect::JSON_Schema_2020_12_Hyper:
    case SchemaBaseDialect::JSON_Schema_2019_09:
    case SchemaBaseDialect::JSON_Schema_2019_09_Hyper:
      return "$defs";
    case SchemaBaseDialect::JSON_Schema_Draft_7:
    case SchemaBaseDialect::JSON_Schema_Draft_7_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_6:
    case SchemaBaseDialect::JSON_Schema_Draft_6_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_4:
    case SchemaBaseDialect::JSON_Schema_Draft_4_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_3:
    case SchemaBaseDialect::JSON_Schema_Draft_3_Hyper:
      return "definitions";
    case SchemaBaseDialect::JSON_Schema_Draft_2_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_1_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_0_Hyper:
      return "";
  }

  assert(false);
  return "$defs";
}

// In older drafts, the presence of `$ref` would override any sibling keywords
// See
// https://json-schema.org/draft-07/draft-handrews-json-schema-01#rfc.section.8.3
inline auto
ref_overrides_adjacent_keywords(const SchemaBaseDialect base_dialect) -> bool {
  switch (base_dialect) {
    case SchemaBaseDialect::JSON_Schema_Draft_7:
    case SchemaBaseDialect::JSON_Schema_Draft_7_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_6:
    case SchemaBaseDialect::JSON_Schema_Draft_6_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_4:
    case SchemaBaseDialect::JSON_Schema_Draft_4_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_3:
    case SchemaBaseDialect::JSON_Schema_Draft_3_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_2_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_1_Hyper:
    case SchemaBaseDialect::JSON_Schema_Draft_0_Hyper:
      return true;
    default:
      return false;
  }
}

inline auto embedded_metaschema_identifier_matches(
    const sourcemeta::core::JSON &candidate, const std::string_view keyword,
    const std::string_view identifier,
    const std::optional<sourcemeta::core::JSON::String> &canonical) -> bool {
  const auto *value{
      candidate.try_at(sourcemeta::core::JSON::StringView{keyword})};
  if (!value || !value->is_string()) {
    return false;
  }

  const auto &current{value->to_string()};
  if (current == identifier) {
    return true;
  }

  if (canonical.has_value()) {
    try {
      return sourcemeta::core::URI::canonicalize(current) == canonical.value();
    } catch (const sourcemeta::core::URIParseError &) {
      return false;
    }
  }

  return false;
}

inline auto embedded_metaschema_matches(
    const sourcemeta::core::JSON &candidate, const std::string_view identifier,
    const std::optional<sourcemeta::core::JSON::String> &canonical) -> bool {
  if (!candidate.is_object()) {
    return false;
  }

  for (const auto *const keyword : {"$id", "id"}) {
    if (embedded_metaschema_identifier_matches(candidate, keyword, identifier,
                                               canonical)) {
      return true;
    }
  }

  return false;
}

inline auto
embedded_metaschema_candidate(const sourcemeta::core::JSON &document,
                              const std::string_view identifier)
    -> std::pair<const sourcemeta::core::JSON *, std::string_view> {
  if (!document.is_object()) {
    return {nullptr, ""};
  }

  std::optional<sourcemeta::core::JSON::String> canonical;
  try {
    canonical = sourcemeta::core::URI::canonicalize(identifier);
  } catch (const sourcemeta::core::URIParseError &) {
    canonical = std::nullopt;
  }

  for (const auto *const container : {"$defs", "definitions"}) {
    const auto *entries{document.try_at(container)};
    if (!entries || !entries->is_object()) {
      continue;
    }

    const auto *direct{
        entries->try_at(sourcemeta::core::JSON::StringView{identifier})};
    if (direct && embedded_metaschema_matches(*direct, identifier, canonical)) {
      return {direct, container};
    }

    for (const auto &entry : entries->as_object()) {
      if (embedded_metaschema_matches(entry.second, identifier, canonical)) {
        return {&entry.second, container};
      }
    }
  }

  return {nullptr, ""};
}

inline auto embedded_metaschema_link_valid(const sourcemeta::core::JSON &link,
                                           const std::string_view identifier,
                                           const std::string_view container,
                                           const SchemaBaseDialect base_dialect)
    -> bool {
  // In 2019-09 and 2020-12, `definitions` is still supported
  // for backwards compatibility
  switch (base_dialect) {
    case SchemaBaseDialect::JSON_Schema_2020_12:
    case SchemaBaseDialect::JSON_Schema_2020_12_Hyper:
    case SchemaBaseDialect::JSON_Schema_2019_09:
    case SchemaBaseDialect::JSON_Schema_2019_09_Hyper:
      if (container != "$defs" && container != "definitions") {
        return false;
      }

      break;
    default:
      if (container != definitions_keyword(base_dialect)) {
        return false;
      }
  }

  std::optional<sourcemeta::core::JSON::String> canonical;
  try {
    canonical = sourcemeta::core::URI::canonicalize(identifier);
  } catch (const sourcemeta::core::URIParseError &) {
    canonical = std::nullopt;
  }

  return embedded_metaschema_identifier_matches(link, id_keyword(base_dialect),
                                                identifier, canonical);
}

struct EmbeddedMetaschemaLink {
  const sourcemeta::core::JSON *schema;
  sourcemeta::core::JSON::StringView identifier;
  std::string_view container;
};

} // namespace sourcemeta::blaze

#endif
