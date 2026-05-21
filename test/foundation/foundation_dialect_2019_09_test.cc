#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(Foundation_dialect_2019_09, jsonschema_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/schema");
}

TEST(Foundation_dialect_2019_09, jsonschema_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/hyper-schema");
}

TEST(Foundation_dialect_2019_09, jsonschema_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/links"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/links");
}

TEST(Foundation_dialect_2019_09, jsonschema_output) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/output/schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/output/schema");
}

TEST(Foundation_dialect_2019_09, jsonschema_output_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/output/hyper-schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect,
            "https://json-schema.org/draft/2019-09/output/hyper-schema");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_applicator) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/applicator"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/applicator");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_content) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/content"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/content");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_core) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/core"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/core");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_format) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/format"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/format");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/hyper-schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/hyper-schema");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_meta_data) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/meta-data"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/meta-data");
}

TEST(Foundation_dialect_2019_09, jsonschema_meta_validation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/validation"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/validation");
}
