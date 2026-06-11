#ifndef SOURCEMETA_BLAZE_COMPILER_DEFAULT_COMPILER_DRAFT4_H_
#define SOURCEMETA_BLAZE_COMPILER_DEFAULT_COMPILER_DRAFT4_H_

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <algorithm> // std::ranges::any_of, std::ranges::all_of, std::ranges::none_of, std::find_if
#include <cassert>       // assert
#include <map>           // std::map
#include <optional>      // std::optional, std::nullopt
#include <set>           // std::set
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move, std::to_underlying
#include <vector>        // std::vector

#include "compile_helpers.h"
#include "default_compiler_draft3.h"

namespace internal {
using namespace sourcemeta::blaze;

auto compiler_draft4_validation_required(const Context &context,
                                         const SchemaContext &schema_context,
                                         const DynamicContext &dynamic_context,
                                         const Instructions &current)
    -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_array()) {
    return {};
  }

  return compile_required_assertions(
      context, schema_context, dynamic_context, current,
      json_array_to_string_set(
          schema_context.schema.at(dynamic_context.keyword)));
}

auto compiler_draft4_applicator_allof(const Context &context,
                                      const SchemaContext &schema_context,
                                      const DynamicContext &dynamic_context,
                                      const Instructions &) -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_array()) {
    return {};
  }

  assert(!schema_context.schema.at(dynamic_context.keyword).empty());

  Instructions children;

  if (context.mode == Mode::FastValidation &&
      // TODO: Make this work with `$dynamicRef`
      !context.uses_dynamic_scopes) {
    for (std::uint64_t index = 0;
         index < schema_context.schema.at(dynamic_context.keyword).size();
         index++) {
      for (auto &&step : compile(
               context, schema_context, dynamic_context,
               {static_cast<sourcemeta::core::Pointer::Token::Index>(index)})) {
        children.push_back(std::move(step));
      }
    }

    return children;
  } else {
    for (std::uint64_t index = 0;
         index < schema_context.schema.at(dynamic_context.keyword).size();
         index++) {
      for (auto &&step : compile(
               context, schema_context, relative_dynamic_context(),
               {static_cast<sourcemeta::core::Pointer::Token::Index>(index)})) {
        children.push_back(std::move(step));
      }
    }

    return {make(sourcemeta::blaze::InstructionIndex::LogicalAnd, context,
                 schema_context, dynamic_context, ValueNone{},
                 std::move(children))};
  }
}

// The set of facts about a disjunct that hold no matter what, used to
// statically prove that a disjunction is a discriminated union
struct SwitchDisjunctFacts {
  bool object_only{false};
  bool never_object{false};
  std::set<sourcemeta::core::JSON::String> required;
  std::map<sourcemeta::core::JSON::String,
           std::vector<sourcemeta::core::JSON::String>>
      pinned;
};

auto is_known_non_object_type_name(const sourcemeta::core::JSON &entry)
    -> bool {
  if (!entry.is_string()) {
    return false;
  }

  const auto &name{entry.to_string()};
  return name == "null" || name == "boolean" || name == "array" ||
         name == "string" || name == "number" || name == "integer";
}

