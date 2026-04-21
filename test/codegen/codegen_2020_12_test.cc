#include <gtest/gtest.h>

#include <sourcemeta/blaze/codegen.h>

#include "codegen_test_utils.h"

TEST(IR_2020_12, test_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, String, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, default_dialect_parameter) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "type": "string"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler,
      "https://json-schema.org/draft/2020-12/schema")};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, String, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, test_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "foo");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.at(0).first, "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/foo");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).members.at(0).second.symbol,
                "foo");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(1)).additional));
}

TEST(IR_2020_12, test_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Integer, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, test_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Number, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, test_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Integer, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, test_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 0,
    "exclusiveMaximum": 1.5,
    "multipleOf": 0.1
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Number, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, enum_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Null, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, enum_boolean_true_false) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Boolean, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, enum_boolean_false_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Boolean, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, enum_string_values) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_SYMBOL(std::get<IREnumeration>(result.at(0)).symbol);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 3);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_string(),
            "foo");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(1).to_string(),
            "bar");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(2).to_string(),
            "baz");
}

TEST(IR_2020_12, const_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": null
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Null, "");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol);
}

TEST(IR_2020_12, const_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "hello"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_SYMBOL(std::get<IREnumeration>(result.at(0)).symbol);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_string(),
            "hello");
}

TEST(IR_2020_12, const_integer) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 42
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_SYMBOL(std::get<IREnumeration>(result.at(0)).symbol);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_integer(),
            42);
}

TEST(IR_2020_12, const_boolean_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": true
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_SYMBOL(std::get<IREnumeration>(result.at(0)).symbol);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_TRUE(std::get<IREnumeration>(result.at(0)).values.at(0).to_boolean());
}

TEST(IR_2020_12, object_type_only) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(0)).symbol);
  EXPECT_TRUE(std::get<IRObject>(result.at(0)).members.empty());
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(0)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(0)).additional));
}

TEST(IR_2020_12, object_empty_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {}
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(0)).symbol);
  EXPECT_TRUE(std::get<IRObject>(result.at(0)).members.empty());
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(0)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(0)).additional));
}

TEST(IR_2020_12, object_with_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    },
    "additionalProperties": { "type": "integer" }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "foo");
  EXPECT_IR_SCALAR(result, 1, Integer, "/additionalProperties");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol,
                "additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/foo");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).members.at(0).second.symbol,
                "foo");

  EXPECT_TRUE(std::holds_alternative<IRType>(
      std::get<IRObject>(result.at(2)).additional));
  EXPECT_AS_STRING(
      std::get<IRType>(std::get<IRObject>(result.at(2)).additional).pointer,
      "/additionalProperties");
  EXPECT_SYMBOL(
      std::get<IRType>(std::get<IRObject>(result.at(2)).additional).symbol,
      "additionalProperties");
}

TEST(IR_2020_12, object_with_impossible_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": false
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_IMPOSSIBLE(result, 0, "/properties/foo");
  EXPECT_SYMBOL(std::get<IRImpossible>(result.at(0)).symbol, "foo");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).first == "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/foo");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).members.at(0).second.symbol,
                "foo");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(1)).additional));
}

TEST(IR_2020_12, object_with_impossible_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    },
    "additionalProperties": false
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "foo");

  EXPECT_IR_IMPOSSIBLE(result, 1, "/additionalProperties");
  EXPECT_SYMBOL(std::get<IRImpossible>(result.at(1)).symbol,
                "additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/foo");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).members.at(0).second.symbol,
                "foo");

  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(2)).additional));
  EXPECT_FALSE(std::get<bool>(std::get<IRObject>(result.at(2)).additional));
}

TEST(IR_2020_12, array_with_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, String, "/items");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "items");

  EXPECT_IR_ARRAY(result, 1, "", "/items");
  EXPECT_SYMBOL(std::get<IRArray>(result.at(1)).symbol);
  EXPECT_SYMBOL(std::get<IRArray>(result.at(1)).items->symbol, "items");
}

