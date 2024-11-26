auto evaluate_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Template &schema,
    const std::optional<sourcemeta::blaze::Callback> &callback,
    const sourcemeta::jsontoolkit::JSON &instance,
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const std::uint64_t depth, sourcemeta::blaze::Evaluator &evaluator) -> bool;

#define INSTRUCTION_HANDLER(name)                                              \
  static inline auto name(                                                     \
      const sourcemeta::blaze::Instruction &instruction,                       \
      const sourcemeta::blaze::Template &schema,                               \
      const std::optional<sourcemeta::blaze::Callback> &callback,              \
      const sourcemeta::jsontoolkit::JSON &instance,                           \
      const std::optional<                                                     \
          std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>> \
          &property_target,                                                    \
      const std::uint64_t depth, sourcemeta::blaze::Evaluator &evaluator)      \
      -> bool

// TODO: Cleanup this file, mainly its MAYBE_UNUSED macros

INSTRUCTION_HANDLER(AssertionFail) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionFail);
  EVALUATE_END(assertion, AssertionFail);
}

INSTRUCTION_HANDLER(AssertionDefines) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionDefines, target.is_object());
  result = target.defines(assertion.value);
  EVALUATE_END(assertion, AssertionDefines);
}

INSTRUCTION_HANDLER(AssertionDefinesStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionDefinesStrict);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = target.is_object() && target.defines(assertion.value);
  EVALUATE_END(assertion, AssertionDefinesStrict);
}

INSTRUCTION_HANDLER(AssertionDefinesAll) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionDefinesAll, target.is_object());

  // Otherwise we are we even emitting this instruction?
  assert(assertion.value.size() > 1);

  // Otherwise there is no way the instance can satisfy it anyway
  if (assertion.value.size() <= target.object_size()) {
    result = true;
    for (const auto &property : assertion.value) {
      if (!target.defines(property)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(assertion, AssertionDefinesAll);
}

INSTRUCTION_HANDLER(AssertionDefinesAllStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionDefinesAllStrict);
  const auto &target{get(instance, assertion.relative_instance_location)};

  // Otherwise we are we even emitting this instruction?
  assert(assertion.value.size() > 1);

  // Otherwise there is no way the instance can satisfy it anyway
  if (target.is_object() && assertion.value.size() <= target.object_size()) {
    result = true;
    for (const auto &property : assertion.value) {
      if (!target.defines(property)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(assertion, AssertionDefinesAllStrict);
}

INSTRUCTION_HANDLER(AssertionDefinesExactly) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionDefinesExactly,
                            target.is_object());

  // Otherwise we are we even emitting this instruction?
  assert(assertion.value.size() > 1);

  if (assertion.value.size() == target.object_size()) {
    result = true;
    for (const auto &property : assertion.value) {
      if (!target.defines(property)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(assertion, AssertionDefinesExactly);
}

INSTRUCTION_HANDLER(AssertionDefinesExactlyStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionDefinesExactlyStrict);
  const auto &target{get(instance, assertion.relative_instance_location)};

  // Otherwise we are we even emitting this instruction?
  assert(assertion.value.size() > 1);

  if (target.is_object() && assertion.value.size() == target.object_size()) {
    result = true;
    for (const auto &property : assertion.value) {
      if (!target.defines(property)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(assertion, AssertionDefinesExactlyStrict);
}

INSTRUCTION_HANDLER(AssertionPropertyDependencies) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionPropertyDependencies,
                            target.is_object());
  // Otherwise we are we even emitting this instruction?
  assert(!assertion.value.empty());
  result = true;
  for (const auto &[property, dependencies] : assertion.value) {
    if (!target.defines(property)) {
      continue;
    }

    assert(!dependencies.empty());
    for (const auto &dependency : dependencies) {
      if (!target.defines(dependency)) {
        result = false;
        EVALUATE_END(assertion, AssertionPropertyDependencies);
      }
    }
  }

  EVALUATE_END(assertion, AssertionPropertyDependencies);
}

INSTRUCTION_HANDLER(AssertionType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionType);
  const auto &target{get(instance, assertion.relative_instance_location)};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  result = target.type() == assertion.value ||
           (assertion.value == JSON::Type::Integer && target.is_integer_real());
  EVALUATE_END(assertion, AssertionType);
}

INSTRUCTION_HANDLER(AssertionTypeAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeAny);
  // Otherwise we are we even emitting this instruction?
  assert(assertion.value.size() > 1);
  const auto &target{get(instance, assertion.relative_instance_location)};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  for (const auto type : assertion.value) {
    if (type == JSON::Type::Integer && target.is_integer_real()) {
      result = true;
      break;
    } else if (type == target.type()) {
      result = true;
      break;
    }
  }

  EVALUATE_END(assertion, AssertionTypeAny);
}

INSTRUCTION_HANDLER(AssertionTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStrict);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = target.type() == assertion.value;
  EVALUATE_END(assertion, AssertionTypeStrict);
}

INSTRUCTION_HANDLER(AssertionTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStrictAny);
  // Otherwise we are we even emitting this instruction?
  assert(assertion.value.size() > 1);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = (std::find(assertion.value.cbegin(), assertion.value.cend(),
                      target.type()) != assertion.value.cend());
  EVALUATE_END(assertion, AssertionTypeStrictAny);
}

INSTRUCTION_HANDLER(AssertionTypeStringBounded) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStringBounded);
  const auto &target{get(instance, assertion.relative_instance_location)};
  const auto minimum{std::get<0>(assertion.value)};
  const auto maximum{std::get<1>(assertion.value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  // Require early breaking
  assert(!std::get<2>(assertion.value));
  result = target.type() == JSON::Type::String &&
           target.string_size() >= minimum &&
           (!maximum.has_value() || target.string_size() <= maximum.value());
  EVALUATE_END(assertion, AssertionTypeStringBounded);
}

INSTRUCTION_HANDLER(AssertionTypeStringUpper) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStringUpper);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = target.is_string() && target.string_size() <= assertion.value;
  EVALUATE_END(assertion, AssertionTypeStringUpper);
}

