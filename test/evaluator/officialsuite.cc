#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "suite_compatibility.h"

#include <cassert>     // assert
#include <cctype>      // std::isalnum
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint32_t
#include <cstdlib>     // EXIT_FAILURE
#include <exception>   // std::exception
#include <filesystem>  // std::filesystem
#include <iostream>    // std::cerr
#include <optional>    // std::optional
#include <ostream>     // std::ostream
#include <set>         // std::set
#include <sstream>     // std::ostringstream
#include <stdexcept>   // std::runtime_error
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::unreachable

static auto slugify(const std::string &input, std::ostream &output) -> void {
  for (const auto character : input) {
    output << ((std::isalnum(character) != 0) ? character : '_');
  }
}

namespace {

// Every test case that relies on references declares the schemas those
// references resolve to, which replaces the standalone directory of remote
// schemas that older revisions of the suite shipped
struct ExternalSchemaResolver {
  const sourcemeta::core::JSON *external_schemas{nullptr};

  auto operator()(const std::string_view identifier) const
      -> sourcemeta::core::SchemaResolverResult {
    if (this->external_schemas != nullptr &&
        this->external_schemas->defines(identifier)) {
      return this->external_schemas->at(identifier);
    }

    return sourcemeta::core::schema_resolver(identifier);
  }
};

auto mode_name(const sourcemeta::blaze::Mode mode) -> std::string_view {
  switch (mode) {
    case sourcemeta::blaze::Mode::FastValidation:
      return "fast_validation";
    case sourcemeta::blaze::Mode::Exhaustive:
      return "exhaustive";
  }

  std::unreachable();
}

// Upstream asks implementations to run a test case only if they provide the
// behaviour that every one of its tags stands for
auto supported_tags(const sourcemeta::core::JSON &test_case) -> bool {
  if (!test_case.defines("tags")) {
    return true;
  }

  assert(test_case.at("tags").is_array());
  for (const auto &tag : test_case.at("tags").as_array()) {
    assert(tag.is_string());
    if (tag.to_string() != "format-annotation" &&
        tag.to_string() != "format-assertion") {
      return false;
    }
  }

  return true;
}

auto declares_format_assertion(const sourcemeta::core::JSON &test_case)
    -> bool {
  if (!test_case.defines("tags")) {
    return false;
  }

  for (const auto &tag : test_case.at("tags").as_array()) {
    if (tag.to_string() == "format-assertion") {
      return true;
    }
  }

  return false;
}

auto skip_key(const std::string &prefix, const std::string &suffix)
    -> std::string {
  std::string result{prefix};
  result += "::";
  result += suffix;
  return result;
}

auto compile_error_message(const std::string &case_key,
                           const std::string &default_dialect,
                           const char *error) -> std::string {
  std::string message{"Cannot compile "};
  message += case_key;
  message += " with ";
  message += default_dialect;
  message += ": ";
  message += error;
  return message;
}

auto write_case_title(const sourcemeta::blaze::Mode mode,
                      const std::string &file_name,
                      const std::string &case_description, std::ostream &output)
    -> void {
  output << mode_name(mode) << "_";
  slugify(file_name, output);
  output << "__";
  slugify(case_description, output);
}

auto run_official_test(const bool valid,
                       const sourcemeta::blaze::Template &schema,
                       const sourcemeta::core::JSON &instance) -> void {
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{evaluator.validate(schema, instance)};
  if (valid) {
    EXPECT_TRUE(result);
  } else {
    EXPECT_FALSE(result);
  }
}
} // namespace

