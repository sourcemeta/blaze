#ifndef SOURCEMETA_BLAZE_NODEJS_BLAZE_JSON_H_
#define SOURCEMETA_BLAZE_NODEJS_BLAZE_JSON_H_

#include <node_api.h>

#include <sourcemeta/core/json.h>

#include <atomic>  // std::atomic
#include <cassert> // assert
#include <cstdint> // std::int64_t
#include <sstream> // std::ostringstream
#include <string>  // std::string

namespace sourcemeta::blaze::nodejs {

class JSONWrapper {
public:
  static inline napi_ref constructor_reference = nullptr;

  static auto init(napi_env environment) -> napi_value {
    napi_property_descriptor properties[] = {
        {"get", nullptr, get_property, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"set", nullptr, set_property, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"delete", nullptr, delete_property, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"keys", nullptr, get_property_names, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"has", nullptr, has_property, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"toJSON", nullptr, to_json, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"type", nullptr, get_type, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"length", nullptr, nullptr, get_length, nullptr, nullptr, napi_default,
         nullptr},
    };

    napi_value result;
    [[maybe_unused]] napi_status status = napi_define_class(
        environment, "BlazeJSON", NAPI_AUTO_LENGTH, constructor, nullptr,
        sizeof(properties) / sizeof(properties[0]), properties, &result);
    assert(status == napi_ok);

    status =
        napi_create_reference(environment, result, 1, &constructor_reference);
    assert(status == napi_ok);

    return result;
  }

  static auto create(napi_env environment, sourcemeta::core::JSON value)
      -> napi_value {
    napi_value constructor_value;
    [[maybe_unused]] napi_status status = napi_get_reference_value(
        environment, constructor_reference, &constructor_value);
    assert(status == napi_ok);

    napi_value instance;
    status = napi_new_instance(environment, constructor_value, 0, nullptr,
                               &instance);
    assert(status == napi_ok);

    auto *wrapper = new JSONWrapper(std::move(value));
    ++instance_count;
    status =
        napi_wrap(environment, instance, wrapper, destructor, nullptr, nullptr);
    assert(status == napi_ok);

    return instance;
  }

  static auto get_instance_count() -> int { return instance_count.load(); }

  static auto unwrap(napi_env environment, napi_value object)
      -> sourcemeta::core::JSON * {
    JSONWrapper *wrapper;
    napi_status status =
        napi_unwrap(environment, object, reinterpret_cast<void **>(&wrapper));
    if (status != napi_ok) {
      return nullptr;
    }
    return &wrapper->data;
  }

  // Convert a JSON value to a plain JavaScript value (not a BlazeJSON wrapper)
  static auto to_napi_value_static(napi_env environment,
                                   const sourcemeta::core::JSON &json)
      -> napi_value {
    return to_napi_value(environment, json);
  }

private:
  explicit JSONWrapper(sourcemeta::core::JSON value) : data{std::move(value)} {}

  ~JSONWrapper() = default;

  static inline std::atomic<int> instance_count{0};

  static auto destructor(napi_env environment, void *native_object, void *hint)
      -> void {
    static_cast<void>(environment);
    static_cast<void>(hint);
    --instance_count;
    delete static_cast<JSONWrapper *>(native_object);
  }

  static auto constructor(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);
    return this_value;
  }

