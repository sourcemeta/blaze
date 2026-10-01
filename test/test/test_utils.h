#ifndef SOURCEMETA_BLAZE_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_TEST_UTILS_H_

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/uri.h>

#include <cstddef>     // std::size_t
#include <filesystem>  // std::filesystem::path
#include <optional>    // std::optional, std::nullopt
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move

// What a target names is resolved, bundled and framed by whoever runs the
// suite, which is what lets a target reach into a document that is not a
// schema of its own. These helpers do that the plain way, for a target that
// names a schema

inline auto test_target_base(const sourcemeta::core::JSON::String &target)
    -> sourcemeta::core::JSON::String {
  const sourcemeta::core::URI uri{target};
  return uri.recompose_without_fragment().value_or(target);
}

inline auto
test_resolve_target(const sourcemeta::core::SchemaResolver &resolver,
                    const sourcemeta::core::JSON::String &base)
    -> sourcemeta::core::JSON {
  auto result{resolver(base)};
  if (!result.has_value()) {
    throw sourcemeta::core::SchemaResolutionError{
        base, "Could not resolve schema under test"};
  }

  return std::move(result.value());
}

inline auto
test_compile_target(const sourcemeta::core::JSON &bundled,
                    const sourcemeta::core::SchemaResolver &resolver,
                    const sourcemeta::core::JSON::String &target,
                    const sourcemeta::core::JSON::String &base,
                    const std::string_view default_dialect,
                    const sourcemeta::blaze::Mode mode,
                    const std::optional<sourcemeta::blaze::Tweaks> &tweaks)
    -> sourcemeta::blaze::Template {
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      bundled,
      sourcemeta::core::schema_walker,
      resolver,
      default_dialect,
      base};
  return sourcemeta::blaze::compile(
      bundled, sourcemeta::core::schema_walker, resolver,
      sourcemeta::blaze::default_schema_compiler, frame, target, mode, tweaks);
}

// Parse a test document and bind every target it names, which is the shape
// that every caller of this module takes
inline auto
parse_and_bind(const sourcemeta::core::JSON &document,
               const sourcemeta::core::PointerPositionTracker &tracker,
               const std::filesystem::path &base_path,
               const sourcemeta::core::SchemaResolver &resolver,
               const std::string_view default_dialect = "")
    -> sourcemeta::blaze::TestSuite {
  auto suite{sourcemeta::blaze::TestSuite::parse(document, tracker, base_path)};

  std::optional<sourcemeta::blaze::Tweaks> tweaks_fast;
  if (suite.requires_jsonld_annotations()) {
    tweaks_fast.emplace();
    tweaks_fast.value().annotations.emplace();
    tweaks_fast.value().annotations.value().insert(
        sourcemeta::blaze::JSONLD_KEYWORDS.cbegin(),
        sourcemeta::blaze::JSONLD_KEYWORDS.cend());
  }

  for (std::size_t target_index = 0; target_index < suite.targets.size();
       ++target_index) {
    const auto &target{suite.targets[target_index]};
    const auto base{test_target_base(target)};
    auto bundled{sourcemeta::core::schema_bundle(
        test_resolve_target(resolver, base), sourcemeta::core::schema_walker,
        resolver, default_dialect, base)};
    auto schema_fast{test_compile_target(
        bundled, resolver, target, base, default_dialect,
        sourcemeta::blaze::Mode::FastValidation, tweaks_fast)};

    // The provider owns what it compiles from, so framing happens again on
    // the first request rather than the suite borrowing anything
    suite.bind(target_index, std::move(schema_fast),
               [schema = std::move(bundled), resolver, target, base,
                dialect = std::string{
                    default_dialect}]() -> sourcemeta::blaze::Template {
                 return test_compile_target(
                     schema, resolver, target, base, dialect,
                     sourcemeta::blaze::Mode::Exhaustive, std::nullopt);
               });
  }

  return suite;
}

#endif
