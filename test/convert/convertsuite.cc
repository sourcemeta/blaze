#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/convert.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <algorithm>   // std::ranges::find, std::ranges::any_of
#include <array>       // std::array
#include <cstddef>     // std::size_t
#include <filesystem>  // std::filesystem
#include <iostream>    // std::cerr
#include <sstream>     // std::ostringstream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::pair
#include <vector>      // std::vector

namespace {

// Every key a fixture may declare. Anything else is a mistake that would
// otherwise go unnoticed, as the runner would simply not read it
// NOLINTBEGIN(cert-err58-cpp,bugprone-throwing-static-initialization)
const std::vector<std::string> KNOWN_KEYS{
    "schema",          "result",     "errors",         "examples",
    "counterExamples", "evaluation", "defaultDialect", "defaultId",
    "isMetaschema",    "resolver"};

// What a fixture may say about evaluating its schema at all. Leaving it out
// means every schema the fixture names accepts and rejects something
const std::vector<std::string> KNOWN_EVALUATIONS{"nothing-valid",
                                                 "not-evaluatable"};

const std::vector<std::string> KNOWN_ERROR_KEYS{"type", "identifier",
                                                "location"};

// Which error a fixture expects conversion to raise. Leaving it out means the
// reference was one the conversion had to carry and could not
const std::vector<std::string> KNOWN_ERROR_TYPES{"invalid-reference"};
// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

// A schema that no evaluator can take, such as one whose reference does not
// point at a schema, cannot be asked about instances at all
auto is_evaluatable(const sourcemeta::core::JSON &test) -> bool {
  const auto *evaluation{test.try_at("evaluation")};
  return evaluation == nullptr || evaluation->to_string() != "not-evaluatable";
}

struct Target {
  std::string_view name;
  sourcemeta::blaze::ConvertTarget value;
};

// Every target that conversion takes, as a fixture has to account for all of
// them rather than for the ones whoever wrote it happened to think of
constexpr std::array<Target, 5> TARGETS{
    {{.name = "draft4", .value = sourcemeta::blaze::ConvertTarget::Draft4},
     {.name = "draft6", .value = sourcemeta::blaze::ConvertTarget::Draft6},
     {.name = "draft7", .value = sourcemeta::blaze::ConvertTarget::Draft7},
     {.name = "2019-09",
      .value = sourcemeta::blaze::ConvertTarget::Draft201909},
     {.name = "2020-12",
      .value = sourcemeta::blaze::ConvertTarget::Draft202012}}};

// Conversion decides where a keyword goes as much as whether it is there at
// all, so the order of the result is part of what a fixture blesses. Both
// sides carry the target they came from, as a fixture accounts for five of
// them and a bare pair of schemas does not say which one went wrong
auto expect_equal_with_ordering(const std::string_view target,
                                const sourcemeta::core::JSON &actual,
                                const sourcemeta::core::JSON &expected)
    -> void {
  auto actual_entry{sourcemeta::core::JSON::make_object()};
  actual_entry.assign("target", sourcemeta::core::JSON{target});
  actual_entry.assign("schema", actual);
  auto expected_entry{sourcemeta::core::JSON::make_object()};
  expected_entry.assign("target", sourcemeta::core::JSON{target});
  expected_entry.assign("schema", expected);

  EXPECT_EQ(actual_entry, expected_entry);
  std::ostringstream actual_stream;
  std::ostringstream expected_stream;
  sourcemeta::core::prettify(actual_entry, actual_stream);
  sourcemeta::core::prettify(expected_entry, expected_stream);
  EXPECT_EQ(actual_stream.str(), expected_stream.str());
}

auto make_resolver(const sourcemeta::core::JSON &test)
    -> sourcemeta::core::SchemaResolver {
  if (!test.defines("resolver")) {
    return sourcemeta::core::schema_resolver;
  }

  const auto &registry{test.at("resolver")};
  return [registry](const std::string_view identifier)
             -> sourcemeta::core::SchemaResolverResult {
    const auto *match{
        registry.try_at(sourcemeta::core::JSON::String{identifier})};
    if (match != nullptr) {
      return *match;
    }

    return sourcemeta::core::schema_resolver(identifier);
  };
}

// Conversion keeps views into the default dialect and the default identifier
// for as long as it runs, so the caller owns both
struct Inputs {
  sourcemeta::core::JSON::String default_dialect;
  sourcemeta::core::JSON::String default_id;
  bool is_metaschema;
};

auto make_inputs(const sourcemeta::core::JSON &test) -> Inputs {
  Inputs inputs;
  const auto *raw_dialect{test.try_at("defaultDialect")};
  if (raw_dialect != nullptr) {
    inputs.default_dialect = raw_dialect->to_string();
  }

  const auto *raw_id{test.try_at("defaultId")};
  if (raw_id != nullptr) {
    inputs.default_id = raw_id->to_string();
  }

  const auto *raw_metaschema{test.try_at("isMetaschema")};
  inputs.is_metaschema =
      raw_metaschema != nullptr && raw_metaschema->to_boolean();
  return inputs;
}

auto convert_schema(const sourcemeta::core::JSON &schema,
                    const sourcemeta::core::SchemaResolver &resolver,
                    const Inputs &inputs, const Target &target)
    -> sourcemeta::core::JSON {
  auto document{schema};
  sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,
                             resolver, target.value, inputs.default_dialect,
                             inputs.default_id, inputs.is_metaschema);
  return document;
}

