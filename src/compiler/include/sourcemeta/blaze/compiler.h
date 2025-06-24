#ifndef SOURCEMETA_BLAZE_COMPILER_COMPILE_H_
#define SOURCEMETA_BLAZE_COMPILER_COMPILE_H_

#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/core/json.h>

namespace sourcemeta::blaze {
auto to_json(const Instruction &instruction) -> sourcemeta::core::JSON;
auto to_json(const Template &schema_template) -> sourcemeta::core::JSON;
} // namespace sourcemeta::blaze

#endif
