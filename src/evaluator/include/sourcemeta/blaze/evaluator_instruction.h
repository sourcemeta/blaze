#ifndef SOURCEMETA_BLAZE_EVALUATOR_TEMPLATE_H
#define SOURCEMETA_BLAZE_EVALUATOR_TEMPLATE_H

#include <sourcemeta/blaze/evaluator_value.h>

#include <sourcemeta/jsontoolkit/jsonpointer.h>

#include <cstdint> // std::uint8_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace sourcemeta::blaze {

// Forward declarations for the sole purpose of being bale to define circular
// structures
#ifndef DOXYGEN
struct AssertionFail;
struct AssertionDefines;
struct AssertionDefinesStrict;
struct AssertionDefinesAll;
struct AssertionDefinesAllStrict;
struct AssertionDefinesExactly;
struct AssertionDefinesExactlyStrict;
struct AssertionPropertyDependencies;
struct AssertionType;
struct AssertionTypeAny;
struct AssertionTypeStrict;
struct AssertionTypeStrictAny;
struct AssertionTypeStringBounded;
struct AssertionTypeStringUpper;
struct AssertionTypeArrayBounded;
struct AssertionTypeArrayUpper;
struct AssertionTypeObjectBounded;
struct AssertionTypeObjectUpper;
struct AssertionRegex;
struct AssertionStringSizeLess;
struct AssertionStringSizeGreater;
struct AssertionArraySizeLess;
struct AssertionArraySizeGreater;
struct AssertionObjectSizeLess;
struct AssertionObjectSizeGreater;
struct AssertionEqual;
struct AssertionEqualsAny;
struct AssertionGreaterEqual;
struct AssertionLessEqual;
struct AssertionGreater;
struct AssertionLess;
struct AssertionUnique;
struct AssertionDivisible;
struct AssertionStringType;
struct AssertionPropertyType;
struct AssertionPropertyTypeEvaluate;
struct AssertionPropertyTypeStrict;
struct AssertionPropertyTypeStrictEvaluate;
struct AssertionPropertyTypeStrictAny;
struct AssertionPropertyTypeStrictAnyEvaluate;
struct AssertionArrayPrefix;
struct AssertionArrayPrefixEvaluate;
struct AnnotationEmit;
struct AnnotationToParent;
struct AnnotationBasenameToParent;
struct LogicalNot;
struct LogicalNotEvaluate;
struct LogicalOr;
struct LogicalAnd;
struct LogicalXor;
struct LogicalCondition;
struct LogicalWhenType;
struct LogicalWhenDefines;
struct LogicalWhenArraySizeGreater;
struct LoopPropertiesUnevaluated;
struct LoopPropertiesUnevaluatedExcept;
struct LoopPropertiesMatch;
struct LoopPropertiesMatchClosed;
struct LoopProperties;
struct LoopPropertiesEvaluate;
struct LoopPropertiesRegex;
struct LoopPropertiesRegexClosed;
struct LoopPropertiesStartsWith;
struct LoopPropertiesExcept;
struct LoopPropertiesWhitelist;
struct LoopPropertiesType;
struct LoopPropertiesTypeEvaluate;
struct LoopPropertiesTypeStrict;
struct LoopPropertiesTypeStrictEvaluate;
struct LoopPropertiesTypeStrictAny;
struct LoopPropertiesTypeStrictAnyEvaluate;
struct LoopKeys;
struct LoopItems;
struct LoopItemsFrom;
struct LoopItemsUnevaluated;
struct LoopItemsType;
struct LoopItemsTypeStrict;
struct LoopItemsTypeStrictAny;
struct LoopContains;
struct ControlGroup;
struct ControlGroupWhenDefines;
struct ControlGroupWhenDefinesDirect;
struct ControlLabel;
struct ControlMark;
struct ControlEvaluate;
struct ControlJump;
struct ControlDynamicAnchorJump;
#endif

