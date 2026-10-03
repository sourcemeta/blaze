#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "canonicalizer_test_utils.h"

namespace {
auto compiled_metaschema() -> const sourcemeta::blaze::Template & {
  static const sourcemeta::blaze::Template SCHEMA_TEMPLATE{
      sourcemeta::blaze::compile(
          sourcemeta::core::read_json(std::filesystem::path{SCHEMAS_PATH} /
                                      "canonical-draft3.json"),
          sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
          sourcemeta::blaze::default_schema_compiler)};
  return SCHEMA_TEMPLATE;
}
} // namespace

TEST(type_boolean_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "enum": [ false, true ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_boolean_as_enum_2) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "boolean",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(equal_bounds_with_exclusive_minimum_unsatisfiable) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number",
    "minimum": 5,
    "maximum": 5,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_null_as_enum_1) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "enum": [ null ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(equal_numeric_bounds_to_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "enum": [ 3 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(string_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(integer_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "integer",
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(number_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(array_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(divisible_by_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "minimum": 0
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "integer",
          "minimum": 0,
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(divisible_by_explicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "divisibleBy": 2
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "integer",
          "divisibleBy": 2
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(exclusive_minimum_false_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number",
    "minimum": 0,
    "exclusiveMinimum": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "number",
          "minimum": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(exclusive_minimum_integer_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "minimum": 0,
    "exclusiveMinimum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "integer",
          "minimum": 1,
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(exclusive_maximum_integer_fold) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "maximum": 10,
    "exclusiveMaximum": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "integer",
          "maximum": 9,
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_property_required_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "name": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_property_required_true) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "name": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": true
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_empty_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {}
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "$ref": "#/definitions/1"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(extends_single_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": { "type": "string" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_string_to_array) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 1, 2, 3 ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "enum": [ 1, 2, 3 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(object_with_ref_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "$ref": "#" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "bar": {
              "$ref": "#/definitions/0"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_any_in_array_with_extras_expanded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "any", "title": "Anything goes" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "title": "Anything goes",
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            }
          ]
        },
        "2": {
          "enum": [ null ]
        },
        "3": {
          "enum": [ false, true ]
        },
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/5"
          }
        },
        "5": {},
        "6": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/5"
          }
        },
        "7": {
          "type": "string",
          "minLength": 0
        },
        "8": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_any_in_array_string_form_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "any", "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_any_in_array_bare_object_form_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", { "type": "any" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_any_in_array_empty_object_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_string_and_object_schema_variant) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "array", { "type": "object" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_schema_variant_distributes_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "array", { "type": "object" } ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/4"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "4": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_with_any_keeps_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "any" ],
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/5"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "string",
          "minLength": 0
        },
        "6": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_nested_schema_union_variant) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "array", { "type": [ "string", { "maxItems": 2 } ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": [
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "4": {
          "type": "string",
          "minLength": 0
        },
        "5": {
          "type": [
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/9"
            },
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/10"
            }
          ]
        },
        "6": {
          "enum": [ null ]
        },
        "7": {
          "enum": [ false, true ]
        },
        "8": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "9": {
          "type": "array",
          "maxItems": 2,
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "10": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_schema_variant_with_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "array", { "type": "object" } ],
    "extends": {
      "type": "object",
      "properties": {
        "foo": { "type": "string" }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "1": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": "string",
          "minLength": 0
        },
        "4": {
          "type": [
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "6": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_additional_properties_not_narrowed_by_branches) {
  auto document = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "type": [
        {
          "type": "object",
          "patternProperties": {
            "^a": {}
          }
        },
        {
          "type": "object",
          "patternProperties": {
            "^b": {}
          }
        }
      ],
      "additionalProperties": {
        "type": "integer"
      }
    })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "2": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^a": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "3": {},
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^b": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "5": {
          "type": [
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/11"
            },
            {
              "$ref": "#/definitions/12"
            }
          ]
        },
        "6": {
          "enum": [ null ]
        },
        "7": {
          "enum": [ false, true ]
        },
        "8": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/9"
          }
        },
        "9": {
          "type": "integer",
          "divisibleBy": 1
        },
        "10": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/3"
          }
        },
        "11": {
          "type": "string",
          "minLength": 0
        },
        "12": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_properties_do_not_narrow_branch_additional_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "type": [
        {
          "type": "object",
          "additionalProperties": {
            "type": "integer"
          }
        },
        {
          "type": "object",
          "patternProperties": {
            "^a": {
              "type": "integer"
            }
          }
        }
      ],
      "properties": {
        "a": {
          "type": "string"
        }
      }
    })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "2": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "3": {
          "type": "integer",
          "divisibleBy": 1
        },
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^a": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/5"
          }
        },
        "5": {},
        "6": {
          "type": [
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/9"
            },
            {
              "$ref": "#/definitions/11"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/12"
            }
          ]
        },
        "7": {
          "enum": [ null ]
        },
        "8": {
          "enum": [ false, true ]
        },
        "9": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/10"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/5"
          }
        },
        "10": {
          "type": "string",
          "minLength": 0
        },
        "11": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/5"
          }
        },
        "12": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_items_do_not_activate_branch_additional_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "type": [
        {
          "type": "array",
          "additionalItems": {
            "type": "string"
          }
        },
        {
          "type": "array",
          "minItems": 3
        }
      ],
      "items": [
        {
          "type": "integer"
        }
      ]
    })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "2": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/3"
          }
        },
        "3": {},
        "4": {
          "type": "array",
          "minItems": 3,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/3"
          }
        },
        "5": {
          "type": [
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/9"
            },
            {
              "$ref": "#/definitions/11"
            },
            {
              "$ref": "#/definitions/12"
            }
          ]
        },
        "6": {
          "enum": [ null ]
        },
        "7": {
          "enum": [ false, true ]
        },
        "8": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "9": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": [
            {
              "$ref": "#/definitions/10"
            }
          ],
          "additionalItems": {
            "$ref": "#/definitions/3"
          }
        },
        "10": {
          "type": "integer",
          "divisibleBy": 1
        },
        "11": {
          "type": "string",
          "minLength": 0
        },
        "12": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_vacuous_additional_properties_still_distributes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "type": [
        {
          "type": "object",
          "properties": {
            "a": {
              "type": "integer"
            }
          }
        },
        {
          "type": "object",
          "patternProperties": {
            "^b": {
              "type": "integer"
            }
          }
        }
      ],
      "additionalProperties": {}
    })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "1": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": "integer",
          "divisibleBy": 1
        },
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^b": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_schema_variants_with_embedded_id_wrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "object", "patternProperties": { "^a": {} } },
      { "type": "object", "patternProperties": { "^b": {} } }
    ],
    "properties": {
      "foo": { "id": "https://example.com/dup", "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "2": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^a": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "3": {},
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^b": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "5": {
          "type": [
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/11"
            },
            {
              "$ref": "#/definitions/12"
            }
          ]
        },
        "6": {
          "enum": [ null ]
        },
        "7": {
          "enum": [ false, true ]
        },
        "8": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/9"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "9": {
          "type": "integer",
          "divisibleBy": 1
        },
        "10": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/3"
          }
        },
        "11": {
          "type": "string",
          "minLength": 0
        },
        "12": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_schema_variants_with_id_anchor_wrap) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "object", "patternProperties": { "^a": {} } },
      { "type": "object", "patternProperties": { "^b": {} } }
    ],
    "properties": {
      "foo": { "id": "#anchor", "type": "integer" },
      "bar": { "$ref": "#anchor" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "2": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^a": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "3": {},
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^b": {
              "$ref": "#/definitions/3"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "5": {
          "type": [
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/11"
            },
            {
              "$ref": "#/definitions/12"
            }
          ]
        },
        "6": {
          "enum": [ null ]
        },
        "7": {
          "enum": [ false, true ]
        },
        "8": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/9"
                }
              ],
              "required": false
            },
            "bar": {
              "$ref": "#/definitions/9"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/3"
          }
        },
        "9": {
          "type": "integer",
          "divisibleBy": 1
        },
        "10": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/3"
          }
        },
        "11": {
          "type": "string",
          "minLength": 0
        },
        "12": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_union_schema_variants_with_property_named_id_distributes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "object", "patternProperties": { "^a": {} } },
      { "type": "object", "patternProperties": { "^b": {} } }
    ],
    "properties": {
      "id": { "type": "integer" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "1": {
          "type": "object",
          "properties": {
            "id": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {
            "^a": {
              "$ref": "#/definitions/2"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": "integer",
          "divisibleBy": 1
        },
        "4": {
          "type": "object",
          "properties": {
            "id": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {
            "^b": {
              "$ref": "#/definitions/2"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_type_any_as_string_collapses) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "any"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_extends_with_any_type_branch_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [
      { "type": "any" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_extends_empty_object_erased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_extends_array_with_single_empty_erased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [ {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_extends_array_drops_empty_keeps_others) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      {},
      { "type": "string", "minLength": 5 }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 5
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(draft3_extends_array_all_empty_erased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [ {}, {} ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(additionalProperties_false) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": false
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": false
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(unnecessary_extends_ref_wrapper_array_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": {
      "extends": [ { "$ref": "#" } ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/0"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(unnecessary_extends_ref_wrapper_single_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": {
      "extends": { "$ref": "#" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/0"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(flatten_nested_extends_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [
      { "extends": [ { "type": "string" } ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(non_applicable_disallow_types_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": [ "number", "boolean" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_narrows_type_simple) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "number" ],
    "disallow": [ "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(ref_sibling_dropped_in_subschema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "bar": { "$ref": "#", "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "bar": {
              "$ref": "#/definitions/0"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(ref_metadata_siblings_kept) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "bar": {
        "$ref": "#",
        "title": "A ref",
        "description": "Refers to root"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "bar": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "title": "A ref",
          "description": "Refers to root",
          "$ref": "#/definitions/0"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(embedded_id_typed_property) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/embedded",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(embedded_id_self_recursive_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/embedded",
        "type": "object",
        "properties": {
          "bar": { "$ref": "#" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "bar": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(nested_embedded_ids) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/a",
    "type": "object",
    "properties": {
      "foo": {
        "id": "https://example.com/a/b",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(ref_into_embedded_resource_pointer) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "https://example.com/embedded",
        "type": "object",
        "properties": {
          "x": { "type": "string" }
        }
      },
      "b": { "$ref": "https://example.com/embedded#/properties/x" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(required_enum_property_preserves_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "enum": [ 1, 2 ], "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": true
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "enum": [ 1, 2 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(optional_enum_property_stays_compact) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "enum": [ 1, 2 ] }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "enum": [ 1, 2 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(required_boolean_property_preserves_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "boolean", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": true
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "enum": [ false, true ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(required_sibling_to_ref_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "$ref": "#", "required": true }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "$ref": "#/definitions/0"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(fragment_id_anchor_with_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "id": "#target", "type": "string" },
      "b": { "$ref": "#target" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_string_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_integer_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "integer",
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_boolean_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "enum": [ false, true ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_null_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "null"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_object_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_array_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_any_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "any"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_array_of_types) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "number" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_array_null_and_boolean) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "null", "boolean" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "enum": [ null ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "enum": [ false, true ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_schema_with_pattern) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "pattern": "^x" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "pattern": "^x",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_schema_with_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ 1, 2 ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "enum": [ 1, 2 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_schema_with_ref) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "$ref": "#" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/0"
            }
          ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_schema_with_minimum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "number", "minimum": 0 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "number",
          "minimum": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_schema_multiple_constraints) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "type": "string", "minLength": 3, "maxLength": 10 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "maxLength": 10,
          "minLength": 3
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_three_type_schemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "string" },
      { "type": "number" },
      { "type": "boolean" }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "number"
        },
        "5": {
          "disallow": [
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "6": {
          "enum": [ false, true ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_mixed_string_and_schema) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", { "type": "object" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/5"
          }
        },
        "5": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "disallow": [ { "type": "string" } ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_triple_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "disallow": [ { "disallow": [ { "type": "string" } ] } ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_quadruple_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "disallow": [
          { "disallow": [ { "disallow": [ { "type": "string" } ] } ] }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation_with_reference_into_subtree_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "disallow": [
              {
                "type": "object",
                "properties": {
                  "x": {
                    "type": "string"
                  }
                }
              }
            ]
          }
        ]
      },
      "b": {
        "$ref": "#/properties/a/disallow/0/disallow/0/properties/x"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation_eliminated_with_reference_out_of_subtree) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "type": "string"
      },
      "b": {
        "disallow": [
          {
            "disallow": [
              {
                "$ref": "#/properties/a"
              }
            ]
          }
        ]
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation_deep_with_reference_out_of_subtree) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "type": "string"
      },
      "b": {
        "disallow": [
          {
            "disallow": [
              {
                "disallow": [
                  {
                    "disallow": [
                      {
                        "type": "object",
                        "properties": {
                          "y": {
                            "$ref": "#/properties/a"
                          }
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
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "type": "object",
          "properties": {
            "y": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation_deep_with_reference_into_subtree_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "disallow": [
              {
                "disallow": [
                  {
                    "disallow": [
                      {
                        "type": "object",
                        "properties": {
                          "x": {
                            "type": "string"
                          }
                        }
                      }
                    ]
                  }
                ]
              }
            ]
          }
        ]
      },
      "b": {
        "$ref": "#/properties/a/disallow/0/disallow/0/disallow/0/disallow/0/properties/x"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation_over_type_union) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "disallow": [
          {
            "type": [
              "string",
              "number"
            ]
          }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "type": "string",
          "minLength": 0
        },
        "2": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_double_negation_over_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "disallow": [
          {
            "extends": [
              {
                "type": "number",
                "minimum": 1
              },
              {
                "type": "number",
                "maximum": 9
              }
            ]
          }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "type": "number",
          "minimum": 1
        },
        "2": {
          "type": "number",
          "maximum": 9
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_object_with_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      { "type": "object", "properties": { "a": { "type": "string" } } }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {},
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_number_single) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_number_with_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "number",
        "minimum": 0,
        "exclusiveMinimum": true,
        "maximum": 10
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "number",
          "maximum": 10,
          "exclusiveMinimum": true,
          "minimum": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_string_full_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "string",
        "minLength": 2,
        "maxLength": 5,
        "pattern": "^a",
        "format": "email"
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "pattern": "^a",
          "format": "email",
          "maxLength": 5,
          "minLength": 2
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_integer_with_bounds) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "integer",
        "minimum": 1,
        "maximum": 9,
        "divisibleBy": 3
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "integer",
          "maximum": 9,
          "minimum": 1,
          "divisibleBy": 3
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_array_tuple_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "array",
        "items": [
          {
            "type": "string"
          }
        ],
        "additionalItems": false
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": [
            {
              "$ref": "#/definitions/3"
            }
          ],
          "additionalItems": {
            "$ref": "#/definitions/2"
          }
        },
        "2": false,
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_array_with_max_and_unique) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": "array",
        "items": {
          "type": "string"
        },
        "minItems": 1,
        "maxItems": 3,
        "uniqueItems": true
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "array",
          "maxItems": 3,
          "minItems": 1,
          "uniqueItems": true,
          "items": {
            "$ref": "#/definitions/2"
          }
        },
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_wrapping_type_union) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "type": [
          "string",
          "number"
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_over_type_union_with_reference_into_subtree_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "type": [
              {
                "type": "object",
                "properties": {
                  "x": {
                    "type": "string"
                  }
                }
              },
              {
                "type": "object",
                "properties": {
                  "y": {
                    "type": "number"
                  }
                }
              }
            ]
          }
        ]
      },
      "b": {
        "$ref": "#/properties/a/disallow/0/type/1/properties/y"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/8"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "extends": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/5"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "5": {
          "type": "string",
          "minLength": 0
        },
        "6": {
          "disallow": [
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "7": {
          "type": "object",
          "properties": {
            "y": {
              "extends": [
                {
                  "$ref": "#/definitions/8"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "8": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_over_type_union_with_reference_to_wrapper_not_pushed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "type": [
              {
                "type": "object",
                "properties": {
                  "x": {
                    "type": "string"
                  }
                }
              },
              {
                "type": "object",
                "properties": {
                  "y": {
                    "type": "number"
                  }
                }
              }
            ]
          }
        ]
      },
      "b": {
        "$ref": "#/properties/a/disallow/0"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "type": [
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "4": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/5"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "5": {
          "type": "string",
          "minLength": 0
        },
        "6": {
          "type": "object",
          "properties": {
            "y": {
              "extends": [
                {
                  "$ref": "#/definitions/7"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_wrapping_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "extends": [
          {
            "type": "string",
            "minLength": 3
          },
          {
            "type": "string",
            "pattern": "^a"
          }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 3
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "string",
          "pattern": "^a",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_extends_single_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "extends": [
          {
            "type": "string",
            "minLength": 3
          }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 3
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_over_extends_with_reference_into_subtree_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "extends": [
              {
                "type": "object",
                "properties": {
                  "x": {
                    "type": "string"
                  }
                }
              },
              {
                "type": "object",
                "properties": {
                  "y": {
                    "type": "number"
                  }
                }
              }
            ]
          }
        ]
      },
      "b": {
        "$ref": "#/properties/a/disallow/0/extends/1/properties/y"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/8"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/5"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "5": {
          "type": "string",
          "minLength": 0
        },
        "6": {
          "disallow": [
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "7": {
          "type": "object",
          "properties": {
            "y": {
              "extends": [
                {
                  "$ref": "#/definitions/8"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "8": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_over_extends_with_reference_to_wrapper_not_pushed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "extends": [
              { "type": "object", "properties": { "x": { "type": "string" } } },
              { "type": "object", "properties": { "y": { "type": "number" } } }
            ]
          }
        ]
      },
      "b": { "$ref": "#/properties/a/disallow/0" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "extends": [
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "4": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/5"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "5": {
          "type": "string",
          "minLength": 0
        },
        "6": {
          "type": "object",
          "properties": {
            "y": {
              "extends": [
                {
                  "$ref": "#/definitions/7"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_in_pattern_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "patternProperties": {
      "^a": {
        "disallow": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {},
          "patternProperties": {
            "^a": {
              "$ref": "#/definitions/2"
            }
          },
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_in_additional_properties) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "additionalProperties": {
      "disallow": "string"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_in_array_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array",
    "items": {
      "disallow": "string"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_in_tuple_items_and_additional_items) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array",
    "items": [
      {
        "disallow": "string"
      }
    ],
    "additionalItems": {
      "disallow": "number"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": [
            {
              "$ref": "#/definitions/3"
            }
          ],
          "additionalItems": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "number"
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_in_extends_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "extends": [
      {
        "disallow": "number"
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "number"
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_in_type_union_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      {
        "type": "string"
      },
      {
        "disallow": "number"
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "type": "string",
          "minLength": 0
        },
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_multiple_in_property_splits) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          "string",
          "number"
        ]
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "extends": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "string",
          "minLength": 0
        },
        "5": {
          "disallow": [
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "6": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_duplicate_entries) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_duplicate_string_and_schema_form) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", { "type": "string" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_duplicate_with_distinct_entry_between) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ "string", "number", "string" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_duplicate_with_reference_into_array_not_compacted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "disallow": [ { "enum": [ 1, 2 ] }, { "enum": [ 1, 2 ] } ] },
      "b": { "$ref": "#/properties/a/disallow/1" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "enum": [ 1, 2 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_duplicate_with_reference_into_middle_entry_not_aliased) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          { "enum": [ 1 ] },
          { "enum": [ 2 ] },
          { "enum": [ 2 ] },
          { "enum": [ 3 ] }
        ]
      },
      "b": { "$ref": "#/properties/a/disallow/2" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/6"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "extends": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "enum": [ 1 ]
        },
        "5": {
          "disallow": [
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "6": {
          "enum": [ 2 ]
        },
        "7": {
          "disallow": [
            {
              "$ref": "#/definitions/8"
            }
          ]
        },
        "8": {
          "enum": [ 3 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_string_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "enum": [ "a", "b" ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {
          "enum": [ "a", "b" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_ref_and_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "$ref": "#" }, { "enum": [ 1 ] } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/0"
            }
          ]
        },
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "enum": [ 1 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_string_disallow_non_overlapping) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": "number"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_string_disallow_overlapping) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_union_disallow_schema_form_narrows) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "string", "number" ],
    "disallow": [ { "type": "string" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_with_disallow) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 1, 2 ],
    "disallow": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 0
        },
        "3": {
          "enum": [ 1, 2 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_with_typeless_disallow_distributes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "disallow": [ { "pattern": "^x" } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/12"
            },
            {
              "$ref": "#/definitions/14"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "enum": [ null ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "enum": [ false, true ]
        },
        "5": {
          "disallow": [
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "6": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/7"
          }
        },
        "7": {},
        "8": {
          "disallow": [
            {
              "$ref": "#/definitions/9"
            }
          ]
        },
        "9": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/7"
          }
        },
        "10": {
          "disallow": [
            {
              "$ref": "#/definitions/11"
            }
          ]
        },
        "11": {
          "type": "string",
          "pattern": "^x",
          "minLength": 0
        },
        "12": {
          "disallow": [
            {
              "$ref": "#/definitions/13"
            }
          ]
        },
        "13": {
          "type": "number"
        },
        "14": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_typeless_scalar_distributes) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [ { "minLength": 3 } ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/12"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "enum": [ null ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "enum": [ false, true ]
        },
        "5": {
          "disallow": [
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "6": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/7"
          }
        },
        "7": {},
        "8": {
          "disallow": [
            {
              "$ref": "#/definitions/9"
            }
          ]
        },
        "9": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/7"
          }
        },
        "10": {
          "disallow": [
            {
              "$ref": "#/definitions/11"
            }
          ]
        },
        "11": {
          "type": "string",
          "minLength": 3
        },
        "12": {
          "disallow": [
            {
              "$ref": "#/definitions/13"
            }
          ]
        },
        "13": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(typeless_pattern_distributes_to_string_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "pattern": "^x"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "pattern": "^x",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(typeless_minimum_distributes_to_number_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "minimum": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number",
          "minimum": 5
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(typeless_max_items_distributes_to_array_branch) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "maxItems": 4
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "maxItems": 4,
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(type_union_conflicting_sibling_wraps_in_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [
      { "type": "string", "minLength": 1 },
      { "type": "string" }
    ],
    "minLength": 3
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "2": {
          "type": "string",
          "minLength": 1
        },
        "3": {
          "type": "string",
          "minLength": 0
        },
        "4": {
          "type": [
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/9"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/11"
            }
          ]
        },
        "5": {
          "enum": [ null ]
        },
        "6": {
          "enum": [ false, true ]
        },
        "7": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/8"
          }
        },
        "8": {},
        "9": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/8"
          }
        },
        "10": {
          "type": "string",
          "minLength": 3
        },
        "11": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_empty_array_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": []
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            }
          ]
        },
        "1": {
          "enum": [ null ]
        },
        "2": {
          "enum": [ false, true ]
        },
        "3": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/4"
          }
        },
        "4": {},
        "5": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/4"
          }
        },
        "6": {
          "type": "string",
          "minLength": 0
        },
        "7": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_property_keeps_required) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "disallow": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(ref_through_wrapped_property_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "object", "properties": { "x": { "type": "string" } } },
      "b": { "$ref": "#/properties/a/properties/x" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(required_to_extends_preserves_existing_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "extends": [ { "type": "string" } ], "minLength": 3 }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "extends": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "3": {
          "type": "string",
          "minLength": 0
        },
        "4": {
          "type": [
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/9"
            },
            {
              "$ref": "#/definitions/10"
            }
          ]
        },
        "5": {
          "enum": [ null ]
        },
        "6": {
          "enum": [ false, true ]
        },
        "7": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "8": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/1"
          }
        },
        "9": {
          "type": "string",
          "minLength": 3
        },
        "10": {
          "type": "number"
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(ref_into_disallow_element_rereferenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          { "type": "string" },
          { "type": "object", "properties": { "x": { "type": "string" } } }
        ]
      },
      "b": { "$ref": "#/properties/a/disallow/1/properties/x" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/4"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "extends": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "type": "string",
          "minLength": 0
        },
        "5": {
          "disallow": [
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "6": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/4"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(disallow_split_preserves_existing_extends) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [ { "type": "number" } ],
    "disallow": [
      { "type": "string", "minLength": 0 },
      { "enum": [ 1 ] }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "1": {
          "type": "number"
        },
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "type": "string",
          "minLength": 0
        },
        "4": {
          "disallow": [
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "5": {
          "enum": [ 1 ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_mixed_into_type_union) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [
      1,
      "a",
      null
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "enum": [ 1 ]
        },
        "2": {
          "enum": [ "a" ]
        },
        "3": {
          "enum": [ null ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_all_kinds_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [
      "s",
      1,
      true,
      null,
      {
        "k": 1
      },
      [
        1
      ]
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "1": {
          "enum": [ "s" ]
        },
        "2": {
          "enum": [ 1 ]
        },
        "3": {
          "enum": [ true ]
        },
        "4": {
          "enum": [ null ]
        },
        "5": {
          "enum": [
            {
              "k": 1
            }
          ]
        },
        "6": {
          "enum": [
            [ 1 ]
          ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_single_kind_unchanged_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [
      "a",
      "b"
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "enum": [ "a", "b" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_folds_integer_and_real_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [
      1,
      2.5,
      "a"
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "enum": [ 1, 2.5 ]
        },
        "2": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_under_disallow) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "enum": [
          1,
          "a"
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "1": {
          "disallow": [
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "2": {
          "enum": [ 1 ]
        },
        "3": {
          "disallow": [
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "4": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_in_property_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "enum": [
          1,
          "a"
        ]
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "3": {
          "enum": [ 1 ]
        },
        "4": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_in_items_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "array",
    "items": {
      "enum": [
        1,
        "a"
      ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "2": {
          "enum": [ 1 ]
        },
        "3": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_with_id_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/x",
    "enum": [
      1,
      "a"
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "enum": [ 1 ]
        },
        "2": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_with_id_anchor_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "#foo",
        "enum": [
          1,
          "a"
        ]
      },
      "b": {
        "$ref": "#foo"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "3": {
          "enum": [ 1 ]
        },
        "4": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_with_reference_to_node_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "enum": [
          1,
          "a"
        ]
      },
      "b": {
        "$ref": "#/properties/a"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "3": {
          "enum": [ 1 ]
        },
        "4": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_under_disallow_ref_into_node) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "disallow": [
          {
            "enum": [
              1,
              "a"
            ]
          }
        ]
      },
      "b": {
        "$ref": "#/properties/a/disallow/0"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "disallow": [
            {
              "$ref": "#/definitions/3"
            }
          ]
        },
        "3": {
          "type": [
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/5"
            }
          ]
        },
        "4": {
          "enum": [ 1 ]
        },
        "5": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_under_double_negation) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": [
      {
        "disallow": [
          {
            "enum": [
              1,
              "a"
            ]
          }
        ]
      }
    ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/2"
            }
          ]
        },
        "1": {
          "enum": [ 1 ]
        },
        "2": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_id_anchor_referenced_twice) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "#foo",
        "enum": [
          1,
          "a"
        ]
      },
      "b": {
        "$ref": "#foo"
      },
      "c": {
        "$ref": "#foo"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/2"
            },
            "c": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "3": {
          "enum": [ 1 ]
        },
        "4": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_id_uri_referenced) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "id": "https://e.com/x",
        "enum": [
          1,
          "a"
        ]
      },
      "b": {
        "$ref": "https://e.com/x"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            }
          ]
        },
        "3": {
          "enum": [ 1 ]
        },
        "4": {
          "enum": [ "a" ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(enum_split_deeply_nested_referenced_d3) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "type": "object",
        "properties": {
          "deep": {
            "enum": [
              1,
              "a",
              null
            ]
          }
        }
      },
      "b": {
        "$ref": "#/properties/a/properties/deep"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/3"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "deep": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": [
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            }
          ]
        },
        "4": {
          "enum": [ 1 ]
        },
        "5": {
          "enum": [ "a" ]
        },
        "6": {
          "enum": [ null ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(empty_dependencies_drop) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "dependencies": {},
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(unsatisfiable_empty_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": []
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "disallow": [
            {
              "$ref": "#/definitions/1"
            }
          ]
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(definitions_preserved_on_a_leaf) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "definitions": { "x": { "type": "string" } }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "integer",
          "divisibleBy": 1
        },
        "1": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(definitions_with_identifier_and_reference) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/root",
    "definitions": { "x": { "id": "https://example.com/x", "type": "integer" } },
    "properties": { "r": { "$ref": "https://example.com/x" } },
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "r": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "integer",
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(required_survives_applicator_rewrite) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": {
        "extends": [ { "minLength": 2 } ],
        "type": "string",
        "required": true
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "foo": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": true
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "extends": [
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/10"
            }
          ]
        },
        "3": {
          "type": [
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/5"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            },
            {
              "$ref": "#/definitions/9"
            }
          ]
        },
        "4": {
          "enum": [ null ]
        },
        "5": {
          "enum": [ false, true ]
        },
        "6": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "7": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/1"
          }
        },
        "8": {
          "type": "string",
          "minLength": 2
        },
        "9": {
          "type": "number"
        },
        "10": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(assertion_beside_extends_is_wrapped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [ { "minLength": 1 } ],
    "maxLength": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "extends": [
            {
              "$ref": "#/definitions/1"
            },
            {
              "$ref": "#/definitions/9"
            }
          ]
        },
        "1": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/7"
            },
            {
              "$ref": "#/definitions/8"
            }
          ]
        },
        "2": {
          "enum": [ null ]
        },
        "3": {
          "enum": [ false, true ]
        },
        "4": {
          "type": "object",
          "properties": {},
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/5"
          }
        },
        "5": {},
        "6": {
          "type": "array",
          "minItems": 0,
          "uniqueItems": false,
          "items": {
            "$ref": "#/definitions/5"
          }
        },
        "7": {
          "type": "string",
          "minLength": 1
        },
        "8": {
          "type": "number"
        },
        "9": {
          "type": [
            {
              "$ref": "#/definitions/2"
            },
            {
              "$ref": "#/definitions/3"
            },
            {
              "$ref": "#/definitions/4"
            },
            {
              "$ref": "#/definitions/6"
            },
            {
              "$ref": "#/definitions/10"
            },
            {
              "$ref": "#/definitions/8"
            }
          ]
        },
        "10": {
          "type": "string",
          "maxLength": 5,
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(external_reference_made_absolute_when_root_id_removed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "id": "https://example.com/dir/root.json",
    "type": "object",
    "properties": {
      "a": { "$ref": "other.json" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "$ref": "https://example.com/dir/other.json"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_shares_identical_subschemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "string", "maxLength": 5 },
      "b": { "type": "string", "maxLength": 5 }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "maxLength": 5,
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_shares_a_subschema_across_keywords) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "integer" }
    },
    "additionalProperties": { "type": "integer" }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/1"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {
          "type": "integer",
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_shares_recursive_subschemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "type": "object",
        "properties": { "next": { "$ref": "#/properties/a" } }
      },
      "b": {
        "type": "object",
        "properties": { "next": { "$ref": "#/properties/b" } }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "next": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_keeps_subschemas_that_differ_deeply_apart) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "type": "object",
        "properties": {
          "x": {
            "type": "object",
            "properties": { "y": { "type": "string" } }
          }
        }
      },
      "b": {
        "type": "object",
        "properties": {
          "x": {
            "type": "object",
            "properties": { "y": { "type": "integer" } }
          }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/5"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": "object",
          "properties": {
            "y": {
              "extends": [
                {
                  "$ref": "#/definitions/4"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "4": {
          "type": "string",
          "minLength": 0
        },
        "5": {
          "type": "object",
          "properties": {
            "x": {
              "extends": [
                {
                  "$ref": "#/definitions/6"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "6": {
          "type": "object",
          "properties": {
            "y": {
              "extends": [
                {
                  "$ref": "#/definitions/7"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "7": {
          "type": "integer",
          "divisibleBy": 1
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_keeps_a_reference_to_a_shared_entry) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "type": "string" },
      "b": { "$ref": "#/properties/a" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "$ref": "#/definitions/2"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_keeps_a_reference_out_of_the_document) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "$ref": "https://example.com/other.json" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "$ref": "https://example.com/other.json"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_of_a_graph_form_document_is_itself) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "extends": [ { "$ref": "#/definitions/0" } ],
    "definitions": {
      "0": {
        "type": "object",
        "properties": {
          "a": {
            "extends": [ { "$ref": "#/definitions/2" } ],
            "required": false
          },
          "b": {
            "extends": [ { "$ref": "#/definitions/2" } ],
            "required": false
          }
        },
        "patternProperties": {},
        "additionalProperties": { "$ref": "#/definitions/1" }
      },
      "1": {},
      "2": { "type": "string", "maxLength": 5, "minLength": 0 }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "string",
          "maxLength": 5,
          "minLength": 0
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_leaves_hyper_schema_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/hyper-schema#",
    "type": "object",
    "links": [
      { "rel": "full", "href": "{id}", "targetSchema": { "type": "string" } }
    ],
    "properties": { "a": { "type": "string" } }
  })JSON");

  // A `links` entry describes a link rather than a subschema, so lifting one
  // into `definitions` and referring to it would say something this document
  // never said. Graph form is the form `canonical-draft3.json` describes, and
  // that is Draft 3 proper, so hyper-schema keeps its nesting
  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/hyper-schema#",
      "type": "object",
      "properties": {
        "a": {
          "type": "string"
        }
      },
      "links": [
        {
          "href": "{id}",
          "rel": "full",
          "targetSchema": {
            "type": "string"
          }
        }
      ]
    })JSON");

  sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  EXPECT_EQ(document, expected);

  auto again{document};
  sourcemeta::blaze::canonicalize(again, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  EXPECT_EQ(again, document);
}

TEST(graph_form_leaves_a_reference_shaped_enum_value_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "enum": [ { "$ref": "#/definitions/999" } ] }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "enum": [
            {
              "$ref": "#/definitions/999"
            }
          ]
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_keeps_entries_that_reference_different_documents_apart) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": {
        "type": "object",
        "properties": { "z": { "$ref": "https://example.com/x.json" } }
      },
      "b": {
        "type": "object",
        "properties": { "z": { "$ref": "https://example.com/y.json" } }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "extends": [
                {
                  "$ref": "#/definitions/2"
                }
              ],
              "required": false
            },
            "b": {
              "extends": [
                {
                  "$ref": "#/definitions/3"
                }
              ],
              "required": false
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {},
        "2": {
          "type": "object",
          "properties": {
            "z": {
              "$ref": "https://example.com/x.json"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "3": {
          "type": "object",
          "properties": {
            "z": {
              "$ref": "https://example.com/y.json"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        }
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_follows_a_reference_out_of_the_document) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "$ref": "https://example.com/other.json" },
      "b": { "$ref": "#/properties/a" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "extends": [
        {
          "$ref": "#/definitions/0"
        }
      ],
      "definitions": {
        "0": {
          "type": "object",
          "properties": {
            "a": {
              "$ref": "https://example.com/other.json"
            },
            "b": {
              "$ref": "https://example.com/other.json"
            }
          },
          "patternProperties": {},
          "additionalProperties": {
            "$ref": "#/definitions/1"
          }
        },
        "1": {}
      }
    })JSON");

  CANONICALIZE_AND_VALIDATE(document, expected, compiled_metaschema());
}

TEST(graph_form_declines_a_reference_cycle_that_says_nothing) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "a": { "$ref": "#/definitions/b" },
      "b": { "$ref": "#/definitions/a" }
    },
    "type": "object",
    "properties": {
      "x": { "$ref": "#/definitions/a" }
    }
  })JSON");

  // Following the references never reaches a subschema that says
  // anything, so there is no entry for the incoming reference to point
  // at. Leaving the document alone keeps it meaning what it did, which
  // the graph-form meta-schema then does not describe
  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "type": "object",
      "properties": {
        "x": {
          "$ref": "#/definitions/a"
        }
      },
      "patternProperties": {},
      "additionalProperties": {},
      "definitions": {
        "a": {
          "$ref": "#/definitions/b"
        },
        "b": {
          "$ref": "#/definitions/a"
        }
      }
    })JSON");

  sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  EXPECT_EQ(document, expected);
}
