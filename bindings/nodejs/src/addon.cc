#include "blaze_json.h"
#include "blaze_schema.h"

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <cassert>   // assert
#include <cstddef>   // std::size_t
#include <optional>  // std::optional
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace sourcemeta::blaze::nodejs {

static thread_local sourcemeta::blaze::Evaluator evaluator;

static auto parse(napi_env environment, napi_callback_info info) -> napi_value {
  std::size_t argc = 2;
  napi_value args[2];
  [[maybe_unused]] napi_status status =
      napi_get_cb_info(environment, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(environment, nullptr,
                          "parse() requires at least 1 argument");
    return nullptr;
  }

  napi_valuetype arg_type;
  status = napi_typeof(environment, args[0], &arg_type);
  assert(status == napi_ok);

  if (arg_type != napi_string) {
    napi_throw_type_error(environment, nullptr,
                          "parse() argument must be a string");
    return nullptr;
  }

  std::size_t length;
  status =
      napi_get_value_string_utf8(environment, args[0], nullptr, 0, &length);
  assert(status == napi_ok);

  std::string input(length, '\0');
  status = napi_get_value_string_utf8(environment, args[0], input.data(),
                                      length + 1, &length);
  assert(status == napi_ok);

  try {
    auto json = sourcemeta::core::parse_json(input);
    return JSONWrapper::create(environment, std::move(json));
  } catch (const sourcemeta::core::JSONParseError &error) {
    std::ostringstream message;
    message << "JSON parse error at line " << error.line() << ", column "
            << error.column() << ": " << error.what();
    napi_throw_error(environment, nullptr, message.str().c_str());
    return nullptr;
  }
}

static auto from_value(napi_env environment, napi_callback_info info)
    -> napi_value {
  std::size_t argc = 1;
  napi_value args[1];
  [[maybe_unused]] napi_status status =
      napi_get_cb_info(environment, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(environment, nullptr, "from() requires 1 argument");
    return nullptr;
  }

  auto json = JSONWrapper::from_napi_value(environment, args[0]);
  return JSONWrapper::create(environment, std::move(json));
}

static auto stringify(napi_env environment, napi_callback_info info)
    -> napi_value {
  std::size_t argc = 3;
  napi_value args[3];
  [[maybe_unused]] napi_status status =
      napi_get_cb_info(environment, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(environment, nullptr,
                          "stringify() requires at least 1 argument");
    return nullptr;
  }

  sourcemeta::core::JSON *json_ptr = JSONWrapper::unwrap(environment, args[0]);
  sourcemeta::core::JSON json =
      json_ptr ? *json_ptr : JSONWrapper::from_napi_value(environment, args[0]);

  std::size_t indent = 0;
  if (argc >= 3) {
    napi_valuetype indent_type;
    status = napi_typeof(environment, args[2], &indent_type);
    assert(status == napi_ok);
    if (indent_type == napi_number) {
      int32_t indent_value;
      status = napi_get_value_int32(environment, args[2], &indent_value);
      assert(status == napi_ok);
      if (indent_value > 0) {
        indent = static_cast<std::size_t>(indent_value);
      }
    }
  }

  std::ostringstream output;
  if (indent > 0) {
    sourcemeta::core::prettify(json, output, indent);
  } else {
    sourcemeta::core::stringify(json, output);
  }

  napi_value result;
  status = napi_create_string_utf8(environment, output.str().c_str(),
                                   output.str().size(), &result);
  assert(status == napi_ok);

  return result;
}

static auto get_string_property(napi_env environment, napi_value object,
                                const char *name)
    -> std::optional<std::string> {
  napi_value property;
  napi_status status =
      napi_get_named_property(environment, object, name, &property);
  if (status != napi_ok) {
    return std::nullopt;
  }

  napi_valuetype property_type;
  status = napi_typeof(environment, property, &property_type);
  if (status != napi_ok || property_type != napi_string) {
    return std::nullopt;
  }

  std::size_t length;
  status =
      napi_get_value_string_utf8(environment, property, nullptr, 0, &length);
  if (status != napi_ok) {
    return std::nullopt;
  }

  std::string result(length, '\0');
  status = napi_get_value_string_utf8(environment, property, result.data(),
                                      length + 1, &length);
  if (status != napi_ok) {
    return std::nullopt;
  }

  return result;
}

struct ResolverContext {
  napi_env environment;
  napi_value resolve_callback;
};

static auto call_js_resolver(napi_env environment, napi_value callback,
                             std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  [[maybe_unused]] napi_status status;

  napi_value global;
  status = napi_get_global(environment, &global);
  assert(status == napi_ok);

  napi_value id_string;
  status = napi_create_string_utf8(environment, identifier.data(),
                                   identifier.size(), &id_string);
  assert(status == napi_ok);

  napi_value result;
  napi_value argv[1] = {id_string};
  status = napi_call_function(environment, global, callback, 1, argv, &result);
  if (status != napi_ok) {
    return std::nullopt;
  }

  napi_valuetype result_type;
  status = napi_typeof(environment, result, &result_type);
  assert(status == napi_ok);

  if (result_type == napi_null || result_type == napi_undefined) {
    return std::nullopt;
  }

  if (result_type != napi_object) {
    return std::nullopt;
  }

  sourcemeta::core::JSON *json_ptr = JSONWrapper::unwrap(environment, result);
  if (json_ptr) {
    return *json_ptr;
  }

  napi_throw_type_error(
      environment, nullptr,
      "resolve() callback must return a BlazeJSON document or null/undefined. "
      "Use BlazeJSON.parse() to parse your schema");
  return std::nullopt;
}

static auto compile_schema(napi_env environment, napi_callback_info info)
    -> napi_value {
  std::size_t argc = 2;
  napi_value args[2];
  [[maybe_unused]] napi_status status =
      napi_get_cb_info(environment, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(environment, nullptr,
                          "compileSchema() requires at least 1 argument");
    return nullptr;
  }

  napi_valuetype arg_type;
  status = napi_typeof(environment, args[0], &arg_type);
  assert(status == napi_ok);

  if (arg_type != napi_object) {
    napi_throw_type_error(environment, nullptr,
                          "compileSchema() schema must be an object");
    return nullptr;
  }

  sourcemeta::core::JSON *json_ptr = JSONWrapper::unwrap(environment, args[0]);
  if (!json_ptr) {
    napi_throw_type_error(
        environment, nullptr,
        "compileSchema() schema must be a BlazeJSON document. "
        "Use BlazeJSON.parse() to parse your schema first");
    return nullptr;
  }
  const sourcemeta::core::JSON &schema = *json_ptr;

  std::optional<std::string> default_dialect = std::nullopt;
  sourcemeta::blaze::Mode mode = sourcemeta::blaze::Mode::FastValidation;
  napi_value resolve_callback = nullptr;

  if (argc >= 2) {
    napi_valuetype options_type;
    status = napi_typeof(environment, args[1], &options_type);
    assert(status == napi_ok);

    if (options_type == napi_object) {
      auto dialect =
          get_string_property(environment, args[1], "defaultDialect");
      if (dialect.has_value()) {
        default_dialect = dialect.value();
      }

      auto mode_str = get_string_property(environment, args[1], "mode");
      if (mode_str.has_value() && mode_str.value() == "exhaustive") {
        mode = sourcemeta::blaze::Mode::Exhaustive;
      }

      napi_value resolve_prop;
      status = napi_get_named_property(environment, args[1], "resolve",
                                       &resolve_prop);
      if (status == napi_ok) {
        napi_valuetype resolve_type;
        status = napi_typeof(environment, resolve_prop, &resolve_type);
        if (status == napi_ok && resolve_type == napi_function) {
          resolve_callback = resolve_prop;
        }
      }
    }
  }

  try {
    sourcemeta::core::SchemaResolver resolver;

    if (resolve_callback) {
      resolver = [environment, resolve_callback](std::string_view identifier)
          -> std::optional<sourcemeta::core::JSON> {
        auto result =
            call_js_resolver(environment, resolve_callback, identifier);
        if (result.has_value()) {
          return result;
        }
        return sourcemeta::core::schema_resolver(identifier);
      };
    } else {
      resolver = sourcemeta::core::schema_resolver;
    }

    auto compiled = sourcemeta::blaze::compile(
        schema, sourcemeta::core::schema_walker, resolver,
        sourcemeta::blaze::default_schema_compiler, mode,
        default_dialect.value_or(""));

    bool is_fast = (mode == sourcemeta::blaze::Mode::FastValidation);
    return SchemaWrapper::create(environment, std::move(compiled), is_fast);
  } catch (const std::exception &error) {
    napi_throw_error(environment, nullptr, error.what());
    return nullptr;
  }
}

static auto compile_from_json(napi_env environment, napi_callback_info info)
    -> napi_value {
  std::size_t argc = 1;
  napi_value args[1];
  [[maybe_unused]] napi_status status =
      napi_get_cb_info(environment, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(environment, nullptr,
                          "restoreSchema() requires 1 argument");
    return nullptr;
  }

  napi_valuetype arg_type;
  status = napi_typeof(environment, args[0], &arg_type);
  assert(status == napi_ok);

  if (arg_type != napi_object) {
    napi_throw_type_error(environment, nullptr,
                          "restoreSchema() argument must be an object");
    return nullptr;
  }

  sourcemeta::core::JSON *json_ptr = JSONWrapper::unwrap(environment, args[0]);
  if (!json_ptr) {
    napi_throw_type_error(
        environment, nullptr,
        "restoreSchema() argument must be a BlazeJSON document. "
        "Use BlazeJSON.parse() to parse your JSON first");
    return nullptr;
  }

  try {
    auto result = sourcemeta::blaze::from_json(*json_ptr);
    if (!result.has_value()) {
      napi_throw_error(environment, nullptr, "Invalid compiled schema JSON");
      return nullptr;
    }

    bool is_fast = !result->track;
    return SchemaWrapper::create(environment, std::move(result.value()),
                                 is_fast);
  } catch (const std::exception &error) {
    napi_throw_error(environment, nullptr, error.what());
    return nullptr;
  }
}

static auto evaluate_schema(napi_env environment, napi_callback_info info)
    -> napi_value {
  std::size_t argc = 2;
  napi_value args[2];
  [[maybe_unused]] napi_status status =
      napi_get_cb_info(environment, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(environment, nullptr,
                          "evaluateSchema() requires 2 arguments");
    return nullptr;
  }

  SchemaWrapper *schema_wrapper = SchemaWrapper::unwrap(environment, args[0]);
  if (!schema_wrapper) {
    napi_throw_type_error(
        environment, nullptr,
        "evaluateSchema() first argument must be a compiled schema");
    return nullptr;
  }

  sourcemeta::core::JSON *json_ptr = JSONWrapper::unwrap(environment, args[1]);
  if (!json_ptr) {
    napi_throw_type_error(
        environment, nullptr,
        "evaluateSchema() instance must be a BlazeJSON document. "
        "Use BlazeJSON.parse() to parse your instance first");
    return nullptr;
  }
  const sourcemeta::core::JSON &instance = *json_ptr;

  try {
    if (schema_wrapper->is_fast()) {
      bool valid = evaluator.validate(schema_wrapper->get_template(), instance);

      // Return a simple JS object to avoid native memory pressure.
      // Plain JS objects are managed entirely by V8 and subject to normal GC,
      // avoiding the async finalization delay that causes memory buildup.
      napi_value result;
      status = napi_create_object(environment, &result);
      assert(status == napi_ok);

      napi_value valid_value;
      status = napi_get_boolean(environment, valid, &valid_value);
      assert(status == napi_ok);

      status =
          napi_set_named_property(environment, result, "valid", valid_value);
      assert(status == napi_ok);

      return result;
    } else {
      auto output = sourcemeta::blaze::standard(
          evaluator, schema_wrapper->get_template(), instance,
          sourcemeta::blaze::StandardOutput::Basic);

      // Convert to plain JS object for consistency with fast mode
      return JSONWrapper::to_napi_value_static(environment, output);
    }
  } catch (const std::exception &error) {
    napi_throw_error(environment, nullptr, error.what());
    return nullptr;
  }
}

static auto get_instance_count(napi_env environment, napi_callback_info info)
    -> napi_value {
  static_cast<void>(info);
  napi_value result;
  [[maybe_unused]] napi_status status = napi_create_int32(
      environment, JSONWrapper::get_instance_count(), &result);
  assert(status == napi_ok);
  return result;
}

static auto init(napi_env environment, napi_value exports) -> napi_value {
  [[maybe_unused]] napi_status status;

  napi_value json_class = JSONWrapper::init(environment);
  napi_value schema_class = SchemaWrapper::init(environment);

  napi_value parse_fn;
  status = napi_create_function(environment, "parse", NAPI_AUTO_LENGTH, parse,
                                nullptr, &parse_fn);
  assert(status == napi_ok);

  napi_value from_fn;
  status = napi_create_function(environment, "from", NAPI_AUTO_LENGTH,
                                from_value, nullptr, &from_fn);
  assert(status == napi_ok);

  napi_value stringify_fn;
  status = napi_create_function(environment, "stringify", NAPI_AUTO_LENGTH,
                                stringify, nullptr, &stringify_fn);
  assert(status == napi_ok);

  napi_value compile_fn;
  status = napi_create_function(environment, "compileSchema", NAPI_AUTO_LENGTH,
                                compile_schema, nullptr, &compile_fn);
  assert(status == napi_ok);

  napi_value restore_schema_fn;
  status = napi_create_function(environment, "restoreSchema", NAPI_AUTO_LENGTH,
                                compile_from_json, nullptr, &restore_schema_fn);
  assert(status == napi_ok);

  napi_value evaluate_fn;
  status = napi_create_function(environment, "evaluateSchema", NAPI_AUTO_LENGTH,
                                evaluate_schema, nullptr, &evaluate_fn);
  assert(status == napi_ok);

  status =
      napi_set_named_property(environment, exports, "BlazeJSON", json_class);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "BlazeSchema",
                                   schema_class);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "parse", parse_fn);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "from", from_fn);
  assert(status == napi_ok);

  status =
      napi_set_named_property(environment, exports, "stringify", stringify_fn);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "compileSchema",
                                   compile_fn);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "restoreSchema",
                                   restore_schema_fn);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "evaluateSchema",
                                   evaluate_fn);
  assert(status == napi_ok);

  napi_value instance_count_fn;
  status =
      napi_create_function(environment, "getInstanceCount", NAPI_AUTO_LENGTH,
                           get_instance_count, nullptr, &instance_count_fn);
  assert(status == napi_ok);

  status = napi_set_named_property(environment, exports, "getInstanceCount",
                                   instance_count_fn);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

} // namespace sourcemeta::blaze::nodejs
