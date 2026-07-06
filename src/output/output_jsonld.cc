#include <sourcemeta/blaze/output_jsonld.h>

#include <sourcemeta/core/jsonld.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/uri.h>

#include <algorithm>     // std::ranges::sort, std::ranges::any_of
#include <functional>    // std::ref
#include <tuple>         // std::tie
#include <unordered_map> // std::unordered_map
#include <utility>       // std::move
#include <variant>       // std::variant, std::get, std::holds_alternative
#include <vector>        // std::vector

namespace {

// The JSON-LD facts accumulated at one instance location, before a descriptor
// kind is derived from the instance value shape.
struct Facts {
  std::vector<sourcemeta::core::JSONLDEdge> edges;
  std::vector<sourcemeta::core::JSON::String> types;
};

using Accumulator = std::unordered_map<sourcemeta::core::WeakPointer, Facts,
                                       sourcemeta::core::WeakPointer::Hasher>;

// Default the undescribed elements of a collection: a scalar becomes a native
// literal, and a nested array becomes an inner (unordered) collection, whose
// own elements are filled the same way. As unordered collections, nested arrays
// flatten into their parent during materialization. Elements that carry their
// own annotations already have an accumulator entry and are left untouched.
auto fill_collection(sourcemeta::core::JSONLDWeakAnnotationMap &map,
                     const Accumulator &accumulator,
                     const sourcemeta::core::WeakPointer &pointer,
                     const sourcemeta::core::JSON &array) -> void {
  for (std::size_t index = 0; index < array.size(); index += 1) {
    auto element_pointer{pointer};
    element_pointer.push_back(index);
    if (accumulator.contains(element_pointer)) {
      continue;
    }

    const auto &element{array.at(index)};
    if (element.is_array()) {
      map.emplace(
          element_pointer,
          sourcemeta::core::JSONLDDescriptor{
              .edges = {}, .value = sourcemeta::core::JSONLDCollection{}});
      fill_collection(map, accumulator, element_pointer, element);
    } else if (!element.is_object()) {
      map.emplace(std::move(element_pointer),
                  sourcemeta::core::JSONLDDescriptor{
                      .edges = {}, .value = sourcemeta::core::JSONLDLiteral{}});
    }
  }
}

auto add_edge(std::vector<sourcemeta::core::JSONLDEdge> &edges,
              const sourcemeta::core::JSON::String &predicate,
              const bool reverse) -> void {
  const auto exists{std::ranges::any_of(
      edges,
      [&predicate, reverse](const sourcemeta::core::JSONLDEdge &edge) -> bool {
        return edge.predicate == predicate && edge.reverse == reverse;
      })};
  if (!exists) {
    edges.push_back({.predicate = predicate, .reverse = reverse});
  }
}

auto add_type(std::vector<sourcemeta::core::JSON::String> &types,
              const sourcemeta::core::JSON::String &type) -> void {
  const auto exists{std::ranges::any_of(
      types, [&type](const sourcemeta::core::JSON::String &existing) -> bool {
        return existing == type;
      })};
  if (!exists) {
    types.push_back(type);
  }
}

// Whether an annotation value is usable as an absolute IRI
auto is_iri_value(const sourcemeta::core::JSON &value) -> bool {
  return value.is_string() && sourcemeta::core::URI::is_iri(value.to_string());
}

auto type_iri_error(const sourcemeta::core::WeakPointer &instance_location)
    -> sourcemeta::blaze::JSONLDResolutionError {
  return {.instance_location = sourcemeta::core::to_pointer(instance_location),
          .facet = sourcemeta::blaze::JSONLDFacet::Type,
          .message = "The value of x-jsonld-type must be an absolute IRI"};
}

// Turn the applicable x-jsonld-* annotations into a resolved annotation map, or
// into the first resolution error found. Only x-jsonld-id and x-jsonld-type are
// handled for now, so resolution fails on a malformed IRI value or on a type
// assigned to a position that does not denote a node.
auto resolve(const sourcemeta::core::JSON &instance,
             const sourcemeta::blaze::SimpleOutput &output)
    -> std::variant<sourcemeta::core::JSONLDWeakAnnotationMap,
                    sourcemeta::blaze::JSONLDResolutionError> {
  Accumulator accumulator;

  for (const auto &[location, values] : output.annotations()) {
    if (location.evaluate_path.empty()) {
      continue;
    }

    const auto &keyword{location.evaluate_path.back().to_property()};
    // Only the keywords resolved below may contribute facts. An unhandled
    // keyword must not create an accumulator entry, as the empty facts would
    // otherwise materialize a spurious node or literal descriptor
    if (keyword != "x-jsonld-id" && keyword != "x-jsonld-type") {
      continue;
    }

    auto &facts{accumulator[location.instance_location]};
    if (keyword == "x-jsonld-id") {
      for (const auto &value : values) {
        if (!is_iri_value(value)) {
          return sourcemeta::blaze::JSONLDResolutionError{
              .instance_location =
                  sourcemeta::core::to_pointer(location.instance_location),
              .facet = sourcemeta::blaze::JSONLDFacet::Predicate,
              .message = "The value of x-jsonld-id must be an absolute IRI"};
        }

        add_edge(facts.edges, value.to_string(), false);
      }
    } else if (keyword == "x-jsonld-type") {
      for (const auto &value : values) {
        if (value.is_array()) {
          for (const auto &element : value.as_array()) {
            if (!is_iri_value(element)) {
              return type_iri_error(location.instance_location);
            }

            add_type(facts.types, element.to_string());
          }
        } else {
          if (!is_iri_value(value)) {
            return type_iri_error(location.instance_location);
          }

          add_type(facts.types, value.to_string());
        }
      }
    }
  }

  sourcemeta::core::JSONLDWeakAnnotationMap map;
  for (auto &[pointer, facts] : accumulator) {
    std::ranges::sort(facts.edges,
                      [](const sourcemeta::core::JSONLDEdge &left,
                         const sourcemeta::core::JSONLDEdge &right) -> bool {
                        return std::tie(left.predicate, left.reverse) <
                               std::tie(right.predicate, right.reverse);
                      });
    std::ranges::sort(facts.types);

    const auto &value{sourcemeta::core::get(instance, pointer)};

    // A type denotes an rdf:type, which only a node can carry
    if (!value.is_object() && !facts.types.empty()) {
      return sourcemeta::blaze::JSONLDResolutionError{
          .instance_location = sourcemeta::core::to_pointer(pointer),
          .facet = sourcemeta::blaze::JSONLDFacet::Type,
          .message = "A JSON-LD type can only be assigned to an object value"};
    }

    // A predicate is only meaningful on an object property, whose parent node
    // it attaches to. The document root (an empty pointer) has no parent, and
    // an array element (an index token) inherits the enclosing edge, so a
    // predicate on either is an error. A type on such a position is fine when
    // it is a node.
    if (!facts.edges.empty() &&
        (pointer.empty() || !pointer.back().is_property())) {
      return sourcemeta::blaze::JSONLDResolutionError{
          .instance_location = sourcemeta::core::to_pointer(pointer),
          .facet = sourcemeta::blaze::JSONLDFacet::Predicate,
          .message = pointer.empty()
                         ? "A JSON-LD predicate cannot be assigned to the "
                           "document root"
                         : "A JSON-LD predicate cannot be assigned to an array "
                           "element"};
    }

    sourcemeta::core::JSONLDDescriptor descriptor;
    descriptor.edges = std::move(facts.edges);
    if (value.is_object()) {
      descriptor.value =
          sourcemeta::core::JSONLDNode{.types = std::move(facts.types)};
    } else if (value.is_array()) {
      descriptor.value = sourcemeta::core::JSONLDCollection{};
    } else {
      descriptor.value = sourcemeta::core::JSONLDLiteral{};
    }

    map.emplace(pointer, std::move(descriptor));

    if (value.is_array()) {
      fill_collection(map, accumulator, pointer, value);
    }
  }

  return map;
}

} // namespace

namespace sourcemeta::blaze {

auto jsonld(Evaluator &evaluator, const Template &schema,
            const sourcemeta::core::JSON &instance) -> JSONLDOutcome {
  SimpleOutput output{instance};
  const auto valid{evaluator.validate(schema, instance, std::ref(output))};
  if (!valid) {
    return std::move(output).release();
  }

  auto resolved{resolve(instance, output)};
  if (std::holds_alternative<JSONLDResolutionError>(resolved)) {
    return std::get<JSONLDResolutionError>(std::move(resolved));
  }

  const auto &map{
      std::get<sourcemeta::core::JSONLDWeakAnnotationMap>(resolved)};
  return sourcemeta::core::jsonld_materialize(instance, map);
}

} // namespace sourcemeta::blaze
