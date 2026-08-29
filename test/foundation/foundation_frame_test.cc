#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <cstddef>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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
  EXPECT_TRUE((frame).location((expected_type), (reference)).has_value());     \
  EXPECT_EQ((frame).root(), (root_id));                                        \
  EXPECT_EQ(                                                                   \
      sourcemeta::core::to_string((frame)                                      \
                                      .location((expected_type), (reference))  \
                                      .value()                                 \
                                      .get()                                   \
                                      .pointer),                               \
      (expected_pointer));                                                     \
  EXPECT_EQ(                                                                   \
      (frame).location((expected_type), (reference)).value().get().dialect,    \
      (expected_dialect));                                                     \
  EXPECT_EQ((frame).location((expected_type), (reference)).value().get().base, \
            (expected_base));                                                  \
  EXPECT_TRUE((frame)                                                          \
                  .traverse((frame)                                            \
                                .location((expected_type), (reference))        \
                                .value()                                       \
                                .get()                                         \
                                .base)                                         \
                  .has_value());                                               \
  EXPECT_EQ((frame)                                                            \
                .location((expected_type), (reference))                        \
                .value()                                                       \
                .get()                                                         \
                .base_dialect,                                                 \
            sourcemeta::blaze::SchemaBaseDialect::expected_base_dialect);      \
  EXPECT_EQ(                                                                   \
      sourcemeta::core::to_string((frame).relative_instance_location(          \
          (frame).location((expected_type), (reference)).value().get())),      \
      (expected_relative_pointer));                                            \
  EXPECT_OPTIONAL_POINTER(                                                     \
      (frame).location((expected_type), (reference)).value().get().parent,     \
      expected_parent);                                                        \
  EXPECT_EQ((frame)                                                            \
                .location((expected_type), (reference))                        \
                .value()                                                       \
                .get()                                                         \
                .property_name,                                                \
            (expected_property_name));                                         \
  EXPECT_EQ(                                                                   \
      (frame).location((expected_type), (reference)).value().get().orphan,     \
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
  EXPECT_EQ((frame)                                                            \
                .location(sourcemeta::blaze::SchemaReferenceType::Static,      \
                          (reference))                                         \
                .value()                                                       \
                .get()                                                         \
                .type,                                                         \
            sourcemeta::blaze::SchemaFrame::LocationType::Resource);

#define EXPECT_FRAME_STATIC_POINTER(                                           \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME_STATIC(frame, reference, root_id, expected_pointer,             \
                      expected_dialect, expected_base_dialect, expected_base,  \
                      expected_relative_pointer, expected_parent,              \
                      expected_property_name, expected_orphan)                 \
  EXPECT_EQ((frame)                                                            \
                .location(sourcemeta::blaze::SchemaReferenceType::Static,      \
                          (reference))                                         \
                .value()                                                       \
                .get()                                                         \
                .type,                                                         \
            sourcemeta::blaze::SchemaFrame::LocationType::Pointer);

#define EXPECT_FRAME_STATIC_SUBSCHEMA(                                         \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME_STATIC(frame, reference, root_id, expected_pointer,             \
                      expected_dialect, expected_base_dialect, expected_base,  \
                      expected_relative_pointer, expected_parent,              \
                      expected_property_name, expected_orphan)                 \
  EXPECT_EQ((frame)                                                            \
                .location(sourcemeta::blaze::SchemaReferenceType::Static,      \
                          (reference))                                         \
                .value()                                                       \
                .get()                                                         \
                .type,                                                         \
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
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

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
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

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

TEST(embedded_custom_metaschema_across_two_frames) {
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

  [[maybe_unused]] const sourcemeta::blaze::SchemaFrame frame_a{
      sourcemeta::blaze::SchemaFrame::Mode::References, document_a,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};
  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document_b,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_EQ(frame.location_count(), 19);

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

  EXPECT_EQ(frame.reference_count(), 2);

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

TEST(accessors_location_count) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_EQ(frame.location_count(), 28);
}

TEST(accessors_reference_count) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_EQ(frame.reference_count(), 4);
}

TEST(accessors_has_dynamic_references) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "a": { "$id": "one", "$dynamicAnchor": "shared" },
      "b": { "$id": "two", "$dynamicAnchor": "shared" }
    },
    "properties": { "value": { "$dynamicRef": "#shared" } }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_TRUE(frame.has_dynamic_references());
  EXPECT_TRUE(frame.any_reference(
      [](const sourcemeta::blaze::SchemaReferenceType type,
         const sourcemeta::core::WeakPointer &,
         const sourcemeta::blaze::SchemaFrame::Reference &) {
        return type == sourcemeta::blaze::SchemaReferenceType::Dynamic;
      }));
}

