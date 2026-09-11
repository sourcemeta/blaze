class UnevaluatedPropertiesToAdditionalProperties final
    : public SchemaTransformRule {
public:
  using reframe_after_transform = std::true_type;
  UnevaluatedPropertiesToAdditionalProperties()
      : SchemaTransformRule{"unevaluated_properties_to_additional_properties"} {
        };

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &walker,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains_any(
            {SchemaVocabularies::Known::JSON_SCHEMA_2020_12_UNEVALUATED,
             SchemaVocabularies::Known::JSON_SCHEMA_2019_09_APPLICATOR}) &&
        schema.is_object() && schema.defines("unevaluatedProperties"));

    for (const auto &entry : schema.as_object()) {
      if (entry.first == "unevaluatedProperties") {
        continue;
      }
      const auto &metadata{walker(entry.first, vocabularies)};
      const auto keyword_type{metadata.type};
      if (keyword_type != sourcemeta::core::SchemaKeywordType::Unknown &&
          keyword_type != sourcemeta::core::SchemaKeywordType::Assertion &&
          keyword_type != sourcemeta::core::SchemaKeywordType::Annotation &&
          keyword_type != sourcemeta::core::SchemaKeywordType::Comment &&
          keyword_type != sourcemeta::core::SchemaKeywordType::Other &&
          keyword_type !=
              sourcemeta::core::SchemaKeywordType::LocationMembers) {
        return false;
      }
    }

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    schema.rename("unevaluatedProperties", "additionalProperties");
  }

  [[nodiscard]] auto rereference(const std::string_view,
                                 const sourcemeta::core::Pointer &,
                                 const sourcemeta::core::Pointer &target,
                                 const sourcemeta::core::Pointer &current) const
      -> std::optional<sourcemeta::core::Pointer> override {
    return target.rebase(current.concat("unevaluatedProperties"),
                         current.concat("additionalProperties"));
  }
};
