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
#include <optional>    // std::optional, std::nullopt
#include <set>         // std::set
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
    "schema",          "result",   "errors",         "examples",
    "counterExamples", "resolver", "defaultDialect", "defaultId"};

const std::vector<std::string> KNOWN_ERROR_KEYS{"type", "identifier",
                                                "location"};

// Which error a fixture expects conversion to raise. Leaving it out means the
// reference was one the conversion had to carry and could not
// A reference that stops resolving because a rule moved the schema it named is
// not something a fixture may expect. Rules say where they moved a schema so
// that the references reaching it follow, which makes such a reference always
// repairable, and accepting one here would write that omission down as the
// intended outcome. A reference that never named a schema to begin with is a
// different matter, as nothing in the conversion can repair the input
const std::vector<std::string> KNOWN_ERROR_TYPES{
    "invalid-reference", "unsupported-metaschema", "unsupported-dialect"};
// NOLINTEND(cert-err58-cpp,bugprone-throwing-static-initialization)

// A refused fixture carries no `result` at all, and this stands in for one so
// that the checks can read it without copying an object per test
// NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
const sourcemeta::core::JSON NO_RESULTS{sourcemeta::core::JSON::make_object()};

// Spelled out here, as `ladder_position` below spells out the ladder, so that
// the suite says independently what it expects. OpenAPI 3.1 publishes its
// dialect at three URIs naming documents that differ only in formatting, and a
// document on any of them sits on the last rung
// NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
constexpr std::array<std::string_view, 3> OPENAPI_3_1_DIALECTS{
    {"https://spec.openapis.org/oas/3.1/dialect/base",
     "https://spec.openapis.org/oas/3.1/dialect/2024-10-25",
     "https://spec.openapis.org/oas/3.1/dialect/2024-11-10"}};

// OpenAPI 3.2 publishes its dialect at one dated URI with no undated alias
constexpr std::string_view OPENAPI_3_2_DIALECT{
    "https://spec.openapis.org/oas/3.2/dialect/2025-09-17"};

auto expect_known(const std::string_view kind, const std::string_view name,
                  const std::vector<std::string> &known) -> void {
  auto actual{sourcemeta::core::JSON::make_object()};
  actual.assign("kind", sourcemeta::core::JSON{kind});
  actual.assign("name", sourcemeta::core::JSON{name});
  actual.assign("known", sourcemeta::core::JSON{
                             std::ranges::find(known, name) != known.cend()});
  auto expected{actual};
  expected.assign("known", sourcemeta::core::JSON{true});
  EXPECT_EQ(actual, expected);
}

struct Target {
  std::string_view name;
  sourcemeta::blaze::ConvertTarget value;
  std::size_t position;
};

// Where a base dialect sits on the ladder, counting from one. Stated here
// rather than taken from the module, so that the suite says independently what
// it expects. Hyper variants sit alongside their plain counterparts, since a
// hyper-schema document is read as that rung, and the drafts below the ladder
// answer zero just as an unrecognised dialect does
auto ladder_position(const sourcemeta::core::SchemaBaseDialect base_dialect)
    -> std::size_t {
  using Base = sourcemeta::core::SchemaBaseDialect;
  switch (base_dialect) {
    case Base::JSON_SCHEMA_DRAFT_3:
    case Base::JSON_SCHEMA_DRAFT_3_HYPER:
      return 1;
    case Base::JSON_SCHEMA_DRAFT_4:
    case Base::JSON_SCHEMA_DRAFT_4_HYPER:
      return 2;
    case Base::JSON_SCHEMA_DRAFT_6:
    case Base::JSON_SCHEMA_DRAFT_6_HYPER:
      return 3;
    case Base::JSON_SCHEMA_DRAFT_7:
    case Base::JSON_SCHEMA_DRAFT_7_HYPER:
      return 4;
    case Base::JSON_SCHEMA_2019_09:
    case Base::JSON_SCHEMA_2019_09_HYPER:
      return 5;
    case Base::JSON_SCHEMA_2020_12:
    case Base::JSON_SCHEMA_2020_12_HYPER:
      return 6;
    default:
      return 0;
  }
}

