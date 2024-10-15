#include <sourcemeta/blaze/compiler.h>

#include <cassert>     // assert
#include <functional>  // std::less
#include <map>         // std::map
#include <sstream>     // std::ostringstream
#include <string_view> // std::string_view
#include <type_traits> // std::is_same_v
#include <utility>     // std::move

namespace {

template <typename T>
auto value_to_json(const T &value) -> sourcemeta::jsontoolkit::JSON {
  using namespace sourcemeta::blaze;
  sourcemeta::jsontoolkit::JSON result{
      sourcemeta::jsontoolkit::JSON::make_object()};
  result.assign("category", sourcemeta::jsontoolkit::JSON{"value"});
  if constexpr (std::is_same_v<SchemaCompilerValueJSON, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"json"});
    result.assign("value", sourcemeta::jsontoolkit::JSON{value});
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueBoolean, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"boolean"});
    result.assign("value", sourcemeta::jsontoolkit::JSON{value});
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueRegex, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"regex"});
    result.assign("value", sourcemeta::jsontoolkit::JSON{value.second});
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueType, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"type"});
    std::ostringstream type_string;
    type_string << value;
    result.assign("value", sourcemeta::jsontoolkit::JSON{type_string.str()});
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueTypes, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"types"});
    sourcemeta::jsontoolkit::JSON types{
        sourcemeta::jsontoolkit::JSON::make_array()};
    for (const auto type : value) {
      std::ostringstream type_string;
      type_string << type;
      types.push_back(sourcemeta::jsontoolkit::JSON{type_string.str()});
    }

    result.assign("value", std::move(types));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueString, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"string"});
    result.assign("value", sourcemeta::jsontoolkit::JSON{value});
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueStrings, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"strings"});
    sourcemeta::jsontoolkit::JSON items{
        sourcemeta::jsontoolkit::JSON::make_array()};
    for (const auto &item : value) {
      items.push_back(sourcemeta::jsontoolkit::JSON{item});
    }

    result.assign("value", std::move(items));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueArray, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"array"});
    sourcemeta::jsontoolkit::JSON items{
        sourcemeta::jsontoolkit::JSON::make_array()};
    for (const auto &item : value) {
      items.push_back(item);
    }

    result.assign("value", std::move(items));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueUnsignedInteger, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"unsigned-integer"});
    result.assign("value", sourcemeta::jsontoolkit::JSON{value});
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueRange, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"range"});
    sourcemeta::jsontoolkit::JSON values{
        sourcemeta::jsontoolkit::JSON::make_array()};
    const auto &range{value};
    values.push_back(sourcemeta::jsontoolkit::JSON{std::get<0>(range)});
    values.push_back(
        std::get<1>(range).has_value()
            ? sourcemeta::jsontoolkit::JSON{std::get<1>(range).value()}
            : sourcemeta::jsontoolkit::JSON{nullptr});
    values.push_back(sourcemeta::jsontoolkit::JSON{std::get<2>(range)});
    result.assign("value", std::move(values));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueNamedIndexes, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"named-indexes"});
    sourcemeta::jsontoolkit::JSON values{
        sourcemeta::jsontoolkit::JSON::make_object()};
    for (const auto &[name, index] : value) {
      values.assign(name, sourcemeta::jsontoolkit::JSON{index});
    }

    result.assign("value", std::move(values));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueStringMap, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"string-map"});
    sourcemeta::jsontoolkit::JSON map{
        sourcemeta::jsontoolkit::JSON::make_object()};
    for (const auto &[string, strings] : value) {
      sourcemeta::jsontoolkit::JSON dependencies{
          sourcemeta::jsontoolkit::JSON::make_array()};
      for (const auto &substring : strings) {
        dependencies.push_back(sourcemeta::jsontoolkit::JSON{substring});
      }

      map.assign(string, std::move(dependencies));
    }

    result.assign("value", std::move(map));
    return result;
  } else if constexpr (std::is_same_v<
                           SchemaCompilerValueItemsAnnotationKeywords, T>) {
    result.assign("type",
                  sourcemeta::jsontoolkit::JSON{"items-annotation-keywords"});
    sourcemeta::jsontoolkit::JSON data{
        sourcemeta::jsontoolkit::JSON::make_object()};
    data.assign("index", sourcemeta::jsontoolkit::JSON{value.index});

    sourcemeta::jsontoolkit::JSON mask{
        sourcemeta::jsontoolkit::JSON::make_array()};
    for (const auto &keyword : value.mask) {
      mask.push_back(sourcemeta::jsontoolkit::JSON{keyword});
    }
    data.assign("mask", std::move(mask));

    sourcemeta::jsontoolkit::JSON filter{
        sourcemeta::jsontoolkit::JSON::make_array()};
    for (const auto &keyword : value.filter) {
      filter.push_back(sourcemeta::jsontoolkit::JSON{keyword});
    }
    data.assign("filter", std::move(filter));

    result.assign("value", std::move(data));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueIndexedJSON, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"indexed-json"});
    sourcemeta::jsontoolkit::JSON data{
        sourcemeta::jsontoolkit::JSON::make_object()};
    data.assign("index", sourcemeta::jsontoolkit::JSON{value.first});
    data.assign("value", value.second);
    result.assign("value", std::move(data));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValuePropertyFilter, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"property-filter"});
    sourcemeta::jsontoolkit::JSON data{
        sourcemeta::jsontoolkit::JSON::make_object()};
    data.assign("names", sourcemeta::jsontoolkit::JSON::make_array());
    data.assign("patterns", sourcemeta::jsontoolkit::JSON::make_array());

    for (const auto &name : value.first) {
      data.at("names").push_back(sourcemeta::jsontoolkit::JSON{name});
    }

    for (const auto &pattern : value.second) {
      data.at("patterns")
          .push_back(sourcemeta::jsontoolkit::JSON{pattern.second});
    }

    result.assign("value", std::move(data));
    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueStringType, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"string-type"});
    switch (value) {
      case SchemaCompilerValueStringType::URI:
        result.assign("value", sourcemeta::jsontoolkit::JSON{"uri"});
        break;
      default:
        // We should never get here
        assert(false);
    }

    return result;
  } else if constexpr (std::is_same_v<SchemaCompilerValueIndexPair, T>) {
    result.assign("type", sourcemeta::jsontoolkit::JSON{"index-pair"});
    sourcemeta::jsontoolkit::JSON data{
        sourcemeta::jsontoolkit::JSON::make_array()};
    data.push_back(sourcemeta::jsontoolkit::JSON{value.first});
    data.push_back(sourcemeta::jsontoolkit::JSON{value.second});
    result.assign("value", std::move(data));
    return result;
  } else {
    static_assert(std::is_same_v<SchemaCompilerValueNone, T>);
    return sourcemeta::jsontoolkit::JSON{nullptr};
  }
}

