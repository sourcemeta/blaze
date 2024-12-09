#ifndef SOURCEMETA_JSONTOOLKIT_JSON_FLAT_MAP_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_FLAT_MAP_H_

#include <algorithm>        // std::swap
#include <cassert>          // assert
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::advance
#include <utility>          // std::pair, std::move
#include <vector>           // std::vector

namespace sourcemeta::jsontoolkit {

// TODO: Merge as part of JSONObject
/// @ingroup json
template <typename Key, typename Value, typename Hash> class FlatMap {
public:
  FlatMap() = default;

  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<Key, Value>;
  using underlying_type = std::vector<value_type>;
  using size_type = typename underlying_type::size_type;
  using difference_type = typename underlying_type::difference_type;
  using allocator_type = typename underlying_type::allocator_type;
  using reference = typename underlying_type::reference;
  using const_reference = typename underlying_type::const_reference;
  using pointer = typename underlying_type::pointer;
  using const_pointer = typename underlying_type::const_pointer;
  using const_iterator = typename underlying_type::const_iterator;
  using hash_type = typename Hash::hash_type;

  FlatMap(std::initializer_list<value_type> entries) {
    this->hashes.reserve(entries.size());
    this->data.reserve(entries.size());
    for (auto &&entry : entries) {
      this->assign(std::move(entry.first), std::move(entry.second));
    }
  }

  auto begin() const noexcept -> const_iterator { return this->data.begin(); }
  auto end() const noexcept -> const_iterator { return this->data.end(); }
  auto cbegin() const noexcept -> const_iterator { return this->data.cbegin(); }
  auto cend() const noexcept -> const_iterator { return this->data.cend(); }

  inline auto hash(const key_type &key) const noexcept -> hash_type {
    return this->hasher(key);
  }

  // TODO: Add an assign overload for const key, rvalue

  auto assign(key_type &&key, mapped_type &&value) -> hash_type {
    assert(this->data.size() == this->hashes.size());
    const auto key_hash{this->hash(key)};
    for (size_type index = 0; index < this->hashes.size(); index++) {
      if (this->hashes[index] == key_hash &&
          this->hasher.equal(this->data[index].first, key, key_hash)) {
        this->data[index].second = std::move(value);
        return key_hash;
      }
    }

    // TODO: Make sure we either emplace both, or none
    this->data.emplace_back(std::move(key), std::move(value));
    this->hashes.emplace_back(key_hash);
    return key_hash;
  }

  auto assign(const key_type &key, const mapped_type &value) -> hash_type {
    assert(this->data.size() == this->hashes.size());
    const auto key_hash{this->hash(key)};
    for (size_type index = 0; index < this->hashes.size(); index++) {
      if (this->hashes[index] == key_hash &&
          this->hasher.equal(this->data[index].first, key, key_hash)) {
        this->data[index].second = value;
        return key_hash;
      }
    }

    // TODO: Make sure we either emplace both, or none
    this->data.emplace_back(key, value);
    this->hashes.emplace_back(key_hash);
    return key_hash;
  }

  // As a performance optimisation if the hash is known
  inline auto find(const key_type &key, const hash_type key_hash) const
      -> const_iterator {
    assert(this->data.size() == this->hashes.size());
    assert(this->hash(key) == key_hash);

    // Move the perfect hash condition out of the loop for extra performance
    if (this->hasher.is_perfect_string_hash(key_hash)) {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash) {
          auto iterator{this->cbegin()};
          std::advance(iterator, index);
          return iterator;
        }
      }
    } else {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash && this->data[index].first == key) {
          auto iterator{this->cbegin()};
          std::advance(iterator, index);
          return iterator;
        }
      }
    }

    return this->cend();
  }

  // As a performance optimisation if the hash is known
  inline auto contains(const key_type &key, const hash_type key_hash) const
      -> bool {
    assert(this->data.size() == this->hashes.size());
    assert(this->hash(key) == key_hash);

    // Move the perfect hash condition out of the loop for extra performance
    if (this->hasher.is_perfect_string_hash(key_hash)) {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash) {
          return true;
        }
      }
    } else {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash && this->data[index].first == key) {
          return true;
        }
      }
    }

    return false;
  }

  // As a performance optimisation if the hash is known

  inline auto at(const key_type &key, const hash_type key_hash) const
      -> const mapped_type & {
    assert(this->data.size() == this->hashes.size());
    assert(this->hash(key) == key_hash);

    // Move the perfect hash condition out of the loop for extra performance
    if (this->hasher.is_perfect_string_hash(key_hash)) {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash) {
          return this->data[index].second;
        }
      }
    } else {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash && this->data[index].first == key) {
          return this->data[index].second;
        }
      }
    }

// See https://en.cppreference.com/w/cpp/utility/unreachable
#if defined(_MSC_VER) && !defined(__clang__)
    __assume(false);
#else
    __builtin_unreachable();
#endif
  }

  inline auto at(const key_type &key, const hash_type key_hash)
      -> mapped_type & {
    assert(this->data.size() == this->hashes.size());
    assert(this->hash(key) == key_hash);

    // Move the perfect hash condition out of the loop for extra performance
    if (this->hasher.is_perfect_string_hash(key_hash)) {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash) {
          return this->data[index].second;
        }
      }
    } else {
      for (size_type index = 0; index < this->hashes.size(); index++) {
        if (this->hashes[index] == key_hash && this->data[index].first == key) {
          return this->data[index].second;
        }
      }
    }

// See https://en.cppreference.com/w/cpp/utility/unreachable
#if defined(_MSC_VER) && !defined(__clang__)
    __assume(false);
#else
    __builtin_unreachable();
#endif
  }

  auto erase(const key_type &key, const hash_type key_hash) -> size_type {
    const auto current_size{this->size()};
    for (size_type index = 0; index < current_size; index++) {
      if (this->hashes[index] == key_hash &&
          this->hasher.equal(this->data[index].first, key, key_hash)) {
        std::swap(this->hashes[index], this->hashes.back());
        std::swap(this->data[index], this->data.back());
        this->hashes.pop_back();
        this->data.pop_back();
        return current_size - 1;
      }
    }

    return current_size;
  }

  inline auto erase(const key_type &key) -> size_type {
    return this->erase(key, this->hash(key));
  }

  inline auto size() const noexcept -> size_type {
    assert(this->data.size() == this->hashes.size());
    return this->data.size();
  }

  inline auto empty() const noexcept -> bool {
    assert(this->data.size() == this->hashes.size());
    return this->data.empty();
  }

  inline auto clear() noexcept -> void {
    this->data.clear();
    this->hashes.clear();
  }

  auto operator!=(const FlatMap &other) const -> bool = default;

  auto operator==(const FlatMap &other) const -> bool {
    if (this->size() != other.size()) {
      return false;
    }

    for (size_type index = 0; index < this->hashes.size(); index++) {
      const auto iterator{
          other.find(this->data[index].first, this->hashes[index])};
      if (iterator == other.cend()) {
        return false;
      } else if (iterator->second != this->data[index].second) {
        return false;
      }
    }

    return true;
  }

private:
  underlying_type data;
  // So that we can loop over hashes faster, potentially vectorizing loops
  std::vector<hash_type> hashes;
  Hash hasher;
};

} // namespace sourcemeta::jsontoolkit

#endif
