#include <sourcemeta/core/crypto.h>
#include <sourcemeta/core/http_aws_sigv4.h>
#include <sourcemeta/core/text.h>
#include <sourcemeta/core/uri.h>

#include "helpers.h"

#include <algorithm>   // std::sort, std::stable_sort
#include <array>       // std::array
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint8_t
#include <span>        // std::span
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::pair, std::move
#include <vector>      // std::vector

namespace {

auto digest_view(const std::array<std::uint8_t, 32> &bytes)
    -> std::string_view {
  return {reinterpret_cast<const char *>(bytes.data()), bytes.size()};
}

auto sorted_headers(
    const std::span<const std::pair<std::string_view, std::string_view>>
        headers) -> std::vector<std::pair<std::string_view, std::string_view>> {
  std::vector<std::pair<std::string_view, std::string_view>> entries;
  entries.reserve(headers.size());
  for (const auto &[name, value] : headers) {
    entries.emplace_back(name,
                         sourcemeta::core::http_trim_trailing_ows(
                             sourcemeta::core::http_trim_leading_ows(value)));
  }

  std::ranges::stable_sort(
      entries, sourcemeta::core::less_ignore_case,
      &std::pair<std::string_view, std::string_view>::first);
  return entries;
}

auto append_lowercased(std::string &output, const std::string_view name)
    -> void {
  for (const auto character : name) {
    output.push_back(sourcemeta::core::to_lowercase(character));
  }
}

auto append_canonical_headers(
    std::string &output,
    const std::vector<std::pair<std::string_view, std::string_view>> &entries)
    -> void {
  std::size_t index{0};
  while (index < entries.size()) {
    const auto name{entries[index].first};
    append_lowercased(output, name);
    output.push_back(':');
    bool first{true};
    while (index < entries.size() &&
           sourcemeta::core::equals_ignore_case(entries[index].first, name)) {
      if (!first) {
        output.push_back(',');
      }

      sourcemeta::core::squeeze(entries[index].second, ' ', output);
      first = false;
      ++index;
    }

    output.push_back('\n');
  }
}

auto append_signed_headers(
    std::string &output,
    const std::vector<std::pair<std::string_view, std::string_view>> &entries)
    -> void {
  std::string_view previous;
  bool first{true};
  for (const auto &[name, value] : entries) {
    if (!first && sourcemeta::core::equals_ignore_case(name, previous)) {
      continue;
    }

    if (!first) {
      output.push_back(';');
    }

    append_lowercased(output, name);
    previous = name;
    first = false;
  }
}

auto append_canonical_uri(std::string &output, std::string_view path,
                          const bool normalize) -> void {
  std::string normalized;
  if (normalize) {
    // Beyond RFC 3986 dot-segment removal, the default canonicalization also
    // collapses redundant slashes, which Amazon S3 does not
    normalized = sourcemeta::core::URI::normalize_path(
        sourcemeta::core::squeeze(path, '/'));
    path = normalized;
  }

  if (path.empty()) {
    output.push_back('/');
    return;
  }

  std::size_t start{0};
  while (true) {
    const auto slash{path.find('/', start)};
    if (slash == std::string_view::npos) {
      sourcemeta::core::URI::escape(path.substr(start), output);
      break;
    }

    sourcemeta::core::URI::escape(path.substr(start, slash - start), output);
    output.push_back('/');
    start = slash + 1;
  }
}

auto append_canonical_query(std::string &output, const std::string_view query)
    -> void {
  if (query.empty()) {
    return;
  }

  std::vector<std::pair<std::string, std::string>> parameters;
  for (const auto &[name, value] : sourcemeta::core::URI::Query{query}) {
    std::string encoded_name;
    std::string encoded_value;
    sourcemeta::core::URI::escape(name, encoded_name);
    sourcemeta::core::URI::escape(value, encoded_value);
    parameters.emplace_back(std::move(encoded_name), std::move(encoded_value));
  }

  std::ranges::sort(parameters);
  bool first{true};
  for (const auto &[key, value] : parameters) {
    if (!first) {
      output.push_back('&');
    }

    output.append(key);
    output.push_back('=');
    output.append(value);
    first = false;
  }
}

} // namespace

namespace sourcemeta::core {

auto http_aws_sigv4_canonical_request(
    const std::string_view method, const std::string_view path,
    const std::string_view query,
    const std::span<const std::pair<std::string_view, std::string_view>>
        headers,
    const std::string_view payload_hash, const bool normalize) -> std::string {
  const auto entries{sorted_headers(headers)};
  std::string result;
  result.append(method);
  result.push_back('\n');
  append_canonical_uri(result, path, normalize);
  result.push_back('\n');
  append_canonical_query(result, query);
  result.push_back('\n');
  append_canonical_headers(result, entries);
  result.push_back('\n');
  append_signed_headers(result, entries);
  result.push_back('\n');
  result.append(payload_hash);
  return result;
}

auto http_aws_sigv4_signed_headers(
    const std::span<const std::pair<std::string_view, std::string_view>>
        headers) -> std::string {
  std::string result;
  append_signed_headers(result, sorted_headers(headers));
  return result;
}

auto http_aws_sigv4_credential_scope(const std::string_view date,
                                     const std::string_view region,
                                     const std::string_view service)
    -> std::string {
  std::string result;
  result.append(date);
  result.push_back('/');
  result.append(region);
  result.push_back('/');
  result.append(service);
  result.append("/aws4_request");
  return result;
}

auto http_aws_sigv4_string_to_sign(const std::string_view amz_date,
                                   const std::string_view scope,
                                   const std::string_view canonical_request)
    -> std::string {
  std::string result{"AWS4-HMAC-SHA256\n"};
  result.append(amz_date);
  result.push_back('\n');
  result.append(scope);
  result.push_back('\n');
  result.append(sha256(canonical_request));
  return result;
}

auto http_aws_sigv4_signing_key(const std::string_view secret,
                                const std::string_view date,
                                const std::string_view region,
                                const std::string_view service)
    -> std::array<std::uint8_t, 32> {
  std::string initial{"AWS4"};
  initial.append(secret);
  const auto key_date{hmac_sha256_digest(initial, date)};
  const auto key_region{hmac_sha256_digest(digest_view(key_date), region)};
  const auto key_service{hmac_sha256_digest(digest_view(key_region), service)};
  return hmac_sha256_digest(digest_view(key_service), "aws4_request");
}

auto http_aws_sigv4_signature(const std::array<std::uint8_t, 32> &signing_key,
                              const std::string_view string_to_sign)
    -> std::string {
  return hmac_sha256(digest_view(signing_key), string_to_sign);
}

auto http_aws_sigv4_authorization(const std::string_view access_key_id,
                                  const std::string_view scope,
                                  const std::string_view signed_headers,
                                  const std::string_view signature)
    -> std::string {
  std::string result{"AWS4-HMAC-SHA256 Credential="};
  result.append(access_key_id);
  result.push_back('/');
  result.append(scope);
  result.append(", SignedHeaders=");
  result.append(signed_headers);
  result.append(", Signature=");
  result.append(signature);
  return result;
}

} // namespace sourcemeta::core
