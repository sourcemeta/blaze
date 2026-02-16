#include <gtest/gtest.h>

#include <sourcemeta/blaze/linter.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

TEST(Linter, schema_rule_pass_when_all_subschemas_conform) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/must_be_object",
    "description": "Every subschema must be an object",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 0);
}

TEST(Linter, schema_rule_fail_root_and_nested_subschema) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/require_type",
    "description": "Every subschema must define a type",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      },
      "bar": {
        "minLength": 1
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/require_type");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Every subschema must define a type");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)),
            sourcemeta::core::Pointer({"properties", "bar"}));
  EXPECT_EQ(std::get<1>(entries.at(1)), "test/require_type");
  EXPECT_EQ(std::get<2>(entries.at(1)), "Every subschema must define a type");
  EXPECT_TRUE(std::get<3>(entries.at(1)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(1)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(1)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(1)));
}

TEST(Linter, schema_rule_no_description_in_rule_schema) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/no_description",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 0);
}

TEST(Linter, schema_rule_no_description_fails) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/no_description",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minLength": 1
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/no_description");
  EXPECT_EQ(std::get<2>(entries.at(0)), "");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_nested_property_fails) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/error_detail",
    "description": "Subschemas must be objects with a type keyword",
    "type": "object",
    "required": [ "type" ],
    "properties": {
      "type": { "type": "string" }
    }
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "minLength": 1
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/error_detail");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Subschemas must be objects with a type keyword");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_all_subschemas_pass) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/all_pass",
    "description": "Subschemas must define type",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string"
      },
      "bar": {
        "type": "integer"
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 0);
}

TEST(Linter, schema_rule_missing_title_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_non_string_title_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": 123,
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_uppercase_title_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Test/Rule",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_space_in_title_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test rule",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_empty_title_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_valid_title_with_digits_and_underscores) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "my_rule_2/check_v3",
    "description": "A valid rule name with digits and underscores",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 0);
}

TEST(Linter, schema_rule_invalid_name_error_preserves_name) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Bad Name!",
    "type": "object"
  })JSON")};

  try {
    sourcemeta::core::SchemaTransformer bundle;
    bundle.add<sourcemeta::blaze::SchemaRule>(
        rule_schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler);
    FAIL() << "Expected LinterInvalidNameError";
  } catch (const sourcemeta::blaze::LinterInvalidNameError &error) {
    EXPECT_EQ(error.name(), "Bad Name!");
    EXPECT_STREQ(error.what(), "The schema rule name is invalid");
  }
}

TEST(Linter, schema_rule_missing_title_error_preserves_empty_name) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON")};

  try {
    sourcemeta::core::SchemaTransformer bundle;
    bundle.add<sourcemeta::blaze::SchemaRule>(
        rule_schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver,
        sourcemeta::blaze::default_schema_compiler);
    FAIL() << "Expected LinterInvalidNameError";
  } catch (const sourcemeta::blaze::LinterInvalidNameError &error) {
    EXPECT_EQ(error.name(), "");
    EXPECT_STREQ(error.what(), "The schema rule name is invalid");
  }
}

TEST(Linter, schema_rule_title_with_hyphen_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "my-rule",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_title_with_dot_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "my.rule",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_title_only_digits) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "123",
    "description": "Title with only digits",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 0);
}

TEST(Linter, schema_rule_title_only_underscores) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "___",
    "description": "Title with only underscores",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 0);
}

TEST(Linter, schema_rule_non_string_description_integer) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/integer_desc",
    "description": 42,
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minLength": 1
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/integer_desc");
  EXPECT_EQ(std::get<2>(entries.at(0)), "42");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_non_string_description_boolean) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/bool_desc",
    "description": true,
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minLength": 1
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/bool_desc");
  EXPECT_EQ(std::get<2>(entries.at(0)), "true");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_non_string_description_null) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/null_desc",
    "description": null,
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "minLength": 1
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/null_desc");
  EXPECT_EQ(std::get<2>(entries.at(0)), "null");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_with_default_dialect_no_schema_keyword) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "title": "test/require_type_no_schema",
    "description": "Every subschema must define a type",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      "https://json-schema.org/draft/2020-12/schema");

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "properties": {
      "foo": {
        "minLength": 1
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      },
      "https://json-schema.org/draft/2020-12/schema");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/require_type_no_schema");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Every subschema must define a type");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_with_default_dialect_and_schema_keyword) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/require_type_with_schema",
    "description": "Every subschema must define a type",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      "https://json-schema.org/draft/2020-12/schema");

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "minLength": 1
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/require_type_with_schema");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Every subschema must define a type");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_multiple_rules_in_bundle) {
  const auto rule_schema_1{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/require_type",
    "description": "Every subschema must define a type",
    "type": "object",
    "required": [ "type" ]
  })JSON")};

  const auto rule_schema_2{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/must_be_object",
    "description": "Every subschema must be an object",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema_1, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema_2, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string"
      },
      "bar": {
        "minLength": 1
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "bar"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/require_type");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Every subschema must define a type");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be an object that defines the property "
            "\"type\"");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_boolean_true_schema_conforms) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/must_be_object",
    "description": "Every subschema must be an object",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": true
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/must_be_object");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Every subschema must be an object");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be of type object but it was of type "
            "boolean");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(Linter, schema_rule_title_with_special_chars_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test@rule#1",
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_title_boolean_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": true,
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_title_null_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": null,
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_title_array_throws) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": [ "foo" ],
    "type": "object"
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  EXPECT_THROW(bundle.add<sourcemeta::blaze::SchemaRule>(
                   rule_schema, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   sourcemeta::blaze::default_schema_compiler),
               sourcemeta::blaze::LinterInvalidNameError);
}

TEST(Linter, schema_rule_non_empty_instance_location) {
  const auto rule_schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "test/foo_must_be_string",
    "description": "The foo property must be a string",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON")};

  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::SchemaRule>(
      rule_schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "bar": {
        "foo": 42
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         sourcemeta::core::SchemaTransformRule::Result, bool>>
      entries;
  const auto result = bundle.check(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      [&entries](const auto &pointer, const auto &name, const auto &message,
                 const auto &outcome, const auto mutable_) {
        entries.emplace_back(pointer, name, message, outcome, mutable_);
      });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "bar"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "test/foo_must_be_string");
  EXPECT_EQ(std::get<2>(entries.at(0)), "The foo property must be a string");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "The value was expected to be of type string but it was of type "
            "integer");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.at(0),
            sourcemeta::core::Pointer({"foo"}));
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}
