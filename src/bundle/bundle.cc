#include <sourcemeta/blaze/bundle.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>

#include "helpers.h"

#include <cassert>       // assert
#include <functional>    // std::reference_wrapper
#include <string>        // std::string
#include <tuple>         // std::tuple
#include <unordered_map> // std::unordered_map
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move
#include <vector>        // std::vector

namespace {

auto dependencies_internal(
    const sourcemeta::core::JSON &schema,
    const sourcemeta::blaze::SchemaWalker &walker,
    const sourcemeta::blaze::SchemaResolver &resolver,
    const sourcemeta::blaze::DependencyCallback &callback,
    std::string_view default_dialect, std::string_view default_id,
    const sourcemeta::blaze::SchemaFrame::Paths &paths,
    std::unordered_set<std::string> &visited, const bool include_official_refs)
    -> void {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, walker, resolver, default_dialect, default_id, paths);
  const auto origin{sourcemeta::blaze::identify(schema, resolver,
                                                default_dialect, default_id)};

  std::vector<
      std::tuple<sourcemeta::core::JSON, sourcemeta::core::JSON::String>>
      found;

  frame.for_each_unresolved_reference([&](const auto &pointer,
                                          const auto &reference) {
    // We don't want to report official schemas, as we can expect
    // virtually all implementations to understand them out of the box.
    // The exception is when the top-level input itself has an official
    // identifier: reporting dependencies of such a document is an
    // explicit ask for the full graph of officials it depends on
    if (!include_official_refs &&
        sourcemeta::blaze::is_official_schema(reference.destination)) {
      return;
    }

    if (reference.base.empty()) {
      throw sourcemeta::blaze::SchemaReferenceError(
          reference.destination, sourcemeta::core::to_pointer(pointer),
          "Could not resolve schema reference");
    }

    // To not infinitely loop on circular references
    if (visited.contains(std::string{reference.base})) {
      return;
    }

    // If we can't find the destination but there is a base and we can
    // find the base, then we are facing an unresolved fragment
    if (frame.traverse(reference.base).has_value()) {
      throw sourcemeta::blaze::SchemaReferenceError(
          reference.destination, sourcemeta::core::to_pointer(pointer),
          "Could not resolve schema reference");
    }

    assert(!reference.base.empty());
    const auto &identifier{reference.base};
    auto remote{resolver(identifier)};
    if (!remote.has_value()) {
      throw sourcemeta::blaze::SchemaResolutionError(
          identifier, "Could not resolve the reference to an external schema");
    }

    if (!sourcemeta::blaze::is_schema(remote.value())) {
      throw sourcemeta::blaze::SchemaReferenceError(
          identifier, sourcemeta::core::to_pointer(pointer),
          "The JSON document is not a valid JSON Schema");
    }

    const auto remote_base_dialect{sourcemeta::blaze::base_dialect(
        remote.value(), resolver, default_dialect)};
    if (!remote_base_dialect.has_value()) {
      throw sourcemeta::blaze::SchemaReferenceError(
          identifier, sourcemeta::core::to_pointer(pointer),
          "The JSON document is not a valid JSON Schema");
    }

    callback(origin, pointer, identifier, remote.value());
    found.emplace_back(std::move(remote).value(),
                       sourcemeta::core::JSON::String{identifier});
    visited.emplace(identifier);
  });

  for (const auto &entry : found) {
    dependencies_internal(std::get<0>(entry), walker, resolver, callback,
                          default_dialect, std::get<1>(entry),
                          {sourcemeta::core::empty_weak_pointer}, visited,
                          include_official_refs);
  }
}

auto embed_schema(sourcemeta::core::JSON &root,
                  const sourcemeta::core::Pointer &container,
                  const std::string_view identifier,
                  const std::string_view reserved_identifier,
                  sourcemeta::core::JSON &&target) -> void {
  if (!reserved_identifier.empty() && identifier == reserved_identifier) {
    throw sourcemeta::blaze::SchemaReservedIdentifierError(
        identifier,
        "This identifier is reserved by the bundler for internal use");
  }

  auto *current{&root};
  for (const auto &token : container) {
    if (token.is_property()) {
      current->assign_if_missing(token.to_property(),
                                 sourcemeta::core::JSON::make_object());
      current = &current->at(token.to_property());
    } else {
      assert(current->is_array() && current->size() >= token.to_index());
      current = &current->at(token.to_index());
    }
  }

  if (!current->is_object()) {
    throw sourcemeta::blaze::SchemaError(
        "Could not bundle to a container path that is not an object");
  }

  std::string key{identifier};
  // Ensure we get a definitions entry that does not exist
  while (current->defines(key)) {
    key += "/x";
  }

  current->assign(key, std::move(target));
}

