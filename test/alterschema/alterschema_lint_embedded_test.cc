#include <sourcemeta/core/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <optional>

#include "alterschema_test_utils.h"

#define LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces)             \
  std::vector<                                                                 \
      std::tuple<sourcemeta::core::Pointer, std::string, std::string,          \
                 sourcemeta::blaze::SchemaTransformRule::Result, bool>>        \
      traces;                                                                  \
  sourcemeta::blaze::SchemaTransformer bundle;                                 \
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);  \
  const sourcemeta::core::SchemaFrame frame{                                   \
      sourcemeta::core::SchemaFrame::Mode::References,                         \
      document,                                                                \
      sourcemeta::core::schema_walker,                                         \
      alterschema_test_resolver,                                               \
      "https://spec.openapis.org/oas/3.1/dialect/base",                        \
      "",                                                                      \
      sourcemeta::core::SchemaFrame::IdentifierMode::Additional,               \
      paths,                                                                   \
      "https://example.com/openapi.json"};                                     \
  const auto result = bundle.check(                                            \
      document, frame, sourcemeta::core::schema_walker,                        \
      alterschema_test_resolver,                                               \
      [&traces](const auto &entry_pointer, const auto &rule_name,              \
                const auto &rule_message, const auto &rule_outcome,            \
                const auto &rule_fixable) {                                    \
        traces.emplace_back(entry_pointer, rule_name, rule_message,            \
                            rule_outcome, rule_fixable);                       \
      });

#define LINT_EMBEDDED_AND_FIX(document, paths, result, traces)                 \
  std::vector<                                                                 \
      std::tuple<sourcemeta::core::Pointer, std::string, std::string,          \
                 sourcemeta::blaze::SchemaTransformRule::Result, bool>>        \
      traces;                                                                  \
  sourcemeta::blaze::SchemaTransformer bundle;                                 \
  sourcemeta::blaze::add(bundle, sourcemeta::blaze::AlterSchemaMode::Linter);  \
  std::optional<sourcemeta::core::SchemaFrame> frame;                          \
  const auto result = bundle.apply(                                            \
      document,                                                                \
      [&frame, &paths](const sourcemeta::core::JSON &current)                  \
          -> const sourcemeta::core::SchemaFrame & {                           \
        frame.emplace(                                                         \
            sourcemeta::core::SchemaFrame::Mode::References, current,          \
            sourcemeta::core::schema_walker, alterschema_test_resolver,        \
            "https://spec.openapis.org/oas/3.1/dialect/base", "",              \
            sourcemeta::core::SchemaFrame::IdentifierMode::Additional, paths,  \
            "https://example.com/openapi.json");                               \
        return frame.value();                                                  \
      },                                                                       \
      sourcemeta::core::schema_walker, alterschema_test_resolver,              \
      [&traces](const auto &entry_pointer, const auto &rule_name,              \
                const auto &rule_message, const auto &rule_outcome,            \
                const auto &rule_fixable) {                                    \
        traces.emplace_back(entry_pointer, rule_name, rule_message,            \
                            rule_outcome, rule_fixable);                       \
      });

TEST(top_level_rules_on_every_embedded_root) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "properties": {
            "name": { "type": "string" }
          }
        },
        "Order": {
          "properties": {
            "id": { "type": "integer" }
          }
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(order)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 50);
  EXPECT_EQ(traces.size(), 6);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Order", "top_level_title",
                    "Set a concise non-empty title at the top level of the "
                    "schema to explain what the definition is about",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(traces.at(0)).description.has_value());

  EXPECT_LINT_TRACE(traces, 1, "/components/schemas/Order",
                    "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(1)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(traces.at(1)).description.has_value());

  EXPECT_LINT_TRACE(traces, 2, "/components/schemas/Order",
                    "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(2)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(traces.at(2)).description.has_value());

  EXPECT_LINT_TRACE(traces, 3, "/components/schemas/Pet", "top_level_title",
                    "Set a concise non-empty title at the top level of the "
                    "schema to explain what the definition is about",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(3)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(traces.at(3)).description.has_value());

  EXPECT_LINT_TRACE(traces, 4, "/components/schemas/Pet",
                    "top_level_description",
                    "Set a non-empty description at the top level of the "
                    "schema to explain what the definition is about in detail",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(4)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(traces.at(4)).description.has_value());

  EXPECT_LINT_TRACE(traces, 5, "/components/schemas/Pet", "top_level_examples",
                    "Set a non-empty examples array at the top level of the "
                    "schema to illustrate the expected data",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(5)).locations.size(), 0);
  EXPECT_FALSE(std::get<3>(traces.at(5)).description.has_value());
}

