#ifndef SOURCEMETA_BLAZE_EVALUATOR_COMPLETE_H_
#define SOURCEMETA_BLAZE_EVALUATOR_COMPLETE_H_

#define EVALUATE_BEGIN(instruction_category, instruction_type, precondition)   \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto track{schema.track || callback.has_value()};                      \
  if (track) {                                                                 \
    context.evaluate_path.push_back(                                           \
        instruction_category.relative_schema_location);                        \
    context.instance_location.push_back(                                       \
        instruction_category.relative_instance_location);                      \
  }                                                                            \
  if (schema.dynamic) {                                                        \
    context.resources.push_back(instruction_category.schema_resource);         \
  }                                                                            \
  const auto &target{resolve_target(                                           \
      property_target,                                                         \
      sourcemeta::jsontoolkit::get(                                            \
          instance, instruction_category.relative_instance_location))};        \
  if (!(precondition)) {                                                       \
    if (track) {                                                               \
      context.evaluate_path.pop_back(                                          \
          instruction_category.relative_schema_location.size());               \
      context.instance_location.pop_back(                                      \
          instruction_category.relative_instance_location.size());             \
    }                                                                          \
    if (schema.dynamic) {                                                      \
      context.resources.pop_back();                                            \
    }                                                                          \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_NON_STRING(instruction_category, instruction_type,      \
                                  precondition)                                \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto track{schema.track || callback.has_value()};                      \
  if (track) {                                                                 \
    context.evaluate_path.push_back(                                           \
        instruction_category.relative_schema_location);                        \
    context.instance_location.push_back(                                       \
        instruction_category.relative_instance_location);                      \
  }                                                                            \
  if (schema.dynamic) {                                                        \
    context.resources.push_back(instruction_category.schema_resource);         \
  }                                                                            \
  const auto &target{sourcemeta::jsontoolkit::get(                             \
      instance, instruction_category.relative_instance_location)};             \
  if (!(precondition)) {                                                       \
    if (track) {                                                               \
      context.evaluate_path.pop_back(                                          \
          instruction_category.relative_schema_location.size());               \
      context.instance_location.pop_back(                                      \
          instruction_category.relative_instance_location.size());             \
    }                                                                          \
    if (schema.dynamic) {                                                      \
      context.resources.pop_back();                                            \
    }                                                                          \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_IF_STRING(instruction_category, instruction_type)       \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto track{schema.track || callback.has_value()};                      \
  if (track) {                                                                 \
    context.evaluate_path.push_back(                                           \
        instruction_category.relative_schema_location);                        \
    context.instance_location.push_back(                                       \
        instruction_category.relative_instance_location);                      \
  }                                                                            \
  if (schema.dynamic) {                                                        \
    context.resources.push_back(instruction_category.schema_resource);         \
  }                                                                            \
  const auto &maybe_target{                                                    \
      resolve_string_target(property_target, instance,                         \
                            instruction_category.relative_instance_location)}; \
  if (!maybe_target.has_value()) {                                             \
    if (track) {                                                               \
      context.evaluate_path.pop_back(                                          \
          instruction_category.relative_schema_location.size());               \
      context.instance_location.pop_back(                                      \
          instruction_category.relative_instance_location.size());             \
    }                                                                          \
    if (schema.dynamic) {                                                      \
      context.resources.pop_back();                                            \
    }                                                                          \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  const auto &target{maybe_target.value().get()};                              \
  bool result{false};

// This is a slightly complicated dance to avoid traversing the relative
// instance location twice.
#define EVALUATE_BEGIN_TRY_TARGET(instruction_category, instruction_type,      \
                                  precondition)                                \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &target{instance};                                                \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  if (!(precondition)) {                                                       \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  const auto target_check{                                                     \
      try_get(target, instruction_category.relative_instance_location)};       \
  if (!target_check.has_value()) {                                             \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  const auto track{schema.track || callback.has_value()};                      \
  if (track) {                                                                 \
    context.evaluate_path.push_back(                                           \
        instruction_category.relative_schema_location);                        \
    context.instance_location.push_back(                                       \
        instruction_category.relative_instance_location);                      \
  }                                                                            \
  if (schema.dynamic) {                                                        \
    context.resources.push_back(instruction_category.schema_resource);         \
  }                                                                            \
  assert(!instruction_category.relative_instance_location.empty());            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION(instruction_category, instruction_type) \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto track{schema.track || callback.has_value()};                      \
  if (track) {                                                                 \
    context.evaluate_path.push_back(                                           \
        instruction_category.relative_schema_location);                        \
    context.instance_location.push_back(                                       \
        instruction_category.relative_instance_location);                      \
  }                                                                            \
  if (schema.dynamic) {                                                        \
    context.resources.push_back(instruction_category.schema_resource);         \
  }                                                                            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(instruction_category,       \
                                                   instruction_type)           \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  bool result{true};

#define EVALUATE_BEGIN_PASS_THROUGH(instruction_category, instruction_type)    \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  bool result{true};

#define EVALUATE_END(instruction_category, instruction_type)                   \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Post, result, instruction,                \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  if (track) {                                                                 \
    context.evaluate_path.pop_back(                                            \
        instruction_category.relative_schema_location.size());                 \
    context.instance_location.pop_back(                                        \
        instruction_category.relative_instance_location.size());               \
  }                                                                            \
  if (schema.dynamic) {                                                        \
    context.resources.pop_back();                                              \
  }                                                                            \
  SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));      \
  return result;

#define EVALUATE_END_NO_POP(instruction_category, instruction_type)            \
  if (callback.has_value()) {                                                  \
    callback.value()(EvaluationType::Post, result, instruction,                \
                     context.evaluate_path, context.instance_location,         \
                     EvaluationContext::null);                                 \
  }                                                                            \
  SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));      \
  return result;

