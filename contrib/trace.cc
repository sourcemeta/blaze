#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include "tweaks.h"

#include <algorithm>   // std::sort, std::max
#include <cstdlib>     // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // std::filesystem::path
#include <iostream>    // std::cerr, std::cout
#include <map>         // std::map
#include <string>      // std::string
#include <string_view> // std::string_view
#include <tuple>       // std::tuple, std::get
#include <type_traits> // std::underlying_type_t
#include <utility>     // std::pair
#include <vector>      // std::vector

// The name a fixture gives an instruction, where every annotation instruction
// answers to the same one
auto fixture_instruction_name(const sourcemeta::blaze::Instruction &step)
    -> std::string {
  if (sourcemeta::blaze::is_annotation(step.type)) {
    return "Annotation";
  }

  return std::string{sourcemeta::blaze::INSTRUCTION_NAMES[static_cast<
      std::underlying_type_t<sourcemeta::blaze::InstructionIndex>>(step.type)]};
}

// The part of a trace fixture that one mode decides, exactly as the evaluator
// callback reports it, so that a fixture covering a mode the tests never
// exercised does not need its expectations written out by hand. What comes out
// is shaped like the fixture itself: the verdict where a fixture keeps it, and
// the trace under the name of the mode that produced it
auto emit_fixture_section(const sourcemeta::blaze::Template &schema_template,
                          const sourcemeta::core::JSON &instance,
                          const std::string_view mode) -> void {
  using Entry =
      std::tuple<bool, sourcemeta::core::WeakPointer,
                 sourcemeta::core::WeakPointer, sourcemeta::blaze::Instruction,
                 sourcemeta::core::JSON, sourcemeta::blaze::InstructionExtra>;
  std::vector<Entry> pre;
  std::vector<Entry> post;

  sourcemeta::blaze::Evaluator evaluator;
  const auto result{evaluator.validate(
      schema_template, instance,
      [&pre, &post](const sourcemeta::blaze::EvaluationType type,
                    const bool valid,
                    const sourcemeta::blaze::Instruction &step,
                    const sourcemeta::blaze::InstructionExtra &step_metadata,
                    const sourcemeta::core::WeakPointer &evaluate_path,
                    const sourcemeta::core::WeakPointer &instance_location,
                    const sourcemeta::core::JSON &annotation) {
        if (type == sourcemeta::blaze::EvaluationType::Pre) {
          pre.emplace_back(valid, evaluate_path, instance_location, step,
                           annotation, step_metadata);
        } else if (type == sourcemeta::blaze::EvaluationType::Post) {
          post.emplace_back(valid, evaluate_path, instance_location, step,
                            annotation, step_metadata);
        }
      })};

  auto pre_entries{sourcemeta::core::JSON::make_array()};
  for (const auto &entry : pre) {
    auto row{sourcemeta::core::JSON::make_array()};
    row.push_back(
        sourcemeta::core::JSON{fixture_instruction_name(std::get<3>(entry))});
    row.push_back(sourcemeta::core::JSON{
        sourcemeta::core::to_string(std::get<1>(entry))});
    row.push_back(sourcemeta::core::JSON{
        std::string{std::get<5>(entry).keyword_location}});
    row.push_back(sourcemeta::core::JSON{
        sourcemeta::core::to_string(std::get<2>(entry))});
    pre_entries.push_back(std::move(row));
  }

  auto post_entries{sourcemeta::core::JSON::make_array()};
  auto descriptions{sourcemeta::core::JSON::make_array()};
  for (const auto &entry : post) {
    auto row{sourcemeta::core::JSON::make_array()};
    row.push_back(sourcemeta::core::JSON{std::get<0>(entry)});
    row.push_back(
        sourcemeta::core::JSON{fixture_instruction_name(std::get<3>(entry))});
    row.push_back(sourcemeta::core::JSON{
        sourcemeta::core::to_string(std::get<1>(entry))});
    row.push_back(sourcemeta::core::JSON{
        std::string{std::get<5>(entry).keyword_location}});
    row.push_back(sourcemeta::core::JSON{
        sourcemeta::core::to_string(std::get<2>(entry))});

    // An annotation also reports the value it emitted
    if (sourcemeta::blaze::is_annotation(std::get<3>(entry).type)) {
      row.push_back(std::get<4>(entry));
    }

    post_entries.push_back(std::move(row));
    descriptions.push_back(sourcemeta::core::JSON{sourcemeta::blaze::describe(
        schema_template, std::get<0>(entry), std::get<3>(entry),
        std::get<1>(entry), std::get<2>(entry), instance, std::get<4>(entry))});
  }

  auto section{sourcemeta::core::JSON::make_object()};
  section.assign("pre", std::move(pre_entries));
  section.assign("post", std::move(post_entries));
  section.assign("descriptions", std::move(descriptions));

  auto fixture{sourcemeta::core::JSON::make_object()};
  fixture.assign("valid", sourcemeta::core::JSON{result});
  fixture.assign(sourcemeta::core::JSON::String{mode}, std::move(section));

  sourcemeta::core::prettify(fixture, std::cout);
  std::cout << "\n";
}

auto print_map(const std::map<std::string_view, std::size_t> &input) -> void {
  std::vector<std::pair<std::string_view, std::size_t>> list{input.cbegin(),
                                                             input.cend()};
  std::sort(list.begin(), list.end(), [](const auto &left, const auto &right) {
    return left.second > right.second;
  });

  std::size_t max_key_width{0};
  for (const auto &[key, value] : list) {
    max_key_width = std::max(max_key_width, key.size());
  }

  for (const auto &[key, value] : list) {
    std::cout << std::setw(static_cast<int>(max_key_width)) << key << " : "
              << value << '\n';
  }
}

