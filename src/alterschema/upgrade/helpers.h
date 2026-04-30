static constexpr std::string_view DIALECT_OVERRIDE_KEYWORD{
    "x-sourcemeta-dialect-override-subschema"};

static auto mark_dialect_override(sourcemeta::core::JSON &schema,
                                  const std::string_view dialect) -> void {
  if (!schema.defines(std::string{DIALECT_OVERRIDE_KEYWORD})) {
    schema.assign(std::string{DIALECT_OVERRIDE_KEYWORD},
                  sourcemeta::core::JSON{std::string{dialect}});
  }
}

static auto drop_dialect_overrides(sourcemeta::core::JSON &schema,
                                   const bool is_root) -> void {
  if (schema.is_array()) {
    for (auto &item : schema.as_array()) {
      drop_dialect_overrides(item, false);
    }
    return;
  }

  if (!schema.is_object()) {
    return;
  }

  if (!is_root && schema.defines("$schema") &&
      schema.at("$schema").is_string()) {
    return;
  }

  schema.erase(std::string{DIALECT_OVERRIDE_KEYWORD});

  std::vector<std::string> keys;
  keys.reserve(schema.size());
  for (const auto &entry : schema.as_object()) {
    keys.push_back(entry.first);
  }
  for (const auto &key : keys) {
    drop_dialect_overrides(schema.at(key), false);
  }
}
