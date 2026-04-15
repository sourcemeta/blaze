#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(Evaluator_draft6, metaschema) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-06/schema#")};
  EXPECT_TRUE(metaschema.has_value());

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), instance, 2, "");
}

TEST(Evaluator_draft6, metaschema_hyper_self) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-06/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_FAST_SUCCESS(metaschema.value(), metaschema.value(), 861,
                                   "");
}

TEST(Evaluator_draft6, metaschema_hyper_self_exhaustive) {
  const auto metaschema{sourcemeta::core::schema_resolver(
      "http://json-schema.org/draft-06/hyper-schema#")};
  EXPECT_TRUE(metaschema.has_value());
  EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(metaschema.value(), metaschema.value(),
                                         1103, "");
}

TEST(Evaluator_draft6, exclusiveMinimum_5) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{10};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(Evaluator_draft6, exclusiveMinimum_6) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMinimum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(Evaluator_draft6, exclusiveMinimum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMinimum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{3.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(Evaluator_draft6, exclusiveMinimum_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be greater than the number 2.5, "
      "but they were equal");
}

TEST(Evaluator_draft6, exclusiveMinimum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"10"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 10 was expected to be greater than the integer 5");
}

TEST(Evaluator_draft6, exclusiveMinimum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be greater than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMinimum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 3.0 was expected to be greater than the number 2.5");
}

TEST(Evaluator_draft6, exclusiveMinimum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMinimum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be greater than the number 2.5, "
      "but they were equal");
}

TEST(Evaluator_draft6, exclusiveMinimum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.7"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.7 was expected to be greater than the number 0.5");
}

TEST(Evaluator_draft6, exclusiveMinimum_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMinimum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionGreater, "/exclusiveMinimum",
                     "#/exclusiveMinimum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionGreater, "/exclusiveMinimum",
                              "#/exclusiveMinimum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be greater than the number 0.5, "
      "but they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_5) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{3};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(Evaluator_draft6, exclusiveMaximum_6) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_7) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(Evaluator_draft6, exclusiveMaximum_8) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_9) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.0};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(Evaluator_draft6, exclusiveMaximum_10) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"2.5"}});

  const sourcemeta::core::JSON instance{2.5};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be less than the number 2.5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 3 was expected to be less than the integer 5");
}

TEST(Evaluator_draft6, exclusiveMaximum_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The integer value 5 was expected to be less than the integer 5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_13) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.0 was expected to be less than the number 2.5");
}

TEST(Evaluator_draft6, exclusiveMaximum_14) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "exclusiveMaximum": 2.5
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"2.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 2.5 was expected to be less than the number 2.5, but "
      "they were equal");
}

TEST(Evaluator_draft6, exclusiveMaximum_17) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.3"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.3 was expected to be less than the number 0.5");
}

TEST(Evaluator_draft6, exclusiveMaximum_18) {
  auto schema{sourcemeta::core::JSON::make_object()};
  schema.assign_assume_new(
      "$schema",
      sourcemeta::core::JSON{"http://json-schema.org/draft-06/schema#"});
  schema.assign_assume_new(
      "exclusiveMaximum",
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"0.5"}});

  const sourcemeta::core::JSON instance{sourcemeta::core::Decimal{"0.5"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");
  EVALUATE_TRACE_PRE(0, AssertionLess, "/exclusiveMaximum",
                     "#/exclusiveMaximum", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionLess, "/exclusiveMaximum",
                              "#/exclusiveMaximum", "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The number value 0.5 was expected to be less than the number 0.5, but "
      "they were equal");
}

TEST(Evaluator_draft6, propertyNames_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "propertyNames": { "minLength": 3 }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 3, "");

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"foo\", and \"bar\" were expected to "
        "validate against the given subschema");
  } else {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"bar\", and \"foo\" were expected to "
        "validate against the given subschema");
  }
}

TEST(Evaluator_draft6, propertyNames_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "propertyNames": { "minLength": 3 }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"bar\": 2, \"fo\": 1 }")};

  if (FIRST_PROPERTY_IS(instance, "fo")) {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/fo");

    EVALUATE_TRACE_POST_FAILURE(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/fo");
    EVALUATE_TRACE_POST_FAILURE(1, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 0,
        "The object property name \"fo\" was expected to consist of at least 3 "
        "characters but it consisted of 2 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object properties \"fo\", and \"bar\" were expected to validate "
        "against the given subschema");
  } else {
    EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 3, "");

    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/fo");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_FAILURE(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/fo");
    EVALUATE_TRACE_POST_FAILURE(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 1,
        "The object property name \"fo\" was expected to consist of at least 3 "
        "characters but it consisted of 2 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"bar\", and \"fo\" were expected to validate "
        "against the given subschema");
  }
}

