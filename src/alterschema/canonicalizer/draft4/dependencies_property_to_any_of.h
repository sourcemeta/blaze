class DependenciesPropertyToAnyOf final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  DependenciesPropertyToAnyOf()
      : SchemaTransformRule{
            "dependencies_property_to_any_of",
            "Array-valued `dependencies` entries can be decomposed "
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
      if (entry.second.is_array()) {
        return true;
      }
    }

    return false;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    auto any_of{schema.defines("anyOf") ? schema.at("anyOf")
                                        : JSON::make_array()};

    std::vector<std::string> processed;
    for (const auto &entry : schema.at("dependencies").as_object()) {
      if (!entry.second.is_array()) {
        continue;
      }

      // Build required array: the trigger property + all dependents
      auto required_all{JSON::make_array()};
      required_all.push_back(JSON{entry.first});
      for (const auto &dependent : entry.second.as_array()) {
        required_all.push_back(dependent);
      }

      // Branch 1: not required (trigger absent)
      // Add type: "object" so TypeUnionImplicit does not expand it
      auto not_required{JSON::make_object()};
      not_required.assign("type", JSON{"object"});
      not_required.assign("required", JSON::make_array());
      not_required.at("required").push_back(JSON{entry.first});
      auto not_branch{JSON::make_object()};
      not_branch.assign("not", std::move(not_required));

      // Branch 2: all required (trigger + dependents)
      auto required_branch{JSON::make_object()};
      required_branch.assign("type", JSON{"object"});
      required_branch.assign("required", std::move(required_all));

      // Wrap in anyOf pair
      auto pair{JSON::make_array()};
      pair.push_back(std::move(not_branch));
      pair.push_back(std::move(required_branch));

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
