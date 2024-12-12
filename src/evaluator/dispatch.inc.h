inline auto evaluate_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Template &schema,
    const std::optional<sourcemeta::blaze::Callback> &callback,
    const sourcemeta::jsontoolkit::JSON &instance,
    const sourcemeta::jsontoolkit::JSON::String *property_target,
    const std::uint64_t depth, sourcemeta::blaze::Evaluator &evaluator) -> bool;

#define INSTRUCTION_HANDLER(name)                                              \
  static inline auto name(                                                     \
      const sourcemeta::blaze::Instruction &instruction,                       \
      const sourcemeta::blaze::Template &schema,                               \
      const std::optional<sourcemeta::blaze::Callback> &callback,              \
      const sourcemeta::jsontoolkit::JSON &instance,                           \
      const sourcemeta::jsontoolkit::JSON::String *property_target,            \
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
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionFail);
  EVALUATE_END(AssertionFail);
}

INSTRUCTION_HANDLER(AssertionDefines) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionDefines, target.is_object());
  const auto &value{*std::get_if<ValueProperty>(&instruction.value)};
  result = target.defines(value.first, value.second);
  EVALUATE_END(AssertionDefines);
}

INSTRUCTION_HANDLER(AssertionDefinesStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionDefinesStrict);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueProperty>(&instruction.value)};
  result = target.is_object() && target.defines(value.first, value.second);
  EVALUATE_END(AssertionDefinesStrict);
}

INSTRUCTION_HANDLER(AssertionDefinesAll) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionDefinesAll, target.is_object());
  const auto &value{*std::get_if<ValueStringSet>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);

  // Otherwise there is no way the instance can satisfy it anyway
  if (value.size() <= target.object_size()) {
    result = true;
    const auto &object{target.as_object()};
    for (const auto &property : value) {
      if (!object.defines(property.first, property.second)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(AssertionDefinesAll);
}

INSTRUCTION_HANDLER(AssertionDefinesAllStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionDefinesAllStrict);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueStringSet>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);

  // Otherwise there is no way the instance can satisfy it anyway
  if (target.is_object() && value.size() <= target.object_size()) {
    result = true;
    const auto &object{target.as_object()};
    for (const auto &property : value) {
      if (!object.defines(property.first, property.second)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(AssertionDefinesAllStrict);
}

INSTRUCTION_HANDLER(AssertionDefinesExactly) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionDefinesExactly, target.is_object());
  const auto &value{*std::get_if<ValueStringSet>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);

  if (value.size() == target.object_size()) {
    result = true;
    const auto &object{target.as_object()};
    for (const auto &property : value) {
      if (!object.defines(property.first, property.second)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(AssertionDefinesExactly);
}

INSTRUCTION_HANDLER(AssertionDefinesExactlyStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionDefinesExactlyStrict);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueStringSet>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);
  assert(target.is_object());

  if (value.size() == target.object_size()) {
    result = true;
    const auto &object{target.as_object()};
    for (const auto &property : value) {
      if (!object.defines(property.first, property.second)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(AssertionDefinesExactlyStrict);
}

INSTRUCTION_HANDLER(AssertionPropertyDependencies) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionPropertyDependencies, target.is_object());
  const auto &value{*std::get_if<ValueStringMap>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(!value.empty());
  result = true;
  const auto &object{target.as_object()};
  const sourcemeta::jsontoolkit::Hash hasher;
  for (const auto &entry : value) {
    if (!object.defines(entry.first, entry.hash)) {
      continue;
    }

    assert(!entry.second.empty());
    for (const auto &dependency : entry.second) {
      if (!object.defines(dependency, hasher(dependency))) {
        result = false;
        EVALUATE_END(AssertionPropertyDependencies);
      }
    }
  }

  EVALUATE_END(AssertionPropertyDependencies);
}

INSTRUCTION_HANDLER(AssertionType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionType);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueType>(&instruction.value)};

  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  result = target.type() == value ||
           (value == JSON::Type::Integer && target.is_integer_real());
  EVALUATE_END(AssertionType);
}

INSTRUCTION_HANDLER(AssertionTypeAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeAny);
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);
  const auto &target{get(instance, instruction.relative_instance_location)};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  for (const auto type : value) {
    if (type == JSON::Type::Integer && target.is_integer_real()) {
      result = true;
      break;
    } else if (type == target.type()) {
      result = true;
      break;
    }
  }

  EVALUATE_END(AssertionTypeAny);
}

INSTRUCTION_HANDLER(AssertionTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeStrict);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  result = target.type() == value;
  EVALUATE_END(AssertionTypeStrict);
}

INSTRUCTION_HANDLER(AssertionTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeStrictAny);
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);
  const auto &target{get(instance, instruction.relative_instance_location)};
  result =
      (std::find(value.cbegin(), value.cend(), target.type()) != value.cend());
  EVALUATE_END(AssertionTypeStrictAny);
}