TEST(accessors_has_dynamic_references_after_static_rewrite) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": { "a": { "$dynamicAnchor": "only" } },
    "properties": { "value": { "$dynamicRef": "#only" } }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_FALSE(frame.has_dynamic_references());
}

TEST(accessors_has_dynamic_references_without_any) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "properties": { "one": { "$ref": "#" } }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_FALSE(frame.has_dynamic_references());
}

TEST(accessors_location_by_uri) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const auto result{
      frame.location(sourcemeta::blaze::SchemaReferenceType::Static,
                     "https://example.com/schema#static-anchor")};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(sourcemeta::core::to_string(result.value().get().pointer),
            "/$defs/foo");
  EXPECT_EQ(result.value().get().type,
            sourcemeta::blaze::SchemaFrame::LocationType::Anchor);
}

TEST(accessors_location_by_uri_wrong_type) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_FALSE(frame
                   .location(sourcemeta::blaze::SchemaReferenceType::Dynamic,
                             "https://example.com/schema#static-anchor")
                   .has_value());
}

TEST(accessors_location_by_uri_unknown) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_FALSE(frame
                   .location(sourcemeta::blaze::SchemaReferenceType::Static,
                             "https://example.com/nowhere")
                   .has_value());
}

TEST(accessors_for_each_subschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  std::vector<std::string> pointers;
  frame.for_each_subschema(
      [&pointers](const sourcemeta::blaze::SchemaFrame::Location &location) {
        pointers.push_back(sourcemeta::core::to_string(location.pointer));
      });

  EXPECT_EQ(pointers.size(), 9);
  EXPECT_EQ(pointers.at(0), "/$defs/baz");
  EXPECT_EQ(pointers.at(1), "/$defs/baz/properties/deep");
  EXPECT_EQ(pointers.at(2), "");
  EXPECT_EQ(pointers.at(3), "/$defs/bar");
  EXPECT_EQ(pointers.at(4), "/$defs/baz");
  EXPECT_EQ(pointers.at(5), "/$defs/baz/properties/deep");
  EXPECT_EQ(pointers.at(6), "/$defs/foo");
  EXPECT_EQ(pointers.at(7), "/properties/one");
  EXPECT_EQ(pointers.at(8), "/properties/two");
}

TEST(accessors_for_each_subschema_under) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const sourcemeta::core::Pointer base{"$defs"};
  std::vector<std::string> pointers;
  frame.for_each_subschema_under(
      sourcemeta::core::to_weak_pointer(base),
      [&pointers](const sourcemeta::blaze::SchemaFrame::Location &location) {
        pointers.push_back(sourcemeta::core::to_string(location.pointer));
      });

  EXPECT_EQ(pointers.size(), 6);
  EXPECT_EQ(pointers.at(0), "/$defs/baz");
  EXPECT_EQ(pointers.at(1), "/$defs/baz/properties/deep");
  EXPECT_EQ(pointers.at(2), "/$defs/bar");
  EXPECT_EQ(pointers.at(3), "/$defs/baz");
  EXPECT_EQ(pointers.at(4), "/$defs/baz/properties/deep");
  EXPECT_EQ(pointers.at(5), "/$defs/foo");
}

TEST(accessors_any_subschema) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_TRUE(frame.any_subschema(
      [](const sourcemeta::blaze::SchemaFrame::Location &location) {
        return sourcemeta::core::to_string(location.pointer) ==
               "/properties/two";
      }));
  EXPECT_FALSE(frame.any_subschema(
      [](const sourcemeta::blaze::SchemaFrame::Location &location) {
        return sourcemeta::core::to_string(location.pointer) == "/nowhere";
      }));
}

TEST(accessors_any_subschema_under) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const sourcemeta::core::Pointer properties{"properties"};
  const sourcemeta::core::Pointer definitions{"$defs"};
  EXPECT_TRUE(frame.any_subschema_under(
      sourcemeta::core::to_weak_pointer(properties),
      [](const sourcemeta::blaze::SchemaFrame::Location &location) {
        return sourcemeta::core::to_string(location.pointer) ==
               "/properties/one";
      }));
  EXPECT_FALSE(frame.any_subschema_under(
      sourcemeta::core::to_weak_pointer(definitions),
      [](const sourcemeta::blaze::SchemaFrame::Location &location) {
        return sourcemeta::core::to_string(location.pointer) ==
               "/properties/one";
      }));
}

TEST(accessors_for_each_anchor_static) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  std::vector<std::string> uris;
  frame.for_each_anchor(
      sourcemeta::blaze::SchemaReferenceType::Static,
      [&uris](const std::string_view uri,
              const sourcemeta::blaze::SchemaFrame::Location &) {
        uris.emplace_back(uri);
      });

  EXPECT_EQ(uris.size(), 2);
  EXPECT_EQ(uris.at(0), "https://example.com/schema#dynamic-anchor");
  EXPECT_EQ(uris.at(1), "https://example.com/schema#static-anchor");
}

