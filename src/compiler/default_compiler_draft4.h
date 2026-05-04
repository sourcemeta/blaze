#ifndef SOURCEMETA_BLAZE_COMPILER_DEFAULT_COMPILER_DRAFT4_H_
#define SOURCEMETA_BLAZE_COMPILER_DEFAULT_COMPILER_DRAFT4_H_

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <algorithm> // std::ranges::any_of, std::ranges::all_of, std::ranges::none_of, std::find_if
#include <cassert> // assert
#include <set>     // std::set
#include <utility> // std::move, std::to_underlying

#include "compile_helpers.h"
#include "default_compiler_draft3.h"

namespace internal {
using namespace sourcemeta::blaze;

auto compiler_draft4_validation_type(const Context &context,
                                     const SchemaContext &schema_context,
                                     const DynamicContext &dynamic_context,
                                     const Instructions &) -> Instructions {
  if (schema_context.schema.at(dynamic_context.keyword).is_string()) {
    const auto &type{
        schema_context.schema.at(dynamic_context.keyword).to_string()};
    if (type == "null") {
      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_null(); })) {
        return {};
      }

      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Null)};
    } else if (type == "boolean") {
      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_boolean(); })) {
        return {};
      }

      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Boolean)};
    } else if (type == "object") {
      const auto minimum{
          unsigned_integer_property(schema_context.schema, "minProperties", 0)};
      const auto maximum{
          unsigned_integer_property(schema_context.schema, "maxProperties")};

      if (context.mode == Mode::FastValidation) {
        if (maximum.has_value() && minimum == 0) {
          return {make(
              sourcemeta::blaze::InstructionIndex::AssertionTypeObjectUpper,
              context, schema_context, dynamic_context,
              ValueUnsignedInteger{maximum.value()})};
        } else if (minimum > 0 || maximum.has_value()) {
          return {make(
              sourcemeta::blaze::InstructionIndex::AssertionTypeObjectBounded,
              context, schema_context, dynamic_context,
              ValueRange{minimum, maximum, false})};
        }
      }

      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_object(); })) {
        return {};
      }

      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("required")) {
        return {};
      }

      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Object)};
    } else if (type == "array") {
      const auto minimum{
          unsigned_integer_property(schema_context.schema, "minItems", 0)};
      const auto maximum{
          unsigned_integer_property(schema_context.schema, "maxItems")};

      if (context.mode == Mode::FastValidation) {
        if (maximum.has_value() && minimum == 0) {
          return {
              make(sourcemeta::blaze::InstructionIndex::AssertionTypeArrayUpper,
                   context, schema_context, dynamic_context,
                   ValueUnsignedInteger{maximum.value()})};
        } else if (minimum > 0 || maximum.has_value()) {
          return {make(
              sourcemeta::blaze::InstructionIndex::AssertionTypeArrayBounded,
              context, schema_context, dynamic_context,
              ValueRange{minimum, maximum, false})};
        }
      }

      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_array(); })) {
        return {};
      }

      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Array)};
    } else if (type == "number") {
      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_number(); })) {
        return {};
      }

      ValueTypes types{};
      types.set(std::to_underlying(sourcemeta::core::JSON::Type::Real));
      types.set(std::to_underlying(sourcemeta::core::JSON::Type::Integer));
      types.set(std::to_underlying(sourcemeta::core::JSON::Type::Decimal));
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrictAny,
                   context, schema_context, dynamic_context, types)};
    } else if (type == "integer") {
      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_integer(); })) {
        return {};
      }

      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Integer)};
    } else if (type == "string") {
      const auto minimum{
          unsigned_integer_property(schema_context.schema, "minLength", 0)};
      const auto maximum{
          unsigned_integer_property(schema_context.schema, "maxLength")};

      if (context.mode == Mode::FastValidation) {
        if (maximum.has_value() && minimum == 0) {
          return {make(
              sourcemeta::blaze::InstructionIndex::AssertionTypeStringUpper,
              context, schema_context, dynamic_context,
              ValueUnsignedInteger{maximum.value()})};
        } else if (minimum > 0 || maximum.has_value()) {
          return {make(
              sourcemeta::blaze::InstructionIndex::AssertionTypeStringBounded,
              context, schema_context, dynamic_context,
              ValueRange{minimum, maximum, false})};
        }
      }

      if (context.mode == Mode::FastValidation &&
          schema_context.schema.defines("enum") &&
          schema_context.schema.at("enum").is_array() &&
          std::ranges::all_of(
              schema_context.schema.at("enum").as_array(),
              [](const auto &value) { return value.is_string(); })) {
        return {};
      }

      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::String)};
    } else {
      return {};
    }
  } else if (schema_context.schema.at(dynamic_context.keyword).is_array() &&
             schema_context.schema.at(dynamic_context.keyword).size() == 1 &&
             schema_context.schema.at(dynamic_context.keyword)
                 .front()
                 .is_string()) {
    const auto &type{
        schema_context.schema.at(dynamic_context.keyword).front().to_string()};
    if (type == "null") {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Null)};
    } else if (type == "boolean") {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Boolean)};
    } else if (type == "object") {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Object)};
    } else if (type == "array") {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Array)};
    } else if (type == "number") {
      ValueTypes types{};
      types.set(std::to_underlying(sourcemeta::core::JSON::Type::Real));
      types.set(std::to_underlying(sourcemeta::core::JSON::Type::Integer));
      types.set(std::to_underlying(sourcemeta::core::JSON::Type::Decimal));
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrictAny,
                   context, schema_context, dynamic_context, types)};
    } else if (type == "integer") {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::Integer)};
    } else if (type == "string") {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrict,
                   context, schema_context, dynamic_context,
                   sourcemeta::core::JSON::Type::String)};
    } else {
      return {};
    }
  } else if (schema_context.schema.at(dynamic_context.keyword).is_array()) {
    ValueTypes types{};
    for (const auto &type :
         schema_context.schema.at(dynamic_context.keyword).as_array()) {
      assert(type.is_string());
      const auto &type_string{type.to_string()};
      if (type_string == "null") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Null));
      } else if (type_string == "boolean") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Boolean));
      } else if (type_string == "object") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Object));
      } else if (type_string == "array") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Array));
      } else if (type_string == "number") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Integer));
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Real));
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Decimal));
      } else if (type_string == "integer") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::Integer));
      } else if (type_string == "string") {
        types.set(std::to_underlying(sourcemeta::core::JSON::Type::String));
      }
    }

    assert(types.any());
    return {make(sourcemeta::blaze::InstructionIndex::AssertionTypeStrictAny,
                 context, schema_context, dynamic_context, types)};
  }

  return {};
}