INSTRUCTION_HANDLER(AssertionTypeStringBounded) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeStringBounded);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueRange>(&instruction.value)};
  const auto minimum{std::get<0>(value)};
  const auto maximum{std::get<1>(value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  // Require early breaking
  assert(!std::get<2>(value));
  result = target.type() == JSON::Type::String &&
           target.string_size() >= minimum &&
           (!maximum.has_value() || target.string_size() <= maximum.value());
  EVALUATE_END(AssertionTypeStringBounded);
}

INSTRUCTION_HANDLER(AssertionTypeStringUpper) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeStringUpper);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = target.is_string() && target.string_size() <= value;
  EVALUATE_END(AssertionTypeStringUpper);
}

INSTRUCTION_HANDLER(AssertionTypeArrayBounded) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeArrayBounded);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueRange>(&instruction.value)};
  const auto minimum{std::get<0>(value)};
  const auto maximum{std::get<1>(value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  // Require early breaking
  assert(!std::get<2>(value));
  result = target.type() == JSON::Type::Array &&
           target.array_size() >= minimum &&
           (!maximum.has_value() || target.array_size() <= maximum.value());
  EVALUATE_END(AssertionTypeArrayBounded);
}

INSTRUCTION_HANDLER(AssertionTypeArrayUpper) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeArrayUpper);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = target.is_array() && target.array_size() <= value;
  EVALUATE_END(AssertionTypeArrayUpper);
}

INSTRUCTION_HANDLER(AssertionTypeObjectBounded) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeObjectBounded);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueRange>(&instruction.value)};
  const auto minimum{std::get<0>(value)};
  const auto maximum{std::get<1>(value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  // Require early breaking
  assert(!std::get<2>(value));
  result = target.type() == JSON::Type::Object &&
           target.object_size() >= minimum &&
           (!maximum.has_value() || target.object_size() <= maximum.value());
  EVALUATE_END(AssertionTypeObjectBounded);
}

INSTRUCTION_HANDLER(AssertionTypeObjectUpper) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionTypeObjectUpper);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = target.is_object() && target.object_size() <= value;
  EVALUATE_END(AssertionTypeObjectUpper);
}

INSTRUCTION_HANDLER(AssertionRegex) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(AssertionRegex);
  const auto &value{*std::get_if<ValueRegex>(&instruction.value)};
  result = matches(value.first, target);
  EVALUATE_END(AssertionRegex);
}

INSTRUCTION_HANDLER(AssertionStringSizeLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(AssertionStringSizeLess);
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = (JSON::size(target) < value);
  EVALUATE_END(AssertionStringSizeLess);
}

INSTRUCTION_HANDLER(AssertionStringSizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(AssertionStringSizeGreater);
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = (JSON::size(target) > value);
  EVALUATE_END(AssertionStringSizeGreater);
}

INSTRUCTION_HANDLER(AssertionArraySizeLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionArraySizeLess, target.is_array());
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = (target.array_size() < value);
  EVALUATE_END(AssertionArraySizeLess);
}

INSTRUCTION_HANDLER(AssertionArraySizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionArraySizeGreater, target.is_array());
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = (target.array_size() > value);
  EVALUATE_END(AssertionArraySizeGreater);
}

INSTRUCTION_HANDLER(AssertionObjectSizeLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionObjectSizeLess, target.is_object());
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = (target.object_size() < value);
  EVALUATE_END(AssertionObjectSizeLess);
}

INSTRUCTION_HANDLER(AssertionObjectSizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionObjectSizeGreater, target.is_object());
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  result = (target.object_size() > value);
  EVALUATE_END(AssertionObjectSizeGreater);
}

INSTRUCTION_HANDLER(AssertionEqual) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionEqual);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
  result = (target == value);
  EVALUATE_END(AssertionEqual);
}

INSTRUCTION_HANDLER(AssertionEqualsAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(AssertionEqualsAny);
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueSet>(&instruction.value)};
  result = value.contains(target);
  EVALUATE_END(AssertionEqualsAny);
}

INSTRUCTION_HANDLER(AssertionGreaterEqual) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionGreaterEqual, target.is_number());
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
  result = target >= value;
  EVALUATE_END(AssertionGreaterEqual);
}

INSTRUCTION_HANDLER(AssertionLessEqual) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionLessEqual, target.is_number());
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
  result = target <= value;
  EVALUATE_END(AssertionLessEqual);
}

INSTRUCTION_HANDLER(AssertionGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionGreater, target.is_number());
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
  result = target > value;
  EVALUATE_END(AssertionGreater);
}

INSTRUCTION_HANDLER(AssertionLess) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionLess, target.is_number());
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
  result = target < value;
  EVALUATE_END(AssertionLess);
}

INSTRUCTION_HANDLER(AssertionUnique) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionUnique, target.is_array());
  result = target.unique();
  EVALUATE_END(AssertionUnique);
}

INSTRUCTION_HANDLER(AssertionDivisible) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionDivisible, target.is_number());
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
  assert(value.is_number());
  result = target.divisible_by(value);
  EVALUATE_END(AssertionDivisible);
}

