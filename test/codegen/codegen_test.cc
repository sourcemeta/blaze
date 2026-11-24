#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/codegen.h>
#include <sourcemeta/core/jsonschema.h>

#include <sstream> // std::ostringstream

#include "codegen_test_utils.h"

TEST(unsupported_dialect_draft3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::core::SchemaVocabularyError &error) {
    EXPECT_STREQ(error.what(), "Unsupported required vocabulary");
  }
}

TEST(unsupported_keyword_error_not) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnsupportedKeywordError &error) {
    EXPECT_STREQ(error.what(), "Unsupported keyword in subschema");
  }
}

TEST(unsupported_keyword_value_error_type_not_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": 123
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a string value");
  }
}

TEST(unknown_type_value_ignored) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "foo"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);

  EXPECT_EQ(output.str(), "export type Schema_5 = number;\n"
                          "\n"
                          "export type Schema_4 = string;\n"
                          "\n"
                          "export type Schema_3Items = unknown;\n"
                          "\n"
                          "export type Schema_3 = Schema_3Items[];\n"
                          "\n"
                          "export type Schema_2 = Record<string, unknown>;\n"
                          "\n"
                          "export type Schema_1 = boolean;\n"
                          "\n"
                          "export type Schema_0 = null;\n"
                          "\n"
                          "export type Schema =\n"
                          "  Schema_0 |\n"
                          "  Schema_1 |\n"
                          "  Schema_2 |\n"
                          "  Schema_3 |\n"
                          "  Schema_4 |\n"
                          "  Schema_5;\n");
}

TEST(unsupported_keyword_value_error_properties_not_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an object value");
    EXPECT_EQ(error.keyword(), "properties");
    EXPECT_AS_STRING(error.pointer(), "/anyOf/2");
  }
}

TEST(unsupported_keyword_value_error_properties_not_object_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "object", "properties": true } }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an object value");
    EXPECT_EQ(error.keyword(), "properties");
    EXPECT_AS_STRING(error.pointer(), "/properties/foo");
  }
}

TEST(unsupported_keyword_value_error_required_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array value");
    EXPECT_EQ(error.keyword(), "required");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_required_item_not_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": [ 5 ]
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array of string values");
    EXPECT_EQ(error.keyword(), "required");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_pattern_properties_not_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an object value");
    EXPECT_EQ(error.keyword(), "patternProperties");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_prefix_items_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array value");
    EXPECT_EQ(error.keyword(), "prefixItems");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_enum_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": 5
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected an array value");
    EXPECT_EQ(error.keyword(), "enum");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_any_of_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": true
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "anyOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_any_of_empty) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "anyOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_one_of_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": 5
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "oneOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_one_of_empty) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "oneOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_all_of_not_array) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": { "type": "string" }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "allOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_value_error_all_of_empty) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (
      const sourcemeta::blaze::CodegenUnsupportedKeywordValueError &error) {
    EXPECT_STREQ(error.what(), "Expected a non-empty array value");
    EXPECT_EQ(error.keyword(), "allOf");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unsupported_keyword_error_draft4_empty_enum) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "enum": []
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnsupportedKeywordError &error) {
    EXPECT_STREQ(error.what(), "Unsupported keyword in subschema");
    EXPECT_EQ(error.keyword(), "not");
    // Draft 4 canonicalises into its graph form, so the subschema that cannot
    // be generated is an entry rather than the root
    EXPECT_AS_STRING(error.pointer(), "/definitions/0");
  }
}

TEST(unsupported_keyword_error_draft6_negated_self_reference) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "allOf": [ { "$ref": "#/definitions/0" } ],
    "definitions": {
      "0": { "not": { "$ref": "#/definitions/0" } }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnsupportedKeywordError &error) {
    EXPECT_STREQ(error.what(), "Unsupported keyword in subschema");
    EXPECT_EQ(error.keyword(), "not");
    // An entry that negates a reference to itself is a circle no boolean
    // stands for, so deciding what the negation means has to give up walking
    // of its own accord rather than follow the edge forever
    EXPECT_AS_STRING(error.pointer(), "/definitions/0");
  }
}

