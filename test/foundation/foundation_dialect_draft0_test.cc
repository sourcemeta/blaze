#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(jsonschema_draft_hyperschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/hyper-schema#",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-00/hyper-schema#");
}

TEST(jsonschema_draft_schema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-00/schema#");
}

TEST(jsonschema_draft_jsonref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/json-ref#"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-00/json-ref#");
}

TEST(jsonschema_draft_links) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/links#"
  })JSON");
  const auto dialect{sourcemeta::blaze::dialect(document)};
  EXPECT_EQ(dialect, "http://json-schema.org/draft-00/links#");
}
