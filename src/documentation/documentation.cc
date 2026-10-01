#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/regex.h>

#include <algorithm>   // std::sort, std::any_of, std::find, std::max
#include <cassert>     // assert
#include <cmath>       // std::isfinite
#include <cstddef>     // std::size_t
#include <cstdint>     // std::int64_t, std::uint8_t, std::uint32_t
#include <exception>   // std::exception
#include <map>         // std::map
#include <optional>    // std::optional
#include <set>         // std::set
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move, std::pair
#include <vector>      // std::vector

// The table format this module writes is described in
// tag:sourcemeta.com,2026:table-format/2, and
// what it says about a schema is meant to hold for every instance the schema
// accepts. Where this module cannot say something exactly, it refuses the
// schema rather than describing it loosely.

namespace {

using sourcemeta::core::JSON;
using sourcemeta::core::Pointer;

// How old a dialect is, so that a keyword is only read where it is defined.
enum class Rank : std::uint8_t {
  Draft4 = 4,
  Draft6 = 6,
  Draft7 = 7,
  Draft2019 = 8,
  Draft2020 = 9
};

auto operator<(const Rank left, const Rank right) -> bool {
  return static_cast<std::uint8_t>(left) < static_cast<std::uint8_t>(right);
}

auto operator>=(const Rank left, const Rank right) -> bool {
  return !(left < right);
}

struct Shape {
  std::string identifier;
  Pointer pointer;
  // How many places refer to it. The format's `usedAt` holds pointers into the
  // document rather than into the schema, so it is left out until the module
  // can state those exactly.
  std::size_t uses;
};

// A schema nested deeper than this is refused, so that a runaway schema gets
// an answer rather than exhausting the stack.
constexpr std::size_t MAXIMUM_DEPTH{64};

struct Context {
  const JSON &root;
  const sourcemeta::core::SchemaWalker &walker;
  const sourcemeta::core::SchemaResolver &resolver;
  const sourcemeta::core::SchemaFrame &frame;
  Rank rank;
  std::map<std::string, Shape> shapes;
  // Where each reference leads, by the place the `$ref` sits in the schema.
  std::map<std::string, sourcemeta::core::JSON::String> references;
  std::size_t depth{0};
};

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
auto nesting_of(const JSON &document) -> std::size_t {
  std::size_t deepest{0};
  std::vector<std::pair<const JSON *, std::size_t>> pending{{&document, 1}};
  while (!pending.empty()) {
    const auto [current, depth]{pending.back()};
    pending.pop_back();
    deepest = std::max(deepest, depth);
    if (depth > MAXIMUM_DEPTH * 2) {
      // No need to look further: it is already too deep to describe.
      return depth;
    }

    if (current->is_object()) {
      for (const auto &entry : current->as_object()) {
        pending.emplace_back(&entry.second, depth + 1);
      }
    } else if (current->is_array()) {
      for (const auto &entry : current->as_array()) {
        pending.emplace_back(&entry, depth + 1);
      }
    }
  }

  return deepest;
}

// The OFFICIAL address of each dialect this module reads, so that a schema
// that writes it without the empty fragment is still understood.
auto official_dialect(const std::string_view declared)
    -> std::optional<std::string_view> {
  static const std::vector<std::string_view> OFFICIAL{
      "http://json-schema.org/draft-04/schema#",
      "http://json-schema.org/draft-06/schema#",
      "http://json-schema.org/draft-07/schema#",
      "https://json-schema.org/draft/2019-09/schema",
      "https://json-schema.org/draft/2020-12/schema"};
  for (const auto &address : OFFICIAL) {
    if (declared == address) {
      return address;
    }

    // The same address, written without the fragment the draft spells it with.
    if (address.back() == '#' &&
        declared == address.substr(0, address.size() - 1)) {
      return address;
    }
  }

  return std::nullopt;
}

auto fail(const std::string &message, const Pointer &location) -> void {
  throw sourcemeta::blaze::DocumentationError{message, location};
}

auto defines(const JSON &subschema, const std::string &keyword) -> bool {
  return subschema.is_object() && subschema.defines(keyword);
}

// A place in the schema, as the pointer string the format uses for a shape.
auto pointer_string(const Pointer &pointer) -> std::string {
  return sourcemeta::core::to_string(pointer);
}

auto make_value(const std::string_view kind) -> JSON {
  auto result{JSON::make_object()};
  result.assign("kind", JSON{std::string{kind}});
  return result;
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

  const auto &count{subschema.at(keyword)};
  if (!count.is_integer() || count.to_integer() < 0) {
    fail("The `" + keyword + "` keyword must be a count", pointer);
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

namespace sourcemeta::blaze {

const char *const DOCUMENTATION_FORMAT =
    "tag:sourcemeta.com,2026:table-format/2";

} // namespace sourcemeta::blaze

namespace {

auto convert(Context &context, const JSON &subschema, const Pointer &pointer)
    -> JSON;

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
    const auto length{static_cast<std::int64_t>(entry.to_string().size())};
    if (defines(subschema, "minLength") &&
        subschema.at("minLength").is_integer() &&
        length < subschema.at("minLength").to_integer()) {
      return Verdict::No;
    }

    if (defines(subschema, "maxLength") &&
        subschema.at("maxLength").is_integer() &&
        length > subschema.at("maxLength").to_integer()) {
      return Verdict::No;
    }

    // A pattern needs a regular expression engine to decide, so it is left to
    // the rule beside the values.
    if (defines(subschema, "pattern")) {
      return Verdict::Unknown;
    }
  }

  if (entry.is_integer() || entry.is_real()) {
    const auto number{entry.is_integer()
                          ? static_cast<double>(entry.to_integer())
                          : entry.to_real()};
    const auto bound = [&subschema](const std::string &keyword,
                                    double &into) -> bool {
      if (!defines(subschema, keyword)) {
        return false;
      }

      const auto &value{subschema.at(keyword)};
      if (value.is_integer()) {
        into = static_cast<double>(value.to_integer());
        return true;
      }

      if (value.is_real()) {
        into = value.to_real();
        return true;
      }

      return false;
    };

    double limit{0};
    if (bound("minimum", limit) && number < limit) {
      return Verdict::No;
    }

    if (bound("maximum", limit) && number > limit) {
      return Verdict::No;
    }

    if (rank >= Rank::Draft6) {
      if (bound("exclusiveMinimum", limit) && number <= limit) {
        return Verdict::No;
      }

      if (bound("exclusiveMaximum", limit) && number >= limit) {
        return Verdict::No;
      }
    }
  }

  // Anything else beside the values, such as an object with fields of its own,
  // a reference, or a combination, is left to the rule beside them.
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

// An object that only says a field must be present, for the `when` of a
// condition made from a dependency keyword.
auto requires_field(const JSON::String &name) -> JSON {
  auto field{JSON::make_object()};
  field.assign("name", JSON{name});
  field.assign("required", JSON{true});
  auto fields{JSON::make_array()};
  fields.push_back(std::move(field));
  auto object{make_value("object")};
  object.assign("fields", std::move(fields));
  return object;
}

auto requires_fields(const JSON &names, const Pointer &pointer) -> JSON {
  if (!names.is_array()) {
    fail("A list of field names was expected", pointer);
  }

  if (names.empty()) {
    // Nothing becomes necessary, so there is nothing to say.
    return make_value("any");
  }

  auto fields{JSON::make_array()};
  for (const auto &name : names.as_array()) {
    if (!name.is_string()) {
      fail("A field name must be a string", pointer);
    }

    auto field{JSON::make_object()};
    field.assign("name", name);
    field.assign("required", JSON{true});
    fields.push_back(std::move(field));
  }

  auto object{make_value("object")};
  object.assign("fields", std::move(fields));
  return object;
}

// ------------------------------------------------------------------ the facts

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

  // In draft 4, the exclusive KEYWORDS are flags on the bounds; from draft 6
  // they are bounds of their own.
  if (defines(subschema, "exclusiveMinimum")) {
    const auto &exclusive{subschema.at("exclusiveMinimum")};
    if (rank < Rank::Draft6) {
      if (!exclusive.is_boolean()) {
        fail("The `exclusiveMinimum` keyword must be a boolean in draft 4",
             pointer);
      }

      if (exclusive.to_boolean() && !range.defines("min")) {
        fail("The `exclusiveMinimum` keyword needs a `minimum` in draft 4",
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
        fail("The `exclusiveMaximum` keyword must be a boolean in draft 4",
             pointer);
      }

      if (exclusive.to_boolean() && !range.defines("max")) {
        fail("The `exclusiveMaximum` keyword needs a `maximum` in draft 4",
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

  for (const auto *keyword : {"minimum", "maximum", "exclusiveMinimum",
                              "exclusiveMaximum", "multipleOf"}) {
    if (!defines(subschema, keyword)) {
      continue;
    }

    const auto &bound{subschema.at(keyword)};
    constexpr std::int64_t EXACT{9007199254740991};
    // A number too large for the usual kinds is kept as a decimal, which is
    // already past what this can state exactly.
    const auto past_exact{
        bound.is_decimal() ||
        (bound.is_integer() &&
         (bound.to_integer() > EXACT || bound.to_integer() < -EXACT)) ||
        (bound.is_real() && (!std::isfinite(bound.to_real()) ||
                             bound.to_real() > static_cast<double>(EXACT) ||
                             bound.to_real() < -static_cast<double>(EXACT)))};
    if (past_exact) {
      fail(std::string{"The `"} + keyword +
               "` keyword is past the numbers JSON holds exactly, so the "
               "format cannot state it",
           pointer);
    }
  }

  if (defines(subschema, "multipleOf")) {
    const auto &step{subschema.at("multipleOf")};
    const auto positive{(step.is_integer() && step.to_integer() > 0) ||
                        (step.is_real() && step.to_real() > 0)};
    if (!positive) {
      fail("The `multipleOf` keyword must be a number above zero", pointer);
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
    const auto size{static_cast<std::int64_t>(name.size())};
    if (length.defines("min") && length.at("min").is_integer() &&
        size < length.at("min").to_integer()) {
      return false;
    }

    if (length.defines("max") && length.at("max").is_integer() &&
        size > length.at("max").to_integer()) {
      return false;
    }
  }

  return true;
}

auto object_facts(Context &context, JSON &value, const JSON &subschema,
                  const Pointer &pointer) -> void {
  std::set<JSON::String> required;
  if (defines(subschema, "required")) {
    const auto &names{subschema.at("required")};
    if (!names.is_array()) {
      fail("The `required` keyword must be a list of field names", pointer);
    }

    for (const auto &name : names.as_array()) {
      if (!name.is_string()) {
        fail("A required field name must be a string", pointer);
      }

      if (!required.insert(name.to_string()).second) {
        fail("The `required` keyword names " + name.to_string() + " twice",
             pointer);
      }
    }
  }

  auto fields{JSON::make_array()};
  std::set<JSON::String> named;
  if (defines(subschema, "properties")) {
    const auto &properties{subschema.at("properties")};
    if (!properties.is_object()) {
      fail("The `properties` keyword must be an object", pointer);
    }

    for (const auto &entry : properties.as_object()) {
      auto field{JSON::make_object()};
      field.assign("name", JSON{entry.first});
      if (required.contains(entry.first)) {
        field.assign("required", JSON{true});
      }

      field.assign("value",
                   convert(context, entry.second,
                           child(child(pointer, "properties"), entry.first)));
      named.insert(entry.first);
      fields.push_back(std::move(field));
    }
  }

  // A name that is required and described nowhere is still a field a reader
  // must know about.
  for (const auto &name : required) {
    if (named.contains(name)) {
      continue;
    }

    auto field{JSON::make_object()};
    field.assign("name", JSON{name});
    field.assign("required", JSON{true});
    fields.push_back(std::move(field));
  }

  if (!fields.empty()) {
    value.assign("fields", std::move(fields));
  }

  if (defines(subschema, "patternProperties")) {
    const auto &patterns{subschema.at("patternProperties")};
    if (!patterns.is_object()) {
      fail("The `patternProperties` keyword must be an object", pointer);
    }

    auto entries{JSON::make_array()};
    for (const auto &entry : patterns.as_object()) {
      auto pattern{JSON::make_object()};
      pattern.assign("pattern", JSON{entry.first});
      pattern.assign("value", convert(context, entry.second,
                                      child(child(pointer, "patternProperties"),
                                            entry.first)));
      entries.push_back(std::move(pattern));
    }

    value.assign("patternFields", std::move(entries));
  }

  if (defines(subschema, "additionalProperties")) {
    const auto &additional{subschema.at("additionalProperties")};
    if (additional.is_boolean() && !additional.to_boolean()) {
      value.assign("closed", JSON{true});
    } else if (additional.is_boolean()) {
      value.assign("otherFields", make_value("any"));
    } else {
      value.assign(
          "otherFields",
          convert(context, additional, child(pointer, "additionalProperties")));
    }
  }

  if (defines(subschema, "propertyNames") && context.rank >= Rank::Draft6) {
    value.assign("keys", convert(context, subschema.at("propertyNames"),
                                 child(pointer, "propertyNames")));
  }

  // A field whose name also matches a pattern is held to both, so the table
  // says both of them rather than only the first.
  if (value.defines("fields") && value.defines("patternFields")) {
    for (auto &field : value.at("fields").as_array()) {
      if (!field.defines("value")) {
        continue;
      }

      for (const auto &entry : value.at("patternFields").as_array()) {
        if (!sourcemeta::core::matches_if_valid(entry.at("pattern").to_string(),
                                                field.at("name").to_string())) {
          continue;
        }

        if (!field.at("value").defines("also")) {
          field.at("value").assign("also", JSON::make_array());
        }

        field.at("value").at("also").push_back(entry.at("value"));
      }
    }
  }

  // A name the key rule does not allow can never appear, whatever a field says
  // it would hold.
  if (value.defines("fields") && value.defines("keys")) {
    const auto &keys{value.at("keys")};
    for (auto &field : value.at("fields").as_array()) {
      if (!name_allowed(keys, field.at("name").to_string())) {
        field.assign("value", make_value("never"));
      }
    }
  }

  count_of(subschema, "minProperties", pointer);
  count_of(subschema, "maxProperties", pointer);
  const auto count{bounds(subschema, "minProperties", "maxProperties")};
  if (count.has_value()) {
    value.assign("fieldCount", JSON{count.value()});
  }

  // One field being present making others necessary is a condition.
  if (defines(subschema, "dependentRequired") &&
      context.rank >= Rank::Draft2019) {
    const auto &dependencies{subschema.at("dependentRequired")};
    if (!dependencies.is_object()) {
      fail("The `dependentRequired` keyword must be an object", pointer);
    }

    for (const auto &entry : dependencies.as_object()) {
      auto entry_condition{JSON::make_object()};
      entry_condition.assign("when", requires_field(entry.first));
      entry_condition.assign(
          "then",
          requires_fields(entry.second, child(pointer, "dependentRequired")));
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
      entry_condition.assign("when", requires_field(entry.first));
      entry_condition.assign(
          "then",
          convert(context, entry.second,
                  child(child(pointer, "dependentSchemas"), entry.first)));
      condition(value, std::move(entry_condition));
    }
  }

  // Before 2019-09, both of the above were one keyword.
  if (defines(subschema, "dependencies") && context.rank < Rank::Draft2019) {
    const auto &dependencies{subschema.at("dependencies")};
    if (!dependencies.is_object()) {
      fail("The `dependencies` keyword must be an object", pointer);
    }

    for (const auto &entry : dependencies.as_object()) {
      auto entry_condition{JSON::make_object()};
      entry_condition.assign("when", requires_field(entry.first));
      if (entry.second.is_array()) {
        entry_condition.assign(
            "then",
            requires_fields(entry.second, child(pointer, "dependencies")));
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
      }
    } else {
      value.assign("item", convert(context, items, child(pointer, "items")));
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

// ------------------------------------------------------------------- the kind

auto kind_of(const JSON::String &name, const Pointer &pointer) -> std::string {
  if (name == "string" || name == "number" || name == "integer" ||
      name == "boolean" || name == "object" || name == "array" ||
      name == "null") {
    return name;
  }

  fail("The `type` keyword names " + name + ", which is not a JSON type",
       pointer);
  return "any";
}

// The types the KEYWORDS of a subschema are about, when it does not say.
auto inferred_kinds(const JSON &subschema, const Rank rank)
    -> std::vector<std::string> {
  std::vector<std::string> string_keywords{"minLength", "maxLength", "pattern"};
  std::vector<std::string> number_keywords{"minimum", "maximum",
                                           "exclusiveMinimum",
                                           "exclusiveMaximum", "multipleOf"};
  std::vector<std::string> object_keywords{
      "properties", "patternProperties", "additionalProperties",
      "required",   "minProperties",     "maxProperties"};
  std::vector<std::string> array_keywords{
      "items", "additionalItems", "minItems", "maxItems", "uniqueItems"};
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
    array_keywords.emplace_back("minContains");
    array_keywords.emplace_back("maxContains");
  } else {
    object_keywords.emplace_back("dependencies");
  }

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

// ------------------------------------------------------------- the references

auto reference_of(Context &context, const JSON &subschema,
                  const Pointer &pointer) -> std::optional<JSON> {
  for (const auto *keyword : {"$dynamicRef", "$recursiveRef"}) {
    if (defines(subschema, keyword)) {
      fail(std::string{"The `"} + keyword +
               "` keyword names a place that depends on where it is used, "
               "which the format cannot state exactly",
           pointer);
    }
  }

  if (!defines(subschema, "$ref")) {
    return std::nullopt;
  }

  if (!subschema.at("$ref").is_string()) {
    fail("The `$ref` keyword must be a string", pointer);
  }

  const auto entry{
      context.references.find(pointer_string(child(pointer, "$ref")))};
  if (entry == context.references.cend()) {
    fail("The `$ref` keyword names a place that does not resolve", pointer);
  }

  const auto &destination{entry->second};
  const auto target{context.frame.traverse(destination)};
  if (!target.has_value()) {
    // A reference into this document that lands nowhere is a schema that
    // cannot be read, rather than a document kept elsewhere.
    const auto &root{context.frame.root()};
    if (!root.empty() && destination.starts_with(root)) {
      fail("The `$ref` keyword names a place in this schema that does not "
           "resolve",
           pointer);
    }

    // Something outside this document, which a reader follows elsewhere.
    auto value{make_value("external")};
    value.assign("href", JSON{destination});
    return value;
  }

  const auto &location{target->get()};
  if (location.type != sourcemeta::core::SchemaFrame::LocationType::Resource &&
      location.type != sourcemeta::core::SchemaFrame::LocationType::Subschema &&
      location.type != sourcemeta::core::SchemaFrame::LocationType::Anchor &&
      location.type != sourcemeta::core::SchemaFrame::LocationType::Pointer) {
    fail("The `$ref` keyword names something that is not a schema", pointer);
  }

  auto pointer_to_target{sourcemeta::core::to_pointer(location.pointer)};
  const auto &target_schema{
      sourcemeta::core::get(context.root, pointer_to_target)};
  if (!target_schema.is_object() && !target_schema.is_boolean()) {
    fail("The `$ref` keyword names something that is not a schema", pointer);
  }

  const auto identifier{pointer_string(pointer_to_target)};
  auto match{context.shapes.find(identifier)};
  if (match == context.shapes.cend()) {
    match = context.shapes
                .emplace(identifier, Shape{.identifier = identifier,
                                           .pointer = pointer_to_target,
                                           .uses = 0})
                .first;
  }

  match->second.uses += 1;
  auto value{make_value("ref")};
  value.assign("ref", JSON{identifier});
  return value;
}

// ------------------------------------------------------------ the whole value

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
    fail("The `" + keyword + "` keyword must be a non-empty list of schemas",
         pointer);
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

// Counts how deep the conversion is while it is inside one subschema.
class Depth {
public:
  Depth(Context &context, const Pointer &pointer) : context_{context} {
    this->context_.depth += 1;
    if (this->context_.depth > MAXIMUM_DEPTH) {
      fail("This schema nests deeper than this module describes", pointer);
    }
  }

  ~Depth() { this->context_.depth -= 1; }
  Depth(const Depth &) = delete;
  auto operator=(const Depth &) -> Depth & = delete;
  Depth(Depth &&) = delete;
  auto operator=(Depth &&) -> Depth & = delete;

private:
  Context &context_;
};

auto convert(Context &context, const JSON &subschema, const Pointer &pointer)
    -> JSON {
  const Depth depth{context, pointer};
  if (subschema.is_boolean()) {
    return make_value(subschema.to_boolean() ? "any" : "never");
  }

  if (!subschema.is_object()) {
    fail("A schema must be an object or a boolean", pointer);
  }

  // What the format cannot state exactly is refused rather than guessed at.
  for (const auto *keyword : {"unevaluatedProperties", "unevaluatedItems"}) {
    if (defines(subschema, keyword) && context.rank >= Rank::Draft2019) {
      fail(std::string{"The `"} + keyword +
               "` keyword depends on what the rest of the schema happened to "
               "describe, which the format cannot state exactly",
           pointer);
    }
  }

  const auto reference{reference_of(context, subschema, pointer)};
  // Before 2019-09, a reference stands alone: its siblings say nothing.
  if (reference.has_value() && context.rank < Rank::Draft2019) {
    auto value{reference.value()};
    return value;
  }

  JSON value{JSON::make_object()};
  std::vector<std::string> kinds;
  if (defines(subschema, "type")) {
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
          fail("The `type` keyword names " + kind + " twice", pointer);
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
  static const std::vector<std::string> NARROWING{
      "allOf", "anyOf", "oneOf", "not", "$ref", "if", "enum", "const"};
  auto can_narrow{false};
  if (subschema.is_object()) {
    for (const auto &keyword : NARROWING) {
      if (subschema.defines(keyword)) {
        can_narrow = true;
      }
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
      if (!listed.is_array() || listed.empty()) {
        fail("The `enum` keyword must be a non-empty list of values", pointer);
      }

      for (const auto &entry : listed.as_array()) {
        allowed.push_back(entry);
      }
    }

    if (defines(subschema, "const") && context.rank >= Rank::Draft6) {
      const auto &only{subschema.at("const")};
      if (allowed.empty()) {
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
      for (const auto &entry : kept) {
        values.push_back(entry);
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

  if (reference.has_value()) {
    if (value.at("kind").to_string() == "any" && value.size() == 1) {
      value = reference.value();
    } else {
      also(value, JSON{reference.value()});
    }
  }

  if (defines(subschema, "allOf")) {
    const auto &members{subschema.at("allOf")};
    if (!members.is_array() || members.empty()) {
      fail("The `allOf` keyword must be a non-empty list of schemas", pointer);
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
    forbid(value, convert(context, subschema.at("not"), child(pointer, "not")));
  }

  conditions(context, value, subschema, pointer);
  annotations(value, subschema, context.rank);
  return value;
}

auto rank_of(const sourcemeta::core::SchemaBaseDialect base_dialect,
             const Pointer &pointer) -> Rank {
  switch (base_dialect) {
    case sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12:
      return Rank::Draft2020;
    case sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09:
      return Rank::Draft2019;
    case sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_7:
      return Rank::Draft7;
    case sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_6:
      return Rank::Draft6;
    case sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4:
      return Rank::Draft4;
    default:
      fail("This module describes JSON Schema draft 4, 6 and 7, 2019-09 and "
           "2020-12, and not hyper-schema",
           pointer);
      return Rank::Draft2020;
  }
}

auto name_of(const Pointer &pointer, const std::string &identifier)
    -> std::string {
  // The last part of the path that is a name of its own, skipping the KEYWORDS
  // and the positions a reader does not think in.
  static const std::vector<std::string> KEYWORDS{"properties",
                                                 "patternProperties",
                                                 "additionalProperties",
                                                 "items",
                                                 "prefixItems",
                                                 "additionalItems",
                                                 "contains",
                                                 "propertyNames",
                                                 "allOf",
                                                 "anyOf",
                                                 "oneOf",
                                                 "not",
                                                 "if",
                                                 "then",
                                                 "else",
                                                 "$defs",
                                                 "definitions",
                                                 "dependentSchemas",
                                                 "dependencies",
                                                 "unevaluatedItems",
                                                 "unevaluatedProperties"};
  std::string result{identifier};
  for (const auto &token : pointer) {
    if (!token.is_property()) {
      continue;
    }

    const auto &name{token.to_property()};
    if (std::find(KEYWORDS.cbegin(), KEYWORDS.cend(), name) ==
        KEYWORDS.cend()) {
      // The deepest such name is the one a reader knows the shape by.
      result = name;
    }
  }

  return result;
}

} // namespace

namespace sourcemeta::blaze {

auto to_documentation(const sourcemeta::core::JSON &schema,
                      const sourcemeta::core::SchemaWalker &walker,
                      const sourcemeta::core::SchemaResolver &resolver)
    -> sourcemeta::core::JSON {
  const Pointer root_pointer;
  if (!schema.is_object() && !schema.is_boolean()) {
    fail("A schema must be an object or a boolean", root_pointer);
  }

  if (!schema.is_object() || !schema.defines("$schema") ||
      !schema.at("$schema").is_string() ||
      schema.at("$schema").to_string().empty()) {
    fail("The schema does not say which dialect it is written in",
         root_pointer);
  }

  const auto declared{schema.at("$schema").to_string()};

  // Reading a schema this deep would run out of stack before it could say
  // anything useful, in this module or in what it calls.
  if (nesting_of(schema) > MAXIMUM_DEPTH * 2) {
    fail("This schema nests deeper than this module describes", root_pointer);
  }

  // An OFFICIAL dialect is known by its address, which a schema may write with
  // or without the empty fragment the drafts use. The work goes through the
  // official spelling, while the document keeps the address the schema gave.
  auto canonical{schema};
  const auto official{official_dialect(declared)};
  if (official.has_value()) {
    canonical.assign("$schema",
                     sourcemeta::core::JSON{std::string{official.value()}});
  }

  std::optional<sourcemeta::core::SchemaFrame> frame;
  try {
    frame.emplace(sourcemeta::core::SchemaFrame::Mode::References, canonical,
                  walker, resolver);
  } catch (const std::exception &error) {
    fail(std::string{"The schema could not be read: "} + error.what(),
         root_pointer);
  }

  const auto root_location{frame->root_location()};
  if (!root_location.has_value()) {
    fail("The schema does not say which dialect it is written in",
         root_pointer);
  }

  const auto rank{rank_of(root_location->get().base_dialect, root_pointer)};
  Context context{.root = canonical,
                  .walker = walker,
                  .resolver = resolver,
                  .frame = frame.value(),
                  .rank = rank,
                  .shapes = {},
                  .references = {},
                  .depth = 0};
  frame->for_each_reference([&context](const auto type,
                                       const auto &reference_pointer,
                                       const auto &reference) {
    if (type == sourcemeta::core::SchemaReferenceType::Static) {
      context.references.emplace(sourcemeta::core::to_string(reference_pointer),
                                 reference.destination);
    }
  });

  auto root{convert(context, canonical, root_pointer)};

  auto result{sourcemeta::core::JSON::make_object()};
  result.assign("$schema",
                sourcemeta::core::JSON{std::string{DOCUMENTATION_FORMAT}});
  if (schema.is_object() && schema.defines("title") &&
      schema.at("title").is_string() &&
      !schema.at("title").to_string().empty()) {
    result.assign("title", schema.at("title"));
  } else {
    result.assign("title", sourcemeta::core::JSON{std::string{"Schema"}});
  }

  if (schema.is_object() && schema.defines("description") &&
      schema.at("description").is_string() &&
      !schema.at("description").to_string().empty()) {
    result.assign("description", schema.at("description"));
  }

  result.assign("language", sourcemeta::core::JSON{std::string{declared}});
  // The root describes itself, so what it says is not repeated as a shape.
  root.erase(JSON::String{"title"});
  root.erase(JSON::String{"description"});
  result.assign("root", std::move(root));

  // Every place a reference lands is described once and linked to.
  // Converting a shape can find more shapes, at any depth, so this keeps
  // going until nothing new turns up.
  std::map<std::string, sourcemeta::core::JSON> values;
  while (true) {
    std::vector<Shape> pending;
    for (const auto &entry : context.shapes) {
      if (entry.second.pointer.empty() || values.contains(entry.first)) {
        continue;
      }

      pending.push_back(entry.second);
    }

    if (pending.empty()) {
      break;
    }

    for (const auto &shape : pending) {
      values.emplace(shape.identifier,
                     convert(context,
                             sourcemeta::core::get(canonical, shape.pointer),
                             shape.pointer));
    }
  }

  std::vector<Shape> shapes;
  for (const auto &entry : context.shapes) {
    if (entry.second.pointer.empty()) {
      continue;
    }

    shapes.push_back(entry.second);
  }

  // Most used first, so a reader meets the common ones early.
  std::sort(shapes.begin(), shapes.end(),
            [](const auto &left, const auto &right) {
              if (left.uses != right.uses) {
                return left.uses > right.uses;
              }

              return left.identifier < right.identifier;
            });

  if (!shapes.empty()) {
    auto entries{sourcemeta::core::JSON::make_array()};
    for (const auto &shape : shapes) {
      auto entry{sourcemeta::core::JSON::make_object()};
      entry.assign("id", sourcemeta::core::JSON{shape.identifier});
      entry.assign("name", sourcemeta::core::JSON{
                               name_of(shape.pointer, shape.identifier)});
      entry.assign("value", values.at(shape.identifier));
      entries.push_back(std::move(entry));
    }

    result.assign("shapes", std::move(entries));
  }

  return result;
}

} // namespace sourcemeta::blaze
