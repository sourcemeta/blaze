#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(Foundation_base_dialect_draft0, jsonschema_draft_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/hyper-schema#",
    "type": "object"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
}

TEST(Foundation_base_dialect_draft0, jsonschema_draft_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
}

TEST(Foundation_base_dialect_draft0, jsonschema_draft_jsonref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/json-ref#"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
}

TEST(Foundation_base_dialect_draft0, jsonschema_draft_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/links#"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
}
