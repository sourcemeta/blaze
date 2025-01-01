#include <sourcemeta/jsontoolkit/jsonschema.h>
#include <sourcemeta/jsontoolkit/uri.h>

#include <cassert> // assert
#include <utility> // std::move

namespace {
using namespace sourcemeta::jsontoolkit;

// TODO: We need to do this dance in various places. If we turn
// `Frame` into a proper class, then this can be a utility method
auto navigate_frame(const FrameLocations &frame,
                    const FrameLocationsEntry &entry,
                    const Pointer &relative_pointer)
    -> const FrameLocationsEntry & {
  const auto new_uri{
      to_uri(entry.relative_pointer.concat(relative_pointer), entry.base)
          .recompose()};
  assert(frame.contains({ReferenceType::Static, new_uri}));
  return frame.at({ReferenceType::Static, new_uri});
}

// TODO: Extract all of this into a public utility to traverse
// adjacent subschemas
auto find_adjacent_dependencies(
    const JSON::String &current, const JSON &schema,
    const FrameLocations &frame, const FrameReferences &references,
    const SchemaWalker &walker, const SchemaResolver &resolver,
    const std::set<JSON::String> &keywords, const FrameLocationsEntry &root,
    const FrameLocationsEntry &entry, const bool is_static,
    UnevaluatedEntry &result) -> void {
  const auto &subschema{get(schema, entry.pointer)};
  if (!subschema.is_object()) {
    return;
  }

  const auto subschema_vocabularies{
      vocabularies(subschema, resolver, entry.dialect)};

  for (const auto &property : subschema.as_object()) {
    if (property.first == current && entry.pointer == root.pointer) {
      continue;
    } else if (keywords.contains(property.first)) {
      // In 2019-09, `additionalItems` takes no effect without `items`
      if (subschema_vocabularies.contains(
              "https://json-schema.org/draft/2019-09/vocab/applicator") &&
          property.first == "additionalItems" && !subschema.defines("items")) {
        continue;
      }

      auto pointer{entry.pointer.concat({property.first})};
      if (is_static) {
        result.static_dependencies.emplace(std::move(pointer));
      } else {
        result.dynamic_dependencies.emplace(std::move(pointer));
      }

      continue;
    }

    const auto strategy{
        walker(property.first, subschema_vocabularies).strategy};
    switch (strategy) {
      // References
      case SchemaWalkerStrategy::Reference:
        if (references.contains({ReferenceType::Static,
                                 entry.pointer.concat({property.first})})) {
          const auto &reference{references.at(
              {ReferenceType::Static, entry.pointer.concat({property.first})})};
          assert(
              frame.contains({ReferenceType::Static, reference.destination}));
          find_adjacent_dependencies(
              current, schema, frame, references, walker, resolver, keywords,
              root, frame.at({ReferenceType::Static, reference.destination}),
              is_static, result);
        } else if (references.contains(
                       {ReferenceType::Dynamic,
                        entry.pointer.concat({property.first})})) {
          result.unresolved = true;
        }

        break;

      // Static
      case SchemaWalkerStrategy::ApplicatorElementsInline:
        for (std::size_t index = 0; index < property.second.size(); index++) {
          find_adjacent_dependencies(
              current, schema, frame, references, walker, resolver, keywords,
              root, navigate_frame(frame, entry, {property.first, index}),
              is_static, result);
        }

        break;

      // Dynamic
      case SchemaWalkerStrategy::ApplicatorElementsInPlace:
        if (property.second.is_array()) {
          for (std::size_t index = 0; index < property.second.size(); index++) {
            find_adjacent_dependencies(
                current, schema, frame, references, walker, resolver, keywords,
                root, navigate_frame(frame, entry, {property.first, index}),
                false, result);
          }
        }

        break;
      case SchemaWalkerStrategy::ApplicatorValueInPlace:
        if (is_schema(property.second)) {
          find_adjacent_dependencies(
              current, schema, frame, references, walker, resolver, keywords,
              root, navigate_frame(frame, entry, {property.first}), false,
              result);
        }

        break;
      case SchemaWalkerStrategy::ApplicatorValueOrElementsInPlace:
        if (property.second.is_array()) {
          for (std::size_t index = 0; index < property.second.size(); index++) {
            find_adjacent_dependencies(
                current, schema, frame, references, walker, resolver, keywords,
                root, navigate_frame(frame, entry, {property.first, index}),
                false, result);
          }
        } else if (is_schema(property.second)) {
          find_adjacent_dependencies(
              current, schema, frame, references, walker, resolver, keywords,
              root, navigate_frame(frame, entry, {property.first}), false,
              result);
        }

        break;
      case SchemaWalkerStrategy::ApplicatorMembersInPlace:
        if (property.second.is_object()) {
          for (const auto &pair : property.second.as_object()) {
            find_adjacent_dependencies(
                current, schema, frame, references, walker, resolver, keywords,
                root,
                navigate_frame(frame, entry, {property.first, pair.first}),
                false, result);
          }
        }

        break;

      // Anything else does not contribute to the dependency list
      default:
        break;
    }
  }
}

} // namespace

