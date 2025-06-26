#include <sourcemeta/blaze/compiler.h>

#include <cassert> // assert
#include <variant> // std::visit

namespace {
auto value_from_json(const sourcemeta::core::JSON &wrapper)
    -> sourcemeta::blaze::Value {
  assert(wrapper.is_object());
  assert(wrapper.defines("t"));
  assert(wrapper.defines("v"));
  const auto &type{wrapper.at("t")};
  const auto &value{wrapper.at("v")};
  assert(type.is_integer() && type.is_positive());
  using namespace sourcemeta::blaze;
  switch (type.to_integer()) {
      // clang-format off
    case 0:  return sourcemeta::core::from_json<ValueNone>(value);
    case 1:  return sourcemeta::core::from_json<ValueJSON>(value);
    case 2:  return sourcemeta::core::from_json<ValueSet>(value);
    case 3:  return sourcemeta::core::from_json<ValueString>(value);
    case 4:  return sourcemeta::core::from_json<ValueProperty>(value);
    case 5:  return sourcemeta::core::from_json<ValueStrings>(value);
    case 6:  return sourcemeta::core::from_json<ValueStringSet>(value);
    case 7:  return sourcemeta::core::from_json<ValueTypes>(value);
    case 8:  return sourcemeta::core::from_json<ValueType>(value);
    case 9:  return sourcemeta::core::from_json<ValueRegex>(value);
    case 10: return sourcemeta::core::from_json<ValueUnsignedInteger>(value);
    case 11: return sourcemeta::core::from_json<ValueRange>(value);
    case 12: return sourcemeta::core::from_json<ValueBoolean>(value);
    case 13: return sourcemeta::core::from_json<ValueNamedIndexes>(value);
    case 14: return sourcemeta::core::from_json<ValueStringType>(value);
    case 15: return sourcemeta::core::from_json<ValueStringMap>(value);
    case 16: return sourcemeta::core::from_json<ValuePropertyFilter>(value);
    case 17: return sourcemeta::core::from_json<ValueIndexPair>(value);
    case 18: return sourcemeta::core::from_json<ValuePointer>(value);
    case 19: return sourcemeta::core::from_json<ValueTypedProperties>(value);
    case 20: return sourcemeta::core::from_json<ValueStringHashes>(value);
    case 21: return sourcemeta::core::from_json<ValueTypedHashes>(value);
    // clang-format on
    default:
      assert(false);
      return ValueNone{};
  }
}

auto instructions_from_json(const sourcemeta::core::JSON &instructions)
    -> sourcemeta::blaze::Instructions {
  assert(instructions.is_array());
  sourcemeta::blaze::Instructions result;
  result.reserve(instructions.size());
  for (const auto &instruction : instructions.as_array()) {
    assert(instruction.is_object());
    assert(instruction.defines("t"));
    assert(instruction.defines("s"));
    assert(instruction.defines("i"));
    assert(instruction.defines("k"));
    assert(instruction.defines("r"));
    assert(instruction.defines("v"));
    assert(instruction.defines("c"));
    const auto &type{instruction.at("t")};
    const auto &relative_schema_location{instruction.at("s")};
    const auto &relative_instance_location{instruction.at("i")};
    const auto &keyword_location{instruction.at("k")};
    const auto &schema_resource{instruction.at("r")};
    const auto &value{instruction.at("v")};
    const auto &children{instruction.at("c")};
    assert(type.is_integer() && type.is_positive());
    assert(relative_schema_location.is_string());
    assert(relative_instance_location.is_string());
    assert(keyword_location.is_string());
    assert(schema_resource.is_integer() && schema_resource.is_positive());
    assert(value.is_object());
    assert(children.is_array());

    // TODO: Maybe we should emplace here?
    result.push_back(
        {sourcemeta::core::from_json<sourcemeta::blaze::InstructionIndex>(type),
         sourcemeta::core::from_json<sourcemeta::core::Pointer>(
             relative_schema_location),
         sourcemeta::core::from_json<sourcemeta::core::Pointer>(
             relative_instance_location),
         sourcemeta::core::from_json<std::string>(keyword_location),
         sourcemeta::core::from_json<std::size_t>(schema_resource),
         value_from_json(value), instructions_from_json(children)});
  }

  return result;
}

auto to_json(const sourcemeta::blaze::Instruction &instruction)
    -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  // We use single characters to save space, as this serialised format
  // is not meant to be human-readable anyway
  result.assign("t", sourcemeta::core::to_json(instruction.type));
  result.assign(
      "s", sourcemeta::core::to_json(instruction.relative_schema_location));
  result.assign(
      "i", sourcemeta::core::to_json(instruction.relative_instance_location));
  result.assign("k", sourcemeta::core::to_json(instruction.keyword_location));
  result.assign("r", sourcemeta::core::to_json(instruction.schema_resource));

  auto value{sourcemeta::core::JSON::make_object()};
  value.assign("t", sourcemeta::core::to_json(instruction.value.index()));
  value.assign("v", std::visit(
                        [](const auto &variant) {
                          return sourcemeta::core::to_json(variant);
                        },
                        instruction.value));
  result.assign("v", std::move(value));

  assert(result.at("v").is_object());
  assert(result.at("v").size() == 2);
  assert(result.at("v").defines("t"));
  assert(result.at("v").defines("v"));
  assert(result.at("v").at("t").is_integer());

  auto children_json{sourcemeta::core::JSON::make_array()};
  result.assign("c", sourcemeta::core::to_json(instruction.children,
                                               [](const auto &subinstruction) {
                                                 return to_json(subinstruction);
                                               }));
  return result;
}
} // namespace

namespace sourcemeta::blaze {

auto to_json(const Template &schema_template) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("dynamic", sourcemeta::core::JSON{schema_template.dynamic});
  result.assign("track", sourcemeta::core::JSON{schema_template.track});
  result.assign("instructions",
                sourcemeta::core::to_json(schema_template.instructions,
                                          [](const auto &instruction) {
                                            return ::to_json(instruction);
                                          }));
  return result;
}

auto from_json(const sourcemeta::core::JSON &json) -> Template {
  assert(json.is_object());
  assert(json.defines("instructions"));
  assert(json.defines("dynamic"));
  assert(json.defines("track"));
  const auto &instructions{json.at("instructions")};
  const auto &dynamic{json.at("dynamic")};
  const auto &track{json.at("track")};
  assert(instructions.is_array());
  assert(dynamic.is_boolean());
  assert(track.is_boolean());
  return {instructions_from_json(instructions), dynamic.to_boolean(),
          track.to_boolean()};
}

} // namespace sourcemeta::blaze