TEST(accessors_for_each_anchor_dynamic) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  std::vector<std::string> uris;
  std::vector<std::string> pointers;
  frame.for_each_anchor(
      sourcemeta::blaze::SchemaReferenceType::Dynamic,
      [&uris,
       &pointers](const std::string_view uri,
                  const sourcemeta::blaze::SchemaFrame::Location &location) {
        uris.emplace_back(uri);
        pointers.push_back(sourcemeta::core::to_string(location.pointer));
      });

  EXPECT_EQ(uris.size(), 1);
  EXPECT_EQ(uris.at(0), "https://example.com/schema#dynamic-anchor");
  EXPECT_EQ(pointers.size(), 1);
  EXPECT_EQ(pointers.at(0), "/$defs/bar");
}

TEST(accessors_any_anchor) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_TRUE(frame.any_anchor(
      sourcemeta::blaze::SchemaReferenceType::Dynamic,
      [](const std::string_view uri,
         const sourcemeta::blaze::SchemaFrame::Location &) {
        return uri == "https://example.com/schema#dynamic-anchor";
      }));
  EXPECT_FALSE(frame.any_anchor(
      sourcemeta::blaze::SchemaReferenceType::Dynamic,
      [](const std::string_view uri,
         const sourcemeta::blaze::SchemaFrame::Location &) {
        return uri == "https://example.com/schema#static-anchor";
      }));
  EXPECT_TRUE(frame.any_anchor(
      sourcemeta::blaze::SchemaReferenceType::Static,
      [](const std::string_view uri,
         const sourcemeta::blaze::SchemaFrame::Location &) {
        return uri == "https://example.com/schema#static-anchor";
      }));
}

TEST(accessors_for_each_resource) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  std::vector<std::string> uris;
  std::vector<std::string> pointers;
  frame.for_each_resource(
      [&uris,
       &pointers](const std::string_view uri,
                  const sourcemeta::blaze::SchemaFrame::Location &location) {
        uris.emplace_back(uri);
        pointers.push_back(sourcemeta::core::to_string(location.pointer));
      });

  EXPECT_EQ(uris.size(), 2);
  EXPECT_EQ(uris.at(0), "https://example.com/nested");
  EXPECT_EQ(pointers.at(0), "/$defs/baz");
  EXPECT_EQ(uris.at(1), "https://example.com/schema");
  EXPECT_EQ(pointers.at(1), "");
}

TEST(accessors_for_each_location) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  std::size_t visited{0};
  std::size_t dynamic{0};
  frame.for_each_location(
      [&visited, &dynamic](const sourcemeta::blaze::SchemaReferenceType type,
                           const std::string_view,
                           const sourcemeta::blaze::SchemaFrame::Location &) {
        visited += 1;
        if (type == sourcemeta::blaze::SchemaReferenceType::Dynamic) {
          dynamic += 1;
        }
      });

  EXPECT_EQ(visited, frame.location_count());
  EXPECT_EQ(visited, 28);
  EXPECT_EQ(dynamic, 1);
}

TEST(accessors_any_location) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_TRUE(
      frame.any_location([](const sourcemeta::blaze::SchemaReferenceType,
                            const std::string_view uri,
                            const sourcemeta::blaze::SchemaFrame::Location &) {
        return uri == "https://example.com/nested#/properties/deep";
      }));
  EXPECT_FALSE(
      frame.any_location([](const sourcemeta::blaze::SchemaReferenceType,
                            const std::string_view uri,
                            const sourcemeta::blaze::SchemaFrame::Location &) {
        return uri == "https://example.com/nowhere";
      }));
}

TEST(accessors_for_each_reference) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  std::vector<std::string> origins;
  std::vector<sourcemeta::blaze::SchemaReferenceType> types;
  frame.for_each_reference(
      [&origins, &types](const sourcemeta::blaze::SchemaReferenceType type,
                         const sourcemeta::core::WeakPointer &origin,
                         const sourcemeta::blaze::SchemaFrame::Reference &) {
        origins.push_back(sourcemeta::core::to_string(origin));
        types.push_back(type);
      });

  EXPECT_EQ(origins.size(), 4);
  EXPECT_EQ(types.size(), 4);
  std::size_t dynamic_references{0};
  for (const auto type : types) {
    if (type == sourcemeta::blaze::SchemaReferenceType::Dynamic) {
      dynamic_references += 1;
    }
  }

  EXPECT_EQ(dynamic_references, 0);
  EXPECT_FALSE(frame.has_dynamic_references());
  EXPECT_EQ(origins.at(0), "/$defs/baz/properties/deep/$ref");
  EXPECT_EQ(origins.at(1), "/$schema");
  EXPECT_EQ(origins.at(2), "/properties/one/$ref");
  EXPECT_EQ(origins.at(3), "/properties/two/$dynamicRef");
}

