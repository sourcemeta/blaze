#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/allocator.h>

namespace {

[[nodiscard]] auto sample_schema() -> sourcemeta::core::JSON {
  return sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/allocator-profile",
    "$defs": {
      "leaf": {
        "type": "object",
        "properties": {
          "id": { "type": "integer" },
          "name": { "type": "string", "minLength": 1 }
        },
        "required": ["id", "name"],
        "additionalProperties": false
      },
      "node": {
        "type": "object",
        "properties": {
          "left": { "$ref": "#/$defs/node" },
          "right": { "$ref": "#/$defs/node" },
          "payload": { "$ref": "#/$defs/leaf" }
        },
        "anyOf": [
          { "required": ["payload"] },
          { "required": ["left", "right"] }
        ],
        "additionalProperties": false
      }
    },
    "type": "object",
    "properties": {
      "root": { "$ref": "#/$defs/node" },
      "kind": {
        "enum": ["tree", "forest", "single"]
      },
      "metadata": {
        "type": "object",
        "properties": {
          "created": { "type": "string", "format": "date-time" },
          "tags": {
            "type": "array",
            "items": { "type": "string" },
            "minItems": 1
          }
        },
        "required": ["created", "tags"],
        "additionalProperties": false
      }
    },
    "required": ["root", "kind", "metadata"],
    "additionalProperties": false
  })JSON");
}

[[nodiscard]] auto sample_instance() -> sourcemeta::core::JSON {
  return sourcemeta::core::parse_json(R"JSON({
    "root": {
      "left": {
        "payload": {
          "id": 1,
          "name": "alpha"
        }
      },
      "right": {
        "payload": {
          "id": 2,
          "name": "beta"
        }
      }
    },
    "kind": "tree",
    "metadata": {
      "created": "2026-05-12T00:00:00Z",
      "tags": ["allocator", "benchmark", "profile"]
    }
  })JSON");
}

[[nodiscard]] auto make_template() -> sourcemeta::blaze::Template {
  const auto schema{sample_schema()};
  return sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation);
}

} // namespace

static void Allocator_Profile_Compile(benchmark::State &state) {
  const auto schema{sample_schema()};
  for (auto _ : state) {
    auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation)};
    benchmark::DoNotOptimize(schema_template);
  }
}

static void Allocator_Profile_Validate(benchmark::State &state) {
  const auto schema_template{make_template()};
  const auto instance{sample_instance()};
  sourcemeta::blaze::Evaluator evaluator;

  for (auto _ : state) {
    const auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }

  state.SetItemsProcessed(state.iterations());
}

static void Allocator_Profile_Concurrent_Validate(benchmark::State &state) {
  const auto schema_template{make_template()};
  const auto instance{sample_instance()};
  sourcemeta::blaze::Evaluator evaluator;

  for (auto _ : state) {
    const auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }

  state.SetItemsProcessed(state.iterations());
}

BENCHMARK(Allocator_Profile_Compile);
BENCHMARK(Allocator_Profile_Validate);
BENCHMARK(Allocator_Profile_Concurrent_Validate)->ThreadRange(1, 8);

// Initialize allocator backend at benchmark startup
// Use standard backend by default (no override)
// To test rpmalloc: rebuild with -DBLAZE_ALLOCATOR_RPMALLOC=ON and set env var
namespace {
struct AllocatorInitializer {
  AllocatorInitializer() {
    sourcemeta::blaze::allocator::Config config;
    // Backend selection: default is Standard
    // In Phase 2, we're not globally enabling rpmalloc, just making it available
    sourcemeta::blaze::allocator::initialize(config);
  }
  ~AllocatorInitializer() {
    sourcemeta::blaze::allocator::finalize();
  }
};
static AllocatorInitializer g_allocator;
} // namespace
