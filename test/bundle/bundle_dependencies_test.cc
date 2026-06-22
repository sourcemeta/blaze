#include <gtest/gtest.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

#include <string>      // std::string
#include <string_view> // std::string_view
#include <tuple>       // std::tuple
#include <vector>      // std::vector

#define EXPECT_DEPENDENCY(expected_traces, expected_index, expected_origin,    \
                          expected_pointer, expected_target)                   \
  EXPECT_EQ(std::get<0>((expected_traces).at(expected_index)),                 \
            (expected_origin));                                                \
  EXPECT_EQ(sourcemeta::core::to_string(                                       \
                std::get<1>((expected_traces).at(expected_index))),            \
            (expected_pointer));                                               \
  EXPECT_EQ(std::get<2>((expected_traces).at(expected_index)),                 \
            (expected_target));

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://www.sourcemeta.com/test-1") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/test-1",
      "type": "string"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-2") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://www.sourcemeta.com/test-2",
      "$ref": "test-3"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-3") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-06/schema#",
      "$id": "https://www.sourcemeta.com/test-3",
      "allOf": [ { "$ref": "test-4" } ]
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-3-top-level-ref") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-06/schema#",
      "$id": "https://www.sourcemeta.com/test-3-top-level-ref",
      "$ref": "test-4"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-4") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-04/schema#",
      "id": "https://www.sourcemeta.com/test-4",
      "type": "string"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/no-dialect") {
    return sourcemeta::core::parse_json(R"JSON({
      "foo": 1
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/array") {
    return sourcemeta::core::parse_json(R"JSON([
      "foo", "bar", "baz"
    ])JSON");
  } else if (identifier == "https://www.sourcemeta.com/sibling-a") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/sibling-a",
      "$ref": "shared"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/sibling-b") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/sibling-b",
      "$ref": "shared"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/shared") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/shared",
      "$ref": "deep"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/deep") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/deep",
      "type": "string"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/custom-metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/custom-metaschema",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true
      },
      "allOf": [
        { "$ref": "https://json-schema.org/draft/2020-12/meta/core" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/applicator" },
        { "$ref": "https://json-schema.org/draft/2020-12/meta/validation" }
      ]
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(Bundle_dependencies, multiple_refs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "https://www.sourcemeta.com/test-3"
      },
      "bar": {
        "$ref": "https://www.sourcemeta.com/test-1"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 3);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com",
                    "/properties/bar/$ref",
                    "https://www.sourcemeta.com/test-1");
  EXPECT_DEPENDENCY(traces, 1, "https://www.example.com",
                    "/properties/foo/$ref",
                    "https://www.sourcemeta.com/test-3");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/test-3",
                    "/allOf/0/$ref", "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, across_dialects) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-2" }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 3);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com", "/items/$ref",
                    "https://www.sourcemeta.com/test-2");
  EXPECT_DEPENDENCY(traces, 1, "https://www.sourcemeta.com/test-2", "/$ref",
                    "https://www.sourcemeta.com/test-3");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/test-3",
                    "/allOf/0/$ref", "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, across_dialects_top_level_ref_draft) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-3-top-level-ref" }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 2);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com", "/items/$ref",
                    "https://www.sourcemeta.com/test-3-top-level-ref");
  EXPECT_DEPENDENCY(traces, 1,
                    "https://www.sourcemeta.com/test-3-top-level-ref", "/$ref",
                    "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, across_dialects_from_top_level_ref_draft_absolute) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://www.sourcemeta.com/test-4"
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 1);

  EXPECT_DEPENDENCY(traces, 0, "", "/$ref",
                    "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, across_dialects_from_top_level_ref_draft_relative) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "test-4"
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  EXPECT_THROW(sourcemeta::blaze::dependencies(
                   document, sourcemeta::blaze::schema_walker, test_resolver,
                   [&traces](const auto &origin, const auto &pointer,
                             const auto &target, const auto &) {
                     traces.emplace_back(
                         origin, sourcemeta::core::to_pointer(pointer), target);
                   }),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Bundle_dependencies,
     across_dialects_from_top_level_ref_draft_with_default_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://www.sourcemeta.com/test-4"
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      },
      "http://json-schema.org/draft-07/schema#");

  EXPECT_EQ(traces.size(), 1);

  EXPECT_DEPENDENCY(traces, 0, "", "/$ref",
                    "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, across_dialects_const) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-2" }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 3);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com", "/items/$ref",
                    "https://www.sourcemeta.com/test-2");
  EXPECT_DEPENDENCY(traces, 1, "https://www.sourcemeta.com/test-2", "/$ref",
                    "https://www.sourcemeta.com/test-3");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/test-3",
                    "/allOf/0/$ref", "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, with_default_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "test-2" }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      },
      "", "https://www.sourcemeta.com/default");

  EXPECT_EQ(traces.size(), 3);

  EXPECT_DEPENDENCY(traces, 0, "https://www.sourcemeta.com/default",
                    "/items/$ref", "https://www.sourcemeta.com/test-2");
  EXPECT_DEPENDENCY(traces, 1, "https://www.sourcemeta.com/test-2", "/$ref",
                    "https://www.sourcemeta.com/test-3");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/test-3",
                    "/allOf/0/$ref", "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, with_default_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      },
      "https://json-schema.org/draft/2020-12/schema");

  EXPECT_EQ(traces.size(), 1);

  EXPECT_DEPENDENCY(traces, 0, "", "/properties/foo/$ref",
                    "https://www.sourcemeta.com/test-1");
}

