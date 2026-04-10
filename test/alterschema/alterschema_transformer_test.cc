#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "alterschema_transform_rules.h"

static auto transformer_callback_noop(
    const sourcemeta::core::Pointer &, const std::string_view,
    const std::string_view,
    const sourcemeta::blaze::SchemaTransformRule::Result &, const bool)
    -> void {}

using TestTransformTraces = std::vector<
    std::tuple<sourcemeta::core::Pointer, std::string, std::string,
               sourcemeta::blaze::SchemaTransformRule::Result, bool>>;

static auto transformer_callback_trace(TestTransformTraces &traces) -> auto {
  return [&traces](const auto &pointer, const auto &name, const auto &message,
                   const auto &result, const auto &fixable) {
    traces.emplace_back(pointer, name, message, result, fixable);
  };
}

TEST(AlterSchema_transformer, flat_document_no_applicators) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_2");
  EXPECT_EQ(std::get<2>(entries.at(1)), "Keyword bar is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(1)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "qux": "xxx"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, embedded_resource_match_check) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  // Framing will register the nested schemas from the point of view of BOTH the
  // root and the embedded resources, and thus we might be linting the same
  // thing twice
  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$id": "https://www.example.com",
        "foo": "bar"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 50);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"$defs", "schema"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, embedded_resource_match_check_with_default_id) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "schema": {
        "$id": "https://www.example.com",
        "foo": "bar"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries), "",
                                   "https://sourcemeta.com");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 50);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"$defs", "schema"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, embedded_resource_vocabularies_check) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDraftTag>(), "example_rule_draft_tag");
  EXPECT_EQ(bundle.add<ExampleRuleModernTag>(), "example_rule_modern_tag");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.example.com/top",
    "$defs": {
      "schema": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://www.example.com/nested"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);
  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"$defs", "schema"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_draft_tag");
  EXPECT_EQ(std::get<2>(entries.at(0)), "");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_modern_tag");
  EXPECT_EQ(std::get<2>(entries.at(1)), "");
  EXPECT_EQ(std::get<3>(entries.at(1)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(1)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(1)));
}

TEST(AlterSchema_transformer, embedded_resource_vocabularies_apply) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDraftTag>(), "example_rule_draft_tag");
  EXPECT_EQ(bundle.add<ExampleRuleModernTag>(), "example_rule_modern_tag");

  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.example.com/top",
    "$defs": {
      "schema": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://www.example.com/nested"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"$defs", "schema"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_draft_tag");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_modern_tag");
  EXPECT_TRUE(std::get<4>(entries.at(1)));

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.example.com/top",
    "x-dialect-type": "modern",
    "$defs": {
      "schema": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://www.example.com/nested",
        "x-dialect-type": "draft"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, throw_if_no_dialect_invalid_default) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  EXPECT_THROW(static_cast<void>(bundle.apply(
                   document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver, transformer_callback_noop,
                   "https://example.com/invalid")),
               sourcemeta::core::SchemaResolutionError);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  // Nothing should have been modified
  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, with_default_dialect) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, transformer_callback_trace(entries),
      "https://json-schema.org/draft/2020-12/schema");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_2");
  EXPECT_EQ(std::get<2>(entries.at(1)), "Keyword bar is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(1)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "qux": "xxx"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, with_explicit_default_dialect_same) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(
      document, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, transformer_callback_trace(entries),
      "https://json-schema.org/draft/2020-12/schema");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_2");
  EXPECT_EQ(std::get<2>(entries.at(1)), "Keyword bar is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(1)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "qux": "xxx"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, throw_on_rules_called_twice) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRuleConflictsWith1>(),
            "example_rule_conflicts_with_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar"
  })JSON");

  try {
    [[maybe_unused]] const auto result = bundle.apply(
        document, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver, transformer_callback_noop);
    FAIL();
  } catch (
      const sourcemeta::blaze::SchemaTransformRuleProcessedTwiceError &error) {
    EXPECT_EQ(error.name(), "example_rule_1");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "");
    SUCCEED();
  } catch (...) {
    FAIL();
  }
}