// Every key a fixture declares has to be one the runner reads, and every
// target has to be accounted for exactly once, either as a result or as an
// error
auto check_shape(const sourcemeta::core::JSON &test) -> void {
  for (const auto &entry : test.as_object()) {
    EXPECT_TRUE(std::ranges::find(KNOWN_KEYS, entry.first) !=
                KNOWN_KEYS.cend());
  }

  EXPECT_TRUE(test.defines("schema"));
  EXPECT_TRUE(test.defines("result"));
  EXPECT_TRUE(test.defines("examples"));
  EXPECT_TRUE(test.defines("counterExamples"));

  // A boolean schema cannot carry both kinds of instance, so it belongs in a
  // hand-written test rather than here
  EXPECT_TRUE(test.at("schema").is_object());

  const auto *evaluation{test.try_at("evaluation")};
  if (evaluation != nullptr) {
    EXPECT_TRUE(std::ranges::find(KNOWN_EVALUATIONS, evaluation->to_string()) !=
                KNOWN_EVALUATIONS.cend());
  }

  EXPECT_TRUE(test.at("examples").is_array());
  EXPECT_TRUE(test.at("counterExamples").is_array());

  // A schema that accepts nothing has to say so and then carry no example,
  // and a schema that says nothing about it has to carry one
  EXPECT_EQ(test.at("examples").empty(), evaluation != nullptr);

  // Only a schema that cannot be evaluated at all gets to reject nothing
  EXPECT_EQ(test.at("counterExamples").empty(), !is_evaluatable(test));

  const auto &results{test.at("result")};
  EXPECT_TRUE(results.is_object());
  for (const auto &entry : results.as_object()) {
    EXPECT_TRUE(std::ranges::any_of(TARGETS, [&entry](const auto &target) {
      return target.name == entry.first;
    }));
  }

  if (test.defines("errors")) {
    for (const auto &entry : test.at("errors").as_object()) {
      EXPECT_TRUE(std::ranges::any_of(TARGETS, [&entry](const auto &target) {
        return target.name == entry.first;
      }));
      EXPECT_FALSE(results.defines(entry.first));
      for (const auto &detail : entry.second.as_object()) {
        EXPECT_TRUE(std::ranges::find(KNOWN_ERROR_KEYS, detail.first) !=
                    KNOWN_ERROR_KEYS.cend());
      }

      const auto *type{entry.second.try_at("type")};
      if (type != nullptr) {
        EXPECT_TRUE(std::ranges::find(KNOWN_ERROR_TYPES, type->to_string()) !=
                    KNOWN_ERROR_TYPES.cend());
      }
    }
  }

  for (const auto &target : TARGETS) {
    const sourcemeta::core::JSON::String name{target.name};
    EXPECT_TRUE(results.defines(name) ||
                (test.defines("errors") && test.at("errors").defines(name)));
  }
}

