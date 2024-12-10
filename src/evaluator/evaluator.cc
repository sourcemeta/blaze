#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonpointer.h>
#include <sourcemeta/jsontoolkit/regex.h>
#include <sourcemeta/jsontoolkit/uri.h>

#include <algorithm>  // std::min, std::any_of, std::find
#include <cassert>    // assert
#include <functional> // std::reference_wrapper
#include <limits>     // std::numeric_limits
#include <optional>   // std::optional

namespace sourcemeta::blaze {
using namespace sourcemeta::jsontoolkit;

inline auto
resolve_target(const std::optional<std::reference_wrapper<const JSON::String>>
                   &property_target,
               const JSON &instance) noexcept -> const JSON & {
  if (property_target.has_value()) [[unlikely]] {
    // In this case, we still need to return a string in order
    // to cope with non-string keywords inside `propertyNames`
    // that need to fail validation. But then, the actual string
    // we return doesn't matter, so we can always return a dummy one.
    return Evaluator::empty_string;
  }

  return instance;
}

inline auto resolve_string_target(
    // TODO: Make this a raw pointer
    const std::optional<std::reference_wrapper<const JSON::String>>
        &property_target,
    const JSON &instance, const Pointer &relative_instance_location) noexcept
    -> const JSON::String * {
  if (property_target.has_value()) [[unlikely]] {
    return &property_target.value().get();
  }

  const auto &target{get(instance, relative_instance_location)};
  if (!target.is_string()) {
    return nullptr;
  } else {
    return &target.to_string();
  }
}

} // namespace sourcemeta::blaze

#define SOURCEMETA_STRINGIFY(x) #x
#define SOURCEMETA_MAYBE_UNUSED(variable) (void)variable;

#include "evaluator_complete.h"
#include "evaluator_fast.h"

#undef SOURCEMETA_STRINGIFY
#undef SOURCEMETA_MAYBE_UNUSED

namespace sourcemeta::blaze {

auto Evaluator::validate(const Template &schema,
                         const sourcemeta::jsontoolkit::JSON &instance)
    -> bool {
  // Do a full reset for the next run
  assert(this->evaluate_path.empty());
  assert(this->instance_location.empty());
  assert(this->resources.empty());
  this->labels.clear();

  if (schema.dynamic || schema.track) {
    this->evaluated_.clear();
    return complete::evaluate(instance, *this, schema, std::nullopt);
  } else {
    return fast::evaluate(instance, *this, schema);
  }
}

auto Evaluator::validate(const Template &schema,
                         const sourcemeta::jsontoolkit::JSON &instance,
                         const Callback &callback) -> bool {
  // Do a full reset for the next run
  assert(this->evaluate_path.empty());
  assert(this->instance_location.empty());
  assert(this->resources.empty());
  this->labels.clear();
  this->evaluated_.clear();

  return complete::evaluate(instance, *this, schema, callback);
}

const sourcemeta::jsontoolkit::JSON Evaluator::null{nullptr};
const sourcemeta::jsontoolkit::JSON Evaluator::empty_string{""};

auto Evaluator::hash(const std::size_t &resource,
                     const sourcemeta::jsontoolkit::JSON::String &fragment)
    const noexcept -> std::size_t {
  return resource + this->hasher_(fragment);
}

auto Evaluator::evaluate() -> void {
  this->evaluate(sourcemeta::jsontoolkit::empty_pointer);
}

auto Evaluator::evaluate(
    const sourcemeta::jsontoolkit::WeakPointer::Token::Index from,
    const sourcemeta::jsontoolkit::WeakPointer::Token::Index to) -> void {
  for (auto cursor = from; cursor <= to; cursor++) {
    this->evaluate({cursor});
  }
}

auto Evaluator::evaluate(
    const sourcemeta::jsontoolkit::Pointer &relative_instance_location)
    -> void {
  auto new_instance_location = this->instance_location;
  new_instance_location.push_back(relative_instance_location);
  Evaluation entry{std::move(new_instance_location), this->evaluate_path,
                   false};
  this->evaluated_.emplace_back(std::move(entry));
}

auto Evaluator::is_evaluated(
    const sourcemeta::jsontoolkit::WeakPointer::Token &tail) const -> bool {
  for (auto iterator = this->evaluated_.crbegin();
       iterator != this->evaluated_.crend(); ++iterator) {
    if (!iterator->skip &&
        this->instance_location.starts_with(iterator->instance_location,
                                            tail) &&
        // Its not possible to affect cousins
        iterator->evaluate_path.starts_with_initial(this->evaluate_path)) {
      return true;
    }
  }

  return false;
}

auto Evaluator::unevaluate() -> void {
  for (auto &entry : this->evaluated_) {
    if (!entry.skip && entry.evaluate_path.starts_with(this->evaluate_path)) {
      entry.skip = true;
    }
  }
}

} // namespace sourcemeta::blaze
