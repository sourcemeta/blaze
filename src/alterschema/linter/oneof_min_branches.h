class OneofMinBranches final : public SchemaTransformRule {
public:
  using mutates = std::false_type;
  using reframe_after_transform = std::false_type;
  OneofMinBranches()
      : SchemaTransformRule{
            "oneof_min_branches",
            "The `oneOf` keyword should have at least 2 branches to be "
            "meaningful"} {};
  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::Vocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &,
            const sourcemeta::blaze::SchemaWalker &,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
        {Vocabularies::Known::JSON_Schema_2020_12_Applicator,
         Vocabularies::Known::JSON_Schema_2019_09_Applicator,
         Vocabularies::Known::JSON_Schema_Draft_7,
         Vocabularies::Known::JSON_Schema_Draft_6,
         Vocabularies::Known::JSON_Schema_Draft_4}));
    ONLY_CONTINUE_IF(schema.is_object());
    const auto *oneof_value{schema.try_at("oneOf")};
    ONLY_CONTINUE_IF(oneof_value && oneof_value->is_array());
    ONLY_CONTINUE_IF(oneof_value->size() < 2);
    return APPLIES_TO_KEYWORDS("oneOf");
  }
};
