#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/canonicalizer.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <cstddef>    // std::size_t
#include <filesystem> // std::filesystem
#include <iostream>   // std::cerr
#include <map>        // std::map
#include <sstream>    // std::ostringstream
#include <string>     // std::string

#include "canonicalizer_test_utils.h"

namespace {

// The directory a fixture sits in names the dialect it is written in, and the
// canonical meta-schema of that dialect goes by the same spelling. Compiling
// one is far more expensive than evaluating it, and a suite that grows a
// dialect at a time names only a handful of them. A node-based container keeps
// what it hands out valid once another dialect joins
auto compiled_metaschema(const std::string &dialect)
    -> const sourcemeta::blaze::Template & {
  static std::map<std::string, sourcemeta::blaze::Template> compiled;
  const auto match{compiled.find(dialect)};
  if (match != compiled.cend()) {
    return match->second;
  }

  return compiled
      .emplace(dialect, sourcemeta::blaze::compile(
                            sourcemeta::core::read_json(
                                std::filesystem::path{SCHEMAS_PATH} /
                                ("canonical-" + dialect + ".json")),
                            sourcemeta::core::schema_walker,
                            sourcemeta::core::schema_resolver,
                            sourcemeta::blaze::default_schema_compiler))
      .first->second;
}

auto prettify(const sourcemeta::core::JSON &document) -> std::string {
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  return stream.str();
}

// Canonicalisation decides where a keyword goes as much as whether it is there
// at all, so the order of the result is part of what a fixture blesses
auto expect_equal_with_ordering(const sourcemeta::core::JSON &actual,
                                const sourcemeta::core::JSON &expected)
    -> void {
  EXPECT_EQ(actual, expected);
  EXPECT_EQ(prettify(actual), prettify(expected));
}

auto canonicalize_schema(const sourcemeta::core::JSON &schema)
    -> sourcemeta::core::JSON {
  auto document{schema};
  sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver);
  return document;
}

// A fixture is the document to canonicalise and the document it canonicalises
// to, and nothing else. Anything more would be an expectation the runner does
// not read, which would otherwise go unnoticed
auto check_shape(const sourcemeta::core::JSON &test) -> void {
  EXPECT_TRUE(test.is_object());
  EXPECT_EQ(test.size(), 2);
  EXPECT_TRUE(test.defines("schema"));
  EXPECT_TRUE(test.defines("expected"));

  // A boolean schema has no keyword to canonicalise and no object to compare,
  // so it belongs in a hand-written test rather than here
  EXPECT_TRUE(test.at("schema").is_object());
  EXPECT_TRUE(test.at("expected").is_object());

  // Canonicalisation rewrites a document within the dialect it is written in,
  // so both documents say which dialect that is and both say the same one. A
  // result on another dialect would be a document about something else
  EXPECT_TRUE(test.at("schema").defines("$schema"));
  EXPECT_TRUE(test.at("schema").at("$schema").is_string());
  EXPECT_TRUE(test.at("expected").defines("$schema"));
  EXPECT_EQ(test.at("expected").at("$schema"), test.at("schema").at("$schema"));
}

auto run_canonicalizer_test(const sourcemeta::core::JSON &test,
                            const std::string &dialect) -> void {
  check_shape(test);

  const auto document{canonicalize_schema(test.at("schema"))};
  expect_equal_with_ordering(document, test.at("expected"));

  // The canonicaliser must never emit a document that the canonical
  // meta-schema of its dialect rejects, so a fixture has no way of saying
  // that it did
  sourcemeta::blaze::Evaluator evaluator;
  EXPECT_TRUE(evaluator.validate(compiled_metaschema(dialect), document));

  // A canonical form that is not a fixpoint would mean the same schema has
  // more than one canonical spelling, down to the order the result comes in
  expect_equal_with_ordering(canonicalize_schema(document), document);
}

auto register_tests(const std::filesystem::path &directory) -> std::size_t {
  std::size_t count{0};
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::recursive_directory_iterator{directory}) {
    if (!entry.is_regular_file() || entry.path().extension() != ".json") {
      continue;
    }

    const auto dialect{entry.path().parent_path().filename().string()};
    std::ostringstream name;
    for (const auto character : entry.path().stem().string()) {
      name << (character == '-' ? '_' : character);
    }

    const auto test{sourcemeta::core::read_json(entry.path())};
    sourcemeta::core::test_register(
        "CanonicalizerSuite_" + dialect, name.str(), __FILE__, __LINE__,
        [test, dialect]() -> void { run_canonicalizer_test(test, dialect); });
    count += 1;
  }

  return count;
}

} // namespace

auto main(int argc, char **argv) -> int {
  const auto count{
      register_tests(std::filesystem::path{CANONICALIZER_SUITE_PATH})};
  // A fixture in the wrong place, or with the wrong extension, would otherwise
  // never run and nobody would notice
  if (count == 0) {
    std::cerr << "No canonicalizer fixtures found at "
              << CANONICALIZER_SUITE_PATH << "\n";
    return 1;
  }

  return sourcemeta::core::test_run(argc, argv);
}
