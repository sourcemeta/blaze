#ifndef SOURCEMETA_BLAZE_EVALUATOR_TEMPLATE_H
#define SOURCEMETA_BLAZE_EVALUATOR_TEMPLATE_H

#ifndef SOURCEMETA_BLAZE_EVALUATOR_EXPORT
#include <sourcemeta/blaze/evaluator_export.h>
#endif

#include <sourcemeta/blaze/evaluator_value.h>

#include <sourcemeta/core/jsonpointer.h>

#include <cstdint>     // std::uint8_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

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
  AssertionDefinesExactlyStrictHash3,
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
  AssertionEqualsAnyStringHash,
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
  Evaluate,
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
  LoopPropertiesType,
  LoopPropertiesTypeEvaluate,
  LoopPropertiesExactlyTypeStrict,
  LoopPropertiesExactlyTypeStrictHash,
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
  LoopItemsPropertiesExactlyTypeStrictHash,
  LoopItemsPropertiesExactlyTypeStrictHash3,
  LoopContains,
  ControlGroup,
  ControlGroupWhenDefines,
  ControlGroupWhenDefinesDirect,
  ControlGroupWhenType,
  ControlEvaluate,
  ControlDynamicAnchorJump,
  ControlJump
};

/// @ingroup evaluator
// NOLINTNEXTLINE(modernize-avoid-c-arrays)
constexpr std::string_view InstructionNames[] = {
    "AssertionFail",
    "AssertionDefines",
    "AssertionDefinesStrict",
    "AssertionDefinesAll",
    "AssertionDefinesAllStrict",
    "AssertionDefinesExactly",
    "AssertionDefinesExactlyStrict",
    "AssertionDefinesExactlyStrictHash3",
    "AssertionPropertyDependencies",
    "AssertionType",
    "AssertionTypeAny",
    "AssertionTypeStrict",
    "AssertionTypeStrictAny",
    "AssertionTypeStringBounded",
    "AssertionTypeStringUpper",
    "AssertionTypeArrayBounded",
    "AssertionTypeArrayUpper",
    "AssertionTypeObjectBounded",
    "AssertionTypeObjectUpper",
    "AssertionRegex",
    "AssertionStringSizeLess",
    "AssertionStringSizeGreater",
    "AssertionArraySizeLess",
    "AssertionArraySizeGreater",
    "AssertionObjectSizeLess",
    "AssertionObjectSizeGreater",
    "AssertionEqual",
    "AssertionEqualsAny",
    "AssertionEqualsAnyStringHash",
    "AssertionGreaterEqual",
    "AssertionLessEqual",
    "AssertionGreater",
    "AssertionLess",
    "AssertionUnique",
    "AssertionDivisible",
    "AssertionStringType",
    "AssertionPropertyType",
    "AssertionPropertyTypeEvaluate",
    "AssertionPropertyTypeStrict",
    "AssertionPropertyTypeStrictEvaluate",
    "AssertionPropertyTypeStrictAny",
    "AssertionPropertyTypeStrictAnyEvaluate",
    "AssertionArrayPrefix",
    "AssertionArrayPrefixEvaluate",
    "AnnotationEmit",
    "AnnotationToParent",
    "AnnotationBasenameToParent",
    "Evaluate",
    "LogicalNot",
    "LogicalNotEvaluate",
    "LogicalOr",
    "LogicalAnd",
    "LogicalXor",
    "LogicalCondition",
    "LogicalWhenType",
    "LogicalWhenDefines",
    "LogicalWhenArraySizeGreater",
    "LoopPropertiesUnevaluated",
    "LoopPropertiesUnevaluatedExcept",
    "LoopPropertiesMatch",
    "LoopPropertiesMatchClosed",
    "LoopProperties",
    "LoopPropertiesEvaluate",
    "LoopPropertiesRegex",
    "LoopPropertiesRegexClosed",
    "LoopPropertiesStartsWith",
    "LoopPropertiesExcept",
    "LoopPropertiesType",
    "LoopPropertiesTypeEvaluate",
    "LoopPropertiesExactlyTypeStrict",
    "LoopPropertiesExactlyTypeStrictHash",
    "LoopPropertiesTypeStrict",
    "LoopPropertiesTypeStrictEvaluate",
    "LoopPropertiesTypeStrictAny",
    "LoopPropertiesTypeStrictAnyEvaluate",
    "LoopKeys",
    "LoopItems",
    "LoopItemsFrom",
    "LoopItemsUnevaluated",
    "LoopItemsType",
    "LoopItemsTypeStrict",
    "LoopItemsTypeStrictAny",
    "LoopItemsPropertiesExactlyTypeStrictHash",
    "LoopItemsPropertiesExactlyTypeStrictHash3",
    "LoopContains",
    "ControlGroup",
    "ControlGroupWhenDefines",
    "ControlGroupWhenDefinesDirect",
    "ControlGroupWhenType",
    "ControlEvaluate",
    "ControlDynamicAnchorJump",
    "ControlJump"};

/// @ingroup evaluator
/// Check if a given instruction type corresponds to an annotation
inline auto is_annotation(const InstructionIndex type) noexcept -> bool {
  switch (type) {
    // NOLINTNEXTLINE(bugprone-branch-clone)
    case InstructionIndex::AnnotationBasenameToParent:
      return true;
    case InstructionIndex::AnnotationToParent:
      return true;
    case InstructionIndex::AnnotationEmit:
      return true;
    default:
      return false;
  }
}

// Forward declaration for defining a circular structure
#ifndef DOXYGEN
struct TreeInstruction;
#endif

/// @ingroup evaluator
/// Represents a set of tree-shaped schema compilation steps
using TreeInstructions = std::vector<TreeInstruction>;

/// @ingroup evaluator
/// Represents a single tree-shaped instruction (used internally by compiler)
// NOLINTNEXTLINE(bugprone-exception-escape)
struct TreeInstruction {
  InstructionIndex type;
  sourcemeta::core::Pointer relative_schema_location;
  sourcemeta::core::Pointer relative_instance_location;
  std::string keyword_location;
  std::size_t schema_resource;
  Value value;
  TreeInstructions children;
};

/// @ingroup evaluator
/// Represents a single instruction for evaluation
// NOLINTNEXTLINE(bugprone-exception-escape)
struct Instruction {
  InstructionIndex type;
  sourcemeta::core::Pointer relative_schema_location;
  sourcemeta::core::Pointer relative_instance_location;
  std::string keyword_location;
  std::size_t schema_resource;
  Value value;
  std::uint32_t children_count{0};
  std::uint32_t direct_children_count{0};
  std::uint32_t flat_offset{0};
  std::uint32_t next_sibling_offset{0};
};

/// @ingroup evaluator
/// Represents a set of instructions for evaluation
using Instructions = std::vector<Instruction>;

/// @ingroup evaluator
///
/// This function translates a "post" step execution into a human-readable
/// string. Useful as the building block for producing user-friendly evaluation
/// results.
///
/// Note that describing a "pre" step execution is NOT supported.
auto SOURCEMETA_BLAZE_EVALUATOR_EXPORT
describe(const bool valid, const Instruction &step,
         const Instructions &all_instructions,
         const sourcemeta::core::WeakPointer &evaluate_path,
         const sourcemeta::core::WeakPointer &instance_location,
         const sourcemeta::core::JSON &instance,
         const sourcemeta::core::JSON &annotation) -> std::string;

} // namespace sourcemeta::blaze

#endif
