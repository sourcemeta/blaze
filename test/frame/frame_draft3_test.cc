#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "frame_test_utils.h"

#define EXPECT_FRAME_STATIC_DRAFT3_POINTER(                                    \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_POINTER(frame, reference, root_id, expected_pointer,     \
                              "http://json-schema.org/draft-03/schema#",       \
                              JSON_Schema_Draft_3, expected_base,              \
                              expected_relative_pointer, expected_parent,      \
                              expected_property_name, expected_orphan);

#define EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(                                   \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_RESOURCE(frame, reference, root_id, expected_pointer,    \
                               "http://json-schema.org/draft-03/schema#",      \
                               JSON_Schema_Draft_3, expected_base,             \
                               expected_relative_pointer, expected_parent,     \
                               expected_property_name, expected_orphan);

#define EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(                                  \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, reference, root_id, expected_pointer,   \
                                "http://json-schema.org/draft-03/schema#",     \
                                JSON_Schema_Draft_3, expected_base,            \
                                expected_relative_pointer, expected_parent,    \
                                expected_property_name, expected_orphan);

TEST(anonymous_with_nested_schema_resource) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "additionalProperties": { "id": "https://example.com" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 6);

  EXPECT_ANONYMOUS_FRAME_STATIC_RESOURCE(
      frame, "https://example.com", "/additionalProperties",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);

  // JSON Pointers

  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "https://example.com#/id", "/additionalProperties/id",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/additionalProperties", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/additionalProperties", "/additionalProperties",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/additionalProperties/id", "/additionalProperties/id",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/additionalProperties", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/additionalProperties",
                                  frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "", "https://example.com");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com",
                                  "https://example.com");
}

TEST(empty_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
}

TEST(empty_schema_trailing_slash) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema#",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
}

TEST(one_level_applicators_without_identifiers) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": { "type": "string" },
    "properties": {
      "foo": { "type": "number" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 8);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/items",
      "https://www.sourcemeta.com/schema", "/items",
      "https://www.sourcemeta.com/schema", "/items", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://www.sourcemeta.com/schema", "/items/type", "/items", false,
      false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties",
      "https://www.sourcemeta.com/schema", "/properties",
      "https://www.sourcemeta.com/schema", "/properties", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/foo",
      "https://www.sourcemeta.com/schema", "/properties/foo",
      "https://www.sourcemeta.com/schema", "/properties/foo", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/foo/type",
      "https://www.sourcemeta.com/schema", "/properties/foo/type",
      "https://www.sourcemeta.com/schema", "/properties/foo/type",
      "/properties/foo", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/items", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/foo",
      frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema#/items");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://www.sourcemeta.com/schema#/items",
                                  "https://www.sourcemeta.com/schema#/items");

  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema#/properties/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/foo",
      "https://www.sourcemeta.com/schema#/properties/foo");
}

TEST(one_level_applicators_with_identifiers) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/test/qux",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": { "id": "../foo", "type": "string" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 9);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/test/qux",
      "https://www.sourcemeta.com/test/qux", "",
      "https://www.sourcemeta.com/test/qux", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/foo",
      "https://www.sourcemeta.com/test/qux", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/id",
      "https://www.sourcemeta.com/test/qux", "/id",
      "https://www.sourcemeta.com/test/qux", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/$schema",
      "https://www.sourcemeta.com/test/qux", "/$schema",
      "https://www.sourcemeta.com/test/qux", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/test/qux#/items",
      "https://www.sourcemeta.com/test/qux", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/items/id",
      "https://www.sourcemeta.com/test/qux", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/items/type",
      "https://www.sourcemeta.com/test/qux", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/foo#/id",
      "https://www.sourcemeta.com/test/qux", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/foo#/type",
      "https://www.sourcemeta.com/test/qux", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/test/qux", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/foo", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://www.sourcemeta.com/test/qux#/items",
                                  frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static,
                                      "https://www.sourcemeta.com/test/qux",
                                      "https://www.sourcemeta.com/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://www.sourcemeta.com/foo",
                                  "https://www.sourcemeta.com/foo");
}

TEST(subschema_absolute_identifier) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": {
      "id": "https://www.sourcemeta.com/foo",
      "type": "string"
     }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 9);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/foo",
      "https://www.sourcemeta.com/schema", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/items",
      "https://www.sourcemeta.com/schema", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/id",
      "https://www.sourcemeta.com/schema", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/foo#/id",
      "https://www.sourcemeta.com/schema", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/foo#/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/foo", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/items", frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static,
                                      "https://www.sourcemeta.com/schema",
                                      "https://www.sourcemeta.com/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://www.sourcemeta.com/foo",
                                  "https://www.sourcemeta.com/foo");
}

