#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/bundle.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>

#include <optional>    // std::nullopt
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

static auto chain_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://www.sourcemeta.com/chain-1") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/chain-1",
      "$ref": "chain-2"
    })JSON");
  }

  if (identifier == "https://www.sourcemeta.com/chain-2") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/chain-2",
      "$ref": "chain-3"
    })JSON");
  }

  if (identifier == "https://www.sourcemeta.com/chain-3") {
    return sourcemeta::core::parse_json(R"JSON({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/chain-3",
      "type": "string"
    })JSON");
  }

  return sourcemeta::core::schema_resolver(identifier);
}

// NOLINTBEGIN(cert-err58-cpp,bugprone-throwing-static-initialization)
// Pulls in a single remote, and so costs a single remote's worth of framing
static const sourcemeta::core::JSON SINGLE =
    sourcemeta::core::parse_json(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$ref": "https://www.sourcemeta.com/chain-3"
})JSON");

// Pulls in three, one reference deep at a time
static const sourcemeta::core::JSON CHAIN =
    sourcemeta::core::parse_json(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$ref": "https://www.sourcemeta.com/chain-1"
})JSON");

static const sourcemeta::core::JSON BUNDLED_CHAIN =
    sourcemeta::core::parse_json(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$ref": "https://www.sourcemeta.com/chain-1",
  "$defs": {
    "https://www.sourcemeta.com/chain-1": {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/chain-1",
      "$ref": "chain-2"
    },
    "https://www.sourcemeta.com/chain-2": {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/chain-2",
      "$ref": "chain-3"
    },
    "https://www.sourcemeta.com/chain-3": {
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "$id": "https://www.sourcemeta.com/chain-3",
      "type": "string"
    }
  }
})JSON");

static const std::vector<std::string> CHAIN_DEPENDENCIES{
    "https://www.sourcemeta.com/chain-1", "https://www.sourcemeta.com/chain-2",
    "https://www.sourcemeta.com/chain-3"};
// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

TEST(bundle_default_limit_is_unbounded) {
  const auto result{sourcemeta::blaze::bundle(
      CHAIN, sourcemeta::core::schema_walker, chain_resolver,
      sourcemeta::blaze::BundleMode::References)};
  EXPECT_EQ(result, BUNDLED_CHAIN);
}

TEST(bundle_at_exactly_the_required_limit_succeeds) {
  const auto result{sourcemeta::blaze::bundle(
      CHAIN, sourcemeta::core::schema_walker, chain_resolver,
      sourcemeta::blaze::BundleMode::References, "", "", std::nullopt,
      {sourcemeta::core::EMPTY_WEAK_POINTER}, 9)};
  EXPECT_EQ(result, BUNDLED_CHAIN);
}

TEST(bundle_one_below_the_required_limit_throws) {
  try {
    [[maybe_unused]] const auto result{sourcemeta::blaze::bundle(
        CHAIN, sourcemeta::core::schema_walker, chain_resolver,
        sourcemeta::blaze::BundleMode::References, "", "", std::nullopt,
        {sourcemeta::core::EMPTY_WEAK_POINTER}, 8)};
    FAIL();
  } catch (const sourcemeta::core::SchemaFrameLimitError &error) {
    EXPECT_STREQ(error.what(),
                 "The schema exceeds the maximum number of frame locations");
    EXPECT_EQ(error.limit(), 8);
  }
}

// Every frame that bundling constructs spends from the one limit, so a chain
// of remotes cannot slip through a limit that each of its frames fits under.
// This is the case that handing each frame a limit of its own would miss
TEST(bundle_limit_accumulates_across_remotes) {
  [[maybe_unused]] const auto single{sourcemeta::blaze::bundle(
      SINGLE, sourcemeta::core::schema_walker, chain_resolver,
      sourcemeta::blaze::BundleMode::References, "", "", std::nullopt,
      {sourcemeta::core::EMPTY_WEAK_POINTER}, 5)};

  try {
    [[maybe_unused]] const auto chained{sourcemeta::blaze::bundle(
        CHAIN, sourcemeta::core::schema_walker, chain_resolver,
        sourcemeta::blaze::BundleMode::References, "", "", std::nullopt,
        {sourcemeta::core::EMPTY_WEAK_POINTER}, 5)};
    FAIL();
  } catch (const sourcemeta::core::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 5);
  }
}

// The frame that runs out was handed whatever was left rather than the whole,
// so bundling reports the limit that the caller set instead of that remainder
TEST(bundle_reports_the_limit_the_caller_set) {
  try {
    [[maybe_unused]] const auto result{sourcemeta::blaze::bundle(
        CHAIN, sourcemeta::core::schema_walker, chain_resolver,
        sourcemeta::blaze::BundleMode::References, "", "", std::nullopt,
        {sourcemeta::core::EMPTY_WEAK_POINTER}, 2)};
    FAIL();
  } catch (const sourcemeta::core::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 2);
  }
}

TEST(bundle_in_place_respects_the_limit) {
  auto schema{CHAIN};
  try {
    sourcemeta::blaze::bundle(
        schema, sourcemeta::core::schema_walker, chain_resolver,
        sourcemeta::blaze::BundleMode::References, "", "", std::nullopt,
        {sourcemeta::core::EMPTY_WEAK_POINTER}, 8);
    FAIL();
  } catch (const sourcemeta::core::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 8);
  }
}

TEST(dependencies_default_limit_is_unbounded) {
  std::vector<std::string> identifiers;
  sourcemeta::blaze::dependencies(
      CHAIN, sourcemeta::core::schema_walker, chain_resolver,
      [&identifiers](const auto &, const auto &, const auto &target,
                     const auto &) { identifiers.emplace_back(target); });
  EXPECT_EQ(identifiers, CHAIN_DEPENDENCIES);
}

TEST(dependencies_at_exactly_the_required_limit_succeeds) {
  std::vector<std::string> identifiers;
  sourcemeta::blaze::dependencies(
      CHAIN, sourcemeta::core::schema_walker, chain_resolver,
      [&identifiers](const auto &, const auto &, const auto &target,
                     const auto &) { identifiers.emplace_back(target); },
      "", "", {sourcemeta::core::EMPTY_WEAK_POINTER}, 7);
  EXPECT_EQ(identifiers, CHAIN_DEPENDENCIES);
}

TEST(dependencies_one_below_the_required_limit_throws) {
  try {
    sourcemeta::blaze::dependencies(
        CHAIN, sourcemeta::core::schema_walker, chain_resolver,
        [](const auto &, const auto &, const auto &, const auto &) {}, "", "",
        {sourcemeta::core::EMPTY_WEAK_POINTER}, 6);
    FAIL();
  } catch (const sourcemeta::core::SchemaFrameLimitError &error) {
    EXPECT_EQ(error.limit(), 6);
  }
}