template <typename V>
auto step_to_json(
    const sourcemeta::blaze::SchemaCompilerTemplate::value_type &step)
    -> sourcemeta::jsontoolkit::JSON {
  static V visitor;
  return std::visit(visitor, step);
}

template <typename V, typename T>
auto encode_step(const std::string_view category, const std::string_view type,
                 const T &step) -> sourcemeta::jsontoolkit::JSON {
  sourcemeta::jsontoolkit::JSON result{
      sourcemeta::jsontoolkit::JSON::make_object()};
  result.assign("category", sourcemeta::jsontoolkit::JSON{category});
  result.assign("type", sourcemeta::jsontoolkit::JSON{type});
  result.assign(
      "relativeSchemaLocation",
      sourcemeta::jsontoolkit::JSON{to_string(step.relative_schema_location)});
  result.assign("relativeInstanceLocation",
                sourcemeta::jsontoolkit::JSON{
                    to_string(step.relative_instance_location)});
  result.assign("absoluteKeywordLocation",
                sourcemeta::jsontoolkit::JSON{step.keyword_location});
  result.assign("schemaResource",
                sourcemeta::jsontoolkit::JSON{step.schema_resource});
  result.assign("dynamic", sourcemeta::jsontoolkit::JSON{step.dynamic});
  result.assign("report", sourcemeta::jsontoolkit::JSON{step.report});
  result.assign("value", value_to_json(step.value));

  if constexpr (requires { step.children; }) {
    result.assign("children", sourcemeta::jsontoolkit::JSON::make_array());
    for (const auto &child : step.children) {
      result.at("children").push_back(step_to_json<V>(child));
    }
  }

  return result;
}

