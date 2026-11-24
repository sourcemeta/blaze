#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/canonicalizer.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"
#include "tracesuite.h"

#include <cstdio>     // std::fprintf
#include <filesystem> // std::filesystem::path
#include <string>     // std::string
#include <utility>    // std::pair

namespace {
auto declared_dialect(const sourcemeta::core::JSON &schema)
    -> sourcemeta::core::JSON::String {
  if (!schema.is_object()) {
    return {};
  }

  const auto *dialect{schema.try_at("$schema")};
  return (dialect != nullptr && dialect->is_string())
             ? dialect->to_string()
             : sourcemeta::core::JSON::String{};
}

auto run_canonicalize_test(const std::string &name,
                           const sourcemeta::core::JSON &data,
                           const sourcemeta::blaze::Mode mode,
                           const std::string &default_dialect) -> void {
  const FixtureResolver resolver{data};
  auto schema{fixture_schema(data, resolver)};
  const auto &instance{data.at("instance")};
  const bool expected_valid{data.at("valid").to_boolean()};

  // Canonicalisation can collapse an unsatisfiable schema into a boolean,
  // which has no room for the dialect the document declares, so hold on to
  // that dialect for the compilation that follows. A dialect that forbids
  // self-identification only arrives from the outside
  auto dialect{declared_dialect(schema)};
  if (dialect.empty()) {
    dialect = fixture_default_dialect(data, default_dialect);
  }

  sourcemeta::blaze::canonicalize(schema, sourcemeta::core::schema_walker,
                                  resolver, dialect);

  const auto compiled_schema{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, resolver,
      sourcemeta::blaze::default_schema_compiler, mode, dialect, "",
      fixture_entrypoint(data), fixture_tweaks(name, data))};
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{evaluator.validate(compiled_schema, instance)};

  if (expected_valid) {
    EXPECT_TRUE(result);
  } else {
    EXPECT_FALSE(result);
  }
}
} // namespace

static auto
register_tests(const std::filesystem::path &directory,
               const std::string &suite_name,
               const sourcemeta::core::SchemaBaseDialect base_dialect,
               const std::string &default_dialect = "") -> void {
  // NOLINTNEXTLINE(modernize-use-std-print)
  std::fprintf(stderr, "-- Parsing: %s\n", directory.string().c_str());

  for (const auto &[name, test_case] : read_fixtures(
           directory, FixtureKind::Trace, base_dialect, default_dialect)) {
    // An entrypoint names a place inside the document as it was written, and
    // canonicalisation is free to restructure what it finds: it renumbers the
    // definitions it rewrites, and drops a subschema nothing refers to. What
    // the entrypoint named need not exist afterwards, so there is nothing here
    // for this suite to compare. The plain trace suite still runs these
    if (test_case.defines("entrypoint")) {
      // NOLINTNEXTLINE(modernize-use-std-print)
      std::fprintf(stderr, "-- Not canonicalising (names an entrypoint): %s\n",
                   name.c_str());
      continue;
    }

    for (const auto &[mode_suffix, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "_fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "_exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {
      sourcemeta::core::test_register(
          suite_name, name + mode_suffix, __FILE__, __LINE__,
          [name, test_case, mode, default_dialect]() -> void {
            run_canonicalize_test(name, test_case, mode, default_dialect);
          });
    }
  }
}

auto main(int argc, char **argv) -> int {
  try {
    const std::filesystem::path suite{TRACE_SUITE_CANONICAL_PATH};

    // The two dated OpenAPI 3.0 dialects answer with the same Schema Object
    // definition, so one suite says what both of them mean
    for (const auto &[label, dialect] :
         {std::pair<const char *, const char *>{
              "2024_10_18", "tag:spec.openapis.org,2024-10-18:oas/3.0/dialect"},
          std::pair<const char *, const char *>{
              "2021_09_28",
              "tag:spec.openapis.org,2021-09-28:oas/3.0/dialect"}}) {
      register_tests(suite / "openapi_3_0" / "valid",
                     std::string{"Canonicalize_OpenAPI_3_0_"} + label,
                     sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4,
                     dialect);
    }
    register_tests(suite / "openapi_3_1" / "valid", "Canonicalize_OpenAPI_3_1",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "openapi_3_2" / "valid", "Canonicalize_OpenAPI_3_2",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "draft7" / "valid", "Canonicalize_draft7",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_7);
    register_tests(suite / "2019_09" / "valid", "Canonicalize_2019_09",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09);
    register_tests(suite / "sourcemeta_v1_2019_09" / "valid",
                   "Canonicalize_sourcemeta_v1_2019_09",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2019_09);
    register_tests(suite / "sourcemeta_v1_2020_12" / "valid",
                   "Canonicalize_sourcemeta_v1_2020_12",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "draft6" / "valid", "Canonicalize_draft6",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_6);
    register_tests(suite / "2020_12" / "valid", "Canonicalize_2020_12",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_2020_12);
    register_tests(suite / "draft4" / "valid", "Canonicalize_draft4",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_4);
    register_tests(suite / "draft3" / "valid", "Canonicalize_draft3",
                   sourcemeta::core::SchemaBaseDialect::JSON_SCHEMA_DRAFT_3);
  } catch (const std::exception &error) {
    // NOLINTNEXTLINE(modernize-use-std-print)
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
