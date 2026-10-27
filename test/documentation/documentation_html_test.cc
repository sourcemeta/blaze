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

} // namespace

TEST(html_a_page_carries_no_stylesheet_and_no_document_around_it) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page);
  EXPECT_TRUE(page.starts_with("<h1>Order</h1>"));
  EXPECT_TRUE(page.find("<style") == std::string::npos);
  EXPECT_TRUE(page.find("<!doctype") == std::string::npos);
  EXPECT_TRUE(page.find("<title") == std::string::npos);
}

TEST(html_a_page_is_on_one_line_unless_pretty) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page);
  EXPECT_TRUE(page.find('\n') == std::string::npos);
}

TEST(html_a_pretty_page_puts_each_block_on_a_line_of_its_own) {
  std::string page;
  sourcemeta::blaze::to_html(order(), page, true);
  EXPECT_TRUE(page.starts_with("<h1>Order</h1>\n<div class=\"counts\">"));
  EXPECT_EQ(page.back(), '\n');
}

TEST(html_the_page_is_appended_to_what_is_already_there) {
  std::string page{"before"};
  sourcemeta::blaze::to_html(order(), page);
  EXPECT_TRUE(page.starts_with("before<h1>Order</h1>"));
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
