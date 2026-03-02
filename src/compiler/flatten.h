#ifndef SOURCEMETA_BLAZE_COMPILER_FLATTEN_H
#define SOURCEMETA_BLAZE_COMPILER_FLATTEN_H

#include <sourcemeta/blaze/evaluator.h>

#include <cassert> // assert
#include <cstdint> // std::uint32_t
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
      output[parent_index].direct_children_count =
          static_cast<std::uint32_t>(tree_instruction.children.size());
      const auto children_count{
          flatten_instructions(tree_instruction.children, output)};
      output[parent_index].children_count =
          static_cast<std::uint32_t>(children_count);
      total += children_count;
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