TEST(Bundle_dependencies, without_default_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" }
    }
  })JSON");

  EXPECT_THROW(
      sourcemeta::blaze::dependencies(
          document, sourcemeta::blaze::schema_walker, test_resolver,
          [](const auto &, const auto &, const auto &, const auto &) {}),
      sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Bundle_dependencies, target_no_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/no-dialect" }
    }
  })JSON");

  EXPECT_THROW(
      sourcemeta::blaze::dependencies(
          document, sourcemeta::blaze::schema_walker, test_resolver,
          [](const auto &, const auto &, const auto &, const auto &) {}),
      sourcemeta::blaze::SchemaReferenceError);
}

TEST(Bundle_dependencies, target_array) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/array" }
    }
  })JSON");

  EXPECT_THROW(
      sourcemeta::blaze::dependencies(
          document, sourcemeta::blaze::schema_walker, test_resolver,
          [](const auto &, const auto &, const auto &, const auto &) {}),
      sourcemeta::blaze::SchemaReferenceError);
}

TEST(Bundle_dependencies, custom_paths_no_external) {
  auto document{sourcemeta::core::parse_json(R"JSON({
    "wrapper": {
      "$ref": "#/common/test"
    },
    "common": {
      "test": {
        "$ref": "#/common/with-id"
      },
      "with-id": {
        "$id": "https://www.sourcemeta.com/schema",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }
    }
  })JSON")};

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  const sourcemeta::core::Pointer path1{"wrapper"};
  const sourcemeta::core::Pointer path2{"common", "test"};
  const sourcemeta::core::Pointer path3{"common", "with-id"};
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      },
      "https://json-schema.org/draft/2020-12/schema", "",
      {
          sourcemeta::core::to_weak_pointer(path1),
          sourcemeta::core::to_weak_pointer(path2),
          sourcemeta::core::to_weak_pointer(path3),
      });

  EXPECT_EQ(traces.size(), 0);
}

TEST(Bundle_dependencies, custom_paths_with_externals) {
  auto document{sourcemeta::core::parse_json(R"JSON({
    "wrapper": {
      "$ref": "#/common/test"
    },
    "common": {
      "test": {
        "$ref": "#/common/with-id"
      },
      "with-id": {
        "$id": "https://www.sourcemeta.com/schema",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$ref": "test-2"
      }
    }
  })JSON")};

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  const sourcemeta::core::Pointer path1{"wrapper"};
  const sourcemeta::core::Pointer path2{"common", "test"};
  const sourcemeta::core::Pointer path3{"common", "with-id"};
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      },
      "https://json-schema.org/draft/2020-12/schema", "",
      {
          sourcemeta::core::to_weak_pointer(path1),
          sourcemeta::core::to_weak_pointer(path2),
          sourcemeta::core::to_weak_pointer(path3),
      });

  EXPECT_EQ(traces.size(), 3);

  // TODO: We should be getting the nested identifier here
  EXPECT_DEPENDENCY(traces, 0, "", "/common/with-id/$ref",
                    "https://www.sourcemeta.com/test-2");
  EXPECT_DEPENDENCY(traces, 1, "https://www.sourcemeta.com/test-2", "/$ref",
                    "https://www.sourcemeta.com/test-3");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/test-3",
                    "/allOf/0/$ref", "https://www.sourcemeta.com/test-4");
}

TEST(Bundle_dependencies, multiple_refs_to_same_target_within_schema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "properties": {
          "foo": { "$ref": "https://www.sourcemeta.com/test-1" }
        }
      },
      {
        "properties": {
          "bar": { "$ref": "https://www.sourcemeta.com/test-1" }
        }
      },
      {
        "properties": {
          "baz": { "$ref": "https://www.sourcemeta.com/test-1" }
        }
      }
    ]
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 1);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com",
                    "/anyOf/0/properties/foo/$ref",
                    "https://www.sourcemeta.com/test-1");
}

