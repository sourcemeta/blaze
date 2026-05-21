#ifndef SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_FOUNDATION_TEST_UTILS_H_

#include <cassert>
#include <sstream>
#include <tuple>
#include <variant>
#include <vector>

#define EXPECT_VOCABULARY_KNOWN(vocabulary_value, expected_known)              \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::Vocabularies::Known>(  \
      (vocabulary_value)));                                                    \
  EXPECT_EQ(                                                                   \
      std::get<sourcemeta::blaze::Vocabularies::Known>((vocabulary_value)),    \
      sourcemeta::blaze::Vocabularies::Known::expected_known)

#define EXPECT_VOCABULARY_REQUIRED(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(sourcemeta::blaze::Vocabularies::Known::expected_known));  \
  EXPECT_TRUE((vocabularies)                                                   \
                  .get(sourcemeta::blaze::Vocabularies::Known::expected_known) \
                  .value())

#define EXPECT_VOCABULARY_OPTIONAL(vocabularies, expected_known)               \
  EXPECT_TRUE(                                                                 \
      (vocabularies)                                                           \
          .contains(sourcemeta::blaze::Vocabularies::Known::expected_known));  \
  EXPECT_FALSE(                                                                \
      (vocabularies)                                                           \
          .get(sourcemeta::blaze::Vocabularies::Known::expected_known)         \
          .value())

#define EXPECT_OPTIONAL_POINTER(optional_value, expected_optional)             \
  if (std::optional<std::string>{expected_optional}.has_value()) {             \
    EXPECT_TRUE((optional_value).has_value());                                 \
    EXPECT_EQ(sourcemeta::core::to_string((optional_value).value()),           \
              std::optional<std::string>{expected_optional}.value());          \
  } else {                                                                     \
    EXPECT_FALSE((optional_value).has_value());                                \
  }

#define EXPECT_POINTER_TEMPLATE(pointer, expected)                             \
  {                                                                            \
    std::ostringstream stream;                                                 \
    sourcemeta::core::stringify((pointer), stream);                            \
    EXPECT_EQ(stream.str(), (expected));                                       \
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

#define EXPECT_FRAME_STATIC_ANCHOR(                                            \
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
      sourcemeta::blaze::SchemaFrame::LocationType::Anchor);

#define EXPECT_FRAME_DYNAMIC_ANCHOR(                                           \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME_DYNAMIC(frame, reference, root_id, expected_pointer,            \
                       expected_dialect, expected_base_dialect, expected_base, \
                       expected_relative_pointer, expected_parent,             \
                       expected_property_name, expected_orphan)                \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Dynamic, (reference)})  \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Anchor);

#define EXPECT_FRAME_DYNAMIC(                                                  \
    frame, reference, root_id, expected_pointer, expected_dialect,             \
    expected_base_dialect, expected_base, expected_relative_pointer,           \
    expected_parent, expected_property_name, expected_orphan)                  \
  EXPECT_FRAME(frame, sourcemeta::blaze::SchemaReferenceType::Dynamic,         \
               reference, root_id, expected_pointer, expected_dialect,         \
               expected_base_dialect, expected_base,                           \
               expected_relative_pointer, expected_parent,                     \
               expected_property_name, expected_orphan)

#define __EXPECT_ANONYMOUS_FRAME(frame, expected_type, reference,              \
                                 expected_pointer, expected_dialect,           \
                                 expected_base_dialect, expected_parent,       \
                                 expected_property_name, expected_orphan)      \
  EXPECT_TRUE((frame).locations().contains({(expected_type), (reference)}));   \
  EXPECT_TRUE((frame).root().empty());                                         \
  EXPECT_EQ(                                                                   \
      sourcemeta::core::to_string(                                             \
          (frame).locations().at({(expected_type), (reference)}).pointer),     \
      (expected_pointer));                                                     \
  EXPECT_EQ((frame).locations().at({(expected_type), (reference)}).dialect,    \
            (expected_dialect));                                               \
  EXPECT_EQ(                                                                   \
      (frame).locations().at({(expected_type), (reference)}).base_dialect,     \
      sourcemeta::blaze::SchemaBaseDialect::expected_base_dialect);            \
  EXPECT_OPTIONAL_POINTER(                                                     \
      (frame).locations().at({(expected_type), (reference)}).parent,           \
      expected_parent);                                                        \
  EXPECT_EQ(                                                                   \
      (frame).locations().at({(expected_type), (reference)}).property_name,    \
      (expected_property_name));                                               \
  EXPECT_EQ((frame).locations().at({(expected_type), (reference)}).orphan,     \
            (expected_orphan));

