#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(dialect_true) {
  const sourcemeta::core::JSON document{true};
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_TRUE(dialect.empty());
}

TEST(dialect_false) {
  const sourcemeta::core::JSON document{false};
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_TRUE(dialect.empty());
}

TEST(dialect_empty_object) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_TRUE(dialect.empty());
}

TEST(dialect_empty_object_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto dialect{sourcemeta::blaze::dialect(
      document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_takes_precedence_over_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_without_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_takes_precedence_over_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-04/schema#"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(
      document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-04/schema#");
}

TEST(override_non_string_falls_back_to_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": 42
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_null_falls_back_to_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema": null
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(
      document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_object_falls_back_to_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": {
      "value": "http://json-schema.org/draft-04/schema#"
    }
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_empty_string_falls_back_to_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema": ""
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(override_empty_string_falls_back_to_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema": ""
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(
      document, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}
