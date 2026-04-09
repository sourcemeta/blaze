#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_canonicalize_draft0, boolean_true_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "properties": {
      "foo": true
    }
  })JSON");

  CANONICALIZE(document, result, traces);

  EXPECT_TRUE(result.first);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": [ "null", "boolean", "object", "array", "string", "number" ],
    "properties": {
      "foo": true
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
