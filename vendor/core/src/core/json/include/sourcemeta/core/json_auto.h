#ifndef SOURCEMETA_CORE_JSON_AUTO_H_
#define SOURCEMETA_CORE_JSON_AUTO_H_

#include <sourcemeta/core/json_value.h>

#include <concepts>    // std::same_as, std::constructible_from
#include <functional>  // std::function
#include <optional>    // std::optional
#include <tuple>       // std::tuple, std::apply
#include <type_traits> // std::false_type, std::true_type, std::void_t, std::is_enum_v, std::underlying_type_t, std::is_same_v
#include <utility>     // std::pair

namespace sourcemeta::core {

/// @ingroup json
template <typename, typename = void>
struct to_json_has_mapped_type : std::false_type {};
template <typename T>
struct to_json_has_mapped_type<T, std::void_t<typename T::mapped_type>>
    : std::true_type {};

/// @ingroup json
template <typename T> struct to_json_is_basic_string : std::false_type {};
template <typename CharT, typename Traits, typename Alloc>
struct to_json_is_basic_string<std::basic_string<CharT, Traits, Alloc>>
    : std::true_type {};

/// @ingroup json
template <typename T>
concept to_json_has_method = requires(const T value) {
  { value.to_json() } -> std::same_as<JSON>;
};

/// @ingroup json
/// Container-like classes can opt-out from automatic JSON
/// serialisation by setting `using json_auto = std::false_type;`
template <typename, typename = void>
struct to_json_supports_auto_impl : std::true_type {};
template <typename T>
struct to_json_supports_auto_impl<T, std::void_t<typename T::json_auto>>
    : std::bool_constant<
          !std::is_same_v<typename T::json_auto, std::false_type>> {};
template <typename T>
concept to_json_supports_auto = to_json_supports_auto_impl<T>::value;

/// @ingroup json
template <typename T>
concept to_json_list_like =
    requires(T type) {
      typename T::value_type;
      typename T::const_iterator;
      { type.cbegin() } -> std::same_as<typename T::const_iterator>;
      { type.cend() } -> std::same_as<typename T::const_iterator>;
    } && to_json_supports_auto<T> && !to_json_has_mapped_type<T>::value &&
    !to_json_has_method<T> && !to_json_is_basic_string<T>::value;

/// @ingroup json
template <typename T>
concept to_json_map_like =
    requires(T type) {
      typename T::value_type;
      typename T::const_iterator;
      typename T::key_type;
      { type.cbegin() } -> std::same_as<typename T::const_iterator>;
      { type.cend() } -> std::same_as<typename T::const_iterator>;
    } && to_json_supports_auto<T> && to_json_has_mapped_type<T>::value &&
    !to_json_has_method<T> &&
    std::is_same_v<typename T::key_type, JSON::String>;

/// @ingroup json
/// If the value has a `.to_json()` method, always prefer that
template <typename T>
  requires(to_json_has_method<T>)
auto to_json(const T &value) -> JSON {
  return value.to_json();
}

// TODO: How can we keep this in the hash header that does not yet know about
// JSON?
/// @ingroup json
template <typename T>
  requires std::is_same_v<T, JSON::Object::Container::hash_type>
auto to_json(const T &hash) -> JSON {
  auto result{JSON::make_array()};
#if defined(__SIZEOF_INT128__)
  result.push_back(JSON{static_cast<std::size_t>(hash.a >> 64)});
  result.push_back(JSON{static_cast<std::size_t>(hash.a)});
  result.push_back(JSON{static_cast<std::size_t>(hash.b >> 64)});
  result.push_back(JSON{static_cast<std::size_t>(hash.b)});
#else
  result.push_back(JSON{static_cast<std::size_t>(hash.a)});
  result.push_back(JSON{static_cast<std::size_t>(hash.b)});
  result.push_back(JSON{static_cast<std::size_t>(hash.c)});
  result.push_back(JSON{static_cast<std::size_t>(hash.d)});
#endif
  return result;
}

/// @ingroup json
template <typename T>
  requires std::constructible_from<JSON, T>
auto to_json(const T &value) -> JSON {
  return JSON{value};
}

/// @ingroup json
template <typename T>
  requires std::is_enum_v<T>
auto to_json(const T value) -> JSON {
  return to_json<std::underlying_type_t<T>>(
      static_cast<std::underlying_type_t<T>>(value));
}

/// @ingroup json
template <typename T> auto to_json(const std::optional<T> &value) -> JSON {
  return value.has_value() ? to_json<T>(value.value()) : JSON{nullptr};
}

/// @ingroup json
template <to_json_list_like T>
auto to_json(typename T::const_iterator begin, typename T::const_iterator end)
    -> JSON {
  // TODO: Extend `make_array` to optionally take iterators, etc
  auto result{JSON::make_array()};
  for (auto iterator = begin; iterator != end; ++iterator) {
    result.push_back(to_json<typename T::value_type>(*iterator));
  }

  return result;
}

/// @ingroup json
template <to_json_list_like T>
auto to_json(
    typename T::const_iterator begin, typename T::const_iterator end,
    const std::function<JSON(const typename T::value_type &)> &callback)
    -> JSON {
  // TODO: Extend `make_array` to optionally take iterators, etc
  auto result{JSON::make_array()};
  for (auto iterator = begin; iterator != end; ++iterator) {
    result.push_back(callback(*iterator));
  }

  return result;
}

/// @ingroup json
template <to_json_list_like T> auto to_json(const T &value) -> JSON {
  return to_json<T>(value.cbegin(), value.cend());
}

/// @ingroup json
template <to_json_list_like T>
auto to_json(
    const T &value,
    const std::function<JSON(const typename T::value_type &)> &callback)
    -> JSON {
  return to_json<T>(value.cbegin(), value.cend(), callback);
}

/// @ingroup json
template <to_json_map_like T>
auto to_json(typename T::const_iterator begin, typename T::const_iterator end)
    -> JSON {
  auto result{JSON::make_object()};
  for (auto iterator = begin; iterator != end; ++iterator) {
    result.assign(iterator->first,
                  to_json<typename T::mapped_type>(iterator->second));
  }

  return result;
}

/// @ingroup json
template <to_json_map_like T> auto to_json(const T &value) -> JSON {
  return to_json<T>(value.cbegin(), value.cend());
}

/// @ingroup json
template <to_json_map_like T>
auto to_json(
    typename T::const_iterator begin, typename T::const_iterator end,
    const std::function<JSON(const typename T::mapped_type &)> &callback)
    -> JSON {
  auto result{JSON::make_object()};
  for (auto iterator = begin; iterator != end; ++iterator) {
    result.assign(iterator->first, callback(iterator->second));
  }

  return result;
}

/// @ingroup json
template <to_json_map_like T>
auto to_json(
    const T &value,
    const std::function<JSON(const typename T::mapped_type &)> &callback)
    -> JSON {
  return to_json<T>(value.cbegin(), value.cend(), callback);
}

// TODO: Try to elevate to Core?
template <typename T>
struct is_pair : std::false_type {};
template <typename L, typename R>
struct is_pair<std::pair<L, R>> : std::true_type {};

/// @ingroup json
template <typename L, typename R>
requires(is_pair<std::pair<L, R>>::value)
auto to_json(const std::pair<L, R> &value) -> JSON {
  auto tuple{JSON::make_array()};
  tuple.push_back(to_json<L>(value.first));
  tuple.push_back(to_json<R>(value.second));
  return tuple;
}

/// @ingroup json
template <typename... Args>
requires(!is_pair<std::tuple<Args...>>::value)
auto to_json(const std::tuple<Args...> &value) -> JSON {
  auto tuple{JSON::make_array()};
  std::apply(
      [&tuple](const Args &...elements) {
        (tuple.push_back(to_json(elements)), ...);
      },
      value);
  return tuple;
}

} // namespace sourcemeta::core

#endif
