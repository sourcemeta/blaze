#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/blaze/editor.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/format.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cerr

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
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  foundation_frame.analyse(foundation_schema, sourcemeta::blaze::schema_walker,
                           sourcemeta::blaze::schema_resolver);

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

  return EXIT_SUCCESS;
}