INSTRUCTION_HANDLER(AssertionTypeArrayBounded) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeArrayBounded);
  const auto &target{get(instance, assertion.relative_instance_location)};
  const auto minimum{std::get<0>(assertion.value)};
  const auto maximum{std::get<1>(assertion.value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  // Require early breaking
  assert(!std::get<2>(assertion.value));
  result = target.type() == JSON::Type::Array &&
           target.array_size() >= minimum &&
           (!maximum.has_value() || target.array_size() <= maximum.value());
  EVALUATE_END(assertion, AssertionTypeArrayBounded);
}

INSTRUCTION_HANDLER(AssertionTypeArrayUpper) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeArrayUpper);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = target.is_array() && target.array_size() <= assertion.value;
  EVALUATE_END(assertion, AssertionTypeArrayUpper);
}

INSTRUCTION_HANDLER(AssertionTypeObjectBounded) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeObjectBounded);
  const auto &target{get(instance, assertion.relative_instance_location)};
  const auto minimum{std::get<0>(assertion.value)};
  const auto maximum{std::get<1>(assertion.value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  // Require early breaking
  assert(!std::get<2>(assertion.value));
  result = target.type() == JSON::Type::Object &&
           target.object_size() >= minimum &&
           (!maximum.has_value() || target.object_size() <= maximum.value());
  EVALUATE_END(assertion, AssertionTypeObjectBounded);
}

INSTRUCTION_HANDLER(AssertionTypeObjectUpper) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeObjectUpper);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = target.is_object() && target.object_size() <= assertion.value;
  EVALUATE_END(assertion, AssertionTypeObjectUpper);
}

INSTRUCTION_HANDLER(AssertionRegex) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(assertion, AssertionRegex);
  result = matches(assertion.value.first, target);
  EVALUATE_END(assertion, AssertionRegex);
}

INSTRUCTION_HANDLER(AssertionStringSizeLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(assertion, AssertionStringSizeLess);
  result = (JSON::size(target) < assertion.value);
  EVALUATE_END(assertion, AssertionStringSizeLess);
}

INSTRUCTION_HANDLER(AssertionStringSizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(assertion, AssertionStringSizeGreater);
  result = (JSON::size(target) > assertion.value);
  EVALUATE_END(assertion, AssertionStringSizeGreater);
}

INSTRUCTION_HANDLER(AssertionArraySizeLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionArraySizeLess,
                            target.is_array());
  result = (target.array_size() < assertion.value);
  EVALUATE_END(assertion, AssertionArraySizeLess);
}

INSTRUCTION_HANDLER(AssertionArraySizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionArraySizeGreater,
                            target.is_array());
  result = (target.array_size() > assertion.value);
  EVALUATE_END(assertion, AssertionArraySizeGreater);
}

INSTRUCTION_HANDLER(AssertionObjectSizeLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionObjectSizeLess,
                            target.is_object());
  result = (target.object_size() < assertion.value);
  EVALUATE_END(assertion, AssertionObjectSizeLess);
}

INSTRUCTION_HANDLER(AssertionObjectSizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionObjectSizeGreater,
                            target.is_object());
  result = (target.object_size() > assertion.value);
  EVALUATE_END(assertion, AssertionObjectSizeGreater);
}

INSTRUCTION_HANDLER(AssertionEqual) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionEqual);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = (target == assertion.value);
  EVALUATE_END(assertion, AssertionEqual);
}

INSTRUCTION_HANDLER(AssertionEqualsAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionEqualsAny);
  const auto &target{get(instance, assertion.relative_instance_location)};
  result = assertion.value.contains(target);
  EVALUATE_END(assertion, AssertionEqualsAny);
}

INSTRUCTION_HANDLER(AssertionGreaterEqual) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionGreaterEqual,
                            target.is_number());
  result = target >= assertion.value;
  EVALUATE_END(assertion, AssertionGreaterEqual);
}

INSTRUCTION_HANDLER(AssertionLessEqual) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionLessEqual, target.is_number());
  result = target <= assertion.value;
  EVALUATE_END(assertion, AssertionLessEqual);
}

INSTRUCTION_HANDLER(AssertionGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionGreater, target.is_number());
  result = target > assertion.value;
  EVALUATE_END(assertion, AssertionGreater);
}

INSTRUCTION_HANDLER(AssertionLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionLess, target.is_number());
  result = target < assertion.value;
  EVALUATE_END(assertion, AssertionLess);
}

INSTRUCTION_HANDLER(AssertionUnique) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionUnique, target.is_array());
  result = target.unique();
  EVALUATE_END(assertion, AssertionUnique);
}

INSTRUCTION_HANDLER(AssertionDivisible) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionDivisible, target.is_number());
  assert(assertion.value.is_number());
  result = target.divisible_by(assertion.value);
  EVALUATE_END(assertion, AssertionDivisible);
}

INSTRUCTION_HANDLER(AssertionStringType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(assertion, AssertionStringType);
  switch (assertion.value) {
    case ValueStringType::URI:
      try {
        // TODO: This implies a string copy
        result = URI{target}.is_absolute();
      } catch (const URIParseError &) {
        result = false;
      }

      break;
    default:
      // We should never get here
      assert(false);
  }

  EVALUATE_END(assertion, AssertionStringType);
}

INSTRUCTION_HANDLER(AssertionPropertyType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyType,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  const auto &effective_target{target_check.value().get()};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  result = effective_target.type() == assertion.value ||
           (assertion.value == JSON::Type::Integer &&
            effective_target.is_integer_real());
  EVALUATE_END(assertion, AssertionPropertyType);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeEvaluate,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  const auto &effective_target{target_check.value().get()};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  result = effective_target.type() == assertion.value ||
           (assertion.value == JSON::Type::Integer &&
            effective_target.is_integer_real());

  if (result) {
    evaluator.evaluate();
  }

  EVALUATE_END(assertion, AssertionPropertyTypeEvaluate);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrict,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  result = target_check.value().get().type() == assertion.value;
  EVALUATE_END(assertion, AssertionPropertyTypeStrict);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrictEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrictEvaluate,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  result = target_check.value().get().type() == assertion.value;

  if (result) {
    evaluator.evaluate();
  }

  EVALUATE_END(assertion, AssertionPropertyTypeStrictEvaluate);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrictAny,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  result =
      (std::find(assertion.value.cbegin(), assertion.value.cend(),
                 target_check.value().get().type()) != assertion.value.cend());
  EVALUATE_END(assertion, AssertionPropertyTypeStrictAny);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrictAnyEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrictAnyEvaluate,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  result =
      (std::find(assertion.value.cbegin(), assertion.value.cend(),
                 target_check.value().get().type()) != assertion.value.cend());

  if (result) {
    evaluator.evaluate();
  }

  EVALUATE_END(assertion, AssertionPropertyTypeStrictAnyEvaluate);
}

