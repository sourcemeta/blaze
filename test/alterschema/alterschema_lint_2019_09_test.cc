#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_lint_2019_09, local_ref_to_unknown_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, local_ref_to_unknown_location_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, local_ref_to_unknown_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     local_ref_to_unknown_location_with_nested_resource_relative) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "foo#/$defs/foo",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     local_ref_to_unknown_location_with_nested_resource_relative_valid) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     local_ref_to_unknown_location_with_nested_resource_absolute) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.example.com/foo#/$defs/foo",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalProperties": { "$id": "foo" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     local_ref_to_unknown_location_with_nested_resource_absolute_valid) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.example.com/foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.example.com/foo#/$defs/foo",
    "additionalProperties": { "$id": "foo", "$defs": { "foo": true } }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, nested_ref_to_unknown_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, nested_ref_to_existing_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, deeply_nested_ref_to_unknown_location) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, nested_ref_to_unknown_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      {
        "$ref": "#unknownAnchor"
      }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, nested_ref_to_existing_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, mixed_nested_refs_valid_and_invalid) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, external_ref_with_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "$ref": "https://example.com/schema#/$defs/bar"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "$ref": "https://example.com/schema#/$defs/bar"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, external_ref_with_unknown_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://json-schema.org/draft/2019-09/schema#/$defs/nonNegativeInteger"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://json-schema.org/draft/2019-09/schema#/$defs/nonNegativeInteger"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, nested_external_ref_with_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com/base-schema#/$defs/common",
    "properties": {
      "value": {
        "$ref": "http://another-example.com/types#/definitions/string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     external_relative_ref_with_fragment_not_removed) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com/my-schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "data": {
        "$ref": "common-types.json#/$defs/uuid"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, enum_to_const_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, const_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, const_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": [ "string", "null" ],
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, const_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, const_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": [ "boolean", "null" ],
    "const": "foo"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": [ "boolean", "null" ],
    "const": "foo"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, enum_with_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, enum_with_type_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "enum": [ "foo", 1 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, enum_with_type_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, enum_with_type_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": [ "string", "null" ],
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "foo", "bar", "null" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "foo", "bar" ],
    "minimum": 0
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, 2, 3 ],
    "minLength": 0,
    "maxLength": 5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ { "a": 1 }, { "b": 2 } ],
    "minLength": 3,
    "minimum": 0
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ { "a": 1 }, { "b": 2 } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0,
    "minItems": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, "foo" ],
    "minLength": 2,
    "minimum": 0
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ { "name": "alice" }, { "age": 25 } ],
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "number" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3,
    "minItems": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "small", "medium", "large" ],
    "title": "Size Options",
    "minLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, non_applicable_enum_validation_keywords_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/schema",
    "$anchor": "color-enum",
    "title": "My Enum Schema",
    "description": "A schema with enum and annotations",
    "$comment": "This schema uses enum with various annotation keywords",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, single_type_array_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": [ "string" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, content_media_type_without_encoding_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentMediaType": "application/json"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, content_schema_without_media_type_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentSchema": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, max_contains_without_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "maxContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, max_contains_without_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": true,
    "maxContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": true,
    "maxContains": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, min_contains_without_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, min_contains_without_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": true,
    "minContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": true,
    "minContains": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, then_without_if_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "then": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, then_without_if_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true,
    "then": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true,
    "then": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, else_without_if_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "else": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, else_without_if_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true,
    "else": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true,
    "else": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, if_without_then_else_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "if": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unevaluated_properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unevaluated_properties_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unevaluated_properties_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedProperties": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unevaluated_items_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unevaluated_items_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unevaluated_items_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, content_schema_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, content_schema_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, content_schema_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, items_schema_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, items_schema_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, items_schema_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, items_array_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, duplicate_enum_values_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, {}, 2, 1, 1, 3, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ 1, {}, 2, 3 ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, duplicate_required_values_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar", "baz", "foo" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_maximum_number_and_maximum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMaximum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMaximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_maximum_number_and_maximum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMaximum": 3,
    "maximum": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "maximum": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_maximum_number_and_maximum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMaximum": 3,
    "maximum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "maximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_minimum_number_and_minimum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3,
    "minimum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_minimum_number_and_minimum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3,
    "minimum": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_minimum_number_and_minimum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3,
    "minimum": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, duplicate_allof_branches_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [ { "type": "string" }, { "type": "integer" }, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, duplicate_anyof_branches_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ { "type": "string" }, { "type": "integer" }, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ { "type": "string" }, { "type": "integer" } ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, anyof_true_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ true, { "type": "string" } ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, anyof_true_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ { "type": "string" }, {} ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, anyof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, anyof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, oneof_false_simplify_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "oneOf": [ false ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, oneof_false_simplify_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "oneOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "oneOf": [ false ],
    "not": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, oneof_to_anyof_disjoint_types_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, oneof_to_anyof_disjoint_types_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "string" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, maximum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "maximum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "maximum": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, minimum_real_for_integer_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "minimum": 3.5
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "minimum": 4
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, dependent_required_tautology_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo" ],
    "dependentRequired": {
      "foo": [ "bar" ],
      "xxx": [ "yyy" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, dependent_required_tautology_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo" ],
    "dependentRequired": {
      "foo": [ "bar" ],
      "bar": [ "baz" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar", "baz" ],
    "properties": {
      "foo": true,
      "bar": true,
      "baz": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, pattern_properties_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "patternProperties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unsatisfiable_min_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unsatisfiable_min_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, unsatisfiable_min_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar", "bar", "baz" ],
    "minProperties": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "bar", "baz", "foo" ],
    "properties": {
      "bar": true,
      "baz": true,
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_array_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "array",
    "minItems": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_boolean_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_null_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_numeric_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "number",
    "multipleOf": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_numeric_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "integer",
    "multipleOf": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_object_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "object",
    "unevaluatedProperties": false,
    "maxProperties": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, drop_non_string_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "type": "string",
    "contentEncoding": "base64",
    "format": "uri"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, type_boolean_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, type_null_as_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "null"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "null"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, const_as_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_maximum_integer_to_maximum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMaximum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, exclusive_minimum_integer_to_minimum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "exclusiveMinimum": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unsatisfiable_max_contains_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unsatisfiable_max_contains_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 1
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unsatisfiable_max_contains_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3,
    "maxContains": 4
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_5) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_8) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, incoherent_min_max_contains_9) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, equal_numeric_bounds_to_const_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, equal_numeric_bounds_to_const_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, equal_numeric_bounds_to_const_decimal_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "minimum": 1.0e400,
    "maximum": 1.0e400
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": 1.0e+400
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com/foo",
    "allOf": [
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com/foo",
    "allOf": [
      { "$ref": "https://example.com/bar" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "type": "number" },
      { "$ref": "https://example.com" },
      { "type": "integer" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com",
    "type": "integer",
    "allOf": [
      { "type": "number" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, multiple_of_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, multiple_of_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "multipleOf": 1.0,
    "contains": { "type": "string" }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "contains": { "type": "string" }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, multiple_of_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "multipleOf": 1.2,
    "type": "number"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "multipleOf": 1.2,
    "type": "number"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, multiple_of_default_no_change_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 2
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "integer",
    "multipleOf": 2
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_properties_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_ref_wrapper_modern_elevation_single_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_ref_wrapper_modern_no_elevation_all_branches_have_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" },
      { "$ref": "https://example.com/baz" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com/foo" },
      { "$ref": "https://example.com/bar" },
      { "$ref": "https://example.com/baz" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_ref_wrapper_modern_no_elevation_ref_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      {
        "$ref": "https://example.com",
        "$id": "https://other.com"
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, additional_items_with_schema_items_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "number"
    },
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "type": "number"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, additional_items_with_schema_items_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "unevaluatedProperties": false
    },
    "additionalItems": {
      "type": "string"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": {
      "unevaluatedProperties": false
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     additional_items_with_schema_items_boolean_items_true) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": true,
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     additional_items_with_schema_items_boolean_items_false) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": false,
    "additionalItems": {
      "type": "string"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, additional_items_with_schema_items_array_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [
      { "type": "string" },
      { "type": "number" }
    ],
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": [
      { "type": "string" },
      { "type": "number" }
    ],
    "additionalItems": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, modern_official_dialect_with_empty_fragment_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, modern_official_dialect_with_empty_fragment_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, modern_official_dialect_with_empty_fragment_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, then_empty_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, else_empty_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, then_empty_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, else_empty_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, property_names_type_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "propertyNames": {
      "type": "string",
      "pattern": "^S_"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "propertyNames": {
      "pattern": "^S_"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, property_names_type_default_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "propertyNames": {
      "type": [ "string" ]
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, property_names_type_default_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "propertyNames": {
      "type": "integer"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "propertyNames": {
      "type": "integer"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, property_names_default_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "propertyNames": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, definitions_to_defs_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "id": {
        "$ref": "#/definitions/uuid"
      }
    },
    "definitions": {
      "uuid": {
        "type": "string",
        "format": "uuid"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "id": {
        "$ref": "#/$defs/uuid"
      }
    },
    "$defs": {
      "uuid": {
        "type": "string",
        "format": "uuid"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, definitions_to_defs_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, definitions_to_defs_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, definitions_to_defs_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, non_applicable_type_specific_keywords_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ true, false ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ true, false ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_type_specific_keywords_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": null,
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": null
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, non_applicable_type_specific_keywords_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "foo",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "foo",
    "maxLength": 3
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ 1 ],
    "type": "integer",
    "format": "email"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "", "non_applicable_type_specific_keywords",
                    "Avoid keywords that don't apply to the type or "
                    "types that the current subschema expects",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "", "format_type_mismatch",
                    "The `format` keyword validates string instances but "
                    "`type` is not `string`",
                    false);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ "foo@bar.com" ],
    "type": "string",
    "format": "email"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ "foo@bar.com" ],
    "format": "email"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "integer",
        "format": "email"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "/properties/foo",
                    "non_applicable_type_specific_keywords",
                    "Avoid keywords that don't apply to the type or "
                    "types that the current subschema expects",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "/properties/foo", "format_type_mismatch",
                    "The `format` keyword validates string instances but "
                    "`type` is not `string`",
                    false);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_5) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ 1 ],
    "type": "integer"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ [] ],
    "type": "array",
    "items": {
      "type": "number",
      "format": "date-time"
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 2);
  EXPECT_LINT_TRACE(traces, 0, "/items",
                    "non_applicable_type_specific_keywords",
                    "Avoid keywords that don't apply to the type or "
                    "types that the current subschema expects",
                    true);
  EXPECT_LINT_TRACE(traces, 1, "/items", "format_type_mismatch",
                    "The `format` keyword validates string instances but "
                    "`type` is not `string`",
                    false);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ 1 ],
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "integer",
        "format": "uri"
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/$defs/foo", "format_type_mismatch",
                    "The `format` keyword validates string instances but "
                    "`type` is not `string`",
                    false);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_8) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ "https://example.com" ],
    "$ref": "#/$defs/A/properties/bar",
    "$defs": {
      "A": {
        "type": "integer",
        "format": "uri",
        "properties": {
          "bar": { "type": "string" }
        }
      }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(traces.size(), 1);
  EXPECT_LINT_TRACE(traces, 0, "/$defs/A", "format_type_mismatch",
                    "The `format` keyword validates string instances but "
                    "`type` is not `string`",
                    false);
}

TEST(AlterSchema_lint_2019_09, format_type_mismatch_9) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Test",
    "description": "A test schema",
    "examples": [ 1 ],
    "type": [ "integer", "string" ],
    "format": "email"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2019_09, not_false_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, not_false_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minimum": 5,
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "minimum": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, not_false_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, not_false_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "not": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, not_false_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "not": {
      "type": "number"
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "not": {
      "type": "number"
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": false,
      "baz": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {}
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": true,
      "bar": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_16) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, required_properties_in_properties_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": true
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "required": [ "foo", "bar" ],
    "additionalProperties": false,
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "fooBar": true
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "x-fooBar": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "baz": 123
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "x-baz": 123
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "needsPrefix": "value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "x-alreadyPrefixed": true,
    "x-X-alsoGood": 456,
    "x-needsPrefix": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "customKeyword": "value",
    "anotherOne": 123,
    "type": "object"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-customKeyword": "value",
    "x-anotherOne": 123,
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "custom": "value",
    "x-custom": "conflicting value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "x-custom": "conflicting value",
    "x-x-custom": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "nested": {
        "type": "string",
        "custom": "value",
        "x-custom": "conflicting value"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "nested": {
        "type": "string",
        "x-custom": "conflicting value",
        "x-x-custom": "value"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "type": "object",
    "$defs": {
      "foo": {
        "type": "string",
        "custom": "value",
        "x-custom": "conflicting value"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "type": "object",
    "$defs": {
      "foo": {
        "type": "string",
        "x-custom": "conflicting value",
        "x-x-custom": "value"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/foo",
    "custom": "value",
    "x-custom": "conflicting value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-custom": "conflicting value",
    "x-x-custom": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unknown_keywords_prefix_11) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "unevaluatedProperties": false,
    "custom": "value",
    "x-custom": "conflicting value"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "unevaluatedProperties": false,
    "x-custom": "conflicting value",
    "x-x-custom": "value"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, top_level_ref_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://sourcemeta.com",
    "$ref": "https://example.com"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://sourcemeta.com",
    "$ref": "https://example.com"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, additional_items_with_no_items) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "additionalItems": false
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, comment_trim_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$comment": "  A comment with whitespace  ",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$comment": "A comment with whitespace",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, comment_trim_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$comment": "A comment without whitespace",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$comment": "A comment without whitespace",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, top_level_examples_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, top_level_examples_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "My schema",
    "description": "A description",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2019_09, duplicate_examples_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ "foo", "bar", "foo" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ "foo", "bar" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, duplicate_examples_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ "foo", "bar", "baz" ],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ "foo", "bar", "baz" ],
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "string" },
      "unused": { "type": "integer" }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#/$defs/used",
    "$defs": {
      "used": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, orphan_definitions_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_inner_additional_properties_outer_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "additionalProperties": false }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "additionalProperties": false }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_inner_properties_and_additional_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": { "type": "string" } },
    "additionalProperties": false
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_type_can_elevate_with_outer_properties) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": { "type": "string" } },
    "allOf": [
      { "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": { "foo": { "type": "string" } },
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_ref_with_siblings_can_elevate) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://example.com", "minLength": 5 }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://example.com",
    "minLength": 5
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_with_recursive_ref_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$recursiveRef": "#", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, unnecessary_allof_wrapper_with_id_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$id": "nested", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$id": "nested", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_with_anchor_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$anchor": "foo", "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$anchor": "foo", "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_with_recursive_anchor_true_not_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$recursiveAnchor": true, "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$recursiveAnchor": true, "type": "object" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     unnecessary_allof_wrapper_with_recursive_anchor_false_elevated) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$recursiveAnchor": false, "type": "object" }
    ]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": false,
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, simple_properties_identifiers_skip_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/my-metaschema",
    "title": "My meta-schema",
    "description": "A custom meta-schema",
    "examples": [ {} ],
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true
    },
    "properties": {
      "foo-bar": { "type": "string" }
    }
  })JSON");

  LINT_WITHOUT_FIX(document, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(traces.size(), 0);
}

