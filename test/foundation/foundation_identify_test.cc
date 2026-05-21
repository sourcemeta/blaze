#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(Foundation_identify, boolean_no_dialect) {
  const sourcemeta::core::JSON document{true};
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, boolean_no_dialect_with_default_id) {
  const sourcemeta::core::JSON document{true};
  const auto id{
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "", "https://www.sourcemeta.com/foo")};
  EXPECT_EQ(id, "https://www.sourcemeta.com/foo");
}

TEST(Foundation_identify, empty_old_no_dollar_sign_id_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "http://json-schema.org/draft-00/schema#",
                                  "https://example.com/my-schema")};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(Foundation_identify, empty_dollar_sign_id_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema",
      "https://example.com/my-schema")};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(Foundation_identify, boolean_unknown_dialect) {
  const sourcemeta::core::JSON document{true};
  EXPECT_THROW(
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "https://www.sourcemeta.com/invalid-dialect"),
      sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_identify, empty_object_no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, empty_object_unknown_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  EXPECT_THROW(
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "https://www.sourcemeta.com/invalid-dialect"),
      sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_identify, object_with_dollar_id_with_no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, object_with_id_with_no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_boolean) {
  const sourcemeta::core::JSON document{true};
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_valid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_invalid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": false
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_valid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_invalid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": false
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_valid_dollar_id_and_invalid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "id": false
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_valid_id_and_invalid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$id": false
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_invalid_id_and_invalid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": 1,
    "id": false
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_matching_id_and_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_non_matching_id_and_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "http://example.com/my-schema",
    "id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_resolvable_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "http://example.com/my-schema",
    "id": "https://example.com/my-schema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(id, "http://example.com/my-schema");
}

TEST(Foundation_identify, strict_draft4_top_level_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/my-schema",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, loose_with_unresolvable_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://www.sourcemeta.com/invalid-dialect"
  })JSON");
  EXPECT_THROW(
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_identify, reidentify_boolean) {
  sourcemeta::core::JSON document{true};
  EXPECT_THROW(
      sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                    sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_identify, draft7_top_level_id_and_ref_strict) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/schema",
    "$ref": "foo"
  })JSON");

  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, draft7_ref_with_wrong_id_keyword_strict) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "id": "https://example.com/schema",
    "$ref": "foo"
  })JSON");

  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify, override_allowed_picks_dollarid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/via-id",
    "$id": "http://example.com/via-dollarid",
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-06/schema#"
  })JSON");

  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(id, "http://example.com/via-dollarid");
}

TEST(Foundation_identify, override_disallowed_picks_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/via-id",
    "$id": "http://example.com/via-dollarid",
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-06/schema#"
  })JSON");

  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver, "", "", false)};
  EXPECT_EQ(id, "http://example.com/via-id");
}

TEST(Foundation_identify, override_disallowed_with_unresolvable_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "http://example.com/foo",
    "x-sourcemeta-dialect-override-subschema":
      "https://example.com/does-not-exist"
  })JSON");

  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver, "", "", false)};
  EXPECT_EQ(id, "http://example.com/foo");
}