TEST(orphan_definitions_in_embedded_schema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ {} ],
          "type": "object",
          "$defs": {
            "unused": { "type": "string" }
          }
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(pet)};

  LINT_EMBEDDED_AND_FIX(document, paths, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Pet", "orphan_definitions",
                    "Schema definitions in `$defs` or `definitions` that are "
                    "never internally referenced can be removed",
                    true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/$defs/unused");
  EXPECT_FALSE(std::get<3>(traces.at(0)).description.has_value());

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ {} ],
          "type": "object"
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(orphan_definitions_referenced_from_embedded_sibling) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ {} ],
          "type": "object",
          "$defs": {
            "name": { "type": "string" }
          }
        },
        "Order": {
          "title": "Order",
          "description": "An order in the store",
          "examples": [ "foo" ],
          "$ref": "#/components/schemas/Pet/$defs/name"
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer order{"components", "schemas", "Order"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(order)};

  LINT_EMBEDDED_AND_FIX(document, paths, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(traces.size(), 0);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ {} ],
          "type": "object",
          "$defs": {
            "name": { "type": "string" }
          }
        },
        "Order": {
          "title": "Order",
          "description": "An order in the store",
          "examples": [ "foo" ],
          "$ref": "#/components/schemas/Pet/$defs/name"
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(valid_default_on_embedded_schema_in_non_standalone_frame) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Name": {
          "title": "Name",
          "description": "A pet name",
          "examples": [ "Rex" ],
          "type": "string"
        },
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "name": "Rex" } ],
          "type": "object",
          "properties": {
            "name": {
              "$ref": "#/components/schemas/Name",
              "default": 1
            }
          }
        },
        "Remote": {
          "title": "Remote",
          "description": "A remote string",
          "examples": [ "foo" ],
          "$ref": "https://example.com/external"
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer name{"components", "schemas", "Name"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer remote{"components", "schemas", "Remote"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(name),
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(remote)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 75);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Pet/properties/name",
                    "valid_default",
                    "Only set a `default` value that validates against the "
                    "schema",
                    true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/default");
  EXPECT_TRUE(std::get<3>(traces.at(0)).description.has_value());
  EXPECT_EQ(
      std::get<3>(traces.at(0)).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/$ref/type"
The integer value was expected to validate against the referenced schema
  at instance location ""
  at evaluate path "/$ref"
)TXT");
}

TEST(valid_examples_on_embedded_schema_in_non_standalone_frame) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Remote": {
          "title": "Remote",
          "description": "A remote string",
          "examples": [ 1 ],
          "$ref": "https://example.com/external"
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer remote{"components", "schemas", "Remote"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(remote)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 0);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Remote", "valid_examples",
                    "Only include instances in the `examples` array that "
                    "validate against the schema",
                    true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/examples/0");
  EXPECT_TRUE(std::get<3>(traces.at(0)).description.has_value());
  EXPECT_EQ(std::get<3>(traces.at(0)).description.value(),
            R"TXT(Invalid example instance at index 0
  The value was expected to be of type string but it was of type integer
    at instance location ""
    at evaluate path "/$ref/type"
  The integer value was expected to validate against the referenced schema
    at instance location ""
    at evaluate path "/$ref"
)TXT");
}

TEST(simple_properties_identifiers_in_embedded_schema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "first-name": "Rex", "age": 3 } ],
          "type": "object",
          "properties": {
            "first-name": { "type": "string" },
            "age": { "type": "integer" }
          }
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(pet)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 67);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Pet",
                    "simple_properties_identifiers",
                    "Set `properties` to identifier names that can be easily "
                    "mapped to programming languages (matching "
                    "[A-Za-z_][A-Za-z0-9_]*)",
                    false);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/properties/first-name");
  EXPECT_FALSE(std::get<3>(traces.at(0)).description.has_value());
}

