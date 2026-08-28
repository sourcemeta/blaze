#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

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

TEST(reidentify_replace_2020_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_2020_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_2020_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_2020_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref_2020_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_2019_09) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_2019_09) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_2019_09) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2019-09/schema");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_2019_09) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref_2019_09) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com/schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-07/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://example.com/schema"
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_set_with_top_level_ref_and_allof_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://example.com/schema",
    "allOf": [ { "type": "string" } ]
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_replace_draft6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-06/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref_draft6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "https://example.com/schema"
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_set_with_top_level_ref_and_allof_draft6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "https://example.com/schema",
    "allOf": [ { "type": "string" } ]
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_replace_draft4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-04/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref_draft4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "https://example.com/schema"
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_set_with_top_level_ref_and_allof_draft4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "https://example.com/schema",
    "allOf": [ { "type": "string" } ]
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_replace_draft3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-03/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref_draft3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "https://example.com/schema"
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_set_with_top_level_ref_and_extends_draft3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "https://example.com/schema",
    "extends": { "type": "string" }
  })JSON");

  try {
    sourcemeta::blaze::schema_reidentify(document,
                                         "https://example.com/my-new-id",
                                         sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_STREQ(
        error.what(),
        "A schema with a top-level `$ref` in JSON Schema Draft 7 and older "
        "dialects ignores every sibling keywords (like identifiers and "
        "meta-schema declarations) and therefore many operations, like "
        "bundling, are not possible without undefined behavior");
  }
}

TEST(reidentify_replace_draft2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-02/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_draft1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-01/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_draft0) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_draft0) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::blaze::schema_reidentify(document,
                                       "https://example.com/my-new-id",
                                       sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect_draft0) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id",
      sourcemeta::blaze::schema_resolver,
      "http://json-schema.org/draft-00/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut_draft0) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const auto base_dialect{frame.root_location().value().get().base_dialect};

  sourcemeta::blaze::schema_reidentify(
      document, "https://example.com/my-new-id", base_dialect);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}