TEST(AlterSchema_transformer, top_level_rule) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule3>(), "example_rule_3");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_3");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Example rule 3");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "top": true,
    "properties": {
      "foo": { "type": "string" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, walker_2020_12) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule4>(), "example_rule_4");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": {
        "items": {
          "type": "number"
        }
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 4);

  // Verify each entry is for example_rule_4 and was mutated (order varies)
  for (std::size_t index = 0; index < entries.size(); ++index) {
    EXPECT_EQ(std::get<1>(entries.at(index)), "example_rule_4");
    EXPECT_EQ(std::get<2>(entries.at(index)), "Example rule 4");
    EXPECT_TRUE(std::get<4>(entries.at(index)));
  }

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "here": true,
    "properties": {
      "foo": {
        "type": "string",
        "here": true
      },
      "bar": {
        "here": true,
        "items": {
          "here": true,
          "type": "number"
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, mismatch_default_dialect) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule4>(), "example_rule_4");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": {
        "unevaluatedItems": {
          "type": "number"
        }
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries),
                                   "http://json-schema.org/draft-04/schema#");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 4);

  // Verify each entry is for example_rule_4 and was mutated (order varies)
  for (std::size_t index = 0; index < entries.size(); ++index) {
    EXPECT_EQ(std::get<1>(entries.at(index)), "example_rule_4");
    EXPECT_EQ(std::get<2>(entries.at(index)), "Example rule 4");
    EXPECT_TRUE(std::get<4>(entries.at(index)));
  }

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "here": true,
    "properties": {
      "foo": {
        "type": "string",
        "here": true
      },
      "bar": {
        "here": true,
        "unevaluatedItems": {
          "here": true,
          "type": "number"
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rule_pointers) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule5>(), "example_rule_5");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "string" },
      "baz": { "type": "string" }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "baz"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_5");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Example rule 5");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "string" },
      "baz": { "type": "string", "baz": true }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, multi_dialect_rules) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule4>(), "example_rule_4");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "unevaluatedItems": { "type": "string" },
    "$defs": {
      "foo": {
        "$schema": "http://json-schema.org/draft-03/schema#",
        "additionalItems": {
          "type": "string"
        }
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 4);

  // Verify each entry is for example_rule_4 and was mutated (order varies)
  for (std::size_t index = 0; index < entries.size(); ++index) {
    EXPECT_EQ(std::get<1>(entries.at(index)), "example_rule_4");
    EXPECT_EQ(std::get<2>(entries.at(index)), "Example rule 4");
    EXPECT_TRUE(std::get<4>(entries.at(index)));
  }

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "here": true,
    "unevaluatedItems": {
      "here": true,
      "type": "string"
    },
    "$defs": {
      "foo": {
        "$schema": "http://json-schema.org/draft-03/schema#",
        "here": true,
        "additionalItems": {
          "here": true,
          "type": "string"
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, dialect_specific_rules) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule6>(), "example_rule_6");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "id": "https://www.example.com/foo",
        "$schema": "http://json-schema.org/draft-03/schema#"
      },
      "bar": {
        "id": "https://www.example.com/bar",
        "$schema": "http://json-schema.org/draft-02/schema#"
      },
      "baz": {
        "id": "https://www.example.com/baz",
        "$schema": "http://json-schema.org/draft-01/schema#"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"$defs", "foo"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_6");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Example rule 6");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "id": "https://www.example.com/foo",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "draft": 3
      },
      "bar": {
        "id": "https://www.example.com/bar",
        "$schema": "http://json-schema.org/draft-02/schema#"
      },
      "baz": {
        "id": "https://www.example.com/baz",
        "$schema": "http://json-schema.org/draft-01/schema#"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, dialect_specific_rules_without_ids) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule6>(), "example_rule_6");

  // Note that `$schema` is only valid on subschemas that represent
  // schema resources. Here we test that if not, `$schema` is ignored
  // and the dialects never change

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "$schema": "http://json-schema.org/draft-03/schema#" },
      "bar": { "$schema": "http://json-schema.org/draft-02/schema#" },
      "baz": { "$schema": "http://json-schema.org/draft-01/schema#" }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "$schema": "http://json-schema.org/draft-03/schema#" },
      "bar": { "$schema": "http://json-schema.org/draft-02/schema#" },
      "baz": { "$schema": "http://json-schema.org/draft-01/schema#" }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, check_top_level) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1WithPointer>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "properties": {
      "xxx": {
        "bar": "baz"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/foo");
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)),
            sourcemeta::core::Pointer({"properties", "xxx"}));
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_2");
  EXPECT_EQ(std::get<2>(entries.at(1)), "Keyword bar is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(1)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(1)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(1)));
}

