#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/regex.h>
#include <sourcemeta/jsontoolkit/uri.h>

#include "trace.h"

#include <algorithm>  // std::min, std::any_of, std::find
#include <cassert>    // assert
#include <functional> // std::reference_wrapper
#include <limits>     // std::numeric_limits
#include <optional>   // std::optional

namespace {

inline auto resolve_target(
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const sourcemeta::jsontoolkit::JSON &instance)
    -> const sourcemeta::jsontoolkit::JSON & {
  if (property_target.has_value()) [[unlikely]] {
    // In this case, we still need to return a string in order
    // to cope with non-string keywords inside `propertyNames`
    // that need to fail validation. But then, the actual string
    // we return doesn't matter, so we can always return a dummy one.
    return sourcemeta::blaze::EvaluationContext::empty_string;
  }

  return instance;
}

inline auto resolve_string_target(
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const sourcemeta::jsontoolkit::JSON &instance,
    const sourcemeta::jsontoolkit::Pointer &relative_instance_location) noexcept
    -> std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>> {
  if (property_target.has_value()) [[unlikely]] {
    return property_target.value();
  }

  const auto &target{
      sourcemeta::jsontoolkit::get(instance, relative_instance_location)};
  if (!target.is_string()) {
    return std::nullopt;
  } else {
    return target.to_string();
  }
}

auto evaluate_step(
    const sourcemeta::blaze::Instruction &step,
    const std::optional<sourcemeta::blaze::Callback> &callback,
    const sourcemeta::jsontoolkit::JSON &instance,
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const std::uint64_t depth, sourcemeta::blaze::EvaluationContext &context)
    -> bool {
  SOURCEMETA_TRACE_REGISTER_ID(trace_id);
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  // Guard against infinite recursion in a cheap manner, as
  // infinite recursion will manifest itself through huge
  // ever-growing evaluate paths
  constexpr auto DEPTH_LIMIT{300};
  if (depth > DEPTH_LIMIT) [[unlikely]] {
    throw sourcemeta::blaze::EvaluationError(
        "The evaluation path depth limit was reached "
        "likely due to infinite recursion");
  }

#define STRINGIFY(x) #x

#define EVALUATE_BEGIN(step_category, step_type, precondition)                 \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  const auto &step_category{std::get<step_type>(step)};                        \
  const auto track{step_category.track || callback.has_value()};               \
  if (track) {                                                                 \
    context.evaluate_path.push_back(step_category.relative_schema_location);   \
    context.instance_location.push_back(                                       \
        step_category.relative_instance_location);                             \
  }                                                                            \
  if (step_category.dynamic) {                                                 \
    context.resources.push_back(step_category.schema_resource);                \
  }                                                                            \
  const auto &target{resolve_target(                                           \
      property_target,                                                         \
      sourcemeta::jsontoolkit::get(                                            \
          instance, step_category.relative_instance_location))};               \
  if (!(precondition)) {                                                       \
    if (track) {                                                               \
      context.evaluate_path.pop_back(                                          \
          step_category.relative_schema_location.size());                      \
      context.instance_location.pop_back(                                      \
          step_category.relative_instance_location.size());                    \
    }                                                                          \
    if (step_category.dynamic) {                                               \
      context.resources.pop_back();                                            \
    }                                                                          \
    SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                      \
    return true;                                                               \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, step, context.evaluate_path,   \
                     context.instance_location, EvaluationContext::null);      \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_IF_STRING(step_category, step_type)                     \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  const auto &step_category{std::get<step_type>(step)};                        \
  const auto track{step_category.track || callback.has_value()};               \
  if (track) {                                                                 \
    context.evaluate_path.push_back(step_category.relative_schema_location);   \
    context.instance_location.push_back(                                       \
        step_category.relative_instance_location);                             \
  }                                                                            \
  if (step_category.dynamic) {                                                 \
    context.resources.push_back(step_category.schema_resource);                \
  }                                                                            \
  const auto &maybe_target{resolve_string_target(                              \
      property_target, instance, step_category.relative_instance_location)};   \
  if (!maybe_target.has_value()) {                                             \
    if (track) {                                                               \
      context.evaluate_path.pop_back(                                          \
          step_category.relative_schema_location.size());                      \
      context.instance_location.pop_back(                                      \
          step_category.relative_instance_location.size());                    \
    }                                                                          \
    if (step_category.dynamic) {                                               \
      context.resources.pop_back();                                            \
    }                                                                          \
    SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                      \
    return true;                                                               \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, step, context.evaluate_path,   \
                     context.instance_location, EvaluationContext::null);      \
  }                                                                            \
  const auto &target{maybe_target.value().get()};                              \
  bool result{false};

