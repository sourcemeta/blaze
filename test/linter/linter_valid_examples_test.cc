#include <gtest/gtest.h>

#include <sourcemeta/blaze/linter.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

static auto transformer_callback_error(
    const sourcemeta::core::Pointer &, const std::string_view,
    const std::string_view,
    const sourcemeta::core::SchemaTransformRule::Result &, const bool mutable_)
    -> void {
  EXPECT_TRUE(mutable_);
}

TEST(Linter, valid_examples_error_message_without_id_nested) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "examples": [ 1 ],
        "type": "string"
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
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_examples");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/examples/0");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(Linter, valid_examples_error_message_without_id_flat) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ 1 ],
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

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_examples");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/examples/0");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(Linter, valid_examples_error_message_with_id_nested) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "properties": {
      "foo": {
        "examples": [ 1 ],
        "type": "string"
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
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_examples");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/examples/0");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(Linter, valid_examples_error_message_with_id_flat) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "examples": [ 1 ],
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

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer({}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_examples");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/type"
)TXT");

  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/examples/0");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(Linter, valid_examples_error_message_with_id_nested_ref_defs) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$defs": {
      "helper": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/helper",
        "examples": [ 1 ]
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
  EXPECT_EQ(std::get<1>(entries.at(0)), "blaze/valid_examples");
  EXPECT_EQ(std::get<2>(entries.at(0)),
            "Only include instances in the `examples` array that validate "
            "against the schema");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/$ref/type"
  The integer value was expected to validate against the referenced schema
    at instance location ""
    at evaluate path "/$ref"
)TXT");

  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/examples/0");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(Linter, valid_examples_1) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_2) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", "bar", "baz" ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ {} ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", "bar", "baz" ]
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_3) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

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

TEST(Linter, valid_examples_4) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

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

TEST(Linter, valid_examples_5) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

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

TEST(Linter, valid_examples_6) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

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

TEST(Linter, valid_examples_7) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "examples": [ { "foo": 1 } ],
    "properties": {
      "foo": {
        "type": "string",
        "examples": [ "foo", 2, "baz" ]
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_8) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [],
    "properties": {
      "foo": {
        "type": "string",
        "examples": []
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "examples": [],
    "properties": {
      "foo": {
        "type": "string",
        "examples": []
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_9) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "examples": [ {} ]
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "additionalProperties": false,
    "examples": [ {} ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_10) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "examples": [ 1 ] },
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

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   resolver, transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "examples": [ 1 ] },
      "bar": { "$ref": "ref.schema.json" }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_11) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" }
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

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_walker, resolver,
                   transformer_callback_error, "", "https://example.com/root");

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_12) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" },
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

    return sourcemeta::core::schema_resolver(identifier);
  };

  const auto result =
      bundle.apply(schema, sourcemeta::core::schema_walker, resolver,
                   transformer_callback_error, "", "https://example.com/root");

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "examples": [ 10 ], "$ref": "ref.json" },
    "$ref": "ref.json"
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_13) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "@foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "@foo": { "type": "string", "examples": [ "bar" ] }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_14) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": { "$ref": "#/definitions/helper", "examples": [ 1 ] }
    },
    "definitions": {
      "helper": { "type": "string" }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "foo": { "$ref": "#/definitions/helper", "examples": [ 1 ] }
    },
    "definitions": {
      "helper": { "type": "string" }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_15) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidExamples>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/definitions/helper", "examples": [ 1 ] }
    },
    "definitions": {
      "helper": { "type": "string" }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "#/definitions/helper" }
    },
    "definitions": {
      "helper": { "type": "string" }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Linter, valid_examples_16) {
  sourcemeta::core::SchemaTransformer bundle;
  bundle.add<sourcemeta::blaze::ValidDefault>(
      sourcemeta::blaze::default_schema_compiler);

  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://www.example.com",
    "examples": [ 0 ],
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {
        "examples": [ 0 ]
      }
    }
  })JSON")};

  const auto result = bundle.apply(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_error);

  EXPECT_TRUE(result.first);

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://www.example.com",
    "examples": [ 0 ],
    "$ref": "#/definitions/test",
    "definitions": {
      "test": {
        "examples": [ 0 ]
      }
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}
