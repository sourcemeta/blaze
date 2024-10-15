#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

// See
// https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <optional> // std::optional, std::nullopt
#include <string>   // std::string
#include <vector>   // std::vector

// TODO: Gracefully handle JSON Toolkit C++ exceptions

class Wrapper {
public:
  auto compile(const std::string &schema_string) -> emscripten::val {
    const auto schema{sourcemeta::jsontoolkit::parse(schema_string)};
    this->schemas.emplace_back(sourcemeta::jsontoolkit::compile(
        schema, sourcemeta::jsontoolkit::default_schema_walker,
        sourcemeta::jsontoolkit::official_resolver,
        sourcemeta::jsontoolkit::default_schema_compiler,
        sourcemeta::jsontoolkit::SchemaCompilerMode::FastValidation));
    return emscripten::val(this->schemas.size() - 1);
  }

  auto compile_with_default_dialect(const std::string &schema_string,
                                    const std::string &default_dialect)
      -> emscripten::val {
    const auto schema{sourcemeta::jsontoolkit::parse(schema_string)};
    this->schemas.emplace_back(sourcemeta::jsontoolkit::compile(
        schema, sourcemeta::jsontoolkit::default_schema_walker,
        sourcemeta::jsontoolkit::official_resolver,
        sourcemeta::jsontoolkit::default_schema_compiler,
        sourcemeta::jsontoolkit::SchemaCompilerMode::FastValidation,
        default_dialect));
    return emscripten::val(this->schemas.size() - 1);
  }

  auto evaluate(const std::size_t schema, const std::string &instance_string)
      -> emscripten::val {
    assert(schema < this->schemas.size());
    assert(this->schemas[schema].has_value());
    const auto instance{sourcemeta::jsontoolkit::parse(instance_string)};
    this->context.prepare(instance);
    const auto result{sourcemeta::jsontoolkit::evaluate(
        this->schemas[schema].value(), context)};
    return emscripten::val(result);
  }

  auto remove(const std::size_t schema) -> void {
    assert(schema < this->schemas.size());
    if (schema == this->schemas.size() - 1) {
      this->schemas.pop_back();
    } else {
      this->schemas[schema] = std::nullopt;
    }
  }

private:
  sourcemeta::jsontoolkit::EvaluationContext context;
  std::vector<std::optional<sourcemeta::jsontoolkit::SchemaCompilerTemplate>>
      schemas;
};

EMSCRIPTEN_BINDINGS(jsontoolkit) {
  emscripten::class_<Wrapper>("Wrapper")
      .constructor<>()
      .function("compile", &Wrapper::compile)
      .function("compileWithDefaultDialect",
                &Wrapper::compile_with_default_dialect)
      .function("evaluate", &Wrapper::evaluate)
      .function("remove", &Wrapper::remove);
}
