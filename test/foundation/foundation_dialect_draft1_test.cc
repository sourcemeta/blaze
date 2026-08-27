#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <string>      // std::string
#include <string_view> // std::string_view

static auto DIALECT_OF(const sourcemeta::core::JSON &document,
                       const std::string_view default_dialect = "")
    -> std::string {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, default_dialect);
  return std::string{frame.root_location().value().get().dialect};
}

TEST(jsonschema_draft_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/hyper-schema#",
    "type": "object"
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-01/hyper-schema#");
}

TEST(jsonschema_draft_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "object"
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-01/schema#");
}

TEST(jsonschema_draft_jsonref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/json-ref#"
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-01/json-ref#");
}

TEST(jsonschema_draft_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/links#"
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-01/links#");
}
