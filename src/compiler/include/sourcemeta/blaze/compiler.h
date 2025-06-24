#ifndef SOURCEMETA_BLAZE_COMPILER_COMPILE_H_
#define SOURCEMETA_BLAZE_COMPILER_COMPILE_H_

#include <sourcemeta/core/json.h>

#include <vector>      // std::vector
#include <utility>       // std::pair

namespace sourcemeta::blaze {

using ValueType = sourcemeta::core::JSON::Type;
using ValueIndexPair = std::pair<std::size_t, std::size_t>;
using ValueStringHashes = std::pair<ValueType, std::vector<ValueIndexPair>>;
using ValueTypedHashes = std::pair<ValueType, ValueStringHashes>;

using Value = std::variant<ValueTypedHashes>;

struct Instruction {
  const Value value;
};

auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON;
} // namespace sourcemeta::blaze

#endif