TEST(IR_2020_12, array_nested_in_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": { "type": "string" }
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/tags/items");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "tags", "items");

  EXPECT_IR_ARRAY(result, 1, "/properties/tags", "/properties/tags/items");
  EXPECT_SYMBOL(std::get<IRArray>(result.at(1)).symbol, "tags");
  EXPECT_SYMBOL(std::get<IRArray>(result.at(1)).items->symbol, "tags", "items");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).symbol);
}

TEST(IR_2020_12, tuple_with_prefix_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 4);

  EXPECT_IR_SCALAR(result, 0, Integer, "/prefixItems/1");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "1");
  EXPECT_IR_SCALAR(result, 1, String, "/prefixItems/0");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol, "0");
  EXPECT_IR_ANY(result, 2, "/items");
  EXPECT_SYMBOL(std::get<IRAny>(result.at(2)).symbol, "items");

  EXPECT_TRUE(std::holds_alternative<IRTuple>(result.at(3)));
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(3)).pointer, "");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(3)).symbol);
  EXPECT_EQ(std::get<IRTuple>(result.at(3)).items.size(), 2);
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(3)).items.at(0).pointer,
                   "/prefixItems/0");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(3)).items.at(0).symbol, "0");
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(3)).items.at(1).pointer,
                   "/prefixItems/1");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(3)).items.at(1).symbol, "1");
  EXPECT_TRUE(std::get<IRTuple>(result.at(3)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(3)).additional->pointer,
                   "/items");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(3)).additional->symbol, "items");
}

TEST(IR_2020_12, tuple_with_prefix_items_and_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" }
    ],
    "items": { "type": "boolean" }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/prefixItems/0");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "0");
  EXPECT_IR_SCALAR(result, 1, Boolean, "/items");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol, "items");

  EXPECT_TRUE(std::holds_alternative<IRTuple>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRTuple>(result.at(2)).items.size(), 1);
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(0).pointer,
                   "/prefixItems/0");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(2)).items.at(0).symbol, "0");
  EXPECT_TRUE(std::get<IRTuple>(result.at(2)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).additional->pointer,
                   "/items");
  EXPECT_SYMBOL(std::get<IRTuple>(result.at(2)).additional->symbol, "items");
}

TEST(IR_2020_12, anyof_two_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, Integer, "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "1");
  EXPECT_IR_SCALAR(result, 1, String, "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol, "0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRUnion>(result.at(2)).values.size(), 2);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(2)).values.at(0).symbol, "0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(2)).values.at(1).symbol, "1");
}

TEST(IR_2020_12, anyof_three_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "boolean" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 4);

  EXPECT_IR_SCALAR(result, 0, Boolean, "/anyOf/2");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "2");
  EXPECT_IR_SCALAR(result, 1, Integer, "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol, "1");
  EXPECT_IR_SCALAR(result, 2, String, "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(2)).symbol, "0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(3)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).pointer, "");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).symbol);
  EXPECT_EQ(std::get<IRUnion>(result.at(3)).values.size(), 3);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).values.at(0).symbol, "0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).values.at(1).symbol, "1");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(2).pointer,
                   "/anyOf/2");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).values.at(2).symbol, "2");
}

TEST(IR_2020_12, oneof_two_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  // Note: The canonicalizer transforms oneOf to anyOf
  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, Integer, "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "1");
  EXPECT_IR_SCALAR(result, 1, String, "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol, "0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRUnion>(result.at(2)).values.size(), 2);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(2)).values.at(0).symbol, "0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(2)).values.at(1).symbol, "1");
}

TEST(IR_2020_12, oneof_three_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "boolean" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  // Note: The canonicalizer transforms oneOf to anyOf
  EXPECT_EQ(result.size(), 4);

  EXPECT_IR_SCALAR(result, 0, Boolean, "/anyOf/2");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "2");
  EXPECT_IR_SCALAR(result, 1, Integer, "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(1)).symbol, "1");
  EXPECT_IR_SCALAR(result, 2, String, "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(2)).symbol, "0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(3)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).pointer, "");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).symbol);
  EXPECT_EQ(std::get<IRUnion>(result.at(3)).values.size(), 3);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).values.at(0).symbol, "0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).values.at(1).symbol, "1");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(2).pointer,
                   "/anyOf/2");
  EXPECT_SYMBOL(std::get<IRUnion>(result.at(3)).values.at(2).symbol, "2");
}

