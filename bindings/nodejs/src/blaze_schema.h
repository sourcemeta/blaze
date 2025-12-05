#ifndef SOURCEMETA_BLAZE_NODEJS_BLAZE_SCHEMA_H_
#define SOURCEMETA_BLAZE_NODEJS_BLAZE_SCHEMA_H_

#include "blaze_json.h"

#include <node_api.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <cassert>   // assert
#include <optional>  // std::optional
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace sourcemeta::blaze::nodejs {

class SchemaWrapper {
public:
  static inline napi_ref constructor_reference = nullptr;

  static auto init(napi_env environment) -> napi_value {
    napi_property_descriptor properties[] = {
        {"toJSON", nullptr, to_json, nullptr, nullptr, nullptr, napi_default,
         nullptr},
    };

    napi_value result;
    [[maybe_unused]] napi_status status = napi_define_class(
        environment, "BlazeSchema", NAPI_AUTO_LENGTH, constructor, nullptr,
        sizeof(properties) / sizeof(properties[0]), properties, &result);
    assert(status == napi_ok);

    status =
        napi_create_reference(environment, result, 1, &constructor_reference);
    assert(status == napi_ok);

    return result;
  }

  static auto create(napi_env environment,
                     sourcemeta::blaze::Template input_template,
                     bool is_fast_mode) -> napi_value {
    napi_value constructor_value;
    [[maybe_unused]] napi_status status = napi_get_reference_value(
        environment, constructor_reference, &constructor_value);
    assert(status == napi_ok);

    napi_value instance;
    status = napi_new_instance(environment, constructor_value, 0, nullptr,
                               &instance);
    assert(status == napi_ok);

    auto *wrapper = new SchemaWrapper(std::move(input_template), is_fast_mode);
    status =
        napi_wrap(environment, instance, wrapper, destructor, nullptr, nullptr);
    assert(status == napi_ok);

    return instance;
  }

  static auto unwrap(napi_env environment, napi_value object)
      -> SchemaWrapper * {
    SchemaWrapper *wrapper;
    napi_status status =
        napi_unwrap(environment, object, reinterpret_cast<void **>(&wrapper));
    if (status != napi_ok) {
      return nullptr;
    }
    return wrapper;
  }

  auto get_template() -> sourcemeta::blaze::Template & {
    return this->schema_template;
  }

  auto is_fast() const -> bool { return this->fast_mode; }

private:
  explicit SchemaWrapper(sourcemeta::blaze::Template input_template,
                         bool is_fast_mode)
      : schema_template{std::move(input_template)}, fast_mode{is_fast_mode} {}

  ~SchemaWrapper() = default;

  static auto destructor(napi_env environment, void *native_object, void *hint)
      -> void {
    static_cast<void>(environment);
    static_cast<void>(hint);
    delete static_cast<SchemaWrapper *>(native_object);
  }

  static auto constructor(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);
    return this_value;
  }

  static auto to_json(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);

    SchemaWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    auto json = sourcemeta::blaze::to_json(wrapper->schema_template);
    return JSONWrapper::create(environment, std::move(json));
  }

  sourcemeta::blaze::Template schema_template;
  bool fast_mode;
};

} // namespace sourcemeta::blaze::nodejs

#endif
