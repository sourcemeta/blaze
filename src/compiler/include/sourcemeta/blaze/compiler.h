#ifndef SOURCEMETA_BLAZE_COMPILER_COMPILE_H_
#define SOURCEMETA_BLAZE_COMPILER_COMPILE_H_

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/regex.h>

#include <cstdint>     // std::uint8_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector
#include <optional>      // std::optional
#include <tuple>         // std::tuple
#include <unordered_set> // std::unordered_set
#include <utility>       // std::pair

namespace sourcemeta::blaze {

class StringSet {
public:
  StringSet() = default;

  using string_type = sourcemeta::core::JSON::String;
  using hash_type = sourcemeta::core::JSON::Object::Container::hash_type;
  using value_type = std::pair<string_type, hash_type>;
  using underlying_type = std::vector<value_type>;
  using size_type = typename underlying_type::size_type;
  using difference_type = typename underlying_type::difference_type;
  using const_iterator = typename underlying_type::const_iterator;

  inline auto begin() const -> const_iterator { return this->data.begin(); }
  inline auto end() const -> const_iterator { return this->data.end(); }
  inline auto cbegin() const -> const_iterator { return this->data.cbegin(); }
  inline auto cend() const -> const_iterator { return this->data.cend(); }

  auto to_json() const -> sourcemeta::core::JSON {
    return sourcemeta::core::to_json(this->data, [](const auto &item) {
      return sourcemeta::core::to_json(item.first);
    });
  }

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif
  underlying_type data;
#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif
};

/// @ingroup evaluator
/// @brief Represents a compiler step empty value
struct ValueNone {};

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
    std::pair<ValueString,
              sourcemeta::core::JSON::Object::Container::hash_type>;

/// @ingroup evaluator
/// Represents a compiler step string values
using ValueStrings = std::vector<ValueString>;

/// @ingroup evaluator
/// Represents a compiler step string set of values
using ValueStringSet = StringSet;

/// @ingroup evaluator
/// Represents a compiler step JSON types value
using ValueTypes = std::vector<sourcemeta::core::JSON::Type>;

/// @ingroup evaluator
/// Represents a compiler step JSON type value
using ValueType = sourcemeta::core::JSON::Type;

/// @ingroup evaluator
/// Represents a compiler step ECMA regular expression value. We store both the
/// original string and the regular expression as standard regular expressions
/// do not keep a copy of their original value (which we need for serialization
/// purposes)
using ValueRegex = std::pair<sourcemeta::core::Regex<ValueString>, std::string>;

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

// TODO: Don't use FlatMap directly, as it is an internal module of Core
/// @ingroup evaluator
/// Represents a compiler step string to index map
using ValueNamedIndexes =
    sourcemeta::core::FlatMap<ValueString, ValueUnsignedInteger,
                              sourcemeta::core::PropertyHashJSON<ValueString>>;

/// @ingroup evaluator
/// Represents a compiler step string logical type
enum class ValueStringType : std::uint8_t { URI };

// TODO: Don't use FlatMap directly, as it is an internal module of Core
/// @ingroup evaluator
/// Represents an compiler step that maps strings to strings
using ValueStringMap =
    sourcemeta::core::FlatMap<ValueString, ValueStrings,
                              sourcemeta::core::PropertyHashJSON<ValueString>>;

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
using ValueStringHashes = std::pair<std::vector<ValueStringSet::hash_type>,
                                    std::vector<ValueIndexPair>>;

/// @ingroup evaluator
/// Represents a compiler step types property hashes value
using ValueTypedHashes = std::pair<ValueType, ValueStringHashes>;

/// @ingroup evaluator
using Value =
    std::variant<ValueNone, ValueJSON, ValueSet, ValueString, ValueProperty,
                 ValueStrings, ValueStringSet, ValueTypes, ValueType,
                 ValueRegex, ValueUnsignedInteger, ValueRange, ValueBoolean,
                 ValueNamedIndexes, ValueStringType, ValueStringMap,
                 ValuePropertyFilter, ValueIndexPair, ValuePointer,
                 ValueTypedProperties, ValueStringHashes, ValueTypedHashes>;

// Forward declaration for defining a circular structure
#ifndef DOXYGEN
struct Instruction;
#endif

/// @ingroup evaluator
/// Represents a set of schema compilation steps that can be evaluated
using Instructions = std::vector<Instruction>;

/// @ingroup evaluator
/// Represents a single instruction to be evaluated
struct Instruction {
  const sourcemeta::core::Pointer relative_schema_location;
  const sourcemeta::core::Pointer relative_instance_location;
  const std::string keyword_location;
  const std::size_t schema_resource;
  const Value value;
  const Instructions children;
};

auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON;
} // namespace sourcemeta::blaze

#endif
