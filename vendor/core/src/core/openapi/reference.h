#ifndef SOURCEMETA_CORE_OPENAPI_REFERENCE_H_
#define SOURCEMETA_CORE_OPENAPI_REFERENCE_H_

#include <sourcemeta/core/openapi.h>

#include "helpers.h"

#include <string_view> // std::string_view

namespace sourcemeta::core {

constexpr auto OPENAPI_HASH_REF{JSON::Object::hash("$ref"sv)};

// OpenAPI Specification 3.1.1, Section 4.8.23: "A simple object to allow
// referencing other components in the OpenAPI Description"
inline auto openapi_check_reference(const JSON &value, const Pointer &base,
                                    const OpenAPIObjectKind expected,
                                    OpenAPIWalk &walk) -> void {
  openapi_record(walk, base, OpenAPIObjectKind::Reference);
  // OpenAPI Specification 3.1.1, Section 4.8.23: "$ref | string | REQUIRED.
  // The reference identifier. This MUST be in the form of a URI"
  const auto *target{value.try_at("$ref", OPENAPI_HASH_REF)};
  const auto reference{openapi_expect_uri_reference(
      *target, base, "$ref"sv,
      "The Reference Object identifier must be a "
      "string",
      "The Reference Object identifier must be a URI reference")};

  const auto *summary{value.try_at("summary", OPENAPI_HASH_SUMMARY)};
  if (summary != nullptr) {
    openapi_expect_string(*summary, base, "summary"sv,
                          "The Reference Object summary must be a string");
  }

  const auto *description{
      value.try_at("description", OPENAPI_HASH_DESCRIPTION)};
  if (description != nullptr) {
    openapi_expect_string(*description, base, "description"sv,
                          "The Reference Object description must be a string");
  }

  // OpenAPI Specification 3.1.1, Section 4.8.23: "This object cannot be
  // extended with additional properties, and any properties added SHALL be
  // ignored". Ignoring is what the specification asks for, so no member beyond
  // the three above is read and none is turned down either

  // Following comes last, so that what is wrong with this Object is reported
  // before whatever may be wrong at the far end of it
  openapi_follow_reference(reference, openapi_child(base, "$ref"sv), expected,
                           walk);
}

// A Reference Object stands in for most of the Objects the Components Object
// holds, and the meta-schema tells the two apart by whether `$ref` is present
inline auto openapi_is_reference(const JSON &value) -> bool {
  return value.is_object() && value.try_at("$ref", OPENAPI_HASH_REF) != nullptr;
}

} // namespace sourcemeta::core

#endif
