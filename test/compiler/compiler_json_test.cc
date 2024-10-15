#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(Compiler_json, defines_basic_root) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{
      SchemaCompilerAssertionDefines{Pointer{}, Pointer{}, "#", 0, true, true,
                                     SchemaCompilerValueString{"foo"}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "defines",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "value": {
        "category": "value",
        "type": "string",
        "value": "foo"
      }
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, defines_basic_nested) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{SchemaCompilerAssertionDefines{
      Pointer{"foo", "bar"}, Pointer{}, "#/foo/bar", 0, true, true,
      SchemaCompilerValueString{"foo"}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "defines",
      "relativeSchemaLocation": "/foo/bar",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#/foo/bar",
      "value": {
        "category": "value",
        "type": "string",
        "value": "foo"
      }
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, fail_basic_root) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{SchemaCompilerAssertionFail{
      Pointer{}, Pointer{}, "#", 0, true, true, SchemaCompilerValueNone{}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "fail",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "value": null
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, type_basic_root) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{SchemaCompilerAssertionTypeStrict{
      Pointer{}, Pointer{}, "#", 0, true, true,
      SchemaCompilerValueType{JSON::Type::String}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "type-strict",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "value": {
        "category": "value",
        "type": "type",
        "value": "string"
      }
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, or_empty) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{SchemaCompilerLogicalOr{
      Pointer{}, Pointer{}, "#", 0, true, true, false, {}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "or",
      "value": {
        "category": "value",
        "type": "boolean",
        "value": false
      },
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "children": []
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, or_single_child) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate children{SchemaCompilerAssertionTypeStrict{
      Pointer{}, Pointer{}, "#", 0, true, true,
      SchemaCompilerValueType{JSON::Type::String}}};

  const SchemaCompilerTemplate steps{SchemaCompilerLogicalOr{
      Pointer{}, Pointer{}, "#", 0, true, true, false, children}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "or",
      "value": {
        "category": "value",
        "type": "boolean",
        "value": false
      },
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
          "dynamic": true,
          "report": true,
          "absoluteKeywordLocation": "#",
          "value": {
            "category": "value",
            "type": "type",
            "value": "string"
          }
        }
      ]
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, or_multiple_children) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate children{
      SchemaCompilerAssertionTypeStrict{
          Pointer{}, Pointer{}, "#", 0, true, true,
          SchemaCompilerValueType{JSON::Type::String}},
      SchemaCompilerAssertionTypeStrict{
          Pointer{}, Pointer{}, "#", 0, true, true,
          SchemaCompilerValueType{JSON::Type::Array}}};

  const SchemaCompilerTemplate steps{SchemaCompilerLogicalOr{
      Pointer{}, Pointer{}, "#", 0, true, true, false, children}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "or",
      "value": {
        "category": "value",
        "type": "boolean",
        "value": false
      },
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
          "dynamic": true,
          "report": true,
          "absoluteKeywordLocation": "#",
          "value": {
            "category": "value",
            "type": "type",
            "value": "string"
          }
        },
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
          "dynamic": true,
          "report": true,
          "absoluteKeywordLocation": "#",
          "value": {
            "category": "value",
            "type": "type",
            "value": "array"
          }
        }
      ]
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, and_empty) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{SchemaCompilerLogicalAnd{
      Pointer{}, Pointer{}, "#", 0, true, true, SchemaCompilerValueNone{}, {}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "and",
      "value": null,
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "children": []
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, and_single_child) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate children{SchemaCompilerAssertionTypeStrict{
      Pointer{}, Pointer{}, "#", 0, true, true,
      SchemaCompilerValueType{JSON::Type::String}}};

  const SchemaCompilerTemplate steps{
      SchemaCompilerLogicalAnd{Pointer{}, Pointer{}, "#", 0, true, true,
                               SchemaCompilerValueNone{}, children}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "and",
      "value": null,
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
          "dynamic": true,
          "report": true,
          "absoluteKeywordLocation": "#",
          "value": {
            "category": "value",
            "type": "type",
            "value": "string"
          }
        }
      ]
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, and_multiple_children) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate children{
      SchemaCompilerAssertionTypeStrict{
          Pointer{}, Pointer{}, "#", 0, true, true,
          SchemaCompilerValueType{JSON::Type::String}},
      SchemaCompilerAssertionTypeStrict{
          Pointer{}, Pointer{}, "#", 0, true, true,
          SchemaCompilerValueType{JSON::Type::Array}}};

  const SchemaCompilerTemplate steps{
      SchemaCompilerLogicalAnd{Pointer{}, Pointer{}, "#", 0, true, true,
                               SchemaCompilerValueNone{}, children}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "and",
      "value": null,
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
          "dynamic": true,
          "report": true,
          "absoluteKeywordLocation": "#",
          "value": {
            "category": "value",
            "type": "type",
            "value": "string"
          }
        },
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
          "dynamic": true,
          "report": true,
          "absoluteKeywordLocation": "#",
          "value": {
            "category": "value",
            "type": "type",
            "value": "array"
          }
        }
      ]
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, regex_basic) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const SchemaCompilerTemplate steps{SchemaCompilerAssertionRegex{
      Pointer{}, Pointer{}, "#", 0, true, true,
      SchemaCompilerValueRegex{std::regex{"^a", std::regex::ECMAScript},
                               "^a"}}};

  const JSON result{to_json(steps)};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "regex",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "dynamic": true,
      "report": true,
      "absoluteKeywordLocation": "#",
      "value": {
        "category": "value",
        "type": "regex",
        "value": "^a"
      }
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}
