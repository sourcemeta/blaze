#include <gtest/gtest.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

static auto slugify(const std::string &input, std::ostream &output) -> void {
  for (const auto character : input) {
    output << (std::isalnum(character) ? character : '_');
  }
}

static auto
has_annotation(const sourcemeta::blaze::SimpleOutput &output,
               const sourcemeta::core::WeakPointer &instance_location,
               const std::string &schema_location,
               const sourcemeta::core::JSON &value) -> bool {
  std::cerr << "Looking for ";
  sourcemeta::core::stringify(value, std::cerr);
  std::cerr << " at instance location \""
            << sourcemeta::core::to_string(instance_location)
            << "\" and schema location \"" << schema_location << "\"" << "\n";

  for (const auto &annotation : output.annotations()) {
    std::cerr << "Checking against annotations for instance location \""
              << sourcemeta::core::to_string(annotation.first.instance_location)
              << "\" and schema location \""
              << annotation.first.schema_location.get() << "\"" << "\n";

    if (annotation.first.instance_location != instance_location ||
        annotation.first.schema_location.get() != schema_location) {
      continue;
    } else if (std::find(annotation.second.cbegin(), annotation.second.cend(),
                         value) != annotation.second.cend()) {
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
              << sourcemeta::core::to_string(annotation.first.instance_location)
              << "\" and evaluate path \""
              << sourcemeta::core::to_string(annotation.first.evaluate_path)
              << "\"" << "\n";

    if (annotation.first.instance_location == instance_location &&
        !annotation.first.evaluate_path.empty() &&
        annotation.first.evaluate_path.back().is_property() &&
        annotation.first.evaluate_path.back().to_property() == keyword) {
      return true;
    }
  }

  return false;
}

class AnnotationTest : public testing::Test {
public:
  explicit AnnotationTest(sourcemeta::blaze::Template test_schema,
                          sourcemeta::core::JSON test_instance,
                          sourcemeta::core::JSON::Array test_assertions)
      : schema{std::move(test_schema)}, instance{std::move(test_instance)},
        assertions{std::move(test_assertions)} {}

  auto TestBody() -> void override {
    sourcemeta::blaze::SimpleOutput output{this->instance};
    const auto result{this->evaluator.validate(this->schema, this->instance,
                                               std::ref(output))};
    EXPECT_TRUE(result);

    for (const auto &assertion : this->assertions) {
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
              schema_location.str(), entry.second));
        }
      }
    }
  }

private:
  const sourcemeta::blaze::Template schema;
  const sourcemeta::core::JSON instance;
  const sourcemeta::core::JSON::Array assertions;
  sourcemeta::blaze::Evaluator evaluator;
};

static auto register_tests(const std::string &suite_name,
                           const std::string &default_dialect,
                           const std::string &default_dialect_name,
                           const std::unordered_set<std::string> &targets)
    -> void {
  auto suite_path{std::filesystem::path{ANNOTATION_SUITE_PATH} / suite_name};
  suite_path.replace_extension(".json");
  assert(std::filesystem::exists(suite_path));

  std::cerr << "Registering suite: " << suite_path.string() << "\n";
  std::cerr << "-- Dialect: " << default_dialect << "\n";
  std::cerr << "-- Targets:";
  assert(!targets.empty());
  for (const auto &target : targets) {
    std::cerr << " " << target;
  }
  std::cerr << "\n";

  const auto suite{sourcemeta::core::read_json(suite_path)};
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
      if (!targets.contains(compatibility)) {
        std::cerr << "-- Skipping " << category.str() << " for compatibility "
                  << compatibility << "\n";
        continue;
      }
    }

    std::cerr << "-- Compiling " << category.str() << "\n";
    assert(entry.defines("schema"));
    const auto &schema{entry.at("schema")};
    assert(sourcemeta::core::is_schema(schema));
    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_official_walker,
        sourcemeta::core::schema_official_resolver,
        sourcemeta::blaze::default_schema_compiler,
        sourcemeta::blaze::Mode::Exhaustive, default_dialect)};

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

      testing::RegisterTest(
          category.str().c_str(), title.str().c_str(), nullptr, nullptr,
          __FILE__, __LINE__, [=]() -> AnnotationTest * {
            return new AnnotationTest(schema_template, instance, assertions);
          });
    }
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  try {
    // 2020-12
    register_tests("applicators",
                   "https://json-schema.org/draft/2020-12/schema", "2020-12",
                   {"3", "4", "6", "7", "2019", "2020"});
    register_tests("content", "https://json-schema.org/draft/2020-12/schema",
                   "2020-12", {"3", "4", "6", "7", "2019", "2020"});
    register_tests("core", "https://json-schema.org/draft/2020-12/schema",
                   "2020-12", {"3", "4", "6", "7", "2019", "2020"});
    register_tests("format", "https://json-schema.org/draft/2020-12/schema",
                   "2020-12", {"3", "4", "6", "7", "2019", "2020"});
    register_tests("meta-data", "https://json-schema.org/draft/2020-12/schema",
                   "2020-12", {"3", "4", "6", "7", "2019", "2020"});
    register_tests("unevaluated",
                   "https://json-schema.org/draft/2020-12/schema", "2020-12",
                   {"3", "4", "6", "7", "2019", "2020"});
    register_tests("unknown", "https://json-schema.org/draft/2020-12/schema",
                   "2020-12", {"3", "4", "6", "7", "2019", "2020"});

    // 2019-09
    register_tests("applicators",
                   "https://json-schema.org/draft/2019-09/schema", "2019-09",
                   {"3", "4", "6", "7", "2019"});
    register_tests("content", "https://json-schema.org/draft/2019-09/schema",
                   "2019-09", {"3", "4", "6", "7", "2019"});
    register_tests("core", "https://json-schema.org/draft/2019-09/schema",
                   "2019-09", {"3", "4", "6", "7", "2019"});
    register_tests("format", "https://json-schema.org/draft/2019-09/schema",
                   "2019-09", {"3", "4", "6", "7", "2019"});
    register_tests("meta-data", "https://json-schema.org/draft/2019-09/schema",
                   "2019-09", {"3", "4", "6", "7", "2019"});
    register_tests("unevaluated",
                   "https://json-schema.org/draft/2019-09/schema", "2019-09",
                   {"3", "4", "6", "7", "2019"});
    register_tests("unknown", "https://json-schema.org/draft/2019-09/schema",
                   "2019-09", {"3", "4", "6", "7", "2019"});
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return RUN_ALL_TESTS();
}