TEST(IR_2020_12, ref_recursive_to_root) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "child": { "$ref": "#" }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_REFERENCE(result, 0, "/properties/child", "");
  EXPECT_SYMBOL(std::get<IRReference>(result.at(0)).symbol, "child");
  EXPECT_SYMBOL(std::get<IRReference>(result.at(0)).target.symbol);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).first == "child");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/child");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).members.at(0).second.symbol,
                "child");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(1)).additional));
}

TEST(IR_2020_12, nested_object_with_required_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "nested": {
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        },
        "required": [ "name" ]
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/nested/properties/name");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "nested", "name");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer,
                   "/properties/nested");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol, "nested");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).first == "name");
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/nested/properties/name");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).members.at(0).second.symbol,
                "nested", "name");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(1)).additional));

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "nested");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/nested");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).members.at(0).second.symbol,
                "nested");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(2)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(2)).additional));
}

TEST(IR_2020_12, array_without_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  // Note: The canonicalizer now adds `items: true` for arrays without items
  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_ANY(result, 0, "/items");
  EXPECT_SYMBOL(std::get<IRAny>(result.at(0)).symbol, "items");

  EXPECT_TRUE(std::holds_alternative<IRArray>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRArray>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRArray>(result.at(1)).symbol);
  EXPECT_TRUE(std::get<IRArray>(result.at(1)).items.has_value());
  EXPECT_AS_STRING(std::get<IRArray>(result.at(1)).items->pointer, "/items");
  EXPECT_SYMBOL(std::get<IRArray>(result.at(1)).items->symbol, "items");
}

TEST(IR_2020_12, object_with_additional_properties_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": true
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  // Note: The canonicalizer now keeps additionalProperties: true as IRAny
  // instead of expanding it into a union of all types
  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/name");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "name");
  EXPECT_IR_ANY(result, 1, "/additionalProperties");
  EXPECT_SYMBOL(std::get<IRAny>(result.at(1)).symbol, "additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "name");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/name");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(2)).members.at(0).second.symbol,
                "name");
  // When additionalProperties is a boolean schema, the object stores the
  // boolean value directly (while the schema itself is compiled as IRAny)
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(2)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(2)).additional));
}

TEST(IR_2020_12, object_only_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": { "type": "boolean" }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, Boolean, "/additionalProperties");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol,
                "additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 0);
  EXPECT_TRUE(std::holds_alternative<IRType>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_AS_STRING(
      std::get<IRType>(std::get<IRObject>(result.at(1)).additional).pointer,
      "/additionalProperties");
  EXPECT_SYMBOL(
      std::get<IRType>(std::get<IRObject>(result.at(1)).additional).symbol,
      "additionalProperties");
}

TEST(IR_2020_12, embedded_resource_with_nested_id_no_duplicates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "type": "object",
    "required": [ "item" ],
    "properties": {
      "item": { "$ref": "https://example.com/item" }
    },
    "additionalProperties": false,
    "$defs": {
      "Item": {
        "$id": "https://example.com/item",
        "type": "object",
        "required": [ "name" ],
        "properties": {
          "name": { "type": "string" }
        },
        "additionalProperties": false
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 6);

  EXPECT_IR_REFERENCE(result, 0, "/properties/item", "/$defs/Item");
  EXPECT_SYMBOL(std::get<IRReference>(result.at(0)).symbol, "item");
  EXPECT_SYMBOL(std::get<IRReference>(result.at(0)).target.symbol, "Item");

  EXPECT_IR_IMPOSSIBLE(result, 1, "/additionalProperties");
  EXPECT_SYMBOL(std::get<IRImpossible>(result.at(1)).symbol,
                "additionalProperties");

  EXPECT_IR_SCALAR(result, 2, String, "/$defs/Item/properties/name");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(2)).symbol, "Item", "name");

  EXPECT_IR_IMPOSSIBLE(result, 3, "/$defs/Item/additionalProperties");
  EXPECT_SYMBOL(std::get<IRImpossible>(result.at(3)).symbol, "Item",
                "additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(4)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(4)).pointer, "/$defs/Item");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(4)).symbol, "Item");
  EXPECT_EQ(std::get<IRObject>(result.at(4)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(4)).members.at(0).first, "name");
  EXPECT_TRUE(std::get<IRObject>(result.at(4)).members.at(0).second.required);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(4)).members.at(0).second.pointer,
      "/$defs/Item/properties/name");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(4)).members.at(0).second.symbol,
                "Item", "name");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(4)).additional));
  EXPECT_FALSE(std::get<bool>(std::get<IRObject>(result.at(4)).additional));

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(5)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(5)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(5)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(5)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(5)).members.at(0).first, "item");
  EXPECT_TRUE(std::get<IRObject>(result.at(5)).members.at(0).second.required);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(5)).members.at(0).second.pointer,
      "/properties/item");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(5)).members.at(0).second.symbol,
                "item");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(5)).additional));
  EXPECT_FALSE(std::get<bool>(std::get<IRObject>(result.at(5)).additional));
}

