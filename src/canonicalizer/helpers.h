#ifndef SOURCEMETA_BLAZE_CANONICALIZER_HELPERS_H_
#define SOURCEMETA_BLAZE_CANONICALIZER_HELPERS_H_

// TODO: Move upstream
inline auto is_in_place_applicator(const SchemaKeywordType type) -> bool {
  return type == SchemaKeywordType::ApplicatorValueOrElementsInPlace ||
         type == SchemaKeywordType::ApplicatorMembersInPlaceSome ||
         type == SchemaKeywordType::ApplicatorElementsInPlace ||
         type == SchemaKeywordType::ApplicatorElementsInPlaceSome ||
         type == SchemaKeywordType::ApplicatorElementsInPlaceSomeNegate ||
         type == SchemaKeywordType::ApplicatorValueInPlaceMaybe ||
         type == SchemaKeywordType::ApplicatorValueInPlaceOther ||
         type == SchemaKeywordType::ApplicatorValueInPlaceNegate;
}

// TODO: Move upstream, so that the compiler can share this predicate rather
// than repeating the same check
// Draft 3 and Draft 4 read "integer" as a number written without a fractional
// part, so `3.0` is not one there, and `type: "integer"` says something that
// an `enum` of integral values cannot. Draft 6 onwards widened it to any
// number whose fractional part is zero, and the dialects before Draft 3 read
// it that way too. Kept in step with `integral_reals_are_integers` in the
// compiler, which decides the same question when evaluating
inline auto integral_reals_are_integers(const SchemaVocabularies &vocabularies)
    -> bool {
  return !vocabularies.contains_any(
      {SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_3,
       SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_3_HYPER,
       SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_4,
       SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_4_HYPER});
}

// Whether a `type` value only consists of simple type names that can be
// parsed into a complete set of instance types. Draft 0 to Draft 3 unions
// may contain subschemas or `any`, in which case the parsed set is an
// under-approximation that cannot be trusted. Later dialects do not give
// such forms any meaning, so the parsed set stands
inline auto is_known_type_form(const sourcemeta::core::JSON &type,
                               const SchemaVocabularies &vocabularies) -> bool {
  if (!vocabularies.contains_any(
          {SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_0,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_0_HYPER,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_1,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_1_HYPER,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_2,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_2_HYPER,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_3,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_3_HYPER})) {
    return true;
  }
  if (type.is_string()) {
    return type.to_string() != "any";
  }
  if (!type.is_array()) {
    return false;
  }
  return std::ranges::all_of(type.as_array(), [](const auto &entry) -> auto {
    return entry.is_string() && entry.to_string() != "any";
  });
}

// The schema that no instance can ever satisfy. Draft 3 and Draft 4 have no
// boolean schemas, so each of them has to spell it out with the negation
// keyword it offers, applied to the schema that every instance satisfies
inline auto unsatisfiable_schema(const SchemaVocabularies &vocabularies)
    -> sourcemeta::core::JSON {
  if (vocabularies.contains_any(
          {SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_4,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_4_HYPER})) {
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("not", sourcemeta::core::JSON::make_object());
    return result;
  }

  if (vocabularies.contains_any(
          {SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_3,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_3_HYPER})) {
    auto branches{sourcemeta::core::JSON::make_array()};
    branches.push_back(sourcemeta::core::JSON::make_object());
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("disallow", std::move(branches));
    return result;
  }

  // Draft 2 and earlier have no boolean schemas either, and their negation
  // keyword takes type names rather than schemas, so the name to rule out is
  // the wildcard that every instance answers to
  if (vocabularies.contains_any(
          {SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_0,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_0_HYPER,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_1,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_1_HYPER,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_2,
           SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_2_HYPER})) {
    auto types{sourcemeta::core::JSON::make_array()};
    types.push_back(sourcemeta::core::JSON{"any"});
    auto result{sourcemeta::core::JSON::make_object()};
    result.assign("disallow", std::move(types));
    return result;
  }

  return sourcemeta::core::JSON{false};
}

// Collapsing a schema to the unsatisfiable one throws away every keyword it
// had, `$schema` included. A boolean cannot carry the dialect back, so the
// caller is left to reset the frame, but an object both can and must. Rewrite
// it in place rather than replacing it outright, so that the dialect the frame
// still points to stays where it is
inline auto into_unsatisfiable(sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &unsatisfiable)
    -> void {
  if (!unsatisfiable.is_object() || !schema.is_object()) {
    schema.into(sourcemeta::core::JSON{unsatisfiable});
    return;
  }

  std::vector<sourcemeta::core::JSON::String> superseded;
  for (const auto &entry : schema.as_object()) {
    if (entry.first != "$schema") {
      superseded.push_back(entry.first);
    }
  }

  for (const auto &keyword : superseded) {
    schema.erase(keyword);
  }

  for (const auto &entry : unsatisfiable.as_object()) {
    schema.assign(entry.first, entry.second);
  }
}

