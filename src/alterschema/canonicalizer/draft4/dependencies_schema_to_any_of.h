class DependenciesSchemaToAnyOf final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  DependenciesSchemaToAnyOf()
      : SchemaTransformRule{
            "dependencies_schema_to_any_of",
            "Schema-valued `dependencies` entries can be decomposed "
            "into an equivalent `anyOf`"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_4) &&
        schema.is_object() && schema.defines("dependencies") &&
        schema.at("dependencies").is_object());

    for (const auto &entry : schema.at("dependencies").as_object()) {
      if (is_schema(entry.second)) {
        return APPLIES_TO_KEYWORDS("dependencies");
      }
    }

    return false;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    auto any_of{schema.defines("anyOf") ? schema.at("anyOf")
                                        : JSON::make_array()};

    std::vector<std::string> processed;
    for (const auto &entry : schema.at("dependencies").as_object()) {
      if (!is_schema(entry.second)) {
        continue;
      }

      // Branch 1: not required (trigger absent)
      auto not_required{JSON::make_object()};
      not_required.assign("type", JSON{"object"});
      not_required.assign("required", JSON::make_array());
      not_required.at("required").push_back(JSON{entry.first});
      auto not_branch{JSON::make_object()};
      not_branch.assign("not", std::move(not_required));

      // Branch 2: trigger required + dependent schema in allOf
      auto required_obj{JSON::make_object()};
      required_obj.assign("type", JSON{"object"});
      required_obj.assign("required", JSON::make_array());
      required_obj.at("required").push_back(JSON{entry.first});

      auto all_of{JSON::make_array()};
      all_of.push_back(std::move(required_obj));
      all_of.push_back(entry.second);

      auto allof_branch{JSON::make_object()};
      allof_branch.assign("allOf", std::move(all_of));

      // Wrap in anyOf pair
      auto pair{JSON::make_array()};
      pair.push_back(std::move(not_branch));
      pair.push_back(std::move(allof_branch));

      auto wrapper{JSON::make_object()};
      wrapper.assign("anyOf", std::move(pair));
      any_of.push_back(std::move(wrapper));

      processed.push_back(entry.first);
    }

    for (const auto &key : processed) {
      schema.at("dependencies").erase(key);
    }

    if (schema.at("dependencies").empty()) {
      schema.erase("dependencies");
    }

    if (schema.defines("allOf") && schema.at("allOf").is_array()) {
      for (auto &item : any_of.as_array()) {
        schema.at("allOf").push_back(std::move(item));
      }
    } else {
      schema.assign("allOf", std::move(any_of));
    }
  }
};
