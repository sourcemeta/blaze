#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace {

// Every key a fixture may declare. Anything else is a mistake that would
// otherwise go unnoticed, as the runner would simply not read it
const std::vector<std::string> KNOWN_KEYS{
    "schema", "resolver",       "defaultDialect", "defaultId",    "paths",
    "root",   "identifierMode", "pointers",       "reachability", "standalone"};

auto make_resolver(const sourcemeta::core::JSON &test)
    -> sourcemeta::blaze::SchemaResolver {
  if (!test.defines("resolver")) {
    return sourcemeta::blaze::schema_resolver;
  }

  const auto &registry{test.at("resolver")};
  return [registry](const std::string_view identifier)
             -> sourcemeta::blaze::SchemaResolverResult {
    const auto *match{
        registry.try_at(sourcemeta::core::JSON::String{identifier})};
    if (match != nullptr) {
      return *match;
    }

    return sourcemeta::blaze::schema_resolver(identifier);
  };
}

// A frame keeps views into the default dialect, the default identifier, and
// the paths it was given, so all three have to outlive it. The caller owns
// this, as anything built inside `analyse` would dangle on return and only
// misbehave later, when the frame is read back
struct Inputs {
  sourcemeta::core::JSON::String default_dialect;
  sourcemeta::core::JSON::String default_id;
  std::vector<sourcemeta::core::Pointer> paths;
};

auto make_inputs(const sourcemeta::core::JSON &test) -> Inputs {
  Inputs inputs;
  const auto *raw_dialect{test.try_at("defaultDialect")};
  if (raw_dialect != nullptr && !raw_dialect->is_null()) {
    inputs.default_dialect = raw_dialect->to_string();
  }

  const auto *raw_id{test.try_at("defaultId")};
  if (raw_id != nullptr && !raw_id->is_null()) {
    inputs.default_id = raw_id->to_string();
  }

  if (test.defines("paths")) {
    for (const auto &path : test.at("paths").as_array()) {
      inputs.paths.push_back(sourcemeta::core::to_pointer(path.to_string()));
    }
  }

  return inputs;
}

auto make_paths(const sourcemeta::core::JSON &test, const Inputs &inputs)
    -> sourcemeta::blaze::SchemaFrame::Paths {
  sourcemeta::blaze::SchemaFrame::Paths paths;
  if (test.defines("paths")) {
    for (const auto &path : inputs.paths) {
      paths.push_back(sourcemeta::core::to_weak_pointer(path));
    }
  } else {
    paths.push_back(sourcemeta::core::EMPTY_WEAK_POINTER);
  }

  return paths;
}

auto make_identifier_mode(const sourcemeta::core::JSON &test)
    -> sourcemeta::blaze::SchemaFrame::IdentifierMode {
  const auto *identifier_mode{test.try_at("identifierMode")};
  return (identifier_mode != nullptr &&
          identifier_mode->to_string() == "fallback")
             ? sourcemeta::blaze::SchemaFrame::IdentifierMode::Fallback
             : sourcemeta::blaze::SchemaFrame::IdentifierMode::Additional;
}

// Whether the target location can be evaluated when validation starts from the
// origin location
auto check_reachability(const sourcemeta::blaze::SchemaFrame &frame,
                        const sourcemeta::blaze::SchemaResolver &resolver,
                        const sourcemeta::core::JSON &check) -> void {
  const auto type{check.defines("type") &&
                          check.at("type").to_string() == "dynamic"
                      ? sourcemeta::blaze::SchemaReferenceType::Dynamic
                      : sourcemeta::blaze::SchemaReferenceType::Static};
  const auto target{frame.location(type, check.at("to").to_string())};
  EXPECT_TRUE(target.has_value());
  const auto origin{frame.traverse(check.at("from").to_string())};
  EXPECT_TRUE(origin.has_value());
  EXPECT_EQ(frame.is_reachable(origin.value().get(), target.value().get(),
                               sourcemeta::blaze::schema_walker, resolver),
            check.at("reachable").to_boolean());
}

// Every mode below sourcemeta::blaze::SchemaFrame::Mode::Pointers reports a
// pointer location only when a reference names it, so the expectations for
// those follow from the one fixture we store rather than from near-duplicates
// of it
auto drop_pointer_locations(
    sourcemeta::core::JSON &document,
    const std::set<sourcemeta::core::JSON::String> &keep) -> void {
  for (const auto &kind : {"static", "dynamic"}) {
    auto &group{document.at("locations").at(kind)};
    std::vector<sourcemeta::core::JSON::String> doomed;
    for (const auto &location : group.as_object()) {
      if (location.second.at("type").to_string() == "pointer" &&
          !keep.contains(location.first)) {
        doomed.push_back(location.first);
      }
    }

    for (const auto &uri : doomed) {
      group.erase(uri);
    }
  }
}

