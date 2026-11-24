#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/canonicalizer.h>
#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>   // std::ranges::contains
#include <cstddef>     // std::size_t
#include <filesystem>  // std::filesystem
#include <iostream>    // std::cerr
#include <map>         // std::map
#include <sstream>     // std::ostringstream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::pair
#include <vector>      // std::vector

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

// The meta-schema a document names, compiled once. Resolving and compiling one
// of these costs far more than evaluating it, and every fixture of a dialect
// names the same one
auto compiled_dialect(const sourcemeta::core::JSON::String &uri)
    -> const sourcemeta::blaze::Template & {
  static std::map<sourcemeta::core::JSON::String, sourcemeta::blaze::Template>
      compiled;
  const auto match{compiled.find(uri)};
  if (match != compiled.cend()) {
    return match->second;
  }

  return compiled
      .emplace(uri,
               sourcemeta::blaze::compile(
                   canonicalizer_test_resolver(uri).value(),
                   sourcemeta::core::schema_walker, canonicalizer_test_resolver,
                   sourcemeta::blaze::default_schema_compiler,
                   sourcemeta::blaze::Mode::FastValidation))
      .first->second;
}

// The same dialect can be named in more than one way, and canonicalisation
// settles on one of them: the official spelling of a draft is the one over
// plain HTTP, with the empty fragment that names the document as a whole. A
// fixture may therefore hand in a document naming its dialect one way and
// expect one naming it the other, and both still say the same dialect
auto dialect_identity(const sourcemeta::core::JSON::String &uri)
    -> sourcemeta::core::JSON::String {
  auto result{uri};
  if (result.starts_with("https://")) {
    result.replace(0, 8, "http://");
  }

  if (result.ends_with('#')) {
    result.pop_back();
  }

  return result;
}

// A document that is nothing but a boolean has nowhere to say which dialect it
// is written in, and neither has one that is nothing but a reference, as a
// reference of these dialects overrides whatever sits beside it, the dialect
// the document names included
auto names_no_dialect(const sourcemeta::core::JSON &schema) -> bool {
  return schema.is_boolean() ||
         (schema.is_object() && schema.size() == 1 && schema.defines("$ref"));
}

// Whether the document says for itself which dialect it is written in
auto names_dialect(const sourcemeta::core::JSON &schema) -> bool {
  return schema.is_object() && schema.defines("$schema");
}

// Which keywords put what they hold to the instance in hand every time,
// without the instance moving on to a part of itself
auto applies_in_place_always(const sourcemeta::core::SchemaKeywordType type)
    -> bool {
  using Type = sourcemeta::core::SchemaKeywordType;
  return type == Type::ApplicatorElementsInPlace ||
         type == Type::ApplicatorValueOrElementsInPlace ||
         type == Type::ApplicatorValueInPlaceNegate;
}

// The innermost subschema that holds the given one, if any
auto enclosing_subschema(
    const std::vector<sourcemeta::core::WeakPointer> &subschemas,
    const sourcemeta::core::WeakPointer &pointer)
    -> const sourcemeta::core::WeakPointer * {
  const sourcemeta::core::WeakPointer *result{nullptr};
  for (const auto &candidate : subschemas) {
    if (pointer.size() > candidate.size() && pointer.starts_with(candidate) &&
        (result == nullptr || candidate.size() > result->size())) {
      result = &candidate;
    }
  }

  return result;
}

