#include <sourcemeta/core/jose_sign.h>

#include <sourcemeta/core/crypto.h>

#include "jose_key.h"

#include <optional>    // std::optional, std::nullopt
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::unreachable

namespace sourcemeta::core {

auto jws_sign(const JWSAlgorithm algorithm,
              const std::string_view signing_input, const JWKPrivate &key)
    -> std::optional<std::string> {
  // A key that names an algorithm must not contradict the one in use (RFC 7517
  // Section 4.4)
  if (key.algorithm().has_value() && key.algorithm().value() != algorithm) {
    return std::nullopt;
  }

  // The key material is parsed into a reusable platform key when the key is
  // constructed, so an absent one is material that never formed a valid key
  const auto *private_key{key.private_key()};
  if (private_key == nullptr) {
    return std::nullopt;
  }

  switch (algorithm) {
    case JWSAlgorithm::RS256:
    case JWSAlgorithm::RS384:
    case JWSAlgorithm::RS512:
      if (key.type() != JWKPrivate::Type::RSA) {
        return std::nullopt;
      }

      return rsassa_pkcs1_v15_sign(*private_key, jws_hash_for(algorithm),
                                   signing_input);
    case JWSAlgorithm::PS256:
    case JWSAlgorithm::PS384:
    case JWSAlgorithm::PS512:
      if (key.type() != JWKPrivate::Type::RSA) {
        return std::nullopt;
      }

      return rsassa_pss_sign(*private_key, jws_hash_for(algorithm),
                             signing_input);
    // Each ECDSA algorithm is pinned to exactly one curve (RFC 7518 Section
    // 3.4). The raw signature width is twice the curve field width, so it pins
    // the key's curve to the algorithm, including for a key parsed from PEM
    // which carries no curve name
    case JWSAlgorithm::ES256:
    case JWSAlgorithm::ES384:
    case JWSAlgorithm::ES512: {
      if (key.type() != JWKPrivate::Type::EllipticCurve) {
        return std::nullopt;
      }

      auto signature{
          ecdsa_sign(*private_key, jws_hash_for(algorithm), signing_input)};
      if (!signature.has_value() ||
          signature.value().size() != jws_ecdsa_signature_bytes(algorithm)) {
        return std::nullopt;
      }

      return signature;
    }
    // The Edwards-curve algorithm names one of two curves through the key
    // rather than the algorithm (RFC 8037 Section 3.1), and the key fixes the
    // curve when it is parsed
    case JWSAlgorithm::EdDSA:
      if (key.type() != JWKPrivate::Type::OctetKeyPair) {
        return std::nullopt;
      }

      return eddsa_sign(*private_key, signing_input);
  }

  std::unreachable();
}

} // namespace sourcemeta::core
