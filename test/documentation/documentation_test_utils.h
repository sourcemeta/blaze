#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_DOCUMENTATION_TEST_UTILS_H_

#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

// Describe the given schema and compare the result with the expected document.
#define EXPECT_DOCUMENTATION(schema, expected)                                 \
  {                                                                            \
    const auto actual{sourcemeta::blaze::to_documentation(                     \
        sourcemeta::core::parse_json(schema), sourcemeta::core::schema_walker, \
        sourcemeta::core::schema_resolver)};                                   \
    EXPECT_EQ(actual, sourcemeta::core::parse_json(expected));                 \
  }

// Describe the given schema and compare its `root` alone, for the many cases
// where the rest of the document says nothing new.
#define EXPECT_DOCUMENTATION_ROOT(schema, expected)                            \
  {                                                                            \
    const auto actual{sourcemeta::blaze::to_documentation(                     \
        sourcemeta::core::parse_json(schema), sourcemeta::core::schema_walker, \
        sourcemeta::core::schema_resolver)};                                   \
    EXPECT_EQ(actual.at("root"), sourcemeta::core::parse_json(expected));      \
  }

// The schema cannot be described exactly, and saying so names the trouble.
#define EXPECT_DOCUMENTATION_REFUSED(schema, message)                          \
  {                                                                            \
    try {                                                                      \
      static_cast<void>(sourcemeta::blaze::to_documentation(                   \
          sourcemeta::core::parse_json(schema),                                \
          sourcemeta::core::schema_walker,                                     \
          sourcemeta::core::schema_resolver));                                 \
      FAIL();                                                                  \
    } catch (const sourcemeta::blaze::DocumentationError &error) {             \
      EXPECT_STREQ(error.what(), message);                                     \
    }                                                                          \
  }

#endif