TEST(AlterSchema_transformer, check_top_level_with_id) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "foo": "bar"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_top_level_with_id_and_default_id) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "foo": "bar"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries), "",
                                   "https://other.com");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_multiple_pointers) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleWithManyPointers>(),
            "example_rule_with_many_pointers");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_with_many_pointers");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Foo Bar");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 2);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/foo");
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(1)),
      "/bar");
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_with_description) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1WithDescription>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(entries.at(0)).locations.at(0)),
      "/foo");
  EXPECT_TRUE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(entries.at(0)).description.value(),
            "This is a message from the rule");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_no_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "xxx": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);

  EXPECT_TRUE(entries.empty());
}

TEST(AlterSchema_transformer, check_partial_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "type": "string"
      },
      "bar": {
        "type": "string",
        "foo": 1
      },
      "baz": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 75);

  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "bar"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_empty) {
  sourcemeta::blaze::SchemaTransformer bundle;
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);

  EXPECT_TRUE(entries.empty());
}

TEST(AlterSchema_transformer, check_throw_if_no_dialect_invalid_default) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  EXPECT_THROW((void)bundle.check(document, sourcemeta::core::schema_walker,
                                  sourcemeta::core::schema_resolver, nullptr,
                                  "https://example.com/invalid"),
               sourcemeta::core::SchemaResolutionError);
}

TEST(AlterSchema_transformer, check_with_default_dialect) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "foo": "bar",
    "properties": {
      "xxx": {
        "bar": "baz"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(
      document, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, transformer_callback_trace(entries),
      "https://json-schema.org/draft/2020-12/schema");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 2);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_EQ(std::get<0>(entries.at(1)),
            sourcemeta::core::Pointer({"properties", "xxx"}));
  EXPECT_EQ(std::get<1>(entries.at(1)), "example_rule_2");
  EXPECT_EQ(std::get<2>(entries.at(1)), "Keyword bar is not permitted");
  EXPECT_EQ(std::get<3>(entries.at(1)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(1)).description.has_value());
  EXPECT_TRUE(std::get<4>(entries.at(1)));
}