TEST(Evaluator_draft6, propertyNames_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object",
    "propertyNames": { "minLength": 3 }
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::parse_json("{ \"foo\": 1, \"bar\": 2 }")};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 4, "");

  if (FIRST_PROPERTY_IS(instance, "foo")) {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");
    EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"foo\", and \"bar\" were expected to "
        "validate against the given subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                                 "The value was expected to be of type object");
  } else {
    EVALUATE_TRACE_PRE(0, LoopKeys, "/propertyNames", "#/propertyNames", "");
    EVALUATE_TRACE_PRE(1, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/bar");
    EVALUATE_TRACE_PRE(2, AssertionStringSizeGreater,
                       "/propertyNames/minLength", "#/propertyNames/minLength",
                       "/foo");
    EVALUATE_TRACE_PRE(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_SUCCESS(0, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/bar");
    EVALUATE_TRACE_POST_SUCCESS(1, AssertionStringSizeGreater,
                                "/propertyNames/minLength",
                                "#/propertyNames/minLength", "/foo");
    EVALUATE_TRACE_POST_SUCCESS(2, LoopKeys, "/propertyNames",
                                "#/propertyNames", "");
    EVALUATE_TRACE_POST_SUCCESS(3, AssertionTypeStrict, "/type", "#/type", "");

    EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                                 "The object property name \"bar\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 1,
                                 "The object property name \"foo\" was "
                                 "expected to consist of at least 3 "
                                 "characters and it consisted of 3 characters");
    EVALUATE_TRACE_POST_DESCRIBE(
        instance, 2,
        "The object properties \"bar\", and \"foo\" were expected to "
        "validate against the given subschema");
    EVALUATE_TRACE_POST_DESCRIBE(instance, 3,
                                 "The value was expected to be of type object");
  }
}

TEST(Evaluator_draft6, invalid_ref_top_level) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/i-dont-exist"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft6, invalid_ref_nested) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {
        "$ref": "#/definitions/i-dont-exist"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft6, invalid_ref_embedded) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "http://json-schema.org/draft-06/schema#",
    "additionalProperties": {
      "$ref": "#/definitions/bar"
    },
    "definitions": {
      "bar": {
        "$id": "https://example.com/nested",
        "additionalProperties": {
          "$ref": "#/definitions/baz"
        }
      },
      "baz": {}
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (const sourcemeta::core::SchemaReferenceError &error) {
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer(
                  {"definitions", "bar", "additionalProperties", "$ref"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft6, reference_from_unknown_keyword) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "$ref": "#/$defs/bar" },
      "baz": { "type": "string" }
    },
    "$defs": {
      "bar": {
        "$ref": "#/properties/baz"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
  } catch (
      const sourcemeta::blaze::CompilerReferenceTargetNotSchemaError &error) {
    EXPECT_EQ(error.identifier(), "#/$defs/bar");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"$defs"}));
  } catch (...) {
    throw;
  }
}

TEST(Evaluator_draft6, top_level_ref_with_id) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::FastValidation),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft6, top_level_ref_with_id_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {}
    }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler,
                                 sourcemeta::blaze::Mode::Exhaustive),
      sourcemeta::core::SchemaError);
}

TEST(Evaluator_draft6, type_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft6, type_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft6, type_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "integer"
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.1"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionType, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft6, type_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string and it was of type integer");
}

TEST(Evaluator_draft6, type_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.0"}};
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionTypeAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string and it was of type integer");
}

TEST(Evaluator_draft6, type_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": [ "integer", "string" ]
  })JSON")};

  const sourcemeta::core::JSON instance{
      sourcemeta::core::Decimal{"99999999999999999999999999999999999.1"}};
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeAny, "/type", "#/type", "");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer, "
                               "or string but it was of type number");
}

TEST(Evaluator_draft6, properties_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyType, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyType, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft6, properties_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyType, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_SUCCESS(0, AssertionPropertyType, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The value was expected to be of type integer");
}

TEST(Evaluator_draft6, properties_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "type": "integer" }
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.1"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionPropertyType, "/properties/foo/type",
                     "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionPropertyType, "/properties/foo/type",
                              "#/properties/foo/type", "/foo");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be of type integer but it was of type number");
}

TEST(Evaluator_draft6, properties_10) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    },
    "additionalProperties": false
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999"}});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesType, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesType, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft6, properties_11) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    },
    "additionalProperties": false
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.0"}});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.0"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesType, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_SUCCESS(1, LoopPropertiesType, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft6, properties_12) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "required": [ "foo", "bar" ],
    "properties": {
      "foo": { "type": "integer" },
      "bar": { "type": "integer" }
    },
    "additionalProperties": false
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_object()};
  instance.assign_assume_new("foo",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.1"}});
  instance.assign_assume_new("bar",
                             sourcemeta::core::JSON{sourcemeta::core::Decimal{
                                 "99999999999999999999999999999999999.1"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 2, "");

  EVALUATE_TRACE_PRE(0, AssertionDefinesExactly, "/required", "#/required", "");
  EVALUATE_TRACE_PRE(1, LoopPropertiesType, "/properties", "#/properties", "");

  EVALUATE_TRACE_POST_SUCCESS(0, AssertionDefinesExactly, "/required",
                              "#/required", "");
  EVALUATE_TRACE_POST_FAILURE(1, LoopPropertiesType, "/properties",
                              "#/properties", "");

  EVALUATE_TRACE_POST_DESCRIBE(instance, 0,
                               "The object value was expected to only define "
                               "properties \"bar\", and \"foo\"");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 1, "The object properties were expected to be of type integer");
}

TEST(Evaluator_draft6, items_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "type": "integer"
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"11111111111111111111111111111111111"}});
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"22222222222222222222222222222222222"}});
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"33333333333333333333333333333333333"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsType, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsType, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type integer");
}

TEST(Evaluator_draft6, items_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "type": "integer"
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"11111111111111111111111111111111111.0"}});
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"22222222222222222222222222222222222.0"}});
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"33333333333333333333333333333333333.0"}});

  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsType, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsType, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type integer");
}

TEST(Evaluator_draft6, items_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": {
      "type": "integer"
    }
  })JSON")};

  auto instance{sourcemeta::core::JSON::make_array()};
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"11111111111111111111111111111111111.1"}});
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"22222222222222222222222222222222222.2"}});
  instance.push_back(sourcemeta::core::JSON{
      sourcemeta::core::Decimal{"33333333333333333333333333333333333.3"}});

  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsType, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsType, "/items", "#/items", "");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0, "The array items were expected to be of type integer");
}