#define EXPECT_ANONYMOUS_FRAME_STATIC(frame, reference, expected_pointer,      \
                                      expected_dialect, expected_base_dialect, \
                                      expected_parent, expected_property_name, \
                                      expected_orphan)                         \
  __EXPECT_ANONYMOUS_FRAME(                                                    \
      frame, sourcemeta::blaze::SchemaReferenceType::Static, reference,        \
      expected_pointer, expected_dialect, expected_base_dialect,               \
      expected_parent, expected_property_name, expected_orphan)

#define EXPECT_ANONYMOUS_FRAME_STATIC_RESOURCE(                                \
    frame, reference, expected_pointer, expected_dialect,                      \
    expected_base_dialect, expected_parent, expected_property_name,            \
    expected_orphan)                                                           \
  __EXPECT_ANONYMOUS_FRAME(                                                    \
      frame, sourcemeta::blaze::SchemaReferenceType::Static, reference,        \
      expected_pointer, expected_dialect, expected_base_dialect,               \
      expected_parent, expected_property_name, expected_orphan)                \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Resource);

#define EXPECT_ANONYMOUS_FRAME_STATIC_POINTER(                                 \
    frame, reference, expected_pointer, expected_dialect,                      \
    expected_base_dialect, expected_parent, expected_property_name,            \
    expected_orphan)                                                           \
  __EXPECT_ANONYMOUS_FRAME(                                                    \
      frame, sourcemeta::blaze::SchemaReferenceType::Static, reference,        \
      expected_pointer, expected_dialect, expected_base_dialect,               \
      expected_parent, expected_property_name, expected_orphan)                \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Pointer);

#define EXPECT_ANONYMOUS_FRAME_STATIC_SUBSCHEMA(                               \
    frame, reference, expected_pointer, expected_dialect,                      \
    expected_base_dialect, expected_parent, expected_property_name,            \
    expected_orphan)                                                           \
  __EXPECT_ANONYMOUS_FRAME(                                                    \
      frame, sourcemeta::blaze::SchemaReferenceType::Static, reference,        \
      expected_pointer, expected_dialect, expected_base_dialect,               \
      expected_parent, expected_property_name, expected_orphan)                \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Subschema);

#define EXPECT_ANONYMOUS_FRAME_STATIC_ANCHOR(                                  \
    frame, reference, expected_pointer, expected_dialect,                      \
    expected_base_dialect, expected_parent, expected_property_name,            \
    expected_orphan)                                                           \
  __EXPECT_ANONYMOUS_FRAME(                                                    \
      frame, sourcemeta::blaze::SchemaReferenceType::Static, reference,        \
      expected_pointer, expected_dialect, expected_base_dialect,               \
      expected_parent, expected_property_name, expected_orphan)                \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Static, (reference)})   \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Anchor);

#define EXPECT_ANONYMOUS_FRAME_DYNAMIC_ANCHOR(                                 \
    frame, reference, expected_pointer, expected_dialect,                      \
    expected_base_dialect, expected_parent, expected_property_name,            \
    expected_orphan)                                                           \
  __EXPECT_ANONYMOUS_FRAME(                                                    \
      frame, sourcemeta::blaze::SchemaReferenceType::Dynamic, reference,       \
      expected_pointer, expected_dialect, expected_base_dialect,               \
      expected_parent, expected_property_name, expected_orphan)                \
  EXPECT_EQ(                                                                   \
      (frame)                                                                  \
          .locations()                                                         \
          .at({sourcemeta::blaze::SchemaReferenceType::Dynamic, (reference)})  \
          .type,                                                               \
      sourcemeta::blaze::SchemaFrame::LocationType::Anchor);

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

#define EXPECT_DYNAMIC_REFERENCE(frame, expected_pointer, expected_uri,        \
                                 expected_base, expected_fragment,             \
                                 expected_original)                            \
  EXPECT_REFERENCE(frame, sourcemeta::blaze::SchemaReferenceType::Dynamic,     \
                   expected_pointer, expected_uri, expected_base,              \
                   expected_fragment, expected_original)

#define __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,        \
                              expected_parent_location, expected_dialect,      \
                              expected_base_dialect)                           \
  EXPECT_EQ(sourcemeta::core::to_string(entries.at(index).pointer),            \
            expected_schema_location);                                         \
  EXPECT_OPTIONAL_POINTER(entries.at(index).parent, expected_parent_location); \
  EXPECT_FALSE(entries.at(index).dialect.empty());                             \
  EXPECT_TRUE(entries.at(index).base_dialect.has_value());                     \
  EXPECT_EQ(entries.at(index).dialect, expected_dialect);                      \
  EXPECT_EQ(                                                                   \
      sourcemeta::blaze::to_string(entries.at(index).base_dialect.value()),    \
      expected_base_dialect);                                                  \
  EXPECT_FALSE(entries.at(index).vocabularies.empty());

