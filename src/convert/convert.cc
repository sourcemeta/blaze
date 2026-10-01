#include <sourcemeta/blaze/convert.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/uri.h>

#include <algorithm> // std::ranges::any_of, std::ranges::find
#include <array>     // std::array
#include <cassert>   // assert
#include <concepts>  // std::derived_from
#include <cstddef>   // std::size_t
#include <cstdint>   // std::uint64_t
#include <functional> // std::cref, std::function, std::hash, std::reference_wrapper
#include <map>        // std::map
#include <memory>     // std::make_unique, std::unique_ptr
#include <optional>      // std::optional, std::nullopt
#include <set>           // std::set
#include <string>        // std::string
#include <string_view>   // std::string_view
#include <tuple>         // std::tuple
#include <type_traits>   // std::is_same_v, std::true_type, std::false_type
#include <unordered_map> // std::unordered_map
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move, std::pair
#include <vector>        // std::vector

namespace sourcemeta::blaze {

using namespace sourcemeta::core;

namespace {

#include "helpers.h"
#include "rule.h"

using Rule = std::tuple<std::unique_ptr<SchemaTransformRule>, bool>;

/// Construct a rule entry for the given rule type
template <std::derived_from<SchemaTransformRule> T>
[[nodiscard]] auto make_rule() -> Rule {
  return {std::make_unique<T>(),
          std::is_same_v<typename T::reframe_after_transform, std::true_type>};
}

/// A reference that lands on something other than a schema is not a reference
/// the conversion can carry across dialects, as the document never had one
auto assert_schema_references(const core::SchemaFrame &frame) -> void {
  frame.for_each_reference(
      [&frame](const core::SchemaReferenceType, const core::WeakPointer &origin,
               const core::SchemaFrame::Reference &reference) -> void {
        const auto destination{frame.traverse(reference.destination)};
        if (destination.has_value() &&
            destination.value().get().type ==
                core::SchemaFrame::LocationType::Pointer) {
          throw ConvertInvalidReferenceError{reference.destination,
                                             core::to_pointer(origin)};
        }
      });
}

/// Conversion renames keywords, while a meta-schema names those same keywords
/// as ordinary data that nothing renames alongside them. Until the two can be
/// told apart, a document that describes itself or that carries the
/// meta-schema something in it declares is refused. A dialect the ladder does
/// not name is refused too, as there are no rules for moving a schema off it
/// Where the requested target sits on the ladder, so that it can be compared
/// against how far a resource has already come
auto target_position(const ConvertTarget target) -> std::size_t {
  switch (target) {
    case ConvertTarget::Draft4:
      return 2;
    case ConvertTarget::Draft6:
      return 3;
    case ConvertTarget::Draft7:
      return 4;
    case ConvertTarget::Draft201909:
      return 5;
    case ConvertTarget::Draft202012:
      return 6;
  }

  return 0;
}

auto assert_convertible_dialects(const core::JSON &schema,
                                 const core::SchemaFrame &frame,
                                 const std::string_view default_id,
                                 const ConvertTarget target) -> void {
  const auto document{frame.traverse(core::EMPTY_WEAK_POINTER)};
  if (document.has_value() &&
      describes_itself(schema, document.value().get().base_dialect,
                       default_id)) {
    throw ConvertUnsupportedMetaschemaError{schema.at("$schema").to_string(),
                                            core::EMPTY_POINTER};
  }

  frame.for_each_subschema(
      [&schema, &frame,
       target](const core::SchemaFrame::Location &location) -> void {
        auto pointer{core::to_pointer(location.pointer)};
        const auto &subschema{core::get(schema, pointer)};
        if (is_metaschema_target(subschema, frame, location.pointer)) {
          // The meta-schema that cannot be moved is what the error names. The
          // dialect that meta-schema is itself written in is an official one
          // the conversion supports perfectly well, so naming that instead
          // would report the evidence rather than the reason
          const auto *identifier{subschema.try_at(
              core::schema_identifier_keyword(location.base_dialect))};
          throw ConvertUnsupportedMetaschemaError{
              identifier != nullptr && identifier->is_string()
                  ? std::string_view{identifier->to_string()}
                  : location.dialect,
              std::move(pointer)};
        }

        // A dialect the ladder does not name has no rules for moving a schema
        // off it, but nothing asks it to move when the target is no newer than
        // the official dialect it derives from: every rule that could reach
        // inside is gated on a vocabulary it does not have. Refusing then would
        // turn a conversion that changes nothing into an error
        if (!names_ladder_dialect(location.dialect) &&
            target_position(target) >
                base_dialect_position(location.base_dialect)) {
          throw ConvertUnsupportedDialectError{location.dialect,
                                               std::move(pointer)};
        }
      });
}

/// Whether every step from the meta-schema down to this reference keeps the
/// instance location, which is what makes the reference pull the other
/// document's keywords in. A reference reached through a keyword that moves to
/// a child location, or through a container that merely holds schemas for
/// others to name, describes another schema rather than extending this one
auto reference_applies_in_place(const core::WeakPointer &base,
                                const core::WeakPointer &origin,
                                const core::SchemaWalker &walker,
                                const core::SchemaVocabularies &vocabularies)
    -> bool {
  if (origin.size() <= base.size() || !origin.starts_with(base)) {
    return false;
  }

  for (auto index = base.size(); index + 1 < origin.size(); index += 1) {
    const auto &token{origin.at(index)};
    if (!token.is_property()) {
      continue;
    }

    switch (walker(token.to_property(), vocabularies).type) {
      case core::SchemaKeywordType::ApplicatorValueOrElementsInPlace:
      case core::SchemaKeywordType::ApplicatorMembersInPlaceSome:
      case core::SchemaKeywordType::ApplicatorElementsInPlace:
      case core::SchemaKeywordType::ApplicatorElementsInPlaceSome:
      case core::SchemaKeywordType::ApplicatorElementsInPlaceSomeNegate:
      case core::SchemaKeywordType::ApplicatorValueInPlaceMaybe:
      case core::SchemaKeywordType::ApplicatorValueInPlaceOther:
      case core::SchemaKeywordType::ApplicatorValueInPlaceNegate:
      case core::SchemaKeywordType::Reference:
        break;
      default:
        return false;
    }
  }

  return true;
}

/// A schema that declares `$vocabulary` is a meta-schema, which is what this
/// conversion asks of one. Extending an official meta-schema means referencing
/// a document that recurses with the keyword of the dialect it was written for,
/// and nothing this conversion renames in the extending schema can carry that
/// recursion to another dialect, so such a meta-schema is refused rather than
/// quietly stripped of the constraints it places on what it describes
auto assert_convertible_metaschema(const core::JSON &schema,
                                   const core::SchemaFrame &frame,
                                   const core::SchemaWalker &walker,
                                   const core::SchemaResolver &resolver)
    -> void {
  if (!schema.is_object()) {
    return;
  }

  // The meta-schema is what cannot be converted, so it is what the error names,
  // and it may sit inside the document rather than be the whole of it
  frame.for_each_subschema(
      [&schema, &frame, &walker,
       &resolver](const core::SchemaFrame::Location &location) -> void {
        auto pointer{core::to_pointer(location.pointer)};
        const auto &subschema{core::get(schema, pointer)};
        if (!subschema.is_object() || !subschema.defines("$vocabulary")) {
          return;
        }

        const auto &vocabularies{frame.vocabularies(location, resolver)};
        const auto extends_official{frame.any_reference(
            [&location, &walker, &vocabularies](
                const core::SchemaReferenceType,
                const core::WeakPointer &origin,
                const core::SchemaFrame::Reference &reference) -> bool {
              if (!origin.empty() && origin.back().is_property() &&
                  origin.back().to_property() == "$schema") {
                return false;
              }

              return names_official_metaschema(reference.destination) &&
                     reference_applies_in_place(location.pointer, origin,
                                                walker, vocabularies);
            })};
        if (extends_official) {
          throw ConvertUnsupportedMetaschemaError{location.dialect,
                                                  std::move(pointer)};
        }
      });
}

/// Apply the given rules top-down to every subschema until none of them applies
auto apply(const std::vector<Rule> &rules, sourcemeta::core::JSON &schema,
           const sourcemeta::core::SchemaWalker &walker,
           const sourcemeta::core::SchemaResolver &resolver,
           const std::string_view default_dialect,
           const std::string_view default_id, const ConvertTarget target)
    -> void {
  assert(!rules.empty());

  struct ProcessedRuleHasher {
    auto operator()(const std::tuple<core::Pointer, std::string_view,
                                     core::JSON> &value) const noexcept
        -> std::size_t {
      return core::Pointer::Hasher{}(std::get<0>(value)) ^
             (std::hash<std::string_view>{}(std::get<1>(value)) << 1) ^
             (std::hash<std::uint64_t>{}(std::get<2>(value).fast_hash()) << 2);
    }
  };

  std::unordered_set<std::tuple<core::Pointer, std::string_view, core::JSON>,
                     ProcessedRuleHasher>
      processed_rules;

  std::optional<core::SchemaFrame> frame;

  struct PotentiallyBrokenReference {
    core::Pointer origin;
    core::JSON::String original;
    core::JSON::String destination;
    core::JSON::String fragment;
    core::Pointer target_pointer;
    std::size_t target_relative_pointer;
  };

  std::vector<PotentiallyBrokenReference> potentially_broken_references;
  bool asserted{false};

  while (true) {
    if (!frame.has_value()) {
      if (schema.is_boolean()) {
        break;
      }

      frame.emplace(core::SchemaFrame::Mode::References, schema, walker,
                    resolver, default_dialect, default_id,
                    sourcemeta::core::SchemaFrame::IdentifierMode::Fallback);

      if (!asserted) {
        assert_convertible_dialects(schema, frame.value(), default_id, target);
        assert_convertible_metaschema(schema, frame.value(), walker, resolver);
        assert_schema_references(frame.value());
        asserted = true;
      }
    }

    std::unordered_set<core::Pointer, core::Pointer::Hasher> visited;
    bool applied{false};

    // Stopping the traversal stands in for the restart that the
    // rules request once they mutate the schema
    [[maybe_unused]] const auto restarted{frame->any_subschema(
        [&](const core::SchemaFrame::Location &location) -> bool {
          const auto [visited_iterator, inserted] =
              visited.insert(core::to_pointer(location.pointer));
          if (!inserted) {
            return false;
          }
          const auto &entry_pointer{*visited_iterator};
          auto &current{core::get(schema, entry_pointer)};
          const auto current_vocabularies{
              frame->vocabularies(location, resolver)};

          for (const auto &[rule, reframe_after_transform] : rules) {
            const auto outcome{rule->condition(current, schema,
                                               current_vocabularies, *frame,
                                               location, walker, resolver)};

            if (!outcome) {
              continue;
            }

            // A rule that already produced this exact state here has nothing
            // left to contribute, and applying it again would be a cycle. The
            // asserts below say a correct rule never gets this far, so this is
            // what keeps a faulty one from spinning where they are compiled out
            if (processed_rules.contains(
                    std::tuple<core::Pointer, std::string_view, core::JSON>{
                        entry_pointer, rule->name(), current})) {
              continue;
            }

            potentially_broken_references.clear();
            frame->for_each_reference([&](const core::SchemaReferenceType,
                                          const core::WeakPointer &origin,
                                          const core::SchemaFrame::Reference
                                              &reference) -> void {
              const auto destination{frame->traverse(reference.destination)};
              if (!destination.has_value() || !reference.fragment.has_value() ||
                  !reference.fragment.value().starts_with('/')) {
                return;
              }

              const auto &target{destination.value().get()};
              potentially_broken_references.push_back(
                  {.origin = core::to_pointer(origin),
                   .original = core::JSON::String{reference.original},
                   .destination = reference.destination,
                   .fragment = core::JSON::String{reference.fragment.value()},
                   .target_pointer = core::to_pointer(target.pointer),
                   .target_relative_pointer = target.relative_pointer});
            });

            rule->prepare(*frame, location);
            rule->transform(current);

            applied = true;

            if (reframe_after_transform) {
              frame.emplace(
                  core::SchemaFrame::Mode::References, schema, walker, resolver,
                  default_dialect, default_id,
                  sourcemeta::core::SchemaFrame::IdentifierMode::Fallback);
            } else if (current.is_boolean()) {
              std::tuple<core::Pointer, std::string_view, core::JSON> mark{
                  entry_pointer, rule->name(), current};
              assert(!processed_rules.contains(mark));
              processed_rules.emplace(std::move(mark));
              frame.reset();
              return true;
            }

            const auto new_location{
                frame->traverse(core::to_weak_pointer(entry_pointer))};
            assert(new_location.has_value());

            // Fix broken references before re-checking the condition,
            // as the re-check may mutate rule state that rereference needs
            bool references_fixed{false};
            const auto resource_offset{
                new_location.value().get().relative_pointer};
            const auto current_slice{entry_pointer.slice(resource_offset)};
            for (const auto &saved_reference : potentially_broken_references) {
              // A reference only breaks when its destination stops resolving.
              // The target sitting at a different pointer than before is not
              // enough, as a resource that moved as a whole keeps resolving
              // the fragments that its own identifier is the base of
              if (frame->traverse(saved_reference.destination).has_value()) {
                continue;
              }

              // If the origin was also relocated, resolve its new location
              auto effective_origin{saved_reference.origin};
              if (!core::try_get(schema, saved_reference.origin.initial())) {
                const auto new_origin{rule->rereference(
                    saved_reference.destination, saved_reference.origin,
                    saved_reference.origin.slice(resource_offset),
                    current_slice)};
                if (!new_origin.has_value()) {
                  continue;
                }
                effective_origin =
                    saved_reference.origin.slice(0, resource_offset)
                        .concat(new_origin.value());
                if (!core::try_get(schema, effective_origin.initial())) {
                  continue;
                }
              }

              const auto new_relative{rule->rereference(
                  saved_reference.destination, saved_reference.origin,
                  saved_reference.target_pointer.slice(
                      saved_reference.target_relative_pointer),
                  current_slice)};
              if (!new_relative.has_value()) {
                throw ConvertBrokenReferenceError{saved_reference.destination,
                                                  saved_reference.origin};
              }
              const auto new_fragment{
                  saved_reference.fragment ==
                          core::to_string(saved_reference.target_pointer)
                      ? saved_reference.target_pointer
                            .slice(0, saved_reference.target_relative_pointer)
                            .concat(new_relative.value())
                      : new_relative.value()};

              core::URI original{saved_reference.original};
              // The stringified pointer is literal text, so a token that
              // already reads as an escape must be encoded rather than taken
              // as one
              original.unescaped_fragment(core::to_string(new_fragment));
              core::set(schema, effective_origin,
                        core::JSON{original.recompose()});
              references_fixed = true;
            }

            const auto new_vocabularies{
                frame->vocabularies(new_location.value().get(), resolver)};

            assert(!rule->condition(current, schema, new_vocabularies, *frame,
                                    new_location.value().get(), walker,
                                    resolver));

            std::tuple<core::Pointer, std::string_view, core::JSON> mark{
                entry_pointer, rule->name(), current};
            assert(!processed_rules.contains(mark));
            processed_rules.emplace(std::move(mark));

            if (references_fixed) {
              frame.reset();
            }

            if (references_fixed || reframe_after_transform) {
              return true;
            }
          }

          return false;
        })};

    if (!applied) {
      break;
    }
  }
}

#include "rules/definitions_to_defs.h"
#include "rules/dependencies_to_dependent.h"
#include "rules/draft_official_dialect_with_https.h"
#include "rules/draft_official_dialect_without_empty_fragment.h"
#include "rules/empty_object_as_true.h"
#include "rules/enum_to_const.h"
#include "rules/modern_official_dialect_with_empty_fragment.h"
#include "rules/prefix_promoted_2020_12_keywords.h"
#include "rules/prefix_promoted_draft_2019_09_keywords.h"
#include "rules/prefix_promoted_draft_4_keywords.h"
#include "rules/prefix_promoted_draft_6_keywords.h"
#include "rules/prefix_promoted_draft_7_keywords.h"
#include "rules/upgrade_2019_09_to_2020_12.h"
#include "rules/upgrade_dialect_override_cleanup.h"
#include "rules/upgrade_draft_3_to_draft_4.h"
#include "rules/upgrade_draft_4_to_draft_6.h"
#include "rules/upgrade_draft_6_to_draft_7.h"
#include "rules/upgrade_draft_7_to_draft_2019_09.h"

#undef ONLY_CONTINUE_IF

} // namespace

auto convert(sourcemeta::core::JSON &schema,
             const sourcemeta::core::SchemaWalker &walker,
             const sourcemeta::core::SchemaResolver &resolver,
             const ConvertTarget target, const std::string_view default_dialect,
             const std::string_view default_id) -> void {
  std::vector<Rule> rules;
  rules.reserve(20);
  rules.push_back(make_rule<DraftOfficialDialectWithHttps>());
  rules.push_back(make_rule<DraftOfficialDialectWithoutEmptyFragment>());
  rules.push_back(make_rule<ModernOfficialDialectWithEmptyFragment>());
  rules.push_back(make_rule<PrefixPromotedDraft4Keywords>());
  rules.push_back(make_rule<UpgradeDraft3ToDraft4>());

  if (target == ConvertTarget::Draft6 || target == ConvertTarget::Draft7 ||
      target == ConvertTarget::Draft201909 ||
      target == ConvertTarget::Draft202012) {
    rules.push_back(make_rule<PrefixPromotedDraft6Keywords>());
    rules.push_back(make_rule<UpgradeDraft4ToDraft6>());
    rules.push_back(make_rule<EmptyObjectAsTrue>());
    rules.push_back(make_rule<EnumToConst>());
  }

  if (target == ConvertTarget::Draft7 || target == ConvertTarget::Draft201909 ||
      target == ConvertTarget::Draft202012) {
    rules.push_back(make_rule<PrefixPromotedDraft7Keywords>());
    rules.push_back(make_rule<UpgradeDraft6ToDraft7>());
  }

  if (target == ConvertTarget::Draft201909 ||
      target == ConvertTarget::Draft202012) {
    rules.push_back(make_rule<PrefixPromoted201909Keywords>());
    rules.push_back(make_rule<UpgradeDraft7To201909>());
    rules.push_back(make_rule<DefinitionsToDefs>());
    rules.push_back(make_rule<DependenciesToDependent>());
  }

  if (target == ConvertTarget::Draft202012) {
    rules.push_back(make_rule<PrefixPromoted202012Keywords>());
    rules.push_back(make_rule<Upgrade201909To202012>());
  }

  rules.push_back(make_rule<UpgradeDialectOverrideCleanup>());
  apply(rules, schema, walker, resolver, default_dialect, default_id, target);
  erase_dialect_overrides(schema, walker, resolver, default_dialect,
                          default_id);
}

} // namespace sourcemeta::blaze
