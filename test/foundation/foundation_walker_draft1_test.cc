#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>

#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set
#include <variant>       // std::holds_alternative, std::get

#define EXPECT_VOCABULARY_KNOWN(vocabulary_value, expected_known)              \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::SchemaVocabularies::Known>(    \
          (vocabulary_value)));                                                \
  EXPECT_EQ(std::get<sourcemeta::blaze::SchemaVocabularies::Known>(            \
                (vocabulary_value)),                                           \
            sourcemeta::blaze::SchemaVocabularies::Known::expected_known)

static const sourcemeta::blaze::SchemaVocabularies VOCABULARIES_DRAFT1{
    {"http://json-schema.org/draft-01/schema#", true}};

static const sourcemeta::blaze::SchemaVocabularies
    VOCABULARIES_DRAFT1_HYPERSCHEMA{
        {"http://json-schema.org/draft-01/hyper-schema#", true}};

TEST(schema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$schema", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(id) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("id", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(ref) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$ref", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(items) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(properties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("properties", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyStatic);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(additionalProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  const std::unordered_set<std::string_view> expected{"properties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(type) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(enum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(maximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
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
  const auto &result{schema_walker("minimum", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
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
  const auto &result{schema_walker("maximumCanEqual", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
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
  const auto &result{schema_walker("minimumCanEqual", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
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
  const auto &result{schema_walker("maxLength", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(minLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minLength", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(pattern) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(maxItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxItems", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(minItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minItems", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(requires) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("requires", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseParent);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(format) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(title) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(description) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("description", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(default) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(disallow) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("disallow", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(extends) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("extends", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueOrElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(contentEncoding) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("contentEncoding", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(optional) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("optional", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(maxDecimal) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxDecimal", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Real}));
}

TEST(hyperschema_links) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_fragmentResolution) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("fragmentResolution", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_root) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("root", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_readonly) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("readonly", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_pathStart) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("pathStart", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_mediaType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("mediaType", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_alternate) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("alternate", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_method) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("method", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_enctype) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enctype", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_schema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$schema", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_id) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("id", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_ref) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$ref", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_items) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_properties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("properties", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyStatic);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_additionalProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  const std::unordered_set<std::string_view> expected{"properties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_type) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_enum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_maximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
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
  const auto &result{schema_walker("minimum", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
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
      schema_walker("maximumCanEqual", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
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
      schema_walker("minimumCanEqual", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
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
      schema_walker("maxLength", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_minLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minLength", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_pattern) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_maxItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxItems", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_minItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("minItems", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(hyperschema_requires) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("requires", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseParent);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_format) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_title) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_description) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("description", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_default) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_disallow) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("disallow", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_extends) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("extends", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueOrElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_contentEncoding) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("contentEncoding", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(hyperschema_optional) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("optional", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(hyperschema_maxDecimal) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("maxDecimal", VOCABULARIES_DRAFT1_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_1_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Real}));
}

TEST(hyperschema_links_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_fragmentResolution_without_hyperchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("fragmentResolution", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_root_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("root", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_readonly_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("readonly", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_pathStart_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pathStart", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_mediaType_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("mediaType", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_alternate_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("alternate", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_method_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("method", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_enctype_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enctype", VOCABULARIES_DRAFT1)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}
