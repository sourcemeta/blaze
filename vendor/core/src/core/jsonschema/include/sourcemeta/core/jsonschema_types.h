#ifndef SOURCEMETA_CORE_JSONSCHEMA_TYPES_H_
#define SOURCEMETA_CORE_JSONSCHEMA_TYPES_H_

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <cstdint>       // std::uint8_t
#include <functional>    // std::function, std::reference_wrapper
#include <optional>      // std::optional
#include <set>           // std::set
#include <string>        // std::string
#include <string_view>   // std::string_view
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace sourcemeta::core {

/// @ingroup jsonschema
/// Vocabulary enumeration for known JSON Schema vocabularies
enum class KnownVocabulary : uint32_t {
  // Pre-vocabulary dialects (treated as vocabularies)
  Draft00 = 1u << 0,
  Draft00Hyper = 1u << 1,
  Draft01 = 1u << 2,
  Draft01Hyper = 1u << 3,
  Draft02 = 1u << 4,
  Draft02Hyper = 1u << 5,
  Draft03 = 1u << 6,
  Draft03Hyper = 1u << 7,
  Draft04 = 1u << 8,
  Draft04Hyper = 1u << 9,
  Draft06 = 1u << 10,
  Draft06Hyper = 1u << 11,
  Draft07 = 1u << 12,
  Draft07Hyper = 1u << 13,
  // 2019-09 vocabularies
  Draft201909Core = 1u << 14,
  Draft201909Applicator = 1u << 15,
  Draft201909Validation = 1u << 16,
  Draft201909MetaData = 1u << 17,
  Draft201909Format = 1u << 18,
  Draft201909Content = 1u << 19,
  Draft201909HyperSchema = 1u << 20,
  // 2020-12 vocabularies
  Draft202012Core = 1u << 21,
  Draft202012Applicator = 1u << 22,
  Draft202012Unevaluated = 1u << 23,
  Draft202012Validation = 1u << 24,
  Draft202012MetaData = 1u << 25,
  Draft202012FormatAnnotation = 1u << 26,
  Draft202012FormatAssertion = 1u << 27,
  Draft202012Content = 1u << 28
};

namespace detail {
inline auto uri_to_known_vocabulary(std::string_view uri)
    -> std::optional<KnownVocabulary> {
  using sourcemeta::core::KnownVocabulary;

  // Pre-vocabulary dialects
  if (uri == "http://json-schema.org/draft-00/schema#") {
    return KnownVocabulary::Draft00;
  }
  if (uri == "http://json-schema.org/draft-00/hyper-schema#") {
    return KnownVocabulary::Draft00Hyper;
  }
  if (uri == "http://json-schema.org/draft-01/schema#") {
    return KnownVocabulary::Draft01;
  }
  if (uri == "http://json-schema.org/draft-01/hyper-schema#") {
    return KnownVocabulary::Draft01Hyper;
  }
  if (uri == "http://json-schema.org/draft-02/schema#") {
    return KnownVocabulary::Draft02;
  }
  if (uri == "http://json-schema.org/draft-02/hyper-schema#") {
    return KnownVocabulary::Draft02Hyper;
  }
  if (uri == "http://json-schema.org/draft-03/schema#") {
    return KnownVocabulary::Draft03;
  }
  if (uri == "http://json-schema.org/draft-03/hyper-schema#") {
    return KnownVocabulary::Draft03Hyper;
  }
  if (uri == "http://json-schema.org/draft-04/schema#") {
    return KnownVocabulary::Draft04;
  }
  if (uri == "http://json-schema.org/draft-04/hyper-schema#") {
    return KnownVocabulary::Draft04Hyper;
  }
  if (uri == "http://json-schema.org/draft-06/schema#") {
    return KnownVocabulary::Draft06;
  }
  if (uri == "http://json-schema.org/draft-06/hyper-schema#") {
    return KnownVocabulary::Draft06Hyper;
  }
  if (uri == "http://json-schema.org/draft-07/schema#") {
    return KnownVocabulary::Draft07;
  }
  if (uri == "http://json-schema.org/draft-07/hyper-schema#") {
    return KnownVocabulary::Draft07Hyper;
  }

  // 2019-09 vocabularies
  if (uri == "https://json-schema.org/draft/2019-09/vocab/core") {
    return KnownVocabulary::Draft201909Core;
  }
  if (uri == "https://json-schema.org/draft/2019-09/vocab/applicator") {
    return KnownVocabulary::Draft201909Applicator;
  }
  if (uri == "https://json-schema.org/draft/2019-09/vocab/validation") {
    return KnownVocabulary::Draft201909Validation;
  }
  if (uri == "https://json-schema.org/draft/2019-09/vocab/meta-data") {
    return KnownVocabulary::Draft201909MetaData;
  }
  if (uri == "https://json-schema.org/draft/2019-09/vocab/format") {
    return KnownVocabulary::Draft201909Format;
  }
  if (uri == "https://json-schema.org/draft/2019-09/vocab/content") {
    return KnownVocabulary::Draft201909Content;
  }
  if (uri == "https://json-schema.org/draft/2019-09/vocab/hyper-schema") {
    return KnownVocabulary::Draft201909HyperSchema;
  }

  // 2020-12 vocabularies
  if (uri == "https://json-schema.org/draft/2020-12/vocab/core") {
    return KnownVocabulary::Draft202012Core;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/applicator") {
    return KnownVocabulary::Draft202012Applicator;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/unevaluated") {
    return KnownVocabulary::Draft202012Unevaluated;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/validation") {
    return KnownVocabulary::Draft202012Validation;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/meta-data") {
    return KnownVocabulary::Draft202012MetaData;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/format-annotation") {
    return KnownVocabulary::Draft202012FormatAnnotation;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/format-assertion") {
    return KnownVocabulary::Draft202012FormatAssertion;
  }
  if (uri == "https://json-schema.org/draft/2020-12/vocab/content") {
    return KnownVocabulary::Draft202012Content;
  }

  return std::nullopt;
}
} // namespace detail

/// @ingroup jsonschema
/// Optimized vocabulary set using bitflags for known vocabularies
struct Vocabularies {
  /// Bitflags for enabled known vocabularies
  uint32_t enabled_known = 0;

  /// Bitflags for disabled known vocabularies (for explicit false values)
  uint32_t disabled_known = 0;

  /// Fallback storage for custom/unknown vocabularies
  std::unordered_map<JSON::String, bool> custom;

  /// Check if a vocabulary is enabled
  [[nodiscard]] auto contains(std::string_view uri) const -> bool {
    const auto maybe_known = detail::uri_to_known_vocabulary(uri);
    if (maybe_known.has_value()) {
      const auto flag = static_cast<uint32_t>(maybe_known.value());
      return (enabled_known & flag) != 0 || (disabled_known & flag) != 0;
    }

    const auto key{std::string{uri}};
    const auto iterator{custom.find(key)};
    return iterator != custom.end() && iterator->second;
  }

  /// Insert a vocabulary
  auto insert(const std::pair<JSON::String, bool> &entry) -> void {
    const auto maybe_known = detail::uri_to_known_vocabulary(entry.first);
    if (maybe_known.has_value()) {
      const auto flag = static_cast<uint32_t>(maybe_known.value());
      if (entry.second) {
        enabled_known |= flag;
        disabled_known &= ~flag;
      } else {
        disabled_known |= flag;
        enabled_known &= ~flag;
      }
    } else {
      custom.insert(entry);
    }
  }

  /// Get vocabulary status by URI
  [[nodiscard]] auto find(std::string_view uri) const -> std::optional<bool> {
    const auto maybe_known = detail::uri_to_known_vocabulary(uri);
    if (maybe_known.has_value()) {
      const auto flag = static_cast<uint32_t>(maybe_known.value());
      if ((enabled_known & flag) != 0) {
        return true;
      }
      if ((disabled_known & flag) != 0) {
        return false;
      }
      return std::nullopt;
    }

    const auto key{std::string{uri}};
    const auto iterator{custom.find(key)};
    if (iterator != custom.end()) {
      return iterator->second;
    }
    return std::nullopt;
  }

  /// Merge another Vocabularies into this one
  auto merge(const Vocabularies &other) -> void {
    const uint32_t already_set = enabled_known | disabled_known;
    const uint32_t to_enable = other.enabled_known & ~already_set;
    const uint32_t to_disable = other.disabled_known & ~already_set;
    enabled_known |= to_enable;
    disabled_known |= to_disable;

    for (const auto &entry : other.custom) {
      custom.insert(entry);
    }
  }

  /// Get all active (enabled or disabled) vocabularies as key-value pairs
  [[nodiscard]] auto all_vocabularies() const
      -> std::vector<std::pair<std::string, bool>> {
    std::vector<std::pair<std::string, bool>> result;
    result.reserve(32);

    const auto check_and_add = [&](KnownVocabulary vocab,
                                   std::string_view uri) {
      const auto flag = static_cast<uint32_t>(vocab);
      if ((enabled_known & flag) != 0) {
        result.emplace_back(std::string{uri}, true);
      } else if ((disabled_known & flag) != 0) {
        result.emplace_back(std::string{uri}, false);
      }
    };

    // Pre-vocabulary dialects
    check_and_add(KnownVocabulary::Draft00, "http://json-schema.org/draft-00/schema#");
    check_and_add(KnownVocabulary::Draft00Hyper, "http://json-schema.org/draft-00/hyper-schema#");
    check_and_add(KnownVocabulary::Draft01, "http://json-schema.org/draft-01/schema#");
    check_and_add(KnownVocabulary::Draft01Hyper, "http://json-schema.org/draft-01/hyper-schema#");
    check_and_add(KnownVocabulary::Draft02, "http://json-schema.org/draft-02/schema#");
    check_and_add(KnownVocabulary::Draft02Hyper, "http://json-schema.org/draft-02/hyper-schema#");
    check_and_add(KnownVocabulary::Draft03, "http://json-schema.org/draft-03/schema#");
    check_and_add(KnownVocabulary::Draft03Hyper, "http://json-schema.org/draft-03/hyper-schema#");
    check_and_add(KnownVocabulary::Draft04, "http://json-schema.org/draft-04/schema#");
    check_and_add(KnownVocabulary::Draft04Hyper, "http://json-schema.org/draft-04/hyper-schema#");
    check_and_add(KnownVocabulary::Draft06, "http://json-schema.org/draft-06/schema#");
    check_and_add(KnownVocabulary::Draft06Hyper, "http://json-schema.org/draft-06/hyper-schema#");
    check_and_add(KnownVocabulary::Draft07, "http://json-schema.org/draft-07/schema#");
    check_and_add(KnownVocabulary::Draft07Hyper, "http://json-schema.org/draft-07/hyper-schema#");

    // 2019-09 vocabularies
    check_and_add(KnownVocabulary::Draft201909Core, "https://json-schema.org/draft/2019-09/vocab/core");
    check_and_add(KnownVocabulary::Draft201909Applicator, "https://json-schema.org/draft/2019-09/vocab/applicator");
    check_and_add(KnownVocabulary::Draft201909Validation, "https://json-schema.org/draft/2019-09/vocab/validation");
    check_and_add(KnownVocabulary::Draft201909MetaData, "https://json-schema.org/draft/2019-09/vocab/meta-data");
    check_and_add(KnownVocabulary::Draft201909Format, "https://json-schema.org/draft/2019-09/vocab/format");
    check_and_add(KnownVocabulary::Draft201909Content, "https://json-schema.org/draft/2019-09/vocab/content");
    check_and_add(KnownVocabulary::Draft201909HyperSchema, "https://json-schema.org/draft/2019-09/vocab/hyper-schema");

    // 2020-12 vocabularies
    check_and_add(KnownVocabulary::Draft202012Core, "https://json-schema.org/draft/2020-12/vocab/core");
    check_and_add(KnownVocabulary::Draft202012Applicator, "https://json-schema.org/draft/2020-12/vocab/applicator");
    check_and_add(KnownVocabulary::Draft202012Unevaluated, "https://json-schema.org/draft/2020-12/vocab/unevaluated");
    check_and_add(KnownVocabulary::Draft202012Validation, "https://json-schema.org/draft/2020-12/vocab/validation");
    check_and_add(KnownVocabulary::Draft202012MetaData, "https://json-schema.org/draft/2020-12/vocab/meta-data");
    check_and_add(KnownVocabulary::Draft202012FormatAnnotation, "https://json-schema.org/draft/2020-12/vocab/format-annotation");
    check_and_add(KnownVocabulary::Draft202012FormatAssertion, "https://json-schema.org/draft/2020-12/vocab/format-assertion");
    check_and_add(KnownVocabulary::Draft202012Content, "https://json-schema.org/draft/2020-12/vocab/content");

    for (const auto &entry : custom) {
      result.emplace_back(entry);
    }

    return result;
  }
};

// Take a URI and get back a schema
/// @ingroup jsonschema
///
/// Some functions need to reference other schemas by their URIs. To accomplish
/// this in a generic and flexible way, these functions take resolver functions
/// as arguments, of the type sourcemeta::core::SchemaResolver.
///
/// For convenience, we provide the following default resolvers:
///
/// - sourcemeta::core::schema_official_resolver
///
/// You can implement resolvers to read from a local storage, to send HTTP
/// requests, or anything your application might require. Unless your resolver
/// is trivial, it is recommended to create a callable object that implements
/// the function interface.
using SchemaResolver = std::function<std::optional<JSON>(std::string_view)>;

/// @ingroup jsonschema
/// The strategy to follow when attempting to identify a schema
enum class SchemaIdentificationStrategy : std::uint8_t {
  /// Only proceed if we can guarantee the identifier is valid
  Strict,

  /// Attempt to guess even if we don't know the base dialect
  Loose
};

/// @ingroup jsonschema
/// The reference type
enum class SchemaReferenceType : std::uint8_t { Static, Dynamic };

#if defined(__GNUC__)
#pragma GCC diagnostic push
// For some strange reason, GCC on Debian 11 believes that a member of
// an enum class (which is namespaced by definition), can shadow an
// alias defined even on a different namespace.
#pragma GCC diagnostic ignored "-Wshadow"
#endif
/// @ingroup jsonschema
/// Determines the type of a JSON Schema keyword
enum class SchemaKeywordType : std::uint8_t {
  /// The JSON Schema keyword is unknown
  Unknown,
  /// The JSON Schema keyword is a non-applicator assertion
  Assertion,
  /// The JSON Schema keyword is a non-applicator annotation
  Annotation,
  /// The JSON Schema keyword is a reference
  Reference,
  /// The JSON Schema keyword is known but doesn't match any other type
  Other,
  /// The JSON Schema keyword is considered to be a comment without any
  /// additional meaning
  Comment,
  /// The JSON Schema keyword is a reserved location that potentially
  /// takes an object as argument, whose values are potentially
  /// JSON Schema definitions
  LocationMembers,

  /// The JSON Schema keyword is an applicator that potentially
  /// takes an object as argument, whose values are potentially
  /// JSON Schema definitions.
  /// The instance traverses based on the members as property names
  ApplicatorMembersTraversePropertyStatic,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes an object as argument, whose values are potentially
  /// JSON Schema definitions.
  /// The instance traverses based on the members as property regular
  /// expressions
  ApplicatorMembersTraversePropertyRegex,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument
  /// The instance traverses to some of the properties
  ApplicatorValueTraverseSomeProperty,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument
  /// The instance traverses to any property key
  ApplicatorValueTraverseAnyPropertyKey,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument
  /// The instance traverses to any item
  ApplicatorValueTraverseAnyItem,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument
  /// The instance traverses to some of the items
  ApplicatorValueTraverseSomeItem,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument
  /// The instance traverses back to the parent
  ApplicatorValueTraverseParent,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes an array of potentially JSON Schema definitions
  /// as an argument
  /// The instance traverses based on the element indexes
  ApplicatorElementsTraverseItem,
  /// The JSON Schema keyword is an applicator that may take a JSON Schema
  /// definition or an array of potentially JSON Schema definitions
  /// as an argument
  /// The instance traverses to any item or based on the element indexes
  ApplicatorValueOrElementsTraverseAnyItemOrItem,
  /// The JSON Schema keyword is an applicator that may take a JSON Schema
  /// definition or an array of potentially JSON Schema definitions
  /// as an argument without affecting the instance location.
  /// The instance does not traverse
  ApplicatorValueOrElementsInPlace,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes an object as argument, whose values are potentially
  /// JSON Schema definitions without affecting the instance location.
  /// The instance does not traverse
  ApplicatorMembersInPlaceSome,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes an array of potentially JSON Schema definitions
  /// as an argument without affecting the instance location.
  /// The instance does not traverse
  ApplicatorElementsInPlace,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes an array of potentially JSON Schema definitions
  /// as an argument without affecting the instance location
  /// The instance does not traverse, and only some of the
  /// elements apply.
  ApplicatorElementsInPlaceSome,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes an array of potentially JSON Schema definitions
  /// as an argument without affecting the instance location
  /// The instance does not traverse, and only some of the
  /// elements apply in negated form.
  ApplicatorElementsInPlaceSomeNegate,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument without affecting the
  /// instance location.
  /// The instance does not traverse, and only applies some of the times.
  ApplicatorValueInPlaceMaybe,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument but its evaluation follows
  /// special rules.
  /// The instance does not traverse
  ApplicatorValueInPlaceOther,
  /// The JSON Schema keyword is an applicator that potentially
  /// takes a JSON Schema definition as an argument but the instance is expected
  /// to not validate against it.
  /// The instance does not traverse
  ApplicatorValueInPlaceNegate,
};
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

/// @ingroup jsonschema
/// A structure that encapsulates the result of walker over a specific keyword
struct SchemaWalkerResult {
  /// The walker strategy to continue traversing across the schema
  SchemaKeywordType type;
  /// The vocabulary associated with the keyword, if any
  std::optional<std::string> vocabulary;
  /// The keywords a given keyword depends on (if any) during the evaluation
  /// process
  std::set<std::string> dependencies;
  /// The JSON instance types that this keyword applies to (or to all of them)
  std::set<JSON::Type> instances;
};

/// @ingroup jsonschema
///
/// For walking purposes, some functions need to understand which JSON Schema
/// keywords declare other JSON Schema definitions. To accomplish this in a
/// generic and flexible way that does not assume the use any vocabulary other
/// than `core`, these functions take a walker function as argument, of the type
/// sourcemeta::core::SchemaWalker.
///
/// For convenience, we provide the following default walkers:
///
/// - sourcemeta::core::schema_official_walker
/// - sourcemeta::core::schema_walker_none
using SchemaWalker =
    std::function<SchemaWalkerResult(std::string_view, const Vocabularies &)>;

/// @ingroup jsonschema
/// An entry of a schema iterator.
struct SchemaIteratorEntry {
  // TODO: Turn this into a weak pointer
  std::optional<Pointer> parent;
  // TODO: Turn this into a weak pointer
  Pointer pointer;
  std::optional<std::string> dialect;
  Vocabularies vocabularies;
  std::optional<std::string> base_dialect;
  std::reference_wrapper<const JSON> subschema;

  // TODO: These two pointer templates contain some overlap.
  // Instead, have a `base_instance_location` and a `relative_instance_location`
  // that when concatenated, represent the full `instance_location`
  PointerTemplate instance_location;
  PointerTemplate relative_instance_location;

  bool orphan;
};

} // namespace sourcemeta::core

#endif
