#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <optional>
#include <set>
#include <sstream>
#include <string>

#define EXPECT_VOCABULARY_REQUIRED(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(                                                           \
              sourcemeta::blaze::SchemaVocabularies::Known::expected_known));  \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .get(sourcemeta::blaze::SchemaVocabularies::Known::expected_known)   \
          .value())

#define EXPECT_OPTIONAL_POINTER(optional_value, expected_optional)             \
  if (std::optional<std::string>{expected_optional}.has_value()) {             \
    EXPECT_TRUE((optional_value).has_value());                                 \
    EXPECT_EQ(sourcemeta::core::to_string((optional_value).value()),           \
              std::optional<std::string>{expected_optional}.value());          \
  } else {                                                                     \
    EXPECT_FALSE((optional_value).has_value());                                \
  }

#define TO_POINTER(pointer_string)                                             \
  sourcemeta::core::to_pointer((pointer_string))

#define EXPECT_FRAME(frame, expected_type, reference, root_id,                 \
                     expected_pointer, expected_dialect,                       \
                     expected_base_dialect, expected_base,                     \
                     expected_relative_pointer, expected_parent,               \
                     expected_property_name, expected_orphan)                  \
  EXPECT_TRUE((frame).locations().contains({(expected_type), (reference)}));   \
  EXPECT_EQ((frame).root(), (root_id));                                        \
  EXPECT_EQ(                                                                   \
      sourcemeta::core::to_string(                                             \
          (frame).locations().at({(expected_type), (reference)}).pointer),     \
      (expected_pointer));                                                     \
  EXPECT_EQ((frame).locations().at({(expected_type), (reference)}).dialect,    \
            (expected_dialect));                                               \
  EXPECT_EQ((frame).locations().at({(expected_type), (reference)}).base,       \
            (expected_base));                                                  \
  EXPECT_TRUE(                                                                 \
      (frame)                                                                  \
          .traverse(                                                           \
              (frame).locations().at({(expected_type), (reference)}).base)     \
          .has_value());                                                       \
  EXPECT_EQ(                                                                   \
      (frame).locations().at({(expected_type), (reference)}).base_dialect,     \
      sourcemeta::blaze::SchemaBaseDialect::expected_base_dialect);            \
  EXPECT_EQ(sourcemeta::core::to_string((frame).relative_instance_location(    \
                (frame).locations().at({(expected_type), (reference)}))),      \
            (expected_relative_pointer));                                      \
  EXPECT_OPTIONAL_POINTER(                                                     \
      (frame).locations().at({(expected_type), (reference)}).parent,           \
      expected_parent);                                                        \
  EXPECT_EQ(                                                                   \
      (frame).locations().at({(expected_type), (reference)}).property_name,    \
      (expected_property_name));                                               \
  EXPECT_EQ((frame).locations().at({(expected_type), (reference)}).orphan,     \
            (expected_orphan));

#define EXPECT_FRAME_STATIC(                                                   \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME(frame, sourcemeta::blaze::SchemaReferenceType::Static,          \
               reference, root_id, expected_pointer, expected_dialect,         \
               expected_base_dialect, expected_base,                           \
               expected_relative_pointer, expected_parent,                     \
               expected_property_name, expected_orphan)

#define EXPECT_FRAME_STATIC_RESOURCE(                                          \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME_STATIC(frame, reference, root_id, expected_pointer,             \
                      expected_dialect, expected_base_dialect, expected_base,  \
                      expected_relative_pointer, expected_parent,              \
                      expected_property_name, expected_orphan)                 \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Resource);

#define EXPECT_FRAME_STATIC_POINTER(                                           \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME_STATIC(frame, reference, root_id, expected_pointer,             \
                      expected_dialect, expected_base_dialect, expected_base,  \
                      expected_relative_pointer, expected_parent,              \
                      expected_property_name, expected_orphan)                 \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Pointer);

