#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>

#include <string_view> // std::string_view

static auto test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://www.sourcemeta.com/recursive") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/recursive",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  }
  return sourcemeta::core::schema_resolver(identifier);
}

static auto draft7_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://www.sourcemeta.com/recursive") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-07/schema#",
      "$id": "https://www.sourcemeta.com/recursive",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  }
  return sourcemeta::core::schema_resolver(identifier);
}

TEST(draft7_bundle_to_defs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, draft7_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"$defs"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://www.sourcemeta.com/recursive",
    "$defs": {
      "https://www.sourcemeta.com/recursive": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://www.sourcemeta.com/recursive",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_nested_object_path_non_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"x-definitions", "foo", "bar"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": {
      "foo": {
        "bar": {
          "https://www.sourcemeta.com/recursive": {
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "$id": "https://www.sourcemeta.com/recursive",
            "properties": {
              "foo": { "$ref": "#" }
            }
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_nested_object_path_half_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": { "foo": {} }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"x-definitions", "foo", "bar"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": {
      "foo": {
        "bar": {
          "https://www.sourcemeta.com/recursive": {
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "$id": "https://www.sourcemeta.com/recursive",
            "properties": {
              "foo": { "$ref": "#" }
            }
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_nested_object_path_half_existent_with_array) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": [ { "foo": {} } ]
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"x-definitions", 0, "foo", "bar"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": [
      {
        "foo": {
          "bar": {
            "https://www.sourcemeta.com/recursive": {
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "$id": "https://www.sourcemeta.com/recursive",
              "properties": {
                "foo": { "$ref": "#" }
              }
            }
          }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}
