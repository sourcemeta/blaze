#include <gtest/gtest.h>

#include <sourcemeta/blaze/linter.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

static auto transformer_callback_error(const sourcemeta::core::Pointer &,
                                       const std::string_view,
                                       const std::string_view,
                                       const std::string_view) -> void {
  throw std::runtime_error("The transform callback must not be called");
}

TEST(Linter, valid_default_error_message_without_id_nested) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "default": 1,
        "type": "string"
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         std::string>>
      entries;
  const auto result =
      bundle.check(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver,
                   [&entries](const auto &pointer, const auto &name,
                              const auto &message, const auto &description) {
                     entries.emplace_back(pointer, name, message, description);
                   });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_default");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only set a `default` value that validates against the schema");
  EXPECT_EQ(
      std::get<3>(entries.at(0)),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");
}

TEST(Linter, valid_default_error_message_without_id_flat) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": 1,
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         std::string>>
      entries;
  const auto result =
      bundle.check(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver,
                   [&entries](const auto &pointer, const auto &name,
                              const auto &message, const auto &description) {
                     entries.emplace_back(pointer, name, message, description);
                   });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_default");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only set a `default` value that validates against the schema");
  EXPECT_EQ(
      std::get<3>(entries.at(0)),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");
}

TEST(Linter, valid_default_error_message_with_id_nested) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": {
      "foo": {
        "default": 1,
        "type": "string"
      }
    }
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         std::string>>
      entries;
  const auto result =
      bundle.check(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver,
                   [&entries](const auto &pointer, const auto &name,
                              const auto &message, const auto &description) {
                     entries.emplace_back(pointer, name, message, description);
                   });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_default");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only set a `default` value that validates against the schema");
  EXPECT_EQ(
      std::get<3>(entries.at(0)),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");
}

TEST(Linter, valid_default_error_message_with_id_flat) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "default": 1,
    "type": "string"
  })JSON")};

  std::vector<std::tuple<sourcemeta::core::Pointer, std::string, std::string,
                         std::string>>
      entries;
  const auto result =
      bundle.check(schema, sourcemeta::core::schema_official_walker,
                   sourcemeta::core::schema_official_resolver,
                   [&entries](const auto &pointer, const auto &name,
                              const auto &message, const auto &description) {
                     entries.emplace_back(pointer, name, message, description);
                   });

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_default");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only set a `default` value that validates against the schema");
  EXPECT_EQ(
      std::get<3>(entries.at(0)),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/type"
)TXT");
}

TEST(Linter, valid_default_1) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_2) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": "bar" },
    "properties": {
      "foo": {
        "type": "string",
        "default": "baz"
      }
    }
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": "bar" },
    "properties": {
      "foo": {
        "type": "string",
        "default": "baz"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_3) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_4) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_5) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_6) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_7) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "default": { "foo": 1 },
    "properties": {
      "foo": {
        "type": "string",
        "default": true
      }
    }
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_8) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "default": {}
  })JSON")};

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "default": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_9) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "default": 1 },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON")};

  auto resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "ref.schema.json") {
      return sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "ref.schema.json"
      })JSON");
    }

    return sourcemeta::core::schema_official_resolver(identifier);
  };

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_official_walker, resolver,
                   transformer_callback_error);

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "default": 1 },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_10) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "default": 10, "$ref": "ref.json" }
  })JSON")};

  auto resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/ref.json") {
      return sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/ref.json",
        "type": "integer"
      })JSON");
    }

    return sourcemeta::core::schema_official_resolver(identifier);
  };

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker, resolver,
      transformer_callback_error, std::nullopt, "https://example.com/root");

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "default": 10, "$ref": "ref.json" }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_default_11) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": 10,
    "$ref": "ref.json"
  })JSON")};

  auto resolver = [](const std::string_view identifier)
      -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/ref.json") {
      return sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/ref.json",
        "type": "integer"
      })JSON");
    }

    return sourcemeta::core::schema_official_resolver(identifier);
  };

  const auto result = bundle.apply(
      schema, sourcemeta::core::schema_official_walker, resolver,
      transformer_callback_error, std::nullopt, "https://example.com/root");

  EXPECT_TRUE(result);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "default": 10,
    "$ref": "ref.json"
  })JSON")};

  EXPECT_EQ(schema, expected);
}