// A reference to the document it sits in asserts whatever that document
// asserts, so a document that arrives back at itself without the instance
// moving never reaches a verdict, and no instance can be put to it however
// many a fixture lists. The way back is a reference, which is followed every
// time, or a keyword that puts what it holds to the instance in hand. A
// reference reached by moving into a part of the instance is a recursive
// document rather than one of these, and every instance put to it reaches a
// verdict in the end
auto never_reaches_a_verdict(const sourcemeta::core::JSON &schema,
                             const std::string_view default_dialect) -> bool {
  if (!schema.is_object()) {
    return false;
  }

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References, schema,
      sourcemeta::core::schema_walker, canonicalizer_test_resolver,
      default_dialect};

  std::vector<sourcemeta::core::WeakPointer> subschemas;
  frame.for_each_subschema(
      [&subschemas](const sourcemeta::core::SchemaFrame::Location &location)
          -> void { subschemas.push_back(location.pointer); });

  std::vector<
      std::pair<sourcemeta::core::WeakPointer, sourcemeta::core::WeakPointer>>
      steps;
  for (const auto &subschema : subschemas) {
    const auto *parent{enclosing_subschema(subschemas, subschema)};
    if (parent == nullptr) {
      continue;
    }

    const auto &token{subschema.at(parent->size())};
    const auto location{frame.traverse(*parent)};
    if (!token.is_property() || !location.has_value()) {
      continue;
    }

    const auto &vocabularies{frame.vocabularies(location.value().get(),
                                                canonicalizer_test_resolver)};
    if (applies_in_place_always(
            sourcemeta::core::schema_walker(token.to_property(), vocabularies)
                .type)) {
      steps.emplace_back(*parent, subschema);
    }
  }

  frame.for_each_reference(
      [&steps, &frame](
          const sourcemeta::core::SchemaReferenceType type,
          const sourcemeta::core::WeakPointer &origin,
          const sourcemeta::core::SchemaFrame::Reference &reference) -> void {
        if (type != sourcemeta::core::SchemaReferenceType::Static ||
            origin.empty() || !origin.back().is_property() ||
            origin.back().to_property() != "$ref") {
          return;
        }

        const auto destination{frame.traverse(reference.destination)};
        if (destination.has_value()) {
          steps.emplace_back(origin.initial(),
                             destination.value().get().pointer);
        }
      });

  std::vector<sourcemeta::core::WeakPointer> reached;
  std::vector<sourcemeta::core::WeakPointer> pending{
      sourcemeta::core::EMPTY_WEAK_POINTER};
  while (!pending.empty()) {
    const auto current{pending.back()};
    pending.pop_back();
    for (const auto &step : steps) {
      if (step.first != current) {
        continue;
      }

      if (step.second.empty()) {
        return true;
      }

      if (!std::ranges::contains(reached, step.second)) {
        reached.push_back(step.second);
        pending.push_back(step.second);
      }
    }
  }

  return false;
}

// What the directory a fixture sits in says its dialect is, for a document
// with nowhere to say it. Whether a document of that kind is a schema of the
// dialect at all is for the meta-schema of the dialect to say: a boolean is
// one only from Draft 6 on, while a document that is nothing but a reference
// is one in every dialect of the suite
auto implied_dialect(const std::string &dialect) -> std::string_view {
  if (dialect == "draft7") {
    return "http://json-schema.org/draft-07/schema#";
  }

  if (dialect == "draft6") {
    return "http://json-schema.org/draft-06/schema#";
  }

  if (dialect == "draft4") {
    return "http://json-schema.org/draft-04/schema#";
  }

  if (dialect == "draft3") {
    return "http://json-schema.org/draft-03/schema#";
  }

  return "";
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

auto canonicalize_schema(const sourcemeta::core::JSON &schema,
                         const std::string_view default_dialect)
    -> sourcemeta::core::JSON {
  auto document{schema};
  sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                  canonicalizer_test_resolver, default_dialect);
  return document;
}

