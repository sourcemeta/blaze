#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_INTERNAL_H_
#define SOURCEMETA_BLAZE_DOCUMENTATION_INTERNAL_H_

#include <sourcemeta/blaze/documentation_error.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <cstddef> // std::size_t
#include <cstdint> // std::uint8_t
#include <map>     // std::map
#include <set>     // std::set
#include <string>  // std::string
#include <utility> // std::move
#include <vector>  // std::vector

// What both halves of this module need to agree on: how old a dialect is, what
// a shape is, and what is being carried through a conversion. Reading one
// subschema lives in `documentation_value.cc`, and walking a whole schema in
// `documentation.cc`.

namespace sourcemeta::blaze::documentation {

using sourcemeta::core::JSON;
using sourcemeta::core::Pointer;

enum class Rank : std::uint8_t {
  Draft4 = 4,
  Draft6 = 6,
  Draft7 = 7,
  Draft2019 = 8,
  Draft2020 = 9
};

inline auto operator<(const Rank left, const Rank right) -> bool {
  return static_cast<std::uint8_t>(left) < static_cast<std::uint8_t>(right);
}

inline auto operator>=(const Rank left, const Rank right) -> bool {
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

inline auto fail(const char *message, const Pointer &location,
                 std::string subject = "") -> void {
  throw sourcemeta::blaze::DocumentationError{message, location,
                                              std::move(subject)};
}

inline auto defines(const JSON &subschema, const std::string &keyword) -> bool {
  return subschema.is_object() && subschema.defines(keyword);
}

// A place in the schema, as the pointer string the format uses for a shape.

// One subschema, described. Defined in `documentation_value.cc`.
auto convert(Context &context, const JSON &subschema, const Pointer &pointer)
    -> JSON;

} // namespace sourcemeta::blaze::documentation

#endif
