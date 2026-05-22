#include <gtest/gtest.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

#include <string>      // std::string
#include <string_view> // std::string_view

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://example.com/foo/bar") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://example.com/foo/bar",
      "$anchor": "baz"
    })JSON");
  } else if (identifier == "https://example.com/baz-anchor") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://example.com/baz-anchor",
      "$defs": {
        "baz": {
          "$anchor": "baz",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-1") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
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
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://www.sourcemeta.com/test-3",
      "$ref": "test-1"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-4") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://www.sourcemeta.com/test-4",
      "type": "boolean"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/recursive") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://www.sourcemeta.com/recursive",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  } else if (identifier ==
             "https://www.sourcemeta.com/recursive-empty-fragment") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://www.sourcemeta.com/recursive-empty-fragment#",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/anonymous") {
    return sourcemeta::core::parse_json(R"JSON({
      "type": "integer"
    })JSON");
  } else if (identifier == "https://example.com/meta/1.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://example.com/meta/2.json",
      "$id": "https://example.com/meta/1.json",
      "$vocabulary": { "https://json-schema.org/draft/2019-09/vocab/core": true }
    })JSON");
  } else if (identifier == "https://example.com/meta/2.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2019-09/schema",
      "$id": "https://example.com/meta/2.json",
      "$vocabulary": { "https://json-schema.org/draft/2019-09/vocab/core": true }
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(Bundle_2019_09, no_references_no_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, const_no_references_no_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  const auto result = sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Bundle_2019_09, simple_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      },
      "https://example.com/foo/bar": {
        "$id": "https://example.com/foo/bar",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$anchor": "baz"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, simple_without_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      },
      "https://example.com/foo/bar": {
        "$id": "https://example.com/foo/bar",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$anchor": "baz"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, schema_not_found) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/xxx" }
    }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::bundle(
                   document, sourcemeta::blaze::schema_walker, test_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Bundle_2019_09, idempotency) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);
  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);
  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, pre_embedded) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    },
    "$defs": {
      "already-embedded": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    },
    "$defs": {
      "already-embedded": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, taken_definitions_entry) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-1" },
      "extra": { "$ref": "https://www.sourcemeta.com/test-4" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": { "foo": 1 },
      "https://www.sourcemeta.com/test-4": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x/x": { "foo": 1 }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-1" },
      "extra": { "$ref": "https://www.sourcemeta.com/test-4" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": { "foo": 1 },
      "https://www.sourcemeta.com/test-1/x": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-4": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x/x": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x/x/x": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/test-4",
        "type": "boolean"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, recursive) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "$defs": {
      "https://www.sourcemeta.com/recursive": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/recursive",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, recursive_empty_fragment) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.sourcemeta.com/recursive-empty-fragment#"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://www.sourcemeta.com/recursive-empty-fragment#",
    "$defs": {
      "https://www.sourcemeta.com/recursive-empty-fragment#": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://www.sourcemeta.com/recursive-empty-fragment#",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, anonymous_no_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://www.sourcemeta.com/anonymous"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            "https://json-schema.org/draft/2019-09/schema");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://www.sourcemeta.com/anonymous",
    "$defs": {
      "https://www.sourcemeta.com/anonymous": {
        "$id": "https://www.sourcemeta.com/anonymous",
        "type": "integer"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, metaschema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "__sourcemeta-blaze-bundle__",
    "$defs": {
      "__sourcemeta-blaze-bundle__": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "__sourcemeta-blaze-bundle__",
        "type": "string"
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2019-09/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2019-09/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, relative_base_uri_with_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "common",
    "allOf": [ { "$ref": "#reference" } ],
    "definitions": {
      "reference": {
        "$anchor": "reference"
      }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "common",
    "allOf": [ { "$ref": "#reference" } ],
    "definitions": {
      "reference": {
        "$anchor": "reference"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, hyperschema_smoke) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$ref": "https://json-schema.org/draft/2019-09/hyper-schema"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  EXPECT_TRUE(document.is_object());
}

TEST(Bundle_2019_09, hyperschema_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://json-schema.org/draft/2019-09/schema" },
      { "$ref": "https://json-schema.org/draft/2019-09/meta/hyper-schema" }
    ]
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [
      { "$ref": "https://json-schema.org/draft/2019-09/schema" },
      { "$ref": "https://json-schema.org/draft/2019-09/meta/hyper-schema" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2019_09, hyperschema_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
    "$id": "https://json-schema.org/draft/2019-09/hyper-schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": true,
      "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
      "https://json-schema.org/draft/2019-09/vocab/format": false,
      "https://json-schema.org/draft/2019-09/vocab/content": true,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema": true
    },
    "$recursiveAnchor": true,
    "title": "JSON Hyper-Schema",
    "allOf": [
      { "$ref": "https://json-schema.org/draft/2019-09/schema" },
      { "$ref": "https://json-schema.org/draft/2019-09/meta/hyper-schema" }
    ],
    "links": [
      {
        "rel": "self",
        "href": "{+%24id}"
      }
    ]
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
    "$id": "https://json-schema.org/draft/2019-09/hyper-schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": true,
      "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
      "https://json-schema.org/draft/2019-09/vocab/format": false,
      "https://json-schema.org/draft/2019-09/vocab/content": true,
      "https://json-schema.org/draft/2019-09/vocab/hyper-schema": true
    },
    "$recursiveAnchor": true,
    "title": "JSON Hyper-Schema",
    "allOf": [
      { "$ref": "https://json-schema.org/draft/2019-09/schema" },
      { "$ref": "https://json-schema.org/draft/2019-09/meta/hyper-schema" }
    ],
    "links": [
      { "rel": "self", "href": "{+%24id}" }
    ],
    "$defs": {
      "https://json-schema.org/draft/2019-09/meta/core": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/core",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true
        },
        "$recursiveAnchor": true,
        "title": "Core vocabulary meta-schema",
        "type": ["object", "boolean"],
        "properties": {
          "$id": {
            "type": "string",
            "format": "uri-reference",
            "$comment": "Non-empty fragments not allowed.",
            "pattern": "^[^#]*#?$"
          },
          "$schema": {"type": "string", "format": "uri"},
          "$anchor": {
            "type": "string",
            "pattern": "^[A-Za-z][-A-Za-z0-9.:_]*$"
          },
          "$ref": {"type": "string", "format": "uri-reference"},
          "$recursiveRef": {"type": "string", "format": "uri-reference"},
          "$recursiveAnchor": {"type": "boolean", "default": false},
          "$vocabulary": {
            "type": "object",
            "propertyNames": {"type": "string", "format": "uri"},
            "additionalProperties": {"type": "boolean"}
          },
          "$comment": {"type": "string"},
          "$defs": {
            "type": "object",
            "additionalProperties": {"$recursiveRef": "#"},
            "default": {}
          }
        }
      },
      "https://json-schema.org/draft/2019-09/meta/applicator": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/applicator",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/applicator": true
        },
        "$recursiveAnchor": true,
        "title": "Applicator vocabulary meta-schema",
        "type": ["object", "boolean"],
        "properties": {
          "additionalItems": {"$recursiveRef": "#"},
          "unevaluatedItems": {"$recursiveRef": "#"},
          "items": {
            "anyOf": [
              {"$recursiveRef": "#"},
              {"$ref": "#/$defs/schemaArray"}
            ]
          },
          "contains": {"$recursiveRef": "#"},
          "additionalProperties": {"$recursiveRef": "#"},
          "unevaluatedProperties": {"$recursiveRef": "#"},
          "properties": {
            "type": "object",
            "additionalProperties": {"$recursiveRef": "#"},
            "default": {}
          },
          "patternProperties": {
            "type": "object",
            "additionalProperties": {"$recursiveRef": "#"},
            "propertyNames": {"format": "regex"},
            "default": {}
          },
          "dependentSchemas": {
            "type": "object",
            "additionalProperties": {"$recursiveRef": "#"}
          },
          "propertyNames": {"$recursiveRef": "#"},
          "if": {"$recursiveRef": "#"},
          "then": {"$recursiveRef": "#"},
          "else": {"$recursiveRef": "#"},
          "allOf": {"$ref": "#/$defs/schemaArray"},
          "anyOf": {"$ref": "#/$defs/schemaArray"},
          "oneOf": {"$ref": "#/$defs/schemaArray"},
          "not": {"$recursiveRef": "#"}
        },
        "$defs": {
          "schemaArray": {
            "type": "array",
            "minItems": 1,
            "items": {"$recursiveRef": "#"}
          }
        }
      },
      "https://json-schema.org/draft/2019-09/meta/validation": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/validation",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/validation": true
        },
        "$recursiveAnchor": true,
        "title": "Validation vocabulary meta-schema",
        "type": ["object", "boolean"],
        "properties": {
          "multipleOf": {"type": "number", "exclusiveMinimum": 0},
          "maximum": {"type": "number"},
          "exclusiveMaximum": {"type": "number"},
          "minimum": {"type": "number"},
          "exclusiveMinimum": {"type": "number"},
          "maxLength": {"$ref": "#/$defs/nonNegativeInteger"},
          "minLength": {"$ref": "#/$defs/nonNegativeIntegerDefault0"},
          "pattern": {"type": "string", "format": "regex"},
          "maxItems": {"$ref": "#/$defs/nonNegativeInteger"},
          "minItems": {"$ref": "#/$defs/nonNegativeIntegerDefault0"},
          "uniqueItems": {"type": "boolean", "default": false},
          "maxContains": {"$ref": "#/$defs/nonNegativeInteger"},
          "minContains": {"$ref": "#/$defs/nonNegativeInteger", "default": 1},
          "maxProperties": {"$ref": "#/$defs/nonNegativeInteger"},
          "minProperties": {"$ref": "#/$defs/nonNegativeIntegerDefault0"},
          "required": {"$ref": "#/$defs/stringArray"},
          "dependentRequired": {
            "type": "object",
            "additionalProperties": {"$ref": "#/$defs/stringArray"}
          },
          "const": true,
          "enum": {"type": "array", "items": true},
          "type": {
            "anyOf": [
              {"$ref": "#/$defs/simpleTypes"},
              {
                "type": "array",
                "items": {"$ref": "#/$defs/simpleTypes"},
                "minItems": 1,
                "uniqueItems": true
              }
            ]
          }
        },
        "$defs": {
          "nonNegativeInteger": {"type": "integer", "minimum": 0},
          "nonNegativeIntegerDefault0": {
            "$ref": "#/$defs/nonNegativeInteger",
            "default": 0
          },
          "simpleTypes": {
            "enum": [
              "array",
              "boolean",
              "integer",
              "null",
              "number",
              "object",
              "string"
            ]
          },
          "stringArray": {
            "type": "array",
            "items": {"type": "string"},
            "uniqueItems": true,
            "default": []
          }
        }
      },
      "https://json-schema.org/draft/2019-09/meta/meta-data": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/meta-data",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/meta-data": true
        },
        "$recursiveAnchor": true,
        "title": "Meta-data vocabulary meta-schema",
        "type": ["object", "boolean"],
        "properties": {
          "title": {"type": "string"},
          "description": {"type": "string"},
          "default": true,
          "deprecated": {"type": "boolean", "default": false},
          "readOnly": {"type": "boolean", "default": false},
          "writeOnly": {"type": "boolean", "default": false},
          "examples": {"type": "array", "items": true}
        }
      },
      "https://json-schema.org/draft/2019-09/meta/format": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/format",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/format": true
        },
        "$recursiveAnchor": true,
        "title": "Format vocabulary meta-schema",
        "type": ["object", "boolean"],
        "properties": {"format": {"type": "string"}}
      },
      "https://json-schema.org/draft/2019-09/meta/content": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/content",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/content": true
        },
        "$recursiveAnchor": true,
        "title": "Content vocabulary meta-schema",
        "type": ["object", "boolean"],
        "properties": {
          "contentMediaType": {"type": "string"},
          "contentEncoding": {"type": "string"},
          "contentSchema": {"$recursiveRef": "#"}
        }
      },
      "https://json-schema.org/draft/2019-09/schema": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true,
          "https://json-schema.org/draft/2019-09/vocab/applicator": true,
          "https://json-schema.org/draft/2019-09/vocab/validation": true,
          "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
          "https://json-schema.org/draft/2019-09/vocab/format": false,
          "https://json-schema.org/draft/2019-09/vocab/content": true
        },
        "$recursiveAnchor": true,
        "title": "Core and Validation specifications meta-schema",
        "allOf": [
          {"$ref": "meta/core"},
          {"$ref": "meta/applicator"},
          {"$ref": "meta/validation"},
          {"$ref": "meta/meta-data"},
          {"$ref": "meta/format"},
          {"$ref": "meta/content"}
        ],
        "type": ["object", "boolean"],
        "properties": {
          "definitions": {
            "$comment": "While no longer an official keyword as it is replaced by $defs, this keyword is retained in the meta-schema to prevent incompatible extensions as it remains in common use.",
            "type": "object",
            "additionalProperties": {"$recursiveRef": "#"},
            "default": {}
          },
          "dependencies": {
            "$comment": "\"dependencies\" is no longer a keyword, but schema authors should avoid redefining it to facilitate a smooth transition to \"dependentSchemas\" and \"dependentRequired\"",
            "type": "object",
            "additionalProperties": {
              "anyOf": [
                {"$recursiveRef": "#"},
                {"$ref": "meta/validation#/$defs/stringArray"}
              ]
            }
          }
        }
      },
      "https://json-schema.org/draft/2019-09/links": {
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$id": "https://json-schema.org/draft/2019-09/links",
        "title": "Link Description Object",
        "allOf": [
          {"required": ["rel", "href"]},
          {"$ref": "#/$defs/noRequiredFields"}
        ],
        "$defs": {
          "noRequiredFields": {
            "type": "object",
            "properties": {
              "anchor": {"type": "string", "format": "uri-template"},
              "anchorPointer": {
                "type": "string",
                "anyOf": [
                  {"format": "json-pointer"},
                  {"format": "relative-json-pointer"}
                ]
              },
              "rel": {
                "anyOf": [
                  {"type": "string"},
                  {
                    "type": "array",
                    "items": {"type": "string"},
                    "minItems": 1
                  }
                ]
              },
              "href": {"type": "string", "format": "uri-template"},
              "hrefSchema": {
                "$ref": "https://json-schema.org/draft/2019-09/hyper-schema",
                "default": false
              },
              "templatePointers": {
                "type": "object",
                "additionalProperties": {
                  "type": "string",
                  "anyOf": [
                    {"format": "json-pointer"},
                    {"format": "relative-json-pointer"}
                  ]
                }
              },
              "templateRequired": {
                "type": "array",
                "items": {"type": "string"},
                "uniqueItems": true
              },
              "title": {"type": "string"},
              "description": {"type": "string"},
              "targetSchema": {
                "$ref": "https://json-schema.org/draft/2019-09/hyper-schema",
                "default": true
              },
              "targetMediaType": {"type": "string"},
              "targetHints": {},
              "headerSchema": {
                "$ref": "https://json-schema.org/draft/2019-09/hyper-schema",
                "default": true
              },
              "submissionMediaType": {
                "type": "string",
                "default": "application/json"
              },
              "submissionSchema": {
                "$ref": "https://json-schema.org/draft/2019-09/hyper-schema",
                "default": true
              },
              "$comment": {"type": "string"}
            }
          }
        }
      },
      "https://json-schema.org/draft/2019-09/meta/hyper-schema": {
        "$schema": "https://json-schema.org/draft/2019-09/hyper-schema",
        "$id": "https://json-schema.org/draft/2019-09/meta/hyper-schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/hyper-schema": true
        },
        "$recursiveAnchor": true,
        "title": "JSON Hyper-Schema Vocabulary Schema",
        "type": ["object", "boolean"],
        "properties": {
          "base": {"type": "string", "format": "uri-template"},
          "links": {
            "type": "array",
            "items": {
              "$ref": "https://json-schema.org/draft/2019-09/links"
            }
          }
        },
        "links": [
          {"rel": "self", "href": "{+%24id}"}
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
