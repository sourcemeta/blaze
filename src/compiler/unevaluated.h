#ifndef SOURCEMETA_BLAZE_COMPILER_UNEVALUATED_H_
#define SOURCEMETA_BLAZE_COMPILER_UNEVALUATED_H_

#include <sourcemeta/blaze/compiler.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

// TODO: Eventually this file should dissapear and move this analysis as part of
// framing

namespace sourcemeta::blaze {

// This function performs a static analysis pass on `unevaluatedProperties` and
// `unevaluatedItems` occurences throughout the entire schema (if any).
auto unevaluated(const sourcemeta::core::JSON &schema,
                 const sourcemeta::core::SchemaFrame &frame,
                 const sourcemeta::core::SchemaWalker &walker,
                 const sourcemeta::core::SchemaResolver &resolver)
    -> SchemaUnevaluatedEntries;

} // namespace sourcemeta::blaze

#endif
