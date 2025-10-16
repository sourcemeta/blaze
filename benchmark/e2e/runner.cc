#include <benchmark/benchmark.h>

#include <cassert>    // assert
#include <filesystem> // std::filesystem
#include <vector>     // std::vector

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonl.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#define REGISTER_E2E_BENCHMARKS(name, directory_name)                          \
  static auto E2E_Compiler_##name(benchmark::State &state)->void {             \
    const std::filesystem::path directory{CURRENT_DIRECTORY                    \
                                          "/e2e/" directory_name};             \
    const auto schema{sourcemeta::core::read_json(directory / "schema.json")}; \
                                                                               \
    for (auto _ : state) {                                                     \
      auto schema_template{sourcemeta::blaze::compile(                         \
          schema, sourcemeta::core::schema_official_walker,                    \
          sourcemeta::core::schema_official_resolver,                          \
          sourcemeta::blaze::default_schema_compiler,                          \
          sourcemeta::blaze::Mode::FastValidation)};                           \
      benchmark::DoNotOptimize(schema_template);                               \
    }                                                                          \
  }                                                                            \
                                                                               \
  static auto E2E_Evaluator_##name(benchmark::State &state)->void {            \
    const std::filesystem::path directory{CURRENT_DIRECTORY                    \
                                          "/e2e/" directory_name};             \
    const auto schema{sourcemeta::core::read_json(directory / "schema.json")}; \
    const auto schema_template{sourcemeta::blaze::compile(                     \
        schema, sourcemeta::core::schema_official_walker,                      \
        sourcemeta::core::schema_official_resolver,                            \
        sourcemeta::blaze::default_schema_compiler,                            \
        sourcemeta::blaze::Mode::FastValidation)};                             \
                                                                               \
    auto stream{sourcemeta::core::read_file(directory / "instances.jsonl")};   \
    std::vector<sourcemeta::core::JSON> instances;                             \
    for (const auto &instance : sourcemeta::core::JSONL{stream}) {             \
      instances.push_back(instance);                                           \
    }                                                                          \
                                                                               \
    sourcemeta::blaze::Evaluator evaluator;                                    \
    for (auto _ : state) {                                                     \
      for (const auto &instance : instances) {                                 \
        auto result{evaluator.validate(schema_template, instance)};            \
        assert(result);                                                        \
        benchmark::DoNotOptimize(result);                                      \
      }                                                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  BENCHMARK(E2E_Compiler_##name);                                              \
  BENCHMARK(E2E_Evaluator_##name)

REGISTER_E2E_BENCHMARKS(ansible_meta, "ansible-meta");
REGISTER_E2E_BENCHMARKS(aws_cdk, "aws-cdk");
REGISTER_E2E_BENCHMARKS(babelrc, "babelrc");
REGISTER_E2E_BENCHMARKS(clang_format, "clang-format");
REGISTER_E2E_BENCHMARKS(cmake_presets, "cmake-presets");
REGISTER_E2E_BENCHMARKS(code_climate, "code-climate");
REGISTER_E2E_BENCHMARKS(cql2, "cql2");
REGISTER_E2E_BENCHMARKS(cspell, "cspell");
REGISTER_E2E_BENCHMARKS(cypress, "cypress");
REGISTER_E2E_BENCHMARKS(deno, "deno");
REGISTER_E2E_BENCHMARKS(dependabot, "dependabot");
REGISTER_E2E_BENCHMARKS(draft_04, "draft-04");
REGISTER_E2E_BENCHMARKS(fabric_mod, "fabric-mod");
REGISTER_E2E_BENCHMARKS(geojson, "geojson");
REGISTER_E2E_BENCHMARKS(gitpod_configuration, "gitpod-configuration");
REGISTER_E2E_BENCHMARKS(helm_chart_lock, "helm-chart-lock");
REGISTER_E2E_BENCHMARKS(importmap, "importmap");
REGISTER_E2E_BENCHMARKS(jasmine, "jasmine");
REGISTER_E2E_BENCHMARKS(jshintrc, "jshintrc");
REGISTER_E2E_BENCHMARKS(jsconfig, "jsconfig");
REGISTER_E2E_BENCHMARKS(krakend, "krakend");
REGISTER_E2E_BENCHMARKS(lazygit, "lazygit");
REGISTER_E2E_BENCHMARKS(lerna, "lerna");
REGISTER_E2E_BENCHMARKS(nest_cli, "nest-cli");
REGISTER_E2E_BENCHMARKS(omnisharp, "omnisharp");
REGISTER_E2E_BENCHMARKS(openapi, "openapi");
REGISTER_E2E_BENCHMARKS(pre_commit_hooks, "pre-commit-hooks");
REGISTER_E2E_BENCHMARKS(pulumi, "pulumi");
REGISTER_E2E_BENCHMARKS(semantic_release, "semantic-release");
REGISTER_E2E_BENCHMARKS(stale, "stale");
REGISTER_E2E_BENCHMARKS(stylecop, "stylecop");
REGISTER_E2E_BENCHMARKS(tmuxinator, "tmuxinator");
REGISTER_E2E_BENCHMARKS(ui5, "ui5");
REGISTER_E2E_BENCHMARKS(ui5_manifest, "ui5-manifest");
REGISTER_E2E_BENCHMARKS(unreal_engine_uproject, "unreal-engine-uproject");
REGISTER_E2E_BENCHMARKS(vercel, "vercel");
REGISTER_E2E_BENCHMARKS(yamllint, "yamllint");