  static auto to_napi_value(napi_env environment,
                            const sourcemeta::core::JSON &json) -> napi_value {
    napi_value result;
    [[maybe_unused]] napi_status status;

    switch (json.type()) {
      case sourcemeta::core::JSON::Type::Null:
        status = napi_get_null(environment, &result);
        assert(status == napi_ok);
        return result;

      case sourcemeta::core::JSON::Type::Boolean:
        status = napi_get_boolean(environment, json.to_boolean(), &result);
        assert(status == napi_ok);
        return result;

      case sourcemeta::core::JSON::Type::Integer:
        status = napi_create_int64(environment, json.to_integer(), &result);
        assert(status == napi_ok);
        return result;

      case sourcemeta::core::JSON::Type::Real:
        status = napi_create_double(environment, json.to_real(), &result);
        assert(status == napi_ok);
        return result;

      case sourcemeta::core::JSON::Type::String: {
        const auto &string_value = json.to_string();
        status = napi_create_string_utf8(environment, string_value.c_str(),
                                         string_value.size(), &result);
        assert(status == napi_ok);
        return result;
      }

      case sourcemeta::core::JSON::Type::Array: {
        status =
            napi_create_array_with_length(environment, json.size(), &result);
        assert(status == napi_ok);
        std::size_t index = 0;
        for (const auto &element : json.as_array()) {
          napi_value element_value = to_napi_value(environment, element);
          status = napi_set_element(
              environment, result, static_cast<uint32_t>(index), element_value);
          assert(status == napi_ok);
          ++index;
        }
        return result;
      }

      case sourcemeta::core::JSON::Type::Object: {
        status = napi_create_object(environment, &result);
        assert(status == napi_ok);
        for (const auto &entry : json.as_object()) {
          napi_value property_value = to_napi_value(environment, entry.second);
          status = napi_set_named_property(environment, result,
                                           entry.first.c_str(), property_value);
          assert(status == napi_ok);
        }
        return result;
      }

      case sourcemeta::core::JSON::Type::Decimal: {
        status = napi_create_double(environment, json.to_decimal().to_double(),
                                    &result);
        assert(status == napi_ok);
        return result;
      }
    }

    status = napi_get_undefined(environment, &result);
    assert(status == napi_ok);
    return result;
  }

public:
  static auto from_napi_value(napi_env environment, napi_value value)
      -> sourcemeta::core::JSON {
    napi_valuetype value_type;
    [[maybe_unused]] napi_status status =
        napi_typeof(environment, value, &value_type);
    assert(status == napi_ok);

    switch (value_type) {
      case napi_undefined:
      case napi_null:
        return sourcemeta::core::JSON{nullptr};

      case napi_boolean: {
        bool result;
        status = napi_get_value_bool(environment, value, &result);
        assert(status == napi_ok);
        return sourcemeta::core::JSON{result};
      }

      case napi_number: {
        double result;
        status = napi_get_value_double(environment, value, &result);
        assert(status == napi_ok);
        if (result == static_cast<std::int64_t>(result)) {
          return sourcemeta::core::JSON{static_cast<std::int64_t>(result)};
        }
        return sourcemeta::core::JSON{result};
      }

      case napi_string: {
        std::size_t length;
        status =
            napi_get_value_string_utf8(environment, value, nullptr, 0, &length);
        assert(status == napi_ok);
        std::string result(length, '\0');
        status = napi_get_value_string_utf8(environment, value, result.data(),
                                            length + 1, &length);
        assert(status == napi_ok);
        return sourcemeta::core::JSON{result};
      }

      case napi_object: {
        bool is_array;
        status = napi_is_array(environment, value, &is_array);
        assert(status == napi_ok);

        if (is_array) {
          uint32_t length;
          status = napi_get_array_length(environment, value, &length);
          assert(status == napi_ok);

          auto result = sourcemeta::core::JSON::make_array();
          for (uint32_t index = 0; index < length; ++index) {
            napi_value element;
            status = napi_get_element(environment, value, index, &element);
            assert(status == napi_ok);
            result.push_back(from_napi_value(environment, element));
          }
          return result;
        } else {
          napi_value property_names;
          status = napi_get_property_names(environment, value, &property_names);
          assert(status == napi_ok);

          uint32_t length;
          status = napi_get_array_length(environment, property_names, &length);
          assert(status == napi_ok);

          auto result = sourcemeta::core::JSON::make_object();
          for (uint32_t index = 0; index < length; ++index) {
            napi_value key;
            status = napi_get_element(environment, property_names, index, &key);
            assert(status == napi_ok);

            std::size_t key_length;
            status = napi_get_value_string_utf8(environment, key, nullptr, 0,
                                                &key_length);
            assert(status == napi_ok);
            std::string key_string(key_length, '\0');
            status =
                napi_get_value_string_utf8(environment, key, key_string.data(),
                                           key_length + 1, &key_length);
            assert(status == napi_ok);

            napi_value property_value;
            status = napi_get_named_property(
                environment, value, key_string.c_str(), &property_value);
            assert(status == napi_ok);
            result.assign(key_string,
                          from_napi_value(environment, property_value));
          }
          return result;
        }
      }

      default:
        return sourcemeta::core::JSON{nullptr};
    }
  }

private:
  static auto get_property(napi_env environment, napi_callback_info info)
      -> napi_value {
    std::size_t argc = 1;
    napi_value args[1];
    napi_value this_value;
    [[maybe_unused]] napi_status status =
        napi_get_cb_info(environment, info, &argc, args, &this_value, nullptr);
    assert(status == napi_ok);

    if (argc < 1) {
      napi_value undefined;
      status = napi_get_undefined(environment, &undefined);
      assert(status == napi_ok);
      return undefined;
    }

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    napi_valuetype arg_type;
    status = napi_typeof(environment, args[0], &arg_type);
    assert(status == napi_ok);

    if (wrapper->data.is_array() && arg_type == napi_number) {
      uint32_t index;
      status = napi_get_value_uint32(environment, args[0], &index);
      assert(status == napi_ok);

      if (index < wrapper->data.size()) {
        const auto &element = wrapper->data.at(index);
        if (element.is_object() || element.is_array()) {
          return create(environment, sourcemeta::core::JSON{element});
        }
        return to_napi_value(environment, element);
      }
    } else if (wrapper->data.is_object() && arg_type == napi_string) {
      std::size_t length;
      status =
          napi_get_value_string_utf8(environment, args[0], nullptr, 0, &length);
      assert(status == napi_ok);
      std::string key(length, '\0');
      status = napi_get_value_string_utf8(environment, args[0], key.data(),
                                          length + 1, &length);
      assert(status == napi_ok);

      if (wrapper->data.defines(key)) {
        const auto &value = wrapper->data.at(key);
        if (value.is_object() || value.is_array()) {
          return create(environment, sourcemeta::core::JSON{value});
        }
        return to_napi_value(environment, value);
      }
    }

    napi_value undefined;
    status = napi_get_undefined(environment, &undefined);
    assert(status == napi_ok);
    return undefined;
  }

