#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "evaluator_utils.h"

TEST(format_utc_millisec_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "utc-millisec"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(
        error.what(),
        "The \"utc-millisec\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(format_utc_millisec_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "utc-millisec"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(
        error.what(),
        "The \"utc-millisec\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(format_style_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "style"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"style\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(format_style_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "style"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"style\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(format_phone_with_tweak_throws_fast) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "phone"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "", tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"phone\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(format_phone_with_tweak_throws_exhaustive) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "format": "phone"
  })JSON")};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.format_assertion = true;

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::Exhaustive, "", "", "",
                               tweaks);
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(),
                 "The \"phone\" format is not supported in assertion mode yet");
    EXPECT_EQ(error.location(), sourcemeta::core::Pointer({"format"}));
    EXPECT_EQ(error.base().recompose(), "");
  } catch (...) {
    FAIL();
  }
}

TEST(boolean_subschema_entrypoint) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "properties": {
      "everything": true
    }
  })JSON")};

  try {
    sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                               sourcemeta::core::schema_resolver,
                               sourcemeta::blaze::default_schema_compiler,
                               sourcemeta::blaze::Mode::FastValidation, "", "",
                               "#/properties/everything");
    FAIL();
  } catch (const sourcemeta::blaze::CompilerError &error) {
    EXPECT_STREQ(error.what(), "This dialect does not support boolean schemas");
  } catch (...) {
    FAIL();
  }
}