// Gather facts that necessarily hold for any instance that validates
// against the given subschema, following static references and `allOf`
// conjunctions. Note that when a subschema declares `$ref`, we ignore its
// siblings: older dialects consider them inert, and on newer dialects
// doing so only loses information, never inventing facts
auto collect_switch_disjunct_facts(
    const Context &context, const sourcemeta::core::JSON &subschema,
    const sourcemeta::blaze::SchemaFrame::Location &location,
    const std::string_view root_dialect, const Vocabularies &root_vocabularies,
    std::unordered_set<const sourcemeta::blaze::SchemaFrame::Location *>
        &visited,
    SwitchDisjunctFacts &facts) -> void {
  if (!subschema.is_object() || !visited.insert(&location).second) {
    return;
  }

  if (subschema.defines("$ref") && subschema.at("$ref").is_string()) {
    static const sourcemeta::core::JSON::String ref_keyword{"$ref"};
    const auto reference{context.frame.reference(
        sourcemeta::blaze::SchemaReferenceType::Static,
        location.pointer.concat(make_weak_pointer(ref_keyword)))};
    if (reference.has_value()) {
      const auto destination{
          context.frame.traverse(reference->get().destination)};
      if (destination.has_value()) {
        collect_switch_disjunct_facts(
            context,
            sourcemeta::core::get(context.root, destination->get().pointer),
            destination->get(), root_dialect, root_vocabularies, visited,
            facts);
      }
    }

    return;
  }

  using Known = sourcemeta::blaze::Vocabularies::Known;
  const auto vocabularies{
      location.dialect == root_dialect
          ? root_vocabularies
          : context.frame.vocabularies(location, context.resolver)};
  const auto supports_validation{
      vocabularies.contains(Known::JSON_Schema_Draft_4) ||
      vocabularies.contains(Known::JSON_Schema_Draft_6) ||
      vocabularies.contains(Known::JSON_Schema_Draft_7) ||
      vocabularies.contains(Known::JSON_Schema_2019_09_Validation) ||
      vocabularies.contains(Known::JSON_Schema_2020_12_Validation)};
  const auto supports_applicator{
      vocabularies.contains(Known::JSON_Schema_Draft_4) ||
      vocabularies.contains(Known::JSON_Schema_Draft_6) ||
      vocabularies.contains(Known::JSON_Schema_Draft_7) ||
      vocabularies.contains(Known::JSON_Schema_2019_09_Applicator) ||
      vocabularies.contains(Known::JSON_Schema_2020_12_Applicator)};
  const auto supports_const{
      vocabularies.contains(Known::JSON_Schema_Draft_6) ||
      vocabularies.contains(Known::JSON_Schema_Draft_7) ||
      vocabularies.contains(Known::JSON_Schema_2019_09_Validation) ||
      vocabularies.contains(Known::JSON_Schema_2020_12_Validation)};

  if (supports_validation) {
    if (subschema.defines("type")) {
      const auto &type{subschema.at("type")};
      if ((type.is_string() && type.to_string() == "object") ||
          (type.is_array() && !type.empty() &&
           std::ranges::all_of(type.as_array(), [](const auto &entry) -> bool {
             return entry.is_string() && entry.to_string() == "object";
           }))) {
        facts.object_only = true;
      } else if (is_known_non_object_type_name(type) ||
                 (type.is_array() && !type.empty() &&
                  std::ranges::all_of(type.as_array(),
                                      is_known_non_object_type_name))) {
        facts.never_object = true;
      }
    }

    if (subschema.defines("enum") && subschema.at("enum").is_array() &&
        std::ranges::none_of(
            subschema.at("enum").as_array(),
            [](const auto &option) -> bool { return option.is_object(); })) {
      facts.never_object = true;
    }

    if (supports_const && subschema.defines("const") &&
        !subschema.at("const").is_object()) {
      facts.never_object = true;
    }

    if (subschema.defines("required") && subschema.at("required").is_array()) {
      for (const auto &entry : subschema.at("required").as_array()) {
        if (entry.is_string()) {
          facts.required.insert(entry.to_string());
        }
      }
    }
  }

  if (supports_applicator && subschema.defines("properties") &&
      subschema.at("properties").is_object()) {
    for (const auto &entry : subschema.at("properties").as_object()) {
      if (facts.pinned.contains(entry.first) || !entry.second.is_object()) {
        continue;
      }

      std::vector<sourcemeta::core::JSON::String> values;
      if (supports_const && entry.second.defines("const") &&
          entry.second.at("const").is_string()) {
        values.push_back(entry.second.at("const").to_string());
      } else if (supports_validation && entry.second.defines("enum") &&
                 entry.second.at("enum").is_array() &&
                 !entry.second.at("enum").empty() &&
                 std::ranges::all_of(entry.second.at("enum").as_array(),
                                     [](const auto &option) -> bool {
                                       return option.is_string();
                                     })) {
        for (const auto &option : entry.second.at("enum").as_array()) {
          values.push_back(option.to_string());
        }
      } else {
        continue;
      }

      facts.pinned.emplace(entry.first, std::move(values));
    }
  }

  if (supports_applicator && subschema.defines("allOf") &&
      subschema.at("allOf").is_array()) {
    static const sourcemeta::core::JSON::String allof_keyword{"allOf"};
    for (std::size_t index = 0; index < subschema.at("allOf").size(); index++) {
      collect_switch_disjunct_facts(
          context, subschema.at("allOf").at(index),
          context.frame.traverse(location,
                                 make_weak_pointer(allof_keyword, index)),
          root_dialect, root_vocabularies, visited, facts);
    }
  }
}

