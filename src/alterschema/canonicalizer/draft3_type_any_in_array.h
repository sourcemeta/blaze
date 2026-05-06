class Draft3TypeAnyInArray final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  Draft3TypeAnyInArray()
      : SchemaTransformRule{"draft3_type_any_in_array", ""} {};

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
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_3) &&
        schema.is_object());

    const auto *type{schema.try_at("type")};
    ONLY_CONTINUE_IF(type && type->is_array());

    for (const auto &element : type->as_array()) {
      if (element.is_string() && element.to_string() == "any") {
        return true;
      }
      if (element.is_object() && element.size() == 1) {
        const auto *element_type{element.try_at("type")};
        if (element_type && element_type->is_string() &&
            element_type->to_string() == "any") {
          return true;
        }
      }
    }

    return false;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.erase("type");
  }
};
