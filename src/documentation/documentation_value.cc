#include "internal.h"

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/regex.h>

#include <algorithm>   // std::sort, std::any_of, std::find, std::max
#include <cassert>     // assert
#include <cmath>       // std::floor
#include <cstddef>     // std::size_t
#include <cstdint>     // std::int64_t, std::uint8_t, std::uint32_t
#include <map>         // std::map
#include <optional>    // std::optional
#include <set>         // std::set
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move, std::pair
#include <vector>      // std::vector

// Turning one subschema into one value of the table format. Every rule it
// states must hold for the data the schema accepts, and what cannot be stated
// exactly is refused rather than guessed at.

namespace sourcemeta::blaze::documentation {

namespace {

auto child(const Pointer &pointer, const std::string &token) -> Pointer {
  Pointer result{pointer};
  result.push_back(JSON::String{token});
  return result;
}

auto child(const Pointer &pointer, const std::size_t index) -> Pointer {
  Pointer result{pointer};
  result.push_back(index);
  return result;
}

// How deeply the document nests, counted without recursion so that measuring a
// runaway schema cannot itself exhaust the stack.

auto pointer_string(const Pointer &pointer) -> std::string {
  return sourcemeta::core::to_string(pointer);
}

auto make_value(const std::string_view kind) -> JSON {
  auto result{JSON::make_object()};
  result.assign("kind", JSON{std::string{kind}});
  return result;
}

// The dialect in effect at a place: the one of the subschema there, or else of
// the nearest one around it.
auto rank_at(const Context &context, const Pointer &pointer) -> Rank {
  Pointer current{pointer};
  while (true) {
    const auto match{context.ranks.find(pointer_string(current))};
    if (match != context.ranks.cend()) {
      return match->second;
    }

    if (current.empty()) {
      return context.rank;
    }

    current.pop_back();
  }
}

// The schema resource a place belongs to: the nearest subschema around it that
// declares an identifier, or the root.
auto resource_of(const Context &context, const Pointer &pointer) -> Pointer {
  Pointer current{pointer};
  while (!current.empty()) {
    if (context.ranks.contains(pointer_string(current))) {
      const auto &candidate{sourcemeta::core::get(context.root, current)};
      if (defines(candidate, "$id") && candidate.at("$id").is_string()) {
        return current;
      }
    }

    current.pop_back();
  }

  return current;
}

// A place in this schema, described once as a shape and linked to wherever it
// is used.
auto shape_at(Context &context, const Pointer &target) -> JSON {
  const auto identifier{pointer_string(target)};
  auto match{context.shapes.find(identifier)};
  if (match == context.shapes.cend()) {
    match = context.shapes
                .emplace(identifier, Shape{.identifier = identifier,
                                           .pointer = target,
                                           .uses = 0})
                .first;
  }

  match->second.uses += 1;
  auto value{make_value("ref")};
  value.assign("ref", JSON{identifier});
  return value;
}

// Where a reference keyword of a subschema lands in this schema. Nothing means
// it leads to another document, kept at the address it gives.
auto landing_of(const Context &context, const Pointer &pointer,
                const std::string &keyword, std::string &destination)
    -> std::optional<Pointer> {
  const auto entry{
      context.references.find(pointer_string(child(pointer, keyword)))};
  if (entry == context.references.cend()) {
    fail("This keyword names a place that does not resolve", pointer, keyword);
  }

  destination = entry->second;
  const auto target{context.frame.traverse(destination)};
  if (!target.has_value()) {
    // A reference into this document that lands nowhere is a schema that
    // cannot be read, rather than a document kept elsewhere.
    const auto &root{context.frame.root()};
    if (destination.starts_with('#') ||
        (!root.empty() && destination.starts_with(root))) {
      fail("This keyword names a place in this schema that does not resolve",
           pointer, keyword);
    }

    return std::nullopt;
  }

  const auto &location{target->get()};
  if (location.type != sourcemeta::core::SchemaFrame::LocationType::Resource &&
      location.type != sourcemeta::core::SchemaFrame::LocationType::Subschema &&
      location.type != sourcemeta::core::SchemaFrame::LocationType::Anchor &&
      location.type != sourcemeta::core::SchemaFrame::LocationType::Pointer) {
    fail("This keyword names something that is not a schema", pointer, keyword);
  }

  auto result{sourcemeta::core::to_pointer(location.pointer)};
  // A place that only holds subschemas, such as `properties`, or holds the
  // author's values, such as `enum`, is not a schema even when it reads as an
  // object.
  if (location.type == sourcemeta::core::SchemaFrame::LocationType::Pointer) {
    static const std::set<std::string> HOLDERS{"properties",
                                               "patternProperties",
                                               "$defs",
                                               "definitions",
                                               "dependentSchemas",
                                               "dependencies",
                                               "allOf",
                                               "anyOf",
                                               "oneOf",
                                               "prefixItems",
                                               "items",
                                               "extends",
                                               "type",
                                               "disallow",
                                               "enum",
                                               "const",
                                               "examples",
                                               "default",
                                               "required"};
    Pointer prefix;
    for (const auto &token : result) {
      if (token.is_property() && HOLDERS.contains(token.to_property()) &&
          context.ranks.contains(pointer_string(prefix))) {
        const auto &holder{sourcemeta::core::get(
            context.root, child(prefix, token.to_property()))};
        const auto container{holder.is_object() || holder.is_array()};
        const auto value_keyword{token.to_property() == "enum" ||
                                 token.to_property() == "const" ||
                                 token.to_property() == "examples" ||
                                 token.to_property() == "default" ||
                                 token.to_property() == "required"};
        // The holder itself, or anything inside an author's value.
        if ((container && prefix.size() + 1 == result.size()) ||
            value_keyword) {
          fail("This keyword names something that is not a schema", pointer,
               keyword);
        }
      }

      if (token.is_property()) {
        prefix.push_back(token.to_property());
      } else {
        prefix.push_back(token.to_index());
      }
    }
  }

  const auto &target_schema{sourcemeta::core::get(context.root, result)};
  if (!target_schema.is_object() && !target_schema.is_boolean()) {
    fail("This keyword names something that is not a schema", pointer, keyword);
  }

  return result;
}

// Where a `$dynamicRef` or `$recursiveRef` may land. Evaluation always starts
// at the root, so an anchor the root resource declares always wins. Otherwise
// the place depends on the path taken to get there, and each place it may be
// is one of the forms the value takes.
auto dynamic_landings(const Context &context, const Pointer &pointer,
                      const std::string &keyword) -> std::vector<Pointer> {
  const auto entry{
      context.dynamic_references.find(pointer_string(child(pointer, keyword)))};
  if (entry == context.dynamic_references.cend()) {
    // It behaves as a plain reference, which the frame resolved as one.
    std::string destination;
    const auto target{landing_of(context, pointer, keyword, destination)};
    if (!target.has_value()) {
      return {};
    }

    return {target.value()};
  }

  const auto hash{entry->second.find('#')};
  const std::string name{keyword == "$recursiveRef" || hash == std::string::npos
                             ? std::string{}
                             : entry->second.substr(hash)};
  const auto places{context.dynamic_anchors.find(name)};
  if (places == context.dynamic_anchors.cend() || places->second.empty()) {
    // Nothing here declares it, so it leads to another document, unless it
    // was meant for this one.
    const auto &root{context.frame.root()};
    if (entry->second.starts_with('#') ||
        (!root.empty() && entry->second.starts_with(root))) {
      fail("This keyword names a place that does not resolve", pointer,
           keyword);
    }

    return {};
  }

  for (const auto &place : places->second) {
    if (resource_of(context, place).empty()) {
      return {place};
    }
  }

  return places->second;
}

auto bounds(const JSON &subschema, const std::string &minimum,
            const std::string &maximum) -> std::optional<JSON> {
  const auto has_minimum{defines(subschema, minimum)};
  const auto has_maximum{defines(subschema, maximum)};
  if (!has_minimum && !has_maximum) {
    return std::nullopt;
  }

  auto result{JSON::make_object()};
  if (has_minimum) {
    result.assign("min", subschema.at(minimum));
  }

  if (has_maximum) {
    result.assign("max", subschema.at(maximum));
  }

  return result;
}

auto copy_if_present(const JSON &subschema, const std::string &keyword,
                     JSON &value, const std::string &into) -> void {
  if (!defines(subschema, keyword)) {
    return;
  }

  // Text that says nothing is not there at all. A default or an example of an
  // empty string is a value, not text about the schema, and is kept.
  const auto &entry{subschema.at(keyword)};
  if ((keyword == "title" || keyword == "description") && entry.is_string() &&
      entry.to_string().empty()) {
    return;
  }

  value.assign(into, entry);
}

// A count keyword must be a whole number that is not negative, in every
// dialect that defines it.
auto count_of(const JSON &subschema, const std::string &keyword,
              const Pointer &pointer) -> void {
  if (!defines(subschema, keyword)) {
    return;
  }

  // A count may be larger than the usual kinds of number hold, which the
  // meta-schema allows as long as it is whole and not negative.
  const auto &count{subschema.at(keyword)};
  const auto whole{
      count.is_integer() ||
      (count.is_real() && std::floor(count.to_real()) == count.to_real()) ||
      (count.is_decimal() && count.to_decimal().is_integral())};
  if (!whole || count < JSON{static_cast<std::int64_t>(0)}) {
    fail("This keyword must be a count", pointer, keyword);
  }
}

// Whether a value, as the format describes it, accepts null.
auto accepts_null(const JSON &value) -> bool {
  if (value.defines("nullable")) {
    return true;
  }

  const auto &kind{value.at("kind").to_string()};
  if (kind == "null" || kind == "any" || kind == "ref" || kind == "external") {
    // A shape or another document might accept null, and this cannot tell.
    return true;
  }

  if (kind == "enum") {
    const auto &values{value.at("values")};
    return std::any_of(values.as_array().cbegin(), values.as_array().cend(),
                       [](const auto &entry) { return entry.is_null(); });
  }

  if (value.defines("otherTypesAllowed")) {
    return true;
  }

  if (kind == "choice") {
    const auto &options{value.at("options")};
    return std::any_of(options.as_array().cbegin(), options.as_array().cend(),
                       [](const auto &option) { return accepts_null(option); });
  }

  return false;
}

} // namespace

// Whether one value of an enumeration is accepted by the KEYWORDS beside it.
// Unknown means this module cannot tell, and then those KEYWORDS are stated as
// a rule of their own rather than being dropped.
enum class Verdict : std::uint8_t { Yes, No, Unknown };

auto kind_of_value(const JSON &entry) -> std::string {
  if (entry.is_string()) {
    return "string";
  }

  if (entry.is_integer()) {
    return "integer";
  }

  if (entry.is_real()) {
    return "number";
  }

  // A number too large for the other kinds, which may still be whole.
  if (entry.is_decimal()) {
    return entry.to_decimal().is_integral() ? "integer" : "number";
  }

  if (entry.is_boolean()) {
    return "boolean";
  }

  if (entry.is_null()) {
    return "null";
  }

  if (entry.is_array()) {
    return "array";
  }

  return "object";
}

auto accepted_by(const JSON &entry, const JSON &subschema,
                 const std::vector<std::string> &kinds, const Rank rank)
    -> Verdict {
  const auto kind{kind_of_value(entry)};
  if (!kinds.empty()) {
    auto matches{false};
    for (const auto &wanted : kinds) {
      if (wanted == kind || (wanted == "number" && kind == "integer")) {
        matches = true;
      }
    }

    if (!matches) {
      return Verdict::No;
    }
  }

  if (entry.is_string()) {
    // `minLength` and `maxLength` count characters, not bytes, and
    // `JSON::size` is the logical length the specification means.
    const JSON length{static_cast<std::int64_t>(entry.size())};
    if (defines(subschema, "minLength") &&
        subschema.at("minLength").is_number() &&
        length < subschema.at("minLength")) {
      return Verdict::No;
    }

    if (defines(subschema, "maxLength") &&
        subschema.at("maxLength").is_number() &&
        subschema.at("maxLength") < length) {
      return Verdict::No;
    }

    // A pattern needs a regular expression engine to decide, so it is left to
    // the rule beside the values.
    if (defines(subschema, "pattern")) {
      return Verdict::Unknown;
    }
  }

  if (entry.is_number()) {
    // Numbers are compared exactly, whatever kind of number each one is.
    // Going through `double` would make distinct integers past the range it
    // holds exactly look equal, and a value the schema rejects would be kept
    // as one it accepts.
    const auto side = [&entry](const JSON &limit) -> int {
      if (entry < limit) {
        return -1;
      }

      return limit < entry ? 1 : 0;
    };

    const auto bound =
        [&subschema](const std::string &keyword) -> const JSON * {
      if (!defines(subschema, keyword)) {
        return nullptr;
      }

      const auto &value{subschema.at(keyword)};
      return value.is_number() ? &value : nullptr;
    };

    // Before Draft 6 an exclusive bound is a flag beside the bound itself,
    // rather than a number of its own.
    const auto flagged = [&subschema,
                          rank](const std::string &keyword) -> bool {
      return rank < Rank::Draft6 && defines(subschema, keyword) &&
             subschema.at(keyword).is_boolean() &&
             subschema.at(keyword).to_boolean();
    };

    const auto *low{bound("minimum")};
    if (low != nullptr) {
      const auto where{side(*low)};
      if (where < 0 || (where == 0 && flagged("exclusiveMinimum"))) {
        return Verdict::No;
      }
    }

    const auto *high{bound("maximum")};
    if (high != nullptr) {
      const auto where{side(*high)};
      if (where > 0 || (where == 0 && flagged("exclusiveMaximum"))) {
        return Verdict::No;
      }
    }

    if (rank >= Rank::Draft6) {
      const auto *above{bound("exclusiveMinimum")};
      if (above != nullptr && side(*above) <= 0) {
        return Verdict::No;
      }

      const auto *below{bound("exclusiveMaximum")};
      if (below != nullptr && side(*below) >= 0) {
        return Verdict::No;
      }
    }
  }

  // Anything else beside the values, such as an object with properties of its
  // own, a reference, or a combination, is left to the rule beside them.
  static const std::vector<std::string> DECIDED{"type",
                                                "enum",
                                                "const",
                                                "minLength",
                                                "maxLength",
                                                "pattern",
                                                "minimum",
                                                "maximum",
                                                "exclusiveMinimum",
                                                "exclusiveMaximum",
                                                "title",
                                                "description",
                                                "default",
                                                "examples",
                                                "$comment",
                                                "deprecated",
                                                "$schema",
                                                "$id",
                                                "format"};
  if (subschema.is_object()) {
    for (const auto &entry_pair : subschema.as_object()) {
      if (std::find(DECIDED.cbegin(), DECIDED.cend(), entry_pair.first) ==
          DECIDED.cend()) {
        return Verdict::Unknown;
      }
    }
  }

  return Verdict::Yes;
}

// `not` forbids, and two prohibitions both hold: not this and not that is not
// (this or that).
auto forbid(JSON &value, JSON &&forbidden) -> void {
  if (!value.defines("not")) {
    value.assign("not", std::move(forbidden));
    return;
  }

  auto options{JSON::make_array()};
  options.push_back(value.at("not"));
  options.push_back(std::move(forbidden));
  auto choice{make_value("choice")};
  choice.assign("options", std::move(options));
  choice.assign("overlap", JSON{true});
  value.assign("not", std::move(choice));
}

auto also(JSON &value, JSON &&other) -> void {
  if (!value.defines("also")) {
    value.assign("also", JSON::make_array());
  }

  value.at("also").push_back(std::move(other));
}

auto condition(JSON &value, JSON &&entry) -> void {
  if (!value.defines("conditions")) {
    value.assign("conditions", JSON::make_array());
  }

  value.at("conditions").push_back(std::move(entry));
}

// An object that only says a property must be present, for the `when` of a
// condition made from a dependency keyword.
auto requires_property(const JSON::String &name) -> JSON {
  auto property{JSON::make_object()};
  property.assign("name", JSON{name});
  property.assign("required", JSON{true});
  auto properties{JSON::make_array()};
  properties.push_back(std::move(property));
  auto object{make_value("object")};
  object.assign("properties", std::move(properties));
  return object;
}

auto requires_properties(const JSON &names, const Pointer &pointer) -> JSON {
  if (!names.is_array()) {
    fail("A list of property names was expected", pointer);
  }

  if (names.empty()) {
    // Nothing becomes necessary, so there is nothing to say.
    return make_value("any");
  }

  auto properties{JSON::make_array()};
  for (const auto &name : names.as_array()) {
    if (!name.is_string()) {
      fail("A property name must be a string", pointer);
    }

    auto property{JSON::make_object()};
    property.assign("name", name);
    property.assign("required", JSON{true});
    properties.push_back(std::move(property));
  }

  auto object{make_value("object")};
  object.assign("properties", std::move(properties));
  return object;
}

auto string_facts(Context &context, JSON &value, const JSON &subschema,
                  const Pointer &pointer) -> void {
  copy_if_present(subschema, "format", value, "format");
  if (defines(subschema, "pattern")) {
    const auto &pattern{subschema.at("pattern")};
    if (!pattern.is_string()) {
      fail("The `pattern` keyword must be a regular expression", pointer);
    }

    value.assign("pattern", pattern);
  }

  count_of(subschema, "minLength", pointer);
  count_of(subschema, "maxLength", pointer);
  const auto length{bounds(subschema, "minLength", "maxLength")};
  if (length.has_value()) {
    value.assign("length", JSON{length.value()});
  }

  if (context.rank >= Rank::Draft7 && (defines(subschema, "contentMediaType") ||
                                       defines(subschema, "contentEncoding") ||
                                       defines(subschema, "contentSchema"))) {
    auto content{JSON::make_object()};
    copy_if_present(subschema, "contentMediaType", content, "mediaType");
    copy_if_present(subschema, "contentEncoding", content, "encoding");
    if (defines(subschema, "contentSchema") &&
        context.rank >= Rank::Draft2019) {
      content.assign("value", convert(context, subschema.at("contentSchema"),
                                      child(pointer, "contentSchema")));
    }

    if (!content.empty()) {
      value.assign("content", std::move(content));
    }
  }
}

auto number_facts(JSON &value, const JSON &subschema, const Pointer &pointer,
                  const Rank rank) -> void {
  copy_if_present(subschema, "format", value, "format");
  auto range{JSON::make_object()};
  if (defines(subschema, "minimum")) {
    range.assign("min", subschema.at("minimum"));
  }

  if (defines(subschema, "maximum")) {
    range.assign("max", subschema.at("maximum"));
  }

  // In Draft 4, the exclusive KEYWORDS are flags on the bounds; from Draft 6
  // they are bounds of their own.
  if (defines(subschema, "exclusiveMinimum")) {
    const auto &exclusive{subschema.at("exclusiveMinimum")};
    if (rank < Rank::Draft6) {
      if (!exclusive.is_boolean()) {
        fail("The `exclusiveMinimum` keyword must be a boolean in Draft 3 and "
             "Draft 4",
             pointer);
      }

      if (exclusive.to_boolean() && !range.defines("min")) {
        fail("The `exclusiveMinimum` keyword needs a `minimum` in Draft 3 and "
             "Draft 4",
             pointer);
      }

      if (exclusive.to_boolean()) {
        range.assign("minExclusive", JSON{true});
      }
    } else if (!range.defines("min")) {
      range.assign("min", exclusive);
      range.assign("minExclusive", JSON{true});
    } else {
      // Both bounds hold, so the tighter one is the rule.
      const auto &inclusive{range.at("min")};
      if (inclusive > exclusive) {
        range.erase(JSON::String{"minExclusive"});
      } else {
        range.assign("min", exclusive);
        range.assign("minExclusive", JSON{true});
      }
    }
  }

  if (defines(subschema, "exclusiveMaximum")) {
    const auto &exclusive{subschema.at("exclusiveMaximum")};
    if (rank < Rank::Draft6) {
      if (!exclusive.is_boolean()) {
        fail("The `exclusiveMaximum` keyword must be a boolean in Draft 3 and "
             "Draft 4",
             pointer);
      }

      if (exclusive.to_boolean() && !range.defines("max")) {
        fail("The `exclusiveMaximum` keyword needs a `maximum` in Draft 3 and "
             "Draft 4",
             pointer);
      }

      if (exclusive.to_boolean()) {
        range.assign("maxExclusive", JSON{true});
      }
    } else if (!range.defines("max")) {
      range.assign("max", exclusive);
      range.assign("maxExclusive", JSON{true});
    } else {
      const auto &inclusive{range.at("max")};
      if (inclusive < exclusive) {
        range.erase(JSON::String{"maxExclusive"});
      } else {
        range.assign("max", exclusive);
        range.assign("maxExclusive", JSON{true});
      }
    }
  }

  if (!range.empty()) {
    value.assign("range", std::move(range));
  }

  // Draft 3 calls the same rule `divisibleBy`.
  const auto *const step_keyword{rank == Rank::Draft3 ? "divisibleBy"
                                                      : "multipleOf"};
  if (defines(subschema, step_keyword)) {
    const auto &step{subschema.at(step_keyword)};
    if (!step.is_number() || !(JSON{static_cast<std::int64_t>(0)} < step)) {
      fail("The `multipleOf` keyword must be a number above zero", pointer,
           step_keyword);
    }

    value.assign("multipleOf", step);
  }
}

// Whether a key rule lets a name through. What it cannot decide, it allows,
// since the table may only state what is certain.
auto name_allowed(const JSON &keys, const JSON::String &name) -> bool {
  if (!keys.is_object()) {
    return true;
  }

  if (keys.at("kind").to_string() == "never") {
    return false;
  }

  if (keys.at("kind").to_string() == "enum" && keys.defines("values")) {
    for (const auto &allowed : keys.at("values").as_array()) {
      if (allowed.is_string() && allowed.to_string() == name) {
        return true;
      }
    }

    return false;
  }

  if (keys.defines("pattern") && keys.at("pattern").is_string() &&
      !sourcemeta::core::matches_if_valid(keys.at("pattern").to_string(),
                                          name)) {
    return false;
  }

  if (keys.defines("length")) {
    const auto &length{keys.at("length")};
    // Counted the way the specification counts, in characters.
    const JSON size{
        static_cast<std::int64_t>(sourcemeta::core::JSON::size(name))};
    if (length.defines("min") && length.at("min").is_number() &&
        size < length.at("min")) {
      return false;
    }

    if (length.defines("max") && length.at("max").is_number() &&
        length.at("max") < size) {
      return false;
    }
  }

  return true;
}

// A part of a subschema that applies to the same data in place, such as a
// member of `allOf` or where a reference lands. It applies always, or only
// when a branch or a condition happens to match.
struct Part {
  Pointer pointer;
  bool always;
};

auto parts_of(const Context &context, const JSON &subschema,
              const Pointer &pointer, const Rank rank) -> std::vector<Part> {
  std::vector<Part> result;
  if (!subschema.is_object()) {
    return result;
  }

  if (defines(subschema, "$ref") && subschema.at("$ref").is_string()) {
    std::string destination;
    const auto target{landing_of(context, pointer, "$ref", destination)};
    if (target.has_value()) {
      result.push_back({.pointer = target.value(), .always = true});
    }

    // Before 2019-09, a reference stands alone.
    if (rank < Rank::Draft2019) {
      return result;
    }
  }

  for (const std::string keyword : {"$dynamicRef", "$recursiveRef"}) {
    if (!defines(subschema, keyword) || !subschema.at(keyword).is_string() ||
        (keyword == "$dynamicRef" && rank < Rank::Draft2020) ||
        (keyword == "$recursiveRef" && rank != Rank::Draft2019)) {
      continue;
    }

    const auto targets{dynamic_landings(context, pointer, keyword)};
    for (const auto &target : targets) {
      result.push_back({.pointer = target, .always = targets.size() == 1});
    }
  }

  const auto members = [&](const std::string &keyword, const bool always) {
    if (!defines(subschema, keyword)) {
      return;
    }

    const auto &list{subschema.at(keyword)};
    if (list.is_array()) {
      for (std::size_t index = 0; index < list.array_size(); index++) {
        if (list.at(index).is_object()) {
          result.push_back({.pointer = child(child(pointer, keyword), index),
                            .always = always});
        }
      }
    } else if (list.is_object() && keyword != "anyOf" && keyword != "oneOf" &&
               keyword != "allOf") {
      result.push_back({.pointer = child(pointer, keyword), .always = always});
    }
  };

  if (rank == Rank::Draft3) {
    members("extends", true);
    members("type", false);
    return result;
  }

  members("allOf", true);
  members("anyOf", false);
  members("oneOf", false);
  if (rank >= Rank::Draft7) {
    for (const std::string keyword : {"if", "then", "else"}) {
      if (defines(subschema, keyword) && subschema.at(keyword).is_object()) {
        result.push_back({.pointer = child(pointer, keyword), .always = false});
      }
    }
  }

  for (const std::string dependencies : {"dependentSchemas", "dependencies"}) {
    if (dependencies == "dependentSchemas" && rank < Rank::Draft2019) {
      continue;
    }

    if (defines(subschema, dependencies) &&
        subschema.at(dependencies).is_object()) {
      for (const auto &entry : subschema.at(dependencies).as_object()) {
        if (entry.second.is_object()) {
          result.push_back(
              {.pointer = child(child(pointer, dependencies), entry.first),
               .always = false});
        }
      }
    }
  }

  return result;
}

// What the parts of a subschema that apply in place look at, as deep as they
// go: the properties they name, and the items they reach.
struct Reach {
  std::set<JSON::String> names;
  std::set<JSON::String> patterns;
  // Whether a part that always applies looks at every property.
  bool every_property{false};
  // Whether any part, even one that only sometimes applies, says what every
  // property it does not name holds, which names every property.
  bool names_every_property{false};
  // Whether a part that always applies looks at every item.
  bool every_item{false};
  // How many items at the start the parts that always apply look at.
  std::size_t prefix{0};
  // What the parts that always apply say some items contain. From 2020-12,
  // such an item counts as looked at.
  std::vector<Pointer> contains;
  // Whether a part that only applies sometimes looks at items.
  bool items_sometimes{false};
};

auto reach_of(const Context &context, const JSON &subschema,
              const Pointer &pointer, const Rank rank, const bool always,
              std::set<std::string> &seen, Reach &reach) -> void {
  for (const auto &part : parts_of(context, subschema, pointer, rank)) {
    const auto applies{always && part.always};
    // The same place may be reached both always and only sometimes, and what
    // it says differs between the two.
    if (!seen.insert(pointer_string(part.pointer) + (applies ? "!" : "?"))
             .second) {
      continue;
    }

    const auto &member{sourcemeta::core::get(context.root, part.pointer)};
    if (!member.is_object()) {
      continue;
    }

    const auto member_rank{rank_at(context, part.pointer)};
    for (const auto *keyword : {"properties", "patternProperties"}) {
      if (defines(member, keyword) && member.at(keyword).is_object()) {
        for (const auto &entry : member.at(keyword).as_object()) {
          (std::string_view{keyword} == "properties" ? reach.names
                                                     : reach.patterns)
              .insert(entry.first);
        }
      }
    }

    if (applies && (defines(member, "additionalProperties") ||
                    (member_rank >= Rank::Draft2019 &&
                     defines(member, "unevaluatedProperties")))) {
      reach.every_property = true;
    }

    for (const auto *keyword :
         {"additionalProperties", "unevaluatedProperties"}) {
      if (defines(member, keyword) &&
          !(member.at(keyword).is_boolean() &&
            !member.at(keyword).to_boolean()) &&
          (std::string_view{keyword} == "additionalProperties" ||
           member_rank >= Rank::Draft2019)) {
        reach.names_every_property = true;
      }
    }

    // What this part looks at among the items.
    std::size_t prefix{0};
    auto every{false};
    auto looks{false};
    const auto *const list{member_rank >= Rank::Draft2020 ? "prefixItems"
                                                          : "items"};
    if (defines(member, list) && member.at(list).is_array()) {
      prefix = member.at(list).array_size();
      looks = true;
      if (member_rank < Rank::Draft2020 && defines(member, "additionalItems")) {
        every = true;
      }
    }

    if (defines(member, "items") &&
        (member_rank >= Rank::Draft2020 || !member.at("items").is_array())) {
      every = true;
    }

    if (member_rank >= Rank::Draft2019 && defines(member, "unevaluatedItems")) {
      every = true;
    }

    const auto contains{member_rank >= Rank::Draft2020 &&
                        defines(member, "contains")};
    looks = looks || every || contains;
    if (looks && !applies) {
      reach.items_sometimes = true;
    } else if (looks) {
      reach.prefix = std::max(reach.prefix, prefix);
      reach.every_item = reach.every_item || every;
      if (contains) {
        reach.contains.push_back(child(part.pointer, "contains"));
      }
    }

    reach_of(context, member, part.pointer, member_rank, applies, seen, reach);
  }
}

auto reach_of(const Context &context, const JSON &subschema,
              const Pointer &pointer) -> Reach {
  Reach reach;
  std::set<std::string> seen;
  reach_of(context, subschema, pointer, context.rank, true, seen, reach);
  return reach;
}

// Escapes a name so a regular expression matches it and nothing else.
auto literally(const JSON::String &name) -> JSON::String {
  JSON::String result;
  for (const auto character : name) {
    if (JSON::String{"\\^$.|?*+()[]{}/"}.find(character) !=
        JSON::String::npos) {
      result.push_back('\\');
    }

    result.push_back(character);
  }

  return result;
}

auto object_facts(Context &context, JSON &value, const JSON &subschema,
                  const Pointer &pointer) -> void {
  std::set<JSON::String> required;
  if (defines(subschema, "required") && context.rank >= Rank::Draft4) {
    const auto &names{subschema.at("required")};
    if (!names.is_array()) {
      fail("The `required` keyword must be a list of property names", pointer);
    }

    for (const auto &name : names.as_array()) {
      if (!name.is_string()) {
        fail("A required property name must be a string", pointer);
      }

      if (!required.insert(name.to_string()).second) {
        fail("The `required` keyword names this property twice", pointer,
             name.to_string());
      }
    }
  }

  // Draft 3 says a property is required on the property itself.
  if (defines(subschema, "properties") && context.rank == Rank::Draft3 &&
      subschema.at("properties").is_object()) {
    for (const auto &entry : subschema.at("properties").as_object()) {
      if (defines(entry.second, "required") &&
          entry.second.at("required").is_boolean() &&
          entry.second.at("required").to_boolean()) {
        required.insert(entry.first);
      }
    }
  }

  std::vector<JSON> properties;
  std::map<JSON::String, std::size_t> position;
  const auto property_named = [&](const JSON::String &name) -> JSON & {
    const auto match{position.find(name)};
    if (match != position.cend()) {
      return properties.at(match->second);
    }

    auto property{JSON::make_object()};
    property.assign("name", JSON{name});
    if (required.contains(name)) {
      property.assign("required", JSON{true});
    }

    position.emplace(name, properties.size());
    properties.push_back(std::move(property));
    return properties.back();
  };

  std::set<JSON::String> own;
  if (defines(subschema, "properties")) {
    const auto &described{subschema.at("properties")};
    if (!described.is_object()) {
      fail("The `properties` keyword must be an object", pointer);
    }

    for (const auto &entry : described.as_object()) {
      property_named(entry.first)
          .assign("value",
                  convert(context, entry.second,
                          child(child(pointer, "properties"), entry.first)));
      own.insert(entry.first);
    }
  }

  // A name that is required and described nowhere is still a property a reader
  // must know about.
  for (const auto &name : required) {
    property_named(name);
  }

  std::vector<JSON::String> own_patterns;
  auto pattern_properties{JSON::make_array()};
  if (defines(subschema, "patternProperties")) {
    const auto &patterns{subschema.at("patternProperties")};
    if (!patterns.is_object()) {
      fail("The `patternProperties` keyword must be an object", pointer);
    }

    for (const auto &entry : patterns.as_object()) {
      auto pattern{JSON::make_object()};
      pattern.assign("pattern", JSON{entry.first});
      pattern.assign("value", convert(context, entry.second,
                                      child(child(pointer, "patternProperties"),
                                            entry.first)));
      own_patterns.push_back(entry.first);
      pattern_properties.push_back(std::move(pattern));
    }
  }

  // The names that make other properties necessary, or bring in a schema.
  std::set<JSON::String> triggers;
  for (const auto *keyword :
       {"dependentRequired", "dependentSchemas", "dependencies"}) {
    if (defines(subschema, keyword) && subschema.at(keyword).is_object()) {
      for (const auto &entry : subschema.at(keyword).as_object()) {
        triggers.insert(entry.first);
      }
    }
  }

  // What every property that is not named holds, if anything is said.
  std::optional<JSON> other_properties;
  auto closed{false};
  if (defines(subschema, "additionalProperties")) {
    const auto &additional{subschema.at("additionalProperties")};
    if (additional.is_boolean() && additional.to_boolean()) {
      other_properties = make_value("any");
    } else {
      const auto other{additional.is_boolean()
                           ? make_value("never")
                           : convert(context, additional,
                                     child(pointer, "additionalProperties"))};
      // This keyword only counts the properties this subschema itself names.
      // A name that only a member of `allOf`, a branch, a condition or a
      // reference uses is held to it as well, and the format would otherwise
      // count that name as named.
      const auto reach{reach_of(context, subschema, pointer)};
      const auto own_match = [&](const JSON::String &name) {
        return std::any_of(own_patterns.cbegin(), own_patterns.cend(),
                           [&name](const auto &pattern) {
                             return sourcemeta::core::matches_if_valid(pattern,
                                                                       name);
                           });
      };

      std::set<JSON::String> held{reach.names};
      held.insert(required.cbegin(), required.cend());
      held.insert(triggers.cbegin(), triggers.cend());
      for (const auto &name : held) {
        if (own.contains(name) || own_match(name)) {
          continue;
        }

        auto &property{property_named(name)};
        if (property.defines("value")) {
          also(property.at("value"), JSON{other});
        } else {
          property.assign("value", other);
        }
      }

      // A name this subschema names itself, or matches by a pattern of its
      // own, is not held to it, so what is held leaves those names out.
      JSON::String excluded;
      if (!own.empty()) {
        excluded += "(?!(?:";
        auto first{true};
        for (const auto &name : own) {
          excluded += first ? "" : "|";
          excluded += literally(name);
          first = false;
        }

        excluded += ")$)";
      }

      for (const auto &own_pattern : own_patterns) {
        excluded += "(?![\\s\\S]*?(?:";
        excluded += own_pattern;
        excluded += "))";
      }

      const auto held_by = [&](JSON::String pattern) {
        auto entry{JSON::make_object()};
        entry.assign("pattern", JSON{std::move(pattern)});
        entry.assign("value", other);
        pattern_properties.push_back(std::move(entry));
      };

      for (const auto &pattern : reach.patterns) {
        if (std::find(own_patterns.cbegin(), own_patterns.cend(), pattern) !=
            own_patterns.cend()) {
          continue;
        }

        if (excluded.empty()) {
          held_by(pattern);
        } else {
          JSON::String written{"^"};
          written += excluded;
          written += "[\\s\\S]*?(?:";
          written += pattern;
          written += ")";
          held_by(std::move(written));
        }
      }

      // A part that says what every property it does not name holds names
      // every property, so the format would count them all as named. Every
      // name this subschema does not name itself is held here outright.
      if (reach.names_every_property) {
        held_by("^" + excluded);
      }

      if (additional.is_boolean()) {
        closed = true;
      } else {
        other_properties = other;
      }
    }
  } else if (defines(subschema, "unevaluatedProperties") &&
             context.rank >= Rank::Draft2019) {
    // A property counts as looked at when a part of the subschema that applies
    // to the data names it, which is what the format means by a named
    // property. So this keyword says just what `closed` and `otherProperties`
    // say, unless a part that always applies already looks at every property.
    const auto &unevaluated{subschema.at("unevaluatedProperties")};
    const auto reach{reach_of(context, subschema, pointer)};
    if (!reach.every_property &&
        !(unevaluated.is_boolean() && unevaluated.to_boolean())) {
      if (unevaluated.is_boolean()) {
        closed = true;
      } else {
        other_properties = convert(context, unevaluated,
                                   child(pointer, "unevaluatedProperties"));
      }
    }
  }

  if (!properties.empty()) {
    auto entries{JSON::make_array()};
    for (auto &property : properties) {
      entries.push_back(std::move(property));
    }

    value.assign("properties", std::move(entries));
  }

  if (!pattern_properties.empty()) {
    value.assign("patternProperties", std::move(pattern_properties));
  }

  if (closed) {
    value.assign("closed", JSON{true});
  } else if (other_properties.has_value()) {
    value.assign("otherProperties", std::move(other_properties).value());
  }

  if (defines(subschema, "propertyNames") && context.rank >= Rank::Draft6) {
    value.assign("keys", convert(context, subschema.at("propertyNames"),
                                 child(pointer, "propertyNames")));
  }

  // A property whose name also matches a pattern is held to both, so the table
  // says both of them rather than only the first.
  if (value.defines("properties") && value.defines("patternProperties")) {
    for (auto &property : value.at("properties").as_array()) {
      if (!property.defines("value")) {
        continue;
      }

      for (const auto &entry : value.at("patternProperties").as_array()) {
        if (!sourcemeta::core::matches_if_valid(
                entry.at("pattern").to_string(),
                property.at("name").to_string())) {
          continue;
        }

        also(property.at("value"), JSON{entry.at("value")});
      }
    }
  }

  // A name the key rule does not allow can never appear, whatever a property
  // says it would hold.
  if (value.defines("properties") && value.defines("keys")) {
    const auto &keys{value.at("keys")};
    for (auto &property : value.at("properties").as_array()) {
      if (!name_allowed(keys, property.at("name").to_string())) {
        property.assign("value", make_value("never"));
      }
    }
  }

  if (context.rank >= Rank::Draft4) {
    count_of(subschema, "minProperties", pointer);
    count_of(subschema, "maxProperties", pointer);
    const auto count{bounds(subschema, "minProperties", "maxProperties")};
    if (count.has_value()) {
      value.assign("propertyCount", JSON{count.value()});
    }
  }

  // One property being present making others necessary is a condition.
  if (defines(subschema, "dependentRequired") &&
      context.rank >= Rank::Draft2019) {
    const auto &dependencies{subschema.at("dependentRequired")};
    if (!dependencies.is_object()) {
      fail("The `dependentRequired` keyword must be an object", pointer);
    }

    for (const auto &entry : dependencies.as_object()) {
      auto entry_condition{JSON::make_object()};
      entry_condition.assign("when", requires_property(entry.first));
      entry_condition.assign(
          "then", requires_properties(entry.second,
                                      child(pointer, "dependentRequired")));
      condition(value, std::move(entry_condition));
    }
  }

  if (defines(subschema, "dependentSchemas") &&
      context.rank >= Rank::Draft2019) {
    const auto &dependencies{subschema.at("dependentSchemas")};
    if (!dependencies.is_object()) {
      fail("The `dependentSchemas` keyword must be an object", pointer);
    }

    for (const auto &entry : dependencies.as_object()) {
      auto entry_condition{JSON::make_object()};
      entry_condition.assign("when", requires_property(entry.first));
      entry_condition.assign(
          "then",
          convert(context, entry.second,
                  child(child(pointer, "dependentSchemas"), entry.first)));
      condition(value, std::move(entry_condition));
    }
  }

  // Before 2019-09, both of the above were one keyword. Later dialects drop it,
  // but Blaze still holds data to it for the sake of older schemas, so it is
  // described wherever it is written.
  if (defines(subschema, "dependencies")) {
    const auto &dependencies{subschema.at("dependencies")};
    if (!dependencies.is_object()) {
      fail("The `dependencies` keyword must be an object", pointer);
    }

    for (const auto &entry : dependencies.as_object()) {
      auto entry_condition{JSON::make_object()};
      entry_condition.assign("when", requires_property(entry.first));
      if (entry.second.is_array()) {
        entry_condition.assign(
            "then",
            requires_properties(entry.second, child(pointer, "dependencies")));
      } else if (entry.second.is_string() && context.rank == Rank::Draft3) {
        // Draft 3 may name the one property it makes necessary on its own.
        auto names{JSON::make_array()};
        names.push_back(entry.second);
        entry_condition.assign(
            "then", requires_properties(names, child(pointer, "dependencies")));
      } else {
        entry_condition.assign(
            "then",
            convert(context, entry.second,
                    child(child(pointer, "dependencies"), entry.first)));
      }

      condition(value, std::move(entry_condition));
    }
  }
}

auto array_facts(Context &context, JSON &value, const JSON &subschema,
                 const Pointer &pointer) -> void {
  if (defines(subschema, "prefixItems") && context.rank >= Rank::Draft2020) {
    const auto &slots{subschema.at("prefixItems")};
    if (!slots.is_array()) {
      fail("The `prefixItems` keyword must be a list of schemas", pointer);
    }

    auto entries{JSON::make_array()};
    for (std::size_t index = 0; index < slots.array_size(); index++) {
      entries.push_back(convert(context, slots.at(index),
                                child(child(pointer, "prefixItems"), index)));
    }

    value.assign("slots", std::move(entries));
  }

  // Whether this subschema itself says what every entry after the slots holds.
  auto rest_said{false};
  if (defines(subschema, "items")) {
    const auto &items{subschema.at("items")};
    if (items.is_array()) {
      if (context.rank >= Rank::Draft2020) {
        fail("The `items` keyword must be a schema in 2020-12, not a list",
             pointer);
      }

      auto entries{JSON::make_array()};
      for (std::size_t index = 0; index < items.array_size(); index++) {
        entries.push_back(convert(context, items.at(index),
                                  child(child(pointer, "items"), index)));
      }

      value.assign("slots", std::move(entries));
      if (defines(subschema, "additionalItems")) {
        value.assign("item", convert(context, subschema.at("additionalItems"),
                                     child(pointer, "additionalItems")));
        rest_said = true;
      }
    } else {
      value.assign("item", convert(context, items, child(pointer, "items")));
      rest_said = true;
    }
  }

  // An entry counts as looked at when this subschema, or a part of it that
  // applies in place, says what it holds.
  if (defines(subschema, "unevaluatedItems") &&
      context.rank >= Rank::Draft2019 && !rest_said) {
    const auto reach{reach_of(context, subschema, pointer)};
    if (reach.items_sometimes) {
      fail("This keyword beside a part that only sometimes applies, and looks "
           "at entries, depends on which part matched, which the format "
           "cannot state exactly",
           pointer, "unevaluatedItems");
    }

    const auto &unevaluated{subschema.at("unevaluatedItems")};
    if (!reach.every_item &&
        !(unevaluated.is_boolean() && unevaluated.to_boolean())) {
      // The entries at the start that some part looks at are not held to it,
      // so they become slots that say nothing of their own.
      if (!value.defines("slots") && reach.prefix > 0) {
        value.assign("slots", JSON::make_array());
      }

      while (value.defines("slots") &&
             value.at("slots").array_size() < reach.prefix) {
        value.at("slots").push_back(make_value("any"));
      }

      std::vector<JSON> options;
      auto rest{
          convert(context, unevaluated, child(pointer, "unevaluatedItems"))};
      if (rest.at("kind").to_string() != "never" || rest.size() > 1) {
        options.push_back(std::move(rest));
      }

      // From 2020-12, an entry that matches `contains` counts as looked at.
      std::vector<Pointer> contains{reach.contains};
      if (context.rank >= Rank::Draft2020 && defines(subschema, "contains")) {
        contains.push_back(child(pointer, "contains"));
      }

      for (const auto &place : contains) {
        options.push_back(convert(
            context, sourcemeta::core::get(context.root, place), place));
      }

      if (options.empty()) {
        value.assign("item", make_value("never"));
      } else if (options.size() == 1) {
        value.assign("item", std::move(options.front()));
      } else {
        auto entries{JSON::make_array()};
        for (auto &option : options) {
          entries.push_back(std::move(option));
        }

        auto choice{make_value("choice")};
        choice.assign("options", std::move(entries));
        choice.assign("overlap", JSON{true});
        value.assign("item", std::move(choice));
      }
    }
  }

  count_of(subschema, "minItems", pointer);
  count_of(subschema, "maxItems", pointer);
  const auto length{bounds(subschema, "minItems", "maxItems")};
  if (length.has_value()) {
    value.assign("length", JSON{length.value()});
  }

  if (defines(subschema, "uniqueItems") &&
      subschema.at("uniqueItems").is_boolean() &&
      subschema.at("uniqueItems").to_boolean()) {
    value.assign("unique", JSON{true});
  }

  if (defines(subschema, "contains") && context.rank >= Rank::Draft6) {
    auto contains{JSON::make_object()};
    contains.assign("value", convert(context, subschema.at("contains"),
                                     child(pointer, "contains")));
    count_of(subschema, "minContains", pointer);
    count_of(subschema, "maxContains", pointer);
    if (defines(subschema, "minContains") && context.rank >= Rank::Draft2019) {
      contains.assign("min", subschema.at("minContains"));
    } else {
      contains.assign("min", JSON{static_cast<std::int64_t>(1)});
    }

    if (defines(subschema, "maxContains") && context.rank >= Rank::Draft2019) {
      contains.assign("max", subschema.at("maxContains"));
    }

    value.assign("contains", std::move(contains));
  }
}

auto kind_of(const JSON::String &name, const Pointer &pointer) -> std::string {
  if (name == "string" || name == "number" || name == "integer" ||
      name == "boolean" || name == "object" || name == "array" ||
      name == "null") {
    return name;
  }

  fail("The `type` keyword names something that is not a JSON type", pointer,
       name);
}

// The types the KEYWORDS of a subschema are about, when it does not say.
auto inferred_kinds(const JSON &subschema, const Rank rank)
    -> std::vector<std::string> {
  std::vector<std::string> string_keywords{"minLength", "maxLength", "pattern"};
  std::vector<std::string> number_keywords{
      "minimum", "maximum", "exclusiveMinimum", "exclusiveMaximum"};
  std::vector<std::string> object_keywords{"properties", "patternProperties",
                                           "additionalProperties"};
  std::vector<std::string> array_keywords{
      "items", "additionalItems", "minItems", "maxItems", "uniqueItems"};
  // Draft 3 marks a property required on the property, with a boolean that
  // says nothing about the kind of the value.
  if (rank == Rank::Draft3) {
    number_keywords.emplace_back("divisibleBy");
  } else {
    number_keywords.emplace_back("multipleOf");
    object_keywords.emplace_back("required");
    object_keywords.emplace_back("minProperties");
    object_keywords.emplace_back("maxProperties");
  }

  if (rank >= Rank::Draft6) {
    object_keywords.emplace_back("propertyNames");
    array_keywords.emplace_back("contains");
  }

  if (rank >= Rank::Draft7) {
    string_keywords.emplace_back("contentMediaType");
    string_keywords.emplace_back("contentEncoding");
  }

  if (rank >= Rank::Draft2019) {
    string_keywords.emplace_back("contentSchema");
    object_keywords.emplace_back("dependentRequired");
    object_keywords.emplace_back("dependentSchemas");
    object_keywords.emplace_back("unevaluatedProperties");
    array_keywords.emplace_back("minContains");
    array_keywords.emplace_back("maxContains");
    array_keywords.emplace_back("unevaluatedItems");
  }

  object_keywords.emplace_back("dependencies");

  if (rank >= Rank::Draft2020) {
    array_keywords.emplace_back("prefixItems");
  }

  const auto about = [&subschema](const std::vector<std::string> &group) {
    return std::any_of(group.cbegin(), group.cend(),
                       [&subschema](const auto &keyword) {
                         return defines(subschema, keyword);
                       });
  };

  std::vector<std::string> result;
  // A label from the source language is about text, unless it names a way of
  // writing a number.
  static const std::vector<std::string> NUMBER_FORMATS{
      "int32", "int64", "float", "double", "integer", "number"};
  const auto labelled_number{
      defines(subschema, "format") && subschema.at("format").is_string() &&
      std::find(NUMBER_FORMATS.cbegin(), NUMBER_FORMATS.cend(),
                subschema.at("format").to_string()) != NUMBER_FORMATS.cend()};
  const auto labelled_text{defines(subschema, "format") &&
                           subschema.at("format").is_string() &&
                           !labelled_number};

  if (about(string_keywords) || labelled_text) {
    result.emplace_back("string");
  }

  if (about(number_keywords) || labelled_number) {
    result.emplace_back("number");
  }

  if (about(object_keywords)) {
    result.emplace_back("object");
  }

  if (about(array_keywords)) {
    result.emplace_back("array");
  }

  return result;
}

auto fill_kind(Context &context, JSON &value, const JSON &subschema,
               const Pointer &pointer) -> void {
  const auto &kind{value.at("kind").to_string()};
  if (kind == "string") {
    string_facts(context, value, subschema, pointer);
  } else if (kind == "number" || kind == "integer") {
    number_facts(value, subschema, pointer, context.rank);
  } else if (kind == "object") {
    object_facts(context, value, subschema, pointer);
  } else if (kind == "array") {
    array_facts(context, value, subschema, pointer);
  }
}

// What the reference keywords of a subschema lead to, one value for each.
auto references_of(Context &context, const JSON &subschema,
                   const Pointer &pointer) -> std::vector<JSON> {
  std::vector<JSON> result;
  for (const std::string keyword : {"$ref", "$dynamicRef", "$recursiveRef"}) {
    if (!defines(subschema, keyword) ||
        (keyword == "$dynamicRef" && context.rank < Rank::Draft2020) ||
        (keyword == "$recursiveRef" && context.rank != Rank::Draft2019)) {
      continue;
    }

    if (!subschema.at(keyword).is_string()) {
      fail("This keyword must be a string", pointer, keyword);
    }

    // A dynamic reference whose target cannot change is a plain one.
    if (keyword == "$ref" || !context.dynamic_references.contains(
                                 pointer_string(child(pointer, keyword)))) {
      std::string destination;
      const auto target{landing_of(context, pointer, keyword, destination)};
      if (target.has_value()) {
        result.push_back(shape_at(context, target.value()));
      } else {
        // Something outside this document, which a reader follows elsewhere.
        auto value{make_value("external")};
        value.assign("href", JSON{destination});
        result.push_back(std::move(value));
      }

      continue;
    }

    const auto targets{dynamic_landings(context, pointer, keyword)};
    if (targets.empty()) {
      // Something outside this document, which a reader follows elsewhere.
      auto value{make_value("external")};
      value.assign("href", JSON{context.dynamic_references.at(
                               pointer_string(child(pointer, keyword)))});
      result.push_back(std::move(value));
    } else if (targets.size() == 1) {
      result.push_back(shape_at(context, targets.front()));
    } else if (!targets.empty()) {
      auto options{JSON::make_array()};
      for (const auto &target : targets) {
        options.push_back(shape_at(context, target));
      }

      auto choice{make_value("choice")};
      choice.assign("options", std::move(options));
      choice.assign("overlap", JSON{true});
      result.push_back(std::move(choice));
    }
  }

  return result;
}

auto annotations(JSON &value, const JSON &subschema, const Rank rank) -> void {
  copy_if_present(subschema, "title", value, "title");
  copy_if_present(subschema, "description", value, "description");
  copy_if_present(subschema, "default", value, "default");
  if (rank >= Rank::Draft6 && defines(subschema, "examples") &&
      subschema.at("examples").is_array() &&
      !subschema.at("examples").empty()) {
    value.assign("examples", subschema.at("examples"));
  }

  if (rank >= Rank::Draft2019 && defines(subschema, "deprecated") &&
      subschema.at("deprecated").is_boolean() &&
      subschema.at("deprecated").to_boolean()) {
    value.assign("deprecated", JSON{true});
  }

  const auto read_only{rank >= Rank::Draft7 && defines(subschema, "readOnly") &&
                       subschema.at("readOnly").is_boolean() &&
                       subschema.at("readOnly").to_boolean()};
  const auto write_only{rank >= Rank::Draft7 &&
                        defines(subschema, "writeOnly") &&
                        subschema.at("writeOnly").is_boolean() &&
                        subschema.at("writeOnly").to_boolean()};
  // Both at once says nothing a reader can act on, so it says nothing here.
  if (read_only && !write_only) {
    value.assign("access", JSON{std::string{"read"}});
  } else if (write_only && !read_only) {
    value.assign("access", JSON{std::string{"write"}});
  }
}

auto branches(Context &context, JSON &value, const JSON &subschema,
              const Pointer &pointer, const std::string &keyword,
              const bool overlap) -> void {
  if (!defines(subschema, keyword)) {
    return;
  }

  const auto &members{subschema.at(keyword)};
  if (!members.is_array() || members.empty()) {
    fail("This keyword must be a non-empty list of schemas", pointer, keyword);
  }

  std::vector<JSON> options;
  options.reserve(members.array_size());
  for (std::size_t index = 0; index < members.array_size(); index++) {
    options.emplace_back(convert(context, members.at(index),
                                 child(child(pointer, keyword), index)));
  }

  // A form that is only null says the value may be null instead.
  const auto only_null = [](const JSON &option) {
    return option.at("kind").to_string() == "null" && option.size() == 1;
  };

  if (options.size() > 1) {
    const auto nulls{
        std::count_if(options.cbegin(), options.cend(), only_null)};
    const auto others{std::count_if(
        options.cbegin(), options.cend(), [&](const auto &option) {
          return !only_null(option) && accepts_null(option);
        })};
    if (nulls == 1 && others == 0) {
      options.erase(std::remove_if(options.begin(), options.end(), only_null),
                    options.end());
      value.assign("nullable", JSON{true});
    }
  }

  if (options.empty()) {
    return;
  }

  if (options.size() == 1) {
    // One form is not a choice: it is simply another thing that must hold.
    also(value, std::move(options.front()));
    return;
  }

  auto choice{make_value("choice")};
  auto entries{JSON::make_array()};
  for (auto &option : options) {
    entries.push_back(std::move(option));
  }

  choice.assign("options", std::move(entries));
  if (overlap) {
    choice.assign("overlap", JSON{true});
  }

  also(value, std::move(choice));
}

auto conditions(Context &context, JSON &value, const JSON &subschema,
                const Pointer &pointer) -> void {
  if (!defines(subschema, "if") || context.rank < Rank::Draft7) {
    return;
  }

  if (!defines(subschema, "then") && !defines(subschema, "else")) {
    // Neither branch says anything, so neither does the condition.
    return;
  }

  auto entry{JSON::make_object()};
  entry.assign("when",
               convert(context, subschema.at("if"), child(pointer, "if")));
  if (defines(subschema, "then")) {
    entry.assign(
        "then", convert(context, subschema.at("then"), child(pointer, "then")));
  }

  if (defines(subschema, "else")) {
    entry.assign("otherwise", convert(context, subschema.at("else"),
                                      child(pointer, "else")));
  }

  condition(value, std::move(entry));
}

/// Inside one subschema, the conversion is one level deeper, and reads that
// subschema in the dialect in effect where it sits.
class Visit {
public:
  Visit(Context &context, const Pointer &pointer)
      : context_{context}, previous_{context.rank} {
    this->context_.depth += 1;
    if (this->context_.depth > MAXIMUM_DEPTH) {
      fail("This schema nests deeper than this module describes", pointer);
    }

    this->context_.rank = rank_at(context, pointer);
  }

