class UnsatisfiableDuplicateOneOfBranches final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  UnsatisfiableDuplicateOneOfBranches()
      : SchemaTransformRule{
            "unsatisfiable_duplicate_oneof_branches",
            "A `oneOf` with duplicate branches is unsatisfiable, as "
            "a value that matches one duplicate will always match the "
            "other, violating the exactly-one-match requirement"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    static const JSON::String KEYWORD{"oneOf"};
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_2020_12_Applicator,
                          Vocabularies::Known::JSON_Schema_2019_09_Applicator,
                          Vocabularies::Known::JSON_Schema_Draft_7,
                          Vocabularies::Known::JSON_Schema_Draft_6,
                          Vocabularies::Known::JSON_Schema_Draft_4}) &&
                     schema.is_object() && schema.defines(KEYWORD) &&
                     !schema.defines("not") && schema.at(KEYWORD).is_array() &&
                     !schema.at(KEYWORD).unique());
    ONLY_CONTINUE_IF(!frame.has_references_through(
        location.pointer, WeakPointer::Token{std::cref(KEYWORD)}));
    return APPLIES_TO_KEYWORDS("oneOf");
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.at("oneOf").into(JSON{true});
    schema.rename("oneOf", "not");
  }
};
