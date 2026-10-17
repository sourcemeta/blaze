#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>

#include <string> // std::string

// How pages are drawn is checked against whole pages in the suite, under
// `suite/pages`. What stays here is what a page cannot show.

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
