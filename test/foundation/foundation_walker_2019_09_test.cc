#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>

#include <algorithm>

#include "foundation_test_utils.h"

#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_CORE{
    {"https://json-schema.org/draft/2019-09/vocab/core", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_APPLICATOR{
    {"https://json-schema.org/draft/2019-09/vocab/core", true},
    {"https://json-schema.org/draft/2019-09/vocab/applicator", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_VALIDATION{
    {"https://json-schema.org/draft/2019-09/vocab/core", true},
    {"https://json-schema.org/draft/2019-09/vocab/validation", true}};

static const sourcemeta::blaze::Vocabularies
    VOCABULARIES_2019_09_APPLICATOR_AND_VALIDATION{
        {"https://json-schema.org/draft/2019-09/vocab/core", true},
        {"https://json-schema.org/draft/2019-09/vocab/applicator", true},
        {"https://json-schema.org/draft/2019-09/vocab/validation", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_FORMAT{
    {"https://json-schema.org/draft/2019-09/vocab/core", true},
    {"https://json-schema.org/draft/2019-09/vocab/format", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_CONTENT{
    {"https://json-schema.org/draft/2019-09/vocab/core", true},
    {"https://json-schema.org/draft/2019-09/vocab/content", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_METADATA{
    {"https://json-schema.org/draft/2019-09/vocab/core", true},
    {"https://json-schema.org/draft/2019-09/vocab/meta-data", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_2019_09_HYPERSCHEMA{
    {"https://json-schema.org/draft/2019-09/vocab/core", true},
    {"https://json-schema.org/draft/2019-09/vocab/hyper-schema", true}};

TEST(core_schema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$schema", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$vocabulary", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_id) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$id", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_anchor) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$anchor", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_recursiveAnchor) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("$recursiveAnchor", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_ref) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$ref", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_recursiveRef) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$recursiveRef", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_defs) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$defs", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::LocationMembers);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(core_comment) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$comment", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_2019_09_Core);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_allOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("allOf", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_anyOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("anyOf", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_oneOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("oneOf", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_not) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("not", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceNegate);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_if) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("if", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceMaybe);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_then) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("then", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceMaybe);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{"if"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_else) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("else", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceMaybe);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{"if"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_dependentSchemas) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("dependentSchemas", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorMembersInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(applicator_items) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(applicator_additionalItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalItems", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseSomeItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{"items"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(applicator_contains_only) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contains", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseAnyItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(applicator_contains_with_validation) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker(
      "contains", VOCABULARIES_2019_09_APPLICATOR_AND_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseAnyItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{"minContains",
                                                      "maxContains"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(applicator_properties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("properties", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyStatic);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(applicator_patternProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("patternProperties", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyRegex);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(applicator_additionalProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{"properties",
                                                      "patternProperties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(applicator_propertyNames) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("propertyNames", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseAnyPropertyKey);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(applicator_unevaluatedItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("unevaluatedItems", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseSomeItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{"items",
                                                      "additionalItems"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(applicator_unevaluatedProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("unevaluatedProperties", VOCABULARIES_2019_09_APPLICATOR)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Applicator);
  const std::unordered_set<std::string_view> expected{
      "properties", "patternProperties", "additionalProperties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(validation_type) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_enum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_const) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("const", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_multipleOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("multipleOf", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(validation_maximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  const std::unordered_set<std::string_view> expected{"type"};
  EXPECT_EQ(result.order_dependencies, expected);
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(validation_minimum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minimum", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  const std::unordered_set<std::string_view> expected{"type"};
  EXPECT_EQ(result.order_dependencies, expected);
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(validation_exclusiveMaximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("exclusiveMaximum", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(validation_exclusiveMinimum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("exclusiveMinimum", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(validation_maxLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxLength", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(validation_minLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minLength", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(validation_pattern) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(validation_maxItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxItems", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(validation_minItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minItems", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(validation_uniqueItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("uniqueItems", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(validation_maxContains) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxContains", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(validation_minContains) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minContains", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(validation_maxProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxProperties", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(validation_minProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minProperties", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(validation_required) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("required", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(validation_dependentRequired) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("dependentRequired", VOCABULARIES_2019_09_VALIDATION)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Validation);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(format_format) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_2019_09_FORMAT)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Format);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(content_contentEncoding) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentEncoding", VOCABULARIES_2019_09_CONTENT)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Content);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(content_contentMediaType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentMediaType", VOCABULARIES_2019_09_CONTENT)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Content);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(content_contentSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentSchema", VOCABULARIES_2019_09_CONTENT)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Content);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(metadata_title) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_description) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("description", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_default) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_deprecated) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("deprecated", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_readOnly) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("readOnly", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_writeOnly) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("writeOnly", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_examples) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("examples", VOCABULARIES_2019_09_METADATA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Annotation);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Meta_Data);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_base) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("base", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_links) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_anchor) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("anchor", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_anchorPointer) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("anchorPointer", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_templatePointers) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("templatePointers", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_templateRequired) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("templateRequired", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetMediaType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("targetMediaType", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetHints) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("targetHints", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionMediaType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("submissionMediaType", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_hrefSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("hrefSchema", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("targetSchema", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_headerSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("headerSchema", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("submissionSchema", VOCABULARIES_2019_09_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(),
                          JSON_Schema_2019_09_Hyper_Schema);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_allOf_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("allOf", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_anyOf_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("anyOf", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_oneOf_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("oneOf", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_not_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("not", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_if_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("if", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_then_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("then", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_else_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("else", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_dependentSchemas_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("dependentSchemas", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_additionalItems_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalItems", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_items_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_contains_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("contains", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_properties_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("properties", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_patternProperties_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("patternProperties", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_additionalProperties_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_propertyNames_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("propertyNames", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_unevaluatedItems_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("unevaluatedItems", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(applicator_unevaluatedProperties_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("unevaluatedProperties", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_type_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_enum_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_const_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("const", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_multipleOf_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("multipleOf", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_maximum_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_minimum_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minimum", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_exclusiveMaximum_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("exclusiveMaximum", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_exclusiveMinimum_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("exclusiveMinimum", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_maxLength_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxLength", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_minLength_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minLength", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_pattern_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_maxItems_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxItems", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_minItems_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minItems", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_uniqueItems_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("uniqueItems", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_maxContains_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxContains", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_minContains_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minContains", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_maxProperties_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxProperties", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_minProperties_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minProperties", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_required_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("required", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(validation_dependentRequired_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("dependentRequired", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(format_format_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(content_contentEncoding_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentEncoding", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(content_contentMediaType_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentMediaType", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(content_contentSchema_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("contentSchema", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_title_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_description_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("description", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_default_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_deprecated_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("deprecated", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_readOnly_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("readOnly", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_writeOnly_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("writeOnly", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(metadata_examples_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("examples", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_base_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("base", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_links_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_ref_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("ref", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_anchor_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("anchor", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_anchorPointer_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("anchorPointer", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_templatePointers_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("templatePointers", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_templateRequired_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("templateRequired", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetMediaType_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("targetMediaType", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetHints_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("targetHints", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionMediaType_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("submissionMediaType", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_hrefSchema_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("hrefSchema", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetSchema_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("targetSchema", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_headerSchema_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("headerSchema", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionSchema_without_vocabulary) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("submissionSchema", VOCABULARIES_2019_09_CORE)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(schema_keyword_priority_array) {
  const auto &vocabularies = VOCABULARIES_2019_09_APPLICATOR_AND_VALIDATION;
  const auto &walker = sourcemeta::blaze::schema_walker;
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  EXPECT_EQ(schema_keyword_priority("items", vocabularies, walker), 0);
  EXPECT_EQ(schema_keyword_priority("additionalItems", vocabularies, walker),
            1);
  EXPECT_EQ(schema_keyword_priority("minContains", vocabularies, walker), 0);
  EXPECT_EQ(schema_keyword_priority("maxContains", vocabularies, walker), 0);
  EXPECT_EQ(schema_keyword_priority("contains", vocabularies, walker), 1);
  EXPECT_EQ(schema_keyword_priority("unevaluatedItems", vocabularies, walker),
            2);
}

TEST(schema_keyword_priority_object) {
  const auto &vocabularies = VOCABULARIES_2019_09_APPLICATOR;
  const auto &walker = sourcemeta::blaze::schema_walker;
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  EXPECT_EQ(schema_keyword_priority("properties", vocabularies, walker), 0);
  EXPECT_EQ(schema_keyword_priority("patternProperties", vocabularies, walker),
            0);
  EXPECT_EQ(
      schema_keyword_priority("additionalProperties", vocabularies, walker), 1);
  EXPECT_EQ(
      schema_keyword_priority("unevaluatedProperties", vocabularies, walker),
      2);
}

TEST(schema_keyword_priority_other) {
  const auto &vocabularies = VOCABULARIES_2019_09_APPLICATOR;
  const auto &walker = sourcemeta::blaze::schema_walker;
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  EXPECT_EQ(schema_keyword_priority("if", vocabularies, walker), 0);
  EXPECT_EQ(schema_keyword_priority("then", vocabularies, walker), 1);
  EXPECT_EQ(schema_keyword_priority("else", vocabularies, walker), 1);
}

TEST(schema_keyword_priority_unknown) {
  const auto &vocabularies = VOCABULARIES_2019_09_CORE;
  const auto &walker = sourcemeta::blaze::schema_walker;
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  EXPECT_EQ(schema_keyword_priority("foobar", vocabularies, walker), 0);
}

TEST(instance_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "allOf": [ { "type": "string" }, { "minLength": 3 } ],
    "anyOf": [ { "type": "string" } ],
    "oneOf": [ { "type": "string" } ],
    "if": { "const": "foo" },
    "then": true,
    "else": { "maxLength": 10 },
    "not": { "const": "bar" },
    "properties": {
      "foo": { "type": "string" },
      "bar": false
    },
    "additionalProperties": { "type": "number" },
    "patternProperties": {
      "^f": { "type": "integer" },
      "x$": true
    },
    "dependentSchemas": {
      "foo": { "minProperties": 1 },
      "bar": { "maxProperties": 10 }
    },
    "propertyNames": { "minLength": 1 },
    "contains": { "type": "number" },
    "additionalItems": { "minimum": 2 },
    "items": { "items": [ true, false ] },
    "unevaluatedProperties": { "type": "number" },
    "unevaluatedItems": { "minimum": 2 },
    "contentSchema": { "type": "string" },
    "$defs": {
      "foo": {
        "properties": {
          "bar": { "type": "string" }
        }
      }
    },
    "definitions": { "foo": true }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 28);

  EXPECT_WALKER_ENTRY_2019_09(entries, 0, "", std::nullopt);

  // Applicator vocabulary (any)
  EXPECT_WALKER_ENTRY_2019_09(entries, 1, "/allOf/0", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 2, "/allOf/1", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 3, "/anyOf/0", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 4, "/oneOf/0", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 5, "/if", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 6, "/then", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 7, "/else", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 8, "/not", "");

  // Applicator vocabulary (object)
  EXPECT_WALKER_ENTRY_2019_09(entries, 9, "/properties/foo", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 10, "/properties/bar", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 11, "/additionalProperties", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 12, "/patternProperties/^f", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 13, "/patternProperties/x$", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 14, "/dependentSchemas/foo", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 15, "/dependentSchemas/bar", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 16, "/propertyNames", "");

  // Applicator vocabulary (array)
  EXPECT_WALKER_ENTRY_2019_09(entries, 17, "/contains", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 18, "/additionalItems", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 19, "/items", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 20, "/items/items/0", "/items");
  EXPECT_WALKER_ENTRY_2019_09(entries, 21, "/items/items/1", "/items");

  // Unevaluated applicators
  EXPECT_WALKER_ENTRY_2019_09(entries, 22, "/unevaluatedProperties", "");
  EXPECT_WALKER_ENTRY_2019_09(entries, 23, "/unevaluatedItems", "");

  // Content vocabulary
  EXPECT_WALKER_ENTRY_2019_09(entries, 24, "/contentSchema", "");

  // Core vocabulary
  EXPECT_WALKER_ENTRY_2019_09_ORPHAN(entries, 25, "/$defs/foo", "");
  EXPECT_WALKER_ENTRY_2019_09_ORPHAN(entries, 26, "/$defs/foo/properties/bar",
                                     "/$defs/foo");
  EXPECT_WALKER_ENTRY_2019_09_ORPHAN(entries, 27, "/definitions/foo", "");
}

TEST(definitions_subschemas) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": {
        "properties": {
          "bar": {
            "additionalProperties": {
              "type": "string"
            }
          }
        }
      }
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 4);

  EXPECT_WALKER_ENTRY_2019_09(entries, 0, "", std::nullopt);
  EXPECT_WALKER_ENTRY_2019_09_ORPHAN(entries, 1, "/$defs/foo", "");
  EXPECT_WALKER_ENTRY_2019_09_ORPHAN(entries, 2, "/$defs/foo/properties/bar",
                                     "/$defs/foo");
  EXPECT_WALKER_ENTRY_2019_09_ORPHAN(
      entries, 3, "/$defs/foo/properties/bar/additionalProperties",
      "/$defs/foo/properties/bar");
}
