#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/blaze/frame.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <set>
#include <sstream>

#include "frame_test_utils.h"

TEST(Frame, nested_schemas_mixing_dialects) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "id": "foo",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "definitions": {
          "bar": {
            "id": "bar",
            "type": "string"
          }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 21);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.sourcemeta.com/test",
      "https://www.sourcemeta.com/test", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/test", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.sourcemeta.com/foo",
      "https://www.sourcemeta.com/test", "/$defs/foo",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "", "", false, true);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.sourcemeta.com/bar",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "", "/$defs/foo", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$id",
      "https://www.sourcemeta.com/test", "/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/test", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$schema",
      "https://www.sourcemeta.com/test", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/test", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$defs",
      "https://www.sourcemeta.com/test", "/$defs",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/test", "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/test#/$defs/foo",
      "https://www.sourcemeta.com/test", "/$defs/foo",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$defs/foo/id",
      "https://www.sourcemeta.com/test", "/$defs/foo/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "/id", "/$defs/foo", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$defs/foo/$schema",
      "https://www.sourcemeta.com/test", "/$defs/foo/$schema",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "/$schema", "/$defs/foo", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$defs/foo/definitions",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "/definitions", "/$defs/foo", false,
      true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/test#/$defs/foo/definitions/bar",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "", "/$defs/foo", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$defs/foo/definitions/bar/id",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "/id", "/$defs/foo/definitions/bar",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/test#/$defs/foo/definitions/bar/type",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar/type",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "/type", "/$defs/foo/definitions/bar",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/foo#/id",
      "https://www.sourcemeta.com/test", "/$defs/foo/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "/id", "/$defs/foo", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/foo#/$schema",
      "https://www.sourcemeta.com/test", "/$defs/foo/$schema",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "/$schema", "/$defs/foo", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/foo#/definitions",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/foo", "/definitions", "/$defs/foo", false,
      true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/foo#/definitions/bar",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "", "/$defs/foo", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/foo#/definitions/bar/id",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "/id", "/$defs/foo/definitions/bar",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/foo#/definitions/bar/type",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar/type",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "/type", "/$defs/foo/definitions/bar",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/bar#/id",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar/id",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "/id", "/$defs/foo/definitions/bar",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/bar#/type",
      "https://www.sourcemeta.com/test", "/$defs/foo/definitions/bar/type",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://www.sourcemeta.com/bar", "/type", "/$defs/foo/definitions/bar",
      false, true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(
      frame, "/$defs/foo/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
}

TEST(Frame, nested_schemas_sibling_ref_nested_2020_12_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "embedded",
    "$defs": {
      "embedded": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "embedded",
        "$ref": "#/definitions/foo",
        "definitions": {
          "foo": { "type": "number" }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 19);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/main", "https://example.com/main", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$schema",
                              "https://example.com/main", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$id",
                              "https://example.com/main", "/$id",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$ref",
                              "https://example.com/main", "/$ref",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$ref", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$defs",
                              "https://example.com/main", "/$defs",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$defs", "", false, false);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/embedded", "https://example.com/main",
      "/$defs/embedded", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, "https://example.com/embedded", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/$schema",
      "https://example.com/main", "/$defs/embedded/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/$schema", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/$id", "https://example.com/main",
      "/$defs/embedded/$id", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, "https://example.com/embedded", "/$id",
      "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/$ref", "https://example.com/main",
      "/$defs/embedded/$ref", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, "https://example.com/embedded", "/$ref",
      "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/definitions",
      "https://example.com/main", "/$defs/embedded/definitions",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/definitions", "/$defs/embedded", false,
      true);

  // Note that this is still considered to be a subschema, but a 2020-12 one.
  // The logic is that we try to interpret it as Draft 7, given `$schema`, but
  // the `$ref` there overrides the `$id`, therefore it is not a schema
  // resource, and thus `$schema` gets ignored.

  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/embedded#/definitions/foo",
      "https://example.com/main", "/$defs/embedded/definitions/foo",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/definitions/foo", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/definitions/foo/type",
      "https://example.com/main", "/$defs/embedded/definitions/foo/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/definitions/foo/type",
      "/$defs/embedded/definitions/foo", false, true);

  // From the root
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded",
      "https://example.com/main", "/$defs/embedded",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$schema",
      "https://example.com/main", "/$defs/embedded/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/$schema", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$id",
      "https://example.com/main", "/$defs/embedded/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/$id", "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$ref",
      "https://example.com/main", "/$defs/embedded/$ref",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/$ref", "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/definitions",
      "https://example.com/main", "/$defs/embedded/definitions",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/definitions", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded/definitions/foo",
      "https://example.com/main", "/$defs/embedded/definitions/foo",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/definitions/foo", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/definitions/foo/type",
      "https://example.com/main", "/$defs/embedded/definitions/foo/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/embedded", "/definitions/foo/type",
      "/$defs/embedded/definitions/foo", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 4);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "https://example.com/embedded",
                          "https://example.com/embedded", std::nullopt,
                          "embedded");
  EXPECT_STATIC_REFERENCE(frame, "/$defs/embedded/$schema",
                          "http://json-schema.org/draft-07/schema",
                          "http://json-schema.org/draft-07/schema",
                          std::nullopt,
                          "http://json-schema.org/draft-07/schema#");

  // Note that the reference keep its base URI because we end up interpreting
  // the embedded schema as 2020-12
  EXPECT_STATIC_REFERENCE(frame, "/$defs/embedded/$ref",
                          "https://example.com/embedded#/definitions/foo",
                          "https://example.com/embedded", "/definitions/foo",
                          "#/definitions/foo");
}

