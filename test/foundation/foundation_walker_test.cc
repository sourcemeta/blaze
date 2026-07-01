#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <vector>

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/test-metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://sourcemeta.com/test-metaschema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://sourcemeta.com/vocab/test-1": true
      }
    })JSON");
  } else if (identifier == "https://sourcemeta.com/custom-vocab") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://sourcemeta.com/custom-vocab",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://sourcemeta.com/vocab/test-2": true
      }
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

static auto test_walker(std::string_view keyword,
                        const sourcemeta::blaze::Vocabularies &vocabularies)
    -> const sourcemeta::blaze::SchemaWalkerResult & {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;

  if (vocabularies.get("https://sourcemeta.com/vocab/test-1").has_value()) {
    if (keyword == "schema") {
      static const SchemaWalkerResult result{
          SchemaKeywordType::ApplicatorValueTraverseSomeProperty,
          "https://sourcemeta.com/vocab/test-1",
          {},
          {},
          {}};
      return result;
    }

    if (keyword == "schemas") {
      static const SchemaWalkerResult result{
          SchemaKeywordType::ApplicatorElementsTraverseItem,
          "https://sourcemeta.com/vocab/test-1",
          {},
          {},
          {}};
      return result;
    }

    if (keyword == "schemaMap") {
      static const SchemaWalkerResult result{
          SchemaKeywordType::ApplicatorMembersTraversePropertyStatic,
          "https://sourcemeta.com/vocab/test-1",
          {},
          {},
          {}};
      return result;
    }

    if (keyword == "schemaOrSchemas") {
      static const SchemaWalkerResult result{
          SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem,
          "https://sourcemeta.com/vocab/test-1",
          {},
          {},
          {}};
      return result;
    }
  }

  if (vocabularies.get("https://sourcemeta.com/vocab/test-2").has_value()) {
    if (keyword == "custom") {
      static const SchemaWalkerResult result{
          SchemaKeywordType::ApplicatorValueTraverseSomeProperty,
          "https://sourcemeta.com/vocab/test-2",
          {},
          {},
          {}};
      return result;
    }
  }

  static const SchemaWalkerResult unknown{
      SchemaKeywordType::Unknown, "", {}, {}, {}};
  return unknown;
}

TEST(true) {
  const sourcemeta::core::JSON document{true};
  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 1);
  EXPECT_EQ(subschemas.at(0).is_boolean(), true);
  EXPECT_EQ(subschemas.at(0).to_boolean(), true);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_TRUE(entries.at(0).dialect.empty());
  EXPECT_FALSE(entries.at(0).base_dialect.has_value());
  EXPECT_TRUE(entries.at(0).vocabularies.empty());
}

TEST(false) {
  const sourcemeta::core::JSON document{false};
  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 1);
  EXPECT_EQ(subschemas.at(0).is_boolean(), true);
  EXPECT_EQ(subschemas.at(0).to_boolean(), false);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_TRUE(entries.at(0).dialect.empty());
  EXPECT_FALSE(entries.at(0).base_dialect.has_value());
  EXPECT_TRUE(entries.at(0).vocabularies.empty());
}

