#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/documentation.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "documentation_test_utils.h"

class Documentation202012Test : public testing::Test {
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
    Documentation202012Test::compiled_schema_ = nullptr;

TEST_F(Documentation202012Test, type_string) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, object_required_with_annotations) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "email": {
        "type": "string",
        "format": "email",
        "description": "The user email address"
      },
      "age": {
        "type": "integer",
        "minimum": 0
      }
    },
    "required": [ "email" ]
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
              "value": "email"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "badges": [
            {
              "kind": "format",
              "value": "email"
            }
          ],
          "required": true,
          "description": "The user email address"
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
          "required": false,
          "constraints": [
            ">= 0"
          ]
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

TEST_F(Documentation202012Test, object_additional_properties_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
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
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, object_additional_properties_true) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": true
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

TEST_F(Documentation202012Test, object_open_implicit) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, object_closed_unevaluated_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "unevaluatedProperties": false
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
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, object_closed_additional_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": false
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
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, object_additional_properties_typed) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, array_items_string) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" }
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
              "kind": "primitive",
              "name": "string"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, nested_object_with_default) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "address": {
        "type": "object",
        "properties": {
          "street": { "type": "string" },
          "city": { "type": "string", "default": "Unknown" }
        },
        "required": [ "street" ]
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
          "required": false,
          "constraints": [
            ">= 1 properties"
          ]
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
          "required": true
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
          "required": false,
          "default": "Unknown"
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

TEST_F(Documentation202012Test, string_min_length) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 1
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "constraints": [ ">= 1 chars" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, string_max_length) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 100
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "constraints": [ "<= 100 chars" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, string_min_max_length) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 1,
    "maxLength": 100
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "constraints": [ ">= 1 chars", "<= 100 chars" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, string_exact_length) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 5,
    "maxLength": 5
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "constraints": [ "exactly 5 chars" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, number_minimum_maximum) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "minimum": 0,
    "maximum": 999
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ ">= 0", "<= 999" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, integer_exclusive_bounds) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 0,
    "exclusiveMaximum": 100
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "integer" },
        "constraints": [ ">= 1", "<= 99" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, array_min_max_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "minItems": 1,
    "maxItems": 10
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            ">= 1 items",
            "<= 10 items"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, array_unique_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "uniqueItems": true
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            "unique"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, array_unique_items_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "uniqueItems": false
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
              "kind": "primitive",
              "name": "string"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, array_items_with_constraints) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": {
      "type": "number",
      "minimum": 0,
      "maximum": 100
    },
    "minItems": 1
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "array", "items": { "kind": "primitive", "name": "number" } },
        "constraints": [ ">= 1 items" ]
      },
      {
        "identifier": 2,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ ">= 0", "<= 100" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, object_min_max_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, string_pattern) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, number_multiple_of) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 0.5
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "number" },
        "constraints": [ "multiple of 0.5" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, enum_single_string) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "active" ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "enum",
          "values": [ "active" ]
        }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, enum_multiple_strings) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "admin", "editor", "viewer", "guest" ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "enum",
          "values": [ "admin", "editor", "viewer", "guest" ]
        }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, enum_mixed_types) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "yes", "no", 1, 0, true, false, null ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "enum",
          "values": [
            "yes",
            "no",
            1,
            0,
            true,
            false,
            null
          ]
        }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, enum_exactly_ten) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "enum",
          "values": [
            "a",
            "b",
            "c",
            "d",
            "e",
            "f",
            "g",
            "h",
            "i",
            "j"
          ]
        }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, enum_overflow) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l" ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "enum",
          "values": [ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" ],
          "overflow": [ "k", "l" ]
        }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, contains_flat_inline) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "contains": { "type": "string", "minLength": 1 }
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            "contains: string",
            "contains >= 1 chars",
            ">= 1 matching items"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, contains_with_min_contains) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "contains": { "type": "string", "minLength": 1 },
    "minContains": 2
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            "contains: string",
            "contains >= 1 chars",
            ">= 2 matching items"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, contains_with_max_contains) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "contains": { "type": "string", "minLength": 1 },
    "maxContains": 5
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            "contains: string",
            "contains >= 1 chars",
            ">= 1 matching items",
            "<= 5 matching items"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, contains_with_min_and_max_contains) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "contains": { "type": "string", "minLength": 1 },
    "minContains": 2,
    "maxContains": 5
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            "contains: string",
            "contains >= 1 chars",
            ">= 2 matching items",
            "<= 5 matching items"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, contains_min_contains_zero) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" },
    "contains": { "type": "string", "minLength": 1 },
    "minContains": 0
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
              "kind": "primitive",
              "name": "string"
            }
          },
          "constraints": [
            "contains: string",
            "contains >= 1 chars",
            "0 or more matching items"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, string_all_annotations) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "title": "Username",
    "description": "The unique identifier for the user",
    "default": "anonymous",
    "examples": [ "alice", "bob" ],
    "deprecated": true,
    "readOnly": true
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "modifiers": [ "readOnly", "deprecated" ],
        "type": { "kind": "primitive", "name": "string" },
        "title": "Username",
        "description": "The unique identifier for the user",
        "default": "anonymous",
        "examples": [ "alice", "bob" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, property_write_only) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "password": {
        "type": "string",
        "writeOnly": true
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
              "value": "password"
            }
          ],
          "modifiers": [
            "writeOnly"
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

TEST_F(Documentation202012Test, nested_property_annotations) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "title": "User",
    "description": "A user record",
    "properties": {
      "name": {
        "type": "string",
        "title": "Full name",
        "description": "First and last name",
        "default": "Unknown",
        "examples": [ "Alice Smith" ]
      },
      "token": {
        "type": "string",
        "readOnly": true,
        "deprecated": true
      }
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
          ],
          "title": "User",
          "description": "A user record"
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
          "required": true,
          "title": "Full name",
          "description": "First and last name",
          "default": "Unknown",
          "examples": [
            "Alice Smith"
          ]
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "token"
            }
          ],
          "modifiers": [
            "readOnly",
            "deprecated"
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

TEST_F(Documentation202012Test, content_encoding_and_media_type) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentEncoding": "base64",
    "contentMediaType": "application/json"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "badges": [
          { "kind": "encoding", "value": "base64" },
          { "kind": "mime", "value": "application/json" }
        ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, content_schema_flat) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": {
      "type": "object",
      "minProperties": 1
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "badges": [
          { "kind": "encoding", "value": "base64" },
          { "kind": "mime", "value": "application/json" }
        ],
        "constraints": [ "decoded >= 1 properties" ]
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, property_names_flat) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "type": "string",
      "minLength": 1,
      "maxLength": 50
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
          },
          "constraints": [
            "keys >= 1 chars",
            "keys <= 50 chars"
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

TEST_F(Documentation202012Test, property_names_flat_pattern) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
      "type": "string",
      "pattern": "^[a-z_]+$"
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
          },
          "constraints": [
            "keys pattern: ^[a-z_]+$"
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

TEST_F(Documentation202012Test, pattern_properties_only) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" }
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
              "value": "^x-"
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

TEST_F(Documentation202012Test, property_with_anyof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": {
        "anyOf": [
          { "type": "string" },
          { "type": "integer" }
        ]
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
              "value": "value"
            }
          ],
          "type": {
            "kind": "any"
          },
          "required": false,
          "children": [
            {
              "label": "Any of",
              "children": [
                {
                  "identifier": 3,
                  "rows": [
                    {
                      "identifier": 4,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "string"
                      }
                    }
                  ]
                },
                {
                  "identifier": 5,
                  "rows": [
                    {
                      "identifier": 6,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "integer"
                      }
                    }
                  ]
                }
              ]
            }
          ]
        },
        {
          "identifier": 7,
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

TEST_F(Documentation202012Test, additional_properties_object_deep) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": {
      "type": "object",
      "properties": { "id": { "type": "integer" } }
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
              "value": "id"
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

TEST_F(Documentation202012Test, additional_properties_array_object_deep) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": {
      "type": "array",
      "items": {
        "type": "object",
        "properties": { "id": { "type": "integer" } }
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
              "type": "wildcard",
              "value": "*"
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
          "identifier": 3,
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
            "kind": "object"
          }
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
            },
            {
              "type": "literal",
              "value": "id"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "integer"
          },
          "required": false
        },
        {
          "identifier": 5,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            },
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