#define EXPECT_FRAME_STATIC_SUBSCHEMA(                                         \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME_STATIC(frame, reference, root_id, expected_pointer,             \
                      expected_dialect, expected_base_dialect, expected_base,  \
                      expected_relative_pointer, expected_parent,              \
                      expected_property_name, expected_orphan)                 \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Subschema);

#define EXPECT_REFERENCE(frame, expected_type, expected_pointer, expected_uri, \
                         expected_base, expected_fragment, expected_original)  \
  {                                                                            \
    const auto __ref_pointer{TO_POINTER(expected_pointer)};                    \
    const auto __ref_entry{(frame).reference(                                  \
        expected_type, sourcemeta::core::to_weak_pointer(__ref_pointer))};     \
    EXPECT_TRUE(__ref_entry.has_value());                                      \
    EXPECT_EQ(__ref_entry->get().destination, (expected_uri));                 \
    EXPECT_EQ(__ref_entry->get().base, (expected_base));                       \
    EXPECT_EQ(__ref_entry->get().fragment, (expected_fragment));               \
    EXPECT_EQ(__ref_entry->get().original, (expected_original));               \
  }

#define EXPECT_STATIC_REFERENCE(frame, expected_pointer, expected_uri,         \
                                expected_base, expected_fragment,              \
                                expected_original)                             \
  EXPECT_REFERENCE(frame, sourcemeta::blaze::SchemaReferenceType::Static,      \
                   expected_pointer, expected_uri, expected_base,              \
                   expected_fragment, expected_original)

TEST(to_json_empty) {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  const auto result{frame.to_json(sourcemeta::blaze::schema_resolver)};
  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "mode": "references",
    "locations": {
      "static": {},
      "dynamic": {}
    },
    "references": []
  })JSON");

  EXPECT_EQ(result, expected);
}

TEST(to_json_mode_references_with_tracking) {
  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "bar"
      },
      "bar": {
        "id": "bar",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON",
                               document, std::ref(tracker));

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto result{frame.to_json(sourcemeta::blaze::schema_resolver, tracker)};

  const auto expected = sourcemeta::core::parse_json(R"JSON(
  {
    "mode": "references",
    "locations": {
      "static": {
        "https://www.sourcemeta.com/bar": {
          "parent": "",
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": [ 8, 7, 12, 7 ],
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": true,
          "hasReferencesThrough": true,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/bar#/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": [ 10, 9, 10, 60 ],
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/bar#/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": [ 9, 9, 9, 19 ],
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/bar#/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": [ 11, 9, 11, 24 ],
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test": {
          "parent": null,
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "",
          "position": [ 1, 1, 14, 3 ],
          "relativePointer": "",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": true,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/$id": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$id",
          "position": [ 2, 5, 2, 44 ],
          "relativePointer": "/$id",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/$schema": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$schema",
          "position": [ 3, 5, 3, 61 ],
          "relativePointer": "/$schema",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/properties": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties",
          "position": [ 4, 5, 13, 5 ],
          "relativePointer": "/properties",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": true,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": [ 8, 7, 12, 7 ],
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": true,
          "hasReferencesThrough": true,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": [ 10, 9, 10, 60 ],
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": [ 9, 9, 9, 19 ],
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": [ 11, 9, 11, 24 ],
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/foo": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo",
          "position": [ 5, 7, 7, 7 ],
          "relativePointer": "/properties/foo",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/foo/$ref": {
          "parent": "/properties/foo",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo/$ref",
          "position": [ 6, 9, 6, 21 ],
          "relativePointer": "/properties/foo/$ref",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        }
      },
      "dynamic": {}
    },
    "references": [
      {
        "type": "static",
        "origin": "/$schema",
        "position": [ 3, 5, 3, 61 ],
        "original": "https://json-schema.org/draft/2020-12/schema",
        "destination": "https://json-schema.org/draft/2020-12/schema",
        "base": "https://json-schema.org/draft/2020-12/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/bar/$schema",
        "position": [ 10, 9, 10, 60 ],
        "original": "http://json-schema.org/draft-04/schema#",
        "destination": "http://json-schema.org/draft-04/schema",
        "base": "http://json-schema.org/draft-04/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/foo/$ref",
        "position": [ 6, 9, 6, 21 ],
        "original": "bar",
        "destination": "https://www.sourcemeta.com/bar",
        "base": "https://www.sourcemeta.com/bar",
        "fragment": null
      }
    ]
  }
  )JSON");

  EXPECT_EQ(result, expected);
}

