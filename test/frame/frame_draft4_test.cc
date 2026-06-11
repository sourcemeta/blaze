#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "frame_test_utils.h"

#define EXPECT_FRAME_STATIC_DRAFT4_POINTER(                                    \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_POINTER(frame, reference, root_id, expected_pointer,     \
                              "http://json-schema.org/draft-04/schema#",       \
                              JSON_Schema_Draft_4, expected_base,              \
                              expected_relative_pointer, expected_parent,      \
                              expected_property_name, expected_orphan);

#define EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(                                   \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_RESOURCE(frame, reference, root_id, expected_pointer,    \
                               "http://json-schema.org/draft-04/schema#",      \
                               JSON_Schema_Draft_4, expected_base,             \
                               expected_relative_pointer, expected_parent,     \
                               expected_property_name, expected_orphan);

#define EXPECT_FRAME_STATIC_DRAFT4_ANCHOR(                                     \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_ANCHOR(frame, reference, root_id, expected_pointer,      \
                             "http://json-schema.org/draft-04/schema#",        \
                             JSON_Schema_Draft_4, expected_base,               \
                             expected_relative_pointer, expected_parent,       \
                             expected_property_name, expected_orphan);

#define EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(                                  \
    frame, reference, root_id, expected_pointer, expected_base,                \
    expected_relative_pointer, expected_parent, expected_property_name,        \
    expected_orphan)                                                           \
  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, reference, root_id, expected_pointer,   \
                                "http://json-schema.org/draft-04/schema#",     \
                                JSON_Schema_Draft_4, expected_base,            \
                                expected_relative_pointer, expected_parent,    \
                                expected_property_name, expected_orphan);

TEST(Frame_draft4, anonymous_with_nested_schema_resource) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": { "id": "https://example.com" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 6);

  EXPECT_ANONYMOUS_FRAME_STATIC_RESOURCE(
      frame, "https://example.com", "/additionalProperties",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);

  // JSON Pointers

  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "https://example.com#/id", "/additionalProperties/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/additionalProperties", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/additionalProperties", "/additionalProperties",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/additionalProperties/id", "/additionalProperties/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/additionalProperties", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/additionalProperties",
                                  frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "", "https://example.com");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "https://example.com",
                                  "https://example.com");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/additionalProperties",
                                  "https://example.com");
}

TEST(Frame_draft4, empty_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
}

TEST(Frame_draft4, empty_schema_trailing_hash) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema#",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
}

TEST(Frame_draft4, one_level_applicators_without_identifiers) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#",
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
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/items",
      "https://www.sourcemeta.com/schema", "/items",
      "https://www.sourcemeta.com/schema", "/items", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://www.sourcemeta.com/schema", "/items/type", "/items", false,
      false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties",
      "https://www.sourcemeta.com/schema", "/properties",
      "https://www.sourcemeta.com/schema", "/properties", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/foo",
      "https://www.sourcemeta.com/schema", "/properties/foo",
      "https://www.sourcemeta.com/schema", "/properties/foo", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/foo/type",
      "https://www.sourcemeta.com/schema", "/properties/foo/type",
      "https://www.sourcemeta.com/schema", "/properties/foo/type",
      "/properties/foo", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

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

TEST(Frame_draft4, one_level_applicators_with_identifiers) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/test/qux",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "id": "../foo", "type": "string" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 9);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/test/qux",
      "https://www.sourcemeta.com/test/qux", "",
      "https://www.sourcemeta.com/test/qux", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/foo",
      "https://www.sourcemeta.com/test/qux", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/id",
      "https://www.sourcemeta.com/test/qux", "/id",
      "https://www.sourcemeta.com/test/qux", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/$schema",
      "https://www.sourcemeta.com/test/qux", "/$schema",
      "https://www.sourcemeta.com/test/qux", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/test/qux#/items",
      "https://www.sourcemeta.com/test/qux", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/items/id",
      "https://www.sourcemeta.com/test/qux", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/test/qux#/items/type",
      "https://www.sourcemeta.com/test/qux", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/foo#/id",
      "https://www.sourcemeta.com/test/qux", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/foo#/type",
      "https://www.sourcemeta.com/test/qux", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

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

