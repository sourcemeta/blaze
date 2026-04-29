class ExclusiveMinimumBooleanToNumeric final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExclusiveMinimumBooleanToNumeric()
      : SchemaTransformRule{
            "exclusive_minimum_boolean_to_numeric",
            "Convert a Draft 4 boolean `exclusiveMinimum` paired with a "
            "numeric `minimum` to the Draft 6+ numeric `exclusiveMinimum`"} {};

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
        schema.is_object() && schema.defines("exclusiveMinimum") &&
        schema.at("exclusiveMinimum").is_boolean() &&
        schema.at("exclusiveMinimum").to_boolean() &&
        schema.defines("minimum") && schema.at("minimum").is_number());
    return APPLIES_TO_KEYWORDS("exclusiveMinimum", "minimum");
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    schema.erase("exclusiveMinimum");
    schema.rename("minimum", "exclusiveMinimum");
  }
};
