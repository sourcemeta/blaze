#ifndef SOURCEMETA_BLAZE_CODEGEN_TYPESCRIPT_H_
#define SOURCEMETA_BLAZE_CODEGEN_TYPESCRIPT_H_

#ifndef SOURCEMETA_BLAZE_CODEGEN_EXPORT
#include <sourcemeta/blaze/codegen_export.h>
#endif

#include <sourcemeta/core/jsonpointer.h>

#include <map>         // std::map
#include <ostream>     // std::ostream
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::blaze {

struct IRScalar;
struct IREnumeration;
struct IRObject;
struct IRImpossible;
struct IRAny;
struct IRArray;
struct IRReference;
struct IRTuple;
struct IRUnion;
struct IRIntersection;
struct IRConditional;

/// @ingroup codegen
class SOURCEMETA_BLAZE_CODEGEN_EXPORT TypeScript {
public:
  TypeScript(std::ostream &stream, std::string_view type_prefix);
  auto operator()(const IRScalar &entry) -> void;
  auto operator()(const IREnumeration &entry) -> void;
  auto operator()(const IRObject &entry) -> void;
  auto operator()(const IRImpossible &entry) -> void;
  auto operator()(const IRAny &entry) -> void;
  auto operator()(const IRArray &entry) -> void;
  auto operator()(const IRReference &entry) -> void;
  auto operator()(const IRTuple &entry) -> void;
  auto operator()(const IRUnion &entry) -> void;
  auto operator()(const IRIntersection &entry) -> void;
  auto operator()(const IRConditional &entry) -> void;

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  std::ostream &output;
  std::string_view prefix;
  std::map<std::string, sourcemeta::core::Pointer> cache;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::blaze

#endif
