#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <optional>
#include <string_view>

TEST(draft0_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-00/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft1_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-01/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft2_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-02/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft3_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-03/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft3_id_fragment_invalid_whitespace) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "#foo bar",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "#foo bar");
  } catch (...) {
    FAIL();
  }
}

TEST(draft3_non_string_id_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "object",
    "properties": {
      "a": { "id": 42, "type": "string" }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "42");
  } catch (...) {
    FAIL();
  }
}

TEST(draft3_embedded_custom_metaschema_wrong_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(draft3_embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-03/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(draft3_top_level_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema#foo",
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft3_nested_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "foo": {
        "id": "https://www.sourcemeta.com/nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft3_nested_id_relative_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "foo": {
        "id": "nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": { "id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft4_ref_with_invalid_type) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "$ref": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$ref");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_invalid_id_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema",
    "id": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_id_fragment_invalid_whitespace) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "id": "#foo bar"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "#foo bar");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_id_fragment_invalid_angle_bracket) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "id": "#foo<bar"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "id");
    EXPECT_EQ(error.value(), "#foo<bar");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_top_level_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema#foo",
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_nested_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "id": "https://www.sourcemeta.com/nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft4_nested_id_relative_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": {
        "id": "nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-06/schema#",
    "items": { "$id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft6_id_fragment_invalid_leading_digit) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": {
        "$id": "#1foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#1foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_id_fragment_invalid_punctuation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": {
        "$id": "#foo!"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#foo!");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_id_fragment_invalid_leading_underscore) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": {
        "$id": "#_foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#_foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_embedded_custom_metaschema_wrong_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "definitions": {
      "https://example.com/meta": {
        "id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-06/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_top_level_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema#foo",
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_nested_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": {
        "$id": "https://www.sourcemeta.com/nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft6_nested_id_relative_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": {
        "$id": "nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-07/schema#",
    "items": { "$id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(draft7_id_fragment_invalid_leading_digit) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": {
        "$id": "#1foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#1foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_id_fragment_invalid_punctuation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": {
        "$id": "#foo!"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#foo!");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_id_fragment_invalid_at_sign) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": {
        "$id": "#foo@bar"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#foo@bar");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_id_fragment_invalid_leading_underscore) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": {
        "$id": "#_foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "#_foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_embedded_custom_metaschema_wrong_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_top_level_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema#foo",
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_nested_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": {
        "$id": "https://www.sourcemeta.com/nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(draft7_nested_id_relative_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": {
        "$id": "nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers may only carry a fragment when they consist of "
                 "nothing else");
    EXPECT_EQ(error.identifier(), "nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "items": { "$id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(2019_09_static_anchor_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "foo",
    "items": { "$anchor": "foo" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/items");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_location_independent_identifier_anonymous) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "$id": "#foo"
      },
      "bar": {
        "$ref": "#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_EQ(error.identifier(), "#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_recursive_anchor_conflict) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": true,
    "items": {
      "$recursiveAnchor": true
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/items");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_invalid_recursive_ref) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveRef": "nested#"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaReferenceError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/$recursiveRef");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_invalid_recursive_anchor_not_boolean) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveAnchor": "foo"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$recursiveAnchor");
    EXPECT_EQ(error.value(), "\"foo\"");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_invalid_recursive_ref_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$recursiveRef": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$recursiveRef");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_anchor_with_invalid_format_empty) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": ""
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_anchor_with_invalid_format_leading_digit) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "1foo"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "1foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_anchor_with_invalid_format_leading_underscore) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "_foo"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "_foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_anchor_with_invalid_format_whitespace) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "foo bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "foo bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_anchor_with_invalid_format_punctuation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "foo!bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "foo!bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_top_level_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema#foo",
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers must not contain non-empty fragments");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2019_09_nested_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "$id": "https://www.sourcemeta.com/nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers must not contain non-empty fragments");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_id_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "items": { "$id": "schema" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(2020_12_static_anchor_override) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo",
    "items": { "$anchor": "foo" }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/items");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_anchor_same_on_schema_resource) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "foo",
    "items": {
      "$dynamicAnchor": "foo"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/items");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_static_anchor_then_dynamic_anchor_same_on_schema_resource) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "$anchor": "test"
      },
      "bar": {
        "$dynamicAnchor": "test"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/$defs/bar");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "/$defs/foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_anchor_then_static_anchor_same_on_schema_resource) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "bar": {
        "$dynamicAnchor": "test"
      },
      "foo": {
        "$anchor": "test"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/$defs/foo");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "/$defs/bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_root_static_anchor_then_nested_dynamic_anchor) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "test",
    "items": {
      "$dynamicAnchor": "test"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/items");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_root_dynamic_anchor_then_nested_static_anchor) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "test",
    "items": {
      "$anchor": "test"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/items");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_static_anchor_then_dynamic_anchor_same_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "$anchor": "test"
      },
      "bar": {
        "$dynamicAnchor": "test"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/$defs/bar");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "/$defs/foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_anchor_then_static_anchor_same_without_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "bar": {
        "$dynamicAnchor": "test"
      },
      "foo": {
        "$anchor": "test"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/$defs/foo");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "/$defs/bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_location_independent_identifier_anonymous) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "$id": "#foo"
      },
      "bar": {
        "$ref": "#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_EQ(error.identifier(), "#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_multiple_nested_no_base_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
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
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  const sourcemeta::core::Pointer path1{"wrapper"};
  const sourcemeta::core::Pointer path2{"common", "test"};
  const sourcemeta::core::Pointer path3{"common", "with-id"};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver, "", "",
                  sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
                  {sourcemeta::core::to_weak_pointer(path1),
                   sourcemeta::core::to_weak_pointer(path2),
                   sourcemeta::core::to_weak_pointer(path3)});
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(2020_12_multiple_nested_same_id) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "common": {
      "foo": {
        "$id": "https://www.sourcemeta.com/schema",
        "$schema": "https://json-schema.org/draft/2020-12/schema"
      },
      "bar": {
        "$id": "https://www.sourcemeta.com/schema",
        "$schema": "https://json-schema.org/draft/2020-12/schema"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  const sourcemeta::core::Pointer path1{"common", "foo"};
  const sourcemeta::core::Pointer path2{"common", "bar"};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver, "", "",
                  sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
                  {sourcemeta::core::to_weak_pointer(path1),
                   sourcemeta::core::to_weak_pointer(path2)});
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

TEST(2020_12_multiple_nested_same_anonymous_anchors) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "common": {
      "foo": {
        "$anchor": "test"
      },
      "bar": {
        "$anchor": "test"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  const sourcemeta::core::Pointer path1{"common", "foo"};
  const sourcemeta::core::Pointer path2{"common", "bar"};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver,
                  "https://json-schema.org/draft/2020-12/schema", "",
                  sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
                  {sourcemeta::core::to_weak_pointer(path1),
                   sourcemeta::core::to_weak_pointer(path2)});
    FAIL();
  } catch (sourcemeta::blaze::SchemaAnchorCollisionError &error) {
    EXPECT_EQ(error.identifier(), "#test");
    EXPECT_EQ(sourcemeta::core::to_string(error.location()), "/common/bar");
    EXPECT_EQ(sourcemeta::core::to_string(error.other()), "/common/foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_ref_with_invalid_type) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$dynamicRef");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_nested_invalid_schema_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "nested": {
        "$schema": 123
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_invalid_id_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_invalid_id_not_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "not a valid uri"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$id");
    EXPECT_EQ(error.value(), "not a valid uri");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_nested_invalid_schema_not_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "nested": {
        "$schema": "not a valid uri"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.value(), "not a valid uri");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_invalid_ref_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$ref");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_invalid_ref_not_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$ref": "not a valid uri"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$ref");
    EXPECT_EQ(error.value(), "not a valid uri");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_invalid_dynamic_ref_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$dynamicRef");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_invalid_dynamic_ref_not_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicRef": "not a valid uri"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$dynamicRef");
    EXPECT_EQ(error.value(), "not a valid uri");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_anchor_with_invalid_format_empty) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": ""
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_anchor_with_invalid_format_leading_digit) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "1foo"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "1foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_anchor_with_invalid_format_leading_hyphen) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "-foo"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "-foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_anchor_with_invalid_format_whitespace) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "foo bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_anchor_with_invalid_format_punctuation) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo!bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "foo!bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_anchor_with_invalid_format_colon) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$anchor": "foo:bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$anchor");
    EXPECT_EQ(error.value(), "foo:bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_anchor_with_invalid_format_empty) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": ""
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$dynamicAnchor");
    EXPECT_EQ(error.value(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_anchor_with_invalid_format_leading_digit) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "1foo"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$dynamicAnchor");
    EXPECT_EQ(error.value(), "1foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_dynamic_anchor_with_invalid_format_colon) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$dynamicAnchor": "foo:bar"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$dynamicAnchor");
    EXPECT_EQ(error.value(), "foo:bar");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_top_level_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema#foo",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers must not contain non-empty fragments");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/schema#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_nested_id_absolute_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": {
        "$id": "https://www.sourcemeta.com/nested#foo"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers must not contain non-empty fragments");
    EXPECT_EQ(error.identifier(), "https://www.sourcemeta.com/nested#foo");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_self_descriptive) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://example.com/meta",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(2020_12_embedded_custom_metaschema_missing) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/other": {
        "$id": "https://example.com/other",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_wrong_id_keyword) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
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
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_cyclic) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
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
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(2020_12_embedded_custom_metaschema_relative_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "meta": {
        "$id": "meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true
        },
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (
      const sourcemeta::blaze::SchemaRelativeMetaschemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_outside_container) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "additionalProperties": {
      "$id": "https://example.com/meta",
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "object"
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_nested_in_subschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "wrapper": {
        "additionalProperties": {
          "$id": "https://example.com/meta",
          "$schema": "https://json-schema.org/draft/2020-12/schema",
          "type": "object"
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_conflicting_resources) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "properties": {
      "foo": {
        "$id": "https://example.com/foo",
        "$schema": "https://example.com/meta",
        "$defs": {
          "https://example.com/meta": {
            "$id": "https://example.com/meta",
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "type": "object"
          }
        }
      },
      "bar": {
        "$id": "https://example.com/bar",
        "$schema": "https://example.com/meta",
        "$defs": {
          "https://example.com/meta": {
            "$id": "https://example.com/meta",
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "type": "string"
          }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_nested_inside_instance_data) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "properties": {
      "foo": {
        "$id": "https://example.com/foo",
        "$schema": "https://example.com/meta",
        "const": {
          "$defs": {
            "https://example.com/meta": {
              "$id": "https://example.com/meta",
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "type": "object"
            }
          }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_nested_in_sibling) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/schema",
    "properties": {
      "foo": {
        "$id": "https://example.com/foo",
        "$schema": "https://example.com/meta"
      },
      "bar": {
        "$id": "https://example.com/bar",
        "$schema": "https://example.com/meta",
        "$defs": {
          "https://example.com/meta": {
            "$id": "https://example.com/meta",
            "$schema": "https://json-schema.org/draft/2020-12/schema",
            "type": "object"
          }
        }
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_boolean) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": true
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/meta");
  } catch (...) {
    FAIL();
  }
}

TEST(2020_12_embedded_custom_metaschema_missing_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(2020_12_embedded_custom_metaschema_non_string_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": 1,
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(no_dialect) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "type": "string"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(self_referencing_metaschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/self",
    "$id": "https://example.com/self"
  })JSON");

  const auto resolver = [&document](std::string_view identifier)
      -> sourcemeta::blaze::SchemaResolverResult {
    if (identifier == "https://example.com/self") {
      return document;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker, resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(indirect_metaschema_cycle) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/b",
    "$id": "https://example.com/a"
  })JSON");

  const sourcemeta::core::JSON other = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/a",
    "$id": "https://example.com/b"
  })JSON");

  const auto resolver = [&document, &other](std::string_view identifier)
      -> sourcemeta::blaze::SchemaResolverResult {
    if (identifier == "https://example.com/a") {
      return document;
    } else if (identifier == "https://example.com/b") {
      return other;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker, resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(invalid_schema_not_string) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": 123
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.value(), "123");
  } catch (...) {
    FAIL();
  }
}

TEST(invalid_schema_not_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "not a valid uri"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaKeywordError &error) {
    EXPECT_EQ(error.keyword(), "$schema");
    EXPECT_EQ(error.value(), "not a valid uri");
  } catch (...) {
    FAIL();
  }
}

TEST(override_unresolvable_throws) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "x-sourcemeta-dialect-override-subschema":
      "https://example.com/does-not-exist"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(override_surfaces_after_2019_09_upgrade) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "bar": { "type": "string" }
    },
    "properties": {
      "foo": {
        "$ref": "#/$defs/bar",
        "x-sourcemeta-dialect-override-subschema":
          "https://example.com/does-not-exist"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Locations};
  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not resolve the metaschema of the schema");
  }
}

TEST(root_mode_identifier_with_non_empty_fragment) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com#foo",
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};

  try {
    frame.analyse(document, sourcemeta::blaze::schema_walker,
                  sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(),
                 "Identifiers must not contain non-empty fragments");
    EXPECT_EQ(error.identifier(), "https://example.com#foo");
  }
}