#define EVALUATE_END_PASS_THROUGH(instruction_type)                            \
  SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));      \
  return result;

#define EVALUATE_ANNOTATION(instruction_category, instruction_type,            \
                            destination, annotation_value)                     \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  if (callback.has_value()) {                                                  \
    const auto &instruction_category{std::get<instruction_type>(instruction)}; \
    context.evaluate_path.push_back(                                           \
        instruction_category.relative_schema_location);                        \
    context.instance_location.push_back(                                       \
        instruction_category.relative_instance_location);                      \
    callback.value()(EvaluationType::Pre, true, instruction,                   \
                     context.evaluate_path, destination,                       \
                     EvaluationContext::null);                                 \
    callback.value()(EvaluationType::Post, true, instruction,                  \
                     context.evaluate_path, destination, annotation_value);    \
    context.evaluate_path.pop_back(                                            \
        instruction_category.relative_schema_location.size());                 \
    context.instance_location.pop_back(                                        \
        instruction_category.relative_instance_location.size());               \
  }                                                                            \
  SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));      \
  return true;

#define EVALUATE_RECURSE(child, target)                                        \
  evaluate_complete_instruction(child, schema, callback, target,               \
                                property_target, depth + 1, context)
#define EVALUATE_RECURSE_ON_PROPERTY_NAME(child, target, name)                 \
  evaluate_complete_instruction(child, schema, callback, target,               \
                                std::cref(name), depth + 1, context)

#define SOURCEMETA_EVALUATOR_COMPLETE

namespace sourcemeta::blaze {

auto evaluate_complete_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Template &schema,
    const std::optional<sourcemeta::blaze::Callback> &callback,
    const sourcemeta::jsontoolkit::JSON &instance,
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const std::uint64_t depth, sourcemeta::blaze::EvaluationContext &context)
    -> bool {
#include "dispatch.inc.h"
}

inline auto
evaluate_complete(const sourcemeta::jsontoolkit::JSON &instance,
                  sourcemeta::blaze::EvaluationContext &context,
                  const sourcemeta::blaze::Template &schema,
                  const std::optional<sourcemeta::blaze::Callback> &callback)
    -> bool {
  bool overall{true};
  for (const auto &instruction : schema.instructions) {
    if (!evaluate_complete_instruction(instruction, schema, callback, instance,
                                       std::nullopt, 0, context)) {
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

} // namespace sourcemeta::blaze

#undef SOURCEMETA_EVALUATOR_COMPLETE

#undef EVALUATE_BEGIN
#undef EVALUATE_BEGIN_NON_STRING
#undef EVALUATE_BEGIN_IF_STRING
#undef EVALUATE_BEGIN_TRY_TARGET
#undef EVALUATE_BEGIN_NO_PRECONDITION
#undef EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH
#undef EVALUATE_BEGIN_PASS_THROUGH
#undef EVALUATE_END
#undef EVALUATE_END_NO_POP
#undef EVALUATE_END_PASS_THROUGH
#undef EVALUATE_ANNOTATION
#undef EVALUATE_RECURSE
#undef EVALUATE_RECURSE_ON_PROPERTY_NAME

#endif
