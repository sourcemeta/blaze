#include <sourcemeta/blaze/compiler.h>

#include <cassert>     // assert
#include <map>         // std::map
#include <string_view> // std::string_view
#include <variant>     // std::visit

namespace {
auto instruction_to_json(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Instructions &all_instructions,
    std::vector<sourcemeta::core::JSON::String> &resources)
    -> sourcemeta::core::JSON {
  // Note that we purposely avoid objects to help consumers avoid potentially
  // expensive hash-map or flat-map lookups when parsing back
  auto result{sourcemeta::core::JSON::make_array()};

  result.push_back(sourcemeta::core::to_json(instruction.type));

  result.push_back(
      sourcemeta::core::to_json(instruction.relative_schema_location));
  result.push_back(
      sourcemeta::core::to_json(instruction.relative_instance_location));

  const auto match{instruction.keyword_location.find('#')};
  if (instruction.schema_resource > 0 && match != std::string::npos) {
    if (resources.size() < instruction.schema_resource) {
      resources.resize(instruction.schema_resource);
    }

    if (resources[instruction.schema_resource - 1].empty()) {
      resources[instruction.schema_resource - 1] =
          instruction.keyword_location.substr(0, match);
    }

    result.push_back(
        sourcemeta::core::JSON{instruction.keyword_location.substr(match)});
  } else {
    result.push_back(sourcemeta::core::to_json(instruction.keyword_location));
  }

  result.push_back(sourcemeta::core::to_json(instruction.schema_resource));

  // Note that we purposely avoid objects to help consumers avoid potentially
  // expensive hash-map or flat-map lookups when parsing back
  auto value{sourcemeta::core::JSON::make_array()};
  const auto value_index{instruction.value.index()};
  value.push_back(sourcemeta::core::to_json(value_index));
  // Don't encode empty values, which tend to happen a lot
  if (value_index != 0) {
    // For instructions whose ValueNamedIndexes were converted from child
    // indices to flat offsets, convert back to child indices for serialization
    if ((instruction.type ==
             sourcemeta::blaze::InstructionIndex::LoopPropertiesMatch ||
         instruction.type ==
             sourcemeta::blaze::InstructionIndex::LoopPropertiesMatchClosed) &&
        instruction.children_count > 0) {
      // Build flat_offset -> child_index reverse mapping
      std::map<std::size_t, std::size_t> flat_to_child;
      std::size_t child_idx{0};
      for (std::size_t offset = instruction.flat_offset;
           offset < instruction.next_sibling_offset;
           offset = all_instructions[offset].next_sibling_offset) {
        flat_to_child[offset] = child_idx++;
      }

      // Create a copy with child indices restored
      auto named_indexes_copy{
          *std::get_if<sourcemeta::blaze::ValueNamedIndexes>(
              &instruction.value)};
      for (const auto &[flat_offset, child_index] : flat_to_child) {
        for (const auto &entry : named_indexes_copy) {
          if (entry.second == flat_offset) {
            named_indexes_copy.emplace(entry.first, child_index);
            break;
          }
        }
      }

      value.push_back(sourcemeta::core::to_json(named_indexes_copy));
    } else {
      value.push_back(std::visit(
          [](const auto &variant) {
            return sourcemeta::core::to_json(variant);
          },
          instruction.value));
    }
  }
  assert(value.is_array());
  assert(!value.empty());
  assert(value.at(0).is_integer());
  result.push_back(std::move(value));

  // Reconstruct tree-shaped children from the flat array
  if (instruction.children_count > 0) {
    auto children_json{sourcemeta::core::JSON::make_array()};
    for (std::size_t index = instruction.flat_offset;
         index < instruction.next_sibling_offset;
         index = all_instructions[index].next_sibling_offset) {
      children_json.push_back(instruction_to_json(all_instructions[index],
                                                  all_instructions, resources));
    }
    result.push_back(std::move(children_json));
  }

  return result;
}
} // namespace

namespace sourcemeta::blaze {

auto to_json(const Template &schema_template) -> sourcemeta::core::JSON {
  // Note that we purposely avoid objects to help consumers avoid potentially
  // expensive hash-map or flat-map lookups when parsing back
  auto result{sourcemeta::core::JSON::make_array()};
  result.push_back(sourcemeta::core::JSON{schema_template.dynamic});
  result.push_back(sourcemeta::core::JSON{schema_template.track});
  std::vector<sourcemeta::core::JSON::String> resources;

  auto targets{sourcemeta::core::JSON::make_array()};
  for (const auto &[offset, count] : schema_template.targets) {
    auto target_json{sourcemeta::core::JSON::make_array()};
    for (std::size_t index = offset; index < offset + count;
         index = schema_template.instructions[index].next_sibling_offset) {
      target_json.push_back(
          instruction_to_json(schema_template.instructions[index],
                              schema_template.instructions, resources));
    }
    targets.push_back(std::move(target_json));
  }

  result.push_back(sourcemeta::core::to_json(resources));
  result.push_back(std::move(targets));

  auto labels{sourcemeta::core::JSON::make_array()};
  for (const auto &[key, value] : schema_template.labels) {
    auto pair{sourcemeta::core::JSON::make_array()};
    pair.push_back(sourcemeta::core::JSON{static_cast<std::int64_t>(key)});
    pair.push_back(sourcemeta::core::JSON{static_cast<std::int64_t>(value)});
    labels.push_back(std::move(pair));
  }
  result.push_back(std::move(labels));

  return result;
}

} // namespace sourcemeta::blaze
