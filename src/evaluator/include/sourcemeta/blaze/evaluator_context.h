#ifndef SOURCEMETA_BLAZE_EVALUATOR_CONTEXT_H
#define SOURCEMETA_BLAZE_EVALUATOR_CONTEXT_H

#ifndef SOURCEMETA_BLAZE_EVALUATOR_EXPORT
#include <sourcemeta/blaze/evaluator_export.h>
#endif

#include <sourcemeta/blaze/evaluator_instruction.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonpointer.h>

#include <cassert>    // assert
#include <cstdint>    // std::uint8_t
#include <functional> // std::reference_wrapper
#include <map>        // std::map
#include <optional>   // std::optional
#include <set>        // std::set
#include <string>     // std::string
#include <vector>     // std::vector

namespace sourcemeta::blaze {

/// @ingroup evaluator
/// Represents a stateful schema evaluation context
class SOURCEMETA_BLAZE_EVALUATOR_EXPORT EvaluationContext {
public:
  // All of these methods are considered internal and no
  // client must depend on them
#ifndef DOXYGEN

  ///////////////////////////////////////////////
  // Evaluation stack
  ///////////////////////////////////////////////

  auto push(const sourcemeta::jsontoolkit::Pointer &relative_schema_location,
            const sourcemeta::jsontoolkit::Pointer &relative_instance_location,
            const std::size_t &schema_resource, const bool dynamic,
            const bool track) -> void;
  auto pop(const std::size_t relative_schema_location_size,
           const std::size_t relative_instance_location_size,
           const bool dynamic, const bool track) -> void;

  ///////////////////////////////////////////////
  // Target resolution
  ///////////////////////////////////////////////

  // TODO: Make these methods plain functions on evaluator.cc
  auto resolve_target(const sourcemeta::jsontoolkit::JSON &instance)
      -> const sourcemeta::jsontoolkit::JSON &;
  auto
  resolve_string_target(const sourcemeta::jsontoolkit::JSON &instance) const
      -> std::optional<
          std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>;

  ///////////////////////////////////////////////
  // References and anchors
  ///////////////////////////////////////////////

  auto
  hash(const std::size_t &resource,
       const sourcemeta::jsontoolkit::JSON::String &fragment) const noexcept
      -> std::size_t;

  ///////////////////////////////////////////////
  // Evaluation
  ///////////////////////////////////////////////

  auto evaluate() -> void;
  auto evaluate(const sourcemeta::jsontoolkit::WeakPointer::Token::Index from,
                const sourcemeta::jsontoolkit::WeakPointer::Token::Index to)
      -> void;
  auto
  evaluate(const sourcemeta::jsontoolkit::Pointer &relative_instance_location)
      -> void;
  auto
  is_evaluated(const sourcemeta::jsontoolkit::WeakPointer::Token &tail) const
      -> bool;
  auto unevaluate() -> void;

  // TODO: Remove this
  const sourcemeta::jsontoolkit::JSON null{nullptr};

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif
  sourcemeta::jsontoolkit::WeakPointer evaluate_path;
  std::uint64_t evaluate_path_size{0};
  sourcemeta::jsontoolkit::WeakPointer instance_location;
  const std::hash<sourcemeta::jsontoolkit::JSON::String> hasher_{};
  std::vector<std::size_t> resources;
  std::map<std::size_t, const std::reference_wrapper<const Instructions>>
      labels;
  std::optional<
      std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
      property_target;

  // TODO: Revamp the data structure we use to track evaluation
  // to provide more performant lookups that don't involve so many
  // pointer token string comparisons
  struct Evaluation {
    sourcemeta::jsontoolkit::WeakPointer instance_location;
    sourcemeta::jsontoolkit::WeakPointer evaluate_path;
    bool skip;
  };

  std::vector<Evaluation> evaluated_;
#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif
#endif
};

} // namespace sourcemeta::blaze

#endif