namespace sourcemeta::jsontoolkit {

auto unevaluated(const JSON &schema, const FrameLocations &frame,
                 const FrameReferences &references, const SchemaWalker &walker,
                 const SchemaResolver &resolver) -> UnevaluatedEntries {
  UnevaluatedEntries result;

  for (const auto &entry : frame) {
    if (entry.second.type != FrameLocationType::Subschema &&
        entry.second.type != FrameLocationType::Resource) {
      continue;
    }

    const auto &subschema{get(schema, entry.second.pointer)};
    assert(is_schema(subschema));
    if (!subschema.is_object()) {
      continue;
    }

    const auto subschema_vocabularies{
        vocabularies(schema, resolver, entry.second.dialect)};
    for (const auto &pair : subschema.as_object()) {
      const auto keyword_uri{
          to_uri(entry.second.relative_pointer.concat({pair.first}),
                 entry.second.base)
              .recompose()};
      UnevaluatedEntry unevaluated;
      if ((subschema_vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           subschema_vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator")) &&
          pair.first == "unevaluatedProperties") {
        find_adjacent_dependencies(
            pair.first, schema, frame, references, walker, resolver,
            {"properties", "patternProperties", "additionalProperties",
             "unevaluatedProperties"},
            entry.second, entry.second, true, unevaluated);
        result.emplace(keyword_uri, std::move(unevaluated));
      } else if (
          (subschema_vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           subschema_vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator")) &&
          pair.first == "unevaluatedItems") {
        find_adjacent_dependencies(
            pair.first, schema, frame, references, walker, resolver,
            {"prefixItems", "items", "contains", "unevaluatedItems"},
            entry.second, entry.second, true, unevaluated);
        result.emplace(keyword_uri, std::move(unevaluated));
      } else if (subschema_vocabularies.contains(
                     "https://json-schema.org/draft/2019-09/vocab/"
                     "applicator") &&
                 pair.first == "unevaluatedProperties") {
        find_adjacent_dependencies(
            pair.first, schema, frame, references, walker, resolver,
            {"properties", "patternProperties", "additionalProperties",
             "unevaluatedProperties"},
            entry.second, entry.second, true, unevaluated);
        result.emplace(keyword_uri, std::move(unevaluated));
      } else if (subschema_vocabularies.contains(
                     "https://json-schema.org/draft/2019-09/vocab/"
                     "applicator") &&
                 pair.first == "unevaluatedItems") {
        find_adjacent_dependencies(
            pair.first, schema, frame, references, walker, resolver,
            {"items", "additionalItems", "unevaluatedItems"}, entry.second,
            entry.second, true, unevaluated);
        result.emplace(keyword_uri, std::move(unevaluated));
      }
    }
  }

  return result;
}

} // namespace sourcemeta::jsontoolkit
