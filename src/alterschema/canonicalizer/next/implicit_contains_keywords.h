class ImplicitContainsKeywords final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ImplicitContainsKeywords()
      : SchemaTransformRule{"implicit_contains_keywords", ""} {};

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
        vocabularies.contains(
            Vocabularies::Known::JSON_Schema_2019_09_Applicator) &&
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() &&
        schema.at("type").to_string() == "array" &&
        (!schema.defines("contains") || !schema.defines("minContains")));
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    const bool had_contains{schema.defines("contains")};
    if (!had_contains) {
      schema.assign("contains", sourcemeta::core::JSON{true});
    }
    if (!schema.defines("minContains")) {
      // When contains was already present, the default minContains is 1.
      // When we are adding an implicit contains: true, use minContains: 0
      // to keep both trivial (no-op)
      schema.assign("minContains",
                    sourcemeta::core::JSON{had_contains ? 1 : 0});
    }
  }
};
