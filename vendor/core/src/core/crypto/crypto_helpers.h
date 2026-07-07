#ifndef SOURCEMETA_CORE_CRYPTO_HELPERS_H_
#define SOURCEMETA_CORE_CRYPTO_HELPERS_H_

#include <sourcemeta/core/crypto_sha256.h>
#include <sourcemeta/core/crypto_sha384.h>
#include <sourcemeta/core/crypto_sha512.h>
#include <sourcemeta/core/crypto_verify.h>
#include <sourcemeta/core/text.h>

#include <cstddef>     // std::size_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::unreachable

namespace sourcemeta::core {

// The largest RSA key any backend accepts, so that every backend agrees on
// the range of valid key sizes
inline constexpr std::size_t MAXIMUM_KEY_BYTES{512};

// Overwrite a buffer that held secret material so it does not linger in freed
// memory. The volatile access stops the compiler from eliding the write as a
// dead store
inline auto secure_zero(void *const data, const std::size_t size) noexcept
    -> void {
  if (data == nullptr) {
    return;
  }

  auto *pointer{static_cast<volatile unsigned char *>(data)};
  for (std::size_t index{0}; index < size; index += 1) {
    pointer[index] = 0;
  }
}

inline auto secure_zero(std::string &value) noexcept -> void {
  secure_zero(value.data(), value.size());
}

// Overwrite the referenced buffer when leaving the current scope, so secret
// material a local holds is wiped across every return path without threading a
// manual call through each one
struct SecureScope {
  explicit SecureScope(std::string &value) noexcept : target{value} {}
  SecureScope(const SecureScope &) = delete;
  auto operator=(const SecureScope &) -> SecureScope & = delete;
  SecureScope(SecureScope &&) = delete;
  auto operator=(SecureScope &&) -> SecureScope & = delete;
  ~SecureScope() { secure_zero(this->target); }
  std::string &target;
};

// Whether a signature representative, as a big-endian integer, is strictly
// less than the modulus. RFC 8017 Section 5.2.2 requires this range check, so
// that an unreduced signature, which an attacker forges by adding the modulus
// without changing the modular exponentiation result, is rejected
inline auto rsa_signature_in_range(const std::string_view signature,
                                   const std::string_view modulus) noexcept
    -> bool {
  const auto value{strip_left(signature, '\x00')};
  const auto bound{strip_left(modulus, '\x00')};
  if (value.size() != bound.size()) {
    return value.size() < bound.size();
  }

  return value < bound;
}

inline auto curve_field_bytes(const EllipticCurve curve) noexcept
    -> std::size_t {
  switch (curve) {
    case EllipticCurve::P256:
      return 32;
    case EllipticCurve::P384:
      return 48;
    case EllipticCurve::P521:
      return 66;
  }

  std::unreachable();
}

// The public key and signature octet lengths are fixed per curve (RFC 8032
// Section 5.1.2 and Section 5.1.6)
inline auto eddsa_public_key_bytes(const EdwardsCurve curve) noexcept
    -> std::size_t {
  switch (curve) {
    case EdwardsCurve::Ed25519:
      return 32;
    case EdwardsCurve::Ed448:
      return 57;
  }

  std::unreachable();
}

inline auto eddsa_signature_bytes(const EdwardsCurve curve) noexcept
    -> std::size_t {
  switch (curve) {
    case EdwardsCurve::Ed25519:
      return 64;
    case EdwardsCurve::Ed448:
      return 114;
  }

  std::unreachable();
}

inline auto digest_message(const SignatureHashFunction hash,
                           const std::string_view message) -> std::string {
  switch (hash) {
    case SignatureHashFunction::SHA256: {
      const auto digest{sha256_digest(message)};
      return {reinterpret_cast<const char *>(digest.data()), digest.size()};
    }
    case SignatureHashFunction::SHA384: {
      const auto digest{sha384_digest(message)};
      return {reinterpret_cast<const char *>(digest.data()), digest.size()};
    }
    case SignatureHashFunction::SHA512: {
      const auto digest{sha512_digest(message)};
      return {reinterpret_cast<const char *>(digest.data()), digest.size()};
    }
  }

  std::unreachable();
}

} // namespace sourcemeta::core

#endif