// Every target that conversion takes, as a fixture has to account for all of
// them rather than for the ones whoever wrote it happened to think of
constexpr std::array<Target, 7> TARGETS{
    {{.name = "draft4",
      .value = sourcemeta::blaze::ConvertTarget::Draft4,
      .position = 2},
     {.name = "draft6",
      .value = sourcemeta::blaze::ConvertTarget::Draft6,
      .position = 3},
     {.name = "draft7",
      .value = sourcemeta::blaze::ConvertTarget::Draft7,
      .position = 4},
     {.name = "2019-09",
      .value = sourcemeta::blaze::ConvertTarget::Draft201909,
      .position = 5},
     {.name = "2020-12",
      .value = sourcemeta::blaze::ConvertTarget::Draft202012,
      .position = 6},
     {.name = "openapi3.1",
      .value = sourcemeta::blaze::ConvertTarget::OpenAPI31,
      .position = 7},
     {.name = "openapi3.2",
      .value = sourcemeta::blaze::ConvertTarget::OpenAPI32,
      .position = 8}}};

// The same names again, as a fixture names its targets in text
// NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
const std::vector<std::string> TARGET_NAMES{
    "draft4",  "draft6",     "draft7",    "2019-09",
    "2020-12", "openapi3.1", "openapi3.2"};

// A document on any spelling of the OpenAPI dialect sits on the last rung. The
// empty fragment does not change which dialect a URI names
auto names_openapi_3_1_dialect(const std::string_view dialect) -> bool {
  const auto candidate{
      dialect.ends_with('#') ? dialect.substr(0, dialect.size() - 1) : dialect};
  return std::ranges::find(OPENAPI_3_1_DIALECTS, candidate) !=
         OPENAPI_3_1_DIALECTS.cend();
}

// Conversion decides where a keyword goes as much as whether it is there at
// all, so the order of the result is part of what a fixture blesses. Both
// sides carry the target they came from, as a fixture accounts for seven of
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

  return inputs;
}

auto convert_schema(const sourcemeta::core::JSON &schema,
                    const sourcemeta::core::SchemaResolver &resolver,
                    const Inputs &inputs, const Target &target)
    -> sourcemeta::core::JSON {
  auto document{schema};
  sourcemeta::blaze::convert(document, sourcemeta::core::schema_walker,
                             resolver, target.value, inputs.default_dialect,
                             inputs.default_id);
  return document;
}

