class MarkDraft4AsDraft6 final : public SchemaTransformRule {
private:
  static inline const std::string KEYWORD_OVERRIDE{
      "x-sourcemeta-dialect-override-subschema"};
  static inline const std::string DRAFT_6_URL{
      "http://json-schema.org/draft-06/schema#"};

public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  MarkDraft4AsDraft6() : SchemaTransformRule{"mark_draft_4_as_draft_6", ""} {};

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
        schema.is_object() && !schema.defines(KEYWORD_OVERRIDE) &&
        !schema.defines("$ref"));
    return true;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    schema.assign(KEYWORD_OVERRIDE, sourcemeta::core::JSON{DRAFT_6_URL});
  }
};
