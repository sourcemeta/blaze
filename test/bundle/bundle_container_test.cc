#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>

#include <string>      // std::string
#include <string_view> // std::string_view

static auto test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://www.sourcemeta.com/test-1") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/test-1",
      "type": "string"
    })JSON");
  }
  if (identifier == "https://www.sourcemeta.com/test-2") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://www.sourcemeta.com/test-2",
      "$ref": "test-3"
    })JSON");
  }
  if (identifier == "https://www.sourcemeta.com/test-3") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-06/schema#",
      "$id": "https://www.sourcemeta.com/test-3",
      "allOf": [ { "$ref": "test-4" } ]
    })JSON");
  }
  if (identifier == "https://www.sourcemeta.com/test-4") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-04/schema#",
      "id": "https://www.sourcemeta.com/test-4",
      "type": "string"
    })JSON");
  }
  if (identifier == "https://www.sourcemeta.com/recursive") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/recursive",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  }
  if (identifier == "https://example.com/meta/1.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://example.com/meta/2.json",
      "$id": "https://example.com/meta/1.json",
      "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
    })JSON");
  }
  if (identifier == "https://example.com/meta/2.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/meta/2.json",
      "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
    })JSON");
  }
  return sourcemeta::core::schema_resolver(identifier);
}

static auto draft7_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://www.sourcemeta.com/recursive") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-07/schema#",
      "$id": "https://www.sourcemeta.com/recursive",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  }
  return sourcemeta::core::schema_resolver(identifier);
}

TEST(draft7_bundle_to_defs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, draft7_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"$defs"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://www.sourcemeta.com/recursive",
    "$defs": {
      "https://www.sourcemeta.com/recursive": {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "$id": "https://www.sourcemeta.com/recursive",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(bundle_to_definitions) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"definitions"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "definitions": {
      "https://www.sourcemeta.com/recursive": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/recursive",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(bundle_to_definitions_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::core::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References, "", "",
                            sourcemeta::core::Pointer{"definitions"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/recursive",
    "definitions": {
      "https://www.sourcemeta.com/recursive": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/recursive",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_nested_object_path_non_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"x-definitions", "foo", "bar"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": {
      "foo": {
        "bar": {
          "https://www.sourcemeta.com/recursive": {
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "$id": "https://www.sourcemeta.com/recursive",
            "properties": {
              "foo": { "$ref": "#" }
            }
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_nested_object_path_half_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": { "foo": {} }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"x-definitions", "foo", "bar"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": {
      "foo": {
        "bar": {
          "https://www.sourcemeta.com/recursive": {
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "$id": "https://www.sourcemeta.com/recursive",
            "properties": {
              "foo": { "$ref": "#" }
            }
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_nested_object_path_half_existent_with_array) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": [ { "foo": {} } ]
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "", "",
      sourcemeta::core::Pointer{"x-definitions", 0, "foo", "bar"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": [
      {
        "foo": {
          "bar": {
            "https://www.sourcemeta.com/recursive": {
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "$id": "https://www.sourcemeta.com/recursive",
              "properties": {
                "foo": { "$ref": "#" }
              }
            }
          }
        }
      }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(custom_paths_with_relative_external_and_default_base) {
  auto document{sourcemeta::core::parse_json(R"JSON({
    "components": {
      "schemas": {
        "Pet": { "$ref": "test-1" }
      }
    }
  })JSON")};

  const sourcemeta::core::Pointer pet{"components", "schemas", "Pet"};
  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas,
      "https://json-schema.org/draft/2020-12/schema", "",
      sourcemeta::core::Pointer{"x-bundled"},
      {sourcemeta::core::to_weak_pointer(pet)},
      "https://www.sourcemeta.com/openapi.json");

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "components": {
      "schemas": {
        "Pet": { "$ref": "test-1" }
      }
    },
    "x-bundled": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(document, expected);
}

TEST(custom_paths_with_externals) {
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

  const sourcemeta::core::Pointer path1{"wrapper"};
  const sourcemeta::core::Pointer path2{"common", "test"};
  const sourcemeta::core::Pointer path3{"common", "with-id"};
  sourcemeta::blaze::bundle(
      document, sourcemeta::core::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas,
      "https://json-schema.org/draft/2020-12/schema", "",
      sourcemeta::core::Pointer{"components"},
      {
          sourcemeta::core::to_weak_pointer(path1),
          sourcemeta::core::to_weak_pointer(path2),
          sourcemeta::core::to_weak_pointer(path3),
      });

  const auto expected{sourcemeta::core::parse_json(R"JSON({
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
    },
    "components": {
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "http://json-schema.org/draft-06/schema#",
        "$id": "https://www.sourcemeta.com/test-3",
        "allOf": [ { "$ref": "test-4" } ]
      },
      "https://www.sourcemeta.com/test-4": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "https://www.sourcemeta.com/test-4",
        "type": "string"
      }
    }
  })JSON")};

  EXPECT_EQ(document, expected);
}
