#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/blaze/foundation.h>

#include <sourcemeta/core/json.h>

#include <string>      // std::string
#include <string_view> // std::string_view

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
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(multiple_refs) {
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

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "https://www.sourcemeta.com/test-3"
      },
      "bar": {
        "$ref": "https://www.sourcemeta.com/test-1"
      }
    },
    "$defs": {
      "https://www.sourcemeta.com/test-4": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "https://www.sourcemeta.com/test-4",
        "type": "string"
      },
      "https://www.sourcemeta.com/test-3": {
        "$schema": "http://json-schema.org/draft-06/schema#",
        "$id": "https://www.sourcemeta.com/test-3",
        "allOf": [ { "$ref": "test-4" } ]
      },
      "https://www.sourcemeta.com/test-1": {
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://www.sourcemeta.com/test-1",
        "type": "string"
      }
    }
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(across_dialects) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-2" }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-2" },
    "$defs": {
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
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(across_dialects_top_level_ref_draft) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-3-top-level-ref" }
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceObjectResourceError &error) {
    EXPECT_EQ(error.identifier(),
              "https://www.sourcemeta.com/test-3-top-level-ref");
  } catch (...) {
    FAIL();
  }
}

TEST(across_dialects_from_top_level_ref_draft_absolute) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "https://www.sourcemeta.com/test-2"
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaError &) {
  }
}

TEST(across_dialects_from_top_level_ref_draft_relative) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$ref": "test-2"
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaError &) {
  }
}

TEST(across_dialects_const) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-2" }
  })JSON");

  const auto result = sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.example.com",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "https://www.sourcemeta.com/test-2" },
    "$defs": {
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
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(with_default_id) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$ref": "test-2" }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas, "",
      "https://www.sourcemeta.com/default");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://www.sourcemeta.com/default",
    "items": { "$ref": "test-2" },
    "$defs": {
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
  })JSON");

  EXPECT_EQ(document, expected);
}

TEST(with_default_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" }
    }
  })JSON");

  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
      sourcemeta::blaze::BundleMode::NonOfficialMetaschemas,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::core::JSON expected = sourcemeta::core::parse_json(R"JSON({
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" }
    },
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

TEST(without_default_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/test-1" }
    }
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &) {
  }
}

TEST(target_no_dialect) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/no-dialect" }
    }
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceError &) {
  }
}

TEST(target_array) {
  sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": { "$ref": "https://www.sourcemeta.com/array" }
    }
  })JSON");

  try {
    sourcemeta::blaze::bundle(
        document, sourcemeta::blaze::schema_walker, test_resolver,
        sourcemeta::blaze::BundleMode::NonOfficialMetaschemas);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceError &) {
  }
}

TEST(custom_paths_no_external) {
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

  const sourcemeta::core::Pointer path1{"wrapper"};
  const sourcemeta::core::Pointer path2{"common", "test"};
  const sourcemeta::core::Pointer path3{"common", "with-id"};
  sourcemeta::blaze::bundle(
      document, sourcemeta::blaze::schema_walker, test_resolver,
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
      document, sourcemeta::blaze::schema_walker, test_resolver,
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