INSTRUCTION_HANDLER(AssertionStringType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_IF_STRING(AssertionStringType);
  const auto value{*std::get_if<ValueStringType>(&instruction.value)};
  switch (value) {
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

  EVALUATE_END(AssertionStringType);
}

INSTRUCTION_HANDLER(AssertionPropertyType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(AssertionPropertyType,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  result = target_check->type() == value ||
           (value == JSON::Type::Integer && target_check->is_integer_real());
  EVALUATE_END(AssertionPropertyType);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(AssertionPropertyTypeEvaluate,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  // In non-strict mode, we consider a real number that represents an
  // integer to be an integer
  result = target_check->type() == value ||
           (value == JSON::Type::Integer && target_check->is_integer_real());

  if (result) {
    evaluator.evaluate();
  }

  EVALUATE_END(AssertionPropertyTypeEvaluate);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(AssertionPropertyTypeStrict,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  result = target_check->type() == value;
  EVALUATE_END(AssertionPropertyTypeStrict);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrictEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(AssertionPropertyTypeStrictEvaluate,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  // Now here we refer to the actual property
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  result = target_check->type() == value;

  if (result) {
    evaluator.evaluate();
  }

  EVALUATE_END(AssertionPropertyTypeStrictEvaluate);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(AssertionPropertyTypeStrictAny,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  // Now here we refer to the actual property
  result = (std::find(value.cbegin(), value.cend(), target_check->type()) !=
            value.cend());
  EVALUATE_END(AssertionPropertyTypeStrictAny);
}

INSTRUCTION_HANDLER(AssertionPropertyTypeStrictAnyEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_TRY_TARGET(AssertionPropertyTypeStrictAnyEvaluate,
                            // Note that here are are referring to the parent
                            // object that might hold the given property,
                            // before traversing into the actual property
                            target.is_object());
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  // Now here we refer to the actual property
  result = (std::find(value.cbegin(), value.cend(), target_check->type()) !=
            value.cend());

  if (result) {
    evaluator.evaluate();
  }

  EVALUATE_END(AssertionPropertyTypeStrictAnyEvaluate);
}

INSTRUCTION_HANDLER(AssertionArrayPrefix) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionArrayPrefix, target.is_array());
  // Otherwise there is no point in emitting this instruction
  assert(!instruction.children.empty());
  result = target.empty();
  const auto prefixes{instruction.children.size() - 1};
  const auto array_size{target.array_size()};
  if (!result) [[likely]] {
    const auto pointer{
        array_size == prefixes ? prefixes : std::min(array_size, prefixes) - 1};
    const auto &entry{instruction.children[pointer]};
    result = true;
    assert(entry.type == sourcemeta::blaze::InstructionIndex::ControlGroup);
    for (const auto &child : entry.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(AssertionArrayPrefix);
}

INSTRUCTION_HANDLER(AssertionArrayPrefixEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(AssertionArrayPrefixEvaluate, target.is_array());
  // Otherwise there is no point in emitting this instruction
  assert(!instruction.children.empty());
  result = target.empty();
  const auto prefixes{instruction.children.size() - 1};
  const auto array_size{target.array_size()};
  if (!result) [[likely]] {
    const auto pointer{
        array_size == prefixes ? prefixes : std::min(array_size, prefixes) - 1};
    const auto &entry{instruction.children[pointer]};
    result = true;
    assert(entry.type == sourcemeta::blaze::InstructionIndex::ControlGroup);
    for (const auto &child : entry.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        EVALUATE_END(AssertionArrayPrefixEvaluate);
      }
    }

    assert(result);
    if (array_size == prefixes) {
      evaluator.evaluate();
    } else {
      evaluator.evaluate(0, pointer);
    }
  }

  EVALUATE_END(AssertionArrayPrefixEvaluate);
}

INSTRUCTION_HANDLER(LogicalOr) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(LogicalOr);
  result = instruction.children.empty();
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueBoolean>(&instruction.value)};

  // This boolean value controls whether we should be exhaustive
  if (value) {
    for (const auto &child : instruction.children) {
      if (EVALUATE_RECURSE(child, target)) {
        result = true;
      }
    }
  } else {
    for (const auto &child : instruction.children) {
      if (EVALUATE_RECURSE(child, target)) {
        result = true;
        break;
      }
    }
  }

  EVALUATE_END(LogicalOr);
}

INSTRUCTION_HANDLER(LogicalAnd) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(LogicalAnd);
  result = true;
  const auto &target{get(instance, instruction.relative_instance_location)};
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LogicalAnd);
}

INSTRUCTION_HANDLER(LogicalWhenType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  EVALUATE_BEGIN(LogicalWhenType, target.type() == value);
  result = true;
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LogicalWhenType);
}

INSTRUCTION_HANDLER(LogicalWhenDefines) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  const auto &value{*std::get_if<ValueProperty>(&instruction.value)};
  EVALUATE_BEGIN_NON_STRING(LogicalWhenDefines,
                            target.is_object() &&
                                target.defines(value.first, value.second));
  result = true;
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LogicalWhenDefines);
}