INSTRUCTION_HANDLER(AssertionArrayPrefix) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionArrayPrefix, target.is_array());
  // Otherwise there is no point in emitting this instruction
  assert(!assertion.children.empty());
  result = target.empty();
  const auto prefixes{assertion.children.size() - 1};
  const auto array_size{target.array_size()};
  if (!result) [[likely]] {
    const auto pointer{
        array_size == prefixes ? prefixes : std::min(array_size, prefixes) - 1};
    const auto &entry{assertion.children[pointer]};
    result = true;
    assert(std::holds_alternative<sourcemeta::blaze::ControlGroup>(entry));
    for (const auto &child :
         std::get<sourcemeta::blaze::ControlGroup>(entry).children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(assertion, AssertionArrayPrefix);
}

INSTRUCTION_HANDLER(AssertionArrayPrefixEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(assertion, AssertionArrayPrefixEvaluate,
                            target.is_array());
  // Otherwise there is no point in emitting this instruction
  assert(!assertion.children.empty());
  result = target.empty();
  const auto prefixes{assertion.children.size() - 1};
  const auto array_size{target.array_size()};
  if (!result) [[likely]] {
    const auto pointer{
        array_size == prefixes ? prefixes : std::min(array_size, prefixes) - 1};
    const auto &entry{assertion.children[pointer]};
    result = true;
    assert(std::holds_alternative<sourcemeta::blaze::ControlGroup>(entry));
    for (const auto &child :
         std::get<sourcemeta::blaze::ControlGroup>(entry).children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        EVALUATE_END(assertion, AssertionArrayPrefixEvaluate);
      }
    }

    assert(result);
    if (array_size == prefixes) {
      evaluator.evaluate();
    } else {
      evaluator.evaluate(0, pointer);
    }
  }

  EVALUATE_END(assertion, AssertionArrayPrefixEvaluate);
}

INSTRUCTION_HANDLER(LogicalOr) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalOr);
  result = logical.children.empty();
  const auto &target{get(instance, logical.relative_instance_location)};
  for (const auto &child : logical.children) {
    if (EVALUATE_RECURSE(child, target)) {
      result = true;
      // This boolean value controls whether we should be exhaustive
      if (!logical.value) {
        break;
      }
    }
  }

  EVALUATE_END(logical, LogicalOr);
}

INSTRUCTION_HANDLER(LogicalAnd) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalAnd);
  result = true;
  const auto &target{get(instance, logical.relative_instance_location)};
  for (const auto &child : logical.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(logical, LogicalAnd);
}

INSTRUCTION_HANDLER(LogicalWhenType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN(logical, LogicalWhenType, target.type() == logical.value);
  result = true;
  for (const auto &child : logical.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(logical, LogicalWhenType);
}

INSTRUCTION_HANDLER(LogicalWhenDefines) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(logical, LogicalWhenDefines,
                            target.is_object() &&
                                target.defines(logical.value));
  result = true;
  for (const auto &child : logical.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(logical, LogicalWhenDefines);
}

INSTRUCTION_HANDLER(LogicalWhenArraySizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(logical, LogicalWhenArraySizeGreater,
                            target.is_array() &&
                                target.array_size() > logical.value);
  result = true;
  for (const auto &child : logical.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(logical, LogicalWhenArraySizeGreater);
}

INSTRUCTION_HANDLER(LogicalXor) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalXor);
  result = true;
  bool has_matched{false};
  const auto &target{get(instance, logical.relative_instance_location)};
  for (const auto &child : logical.children) {
    if (EVALUATE_RECURSE(child, target)) {
      if (has_matched) {
        result = false;
        // This boolean value controls whether we should be exhaustive
        if (!logical.value) {
          break;
        }
      } else {
        has_matched = true;
      }
    }
  }

  result = result && has_matched;
  EVALUATE_END(logical, LogicalXor);
}

INSTRUCTION_HANDLER(LogicalCondition) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalCondition);
  result = true;
  const auto children_size{logical.children.size()};
  assert(children_size >= logical.value.first);
  assert(children_size >= logical.value.second);

  auto condition_end{children_size};
  if (logical.value.first > 0) {
    condition_end = logical.value.first;
  } else if (logical.value.second > 0) {
    condition_end = logical.value.second;
  }

  const auto &target{get(instance, logical.relative_instance_location)};
  for (std::size_t cursor = 0; cursor < condition_end; cursor++) {
    if (!EVALUATE_RECURSE(logical.children[cursor], target)) {
      result = false;
      break;
    }
  }

  const auto consequence_start{result ? logical.value.first
                                      : logical.value.second};
  const auto consequence_end{(result && logical.value.second > 0)
                                 ? logical.value.second
                                 : children_size};
  result = true;
  if (consequence_start > 0) {
    if (track) {
      evaluator.evaluate_path.pop_back(logical.relative_schema_location.size());

      for (auto cursor = consequence_start; cursor < consequence_end;
           cursor++) {
        if (!EVALUATE_RECURSE(logical.children[cursor], instance)) {
          result = false;
          break;
        }
      }

      evaluator.evaluate_path.push_back(logical.relative_schema_location);
    } else {
      for (auto cursor = consequence_start; cursor < consequence_end;
           cursor++) {
        if (!EVALUATE_RECURSE(logical.children[cursor], instance)) {
          result = false;
          break;
        }
      }
    }
  }

  EVALUATE_END(logical, LogicalCondition);
}

INSTRUCTION_HANDLER(ControlGroup) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_PASS_THROUGH(control, ControlGroup);
  for (const auto &child : control.children) {
    if (!EVALUATE_RECURSE(child, instance)) {
      result = false;
      break;
    }
  }

  EVALUATE_END_PASS_THROUGH(ControlGroup);
}