  // This is a slightly complicated dance to avoid traversing the relative
  // instance location twice.
#define EVALUATE_BEGIN_TRY_TARGET(step_category, step_type, precondition)      \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  const auto &target{resolve_target(property_target, instance)};               \
  const auto &step_category{std::get<step_type>(step)};                        \
  if (!(precondition)) {                                                       \
    SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                      \
    return true;                                                               \
  }                                                                            \
  auto target_check{                                                           \
      try_get(target, step_category.relative_instance_location)};              \
  if (!target_check.has_value()) {                                             \
    SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                      \
    return true;                                                               \
  }                                                                            \
  const auto track{step_category.track || callback.has_value()};               \
  if (track) {                                                                 \
    context.evaluate_path.push_back(step_category.relative_schema_location);   \
    context.instance_location.push_back(                                       \
        step_category.relative_instance_location);                             \
  }                                                                            \
  if (step_category.dynamic) {                                                 \
    context.resources.push_back(step_category.schema_resource);                \
  }                                                                            \
  assert(!step_category.relative_instance_location.empty());                   \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, step, context.evaluate_path,   \
                     context.instance_location, EvaluationContext::null);      \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION(step_category, step_type)               \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  const auto &step_category{std::get<step_type>(step)};                        \
  const auto track{step_category.track || callback.has_value()};               \
  if (track) {                                                                 \
    context.evaluate_path.push_back(step_category.relative_schema_location);   \
    context.instance_location.push_back(                                       \
        step_category.relative_instance_location);                             \
  }                                                                            \
  if (step_category.dynamic) {                                                 \
    context.resources.push_back(step_category.schema_resource);                \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, step, context.evaluate_path,   \
                     context.instance_location, EvaluationContext::null);      \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(step_category, step_type)   \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  const auto &step_category{std::get<step_type>(step)};                        \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, step, context.evaluate_path,   \
                     context.instance_location, EvaluationContext::null);      \
  }                                                                            \
  bool result{true};

#define EVALUATE_BEGIN_PASS_THROUGH(step_category, step_type)                  \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  const auto &step_category{std::get<step_type>(step)};                        \
  bool result{true};

#define EVALUATE_END(step_category, step_type)                                 \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Post, result, step,                       \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  if (track) {                                                                 \
    context.evaluate_path.pop_back(                                            \
        step_category.relative_schema_location.size());                        \
    context.instance_location.pop_back(                                        \
        step_category.relative_instance_location.size());                      \
  }                                                                            \
  if (step_category.dynamic) {                                                 \
    context.resources.pop_back();                                              \
  }                                                                            \
  SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                        \
  return result;

#define EVALUATE_END_NO_POP(step_category, step_type)                          \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Post, result, step,                       \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                        \
  return result;

#define EVALUATE_END_PASS_THROUGH(step_type)                                   \
  SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                        \
  return result;

#define EVALUATE_ANNOTATION(step_category, step_type, destination,             \
                            annotation_value)                                  \
  SOURCEMETA_TRACE_START(trace_id, STRINGIFY(step_type));                      \
  if (callback.has_value()) {                                                  \
    const auto &step_category{std::get<step_type>(step)};                      \
    context.evaluate_path.push_back(step_category.relative_schema_location);   \
    context.instance_location.push_back(                                       \
        step_category.relative_instance_location);                             \
    callback.value()(EvaluationType::Pre, true, step, context.evaluate_path,   \
                     destination, EvaluationContext::null);                    \
    callback.value()(EvaluationType::Post, true, step, context.evaluate_path,  \
                     destination, annotation_value);                           \
    context.evaluate_path.pop_back(                                            \
        step_category.relative_schema_location.size());                        \
    context.instance_location.pop_back(                                        \
        step_category.relative_instance_location.size());                      \
  }                                                                            \
  SOURCEMETA_TRACE_END(trace_id, STRINGIFY(step_type));                        \
  return true;

#define EVALUATE_FAIL                                                          \
  assert(false);                                                               \
  return false;

#define IS_STEP(step_type) InstructionIndex::step_type
#define HANDLER_START switch (static_cast<InstructionIndex>(step.index()))

#include "dispatch.h"

#undef IS_STEP
#undef HANDLER_START
#undef STRINGIFY
#undef EVALUATE_BEGIN
#undef EVALUATE_BEGIN_IF_STRING
#undef EVALUATE_BEGIN_TRY_TARGET
#undef EVALUATE_BEGIN_NO_PRECONDITION
#undef EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH
#undef EVALUATE_BEGIN_PASS_THROUGH
#undef EVALUATE_END
#undef EVALUATE_END_NO_POP
#undef EVALUATE_END_PASS_THROUGH
#undef EVALUATE_ANNOTATION
#undef EVALUATE_FAIL
}

inline auto
evaluate_internal(const sourcemeta::jsontoolkit::JSON &instance,
                  sourcemeta::blaze::EvaluationContext &context,
                  const sourcemeta::blaze::Instructions &steps,
                  const std::optional<sourcemeta::blaze::Callback> &callback)
    -> bool {
  bool overall{true};
  for (const auto &step : steps) {
    if (!evaluate_step(step, callback, instance, std::nullopt, 0, context)) {
      overall = false;
      break;
    }
  }

  // The evaluation path and instance location must be empty by the time
  // we are done, otherwise there was a frame push/pop mismatch
  assert(context.evaluate_path.empty());
  assert(context.instance_location.empty());
  assert(context.resources.empty());
  return overall;
}

} // namespace

namespace sourcemeta::blaze {

auto evaluate(const Instructions &steps,
              const sourcemeta::jsontoolkit::JSON &instance,
              const Callback &callback) -> bool {
  EvaluationContext context;
  return evaluate_internal(instance, context, steps, callback);
}

auto evaluate(const Instructions &steps,
              const sourcemeta::jsontoolkit::JSON &instance) -> bool {
  EvaluationContext context;
  return evaluate_internal(instance, context, steps, std::nullopt);
}

auto evaluate(const Instructions &steps,
              const sourcemeta::jsontoolkit::JSON &instance,
              EvaluationContext &context) -> bool {
  // Do a full reset for the next run
  assert(context.evaluate_path.empty());
  assert(context.instance_location.empty());
  assert(context.resources.empty());
  context.labels.clear();
  context.evaluated_.clear();

  return evaluate_internal(instance, context, steps, std::nullopt);
}

} // namespace sourcemeta::blaze