  static auto set_property(napi_env environment, napi_callback_info info)
      -> napi_value {
    std::size_t argc = 2;
    napi_value args[2];
    napi_value this_value;
    [[maybe_unused]] napi_status status =
        napi_get_cb_info(environment, info, &argc, args, &this_value, nullptr);
    assert(status == napi_ok);

    napi_value result;
    status = napi_get_boolean(environment, false, &result);
    assert(status == napi_ok);

    if (argc < 2) {
      return result;
    }

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    napi_valuetype arg_type;
    status = napi_typeof(environment, args[0], &arg_type);
    assert(status == napi_ok);

    sourcemeta::core::JSON new_value = from_napi_value(environment, args[1]);

    if (wrapper->data.is_array() && arg_type == napi_number) {
      uint32_t index;
      status = napi_get_value_uint32(environment, args[0], &index);
      assert(status == napi_ok);

      while (wrapper->data.size() <= index) {
        wrapper->data.push_back(sourcemeta::core::JSON{nullptr});
      }
      wrapper->data.at(index).into(std::move(new_value));
      status = napi_get_boolean(environment, true, &result);
      assert(status == napi_ok);
    } else if (wrapper->data.is_object() && arg_type == napi_string) {
      std::size_t length;
      status =
          napi_get_value_string_utf8(environment, args[0], nullptr, 0, &length);
      assert(status == napi_ok);
      std::string key(length, '\0');
      status = napi_get_value_string_utf8(environment, args[0], key.data(),
                                          length + 1, &length);
      assert(status == napi_ok);

      wrapper->data.assign(key, std::move(new_value));
      status = napi_get_boolean(environment, true, &result);
      assert(status == napi_ok);
    }

    return result;
  }

  static auto delete_property(napi_env environment, napi_callback_info info)
      -> napi_value {
    std::size_t argc = 1;
    napi_value args[1];
    napi_value this_value;
    [[maybe_unused]] napi_status status =
        napi_get_cb_info(environment, info, &argc, args, &this_value, nullptr);
    assert(status == napi_ok);

    napi_value result;
    status = napi_get_boolean(environment, false, &result);
    assert(status == napi_ok);

    if (argc < 1) {
      return result;
    }

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    if (wrapper->data.is_object()) {
      napi_valuetype arg_type;
      status = napi_typeof(environment, args[0], &arg_type);
      assert(status == napi_ok);

      if (arg_type == napi_string) {
        std::size_t length;
        status = napi_get_value_string_utf8(environment, args[0], nullptr, 0,
                                            &length);
        assert(status == napi_ok);
        std::string key(length, '\0');
        status = napi_get_value_string_utf8(environment, args[0], key.data(),
                                            length + 1, &length);
        assert(status == napi_ok);

        if (wrapper->data.defines(key)) {
          wrapper->data.erase(key);
          status = napi_get_boolean(environment, true, &result);
          assert(status == napi_ok);
        }
      }
    }

    return result;
  }

