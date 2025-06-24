#include <sourcemeta/blaze/compiler.h>

#include <variant> // std::visit

namespace sourcemeta::blaze {

auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON {
  return std::visit([](const auto &variant) {
    return sourcemeta::core::to_json(variant);
  }, instruction.value);
}

} // namespace sourcemeta::blaze
