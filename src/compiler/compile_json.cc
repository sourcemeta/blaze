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
  return std::visit([](const auto &variant) {
    return sourcemeta::core::to_json(variant);
  }, instruction.value);
}

} // namespace sourcemeta::blaze
