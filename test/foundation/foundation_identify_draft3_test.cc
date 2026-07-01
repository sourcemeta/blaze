#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "id": "https://sourcemeta.com/metaschema",
      "$schema": "http://json-schema.org/draft-03/schema#"
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(valid_one_hop) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "https://sourcemeta.com/metaschema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(document, test_resolver)};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(new_one_hop) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://sourcemeta.com/metaschema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(document, test_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(id_boolean_default_dialect) {
  const sourcemeta::core::JSON document{true};
  const auto id{
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(id.empty());
}

TEST(empty_object_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(id.empty());
}

TEST(valid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(new_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(default_dialect_precedence) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(base_dialect_shortcut) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3)};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(anonymize_with_base_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  sourcemeta::blaze::anonymize(document, base_dialect.value());

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(anonymize_with_base_dialect_no_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  sourcemeta::blaze::anonymize(document, base_dialect.value());

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(sibling_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(document, test_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(reidentify_replace) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_default_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema"
  })JSON");

  sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                sourcemeta::blaze::schema_resolver,
                                "http://json-schema.org/draft-03/schema#");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_replace_base_dialect_shortcut) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());

  sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                base_dialect.value());

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-new-id",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(reidentify_set_with_top_level_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "https://example.com/schema"
  })JSON");

  try {
    sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
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

TEST(reidentify_set_with_top_level_ref_and_extends) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "https://example.com/schema",
    "extends": { "type": "string" }
  })JSON");

  try {
    sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
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

TEST(id_empty_fragment_only) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "#",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(id_empty_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}
