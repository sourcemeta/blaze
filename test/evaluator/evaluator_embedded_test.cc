#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <string_view> // std::string_view

#include "evaluator_utils.h"

static auto test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://example.com/pet.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/pet.json",
      "type": "string"
    })JSON");
  }

  return sourcemeta::core::schema_resolver(identifier);
}

static auto compile_embedded(const sourcemeta::core::JSON &document,
                             const sourcemeta::core::SchemaFrame::Paths &paths,
                             const std::string_view entrypoint,
                             const sourcemeta::blaze::Mode mode)
    -> sourcemeta::blaze::Template {
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      document,
      sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://spec.openapis.org/oas/3.1/dialect/base",
      "",
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,
      paths,
      "https://example.com/openapi.json"};
  return sourcemeta::blaze::compile(document, sourcemeta::core::schema_walker,
                                    sourcemeta::core::schema_resolver,
                                    sourcemeta::blaze::default_schema_compiler,
                                    frame, entrypoint, mode);
}

TEST(entrypoint_at_embedded_root_success) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" },
        "Order": { "type": "integer" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(entrypoint_at_embedded_root_failure) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" },
        "Order": { "type": "integer" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{1};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(entrypoint_at_embedded_subschema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "properties": {
            "name": { "type": "string" }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet/properties/"
      "name",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type",
                     "https://example.com/openapi.json#/components/schemas/"
                     "Pet/properties/name/type",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/properties/"
      "name/type",
      "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(reference_to_embedded_sibling_by_pointer) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" },
        "Order": { "$ref": "#/components/schemas/Pet" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(reference_to_embedded_sibling_by_identifier) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$id": "pet", "type": "string" },
        "Order": { "$ref": "pet" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "https://example.com/pet#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "https://example.com/pet#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(entrypoint_at_embedded_shell) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};

  try {
    [[maybe_unused]] const auto schema_template{
        compile_embedded(document, {sourcemeta::core::to_weak_pointer(pet)},
                         "https://example.com/openapi.json#/info",
                         sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/openapi.json#/info");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI is not a valid subschema");
  }
}

TEST(entrypoint_at_embedded_missing_location) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "type": "string" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};

  try {
    [[maybe_unused]] const auto schema_template{compile_embedded(
        document, {sourcemeta::core::to_weak_pointer(pet)},
        "https://example.com/openapi.json#/components/schemas/Missing",
        sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidEntryPoint &error) {
    EXPECT_EQ(error.identifier(),
              "https://example.com/openapi.json#/components/schemas/Missing");
    EXPECT_STREQ(error.what(),
                 "The given entry point URI does not exist in the schema");
  }
}

TEST(reference_from_embedded_schema_into_shell) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$ref": "#/info" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};

  try {
    [[maybe_unused]] const auto schema_template{compile_embedded(
        document, {sourcemeta::core::to_weak_pointer(pet)},
        "https://example.com/openapi.json#/components/schemas/Pet",
        sourcemeta::blaze::Mode::FastValidation)};
    FAIL();
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "The referenced schema is not considered to be a valid "
                 "subschema given the dialect and vocabularies in use");
    EXPECT_EQ(error.identifier(), "https://example.com/openapi.json#/info");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer(
                                    {"components", "schemas", "Pet", "$ref"}));
  }
}

TEST(reference_to_embedded_sibling_by_anchor) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$anchor": "pet", "type": "string" },
        "Order": { "$ref": "#pet" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(reference_to_embedded_sibling_subschema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "properties": {
            "name": { "type": "string" }
          }
        },
        "Order": { "$ref": "#/components/schemas/Pet/properties/name" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(order)},
      "https://example.com/openapi.json#/components/schemas/Order",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "https://example.com/openapi.json#/components/schemas/"
                     "Pet/properties/name/type",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "https://example.com/openapi.json#/components/"
                              "schemas/Pet/properties/name/type",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(entrypoint_at_embedded_false_schema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": false
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_FALSE(result);

  EVALUATE_TRACE_PRE(0, AssertionFail, "",
                     "https://example.com/openapi.json#/components/schemas/Pet",
                     "");
  EVALUATE_TRACE_POST_FAILURE(
      0, AssertionFail, "",
      "https://example.com/openapi.json#/components/schemas/Pet", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "No instance is expected to succeed against the false schema");
}

TEST(entrypoint_at_embedded_true_schema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": true
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 0);
  EXPECT_TRUE(result);
}

TEST(dynamic_reference_within_embedded_schema) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "$dynamicRef": "https://example.com/target#meta",
          "$defs": {
            "target": {
              "$id": "https://example.com/target",
              "$dynamicAnchor": "meta",
              "type": "boolean"
            },
            "other": {
              "$id": "https://example.com/other",
              "$dynamicAnchor": "meta",
              "type": "number"
            }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{true};
  EVALUATE_WITH_TRACE(schema_template, instance, 2);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, ControlDynamicAnchorJump, "/$dynamicRef",
      "https://example.com/openapi.json#/components/schemas/Pet/$dynamicRef",
      "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/$dynamicRef/type",
                     "https://example.com/target#/type", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$dynamicRef/type",
                              "https://example.com/target#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, ControlDynamicAnchorJump, "/$dynamicRef",
      "https://example.com/openapi.json#/components/schemas/Pet/$dynamicRef",
      "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type boolean");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The boolean value was expected to validate against the first subschema "
      "in scope that declared the dynamic anchor \"meta\"");
}

TEST(embedded_schema_declaring_its_own_dialect) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "$schema": "http://json-schema.org/draft-07/schema#",
          "type": "string"
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}

