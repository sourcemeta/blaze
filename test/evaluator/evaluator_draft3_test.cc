#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft3, metaschema_1) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 3, "");
}

TEST(Evaluator_draft3, metaschema_2) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const auto instance{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string", "required": true }
    }
  })JSON")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 13, "");
}

TEST(Evaluator_draft3, metaschema_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 312,
                                   "");
}

TEST(Evaluator_draft3, metaschema_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-03/schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         328, "");
}

TEST(Evaluator_draft3, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-03/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 73,
                                   "");
}

TEST(Evaluator_draft3, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-03/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         83, "");
}

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

TEST(Evaluator_draft3, type_integer_invalid_decimal_1e0_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1e0_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1_5e1_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e1")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1_5e1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e1")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1_5e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1_5e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_30e_minus_1_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("30e-1")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_30e_minus_1_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("30e-1")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1e_minus_2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e-2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_invalid_decimal_1e_minus_2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e-2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type "
      "number");
}

TEST(Evaluator_draft3, type_integer_valid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft3, type_integer_valid_decimal_lexical_bignum_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft3, type_array_integer_string_invalid_decimal_1e0_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft3,
     type_array_integer_string_invalid_decimal_1e0_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft3, type_array_integer_string_invalid_decimal_1_5e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft3,
     type_array_integer_string_invalid_decimal_1_5e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1.5e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string but it was of "
      "type number");
}

TEST(Evaluator_draft3,
     type_array_integer_string_valid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string and it was of "
      "type integer");
}

TEST(Evaluator_draft3,
     type_array_integer_string_valid_decimal_lexical_bignum_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer, or string and it was of "
      "type integer");
}

TEST(Evaluator_draft3, disallow_integer_valid_decimal_1e0_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The value was expected to NOT be of type integer");
}

TEST(Evaluator_draft3, disallow_integer_valid_decimal_1e0_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e0")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The value was expected to NOT be of type integer");
}

TEST(Evaluator_draft3, disallow_integer_valid_decimal_1e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The value was expected to NOT be of type integer");
}

TEST(Evaluator_draft3, disallow_integer_valid_decimal_1e2_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The value was expected to NOT be of type integer");
}

TEST(Evaluator_draft3, disallow_integer_invalid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to NOT be of type integer but it was of type "
      "integer");
}

TEST(Evaluator_draft3,
     disallow_integer_invalid_decimal_lexical_bignum_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "disallow": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionNotTypeStrictAny, "/disallow", "#/disallow",
                     "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionNotTypeStrictAny, "/disallow",
                              "#/disallow", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to NOT be of type integer but it was of type "
      "integer");
}

TEST(Evaluator_draft3, type_number_valid_decimal_1e2_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("1e2")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft3, type_number_valid_decimal_lexical_bignum_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "number"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      "12345678910111213141516171819202122232425262728293031")};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrictAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type number");
}

TEST(Evaluator_draft3, format_date_time_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15T14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15T14:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_draft3, format_date_time_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-date\" was expected to represent a valid RFC "
      "3339 date-time");
}

TEST(Evaluator_draft3, format_date_time_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_date_time_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"2026-05-15T14:00:00Z"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2026-05-15T14:00:00Z\" was expected to represent a "
      "valid RFC 3339 date-time");
}

TEST(Evaluator_draft3, format_date_time_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-a-date\" was expected to represent a valid RFC "
      "3339 date-time");
}

TEST(Evaluator_draft3, format_date_time_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-a-date"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_email_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_draft3, format_email_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a valid "
      "email address");
}

TEST(Evaluator_draft3, format_email_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_email_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"user@example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"user@example.com\" was expected to represent a "
      "valid email address");
}

TEST(Evaluator_draft3, format_email_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not-an-email\" was expected to represent a valid "
      "email address");
}

TEST(Evaluator_draft3, format_email_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{"not-an-email"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_host_name_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{"www.example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"www.example.com\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_draft3, format_host_name_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_draft3, format_host_name_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_host_name_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{"www.example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"www.example.com\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_draft3, format_host_name_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"-bad-host\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_draft3, format_host_name_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_ip_address_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{"192.168.1.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"192.168.1.1\" was expected to represent a valid "
      "IPv4 address");
}

TEST(Evaluator_draft3, format_ip_address_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a valid IPv4 "
      "address");
}

TEST(Evaluator_draft3, format_ip_address_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_ip_address_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{"192.168.1.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"192.168.1.1\" was expected to represent a valid "
      "IPv4 address");
}

TEST(Evaluator_draft3, format_ip_address_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a valid IPv4 "
      "address");
}

TEST(Evaluator_draft3, format_ip_address_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_ipv6_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"2001:db8::1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2001:db8::1\" was expected to represent a valid "
      "IPv6 address");
}

TEST(Evaluator_draft3, format_ipv6_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not an address\" was expected to represent a valid "
      "IPv6 address");
}

TEST(Evaluator_draft3, format_ipv6_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_ipv6_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"2001:db8::1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"2001:db8::1\" was expected to represent a valid "
      "IPv6 address");
}

TEST(Evaluator_draft3, format_ipv6_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"not an address\" was expected to represent a valid "
      "IPv6 address");
}

TEST(Evaluator_draft3, format_ipv6_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{"not an address"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_uri_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com/path\" was expected to represent "
      "a valid URI");
}

