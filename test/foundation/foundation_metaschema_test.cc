#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(Foundation_metaschema, example_2020_12) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto metaschema{sourcemeta::blaze::metaschema(
      schema, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(metaschema.is_object());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/schema")
                  .has_value());
  EXPECT_EQ(metaschema, sourcemeta::blaze::schema_resolver(
                            "https://json-schema.org/draft/2020-12/schema")
                            .value());
}

TEST(Foundation_metaschema, with_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string"
  })JSON")};

  const auto metaschema{sourcemeta::blaze::metaschema(
      schema, sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_TRUE(metaschema.is_object());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/schema")
                  .has_value());
  EXPECT_EQ(metaschema, sourcemeta::blaze::schema_resolver(
                            "https://json-schema.org/draft/2020-12/schema")
                            .value());
}

TEST(Foundation_metaschema, no_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::metaschema(schema, sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaUnknownDialectError);
}

TEST(Foundation_metaschema, unknown_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com",
    "type": "string"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::metaschema(schema, sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_metaschema, override_returns_override_metaschema) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto metaschema{sourcemeta::blaze::metaschema(
      schema, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(metaschema.is_object());
  EXPECT_EQ(metaschema, sourcemeta::blaze::schema_resolver(
                            "https://json-schema.org/draft/2020-12/schema")
                            .value());
}

TEST(Foundation_metaschema, override_only_returns_override_metaschema) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto metaschema{sourcemeta::blaze::metaschema(
      schema, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(metaschema.is_object());
  EXPECT_EQ(metaschema, sourcemeta::blaze::schema_resolver(
                            "https://json-schema.org/draft/2020-12/schema")
                            .value());
}

TEST(Foundation_metaschema, override_unresolvable) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": "https://example.com/missing",
    "type": "string"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::metaschema(schema, sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaResolutionError);
}
