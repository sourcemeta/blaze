#ifndef SOURCEMETA_BLAZE_DOCUMENTATION_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_DOCUMENTATION_TEST_UTILS_H_

#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <string>      // std::string
#include <string_view> // std::string_view

// The format has a schema of its own, in `schemas/table-format.json`. Every
// document a test produces is held to it, so this module and the format it
// claims to write cannot drift apart without a test saying so.
inline auto expect_fits_the_format(const sourcemeta::core::JSON &document)
    -> void {
  static const auto format{
      sourcemeta::core::read_json(std::string{TABLE_FORMAT_SCHEMA_PATH})};
  static const auto schema{
      sourcemeta::blaze::compile(format, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_TRUE(evaluator.validate(schema, document));
}

// Describe the given schema and compare the result with the expected document.
#define EXPECT_DOCUMENTATION(schema, expected)                                 \
  {                                                                            \
    const auto actual{sourcemeta::blaze::to_documentation(                     \
        sourcemeta::core::parse_json(schema), sourcemeta::core::schema_walker, \
        sourcemeta::core::schema_resolver)};                                   \
    expect_fits_the_format(actual);                                            \
    EXPECT_EQ(actual, sourcemeta::core::parse_json(expected));                 \
  }

// Describe the given schema and compare its `root` alone, for the many cases
// where the rest of the document says nothing new.
#define EXPECT_DOCUMENTATION_ROOT(schema, expected)                            \
  {                                                                            \
    const auto actual{sourcemeta::blaze::to_documentation(                     \
        sourcemeta::core::parse_json(schema), sourcemeta::core::schema_walker, \
        sourcemeta::core::schema_resolver)};                                   \
    expect_fits_the_format(actual);                                            \
    EXPECT_EQ(actual.at("root"), sourcemeta::core::parse_json(expected));      \
  }

// The schema cannot be described exactly, and saying so names the trouble,
// what it is about, and where in the schema it is.
#define EXPECT_DOCUMENTATION_REFUSED(schema, sentence, about, where)           \
  {                                                                            \
    try {                                                                      \
      [[maybe_unused]] const auto result{sourcemeta::blaze::to_documentation(  \
          sourcemeta::core::parse_json(schema),                                \
          sourcemeta::core::schema_walker,                                     \
          sourcemeta::core::schema_resolver)};                                 \
      FAIL();                                                                  \
    } catch (const sourcemeta::blaze::DocumentationError &error) {             \
      const std::string actual_subject{error.subject()};                       \
      const std::string expected_subject{about};                               \
      const std::string actual_location{                                       \
          sourcemeta::core::to_string(error.location())};                      \
      const std::string expected_location{where};                              \
      EXPECT_STREQ(error.what(), sentence);                                    \
      EXPECT_EQ(actual_subject, expected_subject);                             \
      EXPECT_EQ(actual_location, expected_location);                           \
    }                                                                          \
  }

#endif
