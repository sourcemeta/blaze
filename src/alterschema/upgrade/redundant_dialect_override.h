class RedundantDialectOverride final : public SchemaTransformRule {
private:
  static inline const std::string KEYWORD_OVERRIDE{
      "x-sourcemeta-dialect-override-subschema"};

public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  RedundantDialectOverride()
      : SchemaTransformRule{"redundant_dialect_override", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::Vocabularies &,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(schema.is_object() && schema.defines(KEYWORD_OVERRIDE) &&
                     schema.at(KEYWORD_OVERRIDE).is_string());

    const auto &override_dialect{schema.at(KEYWORD_OVERRIDE).to_string()};

    if (schema.defines("$schema") && schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == override_dialect) {
      return true;
    }

    auto current{location.parent};
    while (current.has_value()) {
      const auto enclosing{frame.traverse(current.value())};
      if (!enclosing.has_value()) {
        break;
      }

      const auto &enclosing_location{enclosing.value().get()};
      const auto enclosing_pointer{
          sourcemeta::core::to_pointer(enclosing_location.pointer)};
      const auto &enclosing_schema{
          sourcemeta::core::get(root, enclosing_pointer)};
      if (enclosing_schema.is_object() && enclosing_schema.defines("$schema") &&
          enclosing_schema.at("$schema").is_string()) {
        if (enclosing_schema.at("$schema").to_string() == override_dialect) {
          return true;
        }
        break;
      }

      current = enclosing_location.parent;
    }

    return false;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    schema.erase(KEYWORD_OVERRIDE);
  }
};
