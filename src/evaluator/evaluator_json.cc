#include <sourcemeta/blaze/evaluator.h>

#include <cassert> // assert
#include <cstdint> // std::uint32_t

namespace {
auto value_from_json(const sourcemeta::core::JSON &wrapper)
    -> std::optional<sourcemeta::blaze::Value> {
  if (!wrapper.is_array() || wrapper.array_size() == 0 ||
      !wrapper.at(0).is_integer()) {
    return std::nullopt;
  } else if (wrapper.array_size() == 1) {
    return sourcemeta::blaze::ValueNone{};
  }

  const auto &value{wrapper.at(1)};

  using namespace sourcemeta::blaze;
  switch (wrapper.at(0).to_integer()) {
      // clang-format off
    case 0:  return ValueNone{};
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

auto instructions_from_json(const sourcemeta::core::JSON &instructions,
                            const sourcemeta::core::JSON &resources)
    -> std::optional<sourcemeta::blaze::TreeInstructions> {
  if (!instructions.is_array()) {
    return std::nullopt;
  }

  sourcemeta::blaze::TreeInstructions result;
  result.reserve(instructions.size());
  for (const auto &instruction : instructions.as_array()) {
    if (!instruction.is_array() || instruction.array_size() < 6) {
      return std::nullopt;
    }

    const auto &type{instruction.at(0)};
    const auto &relative_schema_location{instruction.at(1)};
    const auto &relative_instance_location{instruction.at(2)};
    const auto &keyword_location{instruction.at(3)};
    const auto &schema_resource{instruction.at(4)};
    const auto &value{instruction.at(5)};

    auto type_result{
        sourcemeta::core::from_json<sourcemeta::blaze::InstructionIndex>(type)};
    auto relative_schema_location_result{
        sourcemeta::core::from_json<sourcemeta::core::Pointer>(
            relative_schema_location)};
    auto relative_instance_location_result{
        sourcemeta::core::from_json<sourcemeta::core::Pointer>(
            relative_instance_location)};
    auto keyword_location_result{
        sourcemeta::core::from_json<std::string>(keyword_location)};
    auto schema_resource_result{
        sourcemeta::core::from_json<std::size_t>(schema_resource)};
    auto value_result{value_from_json(value)};

    // Parse children if there
    std::optional<sourcemeta::blaze::TreeInstructions> children_result{
        instruction.array_size() == 7
            ? instructions_from_json(instruction.at(6), resources)
            : sourcemeta::blaze::TreeInstructions{}};

    if (!type_result.has_value() ||
        !relative_schema_location_result.has_value() ||
        !relative_instance_location_result.has_value() ||
        !keyword_location_result.has_value() ||
        !schema_resource_result.has_value() || !value_result.has_value() ||
        !children_result.has_value()) {
      return std::nullopt;
    }

    if (schema_resource_result.value() > 0 &&
        resources.array_size() >= schema_resource_result.value() &&
        keyword_location_result.value().starts_with('#')) {
      // TODO: Maybe we should emplace here?
      result.push_back(
          {std::move(type_result).value(),
           std::move(relative_schema_location_result).value(),
           std::move(relative_instance_location_result).value(),
           resources.at(schema_resource_result.value() - 1).to_string() +
               std::move(keyword_location_result).value(),
           schema_resource_result.value(), std::move(value_result).value(),
           std::move(children_result).value()});
    } else {
      // TODO: Maybe we should emplace here?
      result.push_back({std::move(type_result).value(),
                        std::move(relative_schema_location_result).value(),
                        std::move(relative_instance_location_result).value(),
                        std::move(keyword_location_result).value(),
                        std::move(schema_resource_result).value(),
                        std::move(value_result).value(),
                        std::move(children_result).value()});
    }
  }

  return result;
}

} // namespace

namespace sourcemeta::blaze {

auto from_json(const sourcemeta::core::JSON &json) -> std::optional<Template> {
  if (!json.is_array() || json.array_size() != 5) {
    return std::nullopt;
  }

  const auto &dynamic{json.at(0)};
  const auto &track{json.at(1)};
  const auto &resources{json.at(2)};

  if (!dynamic.is_boolean() || !track.is_boolean() || !resources.is_array()) {
    return std::nullopt;
  }

  const auto &targets{json.at(3)};
  if (!targets.is_array()) {
    return std::nullopt;
  }

  // Parse into tree instructions first
  std::vector<TreeInstructions> tree_targets;
  tree_targets.reserve(targets.size());
  for (const auto &target : targets.as_array()) {
    auto target_result{instructions_from_json(target, resources)};
    if (!target_result.has_value()) {
      return std::nullopt;
    }
    tree_targets.push_back(std::move(target_result).value());
  }

  const auto &labels{json.at(4)};
  if (!labels.is_array()) {
    return std::nullopt;
  }

  std::vector<std::pair<std::size_t, std::size_t>> labels_result;
  labels_result.reserve(labels.size());
  for (const auto &label : labels.as_array()) {
    if (!label.is_array() || label.array_size() != 2 ||
        !label.at(0).is_integer() || !label.at(1).is_integer()) {
      return std::nullopt;
    }
    labels_result.emplace_back(
        static_cast<std::size_t>(label.at(0).to_integer()),
        static_cast<std::size_t>(label.at(1).to_integer()));
  }

  // Build a tree template and flatten it
  const TreeTemplate tree_template{.dynamic = dynamic.to_boolean(),
                                   .track = track.to_boolean(),
                                   .targets = std::move(tree_targets),
                                   .labels = std::move(labels_result)};

  // Inline flattening (same logic as src/compiler/flatten.h but we cannot
  // include internal compiler headers from the evaluator)
  Template result;
  result.dynamic = tree_template.dynamic;
  result.track = tree_template.track;
  result.labels = tree_template.labels;
  result.targets.reserve(tree_template.targets.size());

  // Forward-declare the recursive helper via a std::function
  std::function<std::size_t(const TreeInstructions &, Instructions &)>
      flatten_tree = [&flatten_tree](const TreeInstructions &tree_instructions,
                                     Instructions &output) -> std::size_t {
    std::size_t total{0};
    for (const auto &tree_instruction : tree_instructions) {
      const auto parent_index{output.size()};
      output.push_back(
          {.type = tree_instruction.type,
           .relative_schema_location =
               tree_instruction.relative_schema_location,
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
            flatten_tree(tree_instruction.children, output)};
        output[parent_index].children_count =
            static_cast<std::uint32_t>(children_count);
        total += children_count;

        // Convert child indices to flat offsets in ValueNamedIndexes
        auto &flat_instruction{output[parent_index]};
        if (flat_instruction.type == InstructionIndex::LoopPropertiesMatch ||
            flat_instruction.type ==
                InstructionIndex::LoopPropertiesMatchClosed) {
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
          std::vector<std::pair<ValueString, std::size_t>> updates;
          updates.reserve(named_indexes->size());
          for (const auto &entry : *named_indexes) {
            assert(entry.second < child_offsets.size());
            updates.emplace_back(entry.first, child_offsets[entry.second]);
          }
          for (const auto &update : updates) {
            named_indexes->emplace(update.first, update.second);
          }
        }
      }

      output[parent_index].next_sibling_offset =
          static_cast<std::uint32_t>(output.size());
    }
    return total;
  };

  for (const auto &target : tree_template.targets) {
    const auto offset{result.instructions.size()};
    const auto count{flatten_tree(target, result.instructions)};
    result.targets.emplace_back(offset, count);
  }

  return result;
}

} // namespace sourcemeta::blaze