TEST(Frame, nested_schemas_sibling_ref_nested_2020_12_draft7_with_allof) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "embedded",
    "$defs": {
      "embedded": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "embedded",
        "allOf": [ { "$ref": "#/definitions/foo" } ],
        "definitions": {
          "foo": { "type": "number" }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 23);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/main", "https://example.com/main", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$schema",
                              "https://example.com/main", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$id",
                              "https://example.com/main", "/$id",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$ref",
                              "https://example.com/main", "/$ref",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$ref", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$defs",
                              "https://example.com/main", "/$defs",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$defs", "", false, false);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/embedded", "https://example.com/main",
      "/$defs/embedded", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "https://example.com/embedded", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/$schema",
      "https://example.com/main", "/$defs/embedded/$schema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/$schema", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/$id", "https://example.com/main",
      "/$defs/embedded/$id", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "https://example.com/embedded", "/$id",
      "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/allOf", "https://example.com/main",
      "/$defs/embedded/allOf", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "https://example.com/embedded", "/allOf",
      "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/embedded#/allOf/0",
      "https://example.com/main", "/$defs/embedded/allOf/0",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/allOf/0", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/allOf/0/$ref",
      "https://example.com/main", "/$defs/embedded/allOf/0/$ref",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/allOf/0/$ref",
      "/$defs/embedded/allOf/0", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/definitions",
      "https://example.com/main", "/$defs/embedded/definitions",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/definitions", "/$defs/embedded", false,
      true);

  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/embedded#/definitions/foo",
      "https://example.com/main", "/$defs/embedded/definitions/foo",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/definitions/foo", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/embedded#/definitions/foo/type",
      "https://example.com/main", "/$defs/embedded/definitions/foo/type",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/definitions/foo/type",
      "/$defs/embedded/definitions/foo", false, true);

  // From the root
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded",
      "https://example.com/main", "/$defs/embedded",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$schema",
      "https://example.com/main", "/$defs/embedded/$schema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/$schema", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$id",
      "https://example.com/main", "/$defs/embedded/$id",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/$id", "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/allOf",
      "https://example.com/main", "/$defs/embedded/allOf",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/allOf", "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded/allOf/0",
      "https://example.com/main", "/$defs/embedded/allOf/0",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/allOf/0", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/allOf/0/$ref",
      "https://example.com/main", "/$defs/embedded/allOf/0/$ref",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/allOf/0/$ref",
      "/$defs/embedded/allOf/0", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/definitions",
      "https://example.com/main", "/$defs/embedded/definitions",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/definitions", "/$defs/embedded", false,
      true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded/definitions/foo",
      "https://example.com/main", "/$defs/embedded/definitions/foo",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/definitions/foo", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/definitions/foo/type",
      "https://example.com/main", "/$defs/embedded/definitions/foo/type",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/embedded", "/definitions/foo/type",
      "/$defs/embedded/definitions/foo", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 4);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "https://example.com/embedded",
                          "https://example.com/embedded", std::nullopt,
                          "embedded");
  EXPECT_STATIC_REFERENCE(frame, "/$defs/embedded/$schema",
                          "http://json-schema.org/draft-07/schema",
                          "http://json-schema.org/draft-07/schema",
                          std::nullopt,
                          "http://json-schema.org/draft-07/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/$defs/embedded/allOf/0/$ref",
                          "https://example.com/embedded#/definitions/foo",
                          "https://example.com/embedded", "/definitions/foo",
                          "#/definitions/foo");
}

TEST(Frame, nested_schemas_sibling_ref_nested_2020_12_draft4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "embedded",
    "$defs": {
      "embedded": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "embedded",
        "$ref": "#/definitions/foo",
        "definitions": {
          "foo": { "type": "number" }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 12);

  // Resources
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/main", "https://example.com/main", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$schema",
                              "https://example.com/main", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$id",
                              "https://example.com/main", "/$id",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$ref",
                              "https://example.com/main", "/$ref",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$ref", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/main#/$defs",
                              "https://example.com/main", "/$defs",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/main",
                              "/$defs", "", false, false);

  // Note that in this case, we DO NOT consider this to be a resource, as we end
  // up interpreting it as 2020-12, where `id` is not a valid keyword
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded",
      "https://example.com/main", "/$defs/embedded",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded", "", false, true);

  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$schema",
      "https://example.com/main", "/$defs/embedded/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded/$schema", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/id",
      "https://example.com/main", "/$defs/embedded/id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded/id", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/$ref",
      "https://example.com/main", "/$defs/embedded/$ref",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded/$ref", "/$defs/embedded",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/definitions",
      "https://example.com/main", "/$defs/embedded/definitions",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded/definitions",
      "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/main#/$defs/embedded/definitions/foo",
      "https://example.com/main", "/$defs/embedded/definitions/foo",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded/definitions/foo",
      "/$defs/embedded", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/main#/$defs/embedded/definitions/foo/type",
      "https://example.com/main", "/$defs/embedded/definitions/foo/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/main", "/$defs/embedded/definitions/foo/type",
      "/$defs/embedded/definitions/foo", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 4);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(frame, "/$ref", "https://example.com/embedded",
                          "https://example.com/embedded", std::nullopt,
                          "embedded");
  EXPECT_STATIC_REFERENCE(frame, "/$defs/embedded/$schema",
                          "http://json-schema.org/draft-04/schema",
                          "http://json-schema.org/draft-04/schema",
                          std::nullopt,
                          "http://json-schema.org/draft-04/schema#");

  // Note that this reference is interpreted from the root, as we end up trying
  // to match `id` against 2020-12, which does not exist
  EXPECT_STATIC_REFERENCE(frame, "/$defs/embedded/$ref",
                          "https://example.com/main#/definitions/foo",
                          "https://example.com/main", "/definitions/foo",
                          "#/definitions/foo");
}

