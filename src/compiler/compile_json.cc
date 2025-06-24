#include <sourcemeta/blaze/compiler.h>

namespace sourcemeta::blaze {
auto to_json(const Value &value) -> sourcemeta::core::JSON {
  return sourcemeta::core::to_json(value);
}
} // namespace sourcemeta::blaze
