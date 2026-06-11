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
  } else if (identifier == "https://example.com/with-custom-metaschema") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://example.com/meta/1.json",
      "$id": "https://example.com/with-custom-metaschema",
      "type": "integer"
    })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(Bundle_2020_12, no_references_no_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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
                   document, sourcemeta::blaze::schema_walker, test_resolver,
                   sourcemeta::blaze::BundleMode::NonOfficialMetaschemas),
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
                   document, sourcemeta::blaze::schema_walker, test_resolver,
                   sourcemeta::blaze::BundleMode::NonOfficialMetaschemas),
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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas,
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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string",
    "$defs": {
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, metaschema_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, const_metaschema_references_mode) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  const auto result = sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string"
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(Bundle_2020_12, metaschema_references_mode_with_remote_reference) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/test-4"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/test-4",
    "$defs": {
      "https://www.sourcemeta.com/test-4": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-4",
        "type": "boolean"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, metaschema_references_mode_idempotency) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/test-4"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/test-4",
    "$defs": {
      "https://www.sourcemeta.com/test-4": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-4",
        "type": "boolean"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, remote_with_custom_metaschema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/with-custom-metaschema"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/with-custom-metaschema",
    "$defs": {
      "https://example.com/with-custom-metaschema": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "https://example.com/with-custom-metaschema",
        "type": "integer"
      },
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, remote_with_custom_metaschema_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/with-custom-metaschema"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/with-custom-metaschema",
    "$defs": {
      "https://example.com/with-custom-metaschema": {
        "$schema": "https://example.com/meta/1.json",
        "$id": "https://example.com/with-custom-metaschema",
        "type": "integer"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, ref_to_custom_metaschema) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/meta/1.json"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/meta/1.json",
    "$defs": {
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, ref_to_custom_metaschema_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/meta/1.json"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://example.com/meta/1.json",
    "$defs": {
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, official_dialect_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/test-1"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/test-1",
    "$defs": {
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, openapi_3_1_dialect_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
                            test_resolver,
                            sourcemeta::blaze::BundleMode::References);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object"
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(Bundle_2020_12, bundle_to_definitions_references_mode) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(document, sourcemeta::blaze::schema_walker,
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

TEST(Bundle_2020_12, openapi_3_1_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://spec.openapis.org/oas/3.1/dialect/base",
    "type": "object"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  EXPECT_EQ(document.at("$schema").to_string(),
            "https://spec.openapis.org/oas/3.1/dialect/base");
  EXPECT_TRUE(document.defines("$defs"));
  EXPECT_TRUE(document.at("$defs").is_object());
  EXPECT_EQ(document.at("$defs").size(), 10);

  EXPECT_EQ(
      document.at("$defs").at("https://spec.openapis.org/oas/3.1/dialect/base"),
      sourcemeta::blaze::schema_resolver(
          "https://spec.openapis.org/oas/3.1/dialect/base")
          .value());
  EXPECT_EQ(
      document.at("$defs").at("https://spec.openapis.org/oas/3.1/meta/base"),
      sourcemeta::blaze::schema_resolver(
          "https://spec.openapis.org/oas/3.1/meta/base")
          .value());
  EXPECT_EQ(
      document.at("$defs").at("https://json-schema.org/draft/2020-12/schema"),
      sourcemeta::blaze::schema_resolver(
          "https://json-schema.org/draft/2020-12/schema")
          .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/core"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/core")
                .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/applicator"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/applicator")
                .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/unevaluated"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/unevaluated")
                .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/validation"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/validation")
                .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/meta-data"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/meta-data")
                .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/format-annotation"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/format-annotation")
                .value());
  EXPECT_EQ(document.at("$defs").at(
                "https://json-schema.org/draft/2020-12/meta/content"),
            sourcemeta::blaze::schema_resolver(
                "https://json-schema.org/draft/2020-12/meta/content")
                .value());
}

TEST(Bundle_2020_12, hyperschema_smoke) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://json-schema.org/draft/2020-12/hyper-schema"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  EXPECT_TRUE(document.defines("$defs"));
  EXPECT_TRUE(document.at("$defs").is_object());
  EXPECT_EQ(document.at("$defs").size(), 11);

  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/schema"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/core"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/applicator"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/unevaluated"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/validation"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/meta-data"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/format-annotation"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/content"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/meta/hyper-schema"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/links"));
  EXPECT_TRUE(document.at("$defs").defines(
      "https://json-schema.org/draft/2020-12/hyper-schema"));
}

TEST(Bundle_2020_12, bundle_to_definitions) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
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

TEST(Bundle_2020_12, custom_nested_object_path_non_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
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

TEST(Bundle_2020_12, custom_nested_object_path_half_existent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": { "foo": {} }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
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

TEST(Bundle_2020_12, custom_nested_object_path_half_existent_with_array) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": [ { "foo": {} } ]
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
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

TEST(Bundle_2020_12, custom_nested_object_path_not_object) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "https://www.sourcemeta.com/recursive",
    "x-definitions": { "foo": { "bar": [] } }
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::bundle(
                   document, sourcemeta::blaze::schema_walker, test_resolver,
                   sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
                   "",
                   sourcemeta::core::Pointer{"x-definitions", "foo", "bar"}),
               sourcemeta::blaze::SchemaError);
}

TEST(Bundle_2020_12, default_id_with_different_ref_target_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "title": "Entry",
    "$ref": "schemas/bundled"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://www.example.com/entry");

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://www.example.com/entry");

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://www.example.com/entry");

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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
                   document, sourcemeta::blaze::schema_walker, test_resolver,
                   sourcemeta::blaze::BundleMode::NonOfficialMetaschemas),
               sourcemeta::blaze::SchemaError);
}

TEST(Bundle_2020_12, elevate_embedded_from_single_prebundled) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/elevate-entry",
    "$ref": "elevate-single"
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

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

TEST(Bundle_2020_12, metaschema_offline_idempotent) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string",
    "$defs": {
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  // Note that we bundle with a resolver that does not know about
  // the custom meta-schemas embedded in the document
  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta/1.json",
    "type": "string",
    "$defs": {
      "https://example.com/meta/1.json": {
        "$schema": "https://example.com/meta/2.json",
        "$id": "https://example.com/meta/1.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      },
      "https://example.com/meta/2.json": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/meta/2.json",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}
