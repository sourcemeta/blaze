#ifndef SOURCEMETA_BLAZE_COMPILER_POSTPROCESS_H
#define SOURCEMETA_BLAZE_COMPILER_POSTPROCESS_H

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <vector> // std::vector

namespace sourcemeta::blaze {

inline auto is_noop_without_children(const InstructionIndex type) noexcept
    -> bool {
  switch (type) {
    case InstructionIndex::LogicalAnd:
    case InstructionIndex::LogicalCondition:
    case InstructionIndex::LogicalWhenType:
    case InstructionIndex::LogicalWhenDefines:
    case InstructionIndex::LogicalWhenArraySizeGreater:
    case InstructionIndex::LoopPropertiesMatch:
    case InstructionIndex::LoopProperties:
    case InstructionIndex::LoopPropertiesEvaluate:
    case InstructionIndex::LoopPropertiesRegex:
    case InstructionIndex::LoopPropertiesStartsWith:
    case InstructionIndex::LoopPropertiesExcept:
    case InstructionIndex::LoopKeys:
    case InstructionIndex::LoopItems:
    case InstructionIndex::LoopItemsFrom:
    case InstructionIndex::LoopItemsUnevaluated:
    case InstructionIndex::LoopContains:
    case InstructionIndex::ControlGroupWhenDefines:
    case InstructionIndex::ControlGroupWhenDefinesDirect:
    case InstructionIndex::ControlGroupWhenType:
      return true;
    default:
      return false;
  }
}

inline auto postprocess(std::vector<Instructions> &targets, const Mode mode)
    -> void {
  bool changed{true};
  while (changed) {
    changed = false;

    for (auto &target : targets) {
      // Collect all Instructions* in post-order (children before parents)
      std::vector<Instructions *> worklist;
      std::vector<std::pair<Instructions *, std::size_t>> stack;
      stack.emplace_back(&target, 0);

      while (!stack.empty()) {
        // Copy values to avoid reference invalidation on emplace_back
        auto current{stack.back().first};
        auto index{stack.back().second};
        stack.pop_back();

        // Find next child with non-empty children
        while (index < current->size() && (*current)[index].children.empty()) {
          ++index;
        }

        if (index < current->size()) {
          // Re-push current with updated index to continue after child
          stack.emplace_back(current, index + 1);
          // Push child for immediate processing
          stack.emplace_back(&(*current)[index].children, 0);
        } else {
          // All children visited, add to worklist
          worklist.push_back(current);
        }
      }

      // Process in post-order (children already before parents in worklist)
      for (auto *current : worklist) {
        Instructions result;
        result.reserve(current->size());

        for (auto &instruction : *current) {
          // Remove ControlJump to empty targets (fast validation only)
          if (mode == Mode::FastValidation &&
              instruction.type == InstructionIndex::ControlJump) {
            const auto target_index{
                std::get<ValueUnsignedInteger>(instruction.value)};
            if (targets[target_index].empty()) {
              changed = true;
              continue;
            }
          }

          // Remove instructions that are no-ops with empty children
          if (mode == Mode::FastValidation &&
              is_noop_without_children(instruction.type) &&
              instruction.children.empty()) {
            changed = true;
            continue;
          }

          result.push_back(std::move(instruction));
        }

        *current = std::move(result);
      }
    }
  }
}

} // namespace sourcemeta::blaze

#endif
