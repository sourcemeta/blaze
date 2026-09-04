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

// A schema that is invalid on its own terms reports why it is invalid whether
// or not a limit is in play, so setting one never rewrites an existing error
TEST(limit_does_not_mask_an_identifier_collision) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "id": "https://www.sourcemeta.com/schema",
    "$schema": "http://json-schema.org/draft-00/schema#",
    "items": { "id": "schema" }
  })JSON");

  try {
    [[maybe_unused]] const sourcemeta::blaze::SchemaFrame frame{
        sourcemeta::blaze::SchemaFrame::Mode::References,
        document,
        sourcemeta::blaze::schema_walker,
        sourcemeta::blaze::schema_resolver,
        "",
        "",
        sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional,
        {sourcemeta::core::EMPTY_WEAK_POINTER},
        std::numeric_limits<std::uint64_t>::max()};
    FAIL();
  } catch (const sourcemeta::blaze::SchemaFrameError &error) {
    EXPECT_STREQ(error.what(), "Schema identifier already exists");
  }
}

// Every subschema is registered once per base that encloses it, so nesting
// identifiers costs more locations than the same shape without them. That is
// what makes framing grow faster than the schema does, and what the limit
// exists to catch
TEST(nested_identifiers_cost_more_than_the_same_shape_without_them) {
  const sourcemeta::core::JSON anonymous = sourcemeta::core::parse_json(R"JSON({
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

  const sourcemeta::core::JSON identified =
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

  const sourcemeta::blaze::SchemaFrame anonymous_frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, anonymous,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  EXPECT_EQ(anonymous_frame.location_count(), 4);

  const sourcemeta::blaze::SchemaFrame identified_frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, identified,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  EXPECT_EQ(identified_frame.location_count(), 9);
}
