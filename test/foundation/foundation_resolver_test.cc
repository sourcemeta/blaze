#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/uri.h>

#define EXPECT_SCHEMA(identifier)                                              \
  {                                                                            \
    const std::optional<sourcemeta::core::JSON> result{                        \
        sourcemeta::blaze::schema_resolver(identifier)};                       \
    EXPECT_TRUE(result.has_value());                                           \
    const sourcemeta::core::JSON &document{result.value()};                    \
    EXPECT_TRUE(sourcemeta::blaze::is_schema(document));                       \
    const auto id{sourcemeta::blaze::identify(                                 \
        document, sourcemeta::blaze::schema_resolver)};                        \
    EXPECT_EQ(sourcemeta::core::URI{id}.canonicalize().recompose(),            \
              sourcemeta::core::URI{identifier}.canonicalize().recompose());   \
  }

TEST(Foundation_resolver, jsonschema_2020_12) {
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/applicator");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/content");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/core");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/format-annotation");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/format-assertion");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/hyper-schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/meta-data");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/unevaluated");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/meta/validation");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/links");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/output/schema");

  // Just because a lot of people get this wrong
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/schema#");

  // Take HTTP versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/applicator")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/content")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/core")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/format-annotation")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/format-assertion")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/meta-data")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/unevaluated")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/meta/validation")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2020-12/output/schema")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_2019_09) {
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/applicator");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/content");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/core");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/format");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/hyper-schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/meta-data");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/meta/validation");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/output/schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/links");
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/output/hyper-schema");

  // Just because a lot of people get this wrong
  EXPECT_SCHEMA("https://json-schema.org/draft/2019-09/schema#");

  // Take HTTP versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/applicator")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/content")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/core")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/format")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/meta-data")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/meta/validation")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/output/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft/2019-09/output/hyper-schema")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft7) {
  EXPECT_SCHEMA("http://json-schema.org/draft-07/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-07/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-07/links#");
  EXPECT_SCHEMA("http://json-schema.org/draft-07/hyper-schema-output");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-07/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-07/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-07/links");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-07/hyper-schema-output")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft6) {
  EXPECT_SCHEMA("http://json-schema.org/draft-06/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-06/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-06/links#");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-06/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-06/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-06/links");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-06/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-06/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-06/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-06/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-06/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-06/links")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft4) {
  EXPECT_SCHEMA("http://json-schema.org/draft-04/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-04/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-04/links#");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-04/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-04/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-04/links");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-04/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-04/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-04/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-04/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-04/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-04/links")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft3) {
  EXPECT_SCHEMA("http://json-schema.org/draft-03/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-03/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-03/links#");
  EXPECT_SCHEMA("http://json-schema.org/draft-03/json-ref#");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-03/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-03/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-03/links");
  EXPECT_SCHEMA("http://json-schema.org/draft-03/json-ref");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/json-ref#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-03/json-ref")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft2) {
  EXPECT_SCHEMA("http://json-schema.org/draft-02/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-02/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-02/links#");
  EXPECT_SCHEMA("http://json-schema.org/draft-02/json-ref#");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-02/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-02/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-02/links");
  EXPECT_SCHEMA("http://json-schema.org/draft-02/json-ref");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/json-ref#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-02/json-ref")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft1) {
  EXPECT_SCHEMA("http://json-schema.org/draft-01/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-01/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-01/links#");
  EXPECT_SCHEMA("http://json-schema.org/draft-01/json-ref#");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-01/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-01/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-01/links");
  EXPECT_SCHEMA("http://json-schema.org/draft-01/json-ref");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/json-ref#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-01/json-ref")
                  .has_value());
}

TEST(Foundation_resolver, jsonschema_draft0) {
  EXPECT_SCHEMA("http://json-schema.org/draft-00/schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-00/hyper-schema#");
  EXPECT_SCHEMA("http://json-schema.org/draft-00/links#");
  EXPECT_SCHEMA("http://json-schema.org/draft-00/json-ref#");

  // Take canonicalized versions too
  EXPECT_SCHEMA("http://json-schema.org/draft-00/schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-00/hyper-schema");
  EXPECT_SCHEMA("http://json-schema.org/draft-00/links");
  EXPECT_SCHEMA("http://json-schema.org/draft-00/json-ref");

  // Take HTTPS versions too
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/hyper-schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/links#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/links")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/json-ref#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft-00/json-ref")
                  .has_value());
}

TEST(Foundation_resolver, openapi_3_1) {
  EXPECT_SCHEMA("https://spec.openapis.org/oas/3.1/dialect/base");
  EXPECT_SCHEMA("https://spec.openapis.org/oas/3.1/meta/base");
}

TEST(Foundation_resolver, openapi_3_2) {
  EXPECT_SCHEMA("https://spec.openapis.org/oas/3.2/dialect/2025-09-17");
  EXPECT_SCHEMA("https://spec.openapis.org/oas/3.2/meta/2025-09-17");
}

TEST(Foundation_resolver, idempotency) {
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/schema");
  EXPECT_SCHEMA("https://json-schema.org/draft/2020-12/schema");
}

TEST(Foundation_resolver, invalid) {
  const std::optional<sourcemeta::core::JSON> result{
      sourcemeta::blaze::schema_resolver("https://example.com/foobar")};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_resolver, is_known_schema_2020_12_http) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2020-12/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2020-12/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2020-12/hyper-schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2020-12/meta/applicator"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2020-12/meta/core"));
}

