#ifndef SOURCEMETA_BLAZE_EVALUATOR_TEMPLATE_H
#define SOURCEMETA_BLAZE_EVALUATOR_TEMPLATE_H

#include <sourcemeta/blaze/evaluator_value.h>

#include <sourcemeta/jsontoolkit/jsonpointer.h>

#include <cstdint> // std::uint8_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace sourcemeta::blaze {

// For fast internal instruction dispatching. It must stay
// in sync with the variant ordering above
/// @ingroup evaluator
enum class InstructionIndex : std::uint8_t {
  AssertionFail = 0,
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
  ControlDynamicAnchorJump
};

// Forward declaration for defining a circular structure
#ifndef DOXYGEN
struct Instruction;
#endif

/// @ingroup evaluator
/// Represents a set of schema compilation steps that can be evaluated
using Instructions = std::vector<Instruction>;

/// @ingroup evaluator
/// Represents a single instruction to be evaluated
struct Instruction {
  const InstructionIndex type;
  const sourcemeta::jsontoolkit::Pointer relative_schema_location;
  const sourcemeta::jsontoolkit::Pointer relative_instance_location;
  const std::string keyword_location;
  const std::size_t schema_resource;
  const Value value;
  const Instructions children;
};

} // namespace sourcemeta::blaze

#endif