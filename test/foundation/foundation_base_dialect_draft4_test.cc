#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://sourcemeta.com/metaschema_1") {
    return sourcemeta::core::parse_json(R"JSON({
      "id": "https://sourcemeta.com/metaschema_1",
      "$schema": "http://json-schema.org/draft-04/schema#"
    })JSON");
  } else if (identifier == "https://sourcemeta.com/metaschema_2") {
    return sourcemeta::core::parse_json(R"JSON({
      "id": "https://sourcemeta.com/metaschema_2",
      "$schema": "https://sourcemeta.com/metaschema_1"
    })JSON");
  } else {
    return std::nullopt;
  }
}

TEST(jsonschema_draft_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/hyper-schema#",
    "type": "object"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4_Hyper);
}

TEST(jsonschema_draft_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(jsonschema_draft_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/links#"
  })JSON");
  const auto base_dialect{sourcemeta::blaze::base_dialect(
      document, sourcemeta::blaze::schema_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4_Hyper);
}

TEST(jsonschema_base_one_hop) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/metaschema_1"
  })JSON");
  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}

TEST(jsonschema_base_two_hops) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://sourcemeta.com/metaschema_2"
  })JSON");
  const auto base_dialect{
      sourcemeta::blaze::base_dialect(document, test_resolver)};
  EXPECT_TRUE(base_dialect.has_value());
  EXPECT_EQ(base_dialect.value(),
            sourcemeta::blaze::SchemaBaseDialect::JSON_Schema_Draft_4);
}
