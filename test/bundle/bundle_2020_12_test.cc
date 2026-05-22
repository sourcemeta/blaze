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
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/foo/bar",
      "$anchor": "baz"
    })JSON");
  } else if (identifier == "https://example.com/baz-anchor") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
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
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/test-1",
      "type": "string"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-2") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/test-2",
      "$ref": "test-3"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-3") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/test-3",
      "$ref": "test-1"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/test-4") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/test-4",
      "type": "boolean"
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/recursive") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/recursive",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  } else if (identifier ==
             "https://www.sourcemeta.com/recursive-empty-fragment") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/recursive-empty-fragment#",
      "properties": {
        "foo": { "$ref": "#" }
      }
    })JSON");
  } else if (identifier == "https://www.sourcemeta.com/anonymous") {
    return sourcemeta::core::parse_json(R"JSON({
      "type": "integer"
    })JSON");
  } else if (identifier == "https://example.com/nested/ref-string.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$ref": "string.json"
    })JSON");
  } else if (identifier == "https://example.com/nested/string.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    })JSON");
  } else if (identifier == "https://example.com/meta/1.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://example.com/meta/2.json",
      "$id": "https://example.com/meta/1.json",
      "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
    })JSON");
  } else if (identifier == "https://example.com/meta/2.json") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/meta/2.json",
      "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
    })JSON");
  } else if (identifier == "https://cdn.example.com/schemas/foo") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/foo",
      "$defs": {
        "bar": {
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/dedup-a") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/dedup-a",
      "$ref": "dedup-common",
      "$defs": {
        "https://example.com/dedup-common": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/dedup-common",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/dedup-b") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/dedup-b",
      "$ref": "dedup-common",
      "$defs": {
        "https://example.com/dedup-common": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/dedup-common",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://www.example.com/schemas/bundled") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/schemas/parent",
      "$ref": "./child",
      "$defs": {
        "https://example.com/schemas/child": {
          "$id": "https://example.com/schemas/child",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/dedup-conflict-a") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/dedup-conflict-a",
      "$ref": "dedup-conflict-common",
      "$defs": {
        "https://example.com/dedup-conflict-common": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/dedup-conflict-common",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/dedup-conflict-b") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/dedup-conflict-b",
      "$ref": "dedup-conflict-common",
      "$defs": {
        "https://example.com/dedup-conflict-common": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/dedup-conflict-common",
          "type": "integer"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/elevate-single") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/elevate-single",
      "$ref": "elevate-single-nested",
      "$defs": {
        "https://example.com/elevate-single-nested": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/elevate-single-nested",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/shared-direct") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/shared-direct",
      "type": "string"
    })JSON");
  } else if (identifier == "https://example.com/cross-dialect-host") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/cross-dialect-host",
      "$ref": "cross-dialect-nested",
      "$defs": {
        "https://example.com/cross-dialect-nested": {
          "$schema": "http://json-schema.org/draft-04/schema#",
          "id": "https://example.com/cross-dialect-nested",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/host-with-relative-nested") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/host-with-relative-nested",
      "$ref": "relative-nested",
      "$defs": {
        "relative-nested": {
          "$id": "relative-nested",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/collision-a") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/collision-a",
      "$ref": "collision-common",
      "$defs": {
        "https://example.com/collision-common": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/collision-common",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/collision-b") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/collision-b",
      "$ref": "collision-common",
      "$defs": {
        "https://example.com/collision-common": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/collision-common",
          "type": "string"
        }
      }
    })JSON");
  } else if (identifier == "https://example.com/custom-cross-ref-meta") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/custom-cross-ref-meta",
      "allOf": [
        { "$ref": "https://example.com/main#/$defs/Bar" }
      ]
    })JSON");
  } else if (identifier == "https://example.com/custom-full-meta") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/custom-full-meta",
      "$vocabulary": {
        "https://json-schema.org/draft/2020-12/vocab/core": true,
        "https://json-schema.org/draft/2020-12/vocab/applicator": true,
        "https://json-schema.org/draft/2020-12/vocab/validation": true
      }
    })JSON");
  } else if (identifier == "https://example.com/reserved-id-meta") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "__sourcemeta-blaze-bundle__"
    })JSON");
  } else if (identifier == "https://example.com/prebundled-with-shared") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/prebundled-with-shared",
      "$ref": "shared-direct",
      "$defs": {
        "https://example.com/shared-direct": {
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "$id": "https://example.com/shared-direct",
          "type": "string"
        }
      }
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(Bundle_2020_12, no_references_no_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, const_no_references_no_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  const auto result = sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Bundle_2020_12, simple_with_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" },
      "dyn": { "$dynamicRef": "https://www.sourcemeta.com/test-4" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" },
      "dyn": { "$dynamicRef": "https://www.sourcemeta.com/test-4" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      },
      "https://www.sourcemeta.com/test-4": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-4",
        "type": "boolean"
      },
      "https://example.com/foo/bar": {
        "$id": "https://example.com/foo/bar",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$anchor": "baz"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, simple_without_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" },
      "dyn": { "$dynamicRef": "https://www.sourcemeta.com/test-4" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" },
      "bar": { "$id": "https://www.sourcemeta.com", "$ref": "test-2" },
      "baz": { "$ref": "https://example.com/foo/bar#baz" },
      "qux": { "$ref": "https://example.com/foo/bar" },
      "dyn": { "$dynamicRef": "https://www.sourcemeta.com/test-4" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      },
      "https://www.sourcemeta.com/test-4": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-4",
        "type": "boolean"
      },
      "https://example.com/foo/bar": {
        "$id": "https://example.com/foo/bar",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$anchor": "baz"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, schema_not_found) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/xxx" }
    }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::bundle(
                   document, sourcemeta::blaze::schema_walker, test_resolver),
               sourcemeta::blaze::SchemaResolutionError);
}