// The skip list is keyed by the path of the test file relative to the suite
// directory, optionally followed by `::` and a case description, optionally
// followed by `::` and a test description
static auto register_tests(const std::filesystem::path &group,
                           const std::string &suite_name,
                           const std::string &default_dialect,
                           const std::uint32_t version,
                           const std::set<std::string> &skips) -> void {
  std::cerr << "-- Registering: " << suite_name << "\n";
  std::size_t registered{0};

  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator(
           std::filesystem::path{OFFICIAL_SUITE_PATH} / "validation" / "tests" /
           group)) {
    if (!entry.is_regular_file() || entry.path().extension() != ".json") {
      continue;
    }

    const auto file_name{entry.path().stem().string()};
    const auto file_key{(group / file_name).generic_string()};
    if (skips.contains(file_key)) {
      continue;
    }

    std::cerr << "-- Parsing: " << entry.path().string() << "\n";
    const sourcemeta::core::JSON suite{
        sourcemeta::core::read_json(entry.path())};
    assert(suite.is_object());
    assert(suite.defines("description"));
    assert(suite.defines("tests"));
    assert(suite.at("tests").is_array());

    for (const auto &test_case : suite.at("tests").as_array()) {
      assert(test_case.is_object());
      assert(test_case.defines("description"));
      assert(test_case.defines("schema"));
      assert(test_case.defines("tests"));
      assert(test_case.at("description").is_string());
      assert(test_case.at("schema").is_object() ||
             test_case.at("schema").is_boolean());
      assert(test_case.at("tests").is_array());

      const auto &case_description{test_case.at("description").to_string()};
      const auto case_key{skip_key(file_key, case_description)};
      if (skips.contains(case_key)) {
        continue;
      }

      if (test_case.defines("compatibility")) {
        assert(test_case.at("compatibility").is_string());
        if (!suite_compatibility(test_case.at("compatibility").to_string(),
                                 version)) {
          continue;
        }
      }

      if (!supported_tags(test_case)) {
        continue;
      }

      // Note that the two cases of `optional/format-assertion.json` carry no
      // tag at all and still exercise format assertions, as they declare a
      // meta-schema of their own that opts into the format-assertion
      // vocabulary, which the compiler honours without this tweak
      std::optional<sourcemeta::blaze::Tweaks> tweaks;
      if (declares_format_assertion(test_case)) {
        tweaks = sourcemeta::blaze::Tweaks{.format_assertion = true};
      }

      const sourcemeta::core::JSON *external_schemas{nullptr};
      if (test_case.defines("externalSchemas")) {
        assert(test_case.at("externalSchemas").is_object());
        external_schemas = &test_case.at("externalSchemas");
      }

      registered++;

      for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                              sourcemeta::blaze::Mode::Exhaustive}) {
        sourcemeta::blaze::Template schema_template{};

        try {
          schema_template = sourcemeta::blaze::compile(
              test_case.at("schema"), sourcemeta::core::schema_walker,
              ExternalSchemaResolver{external_schemas},
              sourcemeta::blaze::default_schema_compiler, mode, default_dialect,
              "", "", tweaks);
        } catch (const std::exception &error) {
          // Registering the failure keeps it addressable by name and stops one
          // schema the compiler refuses from taking down the whole run
          std::ostringstream title;
          write_case_title(mode, file_name, case_description, title);
          title << "__compile_error";
          const auto message{
              compile_error_message(case_key, default_dialect, error.what())};
          sourcemeta::core::test_register(
              suite_name, title.str(), __FILE__, __LINE__, [message]() -> void {
                sourcemeta::core::test_report_failure(__FILE__, __LINE__,
                                                      message);
              });
          continue;
        }

        std::size_t ordinal{0};
        for (const auto &test : test_case.at("tests").as_array()) {
          // Several cases hold tests whose descriptions only differ in
          // punctuation, which the slug drops, so the position within the case
          // is what keeps their names apart
          ordinal++;

          assert(test.is_object());
          assert(test.defines("data"));
          assert(test.defines("description"));
          assert(test.defines("valid"));
          assert(test.at("description").is_string());
          assert(test.at("valid").is_boolean());

          if (skips.contains(
                  skip_key(case_key, test.at("description").to_string()))) {
            continue;
          }

          std::ostringstream title;
          write_case_title(mode, file_name, case_description, title);
          title << "__";
          slugify(test.at("description").to_string(), title);
          title << "__" << ordinal;

          const auto &instance{test.at("data")};
          const auto valid{test.at("valid").to_boolean()};

          sourcemeta::core::test_register(
              suite_name, title.str(), __FILE__, __LINE__,
              [valid, schema_template, instance]() -> void {
                run_official_test(valid, schema_template, instance);
              });
        }
      }
    }
  }

  if (registered == 0) {
    throw std::runtime_error{"No test cases were registered for " + suite_name};
  }
}

