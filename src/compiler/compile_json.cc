#include <sourcemeta/blaze/compiler.h>

#include <functional>  // std::function
#include <type_traits> // std::underlying_type_t

// TODO: We need a collection of templated helper functions in Core JSON to help
// serialising common values to JSON
//
// Maybe the mechanism can be:
// - If the given class defines a `.to_json()` method, use that
// - If there is a global `to_json(T)` function, use that
// - Else require passing a custom lambda transformer
//
// If so, start adding this convention everywhere, like for `SchemaFrame`
// (implementing and testing for JSON in different files), `Pointer`, etc

namespace {

// TODO: Move to the JSON module in Core, maybe as a JSON constructor?
// Or as an overload to make_array()
template <typename T>
auto to_array(
    typename T::const_iterator begin, typename T::const_iterator end,
    const std::function<sourcemeta::core::JSON(const typename T::value_type &)>
        &callback) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_array()};
  for (auto iterator = begin; iterator != end; ++iterator) {
    // TODO: We should have an `.emplace_back()` method in JSON
    result.push_back(callback(*iterator));
  }

  return result;
}

template <typename T>
auto to_object(
    typename T::const_iterator begin, typename T::const_iterator end,
    const std::function<sourcemeta::core::JSON(const typename T::mapped_type &)>
        &callback) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  for (auto iterator = begin; iterator != end; ++iterator) {
    result.assign(iterator->first, callback(iterator->second));
  }

  return result;
}

template <typename T> auto enum_to_index(const T value) -> auto {
  return static_cast<std::underlying_type_t<T>>(value);
}

template <typename T>
auto optional_to_json(const std::optional<T> &value) -> sourcemeta::core::JSON {
  if (value.has_value()) {
    return sourcemeta::core::JSON{value.value()};
  } else {
    return sourcemeta::core::JSON{nullptr};
  }
}

// TODO: How can we keep this in the hash header that does not yet know about
// JSON?
auto hash_to_json(
    const sourcemeta::core::JSON::Object::Container::hash_type hash)
    -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_array()};
#if defined(__SIZEOF_INT128__)
  result.push_back(
      sourcemeta::core::JSON{static_cast<std::size_t>(hash.a >> 64)});
  result.push_back(sourcemeta::core::JSON{static_cast<std::size_t>(hash.a)});
  result.push_back(
      sourcemeta::core::JSON{static_cast<std::size_t>(hash.b >> 64)});
  result.push_back(sourcemeta::core::JSON{static_cast<std::size_t>(hash.b)});
#else
  result.push_back(sourcemeta::core::JSON{static_cast<std::size_t>(hash.a)});
  result.push_back(sourcemeta::core::JSON{static_cast<std::size_t>(hash.b)});
  result.push_back(sourcemeta::core::JSON{static_cast<std::size_t>(hash.c)});
  result.push_back(sourcemeta::core::JSON{static_cast<std::size_t>(hash.d)});
#endif
  return result;
}

auto identity(const sourcemeta::core::JSON &value) -> sourcemeta::core::JSON {
  return value;
}

