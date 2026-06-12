#ifndef SOURCEMETA_BLAZE_FOUNDATION_HELPERS_H
#define SOURCEMETA_BLAZE_FOUNDATION_HELPERS_H

#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/uri.h>

#include <cassert>          // assert
#include <initializer_list> // std::initializer_list
#include <optional>         // std::optional
#include <string_view>      // std::string_view
#include <unordered_set>    // std::unordered_set
#include <utility>          // std::pair, std::move
#include <vector>           // std::vector

namespace sourcemeta::blaze {

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

inline auto embedded_metaschema_matches(
    const sourcemeta::core::JSON &candidate, const std::string_view identifier,
    const std::optional<sourcemeta::core::JSON::String> &canonical) -> bool {
  if (!candidate.is_object()) {
    return false;
  }

  for (const auto *const keyword : {"$id", "id"}) {
    const auto *value{candidate.try_at(keyword)};
    if (!value || !value->is_string()) {
      continue;
    }

    const auto &current{value->to_string()};
    if (current == identifier) {
      return true;
    }

    if (canonical.has_value()) {
      try {
        if (sourcemeta::core::URI::canonicalize(current) == canonical.value()) {
          return true;
        }
      } catch (const sourcemeta::core::URIParseError &) {
        continue;
      }
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
        entries->try_at(sourcemeta::core::JSON::String{identifier})};
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

// A meta-schema that is not known to the resolver may still be embedded in
// the document itself, as `bundle()` does for custom meta-schemas. Across
// every official base dialect, the only containers that can hold embedded
// resources are `$defs` (2019-09 and 2020-12, where it belongs to the
// mandatory core vocabulary) and `definitions` (Draft 7 and older, which
// have no vocabulary mechanism), so no custom dialect can redefine them away.
// A candidate only counts if its entire meta-schema chain terminates at an
// official base dialect and every embedded link of the chain sits in the
// exact container that such base dialect prescribes, which is the container
// `bundle()` would have used. For example, a chain that terminates in Draft 7
// but whose links are embedded in `$defs` (which means nothing in Draft 7)
// is rejected
inline auto find_embedded_metaschema(const sourcemeta::core::JSON &document,
                                     const std::string_view identifier,
                                     const SchemaResolver &resolver)
    -> const sourcemeta::core::JSON * {
  const auto candidate{embedded_metaschema_candidate(document, identifier)};
  if (!candidate.first) {
    return nullptr;
  }

  std::unordered_set<sourcemeta::core::JSON::String> visited;
  std::vector<std::string_view> containers{candidate.second};
  // Chain links that the resolver knows about are returned by value, so we
  // need to keep them alive while we keep walking the chain
  std::vector<sourcemeta::core::JSON> resolved;
  const auto *current{candidate.first};
  sourcemeta::core::JSON::String current_identifier{identifier};
  std::optional<SchemaBaseDialect> terminal;

  while (true) {
    if (!visited.emplace(current_identifier).second) {
      return nullptr;
    }

    if (!current->is_object()) {
      return nullptr;
    }

    const auto *metaschema_dialect{current->try_at("$schema")};
    if (!metaschema_dialect || !metaschema_dialect->is_string()) {
      return nullptr;
    }

    const auto &dialect_uri{metaschema_dialect->to_string()};
    const auto known{to_base_dialect(dialect_uri)};
    if (known.has_value()) {
      terminal = known;
      break;
    }

    auto remote{resolver(dialect_uri)};
    if (remote.has_value()) {
      resolved.push_back(std::move(remote).value());
      current = &resolved.back();
      current_identifier = dialect_uri;
      continue;
    }

    const auto next{embedded_metaschema_candidate(document, dialect_uri)};
    if (!next.first) {
      return nullptr;
    }

    containers.push_back(next.second);
    current = next.first;
    current_identifier = dialect_uri;
  }

  assert(terminal.has_value());
  const auto expected{definitions_keyword(terminal.value())};
  for (const auto container : containers) {
    if (container != expected) {
      return nullptr;
    }
  }

  return candidate.first;
}

} // namespace sourcemeta::blaze

#endif