// Attempt to compile a disjunction whose disjuncts all statically pin a
// shared discriminator property to disjoint constant strings (on top of
// requiring it on an object instance) into a single switch instruction
// that picks the only disjunct that can possibly match in constant time.
// Note that the given disjuncts are left untouched unless an instruction
// could indeed be derived
auto compile_switch_property_string(const Context &context,
                                    const SchemaContext &schema_context,
                                    const DynamicContext &dynamic_context,
                                    Instructions &disjunctors)
    -> std::optional<Instruction> {
  const auto &disjunction{schema_context.schema.at(dynamic_context.keyword)};
  if (disjunction.size() < 2) {
    return std::nullopt;
  }

  const auto &keyword_entry{static_frame_entry(context, schema_context)};
  std::vector<SwitchDisjunctFacts> facts_list;
  facts_list.reserve(disjunction.size());
  // The index plus one of the only disjunct that can match non-object
  // instances, where zero means no such disjunct exists
  ValueUnsignedInteger otherwise{0};
  std::vector<std::size_t> discriminated;
  discriminated.reserve(disjunction.size());
  for (std::size_t index = 0; index < disjunction.size(); index++) {
    sourcemeta::core::WeakPointer disjunct_suffix;
    disjunct_suffix.push_back(index);
    SwitchDisjunctFacts facts;
    std::unordered_set<const sourcemeta::blaze::SchemaFrame::Location *>
        visited;
    collect_switch_disjunct_facts(
        context, disjunction.at(index),
        context.frame.traverse(keyword_entry, disjunct_suffix),
        keyword_entry.dialect, schema_context.vocabularies, visited, facts);
    if (facts.never_object) {
      if (otherwise > 0) {
        return std::nullopt;
      }

      otherwise = index + 1;
    } else if (facts.object_only && !facts.pinned.empty()) {
      discriminated.push_back(index);
    } else {
      return std::nullopt;
    }

    facts_list.push_back(std::move(facts));
  }

  if (discriminated.size() < 2) {
    return std::nullopt;
  }

  for (const auto &candidate : facts_list[discriminated.front()].pinned) {
    const auto &name{candidate.first};
    ValueNamedIndexes indexes;
    bool valid{true};
    for (const auto index : discriminated) {
      const auto &facts{facts_list[index]};
      if (!facts.required.contains(name)) {
        valid = false;
        break;
      }

      const auto match{facts.pinned.find(name)};
      if (match == facts.pinned.cend()) {
        valid = false;
        break;
      }

      for (const auto &option : match->second) {
        const auto hash{indexes.hash(option)};
        if (indexes.defines(option, hash)) {
          valid = false;
          break;
        }

        indexes.emplace_assume_new(option, ValueUnsignedInteger{index}, hash);
      }

      if (!valid) {
        break;
      }
    }

    if (valid) {
      return make(
          sourcemeta::blaze::InstructionIndex::LogicalSwitchPropertyString,
          context, schema_context, dynamic_context,
          ValuePropertySwitch{make_property(name), std::move(indexes),
                              otherwise},
          std::move(disjunctors));
    }
  }

  return std::nullopt;
}

auto compiler_draft4_applicator_anyof(const Context &context,
                                      const SchemaContext &schema_context,
                                      const DynamicContext &dynamic_context,
                                      const Instructions &) -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_array()) {
    return {};
  }

  assert(!schema_context.schema.at(dynamic_context.keyword).empty());

  Instructions disjunctors;
  for (std::uint64_t index = 0;
       index < schema_context.schema.at(dynamic_context.keyword).size();
       index++) {
    disjunctors.push_back(make(
        sourcemeta::blaze::InstructionIndex::ControlGroup, context,
        schema_context, relative_dynamic_context(), ValueNone{},
        compile(
            context, schema_context, relative_dynamic_context(),
            {static_cast<sourcemeta::core::Pointer::Token::Index>(index)})));
  }

  if (context.mode == Mode::FastValidation &&
      std::ranges::all_of(disjunctors, [](const auto &instruction) -> auto {
        return instruction.children.size() == 1 &&
               (instruction.children.front().type ==
                    sourcemeta::blaze::InstructionIndex::AssertionTypeStrict ||
                instruction.children.front().type ==
                    sourcemeta::blaze::InstructionIndex::
                        AssertionTypeStrictAny);
      })) {
    ValueTypes types{};
    for (const auto &instruction : disjunctors) {
      if (instruction.children.front().type ==
          sourcemeta::blaze::InstructionIndex::AssertionTypeStrict) {
        const auto &value{
            *std::get_if<ValueType>(&instruction.children.front().value)};
        types.set(static_cast<std::uint8_t>(value));
      }

      if (instruction.children.front().type ==
          sourcemeta::blaze::InstructionIndex::AssertionTypeStrictAny) {
        const auto &value{
            *std::get_if<ValueTypes>(&instruction.children.front().value)};
        types |= value;
      }
    }

    assert(types.any());
    const auto popcount{types.count()};
    if (popcount > 1) {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrictAny,
                   context, schema_context, dynamic_context, types)};
    } else {
      std::uint8_t type_index{0};
      for (std::uint8_t bit{0}; bit < 8; bit++) {
        if (types.test(bit)) {
          type_index = bit;
          break;
        }
      }
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   static_cast<ValueType>(type_index))};
    }
  }

  const auto requires_exhaustive{context.mode == Mode::Exhaustive ||
                                 annotations_collected(context) ||
                                 requires_evaluation(context, schema_context)};

  if (context.mode == Mode::FastValidation && !requires_exhaustive &&
      !schema_context.is_property_name) {
    auto switched{compile_switch_property_string(context, schema_context,
                                                 dynamic_context, disjunctors)};
    if (switched.has_value()) {
      return {std::move(switched).value()};
    }
  }

  return {make(sourcemeta::blaze::InstructionIndex::LogicalOr, context,
               schema_context, dynamic_context,
               ValueBoolean{requires_exhaustive}, std::move(disjunctors))};
}

