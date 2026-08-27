#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <string_view> // std::string_view

static auto
BASE_DIALECT_OF_SCHEMA(const sourcemeta::core::JSON &document,
                       const sourcemeta::blaze::SchemaResolver &resolver,
                       const std::string_view default_dialect = "")
    -> sourcemeta::blaze::SchemaBaseDialect {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};
  frame.analyse(document, sourcemeta::blaze::schema_walker, resolver,
                default_dialect);
  return frame.root_location().value().get().base_dialect;
}

TEST(jsonschema_draft_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/hyper-schema#",
    "type": "object"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3_Hyper);
}

TEST(jsonschema_draft_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3);
}

TEST(jsonschema_draft_jsonref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/json-ref#"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3_Hyper);
}

TEST(jsonschema_draft_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/links#"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3_Hyper);
}
