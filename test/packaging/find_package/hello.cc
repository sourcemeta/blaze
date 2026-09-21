#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/configuration.h>
#include <sourcemeta/blaze/convert.h>
#include <sourcemeta/blaze/dependencies.h>
#include <sourcemeta/blaze/editor.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cerr

auto main() -> int {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto compiled_schema{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
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
  sourcemeta::blaze::for_editor(editor_schema, sourcemeta::core::schema_walker,
                                sourcemeta::core::schema_resolver);

  auto frame_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/frame"
  })JSON")};
  sourcemeta::core::SchemaFrame schema_frame{
      sourcemeta::core::SchemaFrame::Mode::Locations, frame_schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver};

  const auto dependencies_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};
  sourcemeta::blaze::dependencies(
      dependencies_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [](const auto &, const auto &, const auto &, const auto &) {});

  auto convert_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON")};
  sourcemeta::blaze::convert(convert_schema, sourcemeta::core::schema_walker,
                             sourcemeta::core::schema_resolver,
                             sourcemeta::blaze::ConvertTarget::Draft202012);

  return EXIT_SUCCESS;
}