TEST(Bundle_dependencies, ref_to_official_schema_without_recursion) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://json-schema.org/draft/2020-12/schema" }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 1);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com", "/items/$ref",
                    "https://json-schema.org/draft/2020-12/schema");
}

TEST(Bundle_dependencies, custom_metaschema_official_boundary) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://www.sourcemeta.com/custom-metaschema",
    "type": "string"
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 4);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com", "/$schema",
                    "https://www.sourcemeta.com/custom-metaschema");
  EXPECT_DEPENDENCY(traces, 1, "https://www.sourcemeta.com/custom-metaschema",
                    "/allOf/0/$ref",
                    "https://json-schema.org/draft/2020-12/meta/core");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/custom-metaschema",
                    "/allOf/1/$ref",
                    "https://json-schema.org/draft/2020-12/meta/applicator");
  EXPECT_DEPENDENCY(traces, 3, "https://www.sourcemeta.com/custom-metaschema",
                    "/allOf/2/$ref",
                    "https://json-schema.org/draft/2020-12/meta/validation");
}

TEST(Bundle_dependencies, sibling_schemas_with_shared_dependency) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "a": { "$ref": "https://www.sourcemeta.com/sibling-a" },
      "b": { "$ref": "https://www.sourcemeta.com/sibling-b" }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(origin, sourcemeta::core::to_pointer(pointer),
                            target);
      });

  EXPECT_EQ(traces.size(), 4);

  EXPECT_DEPENDENCY(traces, 0, "https://www.example.com", "/properties/a/$ref",
                    "https://www.sourcemeta.com/sibling-a");
  EXPECT_DEPENDENCY(traces, 1, "https://www.example.com", "/properties/b/$ref",
                    "https://www.sourcemeta.com/sibling-b");
  EXPECT_DEPENDENCY(traces, 2, "https://www.sourcemeta.com/sibling-a", "/$ref",
                    "https://www.sourcemeta.com/shared");
  EXPECT_DEPENDENCY(traces, 3, "https://www.sourcemeta.com/shared", "/$ref",
                    "https://www.sourcemeta.com/deep");
}

TEST(Bundle_dependencies, embedded_custom_metaschema_offline) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  // Note that we use a resolver that does not know about
  // the custom meta-schema embedded in the document
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(std::string{origin},
                            sourcemeta::core::to_pointer(pointer),
                            std::string{target});
      });

  EXPECT_TRUE(traces.empty());
}

TEST(Bundle_dependencies, embedded_custom_metaschema_offline_2019_09) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true,
          "https://json-schema.org/draft/2019-09/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  // Note that we use a resolver that does not know about
  // the custom meta-schema embedded in the document
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(std::string{origin},
                            sourcemeta::core::to_pointer(pointer),
                            std::string{target});
      });

  EXPECT_TRUE(traces.empty());
}

TEST(Bundle_dependencies, embedded_custom_metaschema_offline_draft7) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  // Note that we use a resolver that does not know about
  // the custom meta-schema embedded in the document
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(std::string{origin},
                            sourcemeta::core::to_pointer(pointer),
                            std::string{target});
      });

  EXPECT_TRUE(traces.empty());
}

TEST(Bundle_dependencies, embedded_custom_metaschema_offline_draft6) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "object"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  // Note that we use a resolver that does not know about
  // the custom meta-schema embedded in the document
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(std::string{origin},
                            sourcemeta::core::to_pointer(pointer),
                            std::string{target});
      });

  EXPECT_TRUE(traces.empty());
}

TEST(Bundle_dependencies, embedded_custom_metaschema_offline_draft4) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  // Note that we use a resolver that does not know about
  // the custom meta-schema embedded in the document
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(std::string{origin},
                            sourcemeta::core::to_pointer(pointer),
                            std::string{target});
      });

  EXPECT_TRUE(traces.empty());
}

TEST(Bundle_dependencies, embedded_custom_metaschema_offline_draft3) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "type": "string",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  std::vector<std::tuple<std::string, sourcemeta::core::Pointer, std::string>>
      traces;

  // Note that we use a resolver that does not know about
  // the custom meta-schema embedded in the document
  sourcemeta::blaze::dependencies(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      [&traces](const auto &origin, const auto &pointer, const auto &target,
                const auto &) {
        traces.emplace_back(std::string{origin},
                            sourcemeta::core::to_pointer(pointer),
                            std::string{target});
      });

  EXPECT_TRUE(traces.empty());
}