struct ValueVisitorToJSON {
  auto operator()(const sourcemeta::blaze::ValueNone &) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    // TODO: Can we automatically derive the type from the class name?
    result.assign("type", sourcemeta::core::JSON{"none"});
    result.assign("value", sourcemeta::core::JSON{nullptr});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueJSON &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"json"});
    result.assign("value", value);
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueSet &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"set"});
    result.assign("value", to_array<sourcemeta::blaze::ValueSet>(
                               value.cbegin(), value.cend(), identity));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueString &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"string"});
    result.assign("value", sourcemeta::core::JSON{value});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueProperty &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"property"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(sourcemeta::core::JSON{value.first});
    tuple.push_back(hash_to_json(value.second));
    result.assign("value", std::move(tuple));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueStrings &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"strings"});
    result.assign("value", to_array<sourcemeta::blaze::ValueStrings>(
                               value.cbegin(), value.cend(),
                               [](const auto &item) -> sourcemeta::core::JSON {
                                 return sourcemeta::core::JSON{item};
                               }));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueStringSet &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"string-set"});
    result.assign("value", to_array<sourcemeta::blaze::ValueStringSet>(
                               value.begin(), value.end(),
                               [](const auto &item) -> sourcemeta::core::JSON {
                                 return sourcemeta::core::JSON{item.first};
                               }));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueTypes &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"types"});
    result.assign("value",
                  to_array<sourcemeta::blaze::ValueTypes>(
                      value.begin(), value.end(),
                      [](const auto type) -> sourcemeta::core::JSON {
                        return sourcemeta::core::JSON{enum_to_index(type)};
                      }));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueType value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"type"});
    result.assign("value", sourcemeta::core::JSON{enum_to_index(value)});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueRegex &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"regex"});
    result.assign("value", sourcemeta::core::JSON{value.second});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueUnsignedInteger value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"unsigned-integer"});
    result.assign("value", sourcemeta::core::JSON{value});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueRange &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"range"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(sourcemeta::core::JSON{std::get<0>(value)});
    tuple.push_back(optional_to_json(std::get<1>(value)));
    tuple.push_back(sourcemeta::core::JSON{std::get<2>(value)});
    result.assign("value", std::move(tuple));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueBoolean value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"boolean"});
    result.assign("value", sourcemeta::core::JSON{value});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueNamedIndexes &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"named-indexes"});
    result.assign("value", to_object<sourcemeta::blaze::ValueNamedIndexes>(
                               value.cbegin(), value.cend(),
                               [](const auto &entry) -> sourcemeta::core::JSON {
                                 return sourcemeta::core::JSON{entry};
                               }));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueStringType value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"string-type"});
    result.assign("value", sourcemeta::core::JSON{enum_to_index(value)});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueStringMap &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"string-map"});
    result.assign("value",
                  to_object<sourcemeta::blaze::ValueStringMap>(
                      value.cbegin(), value.cend(),
                      [](const auto &entry) -> sourcemeta::core::JSON {
                        return to_array<sourcemeta::blaze::ValueStrings>(
                            entry.begin(), entry.end(),
                            [](const auto &subvalue) -> sourcemeta::core::JSON {
                              return sourcemeta::core::JSON{subvalue};
                            });
                      }));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValuePropertyFilter &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"property-filter"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(this->operator()(std::get<0>(value)));
    tuple.push_back(this->operator()(std::get<1>(value)));
    tuple.push_back(to_array<std::vector<sourcemeta::blaze::ValueRegex>>(
        std::get<2>(value).cbegin(), std::get<2>(value).cend(),
        [](const auto &subvalue) -> sourcemeta::core::JSON {
          return sourcemeta::core::JSON{subvalue.second};
        }));
    result.assign("value", std::move(tuple));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueIndexPair &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"index-pair"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(sourcemeta::core::JSON{value.first});
    tuple.push_back(sourcemeta::core::JSON{value.second});
    result.assign("value", std::move(tuple));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValuePointer &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"pointer"});
    result.assign("value",
                  sourcemeta::core::JSON{sourcemeta::core::to_string(value)});
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueTypedProperties &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"typed-properties"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(this->operator()(std::get<0>(value)));
    tuple.push_back(this->operator()(std::get<1>(value)));
    result.assign("value", std::move(tuple));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueStringHashes &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"string-hashes"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(
        to_array<std::vector<sourcemeta::blaze::ValueStringSet::hash_type>>(
            value.first.cend(), value.first.cend(), hash_to_json));
    tuple.push_back(to_array<std::vector<sourcemeta::blaze::ValueIndexPair>>(
        value.second.cend(), value.second.cend(), *this));
    result.assign("value", std::move(tuple));
    return result;
  }

  auto operator()(const sourcemeta::blaze::ValueTypedHashes &value) const
      -> sourcemeta::core::JSON {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("type", sourcemeta::core::JSON{"typed-hashes"});
    auto tuple{sourcemeta::core::JSON::make_array()};
    tuple.push_back(this->operator()(value.first));
    tuple.push_back(this->operator()(value.second));
    result.assign("value", std::move(tuple));
    return result;
  }
};

} // namespace

namespace sourcemeta::blaze {

auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  // We use single characters to save space, as this serialised format
  // is not meant to be human-readable anyway
  result.assign("t", sourcemeta::core::JSON{enum_to_index(instruction.type)});
  result.assign("s", sourcemeta::core::JSON{sourcemeta::core::to_string(
                         instruction.relative_schema_location)});
  result.assign("i", sourcemeta::core::JSON{sourcemeta::core::to_string(
                         instruction.relative_instance_location)});
  result.assign("k", sourcemeta::core::JSON{instruction.keyword_location});
  result.assign("r", sourcemeta::core::JSON{instruction.schema_resource});

  result.assign("v", std::visit(ValueVisitorToJSON{}, instruction.value));
  assert(result.at("v").is_object());
  assert(result.at("v").size() == 2);
  assert(result.at("v").defines("type"));
  assert(result.at("v").defines("value"));
  assert(result.at("v").at("type").is_string());

  auto children_json{sourcemeta::core::JSON::make_array()};
  result.assign(
      "c",
      to_array<sourcemeta::blaze::Instructions>(
          instruction.children.cbegin(), instruction.children.cend(),
          [](const sourcemeta::blaze::Instruction &subinstruction)
              -> sourcemeta::core::JSON { return to_json(subinstruction); }));
  return result;
}

auto to_json(const Template &schema_template) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("dynamic", sourcemeta::core::JSON{schema_template.dynamic});
  result.assign("track", sourcemeta::core::JSON{schema_template.track});
  result.assign(
      "instructions",
      to_array<sourcemeta::blaze::Instructions>(
          schema_template.instructions.cbegin(),
          schema_template.instructions.cend(),
          [](const sourcemeta::blaze::Instruction &instruction)
              -> sourcemeta::core::JSON { return to_json(instruction); }));
  return result;
}

} // namespace sourcemeta::blaze
