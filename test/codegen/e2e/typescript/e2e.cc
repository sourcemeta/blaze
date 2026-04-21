#include <gtest/gtest.h>

#include <sourcemeta/blaze/codegen.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <sstream>    // std::ostringstream
#include <string>     // std::string

class TypeScriptE2ETest : public testing::Test {
public:
  explicit TypeScriptE2ETest(const std::filesystem::path &test_directory)
      : directory{test_directory} {}

  auto TestBody() -> void override {
    const auto schema_path{this->directory / "schema.json"};
    const auto options_path{this->directory / "options.json"};
    const auto expected_path{this->directory / "expected.d.ts"};

    const auto schema{sourcemeta::core::read_json(schema_path)};
    const auto options{sourcemeta::core::read_json(options_path)};

    std::ifstream expected_stream{expected_path};
    expected_stream.exceptions(std::ios_base::badbit);
    const std::string expected{std::istreambuf_iterator<char>(expected_stream),
                               std::istreambuf_iterator<char>()};

    const auto result{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_compiler)};

    std::ostringstream output;
    if (options.defines("defaultPrefix")) {
      sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(
          output, result, options.at("defaultPrefix").to_string());
    } else {
      sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output,
                                                                 result);
    }

    EXPECT_EQ(output.str(), expected)
        << "Generated TypeScript does not match expected output";
  }

private:
  const std::filesystem::path directory;
};

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);

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
      testing::RegisterTest("Codegen_e2e_typescript", test_name.c_str(),
                            nullptr, nullptr, __FILE__, __LINE__,
                            [=]() -> TypeScriptE2ETest * {
                              return new TypeScriptE2ETest(case_entry.path());
                            });
    }
  }

  return RUN_ALL_TESTS();
}