auto elevate_embedded_resources(
    sourcemeta::core::JSON &remote, sourcemeta::core::JSON &root,
    const sourcemeta::core::Pointer &container,
    const sourcemeta::blaze::SchemaBaseDialect remote_dialect,
    const sourcemeta::blaze::SchemaResolver &resolver,
    std::string_view default_dialect, std::string_view reserved_identifier,
    std::unordered_map<sourcemeta::core::JSON::String,
                       sourcemeta::core::JSON::String> &bundled) -> void {
  const auto keyword{sourcemeta::blaze::definitions_keyword(remote_dialect)};
  const sourcemeta::core::JSON::String keyword_string{keyword};
  if (keyword.empty() || !remote.is_object() ||
      !remote.defines(keyword_string) ||
      !remote.at(keyword_string).is_object()) {
    return;
  }

  auto &defs{remote.at(keyword_string)};

  // Navigate to the root container once, as it doesn't change per entry
  const sourcemeta::core::JSON *root_container{&root};
  bool container_exists{true};
  for (const auto &token : container) {
    if (!token.is_property() || !root_container->is_object() ||
        !root_container->defines(token.to_property())) {
      container_exists = false;
      break;
    }

    root_container = &root_container->at(token.to_property());
  }

  std::vector<sourcemeta::core::JSON::String> to_extract;
  std::vector<sourcemeta::core::JSON::String> to_remove;
  for (const auto &entry : defs.as_object()) {
    const auto &key{entry.first};
    const auto &value{entry.second};
    const auto entry_dialect{
        sourcemeta::blaze::base_dialect(value, resolver, default_dialect)};
    const auto effective_entry_dialect{entry_dialect.value_or(remote_dialect)};
    const auto identifier{
        sourcemeta::blaze::identify(value, effective_entry_dialect)};
    if (identifier.empty() || identifier != key ||
        !sourcemeta::core::URI{identifier}.is_absolute()) {
      continue;
    }

    const sourcemeta::core::JSON::String identifier_string{identifier};
    if (bundled.contains(identifier_string)) {
      if (container_exists && root_container->is_object()) {
        for (const auto &root_entry : root_container->as_object()) {
          if (!root_entry.first.starts_with(identifier_string)) {
            continue;
          }

          const auto stored_dialect{sourcemeta::blaze::base_dialect(
              root_entry.second, resolver, default_dialect)};
          const auto effective_stored_dialect{stored_dialect.has_value()
                                                  ? stored_dialect.value()
                                                  : remote_dialect};
          const auto stored_id{sourcemeta::blaze::identify(
              root_entry.second, effective_stored_dialect)};
          if (stored_id != identifier_string) {
            continue;
          }

          if (root_entry.second != value) {
            throw sourcemeta::blaze::SchemaError(
                "Conflicting embedded resources with the same identifier");
          }

          break;
        }
      }

      to_remove.emplace_back(key);
    } else {
      to_extract.emplace_back(key);
      bundled.emplace(identifier_string, identifier_string);
    }
  }

  for (const auto &key : to_extract) {
    auto value{std::move(defs.at(key))};
    defs.erase(key);
    embed_schema(root, container, key, reserved_identifier, std::move(value));
  }

  for (const auto &key : to_remove) {
    defs.erase(key);
  }

  if (defs.empty()) {
    remote.erase(sourcemeta::core::JSON::String{keyword});
  }
}