TEST(value) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "schema": {
        "foo": 1
      }
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 3);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "schema": {
        "foo": 1
      }
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "schema": {
      "foo": 1
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(2), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 3);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schema");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/schema/schema");
  EXPECT_EQ(entries.at(2).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(value_with_dialect_no_identifier) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "$schema": "https://json-schema.org/draft/2019-09/schema"
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 2);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "$schema": "https://json-schema.org/draft/2019-09/schema"
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON"));

  EXPECT_EQ(entries.size(), 2);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  // `$schema` outside a schema resource is ignored
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schema");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(value_invalid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": [ { "foo": 1 } ]
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 1);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": [ { "foo": 1 } ]
  })JSON"));

  EXPECT_EQ(entries.size(), 1);
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(elements) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemas": [ { "foo": 1 }, { "schema": { "bar": 2 } } ]
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 4);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemas": [ { "foo": 1 }, { "schema": { "bar": 2 } } ]
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));
  EXPECT_EQ(subschemas.at(2), sourcemeta::core::parse_json(R"JSON({
    "schema": { "bar": 2 }
  })JSON"));
  EXPECT_EQ(subschemas.at(3), sourcemeta::core::parse_json(R"JSON({
    "bar": 2
  })JSON"));

  EXPECT_EQ(entries.size(), 4);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schemas/0");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer), "/schemas/1");
  EXPECT_EQ(entries.at(2).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(3).pointer),
            "/schemas/1/schema");
  EXPECT_EQ(entries.at(3).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(3).base_dialect.has_value());
  EXPECT_EQ(entries.at(3).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(elements_invalid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemas": { "foo": 1 }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 1);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemas": { "foo": 1 }
  })JSON"));

  EXPECT_EQ(entries.size(), 1);
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(members) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaMap": {
      "foo": {
        "schema": {
          "bar": 1
        }
      }
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 3);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaMap": {
      "foo": {
        "schema": {
          "bar": 1
        }
      }
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "schema": { "bar": 1 }
  })JSON"));
  EXPECT_EQ(subschemas.at(2), sourcemeta::core::parse_json(R"JSON({
    "bar": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 3);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/schemaMap/foo");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/schemaMap/foo/schema");
  EXPECT_EQ(entries.at(2).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(members_invalid) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaMap": [ { "foo": 1 } ]
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 1);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaMap": [ { "foo": 1 } ]
  })JSON"));

  EXPECT_EQ(entries.size(), 1);
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(value_or_elements) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaOrSchemas": {
      "schemaOrSchemas": [
        { "foo": 1 }
      ]
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 3);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaOrSchemas": {
      "schemaOrSchemas": [
        { "foo": 1 }
      ]
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "schemaOrSchemas": [ { "foo": 1 } ]
  })JSON"));

  EXPECT_EQ(subschemas.at(2), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 3);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/schemaOrSchemas");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/schemaOrSchemas/schemaOrSchemas/0");
  EXPECT_EQ(entries.at(2).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(no_metaschema_and_no_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "schema": { "foo": 1 }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 1);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "schema": { "foo": 1 }
  })JSON"));

  EXPECT_EQ(entries.size(), 1);
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_TRUE(entries.at(0).dialect.empty());
  EXPECT_FALSE(entries.at(0).base_dialect.has_value());
}

TEST(no_metaschema_with_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "schema": {
      "schema": {
        "foo": 1
      }
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver,
           "https://sourcemeta.com/test-metaschema")) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 3);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "schema": {
      "schema": {
        "foo": 1
      }
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "schema": {
      "foo": 1
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(2), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 3);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schema");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/schema/schema");
  EXPECT_EQ(entries.at(2).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(unknown_keyword_from_other_vocab) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "custom": { "foo": 1 }
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 2);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "custom": { "foo": 1 }
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "custom": { "foo": 1 }
  })JSON"));

  EXPECT_EQ(entries.size(), 2);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schema");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(multi_metaschemas) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "$id": "https://www.example.com",
      "$schema": "https://sourcemeta.com/custom-vocab",
      "custom": { "foo": 1 }
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 3);
  EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "$id": "https://www.example.com",
      "$schema": "https://sourcemeta.com/custom-vocab",
      "custom": { "foo": 1 }
    }
  })JSON"));
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://sourcemeta.com/custom-vocab",
    "custom": { "foo": 1 }
  })JSON"));
  EXPECT_EQ(subschemas.at(2), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 3);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schema");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/custom-vocab");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/schema/custom");
  EXPECT_EQ(entries.at(2).dialect, "https://sourcemeta.com/custom-vocab");
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(flat) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "schema": { "foo": 1 }
    },
    "schemaMap": {
      "foo": {
        "schema": { "foo": 2 }
      }
    }
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIteratorFlat(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 2);
  EXPECT_EQ(entries.size(), 2);

  // We don't guarantee any specific ordering
  if (subschemas.at(0).at("schema").at("foo").to_integer() == 1) {
    EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
      "schema": { "foo": 1 }
    })JSON"));
    EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
      "schema": { "foo": 2 }
    })JSON"));

    EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer), "/schema");
    EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
    EXPECT_TRUE(entries.at(0).base_dialect.has_value());
    EXPECT_EQ(entries.at(0).base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

    EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
              "/schemaMap/foo");
    EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
    EXPECT_TRUE(entries.at(1).base_dialect.has_value());
    EXPECT_EQ(entries.at(1).base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  } else {
    EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
      "schema": { "foo": 1 }
    })JSON"));
    EXPECT_EQ(subschemas.at(0), sourcemeta::core::parse_json(R"JSON({
      "schema": { "foo": 2 }
    })JSON"));

    EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schema");
    EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
    EXPECT_TRUE(entries.at(1).base_dialect.has_value());
    EXPECT_EQ(entries.at(1).base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

    EXPECT_EQ(sourcemeta::core::to_string(entries.at(0).pointer),
              "/schemaMap/foo");
    EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
    EXPECT_TRUE(entries.at(0).base_dialect.has_value());
    EXPECT_EQ(entries.at(0).base_dialect.value(),
              sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  }
}

