#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <algorithm>  // std::sort, std::max
#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem::path
#include <iostream>   // std::cerr, std::cout
#include <map>        // std::map
#include <memory>     // std::free
#include <string>     // std::string, std::to_string
#include <utility>    // std::pair
#include <variant>    // std::visit
#include <vector>     // std::vector

#include <cxxabi.h> // abi::__cxa_demangle

static auto step_name(const sourcemeta::blaze::Template::value_type &step)
    -> std::string {
  return std::visit(
      [](const auto &value) {
#ifdef __GNUG__
        int status;
        std::string name{typeid(value).name()};
        char *demangled =
            abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
        if (demangled) {
          name = demangled;
          std::free(demangled);
        }

        return name;
#else
        return std::string{typeid(value).name()};
#endif
      },
      step);
}

auto print_map(const std::map<std::string, std::size_t> &input) -> void {
  std::vector<std::pair<std::string, std::size_t>> list{input.cbegin(),
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

static std::map<std::string, std::size_t> global_keywords_count;
static std::map<std::string, std::size_t> global_steps_count;

static auto
callback(const sourcemeta::blaze::EvaluationType type, const bool result,
         const sourcemeta::blaze::Template::value_type &step,
         const sourcemeta::jsontoolkit::WeakPointer &evaluate_path,
         const sourcemeta::jsontoolkit::WeakPointer &instance_location,
         const sourcemeta::jsontoolkit::JSON &) -> void {
  if (type == sourcemeta::blaze::EvaluationType::Pre) {
    std::cout << "-> (push) ";
  } else {
    std::cout << "<- ";
    if (result) {
      std::cout << "(pass) ";
    } else {
      std::cout << "(fail) ";
    }
  }

  const std::string step_prefix{"sourcemeta::blaze::"};
  const auto full_step_name{step_name(step)};
  const auto short_step_name{full_step_name.starts_with(step_prefix)
                                 ? full_step_name.substr(step_prefix.size())
                                 : full_step_name};

  // Only count on one of the callback types, otherwise we end up
  // duplicating the summary information
  if (type == sourcemeta::blaze::EvaluationType::Pre) {
    global_steps_count[short_step_name] += 1;
    if (!evaluate_path.empty()) {
      assert(evaluate_path.back().is_property());
      const auto &keyword{evaluate_path.back().to_property()};
      global_keywords_count[keyword] += 1;
    }
  }

  std::cout << "\"";
  sourcemeta::jsontoolkit::stringify(evaluate_path, std::cout);
  std::cout << "\" [";
  std::cout << short_step_name;
  std::cout << "]\n";
  std::cout << "   at \"";
  sourcemeta::jsontoolkit::stringify(instance_location, std::cout);
  std::cout << "\"\n";
}

auto main(int argc, char **argv) noexcept -> int {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <schema.json> <instance.json>\n";
    return EXIT_FAILURE;
  }

  const auto schema{sourcemeta::jsontoolkit::from_file(argv[1])};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  const std::filesystem::path instance_path{argv[2]};
  const auto instance{sourcemeta::jsontoolkit::from_file(instance_path)};
  const auto result{
      sourcemeta::blaze::evaluate(schema_template, instance, callback)};

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
