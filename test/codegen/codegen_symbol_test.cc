#include <gtest/gtest.h>

#include <sourcemeta/blaze/codegen.h>

#include <sourcemeta/core/jsonschema.h>

TEST(IR_Symbol, nested_additional_properties_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "data": {
        "type": "object",
        "additionalProperties": {
          "type": "array",
          "items": {
            "type": "string"
          }
        }
      }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver,
                "https://json-schema.org/draft/2020-12/schema");

  const auto location{
      frame.traverse("#/properties/data/additionalProperties/items")};
  EXPECT_TRUE(location.has_value());

  const auto result{sourcemeta::blaze::symbol(frame, location.value().get())};

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0), "data");
  EXPECT_EQ(result.at(1), "additionalProperties");
  EXPECT_EQ(result.at(2), "items");
}

TEST(IR_Symbol, inside_defs) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "MyType": {
        "type": "object",
        "properties": {
          "name": {
            "type": "string"
          }
        }
      }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver,
                "https://json-schema.org/draft/2020-12/schema");

  const auto location{frame.traverse("#/$defs/MyType/properties/name")};
  EXPECT_TRUE(location.has_value());

  const auto result{sourcemeta::blaze::symbol(frame, location.value().get())};

  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result.at(0), "MyType");
  EXPECT_EQ(result.at(1), "name");
}

TEST(IR_Symbol, property_named_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "properties": {
        "type": "string"
      }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver,
                "https://json-schema.org/draft/2020-12/schema");

  const auto location{frame.traverse("#/properties/properties")};
  EXPECT_TRUE(location.has_value());

  const auto result{sourcemeta::blaze::symbol(frame, location.value().get())};

  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result.at(0), "properties");
}

TEST(IR_Symbol, anyof_child) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver,
                "https://json-schema.org/draft/2020-12/schema");

  const auto location{frame.traverse("#/anyOf/1")};
  EXPECT_TRUE(location.has_value());

  const auto result{sourcemeta::blaze::symbol(frame, location.value().get())};

  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result.at(0), "1");
}
