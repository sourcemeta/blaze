#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/documentation.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem
#include <string>     // std::string

// Each case is a directory of real data: the schema that goes in, the document
// it must produce, and the page that document must render as. A case is read
// rather than written in C++, so adding one is adding files.
//
// What a schema cannot be described as stays in C++, because a refusal is
// about a message and a place rather than about a document.

namespace {

auto run_documentation_test(const std::filesystem::path &directory) -> void {
  // The format has a schema of its own, and every document is held to it
  static const auto FORMAT{sourcemeta::blaze::compile(
      sourcemeta::core::read_json(std::string{TABLE_FORMAT_SCHEMA_PATH}),
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler)};

  const auto documentation{sourcemeta::blaze::to_documentation(
      sourcemeta::core::read_json(directory / "schema.json"),
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver)};
  EXPECT_EQ(documentation,
            sourcemeta::core::read_json(directory / "table.json"));

  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_TRUE(evaluator.validate(FORMAT, documentation));

  // The page is compared indented, so that a change to it reads as a change to
  // a line
  std::string page;
  sourcemeta::blaze::to_html(documentation, page, true);
  EXPECT_EQ(page,
            sourcemeta::core::read_file_to_string(directory / "index.html"));
}

auto register_tests(const std::filesystem::path &suite) -> void {
  for (const auto &dialect : std::filesystem::directory_iterator{suite}) {
    std::string name{"DocumentationSuite_"};
    for (const auto character : dialect.path().filename().string()) {
      name += character == '-' ? '_' : character;
    }

    for (const auto &entry : std::filesystem::directory_iterator{dialect}) {
      const auto &directory{entry.path()};
      sourcemeta::core::test_register(
          name, directory.filename().string(), __FILE__, __LINE__,
          [directory]() -> void { run_documentation_test(directory); });
    }
  }
}

} // namespace

auto main(int argc, char **argv) -> int {
  register_tests(std::filesystem::path{DOCUMENTATION_SUITE_PATH});
  return sourcemeta::core::test_run(argc, argv);
}
