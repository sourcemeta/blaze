#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

static void Micro_2020_12_Dynamic_Ref(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "test",
    "$ref": "one",
    "$defs": {
      "one": {
        "$id": "one",
        "$dynamicAnchor": "test",
        "items": { "$ref": "two" }
      },
      "two": {
        "$id": "two",
        "$dynamicAnchor": "test",
        "items": { "$ref": "three" }
      },
      "three": {
        "$id": "three",
        "$dynamicAnchor": "test",
        "items": { "$ref": "four" }
      },
      "four": {
        "$id": "four",
        "$dynamicAnchor": "test",
        "items": { "$ref": "five" }
      },
      "five": {
        "$id": "five",
        "$dynamicAnchor": "test",
        "items": { "$ref": "six" }
      },
      "six": {
        "$id": "six",
        "$dynamicAnchor": "test",
        "items": { "$dynamicRef": "#test" }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON([
    1,
    [2, [3, [4, [5, [6, [7, [8, [9, 10]]]]]]]], 11],
    [[[[[[[12]]]]]]], 13],
    [14, [15, [16, [17, [18, [19, [20]]]]]]],
    21,
    [22, [23, [24, [25, [26, [27, [28]]]]]]]
  ])JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_2020_12_Dynamic_Ref_Single(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#test",
    "$defs": {
      "test": {
        "$dynamicAnchor": "test",
        "type": "boolean"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::JSON{true}};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_2020_12_Simple_Output_Mask(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "data": {
        "oneOf": [
          {
            "anyOf": [
              { "type": "string", "minLength": 100 },
              { "type": "number", "minimum": 1000 },
              { "type": "boolean" }
            ]
          },
          {
            "anyOf": [
              { "type": "string", "pattern": "^[A-Z]+$" },
              { "type": "array", "minItems": 50 },
              { "type": "object", "required": ["x", "y", "z"] }
            ]
          },
          {
            "anyOf": [
              { "type": "null" },
              { "type": "integer", "multipleOf": 7 },
              { "type": "string", "maxLength": 2 }
            ]
          },
          {
            "type": "array",
            "contains": {
              "oneOf": [
                { "type": "string", "minLength": 20 },
                { "type": "number", "minimum": 100 },
                { "const": "special" }
              ]
            },
            "minContains": 3
          },
          {
            "type": "array",
            "items": {
              "anyOf": [
                { "type": "number", "maximum": 50 },
                { "type": "string", "maxLength": 10 }
              ]
            },
            "minItems": 1
          }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "data": [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, "a", "b", "c", "d", "e" ]
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    sourcemeta::blaze::SimpleOutput output{instance};
    auto result{
        evaluator.validate(schema_template, instance, std::ref(output))};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_2020_12_Simple_Output_Annotations(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "allOf": [
      { "contains": { "type": "number" } },
      { "contains": { "type": "number" } },
      { "contains": { "type": "number" } },
      { "contains": { "type": "string" } },
      { "contains": { "type": "string" } },
      { "contains": { "type": "string" } },
      { "contains": { "type": "boolean" } },
      { "contains": { "type": "null" } },
      { "contains": { "type": "number" } },
      { "contains": { "type": "number" } }
    ]
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON([
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    "a", "b", "c", "aa", "bb", "cc",
    "abc", "def", "ghi",
    "ABC", "DEF", "GHI",
    true, false, true,
    null, null,
    42, 48, 54, 60
  ])JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    sourcemeta::blaze::SimpleOutput output{instance};
    auto result{
        evaluator.validate(schema_template, instance, std::ref(output))};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Micro_2020_12_Dynamic_Ref);
BENCHMARK(Micro_2020_12_Dynamic_Ref_Single);
BENCHMARK(Micro_2020_12_Simple_Output_Mask);
BENCHMARK(Micro_2020_12_Simple_Output_Annotations);
