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

TEST(jsonschema_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/hyper-schema",
    "type": "object"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12_Hyper);
}

TEST(jsonschema_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/links"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_output) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/output/schema"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_applicator) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/applicator"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_content) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/content"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_core) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/core"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_format_annotation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/format-annotation"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_format_assertion) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/format-assertion"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/hyper-schema"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12_Hyper);
}

TEST(jsonschema_meta_meta_data) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/meta-data"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_unevaluated) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/unevaluated"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(jsonschema_meta_validation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/validation"
  })JSON");
  const auto base_dialect{
      BASE_DIALECT_OF_SCHEMA(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}
