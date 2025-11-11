#ifndef SOURCEMETA_BLAZE_COMPILER_VOCABULARY_LOOKUP_H_
#define SOURCEMETA_BLAZE_COMPILER_VOCABULARY_LOOKUP_H_

#include <sourcemeta/core/jsonschema.h>

#include <string_view> // std::string_view

namespace sourcemeta::blaze {

// Optimized vocabulary lookup using bitwise operations
// This directly uses the Vocabularies::contains() method which performs
// O(1) bitwise AND operations for known vocabularies
inline auto has_vocabulary(const sourcemeta::core::Vocabularies &vocabularies,
                           std::string_view uri) -> bool {
  return vocabularies.contains(uri);
}

} // namespace sourcemeta::blaze

#endif
