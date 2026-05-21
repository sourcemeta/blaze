#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <vector>

TEST(Foundation_keyword_iterator, draft_2020_12) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "unevaluatedProperties": true,
    "prefixItems": [],
    "items": true,
    "minContains": 0,
    "maxContains": 1,
    "required": [ "foo" ],
    "contains": true,
    "unevaluatedItems": true,
    "if": true,
    "then": true,
    "else": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "https://json-schema.org/draft/2020-12/schema");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
    EXPECT_EQ(entry.vocabularies.size(), 7);
  }

  EXPECT_EQ(entries.size(), 16);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(
      entries.at(0).subschema.get(),
      sourcemeta::core::JSON{"https://json-schema.org/draft/2020-12/schema"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/if");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/maxContains");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::JSON{1});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer), "/minContains");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::JSON{0});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(4).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(4).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(5).pointer), "/prefixItems");
  EXPECT_EQ(entries.at(5).subschema.get(), sourcemeta::core::parse_json("[]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(6).pointer), "/required");
  EXPECT_EQ(entries.at(6).subschema.get(),
            sourcemeta::core::parse_json("[ \"foo\" ]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(7).pointer), "/contains");
  EXPECT_EQ(entries.at(7).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(8).pointer), "/else");
  EXPECT_EQ(entries.at(8).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(9).pointer), "/items");
  EXPECT_EQ(entries.at(9).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(10).pointer), "/properties");
  EXPECT_EQ(entries.at(10).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(11).pointer), "/then");
  EXPECT_EQ(entries.at(11).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(12).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(12).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(13).pointer), "/type");
  EXPECT_EQ(entries.at(13).subschema.get(), sourcemeta::core::JSON{"string"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(14).pointer),
            "/unevaluatedItems");
  EXPECT_EQ(entries.at(14).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(15).pointer),
            "/unevaluatedProperties");
  EXPECT_EQ(entries.at(15).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, draft_2019_09) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "unevaluatedProperties": true,
    "additionalItems": true,
    "items": [],
    "minContains": 0,
    "maxContains": 1,
    "required": [ "foo" ],
    "contains": true,
    "unevaluatedItems": true,
    "if": true,
    "then": true,
    "else": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "https://json-schema.org/draft/2019-09/schema");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09);
    EXPECT_EQ(entry.vocabularies.size(), 6);
  }

  EXPECT_EQ(entries.size(), 16);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(
      entries.at(0).subschema.get(),
      sourcemeta::core::JSON{"https://json-schema.org/draft/2019-09/schema"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/if");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/items");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::parse_json("[]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer), "/maxContains");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::JSON{1});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(4).pointer), "/minContains");
  EXPECT_EQ(entries.at(4).subschema.get(), sourcemeta::core::JSON{0});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(5).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(5).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(6).pointer), "/required");
  EXPECT_EQ(entries.at(6).subschema.get(),
            sourcemeta::core::parse_json("[ \"foo\" ]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(7).pointer),
            "/additionalItems");
  EXPECT_EQ(entries.at(7).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(8).pointer), "/contains");
  EXPECT_EQ(entries.at(8).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(9).pointer), "/else");
  EXPECT_EQ(entries.at(9).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(10).pointer), "/properties");
  EXPECT_EQ(entries.at(10).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(11).pointer), "/then");
  EXPECT_EQ(entries.at(11).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(12).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(12).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(13).pointer), "/type");
  EXPECT_EQ(entries.at(13).subschema.get(), sourcemeta::core::JSON{"string"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(14).pointer),
            "/unevaluatedItems");
  EXPECT_EQ(entries.at(14).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(15).pointer),
            "/unevaluatedProperties");
  EXPECT_EQ(entries.at(15).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "additionalItems": true,
    "required": [ "foo" ],
    "items": [],
    "if": true,
    "then": true,
    "else": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-07/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 11);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-07/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/if");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/items");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::parse_json("[]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(4).pointer), "/required");
  EXPECT_EQ(entries.at(4).subschema.get(),
            sourcemeta::core::parse_json("[ \"foo\" ]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(5).pointer),
            "/additionalItems");
  EXPECT_EQ(entries.at(5).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(6).pointer), "/else");
  EXPECT_EQ(entries.at(6).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(7).pointer), "/properties");
  EXPECT_EQ(entries.at(7).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(8).pointer), "/then");
  EXPECT_EQ(entries.at(8).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(9).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(9).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(10).pointer), "/type");
  EXPECT_EQ(entries.at(10).subschema.get(), sourcemeta::core::JSON{"string"});
}

