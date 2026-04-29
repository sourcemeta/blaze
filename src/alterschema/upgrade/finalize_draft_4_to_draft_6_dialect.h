class FinalizeDraft4ToDraft6Dialect final : public SchemaTransformRule {
private:
  static inline const std::string KEYWORD_OVERRIDE{
      "x-sourcemeta-dialect-override-subschema"};
  static inline const std::string DRAFT_4_URL{
      "http://json-schema.org/draft-04/schema#"};

public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  FinalizeDraft4ToDraft6Dialect()
      : SchemaTransformRule{
            "finalize_draft_4_to_draft_6_dialect",
            "Atomically rename `id` to `$id`, bump `$schema` from Draft 4 to "
            "Draft 6, and drop the upgrade override once every Draft 4 "
            "subschema has been processed"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::Vocabularies &,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &resolver) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(schema.is_object() && schema.defines(KEYWORD_OVERRIDE) &&
                     schema.at(KEYWORD_OVERRIDE).is_string());

    const bool has_draft_4_schema{
        schema.defines("$schema") && schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == DRAFT_4_URL};
    const bool has_unrenamed_id{schema.defines("id") &&
                                schema.at("id").is_string() &&
                                !schema.defines("$id")};

    ONLY_CONTINUE_IF(has_draft_4_schema || has_unrenamed_id);

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
      if (entry_schema.is_object() && entry_schema.defines("$ref")) {
        continue;
      }

      const auto vocabularies{frame.vocabularies(entry.second, resolver)};
      if (vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_4)) {
        return false;
      }
    }

    return APPLIES_TO_KEYWORDS("$schema", "id", KEYWORD_OVERRIDE);
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    if (schema.defines("id") && schema.at("id").is_string() &&
        !schema.defines("$id")) {
      schema.rename("id", "$id");
    }

    if (schema.defines("$schema") && schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == DRAFT_4_URL) {
      auto override_value{schema.at(KEYWORD_OVERRIDE)};
      schema.assign("$schema", std::move(override_value));
    }

    schema.erase(KEYWORD_OVERRIDE);
  }
};