TEST(IR_2020_12, boolean_true_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "anything": true
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_ANY(result, 0, "/properties/anything");
  EXPECT_SYMBOL(std::get<IRAny>(result.at(0)).symbol, "anything");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.at(0).first, "anything");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/anything");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).members.at(0).second.symbol,
                "anything");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(1)).additional));
}

TEST(IR_2020_12, boolean_false_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "nothing": false
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_IMPOSSIBLE(result, 0, "/properties/nothing");
  EXPECT_SYMBOL(std::get<IRImpossible>(result.at(0)).symbol, "nothing");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).symbol);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.at(0).first, "nothing");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/nothing");
  EXPECT_SYMBOL(std::get<IRObject>(result.at(1)).members.at(0).second.symbol,
                "nothing");
  EXPECT_TRUE(std::holds_alternative<bool>(
      std::get<IRObject>(result.at(1)).additional));
  EXPECT_TRUE(std::get<bool>(std::get<IRObject>(result.at(1)).additional));
}

TEST(IR_2020_12, object_with_pattern_properties_prefix) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "patternProperties": {
      "^x-": { "type": "string" }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/name");
  EXPECT_SYMBOL(std::get<IRScalar>(result.at(0)).symbol, "name");

  EXPECT_IR_SCALAR(result, 1, String, "/patternProperties/^x-");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  const auto &object{std::get<IRObject>(result.at(2))};
  EXPECT_AS_STRING(object.pointer, "");
  EXPECT_EQ(object.members.size(), 1);
  EXPECT_EQ(object.members.at(0).first, "name");

  EXPECT_EQ(object.pattern.size(), 1);
  EXPECT_AS_STRING(object.pattern.at(0).pointer, "/patternProperties/^x-");
  EXPECT_EQ(object.pattern.at(0).prefix, "x-");

  EXPECT_TRUE(std::holds_alternative<bool>(object.additional));
  EXPECT_TRUE(std::get<bool>(object.additional));
}

TEST(IR_2020_12, object_with_multiple_pattern_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" },
      "^data-": { "type": "integer" }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_FALSE(result.empty());
  EXPECT_TRUE(std::holds_alternative<IRObject>(result.back()));
  const auto &object{std::get<IRObject>(result.back())};
  EXPECT_EQ(object.pattern.size(), 2);
  EXPECT_EQ(object.pattern.at(0).prefix, "x-");
  EXPECT_EQ(object.pattern.at(1).prefix, "data-");
}

TEST(IR_2020_12, object_with_pattern_properties_and_additional_false) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "patternProperties": {
      "^x-": { "type": "string" }
    },
    "additionalProperties": false
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_FALSE(result.empty());
  EXPECT_TRUE(std::holds_alternative<IRObject>(result.back()));
  const auto &object{std::get<IRObject>(result.back())};
  EXPECT_EQ(object.members.size(), 1);
  EXPECT_EQ(object.pattern.size(), 1);
  EXPECT_EQ(object.pattern.at(0).prefix, "x-");
  EXPECT_TRUE(std::holds_alternative<bool>(object.additional));
  EXPECT_FALSE(std::get<bool>(object.additional));
}