// Every key a fixture declares has to be one the runner reads, and every
// target has to be accounted for exactly once, either as a result or as an
// error
auto check_shape(const sourcemeta::core::JSON &test) -> void {
  for (const auto &entry : test.as_object()) {
    expect_known("fixture key", entry.first, KNOWN_KEYS);
  }

  EXPECT_TRUE(test.defines("schema"));

  // A boolean schema cannot carry both kinds of instance, so it belongs in
  // a hand-written test rather than here
  EXPECT_TRUE(test.at("schema").is_object());

  // A document either converts or is refused, and what makes it
  // unconvertible does not depend on which target was asked for. So one of
  // these two keys accounts for every target and the other is not there at
  // all: an empty one left behind reads as a claim about nothing, and both
  // together describe two different documents
  auto carried{sourcemeta::core::JSON::make_object()};
  carried.assign("result", sourcemeta::core::JSON{test.defines("result")});
  carried.assign("errors", sourcemeta::core::JSON{test.defines("errors")});
  auto wanted_carried{sourcemeta::core::JSON::make_object()};
  wanted_carried.assign("result",
                        sourcemeta::core::JSON{!test.defines("errors")});
  wanted_carried.assign("errors",
                        sourcemeta::core::JSON{!test.defines("result")});
  EXPECT_EQ(carried, wanted_carried);

  // A refused document never comes out, so there is nothing for an instance
  // to be checked against and the keys are left off along with it
  const auto converts{test.defines("result")};
  auto instanced{sourcemeta::core::JSON::make_object()};
  instanced.assign("examples",
                   sourcemeta::core::JSON{test.defines("examples")});
  instanced.assign("counterExamples",
                   sourcemeta::core::JSON{test.defines("counterExamples")});
  auto wanted_instanced{sourcemeta::core::JSON::make_object()};
  wanted_instanced.assign("examples", sourcemeta::core::JSON{converts});
  wanted_instanced.assign("counterExamples", sourcemeta::core::JSON{converts});
  EXPECT_EQ(instanced, wanted_instanced);

  if (converts) {
    EXPECT_TRUE(test.at("examples").is_array());
    EXPECT_TRUE(test.at("counterExamples").is_array());
  }

  const auto *registry{test.try_at("resolver")};
  if (registry != nullptr) {
    EXPECT_TRUE(registry->is_object());
  }

  for (const auto &name : {"defaultDialect", "defaultId"}) {
    const auto *value{test.try_at(sourcemeta::core::JSON::String{name})};
    if (value != nullptr) {
      EXPECT_TRUE(value->is_string());
    }
  }

  const auto &results{converts ? test.at("result") : NO_RESULTS};
  EXPECT_TRUE(results.is_object());
  EXPECT_FALSE(converts && results.empty());
  for (const auto &entry : results.as_object()) {
    expect_known("result target", entry.first, TARGET_NAMES);
    EXPECT_TRUE(entry.second.is_object() || entry.second.is_null());
  }

  if (test.defines("errors")) {
    EXPECT_TRUE(test.at("errors").is_object());
    for (const auto &entry : test.at("errors").as_object()) {
      expect_known("error target", entry.first, TARGET_NAMES);
      EXPECT_FALSE(results.defines(entry.first));
      EXPECT_TRUE(entry.second.is_object());
      for (const auto &detail : entry.second.as_object()) {
        expect_known("error key", detail.first, KNOWN_ERROR_KEYS);
      }

      // `check_error` reads both of these unconditionally
      for (const auto &detail : {"identifier", "location"}) {
        const sourcemeta::core::JSON::String name{detail};
        EXPECT_TRUE(entry.second.defines(name));
        EXPECT_TRUE(entry.second.at(name).is_string());
      }

      EXPECT_TRUE(entry.second.defines("type"));
      EXPECT_TRUE(entry.second.at("type").is_string());
      expect_known("error type", entry.second.at("type").to_string(),
                   KNOWN_ERROR_TYPES);
    }
  }

  for (const auto &target : TARGETS) {
    const sourcemeta::core::JSON::String name{target.name};
    EXPECT_TRUE(results.defines(name) ||
                (test.defines("errors") && test.at("errors").defines(name)));
  }

  if (converts) {
    EXPECT_FALSE(test.at("examples").empty() &&
                 test.at("counterExamples").empty());
  }

  if (test.defines("errors")) {
    EXPECT_FALSE(test.at("errors").empty());
  }
}

// Every error type carries the same three things, and naming all of them in one
// comparison is what lets a report say which target went wrong and how, rather
// than only that some expectation failed
template <typename ErrorType>
auto describe_error(const std::string_view target, const std::string_view type,
                    const ErrorType &error) -> sourcemeta::core::JSON {
  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign("target", sourcemeta::core::JSON{target});
  entry.assign("type", sourcemeta::core::JSON{type});
  entry.assign("identifier", sourcemeta::core::JSON{error.identifier()});
  entry.assign("location", sourcemeta::core::JSON{
                               sourcemeta::core::to_string(error.location())});
  return entry;
}

