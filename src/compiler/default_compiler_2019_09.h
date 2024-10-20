#ifndef SOURCEMETA_BLAZE_COMPILER_DEFAULT_COMPILER_2019_09_H_
#define SOURCEMETA_BLAZE_COMPILER_DEFAULT_COMPILER_2019_09_H_

#include <sourcemeta/blaze/compiler.h>

#include "compile_helpers.h"
#include "default_compiler_draft4.h"

namespace internal {
using namespace sourcemeta::blaze;

auto compiler_2019_09_applicator_dependentschemas(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  assert(schema_context.schema.at(dynamic_context.keyword).is_object());

  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  Template children;

  // To guarantee order
  std::vector<std::string> dependents;
  for (const auto &entry :
       schema_context.schema.at(dynamic_context.keyword).as_object()) {
    dependents.push_back(entry.first);
  }
  std::sort(dependents.begin(), dependents.end());

  for (const auto &dependent : dependents) {
    const auto &dependency{
        schema_context.schema.at(dynamic_context.keyword).at(dependent)};
    if (!is_schema(dependency)) {
      continue;
    }

    if (!dependency.is_boolean() || !dependency.to_boolean()) {
      children.push_back(make<LogicalWhenDefines>(
          true, context, schema_context, relative_dynamic_context,
          ValueString{dependent},
          compile(context, schema_context, relative_dynamic_context,
                  {dependent}, sourcemeta::jsontoolkit::empty_pointer)));
    }
  }

  // TODO: Is this wrapper really necessary?
  return {make<LogicalWhenType>(true, context, schema_context, dynamic_context,
                                sourcemeta::jsontoolkit::JSON::Type::Object,
                                std::move(children))};
}

auto compiler_2019_09_validation_dependentrequired(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  if (!schema_context.schema.at(dynamic_context.keyword).is_object()) {
    return {};
  }

  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  ValueStringMap dependencies;
  for (const auto &entry :
       schema_context.schema.at(dynamic_context.keyword).as_object()) {
    if (!entry.second.is_array()) {
      continue;
    }

    std::vector<sourcemeta::jsontoolkit::JSON::String> properties;
    for (const auto &property : entry.second.as_array()) {
      assert(property.is_string());
      properties.push_back(property.to_string());
    }

    if (!properties.empty()) {
      dependencies.emplace(entry.first, std::move(properties));
    }
  }

  if (dependencies.empty()) {
    return {};
  }

  return {make<AssertionPropertyDependencies>(
      true, context, schema_context, dynamic_context, std::move(dependencies))};
}

auto compiler_2019_09_core_annotation(const Context &context,
                                      const SchemaContext &schema_context,
                                      const DynamicContext &dynamic_context)
    -> Template {
  return {make<AnnotationEmit>(
      true, context, schema_context, dynamic_context,
      sourcemeta::jsontoolkit::JSON{
          schema_context.schema.at(dynamic_context.keyword)})};
}

auto compiler_2019_09_applicator_contains_with_options(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context, const bool annotate,
    const bool track_evaluation) -> Template {
  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "array") {
    return {};
  }

  std::size_t minimum{1};
  if (schema_context.schema.defines("minContains")) {
    if (schema_context.schema.at("minContains").is_integer() &&
        schema_context.schema.at("minContains").is_positive()) {
      minimum = static_cast<std::size_t>(
          schema_context.schema.at("minContains").to_integer());
    } else if (schema_context.schema.at("minContains").is_real() &&
               schema_context.schema.at("minContains").is_positive()) {
      minimum = static_cast<std::size_t>(
          schema_context.schema.at("minContains").as_integer());
    }
  }

  std::optional<std::size_t> maximum;
  if (schema_context.schema.defines("maxContains")) {
    if (schema_context.schema.at("maxContains").is_integer() &&
        schema_context.schema.at("maxContains").is_positive()) {
      maximum = schema_context.schema.at("maxContains").to_integer();
    } else if (schema_context.schema.at("maxContains").is_real() &&
               schema_context.schema.at("maxContains").is_positive()) {
      maximum = schema_context.schema.at("maxContains").as_integer();
    }
  }

  if (maximum.has_value() && minimum > maximum.value()) {
    return {make<AssertionFail>(true, context, schema_context, dynamic_context,
                                ValueNone{})};
  }

  if (minimum == 0 && !maximum.has_value()) {
    return {};
  }

  Template children{compile(context, schema_context, relative_dynamic_context,
                            sourcemeta::jsontoolkit::empty_pointer,
                            sourcemeta::jsontoolkit::empty_pointer)};

