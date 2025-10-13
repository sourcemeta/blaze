#include <uriparser/Uri.h>

#include <cctype>   // std::isalnum
#include <cstdint>  // std::uint8_t
#include <istream>  // std::istream
#include <iterator> // std::istream_iterator
#include <ostream>  // std::ostream
#include <string>   // std::string

namespace sourcemeta::core {

enum class URIEscapeMode : std::uint8_t {
  // Escape every characted that is not in the URI "unreserved" ABNF category
  // See https://www.rfc-editor.org/rfc/rfc3986#appendix-A
  SkipUnreserved,
  // Escape every characted that is not in either the URI "unreserved" nor
  // "sub-delims" ABNF categories
  // See https://www.rfc-editor.org/rfc/rfc3986#appendix-A
  SkipSubDelims,
  // Escape every characted that is not in either the URI "fragment" category
  //
  // unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
  // pct-encoded = "%" HEXDIG HEXDIG
  // sub-delims  = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" /
  // "="
  // pchar       = unreserved / pct-encoded / sub-delims / ":" / "@"
  // fragment    = *( pchar / "/" / "?" )
  //
  // See https://www.rfc-editor.org/rfc/rfc3986#appendix-A
  Fragment,
  // Like SkipSubDelims but also preserves ":" for Windows filesystem paths
  // (drive letters like C:)
  Filesystem
};

inline auto uri_escape(std::istream &input, std::ostream &output,
                       const URIEscapeMode mode) -> void {
  char character = 0;
  while (input.get(character)) {
    // Check if this is an already percent-encoded sequence (%HEX HEX)
    // If so, preserve it as-is to avoid double-encoding
    if (character == '%') {
      const auto position = input.tellg();
      char next_1 = 0;
      char next_2 = 0;

      if (input.get(next_1) && input.get(next_2) &&
          std::isxdigit(static_cast<unsigned char>(next_1)) &&
          std::isxdigit(static_cast<unsigned char>(next_2))) {
        // Valid percent-encoded sequence - preserve it
        output << character << next_1 << next_2;
        continue;
      }

      // Not a valid percent-encoded sequence - restore position and escape %
      input.seekg(position);
    }

    // unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
    // See https://www.rfc-editor.org/rfc/rfc3986#appendix-A
    if (std::isalnum(static_cast<unsigned char>(character)) ||
        character == '-' || character == '.' || character == '_' ||
        character == '~') {
      output << character;
      continue;
    }

    if (mode == URIEscapeMode::SkipSubDelims ||
        mode == URIEscapeMode::Fragment || mode == URIEscapeMode::Filesystem) {
      // sub-delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";"
      // / "="
      // See https://www.rfc-editor.org/rfc/rfc3986#appendix-A
      if (character == '!' || character == '$' || character == '&' ||
          character == '\'' || character == '(' || character == ')' ||
          character == '*' || character == '+' || character == ',' ||
          character == ';' || character == '=') {
        output << character;
        continue;
      }
    }

    if (mode == URIEscapeMode::Fragment) {
      // See https://www.rfc-editor.org/rfc/rfc3986#appendix-A
      // pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
      // fragment = *( pchar / "/" / "?" )
      if (character == ':' || character == '@' || character == '/' ||
          character == '?') {
        output << character;
        continue;
      }
    }

    if (mode == URIEscapeMode::Filesystem) {
      // Preserve ":" for Windows drive letters (e.g., C:)
      if (character == ':') {
        output << character;
        continue;
      }
    }

    // Percent encode this character
    output << '%' << std::hex << std::uppercase
           << +(static_cast<unsigned char>(character));
  }

  // Reset stream format flags
  output << std::dec << std::nouppercase;
}

inline auto uri_unescape(std::istream &input, std::ostream &output) -> void {
  std::istream_iterator<char> iterator(input);
  std::istream_iterator<char> end;
  auto plus_1 = std::ranges::next(iterator, 1, end);
  auto plus_2 = std::ranges::next(plus_1, 1, end);
  const int hex_base = 16;

  while (iterator != end) {
    if (*iterator == '%' && plus_1 != end && plus_2 != end &&
        std::isxdigit(*(plus_1)) && std::isxdigit(*(plus_2))) {
      std::string hex{*plus_1, *plus_2};
      char decoded_char = static_cast<char>(std::stoi(hex, nullptr, hex_base));
      output << decoded_char;

      iterator = std::ranges::next(plus_2, 1, end);
      plus_1 = std::ranges::next(iterator, 1, end);
      plus_2 = std::ranges::next(plus_1, 1, end);
    } else {
      output << *iterator;
      iterator = plus_1;
      plus_1 = plus_2;
      plus_2 = std::ranges::next(plus_1, 1, end);
    }
  }
}

// Selective unescaping for URI normalization
// Only unescapes unreserved characters, keeps reserved characters encoded
// but normalizes hex digits to uppercase
// unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
inline auto uri_unescape_selective(std::string_view input,
                                   bool allow_colon_at = false) -> std::string {
  std::string result;
  result.reserve(input.size());

  for (std::string::size_type i = 0; i < input.size(); ++i) {
    if (input[i] == '%' && i + 2 < input.size() &&
        std::isxdigit(static_cast<unsigned char>(input[i + 1])) &&
        std::isxdigit(static_cast<unsigned char>(input[i + 2]))) {
      // Parse the hex value
      std::string hex{input[i + 1], input[i + 2]};
      const auto value =
          static_cast<unsigned char>(std::stoi(hex, nullptr, 16));

      // Decode unreserved characters: ALPHA / DIGIT / "-" / "." / "_" / "~"
      // For URNs/tags, also decode ":" and "@"
      const bool is_unreserved = std::isalnum(value) || value == '-' ||
                                 value == '.' || value == '_' || value == '~';
      const bool is_urn_allowed =
          allow_colon_at && (value == ':' || value == '@');

      if (is_unreserved || is_urn_allowed) {
        result += static_cast<char>(value);
        i += 2; // Skip the two hex digits
      } else {
        // Keep it percent-encoded (but normalize to uppercase hex)
        result += '%';
        result += static_cast<char>(
            std::toupper(static_cast<unsigned char>(input[i + 1])));
        result += static_cast<char>(
            std::toupper(static_cast<unsigned char>(input[i + 2])));
        i += 2;
      }
    } else {
      result += input[i];
    }
  }

  return result;
}

} // namespace sourcemeta::core
