#ifndef SOURCEMETA_BLAZE_CODEGEN_H_
#define SOURCEMETA_BLAZE_CODEGEN_H_

#ifndef SOURCEMETA_BLAZE_CODEGEN_EXPORT
#include <sourcemeta/blaze/codegen_export.h>
#endif

// NOLINTBEGIN(misc-include-cleaner)
#include <sourcemeta/blaze/codegen_error.h>
#include <sourcemeta/blaze/codegen_typescript.h>
// NOLINTEND(misc-include-cleaner)

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <cstdint>     // std::uint8_t
#include <functional>  // std::function
#include <map>         // std::map
#include <optional>    // std::optional, std::nullopt
#include <ostream>     // std::ostream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::pair
#include <variant>     // std::variant, std::visit
#include <vector>      // std::vector

/// @defgroup codegen Codegen
/// @brief The codegen JSON Schema code generation package

namespace sourcemeta::blaze {

/// @ingroup codegen
enum class IRScalarType : std::uint8_t {
  String,
  Number,
  Integer,
  Boolean,
  Null
};

/// @ingroup codegen
struct IRType {
  sourcemeta::core::Pointer pointer;
  std::vector<std::string> symbol;
};

/// @ingroup codegen
struct IRScalar : IRType {
  IRScalarType value;
};

/// @ingroup codegen
struct IREnumeration : IRType {
  std::vector<sourcemeta::core::JSON> values;
};

/// @ingroup codegen
struct IRUnion : IRType {
  std::vector<IRType> values;
};

/// @ingroup codegen
struct IRIntersection : IRType {
  std::vector<IRType> values;
};

/// @ingroup codegen
struct IRObjectValue : IRType {
  bool required;
  bool immutable;
};

/// @ingroup codegen
struct IRObjectPatternProperty : IRType {
  std::optional<std::string> prefix;
};

/// @ingroup codegen
struct IRObject : IRType {
  // To preserve the user's ordering
  std::vector<std::pair<sourcemeta::core::JSON::String, IRObjectValue>> members;
  std::variant<bool, IRType> additional;
  std::vector<IRObjectPatternProperty> pattern;
};

/// @ingroup codegen
struct IRArray : IRType {
  std::optional<IRType> items;
};

/// @ingroup codegen
struct IRTuple : IRType {
  std::vector<IRType> items;
  std::optional<IRType> additional;
};

/// @ingroup codegen
struct IRImpossible : IRType {};

/// @ingroup codegen
struct IRAny : IRType {};

/// @ingroup codegen
struct IRConditional : IRType {
  IRType condition;
  IRType consequent;
  IRType alternative;
};

/// @ingroup codegen
struct IRReference : IRType {
  IRType target;
};

/// @ingroup codegen
using IREntity = std::variant<IRObject, IRScalar, IREnumeration, IRUnion,
                              IRIntersection, IRConditional, IRArray, IRTuple,
                              IRImpossible, IRAny, IRReference>;

/// @ingroup codegen
using IRResult = std::vector<IREntity>;

/// @ingroup codegen
using CodegenCompiler = std::function<IREntity(
    const sourcemeta::core::JSON &, const sourcemeta::core::SchemaFrame &,
    const sourcemeta::core::SchemaFrame::Location &,
    const sourcemeta::core::SchemaResolver &, const sourcemeta::core::JSON &)>;

/// @ingroup codegen
SOURCEMETA_BLAZE_CODEGEN_EXPORT
auto default_compiler(const sourcemeta::core::JSON &schema,
                      const sourcemeta::core::SchemaFrame &frame,
                      const sourcemeta::core::SchemaFrame::Location &location,
                      const sourcemeta::core::SchemaResolver &resolver,
                      const sourcemeta::core::JSON &subschema) -> IREntity;

/// @ingroup codegen
SOURCEMETA_BLAZE_CODEGEN_EXPORT
auto compile(const sourcemeta::core::JSON &schema,
             const sourcemeta::core::SchemaWalker &walker,
             const sourcemeta::core::SchemaResolver &resolver,
             const CodegenCompiler &compiler,
             const std::string_view default_dialect = "",
             const std::string_view default_id = "") -> IRResult;

/// @ingroup codegen
SOURCEMETA_BLAZE_CODEGEN_EXPORT
auto symbol(const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location)
    -> std::vector<std::string>;

/// @ingroup codegen
SOURCEMETA_BLAZE_CODEGEN_EXPORT
auto mangle(const std::string_view prefix,
            const sourcemeta::core::Pointer &pointer,
            const std::vector<std::string> &symbol,
            std::map<std::string, sourcemeta::core::Pointer> &cache)
    -> const std::string &;

/// @ingroup codegen
template <typename T>
auto generate(std::ostream &output, const IRResult &result,
              const std::string_view prefix = "Schema") -> void {
  T visitor{output, prefix};
  const char *separator{""};
  for (const auto &entity : result) {
    output << separator;
    separator = "\n";
    std::visit(visitor, entity);
  }
}

} // namespace sourcemeta::blaze

#endif