  if (annotate) {
    children.push_back(make<AnnotationBasenameToParent>(
        true, context, schema_context, relative_dynamic_context, ValueNone{}));

    // TODO: If after emitting the above annotation, the number of annotations
    // for the current schema location + instance location is equal to the
    // array size (which means we annotated all of the items), then emit
    // an annotation "true"
  }

  if (track_evaluation) {
    children.push_back(make<ControlEvaluate>(true, context, schema_context,
                                             relative_dynamic_context,
                                             ValuePointer{}));
  }

  return {make<LoopContains>(
      true, context, schema_context, dynamic_context,
      ValueRange{minimum, maximum, annotate || track_evaluation},
      std::move(children))};
}

auto compiler_2019_09_applicator_contains(const Context &context,
                                          const SchemaContext &schema_context,
                                          const DynamicContext &dynamic_context)
    -> Template {
  return compiler_2019_09_applicator_contains_with_options(
      context, schema_context, dynamic_context, false, false);
}

auto compiler_2019_09_applicator_additionalproperties(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  return compiler_draft4_applicator_additionalproperties_with_options(
      context, schema_context, dynamic_context,
      context.mode == Mode::Exhaustive, context.uses_unevaluated_properties);
}

auto compiler_2019_09_applicator_items(const Context &context,
                                       const SchemaContext &schema_context,
                                       const DynamicContext &dynamic_context)
    -> Template {
  return compiler_draft4_applicator_items_with_options(
      context, schema_context, dynamic_context,
      context.mode == Mode::Exhaustive, context.uses_unevaluated_items);
}

auto compiler_2019_09_applicator_additionalitems(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  return compiler_draft4_applicator_additionalitems_with_options(
      context, schema_context, dynamic_context,
      context.mode == Mode::Exhaustive, context.uses_unevaluated_items);
}

auto compiler_2019_09_applicator_unevaluateditems(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "array") {
    return {};
  }

  Template children{compile(context, schema_context, relative_dynamic_context,
                            sourcemeta::jsontoolkit::empty_pointer,
                            sourcemeta::jsontoolkit::empty_pointer)};

  if (context.mode == Mode::Exhaustive) {
    children.push_back(make<AnnotationToParent>(
        true, context, schema_context, relative_dynamic_context,
        sourcemeta::jsontoolkit::JSON{true}));
  }

  return {make<LoopItemsUnevaluated>(true, context, schema_context,
                                     dynamic_context, ValueNone{},
                                     std::move(children))};
}

auto compiler_2019_09_applicator_unevaluatedproperties(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  if (schema_context.schema.defines("type") &&
      schema_context.schema.at("type").is_string() &&
      schema_context.schema.at("type").to_string() != "object") {
    return {};
  }

  Template children{compile(context, schema_context, relative_dynamic_context,
                            sourcemeta::jsontoolkit::empty_pointer,
                            sourcemeta::jsontoolkit::empty_pointer)};

  if (context.mode == Mode::Exhaustive) {
    children.push_back(make<AnnotationBasenameToParent>(
        true, context, schema_context, relative_dynamic_context, ValueNone{}));
  }

  return {make<LoopPropertiesUnevaluated>(true, context, schema_context,
                                          dynamic_context, ValueNone{},
                                          std::move(children))};
}

auto compiler_2019_09_core_recursiveref(const Context &context,
                                        const SchemaContext &schema_context,
                                        const DynamicContext &dynamic_context)
    -> Template {
  const auto current{
      to_uri(schema_context.relative_pointer, schema_context.base).recompose()};
  assert(context.frame.contains(
      {sourcemeta::jsontoolkit::ReferenceType::Static, current}));
  const auto &entry{context.frame.at(
      {sourcemeta::jsontoolkit::ReferenceType::Static, current})};
  // In this case, just behave as a normal static reference
  if (!context.references.contains(
          {sourcemeta::jsontoolkit::ReferenceType::Dynamic, entry.pointer})) {
    return compiler_draft4_core_ref(context, schema_context, dynamic_context);
  }

  return {make<ControlDynamicAnchorJump>(true, context, schema_context,
                                         dynamic_context, "")};
}

auto compiler_2019_09_applicator_properties(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  return compiler_draft4_applicator_properties_with_options(
      context, schema_context, dynamic_context,
      context.mode == Mode::Exhaustive, context.uses_unevaluated_properties);
}

auto compiler_2019_09_applicator_patternproperties(
    const Context &context, const SchemaContext &schema_context,
    const DynamicContext &dynamic_context) -> Template {
  return compiler_draft4_applicator_patternproperties_with_options(
      context, schema_context, dynamic_context,
      context.mode == Mode::Exhaustive, context.uses_unevaluated_properties);
}

} // namespace internal
#endif
