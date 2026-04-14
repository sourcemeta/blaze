class DefinitionsToDefsNext final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  DefinitionsToDefsNext()
      : SchemaTransformRule{"definitions_to_defs_next", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_2020_12_Core,
                          Vocabularies::Known::JSON_Schema_2019_09_Core}) &&
                     schema.is_object() && schema.defines("definitions") &&
                     !schema.defines("$defs"));
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.rename("definitions", "$defs");
  }

  [[nodiscard]] auto rereference(const std::string_view, const Pointer &,
                                 const Pointer &target,
                                 const Pointer &current) const
      -> Pointer override {
    return target.rebase(current.concat({"definitions"}),
                         current.concat({"$defs"}));
  }
};
