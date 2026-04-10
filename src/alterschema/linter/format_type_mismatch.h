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
            const sourcemeta::core::SchemaWalker &walker,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::core::SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(schema.is_object() && schema.defines("format") &&
                     schema.at("format").is_string() &&
                     schema.defines("type") && schema.at("type").is_string());

    const auto current_types{parse_schema_type(schema.at("type"))};
    ONLY_CONTINUE_IF(current_types.any());

    const auto &metadata{walker("format", vocabularies)};
    ONLY_CONTINUE_IF(metadata.instances.any() &&
                     (metadata.instances & current_types).none());

    return APPLIES_TO_KEYWORDS("format");
  }
};