#define EXPECT_WALKER_ENTRY_2020_12(entries, index, expected_schema_location,  \
                                    expected_parent_location)                  \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2020-12/schema",        \
                        "https://json-schema.org/draft/2020-12/schema");       \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_2020_12_ORPHAN(                                    \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2020-12/schema",        \
                        "https://json-schema.org/draft/2020-12/schema");       \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_2019_09(entries, index, expected_schema_location,  \
                                    expected_parent_location)                  \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2019-09/schema",        \
                        "https://json-schema.org/draft/2019-09/schema");       \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_2019_09_ORPHAN(                                    \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "https://json-schema.org/draft/2019-09/schema",        \
                        "https://json-schema.org/draft/2019-09/schema");       \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT7(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-07/schema#",             \
                        "http://json-schema.org/draft-07/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT7_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-07/schema#",             \
                        "http://json-schema.org/draft-07/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT6(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-06/schema#",             \
                        "http://json-schema.org/draft-06/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);                                      \
  EXPECT_FALSE(entries.at(index).property_name);

#define EXPECT_WALKER_ENTRY_DRAFT6_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-06/schema#",             \
                        "http://json-schema.org/draft-06/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);                                       \
  EXPECT_FALSE(entries.at(index).property_name);

#define EXPECT_WALKER_ENTRY_DRAFT6_PROPERTY_NAME(                              \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-06/schema#",             \
                        "http://json-schema.org/draft-06/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);                                      \
  EXPECT_TRUE(entries.at(index).property_name);

#define EXPECT_WALKER_ENTRY_DRAFT4(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-04/schema#",             \
                        "http://json-schema.org/draft-04/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT4_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-04/schema#",             \
                        "http://json-schema.org/draft-04/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT3(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-03/schema#",             \
                        "http://json-schema.org/draft-03/schema#");            \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT3_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-03/schema#",             \
                        "http://json-schema.org/draft-03/schema#");            \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT2(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-02/schema#",             \
                        "http://json-schema.org/draft-02/hyper-schema#");      \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT2_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-02/schema#",             \
                        "http://json-schema.org/draft-02/hyper-schema#");      \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT1(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-01/schema#",             \
                        "http://json-schema.org/draft-01/hyper-schema#");      \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT1_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-01/schema#",             \
                        "http://json-schema.org/draft-01/hyper-schema#");      \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT0(entries, index, expected_schema_location,   \
                                   expected_parent_location)                   \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-00/schema#",             \
                        "http://json-schema.org/draft-00/hyper-schema#");      \
  EXPECT_FALSE(entries.at(index).orphan);

#define EXPECT_WALKER_ENTRY_DRAFT0_ORPHAN(                                     \
    entries, index, expected_schema_location, expected_parent_location)        \
  __EXPECT_WALKER_ENTRY(entries, index, expected_schema_location,              \
                        expected_parent_location,                              \
                        "http://json-schema.org/draft-00/schema#",             \
                        "http://json-schema.org/draft-00/hyper-schema#");      \
  EXPECT_TRUE(entries.at(index).orphan);

#define EXPECT_REFERENCE_TO(result, index, type, origin)                       \
  EXPECT_EQ((result).at((index)).get().first.first,                            \
            sourcemeta::blaze::SchemaReferenceType::type);                     \
  EXPECT_EQ(                                                                   \
      sourcemeta::core::to_string((result).at((index)).get().first.second),    \
      (origin));

#define EXPECT_FRAME_LOCATION_REACHABLE(frame, reference_type, reference,      \
                                        base)                                  \
  EXPECT_TRUE((frame).locations().contains(                                    \
      {sourcemeta::blaze::SchemaReferenceType::reference_type, (reference)})); \
  EXPECT_TRUE((frame).traverse((base)).has_value());                           \
  EXPECT_TRUE((frame).is_reachable(                                            \
      (frame).traverse((base))->get(),                                         \
      (frame).locations().at(                                                  \
          {sourcemeta::blaze::SchemaReferenceType::reference_type,             \
           (reference)}),                                                      \
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver))

#define EXPECT_FRAME_LOCATION_NON_REACHABLE(frame, reference_type, reference,  \
                                            base)                              \
  EXPECT_TRUE((frame).locations().contains(                                    \
      {sourcemeta::blaze::SchemaReferenceType::reference_type, (reference)})); \
  EXPECT_TRUE((frame).traverse((base)).has_value());                           \
  EXPECT_FALSE((frame).is_reachable(                                           \
      (frame).traverse((base))->get(),                                         \
      (frame).locations().at(                                                  \
          {sourcemeta::blaze::SchemaReferenceType::reference_type,             \
           (reference)}),                                                      \
      sourcemeta::blaze::schema_walker, sourcemeta::blaze::schema_resolver))

#endif
