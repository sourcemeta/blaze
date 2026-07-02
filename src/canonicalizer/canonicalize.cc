#include <sourcemeta/blaze/canonicalizer.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/core/regex.h>
#include <sourcemeta/core/uri.h>

#include "canonicalizer_transformer.h"

// For built-in rules
#include <algorithm>     // std::sort, std::unique, std::ranges::none_of
#include <array>         // std::array
#include <bit>           // std::popcount
#include <cassert>       // assert
#include <cmath>         // std::floor, std::ceil, std::isfinite
#include <cstddef>       // std::size_t
#include <functional>    // std::ref
#include <iterator>      // std::back_inserter
#include <limits>        // std::numeric_limits
#include <memory>        // std::unique_ptr, std::make_unique
#include <sstream>       // std::ostringstream
#include <string_view>   // std::string_view
#include <unordered_map> // std::unordered_map
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move, std::to_underlying

namespace sourcemeta::blaze::canonicalizer {

using namespace sourcemeta::core;

// TODO: Move upstream
inline auto IS_IN_PLACE_APPLICATOR(const SchemaKeywordType type) -> bool {
  return type == SchemaKeywordType::ApplicatorValueOrElementsInPlace ||
         type == SchemaKeywordType::ApplicatorMembersInPlaceSome ||
         type == SchemaKeywordType::ApplicatorElementsInPlace ||
         type == SchemaKeywordType::ApplicatorElementsInPlaceSome ||
         type == SchemaKeywordType::ApplicatorElementsInPlaceSomeNegate ||
         type == SchemaKeywordType::ApplicatorValueInPlaceMaybe ||
         type == SchemaKeywordType::ApplicatorValueInPlaceOther ||
         type == SchemaKeywordType::ApplicatorValueInPlaceNegate;
}

// Walk up from a schema location, continuing as long as the traversal
// predicate returns true for each keyword type encountered. Returns a
// reference to the pointer of the ancestor where the match callback returned
// true, or nullopt if no match was found or the traversal predicate stopped
// the walk.
template <typename TraversePredicate, typename MatchCallback>
auto WALK_UP(const JSON &root, const SchemaFrame &frame,
             const SchemaFrame::Location &location, const SchemaWalker &walker,
             const SchemaResolver &resolver,
             const TraversePredicate &should_continue,
             const MatchCallback &matches)
    -> std::optional<std::reference_wrapper<const WeakPointer>> {
  auto current_pointer{location.pointer};
  auto current_parent{location.parent};

  while (current_parent.has_value()) {
    const auto &parent_pointer{current_parent.value()};
    const auto relative_pointer{current_pointer.resolve_from(parent_pointer)};
    assert(!relative_pointer.empty() && relative_pointer.at(0).is_property());
    const auto parent{frame.traverse(frame.uri(parent_pointer).value().get())};
    assert(parent.has_value());
    const auto parent_vocabularies{
        frame.vocabularies(parent.value().get(), resolver)};
    const auto keyword_type{
        walker(relative_pointer.at(0).to_property(), parent_vocabularies).type};

    if (!should_continue(keyword_type)) {
      return std::nullopt;
    }

    if (matches(get(root, parent_pointer), parent_vocabularies)) {
      return std::cref(parent.value().get().pointer);
    }

    current_pointer = parent_pointer;
    current_parent = parent.value().get().parent;
  }

  return std::nullopt;
}

template <typename MatchCallback>
auto WALK_UP_IN_PLACE_APPLICATORS(const JSON &root, const SchemaFrame &frame,
                                  const SchemaFrame::Location &location,
                                  const SchemaWalker &walker,
                                  const SchemaResolver &resolver,
                                  const MatchCallback &matches)
    -> std::optional<std::reference_wrapper<const WeakPointer>> {
  return WALK_UP(root, frame, location, walker, resolver,
                 IS_IN_PLACE_APPLICATOR, matches);
}

#define ONLY_CONTINUE_IF(condition)                                            \
  if (!(condition)) {                                                          \
    return false;                                                              \
  }

#include "rules/additional_items_implicit.h"
#include "rules/allof_false_simplify.h"
#include "rules/allof_merge_compatible_branches.h"
#include "rules/anyof_false_simplify.h"
#include "rules/anyof_remove_false_schemas.h"
#include "rules/anyof_true_simplify.h"
#include "rules/comment_drop.h"
#include "rules/const_as_enum.h"
#include "rules/const_in_enum.h"
#include "rules/const_with_type.h"
#include "rules/content_media_type_without_encoding.h"
#include "rules/content_schema_without_media_type.h"
#include "rules/definitions_to_defs.h"
#include "rules/dependencies_property_tautology.h"
#include "rules/dependencies_to_any_of.h"
#include "rules/dependencies_to_extends_disallow.h"
#include "rules/dependent_required_tautology.h"
#include "rules/dependent_required_to_any_of.h"
#include "rules/dependent_schemas_to_any_of.h"
#include "rules/deprecated_false_drop.h"
#include "rules/disallow_array_to_extends.h"
#include "rules/disallow_double_negation.h"
#include "rules/disallow_extends_to_type.h"
#include "rules/disallow_narrows_type.h"
#include "rules/disallow_to_array_of_schemas.h"
#include "rules/disallow_type_union_to_extends.h"
#include "rules/divisible_by_implicit.h"
#include "rules/double_negation_elimination.h"
#include "rules/draft3_type_any.h"
#include "rules/draft_official_dialect_with_https.h"
#include "rules/draft_official_dialect_without_empty_fragment.h"
#include "rules/draft_ref_siblings.h"
#include "rules/drop_allof_empty_schemas.h"
#include "rules/drop_extends_empty_schemas.h"
#include "rules/duplicate_allof_branches.h"
#include "rules/duplicate_anyof_branches.h"
#include "rules/duplicate_disallow_entries.h"
#include "rules/duplicate_enum_values.h"
#include "rules/duplicate_required_values.h"
#include "rules/dynamic_ref_to_static_ref.h"
#include "rules/else_without_if.h"
#include "rules/empty_definitions_drop.h"
#include "rules/empty_defs_drop.h"
#include "rules/empty_dependencies_drop.h"
#include "rules/empty_dependent_required_drop.h"
#include "rules/empty_dependent_schemas_drop.h"
#include "rules/empty_disallow_drop.h"
#include "rules/empty_object_as_true.h"
#include "rules/enum_drop_redundant_validation.h"
#include "rules/enum_filter_by_type.h"
#include "rules/enum_split_by_type.h"
#include "rules/enum_with_type.h"
#include "rules/equal_numeric_bounds_to_const.h"
#include "rules/equal_numeric_bounds_to_enum.h"
#include "rules/exclusive_bounds_false_drop.h"
#include "rules/exclusive_maximum_boolean_integer_fold.h"
#include "rules/exclusive_maximum_integer_to_maximum.h"
#include "rules/exclusive_maximum_number_and_maximum.h"
#include "rules/exclusive_minimum_boolean_integer_fold.h"
#include "rules/exclusive_minimum_integer_to_minimum.h"
#include "rules/exclusive_minimum_number_and_minimum.h"
#include "rules/extends_to_array.h"
#include "rules/flatten_nested_allof.h"
#include "rules/flatten_nested_anyof.h"
#include "rules/flatten_nested_extends.h"
#include "rules/if_then_else_implicit.h"
#include "rules/if_without_then_else.h"
#include "rules/ignored_metaschema.h"
#include "rules/implicit_contains_keywords.h"
#include "rules/implicit_object_keywords.h"
#include "rules/inline_single_use_ref.h"
#include "rules/items_implicit.h"
#include "rules/max_contains_covered_by_max_items.h"
#include "rules/max_contains_without_contains.h"
#include "rules/max_decimal_implicit.h"
#include "rules/maximum_can_equal_integer_fold.h"
#include "rules/maximum_can_equal_true_drop.h"
#include "rules/maximum_real_for_integer.h"
#include "rules/min_contains_without_contains.h"
#include "rules/min_items_given_min_contains.h"
#include "rules/min_length_implicit.h"
#include "rules/min_properties_covered_by_required.h"
#include "rules/minimum_can_equal_integer_fold.h"
#include "rules/minimum_can_equal_true_drop.h"
#include "rules/minimum_real_for_integer.h"
#include "rules/modern_official_dialect_with_empty_fragment.h"
#include "rules/modern_official_dialect_with_http.h"
#include "rules/multiple_of_implicit.h"
#include "rules/non_applicable_additional_items.h"
#include "rules/non_applicable_disallow_types.h"
#include "rules/non_applicable_enum_validation_keywords.h"
#include "rules/non_applicable_type_specific_keywords.h"
#include "rules/not_false.h"
#include "rules/oneof_false_simplify.h"
#include "rules/oneof_to_anyof_disjoint_types.h"
#include "rules/optional_property_implicit.h"
#include "rules/orphan_definitions.h"
#include "rules/recursive_anchor_false_drop.h"
#include "rules/required_properties_in_properties.h"
#include "rules/required_property_implicit.h"
#include "rules/required_to_extends.h"
#include "rules/single_branch_allof.h"
#include "rules/single_branch_anyof.h"
#include "rules/single_branch_oneof.h"
#include "rules/single_type_array.h"
#include "rules/then_without_if.h"
#include "rules/type_array_to_any_of.h"
#include "rules/type_boolean_as_enum.h"
#include "rules/type_inherit_in_place.h"
#include "rules/type_null_as_enum.h"
#include "rules/type_union_distribute_keywords.h"
#include "rules/type_union_implicit.h"
#include "rules/type_union_to_schemas.h"
#include "rules/type_with_applicator_to_allof.h"
#include "rules/type_with_applicator_to_extends.h"
#include "rules/unevaluated_items_to_items.h"
#include "rules/unevaluated_properties_to_additional_properties.h"
#include "rules/unknown_keywords_prefix.h"
#include "rules/unknown_local_ref.h"
#include "rules/unnecessary_allof_ref_wrapper_draft.h"
#include "rules/unnecessary_extends_ref_wrapper.h"
#include "rules/unsatisfiable_drop_validation.h"
#include "rules/unsatisfiable_exclusive_equal_bounds.h"
#include "rules/unsatisfiable_in_place_applicator_type.h"
#include "rules/unsatisfiable_type_and_enum.h"

#undef ONLY_CONTINUE_IF

namespace {

auto add_canonicalizer_rules(
    sourcemeta::blaze::canonicalizer::SchemaTransformer &bundle) -> void {
  bundle.add<ExclusiveMinimumBooleanIntegerFold>();
  bundle.add<ExclusiveMaximumBooleanIntegerFold>();
  bundle.add<UnsatisfiableExclusiveEqualBounds>();
  bundle.add<MinimumCanEqualIntegerFold>();
  bundle.add<MaximumCanEqualIntegerFold>();
  bundle.add<MinimumCanEqualTrueDrop>();
  bundle.add<MaximumCanEqualTrueDrop>();
  bundle.add<CommentDrop>();
  bundle.add<DeprecatedFalseDrop>();
  bundle.add<RecursiveAnchorFalseDrop>();
  bundle.add<UnevaluatedItemsToItems>();
  bundle.add<UnevaluatedPropertiesToAdditionalProperties>();
  bundle.add<IfThenElseImplicit>();
  bundle.add<ImplicitObjectKeywords>();
  bundle.add<ImplicitContainsKeywords>();
  bundle.add<ExtendsToArray>();
  bundle.add<DisallowToArrayOfSchemas>();
  bundle.add<InlineSingleUseRef>();
  bundle.add<AllOfMergeCompatibleBranches>();
  bundle.add<TypeInheritInPlace>();
  bundle.add<TypeUnionImplicit>();
  bundle.add<TypeArrayToAnyOf>();
  bundle.add<DefinitionsToDefs>();
  bundle.add<ContentMediaTypeWithoutEncoding>();
  bundle.add<ContentSchemaWithoutMediaType>();
  bundle.add<DraftOfficialDialectWithHttps>();
  bundle.add<DraftOfficialDialectWithoutEmptyFragment>();
  bundle.add<NonApplicableTypeSpecificKeywords>();
  bundle.add<NonApplicableDisallowTypes>();
  bundle.add<DisallowNarrowsType>();
  bundle.add<AnyOfRemoveFalseSchemas>();
  bundle.add<AnyOfTrueSimplify>();
  bundle.add<DuplicateAllOfBranches>();
  bundle.add<DuplicateAnyOfBranches>();
  bundle.add<FlattenNestedAllOf>();
  bundle.add<FlattenNestedExtends>();
  bundle.add<FlattenNestedAnyOf>();
  bundle.add<Draft3TypeAny>();
  bundle.add<UnsatisfiableInPlaceApplicatorType>();
  bundle.add<AllOfFalseSimplify>();
  bundle.add<AnyOfFalseSimplify>();
  bundle.add<OneOfFalseSimplify>();
  bundle.add<DoubleNegationElimination>();
  bundle.add<OneOfToAnyOfDisjointTypes>();
  bundle.add<UnsatisfiableDropValidation>();
  bundle.add<ElseWithoutIf>();
  bundle.add<IfWithoutThenElse>();
  bundle.add<IgnoredMetaschema>();
  bundle.add<MaxContainsWithoutContains>();
  bundle.add<MinContainsWithoutContains>();
  bundle.add<NotFalse>();
  bundle.add<ThenWithoutIf>();
  bundle.add<DependenciesPropertyTautology>();
  bundle.add<DependentRequiredTautology>();
  bundle.add<EqualNumericBoundsToEnum>();
  bundle.add<MaximumRealForInteger>();
  bundle.add<MinimumRealForInteger>();
  bundle.add<SingleTypeArray>();
  bundle.add<EnumWithType>();
  bundle.add<NonApplicableEnumValidationKeywords>();
  bundle.add<DuplicateEnumValues>();
  bundle.add<DuplicateRequiredValues>();
  bundle.add<ConstWithType>();
  bundle.add<ConstInEnum>();
  bundle.add<NonApplicableAdditionalItems>();
  bundle.add<ModernOfficialDialectWithEmptyFragment>();
  bundle.add<ModernOfficialDialectWithHttp>();
  bundle.add<ExclusiveMaximumNumberAndMaximum>();
  bundle.add<ExclusiveMinimumNumberAndMinimum>();
  bundle.add<ExclusiveBoundsFalseDrop>();
  bundle.add<DraftRefSiblings>();
  bundle.add<DynamicRefToStaticRef>();
  bundle.add<UnknownKeywordsPrefix>();
  bundle.add<UnknownLocalRef>();
  bundle.add<RequiredPropertiesInProperties>();
  bundle.add<OrphanDefinitions>();
  bundle.add<ConstAsEnum>();
  bundle.add<EqualNumericBoundsToConst>();
  bundle.add<ExclusiveMaximumIntegerToMaximum>();
  bundle.add<ExclusiveMinimumIntegerToMinimum>();
  bundle.add<TypeBooleanAsEnum>();
  bundle.add<TypeNullAsEnum>();
  bundle.add<MaxContainsCoveredByMaxItems>();
  bundle.add<MinItemsGivenMinContains>();
  bundle.add<MinPropertiesCoveredByRequired>();
  bundle.add<MinLengthImplicit>();
  bundle.add<MultipleOfImplicit>();
  bundle.add<DivisibleByImplicit>();
  bundle.add<MaxDecimalImplicit>();
  bundle.add<ItemsImplicit>();
  bundle.add<UnnecessaryAllOfRefWrapperDraft>();
  bundle.add<UnnecessaryExtendsRefWrapper>();
  bundle.add<DropAllOfEmptySchemas>();
  bundle.add<DropExtendsEmptySchemas>();
  bundle.add<EmptyObjectAsTrue>();
  bundle.add<UnsatisfiableTypeAndEnum>();
  bundle.add<EnumFilterByType>();
  bundle.add<TypeUnionToSchemas>();
  bundle.add<TypeUnionDistributeKeywords>();
  bundle.add<DependenciesToAnyOf>();
  bundle.add<DependenciesToExtendsDisallow>();
  bundle.add<DependentSchemasToAnyOf>();
  bundle.add<DependentRequiredToAnyOf>();
  bundle.add<EnumDropRedundantValidation>();
  bundle.add<EnumSplitByType>();
  bundle.add<TypeWithApplicatorToAllOf>();
  bundle.add<TypeWithApplicatorToExtends>();
  bundle.add<EmptyDefinitionsDrop>();
  bundle.add<EmptyDefsDrop>();
  bundle.add<EmptyDependenciesDrop>();
  bundle.add<EmptyDependentSchemasDrop>();
  bundle.add<EmptyDependentRequiredDrop>();
  bundle.add<EmptyDisallowDrop>();
  bundle.add<AdditionalItemsImplicit>();
  bundle.add<RequiredPropertyImplicit>();
  bundle.add<OptionalPropertyImplicit>();
  bundle.add<DuplicateDisallowEntries>();
  bundle.add<DisallowArrayToExtends>();
  bundle.add<DisallowExtendsToType>();
  bundle.add<DisallowTypeUnionToExtends>();
  bundle.add<DisallowDoubleNegation>();
  bundle.add<RequiredToExtends>();
  bundle.add<SingleBranchAllOf>();
  bundle.add<SingleBranchAnyOf>();
  bundle.add<SingleBranchOneOf>();
}

} // namespace

} // namespace sourcemeta::blaze::canonicalizer

namespace sourcemeta::blaze {

auto canonicalize(sourcemeta::core::JSON &schema,
                  const sourcemeta::blaze::SchemaWalker &walker,
                  const sourcemeta::blaze::SchemaResolver &resolver,
                  const std::string_view default_dialect,
                  const std::string_view default_id) -> void {
  sourcemeta::blaze::canonicalizer::SchemaTransformer bundle;
  sourcemeta::blaze::canonicalizer::add_canonicalizer_rules(bundle);
  bundle.apply(
      schema, walker, resolver,
      [](const auto &, const auto &, const auto &, const auto &,
         const auto &) -> void {},
      default_dialect, default_id);
}

} // namespace sourcemeta::blaze
