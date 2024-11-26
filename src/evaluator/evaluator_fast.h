#ifndef SOURCEMETA_BLAZE_EVALUATOR_FAST_H_
#define SOURCEMETA_BLAZE_EVALUATOR_FAST_H_

#define EVALUATE_BEGIN(instruction_category, instruction_type, precondition)   \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto &target{resolve_target(                                           \
      property_target,                                                         \
      sourcemeta::jsontoolkit::get(                                            \
          instance, instruction_category.relative_instance_location))};        \
  if (!(precondition)) {                                                       \
    return true;                                                               \
  }                                                                            \
  constexpr bool track{false};                                                 \
  SOURCEMETA_MAYBE_UNUSED(track);                                              \
  bool result{false};

#define EVALUATE_BEGIN_NON_STRING(instruction_category, instruction_type,      \
                                  precondition)                                \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto &target{sourcemeta::jsontoolkit::get(                             \
      instance, instruction_category.relative_instance_location)};             \
  if (!(precondition)) {                                                       \
    return true;                                                               \
  }                                                                            \
  constexpr bool track{false};                                                 \
  SOURCEMETA_MAYBE_UNUSED(track);                                              \
  bool result{false};

#define EVALUATE_BEGIN_IF_STRING(instruction_category, instruction_type)       \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  const auto &maybe_target{                                                    \
      resolve_string_target(property_target, instance,                         \
                            instruction_category.relative_instance_location)}; \
  if (!maybe_target.has_value()) {                                             \
    return true;                                                               \
  }                                                                            \
  const auto &target{maybe_target.value().get()};                              \
  bool result{false};

#define EVALUATE_BEGIN_TRY_TARGET(instruction_category, instruction_type,      \
                                  precondition)                                \
  const auto &target{instance};                                                \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  if (!(precondition)) {                                                       \
    return true;                                                               \
  }                                                                            \
  auto target_check{                                                           \
      try_get(target, instruction_category.relative_instance_location)};       \
  if (!target_check.has_value()) {                                             \
    return true;                                                               \
  }                                                                            \
  assert(!instruction_category.relative_instance_location.empty());            \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION(instruction_category, instruction_type) \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  SOURCEMETA_MAYBE_UNUSED(instruction_category);                               \
  constexpr bool track{false};                                                 \
  SOURCEMETA_MAYBE_UNUSED(track);                                              \
  bool result{false};

#define EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(instruction_category,       \
                                                   instruction_type)           \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  bool result{true};

#define EVALUATE_BEGIN_PASS_THROUGH(instruction_category, instruction_type)    \
  const auto &instruction_category{std::get<instruction_type>(instruction)};   \
  bool result{true};

#define EVALUATE_END(instruction_category, instruction_type) return result;

#define EVALUATE_END_NO_POP(instruction_category, instruction_type)            \
  EVALUATE_END(instruction_category, instruction_type)

#define EVALUATE_END_PASS_THROUGH(instruction_type)                            \
  EVALUATE_END(instruction_category, instruction_type)

#define EVALUATE_ANNOTATION(instruction_category, instruction_type,            \
                            destination, annotation_value)                     \
  return true;

#define EVALUATE_RECURSE(child, target)                                        \
  evaluate_instruction(child, schema, std::nullopt, target, property_target,   \
                       depth + 1, evaluator)
#define EVALUATE_RECURSE_ON_PROPERTY_NAME(child, target, name)                 \
  evaluate_instruction(child, schema, std::nullopt, target, std::cref(name),   \
                       depth + 1, evaluator)

#define SOURCEMETA_EVALUATOR_FAST

namespace sourcemeta::blaze::fast {

auto evaluate_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Template &schema,
    const std::optional<sourcemeta::blaze::Callback> &,
    const sourcemeta::jsontoolkit::JSON &instance,
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const std::uint64_t depth, sourcemeta::blaze::Evaluator &evaluator)
    -> bool {
#include "dispatch.inc.h"
}

inline auto evaluate(const sourcemeta::jsontoolkit::JSON &instance,
                     sourcemeta::blaze::Evaluator &evaluator,
                     const sourcemeta::blaze::Template &schema) -> bool {
  for (const auto &instruction : schema.instructions) {
    if (!evaluate_instruction(instruction, schema, std::nullopt, instance,
                              std::nullopt, 0, evaluator)) {
      return false;
    }
  }

  return true;
}

} // namespace sourcemeta::blaze::fast

#undef SOURCEMETA_EVALUATOR_FAST

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
