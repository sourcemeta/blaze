#include <gtest/gtest.h>

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::jsontoolkit::JSON> {
  const std::filesystem::path remotes_path{
      std::filesystem::path{OFFICIAL_SUITE_PATH} / "remotes"};

#define READ_SCHEMA_FILE(uri, relative_path)                                   \
  if (identifier == (uri)) {                                                   \
    return sourcemeta::jsontoolkit::from_file(remotes_path / (relative_path)); \
  }

  // We keep an explicit list instead of dynamically reading into the directory
  // to make sure we are only pulling in the right files
  READ_SCHEMA_FILE("http://localhost:1234/integer.json", "integer.json")
  READ_SCHEMA_FILE("http://localhost:1234/subSchemas.json", "subSchemas.json")
  READ_SCHEMA_FILE("http://localhost:1234/baseUriChange/folderInteger.json",
                   std::filesystem::path{"baseUriChange"} /
                       "folderInteger.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/baseUriChangeFolder/folderInteger.json",
      std::filesystem::path{"baseUriChangeFolder"} / "folderInteger.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/baseUriChangeFolderInSubschema/folderInteger.json",
      std::filesystem::path{"baseUriChangeFolderInSubschema"} /
          "folderInteger.json")
  READ_SCHEMA_FILE("http://localhost:1234/name.json", "name.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/locationIndependentIdentifierDraft4.json",
      "locationIndependentIdentifierDraft4.json")
  READ_SCHEMA_FILE("http://localhost:1234/ref-and-definitions.json",
                   "ref-and-definitions.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/locationIndependentIdentifierPre2019.json",
      "locationIndependentIdentifierPre2019.json")
  READ_SCHEMA_FILE("http://localhost:1234/nested/foo-ref-string.json",
                   std::filesystem::path{"nested"} / "foo-ref-string.json")
  READ_SCHEMA_FILE("http://localhost:1234/nested/string.json",
                   std::filesystem::path{"nested"} / "string.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft6/detached-ref.json",
                   std::filesystem::path{"draft6"} / "detached-ref.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft7/detached-ref.json",
                   std::filesystem::path{"draft7"} / "detached-ref.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft7/ignore-dependentRequired.json",
                   std::filesystem::path{"draft7"} /
                       "ignore-dependentRequired.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2019-09/metaschema-no-validation.json",
      std::filesystem::path{"draft2019-09"} / "metaschema-no-validation.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2019-09/metaschema-optional-vocabulary.json",
      std::filesystem::path{"draft2019-09"} /
          "metaschema-optional-vocabulary.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/integer.json",
                   std::filesystem::path{"draft2019-09"} / "integer.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/subSchemas.json",
                   std::filesystem::path{"draft2019-09"} / "subSchemas.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2019-09/locationIndependentIdentifier.json",
      std::filesystem::path{"draft2019-09"} /
          "locationIndependentIdentifier.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2019-09/baseUriChange/folderInteger.json",
      std::filesystem::path{"draft2019-09"} / "baseUriChange" /
          "folderInteger.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/baseUriChangeFolder/"
                   "folderInteger.json",
                   std::filesystem::path{"draft2019-09"} /
                       "baseUriChangeFolder" / "folderInteger.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2019-09/baseUriChangeFolderInSubschema/"
      "folderInteger.json",
      std::filesystem::path{"draft2019-09"} / "baseUriChangeFolderInSubschema" /
          "folderInteger.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/name-defs.json",
                   std::filesystem::path{"draft2019-09"} / "name-defs.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/ref-and-defs.json",
                   std::filesystem::path{"draft2019-09"} / "ref-and-defs.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2019-09/nested/foo-ref-string.json",
      std::filesystem::path{"draft2019-09"} / "nested" / "foo-ref-string.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/nested/string.json",
                   std::filesystem::path{"draft2019-09"} / "nested" /
                       "string.json")
  READ_SCHEMA_FILE("http://localhost:1234/different-id-ref-string.json",
                   "different-id-ref-string.json")
  READ_SCHEMA_FILE("http://localhost:1234/urn-ref-string.json",
                   "urn-ref-string.json")
  READ_SCHEMA_FILE("http://localhost:1234/nested-absolute-ref-to-string.json",
                   "nested-absolute-ref-to-string.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/detached-ref.json",
                   std::filesystem::path{"draft2019-09"} / "detached-ref.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/dependentRequired.json",
                   std::filesystem::path{"draft2019-09"} /
                       "dependentRequired.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2019-09/ignore-prefixItems.json",
                   std::filesystem::path{"draft2019-09"} /
                       "ignore-prefixItems.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/prefixItems.json",
                   std::filesystem::path{"draft2020-12"} / "prefixItems.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/metaschema-no-validation.json",
      std::filesystem::path{"draft2020-12"} / "metaschema-no-validation.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/metaschema-optional-vocabulary.json",
      std::filesystem::path{"draft2020-12"} /
          "metaschema-optional-vocabulary.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/integer.json",
                   std::filesystem::path{"draft2020-12"} / "integer.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/detached-dynamicref.json",
      std::filesystem::path{"draft2020-12"} / "detached-dynamicref.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/detached-ref.json",
                   std::filesystem::path{"draft2020-12"} / "detached-ref.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/extendible-dynamic-ref.json",
      std::filesystem::path{"draft2020-12"} / "extendible-dynamic-ref.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/format-assertion-false.json",
      std::filesystem::path{"draft2020-12"} / "format-assertion-false.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/format-assertion-true.json",
      std::filesystem::path{"draft2020-12"} / "format-assertion-true.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/locationIndependentIdentifier.json",
      std::filesystem::path{"draft2020-12"} /
          "locationIndependentIdentifier.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/name-defs.json",
                   std::filesystem::path{"draft2020-12"} / "name-defs.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/ref-and-defs.json",
                   std::filesystem::path{"draft2020-12"} / "ref-and-defs.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/subSchemas.json",
                   std::filesystem::path{"draft2020-12"} / "subSchemas.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/tree.json",
                   std::filesystem::path{"draft2020-12"} / "tree.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/baseUriChangeFolder/"
                   "folderInteger.json",
                   std::filesystem::path{"draft2020-12"} /
                       "baseUriChangeFolder" / "folderInteger.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/"
                   "baseUriChangeFolderInSubschema/folderInteger.json",
                   std::filesystem::path{"draft2020-12"} /
                       "baseUriChangeFolderInSubschema" / "folderInteger.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/baseUriChange/folderInteger.json",
      std::filesystem::path{"draft2020-12"} / "baseUriChange" /
          "folderInteger.json")
  READ_SCHEMA_FILE(
      "http://localhost:1234/draft2020-12/nested/foo-ref-string.json",
      std::filesystem::path{"draft2020-12"} / "nested" / "foo-ref-string.json")
  READ_SCHEMA_FILE("http://localhost:1234/draft2020-12/nested/string.json",
                   std::filesystem::path{"draft2020-12"} / "nested" /
                       "string.json")

#undef READ_SCHEMA_FILE

  return sourcemeta::jsontoolkit::official_resolver(identifier);
}

