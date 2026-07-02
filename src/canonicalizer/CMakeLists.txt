sourcemeta_library(NAMESPACE sourcemeta PROJECT blaze NAME canonicalizer
  FOLDER "Blaze/Canonicalizer"
  SOURCES canonicalize.cc transformer.cc
    canonicalizer_transformer.h
    canonicalizer_error.h

    # Canonicalizer
    canonicalizer/additional_items_implicit.h
    canonicalizer/allof_merge_compatible_branches.h
    canonicalizer/comment_drop.h
    canonicalizer/const_as_enum.h
    canonicalizer/dependencies_to_any_of.h
    canonicalizer/dependencies_to_extends_disallow.h
    canonicalizer/dependent_required_to_any_of.h
    canonicalizer/dependent_schemas_to_any_of.h
    canonicalizer/deprecated_false_drop.h
    canonicalizer/disallow_array_to_extends.h
    canonicalizer/disallow_double_negation.h
    canonicalizer/disallow_extends_to_type.h
    canonicalizer/disallow_to_array_of_schemas.h
    canonicalizer/disallow_type_union_to_extends.h
    canonicalizer/divisible_by_implicit.h
    canonicalizer/draft3_type_any.h
    canonicalizer/duplicate_disallow_entries.h
    canonicalizer/empty_definitions_drop.h
    canonicalizer/empty_defs_drop.h
    canonicalizer/empty_dependencies_drop.h
    canonicalizer/empty_dependent_required_drop.h
    canonicalizer/empty_dependent_schemas_drop.h
    canonicalizer/empty_disallow_drop.h
    canonicalizer/enum_drop_redundant_validation.h
    canonicalizer/enum_filter_by_type.h
    canonicalizer/enum_split_by_type.h
    canonicalizer/exclusive_maximum_boolean_integer_fold.h
    canonicalizer/exclusive_maximum_integer_to_maximum.h
    canonicalizer/exclusive_minimum_boolean_integer_fold.h
    canonicalizer/exclusive_minimum_integer_to_minimum.h
    canonicalizer/extends_to_array.h
    canonicalizer/if_then_else_implicit.h
    canonicalizer/implicit_contains_keywords.h
    canonicalizer/implicit_object_keywords.h
    canonicalizer/inline_single_use_ref.h
    canonicalizer/items_implicit.h
    canonicalizer/max_contains_covered_by_max_items.h
    canonicalizer/max_decimal_implicit.h
    canonicalizer/maximum_can_equal_integer_fold.h
    canonicalizer/maximum_can_equal_true_drop.h
    canonicalizer/min_items_given_min_contains.h
    canonicalizer/min_length_implicit.h
    canonicalizer/min_properties_covered_by_required.h
    canonicalizer/minimum_can_equal_integer_fold.h
    canonicalizer/minimum_can_equal_true_drop.h
    canonicalizer/multiple_of_implicit.h
    canonicalizer/optional_property_implicit.h
    canonicalizer/recursive_anchor_false_drop.h
    canonicalizer/required_property_implicit.h
    canonicalizer/required_to_extends.h
    canonicalizer/single_branch_allof.h
    canonicalizer/single_branch_anyof.h
    canonicalizer/single_branch_oneof.h
    canonicalizer/type_array_to_any_of.h
    canonicalizer/type_boolean_as_enum.h
    canonicalizer/type_inherit_in_place.h
    canonicalizer/type_null_as_enum.h
    canonicalizer/type_union_distribute_keywords.h
    canonicalizer/type_union_implicit.h
    canonicalizer/type_union_to_schemas.h
    canonicalizer/type_with_applicator_to_allof.h
    canonicalizer/type_with_applicator_to_extends.h
    canonicalizer/unevaluated_items_to_items.h
    canonicalizer/unevaluated_properties_to_additional_properties.h
    canonicalizer/unsatisfiable_can_equal_bounds.h
    canonicalizer/unsatisfiable_exclusive_equal_bounds.h
    canonicalizer/unsatisfiable_type_and_enum.h

    # Common
    common/allof_false_simplify.h
    common/anyof_false_simplify.h
    common/anyof_remove_false_schemas.h
    common/anyof_true_simplify.h
    common/const_in_enum.h
    common/const_with_type.h
    common/content_media_type_without_encoding.h
    common/content_schema_without_media_type.h
    common/dependencies_property_tautology.h
    common/dependent_required_tautology.h
    common/disallow_narrows_type.h
    common/double_negation_elimination.h
    common/draft_official_dialect_with_https.h
    common/draft_official_dialect_without_empty_fragment.h
    common/draft_ref_siblings.h
    common/drop_allof_empty_schemas.h
    common/drop_extends_empty_schemas.h
    common/duplicate_allof_branches.h
    common/duplicate_anyof_branches.h
    common/duplicate_enum_values.h
    common/duplicate_required_values.h
    common/dynamic_ref_to_static_ref.h
    common/else_without_if.h
    common/empty_object_as_true.h
    common/enum_with_type.h
    common/equal_numeric_bounds_to_enum.h
    common/exclusive_bounds_false_drop.h
    common/exclusive_maximum_number_and_maximum.h
    common/exclusive_minimum_number_and_minimum.h
    common/flatten_nested_allof.h
    common/flatten_nested_anyof.h
    common/flatten_nested_extends.h
    common/if_without_then_else.h
    common/ignored_metaschema.h
    common/max_contains_without_contains.h
    common/maximum_real_for_integer.h
    common/min_contains_without_contains.h
    common/minimum_real_for_integer.h
    common/modern_official_dialect_with_empty_fragment.h
    common/modern_official_dialect_with_http.h
    common/non_applicable_additional_items.h
    common/non_applicable_disallow_types.h
    common/non_applicable_enum_validation_keywords.h
    common/non_applicable_type_specific_keywords.h
    common/not_false.h
    common/oneof_false_simplify.h
    common/oneof_to_anyof_disjoint_types.h
    common/orphan_definitions.h
    common/required_properties_in_properties.h
    common/single_type_array.h
    common/then_without_if.h
    common/unknown_keywords_prefix.h
    common/unknown_local_ref.h
    common/unnecessary_allof_ref_wrapper_draft.h
    common/unnecessary_extends_ref_wrapper.h
    common/unsatisfiable_drop_validation.h
    common/unsatisfiable_in_place_applicator_type.h

    # Linter
    linter/definitions_to_defs.h
    linter/equal_numeric_bounds_to_const.h
  )

if(BLAZE_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT blaze NAME canonicalizer)
endif()

target_link_libraries(sourcemeta_blaze_canonicalizer PUBLIC
  sourcemeta::blaze::foundation)
target_link_libraries(sourcemeta_blaze_canonicalizer PUBLIC
  sourcemeta::blaze::frame)
target_link_libraries(sourcemeta_blaze_canonicalizer PUBLIC
  sourcemeta::blaze::compiler)
target_link_libraries(sourcemeta_blaze_canonicalizer PRIVATE
  sourcemeta::blaze::evaluator)
target_link_libraries(sourcemeta_blaze_canonicalizer PRIVATE
  sourcemeta::blaze::output)
target_link_libraries(sourcemeta_blaze_canonicalizer PRIVATE
  sourcemeta::core::regex)
target_link_libraries(sourcemeta_blaze_canonicalizer PRIVATE
  sourcemeta::core::uri)
