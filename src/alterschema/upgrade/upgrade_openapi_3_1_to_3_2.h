class UpgradeOpenAPI31To32 final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  UpgradeOpenAPI31To32()
      : SchemaTransformRule{"upgrade_openapi_3_1_to_3_2", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::SchemaVocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &location,
            const sourcemeta::blaze::SchemaWalker &,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(schema.is_object());

    return declares_openapi_3_1_vocabulary(schema) ||
           (vocabularies.contains(
                SchemaVocabularies::Known::OPENAPI_3_1_BASE) &&
            subschema_at_openapi_3_1_dialect(schema, location));
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    if (declares_openapi_3_1_vocabulary(schema)) {
      rewrite_vocabulary(schema);
      return;
    }

    if (schema.defines("$schema") && schema.at("$schema").is_string() &&
        is_openapi_3_1_dialect(schema.at("$schema").to_string())) {
      schema.assign("$schema",
                    sourcemeta::core::JSON{OPENAPI_3_2_DIALECT_2025_09_17_URL});
      drop_dialect_overrides(schema, true);
    } else {
      mark_dialect_override(schema, OPENAPI_3_2_DIALECT_2025_09_17_URL);
    }
  }

private:
  static constexpr std::string_view OPENAPI_3_1_DIALECT_BASE_URL{
      "https://spec.openapis.org/oas/3.1/dialect/base"};
  static constexpr std::string_view OPENAPI_3_1_DIALECT_2024_11_10_URL{
      "https://spec.openapis.org/oas/3.1/dialect/2024-11-10"};
  static constexpr std::string_view OPENAPI_3_1_DIALECT_2024_10_25_URL{
      "https://spec.openapis.org/oas/3.1/dialect/2024-10-25"};
  static constexpr std::string_view OPENAPI_3_2_DIALECT_2025_09_17_URL{
      "https://spec.openapis.org/oas/3.2/dialect/2025-09-17"};
  static constexpr std::string_view OPENAPI_3_1_VOCABULARY_BASE_URL{
      "https://spec.openapis.org/oas/3.1/vocab/base"};
  static constexpr std::string_view OPENAPI_3_2_VOCABULARY_BASE_URL{
      "https://spec.openapis.org/oas/3.2/vocab/base"};

  static auto is_openapi_3_1_dialect(const std::string_view dialect) -> bool {
    return dialect == OPENAPI_3_1_DIALECT_BASE_URL ||
           dialect == OPENAPI_3_1_DIALECT_2024_11_10_URL ||
           dialect == OPENAPI_3_1_DIALECT_2024_10_25_URL;
  }

  static auto subschema_at_openapi_3_1_dialect(
      const sourcemeta::core::JSON &schema,
      const sourcemeta::blaze::SchemaFrame::Location &location) -> bool {
    const auto current{current_dialect_or_override(schema)};
    if (!current.empty()) {
      return is_openapi_3_1_dialect(current);
    }

    return location.pointer.empty();
  }

  static auto
  declares_openapi_3_1_vocabulary(const sourcemeta::core::JSON &schema)
      -> bool {
    const auto *vocabularies{schema.try_at("$vocabulary")};
    return vocabularies != nullptr && vocabularies->is_object() &&
           vocabularies->defines(OPENAPI_3_1_VOCABULARY_BASE_URL);
  }

  static auto rewrite_vocabulary(sourcemeta::core::JSON &schema) -> void {
    auto &vocabularies{schema.at("$vocabulary")};
    if (vocabularies.defines(OPENAPI_3_2_VOCABULARY_BASE_URL)) {
      vocabularies.erase(OPENAPI_3_1_VOCABULARY_BASE_URL);
      return;
    }

    vocabularies.rename(
        sourcemeta::core::JSON::String{OPENAPI_3_1_VOCABULARY_BASE_URL},
        sourcemeta::core::JSON::String{OPENAPI_3_2_VOCABULARY_BASE_URL});
  }
};
