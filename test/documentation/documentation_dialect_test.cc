#include "documentation_test_utils.h"

TEST(draft4_an_exclusive_bound_without_its_bound_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "exclusiveMinimum": true
  })JSON",
      "The `exclusiveMinimum` keyword needs a `minimum` in Draft 3 and Draft 4",
      "", "");
}

TEST(draft3_an_exclusive_bound_without_its_bound_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "exclusiveMaximum": true
  })JSON",
      "The `exclusiveMaximum` keyword needs a `maximum` in Draft 3 and Draft 4",
      "", "");
}

TEST(draft2_hyper_schema_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-02/hyper-schema#",
    "type": "string"
  })JSON",
      "This module describes JSON Schema Draft 3 to 2020-12", "", "");
}

TEST(a_schema_without_a_dialect_is_read_as_the_default) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "type": "array",
    "prefixItems": [ { "type": "string" } ]
  })JSON")};
  const auto documentation{sourcemeta::blaze::to_documentation(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  expect_fits_the_format(documentation);
  EXPECT_EQ(documentation.at("language").to_string(),
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(documentation.at("root"), sourcemeta::core::parse_json(R"JSON({
    "kind": "array",
    "slots": [ { "kind": "string" } ]
  })JSON"));
}
