#include <sourcemeta/blaze/output_simple.h>

#include <sourcemeta/blaze/foundation.h>

#include <algorithm> // std::any_of, std::equal, std::sort
#include <cassert>   // assert
#include <iterator>  // std::back_inserter, std::make_move_iterator, std::next
#include <ranges>    // std::views::reverse
#include <utility>   // std::move

namespace {

auto shares_prefix(const sourcemeta::core::WeakPointer &pointer,
                   const sourcemeta::core::WeakPointer &other,
                   const std::size_t prefix_size) -> bool {
  return pointer.size() >= prefix_size && other.size() >= prefix_size &&
         std::equal(pointer.cbegin(),
                    std::next(pointer.cbegin(),
                              static_cast<std::ptrdiff_t>(prefix_size)),
                    other.cbegin());
}

auto starts_with_strict(const sourcemeta::core::WeakPointer &pointer,
                        const sourcemeta::core::WeakPointer &other) -> bool {
  return pointer.size() > other.size() &&
         shares_prefix(pointer, other, other.size());
}

} // namespace

namespace sourcemeta::blaze {

SimpleOutput::SimpleOutput(const sourcemeta::core::JSON &instance,
                           sourcemeta::core::WeakPointer base)
    : instance_{instance}, base_{std::move(base)} {}

auto SimpleOutput::begin() const -> const_iterator {
  return this->output.begin();
}

auto SimpleOutput::end() const -> const_iterator { return this->output.end(); }

auto SimpleOutput::cbegin() const -> const_iterator {
  return this->output.cbegin();
}

auto SimpleOutput::cend() const -> const_iterator {
  return this->output.cend();
}

auto SimpleOutput::operator()(
    const EvaluationType type, const bool result, const Instruction &step,
    const InstructionExtra &step_metadata,
    const sourcemeta::core::WeakPointer &evaluate_path,
    const sourcemeta::core::WeakPointer &instance_location,
    const sourcemeta::core::JSON &annotation) -> void {
  if (evaluate_path.empty()) {
    return;
  }

  assert(evaluate_path.back().is_property());

  // Fast path: passing non-annotation instructions that are not
  // closing a mask entry can be skipped entirely
  if (result && !is_annotation(step.type)) {
    if (type == EvaluationType::Pre) {
      const auto &keyword{evaluate_path.back().to_property()};
      if (keyword == "anyOf" || keyword == "oneOf" || keyword == "not" ||
          keyword == "if" || keyword == "contains") {
        this->mask.push_back({.evaluate_path = evaluate_path,
                              .instance_location = instance_location,
                              .annotations_mark = this->annotations_.size(),
                              .buffered_traces = {}});
      }
    } else if (type == EvaluationType::Post && !this->mask.empty() &&
               this->mask.back().evaluate_path == evaluate_path &&
               this->mask.back().instance_location == instance_location) {
      this->mask.pop_back();
    }

    return;
  }

  auto effective_evaluate_path{evaluate_path.resolve_from(this->base_)};
  if (effective_evaluate_path.empty()) {
    return;
  }

  if (is_annotation(step.type)) {
    if (type == EvaluationType::Post) {
      this->annotations_.push_back(
          {.instance_location = instance_location,
           .evaluate_path = std::move(effective_evaluate_path),
           .schema_location = step_metadata.keyword_location,
           .value = annotation});
    }

    return;
  }

  const auto &keyword{evaluate_path.back().to_property()};

  if (type == EvaluationType::Pre) {
    assert(result);
    // To ease the output
    if (keyword == "anyOf" || keyword == "oneOf" || keyword == "not" ||
        keyword == "if" || keyword == "contains") {
      this->mask.push_back({.evaluate_path = evaluate_path,
                            .instance_location = instance_location,
                            .annotations_mark = this->annotations_.size(),
                            .buffered_traces = {}});
    }
  } else if (type == EvaluationType::Post) {
    const auto mask_it{std::ranges::find_if(
        this->mask, [&](const MaskEntry &mask_entry) -> bool {
          return mask_entry.evaluate_path == evaluate_path &&
                 mask_entry.instance_location == instance_location;
        })};
    if (mask_it != this->mask.end()) {
      // Present unexpected traces only when needed
      if (!result && keyword != "not" && keyword != "if") {
#ifdef __cpp_lib_containers_ranges
        this->output.append_range(std::move(mask_it->buffered_traces));
#else
        this->output.insert(
            this->output.end(),
            std::make_move_iterator(mask_it->buffered_traces.begin()),
            std::make_move_iterator(mask_it->buffered_traces.end()));
#endif
      }

      this->mask.erase(mask_it);
    }
  }

  if (result) {
    return;
  }

  if (type == EvaluationType::Post && !this->annotations_.empty()) {
    // A failure inside a branching keyword discards every annotation that
    // the failing unit collected, including the ones at instance locations
    // below the unit's own instance location. The unit is the disjunction
    // branch for `anyOf` and `oneOf`, the application of the subschema to
    // the array element for `contains`, and the entire subschema for `if`
    // and `not`. Outside of branching keywords, annotations from successful
    // sibling subschemas are reported on a best-effort basis, so only
    // annotations at the exact instance location of the failure are
    // discarded
    const MaskEntry *unit{nullptr};
    for (const auto &mask_entry : std::views::reverse(this->mask)) {
      if (starts_with_strict(evaluate_path, mask_entry.evaluate_path) &&
          instance_location.starts_with(mask_entry.instance_location)) {
        unit = &mask_entry;
        break;
      }
    }

    if (unit) {
      const auto &mask_keyword{unit->evaluate_path.back().to_property()};
      const auto evaluate_prefix_size{
          unit->evaluate_path.size() +
          ((mask_keyword == "anyOf" || mask_keyword == "oneOf") ? 1 : 0)};
      const auto instance_prefix_size{unit->instance_location.size() +
                                      (mask_keyword == "contains" ? 1 : 0)};
      // Every annotation the failing unit collected, including the ones
      // that the equality check below would match, sits at or beyond the
      // mark the unit's branching keyword recorded, so older entries do
      // not need to be scanned at all
      assert(unit->annotations_mark <= this->annotations_.size());
      const auto from{this->annotations_.begin() +
                      static_cast<std::ptrdiff_t>(unit->annotations_mark)};
      this->annotations_.erase(
          std::remove_if(
              from, this->annotations_.end(),
              [&](const AnnotationEntry &entry) -> bool {
                return (entry.evaluate_path.starts_with_initial(
                            evaluate_path) &&
                        entry.instance_location == instance_location) ||
                       (shares_prefix(entry.evaluate_path, evaluate_path,
                                      evaluate_prefix_size) &&
                        shares_prefix(entry.instance_location,
                                      instance_location, instance_prefix_size));
              }),
          this->annotations_.end());
    } else {
      std::erase_if(
          this->annotations_, [&](const AnnotationEntry &entry) -> bool {
            return entry.evaluate_path.starts_with_initial(evaluate_path) &&
                   entry.instance_location == instance_location;
          });
    }
  }

  if (keyword == "if") {
    return;
  } else {
    for (auto &mask_entry : this->mask) {
      if (evaluate_path.starts_with(mask_entry.evaluate_path)) {
        mask_entry.buffered_traces.push_back(
            {.message = describe(result, step, evaluate_path, instance_location,
                                 this->instance_, annotation),
             .instance_location = instance_location,
             .evaluate_path = std::move(effective_evaluate_path),
             .schema_location = step_metadata.keyword_location});

        return;
      }
    }
  }

  this->output.push_back(
      {.message = describe(result, step, evaluate_path, instance_location,
                           this->instance_, annotation),
       .instance_location = instance_location,
       .evaluate_path = std::move(effective_evaluate_path),
       .schema_location = step_metadata.keyword_location});
}

} // namespace sourcemeta::blaze
