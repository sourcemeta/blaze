#ifndef SOURCEMETA_CORE_OPENAPI_SERVER_H_
#define SOURCEMETA_CORE_OPENAPI_SERVER_H_

#include <sourcemeta/core/openapi.h>

#include "helpers.h"

#include <sourcemeta/core/text.h>
#include <sourcemeta/core/unicode.h>

#include <algorithm>   // std::ranges::any_of
#include <array>       // std::array
#include <cstddef>     // std::size_t
#include <set>         // std::set
#include <string_view> // std::string_view
#include <utility>     // std::move
#include <vector>      // std::vector

namespace sourcemeta::core {

constexpr auto OPENAPI_HASH_SERVER_VARIABLES{JSON::Object::hash("variables"sv)};
constexpr auto OPENAPI_HASH_SERVER_ENUM{JSON::Object::hash("enum"sv)};
constexpr auto OPENAPI_HASH_SERVER_DEFAULT{JSON::Object::hash("default"sv)};

constexpr std::array<JSON::StringView, 3> OPENAPI_SERVER_FIELDS_3_1{
    {"url"sv, "description"sv, "variables"sv}};

// OpenAPI Specification 3.2.1, Section 4.5 adds `name`
constexpr std::array<JSON::StringView, 4> OPENAPI_SERVER_FIELDS_3_2{
    {"url"sv, "description"sv, "variables"sv, "name"sv}};

constexpr std::array<JSON::StringView, 3> OPENAPI_SERVER_VARIABLE_FIELDS{
    {"enum"sv, "default"sv, "description"sv}};

// OpenAPI Specification 3.1.1, Section 4.8.6: "An object representing a Server
// Variable for server URL template substitution"
inline auto openapi_check_server_variable(const JSON &value,
                                          const Pointer &base,
                                          OpenAPIWalk &walk) -> void {
  openapi_record(walk, base, OpenAPIObjectKind::ServerVariable);
  if (!value.is_object()) {
    throw OpenAPIError{base, "The Server Variable Object must be an object"};
  }

  openapi_reject_unknown_fields(
      value, OPENAPI_SERVER_VARIABLE_FIELDS, base,
      "The Server Variable Object does not define this field");

  // OpenAPI Specification 3.1.1, Section 4.8.6: "enum | [string] | An
  // enumeration of string values to be used if the substitution options are
  // from a limited set. The array MUST NOT be empty"
  const auto *enumeration{value.try_at("enum", OPENAPI_HASH_SERVER_ENUM)};
  if (enumeration != nullptr) {
    if (!enumeration->is_array()) {
      throw OpenAPIError{
          openapi_child(base, "enum"sv),
          "The Server Variable Object enumeration must be an array"};
    }

    if (enumeration->empty()) {
      throw OpenAPIError{
          openapi_child(base, "enum"sv),
          "The Server Variable Object enumeration must not be empty"};
    }

    const auto enumeration_base{openapi_child(base, "enum"sv)};
    std::size_t index{0};
    for (const auto &option : enumeration->as_array()) {
      if (!option.is_string()) {
        throw OpenAPIError{
            openapi_child(enumeration_base, index),
            "The Server Variable Object enumeration must only hold strings"};
      }

      index += 1;
    }
  }

  // OpenAPI Specification 3.1.1, Section 4.8.6: "default | string | REQUIRED.
  // The default value to use for substitution"
  const auto *fallback{value.try_at("default", OPENAPI_HASH_SERVER_DEFAULT)};
  if (fallback == nullptr) {
    throw OpenAPIError{base,
                       "The Server Variable Object must declare a default"};
  }

  const auto default_value{openapi_expect_string(
      *fallback, base, "default"sv,
      "The Server Variable Object default must be a string")};

  const auto *description{
      value.try_at("description", OPENAPI_HASH_DESCRIPTION)};
  if (description != nullptr) {
    openapi_expect_string(
        *description, base, "description"sv,
        "The Server Variable Object description must be a string");
  }

  // OpenAPI Specification 3.1.1, Section 4.8.6: "If the `enum` is defined, the
  // value MUST exist in the enum's values". The published meta-schema does not
  // check this, and the fixture the OpenAPI Initiative ships for an empty
  // enumeration says so in a comment, so the prose is what this follows
  if (enumeration != nullptr &&
      !std::ranges::any_of(enumeration->as_array(),
                           [default_value](const JSON &option) -> bool {
                             return option.to_string() == default_value;
                           })) {
    throw OpenAPIError{
        openapi_child(base, "default"sv),
        "The Server Variable Object default must exist in its enumeration"};
  }
}

// The `literals` of a server URL template, which OpenAPI Specification 3.2.1,
// Section 4.6 takes from RFC 6570 "incorporating the corrections specified in
// Errata 6937":
//
//     literals = 1*( %x21 / %x23-24 / %x26-3B / %x3D / %x3F-5B
//                / %x5D / %x5F / %x61-7A / %x7E / ucschar / iprivate
//                / pct-encoded)
//
// The two productions it names beyond that range are the ones RFC 3987
// Section 2.2 defines, and a `pct-encoded` triplet is read where a run of them
// is
inline auto openapi_is_server_url_literal(const char32_t point) -> bool {
  if (point < 0x80) {
    return point == 0x21 || (point >= 0x23 && point <= 0x24) ||
           (point >= 0x26 && point <= 0x3B) || point == 0x3D ||
           (point >= 0x3F && point <= 0x5B) || point == 0x5D || point == 0x5F ||
           (point >= 0x61 && point <= 0x7A) || point == 0x7E;
  }

  return is_ucschar(point) || is_iprivate(point);
}

// OpenAPI Specification 3.2.1, Section 4.6 states the grammar 3.1 left
// unwritten:
//
//     server-url-template  = 1*( literals / server-variable )
//     server-variable      = "{" server-variable-name "}"
//     server-variable-name = 1*( %x00-7A / %x7C / %x7E-10FFFF )
//
// A variable name admits "every Unicode character except { and }", which of
// the bytes of one holds only of a brace, so it is read byte by byte while a
// literal is read a character at a time
inline auto openapi_is_server_url_template(const JSON::StringView address)
    -> bool {
  if (address.empty()) {
    return false;
  }

  std::size_t cursor{0};
  while (cursor < address.size()) {
    if (address[cursor] == '{') {
      const auto close{address.find('}', cursor + 1)};
      if (close == JSON::StringView::npos || close == cursor + 1 ||
          address.substr(cursor + 1, close - cursor - 1).find('{') !=
              JSON::StringView::npos) {
        return false;
      }

      cursor = close + 1;
    } else if (address[cursor] == '%') {
      if (cursor + 2 >= address.size() || !is_hex_digit(address[cursor + 1]) ||
          !is_hex_digit(address[cursor + 2])) {
        return false;
      }

      cursor += 3;
    } else {
      const auto character{utf8_decode(address, cursor)};
      if (!character.has_value() ||
          !openapi_is_server_url_literal(character.value().first)) {
        return false;
      }

      cursor += character.value().second;
    }
  }

  return true;
}

// The variables a server URL template names, which are unambiguous once the
// grammar above has held
inline auto openapi_server_url_variables(const JSON::StringView address)
    -> std::vector<JSON::StringView> {
  std::vector<JSON::StringView> result;
  std::size_t cursor{0};
  while (cursor < address.size()) {
    const auto open{address.find('{', cursor)};
    if (open == JSON::StringView::npos) {
      break;
    }

    const auto close{address.find('}', open)};
    if (close == JSON::StringView::npos) {
      break;
    }

    result.push_back(address.substr(open + 1, close - open - 1));
    cursor = close + 1;
  }

  return result;
}

// OpenAPI Specification 3.1.1, Section 4.8.5: "An object representing a Server"
inline auto openapi_check_server(const JSON &value, const Pointer &base,
                                 OpenAPIWalk &walk) -> void {
  openapi_record(walk, base, OpenAPIObjectKind::Server);
  if (!value.is_object()) {
    throw OpenAPIError{base, "The Server Object must be an object"};
  }

  openapi_reject_unknown_fields(
      value, OPENAPI_SERVER_FIELDS_3_1, OPENAPI_SERVER_FIELDS_3_2, base,
      "The Server Object does not define this field", walk);

  // OpenAPI Specification 3.1.1, Section 4.8.5: "url | string | REQUIRED. A
  // URL to the target host. This URL supports Server Variables and MAY be
  // relative". Beyond its type there is little to check, as it is a template
  // rather than a URL once a variable is named in braces
  const auto *url{value.try_at("url", OPENAPI_HASH_URL)};
  if (url == nullptr) {
    throw OpenAPIError{base, "The Server Object must declare a URL"};
  }

  const auto address{openapi_expect_string(
      *url, base, "url"sv, "The Server Object URL must be a string")};

  // OpenAPI Specification 3.1.2, Section 4.8.5 adds to that row: "Query and
  // fragment MUST NOT be part of this URL". A query begins at the first `?`
  // and a fragment at the first `#`, so either character in the template
  // starts one, whether or not it sits inside a variable expression. A
  // percent-encoded one is neither and is left alone
  if (address.find('?') != JSON::StringView::npos ||
      address.find('#') != JSON::StringView::npos) {
    throw OpenAPIError{
        openapi_child(base, "url"sv),
        "The Server Object URL must carry no query and no fragment"};
  }

  // 3.1 says nothing more about the shape of the template, while Section 4.6
  // of 3.2 writes out a grammar for it and forbids repeating a variable:
  // "Each server variable MUST NOT appear more than once in the URL template".
  // Both are new in 3.2, so a URL 3.1 accepts is still accepted when a
  // document declares 3.1
  if (walk.version == OpenAPIVersion::OPENAPI_3_2) {
    if (!openapi_is_server_url_template(address)) {
      throw OpenAPIError{openapi_child(base, "url"sv),
                         "The Server Object URL must take the form of a "
                         "server URL template"};
    }

    std::set<JSON::StringView> names;
    for (const auto &variable : openapi_server_url_variables(address)) {
      if (!names.insert(variable).second) {
        throw OpenAPIError{openapi_child(base, "url"sv),
                           "A server URL template must not repeat a variable"};
      }
    }
  }

  const auto *description{
      value.try_at("description", OPENAPI_HASH_DESCRIPTION)};
  if (description != nullptr) {
    openapi_expect_string(*description, base, "description"sv,
                          "The Server Object description must be a string");
  }

  // OpenAPI Specification 3.2.1, Section 4.5: "name | string"
  const auto *name{value.try_at("name", OPENAPI_HASH_NAME)};
  if (name != nullptr) {
    openapi_expect_string(*name, base, "name"sv,
                          "The Server Object name must be a string");
  }

  // OpenAPI Specification 3.1.1, Section 4.8.5: "variables | Map[string,
  // Server Variable Object] | A map between a variable name and its value"
  const auto *variables{
      value.try_at("variables", OPENAPI_HASH_SERVER_VARIABLES)};
  if (variables != nullptr) {
    if (!variables->is_object()) {
      throw OpenAPIError{openapi_child(base, "variables"sv),
                         "The Server Object variables must be an object"};
    }

    const auto variables_base{openapi_child(base, "variables"sv)};
    for (const auto &entry : variables->as_object()) {
      openapi_check_server_variable(
          entry.second, openapi_child(variables_base, entry.first), walk);
    }
  }
}

// The three Objects that may declare servers do so the same way. What comes
// back is where each Server Object was recorded, which is how an operation
// names the servers in force where it sits without repeating them
inline auto openapi_check_server_array(const JSON &value, const Pointer &base,
                                       const char *message, OpenAPIWalk &walk)
    -> std::vector<JSON::String> {
  openapi_expect_array(value, base, message);
  std::vector<JSON::String> result;
  result.reserve(value.size());
  std::size_t index{0};
  for (const auto &server : value.as_array()) {
    const auto location{openapi_child(base, index)};
    openapi_check_server(server, location, walk);
    result.push_back(openapi_location_uri(walk.base, location));
    index += 1;
  }

  return result;
}

// OpenAPI Specification 3.1.1, Section 4.8.1: "servers | [Server Object] | An
// array of Server Objects, which provide connectivity information to a target
// server". An absent or empty array is legal, as the same row states that both
// stand for a single server whose URL is a slash
inline auto openapi_check_servers(const JSON &document, OpenAPIWalk &walk)
    -> void {
  const auto *servers{document.try_at("servers", OPENAPI_HASH_SERVERS)};
  if (servers == nullptr) {
    return;
  }

  auto locations{openapi_check_server_array(
      *servers, Pointer{"servers"},
      "The OpenAPI Description servers must be an array", walk)};

  // Section 4.3.3: "only the entry document's Paths Object contributes URLs to
  // the described API", which makes the entry document's servers the deployment
  // information that every operation falls back on
  if (walk.entry) {
    walk.servers = std::move(locations);
  }
}

} // namespace sourcemeta::core

#endif
