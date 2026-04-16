#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem::path
#include <memory>     // std::unique_ptr

#include "alterschema_test_utils.h"

class CanonicalizerDraft0Test : public testing::Test {
protected:
  static auto SetUpTestSuite() -> void {
    const auto meta_schema = sourcemeta::core::read_json(
        std::filesystem::path{SCHEMAS_PATH} / "canonical-draft1.json");
    compiled_meta_ = std::make_unique<sourcemeta::blaze::Template>(
        sourcemeta::blaze::compile(meta_schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler));
  }

  static std::unique_ptr<sourcemeta::blaze::Template> compiled_meta_;
};

std::unique_ptr<sourcemeta::blaze::Template>
    CanonicalizerDraft0Test::compiled_meta_ = nullptr;

TEST_F(CanonicalizerDraft0Test, type_boolean_as_enum) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "boolean"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "enum": [ false, true ]
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft0Test, integer_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "integer",
    "maxDecimal": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft0Test, array_minimal) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "array"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "array",
    "items": {},
    "minItems": 0
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}

TEST_F(CanonicalizerDraft0Test, object_with_property_optional_implicit) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#",
    "type": "object",
    "properties": {
      "name": { "type": "string", "minLength": 0, "optional": false }
    },
    "additionalProperties": {}
  })JSON");

  CANONICALIZE_NEXT(document, expected, *compiled_meta_);
}
