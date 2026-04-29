class ExclusiveMinimumFalseDrop final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExclusiveMinimumFalseDrop()
      : SchemaTransformRule{
            "exclusive_minimum_false_drop",
            "A Draft 4 `exclusiveMinimum: false` is a no-op and not a "
            "valid value in Draft 6 and later"} {};

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
        !schema.at("exclusiveMinimum").to_boolean());
    return APPLIES_TO_KEYWORDS("exclusiveMinimum");
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    schema.erase("exclusiveMinimum");
  }
};
