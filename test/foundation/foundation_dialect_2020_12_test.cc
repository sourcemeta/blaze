#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(jsonschema_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/schema");
}

TEST(jsonschema_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/hyper-schema",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/hyper-schema");
}

TEST(jsonschema_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/links"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/links");
}

TEST(jsonschema_output) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/output/schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/output/schema");
}

TEST(jsonschema_meta_applicator) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/applicator"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/applicator");
}

TEST(jsonschema_meta_content) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/content"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/content");
}

TEST(jsonschema_meta_core) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/core"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/core");
}

TEST(jsonschema_meta_format_annotation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/format-annotation"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect,
            "https://json-schema.org/draft/2020-12/meta/format-annotation");
}

TEST(jsonschema_meta_format_assertion) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/format-assertion"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect,
            "https://json-schema.org/draft/2020-12/meta/format-assertion");
}

TEST(jsonschema_meta_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/hyper-schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/hyper-schema");
}

TEST(jsonschema_meta_meta_data) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/meta-data"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/meta-data");
}

TEST(jsonschema_meta_unevaluated) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/unevaluated"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/unevaluated");
}

TEST(jsonschema_meta_validation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/meta/validation"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2020-12/meta/validation");
}