auto compiler_draft4_validation_required(const Context &context,
                                         const SchemaContext &schema_context,
                                         const DynamicContext &dynamic_context,
                                         const Instructions &current)
    -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_array()) {
    return {};
  }

  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  const auto assume_object{schema_context.schema.defines("type") &&
                           schema_context.schema.at("type").is_string() &&
                           schema_context.schema.at("type").to_string() ==
                               "object"};

  if (schema_context.schema.at(dynamic_context.keyword).empty()) {
    return {};
  } else if (schema_context.schema.at(dynamic_context.keyword).size() > 1) {
    ValueStringSet properties_set{json_array_to_string_set(
        schema_context.schema.at(dynamic_context.keyword))};
    if (properties_set.size() == 1) {
      if (assume_object) {
        return {
            make(sourcemeta::blaze::InstructionIndex::AssertionDefinesStrict,
                 context, schema_context, dynamic_context,
                 make_property(properties_set.begin()->first))};
      } else {
        return {make(sourcemeta::blaze::InstructionIndex::AssertionDefines,
                     context, schema_context, dynamic_context,
                     make_property(properties_set.begin()->first))};
      }
    } else if (is_closed_properties_required(schema_context.schema,
                                             properties_set)) {
      if (context.mode == Mode::FastValidation && assume_object) {
        static const std::string properties_keyword{"properties"};
        const SchemaContext new_schema_context{
            .relative_pointer =
                schema_context.relative_pointer.initial().concat(
                    sourcemeta::blaze::make_weak_pointer(properties_keyword)),
            .schema = schema_context.schema,
            .vocabularies = schema_context.vocabularies,
            .base = schema_context.base,
            .is_property_name = schema_context.is_property_name};
        const DynamicContext new_dynamic_context{
            .keyword = KEYWORD_PROPERTIES,
            .base_schema_location = sourcemeta::core::empty_weak_pointer,
            .base_instance_location = sourcemeta::core::empty_weak_pointer};
        auto properties{compile_properties(context, new_schema_context,
                                           new_dynamic_context, current)};
        if (std::ranges::all_of(properties, [](const auto &property) {
              return property.second.size() == 1 &&
                     property.second.front().type ==
                         InstructionIndex::AssertionTypeStrict;
            })) {
          std::set<ValueType> types;
          for (const auto &property : properties) {
            types.insert(std::get<ValueType>(property.second.front().value));
          }

          if (types.size() == 1) {
            // Handled in `properties`
            return {};
          }
        }

        sourcemeta::core::PropertyHashJSON<ValueString> hasher;
        if (context.mode == Mode::FastValidation &&
            properties_set.size() == 3 &&
            std::ranges::all_of(properties_set,
                                [&hasher](const auto &property) {
                                  return hasher.is_perfect(property.second);
                                })) {
          std::vector<std::pair<ValueString, ValueStringSet::hash_type>> hashes;
          for (const auto &property : properties_set) {
            hashes.emplace_back(property.first, property.second);
          }

          return {make(sourcemeta::blaze::InstructionIndex::
                           AssertionDefinesExactlyStrictHash3,
                       context, schema_context, dynamic_context,
                       to_string_hashes(hashes))};
        }

        return {make(
            sourcemeta::blaze::InstructionIndex::AssertionDefinesExactlyStrict,
            context, schema_context, dynamic_context,
            std::move(properties_set))};
      } else {
        return {
            make(sourcemeta::blaze::InstructionIndex::AssertionDefinesExactly,
                 context, schema_context, dynamic_context,
                 std::move(properties_set))};
      }
    } else if (assume_object) {
      return {make(
          sourcemeta::blaze::InstructionIndex::AssertionDefinesAllStrict,
          context, schema_context, dynamic_context, std::move(properties_set))};
    } else {
      return {make(sourcemeta::blaze::InstructionIndex::AssertionDefinesAll,
                   context, schema_context, dynamic_context,
                   std::move(properties_set))};
    }
  } else if (assume_object) {
    assert(
        schema_context.schema.at(dynamic_context.keyword).front().is_string());
    return {make(sourcemeta::blaze::InstructionIndex::AssertionDefinesStrict,
                 context, schema_context, dynamic_context,
                 make_property(schema_context.schema.at(dynamic_context.keyword)
                                   .front()
                                   .to_string()))};
  } else {
    assert(
        schema_context.schema.at(dynamic_context.keyword).front().is_string());
    return {make(sourcemeta::blaze::InstructionIndex::AssertionDefines, context,
                 schema_context, dynamic_context,
                 make_property(schema_context.schema.at(dynamic_context.keyword)
                                   .front()
                                   .to_string()))};
  }
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
      std::ranges::all_of(disjunctors, [](const auto &instruction) {
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
                                 requires_evaluation(context, schema_context)};

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
                                 requires_evaluation(context, schema_context)};

  return {make(sourcemeta::blaze::InstructionIndex::LogicalXor, context,
               schema_context, dynamic_context,
               ValueBoolean{requires_exhaustive}, std::move(disjunctors))};
}

