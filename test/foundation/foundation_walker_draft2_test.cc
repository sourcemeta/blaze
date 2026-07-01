#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>

#include "foundation_test_utils.h"

#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

static const sourcemeta::blaze::Vocabularies VOCABULARIES_DRAFT2{
    {"http://json-schema.org/draft-02/schema#", true}};

static const sourcemeta::blaze::Vocabularies VOCABULARIES_DRAFT2_HYPERSCHEMA{
    {"http://json-schema.org/draft-02/hyper-schema#", true}};

TEST(schema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$schema", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(id) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("id", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(ref) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$ref", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(items) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(properties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("properties", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyStatic);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(additionalProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  const std::unordered_set<std::string_view> expected{"properties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(type) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(enum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(maximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(minimum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minimum", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(maximumCanEqual) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximumCanEqual", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(minimumCanEqual) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minimumCanEqual", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(maxLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxLength", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(minLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minLength", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(pattern) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(maxItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxItems", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(minItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minItems", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(uniqueItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("uniqueItems", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(requires) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("requires", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseParent);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(optional) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("optional", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(format) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(title) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(description) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("description", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(default) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(divisibleBy) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("divisibleBy", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(disallow) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("disallow", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(extends) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("extends", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueOrElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(contentEncoding) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("contentEncoding", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_links) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_fragmentResolution) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("fragmentResolution", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_root) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("root", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_readonly) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("readonly", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_pathStart) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("pathStart", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_mediaType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("mediaType", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_alternate) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("alternate", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_method) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("method", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_enctype) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enctype", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_schema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$schema", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_id) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("id", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_ref) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$ref", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_items) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_properties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("properties", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyStatic);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_additionalProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  const std::unordered_set<std::string_view> expected{"properties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_type) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_enum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_maximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(hyperschema_minimum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minimum", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(hyperschema_maximumCanEqual) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maximumCanEqual", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(hyperschema_minimumCanEqual) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minimumCanEqual", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(hyperschema_maxLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxLength", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_minLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minLength", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_pattern) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_maxItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxItems", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_minItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minItems", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_uniqueItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("uniqueItems", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_requires) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("requires", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseParent);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_optional) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("optional", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_format) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_title) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_description) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("description", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_default) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_divisibleBy) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("divisibleBy", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(hyperschema_disallow) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("disallow", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_extends) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("extends", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueOrElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_contentEncoding) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentEncoding", VOCABULARIES_DRAFT2_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_2_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_fragmentResolution_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("fragmentResolution", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_root_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("root", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_readonly_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("readonly", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_pathStart_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pathStart", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_mediaType_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("mediaType", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_alternate_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("alternate", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_method_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("method", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_enctype_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enctype", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetSchema_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("targetSchema", VOCABULARIES_DRAFT2)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(schema_keyword_priority_object) {
  const auto &vocabularies = VOCABULARIES_DRAFT2;
  const auto &walker = sourcemeta::blaze::schema_walker;
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  EXPECT_EQ(schema_keyword_priority("properties", vocabularies, walker), 0);
  EXPECT_EQ(
      schema_keyword_priority("additionalProperties", vocabularies, walker), 1);
}

TEST(schema_keyword_priority_unknown) {
  const auto &vocabularies = VOCABULARIES_DRAFT2;
  const auto &walker = sourcemeta::blaze::schema_walker;
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  EXPECT_EQ(schema_keyword_priority("foobar", vocabularies, walker), 0);
}

TEST(instance_locations) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-02/schema#",
    "properties": {
      "foo": {
        "type": "string",
        "requires": { "type": "object" }
      },
      "bar": false
    },
    "additionalProperties": { "type": "number" },
    "items": { "items": [ { "type": "string" }, { "type": "integer" } ] },
    "type": [ "string", { "type": "number" }, { "type": "integer" } ],
    "extends": {
      "extends": [ { "type": "string" } ]
    }
  })JSON");

  std::vector<sourcemeta::blaze::SchemaIteratorEntry> entries;
  for (const auto &entry : sourcemeta::blaze::SchemaIterator(
           document, sourcemeta::blaze::schema_walker,
           sourcemeta::blaze::schema_resolver)) {
    entries.push_back(entry);
  }

  EXPECT_EQ(entries.size(), 12);

  EXPECT_WALKER_ENTRY_DRAFT2(entries, 0, "", std::nullopt);

  // Applicators (object)
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 1, "/properties/foo", "");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 2, "/properties/foo/requires",
                             "/properties/foo");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 3, "/properties/bar", "");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 4, "/additionalProperties", "");

  // Applicators (array)
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 5, "/items", "");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 6, "/items/items/0", "/items");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 7, "/items/items/1", "/items");

  // Applicators (any)
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 8, "/type/1", "");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 9, "/type/2", "");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 10, "/extends", "");
  EXPECT_WALKER_ENTRY_DRAFT2(entries, 11, "/extends/extends/0", "/extends");
}
