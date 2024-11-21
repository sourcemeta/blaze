#include <sourcemeta/blaze/evaluator_context.h>

#include <cassert> // assert

namespace sourcemeta::blaze {

const sourcemeta::jsontoolkit::JSON EvaluationContext::null{nullptr};
const sourcemeta::jsontoolkit::JSON EvaluationContext::empty_string{""};

EvaluationContext::EvaluationContext() {
  // Generously allocate plenty of space for demanding runs
  this->evaluate_path.reserve(1024);
  this->instance_location.reserve(1024);
  this->resources.reserve(1024);
  this->evaluated.reserve(1024);
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
  this->evaluated.emplace_back(std::move(entry));
}

auto EvaluationContext::is_evaluated(
    const sourcemeta::jsontoolkit::WeakPointer::Token &tail) const -> bool {
  for (auto iterator = this->evaluated.crbegin();
       iterator != this->evaluated.crend(); ++iterator) {
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
  for (auto &entry : this->evaluated) {
    if (!entry.skip && entry.evaluate_path.starts_with(this->evaluate_path)) {
      entry.skip = true;
    }
  }
}

} // namespace sourcemeta::blaze
