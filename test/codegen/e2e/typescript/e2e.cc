#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/codegen.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>

#include <filesystem> // std::filesystem
#include <sstream>    // std::ostringstream
#include <string>     // std::string

namespace {
auto run_typescript_e2e(const std::filesystem::path &directory) -> void {
  const auto schema_path{directory / "schema.json"};
  const auto options_path{directory / "options.json"};
  const auto expected_path{directory / "expected.d.ts"};

  const auto schema{sourcemeta::core::read_json(schema_path)};
  const auto options{sourcemeta::core::read_json(options_path)};

  const auto expected{sourcemeta::core::read_file_to_string(expected_path)};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  if (options.defines("defaultPrefix")) {
    sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(
        output, result, options.at("defaultPrefix").to_string());
  } else {
    sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);
  }

  EXPECT_EQ(output.str(), expected);
}
} // namespace

auto main(int argc, char **argv) -> int {
  const std::filesystem::path e2e_path{E2E_TYPESCRIPT_PATH};
  for (const auto &dialect_entry :
       std::filesystem::directory_iterator(e2e_path)) {
    if (!dialect_entry.is_directory()) {
      continue;
    }

    const auto dialect_name{dialect_entry.path().filename().string()};
    for (const auto &case_entry :
         std::filesystem::directory_iterator(dialect_entry.path())) {
      if (!case_entry.is_directory()) {
        continue;
      }

      const auto case_name{case_entry.path().filename().string()};
      const auto test_name{dialect_name + "/" + case_name};
      const auto case_path{case_entry.path()};
      sourcemeta::core::test_register(
          "Codegen_e2e_typescript", test_name, __FILE__, __LINE__,
          [case_path]() -> void { run_typescript_e2e(case_path); });
    }
  }

  return sourcemeta::core::test_run(argc, argv);
}
