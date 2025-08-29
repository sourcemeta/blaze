#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

#include <algorithm>  // std::sort, std::max
#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem::path
#include <iostream>   // std::cerr, std::cout
#include <map>        // std::map
#include <utility>    // std::pair
#include <vector>     // std::vector

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
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <schema.json> <instance.json>\n";
    return EXIT_FAILURE;
  }

  const auto schema{sourcemeta::core::read_json(argv[1])};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  const std::filesystem::path instance_path{argv[2]};
  const auto instance{sourcemeta::core::read_json(instance_path)};

  sourcemeta::blaze::TraceOutput output{
      sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver};
  sourcemeta::blaze::Evaluator evaluator;
  const auto result{
      evaluator.validate(schema_template, instance, std::ref(output))};

  for (const auto &entry : output) {
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
      default:
        assert(false);
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

    // Only count on one of the callback types, otherwise we end up
    // duplicating the summary information
    if (entry.type == sourcemeta::blaze::TraceOutput::EntryType::Push) {
      global_steps_count[entry.name] += 1;
      if (!entry.evaluate_path.empty()) {
        assert(entry.evaluate_path.back().is_property());
        const auto &keyword{entry.evaluate_path.back().to_property()};
        global_keywords_count[keyword] += 1;
      }
    }
  }

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
  return EXIT_SUCCESS;
}