TEST(Frame, no_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$anchor": "foo",
        "type": "string"
      },
      "bar": {
        "$id": "https://example.com",
        "$anchor": "bar"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 14);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties", "/properties",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);

  // Foo

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/properties/foo", "/properties/foo",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/$anchor", "/properties/foo/$anchor",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/type", "/properties/foo/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_ANCHOR(
      frame, "#foo", "/properties/foo",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);

  // Bar

  EXPECT_ANONYMOUS_FRAME_STATIC_RESOURCE(
      frame, "https://example.com", "/properties/bar",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_ANCHOR(
      frame, "https://example.com#bar", "/properties/bar",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "https://example.com#/$id", "/properties/bar/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/properties/bar", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "https://example.com#/$anchor", "/properties/bar/$anchor",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/properties/bar", false, false);

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/properties/bar", "/properties/bar",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/bar/$id", "/properties/bar/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/properties/bar", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/bar/$anchor", "/properties/bar/$anchor",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/properties/bar", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, no_id_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "type": "string" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver,
                "https://json-schema.org/draft/2020-12/schema",
                "https://www.sourcemeta.com/schema");

  EXPECT_EQ(frame.locations().size(), 4);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/schema#/$schema",
      "https://www.sourcemeta.com/schema", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/schema", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://www.sourcemeta.com/schema#/items",
      "https://www.sourcemeta.com/schema", "/items",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/schema", "/items", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.sourcemeta.com/schema#/items/type",
      "https://www.sourcemeta.com/schema", "/items/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.sourcemeta.com/schema", "/items/type", "/items", false,
      false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, id_with_default_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver, "", "https://other.com");

  EXPECT_EQ(frame.locations().size(), 10);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com", "https://example.com", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com#/$id", "https://example.com", "/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com#/$schema", "https://example.com", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com#/additionalProperties", "https://example.com",
      "/additionalProperties", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, "https://example.com", "/additionalProperties", "",
      false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com#/additionalProperties/type",
      "https://example.com", "/additionalProperties/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "/additionalProperties/type",
      "/additionalProperties", false, false);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://other.com", "https://example.com", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://other.com#/$id", "https://example.com", "/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://other.com#/$schema", "https://example.com", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://other.com#/additionalProperties", "https://example.com",
      "/additionalProperties", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, "https://example.com", "/additionalProperties", "",
      false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://other.com#/additionalProperties/type",
      "https://example.com", "/additionalProperties/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com", "/additionalProperties/type",
      "/additionalProperties", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, cross_2020_12_to_2019_09_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2019-09/schema"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs", "/$defs",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);

  // Subschema

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/$defs/schema", "/$defs/schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs/schema/$schema", "/$defs/schema/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/$defs/schema", false, true);
}

TEST(Frame, cross_2020_12_to_draft7_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$schema": "http://json-schema.org/draft-07/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs", "/$defs",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);

  // Note that `$schema` without an identifier is NOT allowed
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/$defs/schema", "/$defs/schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs/schema/$schema", "/$defs/schema/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/$defs/schema", false, true);
}

TEST(Frame, cross_2020_12_to_draft6_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$schema": "http://json-schema.org/draft-06/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs", "/$defs",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);

  // Note that `$schema` without an identifier is NOT allowed
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/$defs/schema", "/$defs/schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs/schema/$schema", "/$defs/schema/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/$defs/schema", false, true);
}

TEST(Frame, cross_2020_12_to_draft4_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$schema": "http://json-schema.org/draft-04/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs", "/$defs",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, false);

  // Note that `$schema` without an identifier is NOT allowed
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/$defs/schema", "/$defs/schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12, "",
      false, true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$defs/schema/$schema", "/$defs/schema/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "/$defs/schema", false, true);
}

TEST(Frame, cross_draft7_to_draft4_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "schema": {
        "$schema": "http://json-schema.org/draft-04/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      false);

  // Note that `$schema` without an identifier is NOT allowed
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/schema", "/definitions/schema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/schema/$schema", "/definitions/schema/$schema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "/definitions/schema", false, true);
}

TEST(Frame, cross_draft7_to_2020_12_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "schema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 5);

  // Top level

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      false);

  // Subschema

  // Note that `$schema` without an identifier is NOT allowed
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/schema", "/definitions/schema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/schema/$schema", "/definitions/schema/$schema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "/definitions/schema", false, true);
}

TEST(Frame, anchor_on_absolute_subid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "$id": "https://www.example.org",
      "items": {
        "$anchor": "foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 12);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.example.com", "https://www.example.com", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.com", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.example.org", "https://www.example.com", "/items",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.org", "", "", false, false);
  EXPECT_FRAME_STATIC_ANCHOR(frame, "https://www.example.org#foo",
                             "https://www.example.com", "/items/items",
                             "https://json-schema.org/draft/2020-12/schema",
                             JSON_Schema_2020_12, "https://www.example.org",
                             "/items", "/items", false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.example.com#/$id", "https://www.example.com", "/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.com", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/$schema",
                              "https://www.example.com", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://www.example.com#/items", "https://www.example.com",
      "/items", "https://json-schema.org/draft/2020-12/schema",
      JSON_Schema_2020_12, "https://www.example.org", "", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/items/$id",
                              "https://www.example.com", "/items/$id",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.org",
                              "/$id", "/items", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, "https://www.example.com#/items/items",
                                "https://www.example.com", "/items/items",
                                "https://json-schema.org/draft/2020-12/schema",
                                JSON_Schema_2020_12, "https://www.example.org",
                                "/items", "/items", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame,
                              "https://www.example.com#/items/items/$anchor",
                              "https://www.example.com", "/items/items/$anchor",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.org",
                              "/items/$anchor", "/items/items", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.org#/$id",
                              "https://www.example.com", "/items/$id",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.org",
                              "/$id", "/items", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, "https://www.example.org#/items",
                                "https://www.example.com", "/items/items",
                                "https://json-schema.org/draft/2020-12/schema",
                                JSON_Schema_2020_12, "https://www.example.org",
                                "/items", "/items", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.org#/items/$anchor",
                              "https://www.example.com", "/items/items/$anchor",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.org",
                              "/items/$anchor", "/items/items", false, false);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, uri_iterators) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "$id": "test",
      "$anchor": "foo",
      "type": "string"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  std::set<std::string> uris;
  for (const auto &entry : frame.locations()) {
    uris.insert(entry.first.second);
  }

  EXPECT_EQ(frame.locations().size(), 12);
  EXPECT_EQ(uris.size(), 12);

  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/schema"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/test"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/test#foo"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/schema#/$id"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/schema#/$schema"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/schema#/items"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/schema#/items/$id"));
  EXPECT_TRUE(
      uris.contains("https://www.sourcemeta.com/schema#/items/$anchor"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/schema#/items/type"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/test#/$id"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/test#/$anchor"));
  EXPECT_TRUE(uris.contains("https://www.sourcemeta.com/test#/type"));

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, no_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "number" },
      "baz": { "type": "array" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, refs_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#" },
      "bar": { "$ref": "#/properties/baz" },
      "baz": {
        "$anchor": "baz",
        "type": "string"
      },
      "qux": {
        "$id": "test",
        "$ref": "#"
      },
      "anchor": {
        "$ref": "#baz"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.references().size(), 5);
  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(
      frame, "/properties/foo/$ref", "https://www.sourcemeta.com/schema",
      "https://www.sourcemeta.com/schema", std::nullopt, "#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/bar/$ref",
                          "https://www.sourcemeta.com/schema#/properties/baz",
                          "https://www.sourcemeta.com/schema",
                          "/properties/baz", "#/properties/baz");
  EXPECT_STATIC_REFERENCE(frame, "/properties/qux/$ref",
                          "https://www.sourcemeta.com/test",
                          "https://www.sourcemeta.com/test", std::nullopt, "#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/anchor/$ref",
                          "https://www.sourcemeta.com/schema#baz",
                          "https://www.sourcemeta.com/schema", "baz", "#baz");
}

TEST(Frame, refs_with_no_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#" },
      "bar": { "$ref": "#/properties/baz" },
      "baz": {
        "$anchor": "baz",
        "type": "string"
      },
      "qux": {
        "$id": "https://www.example.com",
        "$ref": "#"
      },
      "anchor": {
        "$ref": "#baz"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.references().size(), 5);
  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(frame, "/properties/foo/$ref", "", "", std::nullopt,
                          "#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/bar/$ref", "#/properties/baz", "",
                          "/properties/baz", "#/properties/baz");
  EXPECT_STATIC_REFERENCE(frame, "/properties/qux/$ref",
                          "https://www.example.com", "https://www.example.com",
                          std::nullopt, "#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/anchor/$ref", "#baz", "", "baz",
                          "#baz");
}

TEST(Frame, no_dynamic_ref_on_old_drafts) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$dynamicRef": "#" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2019-09/schema",
      "https://json-schema.org/draft/2019-09/schema", std::nullopt,
      "https://json-schema.org/draft/2019-09/schema");
}