TEST(Foundation_keyword_iterator, draft6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string",
    "properties": {},
    "patternProperties": {},
    "required": [ "foo" ],
    "additionalProperties": true,
    "additionalItems": true,
    "items": []
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-06/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 8);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/items");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("[]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer), "/required");
  EXPECT_EQ(entries.at(3).subschema.get(),
            sourcemeta::core::parse_json("[ \"foo\" ]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(4).pointer),
            "/additionalItems");
  EXPECT_EQ(entries.at(4).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(5).pointer), "/properties");
  EXPECT_EQ(entries.at(5).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(6).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(6).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(7).pointer), "/type");
  EXPECT_EQ(entries.at(7).subschema.get(), sourcemeta::core::JSON{"string"});
}

TEST(Foundation_keyword_iterator, draft4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string",
    "properties": {},
    "patternProperties": {},
    "required": [ "foo" ],
    "additionalProperties": true,
    "additionalItems": true,
    "items": []
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-04/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 8);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-04/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/items");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("[]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer), "/required");
  EXPECT_EQ(entries.at(3).subschema.get(),
            sourcemeta::core::parse_json("[ \"foo\" ]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(4).pointer),
            "/additionalItems");
  EXPECT_EQ(entries.at(4).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(5).pointer), "/properties");
  EXPECT_EQ(entries.at(5).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(6).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(6).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(7).pointer), "/type");
  EXPECT_EQ(entries.at(7).subschema.get(), sourcemeta::core::JSON{"string"});
}

TEST(Foundation_keyword_iterator, draft3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true,
    "additionalItems": true,
    "items": []
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-03/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 7);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-03/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/items");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("[]"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer), "/properties");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(4).pointer), "/type");
  EXPECT_EQ(entries.at(4).subschema.get(), sourcemeta::core::JSON{"string"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(5).pointer),
            "/additionalItems");
  EXPECT_EQ(entries.at(5).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(6).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(6).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, draft2) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-02/schema#",
    "type": "string",
    "properties": {},
    "additionalProperties": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-02/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_2_Hyper);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 4);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-02/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/properties");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/type");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::JSON{"string"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, draft1) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#",
    "type": "string",
    "properties": {},
    "additionalProperties": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-01/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_1_Hyper);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 4);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-01/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/properties");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/type");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::JSON{"string"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, draft0) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "string",
    "properties": {},
    "additionalProperties": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "http://json-schema.org/draft-00/schema#");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
    EXPECT_EQ(entry.vocabularies.size(), 1);
  }

  EXPECT_EQ(entries.size(), 4);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(entries.at(0).subschema.get(),
            sourcemeta::core::JSON{"http://json-schema.org/draft-00/schema#"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/properties");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/type");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::JSON{"string"});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(3).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, unknown_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foobar": 0
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/$schema");
  EXPECT_EQ(
      entries.at(0).subschema.get(),
      sourcemeta::core::JSON{"https://json-schema.org/draft/2020-12/schema"});
  EXPECT_EQ(entries.at(0).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(0).base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_EQ(entries.at(0).vocabularies.size(), 7);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/foobar");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::JSON{0});
  EXPECT_EQ(entries.at(1).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(1).base_dialect,
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_EQ(entries.at(1).vocabularies.size(), 7);
}

TEST(Foundation_keyword_iterator, with_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver,
           "https://json-schema.org/draft/2020-12/schema")) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_EQ(entry.dialect, "https://json-schema.org/draft/2020-12/schema");
    EXPECT_TRUE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
    EXPECT_EQ(entry.vocabularies.size(), 7);
  }

  EXPECT_EQ(entries.size(), 3);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(0).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/properties");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::JSON{true});
}

TEST(Foundation_keyword_iterator, no_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "properties": {},
    "patternProperties": {},
    "additionalProperties": true
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);

    // The same for all entries
    EXPECT_TRUE(entry.dialect.empty());
    EXPECT_FALSE(entry.base_dialect.has_value());
    EXPECT_EQ(entry.vocabularies.size(), 0);
  }

  EXPECT_EQ(entries.size(), 3);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer),
            "/additionalProperties");
  EXPECT_EQ(entries.at(0).subschema.get(), sourcemeta::core::JSON{true});

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/patternProperties");
  EXPECT_EQ(entries.at(1).subschema.get(), sourcemeta::core::parse_json("{}"));

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/properties");
  EXPECT_EQ(entries.at(2).subschema.get(), sourcemeta::core::parse_json("{}"));
}

TEST(Foundation_keyword_iterator, boolean_true) {
  const sourcemeta::core::JSON document{true};

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_TRUE(entries.empty());
}

TEST(Foundation_keyword_iterator, boolean_false) {
  const sourcemeta::core::JSON document{false};

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaKeywordIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_TRUE(entries.empty());
}
