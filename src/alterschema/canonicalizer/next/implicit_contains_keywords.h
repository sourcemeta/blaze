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
    ONLY_CONTINUE_IF(vocabularies.contains(
                         Vocabularies::Known::JSON_Schema_2019_09_Applicator) &&
                     schema.is_object() && schema.defines("type") &&
                     schema.at("type").is_string() &&
                     schema.at("type").to_string() == "array");

    if (schema.defines("contains")) {
      // `contains` is present, just fill in the default `minContains`
      ONLY_CONTINUE_IF(!schema.defines("minContains"));
    } else {
      // Only synthesize `contains` when no contains-related keywords
      // exist. If `minContains`/`maxContains` are present without
      // `contains`, they are no-ops per the spec and should be stripped
      // by other rules first
      ONLY_CONTINUE_IF(!schema.defines("minContains") &&
                       !schema.defines("maxContains"));
    }

    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    if (!schema.defines("contains")) {
      schema.assign("contains", sourcemeta::core::JSON{true});
      schema.assign("minContains", sourcemeta::core::JSON{0});
    } else {
      schema.assign("minContains", sourcemeta::core::JSON{1});
    }
  }
};