auto compiler_draft4_applicator_oneof(const Context &context,
                                      const SchemaContext &schema_context,
                                      const DynamicContext &dynamic_context,
                                      const Instructions &) -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_array()) {
    return {};
  }

  assert(!schema_context.schema.at(dynamic_context.keyword).empty());

  Instructions disjunctors;
  for (std::uint64_t index = 0;
       index < schema_context.schema.at(dynamic_context.keyword).size();
       index++) {
    disjunctors.push_back(make(
        sourcemeta::blaze::InstructionIndex::ControlGroup, context,
        schema_context, relative_dynamic_context(), ValueNone{},
        compile(
            context, schema_context, relative_dynamic_context(),
            {static_cast<sourcemeta::core::Pointer::Token::Index>(index)})));
  }

  const auto requires_exhaustive{context.mode == Mode::Exhaustive ||
                                 annotations_collected(context) ||
                                 requires_evaluation(context, schema_context)};

  // As the discriminator property values across disjuncts are proven to be
  // disjoint, at most one disjunct can ever match, so the exclusivity that
  // `oneOf` demands holds statically and the switch is also valid here
  if (context.mode == Mode::FastValidation && !requires_exhaustive &&
      !schema_context.is_property_name) {
    auto switched{compile_switch_property_string(context, schema_context,
                                                 dynamic_context, disjunctors)};
    if (switched.has_value()) {
      return {std::move(switched).value()};
    }
  }

  return {make(sourcemeta::blaze::InstructionIndex::LogicalXor, context,
               schema_context, dynamic_context,
               ValueBoolean{requires_exhaustive}, std::move(disjunctors))};
}

auto compiler_draft4_applicator_not(const Context &context,
                                    const SchemaContext &schema_context,
                                    const DynamicContext &dynamic_context,
                                    const Instructions &) -> Instructions {
  const auto subschemas{defines_nested_subschemas(context, schema_context)};

  Instructions children{compile(context, schema_context,
                                relative_dynamic_context(),
                                sourcemeta::core::empty_weak_pointer,
                                sourcemeta::core::empty_weak_pointer)};

  // TODO: Be smarter about how we treat `unevaluatedItems` like how we do for
  // `unevaluatedProperties`
  const bool track_items{std::ranges::any_of(
      context.unevaluated, [](const auto &dependency) -> auto {
        return dependency.first.ends_with("unevaluatedItems");
      })};

  // Only emit a `not` instruction that keeps track of
  // evaluation if we really need it. If the "not" subschema
  // does not define applicators, then that's an easy case
  // we can skip
  if (subschemas &&
      (requires_evaluation(context, schema_context) || track_items)) {
    return {make(sourcemeta::blaze::InstructionIndex::LogicalNotEvaluate,
                 context, schema_context, dynamic_context, ValueNone{},
                 std::move(children))};
  } else {
    return {make(sourcemeta::blaze::InstructionIndex::LogicalNot, context,
                 schema_context, dynamic_context, ValueNone{},
                 std::move(children))};
  }
}

auto compiler_draft4_validation_maxproperties(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context, const Instructions &)
    -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_integral()) {
    return {};
  }

  assert(schema_context.schema.at(dynamic_context.keyword).is_positive());

  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  // We'll handle it at the type level as an optimization
  if (context.mode == Mode::FastValidation &&
      schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() == "object") {
    return {};
  }

  return {make(
      sourcemeta::blaze::InstructionIndex::AssertionObjectSizeLess, context,
      schema_context, dynamic_context,
      ValueUnsignedInteger{
          static_cast<unsigned long>(
              schema_context.schema.at(dynamic_context.keyword).as_integer()) +
          1})};
}

auto compiler_draft4_validation_minproperties(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context, const Instructions &)
    -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_integral()) {
    return {};
  }

  assert(schema_context.schema.at(dynamic_context.keyword).is_positive());

  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  // We'll handle it at the type level as an optimization
  if (context.mode == Mode::FastValidation &&
      schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() == "object") {
    return {};
  }

  const auto value{static_cast<unsigned long>(
      schema_context.schema.at(dynamic_context.keyword).as_integer())};
  if (value <= 0) {
    return {};
  }

  return {make(sourcemeta::blaze::InstructionIndex::AssertionObjectSizeGreater,
               context, schema_context, dynamic_context,
               ValueUnsignedInteger{value - 1})};
}

} // namespace internal
#endif
