#ifndef SOURCEMETA_CORE_JOSE_ALGORITHM_H_
#define SOURCEMETA_CORE_JOSE_ALGORITHM_H_

#ifndef SOURCEMETA_CORE_JOSE_EXPORT
#include <sourcemeta/core/jose_export.h>
#endif

#include <cstdint>     // std::uint8_t
#include <optional>    // std::optional
#include <string_view> // std::string_view

namespace sourcemeta::core {

/// @ingroup jose
/// The asymmetric JSON Web Signature algorithms from RFC 7518 Section 3.1 and
/// the Edwards-curve algorithm from RFC 8037 Section 3.1. The symmetric HMAC
/// family and the null algorithm are intentionally absent, which makes
/// algorithm confusion attacks unrepresentable in the type system.
enum class JWSAlgorithm : std::uint8_t {
  /// RSASSA-PKCS1-v1_5 using SHA-256.
  RS256,
  /// RSASSA-PKCS1-v1_5 using SHA-384.
  RS384,
  /// RSASSA-PKCS1-v1_5 using SHA-512.
  RS512,
  /// RSASSA-PSS using SHA-256 and MGF1 with SHA-256.
  PS256,
  /// RSASSA-PSS using SHA-384 and MGF1 with SHA-384.
  PS384,
  /// RSASSA-PSS using SHA-512 and MGF1 with SHA-512.
  PS512,
  /// ECDSA using the NIST P-256 curve and SHA-256.
  ES256,
  /// ECDSA using the NIST P-384 curve and SHA-384.
  ES384,
  /// ECDSA using the NIST P-521 curve and SHA-512.
  ES512,
  /// Edwards-curve Digital Signature Algorithm.
  EdDSA
};

/// @ingroup jose
/// Map a JSON Web Signature `alg` value to its algorithm, returning no value
/// for any unrecognized name. For example:
///
/// ```cpp
/// #include <sourcemeta/core/jose.h>
/// #include <cassert>
///
/// assert(sourcemeta::core::to_jws_algorithm("RS256").has_value());
/// assert(!sourcemeta::core::to_jws_algorithm("none").has_value());
/// ```
SOURCEMETA_CORE_JOSE_EXPORT
auto to_jws_algorithm(const std::string_view value) noexcept
    -> std::optional<JWSAlgorithm>;

} // namespace sourcemeta::core

#endif