INSTRUCTION_HANDLER(ControlGroupWhenDefines) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_PASS_THROUGH(control, ControlGroupWhenDefines);
  assert(!control.children.empty());
  // Otherwise why are we emitting this property?
  assert(!control.relative_instance_location.empty());
  const auto &target{get(instance, control.relative_instance_location)};
  if (target.is_object() && target.defines(control.value)) {
    for (const auto &child : control.children) {
      // Note that in this control instruction, we purposely
      // don't navigate into the target
      if (!EVALUATE_RECURSE(child, instance)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END_PASS_THROUGH(ControlGroupWhenDefines);
}

INSTRUCTION_HANDLER(ControlGroupWhenDefinesDirect) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_PASS_THROUGH(control, ControlGroupWhenDefinesDirect);
  assert(!control.children.empty());
  assert(control.relative_instance_location.empty());
  if (instance.is_object() && instance.defines(control.value)) {
    for (const auto &child : control.children) {
      if (!EVALUATE_RECURSE(child, instance)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END_PASS_THROUGH(ControlGroupWhenDefinesDirect);
}

INSTRUCTION_HANDLER(ControlLabel) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(control, ControlLabel);
  assert(!control.children.empty());
  evaluator.labels.try_emplace(control.value, control.children);
  const auto &target{get(instance, control.relative_instance_location)};
  result = true;
  for (const auto &child : control.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(control, ControlLabel);
}

INSTRUCTION_HANDLER(ControlMark) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(control, ControlMark);
  evaluator.labels.try_emplace(control.value, control.children);
  EVALUATE_END_NO_POP(control, ControlMark);
}

INSTRUCTION_HANDLER(ControlEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_PASS_THROUGH(control, ControlEvaluate);
  SOURCEMETA_MAYBE_UNUSED(control);

#ifdef SOURCEMETA_EVALUATOR_COMPLETE
  if (callback.has_value()) {
    // TODO: Optimize this case to avoid an extra pointer copy
    auto destination = evaluator.instance_location;
    destination.push_back(control.value);
    callback.value()(EvaluationType::Pre, true, instruction,
                     evaluator.evaluate_path, destination, Evaluator::null);
    evaluator.evaluate(control.value);
    callback.value()(EvaluationType::Post, true, instruction,
                     evaluator.evaluate_path, destination, Evaluator::null);
  } else {
    evaluator.evaluate(control.value);
  }
#else
#endif

  EVALUATE_END_PASS_THROUGH(ControlEvaluate);
}

INSTRUCTION_HANDLER(ControlJump) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(control, ControlJump);
  result = true;
  assert(evaluator.labels.contains(control.value));
  const auto &target{get(instance, control.relative_instance_location)};
  for (const auto &child : evaluator.labels.at(control.value).get()) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(control, ControlJump);
}

INSTRUCTION_HANDLER(ControlDynamicAnchorJump) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(control, ControlDynamicAnchorJump);
  result = false;
  const auto &target{get(instance, control.relative_instance_location)};
  for (const auto &resource : evaluator.resources) {
    const auto label{evaluator.hash(resource, control.value)};
    const auto match{evaluator.labels.find(label)};
    if (match != evaluator.labels.cend()) {
      result = true;
      for (const auto &child : match->second.get()) {
        if (!EVALUATE_RECURSE(child, target)) {
          result = false;
          EVALUATE_END(control, ControlDynamicAnchorJump);
        }
      }

      break;
    }
  }

  EVALUATE_END(control, ControlDynamicAnchorJump);
}

INSTRUCTION_HANDLER(AnnotationEmit) {
  SOURCEMETA_MAYBE_UNUSED(instruction);
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_ANNOTATION(annotation, AnnotationEmit, evaluator.instance_location,
                      annotation.value);
}

INSTRUCTION_HANDLER(AnnotationToParent) {
  SOURCEMETA_MAYBE_UNUSED(instruction);
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_ANNOTATION(
      annotation, AnnotationToParent,
      // TODO: Can we avoid a copy of the instance location here?
      evaluator.instance_location.initial(), annotation.value);
}

INSTRUCTION_HANDLER(AnnotationBasenameToParent) {
  SOURCEMETA_MAYBE_UNUSED(instruction);
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_ANNOTATION(
      annotation, AnnotationBasenameToParent,
      // TODO: Can we avoid a copy of the instance location here?
      evaluator.instance_location.initial(),
      evaluator.instance_location.back().to_json());
}

INSTRUCTION_HANDLER(LogicalNot) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalNot);

  const auto &target{get(instance, logical.relative_instance_location)};
  for (const auto &child : logical.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = true;
      break;
    }
  }

  EVALUATE_END(logical, LogicalNot);
}

INSTRUCTION_HANDLER(LogicalNotEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalNotEvaluate);

  const auto &target{get(instance, logical.relative_instance_location)};
  for (const auto &child : logical.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = true;
      break;
    }
  }

  evaluator.unevaluate();

  EVALUATE_END(logical, LogicalNotEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesUnevaluated) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesUnevaluated,
                            target.is_object());
  assert(!loop.children.empty());
  result = true;

  for (const auto &entry : target.as_object()) {
    if (evaluator.is_evaluated({entry.first})) {
      continue;
    }

    evaluator.instance_location.push_back(entry.first);
    const auto &new_instance{target.at(entry.first)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        evaluator.instance_location.pop_back();
        EVALUATE_END(loop, LoopPropertiesUnevaluated);
      }
    }

    evaluator.instance_location.pop_back();
  }

  // Mark the entire object as evaluated
  evaluator.evaluate();

  EVALUATE_END(loop, LoopPropertiesUnevaluated);
}

INSTRUCTION_HANDLER(LoopPropertiesUnevaluatedExcept) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesUnevaluatedExcept,
                            target.is_object());
  assert(!loop.children.empty());
  result = true;
  // Otherwise why emit this instruction?
  assert(!std::get<0>(loop.value).empty() || !std::get<1>(loop.value).empty() ||
         !std::get<2>(loop.value).empty());

  for (const auto &entry : target.as_object()) {
    if (std::get<0>(loop.value).contains(entry.first)) {
      continue;
    }

    if (std::any_of(std::get<1>(loop.value).cbegin(),
                    std::get<1>(loop.value).cend(),
                    [&entry](const auto &prefix) {
                      return entry.first.starts_with(prefix);
                    })) {
      continue;
    }

    if (std::any_of(std::get<2>(loop.value).cbegin(),
                    std::get<2>(loop.value).cend(),
                    [&entry](const auto &pattern) {
                      return matches(pattern.first, entry.first);
                    })) {
      continue;
    }

    if (evaluator.is_evaluated({entry.first})) {
      continue;
    }

    evaluator.instance_location.push_back(entry.first);
    const auto &new_instance{target.at(entry.first)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        evaluator.instance_location.pop_back();
        EVALUATE_END(loop, LoopPropertiesUnevaluatedExcept);
      }
    }

    evaluator.instance_location.pop_back();
  }

  // Mark the entire object as evaluated
  evaluator.evaluate();

  EVALUATE_END(loop, LoopPropertiesUnevaluatedExcept);
}

