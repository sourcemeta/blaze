#include <sourcemeta/blaze/evaluator_context.h>
#include <sourcemeta/blaze/evaluator_error.h>

#include <cassert> // assert

namespace sourcemeta::blaze {

auto EvaluationContext::push(
    const sourcemeta::jsontoolkit::Pointer &relative_schema_location,
    const sourcemeta::jsontoolkit::Pointer &relative_instance_location,
    const std::size_t &schema_resource, const bool dynamic, const bool track)
    -> void {
  // Guard against infinite recursion in a cheap manner, as
  // infinite recursion will manifest itself through huge
  // ever-growing evaluate paths
  constexpr auto EVALUATE_PATH_LIMIT{300};

  if (track) {
    if (this->evaluate_path.size() > EVALUATE_PATH_LIMIT) [[unlikely]] {
      throw sourcemeta::blaze::EvaluationError(
          "The evaluation path depth limit was reached "
          "likely due to infinite recursion");
    }

    this->evaluate_path.push_back(relative_schema_location);
    this->instance_location.push_back(relative_instance_location);
  } else {
    if (this->evaluate_path_size > EVALUATE_PATH_LIMIT) [[unlikely]] {
      throw sourcemeta::blaze::EvaluationError(
          "The evaluation path depth limit was reached "
          "likely due to infinite recursion");
    }

    // We still need to somewhat keep track of this to prevent infinite
    // recursion
    this->evaluate_path_size += relative_schema_location.size();
  }

  if (dynamic) {
    // Note that we are potentially repeatedly pushing back the
    // same schema resource over and over again. However, the
    // logic for making sure this list is "pure" takes a lot of
    // computation power. Being silly seems faster.
    this->resources.push_back(schema_resource);
  }
}

auto EvaluationContext::pop(const std::size_t relative_schema_location_size,
                            const std::size_t relative_instance_location_size,
                            const bool dynamic, const bool track) -> void {
  if (track) {
    this->evaluate_path.pop_back(relative_schema_location_size);
    this->instance_location.pop_back(relative_instance_location_size);
  } else {
    this->evaluate_path_size -= relative_schema_location_size;
  }

  if (dynamic) {
    assert(!this->resources.empty());
    this->resources.pop_back();
  }
}

auto EvaluationContext::hash(
    const std::size_t &resource,
    const sourcemeta::jsontoolkit::JSON::String &fragment) const noexcept
    -> std::size_t {
  return resource + this->hasher_(fragment);
}

auto EvaluationContext::evaluate() -> void {
  this->evaluate(sourcemeta::jsontoolkit::empty_pointer);
}

auto EvaluationContext::evaluate(
    const sourcemeta::jsontoolkit::WeakPointer::Token::Index from,
    const sourcemeta::jsontoolkit::WeakPointer::Token::Index to) -> void {
  for (auto cursor = from; cursor <= to; cursor++) {
    this->evaluate({cursor});
  }
}

auto EvaluationContext::evaluate(
    const sourcemeta::jsontoolkit::Pointer &relative_instance_location)
    -> void {
  auto new_instance_location = this->instance_location;
  new_instance_location.push_back(relative_instance_location);
  Evaluation entry{std::move(new_instance_location), this->evaluate_path,
                   false};
  this->evaluated_.emplace_back(std::move(entry));
}

auto EvaluationContext::is_evaluated(
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

auto EvaluationContext::unevaluate() -> void {
  for (auto &entry : this->evaluated_) {
    if (!entry.skip && entry.evaluate_path.starts_with(this->evaluate_path)) {
      entry.skip = true;
    }
  }
}

} // namespace sourcemeta::blaze
