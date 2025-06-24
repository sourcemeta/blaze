#ifndef SOURCEMETA_BLAZE_COMPILER_COMPILE_H_
#define SOURCEMETA_BLAZE_COMPILER_COMPILE_H_

#include <sourcemeta/core/json.h>

#include <utility>

namespace sourcemeta::blaze {

using ValueType = sourcemeta::core::JSON::Type;
using Value = std::pair<ValueType, std::pair<ValueType, std::size_t>>;

auto to_json(const Value &value) -> sourcemeta::core::JSON;
} // namespace sourcemeta::blaze

#endif
