#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/documentation.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "documentation_test_utils.h"

class DocumentationDraft4Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "documentation.json");
    compiled_schema_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_schema_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    DocumentationDraft4Test::compiled_schema_ = nullptr;

TEST_F(DocumentationDraft4Test, type_string) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, type_integer) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "integer" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, type_number) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, type_boolean) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "boolean"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "enum", "values": [ false, true ] }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, type_null) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "null"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "enum", "values": [ null ] }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, string_min_max_length) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "minLength": 2,
    "maxLength": 10
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "constraints": [ ">= 2 chars", "<= 10 chars" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, string_pattern) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "pattern": "^[a-z]+$"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "constraints": [ "pattern: ^[a-z]+$" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, string_format) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "format": "email"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "badges": [ { "kind": "format", "value": "email" } ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, number_minimum_maximum) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "maximum": 100
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ ">= 0", "<= 100" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, number_multiple_of) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "multipleOf": 5
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ "multiple of 5" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, number_exclusive_minimum) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": true
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ "> 0" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, number_exclusive_maximum) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "maximum": 100,
    "exclusiveMaximum": true
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ "< 100" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, number_both_exclusive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": true,
    "maximum": 100,
    "exclusiveMaximum": true
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ "> 0", "< 100" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, integer_minimum) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "minimum": 1
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "integer" },
        "constraints": [ ">= 1" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, object_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "literal",
              "value": "name"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "age"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "integer"
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, object_required) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "required": [ "name" ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          },
          "constraints": [
            ">= 1 properties"
          ]
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "literal",
              "value": "name"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": true
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, object_additional_properties_typed) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": { "type": "integer" }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "object" }
      },
      {
        "identifier": 2,
        "path": [ { "type": "literal", "value": "name" } ],
        "type": { "kind": "primitive", "name": "string" },
        "required": false
      },
      {
        "identifier": 3,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "primitive", "name": "integer" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, object_open_additional_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "object" }
      },
      {
        "identifier": 2,
        "path": [ { "type": "literal", "value": "name" } ],
        "type": { "kind": "primitive", "name": "string" },
        "required": false
      },
      {
        "identifier": 3,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "any" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, object_pattern_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "patternProperties": {
      "^S_": { "type": "string" }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "pattern",
              "value": "^S_"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          }
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, object_min_max_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "minProperties": 1,
    "maxProperties": 5
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          },
          "constraints": [
            ">= 1 properties",
            "<= 5 properties"
          ]
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, array_items_string) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "string" }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "array", "items": { "kind": "primitive", "name": "string" } }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, array_min_max_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "string" },
    "minItems": 1,
    "maxItems": 10
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "array", "items": { "kind": "primitive", "name": "string" } },
        "constraints": [ ">= 1 items", "<= 10 items" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, array_unique_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": { "type": "integer" },
    "uniqueItems": true
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "array", "items": { "kind": "primitive", "name": "integer" } },
        "constraints": [ "unique" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, tuple_items_array) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "tuple",
          "items": [
            { "kind": "primitive", "name": "string" },
            { "kind": "primitive", "name": "integer" }
          ]
        }
      },
      {
        "identifier": 2,
        "path": [ { "type": "literal", "value": "0" } ],
        "type": { "kind": "primitive", "name": "string" },
        "required": false
      },
      {
        "identifier": 3,
        "path": [ { "type": "literal", "value": "1" } ],
        "type": { "kind": "primitive", "name": "integer" },
        "required": false
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, tuple_with_additional_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": [
      { "type": "string" },
      { "type": "integer" }
    ],
    "additionalItems": { "type": "boolean" }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "tuple",
          "items": [
            { "kind": "primitive", "name": "string" },
            { "kind": "primitive", "name": "integer" }
          ],
          "additional": { "kind": "enum", "values": [ false, true ] }
        }
      },
      {
        "identifier": 2,
        "path": [ { "type": "literal", "value": "0" } ],
        "type": { "kind": "primitive", "name": "string" },
        "required": false
      },
      {
        "identifier": 3,
        "path": [ { "type": "literal", "value": "1" } ],
        "type": { "kind": "primitive", "name": "integer" },
        "required": false
      },
      {
        "identifier": 4,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "enum", "values": [ false, true ] }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, array_of_objects_with_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "array",
    "items": {
      "type": "object",
      "properties": {
        "name": { "type": "string" }
      }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "object"
            }
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "object"
          }
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            },
            {
              "type": "literal",
              "value": "name"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            },
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, enum_values) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": [ "red", "green", "blue" ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "enum", "values": [ "red", "green", "blue" ] }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, title_and_description) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "title": "Name",
    "description": "The full name"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "title": "Name",
        "description": "The full name"
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, default_value) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "default": "unknown"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "default": "unknown"
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, ref_to_definition) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "name": { "$ref": "#/definitions/string_type" }
    },
    "definitions": {
      "string_type": { "type": "string" }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "literal",
              "value": "name"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, ref_recursive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com/tree",
    "type": "object",
    "properties": {
      "value": { "type": "string" },
      "child": { "$ref": "#" }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "literal",
              "value": "value"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "child"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 1
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, anyof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "any" }
      }
    ],
    "children": [
      {
        "label": "Any of",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": { "kind": "primitive", "name": "string" }
              }
            ]
          },
          {
            "identifier": 4,
            "rows": [
              {
                "identifier": 5,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": { "kind": "primitive", "name": "integer" }
              }
            ]
          }
        ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, not_type_only) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "not": { "type": "string" }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "any" }
      }
    ],
    "children": [
      {
        "label": "Must NOT match",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "value" } ],
                "type": { "kind": "primitive", "name": "string" }
              }
            ]
          }
        ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(DocumentationDraft4Test, nested_object_in_property) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object",
    "properties": {
      "address": {
        "type": "object",
        "properties": {
          "street": { "type": "string" },
          "city": { "type": "string" }
        }
      }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "rows": [
        {
          "identifier": 1,
          "path": [
            {
              "type": "synthetic",
              "value": "root"
            }
          ],
          "type": {
            "kind": "object"
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "literal",
              "value": "address"
            }
          ],
          "type": {
            "kind": "object"
          },
          "required": false
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "address"
            },
            {
              "type": "literal",
              "value": "street"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "address"
            },
            {
              "type": "literal",
              "value": "city"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        },
        {
          "identifier": 5,
          "path": [
            {
              "type": "literal",
              "value": "address"
            },
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        },
        {
          "identifier": 6,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}
