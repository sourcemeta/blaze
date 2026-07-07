#include <sourcemeta/core/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonld.h>
#include <sourcemeta/core/jsonpointer.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/blaze/foundation.h>

#include <unordered_set> // std::unordered_set
#include <variant>       // std::get, std::holds_alternative

#define JSON_LD_EVALUATE_SET(schema, instance, annotation_set)                 \
  sourcemeta::blaze::Tweaks tweaks;                                            \
  tweaks.annotations = (annotation_set);                                       \
  const auto schema_template{sourcemeta::blaze::compile(                       \
      (schema), sourcemeta::blaze::schema_walker,                              \
      sourcemeta::blaze::schema_resolver,                                      \
      sourcemeta::blaze::default_schema_compiler,                              \
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};           \
  sourcemeta::blaze::Evaluator evaluator;                                      \
  const auto outcome{                                                          \
      sourcemeta::blaze::jsonld(evaluator, schema_template, (instance))};

#define JSON_LD_EVALUATE(schema, instance)                                     \
  JSON_LD_EVALUATE_SET(                                                        \
      schema, instance,                                                        \
      (std::unordered_set<sourcemeta::core::JSON::StringView>(                 \
          sourcemeta::blaze::JSONLD_KEYWORDS.begin(),                          \
          sourcemeta::blaze::JSONLD_KEYWORDS.end())))

#define JSON_LD_EVALUATE_WITH(schema, instance, ...)                           \
  JSON_LD_EVALUATE_SET(                                                        \
      schema, instance,                                                        \
      (std::unordered_set<sourcemeta::core::JSON::StringView>{__VA_ARGS__}))

#define EXPECT_JSON_LD_VALUE_WITH(schema, instance, expected, ...)             \
  {                                                                            \
    JSON_LD_EVALUATE_WITH(schema, instance, __VA_ARGS__)                       \
    EXPECT_TRUE(std::holds_alternative<sourcemeta::core::JSON>(outcome));      \
    const auto &document{std::get<sourcemeta::core::JSON>(outcome)};           \
    EXPECT_EQ(document, (expected));                                           \
    EXPECT_TRUE(sourcemeta::core::jsonld_is_expanded(document));               \
  }

#define EXPECT_JSON_LD_VALUE(schema, instance, expected)                       \
  {                                                                            \
    JSON_LD_EVALUATE(schema, instance)                                         \
    EXPECT_TRUE(std::holds_alternative<sourcemeta::core::JSON>(outcome));      \
    const auto &document{std::get<sourcemeta::core::JSON>(outcome)};           \
    EXPECT_EQ(document, (expected));                                           \
    EXPECT_TRUE(sourcemeta::core::jsonld_is_expanded(document));               \
  }

#define EXPECT_JSON_LD_INVALID(schema, instance, destination)                  \
  JSON_LD_EVALUATE(schema, instance)                                           \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::JSONLDInvalid>(outcome));      \
  const auto &destination{std::get<sourcemeta::blaze::JSONLDInvalid>(outcome)};

#define EXPECT_JSON_LD_ERROR(errors, index, expected_instance_location,        \
                             expected_evaluate_path, expected_schema_location, \
                             expected_message)                                 \
  EXPECT_TRUE((index) < (errors).size());                                      \
  EXPECT_EQ((errors).at(index).message, (expected_message));                   \
  EXPECT_EQ(sourcemeta::core::to_string((errors).at(index).instance_location), \
            (expected_instance_location));                                     \
  EXPECT_EQ(sourcemeta::core::to_string((errors).at(index).evaluate_path),     \
            (expected_evaluate_path));                                         \
  EXPECT_EQ((errors).at(index).schema_location.get(),                          \
            (expected_schema_location));

#define EXPECT_JSON_LD_RESOLUTION_ERROR(schema, instance,                      \
                                        expected_instance_location,            \
                                        expected_facet, expected_message)      \
  {                                                                            \
    JSON_LD_EVALUATE(schema, instance)                                         \
    EXPECT_TRUE(                                                               \
        std::holds_alternative<sourcemeta::blaze::JSONLDResolutionError>(      \
            outcome));                                                         \
    const auto &error{                                                         \
        std::get<sourcemeta::blaze::JSONLDResolutionError>(outcome)};          \
    EXPECT_EQ(sourcemeta::core::to_string(error.instance_location),            \
              (expected_instance_location));                                   \
    EXPECT_EQ(error.facet, (expected_facet));                                  \
    EXPECT_EQ(error.message, (expected_message));                              \
  }