TEST(draft7_empty_enum) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": []
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);

  // Draft 7 canonicalises into its graph form, as Draft 6 does, so a schema
  // nothing satisfies is the entry the wrapper names rather than a bare
  // boolean, and the impossible type it generates is what the document comes
  // to through the wrapper
  EXPECT_EQ(output.str(), "export type Schema_0 = never;\n"
                          "\n"
                          "export type _Schema_0 = Schema_0;\n"
                          "\n"
                          "export type Schema = _Schema_0;\n");
}

TEST(unexpected_schema_error_required_property_not_allowed) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": [ "bar" ],
    "additionalProperties": false
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnexpectedSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "This schema requires a property that it does not allow");
    EXPECT_AS_STRING(error.pointer(), "");
  }
}

TEST(unexpected_schema_error_required_property_not_allowed_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "object",
        "properties": { "qux": { "type": "string" } },
        "required": [ "bar" ],
        "additionalProperties": false
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnexpectedSchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "This schema requires a property that it does not allow");
    EXPECT_AS_STRING(error.pointer(), "/properties/foo");
  }
}

TEST(required_property_not_in_properties_open) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": { "foo": { "type": "string" } },
    "required": [ "bar" ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  std::ostringstream output;
  sourcemeta::blaze::generate<sourcemeta::blaze::TypeScript>(output, result);

  EXPECT_EQ(output.str(), "export type SchemaFoo = string;\n"
                          "\n"
                          "export type SchemaBar = unknown;\n"
                          "\n"
                          "export interface Schema {\n"
                          "  \"foo\"?: SchemaFoo;\n"
                          "  \"bar\": SchemaBar;\n"
                          "  [key: string]: unknown | undefined;\n"
                          "}\n");
}

TEST(draft4_graph_form_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON")};

  // Draft 4 canonicalises into its graph form, so what reaches codegen is a
  // wrapper over one `definitions` entry rather than the schema as written.
  // Generating from it means the `definitions` container is understood and the
  // references into it are followed
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_SCALAR(result, ir_index_of(result, "/definitions/0"), String,
                   "/definitions/0");
}

TEST(draft6_graph_form_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON")};

  // Draft 6 canonicalises into its graph form too, so what reaches codegen is
  // a wrapper over one `definitions` entry rather than the schema as written
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_SCALAR(result, ir_index_of(result, "/definitions/0"), String,
                   "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
}

TEST(draft6_graph_form_negation_of_everything_is_impossible) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer",
    "enum": [ "x" ]
  })JSON")};

  // A dialect whose booleans are entries of the graph says that nothing
  // satisfies a schema by negating the one everything satisfies, and that is
  // the same impossible type the boolean used to generate. What the negation
  // names is reached only to arrive at that type, so it takes none of its own
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_IMPOSSIBLE(result, ir_index_of(result, "/definitions/0"),
                       "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/not");
  EXPECT_IR_NOTHING(result, "/definitions/1");
}

TEST(draft6_graph_form_closed_object_stays_closed) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": { "a": { "type": "string" } },
    "additionalProperties": false
  })JSON")};

  // What closes an object is an `additionalProperties` nothing can satisfy,
  // and the form says that from the entry an edge names rather than in place
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  const auto entry{ir_index_of(result, "/definitions/0")};
  EXPECT_TRUE(std::holds_alternative<CodegenIRObject>(result.at(entry)));

  const auto &object{std::get<CodegenIRObject>(result.at(entry))};
  EXPECT_AS_STRING(object.pointer, "/definitions/0");
  EXPECT_EQ(object.members.size(), 1);
  EXPECT_TRUE(std::holds_alternative<bool>(object.additional));
  EXPECT_FALSE(std::get<bool>(object.additional));
}

