#ifndef SOURCEMETA_BLAZE_FOUNDATION_TYPES_H_
#define SOURCEMETA_BLAZE_FOUNDATION_TYPES_H_

#include <sourcemeta/blaze/foundation_vocabularies.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <cassert>     // assert
#include <concepts>    // std::move_constructible, std::copy_constructible
#include <cstdint>     // std::uint8_t
#include <format>      // std::formatter, std::format_to
#include <functional>  // std::function, std::reference_wrapper
#include <optional>    // std::optional
#include <ostream>     // std::ostream
#include <span>        // std::span
#include <sstream>     // std::ostringstream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <type_traits> // std::is_object_v

namespace sourcemeta::blaze {

// TODO: This is not specific to schemas at all. Once it proves itself here,
// move it into Core as a general purpose type

/// @ingroup foundation
/// What a sourcemeta::blaze::OwnedOrReference can hold
template <typename T>
concept Referenceable = std::is_object_v<T> && std::move_constructible<T>;

/// @ingroup foundation
/// Either a value this holds itself, a reference to one that outlives it, or
/// nothing at all.
///
/// Reach for this when a function sometimes materialises its result and
/// sometimes hands back something it already has. Producers that build a value,
/// by reading a file, performing a network request, or computing it, return it
/// as they always would. Producers backed by storage that outlives the call,
/// such as a long lived cache, return a reference instead and skip the copy.
///
/// A reference must stay put and stay alive for as long as the consumer reads
/// it. Anything temporary binds to the owning constructor, so a temporary can
/// never be captured by reference here.
template <Referenceable T> class OwnedOrReference {
public:
  /// Hold nothing
  OwnedOrReference() = default;

  /// Hold nothing
  // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
  OwnedOrReference(std::nullopt_t) {}

  /// Take ownership of a value that may or may not be there
  // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
  OwnedOrReference(std::optional<T> &&value) : owned{std::move(value)} {}

  /// Take ownership of a value
  // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
  OwnedOrReference(T &&value) : owned{std::move(value)} {}

  /// Refer to a value that outlives this. Anything temporary binds to the
  /// owning constructor above instead, so this never refers to a dead value
  // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
  OwnedOrReference(const T &value) : referenced{&value} {}

  // Prevent accidental copies, as copying is the very thing this type exists
  // to avoid. Take ownership through `to_owned` instead
  OwnedOrReference(const OwnedOrReference &) = delete;
  auto operator=(const OwnedOrReference &) -> OwnedOrReference & = delete;
  /// Move
  OwnedOrReference(OwnedOrReference &&) = default;
  /// Move
  auto operator=(OwnedOrReference &&) -> OwnedOrReference & = default;
  ~OwnedOrReference() = default;

  /// Whether there is anything to read
  [[nodiscard]] auto has_value() const noexcept -> bool {
    return this->referenced != nullptr || this->owned.has_value();
  }

  /// Read the value, however it is held
  [[nodiscard]] auto value() const -> const T & {
    assert(this->has_value());
    return this->referenced != nullptr ? *this->referenced
                                       : this->owned.value();
  }

  /// Read the value, however it is held
  [[nodiscard]] auto operator*() const -> const T & { return this->value(); }

  /// Read the value, however it is held
  [[nodiscard]] auto operator->() const -> const T * { return &this->value(); }

  /// Get a value the caller owns, moving out of this one when it owns it and
  /// copying only when it holds a reference
  [[nodiscard]] auto to_owned() && -> T
    requires std::copy_constructible<T>
  {
    assert(this->has_value());
    if (this->referenced != nullptr) {
      return *this->referenced;
    }

    return std::move(this->owned).value();
  }

private:
  std::optional<T> owned;
  const T *referenced{nullptr};
};

/// @ingroup foundation
/// What a sourcemeta::blaze::SchemaResolver hands back: either a schema it
/// owns, or a reference to one that outlives the call
using SchemaResolverResult = OwnedOrReference<sourcemeta::core::JSON>;

/// @ingroup foundation
///
/// Some functions need to reference other schemas by their URIs. To accomplish
/// this in a generic and flexible way, these functions take resolver functions
/// as arguments, of the type sourcemeta::blaze::SchemaResolver.
///
/// For convenience, we provide the following default resolvers:
///
/// - sourcemeta::blaze::schema_resolver
///
/// You can implement resolvers to read from a local storage, to send HTTP
/// requests, or anything your application might require. Unless your resolver
/// is trivial, it is recommended to create a callable object that implements
/// the function interface.
using SchemaResolver = std::function<SchemaResolverResult(std::string_view)>;

/// @ingroup foundation
/// The reference type
enum class SchemaReferenceType : std::uint8_t { Static, Dynamic };

/// @ingroup foundation
/// All the known JSON Schema base dialects
enum class SchemaBaseDialect : std::uint8_t {
  JSON_Schema_2020_12,
  JSON_Schema_2020_12_Hyper,
  JSON_Schema_2019_09,
  JSON_Schema_2019_09_Hyper,
  JSON_Schema_Draft_7,
  JSON_Schema_Draft_7_Hyper,
  JSON_Schema_Draft_6,
  JSON_Schema_Draft_6_Hyper,
  JSON_Schema_Draft_4,
  JSON_Schema_Draft_4_Hyper,
  JSON_Schema_Draft_3,
  JSON_Schema_Draft_3_Hyper,
  JSON_Schema_Draft_2_Hyper,
  JSON_Schema_Draft_1_Hyper,
  JSON_Schema_Draft_0_Hyper
};

/// @ingroup foundation
/// Write a base dialect to a stream as its URI
SOURCEMETA_BLAZE_FOUNDATION_EXPORT
auto operator<<(std::ostream &stream, const SchemaBaseDialect base_dialect)
    -> std::ostream &;

#if defined(__GNUC__)
#pragma GCC diagnostic push
// For some strange reason, GCC on Debian 11 believes that a member of
// an enum class (which is namespaced by definition), can shadow an
// alias defined even on a different namespace.
#pragma GCC diagnostic ignored "-Wshadow"
#endif
/// @ingroup foundation
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

/// @ingroup foundation
/// A structure that encapsulates the result of walker over a specific keyword
struct SchemaWalkerResult {
  /// The walker strategy to continue traversing across the schema
  SchemaKeywordType type;
  /// The vocabulary associated with the keyword, if any
  std::optional<SchemaVocabularies::URIView> vocabulary;
  /// The keywords a given keyword depends on (if any) during the evaluation
  /// process
  std::span<const std::string_view> dependencies;
  /// The keywords a given keyword depends on for evaluation ordering purposes
  /// only (not semantic dependencies)
  std::span<const std::string_view> order_dependencies;
  /// The JSON instance types that this keyword applies to (empty means all)
  sourcemeta::core::JSON::TypeSet instances;

