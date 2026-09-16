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
    ONLY_CONTINUE_IF(vocabularies.contains(
                         SchemaVocabularies::Known::JSON_SCHEMA_2019_09_CORE) &&
                     schema.is_object() && !schema.defines("$vocabulary"));
    return (is_metaschema && location.pointer.empty()) ||
           is_metaschema_target(schema, frame, location.pointer);
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    synthesize_2019_09_vocabulary(schema);
  }

private:
  static constexpr std::string_view VOCAB_2019_09_CORE_URL{
      "https://json-schema.org/draft/2019-09/vocab/core"};
  static constexpr std::string_view VOCAB_2019_09_APPLICATOR_URL{
      "https://json-schema.org/draft/2019-09/vocab/applicator"};
  static constexpr std::string_view VOCAB_2019_09_VALIDATION_URL{
      "https://json-schema.org/draft/2019-09/vocab/validation"};
  static constexpr std::string_view VOCAB_2019_09_META_DATA_URL{
      "https://json-schema.org/draft/2019-09/vocab/meta-data"};
  static constexpr std::string_view VOCAB_2019_09_FORMAT_URL{
      "https://json-schema.org/draft/2019-09/vocab/format"};
  static constexpr std::string_view VOCAB_2019_09_CONTENT_URL{
      "https://json-schema.org/draft/2019-09/vocab/content"};

  static auto synthesize_2019_09_vocabulary(sourcemeta::core::JSON &schema)
      -> void {
    std::string_view anchor;
    if (schema.defines("$id")) {
      anchor = "$id";
    } else if (schema.defines("$schema")) {
      anchor = "$schema";
    }

    const std::string *next_key{nullptr};
    if (!anchor.empty()) {
      bool found_anchor{false};
      for (const auto &entry : schema.as_object()) {
        if (found_anchor) {
          next_key = &entry.first;
          break;
        }
        if (entry.first == anchor) {
          found_anchor = true;
        }
      }
    }

    if (next_key != nullptr) {
      schema.try_assign_before(
          "$vocabulary", sourcemeta::core::JSON::make_object(), *next_key);
    } else {
      schema.assign_assume_new("$vocabulary",
                               sourcemeta::core::JSON::make_object());
    }

    auto &vocabularies{schema.at("$vocabulary")};
    vocabularies.assign_assume_new(std::string{VOCAB_2019_09_CORE_URL},
                                   sourcemeta::core::JSON{true});
    vocabularies.assign_assume_new(std::string{VOCAB_2019_09_APPLICATOR_URL},
                                   sourcemeta::core::JSON{true});
    vocabularies.assign_assume_new(std::string{VOCAB_2019_09_VALIDATION_URL},
                                   sourcemeta::core::JSON{true});
    vocabularies.assign_assume_new(std::string{VOCAB_2019_09_META_DATA_URL},
                                   sourcemeta::core::JSON{true});
    vocabularies.assign_assume_new(std::string{VOCAB_2019_09_FORMAT_URL},
                                   sourcemeta::core::JSON{false});
    vocabularies.assign_assume_new(std::string{VOCAB_2019_09_CONTENT_URL},
                                   sourcemeta::core::JSON{true});
  }
};
