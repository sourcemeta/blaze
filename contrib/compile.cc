#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/core/json.h>

#include <chrono>   // std::chrono
#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream> // std::cerr

auto main(int argc, char **argv) noexcept -> int {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <fast|exhaustive> <schema.json>\n";
    return EXIT_FAILURE;
  }

  const std::string mode_string{argv[1]};
  auto mode{sourcemeta::blaze::Mode::FastValidation};
  if (mode_string == "fast") {
    std::cerr << "Choosing fast mode\n";
  } else if (mode_string == "exhaustive") {
    std::cerr << "Choosing exhaustive mode\n";
    mode = sourcemeta::blaze::Mode::Exhaustive;
  } else {
    std::cerr << "Invalid mode: " << mode_string << "\n";
    return EXIT_FAILURE;
  }

  const auto schema{sourcemeta::core::read_json(argv[2])};
  std::cerr << "Compiling schema: " << argv[2] << "\n";
  const auto compile_start{std::chrono::high_resolution_clock::now()};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler, mode)};
  const auto compile_end{std::chrono::high_resolution_clock::now()};
  const auto compile_duration{
      std::chrono::duration_cast<std::chrono::milliseconds>(compile_end -
                                                            compile_start)};
  std::cerr << "Took: " << compile_duration.count() << "ms\n";
  std::cerr << "Number of generated instructions: "
            << schema_template.targets[0].size() << "\n";

  sourcemeta::core::prettify(sourcemeta::blaze::to_json(schema_template),
                             std::cout);
  std::cout << "\n";

  return EXIT_SUCCESS;
}
