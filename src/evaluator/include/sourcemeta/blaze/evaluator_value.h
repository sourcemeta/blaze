#ifndef SOURCEMETA_BLAZE_EVALUATOR_VALUE_H
#define SOURCEMETA_BLAZE_EVALUATOR_VALUE_H

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonpointer.h>
#include <sourcemeta/jsontoolkit/regex.h>
#include <sourcemeta/jsontoolkit/uri.h>

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
struct ValueNone {};

/// @ingroup evaluator
/// Represents a compiler step JSON value
using ValueJSON = sourcemeta::jsontoolkit::JSON;

/// @ingroup evaluator
/// Represents a set of JSON values
using ValueSet = std::unordered_set<sourcemeta::jsontoolkit::JSON,
                                    sourcemeta::jsontoolkit::Hash>;

/// @ingroup evaluator
/// Represents a compiler step string value
using ValueString = sourcemeta::jsontoolkit::JSON::String;

/// @ingroup evaluator
/// Represents a compiler step object property value
using ValueProperty =
    std::pair<ValueString,
              sourcemeta::jsontoolkit::JSON::Object::Container::hash_type>;

/// @ingroup evaluator
/// Represents a compiler step string values
using ValueStrings = std::vector<ValueString>;

/// @ingroup evaluator
/// Represents a compiler step string set of values
using ValueStringSet = StringSet;

/// @ingroup evaluator
/// Represents a compiler step JSON types value
using ValueTypes = std::vector<sourcemeta::jsontoolkit::JSON::Type>;

/// @ingroup evaluator
/// Represents a compiler step JSON type value
using ValueType = sourcemeta::jsontoolkit::JSON::Type;

/// @ingroup evaluator
/// Represents a compiler step ECMA regular expression value. We store both the
/// original string and the regular expression as standard regular expressions
/// do not keep a copy of their original value (which we need for serialization
/// purposes)
using ValueRegex = std::pair<sourcemeta::jsontoolkit::Regex, std::string>;

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
using ValueNamedIndexes =
    sourcemeta::jsontoolkit::FlatMap<ValueString, ValueUnsignedInteger,
                                     sourcemeta::jsontoolkit::Hash>;

/// @ingroup evaluator
/// Represents a compiler step string logical type
enum class ValueStringType : std::uint8_t { URI };

/// @ingroup evaluator
/// Represents an compiler step that maps strings to strings
using ValueStringMap =
    sourcemeta::jsontoolkit::FlatMap<ValueString, ValueStrings,
                                     sourcemeta::jsontoolkit::Hash>;

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
using ValuePointer = sourcemeta::jsontoolkit::Pointer;

/// @ingroup evaluator
/// Represents a compiler step types properties value
using ValueTypedProperties = std::pair<ValueType, ValueStringSet>;

/// @ingroup evaluator
enum class ValueIndex : std::uint8_t {
  None = 0,
  JSON,
  Set,
  String,
  Property,
  Strings,
  StringSet,
  Types,
  Type,
  Regex,
  UnsignedInteger,
  Range,
  Boolean,
  NamedIndexes,
  StringType,
  StringMap,
  PropertyFilter,
  IndexPair,
  Pointer,
  TypedProperties
};

/// @ingroup evaluator
struct Value {
  ValueIndex kind;
  union {
    ValueJSON json;
    ValueSet set;
    ValueString string;
    ValueProperty property;
    ValueStrings strings;
    ValueStringSet string_set;
    ValueTypes types;
    ValueType type;
    ValueRegex regex;
    ValueUnsignedInteger unsigned_integer;
    ValueRange range;
    ValueBoolean boolean;
    ValueNamedIndexes named_indexes;
    ValueStringType string_type;
    ValueStringMap string_map;
    ValuePropertyFilter property_filter;
    ValueIndexPair index_pair;
    ValuePointer pointer;
    ValueTypedProperties typed_properties;
  };

  Value(const ValueNone &) : kind{ValueIndex::None} {}

#define VALUE_CONSTRUCTOR(type, enum_name, name)                               \
  Value(type &&value) : kind{ValueIndex::enum_name} {                          \
    new (&this->name) type{std::move(value)};                                  \
  }

#define VALUE_CONSTRUCTOR_PLAIN(type, enum_name, name)                         \
  Value(type &&value) : kind{ValueIndex::enum_name} {                          \
    this->name = std::move(value);                                             \
  }

