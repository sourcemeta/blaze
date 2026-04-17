class FormatTypeMismatch final : public SchemaTransformRule {
public:
  using mutates = std::false_type;
  using reframe_after_transform = std::false_type;
  FormatTypeMismatch()
      : SchemaTransformRule{
            "format_type_mismatch",
            "The `format` keyword validates string instances but `type` "
            "is not `string`"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::core::SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_2020_12_Validation,
                          Vocabularies::Known::JSON_Schema_2019_09_Validation,
                          Vocabularies::Known::JSON_Schema_Draft_7,
                          Vocabularies::Known::JSON_Schema_Draft_6,
                          Vocabularies::Known::JSON_Schema_Draft_4,
                          Vocabularies::Known::JSON_Schema_Draft_3}) &&
                     schema.is_object() && schema.defines("type") &&
                     schema.at("type").is_string() &&
                     schema.at("type").to_string() != "string" &&
                     schema.defines("format") &&
                     schema.at("format").is_string());
    return APPLIES_TO_KEYWORDS("format", "type");
  }
};
