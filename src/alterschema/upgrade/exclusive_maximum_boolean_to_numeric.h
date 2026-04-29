class ExclusiveMaximumBooleanToNumeric final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExclusiveMaximumBooleanToNumeric()
      : SchemaTransformRule{"exclusive_maximum_boolean_to_numeric", ""} {};

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
        schema.is_object() && schema.defines("exclusiveMaximum") &&
        schema.at("exclusiveMaximum").is_boolean() &&
        schema.at("exclusiveMaximum").to_boolean() &&
        schema.defines("maximum") && schema.at("maximum").is_number());
    return true;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    schema.erase("exclusiveMaximum");
    schema.rename("maximum", "exclusiveMaximum");
  }
};
