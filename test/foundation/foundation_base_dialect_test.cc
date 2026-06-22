#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/metaschema_1") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/metaschema_1",
      "$schema": "https://sourcemeta.com/metaschema_1"
    })JSON");
  } else if (identifier == "https://sourcemeta.com/metaschema_2") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/metaschema_2",
      "$schema": "https://sourcemeta.com/metaschema_1"
    })JSON");
  } else if (identifier == "https://sourcemeta.com/no-schema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/no-schema"
    })JSON");
  } else if (identifier == "https://sourcemeta.com/metaschema_3") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/metaschema_3",
      "$schema": "https://sourcemeta.com/no-schema"
    })JSON");
  } else if (identifier == "https://sourcemeta.com/metaschema_4") {
    return sourcemeta::core::parse_json(R"JSON({
      "$id": "https://sourcemeta.com/metaschema_4",
      "$schema": "https://sourcemeta.com/metaschema_4"
    })JSON");
  } else {
    return std::nullopt;
  }
}

TEST(Foundation_base_dialect, boolean_schema_true) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("true");
  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_FALSE(base_dialect.has_value());
}

TEST(Foundation_base_dialect, boolean_schema_false) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("false");
  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_FALSE(base_dialect.has_value());
}

TEST(Foundation_base_dialect, boolean_schema_default_dialect_official) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("true");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, boolean_schema_default_dialect_custom_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("true");
  EXPECT_THROW(
      sourcemeta::blaze::base_dialect(document, test_resolver,
                                      "https://sourcemeta.com/metaschema_1"),
      sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, self_descriptive_schema_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://example.com/my-schema"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_base_dialect, non_resolvable_schema_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://example.com/does-not-exist"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_base_dialect, relative_schema_uri_with_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "../foo.json"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaRelativeMetaschemaResolutionError);
}

TEST(Foundation_base_dialect, relative_schema_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "../foo.json"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaRelativeMetaschemaResolutionError);
}

TEST(Foundation_base_dialect, non_resolvable_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/does-not-exist"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_base_dialect, non_resolvable_default_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  EXPECT_THROW(
      sourcemeta::blaze::base_dialect(document, test_resolver,
                                      "https://example.com/does-not-exist"),
      sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_base_dialect, id_with_custom_metaschema_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/my-schema",
    "$schema": "https://sourcemeta.com/metaschema_1"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, no_id_with_custom_metaschema_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/metaschema_1"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, self_descriptive_custom_metaschema_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://sourcemeta.com/no-schema",
    "$schema": "https://sourcemeta.com/no-schema"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, metaschema_without_schema_one_hop_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/metaschema_3"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, id_self_descriptive_default_dialect_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://sourcemeta.com/foo-bar"
  })JSON");
  EXPECT_THROW(sourcemeta::blaze::base_dialect(
                   document, test_resolver, "https://sourcemeta.com/foo-bar"),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Foundation_base_dialect, id_default_dialect_custom_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://sourcemeta.com/foo-bar"
  })JSON");
  EXPECT_THROW(
      sourcemeta::blaze::base_dialect(document, test_resolver,
                                      "https://sourcemeta.com/metaschema_1"),
      sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, default_dialect_custom_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json("{}");
  EXPECT_THROW(
      sourcemeta::blaze::base_dialect(document, test_resolver,
                                      "https://sourcemeta.com/metaschema_1"),
      sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, default_dialect_precedence_custom_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/metaschema_4"
  })JSON");
  EXPECT_THROW(
      sourcemeta::blaze::base_dialect(document, test_resolver,
                                      "https://sourcemeta.com/metaschema_1"),
      sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, default_dialect_official_takes_precedence) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, test_resolver, "https://sourcemeta.com/metaschema_1")};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, override_takes_precedence_over_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");
  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, override_takes_precedence_over_default) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "http://json-schema.org/draft-04/schema#"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, test_resolver, "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(Foundation_base_dialect, override_unresolvable_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://example.com/does-not-exist"
  })JSON");

  try {
    sourcemeta::blaze::base_dialect(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/does-not-exist");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_base_dialect, to_string_2020_12) {
  EXPECT_EQ(sourcemeta::blaze::to_string(
                sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12),
            "https://json-schema.org/draft/2020-12/schema");
}

TEST(Foundation_base_dialect, to_string_2020_12_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12_Hyper),
      "https://json-schema.org/draft/2020-12/hyper-schema");
}