struct StepVisitor {
#define HANDLE_STEP(category, type, name)                                      \
  auto operator()(const sourcemeta::blaze::name &step)                         \
      const->sourcemeta::jsontoolkit::JSON {                                   \
    return encode_step<StepVisitor>(category, type, step);                     \
  }

  HANDLE_STEP("assertion", "fail", SchemaCompilerAssertionFail)
  HANDLE_STEP("assertion", "defines", SchemaCompilerAssertionDefines)
  HANDLE_STEP("assertion", "defines-all", SchemaCompilerAssertionDefinesAll)
  HANDLE_STEP("assertion", "property-dependencies",
              SchemaCompilerAssertionPropertyDependencies)
  HANDLE_STEP("assertion", "type", SchemaCompilerAssertionType)
  HANDLE_STEP("assertion", "type-any", SchemaCompilerAssertionTypeAny)
  HANDLE_STEP("assertion", "type-strict", SchemaCompilerAssertionTypeStrict)
  HANDLE_STEP("assertion", "type-strict-any",
              SchemaCompilerAssertionTypeStrictAny)
  HANDLE_STEP("assertion", "type-string-bounded",
              SchemaCompilerAssertionTypeStringBounded)
  HANDLE_STEP("assertion", "type-array-bounded",
              SchemaCompilerAssertionTypeArrayBounded)
  HANDLE_STEP("assertion", "type-object-bounded",
              SchemaCompilerAssertionTypeObjectBounded)
  HANDLE_STEP("assertion", "regex", SchemaCompilerAssertionRegex)
  HANDLE_STEP("assertion", "string-size-less",
              SchemaCompilerAssertionStringSizeLess)
  HANDLE_STEP("assertion", "string-size-greater",
              SchemaCompilerAssertionStringSizeGreater)
  HANDLE_STEP("assertion", "array-size-less",
              SchemaCompilerAssertionArraySizeLess)
  HANDLE_STEP("assertion", "array-size-greater",
              SchemaCompilerAssertionArraySizeGreater)
  HANDLE_STEP("assertion", "object-size-less",
              SchemaCompilerAssertionObjectSizeLess)
  HANDLE_STEP("assertion", "object-size-greater",
              SchemaCompilerAssertionObjectSizeGreater)
  HANDLE_STEP("assertion", "equal", SchemaCompilerAssertionEqual)
  HANDLE_STEP("assertion", "greater-equal", SchemaCompilerAssertionGreaterEqual)
  HANDLE_STEP("assertion", "less-equal", SchemaCompilerAssertionLessEqual)
  HANDLE_STEP("assertion", "greater", SchemaCompilerAssertionGreater)
  HANDLE_STEP("assertion", "less", SchemaCompilerAssertionLess)
  HANDLE_STEP("assertion", "unique", SchemaCompilerAssertionUnique)
  HANDLE_STEP("assertion", "divisible", SchemaCompilerAssertionDivisible)
  HANDLE_STEP("assertion", "string-type", SchemaCompilerAssertionStringType)
  HANDLE_STEP("assertion", "property-type", SchemaCompilerAssertionPropertyType)
  HANDLE_STEP("assertion", "property-type-strict",
              SchemaCompilerAssertionPropertyTypeStrict)
  HANDLE_STEP("assertion", "equals-any", SchemaCompilerAssertionEqualsAny)
  HANDLE_STEP("annotation", "emit", SchemaCompilerAnnotationEmit)
  HANDLE_STEP("annotation", "when-array-size-equal",
              SchemaCompilerAnnotationWhenArraySizeEqual)
  HANDLE_STEP("annotation", "when-array-size-greater",
              SchemaCompilerAnnotationWhenArraySizeGreater)
  HANDLE_STEP("annotation", "to-parent", SchemaCompilerAnnotationToParent)
  HANDLE_STEP("annotation", "basename-to-parent",
              SchemaCompilerAnnotationBasenameToParent)
  HANDLE_STEP("annotation", "loop-properties-unevaluated",
              SchemaCompilerAnnotationLoopPropertiesUnevaluated)
  HANDLE_STEP("annotation", "loop-items-unmarked",
              SchemaCompilerAnnotationLoopItemsUnmarked)
  HANDLE_STEP("annotation", "loop-items-unevaluated",
              SchemaCompilerAnnotationLoopItemsUnevaluated)
  HANDLE_STEP("annotation", "not", SchemaCompilerAnnotationNot)
  HANDLE_STEP("logical", "not", SchemaCompilerLogicalNot)
  HANDLE_STEP("logical", "or", SchemaCompilerLogicalOr)
  HANDLE_STEP("logical", "and", SchemaCompilerLogicalAnd)
  HANDLE_STEP("logical", "xor", SchemaCompilerLogicalXor)
  HANDLE_STEP("logical", "condition", SchemaCompilerLogicalCondition)
  HANDLE_STEP("logical", "when-type", SchemaCompilerLogicalWhenType)
  HANDLE_STEP("logical", "when-defines", SchemaCompilerLogicalWhenDefines)
  HANDLE_STEP("logical", "when-array-size-greater",
              SchemaCompilerLogicalWhenArraySizeGreater)
  HANDLE_STEP("logical", "when-array-size-equal",
              SchemaCompilerLogicalWhenArraySizeEqual)
  HANDLE_STEP("loop", "properties-match", SchemaCompilerLoopPropertiesMatch)
  HANDLE_STEP("loop", "properties", SchemaCompilerLoopProperties)
  HANDLE_STEP("loop", "properties-regex", SchemaCompilerLoopPropertiesRegex)
  HANDLE_STEP("loop", "properties-except", SchemaCompilerLoopPropertiesExcept)
  HANDLE_STEP("loop", "properties-type", SchemaCompilerLoopPropertiesType)
  HANDLE_STEP("loop", "properties-type-strict",
              SchemaCompilerLoopPropertiesTypeStrict)
  HANDLE_STEP("loop", "keys", SchemaCompilerLoopKeys)
  HANDLE_STEP("loop", "items", SchemaCompilerLoopItems)
  HANDLE_STEP("loop", "contains", SchemaCompilerLoopContains)
  HANDLE_STEP("control", "label", SchemaCompilerControlLabel)
  HANDLE_STEP("control", "mark", SchemaCompilerControlMark)
  HANDLE_STEP("control", "jump", SchemaCompilerControlJump)
  HANDLE_STEP("control", "dynamic-anchor-jump",
              SchemaCompilerControlDynamicAnchorJump)

#undef HANDLE_STEP
};

} // namespace

