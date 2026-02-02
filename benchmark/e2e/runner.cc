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

#define REGISTER_E2E_COMPILER(name, directory_name)                            \
  static auto E2E_Compiler_##name(benchmark::State &state)->void {             \
    const std::filesystem::path directory{CURRENT_DIRECTORY                    \
                                          "/e2e/" directory_name};             \
    const auto schema{sourcemeta::core::read_json(directory / "schema.json")}; \
                                                                               \
    for (auto _ : state) {                                                     \
      auto schema_template{sourcemeta::blaze::compile(                         \
          schema, sourcemeta::core::schema_walker,                             \
          sourcemeta::core::schema_resolver,                                   \
          sourcemeta::blaze::default_schema_compiler,                          \
          sourcemeta::blaze::Mode::FastValidation)};                           \
      benchmark::DoNotOptimize(schema_template);                               \
    }                                                                          \
  }                                                                            \
  BENCHMARK(E2E_Compiler_##name)

#define REGISTER_E2E_EVALUATOR(name, directory_name)                           \
  static auto E2E_Evaluator_##name(benchmark::State &state)->void {            \
    const std::filesystem::path directory{CURRENT_DIRECTORY                    \
                                          "/e2e/" directory_name};             \
    const auto schema{sourcemeta::core::read_json(directory / "schema.json")}; \
    const auto schema_template{                                                \
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,    \
                                   sourcemeta::core::schema_resolver,          \
                                   sourcemeta::blaze::default_schema_compiler, \
                                   sourcemeta::blaze::Mode::FastValidation)};  \
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
  BENCHMARK(E2E_Evaluator_##name)

REGISTER_E2E_COMPILER(adaptivecard, "adaptivecard");
REGISTER_E2E_COMPILER(ansible_meta, "ansible-meta");
REGISTER_E2E_COMPILER(aws_cdk, "aws-cdk");
REGISTER_E2E_COMPILER(babelrc, "babelrc");
REGISTER_E2E_COMPILER(clang_format, "clang-format");
REGISTER_E2E_COMPILER(cmake_presets, "cmake-presets");
REGISTER_E2E_COMPILER(code_climate, "code-climate");
REGISTER_E2E_COMPILER(cql2, "cql2");
REGISTER_E2E_COMPILER(cspell, "cspell");
REGISTER_E2E_COMPILER(cypress, "cypress");
REGISTER_E2E_COMPILER(deno, "deno");
REGISTER_E2E_COMPILER(dependabot, "dependabot");
REGISTER_E2E_COMPILER(draft_04, "draft-04");
REGISTER_E2E_COMPILER(fabric_mod, "fabric-mod");
REGISTER_E2E_COMPILER(geojson, "geojson");
REGISTER_E2E_COMPILER(gitpod_configuration, "gitpod-configuration");
REGISTER_E2E_COMPILER(helm_chart_lock, "helm-chart-lock");
REGISTER_E2E_COMPILER(importmap, "importmap");
REGISTER_E2E_COMPILER(jasmine, "jasmine");
REGISTER_E2E_COMPILER(jshintrc, "jshintrc");
REGISTER_E2E_COMPILER(jsconfig, "jsconfig");
REGISTER_E2E_COMPILER(krakend, "krakend");
REGISTER_E2E_COMPILER(lazygit, "lazygit");
REGISTER_E2E_COMPILER(lerna, "lerna");
REGISTER_E2E_COMPILER(nest_cli, "nest-cli");
REGISTER_E2E_COMPILER(omc, "omc");
REGISTER_E2E_COMPILER(omnisharp, "omnisharp");
REGISTER_E2E_COMPILER(openapi, "openapi");
REGISTER_E2E_COMPILER(pre_commit_hooks, "pre-commit-hooks");
REGISTER_E2E_COMPILER(pulumi, "pulumi");
REGISTER_E2E_COMPILER(semantic_release, "semantic-release");
REGISTER_E2E_COMPILER(stale, "stale");
REGISTER_E2E_COMPILER(stylecop, "stylecop");
REGISTER_E2E_COMPILER(tmuxinator, "tmuxinator");
REGISTER_E2E_COMPILER(ui5, "ui5");
REGISTER_E2E_COMPILER(ui5_manifest, "ui5-manifest");
REGISTER_E2E_COMPILER(unreal_engine_uproject, "unreal-engine-uproject");
REGISTER_E2E_COMPILER(vercel, "vercel");
REGISTER_E2E_COMPILER(yamllint, "yamllint");

REGISTER_E2E_EVALUATOR(adaptivecard, "adaptivecard");
REGISTER_E2E_EVALUATOR(ansible_meta, "ansible-meta");
REGISTER_E2E_EVALUATOR(aws_cdk, "aws-cdk");
REGISTER_E2E_EVALUATOR(babelrc, "babelrc");
REGISTER_E2E_EVALUATOR(cerebrum_criminal_case, "cerebrum-criminal-case");
REGISTER_E2E_EVALUATOR(clang_format, "clang-format");
REGISTER_E2E_EVALUATOR(cmake_presets, "cmake-presets");
REGISTER_E2E_EVALUATOR(code_climate, "code-climate");
REGISTER_E2E_EVALUATOR(cql2, "cql2");
REGISTER_E2E_EVALUATOR(cspell, "cspell");
REGISTER_E2E_EVALUATOR(cypress, "cypress");
REGISTER_E2E_EVALUATOR(deno, "deno");
REGISTER_E2E_EVALUATOR(dependabot, "dependabot");
REGISTER_E2E_EVALUATOR(draft_04, "draft-04");
REGISTER_E2E_EVALUATOR(fabric_mod, "fabric-mod");
REGISTER_E2E_EVALUATOR(geojson, "geojson");
REGISTER_E2E_EVALUATOR(gitpod_configuration, "gitpod-configuration");
REGISTER_E2E_EVALUATOR(helm_chart_lock, "helm-chart-lock");
REGISTER_E2E_EVALUATOR(importmap, "importmap");
REGISTER_E2E_EVALUATOR(jasmine, "jasmine");
REGISTER_E2E_EVALUATOR(jshintrc, "jshintrc");
REGISTER_E2E_EVALUATOR(jsconfig, "jsconfig");
REGISTER_E2E_EVALUATOR(krakend, "krakend");
REGISTER_E2E_EVALUATOR(lazygit, "lazygit");
REGISTER_E2E_EVALUATOR(lerna, "lerna");
REGISTER_E2E_EVALUATOR(nest_cli, "nest-cli");
REGISTER_E2E_EVALUATOR(omc, "omc");
REGISTER_E2E_EVALUATOR(omnisharp, "omnisharp");
REGISTER_E2E_EVALUATOR(openapi, "openapi");
REGISTER_E2E_EVALUATOR(pre_commit_hooks, "pre-commit-hooks");
REGISTER_E2E_EVALUATOR(pulumi, "pulumi");
REGISTER_E2E_EVALUATOR(semantic_release, "semantic-release");
REGISTER_E2E_EVALUATOR(stale, "stale");
REGISTER_E2E_EVALUATOR(stylecop, "stylecop");
REGISTER_E2E_EVALUATOR(tmuxinator, "tmuxinator");
REGISTER_E2E_EVALUATOR(ui5, "ui5");
REGISTER_E2E_EVALUATOR(ui5_manifest, "ui5-manifest");
REGISTER_E2E_EVALUATOR(unreal_engine_uproject, "unreal-engine-uproject");
REGISTER_E2E_EVALUATOR(vercel, "vercel");
REGISTER_E2E_EVALUATOR(yamllint, "yamllint");