  // Prevent accidental copies, as walker results are always returned by
  // reference
  SchemaWalkerResult(const SchemaWalkerResult &) = delete;
  auto operator=(const SchemaWalkerResult &) -> SchemaWalkerResult & = delete;
  SchemaWalkerResult(SchemaWalkerResult &&) = default;
  auto operator=(SchemaWalkerResult &&) -> SchemaWalkerResult & = default;
  ~SchemaWalkerResult() = default;

  constexpr SchemaWalkerResult(
      SchemaKeywordType type_,
      std::optional<SchemaVocabularies::URIView> vocabulary_,
      std::span<const std::string_view> dependencies_,
      std::span<const std::string_view> order_dependencies_,
      sourcemeta::core::JSON::TypeSet instances_)
      : type{type_}, vocabulary{vocabulary_}, dependencies{dependencies_},
        order_dependencies{order_dependencies_}, instances{instances_} {}
};

/// @ingroup foundation
///
/// For walking purposes, some functions need to understand which JSON Schema
/// keywords declare other JSON Schema definitions. To accomplish this in a
/// generic and flexible way that does not assume the use any vocabulary other
/// than `core`, these functions take a walker function as argument.
using SchemaWalker = std::function<const SchemaWalkerResult &(
    std::string_view, const SchemaVocabularies &)>;

} // namespace sourcemeta::blaze

template <> struct std::formatter<sourcemeta::blaze::SchemaBaseDialect> {
  constexpr auto parse(std::format_parse_context &context)
      -> decltype(context.begin()) {
    return context.begin();
  }

  auto format(const sourcemeta::blaze::SchemaBaseDialect value,
              std::format_context &context) const -> decltype(context.out()) {
    std::ostringstream stream;
    stream << value;
    return std::format_to(context.out(), "{}", stream.str());
  }
};

#endif