static auto callback_noop(const sourcemeta::blaze::EvaluationType, bool,
                          const sourcemeta::blaze::Template::value_type &,
                          const sourcemeta::jsontoolkit::WeakPointer &,
                          const sourcemeta::jsontoolkit::WeakPointer &,
                          const sourcemeta::jsontoolkit::JSON &) noexcept
    -> void {}

static auto slugify(const std::string &input, std::ostream &output) -> void {
  for (const auto character : input) {
    output << (std::isalnum(character) ? character : '_');
  }
}

class OfficialTest : public testing::Test {
public:
  explicit OfficialTest(bool test_valid,
                        sourcemeta::blaze::Template test_schema,
                        sourcemeta::jsontoolkit::JSON test_instance)
      : valid{test_valid}, schema{std::move(test_schema)},
        instance{std::move(test_instance)} {}

  auto TestBody() -> void override {
    const auto result{sourcemeta::blaze::evaluate(this->schema, this->instance,
                                                  callback_noop)};
    if (this->valid) {
      EXPECT_TRUE(result);
    } else {
      EXPECT_FALSE(result);
    }
  }

private:
  const bool valid;
  const sourcemeta::blaze::Template schema;
  const sourcemeta::jsontoolkit::JSON instance;
};

static auto register_tests(const std::filesystem::path &subdirectory,
                           const std::string &suite_name,
                           const std::string &default_dialect,
                           const std::set<std::string> &blacklist) -> void {
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator(
           std::filesystem::path{OFFICIAL_SUITE_PATH} / "tests" /
           subdirectory)) {
    if (!entry.is_regular_file()) {
      continue;
    }

    const std::string name{entry.path().stem().string()};
    if (blacklist.contains(name)) {
      continue;
    }

    std::cerr << "-- Parsing: " << entry.path().string() << "\n";
    const sourcemeta::jsontoolkit::JSON suite{
        sourcemeta::jsontoolkit::from_file(entry.path())};
    assert(suite.is_array());
    for (const auto &test : suite.as_array()) {
      assert(test.is_object());
      assert(test.defines("description"));
      assert(test.defines("schema"));
      assert(test.defines("tests"));
      assert(test.at("description").is_string());
      assert(sourcemeta::jsontoolkit::is_schema(test.at("schema")));
      assert(test.at("tests").is_array());

      std::cerr << "    Compiling: " << test.at("description").to_string()
                << "\n";

      for (const auto mode : {sourcemeta::blaze::Mode::FastValidation,
                              sourcemeta::blaze::Mode::Exhaustive}) {
        const auto schema_template{sourcemeta::blaze::compile(
            test.at("schema"), sourcemeta::jsontoolkit::default_schema_walker,
            test_resolver, sourcemeta::blaze::default_schema_compiler, mode,
            default_dialect)};

        std::ostringstream title;
        switch (mode) {
          case sourcemeta::blaze::Mode::FastValidation:
            title << "fast_validation";
            break;
          case sourcemeta::blaze::Mode::Exhaustive:
            title << "exhaustive";
            break;
          default:
            // We should never get here
            assert(false);
        }

        for (const auto &test_case : test.at("tests").as_array()) {
          assert(test_case.is_object());
          assert(test_case.defines("data"));
          assert(test_case.defines("description"));
          assert(test_case.defines("valid"));
          assert(test_case.at("description").is_string());
          assert(test_case.at("valid").is_boolean());

          const auto &instance{test_case.at("data")};
          const bool valid{test_case.at("valid").to_boolean()};

          title << "_";
          slugify(test.at("description").to_string(), title);
          title << "__";
          slugify(test_case.at("description").to_string(), title);

          testing::RegisterTest(
              suite_name.c_str(), title.str().c_str(), nullptr, nullptr,
              __FILE__, __LINE__, [=]() -> OfficialTest * {
                return new OfficialTest(valid, schema_template, instance);
              });
        }
      }
    }
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  try {
    // 2020-12
    register_tests("draft2020-12", "JSONSchemaOfficialSuite_2020_12",
                   "https://json-schema.org/draft/2020-12/schema", {});
    register_tests(
        std::filesystem::path{"draft2020-12"} / "optional",
        "JSONSchemaOfficialSuite_2020_12_Optional",
        "https://json-schema.org/draft/2020-12/schema",
        {// TODO: Enable all tests
         "bignum", "ecmascript-regex", "format-assertion", "non-bmp-regex"});
    register_tests(
        std::filesystem::path{"draft2020-12"} / "optional" / "format",
        "JSONSchemaOfficialSuite_2020_12_Optional_Format",
        "https://json-schema.org/draft/2020-12/schema",
        // TODO: Enable all tests
        {"date-time", "date", "duration", "email", "hostname", "idn-email",
         "idn-hostname", "ipv4", "ipv6", "iri-reference", "iri", "json-pointer",
         "regex", "relative-json-pointer", "time", "uri-reference",
         "uri-template", "uri", "uuid"});

    // 2019-09
    register_tests("draft2019-09", "JSONSchemaOfficialSuite_2019_09",
                   "https://json-schema.org/draft/2019-09/schema", {});
    register_tests(std::filesystem::path{"draft2019-09"} / "optional",
                   "JSONSchemaOfficialSuite_2019_09_Optional",
                   "https://json-schema.org/draft/2019-09/schema",
                   {// TODO: Enable all tests
                    "bignum", "ecmascript-regex", "non-bmp-regex"});
    register_tests(
        std::filesystem::path{"draft2019-09"} / "optional" / "format",
        "JSONSchemaOfficialSuite_2019_09_Optional_Format",
        "https://json-schema.org/draft/2019-09/schema",
        // TODO: Enable all tests
        {"date-time", "date", "duration", "email", "hostname", "idn-email",
         "idn-hostname", "ipv4", "ipv6", "iri-reference", "iri", "json-pointer",
         "regex", "relative-json-pointer", "time", "uri-reference",
         "uri-template", "uri", "uuid"});

    // Draft 7
    register_tests("draft7", "JSONSchemaOfficialSuite_Draft7",
                   "http://json-schema.org/draft-07/schema#", {});
    register_tests(std::filesystem::path{"draft7"} / "optional",
                   "JSONSchemaOfficialSuite_Draft7_Optional",
                   "http://json-schema.org/draft-07/schema#",
                   // TODO: Enable all tests
                   {"bignum", "content", "ecmascript-regex", "non-bmp-regex"});
    register_tests(std::filesystem::path{"draft7"} / "optional" / "format",
                   "JSONSchemaOfficialSuite_Draft7_Optional_Format",
                   "http://json-schema.org/draft-07/schema#",
                   // TODO: Enable all tests
                   {"date-time", "date", "email", "hostname", "idn-email",
                    "idn-hostname", "ipv4", "ipv6", "iri-reference", "iri",
                    "json-pointer", "regex", "relative-json-pointer", "time",
                    "unknown", "uri-reference", "uri-template", "uri"});

    // Draft 6
    register_tests("draft6", "JSONSchemaOfficialSuite_Draft6",
                   "http://json-schema.org/draft-06/schema#", {});
    register_tests(std::filesystem::path{"draft6"} / "optional",
                   "JSONSchemaOfficialSuite_Draft6_Optional",
                   "http://json-schema.org/draft-06/schema#",
                   // TODO: Enable all tests
                   {"bignum", "ecmascript-regex", "non-bmp-regex"});
    register_tests(std::filesystem::path{"draft6"} / "optional" / "format",
                   "JSONSchemaOfficialSuite_Draft6_Optional_Format",
                   "http://json-schema.org/draft-06/schema#",
                   // TODO: Enable all tests
                   {"date-time", "email", "hostname", "ipv4", "ipv6",
                    "json-pointer", "unknown", "uri-reference", "uri-template",
                    "uri"});

    // Draft4
    register_tests("draft4", "JSONSchemaOfficialSuite_Draft4",
                   "http://json-schema.org/draft-04/schema#", {});
    register_tests(std::filesystem::path{"draft4"} / "optional",
                   "JSONSchemaOfficialSuite_Draft4_Optional",
                   "http://json-schema.org/draft-04/schema#",
                   // TODO: Enable all tests
                   {"bignum", "ecmascript-regex", "non-bmp-regex"});
    register_tests(std::filesystem::path{"draft4"} / "optional" / "format",
                   "JSONSchemaOfficialSuite_Draft4_Optional_Format",
                   "http://json-schema.org/draft-04/schema#",
                   // TODO: Enable all tests
                   {"date-time", "email", "hostname", "ipv6"});
  } catch (const sourcemeta::jsontoolkit::SchemaResolutionError &error) {
    std::cerr << error.what() << ": " << error.id() << "\n";
    return EXIT_FAILURE;
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return RUN_ALL_TESTS();
}