TEST(flat_non_modify) {
  const std::string json{R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": {
      "schema": { "foo": 1 }
    },
    "schemaMap": {
      "foo": {
        "schema": { "foo": 2 }
      }
    }
  })JSON"};

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(json);
  for (const auto &entry : sourcemeta::blaze::SchemaIteratorFlat(
           document, test_walker, test_resolver)) {
    sourcemeta::core::set(document, sourcemeta::core::to_pointer(entry.pointer),
                          sourcemeta::core::JSON{true});
  }

  EXPECT_EQ(document, sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schema": true,
    "schemaMap": {
      "foo": true
    }
  })JSON"));
}

TEST(flat_no_metaschema) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json(R"JSON({ "foo": 1 })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIteratorFlat(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 0);
  EXPECT_EQ(entries.size(), 0);
}

TEST(members_with_array) {
  const std::string json{R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaMap": {
      "foo": { "test": 1 },
      "bar": [ "baz" ]
    }
  })JSON"};

  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(json);
  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 2);
  EXPECT_EQ(subschemas.at(0), document);
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "test": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 2);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/schemaMap/foo");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(elements_with_string_items) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemas": [ { "foo": 1 }, "foo" ]
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 2);
  EXPECT_EQ(subschemas.at(0), document);
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 2);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/schemas/0");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(value_or_elements_with_string_items) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/test-metaschema",
    "schemaOrSchemas": [ { "foo": 1 }, "foo" ]
  })JSON");

  std::vector<sourcemeta::core::JSON> subschemas;
  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, test_walker, test_resolver)) {
    subschemas.push_back(sourcemeta::core::get(document, entry.pointer));
    entries.push_back(entry);
  }

  EXPECT_EQ(subschemas.size(), 2);
  EXPECT_EQ(subschemas.at(0), document);
  EXPECT_EQ(subschemas.at(1), sourcemeta::core::parse_json(R"JSON({
    "foo": 1
  })JSON"));

  EXPECT_EQ(entries.size(), 2);

  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);

  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/schemaOrSchemas/0");
  EXPECT_EQ(entries.at(1).dialect, "https://sourcemeta.com/test-metaschema");
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(override_at_root) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 1);

  EXPECT_FALSE(entries.at(0).parent.has_value());
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(0).vocabularies.size(), 7);
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_FALSE(entries.at(0).orphan);
  EXPECT_FALSE(entries.at(0).property_name);
}

TEST(override_does_not_inherit_to_children) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 2);

  EXPECT_FALSE(entries.at(0).parent.has_value());
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(0).vocabularies.size(), 7);
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_FALSE(entries.at(0).orphan);
  EXPECT_FALSE(entries.at(0).property_name);

  EXPECT_TRUE(entries.at(1).parent.has_value());
  EXPECT_TRUE(entries.at(1).parent.value().empty());
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/properties/foo");
  EXPECT_EQ(entries.at(1).dialect, "http://json-schema.org/draft-04/schema#");
  EXPECT_EQ(entries.at(1).vocabularies.size(), 1);
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
  EXPECT_FALSE(entries.at(1).orphan);
  EXPECT_FALSE(entries.at(1).property_name);
}

TEST(override_changes_child_discovery) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema",
    "items": [
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 1);

  EXPECT_FALSE(entries.at(0).parent.has_value());
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(0).vocabularies.size(), 7);
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_FALSE(entries.at(0).orphan);
  EXPECT_FALSE(entries.at(0).property_name);
}