auto bundle_schema(sourcemeta::core::JSON &root,
                   const sourcemeta::core::Pointer &container,
                   sourcemeta::core::JSON &subschema,
                   const sourcemeta::blaze::SchemaWalker &walker,
                   const sourcemeta::blaze::SchemaResolver &resolver,
                   std::string_view default_dialect,
                   std::string_view default_id,
                   const sourcemeta::blaze::SchemaFrame::Paths &paths,
                   std::unordered_map<sourcemeta::core::JSON::String,
                                      sourcemeta::core::JSON::String> &bundled,
                   const bool include_official_refs,
                   std::string_view reserved_identifier,
                   const std::size_t depth = 0) -> void {
  // Create a fresh frame for each schema we analyze to avoid key collisions
  // between different schemas that have references at the same pointer paths
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  if (depth == 0) {
    frame.analyse(
        subschema, walker, resolver, default_dialect, default_id,
        // We only want to frame in "wrapper" mode for the top level object
        paths);
  } else {
    frame.analyse(subschema, walker, resolver, default_dialect, default_id);
  }

  std::vector<std::tuple<sourcemeta::core::JSON, sourcemeta::core::JSON::String,
                         sourcemeta::blaze::SchemaBaseDialect>>
      deferred;
  std::vector<
      std::pair<sourcemeta::core::Pointer, sourcemeta::core::JSON::String>>
      ref_rewrites;

  frame.for_each_unresolved_reference([&](const auto &pointer,
                                          const auto &reference) {
    // We don't want to bundle official schemas, as we can expect
    // virtually all implementations to understand them out of the box.
    // The exception is when the top-level input itself has an official
    // identifier: bundling such a document is an explicit ask for the
    // full graph of official references it depends on
    if (!include_official_refs &&
        sourcemeta::blaze::is_official_schema(reference.destination)) {
      return;
    }

    if (reference.base.empty()) {
      throw sourcemeta::blaze::SchemaReferenceError(
          reference.destination, sourcemeta::core::to_pointer(pointer),
          "Could not resolve schema reference");
    }

    assert(!reference.base.empty());
    const sourcemeta::core::JSON::String identifier{reference.base};

    if (bundled.contains(identifier)) {
      const auto &mapped_id{bundled.at(identifier)};
      if (mapped_id != identifier) {
        sourcemeta::core::URI rewrite_uri{mapped_id};
        if (reference.fragment.has_value()) {
          rewrite_uri.fragment(reference.fragment.value());
        }

        ref_rewrites.emplace_back(sourcemeta::core::to_pointer(pointer),
                                  rewrite_uri.recompose());
        return;
      }

      // Identity mapping: the base resource is in the bundle but the
      // destination fragment could not be traversed, which is a broken
      // reference
      if (frame.traverse(reference.base).has_value()) {
        throw sourcemeta::blaze::SchemaReferenceError(
            reference.destination, sourcemeta::core::to_pointer(pointer),
            "Could not resolve schema reference");
      }

      return;
    }

    // If we can't find the destination but there is a base and we can
    // find base, then we are facing an unresolved fragment
    if (frame.traverse(reference.base).has_value()) {
      throw sourcemeta::blaze::SchemaReferenceError(
          reference.destination, sourcemeta::core::to_pointer(pointer),
          "Could not resolve schema reference");
    }

    auto remote{resolver(identifier)};
    if (!remote.has_value()) {
      if (frame.traverse(identifier).has_value()) {
        throw sourcemeta::blaze::SchemaReferenceError(
            reference.destination, sourcemeta::core::to_pointer(pointer),
            "Could not resolve schema reference");
      }

      throw sourcemeta::blaze::SchemaResolutionError(
          identifier, "Could not resolve the reference to an external schema");
    }

    if (!sourcemeta::blaze::is_schema(remote.value())) {
      throw sourcemeta::blaze::SchemaReferenceError(
          identifier, sourcemeta::core::to_pointer(pointer),
          "The JSON document is not a valid JSON Schema");
    }

    const auto remote_base_dialect{sourcemeta::blaze::base_dialect(
        remote.value(), resolver, default_dialect)};
    if (!remote_base_dialect.has_value()) {
      throw sourcemeta::blaze::SchemaReferenceError(
          identifier, sourcemeta::core::to_pointer(pointer),
          "The JSON document is not a valid JSON Schema");
    }

    auto remote_id =
        sourcemeta::blaze::identify(remote.value(), resolver, default_dialect);

    // If the reference has a fragment, verify it exists in the remote
    // schema
    if (reference.fragment.has_value()) {
      // TODO: The fact that we have to re-frame on each loop pass to check
      // for this is probably insanely slow
      sourcemeta::blaze::SchemaFrame remote_frame{
          sourcemeta::blaze::SchemaFrame::Mode::Locations};
      remote_frame.analyse(remote.value(), walker, resolver, default_dialect,
                           identifier);
      if (!remote_frame.traverse(reference.destination).has_value()) {
        throw sourcemeta::blaze::SchemaReferenceError(
            reference.destination, sourcemeta::core::to_pointer(pointer),
            "Could not resolve schema reference");
      }
    }

    sourcemeta::core::JSON::String effective_id{
        remote_id.empty() ? sourcemeta::core::JSON::String{identifier}
                          : sourcemeta::core::JSON::String{remote_id}};

    if (remote.value().is_object()) {
      sourcemeta::blaze::reidentify(remote.value(), effective_id,
                                    remote_base_dialect.value());
    }

    if (effective_id != identifier) {
      sourcemeta::core::URI rewrite_uri{effective_id};
      if (reference.fragment.has_value()) {
        rewrite_uri.fragment(reference.fragment.value());
      }

      ref_rewrites.emplace_back(sourcemeta::core::to_pointer(pointer),
                                rewrite_uri.recompose());
    }

    bundled.emplace(identifier, effective_id);
    bundled.emplace(effective_id, effective_id);
    deferred.emplace_back(std::move(remote).value(), std::move(effective_id),
                          remote_base_dialect.value());
  });

  for (auto &[rewrite_pointer, rewrite_value] : ref_rewrites) {
    sourcemeta::core::set(subschema, rewrite_pointer,
                          sourcemeta::core::JSON{rewrite_value});
  }

  for (auto &[remote, effective_id, remote_dialect] : deferred) {
    bundle_schema(root, container, remote, walker, resolver, default_dialect,
                  effective_id, paths, bundled, include_official_refs,
                  reserved_identifier, depth + 1);
    elevate_embedded_resources(remote, root, container, remote_dialect,
                               resolver, default_dialect, reserved_identifier,
                               bundled);
    embed_schema(root, container, effective_id, reserved_identifier,
                 std::move(remote));
  }
}

} // namespace