TEST(Evaluator_draft3, format_uri_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft3, format_uri_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_uri_valid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com/path\" was expected to represent "
      "a valid URI");
}

TEST(Evaluator_draft3, format_uri_invalid_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE_TWEAKED(schema, instance, 1, "",
                                                 tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft3, format_uri_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_unknown_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "not-a-real-format"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_unknown_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "not-a-real-format"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_keyword_value_integer_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": 42
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_keyword_value_integer_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": 42
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_keyword_value_null_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": null
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_keyword_value_null_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": null
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_date_time_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_date_time_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date-time"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_email_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_email_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "email"
  })JSON")};

  const sourcemeta::core::JSON instance{true};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_host_name_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_host_name_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "host-name"
  })JSON")};

  const sourcemeta::core::JSON instance{nullptr};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_ip_address_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_ip_address_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ip-address"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_ipv6_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_ipv6_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv6"
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_uri_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_uri_non_string_with_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{3.14};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS_TWEAKED(schema, instance, 0, "",
                                                 tweaks);
}

TEST(Evaluator_draft3, format_ipv4_treated_as_custom_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "ipv4"
  })JSON")};

  const sourcemeta::core::JSON instance{"999.0.0.1"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_hostname_treated_as_custom_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "hostname"
  })JSON")};

  const sourcemeta::core::JSON instance{"-bad-host"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_uri_reference_treated_as_custom_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "uri-reference"
  })JSON")};

  const sourcemeta::core::JSON instance{"://bad"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 0, "", tweaks);
}

TEST(Evaluator_draft3, format_date_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_date_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_date_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"date\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_date_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "date"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"date\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_time_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_time_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "time"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_time_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "time"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"time\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_time_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "time"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"time\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_utc_millisec_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "utc-millisec"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_utc_millisec_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "utc-millisec"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_utc_millisec_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "utc-millisec"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(
        error.what(),
        "The \"utc-millisec\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_utc_millisec_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "utc-millisec"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(
        error.what(),
        "The \"utc-millisec\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_regex_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_regex_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "regex"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_regex_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "regex"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"regex\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_regex_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "regex"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"regex\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_color_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "color"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_color_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "color"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_color_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "color"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"color\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_color_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "color"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"color\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_style_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "style"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_style_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "style"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_style_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "style"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"style\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_style_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "style"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"style\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_phone_no_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "phone"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_phone_no_tweak_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "phone"
  })JSON")};

  const sourcemeta::core::JSON instance{"anything"};

  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, 0, "");
}

TEST(Evaluator_draft3, format_phone_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "phone"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"phone\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_phone_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "phone"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"phone\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(Evaluator_draft3, format_under_properties_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "x": { "format": "uri" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON({ "x": "https://example.com" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/x/format",
                     "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/properties/x/format",
                              "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
}

TEST(Evaluator_draft3, format_under_properties_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "x": { "format": "ip-address" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json(R"JSON({ "x": "999.0.0.1" })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/properties/x/format",
                     "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/properties/x/format",
                              "#/properties/x/format", "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"999.0.0.1\" was expected to represent a valid IPv4 "
      "address");
}

TEST(Evaluator_draft3, format_under_items_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": { "format": "host-name" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON([ "www.example.com", "www.example.org" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/items/format", "#/items/format",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/items/format", "#/items/format",
                     "/1");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/items/format",
                              "#/items/format", "/0");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringType, "/items/format",
                              "#/items/format", "/1");
  EVALUATE_TRACE_POST_SUCCESS(2, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"www.example.com\" was expected to represent a valid "
      "hostname");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value \"www.example.org\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_draft3, format_under_items_invalid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": { "format": "host-name" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(
      R"JSON([ "www.example.com", "-bad-host" ])JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 3, "", tweaks);

  EVALUATE_TRACE_PRE(0, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_PRE(1, AssertionStringType, "/items/format", "#/items/format",
                     "/0");
  EVALUATE_TRACE_PRE(2, AssertionStringType, "/items/format", "#/items/format",
                     "/1");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/items/format",
                              "#/items/format", "/0");
  EVALUATE_TRACE_POST_FAILURE(1, AssertionStringType, "/items/format",
                              "#/items/format", "/1");
  EVALUATE_TRACE_POST_FAILURE(2, LoopItems, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"www.example.com\" was expected to represent a valid "
      "hostname");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1,
      "The string value \"-bad-host\" was expected to represent a valid "
      "hostname");
}

TEST(Evaluator_draft3, format_with_type_string_valid_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"https://example.com"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 2, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_PRE(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_SUCCESS(1, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"https://example.com\" was expected to represent a "
      "valid URI");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                               "The value was expected to be of type string");
}

TEST(Evaluator_draft3, format_with_type_string_invalid_format_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{"relative/path"};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionStringType, "/format", "#/format", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionStringType, "/format", "#/format",
                              "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The string value \"relative/path\" was expected to represent a valid "
      "URI");
}

TEST(Evaluator_draft3, format_with_type_string_non_string_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_FAILURE_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type string but it was of type integer");
}

TEST(Evaluator_draft3,
     format_with_type_integer_short_circuits_with_tweak_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "integer",
    "format": "uri"
  })JSON")};

  const sourcemeta::core::JSON instance{42};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  EVALUATE_WITH_TRACE_FAST_SUCCESS_TWEAKED(schema, instance, 1, "", tweaks);

  EVALUATE_TRACE_PRE(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeStrict, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}
