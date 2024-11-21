#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonpointer.h>
#include <sourcemeta/jsontoolkit/regex.h>
#include <sourcemeta/jsontoolkit/uri.h>

#include "trace.h"

#include <algorithm>  // std::min, std::any_of, std::find
#include <cassert>    // assert
#include <functional> // std::reference_wrapper
#include <limits>     // std::numeric_limits
#include <optional>   // std::optional

namespace sourcemeta::blaze {
using namespace sourcemeta::jsontoolkit;

inline auto
resolve_target(const std::optional<std::reference_wrapper<const JSON::String>>
                   &property_target,
               const JSON &instance) -> const JSON & {
  if (property_target.has_value()) [[unlikely]] {
    // In this case, we still need to return a string in order
    // to cope with non-string keywords inside `propertyNames`
    // that need to fail validation. But then, the actual string
    // we return doesn't matter, so we can always return a dummy one.
    return EvaluationContext::empty_string;
  }

  return instance;
}

inline auto resolve_string_target(
    const std::optional<std::reference_wrapper<const JSON::String>>
        &property_target,
    const JSON &instance, const Pointer &relative_instance_location) noexcept
    -> std::optional<std::reference_wrapper<const JSON::String>> {
  if (property_target.has_value()) [[unlikely]] {
    return property_target.value();
  }

  const auto &target{get(instance, relative_instance_location)};
  if (!target.is_string()) {
    return std::nullopt;
  } else {
    return target.to_string();
  }
}

} // namespace sourcemeta::blaze

#define SOURCEMETA_STRINGIFY(x) #x

#include "evaluator_complete.h"

#undef SOURCEMETA_STRINGIFY

namespace sourcemeta::blaze {

auto evaluate(const Template &schema,
              const sourcemeta::jsontoolkit::JSON &instance,
              const Callback &callback) -> bool {
  EvaluationContext context;
  return evaluate_complete(instance, context, schema.first, schema.second,
                           callback);
}

auto evaluate(const Template &schema,
              const sourcemeta::jsontoolkit::JSON &instance) -> bool {
  EvaluationContext context;
  return evaluate_complete(instance, context, schema.first, schema.second,
                           std::nullopt);
}

auto evaluate(const Template &schema,
              const sourcemeta::jsontoolkit::JSON &instance,
              EvaluationContext &context) -> bool {
  // Do a full reset for the next run
  assert(context.evaluate_path.empty());
  assert(context.instance_location.empty());
  assert(context.resources.empty());
  context.labels.clear();
  // TODO: Only do this one for evaluations that are "complete"
  context.evaluated_.clear();

  return evaluate_complete(instance, context, schema.first, schema.second,
                           std::nullopt);
}

} // namespace sourcemeta::blaze