auto reference_destinations(const sourcemeta::core::JSON &document)
    -> std::set<sourcemeta::core::JSON::String> {
  std::set<sourcemeta::core::JSON::String> result;
  for (const auto &reference : document.at("references").as_array()) {
    result.insert(reference.at("destination").to_string());
  }

  return result;
}

auto run_frame_test(const sourcemeta::core::JSON &test) -> void {
  for (const auto &entry : test.as_object()) {
    EXPECT_TRUE(std::ranges::find(KNOWN_KEYS, entry.first) !=
                KNOWN_KEYS.cend());
  }

  EXPECT_TRUE(test.defines("schema"));
  EXPECT_TRUE(test.defines("root"));
  EXPECT_TRUE(test.defines("pointers"));
  EXPECT_TRUE(test.defines("standalone"));

  const auto resolver{make_resolver(test)};
  const auto inputs{make_inputs(test)};
  const auto paths{make_paths(test, inputs)};
  const auto identifier_mode{make_identifier_mode(test)};

  const sourcemeta::blaze::SchemaFrame root{
      sourcemeta::blaze::SchemaFrame::Mode::Root,
      test.at("schema"),
      sourcemeta::blaze::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      identifier_mode,
      paths};
  EXPECT_EQ(root.to_json(resolver), test.at("root"));

  const sourcemeta::blaze::SchemaFrame pointers{
      sourcemeta::blaze::SchemaFrame::Mode::Pointers,
      test.at("schema"),
      sourcemeta::blaze::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      identifier_mode,
      paths};
  EXPECT_EQ(pointers.to_json(resolver), test.at("pointers"));

  // References mode locates every schema, but of the remaining pointers only
  // the ones that a reference actually names
  auto expected_references{test.at("pointers")};
  expected_references.assign("mode", sourcemeta::core::JSON{"references"});
  drop_pointer_locations(expected_references,
                         reference_destinations(expected_references));
  const sourcemeta::blaze::SchemaFrame references{
      sourcemeta::blaze::SchemaFrame::Mode::References,
      test.at("schema"),
      sourcemeta::blaze::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      identifier_mode,
      paths};
  EXPECT_EQ(references.to_json(resolver), expected_references);

  EXPECT_EQ(references.standalone(), test.at("standalone").to_boolean());

  if (test.defines("reachability")) {
    for (const auto &check : test.at("reachability").as_array()) {
      check_reachability(references, resolver, check);
    }
  }

  // Locations mode resolves no reference at all, so it keeps no pointer that
  // only a reference would have justified either
  auto expected_locations{test.at("pointers")};
  expected_locations.assign("mode", sourcemeta::core::JSON{"locations"});
  expected_locations.assign("references", sourcemeta::core::JSON::make_array());
  drop_pointer_locations(expected_locations, {});
  for (const auto &kind : {"static", "dynamic"}) {
    auto &group{expected_locations.at("locations").at(kind)};
    std::vector<sourcemeta::core::JSON::String> uris;
    for (const auto &location : group.as_object()) {
      uris.push_back(location.first);
    }

    for (const auto &uri : uris) {
      group.at(uri).assign("hasReferencesTo", sourcemeta::core::JSON{false});
      group.at(uri).assign("hasReferencesThrough",
                           sourcemeta::core::JSON{false});
    }
  }
  const sourcemeta::blaze::SchemaFrame locations{
      sourcemeta::blaze::SchemaFrame::Mode::Locations,
      test.at("schema"),
      sourcemeta::blaze::schema_walker,
      resolver,
      inputs.default_dialect,
      inputs.default_id,
      identifier_mode,
      paths};
  EXPECT_EQ(locations.to_json(resolver), expected_locations);
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
    sourcemeta::core::test_register("FrameSuite_" + suite, name.str(), __FILE__,
                                    __LINE__,
                                    [test]() -> void { run_frame_test(test); });
    count += 1;
  }

  return count;
}

} // namespace

auto main(int argc, char **argv) -> int {
  const auto count{register_tests(std::filesystem::path{FRAME_SUITE_PATH})};
  // A fixture in the wrong place, or with the wrong extension, would otherwise
  // never run and nobody would notice
  if (count == 0) {
    std::cerr << "No frame fixtures found at " << FRAME_SUITE_PATH << "\n";
    return 1;
  }

  return sourcemeta::core::test_run(argc, argv);
}