TEST(embedded_schema_with_default_dialect_vocabulary_keyword) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "type": "object",
          "discriminator": { "propertyName": "kind" }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document, {sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::Exhaustive)};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::make_object()};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
}

TEST(unevaluated_properties_through_reference_to_embedded_sibling) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Base": {
          "type": "object",
          "properties": { "shared": true }
        },
        "Pet": {
          "type": "object",
          "allOf": [ { "$ref": "#/components/schemas/Base" } ],
          "properties": { "local": true },
          "unevaluatedProperties": false
        }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer base{"components", "schemas", "Base"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const auto schema_template{compile_embedded(
      document,
      {sourcemeta::core::to_weak_pointer(base),
       sourcemeta::core::to_weak_pointer(pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "shared": 1 })JSON")};
  EVALUATE_WITH_TRACE(schema_template, instance, 3);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(
      0, AssertionTypeStrict, "/allOf/0/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Base/type", "");
  EVALUATE_TRACE_PRE(
      1, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_PRE(2, LoopPropertiesExcept, "/unevaluatedProperties",
                     "https://example.com/openapi.json#/components/schemas/"
                     "Pet/unevaluatedProperties",
                     "");

  EVALUATE_TRACE_POST_SUCCESS(
      0, AssertionTypeStrict, "/allOf/0/$ref/type",
      "https://example.com/openapi.json#/components/schemas/Base/type", "");
  EVALUATE_TRACE_POST_SUCCESS(
      1, AssertionTypeStrict, "/type",
      "https://example.com/openapi.json#/components/schemas/Pet/type", "");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopPropertiesExcept, "/unevaluatedProperties",
                              "https://example.com/openapi.json#/components/"
                              "schemas/Pet/unevaluatedProperties",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type object");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 2,
      "The object value was not expected to define unevaluated properties");
}

TEST(entrypoint_at_embedded_root_with_bundled_external_reference) {
  const sourcemeta::core::JSON document{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$ref": "pet.json" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  sourcemeta::core::SchemaBundleOptions options;
  options.mode = sourcemeta::core::SchemaBundleOptions::Mode::References;
  options.default_container = sourcemeta::core::Pointer{"x-bundled"};
  options.paths = {sourcemeta::core::to_weak_pointer(pet)};
  options.default_base = "https://example.com/openapi.json";
  const sourcemeta::core::JSON bundled{sourcemeta::core::schema_bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      "https://spec.openapis.org/oas/3.1/dialect/base", "", options)};

  const sourcemeta::core::JSON expected{sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": { "$ref": "pet.json" }
      }
    },
    "x-bundled": {
      "https://example.com/pet.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/pet.json",
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(bundled, expected);

  const sourcemeta::core::Pointer bundled_pet{"x-bundled",
                                              "https://example.com/pet.json"};
  const auto schema_template{compile_embedded(
      bundled,
      {sourcemeta::core::to_weak_pointer(pet),
       sourcemeta::core::to_weak_pointer(bundled_pet)},
      "https://example.com/openapi.json#/components/schemas/Pet",
      sourcemeta::blaze::Mode::FastValidation)};

  const sourcemeta::core::JSON instance{"foo"};
  EVALUATE_WITH_TRACE(schema_template, instance, 1);
  EXPECT_TRUE(result);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/$ref/type",
                     "https://example.com/pet.json#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/$ref/type",
                              "https://example.com/pet.json#/type", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type string");
}
