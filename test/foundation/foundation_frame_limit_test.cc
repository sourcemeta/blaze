#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <cstdint>
#include <limits>

static const sourcemeta::core::JSON DOCUMENT =
    sourcemeta::core::parse_json(R"JSON({
  "$id": "https://www.sourcemeta.com/schema",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "properties": {
    "foo": { "type": "string" },
    "bar": { "type": "number" }
  }
})JSON");

TEST(references_location_count) {
  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, DOCUMENT,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  EXPECT_EQ(frame.location_count(), 3);
}

TEST(limit_equal_to_location_count_succeeds) {
  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References,
      DOCUMENT,
      sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      "",
      "",
      sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::EMPTY_WEAK_POINTER},
      3};
  EXPECT_EQ(frame.location_count(), 3);
}

TEST(limit_one_below_location_count_throws) {
  try {
    [[maybe_unused]] const sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References,
        DOCUMENT,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        "",
        "",
        sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
        {sourcemeta::core::EMPTY_WEAK_POINTER},
        2};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameLimitError &error) {
    EXPECT_STREQ(error.what(),
                 "The schema exceeds the maximum number of frame locations");
    EXPECT_EQ(error.limit(), 2);
  }
}

TEST(limit_of_zero_throws) {
  try {
    [[maybe_unused]] const sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References,
        DOCUMENT,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        "",
        "",
        sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
        {sourcemeta::core::EMPTY_WEAK_POINTER},
        0};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 0);
  }
}

TEST(default_limit_is_unbounded) {
  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Pointers, DOCUMENT,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  EXPECT_EQ(frame.location_count(), 8);
}

// A location per JSON Pointer rather than per schema costs more of the same
// limit, which is what tells the caller these modes are not interchangeable
TEST(pointers_mode_consumes_more_than_references_mode) {
  const sourcemeta::blaze::SchemaFrame references{
      sourcemeta::blaze::SchemaFrame::Mode::References,
      DOCUMENT,
      sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      "",
      "",
      sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
      {sourcemeta::core::EMPTY_WEAK_POINTER},
      3};
  EXPECT_EQ(references.location_count(), 3);

  try {
    [[maybe_unused]] const sourcemeta::blaze::SchemaFrame pointers{
        sourcemeta::blaze::SchemaFrame::Mode::Pointers,
        DOCUMENT,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        "",
        "",
        sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
        {sourcemeta::core::EMPTY_WEAK_POINTER},
        3};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 3);
  }
}

static const sourcemeta::core::JSON COLLIDING_DOCUMENT =
    sourcemeta::core::parse_json(R"JSON({
  "id": "https://www.sourcemeta.com/schema",
  "$schema": "http://json-schema.org/draft-00/schema#",
  "items": { "id": "schema" }
})JSON");

// The insertion that collides is checked for collision before it is charged,
// so a schema that is invalid on its own terms is still reported as invalid
// rather than as too expensive
TEST(collision_wins_when_the_same_insertion_also_exceeds_the_limit) {
  try {
    [[maybe_unused]] const sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References,
        COLLIDING_DOCUMENT,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        "",
        "",
        sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
        {sourcemeta::core::EMPTY_WEAK_POINTER},
        1};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

// Whereas a limit that runs out before framing ever reaches the collision
// reports the limit, as framing never got far enough to find the collision
TEST(limit_wins_when_it_runs_out_before_the_collision) {
  try {
    [[maybe_unused]] const sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References,
        COLLIDING_DOCUMENT,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        "",
        "",
        sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
        {sourcemeta::core::EMPTY_WEAK_POINTER},
        0};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 0);
  }
}

// Every subschema is registered once per base that encloses it, so nesting
// identifiers costs more locations than the same shape without them. That is
// what makes framing grow faster than the schema does, and what the limit
// exists to catch
TEST(nested_identifiers_cost_more_than_the_same_shape_without_them) {
  const sourcemeta::core::JSON without_identifiers =
      sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "properties": {
          "bar": { "properties": { "baz": { "type": "string" } } }
        }
      }
    }
  })JSON");

  const sourcemeta::core::JSON with_identifiers =
      sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$id": "nested",
        "properties": {
          "bar": { "$id": "deep", "properties": { "baz": { "type": "string" } } }
        }
      }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame without_identifiers_frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, without_identifiers,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  EXPECT_EQ(without_identifiers_frame.location_count(), 4);

  const sourcemeta::blaze::SchemaFrame with_identifiers_frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, with_identifiers,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  EXPECT_EQ(with_identifiers_frame.location_count(), 9);
}
