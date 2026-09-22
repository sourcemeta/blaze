#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/convert.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#define EXPECT_BROKEN_REFERENCE(document, target, expected_identifier,         \
                                expected_location)                             \
  {                                                                            \
    auto schema = sourcemeta::core::parse_json(document);                      \
    try {                                                                      \
      sourcemeta::blaze::convert(schema, sourcemeta::core::schema_walker,      \
                                 sourcemeta::core::schema_resolver,            \
                                 sourcemeta::blaze::ConvertTarget::target);    \
      FAIL();                                                                  \
    } catch (const sourcemeta::blaze::ConvertBrokenReferenceError &error) {    \
      EXPECT_STREQ(error.what(), "The reference broke after transformation");  \
      EXPECT_EQ(error.identifier(), (expected_identifier));                    \
      EXPECT_EQ(sourcemeta::core::to_string(error.location()),                 \
                (expected_location));                                          \
    }                                                                          \
  }

TEST(dependencies_container_reference_with_mixed_forms_2019_09) {
  EXPECT_BROKEN_REFERENCE(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/x",
    "properties": { "v": { "$ref": "#/dependencies" } },
    "dependencies": { "a": [ "b" ], "c": { "type": "string" } }
  })JSON",
                          Draft202012, "https://example.com/x#/dependencies",
                          "/properties/v/$ref");
}

TEST(dependencies_container_reference_with_mixed_forms_draft7) {
  EXPECT_BROKEN_REFERENCE(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com/x",
    "properties": { "v": { "$ref": "#/dependencies" } },
    "dependencies": { "a": [ "b" ], "c": { "type": "string" } }
  })JSON",
                          Draft202012, "https://example.com/x#/dependencies",
                          "/properties/v/$ref");
}

TEST(dependencies_container_reference_with_empty_object) {
  EXPECT_BROKEN_REFERENCE(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/x",
    "properties": { "v": { "$ref": "#/dependencies" } },
    "dependencies": {}
  })JSON",
                          Draft202012, "https://example.com/x#/dependencies",
                          "/properties/v/$ref");
}