INSTRUCTION_HANDLER(LoopPropertiesMatch) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesMatch, target.is_object());
  assert(!loop.value.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    const auto index{loop.value.find(entry.first)};
    if (index == loop.value.cend()) {
      continue;
    }

    const auto &subinstruction{loop.children[index->second]};
    assert(std::holds_alternative<sourcemeta::blaze::ControlGroup>(
        subinstruction));
    for (const auto &child :
         std::get<sourcemeta::blaze::ControlGroup>(subinstruction).children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        EVALUATE_END(loop, LoopPropertiesMatch);
      }
    }
  }

  EVALUATE_END(loop, LoopPropertiesMatch);
}

INSTRUCTION_HANDLER(LoopPropertiesMatchClosed) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesMatchClosed,
                            target.is_object());
  assert(!loop.value.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    const auto index{loop.value.find(entry.first)};
    if (index == loop.value.cend()) {
      result = false;
      break;
    }

    const auto &subinstruction{loop.children[index->second]};
    assert(std::holds_alternative<sourcemeta::blaze::ControlGroup>(
        subinstruction));
    for (const auto &child :
         std::get<sourcemeta::blaze::ControlGroup>(subinstruction).children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        EVALUATE_END(loop, LoopPropertiesMatchClosed);
      }
    }
  }

  EVALUATE_END(loop, LoopPropertiesMatchClosed);
}

INSTRUCTION_HANDLER(LoopProperties) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopProperties, target.is_object());
  assert(!loop.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    const auto &new_instance{target.at(entry.first)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopProperties);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopProperties);
}

INSTRUCTION_HANDLER(LoopPropertiesEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesEvaluate, target.is_object());
  assert(!loop.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    const auto &new_instance{target.at(entry.first)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopPropertiesEvaluate);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  evaluator.evaluate();

  EVALUATE_END(loop, LoopPropertiesEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesRegex) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesRegex, target.is_object());
  assert(!loop.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (!matches(loop.value.first, entry.first)) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    const auto &new_instance{target.at(entry.first)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopPropertiesRegex);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopPropertiesRegex);
}

INSTRUCTION_HANDLER(LoopPropertiesRegexClosed) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesRegexClosed,
                            target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (!matches(loop.value.first, entry.first)) {
      result = false;
      break;
    }

    if (loop.children.empty()) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    const auto &new_instance{target.at(entry.first)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopPropertiesRegexClosed);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopPropertiesRegexClosed);
}

INSTRUCTION_HANDLER(LoopPropertiesStartsWith) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesStartsWith, target.is_object());
  assert(!loop.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (!entry.first.starts_with(loop.value)) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopPropertiesStartsWith);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopPropertiesStartsWith);
}

INSTRUCTION_HANDLER(LoopPropertiesExcept) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesExcept, target.is_object());
  assert(!loop.children.empty());
  result = true;
  // Otherwise why emit this instruction?
  assert(!std::get<0>(loop.value).empty() || !std::get<1>(loop.value).empty() ||
         !std::get<2>(loop.value).empty());

  for (const auto &entry : target.as_object()) {
    if (std::get<0>(loop.value).contains(entry.first)) {
      continue;
    }

    if (std::any_of(std::get<1>(loop.value).cbegin(),
                    std::get<1>(loop.value).cend(),
                    [&entry](const auto &prefix) {
                      return entry.first.starts_with(prefix);
                    })) {
      continue;
    }

    if (std::any_of(std::get<2>(loop.value).cbegin(),
                    std::get<2>(loop.value).cend(),
                    [&entry](const auto &pattern) {
                      return matches(pattern.first, entry.first);
                    })) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopPropertiesExcept);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopPropertiesExcept);
}

INSTRUCTION_HANDLER(LoopPropertiesWhitelist) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesWhitelist, target.is_object());
  // Otherwise why emit this instruction?
  assert(!loop.value.empty());

  // Otherwise if the number of properties in the instance
  // is larger than the whitelist, then it already violated
  // the whitelist?
  if (target.object_size() <= loop.value.size()) {
    result = true;
    for (const auto &entry : target.as_object()) {
      if (!loop.value.contains(entry.first)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(loop, LoopPropertiesWhitelist);
}

INSTRUCTION_HANDLER(LoopPropertiesType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesType, target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != loop.value &&
        // In non-strict mode, we consider a real number that represents an
        // integer to be an integer
        (loop.value != JSON::Type::Integer ||
         !entry.second.is_integer_real())) {
      result = false;
      break;
    }
  }

  EVALUATE_END(loop, LoopPropertiesType);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesTypeEvaluate,
                            target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != loop.value &&
        // In non-strict mode, we consider a real number that represents an
        // integer to be an integer
        (loop.value != JSON::Type::Integer ||
         !entry.second.is_integer_real())) {
      result = false;
      EVALUATE_END(loop, LoopPropertiesTypeEvaluate);
    }
  }

  evaluator.evaluate();

  EVALUATE_END(loop, LoopPropertiesTypeEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesTypeStrict, target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != loop.value) {
      result = false;
      break;
    }
  }

  EVALUATE_END(loop, LoopPropertiesTypeStrict);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrictEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesTypeStrictEvaluate,
                            target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != loop.value) {
      result = false;
      EVALUATE_END(loop, LoopPropertiesTypeStrictEvaluate);
    }
  }

  evaluator.evaluate();

  EVALUATE_END(loop, LoopPropertiesTypeStrictEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesTypeStrictAny,
                            target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (std::find(loop.value.cbegin(), loop.value.cend(),
                  entry.second.type()) == loop.value.cend()) {
      result = false;
      break;
    }
  }

  EVALUATE_END(loop, LoopPropertiesTypeStrictAny);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrictAnyEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopPropertiesTypeStrictAnyEvaluate,
                            target.is_object());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (std::find(loop.value.cbegin(), loop.value.cend(),
                  entry.second.type()) == loop.value.cend()) {
      result = false;
      EVALUATE_END(loop, LoopPropertiesTypeStrictAnyEvaluate);
    }
  }

  evaluator.evaluate();

  EVALUATE_END(loop, LoopPropertiesTypeStrictAnyEvaluate);
}

