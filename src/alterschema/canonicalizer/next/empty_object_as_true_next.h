class EmptyObjectAsTrueNext final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::false_type;
  EmptyObjectAsTrueNext()
      : SchemaTransformRule{
            "empty_object_as_true_next",
            "The empty schema `{}` accepts all values and is equivalent to the "
            "boolean schema `true`"} {};

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
        vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_4,
                                   Vocabularies::Known::JSON_Schema_Draft_6}) &&
        schema.is_object() && schema.empty());
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.into(JSON{true});
  }
};
