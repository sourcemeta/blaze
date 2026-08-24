#include <sourcemeta/blaze/foundation.h>

#include <algorithm> // std::max, std::ranges::fold_left, std::ranges::sort
#include <cassert>   // assert
#include <cstdint>   // std::uint64_t

namespace {
auto schema_keyword_priority(
    const std::string_view keyword,
    const sourcemeta::blaze::Vocabularies &vocabularies,
    const sourcemeta::blaze::SchemaWalker &walker) -> std::uint64_t {
  const auto &result{walker(keyword, vocabularies)};
  const auto priority_from_dependencies{std::ranges::fold_left(
      result.dependencies, static_cast<std::uint64_t>(0),
      [&vocabularies, &walker](const auto accumulator,
                               const auto &dependency) -> std::uint64_t {
        return std::max(
            accumulator,
            schema_keyword_priority(dependency, vocabularies, walker) + 1);
      })};
  const auto priority_from_order_dependencies{std::ranges::fold_left(
      result.order_dependencies, static_cast<std::uint64_t>(0),
      [&vocabularies, &walker](const auto accumulator,
                               const auto &dependency) -> std::uint64_t {
        return std::max(
            accumulator,
            schema_keyword_priority(dependency, vocabularies, walker) + 1);
      })};
  return std::max(priority_from_dependencies, priority_from_order_dependencies);
}
} // namespace

// TODO: This iterator is not very efficient. It traverses once on
// construction and then the client traverses again.

sourcemeta::blaze::SchemaKeywordIterator::SchemaKeywordIterator(
    const sourcemeta::core::JSON &schema,
    const sourcemeta::blaze::SchemaWalker &walker,
    const sourcemeta::blaze::Vocabularies &vocabularies) {
  assert(is_schema(schema));
  if (schema.is_boolean()) {
    return;
  }

  // TODO: Use std::ranges::to<std::vector>() once libc++ supports it
  // (__cpp_lib_ranges_to_container)
  for (const auto &entry : schema.as_object()) {
    sourcemeta::core::WeakPointer entry_pointer;
    entry_pointer.push_back(std::cref(entry.first));
    sourcemeta::blaze::SchemaIteratorEntry subschema_entry{
        .parent = std::nullopt,
        .pointer = std::move(entry_pointer),
        .dialect = "",
        .vocabularies = vocabularies,
        .base_dialect = std::nullopt,
        .subschema = entry.second,
        .orphan = false,
        .property_name = false};
    this->entries.push_back(std::move(subschema_entry));
  }

  // Sort keywords based on priority for correct evaluation
  std::ranges::sort(
      this->entries,
      [&vocabularies, &walker](const auto &left, const auto &right) -> bool {
        // These cannot be empty or indexes, as we created
        // the entries array from a JSON object
        assert(!left.pointer.empty() && left.pointer.back().is_property());
        assert(!right.pointer.empty() && right.pointer.back().is_property());

        const auto left_priority = schema_keyword_priority(
            left.pointer.back().to_property(), vocabularies, walker);
        const auto right_priority = schema_keyword_priority(
            right.pointer.back().to_property(), vocabularies, walker);

        // Sort first on priority, second on actual keywords. The latter is to
        // make sure different compilers with different STL implementations end
        // up at the exact same result. Not really mandatory, but useful for
        // writing tests on the iterator output.
        if (left_priority != right_priority) {
          return left_priority < right_priority;
        } else {
          return left.pointer < right.pointer;
        }
      });
}

auto sourcemeta::blaze::SchemaKeywordIterator::begin() const -> const_iterator {
  return this->entries.begin();
}
auto sourcemeta::blaze::SchemaKeywordIterator::end() const -> const_iterator {
  return this->entries.end();
}
auto sourcemeta::blaze::SchemaKeywordIterator::cbegin() const
    -> const_iterator {
  return this->entries.cbegin();
}
auto sourcemeta::blaze::SchemaKeywordIterator::cend() const -> const_iterator {
  return this->entries.cend();
}
