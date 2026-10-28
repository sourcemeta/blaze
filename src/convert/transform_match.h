#ifndef SOURCEMETA_BLAZE_CONVERT_TRANSFORM_MATCH_H_
#define SOURCEMETA_BLAZE_CONVERT_TRANSFORM_MATCH_H_

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <algorithm>   // std::ranges::any_of
#include <cstddef>     // std::size_t
#include <string_view> // std::string_view
#include <utility>     // std::move
#include <vector>      // std::vector

namespace {

using namespace sourcemeta::core;

auto match_term(const JSON &pattern, const JSON &term, const Pointer &pointer,
                const TransformHost &host, TransformBindings &bindings) -> bool;

auto type_name(const JSON &term) -> std::string_view {
  switch (term.type()) {
    case JSON::Type::Object:
      return "object";
    case JSON::Type::Array:
      return "array";
    case JSON::Type::String:
      return "string";
    case JSON::Type::Integer:
    case JSON::Type::Real:
    case JSON::Type::Decimal:
      return "number";
    case JSON::Type::Boolean:
      return "boolean";
    case JSON::Type::Null:
      return "null";
  }

  return "null";
}

auto matches_type(const JSON &expected, const JSON &term) -> bool {
  const auto actual{type_name(term)};
  if (expected.is_string()) {
    return expected.to_string() == actual;
  }

  if (!expected.is_array()) {
    throw TransformError{"A type matcher takes a string or an array"};
  }

  return std::ranges::any_of(
      expected.as_array(), [&actual](const auto &candidate) -> bool {
        if (!candidate.is_string()) {
          throw TransformError{"A type matcher takes string entries"};
        }

        return candidate.to_string() == actual;
      });
}

auto matches_has(const JSON &expected, const JSON &term) -> bool {
  if (!term.is_object()) {
    return false;
  }

  if (expected.is_string()) {
    return term.defines(expected.to_string());
  }

  if (!expected.is_array()) {
    throw TransformError{"A has matcher takes a string or an array"};
  }

  for (const auto &candidate : expected.as_array()) {
    if (!candidate.is_string()) {
      throw TransformError{"A has matcher takes string entries"};
    }

    if (!term.defines(candidate.to_string())) {
      return false;
    }
  }

  return true;
}

auto matches_size(const JSON &expected, const JSON &term) -> bool {
  if (!expected.is_integer() || expected.to_integer() < 0) {
    throw TransformError{"A size matcher takes a non-negative integer"};
  }

  if (!term.is_object() && !term.is_array()) {
    return false;
  }

  return term.size() == static_cast<std::size_t>(expected.to_integer());
}

auto is_positive(const JSON &pattern) -> bool {
  for (const auto &entry : pattern.as_object()) {
    if (entry.first == "type" || entry.first == "const" ||
        entry.first == "enum" || entry.first == "has" ||
        entry.first == "size" || entry.first == "member" ||
        entry.first == "some-item" || entry.first == "some-member" ||
        entry.first == "call" || entry.first == "binding") {
      return true;
    }

    if (entry.first == "all" || entry.first == "any") {
      if (!entry.second.is_array()) {
        throw TransformError{"An all or any matcher takes an array"};
      }
    }

    if (entry.first == "all") {
      for (const auto &branch : entry.second.as_array()) {
        if (is_positive(branch)) {
          return true;
        }
      }
    }

    if (entry.first == "any") {
      auto every{!entry.second.empty()};
      for (const auto &branch : entry.second.as_array()) {
        every = every && is_positive(branch);
      }

      if (every) {
        return true;
      }
    }
  }

  return false;
}

auto match_all(const JSON &branches, const JSON &term, const Pointer &pointer,
               const TransformHost &host, TransformBindings &bindings) -> bool {
  if (!branches.is_array()) {
    throw TransformError{"An all matcher takes an array"};
  }

  for (const auto &branch : branches.as_array()) {
    if (!match_term(branch, term, pointer, host, bindings)) {
      return false;
    }
  }

  return true;
}

auto match_any(const JSON &branches, const JSON &term, const Pointer &pointer,
               const TransformHost &host, TransformBindings &bindings) -> bool {
  if (!branches.is_array()) {
    throw TransformError{"An any matcher takes an array"};
  }

  for (const auto &branch : branches.as_array()) {
    // A branch that fails must leave nothing behind, so each is tried against
    // a copy and only the branch that matched contributes its bindings
    auto candidate{bindings};
    if (match_term(branch, term, pointer, host, candidate)) {
      bindings = std::move(candidate);
      return true;
    }
  }

  return false;
}

auto match_member(const JSON &specification, const JSON &term,
                  const Pointer &pointer, const TransformHost &host,
                  TransformBindings &bindings) -> bool {
  if (!specification.is_object() || !specification.defines("key")) {
    throw TransformError{"A member matcher takes an object with a key"};
  }

  const auto &key{specification.at("key")};
  if (!key.is_string()) {
    throw TransformError{"A member matcher takes a string key"};
  }

  if (!term.is_object()) {
    return false;
  }

  const auto *value{term.try_at(key.to_string())};
  if (value == nullptr) {
    return false;
  }

  auto position{pointer};
  position.push_back(key.to_string());

  if (specification.defines("match") &&
      !match_term(specification.at("match"), *value, position, host,
                  bindings)) {
    return false;
  }

  if (specification.defines("bind")) {
    const auto &name{specification.at("bind")};
    if (!name.is_string()) {
      throw TransformError{"A bind takes a string name"};
    }

    bindings.insert_or_assign(
        name.to_string(),
        TransformBinding{.value = *value, .pointer = std::move(position)});
  }

  return true;
}

auto match_members(const JSON &pattern, const JSON &term,
                   const Pointer &pointer, const TransformHost &host,
                   TransformBindings &bindings) -> bool {
  if (!term.is_object()) {
    return false;
  }

  for (const auto &entry : term.as_object()) {
    auto position{pointer};
    position.push_back(entry.first);
    if (!match_term(pattern, entry.second, position, host, bindings)) {
      return false;
    }
  }

  return true;
}

/// Whether any member of an object satisfies a pattern on its name, its value,
/// or both. The counterpart of `some-item` for objects
auto match_some_member(const JSON &specification, const JSON &term,
                       const Pointer &pointer, const TransformHost &host,
                       TransformBindings &bindings) -> bool {
  if (!specification.is_object()) {
    throw TransformError{"A some-member matcher takes an object"};
  }

  if (!term.is_object()) {
    return false;
  }

  for (const auto &entry : term.as_object()) {
    auto position{pointer};
    position.push_back(entry.first);
    auto candidate{bindings};

    if (specification.defines("key") &&
        !match_term(specification.at("key"), JSON{entry.first}, position, host,
                    candidate)) {
      continue;
    }

    if (specification.defines("match") &&
        !match_term(specification.at("match"), entry.second, position, host,
                    candidate)) {
      continue;
    }

    if (specification.defines("bind")) {
      candidate.insert_or_assign(
          specification.at("bind").to_string(),
          TransformBinding{.value = entry.second, .pointer = position});
    }

    bindings = std::move(candidate);
    return true;
  }

  return false;
}

auto match_some_item(const JSON &pattern, const JSON &term,
                     const Pointer &pointer, const TransformHost &host,
                     TransformBindings &bindings) -> bool {
  if (!term.is_array()) {
    return false;
  }

  for (std::size_t index = 0; index < term.size(); index += 1) {
    auto position{pointer};
    position.push_back(index);
    auto candidate{bindings};
    if (match_term(pattern, term.at(index), position, host, candidate)) {
      bindings = std::move(candidate);
      return true;
    }
  }

  return false;
}

auto resolve_argument(const JSON &argument, const JSON &term,
                      const TransformBindings &bindings) -> JSON {
  if (!argument.is_string() || !argument.to_string().starts_with('$')) {
    return argument;
  }

  if (argument.to_string().starts_with("$$")) {
    return JSON{argument.to_string().substr(1)};
  }

  if (argument.to_string() == "$term") {
    return term;
  }

  const auto iterator{bindings.find(argument.to_string())};
  if (iterator == bindings.cend()) {
    throw TransformError{"An argument names a binding that was never bound"};
  }

  return iterator->second.value;
}

auto match_call(const JSON &specification, const JSON &term,
                const TransformBindings &bindings, const TransformHost &host)
    -> bool {
  if (!specification.is_object() || !specification.defines("name")) {
    throw TransformError{"A call takes an object with a name"};
  }

  const auto &name{specification.at("name")};
  if (!name.is_string()) {
    throw TransformError{"A call takes a string name"};
  }

  std::vector<JSON> arguments;
  if (specification.defines("args")) {
    const auto &declared{specification.at("args")};
    if (!declared.is_array()) {
      throw TransformError{"A call takes an array of arguments"};
    }

    arguments.reserve(declared.size());
    for (const auto &argument : declared.as_array()) {
      arguments.push_back(resolve_argument(argument, term, bindings));
    }
  }

  return host(name.to_string(), arguments) == JSON{true};
}

auto match_term(const JSON &pattern, const JSON &term, const Pointer &pointer,
                const TransformHost &host, TransformBindings &bindings)
    -> bool {
  if (!pattern.is_object()) {
    throw TransformError{"A pattern must be an object"};
  }

  if (pattern.empty()) {
    throw TransformError{"A pattern must declare at least one matcher"};
  }

  for (const auto &entry : pattern.as_object()) {
    if (entry.first == "type") {
      if (!matches_type(entry.second, term)) {
        return false;
      }
    } else if (entry.first == "const") {
      if (term != entry.second) {
        return false;
      }
    } else if (entry.first == "enum") {
      if (!entry.second.is_array()) {
        throw TransformError{"An enum matcher takes an array"};
      }

      auto found{false};
      for (const auto &candidate : entry.second.as_array()) {
        found = found || term == candidate;
      }

      if (!found) {
        return false;
      }
    } else if (entry.first == "has") {
      if (!matches_has(entry.second, term)) {
        return false;
      }
    } else if (entry.first == "size") {
      if (!matches_size(entry.second, term)) {
        return false;
      }
    } else if (entry.first == "empty") {
      if (!entry.second.is_boolean()) {
        throw TransformError{"An empty matcher takes a boolean"};
      }

      if (term.empty() != entry.second.to_boolean()) {
        return false;
      }
    } else if (entry.first == "all") {
      if (!match_all(entry.second, term, pointer, host, bindings)) {
        return false;
      }
    } else if (entry.first == "any") {
      if (!match_any(entry.second, term, pointer, host, bindings)) {
        return false;
      }
    } else if (entry.first == "not") {
      auto discarded{bindings};
      if (match_term(entry.second, term, pointer, host, discarded)) {
        return false;
      }
    } else if (entry.first == "member") {
      if (!match_member(entry.second, term, pointer, host, bindings)) {
        return false;
      }
    } else if (entry.first == "bind") {
      if (!entry.second.is_string()) {
        throw TransformError{"A bind takes a string name"};
      }

      bindings.insert_or_assign(
          entry.second.to_string(),
          TransformBinding{.value = term, .pointer = pointer});
    } else if (entry.first == "members") {
      if (!match_members(entry.second, term, pointer, host, bindings)) {
        return false;
      }
    } else if (entry.first == "some-member") {
      if (!match_some_member(entry.second, term, pointer, host, bindings)) {
        return false;
      }
    } else if (entry.first == "some-item") {
      if (!match_some_item(entry.second, term, pointer, host, bindings)) {
        return false;
      }
    } else if (entry.first == "call") {
      if (!match_call(entry.second, term, bindings, host)) {
        return false;
      }
    } else if (entry.first == "binding") {
      if (!entry.second.is_object() || !entry.second.defines("name") ||
          !entry.second.defines("match")) {
        throw TransformError{
            "A binding matcher takes an object with a name and a match"};
      }

      const auto iterator{bindings.find(entry.second.at("name").to_string())};
      if (iterator == bindings.cend()) {
        throw TransformError{"A binding matcher names one never bound"};
      }

      auto candidate{bindings};
      if (!match_term(entry.second.at("match"), iterator->second.value,
                      iterator->second.pointer, host, candidate)) {
        return false;
      }

      bindings = std::move(candidate);
    } else {
      throw TransformError{"Unknown matcher"};
    }
  }

  return true;
}

} // namespace

auto transform_match(const sourcemeta::core::JSON &pattern,
                     const sourcemeta::core::JSON &term,
                     const TransformHost &host, TransformBindings &bindings)
    -> bool {
  if (!pattern.is_object()) {
    throw TransformError{"A pattern must be an object"};
  }

  if (!is_positive(pattern)) {
    return false;
  }

  return match_term(pattern, term, sourcemeta::core::Pointer{}, host, bindings);
}

auto transform_guard(const sourcemeta::core::JSON &pattern,
                     const sourcemeta::core::JSON &term,
                     const TransformHost &host, TransformBindings &bindings)
    -> bool {
  return match_term(pattern, term, sourcemeta::core::Pointer{}, host, bindings);
}

#endif
