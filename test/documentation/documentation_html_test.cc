#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>

#include <string> // std::string

// How pages are drawn is checked against whole pages in the suite. What stays
// here is what a page cannot show, and how the options shape its markup.

namespace {

auto order() -> sourcemeta::core::JSON {
  return sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "properties": [ { "name": "id", "value": { "kind": "string" } } ]
    }
  })JSON");
}

auto stylesheet_of(const std::string &page) -> std::string {
  const auto start{page.find("<style>")};
  const auto end{page.find("</style>")};
  EXPECT_TRUE(start != std::string::npos);
  EXPECT_TRUE(end != std::string::npos);
  return page.substr(start, end - start);
}

} // namespace

TEST(html_a_page_carries_its_stylesheet) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page);
  EXPECT_TRUE(page.find("<style>") != std::string::npos);
  EXPECT_TRUE(page.find(".page") != std::string::npos);
}

TEST(html_a_page_may_leave_its_stylesheet_out) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page, false, false);
  EXPECT_TRUE(page.find("<style") == std::string::npos);
  EXPECT_TRUE(page.find("<table class=\"doc\">") != std::string::npos);
}

TEST(html_a_page_is_on_one_line_unless_pretty) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page, false, false);
  EXPECT_TRUE(page.find('\n') == std::string::npos);
}

TEST(html_a_pretty_page_keeps_its_stylesheet_as_it_is) {
  std::string compact;
  sourcemeta::blaze::to_html(order(), compact);
  std::string pretty;
  sourcemeta::blaze::to_html(order(), pretty, true);
  EXPECT_EQ(stylesheet_of(pretty), stylesheet_of(compact));
}

TEST(html_a_pretty_page_puts_each_block_on_a_line_of_its_own) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page, true, false);
  EXPECT_TRUE(page.find("\n  <h1>Order</h1>\n") != std::string::npos);
  EXPECT_EQ(page.back(), '\n');
}

TEST(html_the_page_is_appended_to_what_is_already_there) {
  std::string page{"before"};
  sourcemeta::blaze::to_html(order(), page);
  EXPECT_TRUE(page.starts_with("before<!doctype html>"));
}

TEST(html_two_shapes_that_share_an_anchor_are_refused) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": { "kind": "ref", "ref": "/$defs/party" },
    "shapes": [
      { "id": "/$defs/party", "name": "party", "value": { "kind": "string" } },
      { "id": "/$defs/party", "name": "party", "value": { "kind": "integer" } }
    ]
  })JSON")};

  std::string page;
  try {
    sourcemeta::blaze::to_html(documentation, page);
    FAIL();
  } catch (const sourcemeta::blaze::DocumentationError &error) {
    EXPECT_EQ(std::string{error.what()},
              "Two shapes would share one anchor on the page");
    EXPECT_EQ(error.subject(), "/$defs/party");
  }
}
