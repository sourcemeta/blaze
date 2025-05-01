#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_openapi_3_1, request_body_1) {
  const sourcemeta::core::JSON openapi{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.0",
    "info": {
      "title": "Sample API",
      "version": "1.0.0"
    },
    "paths": {
      "/users": {
        "post": {
          "summary": "Create a new user",
          "requestBody": {
            "required": true,
            "content": {
              "application/json": {
                "schema": {
                  "$ref": "#/components/schemas/User"
                }
              }
            }
          },
          "responses": {
            "201": {
              "description": "User created"
            },
            "400": {
              "description": "Invalid input"
            }
          }
        }
      }
    },
    "components": {
      "schemas": {
        "User": {
          "type": "object",
          "required": ["name", "email"],
          "properties": {
            "name": {
              "type": "string"
            },
            "email": {
              "type": "string",
              "format": "email"
            },
            "age": {
              "type": "integer",
              "minimum": 0
            }
          }
        }
      }
    }
  })JSON")};

  const std::string dialect{"https://json-schema.org/draft/2020-12/schema"};
  const sourcemeta::core::Pointer schema{
      "paths",   "/users",           "post",  "requestBody",
      "content", "application/json", "schema"};
  const sourcemeta::core::Pointer container{"components", "schemas"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      schema, sourcemeta::core::Pointer{"components", "schemas", "User"}};

  // TODO: Abstract the details here behind a new overload to compile()
  // that is meant to work on schema wrappers, taking a set of paths
  // as arguments, and the pointer to the specific path to take as the entry
  // point

  const sourcemeta::core::JSON result{sourcemeta::core::bundle(
      openapi, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, dialect, container, paths)};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(result, sourcemeta::core::schema_official_walker,
                sourcemeta::core::schema_official_resolver, dialect,
                std::nullopt, paths);

  const auto compiled_schema{sourcemeta::blaze::compile(
      sourcemeta::core::get(result, schema),
      sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler, frame,
      sourcemeta::blaze::Mode::FastValidation, dialect)};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "name": "John Doe",
    "email": "johndoe@example.com",
    "age": 55
  })JSON")};

  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_TRUE(evaluator.validate(compiled_schema, instance));

  // TODO: Assert on the traces
}
