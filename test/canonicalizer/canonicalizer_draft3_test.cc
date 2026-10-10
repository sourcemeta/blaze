#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/canonicalizer.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "canonicalizer_test_utils.h"

// Every other Draft 3 case lives in `draft3/` as a JSON fixture, where the
// suite holds whatever comes out to `schemas/canonical-draft3.json`. These two
// cannot go there, because the canonicaliser hands back a document that the
// meta-schema rejects.
//
// TODO: Fix the canonicaliser so that both of these produce a document that
// `schemas/canonical-draft3.json` describes, then move each one into `draft3/`
// like every other case. Each is a BUG, not a property of Draft 3 for a test
// to bless: the canonicaliser must never emit something that violates the
// canonical schema, and the fixture suite deliberately offers no way of saying
// that it did

TEST(graph_form_leaves_hyper_schema_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/hyper-schema#",
    "type": "object",
    "links": [
      { "rel": "full", "href": "{id}", "targetSchema": { "type": "string" } }
    ],
    "properties": { "a": { "type": "string" } }
  })JSON");

  // A `links` entry describes a link rather than a subschema, so lifting one
  // into `definitions` and referring to it would say something this document
  // never said. The canonicaliser therefore leaves the nesting in place, and
  // what comes back is a document `canonical-draft3.json` does not describe
  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/hyper-schema#",
      "type": "object",
      "properties": {
        "a": {
          "type": "string"
        }
      },
      "links": [
        {
          "href": "{id}",
          "rel": "full",
          "targetSchema": {
            "type": "string"
          }
        }
      ]
    })JSON");

  sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  EXPECT_EQ(document, expected);

  auto again{document};
  sourcemeta::blaze::canonicalize(again, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  EXPECT_EQ(again, document);
}

TEST(graph_form_declines_a_reference_cycle_that_says_nothing) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "definitions": {
      "a": { "$ref": "#/definitions/b" },
      "b": { "$ref": "#/definitions/a" }
    },
    "type": "object",
    "properties": {
      "x": { "$ref": "#/definitions/a" }
    }
  })JSON");

  // Following the references never reaches a subschema that says anything, so
  // there is no entry for the incoming reference to point at. The
  // canonicaliser leaves the document alone, which keeps it meaning what it
  // did and leaves graph form out of reach
  const auto expected = sourcemeta::core::parse_json(R"JSON({
      "$schema": "http://json-schema.org/draft-03/schema#",
      "type": "object",
      "properties": {
        "x": {
          "$ref": "#/definitions/a"
        }
      },
      "patternProperties": {},
      "additionalProperties": {},
      "definitions": {
        "a": {
          "$ref": "#/definitions/b"
        },
        "b": {
          "$ref": "#/definitions/a"
        }
      }
    })JSON");

  sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  EXPECT_EQ(document, expected);
}
