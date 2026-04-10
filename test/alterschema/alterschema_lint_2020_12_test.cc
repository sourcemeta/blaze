#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_lint_2020_12, local_ref_to_unknown_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, local_ref_to_unknown_location_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, local_ref_to_unknown_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     local_ref_to_unknown_location_with_nested_resource_relative) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "foo#/$defs/foo",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     local_ref_to_unknown_location_with_nested_resource_relative_valid) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     local_ref_to_unknown_location_with_nested_resource_absolute) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.example.com/foo#/$defs/foo",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     local_ref_to_unknown_location_with_nested_resource_absolute_valid) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.example.com/foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.example.com/foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, nested_ref_to_unknown_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, nested_ref_to_existing_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, deeply_nested_ref_to_unknown_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "items": {
          "properties": {
            "bar": {
              "$ref": "#/$defs/baz"
            }
          }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "items": {
          "properties": {
            "bar": true
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, nested_ref_to_unknown_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "#unknownAnchor"
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, nested_ref_to_existing_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "myDef": {
        "$anchor": "myAnchor",
        "type": "number"
      }
    },
    "properties": {
      "value": {
        "$ref": "#myAnchor"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "myDef": {
        "$anchor": "myAnchor",
        "type": "number"
      }
    },
    "properties": {
      "value": {
        "$ref": "#myAnchor"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, mixed_nested_refs_valid_and_invalid) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "string": { "type": "string" }
    },
    "properties": {
      "name": {
        "$ref": "#/$defs/string"
      },
      "age": {
        "$ref": "#/$defs/number"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "string": { "type": "string" }
    },
    "properties": {
      "name": {
        "$ref": "#/$defs/string"
      },
      "age": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, external_ref_with_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "https://example.com/schema#/$defs/bar"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "https://example.com/schema#/$defs/bar"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, external_ref_with_unknown_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://json-schema.org/draft/2020-12/schema#/$defs/nonNegativeInteger"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://json-schema.org/draft/2020-12/schema#/$defs/nonNegativeInteger"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, nested_external_ref_with_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/base-schema#/$defs/common",
    "properties": {
      "value": {
        "$ref": "http://another-example.com/types#/definitions/string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/base-schema#/$defs/common",
    "properties": {
      "value": {
        "$ref": "http://another-example.com/types#/definitions/string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     external_relative_ref_with_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "data": {
        "$ref": "common-types.json#/$defs/uuid"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "data": {
        "$ref": "common-types.json#/$defs/uuid"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, enum_to_const_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, const_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, const_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "null" ],
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, const_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, const_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "boolean", "null" ],
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "boolean", "null" ],
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, enum_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, enum_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, enum_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, enum_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, single_type_array_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "string" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, content_media_type_without_encoding_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentMediaType": "application/json"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, content_schema_without_media_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentSchema": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, max_contains_without_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "maxContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, max_contains_without_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": true,
    "maxContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": true,
    "maxContains": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, min_contains_without_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, min_contains_without_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": true,
    "minContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": true,
    "minContains": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_without_if_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "then": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_without_if_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "then": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "then": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_without_if_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "else": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_without_if_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "else": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "else": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, if_without_then_else_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_properties_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_properties_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_items_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_items_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_items_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, content_schema_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, content_schema_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, content_schema_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, items_schema_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, items_schema_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, items_schema_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_enum_values_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, {}, 2, 1, 1, 3, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, {}, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_enum_values_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "S", "C", "U", "F", "E", "N", "L", "R", "U", null ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "S", "C", "U", "F", "E", "N", "L", "R", null ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_required_values_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar", "baz", "foo" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_maximum_number_and_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMaximum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMaximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_maximum_number_and_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMaximum": 3,
    "maximum": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "maximum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_maximum_number_and_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMaximum": 3,
    "maximum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "maximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_minimum_number_and_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 3,
    "minimum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_minimum_number_and_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 3,
    "minimum": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_minimum_number_and_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "exclusiveMinimum": 3,
    "minimum": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, allof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ false, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, allof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, allof_false_simplify_with_ref_through) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ false, { "type": "string" } ],
    "properties": {
      "foo": { "$ref": "#/allOf/1" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ false, { "type": "string" } ],
    "properties": {
      "foo": { "$ref": "#/allOf/1" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_allof_branches_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ { "type": "string" }, { "type": "integer" }, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_anyof_branches_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "type": "string" }, { "type": "integer" }, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_anyof_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "anyOf": [
      { "type": "number" },
      { "minLength": 1 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "anyOf": [
      { "minLength": 1 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_anyof_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "anyOf": [
      { "type": "array" },
      { "type": "string" },
      { "type": "object", "minProperties": 1 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "anyOf": [
      { "type": "object", "minProperties": 1 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_oneof_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "oneOf": [
      { "type": "string" },
      { "minimum": 0 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "oneOf": [
      false,
      { "minimum": 0 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_oneof_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "oneOf": [
      { "type": "object" },
      { "type": "string" },
      { "type": "array", "minItems": 1 },
      { "type": "number" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "oneOf": [
      false,
      false,
      { "type": "array", "minItems": 1 },
      false
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_if_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": { "type": "number" },
    "then": { "minLength": 1 }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": false,
    "then": { "minLength": 1 }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_then_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "required": [ "foo" ] },
    "then": { "type": "array" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "required": [ "foo" ], "properties": { "foo": true } },
    "then": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_else_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "if": { "minimum": 0 },
    "else": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "if": { "minimum": 0 },
    "else": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_if_then_else_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": { "type": "number" },
    "then": { "type": "array" },
    "else": { "type": "object" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": false,
    "then": false,
    "else": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_logic_branch_type_mixed_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "allOf": [ { "type": "string" } ],
    "anyOf": [ { "type": "object" }, { "multipleOf": 2 } ],
    "oneOf": [ { "type": "array" }, { "minimum": 0 } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, maximum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, minimum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, dependent_required_tautology_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo" ],
    "dependentRequired": {
      "foo": [ "bar" ],
      "xxx": [ "yyy" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "dependentRequired": {
      "xxx": [ "yyy" ]
    },
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, dependent_required_tautology_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo" ],
    "dependentRequired": {
      "foo": [ "bar" ],
      "bar": [ "baz" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar", "baz" ],
    "properties": {
      "foo": true,
      "bar": true,
      "baz": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, pattern_properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "patternProperties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_min_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_min_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "bar", "baz", "foo" ],
    "minProperties": 4,
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_min_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_array_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "array",
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "array",
    "minItems": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_boolean_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "boolean",
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_null_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "null",
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_numeric_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "number",
    "multipleOf": 2,
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "number",
    "multipleOf": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_numeric_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "integer",
    "multipleOf": 2,
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "integer",
    "multipleOf": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_object_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "object",
    "multipleOf": 2,
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "object",
    "unevaluatedProperties": false,
    "maxProperties": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, drop_non_string_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "string",
    "multipleOf": 2,
    "unevaluatedProperties": false,
    "contentEncoding": "base64",
    "maxProperties": 3,
    "format": "uri",
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "type": "string",
    "contentEncoding": "base64",
    "format": "uri"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, type_boolean_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, type_null_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, const_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_maximum_integer_to_maximum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, exclusive_minimum_integer_to_minimum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_max_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_max_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unsatisfiable_max_contains_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 5,
    "maxContains": 3
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "incoherent_min_max_contains",
                    "`minContains` greater than `maxContains` makes the "
                    "schema unsatisfiable",
                    false);
  EXPECT_LINT_TRACE(traces, 1, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 3,
    "maxContains": 3
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 1,
    "maxContains": 5
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "array",
        "contains": { "type": "string" },
        "minContains": 5,
        "maxContains": 3
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "incoherent_min_max_contains",
                    "`minContains` greater than `maxContains` makes the "
                    "schema unsatisfiable",
                    false);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_5) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 5
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "items": {
      "type": "array",
      "contains": { "type": "string" },
      "minContains": 5,
      "maxContains": 3
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/items", "incoherent_min_max_contains",
                    "`minContains` greater than `maxContains` makes the "
                    "schema unsatisfiable",
                    false);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "array",
        "contains": { "type": "string" },
        "minContains": 5,
        "maxContains": 3
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "/$defs/foo", "incoherent_min_max_contains",
                    "`minContains` greater than `maxContains` makes the "
                    "schema unsatisfiable",
                    false);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_8) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "$ref": "#/$defs/A/properties/bar",
    "$defs": {
      "A": {
        "type": "array",
        "contains": { "type": "string" },
        "minContains": 5,
        "maxContains": 3,
        "properties": {
          "bar": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "/$defs/A", "incoherent_min_max_contains",
                    "`minContains` greater than `maxContains` makes the "
                    "schema unsatisfiable",
                    false);
}

TEST(AlterSchema_lint_2020_12, incoherent_min_max_contains_9) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "minContains": 5,
    "maxContains": 3
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "max_contains_without_contains",
                    "The `maxContains` keyword is meaningless "
                    "without the presence of the `contains` keyword",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "", "min_contains_without_contains",
                    "The `minContains` keyword is meaningless "
                    "without the presence of the `contains` keyword",
                    true);
}

TEST(AlterSchema_lint_2020_12, equal_numeric_bounds_to_const_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, equal_numeric_bounds_to_const_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, equal_numeric_bounds_to_const_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 1.0e400,
    "maximum": 1.0e400
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 1.0e+400
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/foo",
    "allOf": [
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/foo",
    "allOf": [
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "$ref": "https://example.com" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "type": "integer",
    "allOf": [
      { "type": "number" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "integer",
        "$ref": "https://example.com"
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com" }
    ],
    "title": "Foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "title": "Foo"
  })JSON");

  EXPECT_EQ(document, expected);

  // We expect the `$ref` keyword to take the place of `allOf` in
  // terms of keyword ordering
  std::vector<sourcemeta::core::JSON::String> keywords;
  for (const auto &entry : document.as_object()) {
    keywords.emplace_back(entry.first);
  }

  EXPECT_EQ(keywords.size(), 3);
  EXPECT_EQ(keywords.at(0), "$schema");
  EXPECT_EQ(keywords.at(1), "$ref");
  EXPECT_EQ(keywords.at(2), "title");
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com" },
      { "type": "string" }
    ],
    "title": "Foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "type": "string",
    "title": "Foo"
  })JSON");

  EXPECT_EQ(document, expected);

  // We expect the `$ref` and `type` keywords to take the place of `allOf` in
  // terms of keyword ordering
  std::vector<sourcemeta::core::JSON::String> keywords;
  for (const auto &entry : document.as_object()) {
    keywords.emplace_back(entry.first);
  }

  EXPECT_EQ(keywords.size(), 4);
  EXPECT_EQ(keywords.at(0), "$schema");
  EXPECT_EQ(keywords.at(1), "$ref");
  EXPECT_EQ(keywords.at(2), "type");
  EXPECT_EQ(keywords.at(3), "title");
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string", "$ref": "https://example.com" }
    ],
    "title": "Foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "type": "string",
    "title": "Foo"
  })JSON");

  EXPECT_EQ(document, expected);

  // We expect the `$ref` and `type` keywords to take the place of `allOf` in
  // terms of keyword ordering
  std::vector<sourcemeta::core::JSON::String> keywords;
  for (const auto &entry : document.as_object()) {
    keywords.emplace_back(entry.first);
  }

  EXPECT_EQ(keywords.size(), 4);
  EXPECT_EQ(keywords.at(0), "$schema");
  EXPECT_EQ(keywords.at(1), "$ref");
  EXPECT_EQ(keywords.at(2), "type");
  EXPECT_EQ(keywords.at(3), "title");
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_9) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ "test" ],
    "allOf": [
      { "type": "string", "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "unnecessary_allof_ref_wrapper_modern",
                    "Wrapping `$ref` in `allOf` was only necessary in JSON "
                    "Schema Draft 7 and older",
                    true);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number", "$ref": "https://example.com" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "type": "integer",
    "allOf": [
      { "type": "number" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "if": { "type": "string" }, "then": { "minLength": 1 } },
      { "if": { "type": "integer" }, "then": { "minimum": 1 } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "integer" },
    "then": { "minimum": 1 },
    "allOf": [
      { "if": { "type": "string" }, "then": { "minLength": 1 } }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_13) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "allOf": [
      { "patternProperties": { "^f": { "type": "string" } } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "allOf": [
      { "patternProperties": { "^f": { "type": "string" } } }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_14) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false,
    "allOf": [
      { "prefixItems": [ true, false ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false,
    "allOf": [
      { "prefixItems": [ true, false ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_15) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false,
    "properties": { "foo": { "type": "string" } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_16) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "allOf": [
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 5,
    "allOf": [
      { "type": "string", "minLength": 5 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_18) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com", "minLength": 5 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "minLength": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_cross_dependency_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "properties": { "foo": {} } },
      { "additionalProperties": false }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "allOf": [
      { "properties": { "foo": true } }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_cross_dependency_prefixItems) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "prefixItems": [ { "type": "string" } ] },
      { "items": false }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": false,
    "allOf": [
      { "prefixItems": [ { "type": "string" } ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_cross_dependency_contains_minContains) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "contains": { "type": "number" } },
      { "minContains": 2 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contains": { "type": "number" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_with_dynamic_ref_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$dynamicRef": "#foo", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#foo",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_with_id_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$id": "nested", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$id": "nested", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_with_anchor_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$anchor": "foo", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$anchor": "foo", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_with_dynamic_anchor_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$dynamicAnchor": "foo", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$dynamicAnchor": "foo", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, multiple_of_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, multiple_of_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "multipleOf": 1.0,
    "unevaluatedProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, multiple_of_default_no_change_string_value) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": "1"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": "1"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, multiple_of_default_no_change_numeric_value) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 2.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 2.5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "properties": {
          "bar": { "type": "string" }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "properties": {
          "bar": { "type": "string" }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "properties": {
          "foo": { "minLength": 3 }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "properties": {
          "foo": { "minLength": 3 }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "properties": {
          "bar": { "minLength": 3 },
          "baz": { "maxLength": 5 }
        }
      },
      { "type": "object" },
      {
        "properties": {
          "qux": { "pattern": "^f" }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "type": "object",
    "allOf": [
      {
        "properties": {
          "bar": { "minLength": 3 },
          "baz": { "maxLength": 5 }
        }
      },
      {
        "properties": {
          "qux": { "pattern": "^f" }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_properties_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "allOf": [
      {
        "$ref": "https://example.com",
        "properties": {
          "bar": { "pattern": "^f" }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    },
    "$ref": "https://example.com",
    "allOf": [
      {
        "properties": {
          "bar": { "pattern": "^f" }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_ref_wrapper_modern_elevation_single_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_ref_wrapper_modern_elevation_multiple_refs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" },
      { "$ref": "https://example.com/baz" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" },
      { "$ref": "https://example.com/baz" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    unnecessary_allof_ref_wrapper_modern_elevation_mixed_branches_with_and_without_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "properties": { "bar": { "type": "string" } } },
      { "$ref": "https://example.com/baz", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$ref": "https://example.com/foo",
    "properties": { "bar": { "type": "string" } },
    "allOf": [
      { "$ref": "https://example.com/baz", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_ref_wrapper_modern_no_elevation_ref_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "https://example.com",
        "$id": "https://other.com"
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "https://example.com",
        "$id": "https://other.com"
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_ref_wrapper_modern_no_elevation_parent_has_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/main",
    "allOf": [
      { "$ref": "https://example.com/foo" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/main",
    "allOf": [
      { "$ref": "https://example.com/foo" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_ref_wrapper_modern_no_elevation_all_branches_have_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    unnecessary_allof_ref_wrapper_modern_no_elevation_all_branches_have_ref_with_siblings) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo", "type": "object" },
      { "$ref": "https://example.com/bar", "properties": { "x": { "type": "string" } } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://example.com/foo", "type": "object" },
      { "$ref": "https://example.com/bar", "properties": { "x": { "type": "string" } } }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_ref_wrapper_modern_elevation_ref_with_siblings) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "$ref": "https://example.com",
        "type": "object",
        "properties": { "foo": { "type": "string" } }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com",
    "type": "object",
    "properties": { "foo": { "type": "string" } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, modern_official_dialect_with_empty_fragment_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, modern_official_dialect_with_empty_fragment_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/hyper-schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/hyper-schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, modern_official_dialect_with_empty_fragment_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  // Should remain unchanged since there's no empty fragment
  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_empty_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "then": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_empty_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "else": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_empty_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "then": {},
    "else": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_empty_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "then": {
      "type": "string"
    },
    "else": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "then": {
      "type": "string"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_empty_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "else": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_empty_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "properties": {
        "flag": {
          "const": true
        }
      }
    },
    "then": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_empty_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "then": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, property_names_type_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "type": "string",
      "pattern": "^S_"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "pattern": "^S_"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, property_names_type_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "type": [ "string" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, property_names_type_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "type": "integer"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "type": "integer"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, property_names_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, definitions_to_defs_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "definitions": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, definitions_to_defs_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/properties/bar/definitions/helper"
      },
      "bar": {
        "definitions": {
          "helper": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/properties/bar/$defs/helper"
      },
      "bar": {
        "$defs": {
          "helper": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, definitions_to_defs_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "properties": {
          "bar": {
            "definitions": {
              "baz": {
                "type": "string",
                "format": "uuid"
              },
              "qux": {
                "type": "number"
              }
            },
            "properties": {
              "id": {
                "$ref": "#/properties/foo/properties/bar/definitions/baz"
              },
              "count": {
                "$ref": "#/properties/foo/properties/bar/definitions/qux"
              }
            }
          }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "properties": {
          "bar": {
            "$defs": {
              "baz": {
                "type": "string",
                "format": "uuid"
              },
              "qux": {
                "type": "number"
              }
            },
            "properties": {
              "id": {
                "$ref": "#/properties/foo/properties/bar/$defs/baz"
              },
              "count": {
                "$ref": "#/properties/foo/properties/bar/$defs/qux"
              }
            }
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_type_specific_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_type_specific_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": null,
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": null
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_type_specific_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "foo",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "foo",
    "maxLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minimum": 5,
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minimum": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "not": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "not": {
      "type": "number"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "not": {
      "type": "number"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": {},
      "bar": false,
      "baz": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": false,
      "baz": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "anyOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "anyOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "anyOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar", "baz" ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "anyOf": [
      { "required": [ "foo" ] },
      {
        "required": [ "bar", "baz" ],
        "properties": {
          "baz": true
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "oneOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "oneOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "oneOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar", "baz" ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "oneOf": [
      { "required": [ "foo" ] },
      {
        "required": [ "bar", "baz" ],
        "properties": {
          "baz": true
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "allOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar" ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "required": [ "bar" ],
    "allOf": [
      { "required": [ "foo" ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true },
    "allOf": [
      { "required": [ "foo" ] },
      { "required": [ "bar", "baz" ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true, "baz": true },
    "required": [ "bar", "baz" ],
    "allOf": [
      { "required": [ "foo" ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true, "baz": true },
    "if": { "required": [ "foo" ] },
    "then": { "required": [ "bar" ] },
    "else": { "required": [ "baz" ] }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true, "bar": true, "baz": true },
    "if": { "required": [ "foo" ] },
    "then": { "required": [ "bar" ] },
    "else": { "required": [ "baz" ] }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_13) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "not": { "required": [ "foo" ] }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "not": { "required": [ "foo" ] }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_14) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": { "required": [ "foo" ] }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": true },
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": { "required": [ "foo" ] }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_15) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "$ref": "#/$defs/helper",
    "$defs": {
      "helper": {
        "properties": { "foo": true, "bar": true }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "$ref": "#/$defs/helper",
    "properties": { "foo": true, "bar": true },
    "$defs": {
      "helper": {
        "properties": { "foo": true, "bar": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_16) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, required_properties_in_properties_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "fooBar": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-fooBar": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "baz": 123
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "x-baz": 123
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-alreadyPrefixed": true,
    "X-alsoGood": 456,
    "needsPrefix": "value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "x-needsPrefix": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "customKeyword": "value",
    "anotherOne": 123,
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-customKeyword": "value",
    "x-anotherOne": 123,
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "original value",
    "x-foo": "already prefixed value",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-x-foo": "original value",
    "x-foo": "already prefixed value",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "original value",
    "x-foo": "first prefixed",
    "x-x-foo": "second prefixed",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-x-x-foo": "original value",
    "x-foo": "first prefixed",
    "x-x-foo": "second prefixed",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/MyType",
    "definitions": {
      "MyType": { "type": "string" }
    },
    "customKeyword": "should be prefixed",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/MyType",
    "$defs": {
      "MyType": { "type": "string" }
    },
    "x-customKeyword": "should be prefixed",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/MyType",
    "unknownKeyword": "should be prefixed in modern drafts",
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-unknownKeyword": "should be prefixed in modern drafts",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "unevaluatedProperties": false,
    "customKeyword": "should be prefixed"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "unevaluatedProperties": false,
    "x-customKeyword": "should be prefixed"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_12) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ "test" ],
    "unknown-1": 1,
    "unknown-2": 2
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "unknown_keywords_prefix",
      "Future versions of JSON Schema will refuse to evaluate unknown "
      "keywords or custom keywords from optional vocabularies that don't "
      "have an x- prefix",
      true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 2);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/unknown-1");
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(1)),
      "/unknown-2");
}

TEST(AlterSchema_lint_2020_12, unknown_keywords_prefix_13) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2020-12-custom-vocabulary-optional",
    "foo": "bar"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/2020-12-custom-vocabulary-optional",
    "foo": "bar"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ],
    "minLength": 3,
    "pattern": "^[a-z]+$"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "one", "two" ],
    "minimum": 0,
    "maximum": 100,
    "multipleOf": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "one", "two" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ],
    "minLength": 1,
    "minimum": 0,
    "minItems": 1,
    "minProperties": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ { "name": "alice" }, { "age": 25 } ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" }
    },
    "minLength": 5,
    "minimum": 10
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ { "name": "alice" }, { "age": 25 } ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3,
    "minItems": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 42, "hello", true, null, { "key": "value" }, [1, 2, 3] ],
    "minimum": 10,
    "minLength": 2,
    "minItems": 1,
    "minProperties": 1,
    "maxLength": 100,
    "maxItems": 10,
    "maxProperties": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 42, "hello", true, null, { "key": "value" }, [1, 2, 3] ],
    "minimum": 10,
    "minLength": 2,
    "minItems": 1,
    "minProperties": 1,
    "maxLength": 100,
    "maxItems": 10,
    "maxProperties": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "$anchor": "color-enum",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "$comment": "This schema uses enum with various annotation keywords",
    "examples": [ "red", "blue" ],
    "enum": [ "red", "green", "blue" ],
    "minimum": 5,
    "minLength": 10,
    "minItems": 2,
    "minProperties": 1,
    "maxProperties": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "$anchor": "color-enum",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "$comment": "This schema uses enum with various annotation keywords",
    "enum": [ "red", "green", "blue" ],
    "minLength": 10
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, non_applicable_enum_validation_keywords_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ],
    "minLength": 2,
    "maxLength": 10,
    "pattern": "^[a-z]+$"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     non_applicable_enum_validation_keywords_with_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/myType",
    "enum": [ "foo", "bar" ],
    "minimum": 10,
    "maxItems": 5,
    "$defs": {
      "myType": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/myType",
    "enum": [ "foo", "bar" ],
    "$defs": {
      "myType": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     non_applicable_enum_validation_keywords_universal_keywords) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar" ],
    "title": "My enum",
    "description": "A test enum",
    "default": "foo",
    "examples": [ "foo" ],
    "minimum": 10,
    "maxItems": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar" ],
    "title": "My enum",
    "description": "A test enum",
    "default": "foo",
    "examples": [ "foo" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, embedded_resource_draft7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/embedded",
    "$defs": {
      "embedded": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://example.com",
        "definitions": {}
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/embedded",
    "$defs": {
      "embedded": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://example.com",
        "definitions": {}
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, invalid_embedded_resource_draft7_without_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/embedded",
    "$defs": {
      "embedded": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "definitions": {}
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  // As `$schema` without `$id` is ignored
  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/embedded",
    "$defs": {
      "embedded": {
        "$defs": {}
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     invalid_embedded_resource_draft7_with_sibling_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
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

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "embedded",
    "$defs": {
      "embedded": {
        "$id": "embedded",
        "$ref": "#/$defs/foo",
        "$defs": {
          "foo": { "type": "number" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_ref_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com",
    "$ref": "https://example.com"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://sourcemeta.com",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_title_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "description": "Missing title",
    "examples": [ "test" ],
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_title",
                    "Set a concise non-empty title at the top level of the "
                    "schema to explain what the definition is about",
                    false);
}

TEST(AlterSchema_lint_2020_12, top_level_title_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "description": "Missing title",
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "description": "Missing title",
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_description_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Missing description",
    "examples": [ "test" ],
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);
}

TEST(AlterSchema_lint_2020_12, top_level_description_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Missing description",
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Missing description",
    "additionalProperties": {
      "type": "string"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_title_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "",
    "description": "Has empty title",
    "examples": [ "test" ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_title",
                    "Set a concise non-empty title at the top level of the "
                    "schema to explain what the definition is about",
                    false);
}

TEST(AlterSchema_lint_2020_12, top_level_title_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "",
    "description": "Has empty title",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "",
    "description": "Has empty title",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_description_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Has empty description",
    "description": "",
    "examples": [ "test" ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);
}

TEST(AlterSchema_lint_2020_12, top_level_description_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Has empty description",
    "description": "",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Has empty description",
    "description": "",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_description_equal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "My schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_description_equal_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "Different description",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "Different description",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_description_equal_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "Foo property",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_description_equal_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/helper",
    "title": "Top level",
    "description": "Top level description",
    "$defs": {
      "helper": {
        "title": "Helper",
        "description": "Helper",
        "type": "integer"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/helper",
    "title": "Top level",
    "description": "Top level description",
    "$defs": {
      "helper": {
        "title": "Helper",
        "type": "integer"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trailing_period_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema.",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trailing_period_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema...",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trailing_period_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trailing_period_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property.",
        "description": "The foo property",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "The foo property",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trailing_period_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema.",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trailing_period_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema...",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trailing_period_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trailing_period_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "The foo property.",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "The foo property",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trim_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "  My schema  ",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trim_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "\t\nMy schema\r\n",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trim_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trim_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "  Foo property  ",
        "description": "The foo property",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "The foo property",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "  A description of the schema  ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "\t\nA description of the schema\r\n",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "  The foo property  ",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Top level",
    "description": "Top level description",
    "properties": {
      "foo": {
        "title": "Foo property",
        "description": "The foo property",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trim_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "   ",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "",
    "description": "A description of the schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "   ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "a": {
        "description": " untrimmed description a "
      },
      "b": {
        "description": " untrimmed description b "
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 5);

  // The mutable rules that were applied
  EXPECT_LINT_TRACE(traces, 0, "/properties/a", "description_trim",
                    "Descriptions should not contain leading or trailing "
                    "whitespace",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "/properties/b", "description_trim",
                    "Descriptions should not contain leading or trailing "
                    "whitespace",
                    true);

  // The non-mutable rules that couldn't be fixed
  EXPECT_LINT_TRACE(traces, 2, "", "top_level_title",
                    "Set a concise non-empty title at the top level of the "
                    "schema to explain what the definition is about",
                    false);
  EXPECT_LINT_TRACE(traces, 3, "", "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);
  EXPECT_LINT_TRACE(traces, 4, "", "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "a": {
        "description": "untrimmed description a"
      },
      "b": {
        "description": "untrimmed description b"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My Title",
    "description": "My Description",
    "examples": [ "foo" ],
    "allOf": [
      { "minLength": 1 },
      { "minLength": 1 },
      { "minLength": 1 },
      {
        "properties": {
          "foo": { "description": " untrimmed " }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 5);

  EXPECT_LINT_TRACE(
      traces, 0, "", "duplicate_allof_branches",
      "Setting duplicate subschemas in `allOf` is redundant, as it produces "
      "unnecessary additional validation that is guaranteed to not affect the "
      "validation result",
      true);
  EXPECT_LINT_TRACE(
      traces, 1, "", "unnecessary_allof_wrapper",
      "Keywords inside `allOf` that do not conflict with the parent schema can "
      "be elevated",
      true);
  EXPECT_LINT_TRACE(
      traces, 2, "", "duplicate_allof_branches",
      "Setting duplicate subschemas in `allOf` is redundant, as it produces "
      "unnecessary additional validation that is guaranteed to not affect the "
      "validation result",
      true);
  EXPECT_LINT_TRACE(traces, 3, "", "drop_allof_empty_schemas",
                    "Empty schemas in `allOf` are redundant and can be removed",
                    true);
  EXPECT_LINT_TRACE(traces, 4, "/properties/foo", "description_trim",
                    "Descriptions should not contain leading or trailing "
                    "whitespace",
                    true);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My Title",
    "description": "My Description",
    "examples": [ "foo" ],
    "properties": {
      "foo": { "description": "untrimmed" }
    },
    "minLength": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unfixable_allof_renumber_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My Title",
    "description": "My Description",
    "examples": [ "foo" ],
    "properties": {
      "foo-bar": { "type": "number" }
    },
    "allOf": [
      { "minLength": 1 },
      { "minLength": 1 },
      { "minLength": 1 },
      {
        "properties": {
          "foo-bar": { "type": "string" }
        }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 5);

  // The mutable rules that were applied
  EXPECT_LINT_TRACE(
      traces, 0, "", "duplicate_allof_branches",
      "Setting duplicate subschemas in `allOf` is redundant, as it produces "
      "unnecessary additional validation that is guaranteed to not affect the "
      "validation result",
      true);
  EXPECT_LINT_TRACE(
      traces, 1, "", "unnecessary_allof_wrapper",
      "Keywords inside `allOf` that do not conflict with the parent schema can "
      "be elevated",
      true);
  EXPECT_LINT_TRACE(traces, 2, "", "drop_allof_empty_schemas",
                    "Empty schemas in `allOf` are redundant and can be removed",
                    true);

  // The non-mutable rules that matched but couldn't be fixed
  EXPECT_LINT_TRACE(traces, 3, "", "simple_properties_identifiers",
                    "Set `properties` to identifier names that can be easily "
                    "mapped to programming languages (matching "
                    "[A-Za-z_][A-Za-z0-9_]*)",
                    false);
  EXPECT_LINT_TRACE(traces, 4, "/allOf/0", "simple_properties_identifiers",
                    "Set `properties` to identifier names that can be easily "
                    "mapped to programming languages (matching "
                    "[A-Za-z_][A-Za-z0-9_]*)",
                    false);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My Title",
    "description": "My Description",
    "examples": [ "foo" ],
    "properties": {
      "foo-bar": { "type": "number" }
    },
    "minLength": 1,
    "allOf": [
      {
        "properties": {
          "foo-bar": { "type": "string" }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_trim_and_trailing_period_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "  foo.   ",
    "description": "A description",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "foo",
    "description": "A description",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, description_trim_and_trailing_period_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "  bar...   ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "bar",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, title_description_trim_period_and_equal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "  foo.  ",
    "description": "  foo.  ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "foo",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, comment_trim_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "  A comment with whitespace  ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "A comment with whitespace",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, comment_trim_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "\t\nA comment\r\n",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "A comment",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, comment_trim_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "A comment without whitespace",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "A comment without whitespace",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, comment_trim_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$comment": "  Nested comment  ",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$comment": "Nested comment",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, comment_trim_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "   ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$comment": "",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_examples_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description",
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);
}

TEST(AlterSchema_lint_2020_12, top_level_examples_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_examples_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description",
    "examples": [],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);
}

TEST(AlterSchema_lint_2020_12, top_level_examples_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "examples": [],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "examples": [],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, top_level_examples_5) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "description": "A description",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12, top_level_examples_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "My schema",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_examples_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ "foo", "bar", "foo" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_examples_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ "foo", "bar", "baz" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ "foo", "bar", "baz" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_examples_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ 1, 2, 1, 3, 2 ],
    "type": "integer"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ 1, 2, 3 ],
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_examples_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "examples": [ "a", "b", "a" ],
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "examples": [ "a", "b" ],
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {
      "unused": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {
      "unused1": { "type": "string" },
      "unused2": { "type": "integer" },
      "unused3": { "type": "boolean" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "string" },
      "unused": { "type": "integer" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/helper" }
    },
    "$defs": {
      "helper": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/helper" }
    },
    "$defs": {
      "helper": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/parent",
    "$defs": {
      "parent": {
        "$ref": "#/$defs/child"
      },
      "child": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/parent",
    "$defs": {
      "parent": {
        "$ref": "#/$defs/child"
      },
      "child": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {
      "unused": {
        "$anchor": "my-anchor",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {
      "unused1": {
        "$anchor": "my-anchor",
        "type": "string"
      },
      "unused2": {
        "type": "integer"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "definitions": {
      "unused": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/used",
    "definitions": {
      "used": {
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "definitions": {
      "unused": {
        "$anchor": "my-anchor",
        "type": "string"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_13) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "$defs": {
      "unused_in_defs": { "type": "string" }
    },
    "definitions": {
      "unused_in_definitions": { "type": "integer" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_14) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/used",
    "$defs": {
      "unused_in_defs": { "type": "string" }
    },
    "definitions": {
      "used": { "type": "integer" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "integer" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_15) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "string" }
    },
    "definitions": {
      "unused_in_definitions": { "type": "integer" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_16) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/from_defs",
    "$defs": {
      "from_defs": { "$ref": "#/definitions/from_definitions" }
    },
    "definitions": {
      "from_definitions": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/from_defs",
    "$defs": {
      "from_defs": { "$ref": "#/definitions/from_definitions" }
    },
    "definitions": {
      "from_definitions": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "my-anchor", "type": "string" }
    },
    "$ref": "#my-anchor"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "my-anchor", "type": "string" }
    },
    "$ref": "#my-anchor"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_18) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "my-anchor", "type": "string" }
    },
    "$ref": "#/$defs/foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "my-anchor", "type": "string" }
    },
    "$ref": "#/$defs/foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_19) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$ref": "#/$defs/bar" },
      "bar": { "$ref": "#/$defs/baz" },
      "baz": { "type": "string" }
    },
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_20) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$ref": "#/$defs/bar" },
      "bar": { "$ref": "#/$defs/baz" },
      "baz": { "$ref": "#/$defs/foo" }
    },
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_21) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": true
    },
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_22) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_23) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$defs": {
          "unused": { "type": "string" }
        },
        "type": "object"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "object"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_24) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/properties/foo/$defs/used",
        "$defs": {
          "used": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/properties/foo/$defs/used",
        "$defs": {
          "used": { "type": "string" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_25) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/properties/foo/$defs/nested",
    "properties": {
      "foo": {
        "$defs": {
          "nested": { "type": "integer" }
        },
        "type": "object"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/properties/foo/$defs/nested",
    "properties": {
      "foo": {
        "$defs": {
          "nested": { "type": "integer" }
        },
        "type": "object"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_26) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/bar" }
    },
    "$defs": {
      "bar": {
        "allOf": [
          { "$ref": "#/$defs/baz" }
        ]
      },
      "baz": {
        "type": "object",
        "properties": {
          "qux": { "$ref": "#/$defs/extra" }
        }
      },
      "extra": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/bar" }
    },
    "$defs": {
      "bar": { "$ref": "#/$defs/baz" },
      "baz": {
        "type": "object",
        "properties": {
          "qux": { "$ref": "#/$defs/extra" }
        }
      },
      "extra": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_27) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "start": { "$ref": "#/$defs/L1" }
    },
    "$defs": {
      "L1": { "allOf": [ { "$ref": "#/$defs/L2" } ] },
      "L2": { "properties": { "a": { "$ref": "#/$defs/L3" } } },
      "L3": { "allOf": [ { "$ref": "#/$defs/L4" } ] },
      "L4": { "properties": { "b": { "$ref": "#/$defs/L5" } } },
      "L5": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "start": { "$ref": "#/$defs/L1" }
    },
    "$defs": {
      "L1": { "$ref": "#/$defs/L2" },
      "L2": { "properties": { "a": { "$ref": "#/$defs/L3" } } },
      "L3": { "$ref": "#/$defs/L4" },
      "L4": { "properties": { "b": { "$ref": "#/$defs/L5" } } },
      "L5": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, orphan_definitions_28) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/outer/$defs/inner",
    "$defs": {
      "outer": {
        "$defs": {
          "inner": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/outer/$defs/inner",
    "$defs": {
      "outer": {
        "$defs": {
          "inner": { "type": "string" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_unevaluated_properties_depends_on_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "properties": { "foo": { "type": "string" } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    unnecessary_allof_wrapper_unevaluated_properties_depends_on_pattern_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "allOf": [
      { "patternProperties": { "^f": { "type": "string" } } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "patternProperties": { "^f": { "type": "string" } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    unnecessary_allof_wrapper_unevaluated_properties_depends_on_additional_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "allOf": [
      { "additionalProperties": { "type": "string" } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "additionalProperties": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_inner_additional_properties_outer_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "additionalProperties": false }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "additionalProperties": false }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_inner_properties_and_additional_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "properties": { "foo": { "type": "string" } },
        "additionalProperties": false
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "foo": { "type": "string" } },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    unnecessary_allof_wrapper_inner_unevaluated_properties_with_all_dependencies) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "properties": { "foo": { "type": "string" } },
        "patternProperties": { "^b": { "type": "number" } },
        "additionalProperties": { "type": "boolean" },
        "unevaluatedProperties": false
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "properties": { "foo": { "type": "string" } },
        "patternProperties": { "^b": { "type": "number" } },
        "additionalProperties": { "type": "boolean" },
        "unevaluatedProperties": false
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_unevaluated_items_depends_on_prefix_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "allOf": [
      { "prefixItems": [ { "type": "string" } ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "prefixItems": [ { "type": "string" } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_unevaluated_items_depends_on_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "allOf": [
      { "items": { "type": "string" } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "items": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_unevaluated_items_depends_on_contains) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "allOf": [
      { "contains": { "type": "string" } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": false,
    "contains": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_inner_items_outer_prefix_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" } ],
    "allOf": [
      { "items": false }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" } ],
    "allOf": [
      { "items": false }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_inner_prefix_items_and_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "prefixItems": [ { "type": "string" }, { "type": "number" } ],
        "items": false
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "prefixItems": [ { "type": "string" }, { "type": "number" } ],
    "items": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_inner_unevaluated_items_with_all_dependencies) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "prefixItems": [ { "type": "string" } ],
        "items": { "type": "number" },
        "contains": { "minimum": 0 },
        "unevaluatedItems": false
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "prefixItems": [ { "type": "string" } ],
        "items": { "type": "number" },
        "contains": { "minimum": 0 },
        "unevaluatedItems": false
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_outer_if_inner_then_only) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "allOf": [
      { "then": { "minLength": 1 } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_outer_if_inner_else_only) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "allOf": [
      { "else": { "minimum": 0 } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_outer_if_inner_then_and_else) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "allOf": [
      { "then": { "minLength": 1 }, "else": { "minimum": 0 } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unnecessary_allof_wrapper_inner_if_only) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "if": { "type": "string" } }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_inner_if_then_else_complete) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "if": { "type": "string" },
        "then": { "minLength": 1 },
        "else": { "minimum": 0 }
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "minLength": 1 },
    "else": { "minimum": 0 }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_multiple_entries_with_dependencies) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } },
      { "type": "object" },
      { "minProperties": 1 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": false,
    "type": "object",
    "minProperties": 1,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_complex_mixed_dependencies) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "unevaluatedItems": false,
    "allOf": [
      { "properties": { "foo": { "type": "string" } } },
      { "prefixItems": [ { "type": "number" } ] },
      { "title": "Test schema" },
      { "description": "A test" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": false,
    "unevaluatedItems": false,
    "description": "A test",
    "title": "Test schema",
    "prefixItems": [ { "type": "number" } ],
    "properties": { "foo": { "type": "string" } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, circular_ref_through_defs_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$ref": "#/$defs/b" },
      "b": { "$ref": "#/$defs/a" }
    },
    "$ref": "#/$defs/a"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$ref": "#/$defs/b" },
      "b": { "$ref": "#/$defs/a" }
    },
    "$ref": "#/$defs/a"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, simple_properties_identifiers_valid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": { "type": "string" },
      "bar_baz": { "type": "number" },
      "_private": { "type": "boolean" },
      "CamelCase": { "type": "object" },
      "name123": { "type": "array" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12, simple_properties_identifiers_hyphen) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo-bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "simple_properties_identifiers",
      "Set `properties` to identifier names that can be easily mapped "
      "to programming languages (matching [A-Za-z_][A-Za-z0-9_]*)",
      false);
}

TEST(AlterSchema_lint_2020_12,
     simple_properties_identifiers_starts_with_digit) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "123abc": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "simple_properties_identifiers",
      "Set `properties` to identifier names that can be easily mapped "
      "to programming languages (matching [A-Za-z_][A-Za-z0-9_]*)",
      false);
}

TEST(AlterSchema_lint_2020_12, simple_properties_identifiers_special_char) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo@bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "simple_properties_identifiers",
      "Set `properties` to identifier names that can be easily mapped "
      "to programming languages (matching [A-Za-z_][A-Za-z0-9_]*)",
      false);
}

TEST(AlterSchema_lint_2020_12, simple_properties_identifiers_space) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "", "simple_properties_identifiers",
      "Set `properties` to identifier names that can be easily mapped "
      "to programming languages (matching [A-Za-z_][A-Za-z0-9_]*)",
      false);
}

TEST(AlterSchema_lint_2020_12, simple_properties_identifiers_nested) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "valid": {
        "type": "object",
        "properties": {
          "invalid-name": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "/properties/valid", "simple_properties_identifiers",
      "Set `properties` to identifier names that can be easily mapped "
      "to programming languages (matching [A-Za-z_][A-Za-z0-9_]*)",
      false);
}

TEST(AlterSchema_lint_2020_12, simple_properties_identifiers_skip_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/my-metaschema",
    "title": "My meta-schema",
    "description": "A custom meta-schema",
    "examples": [ {} ],
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    },
    "properties": {
      "foo-bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12,
     simple_properties_identifiers_skip_metaschema_nested) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/my-metaschema",
    "title": "My meta-schema",
    "description": "A custom meta-schema",
    "examples": [ {} ],
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true,
      "https://json-schema.org/draft/2020-12/vocab/applicator": true
    },
    "properties": {
      "valid": {
        "properties": {
          "also-invalid": { "type": "number" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12,
     simple_properties_identifiers_skip_bundled_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "title": "Main schema",
    "description": "A schema that bundles a meta-schema",
    "examples": [ {} ],
    "$ref": "https://example.com/my-metaschema",
    "$defs": {
      "metaschema": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/my-metaschema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true
        },
        "properties": {
          "foo-bar": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12, duplicate_allof_branches_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string" },
      { "type": "string" }
    ],
    "properties": {
      "test": {
        "$ref": "#/allOf/1"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string" }
    ],
    "properties": {
      "test": {
        "$ref": "#/allOf/0"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, duplicate_anyof_branches_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "string" }
    ],
    "properties": {
      "test": {
        "$ref": "#/anyOf/1"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" }
    ],
    "properties": {
      "test": {
        "$ref": "#/anyOf/0"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    duplicate_allof_branches_with_reference_should_deduplicate_and_update_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "#/$defs/a" },
      { "$ref": "#/$defs/b" },
      { "$ref": "#/$defs/a" }
    ],
    "$defs": {
      "a": { "minLength": 1 },
      "b": { "minLength": 5 }
    },
    "properties": {
      "test": {
        "$ref": "#/allOf/2"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "#/$defs/a" },
      { "$ref": "#/$defs/b" }
    ],
    "$defs": {
      "a": { "minLength": 1 },
      "b": { "minLength": 5 }
    },
    "properties": {
      "test": {
        "$ref": "#/allOf/0"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_modern_items_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "items": {
          "type": "string"
        }
      }
    ],
    "properties": {
      "foo": {
        "$ref": "#/allOf/0/items"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": {
      "type": "string"
    },
    "properties": {
      "foo": {
        "$ref": "#/items"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unnecessary_allof_wrapper_modern_additional_properties_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "additionalProperties": {
          "type": "number"
        }
      }
    ],
    "items": {
      "$ref": "#/allOf/0/additionalProperties"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "additionalProperties": {
      "type": "number"
    },
    "items": {
      "$ref": "#/additionalProperties"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_empty_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "then": {},
    "additionalProperties": {
      "$ref": "#/then"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "then": true,
    "additionalProperties": {
      "$ref": "#/then"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_empty_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "else": {},
    "properties": {
      "foo": {
        "$ref": "#/else"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": true,
    "else": true,
    "properties": {
      "foo": {
        "$ref": "#/else"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, if_without_then_else_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "type": "string"
    },
    "additionalProperties": {
      "$ref": "#/if"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "type": "string"
    },
    "additionalProperties": {
      "$ref": "#/if"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, items_schema_default_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": true,
    "additionalProperties": {
      "$ref": "#/items"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": true,
    "additionalProperties": {
      "$ref": "#/items"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_properties_default_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": true,
    "items": {
      "$ref": "#/unevaluatedProperties"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedProperties": true,
    "items": {
      "$ref": "#/unevaluatedProperties"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, unevaluated_items_default_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": true,
    "properties": {
      "foo": {
        "$ref": "#/unevaluatedItems"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "unevaluatedItems": true,
    "properties": {
      "foo": {
        "$ref": "#/unevaluatedItems"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, property_names_default_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "propertyNames": {},
    "items": {
      "$ref": "#/propertyNames"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "propertyNames": true,
    "items": {
      "$ref": "#/propertyNames"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, content_schema_default_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentSchema": true,
    "items": {
      "$ref": "#/contentSchema"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "contentSchema": true,
    "items": {
      "$ref": "#/contentSchema"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_without_if_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "then": {
      "type": "string"
    },
    "properties": {
      "foo": {
        "$ref": "#/then"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "then": {
      "type": "string"
    },
    "properties": {
      "foo": {
        "$ref": "#/then"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_without_if_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "else": {
      "type": "string"
    },
    "properties": {
      "foo": {
        "$ref": "#/else"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "else": {
      "type": "string"
    },
    "properties": {
      "foo": {
        "$ref": "#/else"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": false,
    "properties": {
      "foo": {
        "$ref": "#/not"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": false,
    "properties": {
      "foo": {
        "$ref": "#/not"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    non_applicable_type_specific_keywords_additional_properties_for_array_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "additionalProperties": {
      "type": "string"
    },
    "items": {
      "$ref": "#/additionalProperties"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "additionalProperties": {
      "type": "string"
    },
    "items": {
      "$ref": "#/additionalProperties"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    non_applicable_type_specific_keywords_properties_for_array_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "properties": {
      "foo": {
        "type": "string"
      }
    },
    "items": {
      "$ref": "#/properties/foo"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "properties": {
      "foo": {
        "type": "string"
      }
    },
    "items": {
      "$ref": "#/properties/foo"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     non_applicable_type_specific_keywords_items_for_object_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "items": {
      "type": "string"
    },
    "additionalProperties": {
      "$ref": "#/items"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "items": {
      "type": "string"
    },
    "additionalProperties": {
      "$ref": "#/items"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unevaluated_properties_default_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "unevaluatedProperties": true,
        "properties": {
          "foo": { "$ref": "#/unevaluatedProperties" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "unevaluatedProperties": true,
        "properties": {
          "foo": { "$ref": "#/unevaluatedProperties" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     unevaluated_items_default_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "unevaluatedItems": true,
        "properties": {
          "foo": { "$ref": "#/unevaluatedItems" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "unevaluatedItems": true,
        "properties": {
          "foo": { "$ref": "#/unevaluatedItems" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     content_schema_default_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "contentSchema": true,
        "properties": {
          "foo": { "$ref": "#/contentSchema" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "contentSchema": true,
        "properties": {
          "foo": { "$ref": "#/contentSchema" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     items_schema_default_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "#/$defs/nested" },
      { "$ref": "#/$defs/ref_to_items" }
    ],
    "$defs": {
      "ref_to_items": { "$ref": "nested#/items" },
      "nested": {
        "$id": "nested",
        "type": "array",
        "items": true
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "#/$defs/nested" },
      { "$ref": "#/$defs/ref_to_items" }
    ],
    "$defs": {
      "ref_to_items": { "$ref": "nested#/items" },
      "nested": {
        "$id": "nested",
        "type": "array",
        "items": true
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     property_names_default_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "propertyNames": {},
        "properties": {
          "foo": { "$ref": "#/propertyNames" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "propertyNames": true,
        "properties": {
          "foo": { "$ref": "#/propertyNames" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, not_false_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "not": false,
        "properties": {
          "foo": { "$ref": "#/not" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "not": false,
        "properties": {
          "foo": { "$ref": "#/not" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_without_if_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "then": { "type": "string" },
        "properties": {
          "foo": { "$ref": "#/then" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "then": { "type": "string" },
        "properties": {
          "foo": { "$ref": "#/then" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_without_if_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "else": { "type": "string" },
        "properties": {
          "foo": { "$ref": "#/else" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "else": { "type": "string" },
        "properties": {
          "foo": { "$ref": "#/else" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     if_without_then_else_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "if": { "type": "string" },
        "properties": {
          "foo": { "$ref": "#/if" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "if": { "type": "string" },
        "properties": {
          "foo": { "$ref": "#/if" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, then_empty_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "if": { "type": "string" },
        "then": {},
        "properties": {
          "foo": { "$ref": "#/then" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "if": { "type": "string" },
        "then": true,
        "properties": {
          "foo": { "$ref": "#/then" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, else_empty_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "if": { "type": "string" },
        "else": {},
        "properties": {
          "foo": { "$ref": "#/else" }
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "if": { "type": "string" },
        "else": true,
        "properties": {
          "foo": { "$ref": "#/else" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(
    AlterSchema_lint_2020_12,
    non_applicable_type_specific_keywords_items_nested_resource_with_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "type": "object",
        "items": { "type": "string" },
        "additionalProperties": { "$ref": "#/items" }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/nested",
    "$defs": {
      "nested": {
        "$id": "nested",
        "type": "object",
        "items": { "type": "string" },
        "additionalProperties": { "$ref": "#/items" }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_remove_false_schemas_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      false,
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_remove_false_schemas_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      false,
      { "type": "string" },
      false,
      { "type": "number" },
      false
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_remove_false_schemas_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_remove_false_schemas_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false, false, false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_remove_false_schemas_with_ref_through_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      false,
      { "type": "string" }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/1" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      false,
      { "type": "string" }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/1" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_remove_false_schemas_with_ref_through_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      false,
      {
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        }
      }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/1/properties/name" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      false,
      {
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        }
      }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/1/properties/name" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_true_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ true, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_true_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "type": "string" }, true ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_true_simplify_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ { "type": "string" }, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_true_simplify_with_ref_through) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      true,
      {
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        }
      }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/1/properties/name" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      true,
      {
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        }
      }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/1/properties/name" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, anyof_false_simplify_with_ref_through) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false ],
    "properties": {
      "foo": { "$ref": "#/anyOf/0" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [ false ],
    "properties": {
      "foo": { "$ref": "#/anyOf/0" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_false_simplify_with_ref_through) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [ false ],
    "properties": {
      "foo": { "$ref": "#/oneOf/0" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [ false ],
    "properties": {
      "foo": { "$ref": "#/oneOf/0" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "const": "hello" },
      { "const": 42 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "const": "hello" },
      { "const": 42 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "enum": [ "a", "b" ] },
      { "enum": [ 1, 2, 3 ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ "a", "b" ] },
      { "enum": [ 1, 2, 3 ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 1 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "minLength": 1 }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_ref_only) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "type": "string" }
    },
    "oneOf": [
      { "type": "integer" },
      { "$ref": "#/$defs/foo" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "type": "string" }
    },
    "oneOf": [
      { "type": "integer" },
      { "$ref": "#/$defs/foo" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_with_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string", "minLength": 1 },
      { "type": "integer", "minimum": 0 }
    ],
    "properties": {
      "foo": { "$ref": "#/oneOf/0" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string", "minLength": 1 },
      { "type": "integer", "minimum": 0 }
    ],
    "properties": {
      "foo": { "$ref": "#/anyOf/0" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_mixed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "const": 42 },
      { "enum": [ true, false ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "const": 42 },
      { "enum": [ true, false ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_enum_overlap) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "enum": [ "a", 1 ] },
      { "enum": [ "b", 2 ] }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "enum": [ "a", 1 ] },
      { "enum": [ "b", 2 ] }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, oneof_to_anyof_disjoint_types_number_integer) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "integer" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, empty_object_as_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {}
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, empty_object_as_true_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, empty_object_as_true_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [ {}, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, object_oneof_required_not_required_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test",
    "examples": [ {} ],
    "properties": {
      "term1": true,
      "term2": true
    },
    "oneOf": [
      { "required": [ "term1" ], "not": { "required": [ "term2" ] } },
      { "required": [ "term2" ], "not": { "required": [ "term1" ] } }
    ]
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, object_oneof_required_not_required_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test",
    "examples": [ [] ],
    "properties": {
      "term1": true,
      "term2": true
    },
    "items": {
      "not": { "required": [ "term2" ] }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "/items/not", "required_properties_in_properties",
      "Every property listed in the `required` keyword must be explicitly "
      "defined using the `properties` keyword",
      true);
}

TEST(AlterSchema_lint_2020_12, object_oneof_required_not_required_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test",
    "examples": [ {} ],
    "properties": {
      "foo": true,
      "bar": true
    },
    "if": { "type": "object" },
    "then": {
      "oneOf": [
        { "not": { "required": [ "foo" ] } },
        { "not": { "required": [ "bar" ] } }
      ]
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, object_oneof_required_not_required_4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test",
    "examples": [ {} ],
    "properties": {
      "foo": true
    },
    "if": { "required": [ "foo" ] },
    "then": { "not": { "required": [ "foo" ] } }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12, object_oneof_required_not_required_5) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test",
    "examples": [ [] ],
    "properties": {
      "foo": true
    },
    "oneOf": [
      {
        "items": {
          "not": { "required": [ "foo" ] }
        }
      }
    ]
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(
      traces, 0, "/oneOf/0/items/not", "required_properties_in_properties",
      "Every property listed in the `required` keyword must be explicitly "
      "defined using the `properties` keyword",
      true);
}

TEST(AlterSchema_lint_2020_12, object_oneof_required_not_required_6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "A test",
    "examples": [ {} ],
    "properties": {
      "foo": true,
      "bar": true
    },
    "allOf": [
      {
        "oneOf": [
          { "not": { "required": [ "foo" ] } },
          { "not": { "required": [ "bar" ] } }
        ]
      }
    ]
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
  EXPECT_LINT_TRACE(
      traces, 1, "", "unnecessary_allof_wrapper",
      "Keywords inside `allOf` that do not conflict with the parent schema "
      "can be elevated",
      true);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": [1, 2]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": [1, 2]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "enum": []
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "not": true
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "enum": []
      },
      "bar": {
        "enum": []
      },
      "baz": {
        "enum": [1, 2]
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "not": true
      },
      "bar": {
        "not": true
      },
      "baz": {
        "enum": [1, 2]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [[]],
    "prefixItems": [
      {
        "enum": []
      },
      {
        "type": "string"
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [[]],
    "prefixItems": [
      {
        "not": true
      },
      {
        "type": "string"
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [[]],
    "properties": {
      "arr": {
        "type": "array",
        "items": {
          "x-note": "placeholder",
          "enum": []
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [[]],
    "properties": {
      "arr": {
        "type": "array",
        "items": {
          "x-note": "placeholder",
          "not": true
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": {}
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "not": {
          "enum": []
        }
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "not": {
          "not": true
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "enum": []
      }
    },
    "$ref": "#/$defs/A"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "enum": []
      }
    },
    "$ref": "#/$defs/A"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "enum": [],
        "$defs": {
          "inner": { "type": "string" }
        }
      }
    },
    "$ref": "#/$defs/A/$defs/inner"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "enum": [],
        "$defs": {
          "inner": { "type": "string" }
        }
      }
    },
    "$ref": "#/$defs/A/$defs/inner"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "$id": "https://example.com/schemas/A",
        "enum": []
      }
    },
    "$ref": "https://example.com/schemas/A"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "$id": "https://example.com/schemas/A",
        "enum": []
      }
    },
    "$ref": "https://example.com/schemas/A"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_13) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "x-note": "placeholder",
        "enum": []
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [{}],
    "properties": {
      "foo": {
        "x-note": "placeholder",
        "not": true
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_14) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" },
    "enum": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" },
    "enum": []
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, forbid_empty_enum_15) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "enum": [],
        "additionalProperties": { "type": "string" }
      }
    },
    "$ref": "#/$defs/A/additionalProperties"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "A": {
        "enum": [],
        "additionalProperties": { "type": "string" }
      }
    },
    "$ref": "#/$defs/A/additionalProperties"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://unknown.example.com/nonexistent"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://example.com/external"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "type": "object"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$defs": {
      "foo": { "type": "string" }
    },
    "$ref": "#/$defs/foo"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_5) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://example.com/external-with-defs#/$defs/foo"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://example.com/external-with-defs#/$defs/nonexistent"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$defs": {
      "foo": {
        "$id": "https://example.com/embedded",
        "type": "string"
      }
    },
    "$ref": "https://example.com/embedded"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_8) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$defs": {
      "foo": {
        "$id": "https://example.com/embedded",
        "type": "string"
      }
    },
    "$ref": "https://example.com/embedded#/nonexistent"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "unknown_local_ref",
                    "Local references that point to unknown locations are "
                    "invalid and will result in evaluation failures",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "", "orphan_definitions",
                    "Schema definitions in `$defs` or `definitions` that are "
                    "never internally referenced can be removed",
                    true);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_9) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "properties": {
      "foo": {
        "$ref": "https://unknown.example.com/nonexistent"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://unknown.example.com/nonexistent"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "$ref": "https://unknown.example.com/nonexistent"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, invalid_external_ref_11) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test",
    "description": "Test description",
    "examples": [{}],
    "properties": {
      "bar": {
        "$ref": "https://unknown.example.com/first"
      },
      "foo": {
        "$ref": "https://unknown.example.com/second"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "/properties/bar", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
  EXPECT_LINT_TRACE(traces, 1, "/properties/foo", "invalid_external_ref",
                    "External references must point to schemas that can be "
                    "resolved",
                    false);
}

TEST(AlterSchema_lint_2020_12, modern_official_dialect_with_http_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, modern_official_dialect_with_http_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft/2020-12/hyper-schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/hyper-schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, modern_official_dialect_with_http_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft/2020-12/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     modern_official_dialect_with_http_already_https) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12,
     modern_official_dialect_with_http_non_dialect_uri) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "http://json-schema.org/draft/2020-12/meta/applicator"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "http://json-schema.org/draft/2020-12/meta/applicator"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", "bar", "baz" ]
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", "bar", "baz" ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [],
    "properties": {
      "foo": {
        "type": "string",
        "examples": []
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [],
    "properties": {
      "foo": {
        "type": "string",
        "examples": []
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_13) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "@foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "@foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_15) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/definitions/helper", "examples": [ 1 ] }
    },
    "definitions": {
      "helper": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/helper" }
    },
    "$defs": {
      "helper": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": "bar" },
    "properties": {
      "foo": {
        "type": "string",
        "default": "baz"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": "bar" },
    "properties": {
      "foo": {
        "type": "string",
        "default": "baz"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "@foo": { "type": "string", "default": "bar" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "@foo": { "type": "string", "default": "bar" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_14) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/definitions/helper", "default": 1 }
    },
    "definitions": {
      "helper": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/helper" }
    },
    "$defs": {
      "helper": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_16) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "meta",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {},
      "bar": {},
      "baz": {
        "$ref": "#/$defs/bar",
        "default": 0
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "meta",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "examples": [ 1 ] },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "examples": [ 1 ] },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" }
  })JSON");

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::blaze::SchemaTransformRule::Result, bool>>
      traces;
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,
      [&traces](const auto &pointer, const auto &name, const auto &message,
                const auto &outcome, const auto &fixable) {
        traces.emplace_back(pointer, name, message, outcome, fixable);
      },
      "", "https://example.com/root");

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_12) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" },
    "$ref": "ref.json"
  })JSON");

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::blaze::SchemaTransformRule::Result, bool>>
      traces;
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,
      [&traces](const auto &pointer, const auto &name, const auto &message,
                const auto &outcome, const auto &fixable) {
        traces.emplace_back(pointer, name, message, outcome, fixable);
      },
      "", "https://example.com/root");

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" },
    "$ref": "ref.json"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_examples_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ "10" ], "$ref": "ref.json" }
  })JSON");

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::blaze::SchemaTransformRule::Result, bool>>
      traces;
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,
      [&traces](const auto &pointer, const auto &name, const auto &message,
                const auto &outcome, const auto &fixable) {
        traces.emplace_back(pointer, name, message, outcome, fixable);
      },
      "", "https://example.com/root");

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "ref.json" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "default": 1 },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "default": 1 },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "default": 10, "$ref": "ref.json" }
  })JSON");

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::blaze::SchemaTransformRule::Result, bool>>
      traces;
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,
      [&traces](const auto &pointer, const auto &name, const auto &message,
                const auto &outcome, const auto &fixable) {
        traces.emplace_back(pointer, name, message, outcome, fixable);
      },
      "", "https://example.com/root");

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "default": 10, "$ref": "ref.json" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": 10,
    "$ref": "ref.json"
  })JSON");

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::blaze::SchemaTransformRule::Result, bool>>
      traces;
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,
      [&traces](const auto &pointer, const auto &name, const auto &message,
                const auto &outcome, const auto &fixable) {
        traces.emplace_back(pointer, name, message, outcome, fixable);
      },
      "", "https://example.com/root");

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": 10,
    "$ref": "ref.json"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_18) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "default": "10", "$ref": "ref.json" }
  })JSON");

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::blaze::SchemaTransformRule::Result, bool>>
      traces;
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker, alterschema_test_resolver,
      [&traces](const auto &pointer, const auto &name, const auto &message,
                const auto &outcome, const auto &fixable) {
        traces.emplace_back(pointer, name, message, outcome, fixable);
      },
      "", "https://example.com/root");

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "ref.json" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2020_12, valid_default_error_message_without_id_nested) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "default": 1,
        "type": "string"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_default_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_default";
      });
  ASSERT_NE(valid_default_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_default_entry),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<2>(*valid_default_entry),
            "Only set a `default` value that validates against the schema");
  EXPECT_TRUE(std::get<3>(*valid_default_entry).description.has_value());
  EXPECT_EQ(
      std::get<3>(*valid_default_entry).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_default_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_default_entry).locations.at(0)),
            "/default");
  EXPECT_TRUE(std::get<4>(*valid_default_entry));
}

TEST(AlterSchema_lint_2020_12, valid_default_error_message_without_id_flat) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": 1,
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_default_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_default";
      });
  ASSERT_NE(valid_default_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_default_entry), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<2>(*valid_default_entry),
            "Only set a `default` value that validates against the schema");
  EXPECT_TRUE(std::get<3>(*valid_default_entry).description.has_value());
  EXPECT_EQ(
      std::get<3>(*valid_default_entry).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_default_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_default_entry).locations.at(0)),
            "/default");
  EXPECT_TRUE(std::get<4>(*valid_default_entry));
}

TEST(AlterSchema_lint_2020_12, valid_default_error_message_with_id_nested) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": {
      "foo": {
        "default": 1,
        "type": "string"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_default_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_default";
      });
  ASSERT_NE(valid_default_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_default_entry),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<2>(*valid_default_entry),
            "Only set a `default` value that validates against the schema");
  EXPECT_TRUE(std::get<3>(*valid_default_entry).description.has_value());
  EXPECT_EQ(
      std::get<3>(*valid_default_entry).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_default_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_default_entry).locations.at(0)),
            "/default");
  EXPECT_TRUE(std::get<4>(*valid_default_entry));
}

TEST(AlterSchema_lint_2020_12, valid_default_error_message_with_id_flat) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "default": 1,
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_default_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_default";
      });
  ASSERT_NE(valid_default_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_default_entry), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<2>(*valid_default_entry),
            "Only set a `default` value that validates against the schema");
  EXPECT_TRUE(std::get<3>(*valid_default_entry).description.has_value());
  EXPECT_EQ(
      std::get<3>(*valid_default_entry).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_default_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_default_entry).locations.at(0)),
            "/default");
  EXPECT_TRUE(std::get<4>(*valid_default_entry));
}

TEST(AlterSchema_lint_2020_12,
     valid_default_error_message_with_id_nested_ref_defs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$defs": {
      "helper": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/helper",
        "default": 1
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_default_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_default";
      });
  ASSERT_NE(valid_default_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_default_entry),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<2>(*valid_default_entry),
            "Only set a `default` value that validates against the schema");
  EXPECT_TRUE(std::get<3>(*valid_default_entry).description.has_value());
  EXPECT_EQ(
      std::get<3>(*valid_default_entry).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/$ref/type"
The integer value was expected to validate against the referenced schema
  at instance location ""
  at evaluate path "/$ref"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_default_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_default_entry).locations.at(0)),
            "/default");
  EXPECT_TRUE(std::get<4>(*valid_default_entry));
}

TEST(AlterSchema_lint_2020_12, valid_examples_error_message_without_id_nested) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "examples": [ 1 ],
        "type": "string"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_examples_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_examples";
      });
  ASSERT_NE(valid_examples_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_examples_entry),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<2>(*valid_examples_entry),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(*valid_examples_entry).description.has_value());
  EXPECT_EQ(std::get<3>(*valid_examples_entry).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_examples_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_examples_entry).locations.at(0)),
            "/examples/0");
  EXPECT_TRUE(std::get<4>(*valid_examples_entry));
}

TEST(AlterSchema_lint_2020_12, valid_examples_error_message_without_id_flat) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ 1 ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_examples_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_examples";
      });
  ASSERT_NE(valid_examples_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_examples_entry), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<2>(*valid_examples_entry),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(*valid_examples_entry).description.has_value());
  EXPECT_EQ(std::get<3>(*valid_examples_entry).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_examples_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_examples_entry).locations.at(0)),
            "/examples/0");
  EXPECT_TRUE(std::get<4>(*valid_examples_entry));
}

TEST(AlterSchema_lint_2020_12, valid_examples_error_message_with_id_nested) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": {
      "foo": {
        "examples": [ 1 ],
        "type": "string"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_examples_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_examples";
      });
  ASSERT_NE(valid_examples_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_examples_entry),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<2>(*valid_examples_entry),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(*valid_examples_entry).description.has_value());
  EXPECT_EQ(std::get<3>(*valid_examples_entry).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_examples_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_examples_entry).locations.at(0)),
            "/examples/0");
  EXPECT_TRUE(std::get<4>(*valid_examples_entry));
}

TEST(AlterSchema_lint_2020_12, valid_examples_error_message_with_id_flat) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "examples": [ 1 ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_examples_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_examples";
      });
  ASSERT_NE(valid_examples_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_examples_entry), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<2>(*valid_examples_entry),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(*valid_examples_entry).description.has_value());
  EXPECT_EQ(std::get<3>(*valid_examples_entry).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_examples_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_examples_entry).locations.at(0)),
            "/examples/0");
  EXPECT_TRUE(std::get<4>(*valid_examples_entry));
}

TEST(AlterSchema_lint_2020_12,
     valid_examples_error_message_with_id_nested_ref_defs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$defs": {
      "helper": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/helper",
        "examples": [ 1 ]
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const auto valid_examples_entry =
      std::find_if(traces.cbegin(), traces.cend(), [](const auto &entry) {
        return std::get<1>(entry) == "valid_examples";
      });
  ASSERT_NE(valid_examples_entry, traces.cend());

  EXPECT_EQ(std::get<0>(*valid_examples_entry),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<2>(*valid_examples_entry),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(*valid_examples_entry).description.has_value());
  EXPECT_EQ(std::get<3>(*valid_examples_entry).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/$ref/type"
  The integer value was expected to validate against the referenced schema
    at instance location ""
    at evaluate path "/$ref"
)TXT");

  EXPECT_EQ(std::get<3>(*valid_examples_entry).locations.size(), 1);
  EXPECT_EQ(sourcemeta::core::to_string(
                std::get<3>(*valid_examples_entry).locations.at(0)),
            "/examples/0");
  EXPECT_TRUE(std::get<4>(*valid_examples_entry));
}
