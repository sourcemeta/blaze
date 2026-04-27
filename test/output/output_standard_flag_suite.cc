#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <cassert>    // assert
#include <cstdio>     // std::fprintf
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <filesystem> // std::filesystem::path
#include <string>     // std::string
#include <utility>    // std::move, std::pair

class StandardFlagTest : public testing::Test {
public:
  explicit StandardFlagTest(sourcemeta::core::JSON test_data,
                            const sourcemeta::blaze::Mode test_mode,
                            const char *test_mode_key)
      : data{std::move(test_data)}, mode{test_mode}, mode_key{test_mode_key} {}

  auto TestBody() -> void override {
    const auto &schema{this->data.at("schema")};
    const auto &instance{this->data.at("instance")};
    const auto &expected{this->data.at(this->mode_key)};

    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler, this->mode)};

    sourcemeta::blaze::Evaluator evaluator;
    const auto result{
        sourcemeta::blaze::standard(evaluator, schema_template, instance,
                                    sourcemeta::blaze::StandardOutput::Flag)};

    EXPECT_EQ(result, expected);
  }

private:
  const sourcemeta::core::JSON data;
  const sourcemeta::blaze::Mode mode;
  const char *mode_key;
};

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

      testing::RegisterTest(suite_name.c_str(), title.c_str(), nullptr, nullptr,
                            __FILE__, __LINE__, [=]() -> StandardFlagTest * {
                              return new StandardFlagTest(test_data, mode,
                                                          mode_key);
                            });
    }
  }
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);

  try {
    register_tests(std::filesystem::path{OUTPUT_SUITE_PATH} /
                       "output_standard_flag.json",
                   "Output_standard_flag_suite");
  } catch (const std::exception &error) {
    std::fprintf(stderr, "Error: %s\n", error.what());
    return EXIT_FAILURE;
  }

  return RUN_ALL_TESTS();
}