TEST(id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &) {
  }
}

TEST(explicit_argument_id_same) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver,
                "http://json-schema.org/draft-03/schema#",
                "https://www.sourcemeta.com/schema");

  EXPECT_EQ(frame.locations().size(), 3);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
}

TEST(explicit_argument_id_different) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "one": {
        "id": "test"
      },
      "two": {
        "id": "https://www.test.com"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver,
                "http://json-schema.org/draft-03/schema#",
                "https://www.example.com");

  EXPECT_EQ(frame.locations().size(), 22);

  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.sourcemeta.com/test",
      "https://www.sourcemeta.com/schema", "/properties/one",
      "https://www.sourcemeta.com/test", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.example.com", "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.example.com/test",
      "https://www.sourcemeta.com/schema", "/properties/one",
      "https://www.example.com/test", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://www.test.com", "https://www.sourcemeta.com/schema",
      "/properties/two", "https://www.test.com", "", "", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties",
      "https://www.sourcemeta.com/schema", "/properties",
      "https://www.sourcemeta.com/schema", "/properties", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/one",
      "https://www.sourcemeta.com/schema", "/properties/one",
      "https://www.sourcemeta.com/test", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/one/id",
      "https://www.sourcemeta.com/schema", "/properties/one/id",
      "https://www.sourcemeta.com/test", "/id", "/properties/one", false,
      false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/two",
      "https://www.sourcemeta.com/schema", "/properties/two",
      "https://www.test.com", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/two/id",
      "https://www.sourcemeta.com/schema", "/properties/two/id",
      "https://www.test.com", "/id", "/properties/two", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.sourcemeta.com/test#/id",
      "https://www.sourcemeta.com/schema", "/properties/one/id",
      "https://www.sourcemeta.com/test", "/id", "/properties/one", false,
      false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://www.test.com#/id", "https://www.sourcemeta.com/schema",
      "/properties/two/id", "https://www.test.com", "/id", "/properties/two",
      false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/test", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://www.example.com",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://www.example.com/test",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://www.test.com",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/one",
      frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/two",
      frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.example.com#/properties/one", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.example.com#/properties/two", frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static,
                                      "https://www.sourcemeta.com/schema",
                                      "https://www.sourcemeta.com/test");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://www.sourcemeta.com/test",
                                  "https://www.sourcemeta.com/test");

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static,
                                      "https://www.sourcemeta.com/schema",
                                      "https://www.example.com/test");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://www.example.com/test",
                                  "https://www.example.com/test");

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static,
                                      "https://www.sourcemeta.com/schema",
                                      "https://www.test.com");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://www.test.com",
                                  "https://www.test.com");
}

TEST(ref_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$ref", "/$ref", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");
  EXPECT_STATIC_REFERENCE(
      frame, "/$ref", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(ref_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "$ref": "#/definitions/string"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 4);

  // Note that `$ref` MUST override EVERY sibling keyword, so the `id`
  // here is not considered at all
  //
  // However, note that we DO respect `$schema` at the top. This is because
  // we START by checking `$schema` to figure out that `$ref` overrides,
  // so we do know about the dialect anyway
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);

  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$ref", "/$ref", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "#/definitions/string", "",
                          "/definitions/string", "#/definitions/string");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(top_level_relative_ref_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/foo",
    "$ref": "bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 4);

  // Note that `id` is IGNORED given the sibling `$ref`
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$ref", "/$ref", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "bar", "bar", std::nullopt, "bar");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(nested_relative_ref_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com",
    "additionalProperties": {
      "id": "https://nested.com",
      "$ref": "bar"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 6);

  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://example.com", "https://example.com", "",
      "https://example.com", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com#/id", "https://example.com", "/id",
      "https://example.com", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com#/$schema", "https://example.com", "/$schema",
      "https://example.com", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame, "https://example.com#/additionalProperties", "https://example.com",
      "/additionalProperties", "https://example.com", "/additionalProperties",
      "", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com#/additionalProperties/id",
      "https://example.com", "/additionalProperties/id", "https://example.com",
      "/additionalProperties/id", "/additionalProperties", false, false);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com#/additionalProperties/$ref",
      "https://example.com", "/additionalProperties/$ref",
      "https://example.com", "/additionalProperties/$ref",
      "/additionalProperties", false, false);

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/additionalProperties/$ref",
                          "https://example.com/bar", "https://example.com/bar",
                          std::nullopt, "bar");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://example.com#/additionalProperties", frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://example.com",
      "https://example.com#/additionalProperties");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://example.com#/additionalProperties",
                                  "https://example.com#/additionalProperties");
}

