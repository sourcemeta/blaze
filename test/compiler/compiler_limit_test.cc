#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>

#include <sourcemeta/core/json.h>

#include <optional>    // std::nullopt
#include <string_view> // std::string_view

static auto remote_resolver(std::string_view identifier)
    -> sourcemeta::blaze::SchemaResolverResult {
  if (identifier == "https://www.sourcemeta.com/remote") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/remote",
      "type": "string"
    })JSON");
  }

  return sourcemeta::blaze::schema_resolver(identifier);
}

// NOLINTBEGIN(cert-err58-cpp,bugprone-throwing-static-initialization)
static const sourcemeta::core::JSON SCHEMA =
    sourcemeta::core::parse_json(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "object",
  "properties": {
    "foo": { "type": "string" },
    "bar": { "type": "number" }
  }
})JSON");

// Compiling a subschema recurses back into itself through the keyword
// handlers, so a schema deep enough would otherwise run the stack out rather
// than report anything a caller could catch
static const sourcemeta::core::JSON NESTED =
    sourcemeta::core::parse_json(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "not": { "not": { "not": { "type": "string" } } }
})JSON");

// Compiling from a schema rather than from a frame bundles it and frames it
// first, and neither of those is bounded by what compilation itself may spend
static const sourcemeta::core::JSON WITH_REMOTE =
    sourcemeta::core::parse_json(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$ref": "https://www.sourcemeta.com/remote"
})JSON");
// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

TEST(instructions_default_limit_is_unbounded) {
  const auto schema_template{
      sourcemeta::blaze::compile(SCHEMA, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  EXPECT_EQ(schema_template.extra.size(), 8);
}

TEST(instruction_limit_equal_to_the_count_succeeds) {
  sourcemeta::blaze::Tweaks tweaks;
  tweaks.max_instructions = 8;
  const auto schema_template{sourcemeta::blaze::compile(
      SCHEMA, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};
  EXPECT_EQ(schema_template.extra.size(), 8);
}

TEST(instruction_limit_one_below_the_count_throws) {
  sourcemeta::blaze::Tweaks tweaks;
  tweaks.max_instructions = 7;
  try {
    [[maybe_unused]] const auto schema_template{sourcemeta::blaze::compile(
        SCHEMA, sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInstructionLimitError &error) {
    EXPECT_STREQ(
        error.what(),
        "The schema exceeds the maximum number of compiled instructions");
    EXPECT_EQ(error.limit(), 7);
  }
}

TEST(instruction_limit_of_zero_throws) {
  sourcemeta::blaze::Tweaks tweaks;
  tweaks.max_instructions = 0;
  try {
    [[maybe_unused]] const auto schema_template{sourcemeta::blaze::compile(
        SCHEMA, sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerInstructionLimitError &error) {
    EXPECT_EQ(error.limit(), 0);
  }
}

TEST(depth_default_limit_is_unbounded) {
  [[maybe_unused]] const auto schema_template{
      sourcemeta::blaze::compile(NESTED, sourcemeta::blaze::schema_walker,
                                 sourcemeta::blaze::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
}

TEST(depth_limit_equal_to_the_nesting_succeeds) {
  sourcemeta::blaze::Tweaks tweaks;
  tweaks.max_depth = 4;
  [[maybe_unused]] const auto schema_template{sourcemeta::blaze::compile(
      NESTED, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};
}

TEST(depth_limit_one_below_the_nesting_throws) {
  sourcemeta::blaze::Tweaks tweaks;
  tweaks.max_depth = 3;
  try {
    [[maybe_unused]] const auto schema_template{sourcemeta::blaze::compile(
        NESTED, sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};
    FAIL();
  } catch (const sourcemeta::blaze::CompilerDepthLimitError &error) {
    EXPECT_STREQ(error.what(),
                 "The schema exceeds the maximum compilation depth");
    EXPECT_EQ(error.limit(), 3);
  }
}

TEST(locations_default_limit_is_unbounded) {
  [[maybe_unused]] const auto schema_template{sourcemeta::blaze::compile(
      WITH_REMOTE, sourcemeta::blaze::schema_walker, remote_resolver,
      sourcemeta::blaze::default_schema_compiler)};
}

TEST(location_limit_bounds_the_bundling_and_framing_preamble) {
  try {
    [[maybe_unused]] const auto schema_template{sourcemeta::blaze::compile(
        WITH_REMOTE, sourcemeta::blaze::schema_walker, remote_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::FastValidation, "", "", "", std::nullopt, 2)};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameLimitError &error) {
    EXPECT_STREQ(error.what(),
                 "The schema exceeds the maximum number of frame locations");
    EXPECT_EQ(error.limit(), 2);
  }
}
