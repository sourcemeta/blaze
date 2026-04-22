#include <gtest/gtest.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

TEST(Documentation_HTML, 2020_12_type_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(sourcemeta::blaze::to_html(documentation),
            "<table class=\"sourcemeta-blaze-documentation\">"
            "<thead><tr>"
            "<th>Path</th>"
            "<th>Type</th>"
            "<th>Required</th>"
            "<th>Constraints</th>"
            "<th>Notes</th>"
            "</tr></thead>"
            "<tbody>"
            "<tr data-index=\"1\">"
            "<td><code><em>(root)</em></code></td>"
            "<td>String</td>"
            "<td></td>"
            "<td></td>"
            "<td></td>"
            "</tr>"
            "</tbody>"
            "</table>");
}

TEST(Documentation_HTML, 2020_12_pattern_property_path) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" }
    }
  })JSON")};

  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(sourcemeta::blaze::to_html(documentation),
            "<table class=\"sourcemeta-blaze-documentation\">"
            "<thead><tr>"
            "<th>Path</th>"
            "<th>Type</th>"
            "<th>Required</th>"
            "<th>Constraints</th>"
            "<th>Notes</th>"
            "</tr></thead>"
            "<tbody>"
            "<tr data-index=\"1\">"
            "<td><code><em>(root)</em></code></td>"
            "<td>Object</td>"
            "<td></td>"
            "<td></td>"
            "<td></td>"
            "</tr>"
            "<tr data-index=\"2\">"
            "<td><code>/^x-</code></td>"
            "<td>String</td>"
            "<td></td>"
            "<td></td>"
            "<td></td>"
            "</tr>"
            "</tbody>"
            "</table>");
}

TEST(Documentation_HTML, draft4_pattern_property_path) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "patternProperties": {
      "^S_": { "type": "string" }
    }
  })JSON")};

  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(sourcemeta::blaze::to_html(documentation),
            "<table class=\"sourcemeta-blaze-documentation\">"
            "<thead><tr>"
            "<th>Path</th>"
            "<th>Type</th>"
            "<th>Required</th>"
            "<th>Constraints</th>"
            "<th>Notes</th>"
            "</tr></thead>"
            "<tbody>"
            "<tr data-index=\"1\">"
            "<td><code><em>(root)</em></code></td>"
            "<td>Object</td>"
            "<td></td>"
            "<td></td>"
            "<td></td>"
            "</tr>"
            "<tr data-index=\"2\">"
            "<td><code>/^S_</code></td>"
            "<td>String</td>"
            "<td></td>"
            "<td></td>"
            "<td></td>"
            "</tr>"
            "</tbody>"
            "</table>");
}

TEST(Documentation_HTML, 2020_12_external_ref) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/foo.json"
  })JSON")};

  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver)};

  EXPECT_EQ(sourcemeta::blaze::to_html(documentation),
            "<table class=\"sourcemeta-blaze-documentation\">"
            "<thead><tr>"
            "<th>Path</th>"
            "<th>Type</th>"
            "<th>Required</th>"
            "<th>Constraints</th>"
            "<th>Notes</th>"
            "</tr></thead>"
            "<tbody>"
            "<tr data-index=\"1\">"
            "<td><code><em>(root)</em></code></td>"
            "<td><a href=\"https://example.com/foo.json\">"
            "https://example.com/foo.json</a></td>"
            "<td></td>"
            "<td></td>"
            "<td></td>"
            "</tr>"
            "</tbody>"
            "</table>");
}