TEST(JSONLD_node_type_and_property_ids) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": "https://schema.org/Person",
    "properties": {
      "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" },
      "email": { "type": "string", "x-jsonld-id": "https://schema.org/email" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "name": "Ada", "email": "ada@example.com" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Person" ],
      "https://schema.org/email": [ { "@value": "ada@example.com" } ],
      "https://schema.org/name": [ { "@value": "Ada" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_multiple_types_via_array) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": [
      "https://schema.org/Person",
      "https://schema.org/Agent"
    ],
    "properties": {
      "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Agent", "https://schema.org/Person" ],
      "https://schema.org/name": [ { "@value": "Ada" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_types_merge_via_allof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "allOf": [
      { "x-jsonld-type": "https://schema.org/Person" },
      { "x-jsonld-type": "https://schema.org/Agent" }
    ],
    "properties": {
      "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Agent", "https://schema.org/Person" ],
      "https://schema.org/name": [ { "@value": "Ada" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_types_dedup_via_ref_diamond) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "agent": { "x-jsonld-type": "https://schema.org/Agent" },
      "person": {
        "allOf": [ { "$ref": "#/$defs/agent" } ],
        "x-jsonld-type": "https://schema.org/Person"
      }
    },
    "type": "object",
    "allOf": [ { "$ref": "#/$defs/agent" }, { "$ref": "#/$defs/person" } ]
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Agent", "https://schema.org/Person" ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_type_inherited_through_ref) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "person": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Person",
        "properties": {
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
        }
      }
    },
    "type": "object",
    "properties": {
      "author": {
        "$ref": "#/$defs/person",
        "x-jsonld-id": "https://schema.org/author"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "author": { "name": "Ada" } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/author": [
        {
          "@type": [ "https://schema.org/Person" ],
          "https://schema.org/name": [ { "@value": "Ada" } ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_recursive_ref) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "node": {
        "type": "object",
        "x-jsonld-type": "https://example.com/Node",
        "properties": {
          "value": {
            "type": "string",
            "x-jsonld-id": "https://example.com/value"
          },
          "next": {
            "$ref": "#/$defs/node",
            "x-jsonld-id": "https://example.com/next"
          }
        }
      }
    },
    "$ref": "#/$defs/node"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "value": "a",
    "next": { "value": "b", "next": { "value": "c" } }
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://example.com/Node" ],
      "https://example.com/next": [
        {
          "@type": [ "https://example.com/Node" ],
          "https://example.com/next": [
            {
              "@type": [ "https://example.com/Node" ],
              "https://example.com/value": [ { "@value": "c" } ]
            }
          ],
          "https://example.com/value": [ { "@value": "b" } ]
        }
      ],
      "https://example.com/value": [ { "@value": "a" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_array_of_nodes) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "friends": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/knows",
        "items": {
          "type": "object",
          "x-jsonld-type": "https://schema.org/Person",
          "properties": {
            "name": {
              "type": "string",
              "x-jsonld-id": "https://schema.org/name"
            }
          }
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "friends": [ { "name": "Ada" }, { "name": "Bob" } ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/knows": [
        {
          "@type": [ "https://schema.org/Person" ],
          "https://schema.org/name": [ { "@value": "Ada" } ]
        },
        {
          "@type": [ "https://schema.org/Person" ],
          "https://schema.org/name": [ { "@value": "Bob" } ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_conditional_then_branch) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "identifier": {
        "if": { "type": "string" },
        "then": { "x-jsonld-id": "https://schema.org/name" },
        "else": { "x-jsonld-id": "https://schema.org/identifier" }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "identifier": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_conditional_else_branch) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "identifier": {
        "if": { "type": "string" },
        "then": { "x-jsonld-id": "https://schema.org/name" },
        "else": { "x-jsonld-id": "https://schema.org/identifier" }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "identifier": 42 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/identifier": [ { "@value": 42 } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_oneof_only_matching_branch_survives) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": {
        "oneOf": [
          { "type": "integer", "x-jsonld-id": "https://schema.org/age" },
          { "type": "string", "x-jsonld-id": "https://schema.org/name" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "value": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_standalone_node_without_edge) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "author": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Person",
        "properties": {
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "author": { "name": "Ada" } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Person" ],
      "https://schema.org/name": [ { "@value": "Ada" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_invalid_instance_returns_validation_errors) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": "https://schema.org/Person",
    "properties": {
      "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
    },
    "required": [ "name" ]
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_INVALID(schema, instance, errors);

  EXPECT_EQ(errors.size(), 1);
  EXPECT_JSON_LD_ERROR(errors, 0, "", "/required", "#/required",
                       "The value was expected to be an object that defines "
                       "the property \"name\"");
}

TEST(JSONLD_type_on_literal_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "code": {
        "type": "string",
        "x-jsonld-type": "https://schema.org/Thing"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "code": "abc" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/code", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_non_string_id_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "name": { "x-jsonld-id": 42 } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/name", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_relative_id_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "name": { "x-jsonld-id": "name" } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/name", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_empty_type_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": ""
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Type,
      "The value of x-jsonld-type must be an absolute IRI");
}

TEST(JSONLD_type_on_array_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "x-jsonld-type": "https://schema.org/Thing"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "tags": [ "a", "b" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/tags", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_no_annotations_yields_empty_document) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "name": { "type": "string" } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_null_value_produces_no_triple) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "x-jsonld-id": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": null })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_falsy_scalar_literals_are_kept) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "active": { "x-jsonld-id": "https://schema.org/active" },
      "count": { "x-jsonld-id": "https://schema.org/count" },
      "label": { "x-jsonld-id": "https://schema.org/label" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "active": false, "count": 0, "label": "" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/active": [ { "@value": false } ],
      "https://schema.org/count": [ { "@value": 0 } ],
      "https://schema.org/label": [ { "@value": "" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_native_scalar_types) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "s": { "x-jsonld-id": "https://schema.org/s" },
      "i": { "x-jsonld-id": "https://schema.org/i" },
      "f": { "x-jsonld-id": "https://schema.org/f" },
      "b": { "x-jsonld-id": "https://schema.org/b" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "s": "x", "i": 5, "f": 1.5, "b": true })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/b": [ { "@value": true } ],
      "https://schema.org/f": [ { "@value": 1.5 } ],
      "https://schema.org/i": [ { "@value": 5 } ],
      "https://schema.org/s": [ { "@value": "x" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_multiple_predicates_via_allof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "label": {
        "type": "string",
        "allOf": [
          { "x-jsonld-id": "https://schema.org/name" },
          { "x-jsonld-id": "http://www.w3.org/2000/01/rdf-schema#label" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "label": "Hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "http://www.w3.org/2000/01/rdf-schema#label": [ { "@value": "Hi" } ],
      "https://schema.org/name": [ { "@value": "Hi" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_two_properties_same_predicate) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "firstName": { "x-jsonld-id": "https://schema.org/name" },
      "lastName": { "x-jsonld-id": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "firstName": "Ada", "lastName": "Lovelace" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/name": [
        { "@value": "Ada" },
        { "@value": "Lovelace" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_edge_dedup_via_allof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": {
        "allOf": [
          { "x-jsonld-id": "https://schema.org/name" },
          { "x-jsonld-id": "https://schema.org/name" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_empty_array_property_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": { "type": "array", "x-jsonld-id": "https://schema.org/keywords" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "tags": [] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_empty_type_array_is_untyped_node) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": [],
    "properties": {
      "name": { "x-jsonld-id": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_typed_root_with_empty_instance) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": "https://schema.org/Person"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "@type": [ "https://schema.org/Person" ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_absent_described_property) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "x-jsonld-id": "https://schema.org/name" },
      "email": { "x-jsonld-id": "https://schema.org/email" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_property_names_annotation_ignored) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": { "x-jsonld-id": "https://schema.org/name" }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_unicode_value_preserved) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "x-jsonld-id": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada 日本語" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada 日本語" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_array_of_scalars_emits_native_literals) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": { "type": "array", "x-jsonld-id": "https://schema.org/keywords" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "tags": [ "a", "b" ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/keywords": [
        { "@value": "a" },
        { "@value": "b" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_annotation_under_not_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": {
        "not": { "type": "integer", "x-jsonld-id": "https://schema.org/bad" }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "v": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_additional_properties_map_to_predicate) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": { "x-jsonld-id": "https://schema.org/extra" }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "a": "1", "b": "2" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/extra": [
        { "@value": "1" },
        { "@value": "2" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_non_http_iri_schemes_accepted) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": "urn:example:Thing",
    "properties": {
      "id": { "x-jsonld-id": "tag:example.com,2024:id" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "id": "x" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "urn:example:Thing" ],
      "tag:example.com,2024:id": [ { "@value": "x" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_type_array_with_empty_element_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": [ "https://schema.org/A", "" ]
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Type,
      "The value of x-jsonld-type must be an absolute IRI");
}

TEST(JSONLD_object_edge_without_described_children_is_empty_node) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "addr": { "type": "object", "x-jsonld-id": "https://schema.org/address" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "addr": { "street": "x" } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/address": [ {} ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_dynamic_ref_recursive_tree) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/tree",
    "$dynamicAnchor": "node",
    "type": "object",
    "x-jsonld-type": "https://schema.org/Node",
    "properties": {
      "kids": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/child",
        "items": { "$dynamicRef": "#node" }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "kids": [ { "kids": [] } ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Node" ],
      "https://schema.org/child": [
        { "@type": [ "https://schema.org/Node" ] }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_unevaluated_properties_map_to_predicate) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "a": { "x-jsonld-id": "https://schema.org/a" }
    },
    "unevaluatedProperties": { "x-jsonld-id": "https://schema.org/rest" }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "a": "1", "b": "2" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/a": [ { "@value": "1" } ],
      "https://schema.org/rest": [ { "@value": "2" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_property_name_requiring_pointer_escape) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "a/b": { "x-jsonld-id": "https://schema.org/ab" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "a/b": "x" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/ab": [ { "@value": "x" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_resolution_error_location_is_pointer_escaped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "a~b": { "x-jsonld-type": "https://schema.org/T" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "a~b": "x" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/a~0b", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_id_keyword_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "name": { "x-jsonld-id": "@id" } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/name", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_number_precision_preserved) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "big": { "x-jsonld-id": "https://schema.org/b" },
      "neg": { "x-jsonld-id": "https://schema.org/n" },
      "frac": { "x-jsonld-id": "https://schema.org/f" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "big": 1000000000000000000, "neg": -42, "frac": 0.1 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/b": [ { "@value": 1000000000000000000 } ],
      "https://schema.org/f": [ { "@value": 0.1 } ],
      "https://schema.org/n": [ { "@value": -42 } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_array_of_numbers_and_booleans) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "nums": { "type": "array", "x-jsonld-id": "https://schema.org/n" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "nums": [ 1, 2, true ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/n": [
        { "@value": 1 },
        { "@value": 2 },
        { "@value": true }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_null_element_in_array_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": { "type": "array", "x-jsonld-id": "https://schema.org/k" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "tags": [ "a", null, "b" ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/k": [ { "@value": "a" }, { "@value": "b" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_boolean_subschema_and_closed_object) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "x-jsonld-id": "https://schema.org/name" },
      "x": true
    },
    "additionalProperties": false
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada", "x": 1 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_anchor_reference) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "n": { "$anchor": "nm", "x-jsonld-id": "https://schema.org/name" }
    },
    "type": "object",
    "properties": { "name": { "$ref": "#nm" } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "name": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_items_2019_09) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "p": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/p",
        "items": { "x-jsonld-type": "https://schema.org/Item" }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "p": [ {}, {} ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/p": [
        { "@type": [ "https://schema.org/Item" ] },
        { "@type": [ "https://schema.org/Item" ] }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_recursive_ref_2019_09) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/r",
    "$recursiveAnchor": true,
    "type": "object",
    "x-jsonld-type": "https://schema.org/N",
    "properties": {
      "c": { "$recursiveRef": "#", "x-jsonld-id": "https://schema.org/c" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "c": { "c": {} } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/N" ],
      "https://schema.org/c": [
        {
          "@type": [ "https://schema.org/N" ],
          "https://schema.org/c": [ { "@type": [ "https://schema.org/N" ] } ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_const_value) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "kind": { "const": "book", "x-jsonld-id": "https://schema.org/kind" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "kind": "book" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/kind": [ { "@value": "book" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_property_names_type_annotation_ignored) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "propertyNames": { "x-jsonld-type": "https://schema.org/T" }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "a": 1 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_empty_property_name) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "": { "x-jsonld-id": "https://schema.org/empty" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "": "x" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/empty": [ { "@value": "x" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_unicode_property_name) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "名前": { "x-jsonld-id": "https://schema.org/name" } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "名前": "Ada" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "Ada" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_contains_subschema_types) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "list": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/list",
        "contains": {
          "type": "object",
          "x-jsonld-type": "https://schema.org/Item"
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "list": [ { "a": 1 }, { "b": 2 } ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/list": [
        { "@type": [ "https://schema.org/Item" ] },
        { "@type": [ "https://schema.org/Item" ] }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_nested_array_flattens_as_set) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "m": { "type": "array", "x-jsonld-id": "https://schema.org/m" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "m": [ [ "a" ], [ "b" ] ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/m": [ { "@value": "a" }, { "@value": "b" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_deeply_nested_array_flattens_as_set) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "m": { "type": "array", "x-jsonld-id": "https://schema.org/m" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "m": [ [ [ "a" ], [ "b" ] ], [ "c" ] ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/m": [
        { "@value": "a" },
        { "@value": "b" },
        { "@value": "c" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_edge_on_object_root_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-id": "https://schema.org/name",
    "x-jsonld-type": "https://schema.org/Person"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD predicate cannot be assigned to the document root");
}

TEST(JSONLD_edge_on_array_root_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "x-jsonld-id": "https://schema.org/items"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON([ "a", "b" ])JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD predicate cannot be assigned to the document root");
}

TEST(JSONLD_instance_value_object_keys_are_not_special) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": { "x-jsonld-id": "https://schema.org/v" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "v": { "@value": "x", "@type": "y" } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/v": [ {} ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_edge_on_scalar_root_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "x-jsonld-id": "https://schema.org/name"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON("Ada")JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD predicate cannot be assigned to the document root");
}

TEST(JSONLD_polymorphic_oneof_selects_object_branch) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": {
        "oneOf": [
          {
            "type": "object",
            "x-jsonld-type": "https://schema.org/A",
            "properties": {
              "x": { "x-jsonld-id": "https://schema.org/x" }
            }
          },
          { "type": "string", "x-jsonld-id": "https://schema.org/label" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "v": { "x": "hi" } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/A" ],
      "https://schema.org/x": [ { "@value": "hi" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_pattern_properties_map_to_predicate) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x": { "x-jsonld-id": "https://schema.org/x" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x1": "a", "y": "b" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "a" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_type_array_with_duplicates_deduped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": [
      "https://schema.org/A",
      "https://schema.org/A"
    ]
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "@type": [ "https://schema.org/A" ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_type_on_number_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "n": { "x-jsonld-type": "https://schema.org/T" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "n": 5 })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/n", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_non_string_type_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": 123
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Type,
      "The value of x-jsonld-type must be an absolute IRI");
}

TEST(JSONLD_whitespace_iri_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-id": " https://example.com/p" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_complex_iri_accepted) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "x-jsonld-id": "https://u@ex.com:8080/p?q=1#f" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://u@ex.com:8080/p?q=1#f": [ { "@value": "v" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_id_and_type_merge_across_allof_branches) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "author": {
        "allOf": [
          { "x-jsonld-id": "https://schema.org/author" },
          { "type": "object", "x-jsonld-type": "https://schema.org/Person" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "author": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/author": [
        { "@type": [ "https://schema.org/Person" ] }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_tuple_items_default_to_literals) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "t": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/t",
        "prefixItems": [ { "type": "string" } ],
        "items": { "type": "integer" }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "t": [ "a", 1, 2 ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/t": [
        { "@value": "a" },
        { "@value": 1 },
        { "@value": 2 }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_unwhitelisted_keyword_is_ignored) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "d": {
        "x-jsonld-id": "https://schema.org/d",
        "x-jsonld-context": "https://schema.org/"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "d": "2024-01-01" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/d": [ { "@value": "2024-01-01" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_evaluator_reused_across_calls) {
  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      "x-jsonld-id", "x-jsonld-type"};

  const auto schema_first{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "a": { "x-jsonld-id": "https://schema.org/a" } }
  })JSON")};
  const auto schema_second{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": "https://schema.org/Person"
  })JSON")};

  const auto template_first{sourcemeta::blaze::compile(
      schema_first, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};
  const auto template_second{sourcemeta::blaze::compile(
      schema_second, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  const auto instance_first{
      sourcemeta::core::parse_json(R"JSON({ "a": "x" })JSON")};
  const auto instance_second{sourcemeta::core::parse_json(R"JSON({})JSON")};

  sourcemeta::blaze::Evaluator evaluator;

  const auto outcome_first{
      sourcemeta::blaze::jsonld(evaluator, template_first, instance_first)};
  const auto outcome_second{
      sourcemeta::blaze::jsonld(evaluator, template_second, instance_second)};

  EXPECT_TRUE(std::holds_alternative<sourcemeta::core::JSON>(outcome_first));
  EXPECT_EQ(std::get<sourcemeta::core::JSON>(outcome_first),
            sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/a": [ { "@value": "x" } ] }
  ])JSON"));

  EXPECT_TRUE(std::holds_alternative<sourcemeta::core::JSON>(outcome_second));
  EXPECT_EQ(std::get<sourcemeta::core::JSON>(outcome_second),
            sourcemeta::core::parse_json(R"JSON([
    { "@type": [ "https://schema.org/Person" ] }
  ])JSON"));
}

TEST(JSONLD_anyof_multiple_matching_branches_merge_types) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": {
        "anyOf": [
          { "x-jsonld-type": "https://schema.org/A" },
          { "x-jsonld-type": "https://schema.org/B" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "v": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "@type": [ "https://schema.org/A", "https://schema.org/B" ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_ref_chain) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "c": { "x-jsonld-type": "https://schema.org/C" },
      "b": { "$ref": "#/$defs/c" },
      "a": { "$ref": "#/$defs/b" }
    },
    "type": "object",
    "properties": { "x": { "$ref": "#/$defs/a" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "@type": [ "https://schema.org/C" ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_int64_max_preserved) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "n": { "x-jsonld-id": "https://schema.org/n" } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "n": 9223372036854775807 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/n": [ { "@value": 9223372036854775807 } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_overlapping_property_definitions_merge_edges) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x1": { "x-jsonld-id": "https://schema.org/a" }
    },
    "patternProperties": {
      "^x": { "x-jsonld-id": "https://schema.org/b" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x1": "v" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/a": [ { "@value": "v" } ],
      "https://schema.org/b": [ { "@value": "v" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_dependent_schemas) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "cc": { "x-jsonld-id": "https://schema.org/cc" }
    },
    "dependentSchemas": {
      "cc": {
        "properties": {
          "exp": { "x-jsonld-id": "https://schema.org/exp" }
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "cc": "1234", "exp": "12/25" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/cc": [ { "@value": "1234" } ],
      "https://schema.org/exp": [ { "@value": "12/25" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_ref_with_escaped_pointer) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a/b": { "x-jsonld-type": "https://schema.org/T" }
    },
    "type": "object",
    "properties": { "x": { "$ref": "#/$defs/a~1b" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "@type": [ "https://schema.org/T" ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_edge_on_collection_element_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "pair": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/pair",
        "prefixItems": [ { "x-jsonld-id": "https://schema.org/first" } ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "pair": [ "a" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/pair/0", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD predicate cannot be assigned to an array element");
}

TEST(JSONLD_array_of_undescribed_objects_with_described_children) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "friends": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/knows",
        "items": {
          "type": "object",
          "properties": {
            "name": {
              "type": "string",
              "x-jsonld-id": "https://schema.org/name"
            }
          }
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "friends": [ { "name": "Ada" }, { "name": "Bob" } ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/knows": [
        { "https://schema.org/name": [ { "@value": "Ada" } ] },
        { "https://schema.org/name": [ { "@value": "Bob" } ] }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_collected_but_unhandled_keyword_creates_no_descriptor) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "meta": {
        "type": "object",
        "x-jsonld-container": "@index"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "meta": { "a": 1 } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE_WITH(schema, instance, expected, "x-jsonld-id",
                            "x-jsonld-type", "x-jsonld-container");
}

TEST(JSONLD_datatype_explicit) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "dob": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/birthDate",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "dob": "1990-05-15" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/birthDate": [
        {
          "@value": "1990-05-15",
          "@type": "http://www.w3.org/2001/XMLSchema#date"
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_non_iri_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-datatype": 42 } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "The value of x-jsonld-datatype must be an absolute IRI");
}

TEST(JSONLD_datatype_on_object_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "obj": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/o",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "obj": {} })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/obj", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype can only be assigned to a scalar value");
}

TEST(JSONLD_datatype_conflict_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "allOf": [
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date" },
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#string" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype cannot be assigned more than one value");
}

TEST(JSONLD_language_tagged_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "greeting": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/name",
        "x-jsonld-language": "en"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "greeting": "hello" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/name": [ { "@value": "hello", "@language": "en" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_invalid_tag_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-language": "en-" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "The value of x-jsonld-language must be a BCP 47 language tag");
}

TEST(JSONLD_direction_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "text": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/text",
        "x-jsonld-direction": "rtl"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "text": "abc" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/text": [ { "@value": "abc", "@direction": "rtl" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_direction_invalid_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-direction": "up" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Direction,
      R"(The value of x-jsonld-direction must be "ltr" or "rtl")");
}

TEST(JSONLD_json_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "blob": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/data",
        "x-jsonld-json": true
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "blob": "raw" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/data": [ { "@value": "raw", "@type": "@json" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_json_wraps_object) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "data": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/data",
        "x-jsonld-json": true
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "data": { "a": 1, "b": [ 2, 3 ] } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/data": [
        { "@value": { "a": 1, "b": [ 2, 3 ] }, "@type": "@json" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_reverse_edge) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "parent": {
        "type": "object",
        "x-jsonld-reverse": "https://schema.org/children",
        "x-jsonld-type": "https://schema.org/Person"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "parent": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@reverse": {
        "https://schema.org/children": [
          { "@type": [ "https://schema.org/Person" ] }
        ]
      }
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_reverse_non_iri_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-reverse": 42 } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-reverse must be an absolute IRI");
}

TEST(JSONLD_reverse_on_root_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-reverse": "https://schema.org/x"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD predicate cannot be assigned to the document root");
}

TEST(JSONLD_graph_node) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-graph": true,
    "properties": {
      "member": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/member",
        "x-jsonld-type": "https://schema.org/Person"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "member": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@graph": [
        {
          "https://schema.org/member": [
            { "@type": [ "https://schema.org/Person" ] }
          ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_on_scalar_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-graph": true } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Graph,
      "A JSON-LD graph flag can only be assigned to an object value");
}

TEST(JSONLD_datatype_without_edge_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "2024-01-01" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_absent_property_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_number_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "n": {
        "type": "integer",
        "x-jsonld-id": "https://schema.org/n",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#int"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "n": 5 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/n": [
        { "@value": 5, "@type": "http://www.w3.org/2001/XMLSchema#int" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_idempotent_via_allof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date" },
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "2024-01-01" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/x": [
        {
          "@value": "2024-01-01",
          "@type": "http://www.w3.org/2001/XMLSchema#date"
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_array_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": [ "a" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype can only be assigned to a scalar value");
}

TEST(JSONLD_datatype_whitespace_iri_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-datatype": " http://example.com/d" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "The value of x-jsonld-datatype must be an absolute IRI");
}

TEST(JSONLD_language_complex_tag) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-language": "zh-Hant-HK"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "text" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/x": [ { "@value": "text", "@language": "zh-Hant-HK" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_empty_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-language": "" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "The value of x-jsonld-language must be a BCP 47 language tag");
}

TEST(JSONLD_language_non_string_keyword_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-language": 5 } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "The value of x-jsonld-language must be a BCP 47 language tag");
}

TEST(JSONLD_language_on_number_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "x-jsonld-id": "https://schema.org/x", "x-jsonld-language": "en" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": 5 })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "A JSON-LD language can only be assigned to a string value");
}

TEST(JSONLD_language_on_array_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-language": "en"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": [ "a" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "A JSON-LD language can only be assigned to a scalar value");
}

TEST(JSONLD_direction_uppercase_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-direction": "LTR" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Direction,
      R"(The value of x-jsonld-direction must be "ltr" or "rtl")");
}

TEST(JSONLD_direction_on_boolean_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "x-jsonld-id": "https://schema.org/x", "x-jsonld-direction": "rtl" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": true })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Direction,
      "A JSON-LD direction can only be assigned to a string value");
}

TEST(JSONLD_language_and_direction_i18n_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-language": "ar",
        "x-jsonld-direction": "rtl"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "hello" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/x": [
        { "@value": "hello", "@language": "ar", "@direction": "rtl" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_and_language_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date",
        "x-jsonld-language": "en"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype cannot carry a language or direction");
}

TEST(JSONLD_datatype_and_direction_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date",
        "x-jsonld-direction": "ltr"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype cannot carry a language or direction");
}

TEST(JSONLD_json_and_datatype_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-json": true,
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::JSON,
      "A JSON-LD JSON literal cannot be combined with any other JSON-LD "
      "annotation");
}

TEST(JSONLD_json_and_language_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-json": true,
        "x-jsonld-language": "en"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::JSON,
      "A JSON-LD JSON literal cannot be combined with any other JSON-LD "
      "annotation");
}

TEST(JSONLD_json_false_is_a_plain_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-json": false
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "v" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_json_on_number_literal) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "integer",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-json": true
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": 5 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": 5, "@type": "@json" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_json_non_boolean_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-json": "yes" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::JSON,
      "The value of x-jsonld-json must be a boolean");
}

TEST(JSONLD_json_wraps_array) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "raw": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/raw",
        "x-jsonld-json": true
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "raw": [ 1, "two", { "k": true } ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/raw": [
        { "@value": [ 1, "two", { "k": true } ], "@type": "@json" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_false_is_a_plain_node) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-graph": false,
    "properties": {
      "member": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/member",
        "x-jsonld-type": "https://schema.org/Person"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "member": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/member": [
        { "@type": [ "https://schema.org/Person" ] }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_with_type) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": "https://schema.org/Dataset",
    "x-jsonld-graph": true,
    "properties": {
      "member": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/member",
        "x-jsonld-type": "https://schema.org/Person"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "member": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@type": [ "https://schema.org/Dataset" ],
      "@graph": [
        {
          "https://schema.org/member": [
            { "@type": [ "https://schema.org/Person" ] }
          ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_on_array_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-graph": true
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": [ "a" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Graph,
      "A JSON-LD graph flag can only be assigned to an object value");
}

TEST(JSONLD_graph_non_boolean_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-graph": "true"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Graph,
      "The value of x-jsonld-graph must be a boolean");
}

TEST(JSONLD_reverse_and_forward_same_predicate) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "rel": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/knows",
        "x-jsonld-reverse": "https://schema.org/knows",
        "x-jsonld-type": "https://schema.org/Person"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "rel": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/knows": [
        { "@type": [ "https://schema.org/Person" ] }
      ],
      "@reverse": {
        "https://schema.org/knows": [
          { "@type": [ "https://schema.org/Person" ] }
        ]
      }
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_reverse_dedup_via_allof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "rel": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Person",
        "allOf": [
          { "x-jsonld-reverse": "https://schema.org/knows" },
          { "x-jsonld-reverse": "https://schema.org/knows" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "rel": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@reverse": {
        "https://schema.org/knows": [
          { "@type": [ "https://schema.org/Person" ] }
        ]
      }
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_reverse_on_array_element_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "pair": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/pair",
        "prefixItems": [ { "x-jsonld-reverse": "https://schema.org/first" } ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "pair": [ {} ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/pair/0", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD predicate cannot be assigned to an array element");
}

TEST(JSONLD_reverse_to_scalar_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "type": "string", "x-jsonld-reverse": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD reverse predicate can only point to a node or an array of "
      "nodes");
}

TEST(JSONLD_reverse_to_array_of_nodes) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "authors": {
        "type": "array",
        "x-jsonld-reverse": "https://schema.org/author",
        "items": {
          "type": "object",
          "x-jsonld-type": "https://schema.org/Person"
        }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "authors": [ {}, {} ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@reverse": {
        "https://schema.org/author": [
          { "@type": [ "https://schema.org/Person" ] },
          { "@type": [ "https://schema.org/Person" ] }
        ]
      }
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_reverse_to_array_with_scalar_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "type": "array", "x-jsonld-reverse": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": [ {}, "a" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD reverse predicate can only point to a node or an array of "
      "nodes");
}

TEST(JSONLD_reverse_to_array_with_nested_array_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "type": "array", "x-jsonld-reverse": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": [ [ {} ] ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD reverse predicate can only point to a node or an array of "
      "nodes");
}

TEST(JSONLD_type_and_datatype_on_object_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-type": "https://schema.org/Thing",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype can only be assigned to a scalar value");
}

TEST(JSONLD_type_and_datatype_on_scalar_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-type": "https://schema.org/Thing",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_datatype_under_not_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": {
        "not": {
          "type": "integer",
          "x-jsonld-id": "https://schema.org/bad",
          "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#int"
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "v": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_in_oneof_only_matching_branch) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": {
        "oneOf": [
          {
            "type": "integer",
            "x-jsonld-id": "https://schema.org/count",
            "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#int"
          },
          { "type": "string", "x-jsonld-id": "https://schema.org/name" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "v": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/name": [ { "@value": "hi" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_in_then_branch) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "v": {
        "if": { "type": "string" },
        "then": {
          "x-jsonld-id": "https://schema.org/name",
          "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#string"
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "v": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/name": [
        {
          "@value": "hi",
          "@type": "http://www.w3.org/2001/XMLSchema#string"
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_and_language_across_allof_branches_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date" },
          { "x-jsonld-language": "en" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype cannot carry a language or direction");
}

TEST(JSONLD_type_and_datatype_on_array_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-type": "https://schema.org/Thing",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": [ "a" ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_id_and_reverse_different_predicates) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "rel": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/a",
        "x-jsonld-reverse": "https://schema.org/b",
        "x-jsonld-type": "https://schema.org/Person"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "rel": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/a": [
        { "@type": [ "https://schema.org/Person" ] }
      ],
      "@reverse": {
        "https://schema.org/b": [
          { "@type": [ "https://schema.org/Person" ] }
        ]
      }
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_reverse_to_empty_object) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "type": "object", "x-jsonld-reverse": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "@reverse": { "https://schema.org/name": [ {} ] } }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_nested_under_edge) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "dataset": {
        "type": "object",
        "x-jsonld-id": "https://schema.org/dataset",
        "x-jsonld-graph": true,
        "properties": {
          "member": {
            "type": "object",
            "x-jsonld-id": "https://schema.org/member",
            "x-jsonld-type": "https://schema.org/Person"
          }
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "dataset": { "member": {} } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/dataset": [
        {
          "@graph": [
            {
              "https://schema.org/member": [
                { "@type": [ "https://schema.org/Person" ] }
              ]
            }
          ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_on_null_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "x-jsonld-id": "https://schema.org/x", "x-jsonld-language": "en" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": null })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "A JSON-LD language can only be assigned to a string value");
}

TEST(JSONLD_datatype_relative_iri_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-datatype": "date" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "The value of x-jsonld-datatype must be an absolute IRI");
}

TEST(JSONLD_datatype_on_collection_elements) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/keywords",
        "items": {
          "type": "string",
          "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#token"
        }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "tags": [ "a", "b" ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/keywords": [
        { "@value": "a", "@type": "http://www.w3.org/2001/XMLSchema#token" },
        { "@value": "b", "@type": "http://www.w3.org/2001/XMLSchema#token" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_on_collection_elements) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "names": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/name",
        "items": { "type": "string", "x-jsonld-language": "fr" }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(
      R"JSON({ "names": [ "Jean", "Marie" ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/name": [
        { "@value": "Jean", "@language": "fr" },
        { "@value": "Marie", "@language": "fr" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_mixed_collection_element_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "items": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/items",
        "items": {
          "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#string"
        }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "items": [ "a", {} ] })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/items/1", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype can only be assigned to a scalar value");
}

TEST(JSONLD_reverse_to_empty_array_yields_empty_document) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "type": "array", "x-jsonld-reverse": "https://schema.org/name" }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": [] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_conflict_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-language": "en" },
          { "x-jsonld-language": "fr" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "A JSON-LD language cannot be assigned more than one value");
}

TEST(JSONLD_direction_conflict_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-direction": "ltr" },
          { "x-jsonld-direction": "rtl" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Direction,
      "A JSON-LD direction cannot be assigned more than one value");
}

TEST(JSONLD_language_idempotent_via_allof) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-language": "en" },
          { "x-jsonld-language": "en" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "hi", "@language": "en" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_array_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-datatype": [ "http://www.w3.org/2001/XMLSchema#date" ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "The value of x-jsonld-datatype must be an absolute IRI");
}

TEST(JSONLD_datatype_keyword_iri_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-datatype": "@json" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "The value of x-jsonld-datatype must be an absolute IRI");
}

TEST(JSONLD_datatype_urn_scheme_accepted) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "urn:example:kind"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "v", "@type": "urn:example:kind" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_private_use_tag_accepted) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-language": "x-private"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "v", "@language": "x-private" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_root_scalar_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON("v")JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_type_on_root_scalar_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "x-jsonld-type": "https://schema.org/Thing"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON("v")JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Type,
      "A JSON-LD type can only be assigned to an object value");
}

TEST(JSONLD_datatype_on_root_object_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype can only be assigned to a scalar value");
}

TEST(JSONLD_json_on_null_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": { "x-jsonld-id": "https://schema.org/x", "x-jsonld-json": true }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": null })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_null_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": null })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_falsy_zero) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#int"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": 0 })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/x": [
        { "@value": 0, "@type": "http://www.w3.org/2001/XMLSchema#int" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_anyof_datatype_conflict_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "anyOf": [
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date" },
          { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#string" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "A JSON-LD datatype cannot be assigned more than one value");
}

TEST(JSONLD_two_reverse_predicates) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "rel": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Person",
        "allOf": [
          { "x-jsonld-reverse": "https://schema.org/a" },
          { "x-jsonld-reverse": "https://schema.org/b" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "rel": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "@reverse": {
        "https://schema.org/a": [
          { "@type": [ "https://schema.org/Person" ] }
        ],
        "https://schema.org/b": [
          { "@type": [ "https://schema.org/Person" ] }
        ]
      }
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_datatype_on_nested_array_element_flattens) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "m": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/m",
        "items": {
          "type": "array",
          "items": {
            "type": "string",
            "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#token"
          }
        }
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "m": [ [ "a" ], [ "b" ] ] })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/m": [
        { "@value": "a", "@type": "http://www.w3.org/2001/XMLSchema#token" },
        { "@value": "b", "@type": "http://www.w3.org/2001/XMLSchema#token" }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_null_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-graph": null
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Graph,
      "The value of x-jsonld-graph must be a boolean");
}

TEST(JSONLD_json_object_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-json": {} } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::JSON,
      "The value of x-jsonld-json must be a boolean");
}

TEST(JSONLD_language_case_differing_tags_do_not_conflict) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-language": "en" },
          { "x-jsonld-language": "EN" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "hi", "@language": "en" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_type_object_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": {}
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Type,
      "The value of x-jsonld-type must be an absolute IRI");
}

TEST(JSONLD_type_array_with_number_element_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-type": [ "https://schema.org/A", 42 ]
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "", sourcemeta::blaze::JSONLDFacet::Type,
      "The value of x-jsonld-type must be an absolute IRI");
}

TEST(JSONLD_id_empty_string_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-id": "" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_id_array_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-id": [ "https://schema.org/x" ] } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_id_boolean_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-id": true } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-id must be an absolute IRI");
}

TEST(JSONLD_datatype_empty_string_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-datatype": "" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Datatype,
      "The value of x-jsonld-datatype must be an absolute IRI");
}

TEST(JSONLD_reverse_empty_string_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "type": "object", "x-jsonld-reverse": "" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "The value of x-jsonld-reverse must be an absolute IRI");
}

TEST(JSONLD_direction_number_value_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-direction": 5 } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Direction,
      R"(The value of x-jsonld-direction must be "ltr" or "rtl")");
}

TEST(JSONLD_json_and_graph_on_object_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "obj": {
        "type": "object",
        "x-jsonld-json": true,
        "x-jsonld-graph": true
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "obj": {} })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/obj", sourcemeta::blaze::JSONLDFacet::JSON,
      "A JSON-LD JSON literal cannot be combined with any other JSON-LD "
      "annotation");
}

TEST(JSONLD_datatype_dedup_via_ref_diamond) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "dated": { "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date" }
    },
    "type": "object",
    "properties": {
      "x": {
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "$ref": "#/$defs/dated" },
          { "$ref": "#/$defs/dated" }
        ]
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "2024-01-01" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/x": [
        {
          "@value": "2024-01-01",
          "@type": "http://www.w3.org/2001/XMLSchema#date"
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_variant_subtag_accepted) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "x-jsonld-language": "de-DE-1996"
      }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "hallo" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/x": [ { "@value": "hallo", "@language": "de-DE-1996" } ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_empty) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "x-jsonld-graph": true
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({})JSON")};

  const auto expected{
      sourcemeta::core::parse_json(R"JSON([ { "@graph": [] } ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_leading_whitespace_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "x-jsonld-language": " en" } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "v" })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Language,
      "The value of x-jsonld-language must be a BCP 47 language tag");
}

TEST(JSONLD_property_name_is_replaced_by_the_predicate) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "c": { "type": "string", "x-jsonld-id": "https://schema.org/color" }
    }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "c": "red" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/color": [ { "@value": "red" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_two_people_keep_their_own_birth_dates) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "people": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/member",
        "items": {
          "type": "object",
          "x-jsonld-type": "https://schema.org/Person",
          "properties": {
            "name": {
              "type": "string",
              "x-jsonld-id": "https://schema.org/name"
            },
            "dob": {
              "type": "string",
              "x-jsonld-id": "https://schema.org/birthDate",
              "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
            }
          }
        }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "people": [
      { "name": "Ada", "dob": "1815-12-10" },
      { "name": "Bob", "dob": "1990-05-15" }
    ]
  })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    {
      "https://schema.org/member": [
        {
          "@type": [ "https://schema.org/Person" ],
          "https://schema.org/name": [ { "@value": "Ada" } ],
          "https://schema.org/birthDate": [
            {
              "@value": "1815-12-10",
              "@type": "http://www.w3.org/2001/XMLSchema#date"
            }
          ]
        },
        {
          "@type": [ "https://schema.org/Person" ],
          "https://schema.org/name": [ { "@value": "Bob" } ],
          "https://schema.org/birthDate": [
            {
              "@value": "1990-05-15",
              "@type": "http://www.w3.org/2001/XMLSchema#date"
            }
          ]
        }
      ]
    }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_graph_false_alone_is_a_noop) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "type": "object", "x-jsonld-graph": false } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_json_false_alone_is_a_noop) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "type": "object", "x-jsonld-json": false } }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_language_region_case_insensitive_no_conflict) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "string",
        "x-jsonld-id": "https://schema.org/x",
        "allOf": [
          { "x-jsonld-language": "en-US" },
          { "x-jsonld-language": "en-us" }
        ]
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": "hi" })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([
    { "https://schema.org/x": [ { "@value": "hi", "@language": "en-US" } ] }
  ])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}

TEST(JSONLD_json_and_type_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "object",
        "x-jsonld-json": true,
        "x-jsonld-type": "https://schema.org/Thing"
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::JSON,
      "A JSON-LD JSON literal cannot be combined with any other JSON-LD "
      "annotation");
}

TEST(JSONLD_reverse_to_json_literal_is_a_resolution_error) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "x": {
        "type": "object",
        "x-jsonld-reverse": "https://schema.org/x",
        "x-jsonld-json": true
      }
    }
  })JSON")};

  const auto instance{sourcemeta::core::parse_json(R"JSON({ "x": {} })JSON")};

  EXPECT_JSON_LD_RESOLUTION_ERROR(
      schema, instance, "/x", sourcemeta::blaze::JSONLDFacet::Predicate,
      "A JSON-LD reverse predicate can only point to a node or an array of "
      "nodes");
}

TEST(JSONLD_json_object_without_edge_is_dropped) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "x": { "type": "object", "x-jsonld-json": true } }
  })JSON")};

  const auto instance{
      sourcemeta::core::parse_json(R"JSON({ "x": { "a": 1 } })JSON")};

  const auto expected{sourcemeta::core::parse_json(R"JSON([])JSON")};

  EXPECT_JSON_LD_VALUE(schema, instance, expected);
}