TEST(Frame_draft4, subschema_absolute_identifier) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#",
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
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/foo",
      "https://www.sourcemeta.com/schema", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/items",
      "https://www.sourcemeta.com/schema", "/items",
      "https://www.sourcemeta.com/foo", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/id",
      "https://www.sourcemeta.com/schema", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/foo#/id",
      "https://www.sourcemeta.com/schema", "/items/id",
      "https://www.sourcemeta.com/foo", "/id", "/items", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/foo#/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://www.sourcemeta.com/foo", "/type", "/items", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

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
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static,
                                  "https://www.sourcemeta.com/schema#/items",
                                  "https://www.sourcemeta.com/foo");
}

TEST(Frame_draft4, id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  EXPECT_THROW(frame.analyse(document, sourcemeta::blaze::schema_walker,
                             sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaFrameError);
}

TEST(Frame_draft4, explicit_argument_id_same) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver,
                "http://json-schema.org/draft-04/schema#",
                "https://www.sourcemeta.com/schema");

  EXPECT_EQ(frame.locations().size(), 3);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
}

TEST(Frame_draft4, explicit_argument_id_different) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#",
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
                "http://json-schema.org/draft-04/schema#",
                "https://www.example.com");

  EXPECT_EQ(frame.locations().size(), 22);

  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/test",
      "https://www.sourcemeta.com/schema", "/properties/one",
      "https://www.sourcemeta.com/test", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.example.com", "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.example.com/test",
      "https://www.sourcemeta.com/schema", "/properties/one",
      "https://www.example.com/test", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.test.com", "https://www.sourcemeta.com/schema",
      "/properties/two", "https://www.test.com", "", "", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties",
      "https://www.sourcemeta.com/schema", "/properties",
      "https://www.sourcemeta.com/schema", "/properties", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/one",
      "https://www.sourcemeta.com/schema", "/properties/one",
      "https://www.sourcemeta.com/test", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/one/id",
      "https://www.sourcemeta.com/schema", "/properties/one/id",
      "https://www.sourcemeta.com/test", "/id", "/properties/one", false,
      false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/two",
      "https://www.sourcemeta.com/schema", "/properties/two",
      "https://www.test.com", "", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/two/id",
      "https://www.sourcemeta.com/schema", "/properties/two/id",
      "https://www.test.com", "/id", "/properties/two", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/test#/id",
      "https://www.sourcemeta.com/schema", "/properties/one/id",
      "https://www.sourcemeta.com/test", "/id", "/properties/one", false,
      false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.test.com#/id", "https://www.sourcemeta.com/schema",
      "/properties/two/id", "https://www.test.com", "/id", "/properties/two",
      false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

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

TEST(Frame_draft4, ref_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$ref", "/$ref", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(
      frame, "/$ref", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(Frame_draft4, location_independent_identifier_anonymous) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);

  // Foo
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/foo", "/definitions/foo",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/foo/id", "/definitions/foo/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/definitions/foo", false, true);

  // Bar
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/bar", "/definitions/bar",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/bar/$ref", "/definitions/bar/$ref",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/definitions/bar", false, true);

  // Anchors
  EXPECT_ANONYMOUS_FRAME_STATIC_ANCHOR(
      frame, "#foo", "/definitions/foo",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/definitions/bar/$ref", "#foo", "", "foo",
                          "#foo");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#/definitions/foo",
                                      frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#/definitions/bar",
                                      frame.root());
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#foo", frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "", "#/definitions/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/definitions/foo",
                                  "#/definitions/foo");
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "#/definitions/bar",
                                      "#/definitions/foo");

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "", "#/definitions/bar");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/definitions/bar",
                                  "#/definitions/bar");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/definitions/foo",
                                  "#/definitions/bar");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#foo", "#/definitions/bar");
}