TEST(valid_default_fix_on_embedded_schema_in_non_standalone_frame) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Name": {
          "title": "Name",
          "description": "A pet name",
          "examples": [ "Rex" ],
          "type": "string"
        },
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "name": "Rex" } ],
          "type": "object",
          "properties": {
            "name": {
              "$ref": "#/components/schemas/Name",
              "default": 1
            }
          }
        },
        "Remote": {
          "title": "Remote",
          "description": "A remote string",
          "examples": [ "foo" ],
          "$ref": "https://example.com/external"
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer name{"components", "schemas", "Name"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer remote{"components", "schemas", "Remote"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(name),
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(remote)};

  LINT_EMBEDDED_AND_FIX(document, paths, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Pet/properties/name",
                    "valid_default",
                    "Only set a `default` value that validates against the "
                    "schema",
                    true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/default");
  EXPECT_TRUE(std::get<3>(traces.at(0)).description.has_value());
  EXPECT_EQ(
      std::get<3>(traces.at(0)).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/$ref/type"
The integer value was expected to validate against the referenced schema
  at instance location ""
  at evaluate path "/$ref"
)TXT");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Name": {
          "title": "Name",
          "description": "A pet name",
          "examples": [ "Rex" ],
          "type": "string"
        },
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "name": "Rex" } ],
          "type": "object",
          "properties": {
            "name": {
              "$ref": "#/components/schemas/Name"
            }
          }
        },
        "Remote": {
          "title": "Remote",
          "description": "A remote string",
          "examples": [ "foo" ],
          "$ref": "https://example.com/external"
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(clean_description_has_no_findings) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "components": {
      "schemas": {
        "Name": {
          "title": "Name",
          "description": "The name of a pet",
          "examples": [ "Rex" ],
          "type": "string",
          "minLength": 1
        },
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "name": "Rex", "tag": "dog" } ],
          "type": "object",
          "required": [ "name" ],
          "properties": {
            "name": { "$ref": "#/components/schemas/Name" },
            "tag": { "$ref": "#/components/schemas/Pet/$defs/tag" }
          },
          "$defs": {
            "tag": { "type": "string" }
          }
        }
      },
      "parameters": {
        "Limit": {
          "name": "limit",
          "in": "query",
          "schema": {
            "title": "Limit",
            "description": "How many items to return",
            "examples": [ 10 ],
            "type": "integer",
            "minimum": 1
          }
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer name{"components", "schemas", "Name"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer limit{"components", "parameters", "Limit",
                                        "schema"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(name),
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(limit)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_TRUE(result.first);
  EXPECT_EQ(result.second, 100);
  EXPECT_EQ(traces.size(), 0);
}

TEST(valid_default_on_embedded_schema_with_scalar_at_bundle_container) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "x-sourcemeta-embedded": "reserved",
    "components": {
      "schemas": {
        "Name": {
          "title": "Name",
          "description": "A pet name",
          "examples": [ "Rex" ],
          "type": "string"
        },
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "name": "Rex" } ],
          "type": "object",
          "properties": {
            "name": {
              "$ref": "#/components/schemas/Name",
              "default": 1
            }
          }
        },
        "Remote": {
          "title": "Remote",
          "description": "A remote string",
          "examples": [ "foo" ],
          "$ref": "https://example.com/external"
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer name{"components", "schemas", "Name"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer remote{"components", "schemas", "Remote"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(name),
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(remote)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 75);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Pet/properties/name",
                    "valid_default",
                    "Only set a `default` value that validates against the "
                    "schema",
                    true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/default");
  EXPECT_TRUE(std::get<3>(traces.at(0)).description.has_value());
  EXPECT_EQ(
      std::get<3>(traces.at(0)).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/$ref/type"
The integer value was expected to validate against the referenced schema
  at instance location ""
  at evaluate path "/$ref"
)TXT");
}

TEST(valid_default_on_embedded_schema_with_object_at_bundle_container) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "openapi": "3.1.1",
    "info": { "title": "Example", "version": "1.0.0" },
    "x-sourcemeta-embedded": { "note": "reserved" },
    "components": {
      "schemas": {
        "Name": {
          "title": "Name",
          "description": "A pet name",
          "examples": [ "Rex" ],
          "type": "string"
        },
        "Pet": {
          "title": "Pet",
          "description": "A pet in the store",
          "examples": [ { "name": "Rex" } ],
          "type": "object",
          "properties": {
            "name": {
              "$ref": "#/components/schemas/Name",
              "default": 1
            }
          }
        },
        "Remote": {
          "title": "Remote",
          "description": "A remote string",
          "examples": [ "foo" ],
          "$ref": "https://example.com/external"
        }
      }
    }
  })JSON");

  const sourcemeta::core::Pointer name{"components", "schemas", "Name"};
  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  const sourcemeta::core::Pointer remote{"components", "schemas", "Remote"};
  const sourcemeta::core::SchemaFrame::Paths paths{
      sourcemeta::core::to_weak_pointer(name),
      sourcemeta::core::to_weak_pointer(pet),
      sourcemeta::core::to_weak_pointer(remote)};

  LINT_EMBEDDED_WITHOUT_FIX(document, paths, result, traces);

  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second, 75);
  EXPECT_EQ(traces.size(), 1);

  EXPECT_LINT_TRACE(traces, 0, "/components/schemas/Pet/properties/name",
                    "valid_default",
                    "Only set a `default` value that validates against the "
                    "schema",
                    true);
  EXPECT_EQ(std::get<3>(traces.at(0)).locations.size(), 1);
  EXPECT_EQ(
      sourcemeta::core::to_string(std::get<3>(traces.at(0)).locations.at(0)),
      "/default");
  EXPECT_TRUE(std::get<3>(traces.at(0)).description.has_value());
  EXPECT_EQ(
      std::get<3>(traces.at(0)).description.value(),
      R"TXT(The value was expected to be of type string but it was of type integer
  at instance location ""
  at evaluate path "/$ref/type"
The integer value was expected to validate against the referenced schema
  at instance location ""
  at evaluate path "/$ref"
)TXT");
}
