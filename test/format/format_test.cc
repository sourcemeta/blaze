#include <gtest/gtest.h>

#include <sourcemeta/blaze/format.h>
#include <sourcemeta/blaze/foundation.h>

#include <sstream>

TEST(Format, example_1) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "title": "My example schema",
    "type": "object",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "My example schema",
  "type": "object"
})JSON");
}

TEST(Format, example_2) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "default": 1,
    "$ref": "other",
    "x-foo": [ "bar", "baz" ],
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "default": 1,
  "x-foo": [ "bar", "baz" ],
  "$ref": "other"
})JSON");
}

TEST(Format, nested_objects) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "object",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "name": {
        "type": "string",
        "description": "The name",
        "title": "Name"
      }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "properties": {
    "name": {
      "title": "Name",
      "description": "The name",
      "type": "string"
    }
  }
})JSON");
}

TEST(Format, no_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "description": "test"
  })JSON");

  EXPECT_THROW(sourcemeta::blaze::format(document,
                                         sourcemeta::blaze::schema_walker,
                                         sourcemeta::blaze::schema_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(Format, no_dialect_with_default) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "string",
    "description": "test"
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver,
                            "https://json-schema.org/draft/2020-12/schema");
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "description": "test",
  "type": "string"
})JSON");
}

TEST(Format, properties_container_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "minimum": { "description": "min", "type": "string" },
      "maximum": { "description": "max", "type": "number" },
      "pattern": { "description": "pat", "type": "boolean" }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "properties": {
    "minimum": {
      "description": "min",
      "type": "string"
    },
    "maximum": {
      "description": "max",
      "type": "number"
    },
    "pattern": {
      "description": "pat",
      "type": "boolean"
    }
  }
})JSON");
}

TEST(Format, enum_objects_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [
      { "type": 1, "title": 2, "$schema": 3 }
    ]
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "string",
  "enum": [
    {
      "type": 1,
      "title": 2,
      "$schema": 3
    }
  ]
})JSON");
}

TEST(Format, const_object_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "const": { "properties": 1, "description": 2, "$id": 3 }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "const": {
    "properties": 1,
    "description": 2,
    "$id": 3
  }
})JSON");
}

TEST(Format, default_object_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "default": { "enum": 1, "const": 2, "type": 3 }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "default": {
    "enum": 1,
    "const": 2,
    "type": 3
  },
  "type": "object"
})JSON");
}

TEST(Format, examples_objects_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "examples": [
      { "pattern": 1, "minimum": 2, "maximum": 3 }
    ]
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "examples": [
    {
      "pattern": 1,
      "minimum": 2,
      "maximum": 3
    }
  ],
  "type": "object"
})JSON");
}

TEST(Format, typo_keyword_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperty": {
      "type": "string",
      "description": "This is a typo"
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "additionalProperty": {
    "type": "string",
    "description": "This is a typo"
  }
})JSON");
}

TEST(Format, correct_keyword_is_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": {
      "type": "string",
      "description": "This is correct"
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "additionalProperties": {
    "description": "This is correct",
    "type": "string"
  }
})JSON");
}

TEST(Format, nested_properties_subschemas_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "zebra": {
        "type": "object",
        "description": "A zebra",
        "properties": {
          "stripes": {
            "type": "number",
            "description": "Number of stripes"
          }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "properties": {
    "zebra": {
      "description": "A zebra",
      "type": "object",
      "properties": {
        "stripes": {
          "description": "Number of stripes",
          "type": "number"
        }
      }
    }
  }
})JSON");
}

TEST(Format, pattern_properties_container_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {
      "items": { "description": "i", "type": "string" },
      "enum": { "description": "e", "type": "number" },
      "const": { "description": "c", "type": "boolean" }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "patternProperties": {
    "items": {
      "description": "i",
      "type": "string"
    },
    "enum": {
      "description": "e",
      "type": "number"
    },
    "const": {
      "description": "c",
      "type": "boolean"
    }
  }
})JSON");
}

TEST(Format, definitions_container_not_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "allOf": { "type": "string", "description": "A" },
      "anyOf": { "type": "number", "description": "A" },
      "$id": { "type": "boolean", "description": "I" }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$defs": {
    "allOf": {
      "description": "A",
      "type": "string"
    },
    "anyOf": {
      "description": "A",
      "type": "number"
    },
    "$id": {
      "description": "I",
      "type": "boolean"
    }
  }
})JSON");
}

TEST(Format, embedded_resource_reordered) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/root",
    "$defs": {
      "myResource": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://example.com/embedded",
        "properties": { "foo": { "type": "string" } },
        "type": "object",
        "description": "An embedded schema resource",
        "title": "Embedded Resource"
      }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://example.com/root",
  "$defs": {
    "myResource": {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://example.com/embedded",
      "title": "Embedded Resource",
      "description": "An embedded schema resource",
      "type": "object",
      "properties": {
        "foo": {
          "type": "string"
        }
      }
    }
  }
})JSON");
}

TEST(Format, boolean_subschema_does_not_crash) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": true,
    "properties": {
      "foo": { "type": "string", "description": "Foo property" }
    }
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "properties": {
    "foo": {
      "description": "Foo property",
      "type": "string"
    }
  },
  "additionalProperties": true
})JSON");
}

TEST(Format, reorder_does_not_invalidate_child_pointers) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "not": {},
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::format(document, sourcemeta::blaze::schema_walker,
                            sourcemeta::blaze::schema_resolver);

  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  EXPECT_EQ(stream.str(), R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "not": {}
})JSON");
}