TEST(IR_2020_12, object_with_non_prefix_pattern_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "[a-z]+_id": { "type": "integer" }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_FALSE(result.empty());
  EXPECT_TRUE(std::holds_alternative<IRObject>(result.back()));
  const auto &object{std::get<IRObject>(result.back())};
  EXPECT_EQ(object.pattern.size(), 1);
  EXPECT_FALSE(object.pattern.at(0).prefix.has_value());
}

TEST(IR_2020_12, object_with_mixed_prefix_and_non_prefix_patterns) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "^x-": { "type": "string" },
      "[0-9]+": { "type": "integer" }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_FALSE(result.empty());
  EXPECT_TRUE(std::holds_alternative<IRObject>(result.back()));
  const auto &object{std::get<IRObject>(result.back())};
  EXPECT_EQ(object.pattern.size(), 2);
  EXPECT_TRUE(object.pattern.at(0).prefix.has_value());
  EXPECT_EQ(object.pattern.at(0).prefix.value(), "x-");
  EXPECT_FALSE(object.pattern.at(1).prefix.has_value());
}

TEST(IR_2020_12, dynamic_ref_single_anchor) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "$dynamicRef": "#item" },
    "$defs": {
      "foo": {
        "$dynamicAnchor": "item",
        "type": "string"
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_FALSE(result.empty());
  EXPECT_IR_REFERENCE(result, 0, "/items", "/$defs/foo");
  EXPECT_IR_SCALAR(result, 1, String, "/$defs/foo");
}

TEST(IR_2020_12, dynamic_ref_multiple_anchors) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$ref": "list",
    "$defs": {
      "stringItem": {
        "$dynamicAnchor": "item",
        "type": "string"
      },
      "list": {
        "$id": "list",
        "type": "array",
        "items": { "$dynamicRef": "#item" },
        "$defs": {
          "defaultItem": {
            "$dynamicAnchor": "item",
            "type": "number"
          }
        }
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_EQ(result.size(), 6);
  EXPECT_IR_REFERENCE(result, 0, "/allOf/0", "/$defs/list");
  EXPECT_IR_SCALAR(result, 1, String, "/$defs/stringItem");
  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).pointer,
                   "/$defs/list/items");
  EXPECT_EQ(std::get<IRUnion>(result.at(2)).values.size(), 2);
  EXPECT_IR_SCALAR(result, 3, Number, "/$defs/list/$defs/defaultItem");
  EXPECT_IR_ARRAY(result, 4, "/$defs/list", "/$defs/list/items");
  EXPECT_IR_REFERENCE(result, 5, "", "/allOf/0");
}

TEST(IR_2020_12, dynamic_anchor_on_typed_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "item",
    "type": "string"
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_EQ(result.size(), 1);
  EXPECT_IR_SCALAR(result, 0, String, "");
}

TEST(IR_2020_12, allof_two_objects) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "object",
        "properties": { "name": { "type": "string" } },
        "required": [ "name" ],
        "additionalProperties": false
      },
      {
        "type": "object",
        "properties": { "age": { "type": "integer" } },
        "required": [ "age" ],
        "additionalProperties": false
      }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_EQ(result.size(), 7);
  EXPECT_IR_INTERSECTION(result, 6, "", 2);
}

TEST(IR_2020_12, allof_ref_and_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "#/$defs/Base" },
      {
        "type": "object",
        "properties": { "extra": { "type": "string" } },
        "additionalProperties": false
      }
    ],
    "$defs": {
      "Base": {
        "type": "object",
        "properties": { "id": { "type": "integer" } },
        "required": [ "id" ],
        "additionalProperties": false
      }
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_INTERSECTION(result, result.size() - 1, "", 2);
}

TEST(IR_2020_12, allof_single_element) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "string" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  // The canonicalizer inlines allOf with a single element
  ASSERT_EQ(result.size(), 1);
  EXPECT_IR_SCALAR(result, 0, String, "");
}