auto check_error(const sourcemeta::core::JSON &test,
                 const sourcemeta::core::SchemaResolver &resolver,
                 const Inputs &inputs, const Target &target,
                 const sourcemeta::core::JSON &expected) -> void {
  auto actual{sourcemeta::core::JSON::make_object()};
  actual.assign("target", sourcemeta::core::JSON{target.name});
  actual.assign("type", sourcemeta::core::JSON{"none"});

  try {
    [[maybe_unused]] const auto document{
        convert_schema(test.at("schema"), resolver, inputs, target)};
  } catch (const sourcemeta::blaze::ConvertUnsupportedMetaschemaError &error) {
    EXPECT_STREQ(error.what(), "The conversion does not support meta-schemas");
    actual = describe_error(target.name, "unsupported-metaschema", error);
  } catch (const sourcemeta::blaze::ConvertUnsupportedDialectError &error) {
    EXPECT_STREQ(error.what(), "The conversion does not support this dialect");
    actual = describe_error(target.name, "unsupported-dialect", error);
  } catch (const sourcemeta::blaze::ConvertInvalidReferenceError &error) {
    EXPECT_STREQ(error.what(), "The reference does not point to a schema");
    actual = describe_error(target.name, "invalid-reference", error);
  }

  // A reference left dangling by a transform is deliberately not caught here.
  // No fixture may expect one, so there is nothing to compare it against, and
  // letting it escape names it in the report instead of dressing it up as an
  // outcome the suite accepts

  auto wanted{sourcemeta::core::JSON::make_object()};
  wanted.assign("target", sourcemeta::core::JSON{target.name});
  wanted.assign("type", expected.at("type"));
  wanted.assign("identifier", expected.at("identifier"));
  wanted.assign("location", expected.at("location"));

  EXPECT_EQ(actual, wanted);
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
// Whether one meta-schema can judge the whole document. Only a `$schema` at a
// schema position declares a dialect, so framing is what decides where to
// look: the same string sitting in `default`, `enum` or `examples` is instance
// data and says nothing about what dialect the document is written in. Reading
// every node alike would let an author's data switch this answer, and with it
// switch off the check that follows
auto names_one_dialect(const sourcemeta::core::JSON &document,
                       const sourcemeta::core::SchemaResolver &resolver,
                       const Inputs &inputs) -> bool {
  if (!document.is_object()) {
    return true;
  }

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      document,
      sourcemeta::core::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      sourcemeta::core::SchemaFrame::IdentifierMode::Fallback};

  std::vector<sourcemeta::core::JSON::String> dialects;
  frame.for_each_subschema(
      [&document, &dialects](
          const sourcemeta::core::SchemaFrame::Location &location) -> void {
        const auto &subschema{sourcemeta::core::get(
            document, sourcemeta::core::to_pointer(location.pointer))};
        if (!subschema.is_object()) {
          return;
        }

        const auto *dialect{subschema.try_at("$schema")};
        if (dialect != nullptr && dialect->is_string() &&
            std::ranges::find(dialects, dialect->to_string()) ==
                dialects.cend()) {
          dialects.push_back(dialect->to_string());
        }
      });

  return dialects.size() <= 1;
}

