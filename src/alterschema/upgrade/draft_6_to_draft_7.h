class UpgradeDraft6ToDraft7 final : public SchemaTransformRule {
private:
  static inline const std::string KEYWORD_OVERRIDE{
      "x-sourcemeta-dialect-override-subschema"};
  static inline const std::string DRAFT_6_URL{
      "http://json-schema.org/draft-06/schema#"};

public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  UpgradeDraft6ToDraft7()
      : SchemaTransformRule{"upgrade_draft_6_to_draft_7", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_6) &&
        schema.is_object() && schema.defines("$schema") &&
        schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == DRAFT_6_URL);

    for (const auto &entry : frame.locations()) {
      if (entry.second.type !=
              sourcemeta::core::SchemaFrame::LocationType::Resource &&
          entry.second.type !=
              sourcemeta::core::SchemaFrame::LocationType::Subschema) {
        continue;
      }

      const auto entry_pointer{
          sourcemeta::core::to_pointer(entry.second.pointer)};
      const auto &entry_schema{sourcemeta::core::get(root, entry_pointer)};
      if (entry_schema.is_object() && entry_schema.defines(KEYWORD_OVERRIDE)) {
        return false;
      }
    }

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    schema.assign(
        "x-sourcemeta-dialect-override-subschema",
        sourcemeta::core::JSON{"http://json-schema.org/draft-07/schema#"});
    schema.assign("$schema", sourcemeta::core::JSON{
                                 "http://json-schema.org/draft-07/schema#"});
  }
};