TEST(Frame_draft4, ref_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": "#/definitions/string",
    "definitions": {
      "string": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 7);

  // Note that `$ref` MUST override EVERY sibling keyword, so the `id`
  // here is not considered at all
  //
  // However, note that we DO respect `$schema` at the top. This is because
  // we START by checking `$schema` to figure out that `$ref` overrides,
  // so we do know about the dialect anyway
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);

  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$ref", "/$ref", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/string", "/definitions/string",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/string/type", "/definitions/string/type",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "#/definitions/string", "",
                          "/definitions/string", "#/definitions/string");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(Frame_draft4, id_with_trailing_hash_and_ref_and_same_default_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema#",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
        "foo": { "$ref": "#/properties/bar" },
        "bar": {}
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, "",
                // Note that this is intentionally non-canonical
                "https://www.sourcemeta.com/schema#");

  EXPECT_EQ(frame.locations().size(), 7);

  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/id",
      "https://www.sourcemeta.com/schema", "/id",
      "https://www.sourcemeta.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties",
      "https://www.sourcemeta.com/schema", "/properties",
      "https://www.sourcemeta.com/schema", "/properties", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/foo",
      "https://www.sourcemeta.com/schema", "/properties/foo",
      "https://www.sourcemeta.com/schema", "/properties/foo", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://www.sourcemeta.com/schema#/properties/foo/$ref",
      "https://www.sourcemeta.com/schema", "/properties/foo/$ref",
      "https://www.sourcemeta.com/schema", "/properties/foo/$ref",
      "/properties/foo", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/properties/bar",
      "https://www.sourcemeta.com/schema", "/properties/bar",
      "https://www.sourcemeta.com/schema", "/properties/bar", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/foo/$ref",
                          "https://www.sourcemeta.com/schema#/properties/bar",
                          "https://www.sourcemeta.com/schema",
                          "/properties/bar", "#/properties/bar");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/foo",
      frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/bar",
      frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema#/properties/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/foo",
      "https://www.sourcemeta.com/schema#/properties/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/bar",
      "https://www.sourcemeta.com/schema#/properties/foo");

  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema#/properties/bar");
  EXPECT_FRAME_LOCATION_NON_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/foo",
      "https://www.sourcemeta.com/schema#/properties/bar");
  EXPECT_FRAME_LOCATION_REACHABLE(
      frame, Static, "https://www.sourcemeta.com/schema#/properties/bar",
      "https://www.sourcemeta.com/schema#/properties/bar");
}

TEST(Frame_draft4, relative_base_uri_without_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "common"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(frame, "common", "common", "", "common",
                                      "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/$schema", "common",
                                     "/$schema", "common", "/$schema", "",
                                     false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/id", "common", "/id",
                                     "common", "/id", "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common", frame.root());
}

TEST(Frame_draft4, relative_base_uri_with_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "common",
    "allOf": [ { "$ref": "#foo" } ],
    "definitions": {
      "foo": {
        "id": "#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 10);

  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(frame, "common", "common", "", "common",
                                      "", std::nullopt, false, false);

  // Anchors
  EXPECT_FRAME_STATIC_DRAFT4_ANCHOR(frame, "common#foo", "common",
                                    "/definitions/foo", "common",
                                    "/definitions/foo", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/$schema", "common",
                                     "/$schema", "common", "/$schema", "",
                                     false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/id", "common", "/id",
                                     "common", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/allOf", "common", "/allOf",
                                     "common", "/allOf", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(frame, "common#/allOf/0", "common",
                                       "/allOf/0", "common", "/allOf/0", "",
                                       false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/allOf/0/$ref", "common",
                                     "/allOf/0/$ref", "common", "/allOf/0/$ref",
                                     "/allOf/0", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(frame, "common#/definitions", "common",
                                     "/definitions", "common", "/definitions",
                                     "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(frame, "common#/definitions/foo",
                                       "common", "/definitions/foo", "common",
                                       "/definitions/foo", "", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "common#/definitions/foo/id", "common", "/definitions/foo/id",
      "common", "/definitions/foo/id", "/definitions/foo", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/allOf/0/$ref", "common#foo", "common", "foo",
                          "#foo");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#foo", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#/allOf/0",
                                  frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#/definitions/foo",
                                  frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "common",
                                      "common#/allOf/0");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#/allOf/0",
                                  "common#/allOf/0");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#foo",
                                  "common#/allOf/0");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#/definitions/foo",
                                  "common#/allOf/0");

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "common",
                                      "common#/definitions/foo");
  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "common#/allOf/0",
                                      "common#/definitions/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#/definitions/foo",
                                  "common#/definitions/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "common#foo",
                                  "common#/definitions/foo");
}