TEST(Frame, remote_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.example.com" },
      "bar": { "$ref": "https://www.example.com/test#foo" },
      "baz": { "$ref": "https://www.example.com/x/y#/foo/bar" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.references().size(), 4);
  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(frame, "/properties/foo/$ref",
                          "https://www.example.com", "https://www.example.com",
                          std::nullopt, "https://www.example.com");
  EXPECT_STATIC_REFERENCE(frame, "/properties/bar/$ref",
                          "https://www.example.com/test#foo",
                          "https://www.example.com/test", "foo",
                          "https://www.example.com/test#foo");
  EXPECT_STATIC_REFERENCE(frame, "/properties/baz/$ref",
                          "https://www.example.com/x/y#/foo/bar",
                          "https://www.example.com/x/y", "/foo/bar",
                          "https://www.example.com/x/y#/foo/bar");
}

TEST(Frame, standalone_with_external_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.example.com" },
      "bar": { "$ref": "#/properties/foo" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_FALSE(frame.standalone());
}

TEST(Frame, standalone_with_embedded_external_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.example.com" },
      "bar": { "$ref": "#/properties/foo" }
    },
    "$defs": {
      "https://www.example.com": {
        "$id": "https://www.example.com"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.standalone());
}

TEST(Frame, standalone_with_internal_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "$ref": "#/properties/foo" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.standalone());
}

TEST(Frame, standalone_without_refs) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_TRUE(frame.standalone());
}

TEST(Frame, standalone_with_draft3_external_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-1" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_FALSE(frame.standalone());
}

TEST(Frame, no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "string"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  EXPECT_THROW(frame.analyse(document, sourcemeta::blaze::schema_walker,
                             sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Frame, mode_references) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "$anchor": "helper",
      "$ref": "#/$defs/helper"
    },
    "$defs": {
      "helper": true
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.mode(), sourcemeta::blaze::SchemaFrame::Mode::References);

  EXPECT_EQ(frame.locations().size(), 9);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.example.com", "https://www.example.com", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.com", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.example.com#/$id", "https://www.example.com", "/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.com", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/$schema",
                              "https://www.example.com", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/$schema", "", false, false);

  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, "https://www.example.com#/items",
                                "https://www.example.com", "/items",
                                "https://json-schema.org/draft/2020-12/schema",
                                JSON_Schema_2020_12, "https://www.example.com",
                                "/items", "", false, false);
  EXPECT_FRAME_STATIC_ANCHOR(frame, "https://www.example.com#helper",
                             "https://www.example.com", "/items",
                             "https://json-schema.org/draft/2020-12/schema",
                             JSON_Schema_2020_12, "https://www.example.com",
                             "/items", "", false, false);

  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/items/$anchor",
                              "https://www.example.com", "/items/$anchor",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/items/$anchor", "/items", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/items/$ref",
                              "https://www.example.com", "/items/$ref",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/items/$ref", "/items", false, false);

  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/$defs",
                              "https://www.example.com", "/$defs",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, "https://www.example.com#/$defs/helper",
                                "https://www.example.com", "/$defs/helper",
                                "https://json-schema.org/draft/2020-12/schema",
                                JSON_Schema_2020_12, "https://www.example.com",
                                "/$defs/helper", "", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
  EXPECT_STATIC_REFERENCE(
      frame, "/items/$ref", "https://www.example.com#/$defs/helper",
      "https://www.example.com", "/$defs/helper", "#/$defs/helper");
}