// Whichever way a schema is spelled, it has to accept and reject the same
// instances before and after canonicalisation, which is the whole promise of a
// canonical form. Every disagreement is collected rather than asserted on the
// spot, so that the report names the document and the instance instead of only
// saying that something was false
auto check_instances(const sourcemeta::core::JSON &test,
                     const std::string_view side,
                     const sourcemeta::core::JSON &schema,
                     const std::string_view default_dialect,
                     sourcemeta::core::JSON &disagreements) -> void {
  const auto compiled{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, canonicalizer_test_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, default_dialect)};

  sourcemeta::blaze::Evaluator evaluator;
  for (const auto &instance : test.at("examples").as_array()) {
    if (!evaluator.validate(compiled, instance)) {
      auto disagreement{sourcemeta::core::JSON::make_object()};
      disagreement.assign("document", sourcemeta::core::JSON{side});
      disagreement.assign("expected", sourcemeta::core::JSON{"valid"});
      disagreement.assign("instance", instance);
      disagreements.push_back(std::move(disagreement));
    }
  }

  for (const auto &instance : test.at("counterExamples").as_array()) {
    if (evaluator.validate(compiled, instance)) {
      auto disagreement{sourcemeta::core::JSON::make_object()};
      disagreement.assign("document", sourcemeta::core::JSON{side});
      disagreement.assign("expected", sourcemeta::core::JSON{"invalid"});
      disagreement.assign("instance", instance);
      disagreements.push_back(std::move(disagreement));
    }
  }
}

// A fixture is the document to canonicalise, the document it canonicalises to,
// and the instances that say what both of them mean. Anything more would be an
// expectation the runner does not read, which would otherwise go unnoticed
auto check_shape(const sourcemeta::core::JSON &test, const std::string &dialect)
    -> void {
  EXPECT_TRUE(test.is_object());

  // A fixture whose input is a document the dialect itself refuses says so,
  // and that is the only thing it may say beyond the four the rest carry
  const auto refused{test.defines("invalidSchema")};
  if (refused) {
    EXPECT_EQ(test.at("invalidSchema"), sourcemeta::core::JSON{true});
    EXPECT_EQ(test.size(), 5);
  } else {
    EXPECT_EQ(test.size(), 4);
  }
  EXPECT_TRUE(test.defines("schema"));
  EXPECT_TRUE(test.defines("expected"));
  EXPECT_TRUE(test.defines("examples"));
  EXPECT_TRUE(test.defines("counterExamples"));
  EXPECT_TRUE(test.at("examples").is_array());
  EXPECT_TRUE(test.at("counterExamples").is_array());

  // From Draft 6 on a boolean is a schema in its own right, so a document can
  // be one, and a document can also be nothing but a reference. Neither has
  // room to say which dialect it is written in, so its directory says that
  // instead, and a directory the runner knows no dialect for can hold no
  // fixture of either kind. Rewriting such a document gives it nothing to
  // name a dialect with either, however much else the result says
  if (names_no_dialect(test.at("schema"))) {
    EXPECT_FALSE(names_dialect(test.at("expected")));
    EXPECT_FALSE(refused);
    EXPECT_FALSE(implied_dialect(dialect).empty());
    return;
  }

  EXPECT_TRUE(test.at("schema").is_object());
  EXPECT_TRUE(test.at("expected").is_object());

  // Canonicalisation rewrites a document within the dialect it is written in,
  // so both documents say which dialect that is and both say the same one,
  // whichever way each of them spells it. A result on another dialect would be
  // a document about something else
  EXPECT_TRUE(test.at("schema").defines("$schema"));
  EXPECT_TRUE(test.at("schema").at("$schema").is_string());
  EXPECT_TRUE(test.at("expected").defines("$schema"));
  EXPECT_TRUE(test.at("expected").at("$schema").is_string());
  EXPECT_EQ(dialect_identity(test.at("expected").at("$schema").to_string()),
            dialect_identity(test.at("schema").at("$schema").to_string()));
}

// A document the pass turns down has no result to compare and no instance to
// put to it, so such a fixture says what it is turned down with and nothing
// else
auto check_refusal_shape(const sourcemeta::core::JSON &test,
                         const std::string &dialect) -> void {
  EXPECT_TRUE(test.is_object());
  EXPECT_EQ(test.size(), 2);
  EXPECT_TRUE(test.defines("schema"));
  EXPECT_TRUE(test.at("error").is_string());

  // The pass has to know which dialect the document is written in before it
  // can turn it down, and a document whose reference overrides the dialect it
  // names has nowhere to say one
  EXPECT_TRUE(names_dialect(test.at("schema")) ||
              !implied_dialect(dialect).empty());
}