TEST(AlterSchema_transformer, remove_rule_by_name) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  EXPECT_TRUE(bundle.remove("example_rule_2"));
  EXPECT_FALSE(bundle.remove("example_rule_2"));
  EXPECT_FALSE(bundle.remove("i_dont_exist"));

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, unfixable_apply) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleUnfixable1>(), "example_rule_unfixable_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);

  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_unfixable_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "An example rule that cannot be fixed");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_FALSE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, unfixable_check) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleUnfixable1>(), "example_rule_unfixable_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_unfixable_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "An example rule that cannot be fixed");
  EXPECT_EQ(std::get<3>(entries.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(entries.at(0)).description.has_value());
  EXPECT_FALSE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, rereference_not_hit) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsNoRereference>(),
            "example_rule_definitions_to_defs_no_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "definitions": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_no_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_not_fixed_ref) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsNoRereference>(),
            "example_rule_definitions_to_defs_no_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;

  try {
    [[maybe_unused]] const auto result = bundle.apply(
        document, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver, transformer_callback_trace(entries));
    FAIL() << "The transformation was expected to throw";
  } catch (const sourcemeta::blaze::SchemaBrokenReferenceError &error) {
    EXPECT_EQ(error.identifier(), "#/definitions/foo");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/$ref");
    SUCCEED();
  } catch (...) {
    FAIL();
  }

  // The transformation happens before the reference check fails
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_no_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  // Note we still transform the schema to leave it in its broken state for
  // logging, etc
  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/foo",
    "$defs": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_not_fixed_id) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleRemoveIdentifiers>(),
            "example_rule_remove_identifiers");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "helper",
    "$defs": {
      "helper": {
        "$id": "helper"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 2);

  // Verify each entry is for the rule and was mutated (order varies)
  for (std::size_t index = 0; index < entries.size(); ++index) {
    EXPECT_EQ(std::get<1>(entries.at(index)),
              "example_rule_remove_identifiers");
    EXPECT_EQ(std::get<2>(entries.at(index)), "Remove all identifiers");
    EXPECT_TRUE(std::get<4>(entries.at(index)));
  }

  // The reference is now just treated as an external one

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "helper",
    "$defs": {
      "helper": {}
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_not_fixed_anchor) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleRemoveIdentifiers>(),
            "example_rule_remove_identifiers");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#helper",
    "$defs": {
      "helper": {
        "$anchor": "helper"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"$defs", "helper"}));
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_remove_identifiers");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Remove all identifiers");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  // The reference is now just treated as an external one

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#helper",
    "$defs": {
      "helper": {}
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_1) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/definitions/foo",
    "definitions": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_2) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "https://example.com#/definitions/foo",
    "definitions": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "https://example.com#/$defs/foo",
    "$defs": {
      "foo": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_3) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "foo",
    "definitions": {
      "foo": {
        "$id": "foo",
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "foo",
    "$defs": {
      "foo": {
        "$id": "foo",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_4) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "#foo",
    "definitions": {
      "foo": {
        "$anchor": "foo",
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com",
    "$ref": "#foo",
    "$defs": {
      "foo": {
        "$anchor": "foo",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_5) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/properties/definitions/definitions/helper"
      },
      "definitions": {
        "definitions": {
          "helper": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "definitions"}));
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "#/properties/definitions/$defs/helper"
      },
      "definitions": {
        "$defs": {
          "helper": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_6) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/here",
    "properties": {
      "foo": {
        "$id": "nested",
        "$ref": "here#/properties/bar/definitions/helper"
      },
      "bar": {
        "definitions": {
          "helper": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)),
            sourcemeta::core::Pointer({"properties", "bar"}));
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/here",
    "properties": {
      "foo": {
        "$id": "nested",
        "$ref": "here#/properties/bar/$defs/helper"
      },
      "bar": {
        "$defs": {
          "helper": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, rereference_fixed_7) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRuleDefinitionsToDefsWithRereference>(),
            "example_rule_definitions_to_defs_with_rereference");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/here",
    "allOf": [
      { "$ref": "#/definitions/outer" },
      {
        "properties": {
          "foo": {
            "$id": "nested",
            "$ref": "#/definitions/helper",
            "definitions": {
              "inner": {
                "type": "string"
              }
            },
            "$defs": {}
          }
        }
      }
    ],
    "definitions": {
      "outer": {
        "type": "string"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.apply(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)),
            "example_rule_definitions_to_defs_with_rereference");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Rename `definitions` to `$defs`");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/here",
    "allOf": [
      { "$ref": "#/$defs/outer" },
      {
        "properties": {
          "foo": {
            "$id": "nested",
            "$ref": "#/definitions/helper",
            "definitions": {
              "inner": {
                "type": "string"
              }
            },
            "$defs": {}
          }
        }
      }
    ],
    "$defs": {
      "outer": {
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(AlterSchema_transformer, iterators) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");
  EXPECT_EQ(bundle.add<ExampleRule3>(), "example_rule_3");

  std::set<std::string_view> rules;
  for (const auto &rule : bundle) {
    rules.insert(std::get<0>(rule)->name());
  }

  EXPECT_EQ(rules.size(), 3);
  EXPECT_TRUE(rules.contains("example_rule_1"));
  EXPECT_TRUE(rules.contains("example_rule_2"));
  EXPECT_TRUE(rules.contains("example_rule_3"));
}

TEST(AlterSchema_transformer, check_exclude_keyword_string_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": "example_rule_1"
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
}

TEST(AlterSchema_transformer, check_exclude_keyword_string_no_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": "other_rule"
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_array_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": [ "example_rule_1" ]
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
}

TEST(AlterSchema_transformer, check_exclude_keyword_array_multiple_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": [ "other_rule", "example_rule_1", "another_rule" ]
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
}

TEST(AlterSchema_transformer, check_exclude_keyword_array_no_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": [ "other_rule", "another_rule" ]
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_wrong_type) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": 123
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_nested_only) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "properties": {
      "test": {
        "foo": "baz",
        "x-exclude": "example_rule_1"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_multiple_rules) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "value1",
    "bar": "value2",
    "x-exclude": "example_rule_1"
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_2");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_no_keyword_set) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": "example_rule_1"
  })JSON");

  TestTransformTraces entries;
  const auto result = bundle.check(document, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   transformer_callback_trace(entries));

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, apply_exclude_keyword_string_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": "example_rule_1"
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.apply(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
  EXPECT_TRUE(document.defines("foo"));
}

TEST(AlterSchema_transformer, apply_exclude_keyword_string_no_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": "other_rule"
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.apply(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_FALSE(document.defines("foo"));
}

TEST(AlterSchema_transformer, apply_exclude_keyword_array_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": [ "example_rule_1" ]
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.apply(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
  EXPECT_TRUE(document.defines("foo"));
}

TEST(AlterSchema_transformer, apply_exclude_keyword_array_multiple_match) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");
  EXPECT_EQ(bundle.add<ExampleRule2>(), "example_rule_2");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "value1",
    "bar": "value2",
    "x-exclude": [ "example_rule_1", "example_rule_2" ]
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.apply(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
  EXPECT_TRUE(document.defines("foo"));
  EXPECT_TRUE(document.defines("bar"));
}

TEST(AlterSchema_transformer, apply_exclude_keyword_nested_selective) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "root",
    "properties": {
      "test": {
        "foo": "nested",
        "x-exclude": "example_rule_1"
      }
    }
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.apply(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(entries.size(), 1);

  EXPECT_EQ(std::get<0>(entries.at(0)), sourcemeta::core::Pointer{});
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_EQ(std::get<2>(entries.at(0)), "Keyword foo is not permitted");
  EXPECT_TRUE(std::get<4>(entries.at(0)));

  EXPECT_FALSE(document.defines("foo"));
  EXPECT_TRUE(document.at("properties").at("test").defines("foo"));
}

TEST(AlterSchema_transformer, check_exclude_keyword_empty_string) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": ""
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_empty_array) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": []
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_boolean) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": true
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_null) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": null
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_object) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": { "rule": "example_rule_1" }
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_FALSE(result.first);
  EXPECT_EQ(entries.size(), 1);
  EXPECT_EQ(std::get<1>(entries.at(0)), "example_rule_1");
  EXPECT_TRUE(std::get<4>(entries.at(0)));
}

TEST(AlterSchema_transformer, check_exclude_keyword_array_with_non_strings) {
  sourcemeta::blaze::SchemaTransformer bundle;
  EXPECT_EQ(bundle.add<ExampleRule1>(), "example_rule_1");

  const auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "x-exclude": [ 123, true, "example_rule_1" ]
  })JSON");

  TestTransformTraces entries;
  const auto result =
      bundle.check(document, sourcemeta::core::schema_walker,
                   sourcemeta::core::schema_resolver,
                   transformer_callback_trace(entries), "", "", "x-exclude");

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(entries.size(), 0);
}
