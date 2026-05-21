#include <gtest/gtest.h>

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

TEST(Foundation_identify_draft3, valid_one_hop) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "https://sourcemeta.com/metaschema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(document, test_resolver)};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(Foundation_identify_draft3, new_one_hop) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://sourcemeta.com/metaschema"
  })JSON");
  const auto id{sourcemeta::blaze::identify(document, test_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify_draft3, id_boolean_default_dialect) {
  const sourcemeta::core::JSON document{true};
  const auto id{
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify_draft3, empty_object_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  const auto id{
      sourcemeta::blaze::identify(document, sourcemeta::blaze::schema_resolver,
                                  "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify_draft3, valid_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(Foundation_identify_draft3, new_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify_draft3, default_dialect_precedence) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(Foundation_identify_draft3, base_dialect_shortcut) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3)};
  EXPECT_EQ(id, "https://example.com/my-schema");
}

TEST(Foundation_identify_draft3, anonymize_with_base_dialect) {
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

TEST(Foundation_identify_draft3, anonymize_with_base_dialect_no_id) {
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

TEST(Foundation_identify_draft3, sibling_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/my-schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(document, test_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify_draft3, reidentify_replace) {
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

TEST(Foundation_identify_draft3, reidentify_set) {
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

TEST(Foundation_identify_draft3, reidentify_replace_default_dialect) {
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

TEST(Foundation_identify_draft3, reidentify_replace_base_dialect_shortcut) {
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

TEST(Foundation_identify_draft3, reidentify_set_with_top_level_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "https://example.com/schema"
  })JSON");

  EXPECT_THROW(
      sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                    sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaReferenceObjectResourceError);
}

TEST(Foundation_identify_draft3,
     reidentify_set_with_top_level_ref_and_extends) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "https://example.com/schema",
    "extends": { "type": "string" }
  })JSON");

  EXPECT_THROW(
      sourcemeta::blaze::reidentify(document, "https://example.com/my-new-id",
                                    sourcemeta::blaze::schema_resolver),
      sourcemeta::blaze::SchemaReferenceObjectResourceError);
}

TEST(Foundation_identify_draft3, id_empty_fragment_only) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "#",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}

TEST(Foundation_identify_draft3, id_empty_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");
  const auto id{sourcemeta::blaze::identify(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(id.empty());
}