INSTRUCTION_HANDLER(LogicalWhenArraySizeGreater) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  EVALUATE_BEGIN_NON_STRING(LogicalWhenArraySizeGreater,
                            target.is_array() && target.array_size() > value);
  result = true;
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LogicalWhenArraySizeGreater);
}

INSTRUCTION_HANDLER(LogicalXor) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(LogicalXor);
  result = true;
  bool has_matched{false};
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto value{*std::get_if<ValueBoolean>(&instruction.value)};
  for (const auto &child : instruction.children) {
    if (EVALUATE_RECURSE(child, target)) {
      if (has_matched) {
        result = false;
        // This boolean value controls whether we should be exhaustive
        if (!value) {
          break;
        }
      } else {
        has_matched = true;
      }
    }
  }

  result = result && has_matched;
  EVALUATE_END(LogicalXor);
}

INSTRUCTION_HANDLER(LogicalCondition) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(LogicalCondition);
  result = true;
  const auto value{*std::get_if<ValueIndexPair>(&instruction.value)};
  const auto children_size{instruction.children.size()};
  assert(children_size >= value.first);
  assert(children_size >= value.second);

  auto condition_end{children_size};
  if (value.first > 0) {
    condition_end = value.first;
  } else if (value.second > 0) {
    condition_end = value.second;
  }

  const auto &target{get(instance, instruction.relative_instance_location)};
  for (std::size_t cursor = 0; cursor < condition_end; cursor++) {
    if (!EVALUATE_RECURSE(instruction.children[cursor], target)) {
      result = false;
      break;
    }
  }

  const auto consequence_start{result ? value.first : value.second};
  const auto consequence_end{(result && value.second > 0) ? value.second
                                                          : children_size};
  result = true;
  if (consequence_start > 0) {
    if (track) {
      evaluator.evaluate_path.pop_back(
          instruction.relative_schema_location.size());

      for (auto cursor = consequence_start; cursor < consequence_end;
           cursor++) {
        if (!EVALUATE_RECURSE(instruction.children[cursor], instance)) {
          result = false;
          break;
        }
      }

      evaluator.evaluate_path.push_back(instruction.relative_schema_location);
    } else {
      for (auto cursor = consequence_start; cursor < consequence_end;
           cursor++) {
        if (!EVALUATE_RECURSE(instruction.children[cursor], instance)) {
          result = false;
          break;
        }
      }
    }
  }

  EVALUATE_END(LogicalCondition);
}

INSTRUCTION_HANDLER(ControlGroup) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_PASS_THROUGH(ControlGroup);
  for (const auto &child : instruction.children) {
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
  EVALUATE_BEGIN_PASS_THROUGH(ControlGroupWhenDefines);
  assert(!instruction.children.empty());
  // Otherwise why are we emitting this property?
  assert(!instruction.relative_instance_location.empty());
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueProperty>(&instruction.value)};
  if (target.is_object() && target.defines(value.first, value.second)) {
    for (const auto &child : instruction.children) {
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
  EVALUATE_BEGIN_PASS_THROUGH(ControlGroupWhenDefinesDirect);
  assert(!instruction.children.empty());
  assert(instruction.relative_instance_location.empty());
  const auto &value{*std::get_if<ValueProperty>(&instruction.value)};
  if (instance.is_object() && instance.defines(value.first, value.second)) {
    for (const auto &child : instruction.children) {
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
  EVALUATE_BEGIN_NO_PRECONDITION(ControlLabel);
  assert(!instruction.children.empty());
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  evaluator.labels.try_emplace(value, instruction.children);
  const auto &target{get(instance, instruction.relative_instance_location)};
  result = true;
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(ControlLabel);
}

INSTRUCTION_HANDLER(ControlMark) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(ControlMark);
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  evaluator.labels.try_emplace(value, instruction.children);
  EVALUATE_END_NO_POP(ControlMark);
}

INSTRUCTION_HANDLER(ControlEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(instruction);
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_PASS_THROUGH(ControlEvaluate);

#ifdef SOURCEMETA_EVALUATOR_COMPLETE
  if (callback.has_value()) {
    const auto &value{*std::get_if<ValuePointer>(&instruction.value)};
    // TODO: Optimize this case to avoid an extra pointer copy
    auto destination = evaluator.instance_location;
    destination.push_back(value);
    callback.value()(EvaluationType::Pre, true, instruction,
                     evaluator.evaluate_path, destination, Evaluator::null);
    evaluator.evaluate(value);
    callback.value()(EvaluationType::Post, true, instruction,
                     evaluator.evaluate_path, destination, Evaluator::null);
  } else {
    const auto &value{*std::get_if<ValuePointer>(&instruction.value)};
    evaluator.evaluate(value);
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
  EVALUATE_BEGIN_NO_PRECONDITION(ControlJump);
  result = true;
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  assert(evaluator.labels.contains(value));
  const auto &target{get(instance, instruction.relative_instance_location)};
  for (const auto &child : evaluator.labels.at(value).get()) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = false;
      break;
    }
  }

  EVALUATE_END(ControlJump);
}

INSTRUCTION_HANDLER(ControlDynamicAnchorJump) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(ControlDynamicAnchorJump);
  result = false;
  const auto &target{get(instance, instruction.relative_instance_location)};
  const auto &value{*std::get_if<ValueString>(&instruction.value)};
  for (const auto &resource : evaluator.resources) {
    const auto label{evaluator.hash(resource, value)};
    const auto match{evaluator.labels.find(label)};
    if (match != evaluator.labels.cend()) {
      result = true;
      for (const auto &child : match->second.get()) {
        if (!EVALUATE_RECURSE(child, target)) {
          result = false;
          EVALUATE_END(ControlDynamicAnchorJump);
        }
      }

      break;
    }
  }

  EVALUATE_END(ControlDynamicAnchorJump);
}

