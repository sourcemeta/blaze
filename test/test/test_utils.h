#ifndef SOURCEMETA_BLAZE_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_TEST_UTILS_H_

#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/uri.h>

#include <deque>       // std::deque
#include <memory>      // std::make_unique, std::unique_ptr
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move
#include <vector>      // std::vector

// What a target names is the caller's to resolve, bundle and frame. This does
// that for a target that names a schema of its own, and keeps what it resolved
// alive for as long as it lives, as a test suite borrows both the document and
// its frame
class TestTargetStore {
public:
  explicit TestTargetStore(sourcemeta::core::SchemaResolver resolver,
                           const std::string_view default_dialect = "")
      : resolver_{std::move(resolver)}, default_dialect_{default_dialect} {}

  auto operator()(const sourcemeta::core::JSON::String &target)
      -> sourcemeta::blaze::TestTarget {
    const sourcemeta::core::URI uri{target};
    const auto base{uri.recompose_without_fragment().value_or(target)};
    const auto resolved{this->resolver_(base)};
    if (!resolved.has_value()) {
      throw sourcemeta::core::SchemaResolutionError{
          base, "Could not resolve schema under test"};
    }

    const auto &document{
        this->documents_.emplace_back(sourcemeta::core::schema_bundle(
            resolved.value(), sourcemeta::core::schema_walker, this->resolver_,
            this->default_dialect_, base))};
    const auto &frame{*this->frames_.emplace_back(
        std::make_unique<sourcemeta::core::SchemaFrame>(
            sourcemeta::core::SchemaFrame::Mode::References, document,
            sourcemeta::core::schema_walker, this->resolver_,
            this->default_dialect_, base))};

    // Framing under the base that the target was resolved against keys
    // every schema of the document by what the test document names it by,
    // whether that is a place within it or an anchor it declares
    return {.document = document, .frame = frame, .entrypoint = target};
  }

private:
  sourcemeta::core::SchemaResolver resolver_;
  // Framing reports the default dialect back as a view into what the caller
  // passed, so the one every frame here was given has to live as long as they
  // do
  std::string default_dialect_;
  std::deque<sourcemeta::core::JSON> documents_;
  std::vector<std::unique_ptr<sourcemeta::core::SchemaFrame>> frames_;
};

#endif