  ~Visit() {
    this->context_.depth -= 1;
    this->context_.rank = this->previous_;
  }

  Visit(const Visit &) = delete;
  auto operator=(const Visit &) -> Visit & = delete;
  Visit(Visit &&) = delete;
  auto operator=(Visit &&) -> Visit & = delete;

private:
  Context &context_;
  Rank previous_;
};

// Whether a Draft 3 `type` or `disallow` names every type, with `any`.
auto names_any(const JSON &types) -> bool {
  const auto any = [](const JSON &entry) {
    return entry.is_string() && entry.to_string() == "any";
  };

  return any(types) ||
         (types.is_array() &&
          std::any_of(types.as_array().cbegin(), types.as_array().cend(), any));
}

// Whether a Draft 3 `type` or `disallow` holds a whole schema.
auto holds_schemas(const JSON &types) -> bool {
  return types.is_array() &&
         std::any_of(types.as_array().cbegin(), types.as_array().cend(),
                     [](const auto &entry) { return entry.is_object(); });
}

// A Draft 3 list of types, which may hold whole schemas as well as names, as
// the forms a value may take.
auto type_options(Context &context, const JSON &types, const Pointer &pointer,
                  const std::string &keyword) -> JSON {
  std::vector<JSON> options;
  const auto one = [&](const JSON &entry, const Pointer &where) {
    if (entry.is_string()) {
      options.push_back(entry.to_string() == "any"
                            ? make_value("any")
                            : make_value(kind_of(entry.to_string(), pointer)));
    } else if (entry.is_object()) {
      options.push_back(convert(context, entry, where));
    } else {
      fail("The `type` keyword must name types as strings", pointer);
    }
  };

  if (types.is_array()) {
    for (std::size_t index = 0; index < types.array_size(); index++) {
      one(types.at(index), child(child(pointer, keyword), index));
    }
  } else {
    one(types, child(pointer, keyword));
  }

  if (options.size() == 1) {
    return std::move(options.front());
  }

  auto entries{JSON::make_array()};
  for (auto &option : options) {
    entries.push_back(std::move(option));
  }

  auto choice{make_value("choice")};
  choice.assign("options", std::move(entries));
  choice.assign("overlap", JSON{true});
  return choice;
}

// The keywords Draft 3 has and later drafts spell otherwise: `extends` for
// `allOf`, `disallow` for `not`, and a `type` that holds whole schemas for
// `anyOf`.
auto draft3_facts(Context &context, JSON &value, const JSON &subschema,
                  const Pointer &pointer) -> void {
  if (defines(subschema, "type") && holds_schemas(subschema.at("type")) &&
      !names_any(subschema.at("type"))) {
    also(value, type_options(context, subschema.at("type"), pointer, "type"));
  }

  if (defines(subschema, "extends")) {
    const auto &extends{subschema.at("extends")};
    if (extends.is_array()) {
      for (std::size_t index = 0; index < extends.array_size(); index++) {
        also(value, convert(context, extends.at(index),
                            child(child(pointer, "extends"), index)));
      }
    } else {
      also(value, convert(context, extends, child(pointer, "extends")));
    }
  }

  if (defines(subschema, "disallow")) {
    forbid(value, type_options(context, subschema.at("disallow"), pointer,
                               "disallow"));
  }
}

auto convert(Context &context, const JSON &subschema, const Pointer &pointer)
    -> JSON {
  const Visit visit{context, pointer};
  if (subschema.is_boolean()) {
    return make_value(subschema.to_boolean() ? "any" : "never");
  }

  if (!subschema.is_object()) {
    fail("A schema must be an object or a boolean", pointer);
  }

  auto references{references_of(context, subschema, pointer)};
  // Before 2019-09, a reference stands alone: its siblings say nothing.
  if (defines(subschema, "$ref") && context.rank < Rank::Draft2019) {
    return std::move(references.front());
  }

  // A Draft 3 `type` may allow every type, which says nothing, or hold whole
  // schemas, which makes it one of several forms rather than a list of names.
  const auto draft3_type{
      context.rank == Rank::Draft3 && defines(subschema, "type") &&
      (names_any(subschema.at("type")) || holds_schemas(subschema.at("type")))};
  if (context.rank == Rank::Draft3 && defines(subschema, "type") &&
      subschema.at("type").is_array() && subschema.at("type").empty()) {
    // Draft 3 allows a list of no types, which no value is.
    return make_value("never");
  }

  JSON value{JSON::make_object()};
  std::vector<std::string> kinds;
  if (defines(subschema, "type") && !draft3_type) {
    const auto &type{subschema.at("type")};
    if (type.is_string()) {
      kinds.push_back(kind_of(type.to_string(), pointer));
    } else if (type.is_array()) {
      if (type.empty()) {
        fail("The `type` keyword must name at least one type", pointer);
      }

      std::set<std::string> seen;
      for (const auto &entry : type.as_array()) {
        if (!entry.is_string()) {
          fail("The `type` keyword must name types as strings", pointer);
        }

        const auto kind{kind_of(entry.to_string(), pointer)};
        if (!seen.insert(kind).second) {
          fail("The `type` keyword names a type twice", pointer, kind);
        }

        kinds.push_back(kind);
      }
    } else {
      fail("The `type` keyword must be a string or a list of strings", pointer);
    }
  }

  const auto has_enumeration{
      defines(subschema, "enum") ||
      (defines(subschema, "const") && context.rank >= Rank::Draft6)};
  // Saying null is also allowed is only true when nothing beside the type can
  // forbid it. Otherwise null stays one of the forms, and the rules beside it
  // narrow the whole value as they do for every other form.
  static const std::vector<std::string> NARROWING{"allOf",
                                                  "anyOf",
                                                  "oneOf",
                                                  "not",
                                                  "$ref",
                                                  "if",
                                                  "enum",
                                                  "const",
                                                  "extends",
                                                  "disallow",
                                                  "$dynamicRef",
                                                  "$recursiveRef",
                                                  "unevaluatedProperties",
                                                  "unevaluatedItems"};
  auto can_narrow{false};
  for (const auto &keyword : NARROWING) {
    if (subschema.defines(keyword)) {
      can_narrow = true;
    }
  }

  auto nullable{false};
  if (kinds.size() > 1 && !can_narrow) {
    const auto null{std::find(kinds.begin(), kinds.end(), "null")};
    if (null != kinds.end()) {
      kinds.erase(null);
      nullable = true;
    }
  }

  if (has_enumeration) {
    // A fixed set of values, keeping only those the KEYWORDS beside it accept,
    // since a value the schema rejects must not be shown as allowed.
    std::vector<JSON> allowed;
    if (defines(subschema, "enum")) {
      const auto &listed{subschema.at("enum")};
      // From Draft 6 the meta-schema allows an empty list, which no value is
      // in.
      if (!listed.is_array() ||
          (listed.empty() && context.rank < Rank::Draft6)) {
        fail("The `enum` keyword must be a non-empty list of values", pointer);
      }

      allowed.reserve(listed.array_size());
      for (const auto &entry : listed.as_array()) {
        allowed.push_back(entry);
      }
    }

    if (defines(subschema, "const") && context.rank >= Rank::Draft6) {
      const auto &only{subschema.at("const")};
      if (!defines(subschema, "enum")) {
        allowed.push_back(only);
      } else {
        // Both hold, so only a value that is in the list and is the constant
        // is left.
        std::vector<JSON> both;
        for (const auto &entry : allowed) {
          if (entry == only) {
            both.push_back(entry);
          }
        }

        allowed = both;
      }
    }

    std::vector<JSON> kept;
    kept.reserve(allowed.size());
    auto certain{true};
    for (const auto &entry : allowed) {
      const auto verdict{accepted_by(entry, subschema, kinds, context.rank)};
      if (verdict == Verdict::No) {
        continue;
      }

      if (verdict == Verdict::Unknown) {
        certain = false;
      }

      kept.push_back(entry);
    }

    if (kept.empty()) {
      value = make_value("never");
    } else {
      value = make_value("enum");
      auto values{JSON::make_array()};
      for (auto &entry : kept) {
        values.push_back(std::move(entry));
      }

      value.assign("values", std::move(values));
      // What could not be DECIDED about here is said as a rule of its own, so
      // that nothing the schema requires is lost.
      if (!certain) {
        auto rest{JSON{subschema}};
        rest.erase(JSON::String{"enum"});
        rest.erase(JSON::String{"const"});
        rest.erase(JSON::String{"title"});
        rest.erase(JSON::String{"description"});
        rest.erase(JSON::String{"default"});
        rest.erase(JSON::String{"examples"});
        auto beside{convert(context, rest, pointer)};
        if (!(beside.at("kind").to_string() == "any" && beside.size() == 1)) {
          also(value, std::move(beside));
        }
      }
    }

    // Whatever the references beside the values say is in the rule above, if
    // anything was left to say.
    references.clear();
    nullable = false;
  } else if (kinds.empty()) {
    const auto inferred{inferred_kinds(subschema, context.rank)};
    if (inferred.empty()) {
      value = make_value("any");
    } else if (inferred.size() == 1) {
      value = make_value(inferred.front());
      fill_kind(context, value, subschema, pointer);
      value.assign("otherTypesAllowed", JSON{true});
    } else {
      auto options{JSON::make_array()};
      for (const auto &kind : inferred) {
        auto option{make_value(kind)};
        fill_kind(context, option, subschema, pointer);
        options.push_back(std::move(option));
      }

      value = make_value("choice");
      value.assign("options", std::move(options));
      value.assign("overlap", JSON{true});
      value.assign("otherTypesAllowed", JSON{true});
    }
  } else if (kinds.size() == 1) {
    value = make_value(kinds.front());
    fill_kind(context, value, subschema, pointer);
  } else {
    auto options{JSON::make_array()};
    for (const auto &kind : kinds) {
      auto option{make_value(kind)};
      fill_kind(context, option, subschema, pointer);
      options.push_back(std::move(option));
    }

    value = make_value("choice");
    value.assign("options", std::move(options));
    // A whole number is a number too, so those two forms overlap.
    if (std::find(kinds.cbegin(), kinds.cend(), "number") != kinds.cend() &&
        std::find(kinds.cbegin(), kinds.cend(), "integer") != kinds.cend()) {
      value.assign("overlap", JSON{true});
    }
  }

  if (nullable) {
    value.assign("nullable", JSON{true});
  }

  for (auto &reference : references) {
    if (value.at("kind").to_string() == "any" && value.size() == 1) {
      value = std::move(reference);
    } else {
      also(value, std::move(reference));
    }
  }

  if (context.rank == Rank::Draft3) {
    draft3_facts(context, value, subschema, pointer);
  } else {
    if (defines(subschema, "allOf")) {
      const auto &members{subschema.at("allOf")};
      if (!members.is_array() || members.empty()) {
        fail("The `allOf` keyword must be a non-empty list of schemas",
             pointer);
      }

      // Every member holds, so each one is another thing the data must match.
      for (std::size_t index = 0; index < members.array_size(); index++) {
        also(value, convert(context, members.at(index),
                            child(child(pointer, "allOf"), index)));
      }
    }

    branches(context, value, subschema, pointer, "anyOf", true);
    branches(context, value, subschema, pointer, "oneOf", false);
    if (defines(subschema, "not")) {
      forbid(value,
             convert(context, subschema.at("not"), child(pointer, "not")));
    }
  }

  conditions(context, value, subschema, pointer);
  annotations(value, subschema, context.rank);
  return value;
}

} // namespace sourcemeta::blaze::documentation