TEST(Frame, mode_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "$anchor": "helper",
      "$ref": "#/$defs/helper"
    },
    "$defs": {
      "helper": true
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.mode(), sourcemeta::blaze::SchemaFrame::Mode::Locations);
  EXPECT_EQ(frame.locations().size(), 9);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://www.example.com", "https://www.example.com", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.com", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://www.example.com#/$id", "https://www.example.com", "/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://www.example.com", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/$schema",
                              "https://www.example.com", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/$schema", "", false, false);

  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, "https://www.example.com#/items",
                                "https://www.example.com", "/items",
                                "https://json-schema.org/draft/2020-12/schema",
                                JSON_Schema_2020_12, "https://www.example.com",
                                "/items", "", false, false);
  EXPECT_FRAME_STATIC_ANCHOR(frame, "https://www.example.com#helper",
                             "https://www.example.com", "/items",
                             "https://json-schema.org/draft/2020-12/schema",
                             JSON_Schema_2020_12, "https://www.example.com",
                             "/items", "", false, false);

  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/items/$anchor",
                              "https://www.example.com", "/items/$anchor",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/items/$anchor", "/items", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/items/$ref",
                              "https://www.example.com", "/items/$ref",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/items/$ref", "/items", false, false);

  EXPECT_FRAME_STATIC_POINTER(frame, "https://www.example.com#/$defs",
                              "https://www.example.com", "/$defs",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://www.example.com",
                              "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(frame, "https://www.example.com#/$defs/helper",
                                "https://www.example.com", "/$defs/helper",
                                "https://json-schema.org/draft/2020-12/schema",
                                JSON_Schema_2020_12, "https://www.example.com",
                                "/$defs/helper", "", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 0);
}

TEST(Frame, has_references_to_2020_12) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$id": "foo",
        "$dynamicAnchor": "test"
      },
      "bar": {
        "$id": "bar",
        "$dynamicAnchor": "test"
      },
      "baz": {
        "$id": "baz",
        "$anchor": "test"
      }
    },
    "$defs": {
      "bookending": {
        "$dynamicAnchor": "test"
      },
      "static": {
        "$ref": "#test"
      },
      "dynamic": {
        "$dynamicRef": "#test"
      },
      "dynamic-non-anchor": {
        "$dynamicRef": "baz"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::Pointer properties_foo{"properties", "foo"};
  const sourcemeta::core::Pointer properties_bar{"properties", "bar"};
  const sourcemeta::core::Pointer properties_baz{"properties", "baz"};
  const sourcemeta::core::Pointer defs_bookending{"$defs", "bookending"};
  const sourcemeta::core::Pointer defs_static{"$defs", "static"};
  const sourcemeta::core::Pointer defs_dynamic{"$defs", "dynamic"};
  const sourcemeta::core::Pointer defs_dynamic_non_anchor{"$defs",
                                                          "dynamic-non-anchor"};

  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_foo)));
  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_bar)));
  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_baz)));
  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(defs_bookending)));
  EXPECT_FALSE(
      frame.has_references_to(sourcemeta::core::to_weak_pointer(defs_static)));
  EXPECT_FALSE(
      frame.has_references_to(sourcemeta::core::to_weak_pointer(defs_dynamic)));
  EXPECT_FALSE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(defs_dynamic_non_anchor)));
}

TEST(Frame, has_references_to_2019_09) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "$id": "foo",
        "$recursiveAnchor": true
      },
      "bar": {
        "$id": "bar",
        "$recursiveAnchor": true
      },
      "baz": {
        "$id": "baz",
        "$anchor": "test"
      },
      "qux": {
        "$id": "qux",
        "$recursiveAnchor": false
      }
    },
    "$defs": {
      "bookending": {
        "$recursiveAnchor": true
      },
      "static": {
        "$ref": "#test"
      },
      "dynamic": {
        "$recursiveRef": "#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::Pointer properties_foo{"properties", "foo"};
  const sourcemeta::core::Pointer properties_bar{"properties", "bar"};
  const sourcemeta::core::Pointer properties_baz{"properties", "baz"};
  const sourcemeta::core::Pointer properties_qux{"properties", "qux"};
  const sourcemeta::core::Pointer defs_bookending{"$defs", "bookending"};

  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_foo)));
  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_bar)));
  EXPECT_FALSE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_baz)));
  EXPECT_FALSE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_qux)));
  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(defs_bookending)));
}

TEST(Frame, has_references_through) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    },
    "$defs": {
      "test": {
        "$ref": "#/properties/foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::Pointer properties_foo{"properties", "foo"};
  const sourcemeta::core::Pointer properties{"properties"};
  const sourcemeta::core::Pointer defs{"$defs"};

  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(properties_foo)));
  EXPECT_TRUE(frame.has_references_through(
      sourcemeta::core::to_weak_pointer(properties_foo)));
  EXPECT_TRUE(frame.has_references_through(
      sourcemeta::core::to_weak_pointer(properties)));
  EXPECT_FALSE(
      frame.has_references_to(sourcemeta::core::to_weak_pointer(properties)));
  EXPECT_FALSE(
      frame.has_references_to(sourcemeta::core::to_weak_pointer(defs)));
  EXPECT_FALSE(
      frame.has_references_through(sourcemeta::core::to_weak_pointer(defs)));
}

