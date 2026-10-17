#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/documentation.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <sstream>    // std::ostringstream
#include <string>     // std::string
#include <vector>     // std::vector

// Each case is a directory of real data: the schema that goes in, the document
// it must produce, and the page that document must render as. A case under
// `pages` has no schema, only a document written by hand to draw. A case is
// read rather than written in C++, so adding one is adding files.
//
// What a schema cannot be described as stays in C++, because a refusal is
// about a message and a place rather than about a document.

namespace {

auto read_text(const std::filesystem::path &path) -> std::string {
  std::ifstream stream{path, std::ios::binary};
  std::ostringstream contents;
  contents << stream.rdbuf();
  auto result{contents.str()};
  // A fixture ends with a newline, which the value it stands for does not.
  while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
    result.pop_back();
  }

  return result;
}

auto cases() -> std::vector<std::filesystem::path> {
  std::vector<std::filesystem::path> out;
  const std::filesystem::path suite{DOCUMENTATION_SUITE_PATH};
  if (!std::filesystem::exists(suite)) {
    return out;
  }

  for (const auto &dialect : std::filesystem::directory_iterator{suite}) {
    if (!dialect.is_directory()) {
      continue;
    }

    for (const auto &entry : std::filesystem::directory_iterator{dialect}) {
      if (entry.is_directory() &&
          std::filesystem::exists(entry.path() / "table.json")) {
        out.push_back(entry.path());
      }
    }
  }

  std::sort(out.begin(), out.end());
  return out;
}

// Every page carries the same stylesheet, which is kept once in
// `suite/stylesheet.css` rather than in every case. A page is compared with
// its stylesheet taken out, and the stylesheet is checked on its own.
auto without_stylesheet(const std::string &page) -> std::string {
  const auto start{page.find("<style>")};
  const auto end{page.find("</style>")};
  if (start == std::string::npos || end == std::string::npos) {
    return page;
  }

  return page.substr(0, start + 7) + page.substr(end);
}

auto stylesheet_of(const std::string &page) -> std::string {
  const auto start{page.find("<style>")};
  const auto end{page.find("</style>")};
  if (start == std::string::npos || end == std::string::npos) {
    return "";
  }

  return page.substr(start + 7, end - start - 7);
}

} // namespace

TEST(documentation_suite_has_cases) {
  // A suite that quietly found nothing would pass every other check here.
  EXPECT_TRUE(cases().size() > 20);
}

TEST(documentation_suite_describes_every_case_as_its_fixture_says) {
  for (const auto &where : cases()) {
    if (!std::filesystem::exists(where / "schema.json")) {
      continue;
    }

    const auto schema{
        sourcemeta::core::read_json((where / "schema.json").string())};
    const auto expected{
        sourcemeta::core::read_json((where / "table.json").string())};
    const auto actual{sourcemeta::blaze::to_documentation(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver)};
    if (actual != expected) {
      std::cerr << "# differs: " << where.string() << "\n";
    }

    EXPECT_EQ(actual, expected);
  }
}

TEST(documentation_suite_renders_every_case_as_its_fixture_says) {
  for (const auto &where : cases()) {
    const auto page_path{where / "index.html"};
    if (!std::filesystem::exists(page_path)) {
      continue;
    }

    const auto document{
        sourcemeta::core::read_json((where / "table.json").string())};
    std::string page;
    sourcemeta::blaze::to_html(document, page);
    const auto actual{without_stylesheet(page)};
    if (actual != read_text(page_path)) {
      std::cerr << "# differs: " << where.string() << "\n";
    }

    EXPECT_EQ(actual, read_text(page_path));
  }
}

TEST(documentation_suite_every_document_fits_the_format) {
  const auto format{
      sourcemeta::core::read_json(std::string{TABLE_FORMAT_SCHEMA_PATH})};
  const auto compiled{
      sourcemeta::blaze::compile(format, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;

  for (const auto &where : cases()) {
    const auto document{
        sourcemeta::core::read_json((where / "table.json").string())};
    if (!evaluator.validate(compiled, document)) {
      std::cerr << "# does not fit the format: " << where.string() << "\n";
    }

    EXPECT_TRUE(evaluator.validate(compiled, document));
  }
}

TEST(documentation_suite_every_page_carries_the_stylesheet) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "root": { "kind": "string" }
  })JSON")};
  std::string page;
  sourcemeta::blaze::to_html(document, page);
  const std::filesystem::path suite{DOCUMENTATION_SUITE_PATH};
  // The file ends with a newline the page does not have, so the stylesheet is
  // read whole rather than with the trailing newline taken off.
  std::ifstream stream{suite / "stylesheet.css", std::ios::binary};
  std::ostringstream expected;
  expected << stream.rdbuf();
  EXPECT_EQ(stylesheet_of(page), expected.str());
}
