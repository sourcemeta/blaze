class MetaschemaVocabulary final : public SchemaTransformRule {
public:
  using reframe_after_transform = std::true_type;
  MetaschemaVocabulary() : SchemaTransformRule{"metaschema_vocabulary"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &,
            const bool is_metaschema) const -> bool override {
    ONLY_CONTINUE_IF(schema.is_object() && !schema.defines("$vocabulary"));

    // Whichever dialect the meta-schema ends up on is the one whose
    // vocabularies it has to declare, rather than the one the caller asked to
    // convert to
    this->emits_2020_12_ = vocabularies.contains(
        SchemaVocabularies::Known::JSON_SCHEMA_2020_12_CORE);
    ONLY_CONTINUE_IF(this->emits_2020_12_ ||
                     vocabularies.contains(
                         SchemaVocabularies::Known::JSON_SCHEMA_2019_09_CORE));

    return (is_metaschema && location.pointer.empty()) ||
           is_metaschema_target(schema, frame, location.pointer);
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    if (this->emits_2020_12_) {
      synthesize_vocabulary(schema, VOCABULARIES_2020_12);
    } else {
      synthesize_vocabulary(schema, VOCABULARIES_2019_09);
    }
  }

private:
  mutable bool emits_2020_12_{false};
};