static std::map<std::string_view, std::size_t> global_keywords_count;
static std::map<std::string_view, std::size_t> global_steps_count;

auto main(int argc, char **argv) noexcept -> int {
  sourcemeta::core::Options options;
  options.flag("fast", {"f"});
  options.option("dialect", {"d"});
  options.option("entrypoint", {"e"});
  options.option("resolve-map", {});
  register_tweak_options(options);
  options.flag("fixture", {});

  try {
    options.parse(argc, argv);
  } catch (const sourcemeta::core::OptionsError &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  const auto &positional{options.positional()};
  if (positional.size() < 2) {
    std::cerr << "Usage: " << argv[0]
              << " [--fast] [--dialect <uri>] [--resolve-map <file>]..."
                 " [--entrypoint <uri-or-pointer>] [--format-assertion]"
                 " [--annotations <keyword>]... [--no-annotations]"
                 " [--fixture] <schema.json> <instance.json>\n";
    return EXIT_FAILURE;
  }

  const auto mode{options.contains("fast")
                      ? sourcemeta::blaze::Mode::FastValidation
                      : sourcemeta::blaze::Mode::Exhaustive};

  const std::string_view default_dialect{options.contains("dialect") &&
                                                 !options.at("dialect").empty()
                                             ? options.at("dialect").front()
                                             : ""};

  const std::string_view entrypoint{options.contains("entrypoint") &&
                                            !options.at("entrypoint").empty()
                                        ? options.at("entrypoint").front()
                                        : ""};

  try {
    const auto schema{
        sourcemeta::core::read_json(std::filesystem::path{positional.at(0)})};
    // Reaching the same instructions a fixture asks for means taking the
    // same knobs the suites can set
    const auto tweaks{tweaks_from_options(options, std::cerr)};

    // The schemas a file names, by the URI each answers to. A file that holds
    // anything but an object names nothing, and reading it as one would walk a
    // member that is not there
    auto schemas{sourcemeta::core::JSON::make_object()};
    if (options.contains("resolve-map")) {
      for (const auto &path : options.at("resolve-map")) {
        const auto document{
            sourcemeta::core::read_json(std::filesystem::path{path})};
        if (!document.is_object()) {
          std::cerr << "error: expected an object of URIs to schemas at: "
                    << path << "\n";
          return EXIT_FAILURE;
        }

        for (const auto &entry : document.as_object()) {
          schemas.assign(entry.first, entry.second);
        }
      }
    }

    const auto resolver{[&schemas](const std::string_view identifier)
                            -> sourcemeta::core::SchemaResolverResult {
      const auto *named{
          schemas.try_at(sourcemeta::core::JSON::StringView{identifier})};
      if (named != nullptr) {
        return *named;
      }

      return sourcemeta::core::schema_resolver(identifier);
    }};

    const auto schema_template{sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker, resolver,
        sourcemeta::blaze::default_schema_compiler, mode, default_dialect, "",
        entrypoint, tweaks)};
    const auto instance{
        sourcemeta::core::read_json(std::filesystem::path{positional.at(1)})};

    if (options.contains("fixture")) {
      emit_fixture_section(schema_template, instance,
                           mode == sourcemeta::blaze::Mode::FastValidation
                               ? "fast"
                               : "exhaustive");
      return EXIT_SUCCESS;
    }

    sourcemeta::blaze::TraceOutput output{
        schema_template,
        [](const sourcemeta::blaze::TraceOutput::Entry &entry) {
          switch (entry.type) {
            case sourcemeta::blaze::TraceOutput::EntryType::Push:
              std::cout << "-> (push) ";
              break;
            case sourcemeta::blaze::TraceOutput::EntryType::Pass:
              std::cout << "<- (pass) ";
              break;
            case sourcemeta::blaze::TraceOutput::EntryType::Fail:
              std::cout << "<- (fail) ";
              break;
            case sourcemeta::blaze::TraceOutput::EntryType::Annotation:
              std::cout << "<- (note) ";
              break;
          }

          std::cout << "\"";
          sourcemeta::core::stringify(entry.evaluate_path, std::cout);
          std::cout << "\" [";
          std::cout << entry.name;
          std::cout << "]\n";
          std::cout << "   at \"";
          sourcemeta::core::stringify(entry.instance_location, std::cout);
          std::cout << "\"\n";
          std::cout << "   of \"" << entry.keyword_location << "\"\n";

          if (entry.type == sourcemeta::blaze::TraceOutput::EntryType::Push) {
            global_steps_count[entry.name] += 1;
            if (!entry.evaluate_path.empty() &&
                entry.evaluate_path.back().is_property()) {
              const auto &keyword{entry.evaluate_path.back().to_property()};
              global_keywords_count[keyword] += 1;
            }
          }
        }};
    sourcemeta::blaze::Evaluator evaluator;
    const auto result{
        evaluator.validate(schema_template, instance, std::ref(output))};

    std::cout << "\n";
    std::cout << "==== KEYWORD STATS\n";
    print_map(global_keywords_count);
    std::cout << "\n";
    std::cout << "==== STEP STATS\n";
    print_map(global_steps_count);
    std::cout << "\n";

    if (!result) {
      std::cerr << "FAIL\n";
      return EXIT_FAILURE;
    }

    std::cerr << "PASS\n";
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
