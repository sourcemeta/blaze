class Draft3TypeAnyInArray final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  Draft3TypeAnyInArray()
      : SchemaTransformRule{
            "draft3_type_any_in_array",
            "A `type` array that contains `any` accepts any value, "
            "and is equivalent to just `type: any`"} {};

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
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_array());

    for (const auto &element : schema.at("type").as_array()) {
      if (element.is_string() && element.to_string() == "any") {
        return true;
      }
      if (element.is_object() && element.defines("type") &&
          element.at("type").is_string() &&
          element.at("type").to_string() == "any") {
        return true;
      }
    }

    return false;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.assign("type", sourcemeta::core::JSON{"any"});
  }
};