TEST(accessors_any_reference) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  EXPECT_TRUE(frame.any_reference(
      [](const sourcemeta::blaze::SchemaReferenceType,
         const sourcemeta::core::WeakPointer &origin,
         const sourcemeta::blaze::SchemaFrame::Reference &) {
        return sourcemeta::core::to_string(origin) == "/properties/one/$ref";
      }));
  EXPECT_FALSE(frame.any_reference(
      [](const sourcemeta::blaze::SchemaReferenceType,
         const sourcemeta::core::WeakPointer &,
         const sourcemeta::blaze::SchemaFrame::Reference &entry) {
        return entry.destination == "https://example.com/nowhere";
      }));
}

TEST(accessors_for_each_reference_from) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const sourcemeta::core::Pointer properties{"properties"};
  std::vector<std::string> origins;
  frame.for_each_reference_from(
      sourcemeta::core::to_weak_pointer(properties),
      [&origins](const sourcemeta::blaze::SchemaReferenceType,
                 const sourcemeta::core::WeakPointer &origin,
                 const sourcemeta::blaze::SchemaFrame::Reference &) {
        origins.push_back(sourcemeta::core::to_string(origin));
      });

  EXPECT_EQ(origins.size(), 2);
  EXPECT_EQ(origins.at(0), "/properties/one/$ref");
  EXPECT_EQ(origins.at(1), "/properties/two/$dynamicRef");
}

TEST(accessors_any_reference_from) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const sourcemeta::core::Pointer definitions{"$defs"};
  const sourcemeta::core::Pointer nowhere{"nowhere"};
  EXPECT_TRUE(frame.any_reference_from(
      sourcemeta::core::to_weak_pointer(definitions),
      [](const sourcemeta::blaze::SchemaReferenceType,
         const sourcemeta::core::WeakPointer &,
         const sourcemeta::blaze::SchemaFrame::Reference &) { return true; }));
  EXPECT_FALSE(frame.any_reference_from(
      sourcemeta::core::to_weak_pointer(nowhere),
      [](const sourcemeta::blaze::SchemaReferenceType,
         const sourcemeta::core::WeakPointer &,
         const sourcemeta::blaze::SchemaFrame::Reference &) { return true; }));
}

TEST(accessors_for_each_reference_into) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const sourcemeta::core::Pointer target{"$defs", "foo"};
  std::vector<std::string> origins;
  frame.for_each_reference_into(
      sourcemeta::core::to_weak_pointer(target),
      [&origins](const sourcemeta::blaze::SchemaReferenceType,
                 const sourcemeta::core::WeakPointer &origin,
                 const sourcemeta::blaze::SchemaFrame::Reference &) {
        origins.push_back(sourcemeta::core::to_string(origin));
      });

  EXPECT_EQ(origins.size(), 2);
  EXPECT_EQ(origins.at(0), "/$defs/baz/properties/deep/$ref");
  EXPECT_EQ(origins.at(1), "/properties/one/$ref");
}

TEST(accessors_any_reference_into) {
  const sourcemeta::core::JSON document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/schema",
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": {
      "foo": { "$anchor": "static-anchor", "type": "string" },
      "bar": { "$dynamicAnchor": "dynamic-anchor", "type": "number" },
      "baz": {
        "$id": "nested",
        "properties": {
          "deep": { "$ref": "https://example.com/schema#/$defs/foo" }
        }
      }
    },
    "properties": {
      "one": { "$ref": "#/$defs/foo" },
      "two": { "$dynamicRef": "#dynamic-anchor" }
    }
  })JSON");

  const sourcemeta::blaze::SchemaFrame frame{
      sourcemeta::blaze::SchemaFrame::Mode::References, document,
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver};

  const sourcemeta::core::Pointer bar{"$defs", "bar"};
  const sourcemeta::core::Pointer one{"properties", "one"};
  EXPECT_TRUE(frame.any_reference_into(
      sourcemeta::core::to_weak_pointer(bar),
      [](const sourcemeta::blaze::SchemaReferenceType,
         const sourcemeta::core::WeakPointer &origin,
         const sourcemeta::blaze::SchemaFrame::Reference &) {
        return sourcemeta::core::to_string(origin) ==
               "/properties/two/$dynamicRef";
      }));
  EXPECT_FALSE(frame.any_reference_into(
      sourcemeta::core::to_weak_pointer(one),
      [](const sourcemeta::blaze::SchemaReferenceType,
         const sourcemeta::core::WeakPointer &,
         const sourcemeta::blaze::SchemaFrame::Reference &) { return true; }));
}