auto compiler_draft4_applicator_not(const Context &context,
                                    const SchemaContext &schema_context,
                                    const DynamicContext &dynamic_context,
                                    const Instructions &) -> Instructions {
  std::size_t subschemas{0};
  for (const auto &subschema :
       walk_subschemas(context, schema_context, dynamic_context)) {
    if (subschema.pointer.empty()) {
      continue;
    }

    subschemas += 1;
  }

  Instructions children{compile(context, schema_context,
                                relative_dynamic_context(),
                                sourcemeta::core::empty_weak_pointer,
                                sourcemeta::core::empty_weak_pointer)};

  // TODO: Be smarter about how we treat `unevaluatedItems` like how we do for
  // `unevaluatedProperties`
  const bool track_items{
      std::ranges::any_of(context.unevaluated, [](const auto &dependency) {
        return dependency.first.ends_with("unevaluatedItems");
      })};

  // Only emit a `not` instruction that keeps track of
  // evaluation if we really need it. If the "not" subschema
  // does not define applicators, then that's an easy case
  // we can skip
  if (subschemas > 0 &&
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

auto compiler_draft4_applicator_dependencies(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context, const Instructions &)
    -> Instructions {
  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  if (!schema_context.schema.at(dynamic_context.keyword).is_object()) {
    return {};
  }

  Instructions children;
  ValueStringMap dependencies;

  for (const auto &entry :
       schema_context.schema.at(dynamic_context.keyword).as_object()) {
    if (is_schema(entry.second)) {
      if (!entry.second.is_boolean() || !entry.second.to_boolean()) {
        children.push_back(make(
            sourcemeta::blaze::InstructionIndex::LogicalWhenDefines, context,
            schema_context, dynamic_context, make_property(entry.first),
            compile(context, schema_context, relative_dynamic_context(),
                    sourcemeta::blaze::make_weak_pointer(entry.first))));
      }
    } else if (entry.second.is_array()) {
      std::vector<sourcemeta::core::JSON::String> properties;
      for (const auto &property : entry.second.as_array()) {
        assert(property.is_string());
        properties.push_back(property.to_string());
      }

      if (!properties.empty()) {
        dependencies.emplace(entry.first, properties);
      }
    }
  }

  if (!dependencies.empty()) {
    children.push_back(make(
        sourcemeta::blaze::InstructionIndex::AssertionPropertyDependencies,
        context, schema_context, dynamic_context, std::move(dependencies)));
  }

  return children;
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

auto compiler_draft4_validation_multipleof(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context, const Instructions &)
    -> Instructions {
  if (!schema_context.schema.at(dynamic_context.keyword).is_number()) {
    return {};
  }

  assert(schema_context.schema.at(dynamic_context.keyword).is_positive());

  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "integer" &&
      schema_context.schema.at("type").to_string() != "number") {
    return {};
  }

  return {make(sourcemeta::blaze::InstructionIndex::AssertionDivisible, context,
               schema_context, dynamic_context,
               sourcemeta::core::JSON{
                   schema_context.schema.at(dynamic_context.keyword)})};
}

} // namespace internal
#endif