INSTRUCTION_HANDLER(LoopKeys) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopKeys, target.is_object());
  assert(!loop.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE_ON_PROPERTY_NAME(child, Evaluator::null,
                                             entry.first)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopKeys);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopKeys);
}

INSTRUCTION_HANDLER(LoopItems) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopItems, target.is_array());
  assert(!loop.children.empty());
  result = true;

  // To avoid index lookups and unnecessary conditionals
#ifdef SOURCEMETA_EVALUATOR_FAST
  for (const auto &new_instance : target.as_array()) {
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        EVALUATE_END(loop, LoopItems);
      }
    }
  }
#else
  for (std::size_t index = 0; index < target.array_size(); index++) {
    if (track) {
      evaluator.instance_location.push_back(index);
    }
    const auto &new_instance{target.at(index)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopItems);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }
#endif

  EVALUATE_END(loop, LoopItems);
}

INSTRUCTION_HANDLER(LoopItemsFrom) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopItemsFrom,
                            target.is_array() &&
                                loop.value < target.array_size());
  assert(!loop.children.empty());
  result = true;
  for (std::size_t index = loop.value; index < target.array_size(); index++) {
    if (track) {
      evaluator.instance_location.push_back(index);
    }
    const auto &new_instance{target.at(index)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(loop, LoopItemsFrom);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(loop, LoopItemsFrom);
}

INSTRUCTION_HANDLER(LoopItemsUnevaluated) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopItemsUnevaluated, target.is_array());
  assert(!loop.children.empty());
  result = true;

  for (std::size_t index = 0; index < target.array_size(); index++) {
    if (evaluator.is_evaluated(index)) {
      continue;
    }

    evaluator.instance_location.push_back(index);
    const auto &new_instance{target.at(index)};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        evaluator.instance_location.pop_back();
        EVALUATE_END(loop, LoopItemsUnevaluated);
      }
    }

    evaluator.instance_location.pop_back();
  }

  // Mark the entire array as evaluated
  evaluator.evaluate();

  EVALUATE_END(loop, LoopItemsUnevaluated);
}

INSTRUCTION_HANDLER(LoopItemsType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopItemsType, target.is_array());
  result = true;
  for (const auto &entry : target.as_array()) {
    if (entry.type() != loop.value &&
        // In non-strict mode, we consider a real number that represents an
        // integer to be an integer
        (loop.value != JSON::Type::Integer || !entry.is_integer_real())) {
      result = false;
      break;
    }
  }

  EVALUATE_END(loop, LoopItemsType);
}

INSTRUCTION_HANDLER(LoopItemsTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopItemsTypeStrict, target.is_array());
  result = true;
  for (const auto &entry : target.as_array()) {
    if (entry.type() != loop.value) {
      result = false;
      break;
    }
  }

  EVALUATE_END(loop, LoopItemsTypeStrict);
}

INSTRUCTION_HANDLER(LoopItemsTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopItemsTypeStrictAny, target.is_array());
  // Otherwise we are we even emitting this instruction?
  assert(loop.value.size() > 1);
  result = true;
  for (const auto &entry : target.as_array()) {
    if (std::find(loop.value.cbegin(), loop.value.cend(), entry.type()) ==
        loop.value.cend()) {
      result = false;
      break;
    }
  }

  EVALUATE_END(loop, LoopItemsTypeStrictAny);
}

