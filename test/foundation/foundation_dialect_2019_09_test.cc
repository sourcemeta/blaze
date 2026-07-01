#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(jsonschema_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/schema");
}

TEST(jsonschema_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/hyper-schema");
}

TEST(jsonschema_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/links"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/links");
}

TEST(jsonschema_output) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/output/schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/output/schema");
}

TEST(jsonschema_output_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/output/hyper-schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect,
            "https://json-schema.org/draft/2019-09/output/hyper-schema");
}

TEST(jsonschema_meta_applicator) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/applicator"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/applicator");
}

TEST(jsonschema_meta_content) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/content"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/content");
}

TEST(jsonschema_meta_core) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/core"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/core");
}

TEST(jsonschema_meta_format) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/format"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/format");
}

TEST(jsonschema_meta_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/hyper-schema"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/hyper-schema");
}

TEST(jsonschema_meta_meta_data) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/meta-data"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/meta-data");
}

TEST(jsonschema_meta_validation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/meta/validation"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "https://json-schema.org/draft/2019-09/meta/validation");
}