INSTRUCTION_HANDLER(AnnotationEmit) {
  SOURCEMETA_MAYBE_UNUSED(instruction);
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
#ifdef SOURCEMETA_EVALUATOR_COMPLETE
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
#endif
  EVALUATE_ANNOTATION(AnnotationEmit, evaluator.instance_location, value);
}

INSTRUCTION_HANDLER(AnnotationToParent) {
  SOURCEMETA_MAYBE_UNUSED(instruction);
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
#ifdef SOURCEMETA_EVALUATOR_COMPLETE
  const auto &value{*std::get_if<ValueJSON>(&instruction.value)};
#endif
  EVALUATE_ANNOTATION(
      AnnotationToParent,
      // TODO: Can we avoid a copy of the instance location here?
      evaluator.instance_location.initial(), value);
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
      AnnotationBasenameToParent,
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
  EVALUATE_BEGIN_NO_PRECONDITION(LogicalNot);

  const auto &target{get(instance, instruction.relative_instance_location)};
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = true;
      break;
    }
  }

  EVALUATE_END(LogicalNot);
}

INSTRUCTION_HANDLER(LogicalNotEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NO_PRECONDITION(LogicalNotEvaluate);

  const auto &target{get(instance, instruction.relative_instance_location)};
  for (const auto &child : instruction.children) {
    if (!EVALUATE_RECURSE(child, target)) {
      result = true;
      break;
    }
  }

  evaluator.unevaluate();

  EVALUATE_END(LogicalNotEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesUnevaluated) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesUnevaluated, target.is_object());
  assert(!instruction.children.empty());
  result = true;

  for (const auto &entry : target.as_object()) {
    if (evaluator.is_evaluated({entry.first})) {
      continue;
    }

    evaluator.instance_location.push_back(entry.first);
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        evaluator.instance_location.pop_back();
        EVALUATE_END(LoopPropertiesUnevaluated);
      }
    }

    evaluator.instance_location.pop_back();
  }

  // Mark the entire object as evaluated
  evaluator.evaluate();

  EVALUATE_END(LoopPropertiesUnevaluated);
}

INSTRUCTION_HANDLER(LoopPropertiesUnevaluatedExcept) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesUnevaluatedExcept,
                            target.is_object());
  assert(!instruction.children.empty());
  const auto &value{*std::get_if<ValuePropertyFilter>(&instruction.value)};
  result = true;
  // Otherwise why emit this instruction?
  assert(!std::get<0>(value).empty() || !std::get<1>(value).empty() ||
         !std::get<2>(value).empty());

  for (const auto &entry : target.as_object()) {
    if (std::get<0>(value).contains(entry.first, entry.hash)) {
      continue;
    }

    if (std::any_of(std::get<1>(value).cbegin(), std::get<1>(value).cend(),
                    [&entry](const auto &prefix) {
                      return entry.first.starts_with(prefix);
                    })) {
      continue;
    }

    if (std::any_of(std::get<2>(value).cbegin(), std::get<2>(value).cend(),
                    [&entry](const auto &pattern) {
                      return matches(pattern.first, entry.first);
                    })) {
      continue;
    }

    if (evaluator.is_evaluated({entry.first})) {
      continue;
    }

    evaluator.instance_location.push_back(entry.first);
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        evaluator.instance_location.pop_back();
        EVALUATE_END(LoopPropertiesUnevaluatedExcept);
      }
    }

    evaluator.instance_location.pop_back();
  }

  // Mark the entire object as evaluated
  evaluator.evaluate();

  EVALUATE_END(LoopPropertiesUnevaluatedExcept);
}

INSTRUCTION_HANDLER(LoopPropertiesMatch) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesMatch, target.is_object());
  const auto &value{*std::get_if<ValueNamedIndexes>(&instruction.value)};
  assert(!value.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    const auto index{value.find(entry.first, entry.hash)};
    if (index == value.cend()) {
      continue;
    }

    const auto &subinstruction{instruction.children[index->second]};
    assert(subinstruction.type ==
           sourcemeta::blaze::InstructionIndex::ControlGroup);
    for (const auto &child : subinstruction.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        EVALUATE_END(LoopPropertiesMatch);
      }
    }
  }

  EVALUATE_END(LoopPropertiesMatch);
}

