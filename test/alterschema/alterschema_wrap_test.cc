#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>

#include <utility> // std::pair

static auto wrap_schema(const sourcemeta::core::JSON &schema,
                        const sourcemeta::core::Pointer &pointer,
                        std::string_view default_dialect = "")
    -> std::pair<sourcemeta::core::JSON, sourcemeta::core::Pointer> {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, default_dialect);
  const auto location{
      frame.traverse(sourcemeta::core::to_weak_pointer(pointer))};
  assert(location.has_value());
  sourcemeta::core::WeakPointer base;
  auto result{sourcemeta::blaze::wrap(schema, frame, location.value().get(),
                                      sourcemeta::blaze::schema_resolver,
                                      base)};
  return {std::move(result), sourcemeta::core::to_pointer(base)};
}

TEST(schema_without_identifier) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"items"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_without_identifier_and_relative_uri) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "$ref": "relative"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"items"})};

  // We don't want the relative reference to be resolved against
  // an absolute base
  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "__sourcemeta-core-wrap__#/items",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "__sourcemeta-core-wrap__",
        "items": {
          "$ref": "relative"
        }
      }
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_EQ(base.size(), 1);
  EXPECT_TRUE(base.at(0).is_property());
  EXPECT_EQ(base.at(0).to_property(), "$ref");
}

TEST(schema_without_identifier_with_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(
      schema, {"items"}, "https://json-schema.org/draft/2020-12/schema")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_without_identifier_with_different_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(
      schema, {"items"}, "https://json-schema.org/draft/2019-09/schema")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_without_identifier_empty_pointer) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_without_identifier_without_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "items": {
      "type": "string"
    }
  })JSON")};

  try {
    wrap_schema(schema, {"items"});
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(schema_with_identifier) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com/1",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"items"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_with_identifier_trailing_empty_fragment) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com/1#",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"items"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_with_identifier_different_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com/1",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(
      schema, {"items"}, "https://json-schema.org/draft/2019-09/schema")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_with_identifier_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://sourcemeta.com/1",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(
      schema, {"items"}, "https://json-schema.org/draft/2019-09/schema")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_with_identifier_empty_pointer) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com/1",
    "items": {
      "type": "string"
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com/1",
    "items": {
      "type": "string"
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(schema_with_identifier_no_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://sourcemeta.com/1",
    "items": {
      "type": "string"
    }
  })JSON")};

  try {
    wrap_schema(schema, {"items"});
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(draft4_standalone_ref_with_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com"
  })JSON")};

  const auto [result, base]{
      wrap_schema(schema, {}, "http://json-schema.org/draft-04/schema#")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "https://example.com"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft4_top_level_ref_with_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft4_top_level_ref_without_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft6_standalone_ref_with_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com"
  })JSON")};

  const auto [result, base]{
      wrap_schema(schema, {}, "http://json-schema.org/draft-06/schema#")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "https://example.com"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft6_top_level_ref_with_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft6_top_level_ref_without_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft7_standalone_ref_with_default_dialect) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://example.com"
  })JSON")};

  const auto [result, base]{
      wrap_schema(schema, {}, "http://json-schema.org/draft-07/schema#")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://example.com"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft7_top_level_ref_with_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(draft7_top_level_ref_without_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2019_09_top_level_ref_with_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2019_09_top_level_ref_with_id_defs_foo) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"$defs", "foo"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2019_09_top_level_ref_without_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2019_09_top_level_ref_without_id_defs_foo) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"$defs", "foo"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_top_level_ref_with_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_top_level_ref_with_id_defs_foo) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"$defs", "foo"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_top_level_ref_without_id_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_top_level_ref_without_id_defs_foo) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {}
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"$defs", "foo"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(subschema_with_direct_ref) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$defs": {
      "string": { "type": "string" }
    },
    "properties": {
      "foo": { "$ref": "#/$defs/string" }
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"properties", "foo"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com#/properties/foo",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com",
        "$defs": {
          "string": { "type": "string" }
        },
        "properties": {
          "foo": { "$ref": "#/$defs/string" }
        }
      }
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_EQ(base.size(), 1);
  EXPECT_TRUE(base.at(0).is_property());
  EXPECT_EQ(base.at(0).to_property(), "$ref");
}

TEST(subschema_with_nested_ref) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$defs": {
      "string": { "type": "string" }
    },
    "properties": {
      "foo": {
        "type": "object",
        "properties": {
          "bar": { "$ref": "#/$defs/string" }
        }
      }
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"properties", "foo"})};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com#/properties/foo",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com",
        "$defs": {
          "string": { "type": "string" }
        },
        "properties": {
          "foo": {
            "type": "object",
            "properties": {
              "bar": { "$ref": "#/$defs/string" }
            }
          }
        }
      }
    }
  })JSON")};

  EXPECT_EQ(result, expected);
  EXPECT_EQ(base.size(), 1);
  EXPECT_TRUE(base.at(0).is_property());
  EXPECT_EQ(base.at(0).to_property(), "$ref");
}

TEST(2020_12_boolean_subschema_true) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": {
      "foo": true
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"properties", "foo"})};

  const auto expected{sourcemeta::core::parse_json("true")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_boolean_subschema_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": {
      "foo": false
    }
  })JSON")};

  const auto [result, base]{wrap_schema(schema, {"properties", "foo"})};

  const auto expected{sourcemeta::core::parse_json("false")};

  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_top_level_boolean_true) {
  const auto schema{sourcemeta::core::parse_json("true")};
  const auto [result, base]{
      wrap_schema(schema, {}, "https://json-schema.org/draft/2020-12/schema")};
  const auto expected{sourcemeta::core::parse_json("true")};
  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}

TEST(2020_12_top_level_boolean_false) {
  const auto schema{sourcemeta::core::parse_json("false")};
  const auto [result, base]{
      wrap_schema(schema, {}, "https://json-schema.org/draft/2020-12/schema")};
  const auto expected{sourcemeta::core::parse_json("false")};
  EXPECT_EQ(result, expected);
  EXPECT_TRUE(base.empty());
}