TEST(Frame, has_references_through_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentSchema": true,
    "items": {
      "$ref": "#/contentSchema"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const sourcemeta::core::Pointer content_schema{"contentSchema"};

  EXPECT_TRUE(frame.has_references_to(
      sourcemeta::core::to_weak_pointer(content_schema)));
  EXPECT_TRUE(frame.has_references_through(
      sourcemeta::core::to_weak_pointer(content_schema)));
}

TEST(Frame, to_json_empty) {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  const auto result{frame.to_json()};
  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "locations": {
      "static": {},
      "dynamic": {}
    },
    "references": []
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Frame, to_json_mode_references) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "bar"
      },
      "bar": {
        "id": "bar",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto result{frame.to_json()};

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "locations": {
      "static": {
        "https://www.sourcemeta.com/bar": {
          "parent": "",
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test": {
          "parent": null,
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "",
          "position": null,
          "relativePointer": "",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$id": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$id",
          "position": null,
          "relativePointer": "/$id",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$schema": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties",
          "position": null,
          "relativePointer": "/properties",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo",
          "position": null,
          "relativePointer": "/properties/foo",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo/$ref": {
          "parent": "/properties/foo",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo/$ref",
          "position": null,
          "relativePointer": "/properties/foo/$ref",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        }
      },
      "dynamic": {}
    },
    "references": [
      {
        "type": "static",
        "origin": "/$schema",
        "position": null,
        "destination": "https://json-schema.org/draft/2020-12/schema",
        "base": "https://json-schema.org/draft/2020-12/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/bar/$schema",
        "position": null,
        "destination": "http://json-schema.org/draft-04/schema",
        "base": "http://json-schema.org/draft-04/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/foo/$ref",
        "position": null,
        "destination": "https://www.sourcemeta.com/bar",
        "base": "https://www.sourcemeta.com/bar",
        "fragment": null
      }
    ]
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Frame, to_json_mode_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "bar"
      },
      "bar": {
        "id": "bar",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto result{frame.to_json()};

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "locations": {
      "static": {
        "https://www.sourcemeta.com/bar": {
          "parent": "",
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test": {
          "parent": null,
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "",
          "position": null,
          "relativePointer": "",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$id": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$id",
          "position": null,
          "relativePointer": "/$id",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$schema": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties",
          "position": null,
          "relativePointer": "/properties",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo",
          "position": null,
          "relativePointer": "/properties/foo",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo/$ref": {
          "parent": "/properties/foo",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo/$ref",
          "position": null,
          "relativePointer": "/properties/foo/$ref",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        }
      },
      "dynamic": {}
    },
    "references": []
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Frame, to_json_mode_references_with_tracking) {
  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "bar"
      },
      "bar": {
        "id": "bar",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON",
                               document, std::ref(tracker));

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto result{frame.to_json(tracker)};

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "locations": {
      "static": {
        "https://www.sourcemeta.com/bar": {
          "parent": "",
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": [ 8, 7, 12, 7 ],
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": [ 10, 9, 10, 60 ],
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": [ 9, 9, 9, 19 ],
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": [ 11, 9, 11, 24 ],
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test": {
          "parent": null,
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "",
          "position": [ 1, 1, 14, 3 ],
          "relativePointer": "",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$id": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$id",
          "position": [ 2, 5, 2, 44 ],
          "relativePointer": "/$id",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$schema": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$schema",
          "position": [ 3, 5, 3, 61 ],
          "relativePointer": "/$schema",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties",
          "position": [ 4, 5, 13, 5 ],
          "relativePointer": "/properties",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": [ 8, 7, 12, 7 ],
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": [ 10, 9, 10, 60 ],
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": [ 9, 9, 9, 19 ],
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": [ 11, 9, 11, 24 ],
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo",
          "position": [ 5, 7, 7, 7 ],
          "relativePointer": "/properties/foo",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo/$ref": {
          "parent": "/properties/foo",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo/$ref",
          "position": [ 6, 9, 6, 21 ],
          "relativePointer": "/properties/foo/$ref",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        }
      },
      "dynamic": {}
    },
    "references": [
      {
        "type": "static",
        "origin": "/$schema",
        "position": [ 3, 5, 3, 61 ],
        "destination": "https://json-schema.org/draft/2020-12/schema",
        "base": "https://json-schema.org/draft/2020-12/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/bar/$schema",
        "position": [ 10, 9, 10, 60 ],
        "destination": "http://json-schema.org/draft-04/schema",
        "base": "http://json-schema.org/draft-04/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/foo/$ref",
        "position": [ 6, 9, 6, 21 ],
        "destination": "https://www.sourcemeta.com/bar",
        "base": "https://www.sourcemeta.com/bar",
        "fragment": null
      }
    ]
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Frame, to_json_mode_references_with_tracking_empty) {
  sourcemeta::core::PointerPositionTracker tracker;

  // Note we purposely don't pass the tracker to the document
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "bar"
      },
      "bar": {
        "id": "bar",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto result{frame.to_json(tracker)};

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "locations": {
      "static": {
        "https://www.sourcemeta.com/bar": {
          "parent": "",
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/bar#/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test": {
          "parent": null,
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "",
          "position": null,
          "relativePointer": "",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$id": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$id",
          "position": null,
          "relativePointer": "/$id",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/$schema": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties",
          "position": null,
          "relativePointer": "/properties",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/bar/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo",
          "position": null,
          "relativePointer": "/properties/foo",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        },
        "https://www.sourcemeta.com/test#/properties/foo/$ref": {
          "parent": "/properties/foo",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo/$ref",
          "position": null,
          "relativePointer": "/properties/foo/$ref",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false
        }
      },
      "dynamic": {}
    },
    "references": [
      {
        "type": "static",
        "origin": "/$schema",
        "position": null,
        "destination": "https://json-schema.org/draft/2020-12/schema",
        "base": "https://json-schema.org/draft/2020-12/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/bar/$schema",
        "position": null,
        "destination": "http://json-schema.org/draft-04/schema",
        "base": "http://json-schema.org/draft-04/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/foo/$ref",
        "position": null,
        "destination": "https://www.sourcemeta.com/bar",
        "base": "https://www.sourcemeta.com/bar",
        "fragment": null
      }
    ]
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Frame, invalid_schema_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(Frame, invalid_schema_not_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "not a valid uri"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.value(), "not a valid uri");
  } catch (...) {
    FAIL();
  }
}

