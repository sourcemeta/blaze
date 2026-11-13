#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include "suite_compatibility.h"

#include <cassert>       // assert
#include <cstddef>       // std::size_t
#include <cstdint>       // std::uint32_t
#include <cstdlib>       // EXIT_FAILURE
#include <filesystem>    // std::filesystem
#include <functional>    // std::ref
#include <iostream>      // std::cerr
#include <ostream>       // std::ostream
#include <sstream>       // std::ostringstream
#include <stdexcept>     // std::runtime_error
#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move

static auto slugify(const std::string &input, std::ostream &output) -> void {
  for (const auto character : input) {
    output << ((std::isalnum(character) != 0) ? character : '_');
  }
}

static auto schema_location_matches(const std::string &actual,
                                    const std::string &expected,
                                    const sourcemeta::core::SchemaFrame &frame)
    -> bool {
  if (actual == expected) {
    return true;
  }

  // The annotation may use an absolute URI based on an intermediate
  // identifier while the test suite uses root-relative JSON pointer
  // fragments. The frame locates subschemas rather than the keywords inside
  // them, so resolve the location without its keyword and put the keyword
  // back afterwards
  const auto keyword{actual.find_last_of('/')};
  if (keyword == std::string::npos) {
    return false;
  }

  const auto entry{frame.traverse(actual.substr(0, keyword))};
  if (!entry.has_value()) {
    return false;
  }

  auto normalized{sourcemeta::core::to_uri(entry->get().pointer).recompose()};
  normalized += actual.substr(keyword);
  return normalized == expected;
}

static auto
has_annotation(const sourcemeta::blaze::SimpleOutput &output,
               const sourcemeta::core::WeakPointer &instance_location,
               const std::string &schema_location,
               const sourcemeta::core::JSON &value,
               const sourcemeta::core::SchemaFrame &frame) -> bool {
  std::cerr << "Looking for ";
  sourcemeta::core::stringify(value, std::cerr);
  std::cerr << " at instance location \""
            << sourcemeta::core::to_string(instance_location)
            << "\" and schema location \"" << schema_location << "\"" << "\n";

  for (const auto &annotation : output.annotations()) {
    std::cerr << "Checking against annotations for instance location \""
              << sourcemeta::core::to_string(annotation.instance_location)
              << "\" and schema location \"" << annotation.schema_location.get()
              << "\"" << "\n";

    if (annotation.instance_location != instance_location ||
        !schema_location_matches(annotation.schema_location.get(),
                                 schema_location, frame)) {
      continue;
    }
    if (annotation.value == value) {
      return true;
    }
  }

  return false;
}

static auto
has_matching_annotations(const sourcemeta::blaze::SimpleOutput &output,
                         const sourcemeta::core::WeakPointer &instance_location,
                         const std::string &keyword) -> bool {
  std::cerr << "Looking for any annotation at instance location \""
            << sourcemeta::core::to_string(instance_location)
            << "\" from keyword \"" << keyword << "\"" << "\n";

  for (const auto &annotation : output.annotations()) {
    std::cerr << "Checking against annotations for instance location \""
              << sourcemeta::core::to_string(annotation.instance_location)
              << "\" and evaluate path \""
              << sourcemeta::core::to_string(annotation.evaluate_path) << "\""
              << "\n";

    if (annotation.instance_location == instance_location &&
        !annotation.evaluate_path.empty() &&
        annotation.evaluate_path.back().is_property() &&
        annotation.evaluate_path.back().to_property() == keyword) {
      return true;
    }
  }

  return false;
}

namespace {
auto check_assertions(const sourcemeta::blaze::SimpleOutput &output,
                      const sourcemeta::core::JSON::Array &assertions,
                      const sourcemeta::core::SchemaFrame &frame) -> void {
  for (const auto &assertion : assertions) {
    assert(assertion.is_object());
    assert(assertion.defines("location"));
    assert(assertion.at("location").is_string());
    const auto instance_location{
        sourcemeta::core::to_pointer(assertion.at("location").to_string())};
    assert(assertion.defines("expected"));
    assert(assertion.at("expected").is_object());

    if (assertion.at("expected").empty()) {
      assert(assertion.defines("keyword"));
      assert(assertion.at("keyword").is_string());
      EXPECT_FALSE(has_matching_annotations(
          output, sourcemeta::core::to_weak_pointer(instance_location),
          assertion.at("keyword").to_string()));
    } else {
      for (const auto &entry : assertion.at("expected").as_object()) {
        std::ostringstream schema_location;
        schema_location << entry.first;
        assert(assertion.defines("keyword"));
        assert(assertion.at("keyword").is_string());
        schema_location << "/" << assertion.at("keyword").to_string();

        EXPECT_TRUE(has_annotation(
            output, sourcemeta::core::to_weak_pointer(instance_location),
            schema_location.str(), entry.second, frame));
      }
    }
  }
}

auto run_annotation_test(const sourcemeta::core::JSON &schema_json,
                         const std::string &default_dialect,
                         const sourcemeta::core::JSON &instance,
                         const sourcemeta::core::JSON::Array &assertions)
    -> void {
  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema_json,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      default_dialect};
  const auto exhaustive_schema{sourcemeta::blaze::compile(
      schema_json, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::Exhaustive)};