INSTRUCTION_HANDLER(LoopPropertiesMatchClosed) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesMatchClosed, target.is_object());
  const auto &value{*std::get_if<ValueNamedIndexes>(&instruction.value)};
  assert(!value.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    const auto index{value.find(entry.first, entry.hash)};
    if (index == value.cend()) {
      result = false;
      break;
    }

    const auto &subinstruction{instruction.children[index->second]};
    assert(subinstruction.type ==
           sourcemeta::blaze::InstructionIndex::ControlGroup);
    for (const auto &child : subinstruction.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        EVALUATE_END(LoopPropertiesMatchClosed);
      }
    }
  }

  EVALUATE_END(LoopPropertiesMatchClosed);
}

INSTRUCTION_HANDLER(LoopProperties) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopProperties, target.is_object());
  assert(!instruction.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopProperties);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopProperties);
}

INSTRUCTION_HANDLER(LoopPropertiesEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesEvaluate, target.is_object());
  assert(!instruction.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopPropertiesEvaluate);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  evaluator.evaluate();

  EVALUATE_END(LoopPropertiesEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesRegex) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesRegex, target.is_object());
  assert(!instruction.children.empty());
  const auto &value{*std::get_if<ValueRegex>(&instruction.value)};
  result = true;
  for (const auto &entry : target.as_object()) {
    if (!matches(value.first, entry.first)) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopPropertiesRegex);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopPropertiesRegex);
}

INSTRUCTION_HANDLER(LoopPropertiesRegexClosed) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesRegexClosed, target.is_object());
  result = true;
  const auto &value{*std::get_if<ValueRegex>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (!matches(value.first, entry.first)) {
      result = false;
      break;
    }

    if (instruction.children.empty()) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopPropertiesRegexClosed);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopPropertiesRegexClosed);
}

INSTRUCTION_HANDLER(LoopPropertiesStartsWith) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesStartsWith, target.is_object());
  assert(!instruction.children.empty());
  result = true;
  const auto &value{*std::get_if<ValueString>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (!entry.first.starts_with(value)) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopPropertiesStartsWith);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopPropertiesStartsWith);
}

INSTRUCTION_HANDLER(LoopPropertiesExcept) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesExcept, target.is_object());
  assert(!instruction.children.empty());
  result = true;
  const auto &value{*std::get_if<ValuePropertyFilter>(&instruction.value)};
  // Otherwise why emit this instruction?
  assert(!std::get<0>(value).empty() || !std::get<1>(value).empty() ||
         !std::get<2>(value).empty());

  for (const auto &entry : target.as_object()) {
    if (std::get<0>(value).contains(entry.first, entry.hash)) {
      continue;
    }

    if (std::any_of(std::get<1>(value).cbegin(), std::get<1>(value).cend(),
                    [&entry](const auto &prefix) {
                      return entry.first.starts_with(prefix);
                    })) {
      continue;
    }

    if (std::any_of(std::get<2>(value).cbegin(), std::get<2>(value).cend(),
                    [&entry](const auto &pattern) {
                      return matches(pattern.first, entry.first);
                    })) {
      continue;
    }

    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, entry.second)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopPropertiesExcept);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopPropertiesExcept);
}

INSTRUCTION_HANDLER(LoopPropertiesWhitelist) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesWhitelist, target.is_object());
  const auto &value{*std::get_if<ValueStringSet>(&instruction.value)};
  // Otherwise why emit this instruction?
  assert(!value.empty());

  // Otherwise if the number of properties in the instance
  // is larger than the whitelist, then it already violated
  // the whitelist?
  if (target.object_size() <= value.size()) {
    result = true;
    for (const auto &entry : target.as_object()) {
      if (!value.contains(entry.first, entry.hash)) {
        result = false;
        break;
      }
    }
  }

  EVALUATE_END(LoopPropertiesWhitelist);
}

INSTRUCTION_HANDLER(LoopPropertiesType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesType, target.is_object());
  result = true;
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != value &&
        // In non-strict mode, we consider a real number that represents an
        // integer to be an integer
        (value != JSON::Type::Integer || !entry.second.is_integer_real())) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LoopPropertiesType);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesTypeEvaluate, target.is_object());
  result = true;
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != value &&
        // In non-strict mode, we consider a real number that represents an
        // integer to be an integer
        (value != JSON::Type::Integer || !entry.second.is_integer_real())) {
      result = false;
      EVALUATE_END(LoopPropertiesTypeEvaluate);
    }
  }

  evaluator.evaluate();

  EVALUATE_END(LoopPropertiesTypeEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesTypeStrict, target.is_object());
  result = true;
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != value) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LoopPropertiesTypeStrict);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrictEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesTypeStrictEvaluate,
                            target.is_object());
  result = true;
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (entry.second.type() != value) {
      result = false;
      EVALUATE_END(LoopPropertiesTypeStrictEvaluate);
    }
  }

  evaluator.evaluate();

  EVALUATE_END(LoopPropertiesTypeStrictEvaluate);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesTypeStrictAny, target.is_object());
  result = true;
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (std::find(value.cbegin(), value.cend(), entry.second.type()) ==
        value.cend()) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LoopPropertiesTypeStrictAny);
}