TEST(AlterSchema_lint_2019_09,
     simple_properties_identifiers_skip_metaschema_nested) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/my-metaschema",
    "title": "My meta-schema",
    "description": "A custom meta-schema",
    "examples": [ {} ],
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true
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

TEST(AlterSchema_lint_2019_09, simple_properties_identifiers_applies_non_meta) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/my-schema",
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
  EXPECT_LINT_TRACE(traces, 0, "", "simple_properties_identifiers",
                    "Set `properties` to identifier names that can be easily "
                    "mapped to programming languages (matching "
                    "[A-Za-z_][A-Za-z0-9_]*)",
                    false);
}

TEST(AlterSchema_lint_2019_09,
     simple_properties_identifiers_skip_bundled_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/main",
    "title": "Main schema",
    "description": "A schema that bundles a meta-schema",
    "examples": [ {} ],
    "$ref": "https://example.com/my-metaschema",
    "$defs": {
      "metaschema": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://example.com/my-metaschema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true,
          "https://json-schema.org/draft/2019-09/vocab/applicator": true
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

TEST(AlterSchema_lint_2019_09, empty_object_as_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {}
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Example",
    "description": "Example schema",
    "not": true
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": [1, 2]
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "enum": [1, 2]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Example",
    "description": "Example schema",
    "examples": [1],
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "title": "Example",
    "description": "Example schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_5) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "A": {
        "enum": []
      }
    },
    "$ref": "#/$defs/A"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_6) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_7) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_8) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_9) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, forbid_empty_enum_10) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": { "type": "string" },
    "enum": []
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "not": { "type": "string" },
    "enum": []
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, invalid_external_ref_1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, invalid_external_ref_2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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

TEST(AlterSchema_lint_2019_09, modern_official_dialect_with_http_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, modern_official_dialect_with_http_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft/2019-09/hyper-schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, modern_official_dialect_with_http_3) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft/2019-09/schema#",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09,
     modern_official_dialect_with_http_already_https) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, valid_examples_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, valid_default_4) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, valid_default_17) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "endpoint": {
        "default": { "backend": [ { "url": "/foo" } ] },
        "properties": {
          "backend": {
            "items": {
              "$ref": "#/$defs/backend"
            }
          }
        }
      },
      "backend": {
        "type": "object"
      }
    }
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, recursive_ref_to_static_ref_no_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveRef": "#"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_lint_2019_09, recursive_ref_stays_dynamic_with_anchor) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "$recursiveRef": "#"
  })JSON");

  LINT_AND_FIX(document, result, traces);

  EXPECT_FALSE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "$recursiveRef": "#"
  })JSON");

  EXPECT_EQ(document, expected);
}