TEST(Foundation_base_dialect, to_string_2019_09) {
  EXPECT_EQ(sourcemeta::blaze::to_string(
                sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09),
            "https://json-schema.org/draft/2019-09/schema");
}

TEST(Foundation_base_dialect, to_string_2019_09_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09_Hyper),
      "https://json-schema.org/draft/2019-09/hyper-schema");
}

TEST(Foundation_base_dialect, to_string_draft7) {
  EXPECT_EQ(sourcemeta::blaze::to_string(
                sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7),
            "http://json-schema.org/draft-07/schema#");
}

TEST(Foundation_base_dialect, to_string_draft7_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7_Hyper),
      "http://json-schema.org/draft-07/hyper-schema#");
}

TEST(Foundation_base_dialect, to_string_draft6) {
  EXPECT_EQ(sourcemeta::blaze::to_string(
                sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6),
            "http://json-schema.org/draft-06/schema#");
}

TEST(Foundation_base_dialect, to_string_draft6_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6_Hyper),
      "http://json-schema.org/draft-06/hyper-schema#");
}

TEST(Foundation_base_dialect, to_string_draft4) {
  EXPECT_EQ(sourcemeta::blaze::to_string(
                sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4),
            "http://json-schema.org/draft-04/schema#");
}

TEST(Foundation_base_dialect, to_string_draft4_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4_Hyper),
      "http://json-schema.org/draft-04/hyper-schema#");
}

TEST(Foundation_base_dialect, to_string_draft3) {
  EXPECT_EQ(sourcemeta::blaze::to_string(
                sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3),
            "http://json-schema.org/draft-03/schema#");
}

TEST(Foundation_base_dialect, to_string_draft3_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3_Hyper),
      "http://json-schema.org/draft-03/hyper-schema#");
}

TEST(Foundation_base_dialect, to_string_draft2_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_2_Hyper),
      "http://json-schema.org/draft-02/hyper-schema#");
}

TEST(Foundation_base_dialect, to_string_draft1_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_1_Hyper),
      "http://json-schema.org/draft-01/hyper-schema#");
}

TEST(Foundation_base_dialect, to_string_draft0_hyper) {
  EXPECT_EQ(
      sourcemeta::blaze::to_string(
          sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper),
      "http://json-schema.org/draft-00/hyper-schema#");
}

TEST(Foundation_base_dialect, to_base_dialect_2020_12) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft/2020-12/schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, to_base_dialect_2020_12_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_2019_09) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft/2019-09/schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09);
}

TEST(Foundation_base_dialect, to_base_dialect_2019_09_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft/2019-09/hyper-schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft7) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-07/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
}

TEST(Foundation_base_dialect, to_base_dialect_draft7_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-07/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft6) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-06/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6);
}

TEST(Foundation_base_dialect, to_base_dialect_draft6_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-06/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft4) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(Foundation_base_dialect, to_base_dialect_draft4_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-04/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft3) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3);
}

TEST(Foundation_base_dialect, to_base_dialect_draft3_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-03/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft2_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-02/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_2_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft1_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-01/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_1_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft0_hyper) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft-00/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
}