INSTRUCTION_HANDLER(LoopPropertiesTypeStrictAnyEvaluate) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopPropertiesTypeStrictAnyEvaluate,
                            target.is_object());
  result = true;
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  for (const auto &entry : target.as_object()) {
    if (std::find(value.cbegin(), value.cend(), entry.second.type()) ==
        value.cend()) {
      result = false;
      EVALUATE_END(LoopPropertiesTypeStrictAnyEvaluate);
    }
  }

  evaluator.evaluate();

  EVALUATE_END(LoopPropertiesTypeStrictAnyEvaluate);
}

INSTRUCTION_HANDLER(LoopKeys) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopKeys, target.is_object());
  assert(!instruction.children.empty());
  result = true;
  for (const auto &entry : target.as_object()) {
    if (track) {
      evaluator.instance_location.push_back(entry.first);
    }
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE_ON_PROPERTY_NAME(child, Evaluator::null,
                                             entry.first)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopKeys);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopKeys);
}

INSTRUCTION_HANDLER(LoopItems) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopItems, target.is_array());
  assert(!instruction.children.empty());
  result = true;

  // To avoid index lookups and unnecessary conditionals
#ifdef SOURCEMETA_EVALUATOR_FAST
  for (const auto &new_instance : target.as_array()) {
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        EVALUATE_END(LoopItems);
      }
    }
  }
#else
  for (std::size_t index = 0; index < target.array_size(); index++) {
    if (track) {
      evaluator.instance_location.push_back(index);
    }
    const auto &new_instance{target.at(index)};
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopItems);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }
#endif

  EVALUATE_END(LoopItems);
}

INSTRUCTION_HANDLER(LoopItemsFrom) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  const auto value{*std::get_if<ValueUnsignedInteger>(&instruction.value)};
  EVALUATE_BEGIN_NON_STRING(LoopItemsFrom,
                            target.is_array() && value < target.array_size());
  assert(!instruction.children.empty());
  result = true;
  for (std::size_t index = value; index < target.array_size(); index++) {
    if (track) {
      evaluator.instance_location.push_back(index);
    }
    const auto &new_instance{target.at(index)};
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        if (track) {
          evaluator.instance_location.pop_back();
        }
        EVALUATE_END(LoopItemsFrom);
      }
    }

    if (track) {
      evaluator.instance_location.pop_back();
    }
  }

  EVALUATE_END(LoopItemsFrom);
}

INSTRUCTION_HANDLER(LoopItemsUnevaluated) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopItemsUnevaluated, target.is_array());
  assert(!instruction.children.empty());
  result = true;

  for (std::size_t index = 0; index < target.array_size(); index++) {
    if (evaluator.is_evaluated(index)) {
      continue;
    }

    evaluator.instance_location.push_back(index);
    const auto &new_instance{target.at(index)};
    for (const auto &child : instruction.children) {
      if (!EVALUATE_RECURSE(child, new_instance)) {
        result = false;
        evaluator.instance_location.pop_back();
        EVALUATE_END(LoopItemsUnevaluated);
      }
    }

    evaluator.instance_location.pop_back();
  }

  // Mark the entire array as evaluated
  evaluator.evaluate();

  EVALUATE_END(LoopItemsUnevaluated);
}

INSTRUCTION_HANDLER(LoopItemsType) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopItemsType, target.is_array());
  result = true;
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  for (const auto &entry : target.as_array()) {
    if (entry.type() != value &&
        // In non-strict mode, we consider a real number that represents an
        // integer to be an integer
        (value != JSON::Type::Integer || !entry.is_integer_real())) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LoopItemsType);
}

INSTRUCTION_HANDLER(LoopItemsTypeStrict) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopItemsTypeStrict, target.is_array());
  result = true;
  const auto value{*std::get_if<ValueType>(&instruction.value)};
  for (const auto &entry : target.as_array()) {
    if (entry.type() != value) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LoopItemsTypeStrict);
}

INSTRUCTION_HANDLER(LoopItemsTypeStrictAny) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopItemsTypeStrictAny, target.is_array());
  const auto &value{*std::get_if<ValueTypes>(&instruction.value)};
  // Otherwise we are we even emitting this instruction?
  assert(value.size() > 1);
  result = true;
  for (const auto &entry : target.as_array()) {
    if (std::find(value.cbegin(), value.cend(), entry.type()) == value.cend()) {
      result = false;
      break;
    }
  }

  EVALUATE_END(LoopItemsTypeStrictAny);
}