TEST(Frame_draft4, ref_with_invalid_type) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$ref");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(Frame_draft4, ref_invalidates_sibling_subschemas_and_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "$ref": "#/definitions/enabled",
        "properties": {
          "bar": {
            "$ref": "#/definitions/config",
            "additionalProperties": {
              "$ref": "#/definitions/threshold"
            }
          }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 10);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties", "/properties",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/properties/foo", "/properties/foo",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/$ref", "/properties/foo/$ref",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/properties", "/properties/foo/properties",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/properties/bar",
      "/properties/foo/properties/bar",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/properties/bar/$ref",
      "/properties/foo/properties/bar/$ref",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/properties/bar/additionalProperties",
      "/properties/foo/properties/bar/additionalProperties",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/properties/bar/additionalProperties/$ref",
      "/properties/foo/properties/bar/additionalProperties/$ref",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "/properties/foo", false, false);

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/foo/$ref",
                          "#/definitions/enabled", "", "/definitions/enabled",
                          "#/definitions/enabled");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/properties/foo",
                                  frame.root());

  EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, Static, "", "#/properties/foo");
  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "#/properties/foo",
                                  "#/properties/foo");
}

TEST(Frame_draft4, top_level_relative_ref_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$ref", "/$ref", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "bar", "bar", std::nullopt, "bar");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(Frame_draft4, nested_relative_ref_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://example.com", "https://example.com", "",
      "https://example.com", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://example.com#/id", "https://example.com", "/id",
      "https://example.com", "/id", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://example.com#/$schema", "https://example.com", "/$schema",
      "https://example.com", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame, "https://example.com#/additionalProperties", "https://example.com",
      "/additionalProperties", "https://example.com", "/additionalProperties",
      "", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://example.com#/additionalProperties/id",
      "https://example.com", "/additionalProperties/id", "https://example.com",
      "/additionalProperties/id", "/additionalProperties", false, false);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://example.com#/additionalProperties/$ref",
      "https://example.com", "/additionalProperties/$ref",
      "https://example.com", "/additionalProperties/$ref",
      "/additionalProperties", false, false);

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
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

TEST(Frame_draft4, invalid_id_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema",
    "id": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(Frame_draft4, top_level_id_empty_fragment_only) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "#",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.root().empty());

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(Frame_draft4, top_level_id_empty_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.root().empty());

  EXPECT_EQ(frame.locations().size(), 3);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/id", "/id", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-04/schema#",
      JSON_Schema_Draft_4, "", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

  // Reachability

  EXPECT_FRAME_LOCATION_REACHABLE(frame, Static, "", frame.root());
}

TEST(Frame_draft4, id_fragment_invalid_whitespace) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "id": "#foo bar"
      }
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
    EXPECT_EQ(error.value(), "#foo bar");
  } catch (...) {
    FAIL();
  }
}

TEST(Frame_draft4, id_fragment_invalid_angle_bracket) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "id": "#foo<bar"
      }
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
    EXPECT_EQ(error.value(), "#foo<bar");
  } catch (...) {
    FAIL();
  }
}

TEST(Frame_draft4, embedded_custom_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
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
      "https://example.com/meta", JSON_Schema_Draft_4,
      "https://example.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_DRAFT4_RESOURCE(
      frame, "https://example.com/meta", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta", "https://example.com/meta",
      "", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/schema#/$schema",
                              "https://example.com/schema", "/$schema",
                              "https://example.com/meta", JSON_Schema_Draft_4,
                              "https://example.com/schema", "/$schema", "",
                              false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/id", "https://example.com/schema",
      "/id", "https://example.com/meta", JSON_Schema_Draft_4,
      "https://example.com/schema", "/id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/type", "https://example.com/schema",
      "/type", "https://example.com/meta", JSON_Schema_Draft_4,
      "https://example.com/schema", "/type", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/schema#/definitions",
                              "https://example.com/schema", "/definitions",
                              "https://example.com/meta", JSON_Schema_Draft_4,
                              "https://example.com/schema", "/definitions", "",
                              false, false);
  EXPECT_FRAME_STATIC_DRAFT4_SUBSCHEMA(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta",
      "https://example.com/schema", "/definitions/https:~1~1example.com~1meta",
      "https://example.com/meta", "", "", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta/id",
      "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/id", "https://example.com/meta",
      "/id", "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta/"
      "$schema",
      "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/$schema",
      "https://example.com/meta", "/$schema",
      "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame,
      "https://example.com/schema#/definitions/https:~1~1example.com~1meta/"
      "type",
      "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/type",
      "https://example.com/meta", "/type",
      "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://example.com/meta#/id", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/id", "https://example.com/meta",
      "/id", "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
      frame, "https://example.com/meta#/$schema", "https://example.com/schema",
      "/definitions/https:~1~1example.com~1meta/$schema",
      "https://example.com/meta", "/$schema",
      "/definitions/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_DRAFT4_POINTER(
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
      "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");

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

TEST(Frame_draft4, embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
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
