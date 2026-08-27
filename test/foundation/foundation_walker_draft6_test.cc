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

static const sourcemeta::blaze::SchemaVocabularies VOCABULARIES_DRAFT6{
    {"http://json-schema.org/draft-06/schema#", true}};

static const sourcemeta::blaze::SchemaVocabularies
    VOCABULARIES_DRAFT6_HYPERSCHEMA{
        {"http://json-schema.org/draft-06/hyper-schema#", true}};

TEST(schema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$schema", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(id) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$id", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(ref) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("$ref", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Reference);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(definitions) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("definitions", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::LocationMembers);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(allOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("allOf", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(anyOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("anyOf", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(oneOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("oneOf", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(not) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("not", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceNegate);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(items) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("items", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueOrElementsTraverseAnyItemOrItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(additionalItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("additionalItems", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseSomeItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"items"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(contains) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("contains", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueTraverseAnyItem);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(properties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("properties", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyStatic);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected_dependencies{"$ref"};
  EXPECT_EQ(result.dependencies, expected_dependencies);
  const std::unordered_set<std::string_view> expected_order_dependencies{
      "required"};
  EXPECT_EQ(result.order_dependencies, expected_order_dependencies);
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(patternProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("patternProperties", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorMembersTraversePropertyRegex);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(dependencies) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("dependencies", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorMembersInPlaceSome);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(additionalProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("additionalProperties", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseSomeProperty);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"properties",
                                                      "patternProperties"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(propertyNames) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("propertyNames", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type,
            SchemaKeywordType::ApplicatorValueTraverseAnyPropertyKey);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(type) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("type", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  EXPECT_TRUE(result.dependencies.empty());
  const std::unordered_set<std::string_view> expected{"properties"};
  EXPECT_EQ(result.order_dependencies, expected);
  EXPECT_TRUE(result.instances.none());
}

TEST(enum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("enum", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(const) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("const", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(multipleOf) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("multipleOf", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(maximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maximum", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(minimum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minimum", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(exclusiveMaximum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("exclusiveMaximum", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(exclusiveMinimum) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("exclusiveMinimum", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  const auto instances =
      sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Integer,
                                  sourcemeta::core::JSON::Type::Real});
  EXPECT_EQ(result.instances, instances);
}

TEST(maxLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxLength", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(minLength) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minLength", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(pattern) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("pattern", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(maxItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxItems", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(minItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minItems", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(uniqueItems) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("uniqueItems", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Array}));
}

TEST(maxProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("maxProperties", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(minProperties) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("minProperties", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(required) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("required", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Assertion);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::Object}));
}

TEST(format) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("format", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_EQ(result.instances,
            sourcemeta::core::make_set({sourcemeta::core::JSON::Type::String}));
}

TEST(title) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("title", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(description) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("description", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(default) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("default", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(examples) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("examples", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_links) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorElementsInPlace);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_mediaType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("mediaType", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionEncType) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("submissionEncType", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_base) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("base", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_media) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("media", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Other);
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_readOnly) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("readOnly", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_hrefSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("hrefSchema", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("targetSchema", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionSchema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{
      schema_walker("submissionSchema", VOCABULARIES_DRAFT6_HYPERSCHEMA)};
  EXPECT_EQ(result.type, SchemaKeywordType::ApplicatorValueInPlaceOther);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6_Hyper);
  EXPECT_TRUE(result.dependencies.empty());
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_links_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("links", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_href_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("href", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_rel_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("rel", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_mediaType_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("mediaType", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionEncType_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("submissionEncType", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_base_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("base", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_media_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("media", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_readOnly_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("readOnly", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Comment);
  EXPECT_TRUE(result.vocabulary.has_value());
  EXPECT_VOCABULARY_KNOWN(result.vocabulary.value(), JSON_Schema_Draft_6);
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_hrefSchema_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("hrefSchema", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_targetSchema_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("targetSchema", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}

TEST(hyperschema_submissionSchema_without_hyperschema) {
  using namespace sourcemeta::core;
  using namespace sourcemeta::blaze;
  const auto &result{schema_walker("submissionSchema", VOCABULARIES_DRAFT6)};
  EXPECT_EQ(result.type, SchemaKeywordType::Unknown);
  EXPECT_FALSE(result.vocabulary.has_value());
  const std::unordered_set<std::string_view> expected{"$ref"};
  EXPECT_EQ(result.dependencies, expected);
  EXPECT_TRUE(result.order_dependencies.empty());
  EXPECT_TRUE(result.instances.none());
}