INSTRUCTION_HANDLER(LoopContains) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(schema);
  SOURCEMETA_MAYBE_UNUSED(callback);
  SOURCEMETA_MAYBE_UNUSED(instance);
  SOURCEMETA_MAYBE_UNUSED(property_target);
  SOURCEMETA_MAYBE_UNUSED(evaluator);
  EVALUATE_BEGIN_NON_STRING(LoopContains, target.is_array());
  assert(!instruction.children.empty());
  const auto &value{*std::get_if<ValueRange>(&instruction.value)};
  const auto minimum{std::get<0>(value)};
  const auto &maximum{std::get<1>(value)};
  assert(!maximum.has_value() || maximum.value() >= minimum);
  const auto is_exhaustive{std::get<2>(value)};
  result = minimum == 0 && target.empty();
  auto match_count{std::numeric_limits<decltype(minimum)>::min()};

  for (std::size_t index = 0; index < target.array_size(); index++) {
    if (track) {
      evaluator.instance_location.push_back(index);
    }
    const auto &new_instance{target.at(index)};
    bool subresult{true};
    for (const auto &child : instruction.children) {
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

  EVALUATE_END(LoopContains);
}

#undef INSTRUCTION_HANDLER

using DispatchHandler = bool (*)(
    const sourcemeta::blaze::Instruction &, const sourcemeta::blaze::Template &,
    const std::optional<sourcemeta::blaze::Callback> &,
    const sourcemeta::jsontoolkit::JSON &,
    const sourcemeta::jsontoolkit::JSON::String *, const std::uint64_t depth,
    sourcemeta::blaze::Evaluator &);

// Must have same order as InstructionIndex
static constexpr DispatchHandler handlers[87] = {
    AssertionFail,
    AssertionDefines,
    AssertionDefinesStrict,
    AssertionDefinesAll,
    AssertionDefinesAllStrict,
    AssertionDefinesExactly,
    AssertionDefinesExactlyStrict,
    AssertionPropertyDependencies,
    AssertionType,
    AssertionTypeAny,
    AssertionTypeStrict,
    AssertionTypeStrictAny,
    AssertionTypeStringBounded,
    AssertionTypeStringUpper,
    AssertionTypeArrayBounded,
    AssertionTypeArrayUpper,
    AssertionTypeObjectBounded,
    AssertionTypeObjectUpper,
    AssertionRegex,
    AssertionStringSizeLess,
    AssertionStringSizeGreater,
    AssertionArraySizeLess,
    AssertionArraySizeGreater,
    AssertionObjectSizeLess,
    AssertionObjectSizeGreater,
    AssertionEqual,
    AssertionEqualsAny,
    AssertionGreaterEqual,
    AssertionLessEqual,
    AssertionGreater,
    AssertionLess,
    AssertionUnique,
    AssertionDivisible,
    AssertionStringType,
    AssertionPropertyType,
    AssertionPropertyTypeEvaluate,
    AssertionPropertyTypeStrict,
    AssertionPropertyTypeStrictEvaluate,
    AssertionPropertyTypeStrictAny,
    AssertionPropertyTypeStrictAnyEvaluate,
    AssertionArrayPrefix,
    AssertionArrayPrefixEvaluate,
    AnnotationEmit,
    AnnotationToParent,
    AnnotationBasenameToParent,
    LogicalNot,
    LogicalNotEvaluate,
    LogicalOr,
    LogicalAnd,
    LogicalXor,
    LogicalCondition,
    LogicalWhenType,
    LogicalWhenDefines,
    LogicalWhenArraySizeGreater,
    LoopPropertiesUnevaluated,
    LoopPropertiesUnevaluatedExcept,
    LoopPropertiesMatch,
    LoopPropertiesMatchClosed,
    LoopProperties,
    LoopPropertiesEvaluate,
    LoopPropertiesRegex,
    LoopPropertiesRegexClosed,
    LoopPropertiesStartsWith,
    LoopPropertiesExcept,
    LoopPropertiesWhitelist,
    LoopPropertiesType,
    LoopPropertiesTypeEvaluate,
    LoopPropertiesTypeStrict,
    LoopPropertiesTypeStrictEvaluate,
    LoopPropertiesTypeStrictAny,
    LoopPropertiesTypeStrictAnyEvaluate,
    LoopKeys,
    LoopItems,
    LoopItemsFrom,
    LoopItemsUnevaluated,
    LoopItemsType,
    LoopItemsTypeStrict,
    LoopItemsTypeStrictAny,
    LoopContains,
    ControlGroup,
    ControlGroupWhenDefines,
    ControlGroupWhenDefinesDirect,
    ControlLabel,
    ControlMark,
    ControlEvaluate,
    ControlJump,
    ControlDynamicAnchorJump};

inline auto evaluate_instruction(
    const sourcemeta::blaze::Instruction &instruction,
    const sourcemeta::blaze::Template &schema,
    const std::optional<sourcemeta::blaze::Callback> &callback,
    const sourcemeta::jsontoolkit::JSON &instance,
    const sourcemeta::jsontoolkit::JSON::String *property_target,
    const std::uint64_t depth, sourcemeta::blaze::Evaluator &evaluator)
    -> bool {
  // Guard against infinite recursion in a cheap manner, as
  // infinite recursion will manifest itself through huge
  // ever-growing evaluate paths
  constexpr auto DEPTH_LIMIT{300};
  if (depth > DEPTH_LIMIT) [[unlikely]] {
    throw EvaluationError("The evaluation path depth limit was reached "
                          "likely due to infinite recursion");
  }

  return handlers[static_cast<std::underlying_type_t<InstructionIndex>>(
      instruction.type)](instruction, schema, callback, instance,
                         property_target, depth, evaluator);
}