namespace sourcemeta::blaze {

auto dependencies(const sourcemeta::core::JSON &schema,
                  const SchemaWalker &walker, const SchemaResolver &resolver,
                  const DependencyCallback &callback,
                  std::string_view default_dialect, std::string_view default_id,
                  const SchemaFrame::Paths &paths) -> void {
  std::unordered_set<std::string> visited;
  const bool include_official_refs{
      is_official_schema(identify(schema, resolver, default_dialect))};
  dependencies_internal(schema, walker, resolver, callback, default_dialect,
                        default_id, paths, visited, include_official_refs);
}

// TODO: Refactor this function to internally rely on the `.dependencies()`
// function
auto bundle(sourcemeta::core::JSON &schema, const SchemaWalker &walker,
            const SchemaResolver &resolver, std::string_view default_dialect,
            std::string_view default_id,
            const std::optional<sourcemeta::core::Pointer> &default_container,
            const SchemaFrame::Paths &paths) -> void {
  std::unordered_map<sourcemeta::core::JSON::String,
                     sourcemeta::core::JSON::String>
      bundled;

  constexpr std::string_view BUNDLE_FALLBACK_IDENTIFIER{
      "__sourcemeta-blaze-bundle__"};
  std::string_view reserved_identifier;

  // If the user's input itself has an identifier that corresponds to an
  // official schema (e.g. a JSON Schema meta-schema being bundled
  // explicitly), then the user is asking for the full graph of officials
  // they depend on. The default filter that skips official references
  // does not apply
  const bool include_official_refs{
      is_official_schema(identify(schema, resolver, default_dialect))};

  // When the outer schema declares a non-official meta-schema, wrap the
  // document in an envelope whose dialect matches the input's base
  // dialect so the resulting compound document has an unambiguous outer
  // dialect (and thus a deterministic container keyword). The original
  // schema lives in the container with its identifier rephrased via an
  // extra `/x` path segment, and any reference targeting the original
  // identifier is rewritten on the fly via the shared `bundled` map below
  if (!default_container.has_value()) {
    const auto outer_dialect{dialect(schema, default_dialect)};
    if (!outer_dialect.empty() && !is_official_schema(outer_dialect)) {
      // Inject `default_id` ahead of elevation so the envelope can carry
      // it as its top-level identifier
      if (!default_id.empty() &&
          identify(schema, resolver, default_dialect).empty()) {
        reidentify(schema, default_id, resolver, default_dialect);
      }

      const auto inner_base_dialect{
          base_dialect(schema, resolver, default_dialect)};
      if (!inner_base_dialect.has_value()) {
        throw SchemaError(
            "Could not determine how to perform bundling in this dialect");
      }

      const auto envelope_container{
          definitions_keyword(inner_base_dialect.value())};
      if (envelope_container.empty()) {
        throw SchemaError(
            "Could not determine how to perform bundling in this dialect");
      }

      const sourcemeta::core::JSON::String original_id{
          identify(schema, resolver, default_dialect)};

      // Discover existing resource URIs in the input so the rephrased
      // inner URI does not collide with a sub-resource the user authored
      std::unordered_set<sourcemeta::core::JSON::String> existing_uris;
      {
        SchemaFrame discovery_frame{SchemaFrame::Mode::Locations};
        discovery_frame.analyse(schema, walker, resolver, default_dialect,
                                default_id, paths);
        discovery_frame.for_each_resource_uri([&](const auto &uri) {
          existing_uris.emplace(sourcemeta::core::JSON::String{uri});
        });
      }

      sourcemeta::core::JSON::String inner_id;
      if (!original_id.empty()) {
        sourcemeta::core::URI inner_uri{std::string{original_id}};
        inner_uri.append_path("x");
        inner_uri.canonicalize();
        inner_id = inner_uri.recompose();
        while (existing_uris.contains(inner_id)) {
          inner_uri.append_path("x");
          inner_id = inner_uri.recompose();
        }
      } else {
        inner_id = sourcemeta::core::JSON::String{BUNDLE_FALLBACK_IDENTIFIER};
        sourcemeta::core::URI inner_uri{inner_id};
        while (existing_uris.contains(inner_id)) {
          inner_uri.append_path("x");
          inner_id = inner_uri.recompose();
        }
        // The bundler is using its reserved fallback identifier as the
        // identity of the embedded inner. From this point on, any other
        // schema we bundle must not declare this same identifier
        reserved_identifier = BUNDLE_FALLBACK_IDENTIFIER;
      }

      auto inner_copy{schema};
      reidentify(inner_copy, inner_id, resolver, default_dialect);

      auto envelope{sourcemeta::core::JSON::make_object()};
      envelope.assign_assume_new(
          "$schema", sourcemeta::core::JSON{
                         std::string{to_string(inner_base_dialect.value())}});
      if (!original_id.empty()) {
        envelope.assign_assume_new(sourcemeta::core::JSON::String{id_keyword(
                                       inner_base_dialect.value())},
                                   sourcemeta::core::JSON{original_id});
      }

      // In Draft 7 and older, `$ref` overrides sibling keywords, so we
      // route the redirect through `allOf` (or `extends` for Draft 3)
      // instead of using a top-level `$ref`
      if (ref_overrides_adjacent_keywords(inner_base_dialect.value())) {
        auto ref_branch{sourcemeta::core::JSON::make_object()};
        ref_branch.assign_assume_new("$ref", sourcemeta::core::JSON{inner_id});
        auto branches{sourcemeta::core::JSON::make_array()};
        branches.push_back(std::move(ref_branch));
        const bool is_draft3{inner_base_dialect.value() ==
                                 SchemaBaseDialect::JSON_Schema_Draft_3 ||
                             inner_base_dialect.value() ==
                                 SchemaBaseDialect::JSON_Schema_Draft_3_Hyper};
        envelope.assign_assume_new(is_draft3 ? "extends" : "allOf",
                                   std::move(branches));
      } else {
        envelope.assign_assume_new("$ref", sourcemeta::core::JSON{inner_id});
      }

      envelope.assign_assume_new(
          sourcemeta::core::JSON::String{envelope_container},
          sourcemeta::core::JSON::make_object());
      envelope.at(sourcemeta::core::JSON::String{envelope_container})
          .assign_assume_new(inner_id, std::move(inner_copy));

      schema = std::move(envelope);

      // Seed the rewrite mapping. Every reference (in the inner itself
      // and in every schema bundle subsequently pulls in) that targets
      // `original_id` will be retargeted at `inner_id`
      if (!original_id.empty()) {
        bundled.emplace(original_id, inner_id);
      }
    }
  }

  // Pre-scan the schema to find any already-embedded schemas and mark them
  // as bundled to avoid re-embedding them. This includes the root schema itself
  // and any schemas already embedded within it
  SchemaFrame initial_frame{SchemaFrame::Mode::Locations};
  initial_frame.analyse(schema, walker, resolver, default_dialect, default_id,
                        paths);
  initial_frame.for_each_resource_uri([&bundled](const auto &uri) {
    bundled.emplace(sourcemeta::core::JSON::String{uri},
                    sourcemeta::core::JSON::String{uri});
  });
  if (default_container.has_value()) {
    // This is undefined behavior
    assert(!default_container.value().empty());
    bundle_schema(schema, default_container.value(), schema, walker, resolver,
                  default_dialect, default_id, paths, bundled,
                  include_official_refs, reserved_identifier);
    return;
  }

  // If the schema identifier is implicit, add it to the top-level of the
  // bundled schema. Otherwise, potential relative references based on this
  // implicit base URI will likely not resolve unless end users happen to
  // know that this implicit base URI is.
  if (!default_id.empty() &&
      identify(schema, resolver, default_dialect).empty()) {
    reidentify(schema, default_id, resolver, default_dialect);
  }

  const auto schema_base_dialect{
      base_dialect(schema, resolver, default_dialect)};
  if (!schema_base_dialect.has_value()) {
    throw SchemaError(
        "Could not determine how to perform bundling in this dialect");
  }

  const auto container_keyword{
      definitions_keyword(schema_base_dialect.value())};
  if (container_keyword.empty()) {
    SchemaFrame frame{SchemaFrame::Mode::References};
    frame.analyse(schema, walker, resolver, default_dialect, default_id);
    if (frame.standalone()) {
      return;
    }

    throw SchemaError(
        "Could not determine how to perform bundling in this dialect");
  }

  if (ref_overrides_adjacent_keywords(schema_base_dialect.value()) &&
      schema.is_object() && schema.defines("$ref")) {
    if (schema.size() == 1) {
      const auto is_draft3{schema_base_dialect.value() ==
                               SchemaBaseDialect::JSON_Schema_Draft_3 ||
                           schema_base_dialect.value() ==
                               SchemaBaseDialect::JSON_Schema_Draft_3_Hyper};
      auto branches{sourcemeta::core::JSON::make_array()};
      branches.push_back(schema);
      schema.at("$ref").into(std::move(branches));
      schema.rename("$ref", is_draft3 ? "extends" : "allOf");
    } else {
      throw SchemaError(
          "Cannot bundle a JSON Schema Draft 7 or older with a top-level "
          "`$ref` (which overrides sibling keywords) without introducing "
          "undefined behavior");
    }
  }

  bundle_schema(schema, {sourcemeta::core::JSON::String{container_keyword}},
                schema, walker, resolver, default_dialect, default_id, paths,
                bundled, include_official_refs, reserved_identifier);
}

auto bundle(const sourcemeta::core::JSON &schema, const SchemaWalker &walker,
            const SchemaResolver &resolver, std::string_view default_dialect,
            std::string_view default_id,
            const std::optional<sourcemeta::core::Pointer> &default_container,
            const SchemaFrame::Paths &paths) -> sourcemeta::core::JSON {
  sourcemeta::core::JSON copy = schema;
  bundle(copy, walker, resolver, default_dialect, default_id, default_container,
         paths);
  return copy;
}

} // namespace sourcemeta::blaze
