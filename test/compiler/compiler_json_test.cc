#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/regex.h>

TEST(Compiler_json, defines_basic_root) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const Instructions steps{
      AssertionDefines{Pointer{}, Pointer{}, "#", 0, ValueString{"foo"}}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "defines",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
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

  const Instructions steps{AssertionDefines{
      Pointer{"foo", "bar"}, Pointer{}, "#/foo/bar", 0, ValueString{"foo"}}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "defines",
      "relativeSchemaLocation": "/foo/bar",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
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

  const Instructions steps{
      AssertionFail{Pointer{}, Pointer{}, "#", 0, ValueNone{}}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "fail",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "absoluteKeywordLocation": "#",
      "value": null
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, type_basic_root) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const Instructions steps{AssertionTypeStrict{Pointer{}, Pointer{}, "#", 0,
                                               ValueType{JSON::Type::String}}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "type-strict",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
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

  const Instructions steps{LogicalOr{Pointer{}, Pointer{}, "#", 0, false, {}}};

  const JSON result{to_json({steps, {}})};
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
      "absoluteKeywordLocation": "#",
      "children": []
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, or_single_child) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const Instructions children{AssertionTypeStrict{
      Pointer{}, Pointer{}, "#", 0, ValueType{JSON::Type::String}}};

  const Instructions steps{
      LogicalOr{Pointer{}, Pointer{}, "#", 0, false, children}};

  const JSON result{to_json({steps, {}})};
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
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
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

  const Instructions children{
      AssertionTypeStrict{Pointer{}, Pointer{}, "#", 0,
                          ValueType{JSON::Type::String}},
      AssertionTypeStrict{Pointer{}, Pointer{}, "#", 0,
                          ValueType{JSON::Type::Array}}};

  const Instructions steps{
      LogicalOr{Pointer{}, Pointer{}, "#", 0, false, children}};

  const JSON result{to_json({steps, {}})};
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
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
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

  const Instructions steps{
      LogicalAnd{Pointer{}, Pointer{}, "#", 0, ValueNone{}, {}}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "and",
      "value": null,
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "absoluteKeywordLocation": "#",
      "children": []
    }
  ])EOF")};

  EXPECT_EQ(result, expected);
}

TEST(Compiler_json, and_single_child) {
  using namespace sourcemeta::jsontoolkit;
  using namespace sourcemeta::blaze;

  const Instructions children{AssertionTypeStrict{
      Pointer{}, Pointer{}, "#", 0, ValueType{JSON::Type::String}}};

  const Instructions steps{
      LogicalAnd{Pointer{}, Pointer{}, "#", 0, ValueNone{}, children}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "and",
      "value": null,
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
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

  const Instructions children{
      AssertionTypeStrict{Pointer{}, Pointer{}, "#", 0,
                          ValueType{JSON::Type::String}},
      AssertionTypeStrict{Pointer{}, Pointer{}, "#", 0,
                          ValueType{JSON::Type::Array}}};

  const Instructions steps{
      LogicalAnd{Pointer{}, Pointer{}, "#", 0, ValueNone{}, children}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "logical",
      "type": "and",
      "value": null,
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
      "absoluteKeywordLocation": "#",
      "children": [
        {
          "category": "assertion",
          "type": "type-strict",
          "relativeSchemaLocation": "",
          "relativeInstanceLocation": "",
          "schemaResource": 0,
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

  const Instructions steps{AssertionRegex{
      Pointer{}, Pointer{}, "#", 0,
      ValueRegex{sourcemeta::jsontoolkit::to_regex("^a").value(), "^a"}}};

  const JSON result{to_json({steps, {}})};
  const JSON expected{parse(R"EOF([
    {
      "category": "assertion",
      "type": "regex",
      "relativeSchemaLocation": "",
      "relativeInstanceLocation": "",
      "schemaResource": 0,
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