/// @ingroup evaluator
/// Represents a schema compilation step that can be evaluated
using Instruction = std::variant<
    AssertionFail, AssertionDefines, AssertionDefinesStrict,
    AssertionDefinesAll, AssertionDefinesAllStrict, AssertionDefinesExactly,
    AssertionDefinesExactlyStrict, AssertionPropertyDependencies, AssertionType,
    AssertionTypeAny, AssertionTypeStrict, AssertionTypeStrictAny,
    AssertionTypeStringBounded, AssertionTypeStringUpper,
    AssertionTypeArrayBounded, AssertionTypeArrayUpper,
    AssertionTypeObjectBounded, AssertionTypeObjectUpper, AssertionRegex,
    AssertionStringSizeLess, AssertionStringSizeGreater, AssertionArraySizeLess,
    AssertionArraySizeGreater, AssertionObjectSizeLess,
    AssertionObjectSizeGreater, AssertionEqual, AssertionEqualsAny,
    AssertionGreaterEqual, AssertionLessEqual, AssertionGreater, AssertionLess,
    AssertionUnique, AssertionDivisible, AssertionStringType,
    AssertionPropertyType, AssertionPropertyTypeEvaluate,
    AssertionPropertyTypeStrict, AssertionPropertyTypeStrictEvaluate,
    AssertionPropertyTypeStrictAny, AssertionPropertyTypeStrictAnyEvaluate,
    AssertionArrayPrefix, AssertionArrayPrefixEvaluate, AnnotationEmit,
    AnnotationToParent, AnnotationBasenameToParent, LogicalNot,
    LogicalNotEvaluate, LogicalOr, LogicalAnd, LogicalXor, LogicalCondition,
    LogicalWhenType, LogicalWhenDefines, LogicalWhenArraySizeGreater,
    LoopPropertiesUnevaluated, LoopPropertiesUnevaluatedExcept,
    LoopPropertiesMatch, LoopPropertiesMatchClosed, LoopProperties,
    LoopPropertiesEvaluate, LoopPropertiesRegex, LoopPropertiesRegexClosed,
    LoopPropertiesStartsWith, LoopPropertiesExcept, LoopPropertiesWhitelist,
    LoopPropertiesType, LoopPropertiesTypeEvaluate, LoopPropertiesTypeStrict,
    LoopPropertiesTypeStrictEvaluate, LoopPropertiesTypeStrictAny,
    LoopPropertiesTypeStrictAnyEvaluate, LoopKeys, LoopItems, LoopItemsFrom,
    LoopItemsUnevaluated, LoopItemsType, LoopItemsTypeStrict,
    LoopItemsTypeStrictAny, LoopContains, ControlGroup, ControlGroupWhenDefines,
    ControlGroupWhenDefinesDirect, ControlLabel, ControlMark, ControlEvaluate,
    ControlJump, ControlDynamicAnchorJump>;

// For fast internal instruction dispatching. It must stay
// in sync with the variant ordering above
enum class InstructionIndex : std::uint8_t {
  /// @brief Represents a compiler assertion step that always fails
  AssertionFail = 0,
  /// @brief Represents a compiler assertion step that checks if an object
  /// defines
  /// a given property
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

/// @ingroup evaluator
/// Represents a set of schema compilation steps that can be evaluated
using Instructions = std::vector<Instruction>;

#define DEFINE_STEP(category, name)                                            \
  struct category##name {                                                      \
    const InstructionIndex type;                                               \
    const sourcemeta::jsontoolkit::Pointer relative_schema_location;           \
    const sourcemeta::jsontoolkit::Pointer relative_instance_location;         \
    const std::string keyword_location;                                        \
    const std::size_t schema_resource;                                         \
    const Value value;                                                         \
    const Instructions children;                                               \
  };

