#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

auto output_schema_resolver(std::string_view identifier)
    -> sourcemeta::blaze::SchemaResolverResult {
  const std::filesystem::path suite_path{OFFICIAL_OUTPUT_SUITE_PATH};

  const auto hash_pos{identifier.find('#')};
  const std::string_view base_uri{hash_pos != std::string_view::npos
                                      ? identifier.substr(0, hash_pos)
                                      : identifier};

  if (base_uri == "https://json-schema.org/draft/2020-12/output/schema" ||
      base_uri == "/draft/2020-12/output/schema") {
    return sourcemeta::core::read_json(suite_path / "draft2020-12" /
                                       "output-schema.json");
  }

  if (base_uri == "https://json-schema.org/draft/2019-09/output/schema" ||
      base_uri == "/draft/2019-09/output/schema") {
    return sourcemeta::core::read_json(suite_path / "draft2019-09" /
                                       "output-schema.json");
  }

  return sourcemeta::blaze::schema_resolver(identifier);
}

auto run_official_output_test(const sourcemeta::core::JSON &input_schema,
                              const sourcemeta::core::JSON &data,
                              const sourcemeta::core::JSON &output_basic_schema,
                              const sourcemeta::blaze::Mode mode,
                              const std::string &default_dialect) -> void {
  const auto input_template{sourcemeta::blaze::compile(
      input_schema, sourcemeta::blaze::schema_walker, output_schema_resolver,
      sourcemeta::blaze::default_schema_compiler, mode, default_dialect)};

  sourcemeta::blaze::Evaluator evaluator;
  const auto blaze_output{
      sourcemeta::blaze::standard(evaluator, input_template, data,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  const auto output_template{sourcemeta::blaze::compile(
      output_basic_schema, sourcemeta::blaze::schema_walker,
      output_schema_resolver, sourcemeta::blaze::default_schema_compiler, mode,
      default_dialect)};

  const auto valid{evaluator.validate(output_template, blaze_output)};
  EXPECT_TRUE(valid);
}

auto slugify(const std::string &input) -> std::string {
  std::string result;
  result.reserve(input.size());
  for (const auto character : input) {
    result.push_back(std::isalnum(static_cast<unsigned char>(character)) != 0
                         ? character
                         : '_');
  }
  return result;
}

auto register_tests(const std::filesystem::path &path,
                    const std::string &suite_name,
                    const std::string &default_dialect) -> void {
  const auto suite{sourcemeta::core::read_json(path)};
  assert(suite.is_array());

  const auto file_stem{path.stem().string()};

  for (const auto &case_entry : suite.as_array()) {
    assert(case_entry.is_object());
    assert(case_entry.defines("description"));
    assert(case_entry.defines("schema"));
    assert(case_entry.defines("tests"));

    const auto &case_description{case_entry.at("description").to_string()};
    const auto &input_schema{case_entry.at("schema")};

    for (const auto &test_entry : case_entry.at("tests").as_array()) {
      assert(test_entry.is_object());
      assert(test_entry.defines("description"));
      assert(test_entry.defines("data"));
      assert(test_entry.defines("output"));

      const auto &test_description{test_entry.at("description").to_string()};
      const auto &data{test_entry.at("data")};
      const auto &output_def{test_entry.at("output")};

      assert(output_def.defines("basic"));
      const auto &output_basic_schema{output_def.at("basic")};

      const auto title{file_stem + "_" + slugify(case_description) + "_" +
                       slugify(test_description)};

      sourcemeta::core::test_register(
          suite_name, title, __FILE__, __LINE__,
          [input_schema, data, output_basic_schema, default_dialect]() -> void {
            run_official_output_test(input_schema, data, output_basic_schema,
                                     sourcemeta::blaze::Mode::Exhaustive,
                                     default_dialect);
          });
    }
  }
}

} // namespace

auto main(int argc, char **argv) -> int {
  try {
    const std::filesystem::path suite_path{OFFICIAL_OUTPUT_SUITE_PATH};

    const std::vector<std::string> test_files{
        "escape.json",
        "general.json",
        "readOnly.json",
        "type.json",
    };

    // 2020-12
    const std::filesystem::path content_2020_12_dir{suite_path /
                                                    "draft2020-12" / "content"};
    for (const auto &file : test_files) {
      register_tests(content_2020_12_dir / file,
                     "Output_official_2020_12_suite",
                     "https://json-schema.org/draft/2020-12/schema");
    }

    // 2019-09
    const std::filesystem::path content_2019_09_dir{suite_path /
                                                    "draft2019-09" / "content"};
    for (const auto &file : test_files) {
      register_tests(content_2019_09_dir / file,
                     "Output_official_2019_09_suite",
                     "https://json-schema.org/draft/2019-09/schema");
    }
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