auto check_error(const sourcemeta::core::JSON &test,
                 const sourcemeta::core::SchemaResolver &resolver,
                 const Inputs &inputs, const Target &target,
                 const sourcemeta::core::JSON &expected) -> void {
  const auto *type{expected.try_at("type")};
  const auto invalid{type != nullptr &&
                     type->to_string() == "invalid-reference"};

  try {
    [[maybe_unused]] const auto document{
        convert_schema(test.at("schema"), resolver, inputs, target)};
    FAIL();
  } catch (const sourcemeta::blaze::ConvertInvalidReferenceError &error) {
    EXPECT_TRUE(invalid);
    EXPECT_STREQ(error.what(), "The reference does not point to a schema");
    EXPECT_EQ(error.identifier(), expected.at("identifier").to_string());
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              expected.at("location").to_string());
  } catch (const sourcemeta::blaze::ConvertBrokenReferenceError &error) {
    EXPECT_FALSE(invalid);
    EXPECT_STREQ(error.what(), "The reference broke after transformation");
    EXPECT_EQ(error.identifier(), expected.at("identifier").to_string());
    EXPECT_EQ(sourcemeta::core::to_string(error.location()),
              expected.at("location").to_string());
  }
}

// Whichever way a schema is spelled, it has to accept and reject the same
// instances before and after conversion, which is the actual promise of an
// upgrade. Every disagreement is collected so that the report names the
// target and the instance rather than only saying that something was false
auto check_instances(const sourcemeta::core::JSON &schema,
                     const std::string_view target,
                     const sourcemeta::core::JSON &test,
                     const sourcemeta::core::SchemaResolver &resolver,
                     const Inputs &inputs,
                     sourcemeta::core::JSON &disagreements) -> void {
  const auto compiled{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker, resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, inputs.default_dialect,
      inputs.default_id)};

  sourcemeta::blaze::Evaluator evaluator;
  for (const auto &instance : test.at("examples").as_array()) {
    if (!evaluator.validate(compiled, instance)) {
      auto disagreement{sourcemeta::core::JSON::make_object()};
      disagreement.assign("target", sourcemeta::core::JSON{target});
      disagreement.assign("expected", sourcemeta::core::JSON{"valid"});
      disagreement.assign("instance", instance);
      disagreements.push_back(std::move(disagreement));
    }
  }

  for (const auto &instance : test.at("counterExamples").as_array()) {
    if (evaluator.validate(compiled, instance)) {
      auto disagreement{sourcemeta::core::JSON::make_object()};
      disagreement.assign("target", sourcemeta::core::JSON{target});
      disagreement.assign("expected", sourcemeta::core::JSON{"invalid"});
      disagreement.assign("instance", instance);
      disagreements.push_back(std::move(disagreement));
    }
  }
}

// A document that names more than one dialect cannot be checked this way: an
// outer meta-schema describes its own dialect, and it has no way to defer to a
// resource that declares a dialect of its own
auto names_one_dialect(const sourcemeta::core::JSON &document) -> bool {
  std::vector<sourcemeta::core::JSON::String> dialects;
  const auto collect{
      [&dialects](const sourcemeta::core::JSON &node, auto &self) -> void {
        if (node.is_object()) {
          const auto *dialect{node.try_at("$schema")};
          if (dialect != nullptr && dialect->is_string() &&
              std::ranges::find(dialects, dialect->to_string()) ==
                  dialects.cend()) {
            dialects.push_back(dialect->to_string());
          }

          for (const auto &entry : node.as_object()) {
            self(entry.second, self);
          }
        } else if (node.is_array()) {
          for (const auto &item : node.as_array()) {
            self(item, self);
          }
        }
      }};

  collect(document, collect);
  return dialects.size() <= 1;
}

// Whether a document is a schema of the dialect it claims to be
auto meets_metaschema(const sourcemeta::core::JSON &document,
                      const sourcemeta::core::SchemaResolver &resolver,
                      const Inputs &inputs) -> bool {
  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      document,
      sourcemeta::core::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      sourcemeta::core::SchemaFrame::IdentifierMode::Fallback};

  // Compiling a meta-schema is far more expensive than evaluating one, and a
  // suite of this size names only a handful of distinct ones
  static std::vector<
      std::pair<sourcemeta::core::JSON, sourcemeta::blaze::Template>>
      compiled_metaschemas;

  const auto &metaschema{frame.metaschema(resolver)};
  std::size_t index{0};
  while (index < compiled_metaschemas.size() &&
         compiled_metaschemas.at(index).first != metaschema) {
    index += 1;
  }

  if (index == compiled_metaschemas.size()) {
    compiled_metaschemas.emplace_back(
        metaschema, sourcemeta::blaze::compile(
                        metaschema, sourcemeta::core::schema_walker, resolver,
                        sourcemeta::blaze::default_schema_compiler,
                        sourcemeta::blaze::Mode::FastValidation));
  }

  const auto &compiled{compiled_metaschemas.at(index).second};

  sourcemeta::blaze::Evaluator evaluator;
  return evaluator.validate(compiled, document);
}

