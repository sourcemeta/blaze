#ifndef SOURCEMETA_BLAZE_COMPILER_COMPILE_HELPERS_H_
#define SOURCEMETA_BLAZE_COMPILER_COMPILE_HELPERS_H_

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/jsontoolkit/uri.h>

#include <algorithm> // std::find
#include <cassert>   // assert
#include <iterator>  // std::distance
#include <regex>     // std::regex, std::regex_match, std::smatch
#include <utility>   // std::declval, std::move

namespace sourcemeta::blaze {

static const DynamicContext relative_dynamic_context{
    "", sourcemeta::jsontoolkit::empty_pointer,
    sourcemeta::jsontoolkit::empty_pointer};

inline auto schema_resource_id(const Context &context,
                               const std::string &resource) -> std::size_t {
  const auto iterator{std::find(
      context.resources.cbegin(), context.resources.cend(),
      sourcemeta::jsontoolkit::URI{resource}.canonicalize().recompose())};
  if (iterator == context.resources.cend()) {
    assert(resource.empty());
    return 0;
  }

  return 1 + static_cast<std::size_t>(
                 std::distance(context.resources.cbegin(), iterator));
}

// Instantiate a value-oriented step
template <typename Step>
auto make(const Context &context, const SchemaContext &schema_context,
          const DynamicContext &dynamic_context,
          // Take the value type from the "type" property of the step struct
          const decltype(std::declval<Step>().value) &value) -> Step {
  return {
      dynamic_context.keyword.empty()
          ? dynamic_context.base_schema_location
          : dynamic_context.base_schema_location.concat(
                {dynamic_context.keyword}),
      dynamic_context.base_instance_location,
      to_uri(schema_context.relative_pointer, schema_context.base).recompose(),
      schema_resource_id(context, schema_context.base.recompose()),
      context.uses_dynamic_scopes,
      context.mode != Mode::FastValidation ||
          !context.unevaluated_properties_schemas.empty() ||
          !context.unevaluated_items_schemas.empty(),
      value};
}

// Instantiate an applicator step
template <typename Step>
auto make(const Context &context, const SchemaContext &schema_context,
          const DynamicContext &dynamic_context,
          // Take the value type from the "value" property of the step struct
          decltype(std::declval<Step>().value) &&value, Template &&children)
    -> Step {
  return {
      dynamic_context.keyword.empty()
          ? dynamic_context.base_schema_location
          : dynamic_context.base_schema_location.concat(
                {dynamic_context.keyword}),
      dynamic_context.base_instance_location,
      to_uri(schema_context.relative_pointer, schema_context.base).recompose(),
      schema_resource_id(context, schema_context.base.recompose()),
      context.uses_dynamic_scopes,
      context.mode != Mode::FastValidation ||
          !context.unevaluated_properties_schemas.empty() ||
          !context.unevaluated_items_schemas.empty(),
      std::move(value),
      std::move(children)};
}

template <typename Type, typename Step>
auto unroll(const DynamicContext &dynamic_context, const Step &step,
            const sourcemeta::jsontoolkit::Pointer &base_instance_location =
                sourcemeta::jsontoolkit::empty_pointer) -> Type {
  assert(std::holds_alternative<Type>(step));
  return {dynamic_context.keyword.empty()
              ? std::get<Type>(step).relative_schema_location
              : dynamic_context.base_schema_location
                    .concat({dynamic_context.keyword})
                    .concat(std::get<Type>(step).relative_schema_location),
          base_instance_location.concat(
              std::get<Type>(step).relative_instance_location),
          std::get<Type>(step).keyword_location,
          std::get<Type>(step).schema_resource,
          std::get<Type>(step).dynamic,
          std::get<Type>(step).track,
          std::get<Type>(step).value};
}

inline auto
unsigned_integer_property(const sourcemeta::jsontoolkit::JSON &document,
                          const sourcemeta::jsontoolkit::JSON::String &property)
    -> std::optional<std::size_t> {
  if (document.defines(property) && document.at(property).is_integer()) {
    const auto value{document.at(property).to_integer()};
    assert(value >= 0);
    return static_cast<std::size_t>(value);
  }

  return std::nullopt;
}

inline auto
unsigned_integer_property(const sourcemeta::jsontoolkit::JSON &document,
                          const sourcemeta::jsontoolkit::JSON::String &property,
                          const std::size_t otherwise) -> std::size_t {
  return unsigned_integer_property(document, property).value_or(otherwise);
}

inline auto static_frame_entry(const Context &context,
                               const SchemaContext &schema_context)
    -> const sourcemeta::jsontoolkit::ReferenceFrameEntry & {
  const auto type{sourcemeta::jsontoolkit::ReferenceType::Static};
  const auto current{
      to_uri(schema_context.relative_pointer, schema_context.base).recompose()};
  assert(context.frame.contains({type, current}));
  return context.frame.at({type, current});
}

inline auto walk_subschemas(const Context &context,
                            const SchemaContext &schema_context,
                            const DynamicContext &dynamic_context) -> auto {
  const auto &entry{static_frame_entry(context, schema_context)};
  return sourcemeta::jsontoolkit::SchemaIterator{
      schema_context.schema.at(dynamic_context.keyword), context.walker,
      context.resolver, entry.dialect};
}

inline auto pattern_as_prefix(const std::string &pattern)
    -> std::optional<std::string> {
  static const std::regex starts_with_regex{R"(^\^([a-zA-Z0-9-_/]+)$)"};
  std::smatch matches;
  if (std::regex_match(pattern, matches, starts_with_regex)) {
    return matches[1].str();
  } else {
    return std::nullopt;
  }
}

} // namespace sourcemeta::blaze

#endif