TEST(top_level_id_empty_fragment_only) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "#",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.root().empty());

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(top_level_id_empty_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.root().empty());

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(location_independent_identifier_anonymous) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "foo": {
        "id": "#foo"
      },
      "bar": {
        "$ref": "#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 8);

  // Pointers
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);

  // Foo
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/foo", "/definitions/foo",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/foo/id", "/definitions/foo/id",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/definitions/foo", false, true);

  // Bar
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/bar", "/definitions/bar",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/bar/$ref", "/definitions/bar/$ref",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/definitions/bar", false, true);

  // Anchors
  EXPECT_ANONYMOUS_FRAME_STATIC_ANCHOR(
      frame, "#foo", "/definitions/foo",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/definitions/bar/$ref", "#foo", "", "foo",
                          "#foo");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#/definitions/foo",
                                      frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#/definitions/bar",
                                      frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#foo", frame.root());

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#foo", "#/definitions/bar");
}

TEST(id_fragment_invalid_whitespace) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "#foo bar",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "#foo bar");
  } catch (...) {
    FAIL();
  }
}

TEST(non_string_id_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "id": 42, "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "42");
  } catch (...) {
    FAIL();
  }
}

TEST(definitions_subschemas) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/string", "/definitions/string",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/string/type", "/definitions/string/type",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/definitions/string", false, true);

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#/definitions/string",
                                      frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/definitions/string",
                                  "#/definitions/string");
}

TEST(ref_into_definitions) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "foo": { "$ref": "#/definitions/string" }
    },
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 8);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-03/schema#",
      JSON_Schema_Draft_3, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties", "/properties",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/properties/foo", "/properties/foo",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/$ref", "/properties/foo/$ref",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/string", "/definitions/string",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/string/type", "/definitions/string/type",
      "http://json-schema.org/draft-03/schema#", JSON_Schema_Draft_3,
      "/definitions/string", false, true);

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/foo/$ref", "#/definitions/string",
                          "", "/definitions/string", "#/definitions/string");

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/properties/foo",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/definitions/string",
                                  frame.root());
}

TEST(embedded_custom_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 13);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/schema", "https://example.com/schema", "",
      "https://example.com/meta", JSON_Schema_Draft_3,
      "https://example.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT3_RESOURCE(
      frame, "https://example.com/meta", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta", "https://example.com/meta",
      "", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/schema#/$schema",
                              "https://example.com/schema", "/$schema",
                              "https://example.com/meta", JSON_Schema_Draft_3,
                              "https://example.com/schema", "/$schema", "",
                              false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/id", "https://example.com/schema",
      "/id", "https://example.com/meta", JSON_Schema_Draft_3,
      "https://example.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/type", "https://example.com/schema",
      "/type", "https://example.com/meta", JSON_Schema_Draft_3,
      "https://example.com/schema", "/type", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/schema#/definitions",
                              "https://example.com/schema", "/definitions",
                              "https://example.com/meta", JSON_Schema_Draft_3,
                              "https://example.com/schema", "/definitions", "",
                              false, false);
  EXPECT_FRAME_STATIC_DRAFT3_SUBSCHEMA(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta",
      "https://example.com/schema", "/definitions/https:~1~1example.com~1meta",
      "https://example.com/meta", "", "", false, true);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta/id",
      "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/id", "https://example.com/meta",
      "/id", "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta/"
      "$schema",
      "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/$schema",
      "https://example.com/meta", "/$schema",
      "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta/"
      "type",
      "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/type",
      "https://example.com/meta", "/type",
      "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com/meta#/id", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/id", "https://example.com/meta",
      "/id", "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com/meta#/$schema", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/$schema",
      "https://example.com/meta", "/$schema",
      "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT3_POINTER(
      frame, "https://example.com/meta#/type", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/type",
      "https://example.com/meta", "/type",
      "/definitions/https:~1~1example.com~1meta", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(frame, "/$schema", "https://example.com/meta",
                          "https://example.com/meta", std::nullopt,
                          "https://example.com/meta");
  EXPECT_STATIC_REFERENCE(
      frame, "/definitions/https:~1~1example.com~1meta/$schema",
      "http://json-schema.org/draft-03/schema",
      "http://json-schema.org/draft-03/schema", std::nullopt,
      "http://json-schema.org/draft-03/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com/meta",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com/schema",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta",
      frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://example.com/schema", "https://example.com/meta");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com/meta",
                                  "https://example.com/meta");
}

TEST(embedded_custom_metaschema_wrong_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}
