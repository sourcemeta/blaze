#ifndef SOURCEMETA_BLAZE_EVALUATOR_FAST_H_
#define SOURCEMETA_BLAZE_EVALUATOR_FAST_H_

namespace sourcemeta::blaze {

auto evaluate_fast_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::jsontoolkit::JSON &instance,
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const std::uint64_t depth, sourcemeta::blaze::EvaluationContext &context)
    -> bool {

#define EVALUATE_BEGIN(instruction_category, instruction_type, precondition)   \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto &target{resolve_target(                                           \
      property_target,                                                         \
      sourcemeta::jsontoolkit::get(                                            \
          instance, instruction_category.relative_instance_location))};        \
  if (!(precondition)) {                                                       \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  constexpr bool track{false};                                                 \
  SOURCEMETA_MAYBE_UNUSED(track);                                              \
  bool result{false};

#define EVALUATE_BEGIN_IF_STRING(instruction_category, instruction_type)       \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto &maybe_target{                                                    \
      resolve_string_target(property_target, instance,                         \
                            instruction_category.relative_instance_location)}; \
  if (!maybe_target.has_value()) {                                             \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  const auto &target{maybe_target.value().get()};                              \
  bool result{false};

#define EVALUATE_BEGIN_TRY_TARGET(instruction_category, instruction_type,      \
                                  precondition)                                \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &target{instance};                                                \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  if (!(precondition)) {                                                       \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  auto target_check{                                                           \
      try_get(target, instruction_category.relative_instance_location)};       \
  if (!target_check.has_value()) {                                             \
    SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
    return true;                                                               \
  }                                                                            \
  assert(!instruction_category.relative_instance_location.empty());            \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION(instruction_category, instruction_type) \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  SOURCEMETA_MAYBE_UNUSED(instruction_category);                               \
  constexpr bool track{false};                                                 \
  SOURCEMETA_MAYBE_UNUSED(track);                                              \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(instruction_category,       \
                                                   instruction_type)           \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  bool result{true};

#define EVALUATE_BEGIN_PASS_THROUGH(instruction_category, instruction_type)    \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  bool result{true};

#define EVALUATE_END(instruction_category, instruction_type)                   \
  SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));      \
  return result;

#define EVALUATE_END_NO_POP(instruction_category, instruction_type)            \
  EVALUATE_END(instruction_category, instruction_type)

#define EVALUATE_END_PASS_THROUGH(instruction_type)                            \
  EVALUATE_END(instruction_category, instruction_type)

#define EVALUATE_ANNOTATION(instruction_category, instruction_type,            \
                            destination, annotation_value)                     \
  SOURCEMETA_TRACE_START(trace_id, SOURCEMETA_STRINGIFY(instruction_type));    \
  SOURCEMETA_TRACE_END(trace_id, SOURCEMETA_STRINGIFY(instruction_type));      \
  return true;

#define EVALUATE_RECURSE(child, target)                                        \
  evaluate_fast_instruction(child, target, property_target, depth + 1, context)
#define EVALUATE_RECURSE_ON_PROPERTY_NAME(child, target, name)                 \
  evaluate_fast_instruction(child, target, std::cref(name), depth + 1, context)

#define SOURCEMETA_EVALUATOR_FAST
#include "dispatch.inc.h"
#undef SOURCEMETA_EVALUATOR_FAST

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
#undef EVALUATE_RECURSE
#undef EVALUATE_RECURSE_ON_PROPERTY_NAME
}

inline auto evaluate_fast(const sourcemeta::jsontoolkit::JSON &instance,
                          sourcemeta::blaze::EvaluationContext &context,
                          const sourcemeta::blaze::Instructions &instructions)
    -> bool {
  for (const auto &instruction : instructions) {
    // TODO: Can we avoid taking the context on the first place?
    if (!evaluate_fast_instruction(instruction, instance, std::nullopt, 0,
                                   context)) {
      return false;
    }
  }

  return true;
}

} // namespace sourcemeta::blaze

#endif
