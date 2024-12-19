#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Evaluator_2020_12_Dynamic_Ref(benchmark::State &state) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const auto instance{sourcemeta::jsontoolkit::parse(R"JSON([
    1,
    [2, [3, [4, [5, [6, [7, [8, [9, 10]]]]]]]], 11],
    [[[[[[[12]]]]]]], 13],
    [14, [15, [16, [17, [18, [19, [20]]]]]]],
    21,
    [22, [23, [24, [25, [26, [27, [28]]]]]]]
  ])JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Evaluator_2020_12_Dynamic_Ref_Single(benchmark::State &state) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
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

  const auto instance{sourcemeta::jsontoolkit::JSON{true}};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Evaluator_2020_12_CQL_1(benchmark::State &state) {
  const auto schema{sourcemeta::jsontoolkit::from_file(
      std::filesystem::path{CURRENT_DIRECTORY} / "schemas" /
      "2020_12_cql.json")};

  const auto instance{sourcemeta::jsontoolkit::from_file(
      std::filesystem::path{CURRENT_DIRECTORY} / "instances" /
      "2020_12_cql_1.json")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Evaluator_2020_12_Dynamic_Ref);
BENCHMARK(Evaluator_2020_12_Dynamic_Ref_Single);
BENCHMARK(Evaluator_2020_12_CQL_1);
