#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

TEST(try_embedded_2020_12) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema, &document.at("$defs").at("https://example.com/meta"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2020-12/vocab/core": true
    },
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_definitions_2020_12) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  // In 2019-09 and 2020-12, `definitions` is still supported
  // for backwards compatibility
  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema,
            &document.at("definitions").at("https://example.com/meta"));
}

TEST(try_embedded_chain) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta-a",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema, &document.at("$defs").at("https://example.com/meta-a"));

  const auto *link{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta-b",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(link);
  EXPECT_EQ(link, &document.at("$defs").at("https://example.com/meta-b"));
}

TEST(try_embedded_not_found) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/other": {
        "$id": "https://example.com/other",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object"
      }
    }
  })JSON")};

  EXPECT_FALSE(sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver));
}

TEST(try_embedded_no_containers) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string"
  })JSON")};

  EXPECT_FALSE(sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver));
}

TEST(try_embedded_relative_identifier) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "meta": {
        "$id": "meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object"
      }
    }
  })JSON")};

  EXPECT_FALSE(sourcemeta::blaze::metaschema_try_embedded(
      document, "meta", sourcemeta::blaze::schema_resolver));
}

TEST(try_embedded_wrong_container) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON")};

  EXPECT_FALSE(sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver));
}

TEST(try_embedded_wrong_id_keyword) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  EXPECT_FALSE(sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver));
}

TEST(try_embedded_self_descriptive) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://example.com/meta",
        "type": "object"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::metaschema_try_embedded(
        document, "https://example.com/meta",
        sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(try_embedded_cyclic) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://example.com/meta-a",
        "type": "object"
      }
    }
  })JSON")};

  try {
    sourcemeta::blaze::metaschema_try_embedded(
        document, "https://example.com/meta-a",
        sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(try_embedded_chain_intermediate_precedence) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  const auto resolver =
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/meta-b") {
      return sourcemeta::core::parse_json(R"JSON({
        "$id": "https://example.com/meta-b",
        "$schema": "https://example.com/unknown"
      })JSON");
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta-a", resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema, &document.at("$defs").at("https://example.com/meta-a"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta-a",
    "$schema": "https://example.com/meta-b",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_chain_intermediate_precedence_cyclic) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  const auto resolver =
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/meta-b") {
      return sourcemeta::core::parse_json(R"JSON({
        "$id": "https://example.com/meta-b",
        "$schema": "https://example.com/meta-a"
      })JSON");
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta-a", resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema, &document.at("$defs").at("https://example.com/meta-a"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta-a",
    "$schema": "https://example.com/meta-b",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_chain_intermediate_precedence_base_dialect) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta-a",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta-a": {
        "$id": "https://example.com/meta-a",
        "$schema": "https://example.com/meta-b",
        "type": "object"
      },
      "https://example.com/meta-b": {
        "$id": "https://example.com/meta-b",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  const auto resolver =
      [](std::string_view identifier) -> std::optional<sourcemeta::core::JSON> {
    if (identifier == "https://example.com/meta-b") {
      return sourcemeta::core::parse_json(R"JSON({
        "$id": "https://example.com/meta-b",
        "$schema": "http://json-schema.org/draft-07/schema#"
      })JSON");
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta-a", resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema, &document.at("$defs").at("https://example.com/meta-a"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta-a",
    "$schema": "https://example.com/meta-b",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_2019_09) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2019-09/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema, &document.at("$defs").at("https://example.com/meta"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true
    },
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_draft7) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema,
            &document.at("definitions").at("https://example.com/meta"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_draft6) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema,
            &document.at("definitions").at("https://example.com/meta"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/meta",
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_draft4) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema,
            &document.at("definitions").at("https://example.com/meta"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/meta",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}

TEST(try_embedded_draft3) {
  const auto document{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON")};

  const auto *metaschema{sourcemeta::blaze::metaschema_try_embedded(
      document, "https://example.com/meta",
      sourcemeta::blaze::schema_resolver)};

  EXPECT_TRUE(metaschema);
  EXPECT_EQ(metaschema,
            &document.at("definitions").at("https://example.com/meta"));

  const auto expected{sourcemeta::core::parse_json(R"JSON({
    "id": "https://example.com/meta",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object"
  })JSON")};

  EXPECT_EQ(*metaschema, expected);
}