// Whether a document is a schema of the dialect it claims to be
auto meets_metaschema(const sourcemeta::core::JSON &document,
                      const sourcemeta::core::SchemaResolver &resolver,
                      const sourcemeta::core::JSON &registry,
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
  // What the meta-schema compiles to depends on the registry that resolves
  // whatever it points at, so both belong in the key
  static std::vector<
      std::pair<std::pair<sourcemeta::core::JSON, sourcemeta::core::JSON>,
                sourcemeta::blaze::Template>>
      compiled_metaschemas;

  const auto &metaschema{frame.metaschema(resolver)};
  std::size_t index{0};
  while (index < compiled_metaschemas.size() &&
         (compiled_metaschemas.at(index).first.first != metaschema ||
          compiled_metaschemas.at(index).first.second != registry)) {
    index += 1;
  }

  if (index == compiled_metaschemas.size()) {
    compiled_metaschemas.emplace_back(
        std::make_pair(metaschema, registry),
        sourcemeta::blaze::compile(metaschema, sourcemeta::core::schema_walker,
                                   resolver,
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
// does not answer for what it was handed.
//
// What is judged is the document that came out, and it is left out when it
// names more than one dialect, because meta-schema validation is not defined
// across dialects. A meta-schema describes one dialect, so no single document
// can judge a root on one dialect together with a resource on another, and
// holding the whole document to the root's meta-schema would judge that
// resource by keywords it never claimed.
//
// That is asked of the output alone. An upgrade leaves one dialect behind, so
// the output usually names one even where the input named several, and the
// input's count says nothing about whether the output can be judged. Asking it
// of the input as well is what kept this check off for every mixed-dialect
// fixture in the suite, which is exactly where mis-upgrading an embedded
// resource is the risk
auto check_metaschema(const std::string_view target,
                      const sourcemeta::core::JSON &document,
                      const sourcemeta::core::JSON &input,
                      const sourcemeta::core::SchemaResolver &resolver,
                      const sourcemeta::core::JSON &registry,
                      const Inputs &inputs) -> void {
  if (!names_one_dialect(document, resolver, inputs) ||
      !meets_metaschema(input, resolver, registry, inputs)) {
    return;
  }

  auto entry{sourcemeta::core::JSON::make_object()};
  entry.assign("target", sourcemeta::core::JSON{target});
  entry.assign("meetsMetaschema", sourcemeta::core::JSON{meets_metaschema(
                                      document, resolver, registry, inputs)});
  auto expected{sourcemeta::core::JSON::make_object()};
  expected.assign("target", sourcemeta::core::JSON{target});
  expected.assign("meetsMetaschema", sourcemeta::core::JSON{true});
  EXPECT_EQ(entry, expected);
}

// Conversion reaches a dialect by walking the ladder, so going to an older
// target first and then on to a newer one has to land exactly where going
// straight to the newer one does. Anything else means a step depends on state
// that one of the two routes threw away
auto check_transitivity(
    const std::vector<std::optional<sourcemeta::core::JSON>> &converted,
    const sourcemeta::core::SchemaResolver &resolver, const Inputs &inputs)
    -> void {
  for (std::size_t earlier = 0; earlier < TARGETS.size(); earlier += 1) {
    if (!converted.at(earlier).has_value()) {
      continue;
    }

    for (std::size_t later = earlier + 1; later < TARGETS.size(); later += 1) {
      if (!converted.at(later).has_value()) {
        continue;
      }

      std::ostringstream label;
      label << TARGETS.at(earlier).name << " then " << TARGETS.at(later).name;
      expect_equal_with_ordering(label.str(),
                                 convert_schema(converted.at(earlier).value(),
                                                resolver, inputs,
                                                TARGETS.at(later)),
                                 converted.at(later).value());
    }
  }
}

// Conversion moves a document to the dialect it was asked for. A target at or
// above the rung the document starts on must therefore leave it reading as
// that target, and a result still reading as the old dialect is a conversion
// that silently did not happen. A target below that rung must leave it reading
// as the dialect it already had, since conversion only ever upgrades.
//
// Only the rung is asserted here. A lower target may still rewrite the
// document, because the rules that normalise a spelling or canonicalise a
// keyword are registered for every target and do not move the dialect
auto dialect_rung(const sourcemeta::core::JSON &document,
                  const sourcemeta::core::SchemaResolver &resolver,
                  const Inputs &inputs) -> std::size_t {
  if (!document.is_object()) {
    return 0;
  }

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      document,
      sourcemeta::core::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      sourcemeta::core::SchemaFrame::IdentifierMode::Fallback};

  const auto location{frame.traverse(sourcemeta::core::EMPTY_WEAK_POINTER)};
  if (!location.has_value()) {
    return 0;
  }

  // The OpenAPI dialect declares 2020-12 as its own `$schema`, so core frames a
  // document on it with a 2020-12 base dialect and the base dialect cannot say
  // which of the two rungs the document sits on. A dated spelling answers the
  // same rung, as the conversion settles one onto the undated spelling rather
  // than treating it as a dialect of its own
  if (names_openapi_3_1_dialect(location.value().get().dialect)) {
    return 7;
  }

  if (location.value().get().dialect == OPENAPI_3_2_DIALECT) {
    return 8;
  }

  return ladder_position(location.value().get().base_dialect);
}

auto check_dialects(
    const sourcemeta::core::JSON &input,
    const std::vector<std::optional<sourcemeta::core::JSON>> &converted,
    const sourcemeta::core::SchemaResolver &resolver, const Inputs &inputs)
    -> void {
  const auto before{dialect_rung(input, resolver, inputs)};
  if (before == 0) {
    return;
  }

  auto actual{sourcemeta::core::JSON::make_array()};
  auto expected{sourcemeta::core::JSON::make_array()};
  for (std::size_t index = 0; index < TARGETS.size(); index += 1) {
    const auto &target{TARGETS.at(index)};
    if (!converted.at(index).has_value()) {
      continue;
    }

    // A target at or above where the document starts has to leave it reading
    // as that target, and one below has to leave it reading as the dialect it
    // already had. Both are the same statement about the rung the document
    // comes back on, which is the only thing this compares
    const auto wanted_rung{std::max(before, target.position)};

    auto entry{sourcemeta::core::JSON::make_object()};
    entry.assign("target", sourcemeta::core::JSON{target.name});
    entry.assign(
        "rung",
        sourcemeta::core::JSON{static_cast<sourcemeta::core::JSON::Integer>(
            dialect_rung(converted.at(index).value(), resolver, inputs))});
    actual.push_back(std::move(entry));

    auto wanted{sourcemeta::core::JSON::make_object()};
    wanted.assign("target", sourcemeta::core::JSON{target.name});
    wanted.assign(
        "rung", sourcemeta::core::JSON{
                    static_cast<sourcemeta::core::JSON::Integer>(wanted_rung)});
    expected.push_back(std::move(wanted));
  }

  EXPECT_EQ(actual, expected);
}

// Which schema resources a document declares is part of what it means, and
// conversion is not supposed to invent one or lose one. Where each resource
// lives may move, so only the set of URIs is compared, not the pointers they
// sit at
auto resource_uris(const sourcemeta::core::JSON &document,
                   const sourcemeta::core::SchemaResolver &resolver,
                   const Inputs &inputs) -> std::set<std::string> {
  std::set<std::string> uris;
  if (!document.is_object()) {
    return uris;
  }

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References,
      document,
      sourcemeta::core::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      sourcemeta::core::SchemaFrame::IdentifierMode::Fallback};

  frame.for_each_location(
      [&uris](const sourcemeta::core::SchemaReferenceType,
              const std::string_view uri,
              const sourcemeta::core::SchemaFrame::Location &location) -> void {
        if (location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Resource) {
          uris.emplace(uri);
        }
      });

  return uris;
}

auto check_resources(
    const sourcemeta::core::JSON &input,
    const std::vector<std::optional<sourcemeta::core::JSON>> &converted,
    const sourcemeta::core::SchemaResolver &resolver, const Inputs &inputs)
    -> void {
  const auto before{resource_uris(input, resolver, inputs)};
  for (std::size_t index = 0; index < TARGETS.size(); index += 1) {
    if (!converted.at(index).has_value()) {
      continue;
    }

    auto actual{sourcemeta::core::JSON::make_object()};
    actual.assign("target", sourcemeta::core::JSON{TARGETS.at(index).name});
    auto listing{sourcemeta::core::JSON::make_array()};
    for (const auto &uri :
         resource_uris(converted.at(index).value(), resolver, inputs)) {
      listing.push_back(sourcemeta::core::JSON{uri});
    }
    actual.assign("resources", std::move(listing));

    auto expected{sourcemeta::core::JSON::make_object()};
    expected.assign("target", sourcemeta::core::JSON{TARGETS.at(index).name});
    auto baseline{sourcemeta::core::JSON::make_array()};
    for (const auto &uri : before) {
      baseline.push_back(sourcemeta::core::JSON{uri});
    }
    expected.assign("resources", std::move(baseline));

    EXPECT_EQ(actual, expected);
  }
}

auto run_convert_test(const sourcemeta::core::JSON &test) -> void {
  check_shape(test);

  const auto resolver{make_resolver(test)};
  const auto inputs{make_inputs(test)};
  const auto &results{test.defines("result") ? test.at("result") : NO_RESULTS};

  // Every target is converted up front, and the instances have their say before
  // any expectation about the shape of the output. A `result` that turns out
  // wrong would otherwise abort the test first and hide whether the conversion
  // still means what it did, which is the one thing worth knowing
  std::vector<std::optional<sourcemeta::core::JSON>> converted;
  converted.reserve(TARGETS.size());
  for (const auto &target : TARGETS) {
    const sourcemeta::core::JSON::String name{target.name};
    if (test.defines("errors") && test.at("errors").defines(name)) {
      check_error(test, resolver, inputs, target, test.at("errors").at(name));
      converted.emplace_back(std::nullopt);
      continue;
    }

    try {
      converted.emplace_back(
          convert_schema(test.at("schema"), resolver, inputs, target));
    } catch (const std::exception &error) {
      auto actual{sourcemeta::core::JSON::make_object()};
      actual.assign("target", sourcemeta::core::JSON{target.name});
      actual.assign("threw", sourcemeta::core::JSON{error.what()});
      auto expected{sourcemeta::core::JSON::make_object()};
      expected.assign("target", sourcemeta::core::JSON{target.name});
      expected.assign("threw", sourcemeta::core::JSON{"nothing"});

      // No document came out for this target, and the entry keeps the vector
      // in step with the targets whether or not the expectation above stops
      // the test
      converted.emplace_back(std::nullopt);
      EXPECT_EQ(actual, expected);
    }
  }

  // Which resources a document declares is the most basic thing conversion must
  // preserve, so it is asked first: a wrong `result` or a changed instance
  // verdict would otherwise abort the test before this had its say
  check_resources(test.at("schema"), converted, resolver, inputs);

  auto disagreements{sourcemeta::core::JSON::make_array()};
  // A refused fixture carries no instances at all, so there is nothing here to
  // put to either side of the conversion
  if (test.defines("examples") &&
      (!test.at("examples").empty() || !test.at("counterExamples").empty())) {
    check_instances(test.at("schema"), "input", test, resolver, inputs,
                    disagreements);

    std::vector<sourcemeta::core::JSON> evaluated;
    for (std::size_t index = 0; index < TARGETS.size(); index += 1) {
      if (!converted.at(index).has_value()) {
        continue;
      }

      const auto &document{converted.at(index).value()};
      if (std::ranges::find(evaluated, document) != evaluated.cend()) {
        continue;
      }

      check_instances(document, TARGETS.at(index).name, test, resolver, inputs,
                      disagreements);
      evaluated.push_back(document);
    }
  }

  EXPECT_EQ(disagreements, sourcemeta::core::JSON::make_array());

  // After the instances, because a dialect that did not move is coarser news
  // than a changed verdict and must not hide one
  check_dialects(test.at("schema"), converted, resolver, inputs);

  for (std::size_t index = 0; index < TARGETS.size(); index += 1) {
    if (!converted.at(index).has_value()) {
      continue;
    }

    const auto &target{TARGETS.at(index)};
    const auto &document{converted.at(index).value()};
    const auto &expected{
        results.at(sourcemeta::core::JSON::String{target.name})};
    if (expected.is_null()) {
      expect_equal_with_ordering(target.name, document, test.at("schema"));
      continue;
    }

    expect_equal_with_ordering(target.name, document, expected);
    const auto *registry{test.try_at("resolver")};
    check_metaschema(target.name, document, test.at("schema"), resolver,
                     registry == nullptr ? sourcemeta::core::JSON{nullptr}
                                         : *registry,
                     inputs);

    // A target that leaves the schema alone has to say so with `null`, rather
    // than with a copy that silently stops matching the input it came from
    EXPECT_NE(document, test.at("schema"));

    // Conversion that keeps finding work to do on its own output never
    // reaches the dialect it claims to have reached
    expect_equal_with_ordering(
        target.name, convert_schema(document, resolver, inputs, target),
        document);
  }

  check_transitivity(converted, resolver, inputs);
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