TEST(override_applies_at_non_resource_subschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "x-sourcemeta-dialect-override-subschema":
          "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 2);

  EXPECT_FALSE(entries.at(0).parent.has_value());
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(0).vocabularies.size(), 7);
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_FALSE(entries.at(0).orphan);
  EXPECT_FALSE(entries.at(0).property_name);

  EXPECT_TRUE(entries.at(1).parent.has_value());
  EXPECT_TRUE(entries.at(1).parent.value().empty());
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/properties/foo");
  EXPECT_EQ(entries.at(1).dialect, "http://json-schema.org/draft-04/schema#");
  EXPECT_EQ(entries.at(1).vocabularies.size(), 1);
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
  EXPECT_FALSE(entries.at(1).orphan);
  EXPECT_FALSE(entries.at(1).property_name);
}

TEST(override_ignored_sibling_to_ref_in_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/definitions/bar",
        "$id": "https://example.com/foo",
        "x-sourcemeta-dialect-override-subschema":
          "https://json-schema.org/draft/2020-12/schema"
      }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 3);

  EXPECT_FALSE(entries.at(0).parent.has_value());
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect, "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(entries.at(0).vocabularies.size(), 1);
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
  EXPECT_FALSE(entries.at(0).orphan);
  EXPECT_FALSE(entries.at(0).property_name);

  EXPECT_TRUE(entries.at(1).parent.has_value());
  EXPECT_TRUE(entries.at(1).parent.value().empty());
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer),
            "/definitions/bar");
  EXPECT_EQ(entries.at(1).dialect, "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(entries.at(1).vocabularies.size(), 1);
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
  EXPECT_TRUE(entries.at(1).orphan);
  EXPECT_FALSE(entries.at(1).property_name);

  EXPECT_TRUE(entries.at(2).parent.has_value());
  EXPECT_TRUE(entries.at(2).parent.value().empty());
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/properties/foo");
  EXPECT_EQ(entries.at(2).dialect, "http://json-schema.org/draft-07/schema#");
  EXPECT_EQ(entries.at(2).vocabularies.size(), 1);
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
  EXPECT_FALSE(entries.at(2).orphan);
  EXPECT_FALSE(entries.at(2).property_name);
}

TEST(override_honored_sibling_to_ref_in_2019_09) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar",
        "$id": "https://example.com/foo",
        "x-sourcemeta-dialect-override-subschema":
          "https://json-schema.org/draft/2020-12/schema"
      }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 3);

  EXPECT_FALSE(entries.at(0).parent.has_value());
  EXPECT_TRUE(entries.at(0).pointer.empty());
  EXPECT_EQ(entries.at(0).dialect,
            "https://json-schema.org/draft/2019-09/schema");
  EXPECT_EQ(entries.at(0).vocabularies.size(), 6);
  EXPECT_TRUE(entries.at(0).base_dialect.has_value());
  EXPECT_EQ(entries.at(0).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09);
  EXPECT_FALSE(entries.at(0).orphan);
  EXPECT_FALSE(entries.at(0).property_name);

  EXPECT_TRUE(entries.at(1).parent.has_value());
  EXPECT_TRUE(entries.at(1).parent.value().empty());
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(1).pointer), "/$defs/bar");
  EXPECT_EQ(entries.at(1).dialect,
            "https://json-schema.org/draft/2019-09/schema");
  EXPECT_EQ(entries.at(1).vocabularies.size(), 6);
  EXPECT_TRUE(entries.at(1).base_dialect.has_value());
  EXPECT_EQ(entries.at(1).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09);
  EXPECT_TRUE(entries.at(1).orphan);
  EXPECT_FALSE(entries.at(1).property_name);

  EXPECT_TRUE(entries.at(2).parent.has_value());
  EXPECT_TRUE(entries.at(2).parent.value().empty());
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(2).pointer),
            "/properties/foo");
  EXPECT_EQ(entries.at(2).dialect,
            "https://json-schema.org/draft/2020-12/schema");
  EXPECT_EQ(entries.at(2).vocabularies.size(), 7);
  EXPECT_TRUE(entries.at(2).base_dialect.has_value());
  EXPECT_EQ(entries.at(2).base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
  EXPECT_FALSE(entries.at(2).orphan);
  EXPECT_FALSE(entries.at(2).property_name);
}