TEST(Foundation_base_dialect, self_referencing_metaschema) {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/self",
    "$id": "https://example.com/self"
  })JSON")};

  const sourcemeta::blaze::SchemaResolver resolver{
      [&schema](std::string_view identifier)
          -> std::optional<sourcemeta::core::JSON> {
        if (identifier == "https://example.com/self") {
          return schema;
        }
        return sourcemeta::blaze::schema_resolver(identifier);
      }};

  EXPECT_THROW(sourcemeta::blaze::base_dialect(schema, resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, indirect_metaschema_cycle) {
  const auto schema_a{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/b",
    "$id": "https://example.com/a"
  })JSON")};

  const auto schema_b{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/a",
    "$id": "https://example.com/b"
  })JSON")};

  const sourcemeta::blaze::SchemaResolver resolver{
      [&](std::string_view identifier)
          -> std::optional<sourcemeta::core::JSON> {
        if (identifier == "https://example.com/a") {
          return schema_a;
        } else if (identifier == "https://example.com/b") {
          return schema_b;
        } else {
          return sourcemeta::blaze::schema_resolver(identifier);
        }
      }};

  EXPECT_THROW(sourcemeta::blaze::base_dialect(schema_a, resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, to_base_dialect_2020_12_http) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft/2020-12/schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, to_base_dialect_2020_12_hyper_http) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft/2020-12/hyper-schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_2019_09_http) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft/2019-09/schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09);
}

TEST(Foundation_base_dialect, to_base_dialect_2019_09_hyper_http) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "http://json-schema.org/draft/2019-09/hyper-schema")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft7_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-07/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
}

TEST(Foundation_base_dialect, to_base_dialect_draft7_hyper_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-07/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft6_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-06/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6);
}

TEST(Foundation_base_dialect, to_base_dialect_draft4_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-04/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(Foundation_base_dialect, to_base_dialect_draft3_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3);
}

TEST(Foundation_base_dialect, to_base_dialect_draft2_hyper_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-02/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_2_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft1_hyper_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-01/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_1_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_draft0_hyper_https) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://json-schema.org/draft-00/hyper-schema#")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_0_Hyper);
}

TEST(Foundation_base_dialect, to_base_dialect_unknown) {
  const auto result{sourcemeta::blaze::to_base_dialect(
      "https://example.com/unknown-dialect")};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_base_dialect, to_base_dialect_empty) {
  const auto result{sourcemeta::blaze::to_base_dialect("")};
  EXPECT_FALSE(result.has_value());
}

TEST(Foundation_base_dialect, override_disallowed_returns_schema_base) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver, "", false)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(Foundation_base_dialect, override_disallowed_with_unresolvable_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://example.com/does-not-exist"
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver, "", false)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, override_disallowed_with_default_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "x-sourcemeta-dialect-override-subschema":
      "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, test_resolver, "http://json-schema.org/draft-07/schema#",
      false)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_2019_09) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2019_09);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_draft4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_chain) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_chain_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_7);
}

TEST(Foundation_base_dialect,
     embedded_custom_metaschema_non_canonical_dialect_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta#",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_wrong_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  try {
    sourcemeta::blaze::base_dialect(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_definitions_2020_12) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  // In 2019-09 and 2020-12, `definitions` is still supported
  // for backwards compatibility
  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_2020_12);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  try {
    sourcemeta::blaze::base_dialect(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_base_dialect,
     embedded_custom_metaschema_draft4_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      }
    }
  })JSON");

  try {
    sourcemeta::blaze::base_dialect(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_self_descriptive) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://example.com/meta",
        "type": "object"
      }
    }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_cyclic) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://example.com/meta-a",
        "type": "object"
      }
    }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::base_dialect(document, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_not_found) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/other": {
        "$id": "https://example.com/other",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object"
      }
    }
  })JSON");

  try {
    sourcemeta::blaze::base_dialect(document, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_relative_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "meta": {
        "$id": "meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  try {
    sourcemeta::blaze::base_dialect(document, test_resolver);
    FAIL();
  } catch (
      const sourcemeta::blaze::SchemaRelativeMetaschemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "meta");
  } catch (...) {
    FAIL();
  }
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_draft6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_6);
}

TEST(Foundation_base_dialect, embedded_custom_metaschema_draft3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_3);
}
