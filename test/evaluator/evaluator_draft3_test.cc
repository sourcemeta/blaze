#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft3, type_integer_invalid_real_integer_valued_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_real_integer_valued_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3,
     type_array_integer_string_invalid_real_integer_valued_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft3,
     type_array_integer_string_invalid_real_integer_valued_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft3, enum_real_value_equals_integer_member_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 3 ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft3, enum_real_value_equals_integer_member_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "enum": [ 3 ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionEqual, "/enum", "#/enum", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to equal the integer constant 3");
}

TEST(Evaluator_draft3, disallow_integer_invalid_real_integer_valued_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The value was expected to NOT be of type integer");
}

TEST(Evaluator_draft3,
     disallow_integer_invalid_real_integer_valued_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("3.0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The value was expected to NOT be of type integer");
}
