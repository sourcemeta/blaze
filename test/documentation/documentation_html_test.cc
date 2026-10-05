#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>

#include <sourcemeta/core/jsonschema.h>
#include <string> // std::string

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

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
  EXPECT_EQ(page, "<div class=\"sourcemeta-blaze-documentation\">"
                  "<h1>Order</h1>"
                  "<p>A single order</p>"
                  "<section id=\"root\">"
                  "<h2>What this file holds</h2>"
                  "<table class=\"sourcemeta-blaze-documentation\">"
                  "<tr><th>Property</th><th>What may go in it</th>"
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

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
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

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
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

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
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
  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
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

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
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

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
  EXPECT_EQ(page, "<div class=\"sourcemeta-blaze-documentation\">"
                  "<h1>Order</h1>"
                  "<section id=\"root\">"
                  "<h2>What this file holds</h2>"
                  "<table class=\"sourcemeta-blaze-documentation\">"
                  "<tr><th>Property</th><th>What may go in it</th>"
                  "<th>Required</th><th>Notes</th></tr>"
                  "<tr><td><code>bad</code></td>"
                  "<td>described elsewhere, at javascript:alert(1)</td>"
                  "<td>no</td><td></td></tr>"
                  "<tr><td><code>good</code></td>"
                  "<td><a href=\"https://example.com/party\">"
                  "described elsewhere</a></td><td>no</td><td></td></tr>"
                  "</table>"
                  "</section>"
                  "</div>");
}

TEST(html_a_property_that_is_a_group_is_written_out) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "shipTo",
          "value": {
            "kind": "object",
            "description": "Where it goes.",
            "fields": [
              { "name": "city", "required": true, "value": { "kind": "string" } }
            ] } }
      ]
    }
  })JSON")};

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
  // The table could only name it, so what it holds follows the table.
  EXPECT_TRUE(page.find("<code>city</code>") != std::string::npos);
  EXPECT_TRUE(page.find("Where it goes.") != std::string::npos);
}

TEST(html_each_form_of_a_choice_is_written_out) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Payment",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "choice",
      "options": [
        { "kind": "object",
          "fields": [
            { "name": "card", "required": true, "value": { "kind": "string" } }
          ] },
        { "kind": "object",
          "fields": [
            { "name": "invoice", "required": true,
              "value": { "kind": "string" } }
          ] }
      ]
    }
  })JSON")};

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
  EXPECT_TRUE(page.find("<code>card</code>") != std::string::npos);
  EXPECT_TRUE(page.find("<code>invoice</code>") != std::string::npos);
}

TEST(html_what_a_list_entry_must_be_is_written_out) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "tags",
          "value": {
            "kind": "array",
            "item": { "kind": "string", "length": { "max": 8 } } } }
      ]
    }
  })JSON")};

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
  EXPECT_TRUE(page.find("Every entry of the list is") != std::string::npos);
  EXPECT_TRUE(page.find("at most 8") != std::string::npos);
}

TEST(html_a_condition_shows_what_it_asks_and_what_follows) {
  const auto documentation{sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2026:table-format/2",
    "title": "Order",
    "language": "https://json-schema.org/draft/2020-12/schema",
    "root": {
      "kind": "object",
      "fields": [
        { "name": "kind", "value": { "kind": "string" } }
      ],
      "conditions": [
        { "when": {
            "kind": "object",
            "fields": [
              { "name": "kind", "required": true,
                "value": { "kind": "enum", "values": ["gift"] } }
            ] },
          "then": {
            "kind": "object",
            "fields": [
              { "name": "note", "required": true,
                "value": { "kind": "string" } }
            ] } }
      ]
    }
  })JSON")};

  std::string page;
  sourcemeta::blaze::to_html(documentation, page);
  EXPECT_TRUE(page.find("In a certain case") != std::string::npos);
  EXPECT_TRUE(page.find("<code>note</code>") != std::string::npos);
}
