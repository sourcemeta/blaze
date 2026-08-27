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

TEST(dialect_true) {
  const sourcemeta::core::JSON document{true};
  try {
    [[maybe_unused]] const auto dialect{DIALECT_OF(document)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(dialect_false) {
  const sourcemeta::core::JSON document{false};
  try {
    [[maybe_unused]] const auto dialect{DIALECT_OF(document)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(dialect_empty_object) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  try {
    [[maybe_unused]] const auto dialect{DIALECT_OF(document)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(dialect_empty_object_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto dialect{
      DIALECT_OF(document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_takes_precedence_over_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_without_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_takes_precedence_over_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-04/schema#"
  })JSON");
  const auto dialect{
      DIALECT_OF(document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-04/schema#");
}

TEST(override_non_string_falls_back_to_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": 42
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_null_falls_back_to_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema": null
  })JSON");
  const auto dialect{
      DIALECT_OF(document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_object_falls_back_to_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": {
      "value": "http://json-schema.org/draft-04/schema#"
    }
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_empty_string_falls_back_to_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": ""
  })JSON");
  const auto dialect{DIALECT_OF(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_empty_string_falls_back_to_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema": ""
  })JSON");
  const auto dialect{
      DIALECT_OF(document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}