TEST(draft6_graph_form_array_with_impossible_contains_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "contains": false
  })JSON")};

  // The entry that `contains` names says nothing about what the array holds,
  // so the array still generates from the items it does allow
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/definitions/2"),
                "/definitions/2");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/2");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/contains");
  EXPECT_IR_NOTHING(result, "/definitions/1");
  EXPECT_IR_NOTHING(result, "/definitions/1/not");
}

TEST(draft6_graph_form_negation_under_contains_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "contains": { "not": { "type": "string" } }
  })JSON")};

  // What `contains` names is not a type this generates, and the form puts it
  // in the same container as everything else, so what an edge is for is what
  // says whether a node has to generate at all. A negation that stands for no
  // type of its own has none to give, and the array it validates still has one
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/definitions/3"),
                "/definitions/3");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/3");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/contains");
  EXPECT_IR_NOTHING(result, "/definitions/1");
  EXPECT_IR_NOTHING(result, "/definitions/1/not");
  EXPECT_IR_NOTHING(result, "/definitions/2");
}

TEST(nested_form_negation_under_contains_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "not": { "type": "string" } }
  })JSON")};

  // A dialect that keeps its subschemas where they were written says the same
  // thing about what `contains` names, and goes on saying it
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/items"), "/items");
  EXPECT_IR_ARRAY(result, ir_index_of(result, ""), "", "/items");
  EXPECT_IR_NOTHING(result, "/contains");
  EXPECT_IR_NOTHING(result, "/contains/not");
}

TEST(draft6_graph_form_negation_below_contains_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "contains": {
      "type": "object",
      "properties": { "foo": { "not": { "type": "string" } } }
    }
  })JSON")};

  // Nothing an entry that only validates leads to says what an instance looks
  // like either, however far down it sits. A keyword that carries a type
  // elsewhere carries none from an entry that carries none, so the negation
  // below this one is no more a type than the entry that names it
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/definitions/2"),
                "/definitions/2");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/2");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/contains");
  EXPECT_IR_NOTHING(result, "/definitions/1");
  EXPECT_IR_NOTHING(result, "/definitions/1/propertyNames");
  EXPECT_IR_NOTHING(result, "/definitions/1/properties/foo");
  EXPECT_IR_NOTHING(result, "/definitions/1/additionalProperties");
  EXPECT_IR_NOTHING(result, "/definitions/3");
  EXPECT_IR_NOTHING(result, "/definitions/3/not");
  EXPECT_IR_NOTHING(result, "/definitions/4");
}

TEST(nested_form_negation_below_contains_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "object",
      "properties": { "foo": { "not": { "type": "string" } } }
    }
  })JSON")};

  // A dialect that keeps its subschemas where they were written says the same
  // of everything under the keyword, and goes on saying it
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/items"), "/items");
  EXPECT_IR_ARRAY(result, ir_index_of(result, ""), "", "/items");
  EXPECT_IR_NOTHING(result, "/contains");
  EXPECT_IR_NOTHING(result, "/contains/propertyNames");
  EXPECT_IR_NOTHING(result, "/contains/properties/foo");
  EXPECT_IR_NOTHING(result, "/contains/properties/foo/not");
}

TEST(draft6_graph_form_entry_both_contained_and_held_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "items": { "$ref": "#/definitions/shape" },
    "contains": { "$ref": "#/definitions/shape" },
    "definitions": { "shape": { "type": "string" } }
  })JSON")};

  // One entry of the graph can be both what an array holds and what it has to
  // contain, and then there is a type to generate for it after all
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_SCALAR(result, ir_index_of(result, "/definitions/1"), String,
                   "/definitions/1");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/1");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/contains");
}

TEST(unsupported_keyword_error_draft6_negation_under_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "items": { "not": { "type": "string" } }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CodegenUnsupportedKeywordError &error) {
    EXPECT_STREQ(error.what(), "Unsupported keyword in subschema");
    EXPECT_EQ(error.keyword(), "not");
    // What an array holds is a type, so an entry it names has to stand for one
    // and a negation that stands for no type is still as far as this gets
    EXPECT_AS_STRING(error.pointer(), "/definitions/1");
  }
}