TEST(Foundation_resolver, is_known_schema_2019_09_http) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2019-09/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft/2019-09/schema#"));
}

TEST(Foundation_resolver, is_known_schema_draft7_https) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft-07/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft-07/schema"));
}

TEST(Foundation_resolver, is_known_schema_draft4_https) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft-04/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft-04/schema"));
}

TEST(Foundation_resolver, is_known_schema_draft0_https) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft-00/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft-00/schema"));
}

TEST(Foundation_resolver, is_known_schema_2020_12) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2020-12/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2020-12/hyper-schema"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/hyper-schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2020-12/meta/applicator"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/meta/applicator")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2020-12/meta/core"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2020-12/meta/core")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_2019_09) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2019-09/schema"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2019-09/schema")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://json-schema.org/draft/2019-09/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://json-schema.org/draft/2019-09/schema#")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_draft7) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-07/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft-07/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-07/schema"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft-07/schema")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_draft4) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-04/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft-04/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-04/schema"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft-04/schema")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_draft0) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-00/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft-00/schema#")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-00/schema"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "http://json-schema.org/draft-00/schema")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_openapi_3_1) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://spec.openapis.org/oas/3.1/dialect/base"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://spec.openapis.org/oas/3.1/dialect/base")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://spec.openapis.org/oas/3.1/meta/base"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://spec.openapis.org/oas/3.1/meta/base")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_openapi_3_2) {
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://spec.openapis.org/oas/3.2/dialect/2025-09-17"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://spec.openapis.org/oas/3.2/dialect/2025-09-17")
                  .has_value());
  EXPECT_TRUE(sourcemeta::blaze::is_known_schema(
      "https://spec.openapis.org/oas/3.2/meta/2025-09-17"));
  EXPECT_TRUE(sourcemeta::blaze::schema_resolver(
                  "https://spec.openapis.org/oas/3.2/meta/2025-09-17")
                  .has_value());
}

TEST(Foundation_resolver, is_known_schema_unknown) {
  EXPECT_FALSE(
      sourcemeta::blaze::is_known_schema("https://example.com/foobar"));
  EXPECT_FALSE(sourcemeta::blaze::schema_resolver("https://example.com/foobar")
                   .has_value());
  EXPECT_FALSE(sourcemeta::blaze::is_known_schema(""));
  EXPECT_FALSE(sourcemeta::blaze::schema_resolver("").has_value());
  EXPECT_FALSE(sourcemeta::blaze::is_known_schema(
      "http://json-schema.org/draft-99/schema"));
  EXPECT_FALSE(sourcemeta::blaze::schema_resolver(
                   "http://json-schema.org/draft-99/schema")
                   .has_value());
}

TEST(Foundation_resolver, is_official_schema_2020_12) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft/2020-12/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/hyper-schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/applicator"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/core"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/format-annotation"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/format-assertion"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/hyper-schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/meta-data"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/unevaluated"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/meta/validation"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/links"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2020-12/output/schema"));
}

TEST(Foundation_resolver, is_official_schema_2019_09) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft/2019-09/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/hyper-schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/meta/applicator"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/meta/core"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/meta/format"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/meta/hyper-schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/meta/meta-data"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/meta/validation"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/links"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/output/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft/2019-09/output/hyper-schema"));
}

TEST(Foundation_resolver, is_official_schema_draft7) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-07/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-07/schema"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "https://json-schema.org/draft-07/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-07/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-07/links#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-07/hyper-schema-output"));
}

TEST(Foundation_resolver, is_official_schema_draft6) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-06/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-06/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-06/links#"));
}

TEST(Foundation_resolver, is_official_schema_draft4) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-04/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-04/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-04/links#"));
}

TEST(Foundation_resolver, is_official_schema_draft3) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-03/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-03/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-03/links#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-03/json-ref#"));
}

TEST(Foundation_resolver, is_official_schema_draft2) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-02/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-02/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-02/links#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-02/json-ref#"));
}

TEST(Foundation_resolver, is_official_schema_draft1) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-01/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-01/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-01/links#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-01/json-ref#"));
}

TEST(Foundation_resolver, is_official_schema_draft0) {
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-00/schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-00/hyper-schema#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-00/links#"));
  EXPECT_TRUE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-00/json-ref#"));
}

TEST(Foundation_resolver, is_official_schema_openapi_3_1) {
  EXPECT_FALSE(sourcemeta::blaze::is_official_schema(
      "https://spec.openapis.org/oas/3.1/dialect/base"));
  EXPECT_FALSE(sourcemeta::blaze::is_official_schema(
      "https://spec.openapis.org/oas/3.1/meta/base"));
}

TEST(Foundation_resolver, is_official_schema_openapi_3_2) {
  EXPECT_FALSE(sourcemeta::blaze::is_official_schema(
      "https://spec.openapis.org/oas/3.2/dialect/2025-09-17"));
  EXPECT_FALSE(sourcemeta::blaze::is_official_schema(
      "https://spec.openapis.org/oas/3.2/meta/2025-09-17"));
}

TEST(Foundation_resolver, is_official_schema_unknown) {
  EXPECT_FALSE(
      sourcemeta::blaze::is_official_schema("https://example.com/foobar"));
  EXPECT_FALSE(sourcemeta::blaze::is_official_schema(""));
  EXPECT_FALSE(sourcemeta::blaze::is_official_schema(
      "http://json-schema.org/draft-99/schema"));
}