TEST(Frame, override_induces_resource_boundary) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/parent",
    "definitions": {
      "child": {
        "$id": "http://example.com/child",
        "x-sourcemeta-dialect-override-subschema":
          "http://json-schema.org/draft-06/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 10);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "http://example.com/parent", "http://example.com/parent", "",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "http://example.com/parent", "", std::nullopt, false, false);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "http://example.com/child", "http://example.com/parent",
      "/definitions/child", "http://json-schema.org/draft-06/schema#",
      JSON_Schema_Draft_6, "http://example.com/child", "", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/parent#/id", "http://example.com/parent",
      "/id", "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "http://example.com/parent", "/id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "http://example.com/parent#/$schema",
                              "http://example.com/parent", "/$schema",
                              "http://json-schema.org/draft-04/schema#",
                              JSON_Schema_Draft_4, "http://example.com/parent",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "http://example.com/parent#/definitions",
                              "http://example.com/parent", "/definitions",
                              "http://json-schema.org/draft-04/schema#",
                              JSON_Schema_Draft_4, "http://example.com/parent",
                              "/definitions", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/parent#/definitions/child/$id",
      "http://example.com/parent", "/definitions/child/$id",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/child", "/$id", "/definitions/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "http://example.com/parent#/definitions/child/"
      "x-sourcemeta-dialect-override-subschema",
      "http://example.com/parent",
      "/definitions/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/child", "/x-sourcemeta-dialect-override-subschema",
      "/definitions/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/child#/$id", "http://example.com/parent",
      "/definitions/child/$id", "http://json-schema.org/draft-06/schema#",
      JSON_Schema_Draft_6, "http://example.com/child", "/$id",
      "/definitions/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "http://example.com/child#/x-sourcemeta-dialect-override-subschema",
      "http://example.com/parent",
      "/definitions/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/child", "/x-sourcemeta-dialect-override-subschema",
      "/definitions/child", false, true);

  // Subschemas

  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "http://example.com/parent#/definitions/child",
      "http://example.com/parent", "/definitions/child",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/child", "", "", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
}

TEST(Frame, override_destroys_resource_boundary_id_discarded) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/parent",
    "$defs": {
      "child": {
        "$id": "https://example.com/child",
        "x-sourcemeta-dialect-override-subschema":
          "http://json-schema.org/draft-04/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 7);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/parent", "https://example.com/parent", "",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/parent", "", std::nullopt, false, false);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/parent#/$id",
                              "https://example.com/parent", "/$id",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/parent",
                              "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/parent#/$schema",
                              "https://example.com/parent", "/$schema",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/parent",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/parent#/$defs",
                              "https://example.com/parent", "/$defs",
                              "https://json-schema.org/draft/2020-12/schema",
                              JSON_Schema_2020_12, "https://example.com/parent",
                              "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame,
                              "https://example.com/parent#/$defs/child/$id",
                              "https://example.com/parent", "/$defs/child/$id",
                              "http://json-schema.org/draft-04/schema#",
                              JSON_Schema_Draft_4, "https://example.com/parent",
                              "/$defs/child/$id", "/$defs/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/parent#/$defs/child/"
      "x-sourcemeta-dialect-override-subschema",
      "https://example.com/parent",
      "/$defs/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://example.com/parent",
      "/$defs/child/x-sourcemeta-dialect-override-subschema", "/$defs/child",
      false, true);

  // Subschemas

  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/parent#/$defs/child",
      "https://example.com/parent", "/$defs/child",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "https://example.com/parent", "/$defs/child", "", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2020-12/schema",
      "https://json-schema.org/draft/2020-12/schema", std::nullopt,
      "https://json-schema.org/draft/2020-12/schema");
}

TEST(Frame, override_unresolvable_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://example.com/does-not-exist"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  EXPECT_THROW(frame.analyse(document, sourcemeta::blaze::schema_walker,
                             sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Frame, override_inert_under_draft7_ref_siblings) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/definitions/bar",
        "x-sourcemeta-dialect-override-subschema":
          "https://example.com/does-not-exist"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 9);

  // JSON Pointers

  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/$schema", "/$schema", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions", "/definitions",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/definitions/bar/type", "/definitions/bar/type",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "/definitions/bar", false, true);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties", "/properties",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/$ref", "/properties/foo/$ref",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "/properties/foo", false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(
      frame, "#/properties/foo/x-sourcemeta-dialect-override-subschema",
      "/properties/foo/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "/properties/foo", false, false);

  // Subschemas

  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "", "", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, std::nullopt, false, false);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/definitions/bar", "/definitions/bar",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      true);
  EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(
      frame, "#/properties/foo", "/properties/foo",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7, "", false,
      false);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-07/schema",
      "http://json-schema.org/draft-07/schema", std::nullopt,
      "http://json-schema.org/draft-07/schema#");
  EXPECT_STATIC_REFERENCE(frame, "/properties/foo/$ref", "#/definitions/bar",
                          "", "/definitions/bar", "#/definitions/bar");
}

