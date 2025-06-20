#include <sourcemeta/blaze/evaluator_instruction.h>

#include <type_traits> // std::underlying_type_t

namespace sourcemeta::blaze {

auto Instruction::name() const -> std::string_view {
  return InstructionNames[static_cast<std::underlying_type_t<InstructionIndex>>(
      this->type)];
}

} // namespace sourcemeta::blaze