  VALUE_CONSTRUCTOR(ValueJSON, JSON, json)
  VALUE_CONSTRUCTOR(ValueSet, Set, set)
  VALUE_CONSTRUCTOR(ValueString, String, string)
  VALUE_CONSTRUCTOR(ValueProperty, Property, property)
  VALUE_CONSTRUCTOR(ValueStrings, Strings, strings)
  VALUE_CONSTRUCTOR(ValueStringSet, StringSet, string_set)
  VALUE_CONSTRUCTOR(ValueTypes, Types, types)
  VALUE_CONSTRUCTOR_PLAIN(ValueType, Type, type)
  VALUE_CONSTRUCTOR(ValueRegex, Regex, regex)
  VALUE_CONSTRUCTOR_PLAIN(ValueUnsignedInteger, UnsignedInteger,
                          unsigned_integer)
  VALUE_CONSTRUCTOR_PLAIN(ValueRange, Range, range)
  VALUE_CONSTRUCTOR_PLAIN(ValueBoolean, Boolean, boolean)
  VALUE_CONSTRUCTOR(ValueNamedIndexes, NamedIndexes, named_indexes)
  VALUE_CONSTRUCTOR_PLAIN(ValueStringType, StringType, string_type)
  VALUE_CONSTRUCTOR(ValueStringMap, StringMap, string_map)
  VALUE_CONSTRUCTOR(ValuePropertyFilter, PropertyFilter, property_filter)
  VALUE_CONSTRUCTOR(ValueIndexPair, IndexPair, index_pair)
  VALUE_CONSTRUCTOR(ValuePointer, Pointer, pointer)
  VALUE_CONSTRUCTOR(ValueTypedProperties, TypedProperties, typed_properties)

#undef VALUE_CONSTRUCTOR
#undef VALUE_CONSTRUCTOR_PLAIN

  // TODO: Move almost all of this to a .cc file?

  Value(const Value &other) : kind{other.kind} {
    switch (this->kind) {
      case ValueIndex::JSON:
        new (&this->json) ValueJSON{other.json};
        break;
      case ValueIndex::Set:
        new (&this->set) ValueSet{other.set};
        break;
      case ValueIndex::String:
        new (&this->string) ValueString{other.string};
        break;
      case ValueIndex::Property:
        new (&this->property) ValueProperty{other.property};
        break;
      case ValueIndex::Strings:
        new (&this->strings) ValueStrings{other.strings};
        break;
      case ValueIndex::StringSet:
        new (&this->string_set) ValueStringSet{other.string_set};
        break;
      case ValueIndex::Types:
        new (&this->types) ValueTypes{other.types};
        break;
      case ValueIndex::Type:
        this->type = other.type;
        break;
      case ValueIndex::Regex:
        new (&this->regex) ValueRegex{other.regex};
        break;
      case ValueIndex::UnsignedInteger:
        this->unsigned_integer = other.unsigned_integer;
        break;
      case ValueIndex::Range:
        this->range = other.range;
        break;
      case ValueIndex::Boolean:
        this->boolean = other.boolean;
        break;
      case ValueIndex::NamedIndexes:
        new (&this->named_indexes) ValueNamedIndexes{other.named_indexes};
        break;
      case ValueIndex::StringType:
        this->string_type = other.string_type;
        break;
      case ValueIndex::StringMap:
        new (&this->string_map) ValueStringMap{other.string_map};
        break;
      case ValueIndex::PropertyFilter:
        new (&this->property_filter) ValuePropertyFilter{other.property_filter};
        break;
      case ValueIndex::IndexPair:
        new (&this->index_pair) ValueIndexPair{other.index_pair};
        break;
      case ValueIndex::Pointer:
        new (&this->pointer) ValuePointer{other.pointer};
        break;
      case ValueIndex::TypedProperties:
        new (&this->typed_properties)
            ValueTypedProperties{other.typed_properties};
        break;
      default:
        break;
    }
  }

  ~Value() {
    switch (this->kind) {
      case ValueIndex::JSON:
        this->json.~JSON();
        break;
      case ValueIndex::Set:
        this->set.~unordered_set();
        break;
      case ValueIndex::String:
        this->string.~basic_string();
        break;
      case ValueIndex::Property:
        this->property.~pair();
        break;
      case ValueIndex::Strings:
        this->strings.~vector();
        break;
      case ValueIndex::StringSet:
        this->string_set.~StringSet();
        break;
      case ValueIndex::Types:
        this->types.~vector();
        break;
      case ValueIndex::Regex:
        this->regex.~pair();
        break;
      case ValueIndex::NamedIndexes:
        this->named_indexes.~FlatMap();
        break;
      case ValueIndex::StringMap:
        this->string_map.~FlatMap();
        break;
      case ValueIndex::PropertyFilter:
        this->property_filter.~tuple();
        break;
      case ValueIndex::Pointer:
        this->pointer.~GenericPointer();
        break;
      case ValueIndex::TypedProperties:
        this->typed_properties.~pair();
        break;
      default:
        break;
    }
  }
};

} // namespace sourcemeta::blaze

#endif
