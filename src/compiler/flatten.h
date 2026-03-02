#ifndef SOURCEMETA_BLAZE_COMPILER_FLATTEN_H
#define SOURCEMETA_BLAZE_COMPILER_FLATTEN_H

#include <sourcemeta/blaze/evaluator.h>

#include <cassert> // assert
#include <cstdint> // std::uint32_t
#include <utility> // std::pair
#include <vector>  // std::vector

namespace sourcemeta::blaze {

inline auto flatten_instructions(const TreeInstructions &tree_instructions,
                                 Instructions &output) -> std::size_t {
  std::size_t total{0};
  for (const auto &tree_instruction : tree_instructions) {
    const auto parent_index{output.size()};
    output.push_back(
        {.type = tree_instruction.type,
         .relative_schema_location = tree_instruction.relative_schema_location,
         .relative_instance_location =
             tree_instruction.relative_instance_location,
         .keyword_location = tree_instruction.keyword_location,
         .schema_resource = tree_instruction.schema_resource,
         .value = tree_instruction.value,
         .children_count = 0,
         .direct_children_count = 0,
         .flat_offset = static_cast<std::uint32_t>(parent_index + 1),
         .next_sibling_offset = 0});
    total += 1;

    if (!tree_instruction.children.empty()) {
      const auto direct_count{tree_instruction.children.size()};
      output[parent_index].direct_children_count =
          static_cast<std::uint32_t>(direct_count);
      const auto children_count{
          flatten_instructions(tree_instruction.children, output)};
      output[parent_index].children_count =
          static_cast<std::uint32_t>(children_count);
      total += children_count;

      // For instructions that store child indices in their Value,
      // convert those indices to flat array offsets for O(1) access
      auto &flat_instruction{output[parent_index]};
      switch (flat_instruction.type) {
        case InstructionIndex::LoopPropertiesMatch:
        case InstructionIndex::LoopPropertiesMatchClosed: {
          // Build child_index -> flat_offset table
          std::vector<std::size_t> child_offsets;
          child_offsets.reserve(direct_count);
          auto cursor{parent_index + 1};
          for (std::size_t child = 0; child < direct_count; child++) {
            child_offsets.push_back(cursor);
            cursor = output[cursor].next_sibling_offset;
          }

          auto *named_indexes{
              std::get_if<ValueNamedIndexes>(&flat_instruction.value)};
          assert(named_indexes);
          // Collect updates first (can't modify while iterating)
          std::vector<std::pair<ValueString, std::size_t>> updates;
          updates.reserve(named_indexes->size());
          for (const auto &entry : *named_indexes) {
            assert(entry.second < child_offsets.size());
            updates.emplace_back(entry.first, child_offsets[entry.second]);
          }
          for (const auto &update : updates) {
            named_indexes->emplace(update.first, update.second);
          }
          break;
        }
        default:
          break;
      }
    }

    output[parent_index].next_sibling_offset =
        static_cast<std::uint32_t>(output.size());
  }

  return total;
}

inline auto flatten(const TreeTemplate &tree) -> Template {
  Template result;
  result.dynamic = tree.dynamic;
  result.track = tree.track;
  result.labels = tree.labels;

  result.targets.reserve(tree.targets.size());
  for (const auto &target : tree.targets) {
    const auto offset{result.instructions.size()};
    const auto count{flatten_instructions(target, result.instructions)};
    result.targets.emplace_back(offset, count);
  }

  return result;
}

} // namespace sourcemeta::blaze

#endif
