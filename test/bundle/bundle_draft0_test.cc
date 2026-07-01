#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

#include <string>      // std::string
#include <string_view> // std::string_view

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://www.sourcemeta.com/test-1") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-00/schema#",
      "id": "https://www.sourcemeta.com/test-1",
      "type": "string"
    })JSON");
  } else if (identifier == "https://example.com/meta/1.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://example.com/meta/2.json",
      "id": "https://example.com/meta/1.json"
    })JSON");
  } else if (identifier == "https://example.com/meta/2.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-00/schema#",
      "id": "https://example.com/meta/2.json"
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(no_references_no_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(const_no_references_no_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  const auto result = sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(simple_bundling) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com",
    "$schema": "http://json-schema.org/draft-00/schema#",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-1" }
    }
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine how to perform bundling in this dialect");
  }
}

TEST(metaschema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(metaschema_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}
