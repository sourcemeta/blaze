#include <sourcemeta/blaze/evaluator_string_set.h>

namespace sourcemeta::blaze {

auto StringSet::contains(const value_type &value, const hash_type hash) const
    -> bool {
  for (const auto &entry : this->data) {
    if (entry.second == hash && entry.first == value) {
      return true;
    }
  }

  return false;
}

auto StringSet::insert(const value_type &value) -> void {
  const auto hash{this->hasher(value)};
  if (!this->contains(value, hash)) {
    this->data.emplace_back(value, hash);
  }
}

auto StringSet::insert(value_type &&value) -> void {
  const auto hash{this->hasher(value)};
  if (!this->contains(value, hash)) {
    this->data.emplace_back(std::move(value), hash);
  }
}

} // namespace sourcemeta::blaze
