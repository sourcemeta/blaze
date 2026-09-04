#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/blaze/editor.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/format.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/allocator.h>
#include <sourcemeta/core/json.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cerr

// Provided by the allocator that Blaze links into its consumers. Declared
// rather than included, as the allocator headers are an implementation detail
// that the installation must not expose
#if SOURCEMETA_CORE_ALLOCATOR_MIMALLOC
extern "C" auto mi_is_in_heap_region(const void *) -> bool;
#endif

auto main() -> int {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  const sourcemeta::core::JSON instance{"foo"};
  sourcemeta::blaze::Evaluator evaluator;
  if (!evaluator.validate(compiled_schema, instance)) {
    std::cerr << "JSON Schema validation failed\n";
    return EXIT_FAILURE;
  }

  auto editor_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};
  sourcemeta::blaze::for_editor(editor_schema, sourcemeta::blaze::schema_walker,
                                sourcemeta::blaze::schema_resolver);

  auto foundation_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/foundation"
  })JSON")};
  sourcemeta::blaze::SchemaFrame foundation_frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations, foundation_schema,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  auto bundle_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};
  sourcemeta::blaze::bundle(
      bundle_schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  auto format_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};
  sourcemeta::blaze::format(format_schema, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);

#if SOURCEMETA_CORE_ALLOCATOR_MIMALLOC
  // Linking the allocator in is not enough. It only does anything if it also
  // took over the standard allocation entry points that this program uses
  const auto *allocation{new int{1}};
  const auto allocator_took_over{mi_is_in_heap_region(allocation)};
  delete allocation;
  if (!allocator_took_over) {
    std::cerr << "The mimalloc allocator did not take over the program\n";
    return EXIT_FAILURE;
  }
#endif

  return EXIT_SUCCESS;
}
