#ifndef SOURCEMETA_BLAZE_EVALUATOR_VALUE_H
#define SOURCEMETA_BLAZE_EVALUATOR_VALUE_H

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/regex.h>

#include <cstdint>       // std::uint8_t
#include <optional>      // std::optional
#include <string>        // std::string
#include <tuple>         // std::tuple
#include <unordered_set> // std::unordered_set
#include <utility>       // std::pair
#include <vector>        // std::vector

namespace sourcemeta::blaze {

/// @ingroup evaluator
/// @brief Represents a compiler step empty value
struct ValueNone {
  [[nodiscard]] auto to_json() const -> sourcemeta::core::JSON {
    return sourcemeta::core::JSON{nullptr};
  }

  static auto from_json(const sourcemeta::core::JSON &)
      -> std::optional<ValueNone> {
    return ValueNone{};
  }
};

/// @ingroup evaluator
/// Represents a compiler step JSON value
using ValueJSON = sourcemeta::core::JSON;

/// @ingroup evaluator
/// Represents a set of JSON values
using ValueSet =
    std::unordered_set<sourcemeta::core::JSON,
                       sourcemeta::core::HashJSON<sourcemeta::core::JSON>>;

/// @ingroup evaluator
/// Represents a compiler step string value
using ValueString = sourcemeta::core::JSON::String;

/// @ingroup evaluator
/// Represents a compiler step object property value
using ValueProperty =
    std::pair<ValueString, sourcemeta::core::JSON::Object::hash_type>;

/// @ingroup evaluator
/// Represents a compiler step string values
using ValueStrings = std::vector<ValueString>;

/// @ingroup evaluator
/// Represents a compiler step string set of values
using ValueStringSet = sourcemeta::core::JSONPropertySet;

/// @ingroup evaluator
/// Represents a compiler step JSON types value as a bitmask
using ValueTypes = sourcemeta::core::JSON::TypeSet;

/// @ingroup evaluator
/// Represents a compiler step JSON type value
using ValueType = sourcemeta::core::JSON::Type;

/// @ingroup evaluator
/// Represents a compiler step ECMA regular expression value. We store both the
/// original string and the regular expression as standard regular expressions
/// do not keep a copy of their original value (which we need for serialization
/// purposes)
// NOLINTNEXTLINE(bugprone-exception-escape)
struct ValueRegex {
  using second_type = ValueString;
  using first_type = sourcemeta::core::Regex;
  first_type first;
  second_type second;

  [[nodiscard]] auto to_json() const -> sourcemeta::core::JSON {
    return sourcemeta::core::to_json(this->second);
  }

  static auto from_json(const sourcemeta::core::JSON &value)
      -> std::optional<ValueRegex> {
    if (!value.is_string()) {
      return std::nullopt;
    }

    auto string{value.to_string()};
    auto regex{sourcemeta::core::to_regex(string)};
    if (!regex.has_value()) {
      return std::nullopt;
    }

    // NOLINTNEXTLINE(modernize-use-designated-initializers)
    return ValueRegex{std::move(regex).value(), std::move(string)};
  }
};

/// @ingroup evaluator
/// Represents a compiler step JSON unsigned integer value
using ValueUnsignedInteger = std::size_t;

/// @ingroup evaluator
/// Represents a compiler step range value. The boolean option
/// modifies whether the range is considered exhaustively or
/// if the evaluator is allowed to break early
using ValueRange = std::tuple<std::size_t, std::optional<std::size_t>, bool>;

/// @ingroup evaluator
/// Represents a compiler step boolean value
using ValueBoolean = bool;

/// @ingroup evaluator
/// Represents a compiler step string logical type
enum class ValueStringType : std::uint8_t {
  URI,
  URIReference,
  URITemplate,
  IRI,
  IRIReference,
  Email,
  IDNEmail,
  IPv4,
  IPv6,
  Hostname,
  IDNHostname,
  DateTime,
  Date,
  Time,
  PartialTime,
  Duration,
  JSONPointer,
  RelativeJSONPointer,
  UUID,
  Regex,
  Color,
  Base64
};

/// @ingroup evaluator
/// Represents an compiler step that maps strings to strings
using ValueStringMap = sourcemeta::core::JSONObject<
    ValueString, ValueStrings, sourcemeta::core::PropertyHashJSON<ValueString>>;

/// @ingroup evaluator
/// Represents a compiler step value that consist of object property filters
/// (strings, prefixes, regexes)
using ValuePropertyFilter =
    std::tuple<ValueStringSet, ValueStrings, std::vector<ValueRegex>>;

/// @ingroup evaluator
/// Represents a compiler step value that consists of two indexes
using ValueIndexPair = std::pair<std::size_t, std::size_t>;

/// @ingroup evaluator
/// Represents a compiler step value that consists of a pointer
using ValuePointer = sourcemeta::core::Pointer;

/// @ingroup evaluator
/// @brief Selects which part of a property name's hash a lookup compares
///
/// The low half carries the name's size and its first seven bytes and the high
/// half the eight after them, so either tells most sets of names apart on its
/// own. `Folded` mixes the whole hash down to one word for the sets that
/// neither half separates
enum class ValueNamedDiscriminator : std::uint8_t { Low, High, Folded };

/// @ingroup evaluator
/// @brief Represents a compiler step property name to child index map
///
/// The entries are sorted by the size of the name and held as parallel arrays
/// so that a lookup scans nothing but `discriminators`, eight candidates to a
/// cache line, and reads the arrays beside it only once a candidate matches.
/// Everything a lookup reads before it finds a match comes first, so that it
/// never touches a second cache line of the map to get started.
/// A discriminator is the low half of the name's hash, which carries the name's
/// size and its first seven bytes, so names that differ in either never
/// collide. The half beside it carries the next eight bytes and settles a
/// candidate whose discriminator matches, so the scan still reads one array
/// while names that only differ further in are still told apart
struct ValueNamedIndexes {
  /// Bit N set when some name has size N, so that a size no name has is
  /// rejected without reading an entry at all. A name too long for a bit of
  /// its own leaves every bit set
  ValueUnsignedInteger lengths{0};
  /// Which half of the hash, or which mix of it, the discriminators were taken
  /// from. The one chosen is the cheapest that tells this map's names apart
  ValueNamedDiscriminator discriminator{ValueNamedDiscriminator::Low};
  /// Whether matching a discriminator settles a lookup on its own, which holds
  /// unless two names share one
  bool exact{true};
  /// For every name size, the one-based inclusive range of entries that have
  /// that size. Empty when there are too few entries for the load it costs to
  /// pay for the scan it saves
  std::vector<ValueIndexPair> sizes;
  /// The discriminator of every name, in ascending order of name size
  std::vector<ValueUnsignedInteger> discriminators;
  /// The child instruction each entry selects, parallel to `discriminators`
  std::vector<ValueUnsignedInteger> children;
  /// Each entry's name, parallel to `discriminators`. A lookup only reads one
  /// when `exact` is false, though the map always carries them
  std::vector<ValueString> names;