  static auto get_property_names(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    napi_value result;
    if (wrapper->data.is_object()) {
      status = napi_create_array_with_length(environment, wrapper->data.size(),
                                             &result);
      assert(status == napi_ok);

      uint32_t index = 0;
      for (const auto &entry : wrapper->data.as_object()) {
        napi_value key_value;
        status = napi_create_string_utf8(environment, entry.first.c_str(),
                                         entry.first.size(), &key_value);
        assert(status == napi_ok);
        status = napi_set_element(environment, result, index, key_value);
        assert(status == napi_ok);
        ++index;
      }
    } else if (wrapper->data.is_array()) {
      status = napi_create_array_with_length(environment, wrapper->data.size(),
                                             &result);
      assert(status == napi_ok);

      for (uint32_t index = 0; index < wrapper->data.size(); ++index) {
        napi_value index_value;
        status = napi_create_uint32(environment, index, &index_value);
        assert(status == napi_ok);
        status = napi_set_element(environment, result, index, index_value);
        assert(status == napi_ok);
      }
    } else {
      status = napi_create_array(environment, &result);
      assert(status == napi_ok);
    }

    return result;
  }

  static auto has_property(napi_env environment, napi_callback_info info)
      -> napi_value {
    std::size_t argc = 1;
    napi_value args[1];
    napi_value this_value;
    [[maybe_unused]] napi_status status =
        napi_get_cb_info(environment, info, &argc, args, &this_value, nullptr);
    assert(status == napi_ok);

    napi_value result;
    status = napi_get_boolean(environment, false, &result);
    assert(status == napi_ok);

    if (argc < 1) {
      return result;
    }

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    napi_valuetype arg_type;
    status = napi_typeof(environment, args[0], &arg_type);
    assert(status == napi_ok);

    if (wrapper->data.is_array() && arg_type == napi_number) {
      uint32_t index;
      status = napi_get_value_uint32(environment, args[0], &index);
      assert(status == napi_ok);
      status =
          napi_get_boolean(environment, index < wrapper->data.size(), &result);
      assert(status == napi_ok);
    } else if (wrapper->data.is_object() && arg_type == napi_string) {
      std::size_t length;
      status =
          napi_get_value_string_utf8(environment, args[0], nullptr, 0, &length);
      assert(status == napi_ok);
      std::string key(length, '\0');
      status = napi_get_value_string_utf8(environment, args[0], key.data(),
                                          length + 1, &length);
      assert(status == napi_ok);
      status =
          napi_get_boolean(environment, wrapper->data.defines(key), &result);
      assert(status == napi_ok);
    }

    return result;
  }

  static auto to_json(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    return to_napi_value(environment, wrapper->data);
  }

  static auto get_type(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    const char *type_name;
    switch (wrapper->data.type()) {
      case sourcemeta::core::JSON::Type::Null:
        type_name = "null";
        break;
      case sourcemeta::core::JSON::Type::Boolean:
        type_name = "boolean";
        break;
      case sourcemeta::core::JSON::Type::Integer:
        type_name = "integer";
        break;
      case sourcemeta::core::JSON::Type::Real:
      case sourcemeta::core::JSON::Type::Decimal:
        type_name = "real";
        break;
      case sourcemeta::core::JSON::Type::String:
        type_name = "string";
        break;
      case sourcemeta::core::JSON::Type::Array:
        type_name = "array";
        break;
      case sourcemeta::core::JSON::Type::Object:
        type_name = "object";
        break;
      default:
        type_name = "unknown";
        break;
    }

    napi_value result;
    status = napi_create_string_utf8(environment, type_name, NAPI_AUTO_LENGTH,
                                     &result);
    assert(status == napi_ok);
    return result;
  }

  static auto get_length(napi_env environment, napi_callback_info info)
      -> napi_value {
    napi_value this_value;
    [[maybe_unused]] napi_status status = napi_get_cb_info(
        environment, info, nullptr, nullptr, &this_value, nullptr);
    assert(status == napi_ok);

    JSONWrapper *wrapper;
    status = napi_unwrap(environment, this_value,
                         reinterpret_cast<void **>(&wrapper));
    assert(status == napi_ok);

    napi_value result;
    if (wrapper->data.is_array() || wrapper->data.is_object() ||
        wrapper->data.is_string()) {
      status = napi_create_uint32(
          environment, static_cast<uint32_t>(wrapper->data.size()), &result);
    } else {
      status = napi_get_undefined(environment, &result);
    }
    assert(status == napi_ok);

    return result;
  }

  sourcemeta::core::JSON data;
};

} // namespace sourcemeta::blaze::nodejs

#endif