// Walk up from a schema location, continuing as long as the traversal
// predicate returns true for each keyword type encountered. Returns a
// reference to the pointer of the ancestor where the match callback returned
// true, or nullopt if no match was found or the traversal predicate stopped
// the walk.
template <typename TraversePredicate, typename MatchCallback>
auto walk_up(const sourcemeta::core::JSON &root, const SchemaFrame &frame,
             const SchemaFrame::Location &location, const SchemaWalker &walker,
             const SchemaResolver &resolver,
             const TraversePredicate &should_continue,
             const MatchCallback &matches)
    -> std::optional<
        std::reference_wrapper<const sourcemeta::core::WeakPointer>> {
  auto current_pointer{location.pointer};
  auto current_parent{location.parent};

  while (current_parent.has_value()) {
    const auto &parent_pointer{current_parent.value()};
    const auto relative_pointer{current_pointer.resolve_from(parent_pointer)};
    assert(!relative_pointer.empty() && relative_pointer.at(0).is_property());
    const auto parent{frame.traverse(parent_pointer)};
    assert(parent.has_value());
    const auto &parent_vocabularies{
        frame.vocabularies(parent.value().get(), resolver)};
    const auto keyword_type{
        walker(relative_pointer.at(0).to_property(), parent_vocabularies).type};

    if (!should_continue(keyword_type)) {
      return std::nullopt;
    }

    if (matches(sourcemeta::core::get(root, parent_pointer),
                parent_vocabularies)) {
      return std::cref(parent.value().get().pointer);
    }

    current_pointer = parent_pointer;
    current_parent = parent.value().get().parent;
  }

  return std::nullopt;
}

template <typename MatchCallback>
auto walk_up_in_place_applicators(const sourcemeta::core::JSON &root,
                                  const SchemaFrame &frame,
                                  const SchemaFrame::Location &location,
                                  const SchemaWalker &walker,
                                  const SchemaResolver &resolver,
                                  const MatchCallback &matches)
    -> std::optional<
        std::reference_wrapper<const sourcemeta::core::WeakPointer>> {
  return walk_up(root, frame, location, walker, resolver,
                 is_in_place_applicator, matches);
}

// Walk up the in-place applicator chain of a location once, reporting whether
// any ancestor matches and collecting every scope the walk passes through on
// the way. A reference landing on any of those scopes is one that reaches this
// location without moving through the instance, which is what makes them worth
// collecting. The two answers come from the same walk because the chain and
// the predicate that bounds it are the same either way
template <typename MatchCallback>
auto walk_up_in_place_applicators_collecting_scopes(
    const sourcemeta::core::JSON &root, const SchemaFrame &frame,
    const SchemaFrame::Location &location, const SchemaWalker &walker,
    const SchemaResolver &resolver, const MatchCallback &matches,
    std::set<sourcemeta::core::WeakPointer> &scopes) -> bool {
  scopes.insert(location.pointer);
  auto current_pointer{location.pointer};
  auto current_parent{location.parent};

  while (current_parent.has_value()) {
    const auto &parent_pointer{current_parent.value()};
    const auto relative_pointer{current_pointer.resolve_from(parent_pointer)};
    assert(!relative_pointer.empty() && relative_pointer.at(0).is_property());
    const auto parent{frame.traverse(parent_pointer)};
    assert(parent.has_value());
    const auto &parent_vocabularies{
        frame.vocabularies(parent.value().get(), resolver)};
    if (!is_in_place_applicator(
            walker(relative_pointer.at(0).to_property(), parent_vocabularies)
                .type)) {
      return false;
    }

    if (matches(sourcemeta::core::get(root, parent_pointer),
                parent_vocabularies)) {
      return true;
    }

    scopes.insert(parent_pointer);
    current_pointer = parent_pointer;
    current_parent = parent.value().get().parent;
  }

  return false;
}

// The lexical walk stops at a subschema nothing encloses, which is what a
// definition under `$defs` looks like. Whichever scope references that
// definition still sees the annotations it produces, so a keyword that reads
// them, such as `unevaluatedItems`, can sit on the far side of the reference.
// This repeats the walk from every scope that reaches this location through a
// reference, so such a keyword is found wherever it hides
template <typename MatchCallback>
auto walk_up_in_place_applicators_across_references(
    const sourcemeta::core::JSON &root, const SchemaFrame &frame,
    const SchemaFrame::Location &location, const SchemaWalker &walker,
    const SchemaResolver &resolver, const MatchCallback &matches) -> bool {
  std::vector<std::reference_wrapper<const SchemaFrame::Location>> pending{
      std::cref(location)};
  std::set<sourcemeta::core::WeakPointer> visited{location.pointer};

  while (!pending.empty()) {
    const auto &current{pending.back().get()};
    pending.pop_back();

    // The caller already checked the location it asked about, but a scope we
    // arrived at through a reference still has to be checked on its own
    if (current.pointer != location.pointer &&
        matches(sourcemeta::core::get(root, current.pointer),
                frame.vocabularies(current, resolver))) {
      return true;
    }

    std::set<sourcemeta::core::WeakPointer> scopes;
    if (walk_up_in_place_applicators_collecting_scopes(
            root, frame, current, walker, resolver, matches, scopes)) {
      return true;
    }

    frame.for_each_reference(
        [&](const SchemaReferenceType,
            const sourcemeta::core::WeakPointer &origin,
            const SchemaFrame::Reference &reference) -> void {
          const auto destination{frame.traverse(reference.destination)};
          if (!destination.has_value() ||
              !scopes.contains(destination.value().get().pointer)) {
            return;
          }

          const auto source{frame.traverse(origin.initial())};
          if (!source.has_value() ||
              !visited.insert(source.value().get().pointer).second) {
            return;
          }

          pending.emplace_back(std::cref(source.value().get()));
        });
  }

  return false;
}

#define ONLY_CONTINUE_IF(condition)                                            \
  if (!(condition)) {                                                          \
    return false;                                                              \
  }

#endif