TEST_F(Documentation202012Test, unevaluated_properties_object_deep) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "name": { "type": "string" } },
    "unevaluatedProperties": {
      "type": "object",
      "properties": { "extra": { "type": "boolean" } }
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
            "kind": "object"
          }
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            },
            {
              "type": "literal",
              "value": "extra"
            }
          ],
          "type": {
            "kind": "enum",
            "values": [
              false,
              true
            ]
          },
          "required": false
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test, property_additional_properties_object_deep) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "meta": {
        "type": "object",
        "additionalProperties": {
          "type": "object",
          "properties": { "label": { "type": "string" } }
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
              "value": "meta"
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
              "value": "meta"
            },
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
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "meta"
            },
            {
              "type": "wildcard",
              "value": "*"
            },
            {
              "type": "literal",
              "value": "label"
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
              "value": "meta"
            },
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

TEST_F(Documentation202012Test, additional_properties_with_anyof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "name": { "type": "string" } },
    "additionalProperties": {
      "anyOf": [ { "type": "integer" }, { "type": "boolean" } ]
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
          },
          "children": [
            {
              "label": "Any of",
              "children": [
                {
                  "identifier": 4,
                  "rows": [
                    {
                      "identifier": 5,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "integer"
                      }
                    }
                  ]
                },
                {
                  "identifier": 6,
                  "rows": [
                    {
                      "identifier": 7,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "enum",
                        "values": [
                          false,
                          true
                        ]
                      }
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, items_with_anyof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": {
      "anyOf": [ { "type": "string" }, { "type": "integer" } ]
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
              "kind": "any"
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
            "kind": "any"
          },
          "children": [
            {
              "label": "Any of",
              "children": [
                {
                  "identifier": 3,
                  "rows": [
                    {
                      "identifier": 4,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "string"
                      }
                    }
                  ]
                },
                {
                  "identifier": 5,
                  "rows": [
                    {
                      "identifier": 6,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "integer"
                      }
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, property_with_not) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": { "not": { "type": "string" } }
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
            "kind": "any"
          },
          "required": false,
          "children": [
            {
              "label": "Must NOT match",
              "children": [
                {
                  "identifier": 3,
                  "rows": [
                    {
                      "identifier": 4,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "value"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "string"
                      }
                    }
                  ]
                }
              ]
            }
          ]
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test, pattern_property_with_oneof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": { "oneOf": [ { "type": "string" }, { "type": "integer" } ] }
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
              "value": "^x-"
            }
          ],
          "type": {
            "kind": "any"
          },
          "children": [
            {
              "label": "Any of",
              "children": [
                {
                  "identifier": 3,
                  "rows": [
                    {
                      "identifier": 4,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "string"
                      }
                    }
                  ]
                },
                {
                  "identifier": 5,
                  "rows": [
                    {
                      "identifier": 6,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ],
                      "type": {
                        "kind": "primitive",
                        "name": "integer"
                      }
                    }
                  ]
                }
              ]
            }
          ]
        },
        {
          "identifier": 7,
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

TEST_F(Documentation202012Test, pattern_property_nested_object) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": {
        "type": "object",
        "properties": {
          "value": { "type": "string" }
        }
      }
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
        "path": [ { "type": "pattern", "value": "^x-" } ],
        "type": { "kind": "object" }
      },
      {
        "identifier": 3,
        "path": [
          { "type": "pattern", "value": "^x-" },
          { "type": "literal", "value": "value" }
        ],
        "type": { "kind": "primitive", "name": "string" },
        "required": false
      },
      {
        "identifier": 4,
        "path": [
          { "type": "pattern", "value": "^x-" },
          { "type": "wildcard", "value": "*" }
        ],
        "type": { "kind": "any" }
      },
      {
        "identifier": 5,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "any" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, pattern_properties_with_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "patternProperties": {
      "^x-": { "type": "string" }
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
              "type": "pattern",
              "value": "^x-"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          }
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

TEST_F(Documentation202012Test, pattern_properties_with_additional) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" }
    },
    "additionalProperties": { "type": "number" }
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
        "path": [ { "type": "pattern", "value": "^x-" } ],
        "type": { "kind": "primitive", "name": "string" }
      },
      {
        "identifier": 3,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "primitive", "name": "number" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test,
       pattern_properties_with_properties_and_additional) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "patternProperties": {
      "^x-": { "type": "string" },
      "^[0-9]+$": { "type": "integer" }
    },
    "additionalProperties": { "type": "number" }
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
        "path": [ { "type": "pattern", "value": "^x-" } ],
        "type": { "kind": "primitive", "name": "string" }
      },
      {
        "identifier": 4,
        "path": [
          { "type": "pattern", "value": "^[0-9]+$" }
        ],
        "type": { "kind": "primitive", "name": "integer" }
      },
      {
        "identifier": 5,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "primitive", "name": "number" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, pattern_properties_additional_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "id": { "type": "integer" }
    },
    "patternProperties": {
      "^tag_": { "type": "string" }
    },
    "additionalProperties": false
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
        "path": [ { "type": "literal", "value": "id" } ],
        "type": { "kind": "primitive", "name": "integer" },
        "required": false
      },
      {
        "identifier": 3,
        "path": [ { "type": "pattern", "value": "^tag_" } ],
        "type": { "kind": "primitive", "name": "string" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, property_name_with_slash) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo/bar": { "type": "string" }
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
              "value": "foo/bar"
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

TEST_F(Documentation202012Test, property_name_with_tilde) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo~bar": { "type": "string" }
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
              "value": "foo~bar"
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

TEST_F(Documentation202012Test, property_name_with_slash_and_tilde) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "a/b~c": { "type": "string" }
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
              "value": "a/b~c"
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

TEST_F(Documentation202012Test, tuple_prefix_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
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

TEST_F(Documentation202012Test, tuple_prefix_items_with_tail) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" },
      { "type": "integer" }
    ],
    "items": { "type": "number" }
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
          "additional": { "kind": "primitive", "name": "number" }
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
        "type": { "kind": "primitive", "name": "number" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, tuple_prefix_items_complex) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" },
      {
        "type": "object",
        "properties": {
          "name": { "type": "string" },
          "age": { "type": "integer" }
        },
        "required": [ "name" ]
      }
    ]
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
            "kind": "tuple",
            "items": [
              {
                "kind": "primitive",
                "name": "string"
              },
              {
                "kind": "object"
              }
            ]
          }
        },
        {
          "identifier": 2,
          "path": [
            {
              "type": "literal",
              "value": "0"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false
        }
      ],
      "children": [
        {
          "label": "Array item 1",
          "children": [
            {
              "identifier": 3,
              "rows": [
                {
                  "identifier": 4,
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
                  "identifier": 5,
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
                  "identifier": 6,
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
                  "identifier": 7,
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
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, tuple_prefix_items_required) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "number" }
    ],
    "minItems": 2
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
            { "kind": "primitive", "name": "integer" },
            { "kind": "primitive", "name": "number" }
          ]
        },
        "constraints": [ ">= 2 items" ]
      },
      {
        "identifier": 2,
        "path": [ { "type": "literal", "value": "0" } ],
        "type": { "kind": "primitive", "name": "string" },
        "required": true
      },
      {
        "identifier": 3,
        "path": [ { "type": "literal", "value": "1" } ],
        "type": { "kind": "primitive", "name": "integer" },
        "required": true
      },
      {
        "identifier": 4,
        "path": [ { "type": "literal", "value": "2" } ],
        "type": { "kind": "primitive", "name": "number" },
        "required": false
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, object_unevaluated_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "unevaluatedProperties": { "type": "integer" }
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

TEST_F(Documentation202012Test, tuple_unevaluated_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" },
      { "type": "integer" }
    ],
    "unevaluatedItems": { "type": "number" }
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
          "additional": { "kind": "primitive", "name": "number" }
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

TEST_F(Documentation202012Test, property_boolean_true) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "anything": true
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
              "value": "anything"
            }
          ],
          "type": {
            "kind": "any"
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

TEST_F(Documentation202012Test, property_boolean_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "impossible": false
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
              "value": "impossible"
            }
          ],
          "type": {
            "kind": "never"
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

TEST_F(Documentation202012Test, external_ref_property) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "address": { "$ref": "https://example.com/address.json" }
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
            "kind": "externalRef",
            "url": "https://example.com/address.json"
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

TEST_F(Documentation202012Test, external_ref_root) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/user.json"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": {
          "kind": "externalRef",
          "url": "https://example.com/user.json"
        }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, dynamic_ref_with_anchor) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$dynamicAnchor": "node",
    "type": "object",
    "properties": {
      "value": { "type": "string" },
      "children": {
        "type": "array",
        "items": { "$dynamicRef": "#node" }
      }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON(
    {
      "identifier": 0,
      "dynamicAnchor": "node",
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
              "value": "children"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "recursiveRef",
              "identifier": 1,
              "path": [
                {
                  "type": "synthetic",
                  "value": "root"
                }
              ]
            }
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "children"
            },
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 1,
            "path": [
              {
                "type": "synthetic",
                "value": "root"
              }
            ]
          }
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test, dynamic_ref_standalone) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "#target"
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "dynamicRef", "anchor": "target" }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, no_dynamic_anchor_by_default) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, internal_ref_non_recursive) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "billing": { "$ref": "#/$defs/address" },
      "shipping": { "$ref": "#/$defs/address" }
    },
    "$defs": {
      "address": {
        "type": "object",
        "properties": {
          "street": { "type": "string" },
          "city": { "type": "string" }
        },
        "required": [ "street" ]
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
              "value": "billing"
            }
          ],
          "type": {
            "kind": "object"
          },
          "required": false,
          "constraints": [
            ">= 1 properties"
          ]
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "billing"
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
          "required": true
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "billing"
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
              "value": "billing"
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
              "type": "literal",
              "value": "shipping"
            }
          ],
          "type": {
            "kind": "object"
          },
          "required": false,
          "constraints": [
            ">= 1 properties"
          ]
        },
        {
          "identifier": 7,
          "path": [
            {
              "type": "literal",
              "value": "shipping"
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
          "required": true
        },
        {
          "identifier": 8,
          "path": [
            {
              "type": "literal",
              "value": "shipping"
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
          "identifier": 9,
          "path": [
            {
              "type": "literal",
              "value": "shipping"
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
          "identifier": 10,
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

TEST_F(Documentation202012Test, internal_ref_recursive_root) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": { "type": "string" },
      "children": {
        "type": "array",
        "items": { "$ref": "#" }
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
              "value": "children"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "recursiveRef",
              "identifier": 1,
              "path": [
                {
                  "type": "synthetic",
                  "value": "root"
                }
              ]
            }
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "children"
            },
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 1,
            "path": [
              {
                "type": "synthetic",
                "value": "root"
              }
            ]
          }
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test, internal_ref_recursive_via_def) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/node",
    "$defs": {
      "node": {
        "type": "object",
        "properties": {
          "value": { "type": "string" },
          "children": {
            "type": "array",
            "items": { "$ref": "#/$defs/node" }
          }
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
            "kind": "any"
          }
        }
      ],
      "children": [
        {
          "label": "All of",
          "children": [
            {
              "identifier": 2,
              "rows": [
                {
                  "identifier": 3,
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
                  "identifier": 4,
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
                  "identifier": 5,
                  "path": [
                    {
                      "type": "literal",
                      "value": "children"
                    }
                  ],
                  "type": {
                    "kind": "array",
                    "items": {
                      "kind": "recursiveRef",
                      "identifier": 2,
                      "path": [
                        {
                          "type": "synthetic",
                          "value": "root"
                        }
                      ]
                    }
                  },
                  "required": false
                },
                {
                  "identifier": 6,
                  "path": [
                    {
                      "type": "literal",
                      "value": "children"
                    },
                    {
                      "type": "wildcard",
                      "value": "*"
                    }
                  ],
                  "type": {
                    "kind": "recursiveRef",
                    "identifier": 2,
                    "path": [
                      {
                        "type": "synthetic",
                        "value": "root"
                      }
                    ]
                  }
                },
                {
                  "identifier": 7,
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
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, internal_ref_recursive_with_id) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/tree",
    "type": "object",
    "properties": {
      "value": { "type": "string" },
      "children": {
        "type": "array",
        "items": { "$ref": "#" }
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
              "value": "children"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "recursiveRef",
              "identifier": 1,
              "path": [
                {
                  "type": "synthetic",
                  "value": "root"
                }
              ]
            }
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "children"
            },
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 1,
            "path": [
              {
                "type": "synthetic",
                "value": "root"
              }
            ]
          }
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test, internal_ref_shared_def_with_recursion) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "primary": { "$ref": "#/$defs/contact" },
      "emergency": { "$ref": "#/$defs/contact" }
    },
    "$defs": {
      "contact": {
        "type": "object",
        "properties": {
          "name": { "type": "string" },
          "backup": { "$ref": "#/$defs/contact" }
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
              "value": "primary"
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
              "value": "primary"
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
              "type": "literal",
              "value": "primary"
            },
            {
              "type": "literal",
              "value": "backup"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 2,
            "path": [
              {
                "type": "literal",
                "value": "primary"
              }
            ]
          },
          "required": false
        },
        {
          "identifier": 5,
          "path": [
            {
              "type": "literal",
              "value": "primary"
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
              "type": "literal",
              "value": "emergency"
            }
          ],
          "type": {
            "kind": "object"
          },
          "required": false
        },
        {
          "identifier": 7,
          "path": [
            {
              "type": "literal",
              "value": "emergency"
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
          "identifier": 8,
          "path": [
            {
              "type": "literal",
              "value": "emergency"
            },
            {
              "type": "literal",
              "value": "backup"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 6,
            "path": [
              {
                "type": "literal",
                "value": "emergency"
              }
            ]
          },
          "required": false
        },
        {
          "identifier": 9,
          "path": [
            {
              "type": "literal",
              "value": "emergency"
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
          "identifier": 10,
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

TEST_F(Documentation202012Test, object_with_anyof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "title": "T",
    "anyOf": [
        { "required": [ "a" ] },
        { "required": [ "b" ] }
    ]
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
            "kind": "any"
          }
        }
      ],
      "children": [
        {
          "label": "All of",
          "children": [
            {
              "identifier": 2,
              "rows": [
                {
                  "identifier": 3,
                  "path": [
                    {
                      "type": "synthetic",
                      "value": "root"
                    }
                  ],
                  "type": {
                    "kind": "any"
                  }
                }
              ],
              "children": [
                {
                  "label": "Any of",
                  "children": [
                    {
                      "identifier": 4,
                      "rows": [
                        {
                          "identifier": 5,
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
                          "identifier": 6,
                          "path": [
                            {
                              "type": "literal",
                              "value": "a"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          },
                          "required": true
                        },
                        {
                          "identifier": 7,
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
                    },
                    {
                      "identifier": 8,
                      "rows": [
                        {
                          "identifier": 9,
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
                          "identifier": 10,
                          "path": [
                            {
                              "type": "literal",
                              "value": "b"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          },
                          "required": true
                        },
                        {
                          "identifier": 11,
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
                  ]
                }
              ]
            },
            {
              "identifier": 12,
              "rows": [
                {
                  "identifier": 13,
                  "path": [
                    {
                      "type": "synthetic",
                      "value": "root"
                    }
                  ],
                  "type": {
                    "kind": "object"
                  },
                  "title": "T"
                },
                {
                  "identifier": 14,
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
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, if_then_else) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "const": true },
    "then": { "type": "string" },
    "else": { "type": "integer" }
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
        "label": "If",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": {
                  "kind": "enum",
                  "values": [ true ]
                }
              }
            ]
          }
        ]
      },
      {
        "label": "Then",
        "children": [
          {
            "identifier": 4,
            "rows": [
              {
                "identifier": 5,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": { "kind": "primitive", "name": "string" }
              }
            ]
          }
        ]
      },
      {
        "label": "Else",
        "children": [
          {
            "identifier": 6,
            "rows": [
              {
                "identifier": 7,
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

TEST_F(Documentation202012Test, allof_simple) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
        { "enum": [ "a", "b" ] },
        { "enum": [ "b", "c" ] }
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
        "label": "All of",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": {
                  "kind": "enum",
                  "values": [ "a", "b" ]
                }
              }
            ]
          },
          {
            "identifier": 4,
            "rows": [
              {
                "identifier": 5,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": {
                  "kind": "enum",
                  "values": [ "b", "c" ]
                }
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

TEST_F(Documentation202012Test, dependent_schemas) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "dependentSchemas": {
        "a": { "required": [ "b" ] }
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
            "kind": "any"
          }
        }
      ],
      "children": [
        {
          "label": "All of",
          "children": [
            {
              "identifier": 2,
              "rows": [
                {
                  "identifier": 3,
                  "path": [
                    {
                      "type": "synthetic",
                      "value": "root"
                    }
                  ],
                  "type": {
                    "kind": "any"
                  }
                }
              ],
              "children": [
                {
                  "label": "Any of",
                  "children": [
                    {
                      "identifier": 4,
                      "rows": [
                        {
                          "identifier": 5,
                          "path": [
                            {
                              "type": "synthetic",
                              "value": "root"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          },
                          "constraints": [
                            "must NOT match >= 1 properties"
                          ]
                        }
                      ]
                    },
                    {
                      "identifier": 6,
                      "rows": [
                        {
                          "identifier": 7,
                          "path": [
                            {
                              "type": "synthetic",
                              "value": "root"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          }
                        }
                      ],
                      "children": [
                        {
                          "label": "All of",
                          "children": [
                            {
                              "identifier": 8,
                              "rows": [
                                {
                                  "identifier": 9,
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
                                  "identifier": 10,
                                  "path": [
                                    {
                                      "type": "literal",
                                      "value": "a"
                                    }
                                  ],
                                  "type": {
                                    "kind": "any"
                                  },
                                  "required": true
                                },
                                {
                                  "identifier": 11,
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
                            },
                            {
                              "identifier": 12,
                              "rows": [
                                {
                                  "identifier": 13,
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
                                  "identifier": 14,
                                  "path": [
                                    {
                                      "type": "literal",
                                      "value": "b"
                                    }
                                  ],
                                  "type": {
                                    "kind": "any"
                                  },
                                  "required": true
                                },
                                {
                                  "identifier": 15,
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
                          ]
                        }
                      ]
                    }
                  ]
                }
              ]
            },
            {
              "identifier": 16,
              "rows": [
                {
                  "identifier": 17,
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
                  "identifier": 18,
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
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, dependent_required) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "dependentRequired": {
        "a": [ "b" ]
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
            "kind": "any"
          }
        }
      ],
      "children": [
        {
          "label": "All of",
          "children": [
            {
              "identifier": 2,
              "rows": [
                {
                  "identifier": 3,
                  "path": [
                    {
                      "type": "synthetic",
                      "value": "root"
                    }
                  ],
                  "type": {
                    "kind": "any"
                  }
                }
              ],
              "children": [
                {
                  "label": "Any of",
                  "children": [
                    {
                      "identifier": 4,
                      "rows": [
                        {
                          "identifier": 5,
                          "path": [
                            {
                              "type": "synthetic",
                              "value": "root"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          },
                          "constraints": [
                            "must NOT match >= 1 properties"
                          ]
                        }
                      ]
                    },
                    {
                      "identifier": 6,
                      "rows": [
                        {
                          "identifier": 7,
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
                            ">= 2 properties"
                          ]
                        },
                        {
                          "identifier": 8,
                          "path": [
                            {
                              "type": "literal",
                              "value": "a"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          },
                          "required": true
                        },
                        {
                          "identifier": 9,
                          "path": [
                            {
                              "type": "literal",
                              "value": "b"
                            }
                          ],
                          "type": {
                            "kind": "any"
                          },
                          "required": true
                        },
                        {
                          "identifier": 10,
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
                  ]
                }
              ]
            },
            {
              "identifier": 11,
              "rows": [
                {
                  "identifier": 12,
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
                  "identifier": 13,
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
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, contains_branching) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
        "anyOf": [
            { "enum": [ 1 ] },
            { "enum": [ 2 ] }
        ]
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "array" },
        "constraints": [ ">= 1 matching items" ]
      }
    ],
    "children": [
      {
        "label": "Contains",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [
                  { "type": "synthetic", "value": "matching item" }
                ],
                "type": { "kind": "any" }
              }
            ],
            "children": [
              {
                "label": "Any of",
                "children": [
                  {
                    "identifier": 4,
                    "rows": [
                      {
                        "identifier": 5,
                        "path": [
                          { "type": "synthetic", "value": "root" }
                        ],
                        "type": {
                          "kind": "enum",
                          "values": [ 1 ]
                        }
                      }
                    ]
                  },
                  {
                    "identifier": 6,
                    "rows": [
                      {
                        "identifier": 7,
                        "path": [
                          { "type": "synthetic", "value": "root" }
                        ],
                        "type": {
                          "kind": "enum",
                          "values": [ 2 ]
                        }
                      }
                    ]
                  }
                ]
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

TEST_F(Documentation202012Test, content_schema_branching) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentEncoding": "base64",
    "contentMediaType": "application/json",
    "contentSchema": {
        "anyOf": [
            { "enum": [ "v1" ] },
            { "enum": [ "v2" ] }
        ]
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "primitive", "name": "string" },
        "badges": [
          { "kind": "encoding", "value": "base64" },
          { "kind": "mime", "value": "application/json" }
        ]
      }
    ],
    "children": [
      {
        "label": "Decoded content",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "decoded" } ],
                "type": { "kind": "any" }
              }
            ],
            "children": [
              {
                "label": "Any of",
                "children": [
                  {
                    "identifier": 4,
                    "rows": [
                      {
                        "identifier": 5,
                        "path": [
                          { "type": "synthetic", "value": "root" }
                        ],
                        "type": {
                          "kind": "enum",
                          "values": [ "v1" ]
                        }
                      }
                    ]
                  },
                  {
                    "identifier": 6,
                    "rows": [
                      {
                        "identifier": 7,
                        "path": [
                          { "type": "synthetic", "value": "root" }
                        ],
                        "type": {
                          "kind": "enum",
                          "values": [ "v2" ]
                        }
                      }
                    ]
                  }
                ]
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

TEST_F(Documentation202012Test, oneOf_simple) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
        { "enum": [ "x" ] },
        { "enum": [ "y" ] }
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
        "label": "One of",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": {
                  "kind": "enum",
                  "values": [ "x" ]
                }
              }
            ]
          },
          {
            "identifier": 4,
            "rows": [
              {
                "identifier": 5,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": {
                  "kind": "enum",
                  "values": [ "y" ]
                }
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

TEST_F(Documentation202012Test, property_names_branching) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": {
        "anyOf": [
            { "type": "string", "pattern": "^x" },
            { "type": "string", "pattern": "^y" }
        ]
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
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "any"
          }
        }
      ],
      "children": [
        {
          "label": "Property names",
          "children": [
            {
              "identifier": 3,
              "rows": [
                {
                  "identifier": 4,
                  "path": [
                    {
                      "type": "synthetic",
                      "value": "key"
                    }
                  ],
                  "type": {
                    "kind": "any"
                  }
                }
              ],
              "children": [
                {
                  "label": "Any of",
                  "children": [
                    {
                      "identifier": 5,
                      "rows": [
                        {
                          "identifier": 6,
                          "path": [
                            {
                              "type": "synthetic",
                              "value": "root"
                            }
                          ],
                          "type": {
                            "kind": "primitive",
                            "name": "string"
                          },
                          "constraints": [
                            "pattern: ^x"
                          ]
                        }
                      ]
                    },
                    {
                      "identifier": 7,
                      "rows": [
                        {
                          "identifier": 8,
                          "path": [
                            {
                              "type": "synthetic",
                              "value": "root"
                            }
                          ],
                          "type": {
                            "kind": "primitive",
                            "name": "string"
                          },
                          "constraints": [
                            "pattern: ^y"
                          ]
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, not_type_only) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, not_flat) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "not": { "type": "string", "pattern": "^x" }
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
        "label": "All of",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": { "kind": "any" },
                "constraints": [ "must NOT match pattern: ^x" ]
              }
            ]
          },
          {
            "identifier": 4,
            "rows": [
              {
                "identifier": 5,
                "path": [ { "type": "synthetic", "value": "root" } ],
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

TEST_F(Documentation202012Test, not_branching) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "not": {
        "anyOf": [
            { "type": "string", "pattern": "^x" },
            { "type": "string", "pattern": "^y" }
        ]
    }
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
        "label": "All of",
        "children": [
          {
            "identifier": 2,
            "rows": [
              {
                "identifier": 3,
                "path": [ { "type": "synthetic", "value": "root" } ],
                "type": { "kind": "any" }
              }
            ],
            "children": [
              {
                "label": "Must NOT match",
                "children": [
                  {
                    "identifier": 4,
                    "rows": [
                      {
                        "identifier": 5,
                        "path": [
                          { "type": "synthetic", "value": "value" }
                        ],
                        "type": { "kind": "any" }
                      }
                    ],
                    "children": [
                      {
                        "label": "Any of",
                        "children": [
                          {
                            "identifier": 6,
                            "rows": [
                              {
                                "identifier": 7,
                                "path": [
                                  { "type": "synthetic", "value": "root" }
                                ],
                                "type": {
                                  "kind": "primitive",
                                  "name": "string"
                                },
                                "constraints": [ "pattern: ^x" ]
                              }
                            ]
                          },
                          {
                            "identifier": 8,
                            "rows": [
                              {
                                "identifier": 9,
                                "path": [
                                  { "type": "synthetic", "value": "root" }
                                ],
                                "type": {
                                  "kind": "primitive",
                                  "name": "string"
                                },
                                "constraints": [ "pattern: ^y" ]
                              }
                            ]
                          }
                        ]
                      }
                    ]
                  }
                ]
              }
            ]
          },
          {
            "identifier": 10,
            "rows": [
              {
                "identifier": 11,
                "path": [ { "type": "synthetic", "value": "root" } ],
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

TEST_F(Documentation202012Test, anyof_unevaluated) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
        {
            "type": "object",
            "properties": { "a": { "type": "string" } }
        },
        {
            "type": "object",
            "properties": { "b": { "type": "integer" } }
        }
    ],
    "unevaluatedProperties": { "type": "string" }
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
            "kind": "any"
          }
        },
        {
          "identifier": 10,
          "path": [
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          }
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
                  "identifier": 4,
                  "path": [
                    {
                      "type": "literal",
                      "value": "a"
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
                      "type": "wildcard",
                      "value": "*"
                    }
                  ],
                  "type": {
                    "kind": "any"
                  }
                }
              ]
            },
            {
              "identifier": 6,
              "rows": [
                {
                  "identifier": 7,
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
                  "identifier": 8,
                  "path": [
                    {
                      "type": "literal",
                      "value": "b"
                    }
                  ],
                  "type": {
                    "kind": "primitive",
                    "name": "integer"
                  },
                  "required": false
                },
                {
                  "identifier": 9,
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
          ]
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, root_boolean_false) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": true
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
                "type": { "kind": "any" }
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

TEST_F(Documentation202012Test, no_type_keyword_produces_any) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, default_explicit_null) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": {
        "type": "string",
        "default": null
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
              "value": "value"
            }
          ],
          "type": {
            "kind": "primitive",
            "name": "string"
          },
          "required": false,
          "default": null
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

TEST_F(Documentation202012Test, recursive_ref_walk_schema_cycle) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/tree",
    "type": "object",
    "properties": {
      "value": { "type": "string" },
      "left": { "$ref": "#" },
      "right": { "$ref": "#" }
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
              "value": "left"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 1,
            "path": [
              {
                "type": "synthetic",
                "value": "root"
              }
            ]
          },
          "required": false
        },
        {
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "right"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 1,
            "path": [
              {
                "type": "synthetic",
                "value": "root"
              }
            ]
          },
          "required": false
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test, array_items_ref_to_object) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "$ref": "#/$defs/item" },
    "$defs": {
      "item": {
        "type": "object",
        "properties": { "name": { "type": "string" } }
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

TEST_F(Documentation202012Test, array_items_ref_to_string) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "$ref": "#/$defs/item" },
    "$defs": {
      "item": { "type": "string" }
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
              "kind": "primitive",
              "name": "string"
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
            "kind": "primitive",
            "name": "string"
          }
        }
      ]
    }
  )JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, array_items_object_with_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST_F(Documentation202012Test, array_items_ref_to_object_with_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "$ref": "#/$defs/item" },
    "$defs": {
      "item": {
        "type": "object",
        "properties": { "name": { "type": "string" } }
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

TEST_F(Documentation202012Test, object_property_array_of_objects) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": {
          "type": "object",
          "properties": {
            "name": { "type": "string" }
          }
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
              "value": "tags"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "object"
            }
          },
          "required": false
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "tags"
            },
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
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "tags"
            },
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
          "identifier": 5,
          "path": [
            {
              "type": "literal",
              "value": "tags"
            },
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

TEST_F(Documentation202012Test, mutual_ref_cycle_in_type_expression) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "$ref": "#/$defs/a" }
    },
    "$defs": {
      "a": { "$ref": "#/$defs/b" },
      "b": { "$ref": "#/$defs/a" }
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
              "value": "foo"
            }
          ],
          "type": {
            "kind": "any"
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

TEST_F(Documentation202012Test,
       array_items_object_with_unevaluated_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": {
      "type": "object",
      "properties": {
        "name": { "type": "string" }
      },
      "unevaluatedProperties": { "type": "boolean" }
    }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "identifier": 0,
    "rows": [
      {
        "identifier": 1,
        "path": [ { "type": "synthetic", "value": "root" } ],
        "type": { "kind": "array", "items": { "kind": "object" } }
      },
      {
        "identifier": 2,
        "path": [ { "type": "wildcard", "value": "*" } ],
        "type": { "kind": "object" }
      },
      {
        "identifier": 3,
        "path": [
          { "type": "wildcard", "value": "*" },
          { "type": "literal", "value": "name" }
        ],
        "type": { "kind": "primitive", "name": "string" },
        "required": false
      },
      {
        "identifier": 4,
        "path": [
          { "type": "wildcard", "value": "*" },
          { "type": "wildcard", "value": "*" }
        ],
        "type": { "kind": "enum", "values": [ false, true ] }
      }
    ]
  })JSON")};

  EXPECT_DOCUMENTATION(schema, sourcemeta::core::schema_walker,
                       sourcemeta::core::schema_resolver, *compiled_schema_,
                       expected);
}

TEST_F(Documentation202012Test, recursive_ref_inside_array_items) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": {
      "type": "object",
      "properties": {
        "children": {
          "type": "array",
          "items": { "$ref": "#/items" }
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
              "value": "children"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "recursiveRef",
              "identifier": 2,
              "path": [
                {
                  "type": "wildcard",
                  "value": "*"
                }
              ]
            }
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
              "type": "literal",
              "value": "children"
            },
            {
              "type": "wildcard",
              "value": "*"
            }
          ],
          "type": {
            "kind": "recursiveRef",
            "identifier": 2,
            "path": [
              {
                "type": "wildcard",
                "value": "*"
              }
            ]
          }
        },
        {
          "identifier": 5,
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

TEST_F(Documentation202012Test,
       object_property_array_items_unevaluated_properties) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": {
          "type": "object",
          "properties": {
            "name": { "type": "string" }
          },
          "unevaluatedProperties": { "type": "boolean" }
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
              "value": "tags"
            }
          ],
          "type": {
            "kind": "array",
            "items": {
              "kind": "object"
            }
          },
          "required": false
        },
        {
          "identifier": 3,
          "path": [
            {
              "type": "literal",
              "value": "tags"
            },
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
          "identifier": 4,
          "path": [
            {
              "type": "literal",
              "value": "tags"
            },
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
          "identifier": 5,
          "path": [
            {
              "type": "literal",
              "value": "tags"
            },
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
            "kind": "enum",
            "values": [
              false,
              true
            ]
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