  std::unordered_set<sourcemeta::core::JSON::String> keywords;
  for (const auto &assertion : assertions) {
    assert(assertion.is_object());
    assert(assertion.defines("keyword"));
    assert(assertion.at("keyword").is_string());
    keywords.insert(assertion.at("keyword").to_string());
  }

  std::unordered_set<sourcemeta::core::JSON::StringView> whitelist;
  for (const auto &keyword : keywords) {
    whitelist.insert(keyword);
  }

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::move(whitelist);
  const auto fast_validation_schema{sourcemeta::blaze::compile(
      schema_json, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, frame, frame.root(),
      sourcemeta::blaze::Mode::FastValidation, tweaks)};

  sourcemeta::blaze::Evaluator evaluator;

  sourcemeta::blaze::SimpleOutput output{exhaustive_schema, instance};
  const auto result{
      evaluator.validate(exhaustive_schema, instance, std::ref(output))};
  EXPECT_TRUE(result);
  check_assertions(output, assertions, frame);

  // The same annotations must be collected in fast validation mode when the
  // relevant keywords are whitelisted via tweaks
  sourcemeta::blaze::SimpleOutput fast_output{fast_validation_schema, instance};
  const auto fast_result{evaluator.validate(fast_validation_schema, instance,
                                            std::ref(fast_output))};
  EXPECT_TRUE(fast_result);
  check_assertions(fast_output, assertions, frame);
}
} // namespace

static auto register_tests(const std::string &default_dialect,
                           const std::string &default_dialect_name,
                           const std::uint32_t version) -> void {
  std::size_t registered{0};

  for (const std::filesystem::directory_entry &suite_file :
       std::filesystem::directory_iterator{ANNOTATION_SUITE_PATH}) {
    if (!suite_file.is_regular_file() ||
        suite_file.path().extension() != ".json") {
      continue;
    }

    const auto suite_name{suite_file.path().stem().string()};
    std::cerr << "Registering suite: " << suite_file.path().string() << "\n";
    std::cerr << "-- Dialect: " << default_dialect << "\n";

    const auto suite{sourcemeta::core::read_json(suite_file.path())};
    assert(suite.is_object());
    assert(suite.defines("suite"));
    assert(suite.at("suite").is_array());

    for (const auto &entry : suite.at("suite").as_array()) {
      assert(entry.is_object());
      std::ostringstream category;
      category << "JSONSchemaAnnotationSuite_";
      slugify(default_dialect_name, category);
      category << "_" << suite_name << "_";
      assert(entry.defines("description"));
      assert(entry.at("description").is_string());
      slugify(entry.at("description").to_string(), category);

      if (entry.defines("compatibility")) {
        assert(entry.at("compatibility").is_string());
        const auto &compatibility{entry.at("compatibility").to_string()};
        if (!suite_compatibility(compatibility, version)) {
          std::cerr << "-- Skipping " << category.str() << " for compatibility "
                    << compatibility << "\n";
          continue;
        }
      }

      std::cerr << "-- Compiling " << category.str() << "\n";
      registered++;
      assert(entry.defines("schema"));
      const auto &schema{entry.at("schema")};
      assert((schema.is_object() || schema.is_boolean()));

      assert(entry.defines("tests"));
      assert(entry.at("tests").is_array());
      for (std::size_t index = 0; index < entry.at("tests").size(); index++) {
        std::ostringstream title;
        title << index;
        const auto &test{entry.at("tests").at(index)};
        assert(test.is_object());
        assert(test.defines("instance"));
        const auto &instance{test.at("instance")};
        assert(test.defines("assertions"));
        assert(test.at("assertions").is_array());
        const auto &assertions{test.at("assertions").as_array()};

        sourcemeta::core::test_register(
            category.str(), title.str(), __FILE__, __LINE__,
            [schema, default_dialect, instance, assertions]() -> void {
              run_annotation_test(schema, default_dialect, instance,
                                  assertions);
            });
      }
    }
  }

  if (registered == 0) {
    throw std::runtime_error{"No test cases were registered for " +
                             default_dialect};
  }
}

auto main(int argc, char **argv) -> int {
  try {
    register_tests("https://json-schema.org/draft/2020-12/schema", "2020-12",
                   2020);
    register_tests("https://json-schema.org/draft/2019-09/schema", "2019-09",
                   2019);
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return sourcemeta::core::test_run(argc, argv);
}
