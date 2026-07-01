#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <cassert>    // assert
#include <cstdio>     // std::fprintf
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <filesystem> // std::filesystem::path
#include <string>     // std::string
#include <utility>    // std::move, std::pair

namespace {
auto run_standard_basic_test(const sourcemeta::core::JSON &data,
                             const sourcemeta::blaze::Mode mode,
                             const char *mode_key) -> void {
  const auto &schema{data.at("schema")};
  const auto &instance{data.at("instance")};
  const auto &expected{data.at(mode_key)};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, mode)};

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                  sourcemeta::blaze::StandardOutput::Basic)};

  EXPECT_EQ(result, expected);
}
} // namespace

static auto register_tests(const std::filesystem::path &path,
                           const std::string &suite_name) -> void {
  std::fprintf(stderr, "-- Parsing: %s\n", path.string().c_str());
  auto suite{sourcemeta::core::read_json(path)};
  assert(suite.is_array());

  for (const auto &test_case : suite.as_array()) {
    assert(test_case.is_object());
    assert(test_case.defines("description"));
    const auto &description{test_case.at("description").to_string()};

    assert(test_case.defines("fast"));
    assert(test_case.defines("exhaustive"));

    const auto test_data{test_case};

    for (const auto &[mode_key, mode] :
         {std::pair<const char *, sourcemeta::blaze::Mode>{
              "fast", sourcemeta::blaze::Mode::FastValidation},
          std::pair<const char *, sourcemeta::blaze::Mode>{
              "exhaustive", sourcemeta::blaze::Mode::Exhaustive}}) {

      const auto title{description +
                       (mode == sourcemeta::blaze::Mode::FastValidation
                            ? "_fast"
                            : "_exhaustive")};

      sourcemeta::core::test_register(suite_name, title, __FILE__, __LINE__,
                                      [test_data, mode, mode_key]() -> void {
                                        run_standard_basic_test(test_data, mode,
                                                                mode_key);
                                      });
    }
  }
}

auto main(int argc, char **argv) -> int {
  try {
    register_tests(std::filesystem::path{OUTPUT_SUITE_PATH} /
                       "output_standard_basic.json",
                   "Output_standard_basic_suite");
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