TEST(to_json_mode_references_with_tracking_empty) {
  sourcemeta::core::PointerPositionTracker tracker;

  // Note we purposely don't pass the tracker to the document
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://www.sourcemeta.com/test",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": {
      "foo": {
        "$ref": "bar"
      },
      "bar": {
        "id": "bar",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  const auto result{frame.to_json(sourcemeta::blaze::schema_resolver, tracker)};

  const auto expected = sourcemeta::core::parse_json(R"JSON(
  {
    "mode": "references",
    "locations": {
      "static": {
        "https://www.sourcemeta.com/bar": {
          "parent": "",
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": true,
          "hasReferencesThrough": true,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/bar#/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/bar#/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/bar#/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test": {
          "parent": null,
          "type": "resource",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "",
          "position": null,
          "relativePointer": "",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": true,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/$id": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$id",
          "position": null,
          "relativePointer": "/$id",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/$schema": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/properties": {
          "parent": "",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties",
          "position": null,
          "relativePointer": "/properties",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": true,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar",
          "position": null,
          "relativePointer": "",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": true,
          "hasReferencesThrough": true,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar/$schema": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/$schema",
          "position": null,
          "relativePointer": "/$schema",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar/id": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/id",
          "position": null,
          "relativePointer": "/id",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/bar/type": {
          "parent": "/properties/bar",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/bar",
          "pointer": "/properties/bar/type",
          "position": null,
          "relativePointer": "/type",
          "dialect": "http://json-schema.org/draft-04/schema#",
          "baseDialect": "http://json-schema.org/draft-04/schema#",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "http://json-schema.org/draft-04/schema#": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/foo": {
          "parent": "",
          "type": "subschema",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo",
          "position": null,
          "relativePointer": "/properties/foo",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        },
        "https://www.sourcemeta.com/test#/properties/foo/$ref": {
          "parent": "/properties/foo",
          "type": "pointer",
          "root": "https://www.sourcemeta.com/test",
          "base": "https://www.sourcemeta.com/test",
          "pointer": "/properties/foo/$ref",
          "position": null,
          "relativePointer": "/properties/foo/$ref",
          "dialect": "https://json-schema.org/draft/2020-12/schema",
          "baseDialect": "https://json-schema.org/draft/2020-12/schema",
          "propertyName": false,
          "orphan": false,
          "hasReferencesTo": false,
          "hasReferencesThrough": false,
          "vocabularies": {
            "https://json-schema.org/draft/2020-12/vocab/core": true,
            "https://json-schema.org/draft/2020-12/vocab/applicator": true,
            "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
            "https://json-schema.org/draft/2020-12/vocab/validation": true,
            "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
            "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
            "https://json-schema.org/draft/2020-12/vocab/content": true
          }
        }
      },
      "dynamic": {}
    },
    "references": [
      {
        "type": "static",
        "origin": "/$schema",
        "position": null,
        "original": "https://json-schema.org/draft/2020-12/schema",
        "destination": "https://json-schema.org/draft/2020-12/schema",
        "base": "https://json-schema.org/draft/2020-12/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/bar/$schema",
        "position": null,
        "original": "http://json-schema.org/draft-04/schema#",
        "destination": "http://json-schema.org/draft-04/schema",
        "base": "http://json-schema.org/draft-04/schema",
        "fragment": null
      },
      {
        "type": "static",
        "origin": "/properties/foo/$ref",
        "position": null,
        "original": "bar",
        "destination": "https://www.sourcemeta.com/bar",
        "base": "https://www.sourcemeta.com/bar",
        "fragment": null
      }
    ]
  }
  )JSON");

  EXPECT_EQ(result, expected);
}

TEST(reuse_embedded_custom_metaschema_implicit_reset) {
  const sourcemeta::core::JSON document_a =
      sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::core::JSON document_b =
      sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true
        },
        "type": "object"
      }
    }
  })JSON");

  // Reusing a single frame across two analyses of documents that embed the
  // same custom meta-schema identifier with a different definition must
  // reflect the second document, as a new analysis resets the internal state
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document_a, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);
  frame.analyse(document_b, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 19);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/schema", "https://example.com/schema", "",
      "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/meta", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/schema#/$schema",
                              "https://example.com/schema", "/$schema",
                              "https://example.com/meta", JSON_Schema_2020_12,
                              "https://example.com/schema", "/$schema", "",
                              false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/$id", "https://example.com/schema",
      "/$id", "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/type", "https://example.com/schema",
      "/type", "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "/type", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/$defs", "https://example.com/schema",
      "/$defs", "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/schema#/$defs/https:~1~1example.com~1meta",
      "https://example.com/schema", "/$defs/https:~1~1example.com~1meta",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/$id",
      "https://example.com/schema", "/$defs/https:~1~1example.com~1meta/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$id", "/$defs/https:~1~1example.com~1meta",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/$schema",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$schema",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/"
      "$vocabulary",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$vocabulary",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/"
      "$vocabulary/https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/"
      "$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/type",
      "https://example.com/schema", "/$defs/https:~1~1example.com~1meta/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/type", "/$defs/https:~1~1example.com~1meta",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/$id", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$id", "/$defs/https:~1~1example.com~1meta",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/$schema", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$schema",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/$vocabulary",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$vocabulary",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/meta#/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/meta#/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/type", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/type", "/$defs/https:~1~1example.com~1meta",
      false, true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(frame, "/$schema", "https://example.com/meta",
                          "https://example.com/meta", std::nullopt,
                          "https://example.com/meta");
  EXPECT_STATIC_REFERENCE(frame, "/$defs/https:~1~1example.com~1meta/$schema",
                          "https://json-schema.org/draft/2020-12/schema",
                          "https://json-schema.org/draft/2020-12/schema",
                          std::nullopt,
                          "https://json-schema.org/draft/2020-12/schema");

  // SchemaVocabularies

  const auto root_location{frame.traverse("https://example.com/schema")};
  EXPECT_TRUE(root_location.has_value());
  const auto root_vocabularies{frame.vocabularies(
      root_location->get(), sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(root_vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Applicator);
  EXPECT_FALSE(
      root_vocabularies.contains(sourcemeta::blaze::SchemaVocabularies::Known::
                                     JSON_Schema_2020_12_Validation));
}

TEST(reuse_embedded_custom_metaschema_explicit_reset) {
  const sourcemeta::core::JSON document_a =
      sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true
        },
        "type": "object"
      }
    }
  })JSON");

  const sourcemeta::core::JSON document_b =
      sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://example.com/meta",
    "$id": "https://example.com/schema",
    "type": "string",
    "$defs": {
      "https://example.com/meta": {
        "$id": "https://example.com/meta",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true
        },
        "type": "object"
      }
    }
  })JSON");

  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References};
  frame.analyse(document_a, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  // An explicit reset must clear every trace of the first analysis, including
  // the cache of meta-schemas embedded in the previous document
  frame.reset();

  EXPECT_TRUE(frame.empty());
  EXPECT_EQ(frame.locations().size(), 0);
  EXPECT_EQ(frame.references().size(), 0);

  frame.analyse(document_b, sourcemeta::blaze::schema_walker,
                sourcemeta::blaze::schema_resolver);

  EXPECT_EQ(frame.locations().size(), 19);

  // Resources

  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/schema", "https://example.com/schema", "",
      "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "", std::nullopt, false, false);
  EXPECT_FRAME_STATIC_RESOURCE(
      frame, "https://example.com/meta", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "", "", false, true);

  // JSON Pointers

  EXPECT_FRAME_STATIC_POINTER(frame, "https://example.com/schema#/$schema",
                              "https://example.com/schema", "/$schema",
                              "https://example.com/meta", JSON_Schema_2020_12,
                              "https://example.com/schema", "/$schema", "",
                              false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/$id", "https://example.com/schema",
      "/$id", "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "/$id", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/type", "https://example.com/schema",
      "/type", "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "/type", "", false, false);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/schema#/$defs", "https://example.com/schema",
      "/$defs", "https://example.com/meta", JSON_Schema_2020_12,
      "https://example.com/schema", "/$defs", "", false, false);
  EXPECT_FRAME_STATIC_SUBSCHEMA(
      frame, "https://example.com/schema#/$defs/https:~1~1example.com~1meta",
      "https://example.com/schema", "/$defs/https:~1~1example.com~1meta",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "", "", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/$id",
      "https://example.com/schema", "/$defs/https:~1~1example.com~1meta/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$id", "/$defs/https:~1~1example.com~1meta",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/$schema",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$schema",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/"
      "$vocabulary",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$vocabulary",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/"
      "$vocabulary/https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/"
      "$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/schema#/$defs/https:~1~1example.com~1meta/type",
      "https://example.com/schema", "/$defs/https:~1~1example.com~1meta/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/type", "/$defs/https:~1~1example.com~1meta",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/$id", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$id",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$id", "/$defs/https:~1~1example.com~1meta",
      false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/$schema", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$schema",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$schema",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/$vocabulary",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/$vocabulary",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/meta#/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/https:~1~1json-schema.org~1draft~12020-12~1vocab~1core",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame,
      "https://example.com/meta#/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta",
      "/$vocabulary/"
      "https:~1~1json-schema.org~1draft~12020-12~1vocab~1applicator",
      "/$defs/https:~1~1example.com~1meta", false, true);
  EXPECT_FRAME_STATIC_POINTER(
      frame, "https://example.com/meta#/type", "https://example.com/schema",
      "/$defs/https:~1~1example.com~1meta/type",
      "https://json-schema.org/draft/2020-12/schema", JSON_Schema_2020_12,
      "https://example.com/meta", "/type", "/$defs/https:~1~1example.com~1meta",
      false, true);

  // References

  EXPECT_EQ(frame.references().size(), 2);

  EXPECT_STATIC_REFERENCE(frame, "/$schema", "https://example.com/meta",
                          "https://example.com/meta", std::nullopt,
                          "https://example.com/meta");
  EXPECT_STATIC_REFERENCE(frame, "/$defs/https:~1~1example.com~1meta/$schema",
                          "https://json-schema.org/draft/2020-12/schema",
                          "https://json-schema.org/draft/2020-12/schema",
                          std::nullopt,
                          "https://json-schema.org/draft/2020-12/schema");

  // SchemaVocabularies

  const auto root_location{frame.traverse("https://example.com/schema")};
  EXPECT_TRUE(root_location.has_value());
  const auto root_vocabularies{frame.vocabularies(
      root_location->get(), sourcemeta::blaze::schema_resolver)};
  EXPECT_EQ(root_vocabularies.size(), 2);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Core);
  EXPECT_VOCABULARY_REQUIRED(root_vocabularies, JSON_Schema_2020_12_Applicator);
  EXPECT_FALSE(
      root_vocabularies.contains(sourcemeta::blaze::SchemaVocabularies::Known::
                                     JSON_Schema_2020_12_Validation));
}

TEST(root_location_without_analysis) {
  sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::Root};

  EXPECT_TRUE(frame.empty());
  EXPECT_TRUE(frame.root().empty());
  EXPECT_EQ(frame.locations().size(), 0);
  EXPECT_EQ(frame.references().size(), 0);
  EXPECT_FALSE(frame.root_location().has_value());
}