namespace sourcemeta::blaze {

auto to_json(const SchemaCompilerTemplate &steps)
    -> sourcemeta::jsontoolkit::JSON {
  sourcemeta::jsontoolkit::JSON result{
      sourcemeta::jsontoolkit::JSON::make_array()};
  for (const auto &step : steps) {
    result.push_back(step_to_json<StepVisitor>(step));
  }

  return result;
}

auto compiler_template_format_compare(
    const sourcemeta::jsontoolkit::JSON::String &left,
    const sourcemeta::jsontoolkit::JSON::String &right) -> bool {
  using Rank = std::map<
      sourcemeta::jsontoolkit::JSON::String, std::uint64_t,
      std::less<sourcemeta::jsontoolkit::JSON::String>,
      sourcemeta::jsontoolkit::JSON::Allocator<std::pair<
          const sourcemeta::jsontoolkit::JSON::String, std::uint64_t>>>;
  static Rank rank{{"category", 0},
                   {"type", 1},
                   {"value", 2},
                   {"schemaResource", 3},
                   {"absoluteKeywordLocation", 4},
                   {"relativeSchemaLocation", 5},
                   {"relativeInstanceLocation", 6},
                   {"report", 7},
                   {"dynamic", 8},
                   {"children", 9}};

  constexpr std::uint64_t DEFAULT_RANK{999};
  const auto left_rank{rank.contains(left) ? rank.at(left) : DEFAULT_RANK};
  const auto right_rank{rank.contains(right) ? rank.at(right) : DEFAULT_RANK};
  return left_rank < right_rank;
}

} // namespace sourcemeta::blaze
