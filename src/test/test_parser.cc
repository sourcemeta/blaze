#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/uri.h>
#include <sourcemeta/core/yaml.h>

#include <algorithm> // std::ranges::any_of
#include <cassert>   // assert
#include <tuple>     // std::get
#include <utility>   // std::move

namespace {
inline auto test_error_if(
    bool condition, const sourcemeta::core::PointerPositionTracker &tracker,
    const sourcemeta::core::Pointer &pointer, const char *message) -> void {
  if (condition) [[unlikely]] {
    const auto position{tracker.get(pointer)};
    assert(position.has_value());
    throw sourcemeta::blaze::TestParseError{message, pointer,
                                            std::get<0>(position.value()),
                                            std::get<1>(position.value())};
  }
}

} // namespace

namespace sourcemeta::blaze {

auto TestCase::parse(
    const sourcemeta::core::JSON &test_case_json,
    const sourcemeta::core::PointerPositionTracker &tracker,
    const std::filesystem::path &base_path,
    const sourcemeta::core::Pointer &location,
    const sourcemeta::core::PointerPositionTracker::Position &position)
    -> TestCase {
  test_error_if(!test_case_json.is_object(), tracker, location,
                "Test case documents must be objects");
  test_error_if(!test_case_json.defines("data") &&
                    !test_case_json.defines("dataPath"),
                tracker, location,
                "Test case documents must contain a `data` or `dataPath` "
                "property");
  test_error_if(test_case_json.defines("data") &&
                    test_case_json.defines("dataPath"),
                tracker, location,
                "Test case documents must contain either a `data` or "
                "`dataPath` property, but not both");
  test_error_if(test_case_json.defines("dataPath") &&
                    !test_case_json.at("dataPath").is_string(),
                tracker, location.concat("dataPath"),
                "Test case documents must set the `dataPath` property to a "
                "string");
  test_error_if(test_case_json.defines("description") &&
                    !test_case_json.at("description").is_string(),
                tracker, location.concat("description"),
                "If you set a test case description, it must be a string");
  test_error_if(!test_case_json.defines("valid"), tracker, location,
                "Test case documents must contain a `valid` property");
  test_error_if(!test_case_json.at("valid").is_boolean(), tracker,
                location.concat("valid"),
                "The test case document `valid` property must be a boolean");
  test_error_if(test_case_json.defines("rdf") &&
                    test_case_json.defines("rdfPath"),
                tracker, location,
                "Test case documents may contain either an `rdf` or "
                "`rdfPath` property, but not both");
  test_error_if(test_case_json.defines("rdfPath") &&
                    !test_case_json.at("rdfPath").is_string(),
                tracker, location.concat("rdfPath"),
                "Test case documents must set the `rdfPath` property to a "
                "string");
  test_error_if(
      (test_case_json.defines("rdf") || test_case_json.defines("rdfPath")) &&
          !test_case_json.at("valid").to_boolean(),
      tracker, location,
      "Test case documents may only set the `rdf` or `rdfPath` "
      "property when the `valid` property is set to true");
  test_error_if(test_case_json.defines("rdf") &&
                    !test_case_json.at("rdf").is_array(),
                tracker, location.concat("rdf"),
                "Test case documents must set the `rdf` property to an "
                "array");

  sourcemeta::core::JSON::String description;
  if (test_case_json.defines("description")) {
    description = test_case_json.at("description").to_string();
  }

  std::optional<sourcemeta::core::JSON> rdf;
  if (test_case_json.defines("rdf")) {
    rdf = test_case_json.at("rdf");
  } else if (test_case_json.defines("rdfPath")) {
    const std::filesystem::path rdf_path{sourcemeta::core::weakly_canonical(
        base_path / test_case_json.at("rdfPath").to_string())};
    rdf = sourcemeta::core::read_yaml_or_json(rdf_path);
    test_error_if(!rdf.value().is_array(), tracker, location.concat("rdfPath"),
                  "The document referenced by the test case `rdfPath` "
                  "property must be an array");
  }

  sourcemeta::core::PointerPositionTracker data_tracker;

  if (test_case_json.defines("data")) {
    return TestCase{.description = std::move(description),
                    .valid = test_case_json.at("valid").to_boolean(),
                    .data = test_case_json.at("data"),
                    .rdf = std::move(rdf),
                    .tracker = std::move(data_tracker),
                    .position = position};
  }
  const std::filesystem::path data_path{sourcemeta::core::weakly_canonical(
      base_path / test_case_json.at("dataPath").to_string())};
  sourcemeta::core::JSON data{nullptr};
  sourcemeta::core::read_yaml_or_json(data_path, data, std::ref(data_tracker));
  return TestCase{.description = std::move(description),
                  .valid = test_case_json.at("valid").to_boolean(),
                  .data = std::move(data),
                  .rdf = std::move(rdf),
                  .tracker = std::move(data_tracker),
                  .position = position};
}

auto TestSuite::parse(const sourcemeta::core::JSON &document,
                      const sourcemeta::core::PointerPositionTracker &tracker,
                      const std::filesystem::path &base_path) -> TestSuite {
  assert(std::filesystem::is_directory(base_path));
  test_error_if(!document.is_object(), tracker, sourcemeta::core::EMPTY_POINTER,
                "The test document must be an object");
  test_error_if(!document.defines("target"), tracker,
                sourcemeta::core::EMPTY_POINTER,
                "The test document must contain a `target` property");
  test_error_if(!document.at("target").is_string() &&
                    !document.at("target").is_array(),
                tracker, sourcemeta::core::Pointer{"target"},
                "The test document `target` property must be a URI or an "
                "array of URIs");
  test_error_if(!document.defines("tests"), tracker,
                sourcemeta::core::EMPTY_POINTER,
                "The test document must contain a `tests` property");
  test_error_if(!document.at("tests").is_array(), tracker,
                sourcemeta::core::Pointer{"tests"},
                "The test document `tests` property must be an array");

  const auto base_path_uri{
      sourcemeta::core::URI::from_path(base_path / "test.json")};

  TestSuite test_suite;

  if (document.at("target").is_string()) {
    sourcemeta::core::URI schema_uri{document.at("target").to_string()};
    schema_uri.resolve_from(base_path_uri);
    schema_uri.canonicalize();
    test_suite.targets.push_back(schema_uri.recompose());
  } else {
    test_error_if(document.at("target").empty(), tracker,
                  sourcemeta::core::Pointer{"target"},
                  "The test document `target` array must contain at least "
                  "one URI");
    // TODO(C++23): Use std::views::enumerate when available in libc++
    std::size_t target_index{0};
    for (const auto &target_entry : document.at("target").as_array()) {
      const sourcemeta::core::Pointer target_location{"target", target_index};
      test_error_if(!target_entry.is_string(), tracker, target_location,
                    "Each entry in the test document `target` array must be "
                    "a URI");
      sourcemeta::core::URI schema_uri{target_entry.to_string()};
      schema_uri.resolve_from(base_path_uri);
      schema_uri.canonicalize();
      test_suite.targets.push_back(schema_uri.recompose());
      target_index += 1;
    }
  }

  // TODO(C++23): Use std::views::enumerate when available in libc++
  std::size_t index{0};
  for (const auto &test_case_json : document.at("tests").as_array()) {
    const sourcemeta::core::Pointer location{"tests", index};
    const auto position{tracker.get(location)};
    assert(position.has_value());
    test_suite.tests.push_back(TestCase::parse(
        test_case_json, tracker, base_path, location, position.value()));
    index += 1;
  }

  test_suite.requires_jsonld_annotations_ = std::ranges::any_of(
      test_suite.tests, [](const TestCase &test_case) -> bool {
        return test_case.rdf.has_value();
      });

  test_suite.schemas_fast_.resize(test_suite.targets.size());
  test_suite.schemas_exhaustive_.resize(test_suite.targets.size());
  test_suite.exhaustive_providers_.resize(test_suite.targets.size());

  return test_suite;
}

auto TestSuite::bind(const std::size_t target_index, Template fast,
                     ExhaustiveProvider exhaustive) -> void {
  assert(target_index < this->schemas_fast_.size());
  this->schemas_fast_[target_index] = std::move(fast);
  this->exhaustive_providers_[target_index] = std::move(exhaustive);
}

auto TestSuite::requires_jsonld_annotations() const noexcept -> bool {
  return this->requires_jsonld_annotations_;
}

auto TestSuite::fast(const std::size_t target_index) const -> const Template & {
  assert(target_index < this->schemas_fast_.size());
  const auto &schema_fast{this->schemas_fast_[target_index]};
  assert(schema_fast.has_value());
  return schema_fast.value();
}

auto TestSuite::exhaustive(const std::size_t target_index) -> const Template & {
  assert(target_index < this->schemas_exhaustive_.size());
  auto &schema_exhaustive{this->schemas_exhaustive_[target_index]};
  if (!schema_exhaustive.has_value()) {
    assert(this->exhaustive_providers_[target_index]);
    schema_exhaustive = this->exhaustive_providers_[target_index]();
  }

  return schema_exhaustive.value();
}

} // namespace sourcemeta::blaze