// Whatever conversion produces has to be a schema of the dialect it now claims
// to be, which is the one thing the instances cannot tell us. A document that
// did not meet its own meta-schema to begin with is left out, as conversion
// does not answer for what it was handed
auto check_metaschema(const std::string_view target,
                      const sourcemeta::core::JSON &document,
                      const sourcemeta::core::JSON &input,
                      const sourcemeta::core::SchemaResolver &resolver,
                      const Inputs &inputs) -> void {
  if (!names_one_dialect(document) || !names_one_dialect(input) ||
      !meets_metaschema(input, resolver, inputs)) {
    return;
  }

  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign("target", sourcemeta::core::JSON{target});
  entry.assign("meetsMetaschema", sourcemeta::core::JSON{meets_metaschema(
                                      document, resolver, inputs)});
  auto expected{sourcemeta::core::JSON::make_object()};
  expected.assign("target", sourcemeta::core::JSON{target});
  expected.assign("meetsMetaschema", sourcemeta::core::JSON{true});
  EXPECT_EQ(entry, expected);
}

auto run_convert_test(const sourcemeta::core::JSON &test) -> void {
  check_shape(test);

  const auto resolver{make_resolver(test)};
  const auto inputs{make_inputs(test)};
  const auto &results{test.at("result")};

  const auto evaluatable{is_evaluatable(test)};
  auto disagreements{sourcemeta::core::JSON::make_array()};
  if (evaluatable) {
    check_instances(test.at("schema"), "input", test, resolver, inputs,
                    disagreements);
  }

  std::vector<sourcemeta::core::JSON> evaluated;
  for (const auto &target : TARGETS) {
    const sourcemeta::core::JSON::String name{target.name};
    if (test.defines("errors") && test.at("errors").defines(name)) {
      check_error(test, resolver, inputs, target, test.at("errors").at(name));
      continue;
    }

    const auto document{
        convert_schema(test.at("schema"), resolver, inputs, target)};
    const auto &expected{results.at(name)};
    if (expected.is_null()) {
      expect_equal_with_ordering(target.name, document, test.at("schema"));
      continue;
    }

    expect_equal_with_ordering(target.name, document, expected);
    check_metaschema(target.name, document, test.at("schema"), resolver,
                     inputs);

    // A target that leaves the schema alone has to say so with `null`, rather
    // than with a copy that silently stops matching the input it came from
    EXPECT_NE(document, test.at("schema"));

    // Conversion that keeps finding work to do on its own output never
    // reaches the dialect it claims to have reached
    expect_equal_with_ordering(
        target.name, convert_schema(document, resolver, inputs, target),
        document);

    if (!evaluatable ||
        std::ranges::find(evaluated, document) != evaluated.cend()) {
      continue;
    }

    check_instances(document, target.name, test, resolver, inputs,
                    disagreements);
    evaluated.push_back(document);
  }

  EXPECT_EQ(disagreements, sourcemeta::core::JSON::make_array());
}

auto register_tests(const std::filesystem::path &directory) -> std::size_t {
  std::size_t count{0};
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::recursive_directory_iterator{directory}) {
    if (!entry.is_regular_file() || entry.path().extension() != ".json") {
      continue;
    }

    const auto suite{entry.path().parent_path().filename().string()};
    std::ostringstream name;
    for (const auto character : entry.path().stem().string()) {
      name << (character == '-' ? '_' : character);
    }

    const auto test{sourcemeta::core::read_json(entry.path())};
    sourcemeta::core::test_register(
        "ConvertSuite_" + suite, name.str(), __FILE__, __LINE__,
        [test]() -> void { run_convert_test(test); });
    count += 1;
  }

  return count;
}

} // namespace

auto main(int argc, char **argv) -> int {
  const auto count{register_tests(std::filesystem::path{CONVERT_SUITE_PATH})};
  // A fixture in the wrong place, or with the wrong extension, would otherwise
  // never run and nobody would notice
  if (count == 0) {
    std::cerr << "No convert fixtures found at " << CONVERT_SUITE_PATH << "\n";
    return 1;
  }

  return sourcemeta::core::test_run(argc, argv);
}
