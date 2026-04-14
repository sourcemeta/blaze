#ifndef SOURCEMETA_BLAZE_EVALUATOR_VALUE_H
#define SOURCEMETA_BLAZE_EVALUATOR_VALUE_H

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/regex.h>

#include <sourcemeta/blaze/evaluator_string_set.h>

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
using ValueStringSet = StringSet;

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
/// Represents a compiler step string to index map
using ValueNamedIndexes = sourcemeta::core::JSONObject<
    ValueString, ValueUnsignedInteger,
    sourcemeta::core::PropertyHashJSON<ValueString>>;

/// @ingroup evaluator
/// Represents a compiler step string logical type
enum class ValueStringType : std::uint8_t { URI };

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
struct ValueIntegerBounds {
  using first_type = std::int64_t;
  using second_type = std::int64_t;
  first_type first;
  second_type second;

  // TODO: Elevate into the Core project
  [[nodiscard]] auto to_json() const -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_array()};
    result.push_back(sourcemeta::core::JSON{this->first});
    result.push_back(sourcemeta::core::JSON{this->second});
    return result;
  }

  // TODO: Elevate into the Core project
  static auto from_json(const sourcemeta::core::JSON &value)
      -> std::optional<ValueIntegerBounds> {
    if (!value.is_array() || value.array_size() != 2 ||
        !value.at(0).is_integer() || !value.at(1).is_integer()) {
      return std::nullopt;
    }

    return ValueIntegerBounds{.first = value.at(0).to_integer(),
                              .second = value.at(1).to_integer()};
  }
};

/// @ingroup evaluator
/// Represents integer bounds combined with array size range
struct ValueIntegerBoundsWithSize {
  using first_type = ValueIntegerBounds;
  using second_type = ValueRange;
  first_type first;
  second_type second;

  // TODO: Elevate into the Core project
  [[nodiscard]] auto to_json() const -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_array()};
    result.push_back(this->first.to_json());
    auto range{sourcemeta::core::JSON::make_array()};
    range.push_back(sourcemeta::core::JSON{
        static_cast<std::int64_t>(std::get<0>(this->second))});
    if (std::get<1>(this->second).has_value()) {
      range.push_back(sourcemeta::core::JSON{
          static_cast<std::int64_t>(std::get<1>(this->second).value())});
    } else {
      range.push_back(sourcemeta::core::JSON{nullptr});
    }
    range.push_back(sourcemeta::core::JSON{std::get<2>(this->second)});
    result.push_back(std::move(range));
    return result;
  }

  // TODO: Elevate into the Core project
  static auto from_json(const sourcemeta::core::JSON &value)
      -> std::optional<ValueIntegerBoundsWithSize> {
    if (!value.is_array() || value.array_size() != 2) {
      return std::nullopt;
    }

    auto bounds{ValueIntegerBounds::from_json(value.at(0))};
    if (!bounds.has_value()) {
      return std::nullopt;
    }

    const auto &range_json{value.at(1)};
    if (!range_json.is_array() || range_json.array_size() != 3 ||
        !range_json.at(0).is_integer() || !range_json.at(2).is_boolean()) {
      return std::nullopt;
    }

    return ValueIntegerBoundsWithSize{
        .first = std::move(bounds).value(),
        .second = ValueRange{
            static_cast<std::size_t>(range_json.at(0).to_integer()),
            range_json.at(1).is_null()
                ? std::nullopt
                : std::optional<std::size_t>{static_cast<std::size_t>(
                      range_json.at(1).to_integer())},
            range_json.at(2).to_boolean()}};
  }
};

/// @ingroup evaluator
using Value =
    std::variant<ValueNone, ValueJSON, ValueSet, ValueString, ValueProperty,
                 ValueStrings, ValueStringSet, ValueTypes, ValueType,
                 ValueRegex, ValueUnsignedInteger, ValueRange, ValueBoolean,
                 ValueNamedIndexes, ValueStringType, ValueStringMap,
                 ValuePropertyFilter, ValueIndexPair, ValuePointer,
                 ValueTypedProperties, ValueStringHashes, ValueTypedHashes,
                 ValueIntegerBounds, ValueIntegerBoundsWithSize>;

} // namespace sourcemeta::blaze

#endif
