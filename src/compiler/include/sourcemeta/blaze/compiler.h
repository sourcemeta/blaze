#ifndef SOURCEMETA_BLAZE_COMPILER_COMPILE_H_
#define SOURCEMETA_BLAZE_COMPILER_COMPILE_H_

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/regex.h>

#include <cstdint>     // std::uint8_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector
#include <optional>      // std::optional
#include <tuple>         // std::tuple
#include <unordered_set> // std::unordered_set
#include <utility>       // std::pair

namespace sourcemeta::blaze {

class StringSet {
public:
  StringSet() = default;

  using string_type = sourcemeta::core::JSON::String;
  using hash_type = sourcemeta::core::JSON::Object::Container::hash_type;
  using value_type = std::pair<string_type, hash_type>;
  using underlying_type = std::vector<value_type>;
  using size_type = typename underlying_type::size_type;
  using difference_type = typename underlying_type::difference_type;
  using const_iterator = typename underlying_type::const_iterator;

  inline auto begin() const -> const_iterator { return this->data.begin(); }
  inline auto end() const -> const_iterator { return this->data.end(); }
  inline auto cbegin() const -> const_iterator { return this->data.cbegin(); }
  inline auto cend() const -> const_iterator { return this->data.cend(); }

  auto to_json() const -> sourcemeta::core::JSON {
    return sourcemeta::core::to_json(this->data, [](const auto &item) {
      return sourcemeta::core::to_json(item.first);
    });
  }

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif
  underlying_type data;
#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif
};

using ValueType = sourcemeta::core::JSON::Type;
using ValueStringSet = StringSet;
using ValueIndexPair = std::pair<std::size_t, std::size_t>;
using ValueStringHashes = std::pair<std::vector<ValueStringSet::hash_type>, std::vector<ValueIndexPair>>;
using ValueTypedHashes = std::pair<ValueType, ValueStringHashes>;

using Value = std::variant<ValueTypedHashes>;

struct Instruction {
  const Value value;
};

auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON;
} // namespace sourcemeta::blaze

#endif
