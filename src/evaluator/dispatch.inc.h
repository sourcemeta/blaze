SOURCEMETA_TRACE_REGISTER_ID(trace_id);

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

#define IS_INSTRUCTION(instruction_type) InstructionIndex::instruction_type

switch (static_cast<InstructionIndex>(instruction.index())) {
  case IS_INSTRUCTION(AssertionFail): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionFail);
    EVALUATE_END(assertion, AssertionFail);
  }

  case IS_INSTRUCTION(AssertionDefines): {
    EVALUATE_BEGIN(assertion, AssertionDefines, target.is_object());
    result = target.defines(assertion.value);
    EVALUATE_END(assertion, AssertionDefines);
  }

  case IS_INSTRUCTION(AssertionDefinesAll): {
    EVALUATE_BEGIN(assertion, AssertionDefinesAll, target.is_object());

    // Otherwise we are we even emitting this instruction?
    assert(assertion.value.size() > 1);

    // Otherwise there is no way the instance can satisfy it anyway
    if (assertion.value.size() <= target.size()) {
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

  case IS_INSTRUCTION(AssertionPropertyDependencies): {
    EVALUATE_BEGIN(assertion, AssertionPropertyDependencies,
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

  case IS_INSTRUCTION(AssertionType): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionType);
    const auto &target{get(instance, assertion.relative_instance_location)};
    // In non-strict mode, we consider a real number that represents an
    // integer to be an integer
    result =
        target.type() == assertion.value ||
        (assertion.value == JSON::Type::Integer && target.is_integer_real());
    EVALUATE_END(assertion, AssertionType);
  }

  case IS_INSTRUCTION(AssertionTypeAny): {
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

  case IS_INSTRUCTION(AssertionTypeStrict): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStrict);
    const auto &target{get(instance, assertion.relative_instance_location)};
    result = target.type() == assertion.value;
    EVALUATE_END(assertion, AssertionTypeStrict);
  }

  case IS_INSTRUCTION(AssertionTypeStrictAny): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStrictAny);
    // Otherwise we are we even emitting this instruction?
    assert(assertion.value.size() > 1);
    const auto &target{get(instance, assertion.relative_instance_location)};
    result = (std::find(assertion.value.cbegin(), assertion.value.cend(),
                        target.type()) != assertion.value.cend());
    EVALUATE_END(assertion, AssertionTypeStrictAny);
  }

  case IS_INSTRUCTION(AssertionTypeStringBounded): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeStringBounded);
    const auto &target{get(instance, assertion.relative_instance_location)};
    const auto minimum{std::get<0>(assertion.value)};
    const auto maximum{std::get<1>(assertion.value)};
    assert(!maximum.has_value() || maximum.value() >= minimum);
    // Require early breaking
    assert(!std::get<2>(assertion.value));
    result = target.type() == JSON::Type::String && target.size() >= minimum &&
             (!maximum.has_value() || target.size() <= maximum.value());
    EVALUATE_END(assertion, AssertionTypeStringBounded);
  }

  case IS_INSTRUCTION(AssertionTypeArrayBounded): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeArrayBounded);
    const auto &target{get(instance, assertion.relative_instance_location)};
    const auto minimum{std::get<0>(assertion.value)};
    const auto maximum{std::get<1>(assertion.value)};
    assert(!maximum.has_value() || maximum.value() >= minimum);
    // Require early breaking
    assert(!std::get<2>(assertion.value));
    result = target.type() == JSON::Type::Array && target.size() >= minimum &&
             (!maximum.has_value() || target.size() <= maximum.value());
    EVALUATE_END(assertion, AssertionTypeArrayBounded);
  }

  case IS_INSTRUCTION(AssertionTypeObjectBounded): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionTypeObjectBounded);
    const auto &target{get(instance, assertion.relative_instance_location)};
    const auto minimum{std::get<0>(assertion.value)};
    const auto maximum{std::get<1>(assertion.value)};
    assert(!maximum.has_value() || maximum.value() >= minimum);
    // Require early breaking
    assert(!std::get<2>(assertion.value));
    result = target.type() == JSON::Type::Object && target.size() >= minimum &&
             (!maximum.has_value() || target.size() <= maximum.value());
    EVALUATE_END(assertion, AssertionTypeObjectBounded);
  }

  case IS_INSTRUCTION(AssertionRegex): {
    EVALUATE_BEGIN_IF_STRING(assertion, AssertionRegex);
    result = validate(assertion.value.first, target);
    EVALUATE_END(assertion, AssertionRegex);
  }

  case IS_INSTRUCTION(AssertionStringSizeLess): {
    EVALUATE_BEGIN_IF_STRING(assertion, AssertionStringSizeLess);
    result = (JSON::size(target) < assertion.value);
    EVALUATE_END(assertion, AssertionStringSizeLess);
  }

  case IS_INSTRUCTION(AssertionStringSizeGreater): {
    EVALUATE_BEGIN_IF_STRING(assertion, AssertionStringSizeGreater);
    result = (JSON::size(target) > assertion.value);
    EVALUATE_END(assertion, AssertionStringSizeGreater);
  }

  case IS_INSTRUCTION(AssertionArraySizeLess): {
    EVALUATE_BEGIN(assertion, AssertionArraySizeLess, target.is_array());
    result = (target.size() < assertion.value);
    EVALUATE_END(assertion, AssertionArraySizeLess);
  }

  case IS_INSTRUCTION(AssertionArraySizeGreater): {
    EVALUATE_BEGIN(assertion, AssertionArraySizeGreater, target.is_array());
    result = (target.size() > assertion.value);
    EVALUATE_END(assertion, AssertionArraySizeGreater);
  }

  case IS_INSTRUCTION(AssertionObjectSizeLess): {
    EVALUATE_BEGIN(assertion, AssertionObjectSizeLess, target.is_object());
    result = (target.size() < assertion.value);
    EVALUATE_END(assertion, AssertionObjectSizeLess);
  }

  case IS_INSTRUCTION(AssertionObjectSizeGreater): {
    EVALUATE_BEGIN(assertion, AssertionObjectSizeGreater, target.is_object());
    result = (target.size() > assertion.value);
    EVALUATE_END(assertion, AssertionObjectSizeGreater);
  }

  case IS_INSTRUCTION(AssertionEqual): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionEqual);
    const auto &target{get(instance, assertion.relative_instance_location)};
    result = (target == assertion.value);
    EVALUATE_END(assertion, AssertionEqual);
  }

  case IS_INSTRUCTION(AssertionEqualsAny): {
    EVALUATE_BEGIN_NO_PRECONDITION(assertion, AssertionEqualsAny);
    const auto &target{get(instance, assertion.relative_instance_location)};
    result = assertion.value.contains(target);
    EVALUATE_END(assertion, AssertionEqualsAny);
  }

  case IS_INSTRUCTION(AssertionGreaterEqual): {
    EVALUATE_BEGIN(assertion, AssertionGreaterEqual, target.is_number());
    result = target >= assertion.value;
    EVALUATE_END(assertion, AssertionGreaterEqual);
  }

  case IS_INSTRUCTION(AssertionLessEqual): {
    EVALUATE_BEGIN(assertion, AssertionLessEqual, target.is_number());
    result = target <= assertion.value;
    EVALUATE_END(assertion, AssertionLessEqual);
  }

  case IS_INSTRUCTION(AssertionGreater): {
    EVALUATE_BEGIN(assertion, AssertionGreater, target.is_number());
    result = target > assertion.value;
    EVALUATE_END(assertion, AssertionGreater);
  }

  case IS_INSTRUCTION(AssertionLess): {
    EVALUATE_BEGIN(assertion, AssertionLess, target.is_number());
    result = target < assertion.value;
    EVALUATE_END(assertion, AssertionLess);
  }

  case IS_INSTRUCTION(AssertionUnique): {
    EVALUATE_BEGIN(assertion, AssertionUnique, target.is_array());
    result = target.unique();
    EVALUATE_END(assertion, AssertionUnique);
  }

  case IS_INSTRUCTION(AssertionDivisible): {
    EVALUATE_BEGIN(assertion, AssertionDivisible, target.is_number());
    assert(assertion.value.is_number());
    result = target.divisible_by(assertion.value);
    EVALUATE_END(assertion, AssertionDivisible);
  }

  case IS_INSTRUCTION(AssertionStringType): {
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

  case IS_INSTRUCTION(AssertionPropertyType): {
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

  case IS_INSTRUCTION(AssertionPropertyTypeEvaluate): {
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
      context.evaluate();
    }

    EVALUATE_END(assertion, AssertionPropertyTypeEvaluate);
  }

  case IS_INSTRUCTION(AssertionPropertyTypeStrict): {
    EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrict,
                              // Note that here are are referring to the parent
                              // object that might hold the given property,
                              // before traversing into the actual property
                              target.is_object());
    // Now here we refer to the actual property
    result = target_check.value().get().type() == assertion.value;
    EVALUATE_END(assertion, AssertionPropertyTypeStrict);
  }

  case IS_INSTRUCTION(AssertionPropertyTypeStrictEvaluate): {
    EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrictEvaluate,
                              // Note that here are are referring to the parent
                              // object that might hold the given property,
                              // before traversing into the actual property
                              target.is_object());
    // Now here we refer to the actual property
    result = target_check.value().get().type() == assertion.value;

    if (result) {
      context.evaluate();
    }

    EVALUATE_END(assertion, AssertionPropertyTypeStrictEvaluate);
  }

  case IS_INSTRUCTION(AssertionPropertyTypeStrictAny): {
    EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrictAny,
                              // Note that here are are referring to the parent
                              // object that might hold the given property,
                              // before traversing into the actual property
                              target.is_object());
    // Now here we refer to the actual property
    result = (std::find(assertion.value.cbegin(), assertion.value.cend(),
                        target_check.value().get().type()) !=
              assertion.value.cend());
    EVALUATE_END(assertion, AssertionPropertyTypeStrictAny);
  }

  case IS_INSTRUCTION(AssertionPropertyTypeStrictAnyEvaluate): {
    EVALUATE_BEGIN_TRY_TARGET(assertion, AssertionPropertyTypeStrictAnyEvaluate,
                              // Note that here are are referring to the parent
                              // object that might hold the given property,
                              // before traversing into the actual property
                              target.is_object());
    // Now here we refer to the actual property
    result = (std::find(assertion.value.cbegin(), assertion.value.cend(),
                        target_check.value().get().type()) !=
              assertion.value.cend());

    if (result) {
      context.evaluate();
    }

    EVALUATE_END(assertion, AssertionPropertyTypeStrictAnyEvaluate);
  }

  case IS_INSTRUCTION(AssertionArrayPrefix): {
    EVALUATE_BEGIN(assertion, AssertionArrayPrefix, target.is_array());
    // Otherwise there is no point in emitting this instruction
    assert(!assertion.children.empty());
    result = target.empty();
    const auto prefixes{assertion.children.size() - 1};
    const auto array_size{target.size()};
    if (!result) [[likely]] {
      const auto pointer{array_size == prefixes
                             ? prefixes
                             : std::min(array_size, prefixes) - 1};
      const auto &entry{assertion.children[pointer]};
      result = true;
      assert(std::holds_alternative<ControlGroup>(entry));
      for (const auto &child : std::get<ControlGroup>(entry).children) {
        if (!EVALUATE_RECURSE(child, target)) {
          result = false;
          break;
        }
      }
    }

    EVALUATE_END(assertion, AssertionArrayPrefix);
  }

  case IS_INSTRUCTION(AssertionArrayPrefixEvaluate): {
    EVALUATE_BEGIN(assertion, AssertionArrayPrefixEvaluate, target.is_array());
    // Otherwise there is no point in emitting this instruction
    assert(!assertion.children.empty());
    result = target.empty();
    const auto prefixes{assertion.children.size() - 1};
    const auto array_size{target.size()};
    if (!result) [[likely]] {
      const auto pointer{array_size == prefixes
                             ? prefixes
                             : std::min(array_size, prefixes) - 1};
      const auto &entry{assertion.children[pointer]};
      result = true;
      assert(std::holds_alternative<ControlGroup>(entry));
      for (const auto &child : std::get<ControlGroup>(entry).children) {
        if (!EVALUATE_RECURSE(child, target)) {
          result = false;
          EVALUATE_END(assertion, AssertionArrayPrefixEvaluate);
        }
      }

      assert(result);
      if (array_size == prefixes) {
        context.evaluate();
      } else {
        context.evaluate(0, pointer);
      }
    }

    EVALUATE_END(assertion, AssertionArrayPrefixEvaluate);
  }

  case IS_INSTRUCTION(LogicalOr): {
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

  case IS_INSTRUCTION(LogicalAnd): {
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

  case IS_INSTRUCTION(LogicalWhenType): {
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

  case IS_INSTRUCTION(LogicalWhenDefines): {
    EVALUATE_BEGIN(logical, LogicalWhenDefines,
                   target.is_object() && target.defines(logical.value));
    result = true;
    for (const auto &child : logical.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        break;
      }
    }

    EVALUATE_END(logical, LogicalWhenDefines);
  }

  case IS_INSTRUCTION(LogicalWhenArraySizeGreater): {
    EVALUATE_BEGIN(logical, LogicalWhenArraySizeGreater,
                   target.is_array() && target.size() > logical.value);
    result = true;
    for (const auto &child : logical.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        break;
      }
    }

    EVALUATE_END(logical, LogicalWhenArraySizeGreater);
  }

  case IS_INSTRUCTION(LogicalXor): {
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

  case IS_INSTRUCTION(LogicalCondition): {
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
        context.evaluate_path.pop_back(logical.relative_schema_location.size());

        for (auto cursor = consequence_start; cursor < consequence_end;
             cursor++) {
          if (!EVALUATE_RECURSE(logical.children[cursor], instance)) {
            result = false;
            break;
          }
        }

        context.evaluate_path.push_back(logical.relative_schema_location);
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

  case IS_INSTRUCTION(ControlGroup): {
    EVALUATE_BEGIN_PASS_THROUGH(control, ControlGroup);
    for (const auto &child : control.children) {
      if (!EVALUATE_RECURSE(child, instance)) {
        result = false;
        break;
      }
    }

    EVALUATE_END_PASS_THROUGH(ControlGroup);
  }

  case IS_INSTRUCTION(ControlGroupWhenDefines): {
    EVALUATE_BEGIN_PASS_THROUGH(control, ControlGroupWhenDefines);
    assert(!control.children.empty());

    // TODO: This is needed for nested `properties`, but can have a
    // performance impact. Maybe we can be smarter about when we
    // do this traversal?
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

  case IS_INSTRUCTION(ControlLabel): {
    EVALUATE_BEGIN_NO_PRECONDITION(control, ControlLabel);
    assert(!control.children.empty());
    context.labels.try_emplace(control.value, control.children);
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

  case IS_INSTRUCTION(ControlMark): {
    EVALUATE_BEGIN_NO_PRECONDITION_AND_NO_PUSH(control, ControlMark);
    context.labels.try_emplace(control.value, control.children);
    EVALUATE_END_NO_POP(control, ControlMark);
  }

  case IS_INSTRUCTION(ControlEvaluate): {
    EVALUATE_BEGIN_PASS_THROUGH(control, ControlEvaluate);

#ifdef SOURCEMETA_EVALUATOR_COMPLETE
    if (callback.has_value()) {
      // TODO: Optimize this case to avoid an extra pointer copy
      auto destination = context.instance_location;
      destination.push_back(control.value);
      callback.value()(EvaluationType::Pre, true, instruction,
                       context.evaluate_path, destination,
                       EvaluationContext::null);
      context.evaluate(control.value);
      callback.value()(EvaluationType::Post, true, instruction,
                       context.evaluate_path, destination,
                       EvaluationContext::null);
    } else {
      context.evaluate(control.value);
    }
#else
    SOURCEMETA_MAYBE_UNUSED(control);
#endif

    EVALUATE_END_PASS_THROUGH(ControlEvaluate);
  }

  case IS_INSTRUCTION(ControlJump): {
    EVALUATE_BEGIN_NO_PRECONDITION(control, ControlJump);
    result = true;
    assert(context.labels.contains(control.value));
    const auto &target{get(instance, control.relative_instance_location)};
    for (const auto &child : context.labels.at(control.value).get()) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = false;
        break;
      }
    }

    EVALUATE_END(control, ControlJump);
  }

  case IS_INSTRUCTION(ControlDynamicAnchorJump): {
    EVALUATE_BEGIN_NO_PRECONDITION(control, ControlDynamicAnchorJump);
    result = false;
    const auto &target{get(instance, control.relative_instance_location)};
    for (const auto &resource : context.resources) {
      const auto label{context.hash(resource, control.value)};
      const auto match{context.labels.find(label)};
      if (match != context.labels.cend()) {
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

  case IS_INSTRUCTION(AnnotationEmit): {
    EVALUATE_ANNOTATION(annotation, AnnotationEmit, context.instance_location,
                        annotation.value);
  }

  case IS_INSTRUCTION(AnnotationToParent): {
    EVALUATE_ANNOTATION(
        annotation, AnnotationToParent,
        // TODO: Can we avoid a copy of the instance location here?
        context.instance_location.initial(), annotation.value);
  }

  case IS_INSTRUCTION(AnnotationBasenameToParent): {
    EVALUATE_ANNOTATION(
        annotation, AnnotationBasenameToParent,
        // TODO: Can we avoid a copy of the instance location here?
        context.instance_location.initial(),
        context.instance_location.back().to_json());
  }

  case IS_INSTRUCTION(LogicalNot): {
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

  case IS_INSTRUCTION(LogicalNotEvaluate): {
    EVALUATE_BEGIN_NO_PRECONDITION(logical, LogicalNotEvaluate);

    const auto &target{get(instance, logical.relative_instance_location)};
    for (const auto &child : logical.children) {
      if (!EVALUATE_RECURSE(child, target)) {
        result = true;
        break;
      }
    }

    context.unevaluate();

    EVALUATE_END(logical, LogicalNotEvaluate);
  }

  case IS_INSTRUCTION(LoopPropertiesUnevaluated): {
    EVALUATE_BEGIN(loop, LoopPropertiesUnevaluated, target.is_object());
    assert(!loop.children.empty());
    result = true;

    for (const auto &entry : target.as_object()) {
      if (context.is_evaluated({entry.first})) {
        continue;
      }

      context.instance_location.push_back(entry.first);
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          context.instance_location.pop_back();
          EVALUATE_END(loop, LoopPropertiesUnevaluated);
        }
      }

      context.instance_location.pop_back();
    }

    // Mark the entire object as evaluated
    context.evaluate();

    EVALUATE_END(loop, LoopPropertiesUnevaluated);
  }

  case IS_INSTRUCTION(LoopPropertiesUnevaluatedExcept): {
    EVALUATE_BEGIN(loop, LoopPropertiesUnevaluatedExcept, target.is_object());
    assert(!loop.children.empty());
    result = true;
    // Otherwise why emit this instruction?
    assert(!std::get<0>(loop.value).empty() ||
           !std::get<1>(loop.value).empty() ||
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
                        return validate(pattern.first, entry.first);
                      })) {
        continue;
      }

      if (context.is_evaluated({entry.first})) {
        continue;
      }

      context.instance_location.push_back(entry.first);
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          context.instance_location.pop_back();
          EVALUATE_END(loop, LoopPropertiesUnevaluatedExcept);
        }
      }

      context.instance_location.pop_back();
    }

    // Mark the entire object as evaluated
    context.evaluate();

    EVALUATE_END(loop, LoopPropertiesUnevaluatedExcept);
  }

  case IS_INSTRUCTION(LoopPropertiesMatch): {
    EVALUATE_BEGIN(loop, LoopPropertiesMatch, target.is_object());
    assert(!loop.value.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      const auto index{loop.value.find(entry.first)};
      if (index == loop.value.cend()) {
        continue;
      }

      const auto &subinstruction{loop.children[index->second]};
      assert(std::holds_alternative<ControlGroup>(subinstruction));
      for (const auto &child :
           std::get<ControlGroup>(subinstruction).children) {
        if (!EVALUATE_RECURSE(child, target)) {
          result = false;
          EVALUATE_END(loop, LoopPropertiesMatch);
        }
      }
    }

    EVALUATE_END(loop, LoopPropertiesMatch);
  }

  case IS_INSTRUCTION(LoopPropertiesMatchClosed): {
    EVALUATE_BEGIN(loop, LoopPropertiesMatchClosed, target.is_object());
    assert(!loop.value.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      const auto index{loop.value.find(entry.first)};
      if (index == loop.value.cend()) {
        result = false;
        break;
      }

      const auto &subinstruction{loop.children[index->second]};
      assert(std::holds_alternative<ControlGroup>(subinstruction));
      for (const auto &child :
           std::get<ControlGroup>(subinstruction).children) {
        if (!EVALUATE_RECURSE(child, target)) {
          result = false;
          EVALUATE_END(loop, LoopPropertiesMatchClosed);
        }
      }
    }

    EVALUATE_END(loop, LoopPropertiesMatchClosed);
  }

  case IS_INSTRUCTION(LoopProperties): {
    EVALUATE_BEGIN(loop, LoopProperties, target.is_object());
    assert(!loop.children.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopProperties);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopProperties);
  }

  case IS_INSTRUCTION(LoopPropertiesEvaluate): {
    EVALUATE_BEGIN(loop, LoopPropertiesEvaluate, target.is_object());
    assert(!loop.children.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopPropertiesEvaluate);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    context.evaluate();

    EVALUATE_END(loop, LoopPropertiesEvaluate);
  }

  case IS_INSTRUCTION(LoopPropertiesRegex): {
    EVALUATE_BEGIN(loop, LoopPropertiesRegex, target.is_object());
    assert(!loop.children.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (!validate(loop.value.first, entry.first)) {
        continue;
      }

      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopPropertiesRegex);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopPropertiesRegex);
  }

  case IS_INSTRUCTION(LoopPropertiesRegexClosed): {
    EVALUATE_BEGIN(loop, LoopPropertiesRegexClosed, target.is_object());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (!validate(loop.value.first, entry.first)) {
        result = false;
        break;
      }

      if (loop.children.empty()) {
        continue;
      }

      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopPropertiesRegexClosed);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopPropertiesRegexClosed);
  }

  case IS_INSTRUCTION(LoopPropertiesStartsWith): {
    EVALUATE_BEGIN(loop, LoopPropertiesStartsWith, target.is_object());
    assert(!loop.children.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (!entry.first.starts_with(loop.value)) {
        continue;
      }

      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopPropertiesStartsWith);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopPropertiesStartsWith);
  }

  case IS_INSTRUCTION(LoopPropertiesExcept): {
    EVALUATE_BEGIN(loop, LoopPropertiesExcept, target.is_object());
    assert(!loop.children.empty());
    result = true;
    // Otherwise why emit this instruction?
    assert(!std::get<0>(loop.value).empty() ||
           !std::get<1>(loop.value).empty() ||
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
                        return validate(pattern.first, entry.first);
                      })) {
        continue;
      }

      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopPropertiesExcept);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopPropertiesExcept);
  }

  case IS_INSTRUCTION(LoopPropertiesWhitelist): {
    EVALUATE_BEGIN(loop, LoopPropertiesWhitelist, target.is_object());
    // Otherwise why emit this instruction?
    assert(!loop.value.empty());

    // Otherwise if the number of properties in the instance
    // is larger than the whitelist, then it already violated
    // the whitelist?
    if (target.size() <= loop.value.size()) {
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

  case IS_INSTRUCTION(LoopPropertiesType): {
    EVALUATE_BEGIN(loop, LoopPropertiesType, target.is_object());
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

  case IS_INSTRUCTION(LoopPropertiesTypeEvaluate): {
    EVALUATE_BEGIN(loop, LoopPropertiesTypeEvaluate, target.is_object());
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

    context.evaluate();

    EVALUATE_END(loop, LoopPropertiesTypeEvaluate);
  }

  case IS_INSTRUCTION(LoopPropertiesTypeStrict): {
    EVALUATE_BEGIN(loop, LoopPropertiesTypeStrict, target.is_object());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (entry.second.type() != loop.value) {
        result = false;
        break;
      }
    }

    EVALUATE_END(loop, LoopPropertiesTypeStrict);
  }

  case IS_INSTRUCTION(LoopPropertiesTypeStrictEvaluate): {
    EVALUATE_BEGIN(loop, LoopPropertiesTypeStrictEvaluate, target.is_object());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (entry.second.type() != loop.value) {
        result = false;
        EVALUATE_END(loop, LoopPropertiesTypeStrictEvaluate);
      }
    }

    context.evaluate();

    EVALUATE_END(loop, LoopPropertiesTypeStrictEvaluate);
  }

  case IS_INSTRUCTION(LoopPropertiesTypeStrictAny): {
    EVALUATE_BEGIN(loop, LoopPropertiesTypeStrictAny, target.is_object());
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

  case IS_INSTRUCTION(LoopPropertiesTypeStrictAnyEvaluate): {
    EVALUATE_BEGIN(loop, LoopPropertiesTypeStrictAnyEvaluate,
                   target.is_object());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (std::find(loop.value.cbegin(), loop.value.cend(),
                    entry.second.type()) == loop.value.cend()) {
        result = false;
        EVALUATE_END(loop, LoopPropertiesTypeStrictAnyEvaluate);
      }
    }

    context.evaluate();

    EVALUATE_END(loop, LoopPropertiesTypeStrictAnyEvaluate);
  }

  case IS_INSTRUCTION(LoopKeys): {
    EVALUATE_BEGIN(loop, LoopKeys, target.is_object());
    assert(!loop.children.empty());
    result = true;
    for (const auto &entry : target.as_object()) {
      if (track) {
        context.instance_location.push_back(entry.first);
      }
      const auto &new_instance{target.at(entry.first)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE_ON_PROPERTY_NAME(child, new_instance,
                                               entry.first)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopKeys);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopKeys);
  }

  case IS_INSTRUCTION(LoopItemsFrom): {
    EVALUATE_BEGIN(loop, LoopItemsFrom,
                   target.is_array() && loop.value < target.size());
    assert(!loop.children.empty());
    result = true;
    for (std::size_t index = loop.value; index < target.size(); index++) {
      if (track) {
        context.instance_location.push_back(index);
      }
      const auto &new_instance{target.at(index)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          if (track) {
            context.instance_location.pop_back();
          }
          EVALUATE_END(loop, LoopItemsFrom);
        }
      }

      if (track) {
        context.instance_location.pop_back();
      }
    }

    EVALUATE_END(loop, LoopItemsFrom);
  }

  case IS_INSTRUCTION(LoopItemsUnevaluated): {
    EVALUATE_BEGIN(loop, LoopItemsUnevaluated, target.is_array());
    assert(!loop.children.empty());
    result = true;

    for (std::size_t index = 0; index < target.size(); index++) {
      if (context.is_evaluated(index)) {
        continue;
      }

      context.instance_location.push_back(index);
      const auto &new_instance{target.at(index)};
      for (const auto &child : loop.children) {
        if (!EVALUATE_RECURSE(child, new_instance)) {
          result = false;
          context.instance_location.pop_back();
          EVALUATE_END(loop, LoopItemsUnevaluated);
        }
      }

      context.instance_location.pop_back();
    }

    // Mark the entire array as evaluated
    context.evaluate();

    EVALUATE_END(loop, LoopItemsUnevaluated);
  }

  case IS_INSTRUCTION(LoopItemsType): {
    EVALUATE_BEGIN(loop, LoopItemsType, target.is_array());
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

  case IS_INSTRUCTION(LoopItemsTypeStrict): {
    EVALUATE_BEGIN(loop, LoopItemsTypeStrict, target.is_array());
    result = true;
    for (const auto &entry : target.as_array()) {
      if (entry.type() != loop.value) {
        result = false;
        break;
      }
    }

    EVALUATE_END(loop, LoopItemsTypeStrict);
  }

  case IS_INSTRUCTION(LoopItemsTypeStrictAny): {
    EVALUATE_BEGIN(loop, LoopItemsTypeStrictAny, target.is_array());
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

  case IS_INSTRUCTION(LoopContains): {
    EVALUATE_BEGIN(loop, LoopContains, target.is_array());
    assert(!loop.children.empty());
    const auto minimum{std::get<0>(loop.value)};
    const auto &maximum{std::get<1>(loop.value)};
    assert(!maximum.has_value() || maximum.value() >= minimum);
    const auto is_exhaustive{std::get<2>(loop.value)};
    result = minimum == 0 && target.empty();
    auto match_count{std::numeric_limits<decltype(minimum)>::min()};

    for (std::size_t index = 0; index < target.size(); index++) {
      if (track) {
        context.instance_location.push_back(index);
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
        context.instance_location.pop_back();
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

  default:
    // See https://en.cppreference.com/w/cpp/utility/unreachable
#if defined(_MSC_VER) && !defined(__clang__)
    __assume(false);
#else
    __builtin_unreachable();
#endif
}

#undef IS_INSTRUCTION