INSTRUCTION_HANDLER(LoopContains) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(loop, LoopContains, target.is_array());
  assert(!loop.children.empty());
  const auto minimum{std::get<0>(loop.value)};
  const auto &maximum{std::get<1>(loop.value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  const auto is_exhaustive{std::get<2>(loop.value)};
  result = minimum == 0 && target.empty();
  auto match_count{std::numeric_limits<decltype(minimum)>::min()};

  for (std::size_t index = 0; index < target.array_size(); index++) {
    if (track) {
      evaluator.instance_location.push_back(index);
    }
    const auto &new_instance{target.at(index)};
    bool subresult{true};
    for (const auto &child : loop.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        subresult = false;
        break;
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }

    if (subresult) {
      match_count += 1;

      // Exceeding the upper bound is definitely a failure
      if (maximum.has_value() && match_count > maximum.value()) {
        result = false;

        // Note that here we don't want to consider whether to run
        // exhaustively or not. At this point, its already a failure,
        // and anything that comes after would not run at all anyway
        break;
      }

      if (match_count >= minimum) {
        result = true;

        // Exceeding the lower bound when there is no upper bound
        // is definitely a success
        if (!maximum.has_value() && !is_exhaustive) {
          break;
        }
      }
    }
  }

  EVALUATE_END(loop, LoopContains);
}

#undef INSTRUCTION_HANDLER

auto evaluate_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Template &schema,
    const std::optional<sourcemeta::blaze::Callback> &callback,
    const sourcemeta::jsontoolkit::JSON &instance,
    const std::optional<
        std::reference_wrapper<const sourcemeta::jsontoolkit::JSON::String>>
        &property_target,
    const std::uint64_t depth, sourcemeta::blaze::Evaluator &evaluator)
    -> bool {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  // Guard against infinite recursion in a cheap manner, as
  // infinite recursion will manifest itself through huge
  // ever-growing evaluate paths
  constexpr auto DEPTH_LIMIT{300};
  if (depth > DEPTH_LIMIT) [[unlikely]] {
    throw EvaluationError("The evaluation path depth limit was reached "
                          "likely due to infinite recursion");
  }

  switch (static_cast<InstructionIndex>(instruction.index())) {
    case InstructionIndex::AssertionFail:
      return AssertionFail(instruction, schema, callback, instance,
                           property_target, depth, evaluator);
    case InstructionIndex::AssertionDefines:
      return AssertionDefines(instruction, schema, callback, instance,
                              property_target, depth, evaluator);

    case InstructionIndex::AssertionDefinesStrict:
      return AssertionDefinesStrict(instruction, schema, callback, instance,
                                    property_target, depth, evaluator);

    case InstructionIndex::AssertionDefinesAll:
      return AssertionDefinesAll(instruction, schema, callback, instance,
                                 property_target, depth, evaluator);

    case InstructionIndex::AssertionDefinesAllStrict:
      return AssertionDefinesAllStrict(instruction, schema, callback, instance,
                                       property_target, depth, evaluator);

    case InstructionIndex::AssertionDefinesExactly:
      return AssertionDefinesExactly(instruction, schema, callback, instance,
                                     property_target, depth, evaluator);

    case InstructionIndex::AssertionDefinesExactlyStrict:
      return AssertionDefinesExactlyStrict(instruction, schema, callback,
                                           instance, property_target, depth,
                                           evaluator);

    case InstructionIndex::AssertionPropertyDependencies:
      return AssertionPropertyDependencies(instruction, schema, callback,
                                           instance, property_target, depth,
                                           evaluator);

    case InstructionIndex::AssertionType:
      return AssertionType(instruction, schema, callback, instance,
                           property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeAny:
      return AssertionTypeAny(instruction, schema, callback, instance,
                              property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeStrict:
      return AssertionTypeStrict(instruction, schema, callback, instance,
                                 property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeStrictAny:
      return AssertionTypeStrictAny(instruction, schema, callback, instance,
                                    property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeStringBounded:
      return AssertionTypeStringBounded(instruction, schema, callback, instance,
                                        property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeStringUpper:
      return AssertionTypeStringUpper(instruction, schema, callback, instance,
                                      property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeArrayBounded:
      return AssertionTypeArrayBounded(instruction, schema, callback, instance,
                                       property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeArrayUpper:
      return AssertionTypeArrayUpper(instruction, schema, callback, instance,
                                     property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeObjectBounded:
      return AssertionTypeObjectBounded(instruction, schema, callback, instance,
                                        property_target, depth, evaluator);

    case InstructionIndex::AssertionTypeObjectUpper:
      return AssertionTypeObjectUpper(instruction, schema, callback, instance,
                                      property_target, depth, evaluator);

    case InstructionIndex::AssertionRegex:
      return AssertionRegex(instruction, schema, callback, instance,
                            property_target, depth, evaluator);

    case InstructionIndex::AssertionStringSizeLess:
      return AssertionStringSizeLess(instruction, schema, callback, instance,
                                     property_target, depth, evaluator);

    case InstructionIndex::AssertionStringSizeGreater:
      return AssertionStringSizeGreater(instruction, schema, callback, instance,
                                        property_target, depth, evaluator);

    case InstructionIndex::AssertionArraySizeLess:
      return AssertionArraySizeLess(instruction, schema, callback, instance,
                                    property_target, depth, evaluator);

    case InstructionIndex::AssertionArraySizeGreater:
      return AssertionArraySizeGreater(instruction, schema, callback, instance,
                                       property_target, depth, evaluator);

    case InstructionIndex::AssertionObjectSizeLess:
      return AssertionObjectSizeLess(instruction, schema, callback, instance,
                                     property_target, depth, evaluator);

    case InstructionIndex::AssertionObjectSizeGreater:
      return AssertionObjectSizeGreater(instruction, schema, callback, instance,
                                        property_target, depth, evaluator);

    case InstructionIndex::AssertionEqual:
      return AssertionEqual(instruction, schema, callback, instance,
                            property_target, depth, evaluator);

    case InstructionIndex::AssertionEqualsAny:
      return AssertionEqualsAny(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::AssertionGreaterEqual:
      return AssertionGreaterEqual(instruction, schema, callback, instance,
                                   property_target, depth, evaluator);

    case InstructionIndex::AssertionLessEqual:
      return AssertionLessEqual(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::AssertionGreater:
      return AssertionGreater(instruction, schema, callback, instance,
                              property_target, depth, evaluator);

    case InstructionIndex::AssertionLess:
      return AssertionLess(instruction, schema, callback, instance,
                           property_target, depth, evaluator);

    case InstructionIndex::AssertionUnique:
      return AssertionUnique(instruction, schema, callback, instance,
                             property_target, depth, evaluator);

    case InstructionIndex::AssertionDivisible:
      return AssertionDivisible(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::AssertionStringType:
      return AssertionStringType(instruction, schema, callback, instance,
                                 property_target, depth, evaluator);

    case InstructionIndex::AssertionPropertyType:
      return AssertionPropertyType(instruction, schema, callback, instance,
                                   property_target, depth, evaluator);

    case InstructionIndex::AssertionPropertyTypeEvaluate:
      return AssertionPropertyTypeEvaluate(instruction, schema, callback,
                                           instance, property_target, depth,
                                           evaluator);

    case InstructionIndex::AssertionPropertyTypeStrict:
      return AssertionPropertyTypeStrict(instruction, schema, callback,
                                         instance, property_target, depth,
                                         evaluator);

    case InstructionIndex::AssertionPropertyTypeStrictEvaluate:
      return AssertionPropertyTypeStrictEvaluate(instruction, schema, callback,
                                                 instance, property_target,
                                                 depth, evaluator);

    case InstructionIndex::AssertionPropertyTypeStrictAny:
      return AssertionPropertyTypeStrictAny(instruction, schema, callback,
                                            instance, property_target, depth,
                                            evaluator);

    case InstructionIndex::AssertionPropertyTypeStrictAnyEvaluate:
      return AssertionPropertyTypeStrictAnyEvaluate(
          instruction, schema, callback, instance, property_target, depth,
          evaluator);

    case InstructionIndex::AssertionArrayPrefix:
      return AssertionArrayPrefix(instruction, schema, callback, instance,
                                  property_target, depth, evaluator);

    case InstructionIndex::AssertionArrayPrefixEvaluate:
      return AssertionArrayPrefixEvaluate(instruction, schema, callback,
                                          instance, property_target, depth,
                                          evaluator);

    case InstructionIndex::LogicalOr:
      return LogicalOr(instruction, schema, callback, instance, property_target,
                       depth, evaluator);

    case InstructionIndex::LogicalAnd:
      return LogicalAnd(instruction, schema, callback, instance,
                        property_target, depth, evaluator);

    case InstructionIndex::LogicalWhenType:
      return LogicalWhenType(instruction, schema, callback, instance,
                             property_target, depth, evaluator);

    case InstructionIndex::LogicalWhenDefines:
      return LogicalWhenDefines(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::LogicalWhenArraySizeGreater:
      return LogicalWhenArraySizeGreater(instruction, schema, callback,
                                         instance, property_target, depth,
                                         evaluator);

    case InstructionIndex::LogicalXor:
      return LogicalXor(instruction, schema, callback, instance,
                        property_target, depth, evaluator);

    case InstructionIndex::LogicalCondition:
      return LogicalCondition(instruction, schema, callback, instance,
                              property_target, depth, evaluator);

    case InstructionIndex::ControlGroup:
      return ControlGroup(instruction, schema, callback, instance,
                          property_target, depth, evaluator);

    case InstructionIndex::ControlGroupWhenDefines:
      return ControlGroupWhenDefines(instruction, schema, callback, instance,
                                     property_target, depth, evaluator);

    case InstructionIndex::ControlGroupWhenDefinesDirect:
      return ControlGroupWhenDefinesDirect(instruction, schema, callback,
                                           instance, property_target, depth,
                                           evaluator);

    case InstructionIndex::ControlLabel:
      return ControlLabel(instruction, schema, callback, instance,
                          property_target, depth, evaluator);

    case InstructionIndex::ControlMark:
      return ControlMark(instruction, schema, callback, instance,
                         property_target, depth, evaluator);

    case InstructionIndex::ControlEvaluate:
      return ControlEvaluate(instruction, schema, callback, instance,
                             property_target, depth, evaluator);

    case InstructionIndex::ControlJump:
      return ControlJump(instruction, schema, callback, instance,
                         property_target, depth, evaluator);

    case InstructionIndex::ControlDynamicAnchorJump:
      return ControlDynamicAnchorJump(instruction, schema, callback, instance,
                                      property_target, depth, evaluator);

    case InstructionIndex::AnnotationEmit:
      return AnnotationEmit(instruction, schema, callback, instance,
                            property_target, depth, evaluator);

    case InstructionIndex::AnnotationToParent:
      return AnnotationToParent(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::AnnotationBasenameToParent:
      return AnnotationBasenameToParent(instruction, schema, callback, instance,
                                        property_target, depth, evaluator);

    case InstructionIndex::LogicalNot:
      return LogicalNot(instruction, schema, callback, instance,
                        property_target, depth, evaluator);

    case InstructionIndex::LogicalNotEvaluate:
      return LogicalNotEvaluate(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesUnevaluated:
      return LoopPropertiesUnevaluated(instruction, schema, callback, instance,
                                       property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesUnevaluatedExcept:
      return LoopPropertiesUnevaluatedExcept(instruction, schema, callback,
                                             instance, property_target, depth,
                                             evaluator);

    case InstructionIndex::LoopPropertiesMatch:
      return LoopPropertiesMatch(instruction, schema, callback, instance,
                                 property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesMatchClosed:
      return LoopPropertiesMatchClosed(instruction, schema, callback, instance,
                                       property_target, depth, evaluator);

    case InstructionIndex::LoopProperties:
      return LoopProperties(instruction, schema, callback, instance,
                            property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesEvaluate:
      return LoopPropertiesEvaluate(instruction, schema, callback, instance,
                                    property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesRegex:
      return LoopPropertiesRegex(instruction, schema, callback, instance,
                                 property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesRegexClosed:
      return LoopPropertiesRegexClosed(instruction, schema, callback, instance,
                                       property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesStartsWith:
      return LoopPropertiesStartsWith(instruction, schema, callback, instance,
                                      property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesExcept:
      return LoopPropertiesExcept(instruction, schema, callback, instance,
                                  property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesWhitelist:
      return LoopPropertiesWhitelist(instruction, schema, callback, instance,
                                     property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesType:
      return LoopPropertiesType(instruction, schema, callback, instance,
                                property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesTypeEvaluate:
      return LoopPropertiesTypeEvaluate(instruction, schema, callback, instance,
                                        property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesTypeStrict:
      return LoopPropertiesTypeStrict(instruction, schema, callback, instance,
                                      property_target, depth, evaluator);

    case InstructionIndex::LoopPropertiesTypeStrictEvaluate:
      return LoopPropertiesTypeStrictEvaluate(instruction, schema, callback,
                                              instance, property_target, depth,
                                              evaluator);

    case InstructionIndex::LoopPropertiesTypeStrictAny:
      return LoopPropertiesTypeStrictAny(instruction, schema, callback,
                                         instance, property_target, depth,
                                         evaluator);

    case InstructionIndex::LoopPropertiesTypeStrictAnyEvaluate:
      return LoopPropertiesTypeStrictAnyEvaluate(instruction, schema, callback,
                                                 instance, property_target,
                                                 depth, evaluator);

    case InstructionIndex::LoopKeys:
      return LoopKeys(instruction, schema, callback, instance, property_target,
                      depth, evaluator);

    case InstructionIndex::LoopItems:
      return LoopItems(instruction, schema, callback, instance, property_target,
                       depth, evaluator);

    case InstructionIndex::LoopItemsFrom:
      return LoopItemsFrom(instruction, schema, callback, instance,
                           property_target, depth, evaluator);

    case InstructionIndex::LoopItemsUnevaluated:
      return LoopItemsUnevaluated(instruction, schema, callback, instance,
                                  property_target, depth, evaluator);

    case InstructionIndex::LoopItemsType:
      return LoopItemsType(instruction, schema, callback, instance,
                           property_target, depth, evaluator);

    case InstructionIndex::LoopItemsTypeStrict:
      return LoopItemsTypeStrict(instruction, schema, callback, instance,
                                 property_target, depth, evaluator);

    case InstructionIndex::LoopItemsTypeStrictAny:
      return LoopItemsTypeStrictAny(instruction, schema, callback, instance,
                                    property_target, depth, evaluator);

    case InstructionIndex::LoopContains:
      return LoopContains(instruction, schema, callback, instance,
                          property_target, depth, evaluator);
  }

    // See https://en.cppreference.com/w/cpp/utility/unreachable
#if defined(_MSC_VER) && !defined(__clang__)
  __assume(false);
#elif defined(__GNUC__) && !defined(__clang__)
  __builtin_unreachable();
#endif
}