auto main(int argc, char **argv) -> int {
  // The compiler refuses to reference what the dialect in use does not
  // consider a subschema
  // TODO: Can we make this work?
  std::set<std::string> non_schemas_skips;
  for (const auto *description :
       {"reference of a root arbitrary keyword",
        "reference of a root arbitrary keyword with encoded ref",
        "reference of an arbitrary keyword of a sub-schema",
        "reference of an arbitrary keyword of a sub-schema with encoded ref",
        "reference internals of known non-applicator"}) {
    non_schemas_skips.insert(skip_key("optional/non-schemas", description));
  }

  // Draft 7 defines the content keywords as assertions rather than as the
  // annotations that later dialects make of them
  // TODO: Assert `contentEncoding` and `contentMediaType` on Draft 7
  std::set<std::string> draft7_optional_skips;
  for (const auto &[case_description, test_description] :
       {std::pair<const char *, const char *>{
            "validation of string-encoded content based on media type",
            "an invalid JSON document"},
        std::pair<const char *, const char *>{
            "validation of binary string-encoding",
            "an invalid base64 string (% is not a valid character)"},
        std::pair<const char *, const char *>{
            "validation of binary-encoded media type documents",
            "a validly-encoded invalid JSON document"},
        std::pair<const char *, const char *>{
            "validation of binary-encoded media type documents",
            "an invalid base64 string that is valid JSON"}}) {
    draft7_optional_skips.insert(skip_key(
        skip_key("optional/content", case_description), test_description));
  }

  // TODO: Support bundling a Draft 7 schema whose top-level `$ref` sits next
  // to other keywords
  draft7_optional_skips.insert(
      skip_key("optional/cross-draft",
               "refs to future drafts are processed as future drafts (2020)"));

  try {
    // 2020-12
    register_tests("", "JSONSchemaOfficialSuite_2020_12",
                   "https://json-schema.org/draft/2020-12/schema", 2020, {});
    register_tests("optional", "JSONSchemaOfficialSuite_2020_12_Optional",
                   "https://json-schema.org/draft/2020-12/schema", 2020,
                   non_schemas_skips);

    // 2019-09
    register_tests("", "JSONSchemaOfficialSuite_2019_09",
                   "https://json-schema.org/draft/2019-09/schema", 2019, {});
    register_tests("optional", "JSONSchemaOfficialSuite_2019_09_Optional",
                   "https://json-schema.org/draft/2019-09/schema", 2019,
                   non_schemas_skips);

    // Draft 7
    register_tests("", "JSONSchemaOfficialSuite_Draft7",
                   "http://json-schema.org/draft-07/schema#", 7, {});
    register_tests("optional", "JSONSchemaOfficialSuite_Draft7_Optional",
                   "http://json-schema.org/draft-07/schema#", 7,
                   draft7_optional_skips);

    // Draft 6
    register_tests("", "JSONSchemaOfficialSuite_Draft6",
                   "http://json-schema.org/draft-06/schema#", 6, {});
    register_tests("optional", "JSONSchemaOfficialSuite_Draft6_Optional",
                   "http://json-schema.org/draft-06/schema#", 6, {});

    // Draft 4
    register_tests("", "JSONSchemaOfficialSuite_Draft4",
                   "http://json-schema.org/draft-04/schema#", 4, {});
    register_tests("optional", "JSONSchemaOfficialSuite_Draft4_Optional",
                   "http://json-schema.org/draft-04/schema#", 4, {});

    // Draft 3
    register_tests("", "JSONSchemaOfficialSuite_Draft3",
                   "http://json-schema.org/draft-03/schema#", 3, {});
    register_tests("optional", "JSONSchemaOfficialSuite_Draft3_Optional",
                   "http://json-schema.org/draft-03/schema#", 3, {});
  } catch (const sourcemeta::core::SchemaResolutionError &error) {
    std::cerr << error.what() << ": " << error.identifier() << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