DEFINE_STEP(Assertion, Fail)
DEFINE_STEP(Assertion, Defines)
DEFINE_STEP(Assertion, DefinesStrict)
DEFINE_STEP(Assertion, DefinesAll)
DEFINE_STEP(Assertion, DefinesAllStrict)
DEFINE_STEP(Assertion, DefinesExactly)
DEFINE_STEP(Assertion, DefinesExactlyStrict)
DEFINE_STEP(Assertion, PropertyDependencies)
DEFINE_STEP(Assertion, Type)
DEFINE_STEP(Assertion, TypeAny)
DEFINE_STEP(Assertion, TypeStrict)
DEFINE_STEP(Assertion, TypeStrictAny)
DEFINE_STEP(Assertion, TypeStringBounded)
DEFINE_STEP(Assertion, TypeStringUpper)
DEFINE_STEP(Assertion, TypeArrayBounded)
DEFINE_STEP(Assertion, TypeArrayUpper)
DEFINE_STEP(Assertion, TypeObjectBounded)
DEFINE_STEP(Assertion, TypeObjectUpper)
DEFINE_STEP(Assertion, Regex)
DEFINE_STEP(Assertion, StringSizeLess)
DEFINE_STEP(Assertion, StringSizeGreater)
DEFINE_STEP(Assertion, ArraySizeLess)
DEFINE_STEP(Assertion, ArraySizeGreater)
DEFINE_STEP(Assertion, ObjectSizeLess)
DEFINE_STEP(Assertion, ObjectSizeGreater)
DEFINE_STEP(Assertion, Equal)
DEFINE_STEP(Assertion, EqualsAny)
DEFINE_STEP(Assertion, GreaterEqual)
DEFINE_STEP(Assertion, LessEqual)
DEFINE_STEP(Assertion, Greater)
DEFINE_STEP(Assertion, Less)
DEFINE_STEP(Assertion, Unique)
DEFINE_STEP(Assertion, Divisible)
DEFINE_STEP(Assertion, StringType)
DEFINE_STEP(Assertion, PropertyType)
DEFINE_STEP(Assertion, PropertyTypeEvaluate)
DEFINE_STEP(Assertion, PropertyTypeStrict)
DEFINE_STEP(Assertion, PropertyTypeStrictEvaluate)
DEFINE_STEP(Assertion, PropertyTypeStrictAny)
DEFINE_STEP(Assertion, PropertyTypeStrictAnyEvaluate)
DEFINE_STEP(Assertion, ArrayPrefix)
DEFINE_STEP(Assertion, ArrayPrefixEvaluate)
DEFINE_STEP(Annotation, Emit)
DEFINE_STEP(Annotation, ToParent)
DEFINE_STEP(Annotation, BasenameToParent)
DEFINE_STEP(Logical, Not)
DEFINE_STEP(Logical, NotEvaluate)
DEFINE_STEP(Logical, Or)
DEFINE_STEP(Logical, And)
DEFINE_STEP(Logical, Xor)
DEFINE_STEP(Logical, Condition)
DEFINE_STEP(Logical, WhenType)
DEFINE_STEP(Logical, WhenDefines)
DEFINE_STEP(Logical, WhenArraySizeGreater)
DEFINE_STEP(Loop, PropertiesUnevaluated)
DEFINE_STEP(Loop, PropertiesUnevaluatedExcept)
DEFINE_STEP(Loop, PropertiesMatch)
DEFINE_STEP(Loop, PropertiesMatchClosed)
DEFINE_STEP(Loop, Properties)
DEFINE_STEP(Loop, PropertiesEvaluate)
DEFINE_STEP(Loop, PropertiesRegex)
DEFINE_STEP(Loop, PropertiesRegexClosed)
DEFINE_STEP(Loop, PropertiesStartsWith)
DEFINE_STEP(Loop, PropertiesExcept)
DEFINE_STEP(Loop, PropertiesWhitelist)
DEFINE_STEP(Loop, PropertiesType)
DEFINE_STEP(Loop, PropertiesTypeEvaluate)
DEFINE_STEP(Loop, PropertiesTypeStrict)
DEFINE_STEP(Loop, PropertiesTypeStrictEvaluate)
DEFINE_STEP(Loop, PropertiesTypeStrictAny)
DEFINE_STEP(Loop, PropertiesTypeStrictAnyEvaluate)
DEFINE_STEP(Loop, Keys)
DEFINE_STEP(Loop, Items)
DEFINE_STEP(Loop, ItemsFrom)
DEFINE_STEP(Loop, ItemsUnevaluated)
DEFINE_STEP(Loop, ItemsType)
DEFINE_STEP(Loop, ItemsTypeStrict)
DEFINE_STEP(Loop, ItemsTypeStrictAny)
DEFINE_STEP(Loop, Contains)
DEFINE_STEP(Control, Group)
DEFINE_STEP(Control, GroupWhenDefines)
DEFINE_STEP(Control, GroupWhenDefinesDirect)
DEFINE_STEP(Control, Label)
DEFINE_STEP(Control, Mark)
DEFINE_STEP(Control, Evaluate)
DEFINE_STEP(Control, Jump)
DEFINE_STEP(Control, DynamicAnchorJump)

#undef DEFINE_STEP

} // namespace sourcemeta::blaze

#endif