TEST(IR_2020_12, allof_three_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      {
        "type": "object",
        "properties": { "a": { "type": "string" } },
        "additionalProperties": false
      },
      {
        "type": "object",
        "properties": { "b": { "type": "integer" } },
        "additionalProperties": false
      },
      {
        "type": "object",
        "properties": { "c": { "type": "number" } },
        "additionalProperties": false
      }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_INTERSECTION(result, result.size() - 1, "", 3);
}

TEST(IR_2020_12, allof_with_defs) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "Named": {
        "type": "object",
        "properties": { "name": { "type": "string" } },
        "required": [ "name" ],
        "additionalProperties": false
      },
      "Aged": {
        "type": "object",
        "properties": { "age": { "type": "integer" } },
        "required": [ "age" ],
        "additionalProperties": false
      }
    },
    "allOf": [
      { "$ref": "#/$defs/Named" },
      { "$ref": "#/$defs/Aged" }
    ]
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_INTERSECTION(result, result.size() - 1, "", 2);
  EXPECT_IR_REFERENCE(result, 0, "/allOf/1", "/$defs/Aged");
  EXPECT_IR_REFERENCE(result, 1, "/allOf/0", "/$defs/Named");
}

TEST(IR_2020_12, if_then_else_distinct_object_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": {
      "type": "object",
      "properties": { "kind": { "const": "circle" } },
      "required": [ "kind" ]
    },
    "then": {
      "type": "object",
      "properties": { "radius": { "type": "number" } },
      "required": [ "radius" ]
    },
    "else": {
      "type": "object",
      "properties": { "sides": { "type": "integer" } },
      "required": [ "sides" ]
    }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_CONDITIONAL(result, result.size() - 1, "", "/if", "/then", "/else");
}

TEST(IR_2020_12, if_then_else_implicit_else) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "if": { "type": "string" },
    "then": { "type": "string", "minLength": 1 }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_CONDITIONAL(result, result.size() - 1, "", "/if", "/then", "/else");
}

TEST(IR_2020_12, if_then_else_with_type_sibling) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": { "type": "string", "maxLength": 10 },
    "then": { "type": "string", "pattern": "^short" },
    "else": { "type": "string", "pattern": "^long" }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  EXPECT_IR_CONDITIONAL(result, result.size() - 2, "/allOf/0", "/allOf/0/if",
                        "/allOf/0/then", "/allOf/0/else");
  EXPECT_IR_INTERSECTION(result, result.size() - 1, "", 2);
}

TEST(IR_2020_12, if_then_else_with_ref_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "Circle": {
        "type": "object",
        "properties": { "radius": { "type": "number" } },
        "required": [ "radius" ],
        "additionalProperties": false
      },
      "Square": {
        "type": "object",
        "properties": { "side": { "type": "number" } },
        "required": [ "side" ],
        "additionalProperties": false
      }
    },
    "if": {
      "type": "object",
      "properties": { "kind": { "const": "circle" } },
      "required": [ "kind" ]
    },
    "then": { "$ref": "#/$defs/Circle" },
    "else": { "$ref": "#/$defs/Square" }
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_EQ(result.size(), 11);
  EXPECT_IR_REFERENCE(result, 0, "/then", "/$defs/Circle");
  EXPECT_IR_REFERENCE(result, 3, "/else", "/$defs/Square");
  EXPECT_IR_CONDITIONAL(result, 10, "", "/if", "/then", "/else");
}

TEST(IR_2020_12, if_then_else_nested_in_object_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "value": {
        "if": { "type": "string" },
        "then": { "type": "string", "minLength": 1 },
        "else": { "type": "integer" }
      }
    },
    "additionalProperties": false
  })JSON")};

  const auto result{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::blaze::default_compiler)};

  using namespace sourcemeta::blaze;

  ASSERT_EQ(result.size(), 6);
  EXPECT_IR_SCALAR(result, 0, String, "/properties/value/then");
  EXPECT_IR_SCALAR(result, 1, String, "/properties/value/if");
  EXPECT_IR_SCALAR(result, 2, Integer, "/properties/value/else");
  EXPECT_IR_CONDITIONAL(result, 3, "/properties/value", "/properties/value/if",
                        "/properties/value/then", "/properties/value/else");
}
