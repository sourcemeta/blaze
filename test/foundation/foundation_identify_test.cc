#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <string_view> // std::string_view

#include <string> // std::string

static auto IDENTIFY_OF(const sourcemeta::core::JSON &document,
                        const sourcemeta::blaze::SchemaResolver &resolver,
                        const std::string_view default_dialect = "",
                        const std::string_view default_id = "") -> std::string {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};
  frame.analyse(document, sourcemeta::blaze::schema_walker, resolver,
                default_dialect, default_id);
  return frame.root();
}

TEST(boolean_no_dialect) {
  const sourcemeta::core::JSON document{true};
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(boolean_no_dialect_with_default_id) {
  const sourcemeta::core::JSON document{true};
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver, "",
                    "https://www.sourcemeta.com/foo")};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(empty_old_no_dollar_sign_id_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver,
                            "http://json-schema.org/draft-00/schema#",
                            "https://example.com/my-schema")};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(empty_dollar_sign_id_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver,
                            "https://json-schema.org/draft/2020-12/schema",
                            "https://example.com/my-schema")};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(boolean_unknown_dialect) {
  const sourcemeta::core::JSON document{true};
  try {
    IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver,
                "https://www.sourcemeta.com/invalid-dialect");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(empty_object_no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(empty_object_unknown_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  try {
    IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver,
                "https://www.sourcemeta.com/invalid-dialect");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(object_with_dollar_id_with_no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(object_with_id_with_no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_boolean) {
  const sourcemeta::core::JSON document{true};
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_valid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_invalid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": false
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_valid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_invalid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": false
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_valid_dollar_id_and_invalid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "id": false
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_valid_id_and_invalid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$id": false
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_invalid_id_and_invalid_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": 1,
    "id": false
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_matching_id_and_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "id": "https://example.com/my-schema"
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_non_matching_id_and_dollar_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "http://example.com/my-schema",
    "id": "https://example.com/my-schema"
  })JSON");
  try {
    [[maybe_unused]] const auto id{
        IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(loose_with_resolvable_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "http://example.com/my-schema",
    "id": "https://example.com/my-schema"
  })JSON");
  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver,
                            "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(id, "http://example.com/my-schema");
}

TEST(strict_draft4_top_level_ref) {
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
  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(loose_with_unresolvable_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://www.sourcemeta.com/invalid-dialect"
  })JSON");
  try {
    IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(reidentify_boolean) {
  sourcemeta::core::JSON document{true};
  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(draft7_top_level_id_and_ref_strict) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/schema",
    "$ref": "foo"
  })JSON");

  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(draft7_ref_with_wrong_id_keyword_strict) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "id": "https://example.com/schema",
    "$ref": "foo"
  })JSON");

  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(override_allowed_picks_dollarid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/via-id",
    "$id": "http://example.com/via-dollarid",
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-06/schema#"
  })JSON");

  const auto id{IDENTIFY_OF(document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(id, "http://example.com/via-dollarid");
}