TEST(Frame, override_surfaces_after_2019_09_upgrade) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar",
        "x-sourcemeta-dialect-override-subschema":
          "https://example.com/does-not-exist"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  EXPECT_THROW(frame.analyse(document, sourcemeta::blaze::schema_walker,
                             sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Frame, override_picks_dollarid_under_draft6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "http://example.com/parent",
    "definitions": {
      "child": {
        "id": "http://example.com/via-id",
        "$id": "http://example.com/via-dollarid",
        "x-sourcemeta-dialect-override-subschema":
          "http://json-schema.org/draft-06/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 12);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "http://example.com/parent", "http://example.com/parent", "",
      "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "http://example.com/parent", "", std::nullopt, false, false);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "http://example.com/via-dollarid", "http://example.com/parent",
      "/definitions/child", "http://json-schema.org/draft-06/schema#",
      JSON_Schema_Draft_6, "http://example.com/via-dollarid", "", "", false,
      true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/parent#/id", "http://example.com/parent",
      "/id", "http://json-schema.org/draft-04/schema#", JSON_Schema_Draft_4,
      "http://example.com/parent", "/id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "http://example.com/parent#/$schema",
                              "http://example.com/parent", "/$schema",
                              "http://json-schema.org/draft-04/schema#",
                              JSON_Schema_Draft_4, "http://example.com/parent",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "http://example.com/parent#/definitions",
                              "http://example.com/parent", "/definitions",
                              "http://json-schema.org/draft-04/schema#",
                              JSON_Schema_Draft_4, "http://example.com/parent",
                              "/definitions", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/parent#/definitions/child/id",
      "http://example.com/parent", "/definitions/child/id",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/via-dollarid", "/id", "/definitions/child", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/parent#/definitions/child/$id",
      "http://example.com/parent", "/definitions/child/$id",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/via-dollarid", "/$id", "/definitions/child", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "http://example.com/parent#/definitions/child/"
      "x-sourcemeta-dialect-override-subschema",
      "http://example.com/parent",
      "/definitions/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/via-dollarid",
      "/x-sourcemeta-dialect-override-subschema", "/definitions/child", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/via-dollarid#/id", "http://example.com/parent",
      "/definitions/child/id", "http://json-schema.org/draft-06/schema#",
      JSON_Schema_Draft_6, "http://example.com/via-dollarid", "/id",
      "/definitions/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "http://example.com/via-dollarid#/$id",
      "http://example.com/parent", "/definitions/child/$id",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/via-dollarid", "/$id", "/definitions/child", false,
      true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "http://example.com/via-dollarid#/"
      "x-sourcemeta-dialect-override-subschema",
      "http://example.com/parent",
      "/definitions/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/via-dollarid",
      "/x-sourcemeta-dialect-override-subschema", "/definitions/child", false,
      true);

  // Subschemas

  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "http://example.com/parent#/definitions/child",
      "http://example.com/parent", "/definitions/child",
      "http://json-schema.org/draft-06/schema#", JSON_Schema_Draft_6,
      "http://example.com/via-dollarid", "", "", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "http://json-schema.org/draft-04/schema",
      "http://json-schema.org/draft-04/schema", std::nullopt,
      "http://json-schema.org/draft-04/schema#");
}

TEST(Frame, override_hides_anchor_under_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/parent",
    "$defs": {
      "child": {
        "$id": "https://example.com/child",
        "$anchor": "x",
        "x-sourcemeta-dialect-override-subschema":
          "http://json-schema.org/draft-07/schema#"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 12);

  EXPECT_FALSE(frame.locations().contains(
      {sourcemeta::blaze::SchemaReferenceType::Static,
       "https://example.com/child#x"}));

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/parent", "https://example.com/parent", "",
      "https://json-schema.org/draft/2019-09/schema", JSON_Schema_2019_09,
      "https://example.com/parent", "", std::nullopt, false, false);

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/child", "https://example.com/parent",
      "/$defs/child", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "https://example.com/child", "", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/parent#/$schema",
                              "https://example.com/parent", "/$schema",
                              "https://json-schema.org/draft/2019-09/schema",
                              JSON_Schema_2019_09, "https://example.com/parent",
                              "/$schema", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/parent#/$id",
                              "https://example.com/parent", "/$id",
                              "https://json-schema.org/draft/2019-09/schema",
                              JSON_Schema_2019_09, "https://example.com/parent",
                              "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/parent#/$defs",
                              "https://example.com/parent", "/$defs",
                              "https://json-schema.org/draft/2019-09/schema",
                              JSON_Schema_2019_09, "https://example.com/parent",
                              "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/parent#/$defs/child/$id",
      "https://example.com/parent", "/$defs/child/$id",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/child", "/$id", "/$defs/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/parent#/$defs/child/$anchor",
      "https://example.com/parent", "/$defs/child/$anchor",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/child", "/$anchor", "/$defs/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/parent#/$defs/child/"
      "x-sourcemeta-dialect-override-subschema",
      "https://example.com/parent",
      "/$defs/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/child", "/x-sourcemeta-dialect-override-subschema",
      "/$defs/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/child#/$id",
                              "https://example.com/parent", "/$defs/child/$id",
                              "http://json-schema.org/draft-07/schema#",
                              JSON_Schema_Draft_7, "https://example.com/child",
                              "/$id", "/$defs/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/child#/$anchor", "https://example.com/parent",
      "/$defs/child/$anchor", "http://json-schema.org/draft-07/schema#",
      JSON_Schema_Draft_7, "https://example.com/child", "/$anchor",
      "/$defs/child", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/child#/x-sourcemeta-dialect-override-subschema",
      "https://example.com/parent",
      "/$defs/child/x-sourcemeta-dialect-override-subschema",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/child", "/x-sourcemeta-dialect-override-subschema",
      "/$defs/child", false, true);

  // Subschemas

  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/parent#/$defs/child",
      "https://example.com/parent", "/$defs/child",
      "http://json-schema.org/draft-07/schema#", JSON_Schema_Draft_7,
      "https://example.com/child", "", "", false, true);

  // References

  EXPECT_EQ(frame.references().size(), 1);

  EXPECT_STATIC_REFERENCE(
      frame, "/$schema", "https://json-schema.org/draft/2019-09/schema",
      "https://json-schema.org/draft/2019-09/schema", std::nullopt,
      "https://json-schema.org/draft/2019-09/schema");
}

TEST(Frame, vocabularies_embedded_custom_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto root_location{frame.traverse("https://example.com/schema")};
  EXPECT_TRUE(root_location.has_value());
  const auto root_vocabularies{frame.vocabularies(
      root_location->get(), sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(root_vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Validation);

  const auto metaschema_location{frame.traverse("https://example.com/meta")};
  EXPECT_TRUE(metaschema_location.has_value());
  const auto metaschema_vocabularies{frame.vocabularies(
      metaschema_location->get(), sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(metaschema_vocabularies.size(), 7);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies,
                             JSON_Schema_2020_12_Applicator);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies,
                             JSON_Schema_2020_12_Unevaluated);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies,
                             JSON_Schema_2020_12_Validation);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies,
                             JSON_Schema_2020_12_Meta_Data);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies,
                             JSON_Schema_2020_12_Format_Annotation);
  EXPECT_VOCABULARY_REQUIRED(metaschema_vocabularies,
                             JSON_Schema_2020_12_Content);
}

TEST(Frame, vocabularies_embedded_custom_metaschema_precedence) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  // A resolver that knows about the custom meta-schema, but with a
  // different vocabulary set than the embedded copy, used to assert that
  // meta-schemas embedded in the document take precedence over the resolver
  const auto resolver =
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/meta") {
      return sourcemeta::core::parse_json(R"JSON({
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        }
      })JSON");
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker, resolver);

  const auto root_location{frame.traverse("https://example.com/schema")};
  EXPECT_TRUE(root_location.has_value());
  const auto root_vocabularies{
      frame.vocabularies(root_location->get(), resolver)};
  EXPECT_EQ(root_vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Validation);
}
