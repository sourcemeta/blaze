#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

TEST(html_a_document_of_fields) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "description": "A single order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "id", "required": true,
          "value": { "kind": "string", "format": "uuid" } }
      ]
    }
  })JSON")};

  EXPECT_EQ(sourcemeta::blaze::to_html(documentation),
            "<div class=\"sourcemeta-blaze-documentation\">"
            "<h1>Order</h1>"
            "<p>A single order</p>"
            "<section id=\"root\">"
            "<h2>What this file holds</h2>"
            "<table class=\"sourcemeta-blaze-documentation\">"
            "<tr><th>Field</th><th>What may go in it</th>"
            "<th>Required</th><th>Notes</th></tr>"
            "<tr><td><code>id</code></td><td>text</td><td>yes</td>"
            "<td>written as uuid</td></tr>"
            "</table>"
            "</section>"
            "</div>");
}

TEST(html_links_to_a_shape) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [ { "name": "buyer", "value": { "kind": "ref", "ref": "/$defs/party" } } ]
    },
    "shapes": [
      { "id": "/$defs/party", "name": "party",
        "value": { "kind": "object",
                   "fields": [ { "name": "name", "value": { "kind": "string" } } ] } }
    ]
  })JSON")};

  const auto page{sourcemeta::blaze::to_html(documentation)};
  EXPECT_TRUE(page.find("<a href=\"#shape-defs-party-") != std::string::npos);
  EXPECT_TRUE(page.find("<section id=\"shape-defs-party-") !=
              std::string::npos);
}

TEST(html_two_shapes_that_read_alike_get_two_anchors) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Collide",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": { "kind": "any" },
    "shapes": [
      { "id": "/$defs/my_field", "name": "my_field", "value": { "kind": "string" } },
      { "id": "/$defs/my-field", "name": "my-field", "value": { "kind": "integer" } }
    ]
  })JSON")};

  const auto page{sourcemeta::blaze::to_html(documentation)};
  const auto first{page.find("<section id=\"shape-defs-my-field-")};
  EXPECT_TRUE(first != std::string::npos);
  const auto second{page.find("<section id=\"shape-defs-my-field-", first + 1)};
  EXPECT_TRUE(second != std::string::npos);
  const auto first_anchor{page.substr(first, 60)};
  const auto second_anchor{page.substr(second, 60)};
  EXPECT_NE(first_anchor, second_anchor);
}

TEST(html_escapes_what_an_author_wrote) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "<script>alert(1)</script>",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": { "kind": "string" }
  })JSON")};

  const auto page{sourcemeta::blaze::to_html(documentation)};
  EXPECT_TRUE(page.find("<script>") == std::string::npos);
  EXPECT_TRUE(page.find("&lt;script&gt;") != std::string::npos);
}

TEST(html_of_a_schema_end_to_end) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Order",
    "type": "object",
    "properties": { "id": { "type": "string" } },
    "required": [ "id" ]
  })JSON")};

  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};
  const auto page{sourcemeta::blaze::to_html(documentation)};
  EXPECT_TRUE(page.find("<h1>Order</h1>") != std::string::npos);
  EXPECT_TRUE(page.find("<code>id</code>") != std::string::npos);
}

TEST(html_a_list_of_a_shape_links_to_it) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "items",
          "value": { "kind": "array", "item": { "kind": "ref", "ref": "/$defs/line" } } }
      ]
    },
    "shapes": [
      { "id": "/$defs/line", "name": "line",
        "value": { "kind": "object",
                   "fields": [ { "name": "sku", "value": { "kind": "string" } } ] } }
    ]
  })JSON")};

  const auto page{sourcemeta::blaze::to_html(documentation)};
  EXPECT_TRUE(page.find("a list of <a href=\"#shape-defs-line-") !=
              std::string::npos);
}

TEST(html_an_address_worth_not_following_is_not_a_link) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "bad",
          "value": { "kind": "external", "href": "javascript:alert(1)" } },
        { "name": "good",
          "value": { "kind": "external", "href": "https://example.com/party" } }
      ]
    }
  })JSON")};

  const auto page{sourcemeta::blaze::to_html(documentation)};
  EXPECT_TRUE(page.find("href=\"javascript") == std::string::npos);
  EXPECT_TRUE(page.find("javascript:alert(1)") != std::string::npos);
  EXPECT_TRUE(page.find("href=\"https://example.com/party\"") !=
              std::string::npos);
}
