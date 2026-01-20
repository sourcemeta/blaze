#ifndef SOURCEMETA_BLAZE_COMPILER_POSTPROCESS_H
#define SOURCEMETA_BLAZE_COMPILER_POSTPROCESS_H

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <cstddef>       // std::size_t
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace sourcemeta::blaze {

struct TargetStatistics {
  std::size_t count;
  // Maps jump target index -> count of jumps to that target
  std::unordered_map<std::size_t, std::size_t> jump_targets;
  bool requires_empty_instance_location;
};

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

inline auto collect_statistics(const Instructions &instructions,
                               TargetStatistics &statistics) -> void {
  for (const auto &instruction : instructions) {
    statistics.count += 1;

    if (instruction.type == InstructionIndex::ControlJump) {
      statistics
          .jump_targets[std::get<ValueUnsignedInteger>(instruction.value)]++;
    }

    if (instruction.type == InstructionIndex::ControlGroupWhenDefinesDirect ||
        instruction.type == InstructionIndex::ControlGroupWhenType) {
      statistics.requires_empty_instance_location = true;
    }

    collect_statistics(instruction.children, statistics);
  }
}

// Transforms a single instruction, pushing results to the output vector
// Returns true if a transformation was applied (instruction removed or inlined)
inline auto
transform_instruction(Instruction &instruction, Instructions &output,
                      const std::vector<Instructions> &targets,
                      const std::vector<TargetStatistics> &statistics,
                      TargetStatistics &current_stats, const Tweaks &tweaks,
                      const bool uses_dynamic_scopes) -> bool {
  // Handle ControlJump: remove if empty, inline if small
  if (instruction.type == InstructionIndex::ControlJump) {
    const auto jump_target_index{
        std::get<ValueUnsignedInteger>(instruction.value)};
    const auto &jump_target_stats{statistics[jump_target_index]};

    // Remove jump to empty target
    if (jump_target_stats.count == 0) {
      current_stats.jump_targets[jump_target_index]--;
      return true;
    }

    // Inline small targets that:
    // - Don't jump back to themselves (cycles)
    // - Schema doesn't use dynamic scopes (need runtime resolution)
    // - Respect instance location constraints
    const auto jump_target_self_loop{
        jump_target_stats.jump_targets.find(jump_target_index)};
    if (jump_target_stats.count < tweaks.target_inline_threshold &&
        (jump_target_self_loop == jump_target_stats.jump_targets.end() ||
         jump_target_self_loop->second == 0) &&
        !uses_dynamic_scopes &&
        (!jump_target_stats.requires_empty_instance_location ||
         instruction.relative_instance_location.empty())) {
      // Update stats: remove this jump and add the inlined target's jumps
      current_stats.jump_targets[jump_target_index]--;
      for (const auto &[inlined_jump, inlined_count] :
           jump_target_stats.jump_targets) {
        current_stats.jump_targets[inlined_jump] += inlined_count;
      }

      for (auto target_instruction : targets[jump_target_index]) {
        target_instruction.relative_schema_location =
            instruction.relative_schema_location.concat(
                target_instruction.relative_schema_location);
        target_instruction.relative_instance_location =
            instruction.relative_instance_location.concat(
                target_instruction.relative_instance_location);
        output.push_back(std::move(target_instruction));
      }
      return true;
    }
  }

  // Remove instructions that are no-ops with empty children
  if (is_noop_without_children(instruction.type) &&
      instruction.children.empty()) {
    return true;
  }

  output.push_back(std::move(instruction));
  return false;
}

inline auto postprocess(std::vector<Instructions> &targets,
                        const Tweaks &tweaks, const bool uses_dynamic_scopes)
    -> void {
  // Compute statistics for each target upfront
  std::vector<TargetStatistics> statistics;
  statistics.reserve(targets.size());
  for (const auto &target : targets) {
    TargetStatistics entry{.count = 0,
                           .jump_targets = {},
                           .requires_empty_instance_location = false};
    collect_statistics(target, entry);
    statistics.push_back(std::move(entry));
  }

  bool changed{true};
  while (changed) {
    changed = false;

    for (std::size_t current_target_index = 0;
         current_target_index < targets.size(); ++current_target_index) {
      auto &target{targets[current_target_index]};
      auto &current_stats{statistics[current_target_index]};

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
          if (transform_instruction(instruction, result, targets, statistics,
                                    current_stats, tweaks, uses_dynamic_scopes))
            changed = true;
        }

        *current = std::move(result);
      }
    }
  }
}

} // namespace sourcemeta::blaze

#endif