TEST(Bundle_2020_12, anchor_not_found) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://example.com/foo/bar#xxxxxxxx" }
    }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::bundle(
                   document, sourcemeta::blaze::schema_walker, test_resolver),
               sourcemeta::blaze::SchemaReferenceError);
}

TEST(Bundle_2020_12, idempotency) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, pre_embedded) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    },
    "$defs": {
      "already-embedded": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-2" }
    },
    "$defs": {
      "already-embedded": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-2": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-2",
        "$ref": "test-3"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-3",
        "$ref": "test-1"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, taken_definitions_entry) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "test": { "$ref": "https://www.sourcemeta.com/test-1" },
      "extra": { "$ref": "https://www.sourcemeta.com/test-4" }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-1": { "foo": 1 },
      "https://www.sourcemeta.com/test-1/x": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-4": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x/x": { "foo": 1 },
      "https://www.sourcemeta.com/test-4/x/x/x": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-4",
        "type": "boolean"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, recursive) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "$defs": {
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

TEST(Bundle_2020_12, recursive_empty_fragment) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive-empty-fragment#"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive-empty-fragment#",
    "$defs": {
      "https://www.sourcemeta.com/recursive-empty-fragment#": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/recursive-empty-fragment#",
        "properties": {
          "foo": { "$ref": "#" }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, anonymous_no_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$ref": "https://www.sourcemeta.com/anonymous"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            "https://json-schema.org/draft/2020-12/schema");

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

TEST(Bundle_2020_12, relative_in_target_without_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "nested/ref-string.json"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "nested/ref-string.json",
    "$defs": {
      "https://example.com/nested/ref-string.json": {
        "$id": "https://example.com/nested/ref-string.json",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$ref": "string.json"
      },
      "https://example.com/nested/string.json": {
        "$id": "https://example.com/nested/string.json",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, relative_base_uri_with_ref) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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
    "$schema": "https://json-schema.org/draft/2020-12/schema",
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

TEST(Bundle_2020_12, metaschema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "__sourcemeta-blaze-bundle__",
    "$defs": {
      "__sourcemeta-blaze-bundle__": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "__sourcemeta-blaze-bundle__",
        "type": "string"
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, openapi_3_1_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "__sourcemeta-blaze-bundle__",
    "$defs": {
      "__sourcemeta-blaze-bundle__": {
        "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
        "$id": "__sourcemeta-blaze-bundle__",
        "type": "object"
      },
      "https://spec.openapis.org/oas/3.1/meta/base": {
        "$id": "https://spec.openapis.org/oas/3.1/meta/base",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "title": "OAS Base vocabulary",
        "description": "A JSON Schema Vocabulary used in the OpenAPI Schema Dialect",
        "$vocabulary": {
          "https://spec.openapis.org/oas/3.1/vocab/base": true
        },
        "$dynamicAnchor": "meta",
        "type": ["object", "boolean"],
        "properties": {
          "example": true,
          "discriminator": {"$ref": "#/$defs/discriminator"},
          "externalDocs": {"$ref": "#/$defs/external-docs"},
          "xml": {"$ref": "#/$defs/xml"}
        },
        "$defs": {
          "extensible": {"patternProperties": {"^x-": true}},
          "discriminator": {
            "$ref": "#/$defs/extensible",
            "type": "object",
            "properties": {
              "propertyName": {"type": "string"},
              "mapping": {
                "type": "object",
                "additionalProperties": {"type": "string"}
              }
            },
            "required": ["propertyName"],
            "unevaluatedProperties": false
          },
          "external-docs": {
            "$ref": "#/$defs/extensible",
            "type": "object",
            "properties": {
              "url": {"type": "string", "format": "uri-reference"},
              "description": {"type": "string"}
            },
            "required": ["url"],
            "unevaluatedProperties": false
          },
          "xml": {
            "$ref": "#/$defs/extensible",
            "type": "object",
            "properties": {
              "name": {"type": "string"},
              "namespace": {"type": "string", "format": "uri"},
              "prefix": {"type": "string"},
              "attribute": {"type": "boolean"},
              "wrapped": {"type": "boolean"}
            },
            "unevaluatedProperties": false
          }
        }
      },
      "https://spec.openapis.org/oas/3.1/dialect/base": {
        "$id": "https://spec.openapis.org/oas/3.1/dialect/base",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "title": "OpenAPI 3.1 Schema Object Dialect",
        "description": "A JSON Schema dialect describing schemas found in OpenAPI documents",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true,
          "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true,
          "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
          "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
          "https://json-schema.org/draft/2020-12/vocab/content": true,
          "https://spec.openapis.org/oas/3.1/vocab/base": false
        },
        "$dynamicAnchor": "meta",
        "allOf": [
          {"$ref": "https://json-schema.org/draft/2020-12/schema"},
          {"$ref": "https://spec.openapis.org/oas/3.1/meta/base"}
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, hyperschema_smoke) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://json-schema.org/draft/2020-12/hyper-schema"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  EXPECT_TRUE(document.is_object());
}

TEST(Bundle_2020_12, hyperschema_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://json-schema.org/draft/2020-12/schema" },
      { "$ref": "https://json-schema.org/draft/2020-12/meta/hyper-schema" }
    ]
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "$ref": "https://json-schema.org/draft/2020-12/schema" },
      { "$ref": "https://json-schema.org/draft/2020-12/meta/hyper-schema" }
    ]
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, bundle_to_definitions) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver, "", "",
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

TEST(Bundle_2020_12, custom_nested_object_path_non_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver, "", "",
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

TEST(Bundle_2020_12, custom_nested_object_path_half_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": { "foo": {} }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver, "", "",
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

TEST(Bundle_2020_12, custom_nested_object_path_half_existent_with_array) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": [ { "foo": {} } ]
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver, "", "",
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

TEST(Bundle_2020_12, custom_nested_object_path_not_object) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": { "foo": { "bar": [] } }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::bundle(
                   document, sourcemeta::blaze::schema_walker, test_resolver,
                   "", "",
                   sourcemeta::core::Pointer{"x-definitions", "foo", "bar"}),
               sourcemeta::blaze::SchemaError);
}

TEST(Bundle_2020_12, default_id_with_different_ref_target_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Entry",
    "$ref": "schemas/bundled"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver, "", "https://www.example.com/entry");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.example.com/entry",
    "title": "Entry",
    "$ref": "https://example.com/schemas/parent",
    "$defs": {
      "https://example.com/schemas/child": {
        "$id": "https://example.com/schemas/child",
        "type": "string"
      },
      "https://example.com/schemas/parent": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/schemas/parent",
        "$ref": "./child"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, default_id_with_different_ref_target_id_duplicate_refs) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "first": { "$ref": "https://cdn.example.com/schemas/foo" },
      "second": { "$ref": "https://cdn.example.com/schemas/foo" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver, "", "https://www.example.com/entry");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.example.com/entry",
    "properties": {
      "first": { "$ref": "https://example.com/foo" },
      "second": { "$ref": "https://example.com/foo" }
    },
    "$defs": {
      "https://example.com/foo": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/foo",
        "$defs": {
          "bar": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, default_id_with_different_ref_target_id_with_fragment) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://cdn.example.com/schemas/foo#/$defs/bar" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver, "", "https://www.example.com/entry");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.example.com/entry",
    "properties": {
      "foo": { "$ref": "https://example.com/foo#/$defs/bar" }
    },
    "$defs": {
      "https://example.com/foo": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/foo",
        "$defs": {
          "bar": {
            "type": "string"
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, deduplicate_embedded_from_prebundled) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/dedup-entry",
    "allOf": [
      { "$ref": "dedup-a" },
      { "$ref": "dedup-b" }
    ]
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/dedup-entry",
    "allOf": [
      { "$ref": "dedup-a" },
      { "$ref": "dedup-b" }
    ],
    "$defs": {
      "https://example.com/dedup-a": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/dedup-a",
        "$ref": "dedup-common"
      },
      "https://example.com/dedup-b": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/dedup-b",
        "$ref": "dedup-common"
      },
      "https://example.com/dedup-common": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/dedup-common",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, conflicting_embedded_from_prebundled) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/dedup-conflict-entry",
    "allOf": [
      { "$ref": "dedup-conflict-a" },
      { "$ref": "dedup-conflict-b" }
    ]
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::bundle(
                   document, sourcemeta::blaze::schema_walker, test_resolver),
               sourcemeta::blaze::SchemaError);
}

TEST(Bundle_2020_12, elevate_embedded_from_single_prebundled) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/elevate-entry",
    "$ref": "elevate-single"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/elevate-entry",
    "$ref": "elevate-single",
    "$defs": {
      "https://example.com/elevate-single": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/elevate-single",
        "$ref": "elevate-single-nested"
      },
      "https://example.com/elevate-single-nested": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/elevate-single-nested",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, direct_and_embedded_reference_no_duplicate) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/direct-and-embedded-entry",
    "allOf": [
      { "$ref": "prebundled-with-shared" },
      { "$ref": "shared-direct" }
    ]
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/direct-and-embedded-entry",
    "allOf": [
      { "$ref": "prebundled-with-shared" },
      { "$ref": "shared-direct" }
    ],
    "$defs": {
      "https://example.com/prebundled-with-shared": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/prebundled-with-shared",
        "$ref": "shared-direct"
      },
      "https://example.com/shared-direct": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/shared-direct",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_embedded_cross_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/cross-dialect-entry",
    "$ref": "cross-dialect-host"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/cross-dialect-entry",
    "$ref": "cross-dialect-host",
    "$defs": {
      "https://example.com/cross-dialect-host": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/cross-dialect-host",
        "$ref": "cross-dialect-nested"
      },
      "https://example.com/cross-dialect-nested": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "https://example.com/cross-dialect-nested",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, no_elevate_relative_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/relative-entry",
    "$ref": "host-with-relative-nested"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/relative-entry",
    "$ref": "host-with-relative-nested",
    "$defs": {
      "https://example.com/host-with-relative-nested": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/host-with-relative-nested",
        "$ref": "relative-nested",
        "$defs": {
          "relative-nested": {
            "$id": "relative-nested",
            "type": "string"
          }
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, deduplicate_embedded_with_preexisting_key_collision) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/collision-entry",
    "$defs": {
      "https://example.com/collision-common": {
        "type": "boolean"
      }
    },
    "allOf": [
      { "$ref": "collision-a" },
      { "$ref": "collision-b" }
    ]
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/collision-entry",
    "allOf": [
      { "$ref": "collision-a" },
      { "$ref": "collision-b" }
    ],
    "$defs": {
      "https://example.com/collision-common": {
        "type": "boolean"
      },
      "https://example.com/collision-a": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/collision-a",
        "$ref": "collision-common"
      },
      "https://example.com/collision-b": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/collision-b",
        "$ref": "collision-common"
      },
      "https://example.com/collision-common/x": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/collision-common",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_inner_with_absolute_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$id": "https://example.com/main",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "https://example.com/main/x",
    "$defs": {
      "https://example.com/main/x": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "https://example.com/main/x",
        "type": "string"
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_inner_self_ref_with_fragment) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/custom-full-meta",
    "$id": "https://example.com/main",
    "type": "object",
    "properties": {
      "child": { "$ref": "https://example.com/main#/$defs/Bar" }
    },
    "$defs": {
      "Bar": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "https://example.com/main/x",
    "$defs": {
      "https://example.com/main/x": {
        "$schema": "https://example.com/custom-full-meta",
        "$id": "https://example.com/main/x",
        "type": "object",
        "properties": {
          "child": { "$ref": "https://example.com/main/x#/$defs/Bar" }
        },
        "$defs": {
          "Bar": { "type": "string" }
        }
      },
      "https://example.com/custom-full-meta": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/custom-full-meta",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_no_id_with_default_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver, "", "https://example.com/default");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/default",
    "$ref": "https://example.com/default/x",
    "$defs": {
      "https://example.com/default/x": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "https://example.com/default/x",
        "type": "string"
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_collision_uses_x_x) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$id": "https://example.com/main",
    "type": "object",
    "$defs": {
      "sub": {
        "$id": "https://example.com/main/x",
        "type": "integer"
      }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "https://example.com/main/x/x",
    "$defs": {
      "https://example.com/main/x/x": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "https://example.com/main/x/x",
        "type": "object",
        "$defs": {
          "sub": {
            "$id": "https://example.com/main/x",
            "type": "integer"
          }
        }
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_idempotent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$id": "https://example.com/main",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);
  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "https://example.com/main/x",
    "$defs": {
      "https://example.com/main/x": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "https://example.com/main/x",
        "type": "string"
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_cross_referencing_meta_schema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/custom-cross-ref-meta",
    "$id": "https://example.com/main",
    "$defs": {
      "Bar": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "https://example.com/main/x",
    "$defs": {
      "https://example.com/main/x": {
        "$schema": "https://example.com/custom-cross-ref-meta",
        "$id": "https://example.com/main/x",
        "$defs": {
          "Bar": { "type": "string" }
        }
      },
      "https://example.com/custom-cross-ref-meta": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/custom-cross-ref-meta",
        "allOf": [
          { "$ref": "https://example.com/main/x#/$defs/Bar" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_anonymous_inner_keeps_fragment_only_refs_working) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/custom-full-meta",
    "type": "object",
    "properties": {
      "child": { "$ref": "#/$defs/Bar" }
    },
    "$defs": {
      "Bar": { "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "__sourcemeta-blaze-bundle__",
    "$defs": {
      "__sourcemeta-blaze-bundle__": {
        "$schema": "https://example.com/custom-full-meta",
        "$id": "__sourcemeta-blaze-bundle__",
        "type": "object",
        "properties": {
          "child": { "$ref": "#/$defs/Bar" }
        },
        "$defs": {
          "Bar": { "type": "string" }
        }
      },
      "https://example.com/custom-full-meta": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/custom-full-meta",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_default_container_skips_elevation) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$id": "https://example.com/main",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver, "", "",
                            sourcemeta::core::Pointer{"components"});

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$id": "https://example.com/main",
    "type": "string",
    "components": {
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_openapi_with_inner_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "$id": "https://example.com/my-api",
    "type": "object"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/my-api",
    "$ref": "https://example.com/my-api/x",
    "$defs": {
      "https://example.com/my-api/x": {
        "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
        "$id": "https://example.com/my-api/x",
        "type": "object"
      },
      "https://spec.openapis.org/oas/3.1/meta/base": {
        "$id": "https://spec.openapis.org/oas/3.1/meta/base",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "title": "OAS Base vocabulary",
        "description": "A JSON Schema Vocabulary used in the OpenAPI Schema Dialect",
        "$vocabulary": {
          "https://spec.openapis.org/oas/3.1/vocab/base": true
        },
        "$dynamicAnchor": "meta",
        "type": ["object", "boolean"],
        "properties": {
          "example": true,
          "discriminator": {"$ref": "#/$defs/discriminator"},
          "externalDocs": {"$ref": "#/$defs/external-docs"},
          "xml": {"$ref": "#/$defs/xml"}
        },
        "$defs": {
          "extensible": {"patternProperties": {"^x-": true}},
          "discriminator": {
            "$ref": "#/$defs/extensible",
            "type": "object",
            "properties": {
              "propertyName": {"type": "string"},
              "mapping": {
                "type": "object",
                "additionalProperties": {"type": "string"}
              }
            },
            "required": ["propertyName"],
            "unevaluatedProperties": false
          },
          "external-docs": {
            "$ref": "#/$defs/extensible",
            "type": "object",
            "properties": {
              "url": {"type": "string", "format": "uri-reference"},
              "description": {"type": "string"}
            },
            "required": ["url"],
            "unevaluatedProperties": false
          },
          "xml": {
            "$ref": "#/$defs/extensible",
            "type": "object",
            "properties": {
              "name": {"type": "string"},
              "namespace": {"type": "string", "format": "uri"},
              "prefix": {"type": "string"},
              "attribute": {"type": "boolean"},
              "wrapped": {"type": "boolean"}
            },
            "unevaluatedProperties": false
          }
        }
      },
      "https://spec.openapis.org/oas/3.1/dialect/base": {
        "$id": "https://spec.openapis.org/oas/3.1/dialect/base",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "title": "OpenAPI 3.1 Schema Object Dialect",
        "description": "A JSON Schema dialect describing schemas found in OpenAPI documents",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true,
          "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true,
          "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
          "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
          "https://json-schema.org/draft/2020-12/vocab/content": true,
          "https://spec.openapis.org/oas/3.1/vocab/base": false
        },
        "$dynamicAnchor": "meta",
        "allOf": [
          {"$ref": "https://json-schema.org/draft/2020-12/schema"},
          {"$ref": "https://spec.openapis.org/oas/3.1/meta/base"}
        ]
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, elevate_fallback_collision_throws) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/reserved-id-meta",
    "type": "string"
  })JSON");

  try {
    sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                              test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReservedIdentifierError &error) {
    EXPECT_EQ(error.identifier(), "__sourcemeta-blaze-bundle__");
  } catch (...) {
    FAIL();
  }
}

TEST(Bundle_2020_12, fallback_collision_allowed_when_input_has_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/reserved-id-meta",
    "$id": "https://example.com/main",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "$ref": "https://example.com/main/x",
    "$defs": {
      "https://example.com/main/x": {
        "$schema": "__sourcemeta-blaze-bundle__",
        "$id": "https://example.com/main/x",
        "type": "string"
      },
      "__sourcemeta-blaze-bundle__": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "__sourcemeta-blaze-bundle__"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