auto run_refusal_test(const sourcemeta::core::JSON &test,
                      const std::string &dialect) -> void {
  check_refusal_shape(test, dialect);

  const auto default_dialect{names_dialect(test.at("schema"))
                                 ? std::string_view{}
                                 : implied_dialect(dialect)};

  // The document is handed back as it came in, so the caller is left holding
  // what they handed over rather than something half rewritten
  auto document{test.at("schema")};
  try {
    sourcemeta::blaze::canonicalize(document, sourcemeta::core::schema_walker,
                                    canonicalizer_test_resolver,
                                    default_dialect);
    FAIL();
  } catch (const sourcemeta::core::SchemaError &error) {
    EXPECT_EQ(sourcemeta::core::JSON::String{error.what()},
              test.at("error").to_string());
    EXPECT_EQ(document, test.at("schema"));
  } catch (...) {
    FAIL();
  }
}

auto run_canonicalizer_test(const sourcemeta::core::JSON &test,
                            const std::string &dialect) -> void {
  if (test.is_object() && test.defines("error")) {
    run_refusal_test(test, dialect);
    return;
  }

  check_shape(test, dialect);

  // A document with nowhere to name a dialect of its own leaves the one its
  // directory names as what every operation below is told
  const auto default_dialect{names_no_dialect(test.at("schema"))
                                 ? implied_dialect(dialect)
                                 : std::string_view{}};
  const auto refused{test.defines("invalidSchema")};
  const auto document{canonicalize_schema(test.at("schema"), default_dialect)};

  // The instances have their say before any expectation about the shape of the
  // result. An `expected` that turns out wrong would otherwise abort the test
  // first and hide whether the document still means what it did, which is the
  // one thing worth knowing
  //
  // A document that accepts every instance has no counter-example to give, and
  // one that accepts none has no example. A fixture with neither says that no
  // instance can be put to these documents at all, which is true of the ones
  // that negate a reference to themselves: both documents are schemas of the
  // dialect, and neither ever reaches a verdict
  if (!test.at("examples").empty() || !test.at("counterExamples").empty()) {
    auto disagreements{sourcemeta::core::JSON::make_array()};
    // What the dialect refuses is not a schema to put an instance to, and
    // neither is a document that asserts whatever it itself asserts, so a
    // fixture of either kind says what its result means and nothing more
    if (!refused &&
        !never_reaches_a_verdict(test.at("schema"), default_dialect)) {
      check_instances(test, "schema", test.at("schema"), default_dialect,
                      disagreements);
    }

    if (!never_reaches_a_verdict(document, default_dialect)) {
      check_instances(test, "expected", document, default_dialect,
                      disagreements);
    }
    EXPECT_EQ(disagreements, sourcemeta::core::JSON::make_array());
  }

  expect_equal_with_ordering(document, test.at("expected"));

  sourcemeta::blaze::Evaluator evaluator;

  // Both documents are schemas of the dialect they name, which is what makes
  // them schemas at all. A fixture that handed in anything else would have the
  // canonicaliser answering for something nothing describes
  const auto &dialect_metaschema{
      compiled_dialect(names_no_dialect(test.at("schema"))
                           ? sourcemeta::core::JSON::String{default_dialect}
                           : test.at("schema").at("$schema").to_string())};
  if (refused) {
    EXPECT_FALSE(evaluator.validate(dialect_metaschema, test.at("schema")));
  } else {
    EXPECT_TRUE(evaluator.validate(dialect_metaschema, test.at("schema")));
  }
  EXPECT_TRUE(evaluator.validate(dialect_metaschema, document));

  // The canonicaliser must never emit a document that the canonical
  // meta-schema of its dialect rejects, so a fixture has no way of saying
  // that it did
  EXPECT_TRUE(evaluator.validate(compiled_metaschema(dialect), document));

  // A canonical form that is not a fixpoint would mean the same schema has
  // more than one canonical spelling, down to the order the result comes in
  expect_equal_with_ordering(canonicalize_schema(document, default_dialect),
                             document);
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
