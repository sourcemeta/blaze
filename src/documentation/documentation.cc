#include <sourcemeta/blaze/documentation.h>

#include "internal.h"

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>   // std::sort
#include <cstddef>     // std::size_t
#include <exception>   // std::exception
#include <map>         // std::map
#include <optional>    // std::optional
#include <set>         // std::set
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move, std::pair
#include <vector>      // std::vector

// Walking a whole schema: deciding which dialect it is written in, naming the
// shapes it refers to, and assembling the document. Describing one subschema
// lives in `documentation_value.cc`.

namespace sourcemeta::blaze::documentation {

namespace {

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

// The message is a fixed sentence. Whatever the sentence is about, such as
// the keyword at fault, travels beside it rather than inside it.

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
      fail("This module describes JSON Schema Draft 4, 6 and 7, 2019-09 and "
           "2020-12, and not HyperSchema",
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

} // namespace sourcemeta::blaze::documentation

namespace sourcemeta::blaze {

// The vocabulary this module works in, so the entry point reads the same
// way as the two files behind it.
using namespace documentation; // NOLINT(google-build-using-namespace)

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
    fail("The schema could not be read", root_pointer, error.what());
  }

  const auto root_location{frame->root_location()};
  if (!root_location.has_value()) {
    fail("The schema does not say which dialect it is written in",
         root_pointer);
  }

  const auto rank{rank_of(root_location->get().base_dialect, root_pointer)};

  // One dialect for the whole document. A resource of its own may declare a
  // different one, and then a keyword means something else, or nothing at all,
  // from one part of the schema to the next. `prefixItems` inside a Draft 7
  // resource is not a rule, and reading it as one would state something the
  // schema does not say.
  const auto root_dialect{root_location->get().base_dialect};
  frame->for_each_subschema([root_dialect](const auto &location) {
    if (location.base_dialect != root_dialect) {
      Pointer where;
      for (const auto &token : location.pointer) {
        if (token.is_property()) {
          where.push_back(token.to_property());
        } else {
          where.push_back(token.to_index());
        }
      }

      fail("This resource is written in a different dialect from the rest of "
           "the schema, which the format cannot state exactly",
           where);
    }
  });

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