  [[nodiscard]] auto to_json() const -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_array()};
    result.push_back(sourcemeta::core::to_json(this->discriminators));
    result.push_back(sourcemeta::core::to_json(this->children));
    result.push_back(sourcemeta::core::to_json(this->names));
    result.push_back(sourcemeta::core::to_json(this->sizes));
    result.push_back(sourcemeta::core::to_json(this->lengths));
    result.push_back(
        sourcemeta::core::JSON{static_cast<std::int64_t>(this->discriminator)});
    result.push_back(sourcemeta::core::JSON{this->exact});
    return result;
  }

  static auto from_json(const sourcemeta::core::JSON &value)
      -> std::optional<ValueNamedIndexes> {
    if (!value.is_array() || value.size() != 7) {
      return std::nullopt;
    }

    auto discriminators{
        sourcemeta::core::from_json<std::vector<ValueUnsignedInteger>>(
            value.at(0))};
    auto children{
        sourcemeta::core::from_json<std::vector<ValueUnsignedInteger>>(
            value.at(1))};
    auto names{
        sourcemeta::core::from_json<std::vector<ValueString>>(value.at(2))};
    auto sizes{
        sourcemeta::core::from_json<std::vector<ValueIndexPair>>(value.at(3))};
    auto lengths{
        sourcemeta::core::from_json<ValueUnsignedInteger>(value.at(4))};
    if (!discriminators.has_value() || !children.has_value() ||
        !names.has_value() || !sizes.has_value() || !lengths.has_value() ||
        !value.at(5).is_integer() || !value.at(6).is_boolean()) {
      return std::nullopt;
    }

    const auto kind{value.at(5).to_integer()};
    if (kind < 0 ||
        kind > static_cast<std::int64_t>(ValueNamedDiscriminator::Folded)) {
      return std::nullopt;
    }

    const auto entries{discriminators.value().size()};
    if (children.value().size() != entries || names.value().size() != entries) {
      return std::nullopt;
    }

    return ValueNamedIndexes{
        .lengths = lengths.value(),
        .discriminator = static_cast<ValueNamedDiscriminator>(kind),
        .exact = value.at(6).to_boolean(),
        .sizes = std::move(sizes).value(),
        .discriminators = std::move(discriminators).value(),
        .children = std::move(children).value(),
        .names = std::move(names).value()};
  }
};

/// @ingroup evaluator
/// Represents a compiler step types properties value
using ValueTypedProperties = std::pair<ValueType, ValueStringSet>;

/// @ingroup evaluator
/// Represents a compiler step types property hashes value
using ValueStringHashes =
    std::pair<std::vector<std::pair<ValueStringSet::hash_type, ValueString>>,
              std::vector<ValueIndexPair>>;

/// @ingroup evaluator
/// Represents a compiler step types property hashes value
using ValueTypedHashes = std::pair<ValueType, ValueStringHashes>;

/// @ingroup evaluator
/// Represents integer bounds with minimum and maximum
using ValueIntegerBounds = std::pair<std::int64_t, std::int64_t>;

/// @ingroup evaluator
/// Represents integer bounds combined with array size range
using ValueIntegerBoundsWithSize = std::pair<ValueIntegerBounds, ValueRange>;

/// @ingroup evaluator
/// Represents a set of types combined with an array size range
using ValueTypesWithSize = std::pair<ValueTypes, ValueRange>;

/// @ingroup evaluator
/// Represents a list of object property entries: (name, hash, required)
using ValueObjectProperties = std::vector<
    std::tuple<ValueString, sourcemeta::core::JSON::Object::hash_type, bool>>;

/// @ingroup evaluator
/// Represents a compiler step number logical type
enum class ValueNumberType : std::uint8_t { Float, Double };

/// @ingroup evaluator
using Value =
    std::variant<ValueNone, ValueJSON, ValueSet, ValueString, ValueProperty,
                 ValueStrings, ValueStringSet, ValueTypes, ValueType,
                 ValueRegex, ValueUnsignedInteger, ValueRange, ValueBoolean,
                 ValueNamedIndexes, ValueStringType, ValueStringMap,
                 ValuePropertyFilter, ValueIndexPair, ValuePointer,
                 ValueTypedProperties, ValueStringHashes, ValueTypedHashes,
                 ValueIntegerBounds, ValueIntegerBoundsWithSize,
                 ValueObjectProperties, ValueNumberType, ValueTypesWithSize>;

} // namespace sourcemeta::blaze

#endif
