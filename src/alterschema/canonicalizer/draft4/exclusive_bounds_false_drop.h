class ExclusiveBoundsFalseDrop final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExclusiveBoundsFalseDrop()
      : SchemaTransformRule{
            "exclusive_bounds_false_drop",
            "Setting boolean `exclusiveMinimum` or `exclusiveMaximum` to "
            "false on an integer is a no-op and can be removed"} {};

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
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() &&
        schema.at("type").to_string() == "integer");

    const bool has_exclusive_min{schema.defines("exclusiveMinimum") &&
                                 schema.at("exclusiveMinimum").is_boolean() &&
                                 !schema.at("exclusiveMinimum").to_boolean()};
    const bool has_exclusive_max{schema.defines("exclusiveMaximum") &&
                                 schema.at("exclusiveMaximum").is_boolean() &&
                                 !schema.at("exclusiveMaximum").to_boolean()};

    ONLY_CONTINUE_IF(has_exclusive_min || has_exclusive_max);

    if (has_exclusive_min && has_exclusive_max) {
      return APPLIES_TO_KEYWORDS("exclusiveMinimum", "exclusiveMaximum");
    } else if (has_exclusive_min) {
      return APPLIES_TO_KEYWORDS("exclusiveMinimum");
    } else {
      return APPLIES_TO_KEYWORDS("exclusiveMaximum");
    }
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    if (schema.defines("exclusiveMinimum") &&
        schema.at("exclusiveMinimum").is_boolean() &&
        !schema.at("exclusiveMinimum").to_boolean()) {
      schema.erase("exclusiveMinimum");
    }

    if (schema.defines("exclusiveMaximum") &&
        schema.at("exclusiveMaximum").is_boolean() &&
        !schema.at("exclusiveMaximum").to_boolean()) {
      schema.erase("exclusiveMaximum");
    }
  }
};
