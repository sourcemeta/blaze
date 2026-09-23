#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/convert.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#define UPGRADE_BOOLEAN(document, target)                                      \
  {                                                                            \
    auto schema = sourcemeta::core::parse_json(document);                      \
    const auto expected = sourcemeta::core::parse_json(document);              \
    sourcemeta::blaze::convert(schema, sourcemeta::core::schema_walker,        \
                               sourcemeta::core::schema_resolver,              \
                               sourcemeta::blaze::ConvertTarget::target);      \
    EXPECT_EQ(schema, expected);                                               \
  }

#define UPGRADE_BOOLEAN_WITH_DIALECT(document, target, default_dialect)        \
  {                                                                            \
    auto schema = sourcemeta::core::parse_json(document);                      \
    const auto expected = sourcemeta::core::parse_json(document);              \
    sourcemeta::blaze::convert(schema, sourcemeta::core::schema_walker,        \
                               sourcemeta::core::schema_resolver,              \
                               sourcemeta::blaze::ConvertTarget::target,       \
                               (default_dialect));                             \
    EXPECT_EQ(schema, expected);                                               \
  }

TEST(true_to_draft4) { UPGRADE_BOOLEAN("true", Draft4); }

TEST(true_to_draft6) { UPGRADE_BOOLEAN("true", Draft6); }

TEST(true_to_draft7) { UPGRADE_BOOLEAN("true", Draft7); }

TEST(true_to_2019_09) { UPGRADE_BOOLEAN("true", Draft201909); }

TEST(true_to_2020_12) { UPGRADE_BOOLEAN("true", Draft202012); }

TEST(false_to_draft4) { UPGRADE_BOOLEAN("false", Draft4); }

TEST(false_to_draft6) { UPGRADE_BOOLEAN("false", Draft6); }

TEST(false_to_draft7) { UPGRADE_BOOLEAN("false", Draft7); }

TEST(false_to_2019_09) { UPGRADE_BOOLEAN("false", Draft201909); }

TEST(false_to_2020_12) { UPGRADE_BOOLEAN("false", Draft202012); }

TEST(true_to_2020_12_with_default_dialect_draft6) {
  UPGRADE_BOOLEAN_WITH_DIALECT("true", Draft202012,
                               "http://json-schema.org/draft-06/schema#");
}

TEST(false_to_2020_12_with_default_dialect_draft6) {
  UPGRADE_BOOLEAN_WITH_DIALECT("false", Draft202012,
                               "http://json-schema.org/draft-06/schema#");
}

TEST(true_to_2020_12_with_default_dialect_draft7) {
  UPGRADE_BOOLEAN_WITH_DIALECT("true", Draft202012,
                               "http://json-schema.org/draft-07/schema#");
}

TEST(false_to_2020_12_with_default_dialect_draft7) {
  UPGRADE_BOOLEAN_WITH_DIALECT("false", Draft202012,
                               "http://json-schema.org/draft-07/schema#");
}

TEST(true_to_2020_12_with_default_dialect_draft4) {
  UPGRADE_BOOLEAN_WITH_DIALECT("true", Draft202012,
                               "http://json-schema.org/draft-04/schema#");
}

TEST(false_to_2020_12_with_default_dialect_draft4) {
  UPGRADE_BOOLEAN_WITH_DIALECT("false", Draft202012,
                               "http://json-schema.org/draft-04/schema#");
}

TEST(true_to_draft4_with_default_dialect_draft3) {
  UPGRADE_BOOLEAN_WITH_DIALECT("true", Draft4,
                               "http://json-schema.org/draft-03/schema#");
}

TEST(false_to_draft4_with_default_dialect_draft3) {
  UPGRADE_BOOLEAN_WITH_DIALECT("false", Draft4,
                               "http://json-schema.org/draft-03/schema#");
}

TEST(true_to_2020_12_with_default_dialect_2019_09) {
  UPGRADE_BOOLEAN_WITH_DIALECT("true", Draft202012,
                               "https://json-schema.org/draft/2019-09/schema");
}

TEST(false_to_2020_12_with_default_dialect_2019_09) {
  UPGRADE_BOOLEAN_WITH_DIALECT("false", Draft202012,
                               "https://json-schema.org/draft/2019-09/schema");
}
