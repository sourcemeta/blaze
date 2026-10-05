class DisjunctorMinBranches final : public SchemaTransformRule {
public:
  using mutates = std::false_type;
  using reframe_after_transform = std::false_type;
  DisjunctorMinBranches()
      : SchemaTransformRule{
            "disjunctor_min_branches",
            "A `oneOf` or `anyOf` keyword should have at least 2 "
            "branches to be meaningful"} {};
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
    const auto *anyof_value{schema.try_at("anyOf")};
    const bool oneof_bad{oneof_value && oneof_value->is_array() &&
                         oneof_value->size() < 2};
    const bool anyof_bad{anyof_value && anyof_value->is_array() &&
                         anyof_value->size() < 2};
    ONLY_CONTINUE_IF(oneof_bad || anyof_bad);
    if (oneof_bad && anyof_bad) {
      return APPLIES_TO_KEYWORDS("oneOf", "anyOf");
    }
    return oneof_bad ? APPLIES_TO_KEYWORDS("oneOf")
                     : APPLIES_TO_KEYWORDS("anyOf");
  }
};