TEST(draft6_graph_form_dialect_from_the_caller_is_impossible) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "enum": [ 1 ]
  })JSON")};

  // A document that names no dialect takes the one the caller names, and
  // arriving at the schema nothing satisfies is the dialect's business either
  // way, so the entries that say so come out as they do for a document that
  // names the dialect itself
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler,
      "http://json-schema.org/draft-06/schema#")};

  using namespace sourcemeta::blaze;

  EXPECT_IR_IMPOSSIBLE(result, ir_index_of(result, "/definitions/0"),
                       "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/not");
  EXPECT_IR_NOTHING(result, "/definitions/1");
}

TEST(draft6_graph_form_items_nothing_satisfies_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "items": false
  })JSON")};

  // What an array holds is the entry its `items` edge names, and an entry
  // that no instance satisfies stands for the type nothing answers to
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_IMPOSSIBLE(result, ir_index_of(result, "/definitions/1"),
                       "/definitions/1");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/1");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/1/not");
  EXPECT_IR_NOTHING(result, "/definitions/2");
}

TEST(draft6_graph_form_items_nothing_satisfies_with_a_name_from_the_caller) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "items": false
  })JSON")};

  // A name the caller hands the document alongside it is the name every
  // reference inside it resolves against, and an edge of the graph leads to
  // the same entry whether the document arrives with such a name or without
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler,
      "", "https://example.com/schema")};

  using namespace sourcemeta::blaze;

  EXPECT_IR_IMPOSSIBLE(result, ir_index_of(result, "/definitions/1"),
                       "/definitions/1");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/1");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/1/not");
  EXPECT_IR_NOTHING(result, "/definitions/2");
}

TEST(draft6_graph_form_closed_object_with_a_name_from_the_caller) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "properties": { "a": { "type": "string" } },
    "additionalProperties": false
  })JSON")};

  // What closes an object is an entry an edge names too, so the name the
  // caller hands the document makes no difference to it either
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler,
      "", "https://example.com/schema")};

  using namespace sourcemeta::blaze;

  const auto entry{ir_index_of(result, "/definitions/0")};
  EXPECT_TRUE(std::holds_alternative<CodegenIRObject>(result.at(entry)));

  const auto &object{std::get<CodegenIRObject>(result.at(entry))};
  EXPECT_AS_STRING(object.pointer, "/definitions/0");
  EXPECT_EQ(object.members.size(), 1);
  EXPECT_TRUE(std::holds_alternative<bool>(object.additional));
  EXPECT_FALSE(std::get<bool>(object.additional));
}

TEST(draft6_graph_form_entry_contained_by_itself_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "array",
    "contains": { "$ref": "#" }
  })JSON")};

  // An edge that only validates can lead back to the very entry it leaves, and
  // what reaches that entry otherwise is what says it carries a type, so the
  // entry stays where the edge would have taken it away
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/definitions/1"),
                "/definitions/1");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/definitions/0/items"),
                      "/definitions/0/items", "/definitions/1");
  EXPECT_IR_ARRAY(result, ir_index_of(result, "/definitions/0"),
                  "/definitions/0", "/definitions/0/items");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, "/allOf/0"), "/allOf/0",
                      "/definitions/0");
  EXPECT_IR_REFERENCE(result, ir_index_of(result, ""), "", "/allOf/0");
  EXPECT_IR_NOTHING(result, "/definitions/0/contains");
}

TEST(nested_form_root_contained_by_itself_generates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "$ref": "#" }
  })JSON")};

  // A `contains` is reached to say whether an instance is valid rather than to
  // say what it looks like, so what sits under one takes no part in the types
  // a document generates, not even when it leads back to the document itself
  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_ANY(result, ir_index_of(result, "/items"), "/items");
  EXPECT_IR_ARRAY(result, ir_index_of(result, ""), "", "/items");
  EXPECT_IR_NOTHING(result, "/contains");
}
