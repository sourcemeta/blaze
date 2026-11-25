#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(pattern_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(pattern_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(pattern_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "id": "https://nested.com",
        "pattern": "^[a-zA-Z0-9\\/\\_]{1,32}$"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\/\\_]{1,32}$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com/");
  } catch (...) {
    FAIL();
  }
}

TEST(pattern_7) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "id": "https://nested.com",
        "pattern": "("
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "(");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"properties", "foo", "pattern"}));
    EXPECT_EQ(error.base().recompose(), "https://nested.com/");
  } catch (...) {
    FAIL();
  }
}

TEST(patternProperties_9) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": {
      "^[a-zA-Z0-9\\_\\.\\-]*$": { "type": "string" }
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler);
    // The pattern might succeed in some standard library implementations
  } catch (const sourcemeta::blaze::CompilerInvalidRegexError &error) {
    EXPECT_STREQ(error.what(), "Invalid regular expression");
    EXPECT_EQ(error.regex(), "^[a-zA-Z0-9\\_\\.\\-]*$");
    EXPECT_EQ(error.location(),
              sourcemeta::core::Pointer({"patternProperties"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(items_integer_bounded_decimal_in_range) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "type": "number", "minimum": 0, "maximum": 100 }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};
  instance.push_back(sourcemeta::core::JSON{sourcemeta::core::Decimal{"50.5"}});
  EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsIntegerBounded, "/items", "#/items", "");
  EVALUATE_TRACE_POST_SUCCESS(0, LoopItemsIntegerBounded, "/items", "#/items",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be a number within the "
      "given range");
}

TEST(items_integer_bounded_decimal_out_of_range) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "type": "number", "minimum": 0, "maximum": 100 }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::JSON::Array{}};
  instance.push_back(
      sourcemeta::core::JSON{sourcemeta::core::Decimal{"200.5"}});
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, LoopItemsIntegerBounded, "/items", "#/items", "");
  EVALUATE_TRACE_POST_FAILURE(0, LoopItemsIntegerBounded, "/items", "#/items",
                              "");

  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "Every item in the array was expected to be a number within the "
      "given range");
}

TEST(prop_type_integer_bounded_strict_decimal_3_0_fails) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "x": { "type": "integer", "minimum": 0, "maximum": 100 }
    }
  })JSON")};

  sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};
  instance.assign("x",
                  sourcemeta::core::JSON{sourcemeta::core::Decimal{"3.0"}});
  EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, 1, "");

  EVALUATE_TRACE_PRE(0, AssertionTypeIntegerBoundedStrict,
                     "/properties/x/minimum", "#/properties/x/minimum", "/x");
  EVALUATE_TRACE_POST_FAILURE(0, AssertionTypeIntegerBoundedStrict,
                              "/properties/x/minimum", "#/properties/x/minimum",
                              "/x");
  EVALUATE_TRACE_POST_DESCRIBE(
      instance, 0,
      "The value was expected to be an integer within the given range");
}
