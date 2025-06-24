#include <sourcemeta/blaze/compiler.h>

#include <variant> // std::visit

namespace sourcemeta::core {
template <typename T>
  requires std::is_same_v<T, sourcemeta::blaze::ValueNone>
auto to_json(const T &) -> JSON {
  return JSON{nullptr};
}
template <typename T>
  requires std::is_same_v<T, sourcemeta::blaze::ValueRegex>
auto to_json(const T &value) -> JSON {
  return JSON{value.second};
}
} // namespace sourcemeta::core

namespace sourcemeta::blaze {

auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  // We use single characters to save space, as this serialised format
  // is not meant to be human-readable anyway
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

} // namespace sourcemeta::blaze
