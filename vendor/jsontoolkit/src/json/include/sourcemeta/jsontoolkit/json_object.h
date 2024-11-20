#ifndef SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif
#include <ankerl/unordered_dense.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include <functional>       // std::equal_to
#include <initializer_list> // std::initializer_list
#include <memory>           // std::allocator

namespace sourcemeta::jsontoolkit {

/// @ingroup json
template <typename Key, typename Value, typename Hash> class JSONObject {
public:
  using Container = ankerl::unordered_dense::map<
      Key, Value, Hash, std::equal_to<Key>,
      std::allocator<std::pair<Key, Value>>,
      ankerl::unordered_dense::bucket_type::standard>;

  // Constructors
  JSONObject() : data{} {}
  JSONObject(std::initializer_list<typename Container::value_type> values)
      : data{values} {}

  // Operators
  // We cannot default given that this class references
  // a JSON "value" as an incomplete type

  auto operator<(const JSONObject<Key, Value, Hash> &other) const noexcept
      -> bool {
    // The `std::unordered_map` container, by definition, does not provide
    // ordering. However, we still want some level of ordering to allow
    // arrays of objects to be sorted.

    // First try a size comparison
    if (this->data.size() != other.data.size()) {
      return this->data.size() < other.data.size();
    }

    // Otherwise do value comparison for common properties
    for (const auto &[key, value] : this->data) {
      if (other.data.contains(key) && value < other.data.at(key)) {
        return true;
      }
    }

    return false;
  }

  auto operator<=(const JSONObject<Key, Value, Hash> &other) const noexcept
      -> bool {
    return this->data <= other.data;
  }
  auto operator>(const JSONObject<Key, Value, Hash> &other) const noexcept
      -> bool {
    return this->data > other.data;
  }
  auto operator>=(const JSONObject<Key, Value, Hash> &other) const noexcept
      -> bool {
    return this->data >= other.data;
  }
  auto operator==(const JSONObject<Key, Value, Hash> &other) const noexcept
      -> bool {
    return this->data == other.data;
  }
  auto operator!=(const JSONObject<Key, Value, Hash> &other) const noexcept
      -> bool {
    return this->data != other.data;
  }

  // Member types
  using key_type = typename Container::key_type;
  using mapped_type = typename Container::mapped_type;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using difference_type = typename Container::difference_type;
  using allocator_type = typename Container::allocator_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using pointer = typename Container::pointer;
  using const_pointer = typename Container::const_pointer;
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  /// Get a mutable begin iterator on the object
  auto begin() noexcept -> iterator { return this->data.begin(); }
  /// Get a mutable end iterator on the object
  auto end() noexcept -> iterator { return this->data.end(); }
  /// Get a constant begin iterator on the object
  auto begin() const noexcept -> const_iterator { return this->data.begin(); }
  /// Get a constant end iterator on the object
  auto end() const noexcept -> const_iterator { return this->data.end(); }
  /// Get a constant begin iterator on the object
  auto cbegin() const noexcept -> const_iterator { return this->data.cbegin(); }
  /// Get a constant end iterator on the object
  auto cend() const noexcept -> const_iterator { return this->data.cend(); }

private:
  friend Value;
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  Container data;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::jsontoolkit

#endif
